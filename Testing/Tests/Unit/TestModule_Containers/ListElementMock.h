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

#ifndef __LISTELEMENTMOCK__
#define __LISTELEMENTMOCK__

namespace z
{
namespace Test
{

/// <summary>
/// Class to be used to ensure that the copy constructor, assignment operator and destructor are called
/// properly from List.
/// </summary>
class ListElementMock
{
	// CONSTRUCTORS
	// ---------------
public:
	// Necessary for testing
    ListElementMock(u64_z uValue) : 
            m_uValue(uValue),
            m_bCallToCopyConstructor(false),
            m_bCallToOperatorAssignment(false)

    {
        ListElementMock::m_nNumberOfAllocatedObjects++;
    }
    
    // Copy constructor necessary for testing
    ListElementMock(const ListElementMock& listElementMock)
    {
        this->m_uValue = listElementMock.m_uValue;
        this->m_bCallToCopyConstructor = true;
        this->m_bCallToOperatorAssignment = false;
        ListElementMock::m_nNumberOfAllocatedObjects++;
    }
    
    // Destructor necessary for testing
    ~ListElementMock()
    {
        ListElementMock::m_nNumberOfAllocatedObjects--;
    }

	// METHODS
	// ---------------
public:

    // Assignment operator necessary for testing
    ListElementMock& operator= (const ListElementMock& listElementMock)
    {
        this->m_uValue = listElementMock.m_uValue;
        this->m_bCallToOperatorAssignment = true;
        return *this;
    }

    // Exposed member.
    bool GetCallToCopyConstructor() const
    {
        return m_bCallToCopyConstructor;
    }

    // Exposed member.
    bool GetCallToOperatorAssignment() const
    {
        return m_bCallToOperatorAssignment;
    }

    // Exposed member.
    static puint_z GetNumberOfAllocatedObjects() 
    {
        return m_nNumberOfAllocatedObjects;
    }
    
    // ATTRIBUTES
	// ---------------

private:

    // Number of allocated objects
    static puint_z m_nNumberOfAllocatedObjects;

    // Stored value.
    u64_z m_uValue;

    // True if a call to the copy constructor has been done.
    bool m_bCallToCopyConstructor;

    // True if a call to the assignment operator has been done.
    bool m_bCallToOperatorAssignment; 

};

} // namespace Test
} // namespace z

#endif // __LISTELEMENTMOCK__
