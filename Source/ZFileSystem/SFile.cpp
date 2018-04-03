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

#include "ZFileSystem/SFile.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZTime/DateTime.h"
#include "ZTime/TimeZone.h"
#include "ZTiming/LocalTimeZone.h"
#include "ZTiming/Stopwatch.h"
#include "ZThreading/SThisThread.h"

#if defined(Z_OS_WINDOWS)
    #include <Windows.h>
#elif defined(Z_OS_MAC)
    #include <sys/attr.h>
    #include <unistd.h>
#endif


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

EFileSystemError SFile::Delete(const Path &file)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SFile::_ConvertToBoostPath(file);

    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    if(SFile::Exists(file, eErrorCode) && eErrorCode == EFileSystemError::E_Success) // This check is necessary because remove does not return an error when the file does not exist
    {
        boost::system::error_code removeErrorCode;
        boost::filesystem::remove(filePath, removeErrorCode);
        eErrorCode = SFile::_ConvertErrorCodeToFileSystemError(removeErrorCode);
    }
    else if(eErrorCode == EFileSystemError::E_Success)
    {
        eErrorCode = EFileSystemError::E_DoesNotExist;
    }

    return eErrorCode;
}

EFileSystemError SFile::Move(const Path &file, const Path& newLocation, const bool bReplace)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The source path (\"") + file.ToString() + "\") must refer to a file.");
    Z_ASSERT_ERROR(newLocation.IsDirectory(), string_z("The destination path (\"") + newLocation.ToString() + "\") must refer to a directory.");

    Path destination = newLocation;
    destination.SetFilenameAndExtension(file.GetFilename());

    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    
    if(!SFile::Exists(destination, eErrorCode) || bReplace)
    {
        // Moves and replaces the file
        if(eErrorCode == EFileSystemError::E_Success)
        {
            // The copy first
            eErrorCode = SFile::Copy(file, newLocation, bReplace);

            // Then the deletion of the original directory
            if(eErrorCode == EFileSystemError::E_Success)
            {
                SFile::_WaitForCreation(SFile::_ConvertToBoostPath(destination));

                eErrorCode = SFile::Delete(file);
            }
        }
    }
    else
    {
        eErrorCode = EFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EFileSystemError SFile::Rename(Path &file, const string_z &strNewFileName, const bool bRenameExtension)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The input path (\"") + file.ToString() + "\") must refer to a file.");

    Path renamedPath = file;

    if(bRenameExtension)
        renamedPath.SetFilenameAndExtension(strNewFileName);
    else
        renamedPath.SetFilename(strNewFileName);

    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    if(!SFile::Exists(renamedPath, eErrorCode)) // This check is necessary because rename returns "success" instead of "already exists" when there is already a file with the target name
    {
        boost::filesystem::path filePath = SFile::_ConvertToBoostPath(file);
        boost::filesystem::path newFilePath = SFile::_ConvertToBoostPath(renamedPath);

        boost::system::error_code renameErrorCode;
        boost::filesystem::rename(filePath, newFilePath, renameErrorCode);

        if(renameErrorCode == boost::system::errc::success)
        {
            file = renamedPath;
        }

        eErrorCode = SFile::_ConvertErrorCodeToFileSystemError(renameErrorCode);
    }
    else
    {
        eErrorCode = EFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EFileSystemError SFile::Copy(const Path &file, const Path& locationToCopyTo, const bool bReplace)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The source path (\"") + file.ToString() + "\") must refer to a file.");
    Z_ASSERT_ERROR(locationToCopyTo.IsDirectory(), string_z("The destination path (\"") + locationToCopyTo.ToString() + "\") must refer to a directory.");

    // Paths transformations
    Path absoluteDirectory = file.GetAbsolutePath();
    Path absoluteLocationToCopyTo = locationToCopyTo.GetAbsolutePath();
    absoluteLocationToCopyTo.SetFilenameAndExtension(file.GetFilename());

    boost::filesystem::path filePath = SFile::_ConvertToBoostPath(absoluteDirectory);
    boost::filesystem::path newLocationPath = SFile::_ConvertToBoostPath(absoluteLocationToCopyTo);

    // Copies the directory
    const boost::filesystem::copy_option COPY_OPTION(bReplace ? boost::filesystem::copy_option::overwrite_if_exists : 
                                                                boost::filesystem::copy_option::fail_if_exists);
    boost::system::error_code copyErrorCode;
    boost::filesystem::copy_file(filePath, newLocationPath, COPY_OPTION, copyErrorCode);

    return SFile::_ConvertErrorCodeToFileSystemError(copyErrorCode);
}

