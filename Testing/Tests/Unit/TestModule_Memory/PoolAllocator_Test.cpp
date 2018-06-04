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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMemory/PoolAllocator.h"
#include "PoolAllocatorWhiteBox.h"
#include "ZCommon/Alignment.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::PoolAllocatorWhiteBox;


ZTEST_SUITE_BEGIN( PoolAllocator_TestSuite )
    
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0.
/// </summary>
ZTEST_CASE( Constructor1_AssertionFailsWhenPoolSizeOrBlockSizeIsZero_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCK_SIZE_TO_ASSERT = 0;
    const puint_z POOL_SIZE_TO_ASSERT = 0;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;

    try
    {
        PoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        PoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if pre-allocated memory is correctly aligned.
/// </summary>
ZTEST_CASE( Constructor1_PreAllocatedMemoryIsAligned_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);
    const puint_z ZERO_CORRECTION_ALIGNMENT = 0;

    // [Execution]
    PoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    // [Verification]
    puint_z correctionAlignment = (puint_z)pool.GetpAllocatedMemory() & (ALIGNMENT - 1);
    BOOST_CHECK_EQUAL( correctionAlignment, ZERO_CORRECTION_ALIGNMENT );
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0 or buffer address is null.
/// </summary>
ZTEST_CASE( Constructor2_AssertionFailsWhenPoolSizeOrBlockSizeOrBufferAddressHasWrongValue_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer1 = malloc( POOL_SIZE );
    void* pBuffer2 = malloc( POOL_SIZE );

    const puint_z BLOCK_SIZE_TO_ASSERT = 0;
    const puint_z POOL_SIZE_TO_ASSERT = 0;
    void* pBufferToAssert = null_z;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;
    bool bBufferAssertionFailed    = false;

    try
    {
        PoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, pBuffer1);
    }
    catch(const AssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        PoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBuffer2);
    }
    catch(const AssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    try
    {
        PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, pBufferToAssert);
    }
    catch(const AssertException&)
    {
        bBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBufferAssertionFailed, ASSERTION_FAILED);

    free(pBuffer1);
    free(pBuffer2);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if pre-allocated memory points to passed buffer.
/// </summary>
ZTEST_CASE( Constructor2_PreAllocatedMemoryIsOnPassedBuffer_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    puint_z BLOCKS_COUNT = 4;
    puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer = malloc(POOL_SIZE);

    // [Execution]
   PoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, pBuffer);

    // [Verification]
    BOOST_CHECK_EQUAL((puint_z)pool.GetpAllocatedMemory(), (puint_z)pBuffer );

    free( pBuffer );
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when pool size is 0 or block size is 0 or buffer address is null.
/// </summary>
ZTEST_CASE( Constructor3_AssertionFailsWhenPoolSizeOrBlockSizeOrBufferAddressHasWrongValue_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*sizeof(f64_z);
    const Alignment ALIGNMENT(BLOCK_SIZE);
    void* pBuffer1 = malloc( POOL_SIZE );
    void* pBuffer2 = malloc( POOL_SIZE );

    const puint_z BLOCK_SIZE_TO_ASSERT = 0;
    const puint_z POOL_SIZE_TO_ASSERT = 0;
    void* pBufferToAssert = null_z;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    bool bSizeAssertionFailed      = false;
    bool bBlockSizeAssertionFailed = false;
    bool bBufferAssertionFailed    = false;

    try
    {
        PoolAllocator pool(POOL_SIZE_TO_ASSERT, BLOCK_SIZE, pBuffer1, ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bSizeAssertionFailed = true;
    }

    try
    {
        PoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBuffer2, ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bBlockSizeAssertionFailed = true;
    }

    try
    {
        PoolAllocator pool(POOL_SIZE, BLOCK_SIZE_TO_ASSERT, pBufferToAssert, ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBlockSizeAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bBufferAssertionFailed, ASSERTION_FAILED);

    free(pBuffer1);
    free(pBuffer2);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Pointer to first pre-allocated block is as expected
/// </summary>
ZTEST_CASE( Constructor3_PointerToFirstPreAllocatedBlockIsAsExpected_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    void* pBuffer = malloc( POOL_SIZE );
    void *pUnalignedBuffer = (void*)((puint_z)pBuffer + 1);

    const Alignment ALIGNMENT(BLOCK_SIZE);

    puint_z uAdjustment = ALIGNMENT - ((puint_z)pUnalignedBuffer & (ALIGNMENT - 1U));
    if(uAdjustment == ALIGNMENT) uAdjustment = 0;
    puint_z firstAlignedAddress = (puint_z)pUnalignedBuffer + uAdjustment;

    // [Execution]
    PoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, pUnalignedBuffer, ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL((puint_z)pool.GetpFirst(), firstAlignedAddress );

    free( pBuffer );
}


/// <summary>
/// Checks if pointer to first block of pre-allocated memory points to first aligned address on passed buffer.
/// </summary>
ZTEST_CASE( Allocate_FirstAllocatedBlockAddressEqualsFirstPreallocatedBlockAddress_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    PoolAllocatorWhiteBox pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    f64_z *pBlock = (f64_z*)pool.Allocate();

    // [Verification]
    BOOST_CHECK_EQUAL((puint_z)pool.GetpFirst(), (puint_z)pBlock );
}


/// <summary>
/// Checks if attempt to allocate on a full pool returns null pointer.
/// </summary>
ZTEST_CASE( Allocate_AllocateOnAFullPoolReturnsNullPointer_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_z *pBlock;

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT + 1; uIndex++ ) 
    {
        pBlock = (f64_z*)pool.Allocate();
    }

    // [Verification]
    BOOST_CHECK( pBlock == null_z );
}


/// <summary>
/// Checks if address of the second allocated block is as expected.
/// </summary>
ZTEST_CASE( Allocate_AllocatedAddressOfTheSecondBlockIsAsExpected_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_z *pFirstBlock  = (f64_z*)pool.Allocate();
    f64_z *pSecondBlock = (f64_z*)pool.Allocate();

    // [Verification]
    const puint_z EXPECTED_ADDRESS_SECOND_BLOCK = (puint_z)pFirstBlock + BLOCK_SIZE;
    BOOST_CHECK_EQUAL( (puint_z)pSecondBlock, EXPECTED_ADDRESS_SECOND_BLOCK );
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when block pointer is invalid.
/// </summary>
ZTEST_CASE( Deallocate_AssertionFailsWhenBlockPointerIsInvalid_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);

    void *pBufferToAssert1 = null_z;
    void *pBufferToAssert2 = malloc(POOL_SIZE);

    bool bNullBufferAssertionFailed = false;
    bool bInvalidBufferAssertionFailed = false;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    try
    {
        pool.Deallocate(pBufferToAssert1);
    }
    catch(const AssertException&)
    {
        bNullBufferAssertionFailed = true;
    }

    try
    {
        pool.Deallocate(pBufferToAssert2);

    }
    catch(const AssertException&)
    {
        bInvalidBufferAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bNullBufferAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bInvalidBufferAssertionFailed, ASSERTION_FAILED);

    free(pBufferToAssert2);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Checks if a deallocation of a block allows it to be allocated again.
/// </summary>
ZTEST_CASE( Deallocate_DeallocationOfABlockAllowsItToBeAllocatedAgain_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();
    f64_z *pSecondBlock = (f64_z*)pool.Allocate();
    pool.Allocate();

    pool.Deallocate(pSecondBlock);
    f64_z *pFourthBlock = (f64_z*)pool.Allocate();

    // [Verification]
    BOOST_CHECK_EQUAL((puint_z)pSecondBlock, (puint_z)pFourthBlock );
}


/// <summary>
/// Checks if deallocation of entire pool allows it to be allocated again
/// </summary>
ZTEST_CASE( Deallocate_DeallocationOfEntirePoolAllowsItToBeAllocatedAgain_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);
    f64_z* pBlocks[BLOCKS_COUNT];
    puint_z uAllocationsCount = 0;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pBlocks[uIndex] = (f64_z*)pool.Allocate();
    }

    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Deallocate( pBlocks[uIndex] );
    }

    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        f64_z *pBlock = (f64_z*)pool.Allocate();
        if( null_z != pBlock ) 
            uAllocationsCount++;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(  uAllocationsCount, BLOCKS_COUNT );
}


/// <summary>
/// Checks if clear a full pool makes it available to allocate again.
/// </summary>
ZTEST_CASE( Clear_ClearAFullPoolMakesItAvailableToAllocateAgain_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);
    unsigned int uAllocationsCount = 0;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Allocate();
    }

    pool.Clear();

    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        f64_z *pBlock = (f64_z*)pool.Allocate();
        if( null_z != pBlock ) 
            uAllocationsCount++;
    }
	
	// [Verification]
    BOOST_CHECK_EQUAL( uAllocationsCount, BLOCKS_COUNT );
}


