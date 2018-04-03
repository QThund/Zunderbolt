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

#include "ZContainers/ArrayFixed.h"
#include "ArrayFixedWhiteBox.h"
#include "ArrayFixedTestClass.h"
#include "ArrayElementMock.h"
#include "CallCounter.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::CallCounter;
using z::Test::ArrayFixedWhiteBox;
using z::Test::ArrayElementMock;
using z::Test::ArrayFixedTestClass;

i16_z ArrayElementMock::m_nNumberOfAllocatedObjects = 0;

ZTEST_SUITE_BEGIN( ArrayFixed_TestSuite )


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempting to create an array with zero elements.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenCreatingArrayWithZeroElements_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ZERO_ARRAY_COUNT = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]

    try
    {
        ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ZERO_ARRAY_COUNT, INITIAL_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if it's correctly initialized with initial value.
/// </summary>
ZTEST_CASE ( Constructor1_ChecksifIsCorrectlyInitializedWithInitialValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 10;
    const bool VALUES_ARE_AS_EXPECTED = true;

    // [Execution]
    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    u64_z uValue;
    bool bValuesAreAsExpected = true;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++ )
    {
        uValue = fixedArray[uIndex];
        bValuesAreAsExpected &= ( uValue == INITIAL_VALUE );
    }

    BOOST_CHECK_EQUAL( bValuesAreAsExpected, VALUES_ARE_AS_EXPECTED );
}

/// <summary>
/// Checks if the allocator has the expected size.
/// </summary>
ZTEST_CASE ( Constructor1_AllocatorHasExpectedSize_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 10;
    const puint_z SIZEOF_VALUE_TYPE = sizeof(u64_z);
    const puint_z ALLOCATOR_EXPECTED_SIZE = ARRAY_COUNT * SIZEOF_VALUE_TYPE;

    // [Execution]
    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    puint_z uAllocatorSize = fixedArray.GetAllocator()->GetPoolSize();

    BOOST_CHECK_EQUAL( uAllocatorSize, ALLOCATOR_EXPECTED_SIZE );
}