bool SFile::Exists(const Path &file, EFileSystemError& eErrorInfo)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SFile::_ConvertToBoostPath(file);

    boost::system::error_code errorCode;
    bool bExists = boost::filesystem::exists(filePath, errorCode);

    eErrorInfo = SFile::_ConvertErrorCodeToFileSystemError(errorCode);

    if(eErrorInfo == EFileSystemError::E_DoesNotExist)
        eErrorInfo = EFileSystemError::E_Success;

    return bExists;
}

FileInfo SFile::GetFileInfo(const Path &file, EFileSystemError &eErrorInfo)
{
    Z_ASSERT_ERROR(file.IsFile(), string_z("The input path (\"") + file.ToString() + "\") must refer to a file.");

    boost::filesystem::path filePath = SFile::_ConvertToBoostPath(file);
    uintmax_t uFileSize = 0;
    DateTime lastModificationDateTime = DateTime::GetUndefinedDate();
    DateTime creationDateTime = DateTime::GetUndefinedDate();
    bool bIsReadOnly = false;

    // Gets the size of the file
    boost::system::error_code errorCode;
    uFileSize = boost::filesystem::file_size(filePath, errorCode);

    // Gets the last modification date and time
    if(errorCode == boost::system::errc::success)
    {
        // Number of seconds passed since 01/01/1970
        time_t lastModificationTime = boost::filesystem::last_write_time(filePath, errorCode);

        if(errorCode == boost::system::errc::success)
        {
            static const DateTime EPOCH(1970, 1, 1, TimeZone::UTC);
            TimeSpan seconds(0, 0, 0, lastModificationTime, 0, 0, 0);
            lastModificationDateTime = DateTime(EPOCH + seconds, LocalTimeZone().Get());
        }
    }

    // Gets the creation date and time
    if(errorCode == boost::system::errc::success)
    {
#if defined(Z_OS_LINUX)
        // There is no way to get the creation date of a file on Linux
        creationDateTime = lastModificationDateTime;
#else
        creationDateTime = DateTime(SFile::_GetFileCreationDateTime(file), LocalTimeZone().Get());
#endif
    }

    // Gets the file permissions
    if(errorCode == boost::system::errc::success)
    {
        boost::filesystem::file_status fileStatus = boost::filesystem::status(filePath, errorCode);

        if(errorCode == boost::system::errc::success)
        {
            boost::filesystem::perms eFilePermissions = fileStatus.permissions();
            bIsReadOnly = (eFilePermissions & boost::filesystem::owner_write) == 0;
        }
    }

    eErrorInfo = SFile::_ConvertErrorCodeToFileSystemError(errorCode);

    return FileInfo(file, uFileSize, creationDateTime, lastModificationDateTime, bIsReadOnly);
}

boost::filesystem::path SFile::_ConvertToBoostPath(const Path &pathToConvert)
{
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    static const ETextEncoding PATH_ENCODING = ETextEncoding::E_UTF8;
#elif defined(Z_OS_WINDOWS)
    static const ETextEncoding PATH_ENCODING = string_z::GetLocalEncodingUTF16();
#endif

    ArrayResult<i8_z> arBytesDirectory = pathToConvert.ToString().ToBytes(PATH_ENCODING);
    boost::filesystem::path::value_type* szPath = (boost::filesystem::path::value_type*)arBytesDirectory.Get();
    return boost::filesystem::path(szPath);
}

string_z SFile::_ConvertPathToString(const boost::filesystem::path &pathToConvert)
{
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    return string_z(pathToConvert.c_str(), scast_z(strlen(pathToConvert.c_str()), int), ETextEncoding::E_UTF8);
#elif defined(Z_OS_WINDOWS)
    return string_z((i8_z*)pathToConvert.c_str(), scast_z(wcslen(pathToConvert.c_str()) * sizeof(boost::filesystem::path::value_type), int), string_z::GetLocalEncodingUTF16());
#endif
}

