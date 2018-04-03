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

#include "ZFileSystem/FileInfo.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

FileInfo::FileInfo(const Path &path, 
                   const u64_z uSize,
                   const DateTime &creationDate,
                   const DateTime &lastModificationDate,
                   const bool bIsReadOnly) :
                                                m_path(path),
                                                m_uSize(uSize),
                                                m_creationDate(creationDate),
                                                m_lastModificationDate(lastModificationDate),
                                                m_bIsReadOnly(bIsReadOnly)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const bool FileInfo::IsReadOnly() const
{
    return m_bIsReadOnly;
}

const DateTime& FileInfo::GetLastModificationDate() const
{
    return m_lastModificationDate;
}

const DateTime& FileInfo::GetCreationDate() const
{
    return m_creationDate;
}

const u64_z FileInfo::GetSize() const
{
    return m_uSize;
}

const Path& FileInfo::GetPath() const
{
    return m_path;
}

} // namespace z