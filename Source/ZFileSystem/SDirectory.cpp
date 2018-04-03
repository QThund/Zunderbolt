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

#include "ZFileSystem/SDirectory.h"

#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "ZTime/TimeZone.h"
#include "ZTiming/LocalTimeZone.h"
#include "ZCommon/Assertions.h"
#include "ZTiming/Stopwatch.h"
#include "ZThreading/SThisThread.h"


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

EFileSystemError SDirectory::Delete(const Path &directory)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

    EFileSystemError eErrorCode = EFileSystemError::E_Success;
    boost::system::error_code removeErrorCode;

    if(SDirectory::Exists(directory, eErrorCode) && eErrorCode == EFileSystemError::E_Success) // This check is necessary because remove_all does not return an error when the directory does not exist
    {
        boost::filesystem::remove_all(directoryPath, removeErrorCode);
        eErrorCode = SDirectory::_ConvertErrorCodeToFileSystemError(removeErrorCode);
    }
    else
    {
        eErrorCode = EFileSystemError::E_DoesNotExist;
    }

    return eErrorCode;
}

EFileSystemError SDirectory::Move(const Path &directory, const Path &newLocation, const bool bReplaceContent)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The source path (\"") + directory.ToString() + "\") must refer to a directory.");
    Z_ASSERT_ERROR(newLocation.IsDirectory(), string_z("The destination path (\"") + newLocation.ToString() + "\") must refer to a directory.");

    // Note: It would be faster to call rename() when the destination path does not exist but it fails when using different drive letters in source and destination paths

    Path destination = newLocation;
    destination.AppendDirectory(directory.GetLastDirectory());

    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    if(!SDirectory::Exists(destination, eErrorCode) || bReplaceContent)
    {
        // Moves and replaces the directory
        if(eErrorCode == EFileSystemError::E_Success)
        {
            // The copy first
            eErrorCode = SDirectory::Copy(directory, newLocation, bReplaceContent);

            // Then the deletion of the original directory
            if(eErrorCode == EFileSystemError::E_Success)
            {
                static const bool WAIT_FOR_DIRECTORY_CREATION = false;
                SDirectory::_WaitForCreationOrDeletion(SDirectory::_ConvertToBoostPath(destination), WAIT_FOR_DIRECTORY_CREATION);

                eErrorCode = SDirectory::Delete(directory);
            }
        }
    }
    else
    {
        eErrorCode = EFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EFileSystemError SDirectory::Rename(Path &directory, const string_z &strNewDirectoryName)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    Path renamedPath = directory;
    renamedPath.RemoveLastDirectory();
    renamedPath.AppendDirectory(strNewDirectoryName);

    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    if(!SDirectory::Exists(renamedPath, eErrorCode)) // This check is necessary because rename returns "no permissions" instead of "already exists" when there is already a directory with the target name
    {
        boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);
        boost::filesystem::path newDirectoryPath = SDirectory::_ConvertToBoostPath(renamedPath);

        boost::system::error_code renameErrorCode;
        boost::filesystem::rename(directoryPath, newDirectoryPath, renameErrorCode);

        if(renameErrorCode == boost::system::errc::success)
        {
            directory = renamedPath;
        }

        eErrorCode = SDirectory::_ConvertErrorCodeToFileSystemError(renameErrorCode);
    }
    else
    {
        eErrorCode = EFileSystemError::E_AlreadyExists;
    }

    return eErrorCode;
}

