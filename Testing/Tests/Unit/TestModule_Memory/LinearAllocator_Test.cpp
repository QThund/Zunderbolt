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

#include "ZMemory/LinearAllocator.h"

#include "ZCommon/Exceptions/AssertException.h"
#include "ZCommon/AllocationOperators.h"


ZTEST_SUITE_BEGIN( LinearAllocator_TestSuite )

/// <summary>
/// Checks that the size of the constructed allocator equals the size that was used in the constructor.
/// </summary>
ZTEST_CASE ( Constructor1_SizeOfAllocatorIsEqualToCommonSizeUsedAsParameter_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4;
    const Alignment INPUT_ALIGNMENT(4);

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    puint_z uSize = allocator.GetSize();
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

/// <summary>
/// Checks that the buffer is properly created when using a common size and alignment.
/// </summary>
ZTEST_CASE ( Constructor1_ValidBufferIsCreatedWhenUsingCommonSizeAndAlignment_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4;
    const Alignment INPUT_ALIGNMENT(4);
    const void* NULL_BUFFER = null_z;

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    void* pBuffer = allocator.GetPointer();
    puint_z uAdjustment = INPUT_ALIGNMENT - ((puint_z)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_NE(pBuffer, NULL_BUFFER);
    BOOST_CHECK_EQUAL(uAdjustment, INPUT_ALIGNMENT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when zero is passed as size.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        LinearAllocator allocator(ZERO_SIZE, INPUT_ALIGNMENT);
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
/// Checks that the size of the constructed allocator equals the size that was used in the constructor.
/// </summary>
ZTEST_CASE ( Constructor2_SizeOfAllocatorIsEqualToCommonSizeUsedAsParameter_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, pInputBuffer);

    // [Verification]
    puint_z uSize = allocator.GetSize();
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);

    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the buffer is properly created when using a common size and alignment.
/// </summary>
ZTEST_CASE ( Constructor2_ValidBufferIsCreatedWhenUsingCommonSizeAndAlignment_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_BUFFER = null_z;
    void* pInputBuffer = operator new(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, pInputBuffer);

    // [Verification]
    void* pBuffer = allocator.GetPointer();
    puint_z uAdjustment = INPUT_ALIGNMENT - ((puint_z)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_NE(pBuffer, NULL_BUFFER);
    BOOST_CHECK_EQUAL(uAdjustment, INPUT_ALIGNMENT);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the start position of the buffer is not adjusted to any alignment.
/// </summary>
ZTEST_CASE ( Constructor2_BufferIsNotAdjustedToAlignment_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 8U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(EXPECTED_SIZE, INPUT_ALIGNMENT);
    void* INPUT_ADDRESS = (void*)((puint_z)pInputBuffer + 2U);
    void* EXPECTED_ADDRESS = (void*)((puint_z)pInputBuffer + 4U); // The start address should be moved to this address so it is aligned to 4 bytes

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, INPUT_ADDRESS);

    // [Verification]
    void* pBuffer = allocator.GetPointer();
    puint_z uAdjustment = INPUT_ALIGNMENT - ((puint_z)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_NE(pBuffer, EXPECTED_ADDRESS);
    BOOST_CHECK_NE(uAdjustment, INPUT_ALIGNMENT);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when zero is passed as size.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(4U, INPUT_ALIGNMENT);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        LinearAllocator allocator(ZERO_SIZE, pInputBuffer, INPUT_ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that an assertion fails when the pointer to the external buffer is null.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = null_z;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        LinearAllocator allocator(COMMON_SIZE, pInputBuffer);
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
/// Checks that the size of the constructed allocator equals the size that was used in the constructor.
/// </summary>
ZTEST_CASE ( Constructor3_SizeOfAllocatorIsEqualToCommonSizeUsedAsParameter_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, pInputBuffer, INPUT_ALIGNMENT);

    // [Verification]
    puint_z uSize = allocator.GetSize();
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);

    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the buffer is properly created when using a common size and alignment.
/// </summary>
ZTEST_CASE ( Constructor3_ValidBufferIsCreatedWhenUsingCommonSizeAndAlignment_Test )
{
    // [Preparation]
    const puint_z EXPECTED_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_BUFFER = null_z;
    void* pInputBuffer = operator new(EXPECTED_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    LinearAllocator allocator(EXPECTED_SIZE, pInputBuffer, INPUT_ALIGNMENT);

    // [Verification]
    void* pBuffer = allocator.GetPointer();
    puint_z uAdjustment = INPUT_ALIGNMENT - ((puint_z)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_NE(pBuffer, NULL_BUFFER);
    BOOST_CHECK_EQUAL(uAdjustment, INPUT_ALIGNMENT);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the start position of the buffer is adjusted to the alignment.
/// </summary>
ZTEST_CASE ( Constructor3_BufferIsAdjustedToAlignment_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 8U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(8U, INPUT_ALIGNMENT);
    void* INPUT_ADDRESS = (void*)((puint_z)pInputBuffer + 2U);
    void* EXPECTED_ADDRESS = (void*)((puint_z)pInputBuffer + 4U); // The start address should be moved to this address so it is aligned to 4 bytes

    // [Execution]
    LinearAllocator allocator(INPUT_SIZE, INPUT_ADDRESS, INPUT_ALIGNMENT);

    // [Verification]
    void* pBuffer = allocator.GetPointer();
    puint_z uAdjustment = INPUT_ALIGNMENT - ((puint_z)pBuffer & (INPUT_ALIGNMENT - 1U));

    BOOST_CHECK_EQUAL(pBuffer, EXPECTED_ADDRESS);
    BOOST_CHECK_EQUAL(uAdjustment, INPUT_ALIGNMENT);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that the size is affected by the alignment adjustment (memory loss).
/// </summary>
ZTEST_CASE ( Constructor3_SizeIsAffectedByAlignmentAdjustment_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 8U - 2U; // The input address starts 2 positions later
    const puint_z EXPECTED_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(8U, INPUT_ALIGNMENT);
    void* INPUT_ADDRESS = (void*)((puint_z)pInputBuffer + 2U);

    // [Execution]
    LinearAllocator allocator(INPUT_SIZE, INPUT_ADDRESS, INPUT_ALIGNMENT);

    // [Verification]
    puint_z uSize = allocator.GetSize();

    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
    
    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when zero is passed as size.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = operator new(4U, INPUT_ALIGNMENT);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        LinearAllocator allocator(ZERO_SIZE, pInputBuffer, INPUT_ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pInputBuffer, INPUT_ALIGNMENT);
}

/// <summary>
/// Checks that an assertion fails when the pointer to the external buffer is null.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    void* pInputBuffer = null_z;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        LinearAllocator allocator(COMMON_SIZE, pInputBuffer, INPUT_ALIGNMENT);
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
/// Checks that a valid memory address is returned when using a common input size and an empty allocator.
/// </summary>
ZTEST_CASE ( Allocate1_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_z;
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and a non-empty allocator.
/// </summary>
ZTEST_CASE ( Allocate1_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsNotEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_z;
    LinearAllocator allocator(8U, INPUT_ALIGNMENT);
    allocator.Allocate(INPUT_SIZE);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that the allocated bytes increase on every allocation.
/// </summary>
ZTEST_CASE ( Allocate1_AllocatedBytesGrow_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    allocator.Allocate(INPUT_SIZE);

    // [Verification]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, INPUT_SIZE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when zero is passed as size.
/// </summary>
ZTEST_CASE ( Allocate1_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    const bool ASSERTION_FAILED = true;
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Allocate(ZERO_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the allocator is full.
/// </summary>
ZTEST_CASE ( Allocate1_AssertionFailsWhenTheAllocatorIsFull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const bool ASSERTION_FAILED = true;
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    allocator.Allocate(4U);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Allocate(COMMON_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an assertion fails when the allocator is full.
/// </summary>
ZTEST_CASE ( Allocate1_ReturnsNullWhenTheAllocatorIsFull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const void* NULL_POINTER = null_z;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    allocator.Allocate(4U);

    // [Execution]
    void* pNullAllocation = allocator.Allocate(COMMON_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(pNullAllocation, NULL_POINTER);
}

#endif

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and an empty allocator.
/// </summary>
ZTEST_CASE ( Allocate2_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_z;
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that a valid memory address is returned when using a common input size and a non-empty allocator.
/// </summary>
ZTEST_CASE ( Allocate2_ReturnsValidAddressWhenUsingCommonSizeAndAllocatorIsNotEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const void* NULL_POINTER = null_z;
    LinearAllocator allocator(8U, INPUT_ALIGNMENT);
    allocator.Allocate(INPUT_SIZE);

    // [Execution]
    void* pAllocatedMemory = allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_NE(pAllocatedMemory, NULL_POINTER);
}

/// <summary>
/// Checks that the allocated bytes increase on every allocation.
/// </summary>
ZTEST_CASE ( Allocate2_AllocatedBytesGrow_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Execution]
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, INPUT_SIZE);
}

/// <summary>
/// Checks that alignment adjustments count as allocated space.
/// </summary>
ZTEST_CASE ( Allocate2_AlignmentAdjustmentAffectsTheAllocatedBytes_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(8U, Alignment(4U));
    allocator.Allocate(2U);

    const puint_z EXPECTED_ALLOCATED_BYTES = 8U;

    // [Execution]
    allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when zero is passed as size.
/// </summary>
ZTEST_CASE ( Allocate2_AssertionFailsWhenSizeEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    const bool ASSERTION_FAILED = true;
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Allocate(ZERO_SIZE, INPUT_ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the allocator is full.
/// </summary>
ZTEST_CASE ( Allocate2_AssertionFailsWhenTheAllocatorIsFull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    const bool ASSERTION_FAILED = true;
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    allocator.Allocate(4U);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Allocate(COMMON_SIZE, INPUT_ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the block to allocate does not fit in the available free space due to an alignment adjustment.
/// </summary>
ZTEST_CASE ( Allocate2_AssertionFailsWhenTheBlockDoesNotFitInTheBufferDueToAlignmentAdjustment_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 6U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(8U, Alignment(4U));
    allocator.Allocate(2U);

    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.Allocate(INPUT_SIZE, INPUT_ALIGNMENT); // 2 + 6 should fit into a 8 bytes buffer, but due to alignment adjustment, they do not
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an assertion fails when the allocator is full.
/// </summary>
ZTEST_CASE ( Allocate2_ReturnsNullWhenTheAllocatorIsFull_Test )
{
    // [Preparation]
    const puint_z COMMON_SIZE = 4U;
    const void* NULL_POINTER = null_z;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    allocator.Allocate(4U);

    // [Execution]
    void* pNullAllocation = allocator.Allocate(COMMON_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(pNullAllocation, NULL_POINTER);
}

#endif

/// <summary>
/// Checks that nothing changes when the allocator was already empty.
/// </summary>
ZTEST_CASE ( Clear_NothingChangesWhenAllocatorIsEmpty_Test )
{
    // [Preparation]
    LinearAllocator allocator(4U, Alignment(4U));
    const puint_z EXPECTED_ALLOCATED_BYTES = allocator.GetAllocatedBytes();

    // [Execution]
    allocator.Clear();

    // [Verification]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that all the memory blocks are deallocated.
/// </summary>
ZTEST_CASE ( Clear_EntireAllocatorIsEmptied_Test )
{
    // [Preparation]
    LinearAllocator allocator(8U, Alignment(4U));
    allocator.Allocate(4U);
    allocator.Allocate(4U);
    const puint_z EXPECTED_ALLOCATED_BYTES = 0;

    // [Execution]
    allocator.Clear();

    // [Verification]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that new allocations start at the beginning of the internal buffer after it has been cleared.
/// </summary>
ZTEST_CASE ( Clear_AllocationsStartAtBeginningOfBufferAfterClearing_Test )
{
    // [Preparation]
    LinearAllocator allocator(8U, Alignment(4U));
    const void* EXPECTED_FIRST_POSITION = allocator.Allocate(4U);
    allocator.Allocate(4U);

    // [Execution]
    allocator.Clear();
    
    // [Verification]
    void* pAllocationPosition = allocator.Allocate(4U);
    BOOST_CHECK_EQUAL(pAllocationPosition, EXPECTED_FIRST_POSITION);
}

/// <summary>
/// Checks that allocators of the same size are correctly copied.
/// </summary>
ZTEST_CASE ( CopyTo_AllocatorsOfSameSizeAreCorrectlyCopied_Test )
{

    // [Preparation]
    const bool ARE_EQUAL = true;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    LinearAllocator destinationAllocator(12U, Alignment(4U));

    for(int i = 1; i < 4; ++i)
        *scast_z(sourceAllocator.Allocate(4U), i32_z*) = i;

    // [Execution]
    sourceAllocator.CopyTo(destinationAllocator);
    
    // [Verification]
    int* pBufferSource = scast_z(sourceAllocator.GetPointer(), int*);
    int* pBufferDestination = scast_z(destinationAllocator.GetPointer(), int*);

    bool bAreEqual = true;

    for(int i = 1; i < 4; ++i, ++pBufferSource, ++pBufferDestination)
        bAreEqual = bAreEqual && *pBufferSource == *pBufferDestination;

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that it's possible to allocate new memory blocks in the destination allocator after the copy.
/// </summary>
ZTEST_CASE ( CopyTo_ItIsPossibleToAllocateNewBlocksInDestinationAfterCopy_Test )
{

    // [Preparation]
    const void* NULL_POINTER = null_z;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    LinearAllocator destinationAllocator(16U, Alignment(4U));

    for(int i = 1; i < 4; ++i)
        *scast_z(sourceAllocator.Allocate(4U), i32_z*) = i;

    // [Execution]
    sourceAllocator.CopyTo(destinationAllocator);
    void* pAllocationAfterCopy = destinationAllocator.Allocate(4U);
    
    // [Verification]
    BOOST_CHECK_NE(pAllocationAfterCopy, NULL_POINTER);
}

/// <summary>
/// Checks that empty allocators are correctly copied.
/// </summary>
ZTEST_CASE ( CopyTo_EmptyAllocatorsAreCorrectlyCopied_Test )
{
    // [Preparation]
    const puint_z EXPECTED_ALLOCATED_BYTES = 0;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    LinearAllocator destinationAllocator(12U, Alignment(4U));
    
    // [Execution]
    sourceAllocator.CopyTo(destinationAllocator);

    // [Verification]
    puint_z uAllocatedBytes = destinationAllocator.GetAllocatedBytes();
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

/// <summary>
/// Checks that an allocator can be copied to a non-empty allocator properly.
/// </summary>
ZTEST_CASE ( CopyTo_CopyingToNonEmptyAllocatorIsPerformedProperly_Test )
{

    // [Preparation]
    const bool ARE_EQUAL = true;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    LinearAllocator destinationAllocator(16U, Alignment(4U));

    for(int i = 1; i < 4; ++i)
        *scast_z(sourceAllocator.Allocate(4U), i32_z*) = i;

    const puint_z EXPECTED_ALLOCATED_BYTES = sourceAllocator.GetAllocatedBytes();

    for(int i = 5; i < 9; ++i)
        *scast_z(destinationAllocator.Allocate(4U), i32_z*) = i;

    // [Execution]
    sourceAllocator.CopyTo(destinationAllocator);
    
    // [Verification]
    int* pBufferSource = scast_z(sourceAllocator.GetPointer(), int*);
    int* pBufferDestination = scast_z(destinationAllocator.GetPointer(), int*);

    bool bAreEqual = true;

    for(int i = 1; i < 4; ++i, ++pBufferSource, ++pBufferDestination)
        bAreEqual = bAreEqual && *pBufferSource == *pBufferDestination;

    puint_z uDestinationAllocatedBytes = destinationAllocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
    BOOST_CHECK_EQUAL(uDestinationAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when allocators have different alignment.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenAllocatorsHaveDifferentAlignment_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    LinearAllocator sourceAllocator(12U, Alignment(2U));
    LinearAllocator destinationAllocator(12U, Alignment(4U));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.CopyTo(destinationAllocator);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input allocator is smaller than resident allocator.
/// </summary>
ZTEST_CASE ( CopyTo_AssertionFailsWhenInputAllocatorIsSmaller_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    sourceAllocator.Allocate(5U);
    LinearAllocator destinationAllocator(4U, Alignment(4U));
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.CopyTo(destinationAllocator);
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
/// Checks that the contents of the buffer are the same after the reallocation.
/// </summary>
ZTEST_CASE ( Reallocate1_ContentsAreTheSameAfterReallocation_Test )
{

    // [Preparation]
    const bool ARE_EQUAL = true;
    LinearAllocator sourceAllocator(12U, Alignment(4U));

    for(int i = 1; i < 4; ++i)
        *scast_z(sourceAllocator.Allocate(4U), i32_z*) = i;

    const puint_z NEW_SIZE = 16U;
    const puint_z EXPECTED_ALLOCATED_BYTES = 12U;

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE);
    
    // [Verification]
    int* pBufferSource = scast_z(sourceAllocator.GetPointer(), int*);

    bool bAreEqual = true;

    for(int i = 1; i < 4; ++i, ++pBufferSource)
        bAreEqual = bAreEqual && *pBufferSource == i;

    puint_z uAllocatedBytes = sourceAllocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that a new buffer has been created internally.
/// </summary>
ZTEST_CASE ( Reallocate1_NewBufferHasBeenCreated_Test )
{
    // [Preparation]
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    const void* ORIGINAL_BUFFER = sourceAllocator.GetPointer();

    const puint_z NEW_SIZE = 16U;

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE);
    
    // [Verification]
    void* pNewBuffer = sourceAllocator.GetPointer();

    BOOST_CHECK_NE(pNewBuffer, ORIGINAL_BUFFER);
}

/// <summary>
/// Checks that a new buffer has expected size.
/// </summary>
ZTEST_CASE ( Reallocate1_NewBufferHasExpectedSize_Test )
{
    // [Preparation]
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    const puint_z NEW_SIZE = 16U;

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE);
    
    // [Verification]
    puint_z uNewSize = sourceAllocator.GetSize();

    BOOST_CHECK_EQUAL(uNewSize, NEW_SIZE);
}

/// <summary>
/// Checks that it is possible to allocate new memory blocks after the reallocation.
/// </summary>
ZTEST_CASE ( Reallocate1_ItIsPossibleToAllocateNewBlocksAfterReallocation_Test )
{

    // [Preparation]
    const void* NULL_POINTER = null_z;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    sourceAllocator.Allocate(4U);

    const puint_z NEW_SIZE = 16U;

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE);

    // [Verification]
    void* pAllocationAddress = sourceAllocator.Allocate(4U);
    BOOST_CHECK_NE(pAllocationAddress, NULL_POINTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the allocator uses an external buffer.
/// </summary>
ZTEST_CASE ( Reallocate1_AssertionFailsWhenAllocatorUsesExternalBuffer_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    
    void* pExternalBuffer = ::operator new(12U, Alignment(4U));
    LinearAllocator sourceAllocator(12U, pExternalBuffer, Alignment(4U));

    const puint_z NEW_SIZE = 16U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    
    // [Cleaning]
    operator delete(pExternalBuffer, Alignment(4U));
}

/// <summary>
/// Checks that an assertion fails when the input size is not bigger than the size of the current buffer.
/// </summary>
ZTEST_CASE ( Reallocate1_AssertionFailsWhenNewSizeIsNotBigger_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    const puint_z NEW_SIZE = 12U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing changes if the input size is not bigger than the size of the current buffer.
/// </summary>
ZTEST_CASE ( Reallocate1_NothingHappensWhenInputSizeIsNotBigger_Test )
{
    // [Preparation]
    LinearAllocator sourceAllocator(12U, Alignment(4U));
    const void* EXPECTED_BUFFER = sourceAllocator.GetPointer();
    const puint_z EXPECTED_SIZE = sourceAllocator.GetSize();
    const puint_z NEW_SIZE = 8U;

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE);

    // [Verification]
    puint_z uSize = sourceAllocator.GetSize();
    void* pBuffer = sourceAllocator.GetPointer();
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
    BOOST_CHECK_EQUAL(pBuffer, EXPECTED_BUFFER);
}

#endif

/// <summary>
/// Checks that the contents of the buffer are the same after the reallocation.
/// </summary>
ZTEST_CASE ( Reallocate2_ContentsAreTheSameAfterReallocation_Test )
{

    // [Preparation]
    const bool ARE_EQUAL = true;
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);

    for(int i = 1; i < 4; ++i)
        *scast_z(sourceAllocator.Allocate(4U), i32_z*) = i;

    const puint_z NEW_SIZE = 16U;
    const puint_z EXPECTED_ALLOCATED_BYTES = 12U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);
    
    // [Verification]
    int* pBufferSource = scast_z(sourceAllocator.GetPointer(), int*);

    bool bAreEqual = true;

    for(int i = 1; i < 4; ++i, ++pBufferSource)
        bAreEqual = bAreEqual && *pBufferSource == i;

    puint_z uAllocatedBytes = sourceAllocator.GetAllocatedBytes();

    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_ALLOCATED_BYTES);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that a new buffer has been stored.
/// </summary>
ZTEST_CASE ( Reallocate2_NewBufferHasBeenStored_Test )
{
    // [Preparation]
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);
    const void* ORIGINAL_BUFFER = sourceAllocator.GetPointer();

    const puint_z NEW_SIZE = 16U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);
    
    // [Verification]
    void* pBuffer = sourceAllocator.GetPointer();
    BOOST_CHECK_EQUAL(pBuffer, pNewBuffer);
    BOOST_CHECK_NE(pBuffer, ORIGINAL_BUFFER);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that a new buffer has expected size.
/// </summary>
ZTEST_CASE ( Reallocate2_NewBufferHasExpectedSize_Test )
{
    // [Preparation]
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);
    const puint_z NEW_SIZE = 16U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);
    
    // [Verification]
    puint_z uNewSize = sourceAllocator.GetSize();
    BOOST_CHECK_EQUAL(uNewSize, NEW_SIZE);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that it is possible to allocate new memory blocks after the reallocation.
/// </summary>
ZTEST_CASE ( Reallocate2_ItIsPossibleToAllocateNewBlocksAfterReallocation_Test )
{

    // [Preparation]
    const void* NULL_POINTER = null_z;
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);
    sourceAllocator.Allocate(4U);

    const puint_z NEW_SIZE = 16U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);

    // [Verification]
    void* pAllocationAddress = sourceAllocator.Allocate(4U);
    BOOST_CHECK_NE(pAllocationAddress, NULL_POINTER);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the allocator uses an internal buffer.
/// </summary>
ZTEST_CASE ( Reallocate2_AssertionFailsWhenAllocatorUsesInternalBuffer_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const Alignment ALIGNMENT(4U);
    LinearAllocator sourceAllocator(12U, ALIGNMENT);
    const puint_z NEW_SIZE = 16U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    
    // [Cleaning]
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that an assertion fails when the input size is not bigger than the size of the current buffer.
/// </summary>
ZTEST_CASE ( Reallocate2_AssertionFailsWhenNewSizeIsNotBigger_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);

    const puint_z NEW_SIZE = 12U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that an assertion fails when it is not possible to reallocate the buffer due to the alignment adjustment increases the required size.
/// </summary>
ZTEST_CASE ( Reallocate2_AssertionFailsWhenItIsNotPossibleToReallocateDueToAlignmentAdjustment_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);

    const puint_z NEW_SIZE = 14U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);
    void* pNotAlignedBuffer = (void*)((puint_z)pNewBuffer + 2U);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE, pNotAlignedBuffer);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);

    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

/// <summary>
/// Checks that an assertion fails when the input buffer is null.
/// </summary>
ZTEST_CASE ( Reallocate2_AssertionFailsWhenInputBufferIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);

    const puint_z NEW_SIZE = 12U;
    void* NULL_BUFFER = null_z;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        sourceAllocator.Reallocate(NEW_SIZE, NULL_BUFFER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing changes if the input size is not bigger than the size of the current buffer.
/// </summary>
ZTEST_CASE ( Reallocate2_NothingHappensWhenInputSizeIsNotBigger_Test )
{
    // [Preparation]
    const Alignment ALIGNMENT(4U);
    void* pExternalBuffer = ::operator new(12U, ALIGNMENT);
    LinearAllocator sourceAllocator(12U, pExternalBuffer, ALIGNMENT);
    const void* EXPECTED_BUFFER = sourceAllocator.GetPointer();
    const puint_z EXPECTED_SIZE = sourceAllocator.GetSize();
    const puint_z NEW_SIZE = 8U;
    void* pNewBuffer = ::operator new(NEW_SIZE, ALIGNMENT);

    // [Execution]
    sourceAllocator.Reallocate(NEW_SIZE, pNewBuffer);

    // [Verification]
    puint_z uSize = sourceAllocator.GetSize();
    void* pBuffer = sourceAllocator.GetPointer();
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
    BOOST_CHECK_EQUAL(pBuffer, EXPECTED_BUFFER);
    
    // [Cleaning]
    operator delete(pExternalBuffer, ALIGNMENT);
    operator delete(pNewBuffer, ALIGNMENT);
}

#endif

/// <summary>
/// Checks that it returns True when there is enough free space in the buffer.
/// </summary>
ZTEST_CASE ( CanAllocate1_ReturnsTrueWhenThereIsEnoughFreeSpace_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when there is not enough free space in the buffer.
/// </summary>
ZTEST_CASE ( CanAllocate1_ReturnsFalseWhenThereIsNotEnoughFreeSpace_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 8U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    allocator.Allocate(4U);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input size is zero.
/// </summary>
ZTEST_CASE ( CanAllocate1_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.CanAllocate(INPUT_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}


#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns True when input size is zero.
/// </summary>
ZTEST_CASE ( CanAllocate1_ReturnsTrueWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when there is enough free space in the buffer.
/// </summary>
ZTEST_CASE ( CanAllocate2_ReturnsTrueWhenThereIsEnoughFreeSpace_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when there is not enough free space in the buffer.
/// </summary>
ZTEST_CASE ( CanAllocate2_ReturnsFalseWhenThereIsNotEnoughFreeSpace_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 8U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    allocator.Allocate(4U);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when there is not enough free space in the buffer due to the alignment adjustment.
/// </summary>
ZTEST_CASE ( CanAllocate2_ReturnsFalseWhenThereIsNotEnoughFreeSpaceDueToAlignmentAdjustment_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 6U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(8U, INPUT_ALIGNMENT);
    allocator.Allocate(2U);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input size is zero.
/// </summary>
ZTEST_CASE ( CanAllocate2_AssertionFailsWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, INPUT_ALIGNMENT);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}


#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns True when input size is zero.
/// </summary>
ZTEST_CASE ( CanAllocate2_ReturnsTrueWhenInputSizeIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 0;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(4U, Alignment(4U));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = allocator.CanAllocate(INPUT_SIZE, INPUT_ALIGNMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns the expected value after performing some allocations.
/// </summary>
ZTEST_CASE ( GetAllocatedBytes_ReturnsExpectedValueAfterSomeAllocations_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 8U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    allocator.Allocate(3U);
    allocator.Allocate(4U);
    const puint_z EXPECTED_VALUE = 7U;

    // [Execution]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the allocator is empty.
/// </summary>
ZTEST_CASE ( GetAllocatedBytes_ReturnsZeroWhenAllocatorIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_SIZE = 4U;
    const Alignment INPUT_ALIGNMENT(4U);
    LinearAllocator allocator(INPUT_SIZE, INPUT_ALIGNMENT);
    const puint_z EXPECTED_VALUE = 0;

    // [Execution]
    puint_z uAllocatedBytes = allocator.GetAllocatedBytes();

    // [Verification]
    BOOST_CHECK_EQUAL(uAllocatedBytes, EXPECTED_VALUE);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetPointer_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetSize_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: LinearAllocator
ZTEST_SUITE_END()