EFileSystemError SFile::_ConvertErrorCodeToFileSystemError(const boost::system::error_code &errorCode)
{
    EFileSystemError eErrorInfo = EFileSystemError::E_Unknown;
    boost::system::error_condition posixError = errorCode.default_error_condition();

    if(posixError == boost::system::errc::success)
    {
        eErrorInfo = EFileSystemError::E_Success;
    }
    else if(posixError == boost::system::errc::no_such_file_or_directory)
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }
    else if(posixError == boost::system::errc::file_exists)
    {
        eErrorInfo = EFileSystemError::E_AlreadyExists;
    }
    else if(posixError == boost::system::errc::filename_too_long)
    {
        eErrorInfo = EFileSystemError::E_NameIsTooLong;
    }
    else if(posixError == boost::system::errc::permission_denied)
    {
        eErrorInfo = EFileSystemError::E_NoPermissions;
    }
    else if(posixError == boost::system::errc::file_too_large)
    {
        eErrorInfo = EFileSystemError::E_FileIsTooLarge;
    }
    else if(posixError == boost::system::errc::no_space_on_device)
    {
        eErrorInfo = EFileSystemError::E_NoSpaceInDevice;
    }
    else
    {
        eErrorInfo = EFileSystemError::E_Unknown;
    }

    return eErrorInfo;
}

bool SFile::_WaitForCreation(const boost::filesystem::path &filePath)
{
    static const u64_z MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

    Stopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(!boost::filesystem::exists(filePath) && !bTooMuchTime)
    {
        SThisThread::Yield();
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    Z_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}

#if defined(Z_OS_WINDOWS)

DateTime SFile::_GetFileCreationDateTime(const Path &file)
{
    // GetFileAttributesExW returns the number of hundreds of nanosecond since January 1, 1601 (UTC)
    static const DateTime SYSTEM_EPOCH(1601, 1, 1, TimeZone::UTC);

    // Gets the raw data from the system
    WIN32_FILE_ATTRIBUTE_DATA fileAttributes;
    ArrayResult<i8_z> arPathString = file.ToString().ToBytes(string_z::GetLocalEncodingUTF16());
    BOOL bResult = GetFileAttributesExW(rcast_z(arPathString.Get(), wchar_t*), GetFileExInfoStandard, &fileAttributes);

    Z_ASSERT_ERROR(bResult != 0, "An unexpected error ocurred when obtaining the file attributes.");
    
    // Uses an intermediate structure to extract the number of hundreds of nanoseconds
    ULARGE_INTEGER uTimePassedSinceEpochInHundredsOfNanoseconds;
    uTimePassedSinceEpochInHundredsOfNanoseconds.LowPart = fileAttributes.ftCreationTime.dwLowDateTime;
    uTimePassedSinceEpochInHundredsOfNanoseconds.HighPart = fileAttributes.ftCreationTime.dwHighDateTime;

    // Builds a time span from the obtained data
    TimeSpan uTimeSinceEpoch(uTimePassedSinceEpochInHundredsOfNanoseconds.QuadPart);

    // The result is the system epoch plus the time passed since then
    return SYSTEM_EPOCH + uTimeSinceEpoch;
}

#elif defined(Z_OS_MAC)

DateTime SFile::_GetFileCreationDateTime(const Path &file)
{
    using DateTime;
    using TimeSpan;
    using TimeZone;
    
    // getattrlist returns the number of seconds since January 1, 1970 (UTC)
    static const DateTime SYSTEM_EPOCH(1970, 1, 1, TimeZone::UTC);

    struct FileCreationDataStructure
    {
        uint32_t length;
        timespec creationTime;
    };

    struct attrlist al;
    al.bitmapcount = ATTR_BIT_MAP_COUNT;
    al.reserved = 0;
    al.commonattr = ATTR_CMN_CRTIME;
    al.volattr = 0;
    al.dirattr = 0;
    al.fileattr = 0;
    al.forkattr = 0;
    
    ArrayResult<i8_z> arPathString = file.ToString().ToBytes(ETextEncoding::E_UTF8);
    FileCreationDataStructure fileCreationData;
    int nResult = getattrlist(arPathString.Get(), &al, &fileCreationData, sizeof(fileCreationData), FSOPT_REPORT_FULLSIZE);
    
    Z_ASSERT_ERROR(nResult == 0, "An unexpected error ocurred when obtaining the file attributes.");
    
    return SYSTEM_EPOCH + TimeSpan(0, 0, 0, fileCreationData.creationTime.tv_sec, 0, 0, 0);
}

#endif

} // namespace z