/// <summary>
/// Checks if returns the size of memory pre-allocated plus the size of memory needed by internals.
/// </summary>
ZTEST_CASE( GetTotalSize_SizeOfMemoryPreAllocatedPlusSizeOfMemoryNeededByInternalsIsAsExpected_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    // Expected Size = pre-allocated size for the blocks + size of pointers list to free blocks.
    const puint_z EXPECTED_SIZE = POOL_SIZE + sizeof(puint_z*)*BLOCKS_COUNT;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    puint_z uTotalSize = pool.GetTotalSize();

    // [Verification]
    BOOST_CHECK_EQUAL( uTotalSize, EXPECTED_SIZE );
}

/// <summary>
/// Checks if returns de size of the pool.
/// </summary>
ZTEST_CASE( GetPoolSize_SizeOfThePoolIsAsExpected_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    puint_z uPoolSize = pool.GetPoolSize();

    // [Verification]
    BOOST_CHECK_EQUAL( uPoolSize, POOL_SIZE );
}

/// <summary>
/// Checks if returns false if cannot allocate.
/// </summary>
ZTEST_CASE( CanAllocate_ReturnsFalseIfCannotAllocate_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const bool CANNOT_ALLOCATE = false;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for( puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        pool.Allocate();
    }

    // [Verification]
    BOOST_CHECK_EQUAL( pool.CanAllocate(), CANNOT_ALLOCATE );
}


