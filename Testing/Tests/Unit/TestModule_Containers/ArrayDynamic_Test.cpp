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

#include "ZContainers/ArrayDynamic.h"

#include "CallCounter.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::CallCounter;


ZTEST_SUITE_BEGIN( ArrayDynamic_TestSuite )

/// <summary>
/// Checks that an empty array is correctly created.
/// </summary>
ZTEST_CASE ( Constructor1_CreatesAnEmptyArray_Test )
{
    // [Preparation]
    const bool IS_EMPTY = true;

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    
    // [Verification]
    bool bIsEmpty = arDynamicArray.IsEmpty();

    BOOST_CHECK_EQUAL(bIsEmpty, IS_EMPTY);
}

/// <summary>
/// Checks that the capacity is not zero by default.
/// </summary>
ZTEST_CASE ( Constructor1_CapacityIsNotZero_Test )
{
    // [Preparation]
    const puint_z ZERO = 0;

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_NE(uCapacity, ZERO);
}

/// <summary>
/// Checks that an empty array is correctly created.
/// </summary>
ZTEST_CASE ( Constructor2_CreatesAnEmptyArray_Test )
{
    // [Preparation]
    const bool IS_EMPTY = true;
    const puint_z INPUT_CAPACITY = 3;
    
	// [Execution]
    ArrayDynamic<int> arDynamicArray(INPUT_CAPACITY);;
    
    // [Verification]
    bool bIsEmpty = arDynamicArray.IsEmpty();

    BOOST_CHECK_EQUAL(bIsEmpty, IS_EMPTY);
}

