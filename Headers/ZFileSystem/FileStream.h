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

#ifndef __FILESTREAM__
#define __FILESTREAM__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZFileSystem/EFileSystemError.h"
#include "ZMemory/LinearAllocator.h"
#include "ZFileSystem/EFileOpenMode.h"
#include "ZFileSystem/Path.h"

#if defined(Z_OS_WINDOWS)
    #include <Windows.h>
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    #include <unistd.h>
#endif


namespace z
{

/// <summary>
/// Represents a stream of data stored in a device managed by a file system.
/// </summary>
/// <remarks>
/// It keeps an internal pointer to a position of the stream, which allows reading or writing a group of bytes from there forward.<br/>
/// The internal pointer can be moved back and forth as necessary, and it will be moved automatically after every read / write operation.<br/>
/// Streams grow as more memory is required to store the incoming bytes.<br/>
/// With the aim of reducing as much as possible the number of read/write operations performed in secondary memory, which is terribly slow in relative terms,
/// this class stores an internal read/write buffer. When reading, the file is accessed only when the content is not already in the buffer; when writing,
/// the content is stored in the buffer until Flush is called, sending the entire content of the buffer to the file. This implies that it is possible to
/// write and read many times the same contiguous block of bytes without a big performance hit.<br/>
/// The Flush method will not be called internally unless the position pointer is set to a non-contiguous place in the stream; for example, if the buffer contains 
/// bytes from position 5 to 10, writing or reading at position 11 will just extend the buffer; however, doing the same at either position 4 or 12 will produce a call 
/// to Flush before the read or write operation takes place.<br/>
/// The range of positions this class can point to is limited by machine's address space. When compiling for 32-bits systems, only files whose size is 4 GB or less can be operated;
/// 64-bits compilations allow up to 16 EB.<br/>
/// A file stream can be reutilized after it is closed, to operate with either the same file or another one.
/// </remarks>
class Z_LAYER_FILESYSTEM_SYMBOLS FileStream
{
    // TYPEDEFS
    // ---------------
public:
    
#if defined(Z_OS_WINDOWS)

    typedef HANDLE NativeHandle;

#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)

    typedef int NativeHandle;

#endif
    
    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float _REALLOCATION_FACTOR;

    /// <summary>
    /// The default size (in bytes) of the batches used in the copy operation.
    /// </summary>
    static const puint_z _COPY_BATCH_SIZE = 4096U; // 4096 bytes is apparently the most common cluster size in a file system. It should be tuned to improve performance


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that initializes a file stream.
    /// </summary>
    /// <remarks>
    /// The instance is ready for opening a file and operate with it.<br/>
    /// The internal buffer is 4-byte aligned.
    /// </remarks>
    /// <param name="uInitialCapacity">[IN] The initial capacity of the internal buffer, in bytes. It must not equal zero.</param>
    FileStream(const puint_z uInitialCapacity);

    /// <summary>
    /// Constructor that opens or creates a file stream, receiving also the initial capacity of the internal buffer.
    /// </summary>
    /// <remarks>
    /// The internal pointer's position is set to zero.<br/>
    /// The internal buffer is 4-byte aligned.<br/>
    /// It calls the Open method.<br/>
    /// If the current user has no writing permissions on the file, it will be opened as read-only.
    /// </remarks>
    /// <param name="filePath">[IN] The path of a file in the file system. It must neither be empty nor contain invalid characters.</param>
    /// <param name="eOpenMode">[IN] The way the file will be opened.</param>
    /// <param name="uInitialCapacity">[IN] The initial capacity of the internal buffer, in bytes. It must not equal zero.</param>
    /// <param name="eErrorInfo">[OUT] An error code representing the result of the operation. If nothing unexpected occurred, its value will be Success.</param>
    FileStream(const Path &filePath, const EFileOpenMode &eOpenMode, const puint_z uInitialCapacity, EFileSystemError &eErrorInfo);


private:

    // Hidden
    FileStream(const FileStream &fileStream);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// If the file is open, it will be closed.
    /// </remarks>
    ~FileStream();


    // METHODS
    // ---------------
private:

    // Hidden
    FileStream& operator=(const FileStream &fileStream);

public:

