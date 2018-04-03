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
#include "BinarySearchTreeWhiteBox.h"
#include "CallCounter.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::BinarySearchTreeWhiteBox;
using z::Test::CallCounter;


ZTEST_SUITE_BEGIN( BinarySearchTree_TestSuite )

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const puint_z EXPECTED_ROOT = BinarySearchTreeWhiteBox<int>::GetEndPositionForward();
    const puint_z EXPECTED_CAPACITY = 1;
    const puint_z EXPECTED_NODE_CAPACITY = EXPECTED_CAPACITY;

    // [Execution]
    BinarySearchTreeWhiteBox<int> tree;

    // [Verification]
    puint_z uStoredRoot = tree.GetRootPosition();
    puint_z uStoredCapacity = tree.GetCapacity();
    puint_z uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(BinarySearchTreeWhiteBox<int>::BinaryNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

/// <summary>
/// Checks that the value of input parameters are correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_InputParametersAreCorrectlySet_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 5;

    // [Execution]
    BinarySearchTreeWhiteBox<int> tree(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = tree.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that all the default values have not changed since the last time this test was executed.
/// </summary>
ZTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 5;
    const puint_z EXPECTED_ROOT = BinarySearchTreeWhiteBox<int>::GetEndPositionForward();
    const puint_z EXPECTED_NODE_CAPACITY = INPUT_CAPACITY;

    // [Execution]
    BinarySearchTreeWhiteBox<int> tree(INPUT_CAPACITY);

    // [Verification]
    const puint_z uStoredRoot = tree.GetRootPosition();
    const puint_z uStoredNodeCapacity = tree.GetNodeAllocator().GetPoolSize() / sizeof(BinarySearchTreeWhiteBox<int>::BinaryNode);

    BOOST_CHECK_EQUAL(uStoredRoot, EXPECTED_ROOT);
    BOOST_CHECK_EQUAL(uStoredNodeCapacity, EXPECTED_NODE_CAPACITY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input capacity equals zero.
/// </summary>
ZTEST_CASE ( Constructor2_AssertionFailsWhenCapacityEqualsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_ZERO = 0;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        BinarySearchTree<int> tree(INPUT_ZERO);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // #if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the tree is correctly copied when it has elements.
/// </summary>
ZTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItHasElements_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);

    const puint_z EXPECTED_COUNT = TREE.GetCount();

    // [Execution]
    BinarySearchTree<int> copiedTree(TREE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    puint_z uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when it is empty.
/// </summary>
ZTEST_CASE ( Constructor3_TreeIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);

    // [Execution]
    BinarySearchTree<int> copiedTree(TREE);

    // [Verification]
    bool bTreeIsEmpty = copiedTree.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
ZTEST_CASE ( Constructor3_CopyConstructorsAreCalledForAllElements_Test )
{
    // [Preparation]
    BinarySearchTree<CallCounter> TREE(5);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);

    const puint_z EXPECTED_VALUE = TREE.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    BinarySearchTree<CallCounter> copiedTree(TREE);

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the destructor of every element is called.
/// </summary>
ZTEST_CASE ( Destructor_TheDestructorOfEveryElementIsCalled_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 3;

    {
        BinarySearchTree<CallCounter> TREE(3);
        TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
        TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
        TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
        CallCounter::ResetCounters();

    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the tree is correctly copied when it has elements and the destination tree is empty.
/// </summary>
ZTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);

    const puint_z EXPECTED_COUNT = TREE.GetCount();
    BinarySearchTree<int> copiedTree(8);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    puint_z uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are more elements in the source tree than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    BinarySearchTree<int> TREE(8);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z EXPECTED_COUNT = TREE.GetCount();

    BinarySearchTree<int> copiedTree(3);
    copiedTree.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    puint_z uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are less elements in the source tree than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {3, 5};
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z EXPECTED_COUNT = TREE.GetCount();

    BinarySearchTree<int> copiedTree(3);
    copiedTree.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    puint_z uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when there are the same number of elements in the source tree than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {3, 5, 6};
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z EXPECTED_COUNT = TREE.GetCount();

    BinarySearchTree<int> copiedTree(3);
    copiedTree.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = copiedTree.GetIterator(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    puint_z uCount = copiedTree.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the tree is correctly copied when it is empty and the destination tree has elements.
/// </summary>
ZTEST_CASE ( OperatorAssignment_TreeIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    BinarySearchTree<int> copiedTree(3);
    copiedTree.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    bool bTreeIsEmpty = copiedTree.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllElements_Test )
{
    // [Preparation]
    BinarySearchTree<CallCounter> TREE(8);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<CallCounter> copiedTree(3);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);

    const puint_z EXPECTED_COPY_CONSTRUCTORS_VALUE = TREE.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_COPY_CONSTRUCTORS_VALUE);
}

/// <summary>
/// Checks that the destructors are called for each element.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DestructorsAreCalledForAllElements_Test )
{
    // [Preparation]
    BinarySearchTree<CallCounter> TREE(8);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<CallCounter> copiedTree(3);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);
    copiedTree.Add(CallCounter(), ETreeTraversalOrder::E_DepthFirstInOrder);

    const puint_z EXPECTED_DESTRUCTORS_VALUE = copiedTree.GetCount();
    CallCounter::ResetCounters();

    // [Execution]
    copiedTree = TREE;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
}

/// <sumary>
/// Checks that it returns True when trees are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenTreesAreExactlyEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2 = TREE1;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees are the same instance.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenTreesAreSameInstance_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 == TREE1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have the same structure but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesHaveSameStructureButElementsAreNotEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have the same values but with a different structure.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesAreHaveSameValuesButDifferentStructure_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenTreesHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 == TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenTreesAreExactlyEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2 = TREE1;

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when trees are the same instance.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenTreesAreSameInstance_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE1 != TREE1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have the same structure but elements are not equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesHaveSameStructureButElementsAreNotEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have the same values but with a different structure.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesAreHaveSameValuesButDifferentStructure_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when trees have different number of elements although elements are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenTreesHaveDifferentNumberOfElementsAlthoughElementsAreEqual_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE1(8);
    TREE1.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE1.Add(9, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> TREE2(8);
    TREE2.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE2.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE1 != TREE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
ZTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 4;
    BinarySearchTree<int> TREE(2);

    // [Execution]
    TREE.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = TREE.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
ZTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 4;
    const int EXPECTED_FIRST_ELEMENT = 1;
    const int EXPECTED_SECOND_ELEMENT = 2;
    BinarySearchTree<int> TREE(2);
    TREE.Add(EXPECTED_FIRST_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(EXPECTED_SECOND_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);
    BOOST_CHECK_EQUAL(*it, EXPECTED_FIRST_ELEMENT);
    ++it;
    BOOST_CHECK_EQUAL(*it, EXPECTED_SECOND_ELEMENT);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
ZTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 1;
    const puint_z EXPECTED_CAPACITY = 4;
    BinarySearchTree<int> TREE(4);

    // [Execution]
    TREE.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    puint_z uCapacity = TREE.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that it returns True when the tree contains the element.
/// </summary>
ZTEST_CASE ( Contains_ReturnsTrueWhenTreeContainsTheElement_Test )
{
    // [Preparation]
    const int INPUT_VALUE = 3;
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(INPUT_VALUE, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree does not contain the element.
/// </summary>
ZTEST_CASE ( Contains_ReturnsFalseWhenTreeDoesNotContainTheElement_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    const int INPUT_VALUE = 0;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree is empty.
/// </summary>
ZTEST_CASE ( Contains_ReturnsFalseWhenTreeIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    const int INPUT_VALUE = 5;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = TREE.Contains(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the element is correctly added when the tree is empty.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 0;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT};
    
    BinarySearchTree<int> TREE(3);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and the tree only contains one element.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndTreeOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 3;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT, 5};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and the tree only contains one element.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndTreeOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 7;
    const int EXPECTED_VALUES[] = {5, INPUT_ELEMENT};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and greater than its left child.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndGreaterThanItsLeftChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 4;
    const int EXPECTED_VALUES[] = {3, INPUT_ELEMENT, 5};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is lower than the root and lower than its left child.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsLowerThanRootAndLowerThanItsLeftChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 2;
    const int EXPECTED_VALUES[] = {INPUT_ELEMENT, 3, 5};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and lower than its right child.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndLowerThanItsRightChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 6;
    const int EXPECTED_VALUES[] = {5, INPUT_ELEMENT, 7};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when it is greater than the root and greater than its right child.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenItIsGreaterThanRootAndGreaterThanItsRightChild_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    const int EXPECTED_VALUES[] = {5, 7, INPUT_ELEMENT};
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
ZTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itResult = TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itResult, INPUT_ELEMENT);
}

/// <summary>
/// Checks that the number of elements is incremented after adding.
/// </summary>
ZTEST_CASE ( Add_CountIsIncremented_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z COUNT_BEFORE_ADDING = TREE.GetCount();

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    puint_z uCountAfterAdding = TREE.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
ZTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const int INPUT_ELEMENT = 8;
    
    BinarySearchTree<int> TREE(1);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z CAPACITY_BEFORE_ADDING = TREE.GetCapacity();

    // [Execution]
    TREE.Add(INPUT_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    puint_z uCapacityAfterAdding = TREE.GetCapacity();
    BOOST_CHECK(uCapacityAfterAdding > CAPACITY_BEFORE_ADDING);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the element already exists.
/// </summary>
ZTEST_CASE ( Add_AssertionFailsWhenTheElementAlreadyExists_Test )
{
    // [Preparation]
    const int ELEMENT = 0;
    
    BinarySearchTree<int> TREE(1);
    TREE.Add(ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Add(ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);
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
/// Checks that the tree is empty when removing the only element in it.
/// </summary>
ZTEST_CASE ( Remove_TreeIsEmptyWhenRemovingTheOnlyElementInTheTree_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bTreeIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bTreeIsEmpty);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children, which do not have descendants.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenWhichDoNotHaveDescendants_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 4, 5};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and it is the left child of its parent.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndIsLeftChildOfItsParent_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 4, 5};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and it is the right child of its parent.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndIsRightChildOfItsParent_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {5, 6, 8};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and the left child has a right child.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndTheLeftChildHasRightChild_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 2, 4, 5};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has both left and right children and the left child has a left child.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftAndRightChildrenAndTheLeftChildHasLeftChild_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {0, 1, 4, 5};
    BinarySearchTree<int> TREE(5);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has a left child only.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasLeftChildOnly_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 5};
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has a right child only.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenItHasRightChildOnly_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {4, 5};
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly removed when it has no children.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenHasNoChildren_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {5};
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementPosition = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&TREE, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the root is updated when it is removed.
/// </summary>
ZTEST_CASE ( Remove_RootElementIsUpdatedWhenItIsRemoved_Test )
{
    // [Preparation]
    //BinarySearchTree<int> TREE(3);
    //const BinarySearchTree<int>::ConstBinarySearchTreeIterator ROOT_ITERATOR = TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    //const BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    //TREE.Remove(ROOT_ITERATOR);

    // [Verification]
    // [TODO] Thund: Uncomment when GetRoot exists
    //BinarySearchTree<int>::ConstBinarySearchTreeIterator itRoot = TREE.GetRoot();
    //BOOST_CHECK(itRoot == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the returned iterator points to the end position when there is not next element in the tree.
/// </summary>
ZTEST_CASE ( Remove_ReturnedIteratorPointsToEndPositionWhenThereIsNoNextElementInTree_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itLastElement = TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itResult = TREE.Remove(itLastElement);

    // [Verification]
    bool bIteratorPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK(bIteratorPointsToEndPosition);
}

/// <summary>
/// Checks that the returned iterator points to the next element.
/// </summary>
ZTEST_CASE ( Remove_ReturnedIteratorPointsToNextElement_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(4);
    TREE.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itElementToRemove = TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = itElementToRemove;
    ++EXPECTED_ITERATOR;

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itResult = TREE.Remove(itElementToRemove);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to end position.
/// </summary>
ZTEST_CASE ( Remove_AssertionFailsWhenTheInputIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(1);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itEnd = TREE.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    ++itEnd;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.Remove(itEnd);
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
/// Checks that the tree is emptied.
/// </sumary>
ZTEST_CASE( Clear_TheTreeIsEmptied_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    TREE.Add(0, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    TREE.Clear();

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that nothing is done when the tree is already empty.
/// </sumary>
ZTEST_CASE( Clear_NothingHappensWhenTreeIsAlreadyEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<char> TREE(3);

    // [Execution]
    TREE.Clear();

    // [Verification]
    bool bIsEmpty = TREE.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that the node is obtained when using the depth-first in-order.
/// </sumary>
ZTEST_CASE( GetFirst_NodeIsObtainedWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    BinarySearchTree<int> TREE(5);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itFirst = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itFirst, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the tree is empty.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnedIteratorPointsToEndWhenTreeIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(5);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itFirst = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIteratorPointstoEnd = itFirst.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the node is obtained when using the depth-first in-order.
/// </sumary>
ZTEST_CASE( GetLast_NodeIsObtainedWhenUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 4;
    BinarySearchTree<int> TREE(5);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itLast = TREE.GetLast(ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itLast, EXPECTED_ELEMENT);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the tree is empty.
/// </sumary>
ZTEST_CASE( GetLast_ReturnedIteratorPointsToEndWhenTreeIsEmpty_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(5);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itLast = TREE.GetLast(ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIteratorPointstoEnd = itLast.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the expected iterator is returned when using a common tree and a common index and using the depth-first in-order.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheExpectedIteratorWhenUsingCommonTreeAndPositionAndDepthFirstInOrder_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 1;
    BinarySearchTree<int> TREE(3);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);
    ++EXPECTED_ITERATOR;

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetIterator(INPUT_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the first position is returned when using a common tree and the index equals zero and using the depth-first in-order.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheFirstPositionWhenUsingCommonTreeAndZeroIndexAndDepthFirstInOrder_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 0;
    BinarySearchTree<int> TREE(3);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetIterator(INPUT_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

/// <sumary>
/// Checks that the last position is returned when using a common tree and the last index and using the depth-first in-order.
/// </sumary>
ZTEST_CASE( GetIterator_ReturnsTheLastPositionWhenUsingCommonTreeAndLastIndexAndDepthFirstInOrder_Test )
{
    // [Preparation]
    BinarySearchTree<int> TREE(3);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z INPUT_INDEX = TREE.GetCount() - 1U;
    BinarySearchTree<int>::ConstBinarySearchTreeIterator EXPECTED_ITERATOR = TREE.GetFirst(ETreeTraversalOrder::E_DepthFirstInOrder);
    EXPECTED_ITERATOR.MoveLast();

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetIterator(INPUT_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK(it == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the tree is empty.
/// </sumary>
ZTEST_CASE( GetIterator_AssertionFailsWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 0;
    BinarySearchTree<int> TREE(3);
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetIterator(INPUT_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);
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
    BinarySearchTree<int> TREE(3);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z OUT_OF_BOUNDS_INDEX = TREE.GetCount() + 1U;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TREE.GetIterator(OUT_OF_BOUNDS_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);
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
ZTEST_CASE( GetIterator_IteratorPointsToEndPositionWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const puint_z INPUT_INDEX = 0;
    BinarySearchTree<int> TREE(3);
    const bool ITERATOR_POINTS_END_POSITION = true;

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetIterator(INPUT_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);

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
    BinarySearchTree<int> TREE(3);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    const puint_z OUT_OF_BOUNDS_INDEX = TREE.GetCount() + 1U;

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = TREE.GetIterator(OUT_OF_BOUNDS_INDEX, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIsEnd = it.IsEnd(EIterationDirection::E_Forward);
    BOOST_CHECK_EQUAL(bIsEnd, ITERATOR_POINTS_END_POSITION);
}

#endif

/// <summary>
/// Checks that it returns the expected position when the tree contains the element and using depth-first in-order.
/// </summary>
ZTEST_CASE ( PositionOf_ReturnsExpectedPositionWhenTreeContainsTheElementAndUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 1;
    BinarySearchTree<int> TREE(5);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itPosition = TREE.PositionOf(EXPECTED_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    BOOST_CHECK_EQUAL(*itPosition, EXPECTED_ELEMENT);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the tree does not contain the element and using depth-first in-order.
/// </summary>
ZTEST_CASE ( PositionOf_ReturnsEndPositionWhenTreeDoesNotContainTheElementAndUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 9;
    BinarySearchTree<int> TREE(5);
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    TREE.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itPosition = TREE.PositionOf(EXPECTED_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the tree is empty and using depth-first in-order.
/// </summary>
ZTEST_CASE ( PositionOf_ReturnsEndPositionWhenTreeIsEmptyAndUsingDepthFirstInOrder_Test )
{
    // [Preparation]
    const int EXPECTED_ELEMENT = 9;
    BinarySearchTree<int> TREE(5);

    // [Execution]
    BinarySearchTree<int>::ConstBinarySearchTreeIterator itPosition = TREE.PositionOf(EXPECTED_ELEMENT, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
ZTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTree_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 2, 3};
    BinarySearchTree<int> sourceTree(3);
    sourceTree.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> destinationTree(3);

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&destinationTree, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination tree has more capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTreeWhenInputTreeHasMoreCapacityAndElements_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 2, 3};
    BinarySearchTree<int> sourceTree(3);
    sourceTree.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> destinationTree(5);
    destinationTree.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&destinationTree, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination tree has less capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedTreeHasSameValuesThanTheOriginalTreeWhenInputTreeHasLessCapacityAndElements_Test )
{
    // [Preparation]
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5};
    BinarySearchTree<int> sourceTree(5);
    sourceTree.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(4, ETreeTraversalOrder::E_DepthFirstInOrder);
    sourceTree.Add(5, ETreeTraversalOrder::E_DepthFirstInOrder);

    BinarySearchTree<int> destinationTree(3);
    destinationTree.Add(6, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(7, ETreeTraversalOrder::E_DepthFirstInOrder);
    destinationTree.Add(8, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    sourceTree.Clone(destinationTree);

    // [Verification]
    bool bResultIsWhatEspected = true;

    BinarySearchTree<int>::ConstBinarySearchTreeIterator it = BinarySearchTree<int>::ConstBinarySearchTreeIterator(&destinationTree, 0, ETreeTraversalOrder::E_DepthFirstInOrder);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
        bResultIsWhatEspected = bResultIsWhatEspected && *it == EXPECTED_VALUES[i];

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the capacity is correctly calculated.
/// </summary>
ZTEST_CASE ( GetCapacity_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 3;
    BinarySearchTree<int> TREE(3);

    // [Execution]
    puint_z uCapacity = TREE.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the number of elements is correctly counted.
/// </summary>
ZTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    BinarySearchTree<int> TREE(3);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder); // [ 1 |   |   ]
    TREE.Add(2, ETreeTraversalOrder::E_DepthFirstInOrder); // [ 1 | 2 |   ]
    TREE.Add(3, ETreeTraversalOrder::E_DepthFirstInOrder); // [ 1 | 2 | 3 ]

    // [Execution]
    puint_z uCount = TREE.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns zero when the tree is empty.
/// </summary>
ZTEST_CASE ( GetCount_ReturnsZeroWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 0;
    BinarySearchTree<int> TREE(3);

    // [Execution]
    puint_z uCount = TREE.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns True when the tree is empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsTrueWhenTreeIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    BinarySearchTree<int> TREE(3);

    // [Execution]
    bool bResult = TREE.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the tree is not empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsFalseWhenTreeIsNotEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    BinarySearchTree<int> TREE(3);
    TREE.Add(1, ETreeTraversalOrder::E_DepthFirstInOrder);

    // [Execution]
    bool bResult = TREE.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: BinarySearchTree

ZTEST_SUITE_END()