/// <summary>
/// Checks that the initial capacity is set correctly.
/// </summary>
ZTEST_CASE ( Constructor2_CapacityIsSetCorrectly_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 3;

	// [Execution]
    ArrayDynamic<int> arDynamicArray(EXPECTED_CAPACITY);
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input capacity equals zero.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenInputCapacityEqualsZero_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const puint_z ZERO_CAPACITY = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayDynamic<int> arDynamicArray(ZERO_CAPACITY);;
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
/// Checks that the capacity is not zero when the input initial capacity was equal to zero.
/// </summary>
ZTEST_CASE ( Constructor2_CapacityIsNotZeroWhenInputCapacityEqualsZero_Test )
{
    // [Preparation]
    const puint_z ZERO_CAPACITY = 0;

	// [Execution]
    ArrayDynamic<int> arDynamicArray(ZERO_CAPACITY);;
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_NE(uCapacity, ZERO_CAPACITY);
}

#endif

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
ZTEST_CASE ( Constructor3_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    puint_z uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array.
/// </summary>
ZTEST_CASE ( Constructor3_CapacityEqualsInputArrayCount_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every element is called.
/// </summary>
ZTEST_CASE ( Constructor3_CopyConstructorOfEveryElementIsCalled_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);

    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();
    CallCounter::ResetCounters();

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCopyConstructorsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorsCalled, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
ZTEST_CASE ( Constructor3_ElementsAreCopiedInOrder_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const bool ARE_EQUAL = true;

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
ZTEST_CASE ( Constructor4_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arOriginalArray(5);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    puint_z uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array.
/// </summary>
ZTEST_CASE ( Constructor4_CapacityEqualsInputArrayCount_Test )
{
    // [Preparation]
    ArrayDynamic<int> arOriginalArray(5);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every element is called.
/// </summary>
ZTEST_CASE ( Constructor4_CopyConstructorOfEveryElementIsCalled_Test )
{
    // [Preparation]
    ArrayDynamic<CallCounter> arOriginalArray;
    arOriginalArray.Add(CallCounter());
    arOriginalArray.Add(CallCounter());
    arOriginalArray.Add(CallCounter());
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();
    CallCounter::ResetCounters();

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCopyConstructorsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorsCalled, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the amount of elements in the resultant array equals zero when input array is empty.
/// </summary>
ZTEST_CASE ( Constructor4_ElementCountIsZeroAfterCopyingEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arOriginalArray;
    const puint_z ZERO_COUNT = 0;

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    puint_z uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ZERO_COUNT);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
ZTEST_CASE ( Constructor4_ElementsAreCopiedInOrder_Test )
{
    // [Preparation]
    ArrayDynamic<int> arOriginalArray(3U);
    arOriginalArray.Add(1);
    arOriginalArray.Add(2);
    arOriginalArray.Add(3);
    const bool ARE_EQUAL = true;

	// [Execution]
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks if the instance is correctly constructed when it receives a common array and its size.
/// </summary>
ZTEST_CASE ( Constructor5_ItIsCorrectlyConstructedFromCommonArray_Test )
{
    // [Preparation]
    const unsigned int ARRAY_SIZE = 3;
    const char SOURCE_ARRAY[ARRAY_SIZE] = {0, 1, 2};

    // [Execution]
    ArrayDynamic<char> arArray(SOURCE_ARRAY, ARRAY_SIZE);

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
ZTEST_CASE ( Constructor5_AssertionFailsWhenArrayIsNull_Test )
{
    // [Preparation]
    const int* NULL_ARRAY = null_z;
    const unsigned int NON_ZERO_SIZE = 3;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        ArrayDynamic<int> arArray = ArrayDynamic<int>(NULL_ARRAY, NON_ZERO_SIZE);
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
ZTEST_CASE ( Constructor5_AssertionFailsWhenCountIsZero_Test )
{
    // [Preparation]
    const int SOURCE_ARRAY[3] = {0, 1, 2};
    const unsigned int ZERO_SIZE = 0;
    const bool ASSERTION_FAILED = true;

    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        ArrayDynamic<int> arArray = ArrayDynamic<int>(SOURCE_ARRAY, ZERO_SIZE);
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
/// Checks that all he elements are properly copied when the resident array is not empty.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_ElementsAreProperlyCopiedWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    int arExpectedArrayElements[] = {4, 5, 6};
    ArrayFixed<int> arExpectedArray(arExpectedArrayElements, 3U);

    bool ARE_EQUAL = true;

	// [Execution]
    arDynamicArray = arExpectedArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arExpectedArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arExpectedArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array when it is greater than the resident array.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_CapacityEqualsInputArrayCountWhenItIsGreaterThanResidentArray_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every new element is called when copying a bigger array.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_CopyConstructorOfEveryNewElementIsCalledWhenCopyingBiggerArray_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[1];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 1U);
    CallCounter arBiggerArrayElements[3];
    ArrayFixed<CallCounter> arBiggerArray(arBiggerArrayElements, 3U);
    const puint_z NEW_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    puint_z uCopyConstructorIsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorIsCalled, NEW_ELEMENTS);
}

/// <summary>
/// Checks that the assignment operator of every existing element is called.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_AssignmentOperatorOfEveryExistingElementIsCalled_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[2];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 2U);
    CallCounter arBiggerArrayElements[3];
    ArrayFixed<CallCounter> arBiggerArray(arBiggerArrayElements, 3U);
    const puint_z EXISTING_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    puint_z uAssignmentOperatorIsCalled = CallCounter::GetAssignmentCallsCount();
    BOOST_CHECK_EQUAL(uAssignmentOperatorIsCalled, EXISTING_ELEMENTS);
}

/// <summary>
/// Checks that the destructor of every exceeding element is called when copying a smaller array.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_DestructorOfElementsIsCalledWhenCopyingSmallerArray_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);
    CallCounter arSmallerArrayElements[1];
    ArrayFixed<CallCounter> arSmallerArray(arSmallerArrayElements, 1U);
    const puint_z EXCEEDING_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arSmallerArray;
    
    // [Verification]
    puint_z uDestructorIsCalled = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorIsCalled, EXCEEDING_ELEMENTS);
}

/// <summary>
/// Checks that the capacity of the resident array does not change when assigned to smaller array.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_CapacityDoesNotChangeWhenAssigningToSmallerArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    int arNonEmptyArrayElements[] = {1, 2, 3};
    int arSmallerArrayElements[] = {1, 2};
    ArrayDynamic<int> arNonEmptyArray(ArrayFixed<int>(arNonEmptyArrayElements, 3U));
    ArrayFixed<int> arSmallerArray(arSmallerArrayElements, 2U);
    const puint_z ORIGINAL_CAPACITY = arNonEmptyArray.GetCapacity();

	// [Execution]
    arNonEmptyArray = arSmallerArray;
    
    // [Verification]
    puint_z uCapacity = arNonEmptyArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_ElementsAreCopiedInOrder_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    const bool ARE_EQUAL = true;

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that it returns a reference to the resident array.
/// </summary>
ZTEST_CASE ( AssignmentOperator1_ReturnsReferenceToResidentArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    ArrayDynamic<int> arNonEmptyArray;

    // [Execution]
    ArrayDynamic<int>& referenceToResult = arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    BOOST_CHECK_EQUAL(&referenceToResult, &arNonEmptyArray);
}

/// <summary>
/// Checks that the amount of elements in the resultant array equals zero when input array is empty.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_ElementCountIsZeroAfterCopyingEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    const puint_z ZERO_COUNT = 0;

    // [Preparation]
    int arNonEmptyArrayElements[] = {1, 2, 3};
    ArrayDynamic<int> arNonEmptyArray(ArrayFixed<int>(arNonEmptyArrayElements, 3U));

	// [Execution]
    arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    puint_z uCount = arNonEmptyArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ZERO_COUNT);
}

/// <summary>
/// Checks that all he elements are properly copied when the resident array is not empty.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_ElementsAreProperlyCopiedWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    ArrayDynamic<int> arDynamicArray(arOriginalArray);
    int arExpectedArrayElements[] = {4, 5, 6};
    ArrayDynamic<int> arExpectedArray(ArrayFixed<int>(arExpectedArrayElements, 3U));

    bool ARE_EQUAL = true;

	// [Execution]
    arDynamicArray = arExpectedArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arExpectedArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arExpectedArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that the amount of elements in the source array and the array copy are the same.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_ElementCountIsCorrectAfterCopyingCommonArray_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayDynamic<int> arOriginalArray(ArrayFixed<int>(arOriginalArrayElements, 3U));
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCount = arDynamicArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the capacity of the resultant array equals the element count of the input array when it is greater than the resident array.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_CapacityEqualsInputArrayCountWhenItIsGreaterThanResidentArray_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayDynamic<int> arOriginalArray(ArrayFixed<int>(arOriginalArrayElements, 3U));
    const puint_z ORIGINAL_COUNT = arOriginalArray.GetCount();

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of every new element is called when copying a bigger array.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_CopyConstructorOfEveryNewElementIsCalledWhenCopyingBiggerArray_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[1];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 1U);
    CallCounter arBiggerArrayElements[3];
    ArrayDynamic<CallCounter> arBiggerArray(ArrayFixed<CallCounter>(arBiggerArrayElements, 3U));
    const puint_z NEW_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    puint_z uCopyConstructorIsCalled = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorIsCalled, NEW_ELEMENTS);
}