/// <summary>
/// Checks if the copy constructor of the array elements are called.
/// </summary>
ZTEST_CASE ( Constructor1_CopyConstructorOfArrayElementsAreCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const puint_z ARRAY_COUNT = 10;
    const puint_z EXPECTED_CALLS_TO_COPY_CONSTRUCTOR = ARRAY_COUNT;

    // [Execution]
    ArrayFixed<ArrayElementMock> fixedArray = ArrayFixed<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);

    // [Verification]
    puint_z uCallsToCopyConstructor = 0;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(((ArrayElementMock*)
            ((puint_z)fixedArray.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToCopyConstructor())
        {
            uCallsToCopyConstructor++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToCopyConstructor, EXPECTED_CALLS_TO_COPY_CONSTRUCTOR );
}

/// <summary>
/// Checks if the instance is correctly constructed when it receives a common array and its size.
/// </summary>
ZTEST_CASE ( Constructor2_ItIsCorrectlyConstructedFromCommonArray_Test )
{
    // [Preparation]
    const unsigned int ARRAY_SIZE = 3;
    const char SOURCE_ARRAY[ARRAY_SIZE] = {0, 1, 2};

    // [Execution]
    ArrayFixed<char> arArray(SOURCE_ARRAY, ARRAY_SIZE);

    // [Verification]
    puint_z uArraySize = arArray.GetCount();
    BOOST_CHECK_EQUAL(uArraySize, ARRAY_SIZE);

    for(unsigned int i = 0; i < arArray.GetCount(); ++i)
        BOOST_CHECK_EQUAL( arArray[i], SOURCE_ARRAY[i] );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when the input array is null.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenArrayIsNull_Test )
{
    // [Preparation]
    const int* NULL_ARRAY = null_z;
    const unsigned int NON_ZERO_SIZE = 3;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        ArrayFixed<int> arArray = ArrayFixed<int>(NULL_ARRAY, NON_ZERO_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <summary>
/// Checks than assertion fails when the input array size equals zero.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenCountIsZero_Test )
{
    // [Preparation]
    const int SOURCE_ARRAY[3] = {0, 1, 2};
    const unsigned int ZERO_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        ArrayFixed<int> arArray = ArrayFixed<int>(SOURCE_ARRAY, ZERO_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the copy constructor of the array elements are called for the second constructor.
/// </summary>
ZTEST_CASE ( Constructor3_CopyConstructorOfArrayElementsAreCalled_Test )
{
    // [Preparation]
    const puint_z ARRAY_COUNT = 10;
    const puint_z EXPECTED_CALLS_TO_COPY_CONSTRUCTOR = ARRAY_COUNT;
    ArrayFixed<CallCounter> fixedArrayOrigin = ArrayFixed<CallCounter>(ARRAY_COUNT, CallCounter());
    CallCounter::ResetCounters();

    // [Execution]
    ArrayFixed<CallCounter> fixedArrayDestination = ArrayFixed<CallCounter>(fixedArrayOrigin);

    // [Verification]
    unsigned int uCallsToCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL( uCallsToCopyConstructor, EXPECTED_CALLS_TO_COPY_CONSTRUCTOR );
}

/// <summary>
/// Checks if the constructor without parameters initializes correctly.
/// </summary>
ZTEST_CASE ( Constructor4_ConstructorWithoutParametersInitializesCorrectly_Test )
{
    // [Preparation]
    const puint_z END_POSITION_FORWARD = -2;
    const puint_z END_POSITION_BACKWARD = -1;

    // [Execution]
    ArrayFixedWhiteBox<u64_z> fixedArray;

    // [Verification]
    puint_z uFirst = fixedArray.GetFirstPosition();
    puint_z uLast  = fixedArray.GetLastPosition();

    BOOST_CHECK_EQUAL( uFirst, END_POSITION_BACKWARD );
    BOOST_CHECK_EQUAL( uLast, END_POSITION_FORWARD );
}

/// <summary>
/// Checks if the destructor is called for every element.
/// </summary>
ZTEST_CASE ( Destructor_TheDestructorOfEveryElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 5;
    {
        ArrayFixed<CallCounter> fixedArray(EXPECTED_CALLS, CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    } // Destructor called

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin array is equal to the destination array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginArraySizeIsEqualToDestinationArraySize_Test )
{
    // [Preparation]
    const u64_z ORIGIN_VALUES[] = {0, 1, 2, 3};
    ArrayFixed<u64_z> arOrigin = ArrayFixed<u64_z>(ORIGIN_VALUES, 4U);
    const u64_z DESTINATION_VALUES[] = {4, 5, 6, 7};
    ArrayFixed<u64_z> arDestination = ArrayFixed<u64_z>(DESTINATION_VALUES, 4U);

    // [Execution]
    arDestination = arOrigin;

    // [Verification]
    BOOST_CHECK(arDestination == arOrigin);
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin array is lower than the destination array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginArraySizeIsLowerThanDestinationArraySize_Test )
{
    // [Preparation]
    const u64_z ORIGIN_VALUES[] = {0, 1, 2};
    ArrayFixed<u64_z> arOrigin = ArrayFixed<u64_z>(ORIGIN_VALUES, 3U);
    const u64_z DESTINATION_VALUES[] = {4, 5, 6, 7};
    ArrayFixed<u64_z> arDestination = ArrayFixed<u64_z>(DESTINATION_VALUES, 4U);
    const u64_z EXPECTED_VALUES[] = {0, 1, 2, 7};
    ArrayFixed<u64_z> arExpectedValues = ArrayFixed<u64_z>(EXPECTED_VALUES, 4U);

    // [Execution]
    arDestination = arOrigin;

    // [Verification]
    BOOST_CHECK(arDestination == arExpectedValues);
}

/// <summary>
/// Checks if it calls to operator assignment of the array elements.
/// </summary>
ZTEST_CASE ( OperatorAssignment_OperatorAssignmentOfArrayElementsIsCalled_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const puint_z ARRAY_COUNT = 10;
    const puint_z EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT;

    ArrayFixed<ArrayElementMock> fixedArrayOrigin = ArrayFixed<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);
    ArrayFixed<ArrayElementMock> fixedArrayDestination = ArrayFixed<ArrayElementMock>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]
    puint_z uCallsToOperatorAssignment = 0;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(((ArrayElementMock*)
            ((puint_z)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );
}

/// <summary>
/// Checks if it calls operator assignment of elements as number of times as number of elements has the
/// origin array, when it's less than the destination array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_OriginSizeNumberOfCopiesAreDoneWhereIsLessThanDestinationSize_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const puint_z ARRAY_COUNT_ORIGIN = 5;
    const puint_z ARRAY_COUNT_DESTINATION = 10;

    ArrayFixed<ArrayElementMock> fixedArrayOrigin = ArrayFixed<ArrayElementMock>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    ArrayFixed<ArrayElementMock> fixedArrayDestination = ArrayFixed<ArrayElementMock>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    const puint_z EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT_ORIGIN;

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]
    puint_z uCallsToOperatorAssignment = 0;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT_DESTINATION; uIndex++)
    {
        if(((ArrayElementMock*)
            ((puint_z)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );

}

/// <summary>
/// Checks if it calls operator assignment of elements as number of times as number of elements has the
/// destination array, when the origin array is greater than the destination array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DestinationSizeNumberOfCopiesAreDoneWhereOriginSizeIsGreatherThanDestinationSize_Test )
{
    // [Preparation]
    const ArrayElementMock INITIAL_VALUE = ArrayElementMock(12);
    const puint_z ARRAY_COUNT_ORIGIN = 10;
    const puint_z ARRAY_COUNT_DESTINATION = 5;

    ArrayFixed<ArrayElementMock> fixedArrayOrigin = ArrayFixed<ArrayElementMock>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    ArrayFixed<ArrayElementMock> fixedArrayDestination = ArrayFixed<ArrayElementMock>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    const puint_z EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT = ARRAY_COUNT_DESTINATION;

    // [Execution]
    fixedArrayDestination = fixedArrayOrigin;

    // [Verification]

    puint_z uCallsToOperatorAssignment = 0;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT_DESTINATION; uIndex++)
    {
        if(((ArrayElementMock*)
            ((puint_z)fixedArrayDestination.GetAllocator()->GetPointer() + uIndex * sizeof(ArrayElementMock)))
            ->GetCallToOperatorAssignment())
        {
            uCallsToOperatorAssignment++;
        }
    }

    BOOST_CHECK_EQUAL( uCallsToOperatorAssignment, EXPECTED_CALLS_TO_OPERATOR_ASSIGNMENT );
}


/// <sumary>
/// Checks if the value is set at correct position.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_ValueIsSetAtCorrectPosition_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const u64_z NEW_VALUE = 10;
    const puint_z POSITION_TO_SET_NEW_VALUE = 2;
    const bool OTHER_POSITIONS_UNTOUCHED = true;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArray[POSITION_TO_SET_NEW_VALUE] = NEW_VALUE;

    // [Verification]
    u64_z uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);

    bool bOtherPositionsUntouched = true;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(uIndex != POSITION_TO_SET_NEW_VALUE)
            bOtherPositionsUntouched = bOtherPositionsUntouched &&
                (fixedArray.GetValue(uIndex) == INITIAL_VALUE);
    }

    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
    BOOST_CHECK_EQUAL( bOtherPositionsUntouched, OTHER_POSITIONS_UNTOUCHED );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to set a value to a position greater than the array's size.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenAttemptsToSetAValueToAPositionGreaterThanArraySize_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const puint_z POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray[POSITION_GREATER_THAN_ARRAY_SIZE] = INITIAL_VALUE;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS


/// <sumary>
/// Checks if it gets the correct value at supplied position.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const u64_z NEW_VALUE = 10;
    const puint_z POSITION_TO_SET_NEW_VALUE = 2;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Execution]
    u64_z uValue = fixedArray[POSITION_TO_SET_NEW_VALUE];

    // [Verification]
    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when it attempts to get the value from a position greater than the array's size.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenAttemptsToGetTheValueFromAPositionGreaterThanArraySize_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const puint_z POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray[POSITION_GREATER_THAN_ARRAY_SIZE];
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks if gets the correct value at supplied position.
/// </sumary>
ZTEST_CASE( GetValue_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const u64_z NEW_VALUE = 10;
    const puint_z POSITION_TO_SET_NEW_VALUE = 2;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Execution]
    u64_z uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to get the value from a position greater than the array's size.
/// </summary>
ZTEST_CASE ( GetValue_AssertionFailsWhenAttemptsToGetTheValueFromAPositionNotLessThanArraySize_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const puint_z POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray.GetValue(POSITION_GREATER_THAN_ARRAY_SIZE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Clones an array and checks if the arrays have the same values.
/// </sumary>
ZTEST_CASE( Clone_ClonedArrayHasSameValuesThanTheOriginArray_Test )
{
    // [Preparation]
    const u64_z VALUE_ORIGIN = 12;
    const u64_z VALUE_DESTINATION = 15;
    const puint_z ARRAY_COUNT = 5;
    const bool SAME_VALUES = true;

    ArrayFixed<u64_z> fixedArrayOrigin = ArrayFixed<u64_z>(ARRAY_COUNT, VALUE_ORIGIN);
    ArrayFixed<u64_z> fixedArrayDestination = ArrayFixed<u64_z>(ARRAY_COUNT, VALUE_DESTINATION);

    // [Execution]
    fixedArrayOrigin.Clone(fixedArrayDestination);

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        bSameValues = bSameValues && ( VALUE_ORIGIN == fixedArrayDestination[uIndex] );
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when the two array's capacities are different.
/// </summary>
ZTEST_CASE ( Clone_AssertionFailsWhenArrayCapacitiesAreDifferent_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT_ORIGIN = 5;
    const puint_z ARRAY_COUNT_DESTINATION = 6;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    ArrayFixed<u64_z> fixedArrayOrigin = ArrayFixed<u64_z>(ARRAY_COUNT_ORIGIN, INITIAL_VALUE);
    ArrayFixed<u64_z> fixedArrayDestination = ArrayFixed<u64_z>(ARRAY_COUNT_DESTINATION, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArrayOrigin.Clone(fixedArrayDestination);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks if the value is set at correct position.
/// </sumary>
ZTEST_CASE( SetValue_ValueIsSetAtCorrectPosition_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const u64_z NEW_VALUE = 10;
    const puint_z POSITION_TO_SET_NEW_VALUE = 2;
    const bool OTHER_POSITIONS_UNTOUCHED = true;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    fixedArray.SetValue(POSITION_TO_SET_NEW_VALUE, NEW_VALUE);

    // [Verification]
    u64_z uValue = fixedArray.GetValue(POSITION_TO_SET_NEW_VALUE);
    bool bOtherPositionsUntouched = true;

    for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; uIndex++)
    {
        if(uIndex != POSITION_TO_SET_NEW_VALUE)
            bOtherPositionsUntouched = bOtherPositionsUntouched &&
                (fixedArray.GetValue(uIndex) == INITIAL_VALUE);
    }

    BOOST_CHECK_EQUAL( uValue, NEW_VALUE );
    BOOST_CHECK_EQUAL( bOtherPositionsUntouched, OTHER_POSITIONS_UNTOUCHED );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when attempts to set a value to a position greater than the array's size.
/// </summary>
ZTEST_CASE ( SetValue_AssertionFailsWhenAttemptsToSetAValueToAPositionNotLessThanArraySize_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const bool ASSERTION_FAILED = true;
    const puint_z POSITION_GREATER_THAN_ARRAY_SIZE = ARRAY_COUNT;
    bool bAssertionFailed = false;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]

    try
    {
        fixedArray.SetValue(POSITION_GREATER_THAN_ARRAY_SIZE, INITIAL_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]

    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Returns an iterator to the position passed as parameter.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsIteratorToSpecificPositionInTheArray_Test )
{
    // [Preparation]
    const u32_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z INDEX = 2;
    const u32_z NEW_VALUE = 10;
    ArrayFixed<u32_z> arFixedArray = ArrayFixed<u32_z>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(INDEX, NEW_VALUE);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator it = arFixedArray.GetIterator(INDEX);

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// This test checks that the assert is thrown when trying to get an iterator passing an index bigger than array´s size.
/// </sumary>
ZTEST_CASE( GetIterator_AssertionFailsWhenParameterIsBiggerThanArraySize_Test )
{
    // [Preparation]
    const u32_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z INDEX = 7;
    ArrayFixed<u32_z> arFixedArray(ARRAY_COUNT, INITIAL_VALUE);
    bool bAssertionFailed = false;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    try
    {
        arFixedArray.GetIterator(INDEX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that if parameter bigger than array´s size is passed forward end position of the array is returned.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsIteratorToForwardEndPositionInTheArrayWhenParameterIsBiggerThanArraySize_Test )
{
    // [Preparation]
    const u32_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z INDEX = 7;
    const bool EXPECTED_VALUE = true;
    bool bForwardEndPosition = false;
    ArrayFixed<u32_z> arFixedArray = ArrayFixed<u32_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator it = arFixedArray.GetIterator(INDEX);
    bForwardEndPosition = it.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bForwardEndPosition, EXPECTED_VALUE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Returns an iterator to the first element in the array.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnsIteratorToFirstElementInTheArray_Test )
{
    // [Preparation]
    const u32_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z INITIAL_POS = 0;
    const u32_z NEW_VALUE = 10;
    ArrayFixed<u32_z> arFixedArray = ArrayFixed<u32_z>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(INITIAL_POS, NEW_VALUE);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator it = arFixedArray.GetFirst();

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

/// <sumary>
/// Checks that if the array is empty backward end position of the array is returned.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnsIteratorToBackwardEndPositionInTheArrayWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    bool bBackwardEndPosition = false;
    ArrayFixedTestClass<u32_z> arFixedArray;

    // [Execution]
    ArrayFixedTestClass<u32_z>::ConstArrayIterator it = arFixedArray.GetFirst();
    bBackwardEndPosition = it.IsEnd(); 

    // [Verification]
    BOOST_CHECK_EQUAL(bBackwardEndPosition, EXPECTED_VALUE);
}

/// <sumary>
/// Returns an iterator to the last element in the array.
/// </sumary>
ZTEST_CASE( GetLast_ReturnsIteratorToLastElementInTheArray_Test )
{
    // [Preparation]
    const u32_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z LAST_POS = 4;
    const u32_z NEW_VALUE = 10;
    ArrayFixed<u32_z> arFixedArray = ArrayFixed<u32_z>(ARRAY_COUNT, INITIAL_VALUE);
    arFixedArray.SetValue(LAST_POS, NEW_VALUE);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator it = arFixedArray.GetLast();

    // [Verification]
    BOOST_CHECK_EQUAL(*it, NEW_VALUE);
}

/// <sumary>
/// Checks that if the array is empty forward end position of the array is returned.
/// </sumary>
ZTEST_CASE( GetLast_ReturnsIteratorToForwardEndPositionInTheArrayWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    bool bForwardEndPosition = false;
    ArrayFixedTestClass<u32_z> arFixedArray;

    // [Execution]
    ArrayFixedTestClass<u32_z>::ConstArrayIterator it = arFixedArray.GetLast();
    bForwardEndPosition = it.IsEnd(); 

    // [Verification]
    BOOST_CHECK_EQUAL(bForwardEndPosition, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses the entire array.
/// </sumary>
ZTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeIsTheEntireArray_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z> EXPECTED_RESULT(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z FIRST_POSITION = 0;
    const puint_z LAST_POSITION = sizeof(arValues) / sizeof(u32_z) - 1U;

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(puint_z i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses just one element.
/// </sumary>
ZTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeIsOnlyOneElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    u32_z arExpectedValues[] = {3U};
    const ArrayFixed<u32_z> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_z));
    const puint_z FIRST_POSITION = 3U;
    const puint_z LAST_POSITION = FIRST_POSITION;
    const puint_z EXPECTED_COUNT = 1U;

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = arResult[0] == EXPECTED_RESULT[0];
    puint_z uCount = arResult.GetCount();

    BOOST_CHECK(bArrayIsWhatExpected);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses a common subarray.
/// </sumary>
ZTEST_CASE( GetRange1_ReturnsExpectedArrayWhenRangeEnclosesCommonSubarray_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    u32_z arExpectedValues[] = {2U, 3U, 4U};
    const ArrayFixed<u32_z> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_z));
    const puint_z FIRST_POSITION = 2U;
    const puint_z LAST_POSITION = 4U;

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(puint_z i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when positions are out of bounds.
/// </sumary>
ZTEST_CASE( GetRange1_AssertionFailsWhenPositionsAreOutOfBounds_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z FIRST_POSITION = sizeof(arValues) / sizeof(u32_z);
    const puint_z LAST_POSITION = FIRST_POSITION;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the first position is greater than the last position.
/// </sumary>
ZTEST_CASE( GetRange1_AssertionFailsWhenFirstPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z LAST_POSITION = 0;
    const puint_z FIRST_POSITION = LAST_POSITION + 1U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses the entire array.
/// </sumary>
ZTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeIsTheEntireArray_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z> EXPECTED_RESULT(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetFirst();
    const ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = arFixedArray.GetLast();

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(puint_z i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses just one element.
/// </sumary>
ZTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeIsOnlyOneElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    u32_z arExpectedValues[] = {3U};
    const ArrayFixed<u32_z> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(3U);
    const ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = FIRST_POSITION;
    const puint_z EXPECTED_COUNT = 1U;

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = arResult[0] == EXPECTED_RESULT[0];
    puint_z uCount = arResult.GetCount();

    BOOST_CHECK(bArrayIsWhatExpected);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <sumary>
/// Checks that it returns the expected array when the selected range encloses a common subarray.
/// </sumary>
ZTEST_CASE( GetRange2_ReturnsExpectedArrayWhenRangeEnclosesCommonSubarray_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    u32_z arExpectedValues[] = {2U, 3U, 4U};
    const ArrayFixed<u32_z> EXPECTED_RESULT(arExpectedValues, sizeof(arExpectedValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(2U);
    const ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = arFixedArray.GetIterator(4U);

    // [Execution]
    ArrayFixed<u32_z> arResult = arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);

    // [Verification]
    bool bArrayIsWhatExpected = true;

    for(puint_z i = 0; i < arResult.GetCapacity(); ++i)
        bArrayIsWhatExpected = bArrayIsWhatExpected && arResult[i] == EXPECTED_RESULT[i];

    BOOST_CHECK(bArrayIsWhatExpected);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position is an end position.
/// </sumary>
ZTEST_CASE( GetRange2_AssertionFailsWhenFirstPositionIsEnd_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetLast();
    ++FIRST_POSITION;
    const ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = arFixedArray.GetIterator(0);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the last position is an end position.
/// </sumary>
ZTEST_CASE( GetRange2_AssertionFailsWhenLastPositionIsEnd_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = arFixedArray.GetLast();
    ++LAST_POSITION;
    const ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetIterator(0);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the first position is greater than the last position.
/// </sumary>
ZTEST_CASE( GetRange2_AssertionFailsWhenFirstPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator FIRST_POSITION = arFixedArray.GetLast();
    ArrayFixed<u32_z>::ConstArrayIterator LAST_POSITION = FIRST_POSITION;
    --LAST_POSITION;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.GetRange(FIRST_POSITION, LAST_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
ZTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 0;
    const puint_z POSITION_B = sizeof(arValues) / sizeof(u32_z) - 1U;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
ZTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 2U;
    const puint_z POSITION_B = 4U;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is out of bounds.
/// </sumary>
ZTEST_CASE( Swap1_AssertionFailsWhenFirstPositionIsOutOfBounds_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = sizeof(arValues) / sizeof(u32_z);
    const puint_z POSITION_B = 4U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the second position provided is out of bounds.
/// </sumary>
ZTEST_CASE( Swap1_AssertionFailsWhenSecondPositionIsOutOfBounds_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = sizeof(arValues) / sizeof(u32_z);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when swapping the same element.
/// </sumary>
ZTEST_CASE( Swap1_AssertionFailsWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that nothing happens when swapping the same element.
/// </sumary>
ZTEST_CASE( Swap1_NothingHappensWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = POSITION_A;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_A];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(arFixedArray[POSITION_B], EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
ZTEST_CASE( Swap2_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetFirst();
    const ArrayFixed<u32_z>::ArrayIterator POSITION_B = arFixedArray.GetLast();
    const u32_z EXPECTED_VALUE_A = *POSITION_B;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
ZTEST_CASE( Swap2_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetIterator(2U);
    const ArrayFixed<u32_z>::ArrayIterator POSITION_B = arFixedArray.GetIterator(4U);
    const u32_z EXPECTED_VALUE_A = *POSITION_B;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is an end position.
/// </sumary>
ZTEST_CASE( Swap2_AssertionFailsWhenFirstPositionIsEndPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetLast();
    ++POSITION_A;
    const ArrayFixed<u32_z>::ArrayIterator POSITION_B = arFixedArray.GetFirst();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when the second position provided is an end position.
/// </sumary>
ZTEST_CASE( Swap2_AssertionFailsWhenSecondPositionIsEndPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetFirst();
    ArrayFixed<u32_z>::ArrayIterator POSITION_B = arFixedArray.GetLast();
    ++POSITION_B;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

/// <sumary>
/// Checks that an assertion fails when swapping the same element.
/// </sumary>
ZTEST_CASE( Swap2_AssertionFailsWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetFirst();
    const ArrayFixed<u32_z>::ArrayIterator POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.Swap(POSITION_A, POSITION_B);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that nothing happens when swapping the same element.
/// </sumary>
ZTEST_CASE( Swap2_NothingHappensWhenSwappingTheSameElement_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ArrayIterator POSITION_A = arFixedArray.GetFirst();
    const ArrayFixed<u32_z>::ArrayIterator POSITION_B = POSITION_A;
    const u32_z EXPECTED_VALUE_A = *POSITION_A;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    arFixedArray.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that it returns True when arrays have the same number of elements and those elements are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenArraysHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays are the same instance.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenArraysAreSameInstance_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray == arFixedArray;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have the same number of elements but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenArraysHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenArraysHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 == arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays have the same number of elements and those elements are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenArraysHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when arrays are the same instance.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenArraysAreSameInstance_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray != arFixedArray;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays have the same number of elements but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenArraysHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when arrays have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenArraysHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U};
    ArrayFixed<u32_z> arFixedArray1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    ArrayFixed<u32_z> arFixedArray2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray1 != arFixedArray2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears the first.
/// </sumary>
ZTEST_CASE( Contains_ReturnsTrueWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears in the middle.
/// </sumary>
ZTEST_CASE( Contains_ReturnsTrueWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, INPUT_ELEMENT, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when the element appears the last.
/// </sumary>
ZTEST_CASE( Contains_ReturnsTrueWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, INPUT_ELEMENT};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when the element is not in the array.
/// </sumary>
ZTEST_CASE( Contains_ReturnsFalseWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = arFixedArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the first.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 0;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears in the middle.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, INPUT_ELEMENT, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 1U;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the last.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsExpectedIndexWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, INPUT_ELEMENT};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 2U;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the array.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = ArrayFixed<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the first.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 0;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 0;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears in the middle.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 2U;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, INPUT_ELEMENT, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 2U;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected index when the element appears the last.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsExpectedIndexWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 3U;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, INPUT_ELEMENT};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 3U;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the array.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 0;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = ArrayFixed<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element appears before the start position.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenElementAppearsBeforeTheStartPosition_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 2U;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = ArrayFixed<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the start index is not lower than the number of elements.
/// </sumary>
ZTEST_CASE( IndexOf2_AssertionFailsWhenStartIndexIsNotLowerThanCount_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z START_POSITION = arFixedArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the start position is not lower than the number of elements.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenStartPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z START_POSITION = arFixedArray.GetCount();
    const puint_z EXPECTED_RESULT = ArrayFixed<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = arFixedArray.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

#endif

/// <sumary>
/// Checks that it returns the expected position when the element appears the first.
/// </sumary>
ZTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetFirst();

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears in the middle.
/// </sumary>
ZTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, INPUT_ELEMENT, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetIterator(1U);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the last.
/// </sumary>
ZTEST_CASE( PositionOf1_ReturnsExpectedPositionWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, INPUT_ELEMENT};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the returned iterator points to the end position when the element is not in the array.
/// </sumary>
ZTEST_CASE( PositionOf1_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the first.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetFirst();
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetFirst();

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears in the middle.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsInTheMiddle_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, INPUT_ELEMENT, 3U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetIterator(2U);
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetIterator(2U);

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns the expected position when the element appears the last.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsExpectedPositionWhenElementAppearsTheLast_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, INPUT_ELEMENT};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetIterator(3U);
    const ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the element is not in the array.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetFirst();
    ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the element appears before the start position.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsEndPositionWhenElementAppearsBeforeTheStartPosition_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    const ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetIterator(2U);
    ArrayFixed<u32_z>::ConstArrayIterator EXPECTED_RESULT = arFixedArray.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the input start position points to the end position.
/// </sumary>
ZTEST_CASE( PositionOf2_AssertionFailsWhenStartPositionIsEnd_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetLast();
    ++START_POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the start position points to an end position.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsEndPositionWhenStartPositionPointsToEndPosition_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U, 4U};
    ArrayFixed<u32_z> arFixedArray(arValues, sizeof(arValues) / sizeof(u32_z));
    ArrayFixed<u32_z>::ConstArrayIterator START_POSITION = arFixedArray.GetLast();
    ++START_POSITION;

    // [Execution]
    ArrayFixed<u32_z>::ConstArrayIterator itResult = arFixedArray.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult.IsEnd(EIterationDirection::E_Forward));
}

#endif

/// <summary>
/// Checks if returns a valid allocator.
/// </summary>
ZTEST_CASE ( GetAllocator_ReturnsValidAllocator_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;

    // [Execution]
    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    u64_z uFirstValue = *((u64_z*)fixedArray.GetAllocator()->GetPointer());

    // [Verification]
    BOOST_CHECK_EQUAL( uFirstValue, INITIAL_VALUE );
}

/// <sumary>
/// Returns the number of elements in the array.
/// </sumary>
ZTEST_CASE( GetCount_ReturnsNumberOfElementsInTheArray_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z EXPECTED_NUMBER_OF_ELEMENTS = ARRAY_COUNT;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    puint_z uNumberOfElements = fixedArray.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uNumberOfElements, EXPECTED_NUMBER_OF_ELEMENTS );
}

/// <sumary>
/// Returns the capacity of the array.
/// </sumary>
ZTEST_CASE( GetCapacity_ReturnsTheCapacityOfTheArray_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const puint_z EXPECTED_CAPACITY = ARRAY_COUNT;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    puint_z uCapacity = fixedArray.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL( uCapacity, EXPECTED_CAPACITY );
}

/// <sumary>
/// Returns false when the array is not empty.
/// </sumary>
ZTEST_CASE( IsEmpty_ReturnsFalseWhenTheArrayIsNotEmpty_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE = 12;
    const puint_z ARRAY_COUNT = 5;
    const bool ARRAY_NOT_EMPTY = false;

    ArrayFixed<u64_z> fixedArray = ArrayFixed<u64_z>(ARRAY_COUNT, INITIAL_VALUE);

    // [Execution]
    bool bIsEmpty = fixedArray.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmpty, ARRAY_NOT_EMPTY );
}

// End - Test Suite: ArrayFixed
ZTEST_SUITE_END()

