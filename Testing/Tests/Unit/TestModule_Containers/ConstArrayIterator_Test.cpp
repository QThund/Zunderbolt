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
#include "ZContainers/ArrayDynamic.h"

#include "ZContainers/EIterationDirection.h"
#include "ZCommon/Exceptions/AssertException.h"


/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const int nField) : m_nField(nField)
    {
    }

    int m_nField;
};

ZTEST_SUITE_BEGIN( ConstArrayIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the given position when using a common array.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonArray_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    const unsigned int POSITION = 1;
    ArrayFixed<int>::ConstArrayIterator EXPECTED_ITERATOR(&SOURCE_ARRAY, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(&SOURCE_ARRAY, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input array is null.
/// </summary>
ZTEST_CASE ( Constructor_AssertionFailsWhenInputArrayIsNull_Test )
{
    // [Preparation]
    ArrayFixed<int>* SOURCE_ARRAY = null_z;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator INVALID_ITERATOR(SOURCE_ARRAY, 0);
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
/// Checks that the iterator points to the end position (forward iteration) when using an empty array.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyArray_Test )
{
    // [Preparation]
    const ArrayDynamic<int> SOURCE_ARRAY(1U);
    const bool IS_END = true;

	// [Execution]
    ArrayDynamic<int>::ConstArrayIterator iterator(&SOURCE_ARRAY, 0);

    // [Verification]
    bool bIsEndIterationForward = iterator.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

#endif

/// <summary>
/// Checks that the element pointed to by the iterator is returned.
/// </summary>
ZTEST_CASE ( OperatorIndirection_ReturnsTheCorrespondingElement_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = EXPECTED_VALUE;
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = *ITERATOR;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
ZTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (backward iteration).
/// </summary>
ZTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *ITERATOR;
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
/// Checks that the element pointed to by the iterator is returned.
/// </summary>
ZTEST_CASE ( OperatorDereferencing_ReturnsTheCorrespondingElement_Test )
{
    // [Preparation]
    ArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    const int EXPECTED_VALUE = 1;
    SOURCE_ARRAY[1] = TestStructure(EXPECTED_VALUE);
    ArrayFixed<TestStructure>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR++;

	// [Execution]
    int nValue = ITERATOR->m_nField;

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
ZTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    ArrayFixed<TestStructure>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (backward iteration).
/// </summary>
ZTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<TestStructure> SOURCE_ARRAY(3, TestStructure(0));
    ArrayFixed<TestStructure>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_nField;
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
/// Checks that the iterator steps forward properly and returns the previous state.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorPreviousState = iterator++;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END++;
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
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorChangesWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> SOURCE_ARRAY(3);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWaSVectorArrayingToLastEndPosition_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 3;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorPreviousState = iterator--;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END--;
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
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorChangesWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(1, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    --ITERATOR_END;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorCurrentState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[0] = FIRST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorCurrentState = ++iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++ITERATOR_END;
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
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorChangesWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    ArrayDynamic<int> SOURCE_ARRAY(3);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[1] = SECOND_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorCurrentState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWaSVectorArrayingToLastEndPosition_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 3;
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    SOURCE_ARRAY[2] = LAST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    ArrayFixed<int>::ConstArrayIterator iteratorCurrentState = --iterator;
    int currentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(currentElement == LAST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --ITERATOR_END;
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
/// Checks that the iterator changes when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorChangesWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_END(&SOURCE_ARRAY, 0);
    --ITERATOR_END;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ITERATOR_END);
    --iterator;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_END);
}

#endif

/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CommonIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&SOURCE_ARRAY, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&SOURCE_ARRAY, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator = ITERATOR_A;
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
/// Checks that the iterator is not copied when it points to a different array.
/// </summary>
ZTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentArray_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

/// <summary>
/// Checks that it returns True when iterators are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when iterators are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator == ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when iterators are equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when iterators are not equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator != ITERATOR_A;
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
/// Checks that it returns True when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator > ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator < ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator >= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ++ITERATOR_A;
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different array.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ArrayFixed<int>::ConstArrayIterator iterator(&ARRAY_B, 0);
        iterator <= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different array.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentArrays_Test )
{
    // [Preparation]
    ArrayFixed<int> ARRAY_A(3, 0);
    ArrayFixed<int> ARRAY_B(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_A(&ARRAY_A, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_B(&ARRAY_B, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
ZTEST_CASE ( IsEnd1_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    ITERATOR--;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position after the last.
/// </summary>
ZTEST_CASE ( IsEnd1_ReturnsTrueWhenIteratorPointsToPositionAfterLast_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator does not point to an end position.
/// </summary>
ZTEST_CASE ( IsEnd1_ReturnsFalseWhenIteratorDoesNotPointToEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
ZTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveFirst();
    ITERATOR--;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position after the last.
/// </summary>
ZTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionAfterLast_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EIterationDirection::E_Forward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator does not point to an end position.
/// </summary>
ZTEST_CASE ( IsEnd2_ReturnsFalseWhenIteratorDoesNotPointToEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when the array is not empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(10, 0);
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ArrayFixed<int>::ConstArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenArrayIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ORIGINAL_ITERATOR--;

    ArrayFixed<int>::ConstArrayIterator ITERATOR_FIRST(&SOURCE_ARRAY, 0);

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_AssertionFailsWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> EMPTY_ARRAY;
    EMPTY_ARRAY.Add(0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&EMPTY_ARRAY, 0);
    EMPTY_ARRAY.Remove(0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveFirst();
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
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> EMPTY_ARRAY;
    ArrayFixed<int>::ConstArrayIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the array is not empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmpty_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenArrayIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ORIGINAL_ITERATOR(&SOURCE_ARRAY, 0);
    --ORIGINAL_ITERATOR;

    ArrayFixed<int>::ConstArrayIterator ITERATOR_LAST(&SOURCE_ARRAY, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    ArrayFixed<int>::ConstArrayIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the array is empty.
/// </summary>
ZTEST_CASE ( MoveLast_AssertionFailsWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> EMPTY_ARRAY;
    EMPTY_ARRAY.Add(0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&EMPTY_ARRAY, 0);
    EMPTY_ARRAY.Remove(0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveLast();
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
/// Checks that the iterator points to the end position when the array is empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenArrayIsEmpty_Test )
{
    // [Preparation]
    ArrayDynamic<int> EMPTY_ARRAY;
    ArrayFixed<int>::ConstArrayIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator is correctly incremented when the increment is greater than zero.
/// </summary>
ZTEST_CASE ( MoveForward_CommonIteratorIsCorrectlyIncrementedWhenIncrementIsGreaterThanZero_Test )
{
    // [Preparation]
    const int THIRD_ELEMENT_VALUE = 3;
    const int INCREMENT = 2;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = THIRD_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, THIRD_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator is not modified when the increment equals zero.
/// </summary>
ZTEST_CASE ( MoveForward_CommonIteratorDoesNotChangeWhenIncrementIsZero_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 3;
    const int INCREMENT = 0;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the forward end position when the new position is out of bounds.
/// </summary>
ZTEST_CASE ( MoveForward_CommonIteratorPointsToForwardEndPositionWhenNewPositionIsOutOfBounds_Test )
{
    // [Preparation]
    ArrayFixed<int> arSourceArray(3, 0);
    const puint_z INCREMENT = arSourceArray.GetCount();
    const bool EXPECTED_RESULT = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    bool bIsForwardEnd = iterator.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsForwardEnd, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when it was pointing to the backward end position and then was incremented by 1.
/// </summary>
ZTEST_CASE ( MoveForward_CommonIteratorPointsToFirstElementWhenStartsFromBackwardEndPositionAndIsIncrementedByOne_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 5;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    const int INCREMENT = 1;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    int nCurrentElementValue = *iterator;
    BOOST_CHECK_EQUAL(nCurrentElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the forward end position when it was pointing to the backward end position and then was incremented by the size of the array.
/// </summary>
ZTEST_CASE ( MoveForward_CommonIteratorPointsToForwardEndWhenStartsFromBackwardEndPositionAndIsIncrementedByMoreThanCount_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    const puint_z INCREMENT = SOURCE_ARRAY.GetCount() + 1U;
    const bool EXPECTED_RESULT = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&SOURCE_ARRAY, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    iterator.MoveForward(INCREMENT);

    // [Verification]
    bool bIsForwardEnd = iterator.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsForwardEnd, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator points to forward end position.
/// </summary>
ZTEST_CASE ( MoveForward_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    const int INCREMENT = 1;
    const bool ASSERTION_FAILED = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&SOURCE_ARRAY, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        iterator.MoveForward(INCREMENT);
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
/// Checks that the iterator is correctly decremented when the decrement is greater than zero.
/// </summary>
ZTEST_CASE ( MoveBackward_CommonIteratorIsCorrectlyDecrementedWhenDecrementIsGreaterThanZero_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 3;
    const int DECREMENT = 2;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[0] = FIRST_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, FIRST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator is not modified when the decrement equals zero.
/// </summary>
ZTEST_CASE ( MoveBackward_CommonIteratorDoesNotChangeWhenDecrementIsZero_Test )
{
    // [Preparation]
    const int THIRD_ELEMENT_VALUE = 3;
    const int DECREMENT = 0;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = THIRD_ELEMENT_VALUE;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int uElementValue = *iterator;
    BOOST_CHECK_EQUAL(uElementValue, THIRD_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the backward end position when the new position is out of bounds.
/// </summary>
ZTEST_CASE ( MoveBackward_CommonIteratorPointsToBackwardEndPositionWhenNewPositionIsOutOfBounds_Test )
{
    // [Preparation]
    ArrayFixed<int> arSourceArray(3, 0);
    const puint_z DECREMENT = arSourceArray.GetCount();
    const bool EXPECTED_RESULT = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    bool bIsBackwardEnd = iterator.IsEnd(EIterationDirection::E_Backward);
    BOOST_CHECK_EQUAL(bIsBackwardEnd, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the last position when it was pointing to the forward end position and then was decremented by 1.
/// </summary>
ZTEST_CASE ( MoveBackward_CommonIteratorPointsToFirstElementWhenStartsFromForwardEndPositionAndIsIncrementedByOne_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 5;
    ArrayFixed<int> arSourceArray(3, 0);
    arSourceArray[2] = LAST_ELEMENT_VALUE;
    const int DECREMENT = 1;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    int nCurrentElementValue = *iterator;
    BOOST_CHECK_EQUAL(nCurrentElementValue, LAST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the backward end position when it was pointing to the forward end position and then was decremented by the size of the array.
/// </summary>
ZTEST_CASE ( MoveBackward_CommonIteratorPointsToBackwardEndWhenStartsFromForwardEndPositionAndIsDecrementedByMoreThanCount_Test )
{
    // [Preparation]
    ArrayFixed<int> arSourceArray(3, 0);
    const puint_z DECREMENT = arSourceArray.GetCount() + 1U;
    const bool EXPECTED_RESULT = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveLast();
    ++iterator;

	// [Execution]
    iterator.MoveBackward(DECREMENT);

    // [Verification]
    bool bIsBackwardEnd = iterator.IsEnd(EIterationDirection::E_Backward);
    BOOST_CHECK_EQUAL(bIsBackwardEnd, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the backward end position.
/// </summary>
ZTEST_CASE ( MoveBackward_AssertionFailsWhenIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> arSourceArray(3, 0);
    const int DECREMENT = 1;
    const bool ASSERTION_FAILED = true;
    ArrayFixed<int>::ConstArrayIterator iterator(&arSourceArray, 0);
    iterator.MoveFirst();
    --iterator;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        iterator.MoveBackward(DECREMENT);
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
/// Checks that it returns True when iterator points to a common position.
/// </summary>
ZTEST_CASE ( IsValid_ReturnsTrueWhenIteratorPointsToCommonPosition_Test )
{
    // [Preparation]
    ArrayFixed<int> SOURCE_ARRAY(3, 0);
    ArrayFixed<int>::ConstArrayIterator ITERATOR(&SOURCE_ARRAY, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: ConstArrayIterator
ZTEST_SUITE_END()