/// <summary>
/// Checks that the assignment operator of every existing element is called.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_AssignmentOperatorOfEveryExistingElementIsCalled_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[2];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 2U);
    CallCounter arBiggerArrayElements[3];
    ArrayDynamic<CallCounter> arBiggerArray(ArrayFixed<CallCounter>(arBiggerArrayElements, 3U));
    const puint_z EXISTING_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arBiggerArray;
    
    // [Verification]
    puint_z uAssignmentOperatorIsCalled = CallCounter::GetAssignmentCallsCount();
    BOOST_CHECK_EQUAL(uAssignmentOperatorIsCalled, EXISTING_ELEMENTS);
}

/// <summary>
/// Checks that the destructor of every exceeding element is called when copying a smaller array.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_DestructorOfElementsIsCalledWhenCopyingSmallerArray_Test )
{
    // [Preparation]
    CallCounter arOriginalArrayElements[3];
    ArrayFixed<CallCounter> arOriginalArray(arOriginalArrayElements, 3U);
    CallCounter arSmallerArrayElements[1];
    ArrayDynamic<CallCounter> arSmallerArray(ArrayFixed<CallCounter>(arSmallerArrayElements, 1U));
    const puint_z EXCEEDING_ELEMENTS = 2U;

	// [Execution]
    ArrayDynamic<CallCounter> arDynamicArray(arOriginalArray);
    CallCounter::ResetCounters();
    arDynamicArray = arSmallerArray;
    
    // [Verification]
    puint_z uDestructorIsCalled = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorIsCalled, EXCEEDING_ELEMENTS);
}

/// <summary>
/// Checks that the capacity of the resident array does not change when assigned to smaller array.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_CapacityDoesNotChangeWhenAssigningToSmallerArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    int arNonEmptyArrayElements[] = {1, 2, 3};
    int arSmallerArrayElements[] = {1, 2};
    ArrayDynamic<int> arNonEmptyArray(ArrayFixed<int>(arNonEmptyArrayElements, 3U));
    ArrayDynamic<int> arSmallerArray(ArrayFixed<int>(arSmallerArrayElements, 2U));
    const puint_z ORIGINAL_CAPACITY = arNonEmptyArray.GetCapacity();

	// [Execution]
    arNonEmptyArray = arSmallerArray;
    
    // [Verification]
    puint_z uCapacity = arNonEmptyArray.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, ORIGINAL_CAPACITY);
}