    /// <summary>
    /// Reads a group of bytes from the stream and copies them to an output buffer.
    /// </summary>
    /// <remarks>
    /// The internal pointer is moved forward by the number of bytes read, after the operation. If the number of bytes
    /// to read from the current position exceed the buffer's limits, the pointer will be moved to the lastest valid position.<br/>
    /// If the file is modified externally by another process, these changes may not be reflected in the obtained data if the internal buffer is not flushed previously.
    /// The real file will be accessed only in case the requested block of bytes is not already cached in the buffer.<br/>
    /// Flush is automatically called before the read operation takes place when the position pointer has been previously set to a non-contiguous position.
    /// </remarks>
    /// <param name="pOutput">[IN] The output buffer where bytes are to be copied. Is must not be null.</param>
    /// <param name="uOutputOffset">[IN] The offset, in bytes, from where to start writing to the output buffer.</param>
    /// <param name="uOutputSize">[IN] The number of bytes to be read. It must not equal zero.</param>
    void Read(void* pOutput, const puint_z uOutputOffset, const puint_z uOutputSize);
    
    /// <summary>
    /// Copies a group of bytes from an input buffer to the stream.
    /// </summary>
    /// <remarks>
    /// The internal pointer is moved forward by the number of bytes written, after the operation.<br/>
    /// The stream will grow as more memory is required to store new data.<br/>
    /// If the position of the internal pointer is not set to the end of the buffer, the stream will be partially overwritten.<br/>
    /// The real file will be updated only when Flush method is called.<br/>
    /// Flush is automatically called before the write operation takes place when the position pointer has been previously set to a non-contiguous position.<br/>
    /// The length of the stream will increase, if bytes are appended, even though the Flush method has not been called.<br/>
    /// The current user needs to have writing permissions on the file.
    /// </remarks>
    /// <param name="pInput">[IN] The input buffer from which bytes are to be copied. Is must not be null.</param>
    /// <param name="uInputOffset">[IN] The offset, in bytes, from where to start reading from the input buffer.</param>
    /// <param name="uInputSize">[IN] The number of bytes to be written. It must not equal zero.</param>
    void Write(const void* pInput, const puint_z uInputOffset, const puint_z uInputSize);
    
    /// <summary>
    /// Copies the content of the stream to another stream of any other kind.
    /// </summary>
    /// <remarks>
    /// Bytes are copied sequentially as batches of an arbitrary size, starting at the specified offset.<br/>
    /// The internal pointer of both streams is moved forward by the number of bytes copied.<br/>
    /// The destination stream will grow as more memory is required to store new data.<br/>
    /// The Flush method will not be called during this operation.
    /// </remarks>
    /// <typeparam name="StreamT">The type of the destination stream.</typeparam>
    /// <param name="destinationStream">[OUT] The destination stream to which the content will be copied.</param>
    /// <param name="uSourceOffset">[IN] The offset, in bytes, from where to start reading from the source stream (zero means the first position). 
    /// It must be lower than the length of the source stream.</param>
    /// <param name="uDestinationOffset">[IN] The offset, in bytes, from where to start writing to the destination stream (zero means the first position). 
    /// It must be lower than or equal to the length of the destination stream.</param>
    /// <param name="uNumberOfBytes">[IN] The number of bytes to copy. It must be lower than the length of the source stream minus the source offset.</param>
    /// <param name="uBatchSize">[IN] The size, in bytes, of every copied batch. It must be greater than zero. It may affect the performance of the operation.</param>
    template<class StreamT>
    void CopyTo(StreamT &destinationStream, const puint_z uSourceOffset, const puint_z uDestinationOffset, 
                                            const puint_z uNumberOfBytes, const puint_z uBatchSize=FileStream::_COPY_BATCH_SIZE)
    {
        Z_ASSERT_ERROR(uBatchSize > 0, "The number of bytes per batch must be greater than zero.");
        Z_ASSERT_ERROR(uSourceOffset < this->GetLength(), "The offset of the source stream is out of bounds.");
        Z_ASSERT_ERROR(uDestinationOffset <= destinationStream.GetLength(), "The offset of the destination stream is out of bounds.");
        Z_ASSERT_ERROR(uSourceOffset + uNumberOfBytes <= this->GetLength(), "The number of bytes to copy from the source, starting at the given offset, exceeds the limits of the stream.");

        // If offsets point to valid positions
        if(uSourceOffset < this->GetLength() && uDestinationOffset <= destinationStream.GetLength())
        {
            // The stream is copied batch by batch
            const puint_z NUMBER_OF_BATCHES = uNumberOfBytes / uBatchSize;
            u8_z* arBatch = new u8_z[uBatchSize];
            
            this->SetPosition(uSourceOffset);
            destinationStream.SetPosition(uDestinationOffset);

            for(puint_z i = 0; i < NUMBER_OF_BATCHES; ++i)
            {
                this->Read(arBatch, 0, uBatchSize);
                destinationStream.Write(arBatch, 0, uBatchSize);
            }

            const puint_z REST_OF_BYTES = uNumberOfBytes % uBatchSize;

            if(REST_OF_BYTES != 0)
            {
                this->Read(arBatch, 0, REST_OF_BYTES);
                destinationStream.Write(arBatch, 0, REST_OF_BYTES);
            }

            delete[] arBatch;
        }
    }

