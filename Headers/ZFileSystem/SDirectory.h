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

#ifndef __DIRECTORY__
#define __DIRECTORY__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include <boost/filesystem.hpp>

#include "ZFileSystem/DirectoryInfo.h"
#include "ZFileSystem/EFileSystemError.h"
#include "ZContainers/ArrayDynamic.h"


namespace z
{

/// <summary>
/// Provides functionalities to manage directories in the file system.
/// </summary>
class Z_FILESYSTEM_MODULE_SYMBOLS SDirectory
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SDirectory();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Removes a directory and its content.
    /// </summary>
    /// <param name="directory">[IN] The path to a directory to be removed.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Delete(const Path &directory);
    
    /// <summary>
    /// Moves a directory and its content to inside another directory ("/p1/" to "/p2/" results in "/p2/p1/").
    /// </summary>
    /// <remarks>
    /// If an error occurs during the process, it will stop immediately leaving the files or directories that have not been moved yet
    /// at their original place.<br/>
    /// Since read/write operations in secondary memory are considerably slower than the submision of file system commands from the application, it is
    /// necessary to apply some delay between each directory or file copy or deletion. The calling thread will yield the execution to other threads until every 
    /// "atomic" operation is completed.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory to be moved.</param>
    /// <param name="newLocation">[IN] The path to a directory inside which the source directory is to be moved to.</param>
    /// <param name="bReplaceContent">[IN] Indicates the behavior of the operation when the new location already contains a directory 
    /// with the same name as source directory's. If it is True, source directories will be merged into existing ones recursively and, if both directories contain files 
    /// with the same name and extension, source directory's files will replace existing ones. If it is False, the operation will take place only if there is no other
    /// directory with the same name at the new location; otherwise an error will occur.
    /// </param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Move(const Path &directory, const Path &newLocation, const bool bReplaceContent);
    
    /// <summary>
    /// Renames a directory and obtains the renamed path.
    /// </summary>
    /// <param name="directory">[IN/OUT] The path to a directory to be renamed. If the operation takes place successfully, it will contain the resultant path.</param>
    /// <param name="strNewDirectoryName">[IN] The new name for the directory. It must neither be empty nor contain invalid characters. The resultant path must not exist 
    /// already or an error will occur.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Rename(Path &directory, const string_z &strNewDirectoryName);
    
    /// <summary>
    /// Copies a directory and its content to inside another directory ("/p1/" to "/p2/" results in "/p2/p1/").
    /// </summary>
    /// <remarks>
    /// If an error occurs during the process, it will stop immediately not copying the peding files or directories.<br/>
    /// Since read/write operations in secondary memory are considerably slower than the submision of file system commands from the application, it is
    /// necessary to apply some delay between each directory copy or deletion. The calling thread will yield the execution to other threads until every 
    /// "atomic" operation is completed.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory to be copied.</param>
    /// <param name="locationToCopyTo">[IN] The path to a directory inside which the source directory is to be copied to.</param>
    /// <param name="bReplaceContent">[IN] Indicates the behavior of the operation when the new location already contains a directory 
    /// with the same name as source directory's. If it is True, copied directories will be merged into existing ones recursively and, if both directories contain files 
    /// with the same name and extension, source directory's files will replace existing ones. If it is False, the same operation will be performed but skipping any existing files.
    /// </param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success. If it returns the AlreadyExists code, it means that
    /// all directories and files were copied but those already existing in the destination path.
    /// </returns>
    static EFileSystemError Copy(const Path &directory, const Path& locationToCopyTo, const bool bReplaceContent);
    
    /// <summary>
    /// Gets the current working directory of the calling process.
    /// </summary>
    /// <returns>
    /// An absolute path that refers to the current working directory of the process.
    /// </returns>
    static Path GetCurrentWorkingDirectory();

    /// <summary>
    /// Sets the current working directory of the calling process.
    /// </summary>
    /// <param name="newDirectory">[IN] The path to a directory to be set as current working directory.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    static void SetCurrentWorkingDirectory(const Path& newDirectory, EFileSystemError& eErrorInfo);
    
    /// <summary>
    /// Checks whether a directory exists or not.
    /// </summary>
    /// <param name="directory">[IN] The path to a directory that may or may not exist.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    /// <returns>
    /// True if the directory exists; False otherwise.
    /// </returns>
    static bool Exists(const Path &directory, EFileSystemError& eErrorInfo);
    
    /// <summary>
    /// Gets information about a directory.
    /// </summary>
    /// <remarks>
    /// All the retrieved dates and times are local.<br/>
    /// The "creation date" concept did not exist on Linux until the ext4 file system was introduced. Therefore, the last modification date will be returned instead on that platform.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory whose properties are to be retrieved.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    /// <returns>
    /// Information about the directory, like its creation date.
    /// </returns>
    static DirectoryInfo GetDirectoryInfo(const Path& directory, EFileSystemError& eErrorInfo);
    
