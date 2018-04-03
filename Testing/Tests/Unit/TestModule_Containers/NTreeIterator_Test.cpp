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

#include "ZContainers/NTree.h"

#include "NTreeIteratorMock.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::NTreeIteratorMock;


/// <summary>
/// Small structure used in operator* and operator-> tests.
/// </summary>
struct TestStructure
{
    TestStructure(const char field) : m_field(field)
    {
    }

    char m_field;
};

ZTEST_SUITE_BEGIN( NTreeIterator_TestSuite )

/// <summary>
/// Gets a sample tree with which to perform some tests.
/// </summary>
/// <returns>
/// A sample tree with a variety of nodes.
/// </returns>
static const NTree<char>* GetSampleTree()
{
    static NTree<char> sampleTree(3, 7);
    static bool bInitialized = false;

    if(!bInitialized)
    {
        //          A
        //         /|\
        //        / | \
        //       B  C  D
        //      / \     \
        //     /   \     \
        //    E     F     G
        sampleTree.SetRootValue('A');
        NTree<char>::NTreeIterator iteratorA = sampleTree.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
        sampleTree.AddChild(iteratorA, 'B');
        sampleTree.AddChild(iteratorA, 'C');
        sampleTree.AddChild(iteratorA, 'D');
        NTree<char>::NTreeIterator iteratorB = sampleTree.GetFirstChild(iteratorA);
        sampleTree.AddChild(iteratorB, 'E');
        sampleTree.AddChild(iteratorB, 'F');
        NTree<char>::NTreeIterator iteratorD = sampleTree.GetLastChild(iteratorA);
        sampleTree.AddChild(iteratorD, 'G');

        bInitialized = true;
    }

    return &sampleTree;
}

/// <summary>
/// Creates a sample tree using an external tree.
/// </summary>
/// <param name="inputTree">An empty tree.</param>
static void BuildSampleTree(NTree<char> &inputTree)
{
    //          A
    //         /|\
    //        / | \
    //       B  C  D
    //      / \     \
    //     /   \     \
    //    E     F     G
    inputTree.SetRootValue('A');
    NTree<char>::NTreeIterator iteratorA = inputTree.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
    inputTree.AddChild(iteratorA, 'B');
    inputTree.AddChild(iteratorA, 'C');
    inputTree.AddChild(iteratorA, 'D');
    NTree<char>::NTreeIterator iteratorB = inputTree.GetFirstChild(iteratorA);
    inputTree.AddChild(iteratorB, 'E');
    inputTree.AddChild(iteratorB, 'F');
    NTree<char>::NTreeIterator iteratorD = inputTree.GetLastChild(iteratorA);
    inputTree.AddChild(iteratorD, 'G');
}


