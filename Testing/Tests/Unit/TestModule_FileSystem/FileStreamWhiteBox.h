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

#ifndef __FILESTREAMWHITEBOX__
#define __FILESTREAMWHITEBOX__

#include "ZFileSystem/FileStream.h"


namespace z
{
namespace Test
{

/// <summary>
/// Class to be used in FileStream tests to manipulate internal members.
/// </summary>
class FileStreamWhiteBox : public FileStream
{
	// CONSTRUCTORS
	// ---------------
public:
	// Necessary for testing
    FileStreamWhiteBox(const string_z &strFilePath, const EFileOpenMode &eOpenMode, const puint_z uInitialCapacity, EFileSystemError &errorInfo) : 
                                                                                                FileStream(strFilePath, eOpenMode, uInitialCapacity, errorInfo),
                                                                                                m_bPendingBytesFlagWhenDestroyed(true)

    {
    }

	// DESTRUCTOR
	// ---------------
public:

    ~FileStreamWhiteBox()
    {
        if(!m_bPendingBytesFlagWhenDestroyed)
        {
            m_bIsWritePending = false;
        }
    }


	// METHODS
	// ---------------
public:

    // Sets the behavior of the destructor, True means that the destructor will flush the content if there are pending bytes
    void SetPendingBytesFlagWhenDestroyed(const bool bValue)
    {
        m_bPendingBytesFlagWhenDestroyed = bValue;
    }

	// ATTRIBUTES
	// ---------------
private:

    bool m_bPendingBytesFlagWhenDestroyed;
};

} // namespace Test
} // namespace z

#endif // __FILESTREAMWHITEBOX__