EFileSystemError SDirectory::Copy(const Path &directory, const Path& locationToCopyTo, const bool bReplaceContent)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The source path (\"") + directory.ToString() + "\") must refer to a directory.");
    Z_ASSERT_ERROR(locationToCopyTo.IsDirectory(), string_z("The destination path (\"") + locationToCopyTo.ToString() + "\") must refer to a directory.");

    // Paths transformations
    Path absoluteDirectory = directory.GetAbsolutePath();
    Path absoluteLocationToCopyTo = locationToCopyTo.GetAbsolutePath();
    absoluteLocationToCopyTo.AppendDirectory(absoluteDirectory.GetLastDirectory());

    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(absoluteDirectory);
    boost::filesystem::path newLocationPath = SDirectory::_ConvertToBoostPath(absoluteLocationToCopyTo);

    EFileSystemError eErrorCode = EFileSystemError::E_Success;

    // Copies the directory
    boost::system::error_code copyErrorCode;
    boost::filesystem::copy_directory(directoryPath, newLocationPath, copyErrorCode);

    // If the destination folder already exists, it is not cosidered an error
    eErrorCode = copyErrorCode.default_error_condition() == boost::system::errc::file_exists ? 
                                                                        EFileSystemError(EFileSystemError::E_Success) : 
                                                                        SDirectory::_ConvertErrorCodeToFileSystemError(copyErrorCode);
    
    if(eErrorCode == EFileSystemError::E_Success)
    {
        // Copies the content of the directory
        boost::filesystem::recursive_directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::recursive_directory_iterator endOfContent;
        const boost::filesystem::copy_option COPY_OPTION(bReplaceContent ? boost::filesystem::copy_option::overwrite_if_exists : 
                                                                           boost::filesystem::copy_option::fail_if_exists
                                                        );

        while((eErrorCode == EFileSystemError::E_Success || eErrorCode == EFileSystemError::E_AlreadyExists) && currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            string_z strCurrentDirOrFilePath = SDirectory::_ConvertPathToString(currentDirOrFilePath);

            // If the current element is a directory, it adds a trailing separator (this is necessary to adapt Boost's paths)
            bool bIsDirectory = boost::filesystem::is_directory(currentDirOrFilePath);
        
            if(bIsDirectory)
                strCurrentDirOrFilePath.Append(Path::GetPathSeparator());

            // Compounds a path as if the file or directory was already copied to the destination
            Path destinationFileOrDir(absoluteLocationToCopyTo.ToString() + Path(absoluteDirectory).GetRelativePathTo(strCurrentDirOrFilePath) + Path(strCurrentDirOrFilePath).GetFilename());

            // Copies the current file or directory
            boost::filesystem::path destinationPath = SDirectory::_ConvertToBoostPath(destinationFileOrDir);
            copyErrorCode.clear();

            if(bIsDirectory && !SDirectory::Exists(destinationFileOrDir, eErrorCode) && eErrorCode == EFileSystemError::E_Success)
                // Copies the directory if it does not exist
                boost::filesystem::copy_directory(currentDirOrFilePath, destinationPath, copyErrorCode);
            else if(!bIsDirectory)
                // Copies the file and overwrites if it has to
                boost::filesystem::copy_file(currentDirOrFilePath, destinationPath, COPY_OPTION, copyErrorCode);

            static const bool WAIT_FOR_DIRECTORY_CREATION = false;

            if(copyErrorCode != boost::system::errc::success)
                // An error occurred
                eErrorCode = SDirectory::_ConvertErrorCodeToFileSystemError(copyErrorCode);
            else if(bIsDirectory)
                // Waits until the directory has been created
                SDirectory::_WaitForCreationOrDeletion(destinationPath, WAIT_FOR_DIRECTORY_CREATION);

            ++currentDirOrFile;
        }
    }

    return eErrorCode;
}

