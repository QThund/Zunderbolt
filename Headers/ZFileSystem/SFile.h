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

#ifndef __SFILE__
#define __SFILE__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include <boost/filesystem.hpp>
#include "ZFileSystem/EFileSystemError.h"
#include "ZFileSystem/FileInfo.h"
#include "ZTime/DateTime.h"


namespace z
{

/// <summary>
/// Provides functionalities to manage files in the file system.
/// </summary>
class Z_LAYER_FILESYSTEM_SYMBOLS SFile
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SFile();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Removes a file.
    /// </summary>
    /// <param name="file">[IN] The path to a file to be removed.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Delete(const Path &file);
    
    /// <summary>
    /// Moves a file to inside another directory ("/p1.ext" to "/p2/" results in "/p2/p1.ext").
    /// </summary>
    /// <param name="file">[IN] The path to a file to be moved.</param>
    /// <param name="newLocation">[IN] The path to a directory inside which the file is to be moved to.</param>
    /// <param name="bReplace">[IN] Indicates the behavior of the operation when the new location already contains a file
    /// with the same name as source file's. If it is True, source file will replace the existing file; if it is False, nothing will be done
    /// and an error will occur.
    /// </param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Move(const Path &file, const Path& newLocation, const bool bReplace);
    
    /// <summary>
    /// Renames a file and obtains the renamed path.
    /// </summary>
    /// <param name="file">[IN/OUT] The path to a file to be renamed. If the operation takes place successfully, it will contain the resultant path.</param>
    /// <param name="strNewFileName">[IN] The new name for the file. It must neither be empty nor contain invalid characters. The resultant path must not exist 
    /// already or an error will occur.</param>
    /// <param name="bRenameExtension">[IN] Indicates whether the new name affets also the file extension or not. If it is True, both the name and the extension of
    /// the file will be replaced with the new name; otherwise only the name before the last dot will be replaced, keeping the same extension.</param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Rename(Path &file, const string_z &strNewFileName, const bool bRenameExtension);
    
    /// <summary>
    /// Copies a file to inside another directory ("/p1.ext" to "/p2/" results in "/p2/p1.ext").
    /// </summary>
    /// <param name="file">[IN] The path to a file to be moved.</param>
    /// <param name="locationToCopyTo">[IN] The path to a directory inside which the file is to be copied to.</param>
    /// <param name="bReplace">[IN] Indicates the behavior of the operation when the new location already contains a file
    /// with the same name as source file's. If it is True, source file will replace the existing file; if it is False, nothing will be done
    /// and an error will occur.
    /// </param>
    /// <returns>
    /// An error code depending on the result of the operation. If nothing unexpected ocurred, it returns Success.
    /// </returns>
    static EFileSystemError Copy(const Path &file, const Path& locationToCopyTo, const bool bReplace);
    
    /// <summary>
    /// Checks whether a file exists or not.
    /// </summary>
    /// <param name="file">[IN] The path to a file that may or may not exist.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    /// <returns>
    /// True if the file exists; False otherwise.
    /// </returns>
    static bool Exists(const Path &file, EFileSystemError& eErrorInfo);
    
    /// <summary>
    /// Gets information about a file.
    /// </summary>
    /// <remarks>
    /// All the retrieved dates and times are local.<br/>
    /// The "creation date" concept did not exist on Linux until the ext4 file system was introduced. Therefore, the last modification date will be returned instead on that platform.<br/>
    /// The "read-only" flag will be True if the owner of the file does not have write permissions.
    /// </remarks>
    /// <param name="file">[IN] The path to a file whose properties are to be retrieved.</param>
    /// <param name="eErrorInfo">[OUT] An error code depending on the result of the operation. If nothing unexpected ocurred, its value will be Success.</param>
    /// <returns>
    /// Information about the file, like its creation date or its size.
    /// </returns>
    static FileInfo GetFileInfo(const Path &file, EFileSystemError &eErrorInfo);
    
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
    /// Waits for the creation of a file.
    /// </summary>
    /// <remarks>
    /// It uses a timeout so it is not waiting forever.
    /// </remarks>
    /// <param name="filePath">[IN] The path to the file.</param>
    /// <returns>
    /// True if the creation was performed before the timeout expires; False otherwise.
    /// </returns>
    static bool _WaitForCreation(const boost::filesystem::path &filePath);

    /// <summary>
    /// Obtains the creation date and time of a file using the API provided by the operating system.
    /// </summary>
    /// <remarks>
    /// Its implementation varies depending on the operating system. There is no version of this function on Linux.
    /// </remarks>
    /// <param name="file">[IN] The path to the file.</param>
    /// <returns>
    /// The date and time (UTC) when the file was created.
    /// </returns>
    static DateTime _GetFileCreationDateTime(const Path &file);
};

} // namespace z

#endif // __SFILE__
