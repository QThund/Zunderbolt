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

#ifndef __FIXEDARRAYWHITEBOX__
#define __FIXEDARRAYWHITEBOX__

#include "ZContainers/ArrayFixed.h"
#include "ZMemory/PoolAllocator.h"

namespace z
{
namespace Test
{

/// <summary>
/// Class intended to be used to expose protected methods of ArrayFixed for testing purposes.
/// </summary>
template <class T, class Allocator = PoolAllocator>
class ArrayFixedWhiteBox : public ArrayFixed<T>
{
    using ArrayFixed<T>::m_allocator;


	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
    ArrayFixedWhiteBox() : ArrayFixed<T>()
    {
    }

	// PROPERTIES
	// ---------------
public:

    // Necessary for testing
    puint_z GetFirstPosition() const
    {
        return ArrayFixed<T, Allocator>::m_uFirst;
    }

    // Necessary for testing
    puint_z GetLastPosition() const
    {
        return ArrayFixed<T, Allocator>::m_uLast;
    }

    // Necessary for testing
    Allocator* GetpAllocator() const
    {
        return &ArrayFixed<T, Allocator>::m_allocator;
    }
};

} // namespace Test
} // namespace z

#endif // __FIXEDARRAYWHITEBOX__
