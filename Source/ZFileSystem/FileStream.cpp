//-------------------------------------------------------------------------------//
//                             ZUNDERBOLT : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Zunderbolt.                                              //
// Zunderbolt is free software: you can redistribute it and/or modify            //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Zunderbolt is distributed in the hope that it will be useful,                 //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Zunderbolt. If not, see <http://www.gnu.org/licenses/>.            //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Zunderbolt in your project but we would appreciate         //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "ZFileSystem/FileStream.h"

#include "ZFileSystem/SFile.h"
#include "ZMemory/Alignment.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include <cstring>

#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>
#endif

#if defined(Z_OS_MAC)
    typedef int error_t; // It exists on Linux but not on MacOSX
#endif


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float FileStream::_REALLOCATION_FACTOR = 1.5f;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

FileStream::FileStream(const puint_z uInitialCapacity) :
                                                                m_path(string_z::GetEmpty()),
                                                                m_rwBuffer(uInitialCapacity, Alignment(4U)), // 4-byte alignment since maximum supported character length is 4 bytes (UTF-32)
                                                                m_uFileSize(0),
                                                                m_uPositionPointer(0),
                                                                m_uBufferStartPosition(0),
                                                                m_uBufferVirtualSize(0),
                                                                m_bIsOpen(false),
                                                                m_bIsWritePending(false),
                                                                m_bWritingIsAllowed(false)
{
    m_rwBuffer.Allocate(uInitialCapacity);
}

FileStream::FileStream(const Path &filePath, const EFileOpenMode &eOpenMode, const puint_z uInitialCapacity, EFileSystemError &eErrorInfo) : 
                                                                                      m_path(filePath),
                                                                                      m_rwBuffer(uInitialCapacity, Alignment(4U)), // 4-byte alignment since maximum supported character length is 4 bytes (UTF-32)
                                                                                      m_uFileSize(0),
                                                                                      m_uPositionPointer(0),
                                                                                      m_uBufferStartPosition(0),
                                                                                      m_uBufferVirtualSize(0),
                                                                                      m_bIsOpen(false),
                                                                                      m_bIsWritePending(false),
                                                                                      m_bWritingIsAllowed(false)
{
    m_rwBuffer.Allocate(uInitialCapacity);
    eErrorInfo = this->Open(filePath, eOpenMode);
}
    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