    /// <summary>
    /// Creates a directory.
    /// </summary>
    /// <param name="directory">[IN] The path to a directory inside which the new directory is to be created.</param>
    /// <param name="strDirectoryName">[IN] The name of the new directory. It must neither be empty nor contain invalid characters. If it already exists, 
    /// the operation is considered a success.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Create(const Path &directory, const string_z &strDirectoryName);
    
    /// <summary>
    /// Gets the path to all the files inside a directory.
    /// </summary>
    /// <remarks>
    /// It is not recursive. The order of appearance of the file paths in the output container is undefined.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory whose files are to be retrieved. If it does not contain files, nothing will be done.</param>
    /// <param name="arFiles">[OUT] The container that will store the paths to every file in the directory. Elements are appended.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError GetFiles(const Path &directory, ArrayDynamic<Path> &arFiles);
    
    /// <summary>
    /// Gets the path to all the files inside a directory, filtered by extension.
    /// </summary>
    /// <remarks>
    /// It is not recursive. The order of appearance of the file paths in the output container is undefined.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory whose files are to be retrieved. If it does not contain files, nothing will be done.</param>
    /// <param name="arFiles">[OUT] The container that will store the paths to every file in the directory. Elements are appended.</param>
    /// <param name="strExtensionFilter">[IN] The extension that files must have in order to be included in the container. It must neither contain the separation dot nor any 
    /// invalid character. Depending on the operating system, the string comparison will be case-sensitive (Unix-based systems) or case-insensitive (Windows); in any case, 
    /// it will be performed in the canonical form.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError GetFiles(const Path &directory, ArrayDynamic<Path> &arFiles, const string_z &strExtensionFilter);
    
    /// <summary>
    /// Gets the path to all the subdirectories of a directory.
    /// </summary>
    /// <remarks>
    /// It is not recursive. The order of appearance of the directory paths in the output container is undefined.
    /// </remarks>
    /// <param name="directory">[IN] The path to a directory whose subdirectories are to be retrieved. If it does not contain files, nothing will be done.</param>
    /// <param name="arDirectories">[OUT] The container that will store the paths to every subdirectory in the directory. Elements are appended.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError GetSubdirectories(const Path &directory, ArrayDynamic<Path> &arDirectories);
    
    /// <summary>
    /// Gets the parent of a directory.
    /// </summary>
    /// <param name="directory">[IN] The path to a directory whose parent is to be obtained.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    /// <returns>
    /// An absolute path to the parent directory. If the directory has no parent (it is a drive letter "x:/" on Windows, for example), the returned parent will be itself.
    /// </returns>
    static Path GetParentDirectory(const Path &directory, EFileSystemError &eErrorInfo);

protected:
    
    /// <summary>
    /// Converts a path from Zunderbolt to a path from Boost.
    /// </summary>
    /// <param name="pathToConvert">[IN] The path to be converted.</param>
    /// <returns>
    /// The equivalent resultant path.
    /// </returns>
    static boost::filesystem::path _ConvertToBoostPath(const Path &pathToConvert);
    
    /// <summary>
    /// Converts a path from Boost to a string.
    /// </summary>
    /// <param name="pathToConvert">[IN] The path to be converted.</param>
    /// <returns>
    /// The string that contains the path.
    /// </returns>
    static string_z _ConvertPathToString(const boost::filesystem::path &pathToConvert);
    
    /// <summary>
    /// Gets the equivalent enumeration value for a given POSIX error coming from Boost's functions.
    /// </summary>
    /// <param name="errorCode">[IN] The POSIX error code.</param>
    /// <returns>
    /// The equivalent enumeration value.
    /// </returns>
    static EFileSystemError _ConvertErrorCodeToFileSystemError(const boost::system::error_code &errorCode);
    
    /// <summary>
    /// Waits for either the creation or deletion of a directory or file.
    /// </summary>
    /// <remarks>
    /// It uses a timeout so it is not waiting forever.
    /// </remarks>
    /// <param name="directoryOrFilePath">[IN] The path to the directory or file.</param>
    /// <param name="bTDeletionFCreation">[IN] Switches between waiting for either the creation (False) or the deletion (True).</param>
    /// <returns>
    /// True if the creation or deletion was performed before the timeout expires; False otherwise.
    /// </returns>
    static bool _WaitForCreationOrDeletion(const boost::filesystem::path &directoryOrFilePath, const bool bTDeletionFCreation);

};

} // namespace z

#endif // __DIRECTORY__
