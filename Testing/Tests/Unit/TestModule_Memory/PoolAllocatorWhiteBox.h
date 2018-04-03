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

#ifndef __POOLALLOCATORWHITEBOX__
#define __POOLALLOCATORWHITEBOX__

#include "ZMemory/PoolAllocator.h"


namespace z    
{
namespace Test
{

/// <summary>
/// Class to be used to expose protected methods of PoolAllocator for testing purposes.
/// </summary>

class PoolAllocatorWhiteBox : public PoolAllocator
{
	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	PoolAllocatorWhiteBox(puint_z uSize, puint_z uBlockSize, Alignment alignment) :
        PoolAllocator(uSize, uBlockSize, alignment)
    {
    }

    // Necessary for testing
    PoolAllocatorWhiteBox(puint_z uSize, puint_z uBlockSize, void *pBuffer) :
        PoolAllocator(uSize, uBlockSize, pBuffer)
    {
    }

    // Necessary for testing
    PoolAllocatorWhiteBox(puint_z uSize, puint_z uBlockSize, void *pBuffer, Alignment alignment) :
        PoolAllocator(uSize, uBlockSize, pBuffer, alignment )
    {
    }
	// METHODS
	// ---------------
public:

    // Exposed member.
    void* GetpAllocatedMemory()
    {
        return m_pAllocatedMemory;
    }

    // Exposed member.
    void* GetpFirst() 
    {
        return m_pFirst;
    }

    // Exposed member.
    puint_z GetSize() 
    {
        return m_uSize;
    }

    // Returns address of the block in the passed position.
    void* GetpBlock(puint_z uBlockIndex)
    {
        return (void*)((puint_z)m_pFirst + uBlockIndex*m_uBlockSize);
    }
};

} // namespace Test
} // namespace z

#endif // __POOLALLOCATORWHITEBOX__