FileStream::~FileStream()
{
    if(m_bIsOpen)
    {
        this->Close();
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void FileStream::Read(void* pOutput, const puint_z uOutputOffset, const puint_z uOutputSize)
{
    Z_ASSERT_ERROR(uOutputSize > 0, "The output size must not equal zero.");
    Z_ASSERT_ERROR(pOutput != null_z, "The output buffer cannot be null.");
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file must be opened before reading.");

    const puint_z FUTURE_POSITION_POINTER = m_uPositionPointer + uOutputSize;

    Z_ASSERT_WARNING(FUTURE_POSITION_POINTER <= m_uFileSize, "Attempting to read from outside of the file.");

    // If the output size is greater than the remaining bytes, it is fixed so the next read position does not exceed the end of the file
    puint_z uClampedOutputSize = FUTURE_POSITION_POINTER > m_uFileSize ? scast_z(m_uFileSize, puint_z) - m_uPositionPointer :
                                                                                uOutputSize;

    u8_z* pOutputPosition = scast_z(pOutput, u8_z*) + uOutputOffset;

    // Flushes if the buffer is going to be discontinued
    this->_FlushIfPositionDoesNotBelongToBuffer();

    // Calculates the relative position in the read/write buffer. Note: After flushing, operands below are equal and result is zero. The first will never be lower than the second.
    puint_z uPositionInBuffer = m_uPositionPointer - m_uBufferStartPosition;

    // Reallocates the read/write buffer if necessary
    puint_z uBytesFromPositionToEndOfAllocatedMemory = m_rwBuffer.GetSize() - uPositionInBuffer;
    if(uBytesFromPositionToEndOfAllocatedMemory < uClampedOutputSize)
    {
        puint_z uExceedingBytes = uClampedOutputSize - uBytesFromPositionToEndOfAllocatedMemory;
        puint_z uPreviousSize = m_rwBuffer.GetSize();
        this->_ReallocateByFactor(uPreviousSize + uExceedingBytes);
        m_rwBuffer.Allocate(m_rwBuffer.GetSize() - uPreviousSize);
    }

    u8_z* pPositionInBuffer = scast_z(m_rwBuffer.GetPointer(), u8_z*) + uPositionInBuffer;

    // Reads the data from the file
    // Only the bytes that are not in the buffer yet are read directly from the file
    bool bOperationSuccessful = true;
    puint_z uBytesFromPositionToEndOfBuffer = m_uBufferVirtualSize - uPositionInBuffer;

    if(uBytesFromPositionToEndOfBuffer < uClampedOutputSize)
    {
        puint_z uExceedingBytesToReadFromFile = uClampedOutputSize - uBytesFromPositionToEndOfBuffer;
        puint_z uPositionAtEndOfBuffer = m_uPositionPointer + uBytesFromPositionToEndOfBuffer;
        u8_z* pPositionAtEndOfBuffer = pPositionInBuffer + uBytesFromPositionToEndOfBuffer;

        bOperationSuccessful = FileStream::_ReadPlatformImplementation(pPositionAtEndOfBuffer, uExceedingBytesToReadFromFile, uPositionAtEndOfBuffer, m_nativeHandle, m_path);

        if(bOperationSuccessful)
        {
            m_uBufferVirtualSize += uExceedingBytesToReadFromFile;
        }
        
    } // if(uBytesFromPositionToEndOfBuffer < uClampedOutputSize)
            
    if(bOperationSuccessful)
    {
        // Copies the content of the read/write buffer to the output buffer from the current position
        memcpy(pOutputPosition, pPositionInBuffer, uClampedOutputSize);

        m_uPositionPointer = FUTURE_POSITION_POINTER > m_uFileSize ? 
                                                                    m_uFileSize : 
                                                                    FUTURE_POSITION_POINTER;
    }
}

void FileStream::Write(const void* pInput, const puint_z uInputOffset, const puint_z uInputSize)
{
    Z_ASSERT_ERROR(uInputSize > 0, "The output size must not equal zero.");
    Z_ASSERT_ERROR(pInput != null_z, "The output buffer cannot be null.");
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file must be opened before writing.");

    const u8_z* pInputPosition = scast_z(pInput, const u8_z*) + uInputOffset;

    // Flushes if the buffer is going to be discontinued
    this->_FlushIfPositionDoesNotBelongToBuffer();

    // Calculates the relative position in the read/write buffer
    puint_z uPositionInBuffer = m_uPositionPointer - m_uBufferStartPosition;

    // Reallocates the read/write buffer if necessary
    puint_z uBytesFromPositionToEndOfAllocatedMemory = m_rwBuffer.GetSize() - uPositionInBuffer;
    if(uBytesFromPositionToEndOfAllocatedMemory < uInputSize)
    {
        puint_z uExceedingBytes = uInputSize - uBytesFromPositionToEndOfAllocatedMemory;
        puint_z uPreviousSize = m_rwBuffer.GetSize();
        this->_ReallocateByFactor(uPreviousSize + uExceedingBytes);
        m_rwBuffer.Allocate(m_rwBuffer.GetSize() - uPreviousSize);
    }

    u8_z* pPositionInBuffer = scast_z(m_rwBuffer.GetPointer(), u8_z*) + uPositionInBuffer;

    // Copies the content of the input buffer to the read/write buffer from the current position
    memcpy(pPositionInBuffer, pInputPosition, uInputSize);
    m_bIsWritePending = true;
    m_uBufferVirtualSize = uPositionInBuffer + uInputSize > m_uBufferVirtualSize ? uPositionInBuffer + uInputSize :
                                                                                   m_uBufferVirtualSize;
    m_uPositionPointer += uInputSize;
    m_uFileSize = m_uPositionPointer > m_uFileSize ? m_uPositionPointer :
                                                     m_uFileSize;
}

void FileStream::Flush()
{
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    Z_ASSERT_ERROR(!m_bIsWritePending || m_bWritingIsAllowed, "It is not possible to write to the file, it is read-only.");

    bool bOperationSuccessful = true;

    if(m_bIsWritePending)
    {
        // Writes the full buffer
        bOperationSuccessful = FileStream::_WritePlatformImplementation(m_rwBuffer.GetPointer(), m_uBufferVirtualSize, m_uBufferStartPosition, m_nativeHandle, m_path);
    }

    if(bOperationSuccessful)
    {
        m_uBufferStartPosition = m_uPositionPointer;
        m_uBufferVirtualSize = 0;
        m_bIsWritePending = false;
    }
}

void FileStream::MoveBackward(const puint_z uAmount)
{
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    Z_ASSERT_WARNING(m_uPositionPointer >= uAmount, "It is not possible to move backward the specified amount, it would be out of bounds.");

    if(m_uPositionPointer != 0)
    {
        puint_z uFixedAmount = m_uPositionPointer < uAmount ? uAmount - m_uPositionPointer :
                                                                     uAmount;
        m_uPositionPointer -= uFixedAmount;
    }
}

void FileStream::MoveForward(const puint_z uAmount)
{
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");
    Z_ASSERT_WARNING(m_uPositionPointer + uAmount <= m_uFileSize, "It is not possible to move forward the specified amount, it would be out of bounds.");

    puint_z uFixedAmount = m_uPositionPointer + uAmount > m_uFileSize ? m_uFileSize - m_uPositionPointer :
                                                                               uAmount;
    m_uPositionPointer += uFixedAmount;
}

EFileSystemError FileStream::Open(const Path &filePath, const EFileOpenMode &eOpenMode)
{
    Z_ASSERT_ERROR(m_bIsOpen != true, "The file stream is already open.");

    EFileSystemError eErrorInfo = EFileSystemError::E_Unknown;
    const bool FILE_EXISTS = SFile::Exists(filePath, eErrorInfo);

    if((FILE_EXISTS && (eOpenMode == EFileOpenMode::E_Append || eOpenMode == EFileOpenMode::E_Open)) ||
       (!FILE_EXISTS && eOpenMode == EFileOpenMode::E_Create)                                         ||
       eOpenMode == EFileOpenMode::E_CreateOrOverwrite                                                || 
       eOpenMode == EFileOpenMode::E_OpenOrCreate)
    {
        if(FILE_EXISTS)
        {
            FileInfo fileInfo = SFile::GetFileInfo(filePath, eErrorInfo);
            m_uFileSize = scast_z(fileInfo.GetSize(), puint_z);
            m_bWritingIsAllowed = !fileInfo.IsReadOnly();
            
            Z_ASSERT_ERROR(!(fileInfo.IsReadOnly() && eOpenMode == EFileOpenMode::E_CreateOrOverwrite), string_z("The current user does not have permissions to overwrite the file \"") + filePath.GetAbsolutePath() + "\".");
        }
        else
        {
            m_uFileSize = 0;
            m_bWritingIsAllowed = true;
        }

        m_uBufferVirtualSize = 0;
        m_uBufferStartPosition = 0;
        m_path = filePath;

        bool bOperationSuccessful = FileStream::_OpenPlatformImplementation(m_path, eOpenMode, m_bWritingIsAllowed, m_nativeHandle, eErrorInfo);
        
        if(bOperationSuccessful)
        {
            m_bIsOpen = true;
            eErrorInfo = EFileSystemError::E_Success;

            if(eOpenMode == EFileOpenMode::E_Append)
                this->SetPosition(m_uFileSize);
            else
                this->SetPosition(0);

            Z_ASSERT_WARNING(m_uFileSize <= puint_z(-1), "The the file is too large, this class cannot access file offsets over 2^32 - 1 when it is compiled for x86 architecture.");

            if(m_uFileSize > puint_z(-1))
            {
                eErrorInfo = EFileSystemError::E_FileIsTooLarge;
            }
        }
    }
    else if(FILE_EXISTS && eOpenMode == EFileOpenMode::E_Create)
    {
        eErrorInfo = EFileSystemError::E_AlreadyExists;
    }
    else
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

void FileStream::Close()
{
    Z_ASSERT_WARNING(m_bIsOpen == true, "The file was already closed.");

    if(m_bIsOpen)
    {
        if(m_bIsWritePending)
            this->Flush();

        bool bOperationSuccessful = FileStream::_ClosePlarformImplementation(m_nativeHandle, m_path);

        if(bOperationSuccessful)
        {
            m_bIsOpen = false;
        }
    }
}

void FileStream::_ReallocateByFactor(const puint_z uBytes)
{
    const puint_z FINAL_CAPACITY = scast_z(scast_z(uBytes, float) * FileStream::_REALLOCATION_FACTOR, puint_z);
    m_rwBuffer.Reallocate(FINAL_CAPACITY);
}

bool FileStream::_FlushIfPositionDoesNotBelongToBuffer()
{
    bool bPositionDoesNotBelongToBuffer = m_uPositionPointer < m_uBufferStartPosition || m_uPositionPointer > m_uBufferStartPosition + m_uBufferVirtualSize;

    // If the resultant relative position in the buffer is lower than the base position or surpasses the current virtual size, the buffer is flushed
    if(bPositionDoesNotBelongToBuffer)
        this->Flush();

    return bPositionDoesNotBelongToBuffer;
}

#if defined(Z_OS_WINDOWS)

bool FileStream::_ReadPlatformImplementation(u8_z* pOutputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    OVERLAPPED offsets;
    memset(&offsets, 0, sizeof(OVERLAPPED)); // The structure MUST be zero-initialized

    // Sets the offset from where to start reading
#if Z_OS_WINDOWS == 32
        offsets.Offset = uFileOffset;
        offsets.OffsetHigh = 0;
#elif Z_OS_WINDOWS == 64
        const u32_z* pPosition = rcast_z(&uFileOffset, const u32_z*);
        offsets.Offset = pPosition[0];
        offsets.OffsetHigh = pPosition[1];
#endif

    static const BOOL READ_OPERATION_FAILED = 0;
    BOOL uReadFileResult = ::ReadFile(handle, pOutputBuffer, scast_z(uNumberOfBytes, DWORD), NULL, &offsets);

    if(uReadFileResult == READ_OPERATION_FAILED)
    {
        bSuccess = false;
        DWORD uReadFileLastError = ::GetLastError();
        Z_ASSERT_ERROR(uReadFileResult != 0, string_z("An unexpected error occurred when reading from the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(uReadFileLastError) + ".");
    }

    return bSuccess;
}

bool FileStream::_WritePlatformImplementation(const void* pInputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    OVERLAPPED offsets;
    memset(&offsets, 0, sizeof(OVERLAPPED)); // The structure MUST be zero-initialized

    // Sets the offset from where to start reading
#if Z_OS_WINDOWS == 32
        offsets.Offset = uFileOffset;
        offsets.OffsetHigh = 0;
#elif Z_OS_WINDOWS == 64
        const u32_z* pPosition = rcast_z(&uFileOffset, const u32_z*);
        offsets.Offset = pPosition[0];
        offsets.OffsetHigh = pPosition[1];
#endif

    static const BOOL WRITE_OPERATION_FAILED = 0;
    BOOL uWriteFileResult = ::WriteFile(handle, pInputBuffer, scast_z(uNumberOfBytes, DWORD), NULL, &offsets);

    if(uWriteFileResult == WRITE_OPERATION_FAILED)
    {
        bSuccess = false;
            
        DWORD uWriteFileLastError = ::GetLastError();
        Z_ASSERT_WARNING(uWriteFileResult != WRITE_OPERATION_FAILED, string_z("An unexpected error occurred when writing to the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(uWriteFileLastError) + ".");
    }

    return bSuccess;
}

bool FileStream::_OpenPlatformImplementation(const Path &filePath, const EFileOpenMode &eOpenMode, const bool bIsWritingAllowed, FileStream::NativeHandle &handle, EFileSystemError &eErrorInfo)
{
    bool bSuccess = true;

    ArrayResult<i8_z> arPath = filePath.ToString().ToBytes(string_z::GetLocalEncodingUTF16());
    const wchar_t* szPath = rcast_z(arPath.Get(), wchar_t*);
    DWORD uAccess = bIsWritingAllowed ? GENERIC_READ | GENERIC_WRITE : 
                                        GENERIC_READ;
    DWORD uOpenMode = 0;

    switch(eOpenMode)
    {
    case EFileOpenMode::E_Append:
    case EFileOpenMode::E_Open:
        uOpenMode = OPEN_EXISTING;
        break;
    case EFileOpenMode::E_Create:
        uOpenMode = CREATE_NEW;
        break;
    case EFileOpenMode::E_CreateOrOverwrite:
        uOpenMode = CREATE_ALWAYS;
        break;
    case EFileOpenMode::E_OpenOrCreate:
        uOpenMode = OPEN_ALWAYS;
        break;
    default:
        break;
    }

    handle = ::CreateFileW(szPath, uAccess, FILE_SHARE_READ, NULL, uOpenMode, FILE_FLAG_RANDOM_ACCESS, NULL);

    const bool FILE_OPENED_SUCCESSFULLY = handle != INVALID_HANDLE_VALUE;

    if(!FILE_OPENED_SUCCESSFULLY)
    {
        bSuccess = false;
        DWORD uCreateFileWLastError = ::GetLastError();
        Z_ASSERT_ERROR(handle != INVALID_HANDLE_VALUE, string_z("An unexpected error occurred when opening the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(uCreateFileWLastError) + ".");

        if(uCreateFileWLastError == ERROR_ACCESS_DENIED)
            eErrorInfo = EFileSystemError::E_NoPermissions;
        else
            eErrorInfo = EFileSystemError::E_Unknown;
    }

    return bSuccess;
}

bool FileStream::_ClosePlarformImplementation(const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    static const BOOL CLOSE_OPERATION_FAILED = 0;
    BOOL uCloseHandleResult = ::CloseHandle(handle);

    if(uCloseHandleResult == CLOSE_OPERATION_FAILED)
    {
        bSuccess = false;
        DWORD uCloseHandleLastError = ::GetLastError();
        Z_ASSERT_ERROR(uCloseHandleResult != 0, string_z("An unexpected error occurred when closing the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(uCloseHandleLastError) + ".");
    }

    return bSuccess;
}

#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)

bool FileStream::_ReadPlatformImplementation(u8_z* pOutputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    ssize_t nResult = pread(handle, pOutputBuffer, uNumberOfBytes, uFileOffset);
        
    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        Z_ASSERT_ERROR(nResult >= 0, string_z("An unexpected error occurred when reading from the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(lastError) + ".");
    }

    return bSuccess;
}

bool FileStream::_WritePlatformImplementation(const void* pInputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    ssize_t nResult = pwrite(handle, pInputBuffer, uNumberOfBytes, uFileOffset);
        
    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        Z_ASSERT_ERROR(nResult >= 0, string_z("An unexpected error occurred when writing to the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(lastError) + ".");
    }

    return bSuccess;
}

bool FileStream::_OpenPlatformImplementation(const Path &filePath, const EFileOpenMode &eOpenMode, const bool bIsWritingAllowed, FileStream::NativeHandle &handle, EFileSystemError &eErrorInfo)
{
    bool bSuccess = true;

    using ArrayResult;
    using i8_z;
    using ETextEncoding;

    ArrayResult<i8_z> szPath = filePath.ToString().ToBytes(ETextEncoding::E_UTF8);
        
    int nAccess = bIsWritingAllowed ? O_RDWR: 
                                      O_RDONLY;
    int nPermissions = S_IRWXU; // Read, write and execution permissions for the owner
    int nOpenMode = 0;

    switch(eOpenMode)
    {
    case EFileOpenMode::E_Append:
    case EFileOpenMode::E_Open:
        nOpenMode = 0;
        break;
    case EFileOpenMode::E_Create:
        nOpenMode = O_CREAT | O_EXCL;
        break;
    case EFileOpenMode::E_CreateOrOverwrite:
        nOpenMode = O_CREAT | O_TRUNC;
        break;
    case EFileOpenMode::E_OpenOrCreate:
        nOpenMode = O_CREAT;
        break;
    default:
        break;
    }
        
    handle = open(szPath.Get(), nAccess | nOpenMode, nPermissions);

    const bool FILE_OPENED_SUCCESSFULLY = handle >= 0;
        
    if(!FILE_OPENED_SUCCESSFULLY)
    {
        bSuccess = false;
        error_t lastError = errno;
        Z_ASSERT_ERROR(handle >= 0, string_z("An unexpected error occurred when opening the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(lastError) + ".");
            
        if(lastError == EACCES)
            eErrorInfo = EFileSystemError::E_NoPermissions;
        else
            eErrorInfo = EFileSystemError::E_Unknown;
    }

    return bSuccess;
}

bool FileStream::_ClosePlarformImplementation(const FileStream::NativeHandle &handle, const Path &filePath)
{
    bool bSuccess = true;

    int nResult = close(handle);

    if(nResult < 0)
    {
        bSuccess = false;
        error_t lastError = errno;
        Z_ASSERT_ERROR(nResult >= 0, string_z("An unexpected error occurred when closing the file \"") + filePath.GetAbsolutePath() + "\". The error code was: " + string_z::FromInteger(lastError) + ".");
    }

    return bSuccess;
}

#endif


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

puint_z FileStream::GetLength() const
{
    Z_ASSERT_WARNING(m_bIsOpen == true, "The file is not open.");

    return m_uFileSize;
}

puint_z FileStream::GetPosition() const
{
    return m_uPositionPointer;
}

void FileStream::SetPosition(const puint_z uPosition)
{
    Z_ASSERT_WARNING(m_bIsOpen == true, "The file is not open.");
    Z_ASSERT_WARNING(uPosition <= m_uFileSize, "It is not possible to set the specified position, it would be out of bounds.");

    if(uPosition <= m_uFileSize)
        m_uPositionPointer = uPosition;
}

Path FileStream::GetPath() const
{
    return m_path;
}

bool FileStream::IsOpen() const
{
    return m_bIsOpen;
}

FileStream::NativeHandle FileStream::GetNativeHandle() const
{
    Z_ASSERT_ERROR(m_bIsOpen == true, "The file is not open.");

    return m_nativeHandle;
}


} // namespace z