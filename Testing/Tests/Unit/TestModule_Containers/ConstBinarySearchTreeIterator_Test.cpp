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

#include "ZContainers/BinarySearchTree.h"

#include "ConstBinarySearchTreeIteratorMock.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::ConstBinarySearchTreeIteratorMock;


/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const int field) : m_field(field)
    {
    }

    bool operator==(const TestStructure& ts) const
    {
        return m_field == ts.m_field;
    }
    
    bool operator<(const TestStructure& ts) const
    {
        return m_field < ts.m_field;
    }

    int m_field;
};

ZTEST_SUITE_BEGIN( ConstBinarySearchTreeIterator_TestSuite )

/// <summary>
/// Gets a sample tree with which to perform some tests.
/// </summary>
/// <returns>
/// A sample tree with a variety of nodes.
/// </returns>
static const BinarySearchTree<int>* GetSampleTree()
{
    static BinarySearchTree<int> sampleTree(7);
    static bool bInitialized = false;

    if(!bInitialized)
    {
        //         4
        //       /   \
        //      /     \
        //     2       6
        //    / \     / \
        //   /   \   /   \
        //  1     3 5     7
        sampleTree.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
        sampleTree.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);

        bInitialized = true;
    }

    return &sampleTree;
}

/// <summary>
/// Creates a sample tree using an external tree.
/// </summary>
/// <param name="inputTree">An empty tree.</param>
static void BuildSampleTree(BinarySearchTree<int> &inputTree)
{
    //         4
    //       /   \
    //      /     \
    //     2       6
    //    / \     / \
    //   /   \   /   \
    //  1     3 5     7
    inputTree.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    inputTree.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
}


/// <summary>
/// Checks that the iterator points to the given position when using a common tree and depth-first in-order traversal order.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonTreeAndDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();
    const puint_z POSITION = 1;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = SAMPLE_TREE->GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);
    ++EXPECTED_ITERATOR;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, POSITION, ETreeTraversalOrder::E_DepthFirstInOrder);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when input tree is null.
/// </summary>
ZTEST_CASE ( Constructor_AssertionFailsWhenInputTreeIsNull_Test )
{
    // [Preparation]
    BinarySearchTree<int>* SOURCE_TREE = null_z;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator INVALID_ITERATOR(SOURCE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const puint_z CAPACITY = SAMPLE_TREE->GetCapacity();
    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, ETreeTraversalOrder::E_DepthFirstInOrder);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input traversal order is not supported.
/// </summary>
ZTEST_CASE ( Constructor_AssertionFailsWhenInputTraversalOrderIsNotSupported_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();
    const ETreeTraversalOrder UNSUPPORTED_TRAVERSAL_ORDER = ETreeTraversalOrder::_NotEnumValue;
    const unsigned int INPUT_POSITION = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INPUT_POSITION, UNSUPPORTED_TRAVERSAL_ORDER);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const puint_z NUMBER_OF_ELEMENTS = SAMPLE_TREE->GetCount();

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIsEndIterationForward = INVALID_ITERATOR.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEndIterationForward, IS_END);
}

