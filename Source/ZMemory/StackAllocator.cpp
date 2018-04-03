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

#include "ZMemory/StackAllocator.h"

#include <cstring>                  // memcpy
#include "ZMemory/AllocationOperators.h"
#include "ZCommon/Assertions.h"


namespace z
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const puint_z StackAllocator::ALIGNMENT_VALUE_DEFAULT = 1;


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

StackAllocator::StackAllocator(const puint_z uPreallocationSize) : m_alignment(ALIGNMENT_VALUE_DEFAULT)
{
    // In this case, the preallocated block has to be deleted by the stack allocator.
    m_bDeletePreallocatedBlock = true;

    this->ClearAttributes();

    Z_ASSERT_ERROR(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");

    Alignment alignDefault(ALIGNMENT_VALUE_DEFAULT);

    m_pBase = this->Preallocate(uPreallocationSize, alignDefault);
    Z_ASSERT_ERROR(null_z != m_pBase, "Error during preallocation, stack base remains as null.");

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

StackAllocator::StackAllocator(const puint_z uPreallocationSize, const Alignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has to be deleted by the stack allocator.
    m_bDeletePreallocatedBlock = true;

    this->ClearAttributes();

    Z_ASSERT_ERROR(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");

    m_pBase = this->Preallocate(uPreallocationSize, alignment);
    Z_ASSERT_ERROR(null_z != m_pBase, "Error during preallocation, stack base remains as null.");

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

StackAllocator::StackAllocator(const puint_z uPreallocationSize, void* pMemAddress) : m_alignment(ALIGNMENT_VALUE_DEFAULT)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    Z_ASSERT_ERROR(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    Z_ASSERT_ERROR(null_z != pMemAddress, "The input pointer to a preallocated memory block cannot be null.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase = pMemAddress;
    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize;
}

StackAllocator::StackAllocator(const puint_z uPreallocationSize, void* pMemAddress, const Alignment& alignment) : m_alignment(alignment)
{
    // In this case, the preallocated block has NOT to be deleted by the stack allocator (it will be done so externally
    // by the entity which passed it).
    m_bDeletePreallocatedBlock = false;

    this->ClearAttributes();

    puint_z uAlignment = alignment;

    Z_ASSERT_ERROR(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");
    Z_ASSERT_ERROR(null_z != pMemAddress, "The input pointer to a preallocated memory block cannot be null.");

    // VERY IMPORTANT: there is no way to prove pMemAddress points to the start of a real allocated memory block.
    m_pBase = pMemAddress;
        
    // If necessary, adjust the address of the stack base to make it to point to the first address, starting from
    // the input address, that has the given alignment.
    puint_z  uAmountMisalignedBytes = (rcast_z(m_pBase, puint_z)) & (uAlignment - 1U);
    if (uAmountMisalignedBytes > 0)
    {
        puint_z  uAddressResult = (rcast_z(m_pBase, puint_z)) + uAmountMisalignedBytes;
        m_pBase = rcast_z(uAddressResult, void*);
    }

    m_pTop  = m_pPrevious = m_pBase;
    m_uSize = uPreallocationSize - uAmountMisalignedBytes;
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		  DESTRUCTOR		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

StackAllocator::~StackAllocator()
{
    // Deallocate the preallocated memory block if it has to be made.
    if (true == m_bDeletePreallocatedBlock)
    {
        operator delete(m_pBase, m_alignment);
    }
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

void* StackAllocator::Preallocate(const puint_z uPreallocationSize, const Alignment& alignment)
{
    Z_ASSERT_ERROR(uPreallocationSize > 0, "The given size for the preallocated memory block cannot be zero.");

    // If something goes wrong (and the block cannot be allocated) a null pointer is returned.
    void* pPreallocatedRes = operator new(uPreallocationSize, alignment);

    Z_ASSERT_ERROR(null_z != pPreallocatedRes, "It couldn't preallocate the asked memory block.");

    return pPreallocatedRes;
}

void* StackAllocator::Allocate(const puint_z uSize)
{
    return this->Allocate( uSize, Alignment(ALIGNMENT_VALUE_DEFAULT) );
}

void* StackAllocator::Allocate(const puint_z uSize, const Alignment& alignment)
{
    Z_ASSERT_ERROR(uSize > 0, "The given size for the memory block to allocate cannot be zero.");
    Z_ASSERT_WARNING(this->CanAllocate(uSize, alignment), "Allocation cannot be accomplished, currently there's not enough space to allocate a memory block with such size.");

    void* pAllocBlock = null_z;

    if(this->CanAllocate(uSize, alignment))
    {
        // STEP 1) Prerrequisites.
        m_pPrevious = m_pTop;

        // STEP 2) Compute the alignment offset, if it proceeds.
        puint_z uAmountMisalignedBytes = (rcast_z(m_pTop, puint_z) + StackAllocator::GetBlockHeaderSize()) & (alignment - 1U);

        // STEP 3) Create a Block Header.
        //         (** using the so-called 'placement new operator' **).
        BlockHeader* pLastBlock = scast_z(m_pPrevious, BlockHeader*);
        puint_z uOffsetToPreviousBlock = pLastBlock != null_z ? 
                                                                      0 : 
                                                                      pLastBlock->GetAllocatedBlockSize() + pLastBlock->GetAlignmentOffset() + StackAllocator::GetBlockHeaderSize();

        new (m_pTop) BlockHeader(uSize, uAmountMisalignedBytes, uOffsetToPreviousBlock);

        // STEP 4) Gets the allocated block and moves the stack top above it
        puint_z uAllocatedBlockAddress = rcast_z(m_pTop, puint_z) + StackAllocator::GetBlockHeaderSize() + uAmountMisalignedBytes;
        pAllocBlock = rcast_z(uAllocatedBlockAddress, void*);
        m_pTop = rcast_z(uAllocatedBlockAddress + uSize, void*);
        

        // STEP 5) Update the current size (in bytes) of occupied size in the stack allocator,
        //         counting on the size of the Block Header as well.
        m_uAllocatedBytes += StackAllocator::GetBlockHeaderSize() + uAmountMisalignedBytes + uSize;
    }

    // STEP 6) Return the pointer to the block header.
    return pAllocBlock;
}

void StackAllocator::Deallocate()
{
    Z_ASSERT_WARNING(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");
    
    if(this->GetAllocatedBytes() > 0)
    {
        // STEP 1) Compute the Previous header.

        puint_z uBackOffset          = scast_z(m_pPrevious, BlockHeader*)->GetPreviousHeaderBackOffset();
        puint_z uPointerDecremented  = rcast_z(m_pPrevious, puint_z) - uBackOffset;
        void*          pPreviousBlockHeader = rcast_z(uPointerDecremented, void*);

        if (null_z == pPreviousBlockHeader)
        {
            pPreviousBlockHeader = m_pBase;
        }


        // STEP 2) Compute the deallocation.

        m_pTop      = m_pPrevious;
        m_pPrevious = pPreviousBlockHeader;


        // STEP 3) Update the current size (in bytes) of occupied size in the stack allocator.

        m_uAllocatedBytes -= scast_z(m_pTop, BlockHeader*)->GetAllocatedBlockSize()
                              + scast_z(m_pTop, BlockHeader*)->GetAlignmentOffset()
                              + StackAllocator::GetBlockHeaderSize();
    }
}

void StackAllocator::Deallocate(const StackAllocator::Mark& mark)
{
    Z_ASSERT_WARNING(this->GetAllocatedBytes() > 0, "Error trying to deallocate: stack allocator is empty.");

    void* pMarkAddress = mark.GetMemoryAddress();

    Z_ASSERT_ERROR(null_z != pMarkAddress,  "The given mark address cannot be null.");
    Z_ASSERT_ERROR(pMarkAddress >= m_pBase, "Error: mark out of range --> lesser than stack base.");
    Z_ASSERT_ERROR(pMarkAddress <= m_pTop,  "Error: mark out of range --> greater than current stack top.");
    
    if(this->GetAllocatedBytes() > 0 && pMarkAddress >= m_pBase && pMarkAddress < m_pTop)
    {
        // STEP 1) Update 'm_pPrevious'.
     
        // Auxiliar variable that will store the accumulated decrement of allocates bytes during the traversal.
        puint_z uAcumDecrementOfAllocatedBytes = 0;

        uAcumDecrementOfAllocatedBytes = rcast_z(m_pTop, puint_z) - rcast_z(mark.GetMemoryAddress(), puint_z);
        BlockHeader* pMarkBlockHeader = scast_z(mark.GetMemoryAddress(), BlockHeader*);
        puint_z uMarkPreviousBlockAddress = rcast_z(mark.GetMemoryAddress(), puint_z) - pMarkBlockHeader->GetPreviousHeaderBackOffset();
        m_pPrevious = rcast_z(uMarkPreviousBlockAddress, void*);

        // Now 'm_pPrevious' is pointing to block header regarding to the memory block that now is considered the one
        // placed in the top of the stack.

        // STEP 2) Update the stack top.
        m_pTop = pMarkAddress;

        // Now 'm_pTop' is pointing to the start of the considered "free space" in the stack (everything stored in higher memory
        // addresses into the preallocated memory block is considered as released/deleted).
    
        // STEP 3) Update the amount of allocated bytes.
        m_uAllocatedBytes -= uAcumDecrementOfAllocatedBytes;
    }
}

void StackAllocator::Clear()
{
    m_pTop = m_pPrevious = m_pBase;
    m_uAllocatedBytes = 0;
}

puint_z StackAllocator::GetSize() const
{
    Z_ASSERT_ERROR(m_uAllocatedBytes <= m_uSize, "The amount of allocated bytes is greater than the size of the preallocated memory block.");
    return m_uSize;
}

bool StackAllocator::CanAllocate(const puint_z uSize) const
{
    Z_ASSERT_WARNING(uSize > 0, "The size of the memory block to be allocated cannot be zero.");

    puint_z uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
    puint_z uSpaceOccupiedByNewMemoryBlock =   uSize + StackAllocator::GetBlockHeaderSize();

    return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
}

bool StackAllocator::CanAllocate(const puint_z uSize, const Alignment& alignment) const
{
    Z_ASSERT_WARNING(uSize > 0, "The given size for the memory block to be allocated cannot be zero.");
    puint_z uAlignment = alignment;

    puint_z  uOffsetToAlign                 = ((rcast_z(m_pTop, puint_z)) + StackAllocator::GetBlockHeaderSize()) & (uAlignment - 1U);
    puint_z  uFreeSpaceInPreallocatedBlock  = m_uSize - m_uAllocatedBytes;
    puint_z  uSpaceOccupiedByNewMemoryBlock =   uSize + (StackAllocator::GetBlockHeaderSize()) + uOffsetToAlign;

    return uFreeSpaceInPreallocatedBlock >= uSpaceOccupiedByNewMemoryBlock;
}

puint_z StackAllocator::GetAllocatedBytes() const
{
    Z_ASSERT_ERROR(m_uAllocatedBytes <= m_uSize, "Error: the amount of allocated bytes is greater than the size of the preallocated memory block.");
    return m_uAllocatedBytes;
}

void StackAllocator::CopyTo(StackAllocator& stackAllocator) const
{
    Z_ASSERT_ERROR( (this->GetSize() > 0) && (stackAllocator.GetSize() > 0), "Error on copying of stack allocators: the size of any stack allocators cannot be zero.");
    Z_ASSERT_WARNING(this->GetSize() <= stackAllocator.GetSize(), "Error on copying of stack allocators: the size of the passed stack allocator cannot be lower than the size of the resident one.");
    Z_ASSERT_WARNING(m_alignment == stackAllocator.m_alignment, "Error on copying of stack allocators: the alignment of both allocators must be the same.");

    if(this->GetSize() <= stackAllocator.GetSize() && m_alignment == stackAllocator.m_alignment)
    {
        // If the above assertion has passed the test, is assumed that the amount of allocated bytes 
        // in the resident stack allocator will be <= than the amount of allocated bytes in the passed one.

        // STEP 1) Clear the passed stack allocator.
        stackAllocator.Clear();

        // STEP 2) Set the new state for the passed stack allocator, part 1/4: Setting the basic attributes for the class: alignment
        //         value and amount of allocated bytes.
        stackAllocator.m_uAllocatedBytes = this->m_uAllocatedBytes;

        // STEP 3) Set the new state for the passed stack allocator, part 2/4: Copying the preallocated block of the resident allocator
        //         onto the passed stack allocator.
        //
        //         VERY IMPORTANT: The passed stack allocator will keep its preallocated memory block due to two main reasons:
        //                           -The size of the resident stack allocator's preallocated block will be <= than the size of the passed one
        //                            when reached this stage, so there's no chance of overwritting a memory location out of bounds.
        //                           -It cannot be determined if the passed stack allocator's preallocated block was created by itself, or was
        //                            externally assigned, so it cannot be deleted.
        //                          
        //                         SUMMARIZING: The preallocated block of the passed stack allocator is overwritten accordingly, not deleted and
        //                                    then created from scratch.
        memcpy(stackAllocator.m_pBase, this->m_pBase, this->m_uAllocatedBytes);

        // STEP 4) Set the new state for the passed stack allocator, part 3/4: Updating its Stack Top.
        puint_z uAddressTemp = rcast_z(stackAllocator.m_pBase, puint_z) + stackAllocator.m_uAllocatedBytes;
        stackAllocator.m_pTop       = rcast_z(uAddressTemp, void*);

        // STEP 5) Set the new state for the passed stack allocator, part 4/4: Updating its m_pPrevious pointer.
        puint_z uBytesFromPreviousToBase = rcast_z(m_pPrevious, puint_z) - rcast_z(m_pBase, puint_z);
        stackAllocator.m_pPrevious = (void*)( (puint_z)stackAllocator.m_pBase + uBytesFromPreviousToBase );
    }
}

StackAllocator::Mark StackAllocator::GetMark() const
{
    Z_ASSERT_ERROR(null_z != m_pTop, "Error on retrieving a mark: stack top is null.");
    return Mark(m_pTop);
}

void StackAllocator::ClearAttributes()
{
    m_pBase = m_pTop = m_pPrevious = null_z;
    m_uSize = m_uAllocatedBytes    = 0;
}

} // namespace z
