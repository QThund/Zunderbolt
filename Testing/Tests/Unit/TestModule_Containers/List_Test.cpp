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

#include "ZContainers/List.h"
#include "ListWhiteBox.h"
#include "ListElementMock.h"
#include "CallCounter.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::ListWhiteBox;
using z::Test::ListElementMock;
using z::Test::CallCounter;


ZTEST_SUITE_BEGIN( List_TestSuite )

/// <summary>
/// Checks if constructor without parameteres initializes members correctly.
/// </summary>
ZTEST_CASE ( Constructor1_ChecksIfConstructorWithoutParametersInitializesMembersCorrectly_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = ListWhiteBox<u64_z>::GetDefaultInitialCapacity();

    // [Execution]
    List<u64_z> list;

    // [Verification]
    puint_z uInitialCapacity = list.GetCapacity();
    BOOST_CHECK_EQUAL( uInitialCapacity, INITIAL_CAPACITY );
}

/// <summary>
/// Checks if constructor with number of elements to reserve by parameter initializes members correctly.
/// </summary>
ZTEST_CASE ( Constructor2_ChecksIfConstructorInitializesMembersCorrectly_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 5;

    // [Execution]
    List<u64_z> list( INITIAL_CAPACITY );

    // [Verification]
    puint_z uInitialCapacity = list.GetCapacity();
    BOOST_CHECK_EQUAL( uInitialCapacity, INITIAL_CAPACITY );

}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing zero elements as initial capacity.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailedWhenPassingZeroElementsAsInitialCapacity_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY_ZERO = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<u64_z> list(INITIAL_CAPACITY_ZERO);
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
/// Checks if copy constructor initializes correctly when passing a list with zero elements.
/// </summary>
ZTEST_CASE ( Constructor3_ChecksIfConstructorInitializesCorrectlyWhenPassingAListWithZeroElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = ListWhiteBox<u64_z>::GetDefaultInitialCapacity();
    const puint_z EXPECTED_COUNT = 0;
    List<u64_z> listOrigin;

    // [Execution]
    List<u64_z> listDestination(listOrigin);

    // [Verification]
    puint_z uCapacity = listOrigin.GetCapacity();
    puint_z uCount = listOrigin.GetCount();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks if copy constructor initializes correctly when passing a full list.
/// </summary>
ZTEST_CASE ( Constructor3_ChecksIfConstructorInitializesCorrectlyWhenPassingAFullList_Test )
{
    // [Preparation]
    const puint_z NUMBER_OF_ELEMENTS = 5;
    const bool SAME_VALUES = true;

    List<u64_z> listOrigin = List<u64_z>(NUMBER_OF_ELEMENTS);

    for(u64_z uIndex = 0; uIndex < NUMBER_OF_ELEMENTS; uIndex++)
    {
        listOrigin.Add(uIndex);
    }

    // [Execution]
    List<u64_z> listDestination(listOrigin);

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < NUMBER_OF_ELEMENTS; uIndex++)
    {
        bSameValues = bSameValues && (listOrigin.GetValue(uIndex) == listDestination.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if the instance is correctly constructed when it receives a common array and its size.
/// </summary>
ZTEST_CASE ( Constructor4_ItIsCorrectlyConstructedFromCommonArray_Test )
{
    // [Preparation]
    const unsigned int ARRAY_SIZE = 3;
    const char SOURCE_ARRAY[ARRAY_SIZE] = {0, 1, 2};

    // [Execution]
    List<char> list(SOURCE_ARRAY, ARRAY_SIZE);

    // [Verification]
    puint_z uListSize = list.GetCount();
    BOOST_CHECK_EQUAL(uListSize, ARRAY_SIZE);

    for(unsigned int i = 0; i < list.GetCount(); ++i)
        BOOST_CHECK_EQUAL( list[i], SOURCE_ARRAY[i] );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks than assertion fails when the input array is null.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenListIsNull_Test )
{
    // [Preparation]
    const int* NULL_ARRAY = null_z;
    const unsigned int NON_ZERO_SIZE = 3;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        List<int> list(NULL_ARRAY, NON_ZERO_SIZE);
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
ZTEST_CASE ( Constructor4_AssertionFailsWhenCountIsZero_Test )
{
    // [Preparation]
    const int SOURCE_ARRAY[3] = {0, 1, 2};
    const unsigned int ZERO_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        List<int> list(SOURCE_ARRAY, ZERO_SIZE);
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
/// Checks if the destructor is called for every element.
/// </summary>
ZTEST_CASE ( Destructor_TheDestructorOfEveryElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 5;
    {
        List<CallCounter> list(EXPECTED_CALLS);
        list.Add(CallCounter());
        list.Add(CallCounter());
        list.Add(CallCounter());
        list.Add(CallCounter());
        list.Add(CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    } // Destructor called

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is equal to the destination list.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsEqualToDestinationListSize_Test )
{
    // [Preparation]
    const puint_z LIST_COUNT = 5;
    List<u64_z> listOrigin = List<u64_z>(LIST_COUNT);
    List<u64_z> listDestination = List<u64_z>(LIST_COUNT);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        listOrigin.Add(uIndex);
        listDestination.Add(LIST_COUNT-uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when assigning a list to itself.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenAssigningAListToItself_Test )
{
    // [Preparation]
    const puint_z LIST_COUNT = 5;
    List<u64_z> list = List<u64_z>(LIST_COUNT);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        list.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    list = list;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        bSameValues = bSameValues && (list.GetValue(uIndex) == uIndex);
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is minor than the destination list.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsMinorThanDestinationListSize_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 3;
    const puint_z LIST_COUNT_DESTINATION = 5;
    List<u64_z> listOrigin = List<u64_z>(INITIAL_CAPACITY);
    List<u64_z> listDestination = List<u64_z>(INITIAL_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is zero and the destination list has elements.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListIsZeroAndTheDestinationListHasElements_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 5;
    const puint_z LIST_COUNT_DESTINATION = 5;
    List<u64_z> listOrigin = List<u64_z>(INITIAL_CAPACITY);
    List<u64_z> listDestination = List<u64_z>(INITIAL_CAPACITY);
    const bool DESTINATION_IS_EMPTY = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bDestinationIsEmpty = listDestination.IsEmpty();

    BOOST_CHECK_EQUAL( bDestinationIsEmpty, DESTINATION_IS_EMPTY );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// destination list capacity is not minor than origin list capacity.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndDestinationListCapacityIsNotMinorThanOriginListCapacity_Test )
{
    // [Preparation]
    const puint_z LISTS_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const puint_z LIST_COUNT_DESTINATION = 3;
    List<u64_z> listOrigin = List<u64_z>(LISTS_CAPACITY);
    List<u64_z> listDestination = List<u64_z>(LISTS_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// the capacity of the origin list is greater than the capacity of the destination list.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndOriginListCapacityIsGreaterThanDestinationListCapacity_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY_ORIGIN = 5;
    const puint_z LIST_CAPACITY_DESTINATION = 3;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const puint_z LIST_COUNT_DESTINATION = 3;
    List<u64_z> listOrigin = List<u64_z>(LIST_CAPACITY_ORIGIN);
    List<u64_z> listDestination = List<u64_z>(LIST_CAPACITY_DESTINATION);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <summary>
/// Checks if it assigns correctly when the size of the origin list is greater than the destination list and
/// the capacity of the two lists are equal.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CorrectlyAssignedWhenOriginListSizeIsGreaterThanDestinationListSizeAndOriginListCapacityOfBothIsEqual_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const puint_z LIST_COUNT_DESTINATION = 3;
    List<u64_z> listOrigin = List<u64_z>(LIST_CAPACITY);
    List<u64_z> listDestination = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_DESTINATION; uIndex++)
    {
        listDestination.Add(uIndex);
    }

    const bool SAME_VALUES = true;

    // [Execution]
    listDestination = listOrigin;

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, SAME_VALUES );
}

/// <sumary>
/// Checks that it returns True when lists have the same number of elements and those elements are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenListsHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list1 == list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when lists are the same instance.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenListsAreSameInstance_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list == list;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when lists have the same number of elements but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenListsHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = list1 == list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when lists have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenListsHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = list1 == list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when lists have the same number of elements and those elements are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenListsHaveSameNumberOfElementsAndElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = list1 != list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when lists are the same instance.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenListsAreSameInstance_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = list != list;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when lists have the same number of elements but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenListsHaveSameNumberOfElementsButElementsAreNotEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {7U, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list1 != list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when lists have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenListsHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    u32_z arValues1[] = {0, 1U, 2U, 3U};
    List<u32_z> list1(arValues1, sizeof(arValues1) / sizeof(u32_z));
    u32_z arValues2[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list2(arValues2, sizeof(arValues2) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list1 != list2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
ZTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalList_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    List<u64_z> listOrigin = List<u64_z>(LIST_CAPACITY);
    List<u64_z> listDestination = List<u64_z>(LIST_CAPACITY);
    const bool VALUES_ARE_THE_SAME = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the clone method works properly when the size of the destination list is bigger.
/// </summary>
ZTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalListWhenInputListSizeIsBigger_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY_ORIGIN = 5;
    const puint_z LIST_CAPACITY_DESTINATION = 8;
    const puint_z LIST_COUNT_ORIGIN = 5;
    List<u64_z> listOrigin = List<u64_z>(LIST_CAPACITY_ORIGIN);
    List<u64_z> listDestination = List<u64_z>(LIST_CAPACITY_DESTINATION);
    const bool VALUES_ARE_THE_SAME = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the clone method works properly when the size of the destination list is lower.
/// </summary>
ZTEST_CASE ( Clone_ClonedListHasSameValuesThanTheOriginalListWhenInputListSizeIsLower_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY_ORIGIN = 8;
    const puint_z LIST_CAPACITY_DESTINATION = 5;
    const puint_z LIST_COUNT_ORIGIN = 8;
    List<u64_z> listOrigin = List<u64_z>(LIST_CAPACITY_ORIGIN);
    List<u64_z> listDestination = List<u64_z>(LIST_CAPACITY_DESTINATION);
    const bool VALUES_ARE_THE_SAME = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        listOrigin.Add(uIndex+10);
    }

    // [Execution]
    listOrigin.Clone(listDestination);

    // [Verification]
    bool bSameValues = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        bSameValues = bSameValues && (listDestination.GetValue(uIndex) == listOrigin.GetValue(uIndex));
    }

    BOOST_CHECK_EQUAL( bSameValues, VALUES_ARE_THE_SAME );
}

/// <summary>
/// Checks if it the getValue method method returns the value placed in the position passed as parameter.
/// </summary>
ZTEST_CASE ( GetValue_CorrectValueReturned_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const u64_z VALUE_TO_RETURN = 19;
    const u64_z VALUE_TO_FILL_LIST = 4;
    const puint_z INDEX_POSITION_TO_RETURN = 3;
    u64_z uReturnedValue = 0;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        if (uIndex == INDEX_POSITION_TO_RETURN)
        {
            list.Add(VALUE_TO_RETURN);
        }
        else
        {
            list.Add(VALUE_TO_FILL_LIST);
        }
    }

    // [Execution]
    uReturnedValue = list.GetValue(INDEX_POSITION_TO_RETURN);

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_RETURN );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing non existant index to get the value.
/// </summary>
ZTEST_CASE ( GetValue_AssertionFailedWhenPassingAnIndexBiggerThanNumberOfElements_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const u64_z VALUE_TO_FILL_LIST = 4;
    const puint_z INDEX_POSITION_TO_RETURN = 10;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetValue(INDEX_POSITION_TO_RETURN);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
ZTEST_CASE ( GetValue_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z INDEX_POSITION_TO_RETURN = 4;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetValue(INDEX_POSITION_TO_RETURN);
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
/// Checks if it the method set the value in the position passed as parameter.
/// </summary>
ZTEST_CASE ( SetValue_CorrectValueSet_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const u64_z VALUE_TO_SET = 19;
    const u64_z VALUE_TO_FILL_LIST = 4;
    const puint_z INDEX_POSITION_TO_SET = 3;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_SET);

    // [Verification]
    u64_z uReturnedValue = list.GetValue(INDEX_POSITION_TO_SET);
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_SET );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
ZTEST_CASE ( SetValue_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z INDEX_POSITION_TO_SET = 4;
    List<u64_z> list(LIST_CAPACITY);
    const u64_z VALUE_TO_SET = 10;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_SET);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when trying to set a value in a wrong index.
/// </summary>
ZTEST_CASE ( SetValue_AssertionFailedWhenSettingValueInWrongIndex_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const u64_z VALUE_TO_FILL_LIST = 4;
    const puint_z INDEX_POSITION_TO_SET = 10;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.SetValue(INDEX_POSITION_TO_SET, VALUE_TO_FILL_LIST);
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
/// Checks if it the operator returns the value placed in the position passed as parameter.
/// </summary>
ZTEST_CASE ( OperatorListSubscript_CorrectValueReturned_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    const u64_z VALUE_TO_RETURN = 19;
    const u64_z VALUE_TO_FILL_LIST = 4;
    const puint_z INDEX_POSITION_TO_RETURN = 3;
    u64_z uReturnedValue = 0;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        if (uIndex == INDEX_POSITION_TO_RETURN)
        {
            list.Add(VALUE_TO_RETURN);
        }
        else
        {
            list.Add(VALUE_TO_FILL_LIST);
        }
    }

    // [Execution]
    uReturnedValue = list[INDEX_POSITION_TO_RETURN];

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, VALUE_TO_RETURN );
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when empty list.
/// </summary>
ZTEST_CASE ( OperatorListSubscript_AssertionFailedWhenListIsEmpty_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z INDEX_POSITION_TO_RETURN = 4;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list[INDEX_POSITION_TO_RETURN];
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing a wrong index to get the element.
/// </summary>
ZTEST_CASE ( OperatorListSubscript_AssertionFailedWhenPassingAnIndexBiggerThanNumberOfElements_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT = 5;
    const u64_z VALUE_TO_FILL_LIST = 4;
     const puint_z INDEX_POSITION_TO_RETURN = 10;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);
    const bool ASSERTION_FAILED = true;

    for(puint_z uIndex = 0; uIndex < LIST_COUNT; uIndex++)
    {
        list.Add(VALUE_TO_FILL_LIST);
    }

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list[INDEX_POSITION_TO_RETURN];
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
/// Checks that the expected iterator is returned when using a common list and a common index.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheExpectedIteratorWhenUsingCommonListAndPosition_Test )
{
    // [Preparation]
    const int NUMBER_OF_ELEMENTS = 5;
    const puint_z INPUT_INDEX = 1;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    List<int>::ConstListIterator EXPECTED_ITERATOR = list.GetFirst();
    ++EXPECTED_ITERATOR;

    // [Execution]
    List<int>::ConstListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the first position is returned when using a common list and the index equals zero.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheFirstPositionWhenUsingCommonListAndZeroIndex_Test )
{
    // [Preparation]
    const int NUMBER_OF_ELEMENTS = 5;
    const puint_z INPUT_INDEX = 0;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    List<int>::ConstListIterator EXPECTED_ITERATOR = list.GetFirst();

    // [Execution]
    List<int>::ConstListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the last position is returned when using a common list and the last index.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheLastPositionWhenUsingCommonListAndLastIndex_Test )
{
    // [Preparation]
    const int NUMBER_OF_ELEMENTS = 5;
    const puint_z INPUT_INDEX = NUMBER_OF_ELEMENTS - 1U;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    List<int>::ConstListIterator EXPECTED_ITERATOR = list.GetLast();

    // [Execution]
    List<int>::ConstListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the list is empty.
/// </sumary>
ZTEST_CASE( GetIterator_AssertionFailsWhenListIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 0;
    List<int> list = List<int>();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetIterator(INPUT_INDEX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <sumary>
/// Checks that an assertion fails when the input index is out of bounds.
/// </sumary>
ZTEST_CASE( GetIterator_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int NUMBER_OF_ELEMENTS = 5;
    const puint_z OUT_OF_BOUNDS_INDEX = NUMBER_OF_ELEMENTS;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.GetIterator(OUT_OF_BOUNDS_INDEX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
ZTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 0;
    List<int> list = List<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    List<int>::ConstListIterator it = list.GetIterator(INPUT_INDEX);

    // [Verification]
    bool bIsEnd = it.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

/// <sumary>
/// Checks that the resultant iterator points to the end position when the input index is out of bounds.
/// </sumary>
ZTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    const bool ITERATOR_POINTS_END_POSITION = true;
    const int NUMBER_OF_ELEMENTS = 5;
    const puint_z OUT_OF_BOUNDS_INDEX = NUMBER_OF_ELEMENTS;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    List<int>::ConstListIterator it = list.GetIterator(OUT_OF_BOUNDS_INDEX);

    // [Verification]
    bool bIsEnd = it.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <sumary>
/// Checks that the first position is returned when using a common list.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnsTheFirstPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    const int NUMBER_OF_ELEMENTS = 5;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    List<int>::ConstListIterator EXPECTED_ITERATOR(&list, 0);

    // [Execution]
    List<int>::ConstListIterator it = list.GetFirst();

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
ZTEST_CASE( GetFirst_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> list = List<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    List<int>::ConstListIterator it = list.GetFirst();

    // [Verification]
    bool bIsEnd = it.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

/// <sumary>
/// Checks that the last position is returned when using a common list.
/// </sumary>
ZTEST_CASE( GetLast_ReturnsTheLastPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    const int NUMBER_OF_ELEMENTS = 5;
    List<int> list = List<int>(NUMBER_OF_ELEMENTS);

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    List<int>::ConstListIterator EXPECTED_ITERATOR(&list, NUMBER_OF_ELEMENTS - 1U);

    // [Execution]
    List<int>::ConstListIterator it = list.GetLast();

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the resultant iterator points to the end position when the list is empty.
/// </sumary>
ZTEST_CASE( GetLast_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> list = List<int>();
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    List<int>::ConstListIterator it = list.GetLast();

    // [Verification]
    bool bIsEnd = it.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
ZTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 4U;
    List<int> list(1U);

    // [Execution]
    list.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = list.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
ZTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const puint_z INPUT_CAPACITY = 20U;
    List<int> list(3U);
    const int NUMBER_OF_ELEMENTS = 3;
    
    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        list.Add(i);

    // [Execution]
    list.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        bElementsAreTheSame = bElementsAreTheSame && (list[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than currently reserved.
/// </summary>
ZTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 1U;
    const puint_z EXPECTED_CAPACITY = 3U;
    List<puint_z> list(EXPECTED_CAPACITY);
    
    for(puint_z i = 0; i < EXPECTED_CAPACITY; ++i)
        list.Add(i);

    const puint_z* ORIGINAL_FIRST_ELEMENT_ADDRESS = &list[0];

    // [Execution]
    list.Reserve(INPUT_CAPACITY);

    // [Verification]
    puint_z uCapacity = list.GetCapacity();
    puint_z* pFirstElementAddress = &list[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks if the method returns the correct number of elements in the list.
/// </summary>
ZTEST_CASE ( GetCount_CorrectNumberOfElementsReturned_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z LIST_COUNT_ORIGIN = 5;
    puint_z uReturnedValue = 0;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(uIndex);
    }

    // [Execution]
    uReturnedValue = list.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, LIST_COUNT_ORIGIN );
}

/// <summary>
/// Checks that elements can be added to empty lists.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedToEmptyList_Test )
{
    // [Preparation]
    List<int> emptyList;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    emptyList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(emptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( Add_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    fullList.Add(0);
    fullList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    fullList.Add(ELEMENT_VALUE);

    // [Verification]
    puint_z uCapacity =  fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when lists are full.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenListIsFull_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    fullList.Add(0);
    fullList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    fullList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(fullList[3], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> commonList(INITIAL_CAPACITY);
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    commonList.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
ZTEST_CASE ( Add_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 1;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> commonList(INITIAL_CAPACITY);

    // [Execution]
    commonList.Add(ELEMENT_VALUE);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
ZTEST_CASE ( Add_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<CallCounter> commonList(INITIAL_CAPACITY);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.Add(newElement);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const List<int>::ConstListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const List<int>::ConstListIterator POSITION = commonList.GetIterator(1);

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( Insert1_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    fullList.Add(0);
    fullList.Add(0);
    const int ELEMENT_VALUE = 1;
    const List<int>::ConstListIterator POSITION = fullList.GetFirst();

    // [Execution]
    fullList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCapacity =  fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
ZTEST_CASE ( Insert1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> commonList(INITIAL_CAPACITY);
    commonList.Add(0);
    const List<int>::ConstListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
ZTEST_CASE ( Insert1_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<CallCounter> commonList(INITIAL_CAPACITY);
    commonList.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const List<CallCounter>::ConstListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.Insert(newElement, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that it returns an iterator that returns to the inserted element.
/// </summary>
ZTEST_CASE ( Insert1_ReturnsIteratorThatPointsToInsertedElement_Test )
{
    // [Preparation]
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const List<int>::ConstListIterator POSITION = commonList.GetIterator(1);

    // [Execution]
    List<int>::ConstListIterator itResult = commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Insert1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    List<int>::ConstListIterator ITERATOR_END = commonList.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.Insert(ELEMENT_VALUE, ITERATOR_END);
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
/// Checks that elements can be inserted into empty lists.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    List<int> emptyList;
    List<int>::ConstListIterator ITERATOR = emptyList.GetFirst();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    emptyList.Insert(ELEMENT_VALUE, ITERATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(emptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsInsertedAtTheEndWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    List<int>::ConstListIterator ITERATOR_END = commonList.GetLast();
    ++ITERATOR_END;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, ITERATOR_END);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 1;

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( Insert2_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    fullList.Add(0);
    fullList.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 0;

    // [Execution]
    fullList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCapacity = fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
ZTEST_CASE ( Insert2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> commonList(INITIAL_CAPACITY);
    commonList.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
ZTEST_CASE ( Insert2_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    List<CallCounter> commonList(INITIAL_CAPACITY);
    commonList.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Insert(newElement, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
ZTEST_CASE ( Insert2_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const puint_z OUT_OF_BOUNDS_INDEX = commonList.GetCount();
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.Insert(ELEMENT_VALUE, OUT_OF_BOUNDS_INDEX);
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
/// Checks that elements can be inserted into empty lists.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    List<int> emptyList;
    const puint_z POSITION = 0;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    emptyList.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(emptyList[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the index is out of bounds.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsInsertedAtTheEndWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const puint_z INDEX_OUT_OF_BOUNDS = commonList.GetCount();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    commonList.Insert(ELEMENT_VALUE, INDEX_OUT_OF_BOUNDS);

    // [Verification]
    BOOST_CHECK_EQUAL(commonList[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
ZTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(ELEMENT_VALUE);
    const List<int>::ListIterator POSITION = commonList.GetLast();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
ZTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(ELEMENT_VALUE);
    commonList.Add(0);
    commonList.Add(0);
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(ELEMENT_VALUE);
    commonList.Add(0);
    const List<int>::ListIterator POSITION = commonList.GetIterator(1);

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
ZTEST_CASE ( Remove1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(0);
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
ZTEST_CASE ( Remove1_DestructorOfElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    List<CallCounter> commonList;
    commonList.Add(CallCounter());
    const List<CallCounter>::ListIterator POSITION = commonList.GetFirst();
    CallCounter::ResetCounters();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the returned iterator points to the next element when the removed element was not the last one.
/// </summary>
ZTEST_CASE ( Remove1_ReturnedIteratorPointsNextWhenElementWasNotTheLastOne_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(EXPECTED_ELEMENT);
    commonList.Add(0);
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    List<int>::ConstListIterator itResult = commonList.Remove(POSITION);

    // [Verification]
    int nValue = *itResult;
    BOOST_CHECK_EQUAL(nValue, EXPECTED_ELEMENT);
}

/// <summary>
/// Checks that the returned iterator points to the end position when the removed element was the last one.
/// </summary>
ZTEST_CASE ( Remove1_ReturnedIteratorPointsEndPositionWhenElementWasTheLastOne_Test )
{
    // [Preparation]
    const bool POINTS_END_POSITION = true;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(0);
    const List<int>::ListIterator POSITION = commonList.GetLast();

    // [Execution]
    List<int>::ConstListIterator itResult = commonList.Remove(POSITION);

    // [Verification]
    bool bPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_END_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Remove1_AssertionFailsWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    List<int>::ListIterator ITERATOR_END = commonList.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.Remove(ITERATOR_END);
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
/// Checks that nothing happens when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Remove1_NothingHappensWhenIteratorsPointsToForwardEndPosition_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const puint_z EXPECTED_COUNT = commonList.GetCount();
    List<int>::ListIterator ITERATOR_END = commonList.GetLast();
    ++ITERATOR_END;

    // [Execution]
    commonList.Remove(ITERATOR_END);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
ZTEST_CASE ( Remove1_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> commonList;
    const puint_z EXPECTED_COUNT = 0;
    List<int>::ListIterator ITERATOR = commonList.GetFirst();

    // [Execution]
    commonList.Remove(ITERATOR);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(ELEMENT_VALUE);
    const puint_z POSITION = commonList.GetCount() - 1U;

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(ELEMENT_VALUE);
    commonList.Add(0);
    commonList.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK(bElementDoesNotExist);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(ELEMENT_VALUE);
    commonList.Add(0);
    const puint_z POSITION = 1;

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !commonList.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
ZTEST_CASE ( Remove2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
ZTEST_CASE ( Remove2_DestructorOfElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    List<CallCounter> commonList;
    commonList.Add(CallCounter());
    const puint_z POSITION = 0;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
ZTEST_CASE ( Remove2_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const puint_z POSITION = commonList.GetCount();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.Remove(POSITION);
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
/// Checks that nothing happens when the index is out of bounds.
/// </summary>
ZTEST_CASE ( Remove2_NothingHappensWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    List<int> commonList;
    commonList.Add(0);
    const puint_z EXPECTED_COUNT = commonList.GetCount();
    const puint_z POSITION = commonList.GetCount();

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
ZTEST_CASE ( Remove2_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> commonList;
    const puint_z EXPECTED_COUNT = 0;
    const puint_z POSITION = 0;

    // [Execution]
    commonList.Remove(POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that nothing happens when the list is empty.
/// </summary>
ZTEST_CASE ( Clear_NothingHappensWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> commonList;
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    commonList.Clear();

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the list is full.
/// </summary>
ZTEST_CASE ( Clear_AllElemensAreRemovedWhenListIsFull_Test )
{
    // [Preparation]
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    commonList.Add(0);
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    commonList.Clear();

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the list contains some elements.
/// </summary>
ZTEST_CASE ( Clear_AllElementsAreRemovedWhenListContainsSomeElements_Test )
{
    // [Preparation]
    List<int> commonList(3U);
    commonList.Add(0);
    commonList.Add(0);
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    commonList.Clear();

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
ZTEST_CASE ( Clear_DestructorIsCalledForEveryElement_Test )
{
    // [Preparation]
    List<CallCounter> commonList(3U);
    commonList.Add(CallCounter());
    commonList.Add(CallCounter());
    const puint_z EXPECTED_CALLS = 2;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.Clear();

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly retrieved from the last position of the list.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(3);
    List<int>::ListIterator itLast = commonList.GetLast();

    // [Execution]
    List<int> returnedList = commonList.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the list.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetFirst();
    List<int>::ListIterator itLast = commonList.GetIterator(2);
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetIterator(3);
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = itFirst;
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
ZTEST_CASE ( GetRange1_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    List<CallCounter>::ListIterator itFirst = commonList.GetIterator(1);
    List<CallCounter>::ListIterator itLast = commonList.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    commonList.GetRange(itFirst, itLast);

    // [Verification]
    puint_z uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the list can be retrieved.
/// </summary>
ZTEST_CASE ( GetRange1_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int> expectedList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));;
    List<int>::ListIterator itFirst = commonList.GetFirst();
    List<int>::ListIterator itLast = commonList.GetLast();

    // [Execution]
    List<int> returnedList = commonList.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( GetRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
ZTEST_CASE ( GetRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
ZTEST_CASE ( GetRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements are correctly retrieved from the last position of the list.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 3U;
    const puint_z LAST = 5U;

    // [Execution]
    List<int> returnedList = commonList.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the list.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = 2U;
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = FIRST;
    
    // [Execution]
    List<int> returnedList = commonList.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(returnedList == expectedList);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
ZTEST_CASE ( GetRange2_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    const puint_z FIRST = 1U;
    const puint_z LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.GetRange(FIRST, LAST);

    // [Verification]
    puint_z uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the list can be retrieved.
/// </summary>
ZTEST_CASE ( GetRange2_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int> expectedList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = commonList.GetCount() - 1U;

    // [Execution]
    List<int> returnedList = commonList.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the list.
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = commonList.GetCount();
    const puint_z LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the list
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = commonList.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
ZTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 0;
    const puint_z POSITION_B = sizeof(arValues) / sizeof(u32_z) - 1U;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(list[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(list[POSITION_B], EXPECTED_VALUE_B);
}

/// <sumary>
/// Checks that elements are correctly swapped when selecting any position.
/// </sumary>
ZTEST_CASE( Swap1_ElementsAreCorrectlySwappedWhenSelectingAnyPosition_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 2U;
    const puint_z POSITION_B = 4U;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_B];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(list[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(list[POSITION_B], EXPECTED_VALUE_B);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the first position provided is out of bounds.
/// </sumary>
ZTEST_CASE( Swap1_AssertionFailsWhenFirstPositionIsOutOfBounds_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = sizeof(arValues) / sizeof(u32_z);
    const puint_z POSITION_B = 4U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = sizeof(arValues) / sizeof(u32_z);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z POSITION_A = 4U;
    const puint_z POSITION_B = POSITION_A;
    const u32_z EXPECTED_VALUE_A = arValues[POSITION_A];
    const u32_z EXPECTED_VALUE_B = arValues[POSITION_A];

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(list[POSITION_A], EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(list[POSITION_B], EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that elements are correctly swapped when they occupy the first and the last positions.
/// </sumary>
ZTEST_CASE( Swap2_ElementsAreCorrectlySwappedWhenTheyAreTheFirstAndTheLast_Test )
{
    // [Preparation]
    u32_z arValues[] = {0, 1U, 2U, 3U, 4U, 5U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ListIterator POSITION_A = list.GetFirst();
    const List<u32_z>::ListIterator POSITION_B = list.GetLast();
    const u32_z EXPECTED_VALUE_A = *POSITION_B;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ListIterator POSITION_A = list.GetIterator(2U);
    const List<u32_z>::ListIterator POSITION_B = list.GetIterator(4U);
    const u32_z EXPECTED_VALUE_A = *POSITION_B;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    List<u32_z>::ListIterator POSITION_A = list.GetLast();
    ++POSITION_A;
    const List<u32_z>::ListIterator POSITION_B = list.GetFirst();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ListIterator POSITION_A = list.GetFirst();
    List<u32_z>::ListIterator POSITION_B = list.GetLast();
    ++POSITION_B;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ListIterator POSITION_A = list.GetFirst();
    const List<u32_z>::ListIterator POSITION_B = POSITION_A;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.Swap(POSITION_A, POSITION_B);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ListIterator POSITION_A = list.GetFirst();
    const List<u32_z>::ListIterator POSITION_B = POSITION_A;
    const u32_z EXPECTED_VALUE_A = *POSITION_A;
    const u32_z EXPECTED_VALUE_B = *POSITION_A;

    // [Execution]
    list.Swap(POSITION_A, POSITION_B);

    // [Verification]
    BOOST_CHECK_EQUAL(*POSITION_A, EXPECTED_VALUE_A);
    BOOST_CHECK_EQUAL(*POSITION_B, EXPECTED_VALUE_B);
}

#endif

/// <sumary>
/// Checks that it returns True when the element appears the first.
/// </sumary>
ZTEST_CASE( Contains_ReturnsTrueWhenElementAppearsTheFirst_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {INPUT_ELEMENT, 1U, 3U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list.Contains(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list.Contains(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = list.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when the element is not in the list.
/// </sumary>
ZTEST_CASE( Contains_ReturnsFalseWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = list.Contains(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 0;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 1U;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 2U;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the list.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = List<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 0;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 2U;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = 3U;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the element is not in the list.
/// </sumary>
ZTEST_CASE( IndexOf2_ReturnsElementNotFoundWhenElementIsNotFound_Test )
{
    // [Preparation]
    const puint_z START_POSITION = 0;
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = List<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z EXPECTED_RESULT = List<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z START_POSITION = list.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.IndexOf(INPUT_ELEMENT, START_POSITION);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const puint_z START_POSITION = list.GetCount();
    const puint_z EXPECTED_RESULT = List<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = list.IndexOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetFirst();

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetIterator(1U);

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the returned iterator points to the end position when the element is not in the list.
/// </sumary>
ZTEST_CASE( PositionOf1_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator START_POSITION = list.GetFirst();
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetFirst();

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator START_POSITION = list.GetIterator(2U);
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetIterator(2U);

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator START_POSITION = list.GetIterator(3U);
    const List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns an iterator that points to the end position when the element is not in the list.
/// </sumary>
ZTEST_CASE( PositionOf2_ReturnsEndPositionWhenElementIsNotFound_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    u32_z arValues[] = {1U, 3U, 4U};
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator START_POSITION = list.GetFirst();
    List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    const List<u32_z>::ConstListIterator START_POSITION = list.GetIterator(2U);
    List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    List<u32_z>::ConstListIterator START_POSITION = list.GetLast();
    ++START_POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        list.PositionOf(INPUT_ELEMENT, START_POSITION);
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
    List<u32_z> list(arValues, sizeof(arValues) / sizeof(u32_z));
    List<u32_z>::ConstListIterator START_POSITION = list.GetLast();
    ++START_POSITION;
    List<u32_z>::ConstListIterator EXPECTED_RESULT = list.GetLast();
    ++EXPECTED_RESULT;

    // [Execution]
    List<u32_z>::ConstListIterator itResult = list.PositionOf(INPUT_ELEMENT, START_POSITION);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that elements can be added to empty lists.
/// </summary>
ZTEST_CASE ( AddRange_ElementIsCorrectlyAddedToEmptyList_Test )
{
    // [Preparation]
    List<int> emptyList;
    const int EXPECTED_VALUES[] = {2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    
    // [Execution]
    emptyList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(emptyList == expectedList);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( AddRange_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    
    // [Execution]
    fullList.AddRange(itFirst, itLast);

    // [Verification]
    puint_z uCapacity = fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when lists are full.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenListIsFull_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(8);
    fullList.Add(9);
    fullList.Add(0);
    const int EXPECTED_VALUES[] = {8, 9, 0, 2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);

    // [Execution]
    fullList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(fullList == expectedList);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(2);
    List<int>::ListIterator itLast = inputList.GetIterator(4);

    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that the count of elements of the list is increased after some elements are added.
/// </summary>
ZTEST_CASE ( AddRange_CountIsIncreasedAfterAddingElements_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    List<int> commonList(3);
    commonList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    
    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the elements is called when adding them to the list.
/// </summary>
ZTEST_CASE ( AddRange_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    List<CallCounter>::ListIterator itFirst = inputList.GetIterator(0);
    List<CallCounter>::ListIterator itLast = inputList.GetIterator(2);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly added at the end when both iterators are equal.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(2);
    List<int>::ListIterator itLast = itFirst;

    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list when using all the elements of another list.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherList_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2, 3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetFirst();
    List<int>::ListIterator itLast = inputList.GetLast();

    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list when using elements of the same list and no reallocation is necessary.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingElementsOfTheSameListAndNoReallocationIsNecessary_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    commonList.Reserve(5);
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetLast();

    // [Execution]
    commonList.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( AddRange_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.AddRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
ZTEST_CASE ( AddRange_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.AddRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
ZTEST_CASE ( AddRange_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.AddRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementsAreCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const puint_z POSITION = 0;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const puint_z POSITION = 1;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly inserted when using elements of the same list and no reallocation is necessary.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenUsingElementsOfTheSameListAndNoReallocationIsNecessary_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    commonList.Reserve(5);
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetLast();
    const puint_z POSITION = 1;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( InsertRange1_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const puint_z POSITION = 0;
    
    // [Execution]
    fullList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCapacity = fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
ZTEST_CASE ( InsertRange1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    List<int> commonList(3);
    commonList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const puint_z POSITION = 0;
    
    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
ZTEST_CASE ( InsertRange1_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    List<CallCounter>::ListIterator itFirst = inputList.GetIterator(0);
    List<CallCounter>::ListIterator itLast = inputList.GetIterator(2);
    const puint_z POSITION = 0;

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly inserted when both positions are equal.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(2);
    List<int>::ListIterator itLast = itFirst;
    const puint_z POSITION = 0;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list when using all the elements of another list.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherList_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetFirst();
    List<int>::ListIterator itLast = inputList.GetLast();
    const puint_z POSITION = 0;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetFirst();
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itFirst;
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itLast;
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the insertion position is not lower than the number of elements in the list.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetFirst();
    List<int>::ListIterator itLast = inputList.GetLast();
    const puint_z POSITION = commonList.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty lists.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    List<int> emptyList(5);
    const puint_z POSITION = 0;

    // [Execution]
    emptyList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(emptyList == expectedList);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position is not lower than the number of elements in the list.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementIsInsertedAtTheEndWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const puint_z POSITION = commonList.GetCount();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const List<int>::ListIterator POSITION = commonList.GetIterator(1);

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly inserted when using elements of the same list and no reallocation is necessary.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenUsingElementsOfTheSameListAndNoReallocationIsNecessary_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    commonList.Reserve(5);
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetLast();
    const List<int>::ListIterator POSITION = commonList.GetIterator(1);

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full list.
/// </summary>
ZTEST_CASE ( InsertRange2_CapacityIsIncreasedWhenAddingElementsToFullList_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    List<int> fullList(INITIAL_CAPACITY);
    fullList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const List<int>::ListIterator POSITION = fullList.GetFirst();
    
    // [Execution]
    fullList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCapacity = fullList.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the list is increased after an element is added.
/// </summary>
ZTEST_CASE ( InsertRange2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    List<int> commonList(3);
    commonList.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    const List<int>::ListIterator POSITION = commonList.GetFirst();
    
    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the list.
/// </summary>
ZTEST_CASE ( InsertRange2_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    List<CallCounter>::ListIterator itFirst = inputList.GetIterator(0);
    List<CallCounter>::ListIterator itLast = inputList.GetIterator(2);
    const List<CallCounter>::ListIterator POSITION = commonList.GetFirst();

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(2);
    List<int>::ListIterator itLast = itFirst;
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common list when using all the elements of another list.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherList_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetFirst();
    List<int>::ListIterator itLast = inputList.GetLast();
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( InsertRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetFirst();
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
ZTEST_CASE ( InsertRange2_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itFirst;
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
ZTEST_CASE ( InsertRange2_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetLast();
    List<int>::ListIterator itLast = inputList.GetLast();
    ++itLast;
    const List<int>::ListIterator POSITION = commonList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the insertion position points to the end position.
/// </summary>
ZTEST_CASE ( InsertRange2_AssertionFailsWhenInsertionPositionIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetFirst();
    List<int>::ListIterator itLast = inputList.GetLast();
    List<int>::ListIterator POSITION = commonList.GetLast();
    ++POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that elements can be inserted into empty lists.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementIsInsertedIntoEmptyList_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    List<int> emptyList(5);
    const List<int>::ListIterator POSITION = emptyList.GetFirst();

    // [Execution]
    emptyList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(emptyList == expectedList);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position points to the forward end position.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementIsInsertedAtTheEndWhenInsertionPositionPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    List<int> inputList(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = inputList.GetIterator(1);
    List<int>::ListIterator itLast = inputList.GetIterator(3);
    List<int>::ListIterator POSITION = commonList.GetLast();
    ++POSITION;

    // [Execution]
    commonList.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(3);
    List<int>::ListIterator itLast = commonList.GetLast();

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetFirst();
    List<int>::ListIterator itLast = commonList.GetIterator(2);

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetIterator(3);

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that all elements of the list can be removed.
/// </summary>
ZTEST_CASE ( RemoveRange1_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int> expectedList;
    List<int>::ListIterator itFirst = commonList.GetFirst();
    List<int>::ListIterator itLast = commonList.GetLast();

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = itFirst;

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
ZTEST_CASE ( RemoveRange1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));

    List<int>::ListIterator itFirst = commonList.GetIterator(1);
    List<int>::ListIterator itLast = commonList.GetIterator(3);

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of each element is called when it is removed.
/// </summary>
ZTEST_CASE ( RemoveRange1_DestructorOfEachElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    List<CallCounter>::ListIterator itFirst = commonList.GetIterator(1);
    List<CallCounter>::ListIterator itLast = commonList.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    commonList.RemoveRange(itFirst, itLast);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( RemoveRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first element points to the end position.
/// </summary>
ZTEST_CASE ( RemoveRange1_AssertionFailsWhenFirstElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last element points to the end position.
/// </summary>
ZTEST_CASE ( RemoveRange1_AssertionFailsWhenLastElementIsEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int>::ListIterator itFirst = commonList.GetLast();
    List<int>::ListIterator itLast = commonList.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(itFirst, itLast);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the list.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 3U;
    const puint_z LAST = 5U;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the list.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = 2U;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that all elements of the list can be removed.
/// </summary>
ZTEST_CASE ( RemoveRange2_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    List<int> expectedList;
    const puint_z FIRST = 0;
    const puint_z LAST = commonList.GetCount() - 1U;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    List<int> expectedList(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = FIRST;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(commonList == expectedList);
}

/// <summary>
/// Checks that count of elements in the list decreases after they are removed.
/// </summary>
ZTEST_CASE ( RemoveRange2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    puint_z uCount = commonList.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of each element is called when it is removed.
/// </summary>
ZTEST_CASE ( RemoveRange2_DestructorOfEachElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    List<CallCounter> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const puint_z FIRST = 1U;
    const puint_z LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    commonList.RemoveRange(FIRST, LAST);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( RemoveRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the list.
/// </summary>
ZTEST_CASE ( RemoveRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = commonList.GetCount();
    const puint_z LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the list
/// </summary>
ZTEST_CASE ( RemoveRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    List<int> commonList(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = commonList.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        commonList.RemoveRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks if the method returns the correct number of elements in the list.
/// </summary>
ZTEST_CASE ( GetCount_MethodReturnsZeroWithEmptyList_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    puint_z uReturnedValue = 0;
    const puint_z EXPECTED_VALUE = 0;
    List<u64_z> list(LIST_CAPACITY);

    // [Execution]
    uReturnedValue = list.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL( uReturnedValue, EXPECTED_VALUE );
}

/// <summary>
/// Checks if the method returns true when the list is empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsTrueWhenEmptyList_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const bool LIST_IS_EMPTY = true;
    bool bIsEmptyList = false;
    List<u64_z> list(LIST_CAPACITY);

    // [Execution]
    bIsEmptyList = list.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmptyList, LIST_IS_EMPTY );
}

/// <summary>
/// Checks if the method returns false when the list is not empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsFalseWhenNoEmptyList_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 1;
    const puint_z LIST_COUNT_ORIGIN = 1;
    const bool LIST_IS_EMPTY = false;
    bool bIsEmptyList = true;
    List<u64_z> list = List<u64_z>(LIST_CAPACITY);

    for(puint_z uIndex = 0; uIndex < LIST_COUNT_ORIGIN; uIndex++)
    {
        list.Add(uIndex + 10);
    }

    // [Execution]
    bIsEmptyList = list.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL( bIsEmptyList, LIST_IS_EMPTY );
}

/// <sumary>
/// Returns the capacity of the list.
/// </sumary>
ZTEST_CASE( GetCapacity_ReturnsTheCapacityOfTheList_Test )
{
    // [Preparation]
    const puint_z LIST_CAPACITY = 5;
    const puint_z EXPECTED_CAPACITY = LIST_CAPACITY;
    List<u64_z> list(LIST_CAPACITY);

    // [Execution]
    puint_z uCapacity = list.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL( uCapacity, EXPECTED_CAPACITY );
}


// End - Test Suite: List

ZTEST_SUITE_END()
