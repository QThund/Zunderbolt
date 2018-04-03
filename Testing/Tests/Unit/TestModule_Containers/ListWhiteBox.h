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

#ifndef __LISTWHITEBOX__
#define __LISTWHITEBOX__

#include "ZContainers/List.h"
#include "ZMemory/PoolAllocator.h"


namespace z
{
namespace Test
{

/// <summary>
/// Class intended to be used to expose protected methods of List for testing purposes.
/// </summary>
template <class T, class AllocatorT = PoolAllocator>
class ListWhiteBox : public List<T, AllocatorT>
{
    using List<T>::m_linkAllocator;
    using List<T>::m_uFirst;
    using List<T>::m_uLast;
    using List<T>::DEFAULT_NUMBER_OF_ELEMENTS;

	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
    ListWhiteBox() : List<T>()
    {
    }

    // Necessary for testing
    ListWhiteBox(puint_z uReserve) : List<T>(uReserve)
    {
    }

	// PROPERTIES
	// ---------------
public:

    // Necessary for testing
    puint_z GetFirstPosition() const
    {
        return m_uFirst;
    }

    // Necessary for testing
    puint_z GetLastPosition() const
    {
        return m_uLast;
    }

    // Necessary for testing
    const AllocatorT* GetLinkAllocator() const
    {
        return &m_linkAllocator;
    }

    // Necessary for testing
    static puint_z GetDefaultInitialCapacity()
    {
        return DEFAULT_NUMBER_OF_ELEMENTS;
    }
};

} // namespace Test
} // namespace z

#endif // __LISTWHITEBOX__