/// <summary>
/// Checks that the iterator points to the given position when using a common tree and depth-first pre-order traversal order.
/// </summary>
ZTEST_CASE ( Constructor_IteratorPointsToGivenPositionWhenUsingCommonTreeAndDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();
    const puint_z POSITION = 1;
    NTree<char>::NTreeIterator EXPECTED_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    EXPECTED_ITERATOR.MoveFirst();
    ++EXPECTED_ITERATOR;

	// [Execution]
    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, POSITION, ETreeTraversalOrder::E_DepthFirstPreOrder);
    
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
    NTree<char>* SOURCE_TREE = null_z;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NTree<char>::NTreeIterator INVALID_ITERATOR(SOURCE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    const puint_z CAPACITY = SAMPLE_TREE->GetCapacity();
    const unsigned int INVALID_POSITION = CAPACITY;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NTree<char>::NTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();
    const ETreeTraversalOrder UNSUPPORTED_TRAVERSAL_ORDER = ETreeTraversalOrder::_NotEnumValue;
    const unsigned int INPUT_POSITION = 0;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NTree<char>::NTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INPUT_POSITION, UNSUPPORTED_TRAVERSAL_ORDER);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    const puint_z NUMBER_OF_ELEMENTS = SAMPLE_TREE->GetCount();

    const unsigned int INVALID_POSITION = NUMBER_OF_ELEMENTS;
    const bool IS_END = true;

	// [Execution]
    NTree<char>::NTreeIterator INVALID_ITERATOR(SAMPLE_TREE, INVALID_POSITION, ETreeTraversalOrder::E_DepthFirstPreOrder);

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
    const NTree<char> SOURCE_TREE(3);
    const bool IS_END = true;

	// [Execution]
    NTree<char>::NTreeIterator iterator(&SOURCE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    const char EXPECTED_VALUE = 'B';
    NTree<char>::NTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR;

	// [Execution]
    char value = *ITERATOR;

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
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTree<char>::NTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    NTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    NTree<TestStructure>::NTreeIterator iteratorA = SAMPLE_TREE.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    NTree<TestStructure>::NTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    NTree<TestStructure>::NTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    const char EXPECTED_VALUE = 'B';
    NTree<TestStructure>::NTreeIterator ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR;

	// [Execution]
    char value = ITERATOR->m_field;

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
    NTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    NTree<TestStructure>::NTreeIterator iteratorA = SAMPLE_TREE.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    NTree<TestStructure>::NTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    NTree<TestStructure>::NTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    NTree<TestStructure>::NTreeIterator FIRST_POSITION(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    NTreeIteratorMock<TestStructure> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    NTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    NTree<TestStructure>::NTreeIterator iteratorA = SAMPLE_TREE.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    NTree<TestStructure>::NTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    NTree<TestStructure>::NTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    NTree<TestStructure>::NTreeIterator ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    NTree<TestStructure> SAMPLE_TREE(3, 7);
    SAMPLE_TREE.SetRootValue(TestStructure('A'));
    NTree<TestStructure>::NTreeIterator iteratorA = SAMPLE_TREE.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('B'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('C'));
    SAMPLE_TREE.AddChild(iteratorA, TestStructure('D'));
    NTree<TestStructure>::NTreeIterator iteratorB = SAMPLE_TREE.GetFirstChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('E'));
    SAMPLE_TREE.AddChild(iteratorB, TestStructure('F'));
    NTree<TestStructure>::NTreeIterator iteratorD = SAMPLE_TREE.GetLastChild(iteratorA);
    SAMPLE_TREE.AddChild(iteratorD, TestStructure('G'));

    NTree<TestStructure>::NTreeIterator ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that the iterator steps forward properly and returns the previous state when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'B';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = iterator++;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'A', 'B', 'E', 'F', 'C', 'D', 'G'};
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    iterator.MoveFirst();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator++;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char FIRST_ELEMENT_VALUE = 'A';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = iterator++;
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
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ITERATOR_END);
    iterator++;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'D';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = iterator--;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'G', 'D', 'C', 'F', 'E', 'B', 'A'};
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    iterator.MoveLast();
    bool bIsCorrect = true;
    unsigned int i = 0;

	// [Execution]
    while(bIsCorrect && !iterator.IsEnd())
    {
        bIsCorrect = bIsCorrect && ELEMENT_VALUES[i] == *iterator;
        iterator--;
        ++i;
    }

    // [Verification]
    BOOST_CHECK(bIsCorrect);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWasPointingToLastEndPositionUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char LAST_ELEMENT_VALUE = 'G';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = iterator--;
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
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ITERATOR_END);
    iterator--;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'B';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = ++iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'A', 'B', 'E', 'F', 'C', 'D', 'G'};
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char FIRST_ELEMENT_VALUE = 'A';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveFirst();
    --ORIGINAL_ITERATOR;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = ++iterator;
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
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveLast();
    ITERATOR_END++;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ITERATOR_END);
    ++iterator;

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentStateWhenUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char SECOND_ELEMENT_VALUE = 'D';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = --iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(*iterator == SECOND_ELEMENT_VALUE);
}