/// <summary>
/// Checks if returns true when can allocate.
/// </summary>
ZTEST_CASE( CanAllocate_ReturnsTrueWhenCanAllocate_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const bool CAN_ALLOCATE = true;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL( pool.CanAllocate(), CAN_ALLOCATE );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when zero blocks has been allocated.
/// </summary>
ZTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenZeroBlocksAllocated_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);
    const puint_z ZERO_ALLOCATED_BYTES = 0;

    puint_z uAllocatedBytesZeroExpected;

    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    uAllocatedBytesZeroExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesZeroExpected, ZERO_ALLOCATED_BYTES );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when one block has been allocated.
/// </summary>
ZTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenOneBlockAllocated_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);
    const puint_z ONE_BLOCK_ALLOCATED_BYTES = BLOCK_SIZE;
    
    puint_z uAllocatedBytesOneBlockExpected;
    
    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();

    uAllocatedBytesOneBlockExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesOneBlockExpected, ONE_BLOCK_ALLOCATED_BYTES );
}


/// <summary>
/// Check if Allocated Bytes is correctly calculated when all blocks has been allocated.
/// </summary>
ZTEST_CASE( GetAllocatedBytes_CheckIfCorrectlyCalculatedWhenAllBlocksAllocated_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT*BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);
    const puint_z FULL_ALLOCATED_BYTES = POOL_SIZE;

    puint_z uAllocatedBytesFullExpected;
    
    // [Execution]
    PoolAllocator pool(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    pool.Allocate();

    for(puint_z uIndex = 0; uIndex < BLOCK_SIZE; uIndex++)
    {
        pool.Allocate();
    }

    uAllocatedBytesFullExpected = pool.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL( uAllocatedBytesFullExpected, FULL_ALLOCATED_BYTES );
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when destination blocks count are minor than origin.
/// </summary>
ZTEST_CASE( CopyTo_AssertionFailsWhenDestinationBlocksCountAreMinorThanOrigin_Test )
{
    // [Preparation]

    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT_ORIGIN = 6;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN*BLOCK_SIZE;
    Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCKS_COUNT_DESTINATION = 4;
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    const bool ASSERTION_FAILED    = true;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    PoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    bool bAssertionFailed = false;

    try
    {
        poolOrigin.CopyTo(poolDestination);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when destination blocks size are minor than origin.
/// </summary>
ZTEST_CASE( CopyTo_AssertionFailsWhenDestinationBlocksSizeAreMinorThanOrigin_Test )
{
    // [Preparation]

    // Greater Blocks Size in origin
    const puint_z BLOCK_SIZE_ORIGIN = sizeof(f64_z)*2;
    const puint_z BLOCKS_COUNT = 6;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT*BLOCK_SIZE_ORIGIN;
    const Alignment ALIGNMENT_ORIGIN(BLOCK_SIZE_ORIGIN);

    const puint_z BLOCK_SIZE_DESTINATION = sizeof(f64_z);
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT*BLOCK_SIZE_DESTINATION;
    const Alignment ALIGNMENT_DESTINATION(BLOCK_SIZE_DESTINATION);

    const bool ASSERTION_FAILED    = true;

    // [Execution]

    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE_ORIGIN, ALIGNMENT_ORIGIN);
    PoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE_DESTINATION, ALIGNMENT_DESTINATION);

    bool bAssertionFailed = false;

    try
    {
        poolOrigin.CopyTo(poolDestination);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}


#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <summary>
/// Case when origin allocator has less blocks than destination and all blocks allocated.
/// It checks that origin blocks has correctly copied.
/// </summary>
ZTEST_CASE( CopyTo_CheckIfCorrectlyCopiedWhenOriginAllocatorHasLessBlocksAndAllBlocksAllocated_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT_ORIGIN = 4;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCKS_COUNT_DESTINATION = 6;
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    PoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_z *pElements[BLOCKS_COUNT_ORIGIN];

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        pElements[uIndex] = (f64_z*)poolOrigin.Allocate();
        *pElements[uIndex] = scast_z(uIndex, f64_z);
    }

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        f64_z *pElementDestination = (f64_z*)poolDestination.GetpBlock(uIndex);
        BOOST_CHECK_EQUAL( *pElements[uIndex], *pElementDestination );
    }

    BOOST_CHECK_EQUAL( poolOrigin.GetAllocatedBytes(), poolDestination.GetAllocatedBytes() );
}


