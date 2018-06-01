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

#ifndef __FILEINFO__
#define __FILEINFO__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZTime/DateTime.h"
#include "ZFileSystem/Path.h"


namespace z
{

/// <summary>
/// Stores information about a file in the file system.
/// </summary>
class Z_FILESYSTEM_MODULE_SYMBOLS FileInfo
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about a file.
    /// </summary>
    /// <param name="path">[IN] The absolute path to the file.</param>
    /// <param name="uSize">[IN] The size of the file, in bytes.</param>
    /// <param name="creationDate">[IN] The date and time of the file's creation.</param>
    /// <param name="lastModificationDate">[IN] The date and time of the file's last modification.</param>
    /// <param name="bIsReadOnly">[IN] The ability of the file to be modified. True if it is read-only, False otherwise.</param>
    FileInfo(const Path &path, 
              const u64_z uSize,
              const DateTime &creationDate,
              const DateTime &lastModificationDate,
              const bool bIsReadOnly);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Indicates whether the file can be modified or not.
    /// </summary>
    /// <returns>
    /// True if it is read-only, False otherwise.
    /// </returns>
    const bool IsReadOnly() const;
    
    /// <summary>
    /// Gets the date and time of the file's last modification.
    /// </summary>
    /// <returns>
    /// The date and time of the file's last modification.
    /// </returns>
    const DateTime& GetLastModificationDate() const;
    
    /// <summary>
    /// Gets the date and time of the file's creation.
    /// </summary>
    /// <returns>
    /// The date and time of the file's creation.
    /// </returns>
    const DateTime& GetCreationDate() const;
    
    /// <summary>
    /// Gets the size of the file, in bytes.
    /// </summary>
    /// <returns>
    /// The size of the file, in bytes.
    /// </returns>
    const u64_z GetSize() const;
    
    /// <summary>
    /// Gets the absolute path to the file.
    /// </summary>
    /// <returns>
    /// The absolute path to the file.
    /// </returns>
    const Path& GetPath() const;


    // ATTRIBUTES
    // ---------------
private:
    
    /// <summary>
    /// The absolute path to the file.
    /// </summary>
    Path m_path;
    
    /// <summary>
    /// The size of the file, in bytes.
    /// </summary>
    u64_z m_uSize;

    /// <summary>
    /// The date and time of the file's creation.
    /// </summary>
    DateTime m_creationDate;
    
    /// <summary>
    /// The date and time of the file's last modification.
    /// </summary>
    DateTime m_lastModificationDate;
        
    /// <summary>
    /// Indicates whether the file can be modified or not.
    /// </summary>
    bool m_bIsReadOnly;
};

} // namespace z

#endif // __FILEINFO__