/// <summary>
/// Checks that the tree is traversed in the correct order when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_TreeIsTraversedInCorrectOrderWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const char ELEMENT_VALUES[] = {'G', 'D', 'C', 'F', 'E', 'B', 'A'};
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one, when using depth-first pre-order.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWasPointingToLastEndPositionUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const char LAST_ELEMENT_VALUE = 'G';
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ORIGINAL_ITERATOR.MoveLast();
    ORIGINAL_ITERATOR++;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    NTree<char>::NTreeIterator iteratorPreviousState = --iterator;
    int nCurrentElement = *iterator;

    // [Verification]
    BOOST_CHECK(iteratorPreviousState == iterator);
    BOOST_CHECK(nCurrentElement == LAST_ELEMENT_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_END(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ITERATOR_END);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_A(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    NTree<char>::NTreeIterator ITERATOR_B(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ++ITERATOR_A;

	// [Execution]
    NTree<char>::NTreeIterator iterator = ITERATOR_B;
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
    NTree<char> SAMPLE_TREE(3, 7);
    BuildSampleTree(SAMPLE_TREE);

    NTreeIteratorMock<char> INVALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE.GetCapacity());
    NTree<char>::NTreeIterator VALID_ITERATOR(&SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    NTree<char>::NTreeIterator iterator = INVALID_ITERATOR;
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    NTree<char> TREE_A(3);
    const NTree<char>* TREE_B = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NTree<char>::NTreeIterator iterator(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
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
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    NTree<char>::NTreeIterator iterator(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    iterator = INVALID_ITERATOR;

    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different tree.
/// </summary>
ZTEST_CASE ( OperatorAssignment_IteratorDoesNotChangeIfInputIteratorPointsToDifferentTree_Test )
{
    NTree<char> TREE_A(3);
    const NTree<char>* TREE_B = GetSampleTree();

    NTree<char>::NTreeIterator ITERATOR_A(&TREE_A, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    NTree<char>::NTreeIterator ITERATOR_B(TREE_B, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    NTree<char>::NTreeIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;

    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the tree is not empty, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    NTree<char>::NTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

    NTree<char>::NTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    NTree<char>::NTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    --ORIGINAL_ITERATOR;

    NTree<char>::NTreeIterator ITERATOR_FIRST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
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
    NTree<char> EMPTY_ARRAY(3, 1);
    NTree<char>::NTreeIterator END_ITERATOR(&EMPTY_ARRAY, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    NTree<char>::NTreeIterator ITERATOR(&EMPTY_ARRAY, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    ITERATOR.MoveFirst();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the tree is not empty, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

    NTree<char>::NTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasNotValidUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

    NTree<char>::NTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

    NTreeIteratorMock<char> INVALID_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder); 
    INVALID_ITERATOR.SetPosition(SAMPLE_TREE->GetCapacity());

	// [Execution]
    NTree<char>::NTreeIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();

    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first, using depth-first pre-order.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenTreeIsNotEmptyAndIteratorWasPointingToPositionBeforeFirstUsingDepthFirstPreOrder_Test )
{
    // [Preparation]
    const NTree<char>* SAMPLE_TREE = GetSampleTree();

    NTree<char>::NTreeIterator ORIGINAL_ITERATOR(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    --ORIGINAL_ITERATOR;

    NTree<char>::NTreeIterator ITERATOR_LAST(SAMPLE_TREE, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    while(!ITERATOR_LAST.IsEnd())
        ++ITERATOR_LAST;
    --ITERATOR_LAST;

	// [Execution]
    NTree<char>::NTreeIterator iterator(ORIGINAL_ITERATOR);
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
    NTree<char> EMPTY_ARRAY(3, 1);

    NTree<char>::NTreeIterator END_ITERATOR(&EMPTY_ARRAY, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;

    NTree<char>::NTreeIterator ITERATOR(&EMPTY_ARRAY, 0, ETreeTraversalOrder::E_DepthFirstPreOrder);

	// [Execution]
    ITERATOR.MoveLast();

    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif


// End - Test Suite: NTreeIterator
ZTEST_SUITE_END()