Path SDirectory::GetCurrentWorkingDirectory()
{
    // Note: Interesting article about the variable PATH_MAX http://insanecoding.blogspot.com.es/2007/11/pathmax-simply-isnt.html
    // Note: Interesting article about working directories on Windows http://blogs.msdn.com/b/oldnewthing/archive/2010/10/11/10073890.aspx

    //  This is an alternative to Boost
    //
    //#if defined(Z_OS_WINDOWS)
    //    #include <Windows.h>
    //#else
    //    #include <unistd.h>
    //#endif
    //
    //    using ETextEncoding;
    //
    //    string_z strPath;
    //
    //#if defined(Z_OS_WINDOWS)
    //    DWORD uPathLength = ::GetCurrentDirectoryW(0, null_z);
    //    wchar_t* arCharacters = new wchar_t[uPathLength + 1U];
    //    ::GetCurrentDirectoryW(uPathLength, arCharacters);
    //
    //    strPath = string_z(rcast_z(arCharacters, char*), uPathLength * sizeof(wchar_t), ETextEncoding::E_UTF16LE);
    //    delete[] arCharacters;
    //#elif defined(_GNU_SOURCE)
    //    char* arCharacters = ::get_current_dir_name();
    //    puint_z uPathLength = strlen(arCharacters);
    //    strPath = string_z(arCharacters, uPathLength, ETextEncoding::E_UTF8);
    //    free(arCharacters);
    //#else
    //    char* arCharacters = ::getcwd(null_z, 0);
    //    puint_z uPathLength = strlen(arCharacters);
    //    strPath = string_z(arCharacters, uPathLength, ETextEncoding::E_UTF8);
    //    free(arCharacters);
    //#endif
    //
    //    // Adds a trailing slash if it does not end with one
    //    if(!strPath.IsEmpty() && strPath.Substring(strPath.GetLength() - Path::GetPathSeparator().GetLength()) != Path::GetPathSeparator())
    //        strPath.Append(Path::GetPathSeparator());
    //
    //    return Path(strPath);

    boost::system::error_code eErrorCode;
    boost::filesystem::path directoryPath = boost::filesystem::current_path(eErrorCode);

    Z_ASSERT_ERROR(eErrorCode == boost::system::errc::success, "An unexpected error occurred when retrieving the current working directory.");

    return Path(SDirectory::_ConvertPathToString(directoryPath) + Path::GetPathSeparator());
}

void SDirectory::SetCurrentWorkingDirectory(const Path& newDirectory, EFileSystemError& eErrorInfo)
{
    Z_ASSERT_ERROR(newDirectory.IsDirectory(), string_z("The input path (\"") + newDirectory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(newDirectory);

    boost::system::error_code errorCode;
    boost::filesystem::current_path(directoryPath, errorCode);

    eErrorInfo = SDirectory::_ConvertErrorCodeToFileSystemError(errorCode);
}

bool SDirectory::Exists(const Path &directory, EFileSystemError& eErrorInfo)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

    boost::system::error_code eErrorCode;
    bool bExists = boost::filesystem::exists(directoryPath, eErrorCode);

    eErrorInfo = SDirectory::_ConvertErrorCodeToFileSystemError(eErrorCode);

    if(eErrorInfo == EFileSystemError::E_DoesNotExist)
        eErrorInfo = EFileSystemError::E_Success;

    return bExists;
}

DirectoryInfo SDirectory::GetDirectoryInfo(const Path& directory, EFileSystemError& eErrorInfo)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    DateTime creationDateTime;

    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

    // Number of seconds passed since 01/01/1970
    boost::system::error_code eErrorCode;
    time_t creationTime = boost::filesystem::last_write_time(directoryPath, eErrorCode);

    if(eErrorCode == boost::system::errc::success)
    {
        TimeSpan seconds(0, 0, 0, creationTime, 0, 0, 0);
        static const DateTime EPOCH(1970, 1, 1, TimeZone::UTC);
        creationDateTime = DateTime(EPOCH + seconds, LocalTimeZone().Get());
    }

    eErrorInfo = SDirectory::_ConvertErrorCodeToFileSystemError(eErrorCode);

    return DirectoryInfo(directory, creationDateTime);
}

EFileSystemError SDirectory::Create(const Path &directory, const string_z &strDirectoryName)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    boost::system::error_code errorCode;
    Path newDirectory = directory;
    newDirectory.AppendDirectory(strDirectoryName);
    boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(newDirectory);
    boost::filesystem::create_directory(directoryPath, errorCode);

    return SDirectory::_ConvertErrorCodeToFileSystemError(errorCode);
}

EFileSystemError SDirectory::GetFiles(const Path &directory, ArrayDynamic<Path> &arFiles)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EFileSystemError eErrorInfo = EFileSystemError::E_Success;

    if(SDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            if(!boost::filesystem::is_directory(currentDirOrFilePath))
            {
                string_z strCurrentDirOrFilePath = SDirectory::_ConvertPathToString(currentDirOrFilePath);
                arFiles.Add(strCurrentDirOrFilePath);
            }

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EFileSystemError::E_Success)
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

