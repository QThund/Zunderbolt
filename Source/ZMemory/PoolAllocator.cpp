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

#include "ZMemory/PoolAllocator.h"
#include "ZCommon/AllocationOperators.h"
// To use memcpy
#include <cstring>

#include "ZCommon/Assertions.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

PoolAllocator::PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const Alignment &alignment) :
            m_uBlockSize(uBlockSize),
            m_uPoolSize(uSize),
            m_uAllocatedBytes(0),
            m_uAlignment(alignment),
            m_bNeedDestroyMemoryChunk(true)
{
    Z_ASSERT_ERROR( 0 != uSize, "Size cannot be zero"  );
    Z_ASSERT_ERROR( 0 != uBlockSize, "Block size cannot be zero" );

    m_pAllocatedMemory = operator new(m_uPoolSize, alignment);
    Z_ASSERT_ERROR( null_z != m_pAllocatedMemory, "Pointer to allocated memory is null" );

    m_pFirst = m_pAllocatedMemory;

    m_uBlocksCount = m_uPoolSize / uBlockSize;

    this->AllocateFreeBlocksList();
}

PoolAllocator::PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const void *pBuffer) :
            m_uBlockSize(uBlockSize),
            m_uPoolSize(uSize),
            m_uAllocatedBytes(0),
            m_uAlignment(Alignment(sizeof(void**))),
            m_bNeedDestroyMemoryChunk(false)
{
    Z_ASSERT_ERROR( 0 != uSize, "Size cannot be zero" );
    Z_ASSERT_ERROR( 0 != uBlockSize, "Block size cannot be zero" );
    Z_ASSERT_ERROR( 0 != pBuffer, "Pointer to buffer cannot be null" );

    m_pAllocatedMemory = (void**)align_z(pBuffer, m_uAlignment);
    m_pFirst = m_pAllocatedMemory;

    puint_z uAdjustment = alignment_offset_z(pBuffer, m_uAlignment);
    m_uBlocksCount = (m_uPoolSize - uAdjustment) / uBlockSize;

    this->AllocateFreeBlocksList();
}