/// <summary>
/// Checks that elements are copied in the same order.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_ElementsAreCopiedInOrder_Test )
{
    // [Preparation]
    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayDynamic<int> arOriginalArray(ArrayFixed<int>(arOriginalArrayElements, 3U));
    const bool ARE_EQUAL = true;

	// [Execution]
    ArrayDynamic<int> arDynamicArray;
    arDynamicArray = arOriginalArray;
    
    // [Verification]
    bool bAreEqual = true;

    for(puint_z i = 0; i < arOriginalArray.GetCount(); ++i)
        bAreEqual = bAreEqual && (arOriginalArray[i] == arDynamicArray[i]);

    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that it returns a reference to the resident array.
/// </summary>
ZTEST_CASE ( AssignmentOperator2_ReturnsReferenceToResidentArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    ArrayDynamic<int> arNonEmptyArray;

    // [Execution]
    ArrayDynamic<int>& referenceToResult = arNonEmptyArray = arEmptyArray;
    
    // [Verification]
    BOOST_CHECK_EQUAL(&referenceToResult, &arNonEmptyArray);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
ZTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 4U;
    ArrayDynamic<int> arDynamicArray(1U);

    // [Execution]
    arDynamicArray.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = arDynamicArray.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
ZTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    unsigned int arOriginalArrayElements[] = {0, 1, 2};
    ArrayFixed<unsigned int> arOriginalArray(arOriginalArrayElements, 3U);
    ArrayDynamic<unsigned int> arDynamicArray(arOriginalArray);

    const bool ELEMENTS_ARE_THE_SAME = true;
    const puint_z INPUT_CAPACITY = 20U;

    // [Execution]
    arDynamicArray.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(puint_z i = 0; i < arDynamicArray.GetCount(); ++i)
        bElementsAreTheSame = bElementsAreTheSame && (arDynamicArray[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
ZTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 1U;
    const puint_z EXPECTED_CAPACITY = 3U;

    int arOriginalArrayElements[] = {1, 2, 3};
    ArrayFixed<int> arOriginalArray(arOriginalArrayElements, 3U);
    ArrayDynamic<int> arDynamicArray(arOriginalArray);

    const int* ORIGINAL_FIRST_ELEMENT_ADDRESS = &arDynamicArray[0];

    // [Execution]
    arDynamicArray.Reserve(INPUT_CAPACITY);

    // [Verification]
    puint_z uCapacity = arDynamicArray.GetCapacity();
    int* pFirstElementAddress = &arDynamicArray[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements can be added to empty arrays.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedToEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( Add_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullArray.Add(ELEMENT_VALUE);

    // [Verification]
    puint_z uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when arrays are full.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenArrayIsFull_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arFullArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arFullArray[3], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Add(ELEMENT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
ZTEST_CASE ( Add_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 1;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arCommonArray(INITIAL_CAPACITY);

    // [Execution]
    arCommonArray.Add(ELEMENT_VALUE);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
ZTEST_CASE ( Add_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<CallCounter> arCommonArray(INITIAL_CAPACITY);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Add(newElement);

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
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const ArrayDynamic<int>::ConstArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const ArrayDynamic<int>::ConstArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( Insert1_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const ArrayDynamic<int>::ConstArrayIterator POSITION = arFullArray.GetFirst();

    // [Execution]
    arFullArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
ZTEST_CASE ( Insert1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const ArrayDynamic<int>::ConstArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
ZTEST_CASE ( Insert1_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<CallCounter> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const ArrayDynamic<CallCounter>::ConstArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Insert(newElement, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Insert1_AssertionFailsWhenIteratorSVectorArraysToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    ArrayDynamic<int>::ConstArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, ITERATOR_END);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is invalid.
/// </summary>
ZTEST_CASE ( Insert1_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    ArrayDynamic<int>::ArrayIterator ITERATOR = arCommonArray.GetLast();
    arCommonArray.Remove(ITERATOR);
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, ITERATOR);
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
/// Checks that elements can be inserted into empty arrays.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    ArrayDynamic<int>::ConstArrayIterator ITERATOR = arEmptyArray.GetFirst();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Insert(ELEMENT_VALUE, ITERATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Insert1_ElementIsInsertedAtTheEndWhenIteratorSVectorArraysToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    ArrayDynamic<int>::ConstArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, ITERATOR_END);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( Insert2_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    arFullArray.Add(0);
    arFullArray.Add(0);
    const int ELEMENT_VALUE = 1;
    const puint_z POSITION = 0;

    // [Execution]
    arFullArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCapacity =  arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
ZTEST_CASE ( Insert2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    const int ELEMENT_VALUE = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
ZTEST_CASE ( Insert2_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<CallCounter> arCommonArray(INITIAL_CAPACITY);
    arCommonArray.Add(CallCounter());
    CallCounter newElement;
    CallCounter::ResetCounters();
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Insert(newElement, POSITION);

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
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const puint_z OUT_OF_BOUNDS_INDEX = arCommonArray.GetCount();
    const bool ASSERTION_FAILED = true;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Insert(ELEMENT_VALUE, OUT_OF_BOUNDS_INDEX);
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
/// Checks that elements can be inserted into empty arrays.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    const puint_z POSITION = 0;
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arEmptyArray.Insert(ELEMENT_VALUE, POSITION);

    // [Verification]
    BOOST_CHECK_EQUAL(arEmptyArray[0], ELEMENT_VALUE);
}

/// <summary>
/// Checks that elements are inserted at the end when the index is out of bounds.
/// </summary>
ZTEST_CASE ( Insert2_ElementIsInsertedAtTheEndWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const puint_z INDEX_OUT_OF_BOUNDS = arCommonArray.GetCount();
    const int ELEMENT_VALUE = 1;

    // [Execution]
    arCommonArray.Insert(ELEMENT_VALUE, INDEX_OUT_OF_BOUNDS);

    // [Verification]
    BOOST_CHECK_EQUAL(arCommonArray[1], ELEMENT_VALUE);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
ZTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
ZTEST_CASE ( Remove1_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
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
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
ZTEST_CASE ( Remove1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
ZTEST_CASE ( Remove1_DestructorOfElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    ArrayDynamic<CallCounter> arCommonArray;
    arCommonArray.Add(CallCounter());
    const ArrayDynamic<CallCounter>::ArrayIterator POSITION = arCommonArray.GetFirst();
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to the forward end position.
/// </summary>
ZTEST_CASE ( Remove1_AssertionFailsWhenIteratorSVectorArraysToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    ArrayDynamic<int>::ArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(ITERATOR_END);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is invalid.
/// </summary>
ZTEST_CASE ( Remove1_AssertionFailsWhenInteratorIsInvalid_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    ArrayDynamic<int>::ArrayIterator ITERATOR = arCommonArray.GetLast();
    arCommonArray.Remove(ITERATOR);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(ITERATOR);
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
ZTEST_CASE ( Remove1_NothingHappensWhenIteratorSVectorArraysToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const puint_z EXPECTED_COUNT = arCommonArray.GetCount();
    ArrayDynamic<int>::ArrayIterator ITERATOR_END = arCommonArray.GetLast();
    ++ITERATOR_END;

    // [Execution]
    arCommonArray.Remove(ITERATOR_END);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
ZTEST_CASE ( Remove1_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    const puint_z EXPECTED_COUNT = 0;
    ArrayDynamic<int>::ArrayIterator ITERATOR = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.Remove(ITERATOR);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    const puint_z POSITION = arCommonArray.GetCount() - 1U;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( Remove2_ElementIsCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const bool ELEMENT_DOES_NOT_EXIST = true;
    const int ELEMENT_VALUE = 1;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(ELEMENT_VALUE);
    arCommonArray.Add(0);
    const puint_z POSITION = 1;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    bool bElementDoesNotExist = !arCommonArray.Contains(ELEMENT_VALUE);
    BOOST_CHECK_EQUAL(bElementDoesNotExist, ELEMENT_DOES_NOT_EXIST);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
ZTEST_CASE ( Remove2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 2;
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of the element is called when it is removed.
/// </summary>
ZTEST_CASE ( Remove2_DestructorOfElementIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 1;
    ArrayDynamic<CallCounter> arCommonArray;
    arCommonArray.Add(CallCounter());
    const puint_z POSITION = 0;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Remove(POSITION);

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
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const puint_z POSITION = arCommonArray.GetCount();
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.Remove(POSITION);
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
    ArrayDynamic<int> arCommonArray;
    arCommonArray.Add(0);
    const puint_z EXPECTED_COUNT = arCommonArray.GetCount();
    const puint_z POSITION = arCommonArray.GetCount();

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
ZTEST_CASE ( Remove2_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    const puint_z EXPECTED_COUNT = 0;
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.Remove(POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

#endif

/// <summary>
/// Checks that nothing happens when the array is empty.
/// </summary>
ZTEST_CASE ( Clear_NothingHappensWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the array is full.
/// </summary>
ZTEST_CASE ( Clear_AllElemensAreRemovedWhenArrayIsFull_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that all the elements are removed when the array contains some elements.
/// </summary>
ZTEST_CASE ( Clear_AllElementsAreRemovedWhenArrayContainsSomeElements_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(3U);
    arCommonArray.Add(0);
    arCommonArray.Add(0);
    const puint_z EXPECTED_COUNT = 0;

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
ZTEST_CASE ( Clear_DestructorIsCalledForEveryElement_Test )
{
    // [Preparation]
    ArrayDynamic<CallCounter> arCommonArray(3U);
    arCommonArray.Add(CallCounter());
    arCommonArray.Add(CallCounter());
    const puint_z EXPECTED_CALLS = 2;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Clear();

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the capacity of the destination allocator is increased when it is lower than the capacity of the source.
/// </summary>
ZTEST_CASE ( Clone_CapacityOfDestinationIsIncreasedWhenItIsLowerThanCapacityOfSource_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    ArrayDynamic<int> arDestination;
    const puint_z INITIAL_CAPACITY = arDestination.GetCapacity();
    const puint_z EXPECTED_CAPACITY = arCommonArray.GetCapacity();

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    puint_z uCapacity = arDestination.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that no elements are copied when the source array is empty.
/// </summary>
ZTEST_CASE ( Clone_NoElementsAreCopiedWhenSourceArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> arCommonArray;
    ArrayDynamic<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    puint_z uSourceCount = arCommonArray.GetCount();
    puint_z uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
}

/// <summary>
/// Checks that all elements are correctly copied when the source array is partially full.
/// </summary>
ZTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenSourceArrayIsPartiallyFull_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    ArrayDynamic<int> arCommonArray(10U);
    for(int i = 0; i < 5; ++i)
        arCommonArray.Add(i);
    ArrayDynamic<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 5; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    puint_z uSourceCount = arCommonArray.GetCount();
    puint_z uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that all elements are correctly copied when the source array is full.
/// </summary>
ZTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenSourceArrayIsFull_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    ArrayDynamic<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    ArrayDynamic<int> arDestination;

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 10; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    puint_z uSourceCount = arCommonArray.GetCount();
    puint_z uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that all elements are correctly copied when the destination array is not empty.
/// </summary>
ZTEST_CASE ( Clone_ElementsAreCorrectlyCopiedWhenDestinationIsNotEmpty_Test )
{
    // [Preparation]
    const bool ARE_EQUAL = true;
    ArrayDynamic<int> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(i);
    ArrayDynamic<int> arDestination;
    for(int i = 10; i < 15; ++i)
        arDestination.Add(i);

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    bool bAreEqual = true;

    for(int i = 0; i < 10; ++i)
        bAreEqual = bAreEqual && (arCommonArray[i] == arDestination[i]);

    puint_z uSourceCount = arCommonArray.GetCount();
    puint_z uDestinationCount = arDestination.GetCount();

    BOOST_CHECK_EQUAL(uSourceCount, uDestinationCount);
    BOOST_CHECK_EQUAL(bAreEqual, ARE_EQUAL);
}

/// <summary>
/// Checks that neither the destructor nor the copy constructor of any element is called when cloning.
/// </summary>
ZTEST_CASE ( Clone_NeitherDestructorNorConstructorsAreCalledWhenCloning_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 0;
    ArrayDynamic<CallCounter> arCommonArray(10U);
    for(int i = 0; i < 10; ++i)
        arCommonArray.Add(CallCounter());
    ArrayDynamic<CallCounter> arDestination;
    for(int i = 10; i < 15; ++i)
        arCommonArray.Add(CallCounter());

    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.Clone(arDestination);

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();

    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <sumary>
/// Checks that it returns False when the array is empty.
/// </sumary>
ZTEST_CASE( Contains_ReturnsFalseWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    ArrayDynamic<u32_z> dynamicArray;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = dynamicArray.Contains(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns ELEMENT_NOT_FOUND when the array is empty.
/// </sumary>
ZTEST_CASE( IndexOf1_ReturnsElementNotFoundWhenArrayIsEmpty_Test )
{
    // [Preparation]
    const u32_z INPUT_ELEMENT = 2U;
    ArrayDynamic<u32_z> dynamicArray;
    const puint_z EXPECTED_RESULT = ArrayDynamic<u32_z>::ELEMENT_NOT_FOUND;

    // [Execution]
    puint_z uResult = dynamicArray.IndexOf(INPUT_ELEMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that elements can be added to empty arrays.
/// </summary>
ZTEST_CASE ( AddRange_ElementIsCorrectlyAddedToEmptyArray_Test )
{
    // [Preparation]
    ArrayDynamic<int> arEmptyArray;
    const int EXPECTED_VALUES[] = {2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arEmptyArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( AddRange_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arFullArray.AddRange(itFirst, itLast);

    // [Verification]
    puint_z uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly added when arrays are full.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenArrayIsFull_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 3U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(8);
    arFullArray.Add(9);
    arFullArray.Add(0);
    const int EXPECTED_VALUES[] = {8, 9, 0, 2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);

    // [Execution]
    arFullArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arFullArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedAtTheEnd_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(2);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(4);

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the count of elements of the array is increased after some elements are added.
/// </summary>
ZTEST_CASE ( AddRange_CountIsIncreasedAfterAddingElements_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    ArrayDynamic<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    
    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the elements is called when adding them to the array.
/// </summary>
ZTEST_CASE ( AddRange_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    ArrayDynamic<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    ArrayDynamic<CallCounter>::ArrayIterator itFirst = arInputArray.GetIterator(0);
    ArrayDynamic<CallCounter>::ArrayIterator itLast = arInputArray.GetIterator(2);
    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 3};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(2);
    ArrayDynamic<int>::ArrayIterator itLast = itFirst;

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using elements of the same array.
/// </summary>
ZTEST_CASE ( AddRange_ElementRangeIsCorrectlyAddedWhenUsingElementsOfTheSameArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.AddRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( AddRange_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.AddRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const puint_z POSITION = 1;


    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( InsertRange1_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const puint_z POSITION = 0;
    
    // [Execution]
    arFullArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
ZTEST_CASE ( InsertRange1_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    ArrayDynamic<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const puint_z POSITION = 0;
    
    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
ZTEST_CASE ( InsertRange1_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    ArrayDynamic<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    ArrayDynamic<CallCounter>::ArrayIterator itFirst = arInputArray.GetIterator(0);
    ArrayDynamic<CallCounter>::ArrayIterator itLast = arInputArray.GetIterator(2);
    const puint_z POSITION = 0;

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(2);
    ArrayDynamic<int>::ArrayIterator itLast = itFirst;
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    const puint_z POSITION = 0;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetFirst();
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itLast;
    const puint_z POSITION = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the insertion position is not lower than the number of elements in the array.
/// </summary>
ZTEST_CASE ( InsertRange1_AssertionFailsWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    const puint_z POSITION = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
/// Checks that elements can be inserted into empty arrays.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    ArrayDynamic<int> arEmptyArray(5);
    const puint_z POSITION = 0;

    // [Execution]
    arEmptyArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position is not lower than the number of elements in the array.
/// </summary>
ZTEST_CASE ( InsertRange1_ElementIsInsertedAtTheEndWhenInsertionPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const puint_z POSITION = arCommonArray.GetCount();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#endif

/// <summary>
/// Checks that elements can be inserted at the first position.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedAtFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {2, 3, 4, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements can be inserted in between of two existing elements.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementsAreCorrectlyInsertedInBetween_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetIterator(1);

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that the capacity is increased when elements are added to a full array.
/// </summary>
ZTEST_CASE ( InsertRange2_CapacityIsIncreasedWhenAddingElementsToFullArray_Test )
{
    // [Preparation]
    const puint_z INITIAL_CAPACITY = 1U;
    ArrayDynamic<int> arFullArray(INITIAL_CAPACITY);
    arFullArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const ArrayDynamic<int>::ArrayIterator POSITION = arFullArray.GetFirst();
    
    // [Execution]
    arFullArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCapacity = arFullArray.GetCapacity();
    BOOST_CHECK(uCapacity > INITIAL_CAPACITY);
}

/// <summary>
/// Checks that the count of elements of the array is increased after an element is added.
/// </summary>
ZTEST_CASE ( InsertRange2_CountIsIncreasedAfterAddingAnElement_Test )
{
    // [Preparation]
    const puint_z INITIAL_COUNT = 1U;
    ArrayDynamic<int> arCommonArray(3);
    arCommonArray.Add(0);
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();
    
    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
    BOOST_CHECK(uCount > INITIAL_COUNT);
}

/// <summary>
/// Checks that the copy constructor of the element is called when adding it to the array.
/// </summary>
ZTEST_CASE ( InsertRange2_CopyConstructorIsCalledForAddedElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 3;
    const CallCounter COMMON_VALUES[] = {CallCounter()};
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const CallCounter ELEMENT_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    ArrayDynamic<CallCounter> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(CallCounter));
    ArrayDynamic<CallCounter>::ArrayIterator itFirst = arInputArray.GetIterator(0);
    ArrayDynamic<CallCounter>::ArrayIterator itLast = arInputArray.GetIterator(2);
    const ArrayDynamic<CallCounter>::ArrayIterator POSITION = arCommonArray.GetFirst();

    CallCounter newElement;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    puint_z uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenBothIteratorsAreEqual_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(2);
    ArrayDynamic<int>::ArrayIterator itLast = itFirst;
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly added at the end of a common array when using all the elements of another array.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementRangeIsCorrectlyAddedWhenUsingAllTheElementsOfAnotherArray_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5, 0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( InsertRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetFirst();
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itFirst;
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ++itLast;
    const ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(ELEMENT_VALUES, sizeof(ELEMENT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetLast();
    ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetLast();
    ++POSITION;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.InsertRange(itFirst, itLast, POSITION);
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
/// Checks that elements can be inserted into empty arrays.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementIsInsertedIntoEmptyArray_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    ArrayDynamic<int> arEmptyArray(5);
    arEmptyArray.Add(0);
    const ArrayDynamic<int>::ArrayIterator POSITION = arEmptyArray.GetFirst();
    arEmptyArray.Clear();

    // [Execution]
    arEmptyArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arEmptyArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are inserted at the end when the insertion position points to the forward end position.
/// </summary>
ZTEST_CASE ( InsertRange2_ElementIsInsertedAtTheEndWhenInsertionPositionPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2, 2, 3, 4};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const int INPUT_VALUES[] = {1, 2, 3, 4, 5};
    ArrayDynamic<int> arInputArray(INPUT_VALUES, sizeof(INPUT_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arInputArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arInputArray.GetIterator(3);
    ArrayDynamic<int>::ArrayIterator POSITION = arCommonArray.GetLast();
    ++POSITION;

    // [Execution]
    arCommonArray.InsertRange(itFirst, itLast, POSITION);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#endif

/// <summary>
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(3);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetIterator(2);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetIterator(3);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that all elements of the array can be removed.
/// </summary>
ZTEST_CASE ( RemoveRange1_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int> arExpectedArray;
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( RemoveRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = itFirst;

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
ZTEST_CASE ( RemoveRange1_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));

    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetIterator(3);

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
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
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    ArrayDynamic<CallCounter>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<CallCounter>::ArrayIterator itLast = arCommonArray.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.RemoveRange(itFirst, itLast);

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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(itFirst, itLast);
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
/// Checks that elements are correctly removed from the last position of the array.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 3U;
    const puint_z LAST = 5U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed from the first position of the array.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = 2U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when they are in between of two elements.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that all elements of the array can be removed.
/// </summary>
ZTEST_CASE ( RemoveRange2_AllElementsCanBeRemoved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int> arExpectedArray;
    const puint_z FIRST = 0;
    const puint_z LAST = arCommonArray.GetCount() - 1U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( RemoveRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 2, 3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = FIRST;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

/// <summary>
/// Checks that count of elements in the array decreases after they are removed.
/// </summary>
ZTEST_CASE ( RemoveRange2_CountDecreasesAfterRemovingElements_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

    // [Verification]
    puint_z uCount = arCommonArray.GetCount();
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
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));
    const puint_z FIRST = 1U;
    const puint_z LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.RemoveRange(FIRST, LAST);

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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the array.
/// </summary>
ZTEST_CASE ( RemoveRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = arCommonArray.GetCount();
    const puint_z LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the array
/// </summary>
ZTEST_CASE ( RemoveRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.RemoveRange(FIRST, LAST);
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
/// Checks that elements are correctly retrieved from the last position of the array.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(3);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the array.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetIterator(2);
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetIterator(3);
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( GetRange1_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<int>::ArrayIterator itLast = itFirst;
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
ZTEST_CASE ( GetRange1_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    ArrayDynamic<CallCounter>::ArrayIterator itFirst = arCommonArray.GetIterator(1);
    ArrayDynamic<CallCounter>::ArrayIterator itLast = arCommonArray.GetIterator(2);
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    puint_z uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the array can be retrieved.
/// </summary>
ZTEST_CASE ( GetRange1_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int> arExpectedArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));;
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetFirst();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();

    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(itFirst, itLast);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( GetRange1_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetFirst();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();
    ++itFirst;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
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
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int>::ArrayIterator itFirst = arCommonArray.GetLast();
    ArrayDynamic<int>::ArrayIterator itLast = arCommonArray.GetLast();
    ++itLast;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(itFirst, itLast);
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
/// Checks that elements are correctly retrieved from the last position of the array.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromLastPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {3, 4, 5};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 3U;
    const puint_z LAST = 5U;

    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved from the first position of the array.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromFirstPosition_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = 2U;
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly retrieved when they are in between of two elements.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyGotFromBetweenTwoElements_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1, 2, 3};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 3U;
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that elements are correctly removed when both positions are the same.
/// </summary>
ZTEST_CASE ( GetRange2_ElementsAreCorrectlyRemovedWhenBothPositionsAreTheSame_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const int EXPECTED_VALUES[] = {1};
    ArrayDynamic<int> arExpectedArray(EXPECTED_VALUES, sizeof(EXPECTED_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = FIRST;
    
    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arReturnedArray == arExpectedArray);
}

/// <summary>
/// Checks that the copy constructor of each element is called when it is copied, at least once.
/// </summary>
ZTEST_CASE ( GetRange2_CopyConstructorOfEachElementIsCalledAtLeastOnce_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CALLS = 2;
    const CallCounter COMMON_VALUES[] = {CallCounter(), CallCounter(), CallCounter()};
    ArrayDynamic<CallCounter> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(CallCounter));

    const puint_z FIRST = 1U;
    const puint_z LAST = 2U;
    CallCounter::ResetCounters();

    // [Execution]
    arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    puint_z uCopyConstructor = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK(uCopyConstructor >= EXPECTED_CALLS);
}

/// <summary>
/// Checks that all elements of the array can be retrieved.
/// </summary>
ZTEST_CASE ( GetRange2_AllElementsCanBeRetrieved_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2, 3, 4, 5};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    ArrayDynamic<int> arExpectedArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 0;
    const puint_z LAST = arCommonArray.GetCount() - 1U;

    // [Execution]
    ArrayDynamic<int> arReturnedArray = arCommonArray.GetRange(FIRST, LAST);

    // [Verification]
    BOOST_CHECK(arCommonArray == arExpectedArray);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the last element is anterior to the first element in the range.
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenLastElementIsAnteriorToFirstElement_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the first position is not lower than the number of elements in the array.
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenFirstPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = arCommonArray.GetCount();
    const puint_z LAST = 2U;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the last position is not lower than the number of elements in the array
/// </summary>
ZTEST_CASE ( GetRange2_AssertionFailsWhenLastPositionIsNotLowerThanCount_Test )
{
    // [Preparation]
    const int COMMON_VALUES[] = {0, 1, 2};
    ArrayDynamic<int> arCommonArray(COMMON_VALUES, sizeof(COMMON_VALUES) / sizeof(int));
    const puint_z FIRST = 1U;
    const puint_z LAST = arCommonArray.GetCount();

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        arCommonArray.GetRange(FIRST, LAST);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: ArrayDynamic
ZTEST_SUITE_END()