/// <summary>
/// Case when origin allocator has less blocks than destination and one allocated block.
/// After copy it verifies that destination has origin blocks plus remaining free space.
/// </summary>
ZTEST_CASE( CopyTo_CheckIfCorrectlyCopiedWhenOriginAllocatorHasLessBlocksAndOneAllocatedBlock_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT_ORIGIN = 4;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCKS_COUNT_DESTINATION = 6;
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    const f64_z TEST_VALUE = 5;
    const puint_z EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT_DESTINATION - 1;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    PoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_z *pElement = (f64_z*)poolOrigin.Allocate();
    *pElement = TEST_VALUE;

    poolOrigin.CopyTo(poolDestination);

    // [Verification]
    puint_z uAllocations = 0;

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
    {
        if( null_z != poolDestination.Allocate() ) 
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );

    f64_z *pElementDestination = (f64_z*)poolDestination.GetpBlock(0);
    BOOST_CHECK_EQUAL( *pElementDestination, TEST_VALUE );
}


/// <summary>
/// When copied a full origin and allocates more elements in destination it checks if destination has expected contents.
/// </summary>
ZTEST_CASE( CopyTo_WhenCopiedAFullOriginAndAllocatesMoreElementsInDestinationChecksIfDestinationHasExpectedContents_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT_ORIGIN = 4;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCKS_COUNT_DESTINATION = 6;
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    PoolAllocatorWhiteBox poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    f64_z *pElements[BLOCKS_COUNT_DESTINATION];

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_ORIGIN; uIndex++ )
    {
        pElements[uIndex] = (f64_z*)poolOrigin.Allocate();
        *pElements[uIndex] = scast_z(uIndex, f64_z);
    }

    poolOrigin.CopyTo(poolDestination);

    for(puint_z uIndex = BLOCKS_COUNT_ORIGIN; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
    {
        pElements[uIndex] = (f64_z*)poolDestination.Allocate();
        *pElements[uIndex] = scast_z(uIndex, f64_z);
    }

    // [Verification]

    // Check if no more allocates area available
    BOOST_CHECK( poolDestination.Allocate() == null_z );

    // Check contents
    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++ )
    {
        f64_z *pElementDestination = (f64_z*)poolDestination.GetpBlock(uIndex);
        BOOST_CHECK_EQUAL( *pElements[uIndex], *pElementDestination );
    }
}