    /// <summary>
    /// Empties all the intermediate buffers and sends the data to the final storage support.
    /// </summary>
    /// <remarks>
    /// The current user must have writing permissions on the file in case some bytes are needed to be written.
    /// </remarks>
    void Flush();

    /// <summary>
    /// Moves the internal pointer to a prior position.
    /// </summary>
    /// <param name="uAmount">[IN] The number of bytes to move back the internal pointer's position. If it is already at the first position, it does nothing.</param>
    void MoveBackward(const puint_z uAmount);

    /// <summary>
    /// Moves the internal pointer to a posterior position.
    /// </summary>
    /// <param name="uAmount">[IN] The number of bytes to move forward the internal pointer's position. If it is already at the latest position, it does nothing.</param>
    void MoveForward(const puint_z uAmount);

    /// <summary>
    /// Opens or creates a file stream.
    /// </summary>
    /// <remarks>
    /// The internal pointer's position is set to zero.<br/>
    /// The file stream must not be already opened.<br/>
    /// If the current user has no writing permissions on the file, it will be opened as read-only.
    /// </remarks>
    /// <param name="filePath">[IN] The path of a file in the file system. It must neither be empty nor contain invalid characters.</param>
    /// <param name="eOpenMode">[IN] The way the file will be opened.</param>
    /// <returns>
    /// An error code representing the result of the operation. If nothing unexpected occurred, it returns Success.
    /// </returns>
    EFileSystemError Open(const Path &filePath, const EFileOpenMode &eOpenMode);

    /// <summary>
    /// Closes the file stream.
    /// </summary>
    /// <remarks>
    /// The Flush method is called before the stream is closed.
    /// </remarks>
    void Close();

private:

    /// <summary>
    /// Increases the capacity of the buffer, reserving more memory than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uBytes">[IN] The number of bytes for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const puint_z uBytes);

    /// <summary>
    /// Calls Flush if the current position pointer is not contained in the internal buffer.
    /// </summary>
    /// <returns>
    /// True if the Flush method was called; False otherwise.
    /// </returns>
    bool _FlushIfPositionDoesNotBelongToBuffer();
    
    /// <summary>
    /// The platform-specific implementation of the Read operation.
    /// </summary>
    /// <param name="pOutputBuffer">[OUT] The output buffer to which read bytes are to be copied.</param>
    /// <param name="uNumberOfBytes">[IN] The number of bytes to copy to the output buffer.</param>
    /// <param name="uFileOffset">[IN] The position to start copying from the file.</param>
    /// <param name="handle">[IN] The operating system file handle.</param>
    /// <param name="filePath">[IN] The path to the file.</param>
    /// <returns>
    /// True if the operation succeed; False otherwise.
    /// </returns>
    static bool _ReadPlatformImplementation(u8_z* pOutputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath);
    
    /// <summary>
    /// The platform-specific implementation of the Write operation.
    /// </summary>
    /// <param name="pInputBuffer">[IN] The input buffer whose content is to be written to the file.</param>
    /// <param name="uNumberOfBytes">[IN] The number of bytes to copy to the file.</param>
    /// <param name="uFileOffset">[IN] The position to start copying to the file.</param>
    /// <param name="handle">[IN] The operating system file handle.</param>
    /// <param name="filePath">[IN] The path to the file.</param>
    /// <returns>
    /// True if the operation succeed; False otherwise.
    /// </returns>
    static bool _WritePlatformImplementation(const void* pInputBuffer, const puint_z uNumberOfBytes, const puint_z uFileOffset, const FileStream::NativeHandle &handle, const Path &filePath);
    
