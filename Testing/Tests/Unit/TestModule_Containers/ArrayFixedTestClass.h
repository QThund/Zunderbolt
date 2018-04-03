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

#ifndef __FIXEDARRAYTESTCLASS__
#define __FIXEDARRAYTESTCLASS__

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
class ArrayFixedTestClass : public ArrayFixed<T>
{
    using ArrayFixed<T>::m_allocator;
	static const puint_z DEFAULT_NUMBER_OF_ELEMENTS = 1;

    // CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
    ArrayFixedTestClass() : ArrayFixed<T>()
    {
    }

};

} // namespace Test
} // namespace z

#endif // __FIXEDARRAYTESTCLASS__