/// <summary>
/// Checks that the iterator points to the end position (forward iteration) when using an empty tree.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToForwardEndPositionWhenUsingEmptyTree_Test )
{
    // [Preparation]
    const BinarySearchTree<int> SOURCE_TREE(3);
    const bool IS_END = true;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(&SOURCE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    const int EXPECTED_VALUE = 1;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveFirst();

	// [Execution]
    int value = *ITERATOR;

    // [Verification]
    BOOST_CHECK_EQUAL(value, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(8);
    BuildSampleTree(SAMPLE_TREE);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        *INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
ZTEST_CASE ( OperatorIndirection_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    BinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), ETreeTraversalOrder::E_DepthFirstInOrder);

    const int EXPECTED_VALUE = 2;
    BinarySearchTree<TestStructure>::ConstBinarySearchTreeIterator ITERATOR = SAMPLE_TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR;

	// [Execution]
    int value = ITERATOR->m_field;

    // [Verification]
    BOOST_CHECK_EQUAL(value, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorIsInvalid_Test )
{
    // [Preparation]
    BinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<TestStructure>::ConstBinarySearchTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    ConstBinarySearchTreeIteratorMock<TestStructure> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR->m_field;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator is pointing to the end position (forward iteration).
/// </summary>
ZTEST_CASE ( OperatorDereferencing_AssertionFailsWhenIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    BinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<TestStructure>::ConstBinarySearchTreeIterator ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_field;
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
    BinarySearchTree<TestStructure> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(TestStructure(4), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(2), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(1), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(3), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(6), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(5), ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(TestStructure(7), ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<TestStructure>::ConstBinarySearchTreeIterator ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveFirst();
    --ITERATOR;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR->m_field;
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
/// Checks that the iterator steps forward properly and returns the previous state when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5, 6, 7};
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator++;
        i++;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = iterator++;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR++;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 6;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {7, 6, 5, 4, 3, 2, 1};
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator--;
        i++;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPositionUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 7;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = iterator--;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR--;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 2;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR = SAMPLE_TREE->GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {1, 2, 3, 4, 5, 6, 7};
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        ++iterator;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int FIRST_ELEMENT_VALUE = 1;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = ++iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(nCurrentElement == FIRST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int SECOND_ELEMENT_VALUE = 6;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR = SAMPLE_TREE->GetLast(ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one, when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPositionUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int LAST_ELEMENT_VALUE = 7;
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR = SAMPLE_TREE->GetLast(ETreeTraversalOrder::E_DepthFirstInOrder);
    ORIGINAL_ITERATOR++;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iteratorPreviousState = --iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int ELEMENT_VALUES[] = {7, 6, 5, 4, 3, 2, 1};
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        --iterator;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ITERATOR_END);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

/// <summary>
/// Checks that input iterator is copied when resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignment_InputIteratorIsCorrectlyCopiedWhenResidentIteratorIsNotValid_Test )
{
    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    BuildSampleTree(SAMPLE_TREE);

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    BinarySearchTree<int>::ConstBinarySearchTreeIterator VALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator = INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorAssignment_AssertionFailsWhenInputIteratorPointsToDifferentTree_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that the iterator is copied when it is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignment_IteratorIsCopiedWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentTree_Test )
{
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator = ITERATOR_B;
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator == INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR == iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator != INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR != iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns True when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator > INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR > iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator < INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR < iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    TREE_A.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator >= INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR >= iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither lower than nor equals to the input iterator, using depth-first in-order.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIteratorUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        iterator <= INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
        INVALID_ITERATOR <= iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that it returns False when iterators point to a different tree.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorsPointToDifferentTrees_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE_A(3);
    const BinarySearchTree<int>* TREE_B = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd1_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.IsEnd();
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
/// Checks that it returns False when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd1_ReturnsFalseWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
ZTEST_CASE ( IsEnd2_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd(EIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd2_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.IsEnd(EIterationDirection::E_Backward);
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
/// Checks that it returns False when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd2_ReturnsFalseWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd(EIterationDirection::E_Backward);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the tree is not empty, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position when the root node does not have left-child, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenRootDoesNotHaveLeftChildUsingDepthFirstInOrder_Test )
{
    //     1
    //      \
    //       2
    //        \
    //         3
    //          \
    //           4

    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_FIRST(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    --ORIGINAL_ITERATOR;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 2, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> EMPTY_TREE(1);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator END_ITERATOR(&EMPTY_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(&EMPTY_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the tree is not empty, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position when the root node does not have right-child, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenRootDoesNotHaveRightChildUsingDepthFirstInOrder_Test )
{
    //        4
    //       /
    //      3
    //     /
    //    2
    //   /
    //  1

    // [Preparation]
    BinarySearchTree<int> SAMPLE_TREE(7);
    SAMPLE_TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    SAMPLE_TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_LAST(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first, using depth-first in-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    --ORIGINAL_ITERATOR;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator points to the end position when the tree is empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> EMPTY_TREE(1);

    BinarySearchTree<int>::ConstBinarySearchTreeIterator END_ITERATOR(&EMPTY_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(&EMPTY_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

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
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    BinarySearchTree<int>::ConstBinarySearchTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator points to an out of bounds position.
/// </summary>
ZTEST_CASE ( IsValid_ReturnsFalseWhenIteratorPointsToOutOfBoundPosition_Test )
{
    // [Preparation]
    const BinarySearchTree<int>* SAMPLE_TREE = GetSampleTree();

    ConstBinarySearchTreeIteratorMock<int> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsValid();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: ConstBinarySearchTreeIterator
ZTEST_SUITE_END()