    /// <summary>
    /// The platform-specific implementation of the Open operation.
    /// </summary>
    /// <param name="filePath">[IN] The path to the file.</param>
    /// <param name="eOpenMode">[IN] The way the operating system will open the file.</param>
    /// <param name="bIsWritingAllowed">[IN] Indicates whether the current user has enough permissions to open the file.</param>
    /// <param name="handle">[OUT] The operating system file handle.</param>
    /// <param name="eErrorInfo">[OUT] The result of the operation.</param>
    /// <returns>
    /// True if the operation succeed; False otherwise.
    /// </returns>
    static bool _OpenPlatformImplementation(const Path &filePath, const EFileOpenMode &eOpenMode, const bool bIsWritingAllowed, FileStream::NativeHandle &handle, EFileSystemError &eErrorInfo);
    
    /// <summary>
    /// The platform-specific implementation of the Close operation.
    /// </summary>
    /// <param name="handle">[IN] The operating system file handle.</param>
    /// <param name="filePath">[IN] The path to the file.</param>
    /// <returns>
    /// True if the operation succeed; False otherwise.
    /// </returns>
    static bool _ClosePlarformImplementation(const FileStream::NativeHandle &handle, const Path &filePath);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the length of the stream, in bytes.
    /// </summary>
    /// <returns>
    /// The number of bytes contained in the stream.
    /// </returns>
    puint_z GetLength() const;

    /// <summary>
    /// Gets the position of the internal pointer in the stream.
    /// </summary>
    /// <returns>
    /// The byte number to which the internal pointer is pointing to.
    /// </returns>
    puint_z GetPosition() const;

    /// <summary>
    /// Sets the position of the internal pointer.
    /// </summary>
    /// <param name="uPosition">[IN] The new position of the internal pointer. It must be lower than or equal to the length of the stream 
    /// or it will not be set.</param>
    void SetPosition(const puint_z uPosition);

    /// <summary>
    /// Gets the path of the file.
    /// </summary>
    /// <returns>
    /// The path of the file that is being read/written.
    /// </returns>
    Path GetPath() const;

    /// <summary>
    /// Indicates whether the file is open or not.
    /// </summary>
    /// <returns>
    /// True if the file is open; False otherwise.
    /// </returns>
    bool IsOpen() const;
    
    /// <summary>
    /// Gets the native handle generated by the operating system.
    /// </summary>
    /// <returns>
    /// A handle as the native type for the current operating system.
    /// </returns>
    FileStream::NativeHandle GetNativeHandle() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The path of the file.
    /// </summary>
    Path m_path;

    /// <summary>
    /// A read/write buffer used to cache the content of the file.
    /// </summary>
    LinearAllocator m_rwBuffer;
    
    /// <summary>
    /// The size of the file, in bytes. Although the Flush method has not been called, if the length of the stream is increased, 
    /// this attribute will store the size that the file would have once it is updated.
    /// </summary>
    puint_z m_uFileSize;

    /// <summary>
    /// A native handle for the file in the local file system.
    /// </summary>
    FileStream::NativeHandle m_nativeHandle;

    /// <summary>
    /// The position of the internal reading/writing pointer.
    /// </summary>
    puint_z m_uPositionPointer;

    /// <summary>
    /// The position in the stream of the first byte stored in the read/write buffer.
    /// </summary>
    puint_z m_uBufferStartPosition;

    /// <summary>
    /// The amount of cached bytes.
    /// </summary>
    puint_z m_uBufferVirtualSize;

    /// <summary>
    /// Indicates whether the file is open or not.
    /// </summary>
    bool m_bIsOpen;

    /// <summary>
    /// Indicates whether there are pending bytes to be sent to the file.
    /// </summary>
    bool m_bIsWritePending;

    /// <summary>
    /// Indicates whether the user has permissions to write to the file or not.
    /// </summary>
    bool m_bWritingIsAllowed;
};

} // namespace z

#endif // __FILESTREAM__
