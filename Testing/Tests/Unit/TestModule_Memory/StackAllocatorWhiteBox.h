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

#ifndef __STACKALLOCATORWHITEBOX__
#define __STACKALLOCATORWHITEBOX__


#include "ZMemory/StackAllocator.h"
#include "ZMemory/AllocationOperators.h"
#include "AlignmentMocked.h"


namespace z
{
namespace Test
{

/// <summary>
/// This derived class from StackAllocator is used to expose protected methods of StackAllocator for testing purposes.
/// </summary>
class StackAllocatorWhiteBox : public StackAllocator
{
    // USINGS
	// -----------------
public:

    using StackAllocator::BlockHeader;
    
    
    // INTERNAL CLASSES
	// -----------------

public:

    /// <summary>
    /// Represents a fake mark that can autosabotage the address that holds for testing purposes of a stack allocator.
    /// </summary>
    class MarkMocked : public Mark
    {
    private:
        // The offset value for autosabotage the address that the mark holds to a greater or lesser value<br/>
        // than the current one.
        static const puint_z MARKMOCKED_OFFSET_VALUE;

        // CONSTRUCTORS
	    // ---------------
    public:

        explicit inline MarkMocked(void* pMemAddress) : Mark(pMemAddress)
        {
        }


        // METHODS
	    // ---------------
    public:

        // Set the address to null.
        void SabotageMarkToNull();

        // Sets the address to a lesser value than the current one.
        void SabotageMarkToLesserMemoryAddress();

         // Sets the address to a greater value than the current one.
        void SabotageMarkToGreaterMemoryAddress();

    }; // --- MarkMocked ---


	// CONSTRUCTORS
	// ---------------
public:

	// Necessary for testing
	explicit StackAllocatorWhiteBox(const puint_z uPreallocationSize) : StackAllocator(uPreallocationSize)
    {
    }

    // Necessary for testing
    StackAllocatorWhiteBox(const puint_z uPreallocationSize, const Alignment& alignment) : StackAllocator(uPreallocationSize, alignment)
    {
    }

    // Necessary for testing
    StackAllocatorWhiteBox(const puint_z uPreallocationSize, void* pMemAddress) : StackAllocator(uPreallocationSize, pMemAddress)
    {
    }

    // Necessary for testing
    StackAllocatorWhiteBox(const puint_z uPreallocationSize, void* pMemAddress, const Alignment& alignment) : StackAllocator(uPreallocationSize, pMemAddress, alignment)
    {
    }


	// METHODS
	// ---------------

public:

    // Exposed member.
    void* GetpBase() const
    {
        return m_pBase;
    }

    // Exposed member.
    Alignment GetAlignmentValue() const
    {
        return m_alignment;
    }

    // Exposed member.
    void* GetpPrevious() const
    {
        return m_pPrevious;
    }

    // Exposed member.
    // This member will NOT modify the preallocated block in the resident stack allocator,
    // is just for testing.
    void* PreallocatePublic (const puint_z uPreallocationSize,
                             const Alignment& alignment)
    {
        return this->Preallocate(uPreallocationSize, alignment);
    }

    // Exposed member.
    void SetuAllocatedBytes(const puint_z uAllocatedBytes)
    {
        m_uAllocatedBytes = uAllocatedBytes;
    }

    // Enable or disable the deletion of the preallocated block. If disabled, this one must be deleted
    // externally in order to avoid a huge memory leak.
    void SetDeletePreallocatedBlock(const bool bDeletePreallocatedBlock)
    {
        m_bDeletePreallocatedBlock = bDeletePreallocatedBlock;
    }

    // Sabotages a StackAllocator correctly created as if it was not be created properly.
    void SabotageStackAllocator()
    {
        StackAllocator::Clear();

        if(StackAllocator::m_bDeletePreallocatedBlock)
            operator delete(StackAllocator::m_pBase, StackAllocator::m_alignment);

        StackAllocator::ClearAttributes();
    }

    // This method returns the starting address of the allocated memory block placed at the top of the stack.
    void* GetMemoryBlockStart()
    {
        puint_z uBaseAddress = rcast_z(m_pPrevious, puint_z);
        uBaseAddress += ( sizeof(BlockHeader) + (scast_z(m_pPrevious, BlockHeader*)->GetAlignmentOffset()) );
        return rcast_z(uBaseAddress, void*);
    }
};

} // namespace Test
} // namespace z

#endif // __STACKALLOCATORWHITEBOX__
