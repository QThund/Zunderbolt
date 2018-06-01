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

#ifndef __POOLALLOCATOR__
#define __POOLALLOCATOR__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZCommon/CommonModuleDefinitions.h"
#include "ZCommon/Alignment.h"
#include "ZMemory/MemoryModuleDefinitions.h"


namespace z
{

/// <summary>
/// Represents a custom allocator that works as a pool, providing a limited set of fixed-size and fixed-alignment blocks
/// that are occupied and released as demanded.
/// </summary>
class Z_MEMORY_MODULE_SYMBOLS PoolAllocator
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructs a pool allocator passing the pool size, block size and memory alignment.
    /// </summary>
    /// <remarks>
    /// Pre-allocates uSize bytes plus a maximum of (uSize/uBlockSize)*sizeof(void**) bytes for internals.<br/>
    /// Invalid values of the parameters may cause an unexpected behaviour.
    /// </remarks>
    /// <param name="uSize">[IN] Size of the pool, in bytes. It must be greater than zero.</param>
    /// <param name="uBlockSize">[IN] Size of each block to allocate, in bytes. It must be greater than zero.</param>
    /// <param name="alignment">[IN] Multiple of which must be the memory address. All the blocks will have the same alignment.</param>
    PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const Alignment &alignment); 

    /// <summary>
    /// Constructs a pool allocator passing the pool size, block size and memory address of a valid buffer to be used by the pool.
    /// </summary>
    /// <remarks>
    /// It uses a pointer to a buffer to allocate blocks but it will also allocate a maximum of (uSize/uBlockSize)*sizeof(void**) bytes for internals.<br/>
    /// Destructor will not free the buffer passed to be used by the pool.
    /// Invalid values of the parameters may cause an unexpected behaviour.
    /// </remarks>
    /// <param name="uSize">[IN] Size of the pool, in bytes. It must be greater than zero.</param>
    /// <param name="uBlockSize">[IN] Size of each block to allocate, in bytes. It must be greater than zero.</param>
    /// <param name="pBuffer">[IN] Pointer to an allocated buffer of size greater or equal than size passed in the parameter.</param>
    PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const void *pBuffer); 

    /// <summary>
    /// Constructs a pool allocator passing the pool size, blocks size, memory address of a valid buffer to be used by the pool and the alignment.
    /// </summary>
    /// <remarks>
    /// It uses the passed buffer to allocate blocks but it will also allocate a maximum of (uSize/uBlockSize)*sizeof(void**) bytes for internals.<br/>
    /// The buffer may not start exactly at the memory address passed as parameter due to the alignment adjustment. This will cause that the size may not be 
    /// exactly what was passed as parameter.<br/>
    /// Destructor will not free the buffer passed for the pool.
    /// Invalid values of the parameters may cause an unexpected behaviour.
    /// </remarks>
    /// <param name="uSize">[IN] Size of the pool, in bytes. It must be greater than zero.</param>
    /// <param name="uBlockSize">[IN] Size of each block to allocate, in bytes. It must be greater than zero.</param>
    /// <param name="pBuffer">[IN] Pointer to an allocated buffer of size greater than or equal to the size passed in the parameter.</param>
    /// <param name="alignment">[IN] Multiple of which must be the memory address. All the blocks will have the same alignment.</param>
    PoolAllocator(const puint_z uSize, const puint_z uBlockSize, const void *pBuffer, const Alignment &alignment); 

private:

    // Disabled.
    PoolAllocator(const PoolAllocator &);
    

    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. It will free memory chunk allocated for the pool if no buffer was supplied in constructor. 
    /// </summary>        
    ~PoolAllocator();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Allocates a block in the pool and returns its address.
    /// </summary>
    /// <returns>
    /// Pointer to the allocated memory block. Returns null if pool is full.
    /// </returns>
    void* Allocate();

    /// <summary>
    /// Deallocates the block passed in the parameter.
    /// </summary>        
    /// <param name="pBlock">[IN] Pointer to a block previously allocated with the corresponding class method. Other values may cause an unexpected behaviour.</param>
    void Deallocate( const void* pBlock );

    /// <summary>
    /// Clears the pool, so that makes it all available to allocate.
    /// </summary>        
    void Clear();

    /// <summary>
    /// Copies raw data in allocated blocks into destination pool allocator passed by parameter.
    /// </summary>    
    /// <remarks>
    /// The size of destination pool allocator must be greater or equal than the size of the source pool. 
    /// The block size of the destination pool allocator must be equal than the source block size.<br />
    /// If the amount of blocks of the destination pool is greater than source pool's, exceeding blocks will be appended to the list of free blocks.
    /// </remarks>
    /// <param name="poolAllocator">[IN/OUT] The destination allocator.</param>
    void CopyTo(PoolAllocator &poolAllocator) const;

    /// <summary>
    /// Moves the allocated data to a bigger memory block at a different memory address.
    /// </summary>    
    /// <remarks>
    /// The new address will be resolved by the system. The internal buffer's memory address will be adjusted to the same alignment.
    /// </remarks>
    /// <param name="uNewSize">[IN] The new size of the pool, in bytes. It must be greater than the current size of the pool; otherwise, no action 
    /// will be performed.</param>
    void Reallocate(const puint_z uNewSize);

    /// <summary>
    /// Moves the allocated data to a bigger memory block at a different memory address.
    /// </summary>
    /// <remarks>
    /// The buffer's memory address will be adjusted to the same alignment so, if it is not already aligned, there will be some memory loss.
    /// </remarks>
    /// <param name="uNewSize">[IN] The new size of the pool, in bytes. It must be greater than the current size of the pool; otherwise, no action 
    /// will be performed.</param>
    /// <param name="pNewLocation">[IN] The new memory address where the new block will be reserved. It must not be null, or no reallocation will be done.</param>
    void Reallocate(const puint_z uNewSize, const void* pNewLocation);