/// <summary>
/// When copied an empty origin to a full destination with different blocks count check if destination has all free space available.
/// </summary>
ZTEST_CASE( CopyTo_WhenCopiedAnEmptyOriginToAFullDestinationWithDifferentBlocksCountCheckIfDestinationHasAllFreeSpaceAvailable_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT_ORIGIN = 4;
    const puint_z POOL_SIZE_ORIGIN = BLOCKS_COUNT_ORIGIN * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z BLOCKS_COUNT_DESTINATION = 6;
    const puint_z POOL_SIZE_DESTINATION = BLOCKS_COUNT_DESTINATION * BLOCK_SIZE;
    const puint_z EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT_DESTINATION;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE_ORIGIN, BLOCK_SIZE, ALIGNMENT);
    PoolAllocator poolDestination(POOL_SIZE_DESTINATION, BLOCK_SIZE, ALIGNMENT);

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION; uIndex++)
        poolDestination.Allocate();

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    puint_z uAllocations = 0;

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT_DESTINATION + 1; uIndex++ )
    {
        if(null_z != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied an empty origin to a destination with the same blocks count check if destination has all free space available.
/// </summary>
ZTEST_CASE( CopyTo_WhenCopiedAnEmptyOriginToADestinationWithTheSameBlocksCountCheckIfDestinationHasAllFreeSpaceAvailable_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    PoolAllocator poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    puint_z uAllocations = 0;

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT + 1; uIndex++ )
    {
        if(null_z != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied a full origin to a destination with the same blocks count check if destination has no free space available.
/// </summary>
ZTEST_CASE( CopyTo_WhenCopiedAFullOriginToADestinationWithTheSameBlocksCountCheckIfDestinationHasNoFreeSpaceAvailable_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const puint_z EXPECTED_NUMBER_OF_ALLOCATIONS = 0;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    PoolAllocator poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++)
        poolOrigin.Allocate();

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    puint_z uAllocations = 0;
    
    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        if(null_z != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}


/// <summary>
/// When copied an origin with one allocated block to a destination check if destination has expected contents and available space.
/// </summary>
ZTEST_CASE( CopyTo_WhenCopiedAnOriginWithOneAllocatedBlockToADestinationCheckIfDestinationHasExpectedContentsAndAvailableSpace_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(f64_z);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const Alignment ALIGNMENT(BLOCK_SIZE);

    const f64_z TEST_VALUE = 10;
    const puint_z EXPECTED_NUMBER_OF_ALLOCATIONS = BLOCKS_COUNT - 1;

    // [Execution]
    PoolAllocator poolOrigin(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);
    PoolAllocatorWhiteBox poolDestination(POOL_SIZE, BLOCK_SIZE, ALIGNMENT);

    f64_z *pBuffer = (f64_z*)poolOrigin.Allocate();
    *pBuffer = TEST_VALUE;

    poolOrigin.CopyTo(poolDestination);

    // [Verification]

    pBuffer = (f64_z*)poolDestination.GetpFirst();

    BOOST_CHECK_EQUAL( *pBuffer, TEST_VALUE );

    puint_z uAllocations = 0;
    
    for(puint_z uIndex = 0; uIndex < BLOCKS_COUNT; uIndex++ )
    {
        if(null_z != poolDestination.Allocate() )
            uAllocations++;
    }

    BOOST_CHECK_EQUAL( uAllocations, EXPECTED_NUMBER_OF_ALLOCATIONS );
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
ZTEST_CASE( Reallocate1_PoolContentIsCorrectlyCopied_Test )
{
    // [Preparation]
    const bool IS_SAME_DATA = true;
    const puint_z BLOCK_SIZE = sizeof(unsigned int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(unsigned int)));
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        *(unsigned int*)allocator.Allocate() = scast_z(i, unsigned int);
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1));
 
    // [Verification]
    bool bIsSameData = true;
    
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        bIsSameData = bIsSameData && *((unsigned int*)allocator.GetPointer() + i) == i;

    BOOST_CHECK_EQUAL(bIsSameData, IS_SAME_DATA);
}

/// <summary>
/// Checks that the size of the pool, the total size and the allocated bytes are correct after the reallocation.
/// </summary>
ZTEST_CASE( Reallocate1_SizesAreCorrectAfterReallocation_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    
    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    for(puint_z i = 0; i < BLOCKS_COUNT - 1; ++i)
        *(int*)allocator.Allocate() = scast_z(i, unsigned int);

    const puint_z EXPECTED_POOL_SIZE       = (BLOCKS_COUNT + 1) * BLOCK_SIZE;
    const puint_z EXPECTED_TOTAL_SIZE      = EXPECTED_POOL_SIZE + sizeof(void**) * (BLOCKS_COUNT + 1);
    const puint_z EXPECTED_ALLOCATED_BYTES = allocator.GetAllocatedBytes();
    
    // [Execution]
    allocator.Reallocate(EXPECTED_POOL_SIZE);
 
    // [Verification]
    puint_z uTotalSize      = allocator.GetTotalSize();
    puint_z uPoolSize       = allocator.GetPoolSize();
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uTotalSize,      EXPECTED_TOTAL_SIZE);
    BOOST_CHECK_EQUAL(uPoolSize,       EXPECTED_POOL_SIZE);
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
ZTEST_CASE( Reallocate1_AllocationsCanBeDoneAfterReallocatingFullAllocator_Test )
{
    // [Preparation]
    void* NULL_POINTER = null_z;
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        *(int*)allocator.Allocate() = scast_z(i, unsigned int);
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1));
 
    // [Verification]
    void* pAllocation = allocator.Allocate();
    
    BOOST_CHECK_NE(pAllocation, NULL_POINTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size is not greater than the current pool size.
/// </summary>
ZTEST_CASE( Reallocate1_AssertionFailsWhenInputSizeIsNotGreaterThanCurrentPoolSize_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    PoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
ZTEST_CASE( Reallocate2_PoolContentIsCorrectlyCopied_Test )
{
    // [Preparation]
    const bool IS_SAME_DATA = true;
    const puint_z BLOCK_SIZE = sizeof(unsigned int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const puint_z NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(unsigned int)));
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        *(unsigned int*)allocator.Allocate() = scast_z(i, unsigned int);
    
    // [Execution]
    allocator.Reallocate(NEW_POOL_SIZE, pInputBuffer);
 
    // [Verification]
    bool bIsSameData = true;
    
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        bIsSameData = bIsSameData && *((unsigned int*)allocator.GetPointer() + i) == i;

    BOOST_CHECK_EQUAL(bIsSameData, IS_SAME_DATA);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that the size of the pool, the total size and the allocated bytes are correct after the reallocation.
/// </summary>
ZTEST_CASE( Reallocate2_SizesAreCorrectAfterReallocation_Test )
{
    // [Preparation]
    const puint_z BLOCK_SIZE = sizeof(unsigned int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const puint_z NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(unsigned int)));
    for(puint_z i = 0; i < BLOCKS_COUNT - 1; ++i)
        *(unsigned int*)allocator.Allocate() = scast_z(i, unsigned int);

    const puint_z EXPECTED_POOL_SIZE       = (BLOCKS_COUNT + 1) * BLOCK_SIZE;
    const puint_z EXPECTED_TOTAL_SIZE      = EXPECTED_POOL_SIZE + sizeof(void**) * (BLOCKS_COUNT + 1);
    const puint_z EXPECTED_ALLOCATED_BYTES = allocator.GetAllocatedBytes();
    
    // [Execution]
    allocator.Reallocate(EXPECTED_POOL_SIZE, pInputBuffer);
 
    // [Verification]
    puint_z uTotalSize      = allocator.GetTotalSize();
    puint_z uPoolSize       = allocator.GetPoolSize();
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uTotalSize,      EXPECTED_TOTAL_SIZE);
    BOOST_CHECK_EQUAL(uPoolSize,       EXPECTED_POOL_SIZE);
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that the data inside the pool is correctly copied.
/// </summary>
ZTEST_CASE( Reallocate2_AllocationsCanBeDoneAfterReallocatingFullAllocator_Test )
{
    // [Preparation]
    void* NULL_POINTER = null_z;
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const puint_z NEW_POOL_SIZE = POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    PoolAllocator allocator(POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    for(puint_z i = 0; i < BLOCKS_COUNT; ++i)
        *(int*)allocator.Allocate() = scast_z(i, unsigned int);
    
    // [Execution]
    allocator.Reallocate(BLOCK_SIZE * (BLOCKS_COUNT + 1), pInputBuffer);
 
    // [Verification]
    void* pAllocation = allocator.Allocate();
    
    BOOST_CHECK_NE(pAllocation, NULL_POINTER);

    // [Cleaning]
    operator delete(pInputBuffer);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input size is not greater than the current pool size.
/// </summary>
ZTEST_CASE( Reallocate2_AssertionFailsWhenInputSizeIsNotGreaterThanCurrentPoolSize_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const puint_z NEW_POOL_SIZE = CURRENT_POOL_SIZE + BLOCK_SIZE;

    void* pInputBuffer = operator new(NEW_POOL_SIZE);

    PoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE, pInputBuffer);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pInputBuffer);
}

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE( Reallocate2_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const puint_z BLOCK_SIZE = sizeof(int);
    const puint_z BLOCKS_COUNT = 4;
    const puint_z CURRENT_POOL_SIZE = BLOCKS_COUNT * BLOCK_SIZE;
    const void* NULL_POINTER = null_z;
    PoolAllocator allocator(CURRENT_POOL_SIZE, BLOCK_SIZE, Alignment(alignof_z(int)));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Reallocate(CURRENT_POOL_SIZE, NULL_POINTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
 
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif


// End - Test Suite: PoolAllocator
ZTEST_SUITE_END()