EFileSystemError SDirectory::GetFiles(const Path &directory, ArrayDynamic<Path> &arFiles, const string_z &strExtensionFilter)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EFileSystemError eErrorInfo = EFileSystemError::E_Success;

    if(SDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            Path fileOrDirectory(SDirectory::_ConvertPathToString(currentDirOrFilePath));

#if defined(Z_OS_WINDOWS)
            static const EComparisonType STRING_COMPARISON = EComparisonType::E_CanonicalCaseInsensitive;
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
            static const EComparisonType STRING_COMPARISON = EComparisonType::E_CanonicalCaseSensitive;
#endif

            if(!boost::filesystem::is_directory(currentDirOrFilePath) && 
               fileOrDirectory.GetFileExtension().CompareTo(strExtensionFilter, STRING_COMPARISON) == 0)
                arFiles.Add(fileOrDirectory);

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EFileSystemError::E_Success)
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

EFileSystemError SDirectory::GetSubdirectories(const Path &directory, ArrayDynamic<Path> &arDirectories)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    EFileSystemError eErrorInfo = EFileSystemError::E_Success;

    if(SDirectory::Exists(directory, eErrorInfo))
    {
        boost::filesystem::path directoryPath = SDirectory::_ConvertToBoostPath(directory);

        boost::filesystem::directory_iterator currentDirOrFile(directoryPath);
        boost::filesystem::directory_iterator endOfContent;

        while(currentDirOrFile != endOfContent) 
        {
            boost::filesystem::path currentDirOrFilePath = currentDirOrFile->path();

            if(boost::filesystem::is_directory(currentDirOrFilePath))
            {
                string_z strCurrentDirOrFilePath = SDirectory::_ConvertPathToString(currentDirOrFilePath);
                strCurrentDirOrFilePath.Append(Path::GetPathSeparator());
                arDirectories.Add(strCurrentDirOrFilePath);
            }

            ++currentDirOrFile;
        }
    }
    else if(eErrorInfo == EFileSystemError::E_Success)
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }

    return eErrorInfo;
}

Path SDirectory::GetParentDirectory(const Path &directory, EFileSystemError &eErrorInfo)
{
    Z_ASSERT_ERROR(directory.IsDirectory(), string_z("The input path (\"") + directory.ToString() + "\") must refer to a directory.");

    eErrorInfo = EFileSystemError::E_Success;
    Path parentPath("./");

    if(SDirectory::Exists(directory, eErrorInfo))
    {
        parentPath = Path(directory.GetAbsolutePath());
        parentPath.RemoveLastDirectory();
    }
    else if(eErrorInfo == EFileSystemError::E_Success)
    {
        eErrorInfo = EFileSystemError::E_DoesNotExist;
    }

    return parentPath;
}

boost::filesystem::path SDirectory::_ConvertToBoostPath(const Path &pathToConvert)
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

string_z SDirectory::_ConvertPathToString(const boost::filesystem::path &pathToConvert)
{
#if defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    return string_z(pathToConvert.c_str(), scast_z(strlen(pathToConvert.c_str()), int), ETextEncoding::E_UTF8);
#elif defined(Z_OS_WINDOWS)
    return string_z((i8_z*)pathToConvert.c_str(), scast_z(wcslen(pathToConvert.c_str()) * sizeof(boost::filesystem::path::value_type), int), string_z::GetLocalEncodingUTF16());
#endif
}

EFileSystemError SDirectory::_ConvertErrorCodeToFileSystemError(const boost::system::error_code &eErrorCode)
{
    EFileSystemError eErrorInfo = EFileSystemError::E_Unknown;
    boost::system::error_condition posixError = eErrorCode.default_error_condition();

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

bool SDirectory::_WaitForCreationOrDeletion(const boost::filesystem::path &directoryOrFilePath, const bool bTDeletionFCreation)
{
    static const u64_z MAXIMUM_WAIT_TIME = 600ULL; // milliseconds

    Stopwatch elapsedTime;
    elapsedTime.Set();
    bool bTooMuchTime = false;

    while(boost::filesystem::exists(directoryOrFilePath) == bTDeletionFCreation && !bTooMuchTime)
    {
        SThisThread::Yield();
        bTooMuchTime = elapsedTime.GetElapsedTimeAsTimeSpan().GetMilliseconds() < MAXIMUM_WAIT_TIME;
    }

    Z_ASSERT_ERROR(!bTooMuchTime, "The timeout expired, the file or directory could not be created or deleted fast enough.");

    return !bTooMuchTime;
}


} // namespace z