private:

    // Disabled.
    PoolAllocator& operator=(const PoolAllocator &poolAllocator); 

    /// <summary>
    /// Allocates and initializes the free blocks list.
    /// </summary>    
    void AllocateFreeBlocksList();

    /// <summary>
    /// Initializes the free blocks list. So all blocks area available to allocate.
    /// </summary>    
    void ClearFreeBlocksList(); 

    /// <summary>
    /// Moves the allocated data to a bigger memory block at a different memory address. It's intended for internal use only.
    /// </summary>    
    /// <param name="uNewSize">[IN] The new size of the pool, in bytes. It must be greater than the current size of the pool; otherwise, no action 
    /// will be performed.</param>
    /// <param name="pNewLocation">[IN] The new memory address where the new block will be reserved. It must not be null, or no reallocation will be done.</param>
    void InternalReallocate(const puint_z uNewSize, void* pNewLocation);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Returns the size of the buffer reserved to allocate blocks (passed to the constructors as pool's size parameter)
    /// plus the size of the chunk reserved for internals.
    /// </summary>    
    /// <returns>
    /// The size of the buffer reserved to allocate blocks plus the size of the chunk reserved for internals.
    /// </returns>    
    inline puint_z GetTotalSize() const
    {
        return m_uSize;
    }

    /// <summary>
    /// Returns the size of the buffer reserved to allocate blocks (passed to the constructors as pool's size parameter).
    /// </summary>    
    /// <returns>
    /// The size of the buffer reserved to allocate blocks.
    /// </returns>    
    inline puint_z GetPoolSize() const
    {
        return m_uPoolSize;
    }

    /// <summary>
    /// Returns if there are free blocks to allocate.
    /// </summary>        
    /// <returns>
    /// True if there are free blocks to allocate. Otherwise returns false.
    /// </returns>
    inline bool CanAllocate() const
    {
        return null_z != m_ppNextFreeBlock;
    }

    /// <summary>
    /// Returns the bytes sum of current allocated blocks.
    /// </summary>        
    /// <returns>
    /// The bytes sum of current allocated blocks.
    /// </returns>        
    inline puint_z GetAllocatedBytes() const
    {
        return m_uAllocatedBytes;
    }

    /// <summary>
    /// Returns a pointer to the first block of the entire chunk of memory.
    /// </summary>        
    /// <returns>
    /// A pointer to the first block of the entire chunk of memory.
    /// </returns>        
    inline void* GetPointer() const
    {
        return m_pFirst;
    }

    /// <summary>
    /// Returns the memory alignment.
    /// </summary>        
    /// <returns>
    /// The memory alignment.
    /// </returns>        
    inline Alignment GetAlignment() const
    {
        return m_uAlignment;
    }


    // ATTRIBUTES
    // ---------------
protected:
    /// <summary>
    /// Pointer to the chunk containing pointers to the free blocks of the pool.
    /// </summary>        
    void** m_ppFreeBlocks;

    /// <summary>
    /// Pointer to the block containing the pointer to the next free block.
    /// </summary>        
    void** m_ppNextFreeBlock;

    /// <summary>
    /// Pointer to the first block in the pool.
    /// </summary>    
    /// <remarks>
    /// It takes into account the alignment offset.
    /// </remarks>
    void* m_pFirst;

    /// <summary>
    /// Size of blocks to allocate.
    /// </summary>    
    puint_z m_uBlockSize;

    /// <summary>
    /// Size of the pre-allocated chunk for the blocks (bytes needed for alignment are included).
    /// </summary>    
    puint_z m_uPoolSize;

    /// <summary>
    /// Size of the pre-allocated chunk for the blocks (bytes needed for alignment are included) plus memory reserved for internals.
    /// </summary>    
    puint_z m_uSize;

    /// <summary>
    /// Sum of current allocated bytes.
    /// </summary>    
    puint_z m_uAllocatedBytes;

    /// <summary>
    /// Alignment of the pool.
    /// </summary>    
    Alignment m_uAlignment;

    /// <summary>
    /// Pointer to the chunk with the blocks of the pool.
    /// </summary>    
    /// <remarks>
    /// It does not take into account the alignment offset.
    /// </remarks>
    void* m_pAllocatedMemory;

private:
        
    /// <summary>
    /// Number of blocks that fit into the pool allocator.
    /// </summary>    
    puint_z m_uBlocksCount;

    /// <summary>
    /// False if memory buffer was passed by parameter to the constructor, in which case it does not need to be destroyed.
    /// Otherwise True and memory buffer needs to be destroyed.
    /// </summary>    
    bool m_bNeedDestroyMemoryChunk;
};

} // namespace z


#endif // __POOLALLOCATOR__
