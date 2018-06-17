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

ZTEST_SUITE_BEGIN( ConstListIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the given position when using a common list.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonList_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int POSITION = 1;
    List<int>::ConstListIterator EXPECTED_ITERATOR(&SOURCE_LIST, 0);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    List<int>::ConstListIterator iterator(&SOURCE_LIST, POSITION);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input list is null.
/// </summary>
ZTEST_CASE ( Constructor_AssertionFailsWhenInputListIsNull_Test )
{
    // [Preparation]
    List<int>* SOURCE_LIST = null_z;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator INVALID_ITERATOR(SOURCE_LIST, 0);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input position is not lower than the capacity.
/// </summary>
ZTEST_CASE ( Constructor_AssertionFailsWhenInputPositionIsNotLowerThanCapacity_Test )
{
    // [Preparation]
    const unsigned int CAPACITY = 3;
    List<int> SOURCE_LIST(CAPACITY);
    for(unsigned int i = 0; i < CAPACITY; ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator INVALID_ITERATOR(&SOURCE_LIST, INVALID_POSITION);
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
/// Checks that the iterator points to the end position (forward iteration) when using an invalid position.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingInvalidPosition_Test )
{
    // [Preparation]
    const unsigned int NUMBER_OF_ELEMENTS = 3;
    List<int> SOURCE_LIST(NUMBER_OF_ELEMENTS);
    for(unsigned int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    List<int>::ConstListIterator iterator(&SOURCE_LIST, INVALID_POSITION);

    // [Verification]
    bool bIsEndIterationForward = iterator.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty list.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyList_Test )
{
    // [Preparation]
    const List<int> SOURCE_LIST(3);
    const bool IS_END = true;

	// [Execution]
    List<int>::ConstListIterator iterator(&SOURCE_LIST, 0);

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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    const int EXPECTED_VALUE = 1;
    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    const int EXPECTED_VALUE = 1;
    List<TestStructure>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ++ITERATOR;

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
    List<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    List<TestStructure>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<TestStructure> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(TestStructure(i));
    }

    List<TestStructure>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    const int SECOND_ELEMENT_VALUE = 1;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorPreviousState = iterator++;

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
    const int FIRST_ELEMENT_VALUE = 0;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorPreviousState = iterator++;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    List<int>::ConstListIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 1;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorPreviousState = iterator--;

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
    const int LAST_ELEMENT_VALUE = 2;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorPreviousState = iterator--;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    List<int>::ConstListIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 1;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorCurrentState = ++iterator;

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
    const int FIRST_ELEMENT_VALUE = 0;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorCurrentState = ++iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorCurrentState == iterator);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    List<int>::ConstListIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 1;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorCurrentState = --iterator;

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
    const int LAST_ELEMENT_VALUE = 2;
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    List<int>::ConstListIterator iteratorCurrentState = --iterator;
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
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
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_END(&SOURCE_LIST, 0);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    List<int>::ConstListIterator iterator(ITERATOR_END);
    --iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CommonIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&SOURCE_LIST, 0);
    List<int>::ConstListIterator ITERATOR_B(&SOURCE_LIST, 0);
    ++ITERATOR_A;

	// [Execution]
    List<int>::ConstListIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentList_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that the iterator is not copied when it points to a different list.
/// </summary>
ZTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentList_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);

	// [Execution]
    List<int>::ConstListIterator iterator = ITERATOR_B;
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns True when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator, even if the internal position to which the resident iterator is greater.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIteratorEvenIfPositionIsGreater_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    LIST_A.Remove(0);
    LIST_A.Remove(0);
    LIST_A.Add(1);
    LIST_A.Add(1);

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    ITERATOR_A.MoveFirst(); // Internal position: 2
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ITERATOR_B.MoveLast(); // Internal position: 0
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator, even if the internal position to which the resident iterator is lower.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIteratorEvenIfPositionIsLower_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    LIST_A.Remove(0);
    LIST_A.Remove(0);
    LIST_A.Add(1);
    LIST_A.Add(1);

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    ITERATOR_A.MoveFirst(); // Internal position: 2
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ITERATOR_B.MoveLast(); // Internal position: 0
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    ++ITERATOR_A;
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
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
    List<int> LIST_A(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_A, 0);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different list.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        List<int>::ConstListIterator iterator(&LIST_B, 0);
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
/// Checks that it returns False when iterators point to a different list.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentLists_Test )
{
    // [Preparation]
    List<int> LIST_A(3);
    List<int> LIST_B(3);
    for(unsigned int i = 0; i < LIST_A.GetCapacity(); ++i)
    {
        LIST_A.Add(i);
        LIST_B.Add(i);
    }

    List<int>::ConstListIterator ITERATOR_A(&LIST_A, 0);
    List<int>::ConstListIterator ITERATOR_B(&LIST_B, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
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
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the iterator points to the first position when the list is not empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenListIsNotEmpty_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(10);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    List<int>::ConstListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenListIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    ORIGINAL_ITERATOR--;

    List<int>::ConstListIterator ITERATOR_FIRST(&SOURCE_LIST, 0);

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the list is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> EMPTY_ARRAY;
    List<int>::ConstListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    List<int>::ConstListIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the list is not empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenListIsNotEmpty_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    List<int>::ConstListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenListIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ORIGINAL_ITERATOR(&SOURCE_LIST, 0);
    --ORIGINAL_ITERATOR;

    List<int>::ConstListIterator ITERATOR_LAST(&SOURCE_LIST, 0);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    List<int>::ConstListIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the list is empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenListIsEmpty_Test )
{
    // [Preparation]
    List<int> EMPTY_ARRAY;
    List<int>::ConstListIterator END_ITERATOR(&EMPTY_ARRAY, 0);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    List<int>::ConstListIterator ITERATOR(&EMPTY_ARRAY, 0);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that it returns True when iterator points to a common position.
/// </summary>
ZTEST_CASE ( IsValid_ReturnsTrueWhenIteratorPointsToCommonPosition_Test )
{
    // [Preparation]
    List<int> SOURCE_LIST(3);
    for(unsigned int i = 0; i < SOURCE_LIST.GetCapacity(); ++i)
    {
        SOURCE_LIST.Add(i);
    }

    List<int>::ConstListIterator ITERATOR(&SOURCE_LIST, 0);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: ConstListIterator
ZTEST_SUITE_END()
