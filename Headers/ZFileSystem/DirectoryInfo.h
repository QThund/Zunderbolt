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

#ifndef __DIRECTORYINFO__
#define __DIRECTORYINFO__

#include "ZFileSystem/FileSystemModuleDefinitions.h"

#include "ZFileSystem/Path.h"
#include "ZTime/DateTime.h"


namespace z
{

/// <summary>
/// Stores information about a directory in the file system.
/// </summary>
class Z_FILESYSTEM_MODULE_SYMBOLS DirectoryInfo
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about the directory.
    /// </summary>
    /// <param name="path">[IN] The absolute path to the directory.</param>
    /// <param name="creationDate">[IN] The date and time of the directory's creation.</param>
    DirectoryInfo(const Path &path,
                  const DateTime &creationDate);


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the absolute path to the directory.
    /// </summary>
    /// <returns>
    /// The absolute path to the directory.
    /// </returns>
    const Path& GetPath() const;
    
    /// <summary>
    /// Gets the date and time of the directory's creation.
    /// </summary>
    /// <returns>
    /// The date and time of the directory's creation.
    /// </returns>
    const DateTime& GetCreationDate() const;


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The absolute path to the directory.
    /// </summary>
    Path m_path;

    /// <summary>
    /// The date and time of the directory's creation.
    /// </summary>
    DateTime m_creationDate;

};

} // namespace z

#endif // __DIRECTORYINFO__