PoolAllocator::PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const void *pBuffer, const Alignment &alignment) :
            m_uBlockSize(uBlockSize),
            m_uPoolSize(uSize),
            m_uAllocatedBytes(0),
            m_uAlignment(alignment),
            m_bNeedDestroyMemoryChunk(false)
{
    Z_ASSERT_ERROR( 0 != uSize, "Size cannot be zero" );
    Z_ASSERT_ERROR( 0 != uBlockSize, "Block size cannot be zero" );
    Z_ASSERT_ERROR( 0 != pBuffer, "Pointer to buffer cannot be null" );

    m_pAllocatedMemory = (void**)align_z(pBuffer, m_uAlignment);
    m_pFirst = m_pAllocatedMemory;

    puint_z uAdjustment = alignment_offset_z(pBuffer, m_uAlignment);
    m_uPoolSize -= uAdjustment; // Some free space is lost

    m_uBlocksCount = m_uPoolSize / uBlockSize;

    this->AllocateFreeBlocksList();
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |          DESTRUCTOR        |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

PoolAllocator::~PoolAllocator()
{
    if(m_bNeedDestroyMemoryChunk)
        operator delete(m_pAllocatedMemory, m_uAlignment);

    operator delete(m_ppFreeBlocks);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void* PoolAllocator::Allocate()
{
    if( null_z == m_ppNextFreeBlock )
        return null_z;

    m_uAllocatedBytes += m_uBlockSize;

    // Takes the index of the next free block from the free blocks pointers list.
    puint_z uNextFreeBlockIndex = m_ppNextFreeBlock - m_ppFreeBlocks;

    // Updates with the pointer to the new free block pointer.
    m_ppNextFreeBlock = (void**)*m_ppNextFreeBlock;

    // Returns pointer to the allocated block from the index taken before.
    return (void*)((puint_z)m_pFirst + uNextFreeBlockIndex * m_uBlockSize);
}

void PoolAllocator::Deallocate(const void* pBlock)
{
    Z_ASSERT_ERROR( null_z != pBlock, "Pointer to block to deallocate cannot be null" );
    Z_ASSERT_ERROR( (puint_z)pBlock >= (puint_z)m_pAllocatedMemory && (puint_z)pBlock <= ((puint_z)m_pAllocatedMemory + m_uSize), "Pointer to block to deallocate must be an address provided by this pool allocator" );

    m_uAllocatedBytes -= m_uBlockSize;

    // Calculates the address in the blocks pointers list of the block to deallocate.
    // ppDeallocatedBlock = m_ppFreeBlocks + Index of the block to deallocate
    void **ppDeallocatedBlock = m_ppFreeBlocks + (((puint_z)pBlock - (puint_z)m_pFirst) / m_uBlockSize);

    // Inserts at the beginning of the free blocks pointers list the deallocated block.
    *ppDeallocatedBlock = m_ppNextFreeBlock;
    m_ppNextFreeBlock = (void**)ppDeallocatedBlock;
}


void PoolAllocator::Clear()
{
    m_ppNextFreeBlock = m_ppFreeBlocks;
    this->ClearFreeBlocksList();
}

void PoolAllocator::CopyTo(PoolAllocator &poolAllocator) const
{
    Z_ASSERT_ERROR(m_uBlocksCount <= poolAllocator.m_uBlocksCount, "Blocks count of destination pool allocator must be greater or equal than the source pool allocator" );
    Z_ASSERT_ERROR(m_uPoolSize <= poolAllocator.m_uPoolSize, "Chunk size for allocations must be greater or equal in the destination pool allocator than in the source pool allocator" );
    Z_ASSERT_ERROR(m_uBlockSize == poolAllocator.m_uBlockSize, "Block sizes of origin and destination pool allocators must be equal");
    Z_ASSERT_WARNING(poolAllocator.m_uAlignment == m_uAlignment, "The alignment of the input allocator is different from the resident allocator's.");

    if(null_z == m_ppNextFreeBlock)
    {
        // No free blocks in source. Append extra destination free blocks pointers if it has more blocks count.
        if(m_uBlocksCount < poolAllocator.m_uBlocksCount)
        {
            // ppNext = first free block of remaining free blocks.
            void **ppNext = poolAllocator.m_ppFreeBlocks + m_uBlocksCount;

            // Assigns the next free block in the destination pool
            poolAllocator.m_ppNextFreeBlock = ppNext;

            // Frees remaining blocks from destination redoing the rest of the list.
            for( puint_z uIndex = m_uBlocksCount; uIndex < poolAllocator.m_uBlocksCount - 1; ++uIndex )
            {
                *ppNext = (void*)((void**)ppNext + 1);
                ppNext = (void**)*ppNext;
            }

            *ppNext = null_z;
        }
        else
        {
            poolAllocator.m_ppNextFreeBlock = null_z;
        }
    }
    else
    {
        // Assigns the next free block in the destination pool (same block index as in origin).
        poolAllocator.m_ppNextFreeBlock = poolAllocator.m_ppFreeBlocks + (m_ppNextFreeBlock - m_ppFreeBlocks);

        // Copy free blocks pointers list from source to destination
        void **ppLastFreeBlock = m_ppNextFreeBlock;

        while( null_z != *ppLastFreeBlock )
        {
            // Index of the next free block in the source = *ppLastFreeBlock - m_ppFreeBlocks
            *(poolAllocator.m_ppFreeBlocks + ((void**)ppLastFreeBlock - m_ppFreeBlocks)) =
                                    poolAllocator.m_ppFreeBlocks + ((void**)*ppLastFreeBlock - m_ppFreeBlocks);

            // ppLastFreeBlock will contain the pointer to last free block in the list or null if there are no free blocks
            // when exits from the while loop.
            if(null_z != *ppLastFreeBlock)
                ppLastFreeBlock = (void**)*ppLastFreeBlock;
        }

        if(m_uBlocksCount < poolAllocator.m_uBlocksCount)
        {
            // Appends extra free blocks pointers of destination

            // Links copied free blocks list from source to remaining free blocks from destination.

            // ppNext = first free block of remaining free blocks.
            void **ppNext = poolAllocator.m_ppFreeBlocks + m_uBlocksCount;

            // Links two lists.
            *(poolAllocator.m_ppFreeBlocks +  (ppLastFreeBlock - m_ppFreeBlocks)) = ppNext;

            // Frees the rest of blocks from destination redoing the rest of the list.
            for( puint_z uIndex = m_uBlocksCount; uIndex < poolAllocator.m_uBlocksCount - 1; uIndex++ )
            {
                *ppNext = (void*)((void**)ppNext + 1);
                ppNext = (void**)*ppNext;
            }

            *ppNext = null_z;
        }
    }

    // Copies all source blocks in destination
    memcpy(poolAllocator.m_pFirst, m_pFirst, m_uBlockSize * m_uBlocksCount);

    poolAllocator.m_uAllocatedBytes = m_uAllocatedBytes;
}

void PoolAllocator::Reallocate(const puint_z uNewSize)
{
    Z_ASSERT_WARNING(uNewSize > m_uPoolSize, "The new size must be greater than the current size of the pool.");

    if(uNewSize > m_uPoolSize)
    {
        void* pNewLocation = operator new(uNewSize, m_uAlignment);

        this->InternalReallocate(uNewSize, pNewLocation);

        m_bNeedDestroyMemoryChunk = true;
    }
}

void PoolAllocator::Reallocate(const puint_z uNewSize, const void* pNewLocation)
{
    Z_ASSERT_WARNING(uNewSize > m_uPoolSize, "The new size must be greater than the current size of the pool.");
    Z_ASSERT_ERROR(pNewLocation != null_z, "The input new location cannot be null.");

    if(uNewSize > m_uPoolSize && pNewLocation != null_z)
    {
        puint_z uNewLocationAddress = (puint_z)pNewLocation;
        void* pAdjustedNewLocation = (void*)align_z(pNewLocation, m_uAlignment);

        this->InternalReallocate(uNewSize, pAdjustedNewLocation);

        m_bNeedDestroyMemoryChunk = false;
    }
}

void PoolAllocator::AllocateFreeBlocksList()
{
    m_ppFreeBlocks = (void**) operator new(m_uBlocksCount * sizeof(void**));
    Z_ASSERT_ERROR( null_z != m_ppFreeBlocks, "Pointer to allocated memory for internals is null" );

    m_ppNextFreeBlock = m_ppFreeBlocks;
    m_uSize = m_uPoolSize + m_uBlocksCount * sizeof(void**);

    this->ClearFreeBlocksList();
}

void PoolAllocator::ClearFreeBlocksList()
{
    void **ppNext = m_ppFreeBlocks;

    // Every pointer points to the next pointer as a linked list of free blocks to allocate.
    for( puint_z uIndex = 0; uIndex < m_uBlocksCount - 1; uIndex++ )
    {
        *ppNext = (void*)((void**)ppNext + 1);
        ppNext = (void**)*ppNext;
    }

    *ppNext = null_z;

    m_uAllocatedBytes = 0;
}

void PoolAllocator::InternalReallocate(const puint_z uNewSize, void* pNewLocation)
{
    puint_z uNewBlocksCount = uNewSize / m_uBlockSize;

    Z_ASSERT_ERROR( null_z != pNewLocation, "Pointer to allocated memory is null" );

    memcpy(pNewLocation, m_pFirst, m_uBlockSize * m_uBlocksCount);

    // Copies the free block list
    // -----------------------------------
    void** ppNewFreeBlockList = (void**) operator new(uNewBlocksCount * sizeof(void**));

    Z_ASSERT_ERROR( null_z != ppNewFreeBlockList, "Pointer to allocated memory for internals is null" );

    if(null_z == m_ppNextFreeBlock) // No free blocks in source.
    {
        // Appends extra destination free blocks pointers
        // ppNext = first free block of remaining free blocks.
        void** ppNext = ppNewFreeBlockList + m_uBlocksCount;

        // Assigns the next free block
        m_ppNextFreeBlock = ppNext;

        // Frees remaining blocks from destination redoing the rest of the list.
        for( puint_z uIndex = m_uBlocksCount; uIndex < uNewBlocksCount - 1U; ++uIndex )
        {
            *ppNext = (void*)(ppNext + 1U);
            ++ppNext;
        }

        *ppNext = null_z;
    }
    else
    {
        // Copy free blocks pointers list from source to destination
        void** ppLastFreeBlock = m_ppNextFreeBlock;

        while( null_z != *ppLastFreeBlock )
        {
            // Index of the next free block in the source = *ppLastFreeBlock - m_ppFreeBlocks
            puint_z uLastFreeBlockPosition = (void**)(ppLastFreeBlock) - m_ppFreeBlocks;
            puint_z uNextFreeBlockPosition = (void**)(*ppLastFreeBlock) - m_ppFreeBlocks;
            *(ppNewFreeBlockList + uLastFreeBlockPosition) = ppNewFreeBlockList + uNextFreeBlockPosition;

            // Moves to the next free block
            ppLastFreeBlock = (void**)*ppLastFreeBlock;
        }

        // Assigns the next free block in the destination (same block index as in origin).
        m_ppNextFreeBlock = ppNewFreeBlockList + (m_ppNextFreeBlock - m_ppFreeBlocks);

        // Appends extra free blocks pointers of destination
        // Links copied free blocks list from source to remaining free blocks from destination.

        // ppNext = first free block of remaining free blocks.
        void** ppNext = ppNewFreeBlockList + m_uBlocksCount;

        // Links two lists.
        *(ppNewFreeBlockList + (ppLastFreeBlock - m_ppFreeBlocks)) = ppNext;

        // Frees the rest of blocks from destination redoing the rest of the list.
        for( puint_z uIndex = m_uBlocksCount; uIndex < uNewBlocksCount - 1U; ++uIndex )
        {
            *ppNext = (void*)(ppNext + 1U);
            ++ppNext;
        }

        *ppNext = null_z;
    }

    // Updates some additional fields
    // ---------------------------------
    m_uBlocksCount = uNewBlocksCount;
    m_uPoolSize = uNewSize;
    m_uSize = m_uPoolSize + sizeof(void**) * m_uBlocksCount;

    // Frees the old buffers
    // -------------------------
    if(m_bNeedDestroyMemoryChunk)
        operator delete(m_pAllocatedMemory, m_uAlignment);
    
    m_pAllocatedMemory = pNewLocation;
    m_pFirst = m_pAllocatedMemory;

    operator delete(m_ppFreeBlocks);
    m_ppFreeBlocks = ppNewFreeBlockList;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



} // namespace z
