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

#ifndef __NTREE__
#define __NTREE__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"
#include "ZCommon/Assertions.h"
#include "ZMemory/PoolAllocator.h"
#include "ZMemory/Alignment.h"
#include "ZContainers/SComparatorDefault.h"
#include "ZMemory/AllocationOperators.h"
#include "ZContainers/ETreeTraversalOrder.h"
#include "ZContainers/EIterationDirection.h"
#include "ZCommon/DataTypes/SInteger.h"


namespace z
{

/// <summary>
/// Represents an N-ary tree, i. e. an acyclic undirected graph whose nodes have up to a maximum number of children nodes.
/// </summary>
/// <remarks>
/// Trees are empty when they are created; to add the root node, use the the SetRootNode method.<br/>
/// The number of child nodes per node (N) is set when the tree is created. Trees with different value of N cannot interact in certain scenarios. However, 
/// trees can be created without that restriction by using the NO_MAX_CHILDREN constant.<br/>
/// Every node keeps a reference to its parent and its children. Removing a node implies removing all its children.<br/>
/// There is not a default way to traverse an N-ary tree, the desired method will have to be specified when necessary.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the tree elements.</typeparam>
/// <typeparam name="AllocatorT">The allocator used to reserve memory. The default type is PoolAllocator.</typeparam>
/// <typeparam name="ComparatorT">The comparator. The default type is SComparatorDefault.</typeparam>
template <class T, class AllocatorT = PoolAllocator, class ComparatorT = SComparatorDefault<T> >
class NTree
{

    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// A node of the N-ary tree for internal use.
    /// </summary>
    /// <remarks>
    /// Nodes store the position of the parent node, the previous node, the next node and the first child node, in the internal
    /// contiguous chunks of memory used to store all the nodes and the elements.<br/>
    /// Child nodes are not stored in parent nodes, only the first child node is referenced and the rest are part of a double
    /// linked list formed by all the children.
    /// </remarks>
    class Node
    {
        // CONSTRUCTORS
        // ---------------

    public:

        /// <summary>
        /// Constructor that receives the positions in the allocated memory chunk of the related nodes.
        /// </summary>
        /// <param name="uParent">[IN] Position of the parent of the node.</param>
        /// <param name="uNext">[IN] Position of the next node.</param>
        /// <param name="uPrevious">[IN] Position of the previous node.</param>
        /// <param name="uFirstChild">[IN] Position of the first child node of the node.</param>
        Node(const puint_z uParent, const puint_z uNext, const puint_z uPrevious, const puint_z uFirstChild) :
                                                                                    m_uParent(uParent),
                                                                                    m_uNext(uNext),
                                                                                    m_uPrevious(uPrevious),
                                                                                    m_uFirstChild(uFirstChild)
        {
        }


        // PROPERTIES
        // ---------------

    public:

        /// <summary>
        /// Gets the position of the parent node.
        /// </summary>
        /// <returns>
        /// The position of the parent node. Returns NTree::END_POSITION_FORWARD if there is no parent node (it is the root node).
        /// </returns>
        puint_z GetParent() const
        {
            return m_uParent;
        }

        /// <summary>
        /// Gets the position of the next node.
        /// </summary>
        /// <returns>
        /// The position of the next node. Returns NTree::END_POSITION_FORWARD if there is no next node (it is the last child).
        /// </returns>
        puint_z GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Gets the position of the previous node.
        /// </summary>
        /// <returns>
        /// The position of the previous node. Returns NTree::END_POSITION_FORWARD if there is no previous node (it is the first child).
        /// </returns>
        puint_z GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Gets the position of the first child node.
        /// </summary>
        /// <returns>
        /// The position of the first child node. Returns NTree::END_POSITION_FORWARD if there is no first child node.
        /// </returns>
        puint_z GetFirstChild() const
        {
            return m_uFirstChild;
        }

        /// <summary>
        /// Sets the position of the parent node.
        /// </summary>
        /// <param name="uParent">[IN] The position of the parent node. It can be NTree::END_POSITION_FORWARD if there is no parent node (it is the root node).</param>
        void SetParent(const puint_z uParent)
        {
            m_uParent = uParent;
        }

        /// <summary>
        /// Sets the position of the next node.
        /// </summary>
        /// <param name="uNext">[IN] The position of the next node. It can be NTree::END_POSITION_FORWARD if there is no next node (it is the last child node).</param>
        void SetNext(const puint_z uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the position of the previous node.
        /// </summary>
        /// <param name="uPrevious">[IN] The position of the previous node. It can be NTree::END_POSITION_FORWARD if there is no previous node (it is the first child node).</param>
        void SetPrevious(const puint_z uPrevious)
        {
            m_uPrevious = uPrevious;
        }

        /// <summary>
        /// Sets the position of the first child node.
        /// </summary>
        /// <param name="uFirstChild">[IN] The position of the first child node. It can be NTree::END_POSITION_FORWARD if there is no child node (it has not got children nodes).</param>
        void SetFirstChild(const puint_z uFirstChild)
        {
            m_uFirstChild = uFirstChild;
        }


        // ATTRIBUTES
        // ---------------

    private:

        /// <returns>
        /// The position of the parent node. Returns NTree::END_POSITION_FORWARD if there is no parent node (it is the root node).
        /// </returns>
        puint_z m_uParent;

        /// <returns>
        /// The position of the next node. Returns NTree::END_POSITION_FORWARD if there is no next node (it is the last child).
        /// </returns>
        puint_z m_uNext;

        /// <returns>
        /// The position of the previous node. Returns NTree::END_POSITION_FORWARD if there is no previous node (it is the first child).
        /// </returns>
        puint_z m_uPrevious;

        /// <returns>
        /// The position of the first child node. Returns NTree::END_POSITION_FORWARD if there is no first child node.
        /// </returns>
        puint_z m_uFirstChild;

    };
    
public:

    /// <summary>
    /// Iterator that steps once per element of an n-ary tree, in a concrete order, and does not allow the modification of them. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ConstNTreeIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the tree to iterate through, the position to physically point to and the traversal order. This constructor is intended 
        /// to be used internally, use GetIterator method of the NTree class instead.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pTree">[IN] The tree to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of tree elements, but the physical.
        /// It must be lower than the capacity of the tree.</param>
        /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited. Currently, only depth-first pre-order is supported.</param>
        ConstNTreeIterator(const NTree* pTree, const puint_z uPosition, const ETreeTraversalOrder &eTraversalOrder) : m_pTree(pTree), 
                                                                                                                           m_uPosition(uPosition), 
                                                                                                                           m_eTraversalOrder(eTraversalOrder)
        {
            
            Z_ASSERT_ERROR(pTree != null_z, "Invalid argument: The pointer to the tree cannot be null");
            Z_ASSERT_WARNING(pTree->GetCapacity() > uPosition || 
                              uPosition == NTree::END_POSITION_BACKWARD || 
                              uPosition == NTree::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the capacity of the tree");
            Z_ASSERT_ERROR(eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder, string_z("The traversal order specified (") + eTraversalOrder.ToString() + ") is not supported. The only traversal order available currently is: DepthFirstPreOrder.");

            if(pTree == null_z || 
               (pTree->GetCapacity() <= uPosition && uPosition != NTree::END_POSITION_BACKWARD && uPosition != NTree::END_POSITION_FORWARD) || 
               pTree->IsEmpty())
                m_uPosition = NTree::END_POSITION_FORWARD;
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same tree as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstNTreeIterator& operator=(const ConstNTreeIterator &iterator)
        {
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "The input iterator points to a different tree");
            Z_ASSERT_WARNING(m_eTraversalOrder == iterator.m_eTraversalOrder, "The iterators have different traversal order.");

            if(m_pTree == iterator.m_pTree)
            {
                m_uPosition = iterator.m_uPosition;
            }

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T& operator*() const
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            Z_ASSERT_ERROR(m_uPosition != NTree::END_POSITION_FORWARD && m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return *(m_pTree->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T* operator->() const
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            Z_ASSERT_ERROR(m_uPosition != NTree::END_POSITION_FORWARD && m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return m_pTree->m_pElementBasePointer + m_uPosition;
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        ConstNTreeIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator (replacing ConstNTreeIterator with ConstNTreeIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            ConstNTreeIterator iteratorCopy = *this;

            if(m_uPosition != NTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          1
                    //         /|\
                    //        / | \
                    //       2  5  6
                    //      / \     \
                    //     /   \     \
                    //    3     4     7

                    if(m_uPosition != NTree::END_POSITION_BACKWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetFirstChild() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no children

                            if(pNode->GetNext() == NTree::END_POSITION_FORWARD)
                            {
                                // This node has no more brothers

                                // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                while(pNode->GetParent() != NTree::END_POSITION_FORWARD && 
                                      (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext() == NTree::END_POSITION_FORWARD)
                                {
                                    // Visits current node's parent
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetParent();
                                }

                                if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                                {
                                    // It reached the root node, all the nodes have been visited
                                    m_uPosition = NTree::END_POSITION_FORWARD;
                                }
                                else
                                {
                                    // It finds an ascendant whose brothers haven't been visited yet
                                    m_uPosition = (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext();
                                }
                            }
                            else // pNode->GetNext() == NTree::END_POSITION_FORWARD
                            {
                                // The next brother is visited
                                m_uPosition = pNode->GetNext();
                            }
                        }
                        else // pNode->GetFirstChild() == NTree::END_POSITION_FORWARD
                        {
                            // The first child of the current node is visited
                            m_uPosition = pNode->GetFirstChild();
                        }
                    }
                    else // m_uPosition != NTree::END_POSITION_BACKWARD
                    {
                        if(m_pTree->m_uRoot != NTree::END_POSITION_FORWARD)
                        {
                            this->MoveFirst();
                        }
                        else
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_FORWARD;
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_FORWARD)
            else if(m_uPosition == NTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        ConstNTreeIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator (replacing ConstNTreeIterator with ConstNTreeIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            ConstNTreeIterator iteratorCopy = *this;

            if(m_uPosition != NTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          7
                    //         /|\
                    //        / | \
                    //       6  3  2
                    //      / \     \
                    //     /   \     \
                    //    5     4     1

                    if(m_uPosition != NTree::END_POSITION_FORWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetPrevious() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no previous brother

                            if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = NTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
                            }
                        }
                        else
                        {
                            // The current node has a previous brother
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetPrevious();

                            // Searches for the last child of the deepest descendant
                            while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                            {
                                pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                                while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                                {
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                                }
                            }

                            m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_FORWARD
                    {
                        if(m_pTree->m_uRoot != NTree::END_POSITION_FORWARD)
                        {
                            this->MoveLast();
                        }
                        else
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_BACKWARD;
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_BACKWARD)
            else if(m_uPosition == NTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstNTreeIterator& operator++()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != NTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          1
                    //         /|\
                    //        / | \
                    //       2  5  6
                    //      / \     \
                    //     /   \     \
                    //    3     4     7

                    if(m_uPosition != NTree::END_POSITION_BACKWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetFirstChild() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no children

                            if(pNode->GetNext() == NTree::END_POSITION_FORWARD)
                            {
                                // This node has no more brothers
                                // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                while(pNode->GetParent() != NTree::END_POSITION_FORWARD && 
                                      (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext() == NTree::END_POSITION_FORWARD)
                                {
                                    // Visits current node's parent
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetParent();
                                }

                                if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                                {
                                    // It reached the root node, all the nodes have been visited
                                    m_uPosition = NTree::END_POSITION_FORWARD;
                                }
                                else // pNode->GetParent()->GetNext() != NTree::END_POSITION_FORWARD
                                {
                                    // It finds an ascendant whose brothers haven't been visited yet
                                    m_uPosition = (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext();
                                }
                            }
                            else
                            {
                                // The next brother is visited
                                m_uPosition = pNode->GetNext();
                            }
                        }
                        else
                        {
                            // The first child of the current node is visited
                            m_uPosition = pNode->GetFirstChild();
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_BACKWARD
                    {
                        if(m_pTree->IsEmpty())
                        {
                            m_uPosition = NTree::END_POSITION_FORWARD;
                        }
                        else
                        {
                            this->MoveFirst();
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_FORWARD)
            else if(m_uPosition == NTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstNTreeIterator& operator--()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition != NTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          7
                    //         /|\
                    //        / | \
                    //       6  3  2
                    //      / \     \
                    //     /   \     \
                    //    5     4     1

                    if(m_uPosition != NTree::END_POSITION_FORWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetPrevious() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no previous brother

                            if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = NTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
                            }
                        }
                        else
                        {
                            // The current node has a previous brother
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetPrevious();

                            // Searches for the last child of the deepest descendant
                            while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                            {
                                pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                                while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                                {
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                                }
                            }

                            m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_FORWARD
                    {
                        if(m_pTree->IsEmpty())
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_BACKWARD;
                        }
                        else
                        {
                            this->MoveLast();
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_BACKWARD)
            else if(m_uPosition == NTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same tree to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same tree; False otherwise.
        /// </returns>
        bool operator==(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            return m_uPosition == iterator.m_uPosition && m_pTree == iterator.m_pTree;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different tree is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different tree; False otherwise.
        /// </returns>
        bool operator!=(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            return m_uPosition != iterator.m_uPosition || m_pTree != iterator.m_pTree;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != NTree::END_POSITION_FORWARD &&
               m_uPosition != NTree::END_POSITION_BACKWARD)
            {
                NTree::ConstNTreeIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator does not equal the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != NTree::END_POSITION_BACKWARD &&
               m_uPosition != NTree::END_POSITION_FORWARD)
            {
                NTree::ConstNTreeIterator iteratorFromThis = *this;

                // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                    ++iteratorFromThis;

                // If the iterator equals the input iterator, input iterator is greater than resident one
                bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
            }

            return bResult;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    NTree::ConstNTreeIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator does not equal the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition != iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different trees or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstNTreeIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pTree == iterator.m_pTree, "Iterators point to different trees");

            bool bResult = false;

            if(m_pTree == iterator.m_pTree)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    NTree::ConstNTreeIterator iteratorFromThis = *this;

                    // One iterator is moved forward till it either reaches the position of the input iterator or the end position
                    while(!iteratorFromThis.IsEnd() && iterator.m_uPosition != iteratorFromThis.m_uPosition)
                        ++iteratorFromThis;

                    // If the iterator equals the input iterator, input iterator is greater than resident one
                    bResult = iterator.m_uPosition == iteratorFromThis.m_uPosition;
                }
            }

            return bResult;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the tree.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid.");

            return m_uPosition == NTree::END_POSITION_BACKWARD || m_uPosition == NTree::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the tree, distinguishing which of them.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first element and the position immediately after the last element are cosidered end
        /// positions; therefore, this method can be used for both forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <param name="eIterationDirection">[IN] The iteration direction used to identify which of the end positions is checked.</param>
        /// <returns>
        /// True if the iterator is pointing to the position after the last element when iterating forward or if it is
        /// pointing to the position immediately before the first position when iterating backward; False otherwise.
        /// </returns>
        bool IsEnd(const EIterationDirection &eIterationDirection) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid.");

            return (eIterationDirection == EIterationDirection::E_Backward && m_uPosition == NTree::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EIterationDirection::E_Forward  && m_uPosition == NTree::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = NTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // In this order, the first node will be always the root
                    m_uPosition = m_pTree->m_uRoot;
                }
            }
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = NTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // The current node has a previous brother
                    NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_pTree->m_uRoot;

                    // Searches for the last child of the deepest descendant
                    while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                    {
                        pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                        while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                        {
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                        }
                    }

                    m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                }
            }
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a tree may have been shortened while the iterator
        /// was pointing to its last position). If the tree to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pTree != null_z && 
                   (m_uPosition < m_pTree->m_nodeAllocator.GetPoolSize() / sizeof(Node) ||
                    m_uPosition == NTree::END_POSITION_BACKWARD ||
                    m_uPosition == NTree::END_POSITION_FORWARD);
        }
        
        /// <summary>
        /// Gets the order in which the iterator traverses the tree.
        /// </summary>
        /// <returns>
        /// The tree traversal order.
        /// </returns>
        ETreeTraversalOrder GetTraversalOrder() const
        {
            return m_eTraversalOrder;
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const NTree* GetContainer() const
        {
            return m_pTree;
        }
        
        /// <summary>
        /// Gets the "physical" position of the container's allocated buffer where the iterator is pointing to.
        /// </summary>
        /// <remarks>
        /// This method is intended to be used internally by containers, users should not call it.
        /// </remarks>
        /// <returns>
        /// The position the iterator points to.
        /// </returns>
        puint_z GetInternalPosition() const
        {
            return m_uPosition;
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// The tree the iterator points to.
        /// </summary>
        const NTree* m_pTree;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        puint_z m_uPosition;

        /// <summary>
        /// The order in which elements will be visited.
        /// </summary>
        const ETreeTraversalOrder m_eTraversalOrder;

    }; // ConstNTreeIterator

    
    /// <summary>
    /// Iterator that steps once per element of an n-ary tree, in a concrete order. Since the traversal order may vary, the meaning of the words
    /// "last", "first" and "next", used in the documentation of this class, can be different depending on such order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a tree, it cannot point to another tree ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the tree.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class NTreeIterator : public NTree::ConstNTreeIterator
    {
        
    protected:
    
        using NTree::ConstNTreeIterator::m_pTree;
        using NTree::ConstNTreeIterator::m_uPosition;
        using NTree::ConstNTreeIterator::m_eTraversalOrder;


        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the tree to iterate through, the position to physically point to and the traversal order. This constructor is intended 
        /// to be used internally, use GetIterator method of the NTree class instead.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pTree">[IN] The tree to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of tree elements, but the physical.
        /// It must be lower than the capacity of the tree.</param>
        /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
        NTreeIterator(const NTree* pTree, const puint_z uPosition, const ETreeTraversalOrder &eTraversalOrder) : NTree::ConstNTreeIterator(pTree, uPosition, eTraversalOrder)
        {
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same tree as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        NTreeIterator& operator=(const NTreeIterator &iterator)
        {
            NTree::ConstNTreeIterator::operator=(iterator);
            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the tree element");

            Z_ASSERT_ERROR(m_uPosition != NTree::END_POSITION_FORWARD && m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return *(m_pTree->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the tree element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the tree element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the tree element");

            Z_ASSERT_ERROR(m_uPosition != NTree::END_POSITION_FORWARD && m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the tree element");

            return m_pTree->m_pElementBasePointer + m_uPosition;
        }

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        NTreeIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator (replacing ConstNTreeIterator with NTreeIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            NTreeIterator iteratorCopy = *this;

            if(m_uPosition != NTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          1
                    //         /|\
                    //        / | \
                    //       2  5  6
                    //      / \     \
                    //     /   \     \
                    //    3     4     7

                    if(m_uPosition != NTree::END_POSITION_BACKWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetFirstChild() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no children

                            if(pNode->GetNext() == NTree::END_POSITION_FORWARD)
                            {
                                // This node has no more brothers

                                // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                while(pNode->GetParent() != NTree::END_POSITION_FORWARD && 
                                      (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext() == NTree::END_POSITION_FORWARD)
                                {
                                    // Visits current node's parent
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetParent();
                                }

                                if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                                {
                                    // It reached the root node, all the nodes have been visited
                                    m_uPosition = NTree::END_POSITION_FORWARD;
                                }
                                else
                                {
                                    // It finds an ascendant whose brothers haven't been visited yet
                                    m_uPosition = (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext();
                                }
                            }
                            else // pNode->GetNext() == NTree::END_POSITION_FORWARD
                            {
                                // The next brother is visited
                                m_uPosition = pNode->GetNext();
                            }
                        }
                        else // pNode->GetFirstChild() == NTree::END_POSITION_FORWARD
                        {
                            // The first child of the current node is visited
                            m_uPosition = pNode->GetFirstChild();
                        }
                    }
                    else // m_uPosition != NTree::END_POSITION_BACKWARD
                    {
                        if(m_pTree->m_uRoot != NTree::END_POSITION_FORWARD)
                        {
                            this->MoveFirst();
                        }
                        else
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_FORWARD;
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_FORWARD)
            else if(m_uPosition == NTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

            return iteratorCopy;
        }

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        NTreeIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator (replacing ConstNTreeIterator with NTreeIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            NTreeIterator iteratorCopy = *this;

            if(m_uPosition != NTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          7
                    //         /|\
                    //        / | \
                    //       6  3  2
                    //      / \     \
                    //     /   \     \
                    //    5     4     1

                    if(m_uPosition != NTree::END_POSITION_FORWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetPrevious() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no previous brother

                            if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = NTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
                            }
                        }
                        else
                        {
                            // The current node has a previous brother
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetPrevious();

                            // Searches for the last child of the deepest descendant
                            while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                            {
                                pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                                while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                                {
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                                }
                            }

                            m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_FORWARD
                    {
                        if(m_pTree->m_uRoot != NTree::END_POSITION_FORWARD)
                        {
                            this->MoveLast();
                        }
                        else
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_BACKWARD;
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_BACKWARD)
            else if(m_uPosition == NTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

            return iteratorCopy;
        }

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        NTreeIterator& operator++()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition != NTree::END_POSITION_FORWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          1
                    //         /|\
                    //        / | \
                    //       2  5  6
                    //      / \     \
                    //     /   \     \
                    //    3     4     7

                    if(m_uPosition != NTree::END_POSITION_BACKWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetFirstChild() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no children

                            if(pNode->GetNext() == NTree::END_POSITION_FORWARD)
                            {
                                // This node has no more brothers
                                // Goes up in the tree until it finds a parent with non-visited brothers or it reaches the root node
                                while(pNode->GetParent() != NTree::END_POSITION_FORWARD && 
                                      (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext() == NTree::END_POSITION_FORWARD)
                                {
                                    // Visits current node's parent
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetParent();
                                }

                                if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                                {
                                    // It reached the root node, all the nodes have been visited
                                    m_uPosition = NTree::END_POSITION_FORWARD;
                                }
                                else // pNode->GetParent()->GetNext() != NTree::END_POSITION_FORWARD
                                {
                                    // It finds an ascendant whose brothers haven't been visited yet
                                    m_uPosition = (m_pTree->m_pNodeBasePointer + pNode->GetParent())->GetNext();
                                }
                            }
                            else
                            {
                                // The next brother is visited
                                m_uPosition = pNode->GetNext();
                            }
                        }
                        else
                        {
                            // The first child of the current node is visited
                            m_uPosition = pNode->GetFirstChild();
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_BACKWARD
                    {
                        if(m_pTree->IsEmpty())
                        {
                            m_uPosition = NTree::END_POSITION_FORWARD;
                        }
                        else
                        {
                            this->MoveFirst();
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_FORWARD)
            else if(m_uPosition == NTree::END_POSITION_BACKWARD)
            {
                this->MoveFirst();
            }

            return *this;
        }

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        NTreeIterator& operator--()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != NTree::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition != NTree::END_POSITION_BACKWARD)
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    //          7
                    //         /|\
                    //        / | \
                    //       6  3  2
                    //      / \     \
                    //     /   \     \
                    //    5     4     1

                    if(m_uPosition != NTree::END_POSITION_FORWARD)
                    {
                        NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_uPosition;

                        if(pNode->GetPrevious() == NTree::END_POSITION_FORWARD)
                        {
                            // The current node has no previous brother

                            if(pNode->GetParent() == NTree::END_POSITION_FORWARD)
                            {
                                // The current node has no parent so it is the root, all the nodes have been visited
                                m_uPosition = NTree::END_POSITION_BACKWARD;
                            }
                            else
                            {
                                // The current node's parent is visited
                                m_uPosition = pNode->GetParent();
                            }
                        }
                        else
                        {
                            // The current node has a previous brother
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetPrevious();

                            // Searches for the last child of the deepest descendant
                            while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                            {
                                pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                                while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                                {
                                    pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                                }
                            }

                            m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                        }
                    }
                    else // m_uPosition == NTree::END_POSITION_FORWARD
                    {
                        if(m_pTree->IsEmpty())
                        {
                            // The tree is empty
                            m_uPosition = NTree::END_POSITION_BACKWARD;
                        }
                        else
                        {
                            this->MoveLast();
                        }
                    }
                }
            } // if(m_uPosition != NTree::END_POSITION_BACKWARD)
            else if(m_uPosition == NTree::END_POSITION_FORWARD)
            {
                this->MoveLast();
            }

            return *this;
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = NTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // In this order, the first node will be always the root
                    m_uPosition = m_pTree->m_uRoot;
                }
            }
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the tree is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ConstNTreeIterator

            if(m_pTree->IsEmpty())
            {
                m_uPosition = NTree::END_POSITION_FORWARD;
            }
            else
            {
                if(m_eTraversalOrder == ETreeTraversalOrder::E_DepthFirstPreOrder)
                {
                    // The current node has a previous brother
                    NTree::Node* pNode = m_pTree->m_pNodeBasePointer + m_pTree->m_uRoot;

                    // Searches for the last child of the deepest descendant
                    while(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
                    {
                        pNode = m_pTree->m_pNodeBasePointer + pNode->GetFirstChild();

                        while(pNode->GetNext() != NTree::END_POSITION_FORWARD)
                        {
                            pNode = m_pTree->m_pNodeBasePointer + pNode->GetNext();
                        }
                    }

                    m_uPosition = scast_z(pNode - m_pTree->m_pNodeBasePointer, puint_z);
                }
            }
        }

    }; // NTreeIterator
    

    // TYPEDEFS
    // --------------
public:

    typedef typename NTree::NTreeIterator Iterator;
    typedef typename NTree::ConstNTreeIterator ConstIterator;


   	// CONSTANTS
    // ---------------
public:
    
    /// <summary>
    /// Constant used to specify that the tree nodes have no maximum child nodes restriction.
    /// </summary>
    static const puint_z NO_MAXIMUM_CHILDREN = -1;

protected:

    /// <summary>
    /// Number of elements for which to reserve memory by default.
    /// </summary>
    static puint_z sm_uDefaultCapacity;
    
	/// <summary>
	/// Constant to symbolize the end of the sequence when the tree is traversed backward.
	/// </summary>
    static const puint_z END_POSITION_BACKWARD = -1;

    /// <summary>
    /// Constant to symbolize the absence of a node or the end of the sequence when the tree is traversed forward.
    /// </summary>
    static const puint_z END_POSITION_FORWARD = -2;

    /// <summary>
    /// The maximum number of child nodes per node.
    /// </summary>
    const puint_z MAX_CHILDREN;

private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;
    

    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Constructor that only receives the maximum number of child nodes per node in the tree.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero. Use the NO_MAXIMUM_CHILDREN constant to disable this restriction.</param>
    explicit NTree(const puint_z uMaximumChildren) : MAX_CHILDREN(uMaximumChildren),
                                                             m_elementAllocator(NTree::sm_uDefaultCapacity * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
                                                             m_nodeAllocator(NTree::sm_uDefaultCapacity * sizeof(NTree::Node), sizeof(NTree::Node), Alignment(alignof_z(NTree::Node))),
                                                             m_uRoot(NTree::END_POSITION_FORWARD),
                                                             m_pElementBasePointer(null_z),
                                                             m_pNodeBasePointer(null_z)
    {
        Z_ASSERT_ERROR(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");

        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pNodeBasePointer = scast_z(m_nodeAllocator.GetPointer(), NTree::Node*);
    }

    /// <summary>
    /// Constructor that receives the maximum number of child nodes per node in the tree and the initial capacity.
    /// </summary>
    /// <remarks>
    /// Once the maximum number of child nodes has been set, it cannot be changed in the future.
    /// </remarks>
    /// <param name="uMaximumChildren">[IN] The maximum number of child nodes per node. It must be greater than zero. Use the NO_MAXIMUM_CHILDREN constant to disable this restriction.</param>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory. It must be greater than zero.</param>
    NTree(const puint_z uMaximumChildren, const puint_z uInitialCapacity) :
                                                            MAX_CHILDREN(uMaximumChildren),
                                                            m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
                                                            m_nodeAllocator(uInitialCapacity * sizeof(NTree::Node), sizeof(NTree::Node), Alignment(alignof_z(NTree::Node))),
                                                            m_uRoot(NTree::END_POSITION_FORWARD),
                                                            m_pElementBasePointer(null_z),
                                                            m_pNodeBasePointer(null_z)
    {
        Z_ASSERT_ERROR(uMaximumChildren > 0, "The maximum number of children for every node of the tree must be greater than zero.");
        Z_ASSERT_ERROR(uInitialCapacity > 0, "The initial capacity of the tree must be greater than zero.");
        
        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pNodeBasePointer = scast_z(m_nodeAllocator.GetPointer(), NTree::Node*);
    }

    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every copied element, in an arbitrary order.
    /// </remarks>
    /// <param name="tree">[IN] The other tree to be copied.</param>
    NTree(const NTree &tree) :
                                MAX_CHILDREN(tree.MAX_CHILDREN),
                                m_elementAllocator(tree.GetCapacity() * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
                                m_nodeAllocator(tree.GetCapacity() * sizeof(NTree::Node), sizeof(NTree::Node), Alignment(alignof_z(NTree::Node))),
                                m_uRoot(tree.m_uRoot),
                                m_pElementBasePointer(null_z),
                                m_pNodeBasePointer(null_z)
    {
        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pNodeBasePointer = scast_z(m_nodeAllocator.GetPointer(), NTree::Node*);

        if(!tree.IsEmpty())
        {
            tree.m_elementAllocator.CopyTo(m_elementAllocator);
            tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

            NTree::NTreeIterator itSource = tree.GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);
            NTree::NTreeIterator itDestination = this->GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);

            for(; !itSource.IsEnd(); ++itSource, ++itDestination)
                new(&*itDestination) T(*itSource);
        }
    }

protected:

    // DESTRUCTOR
    // ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element will be called in an undetermined order.
    /// </remarks>
    ~NTree()
    {
        if(!this->IsEmpty())
            for(NTree::ConstNTreeIterator it = this->GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder); !it.IsEnd(); ++it)
                (*it).~T();
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// All the elements in the resident tree will be firstly removed, calling each element's destructor.
    /// The copy constructor is then called for every copied element, in an arbitrary order.
    /// </remarks>
    /// <param name="tree">[IN] The other tree to be copied. The maximum number of children per node in the tree must 
    /// be lower than or equal to the resident tree's.</param>
    /// <returns>
    /// A reference to the resultant n-ary tree.
    /// </returns>
    NTree& operator=(const NTree &tree)
    {
        Z_ASSERT_ERROR(this->MAX_CHILDREN >= tree.MAX_CHILDREN && this->MAX_CHILDREN != NTree::NO_MAXIMUM_CHILDREN, "The maximum number of children per node in the resident tree is lower than the input tree's.");

        if(this != &tree)
        {
            if(!this->IsEmpty())
                this->Clear();

            if(!tree.IsEmpty())
            {
                m_uRoot = tree.m_uRoot;

                if(this->GetCapacity() < tree.GetCapacity())
                    this->Reserve(tree.GetCapacity());

                tree.m_elementAllocator.CopyTo(m_elementAllocator);
                tree.m_nodeAllocator.CopyTo(m_nodeAllocator);

                NTree::NTreeIterator itSource = tree.GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);
                NTree::NTreeIterator itDestination = this->GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);

                for(; !itSource.IsEnd(); ++itSource, ++itDestination)
                    new(&*itDestination) T(*itSource);
            }
        }

        return *this;
    }
    
    /// <summary>
    /// Equality operator that checks whether two trees are equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other tree. Elements are compared using the tree's comparator.<br/>
    /// Trees are compared morphologically too, so if an element A is a child of another element B in one of the trees, this relation must exist in the other tree to be considered equal.
    /// </remarks>
    /// <param name="tree">[IN] The tree to compare to.</param>
    /// <returns>
    /// True if all the elements of both trees are equal and the trees have the same structure; False otherwise.
    /// </returns>
    bool operator==(const NTree &tree) const
    {
        bool bAreEqual = true;

        // If they are not the same instance
        if(this != &tree)
        {
            // If they have the same number of elements
            if(this->GetCount() == tree.GetCount())
            {
                // Both trees are traversed in the same order
                NTree::NTreeIterator itThis = this->GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);
                NTree::NTreeIterator itInput = tree.GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder);

                while(bAreEqual && !itThis.IsEnd())
                {
                    // Note: Both trees can have the same structure and be physically ordered differently in memory

                    NTree::Node* pCurrentNodeThis = m_pNodeBasePointer + itThis.GetInternalPosition();
                    NTree::Node* pCurrentNodeInput = tree.m_pNodeBasePointer + itInput.GetInternalPosition();

                    // The value of the current element is checked
                    bAreEqual = ComparatorT::Compare(*itThis, *itInput) == 0
                    // The relations of the current node are checked too
                                && ((pCurrentNodeThis->GetFirstChild() != NTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetFirstChild() != NTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetNext() != NTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetNext() != NTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetPrevious() != NTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetPrevious() != NTree::END_POSITION_FORWARD))
                                && ((pCurrentNodeThis->GetParent() != NTree::END_POSITION_FORWARD) == (pCurrentNodeInput->GetParent() != NTree::END_POSITION_FORWARD));

                    ++itThis;
                    ++itInput;
                }
            }
            else
                bAreEqual = false;
        }

        return bAreEqual;
    }
    
    /// <summary>
    /// Inequality operator that checks whether two trees are not equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other tree. Elements are compared using the tree's comparator.<br/>
    /// Trees are compared morphologically too, so if an element A is a child of another element B in one of the trees, this relation must exist in the other tree to be considered equal.
    /// </remarks>
    /// <param name="tree">[IN] The tree to compare to.</param>
    /// <returns>
    /// True if not all the elements of both trees are equal or if the trees do not have the same structure; False otherwise.
    /// </returns>
    bool operator!=(const NTree &tree) const
    {
        return !this->operator==(tree);
    }

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this tree will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const puint_z uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_elementAllocator.Reallocate(uNumberOfElements * sizeof(T));
            m_nodeAllocator.Reallocate(uNumberOfElements * sizeof(NTree::Node));
            m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
            m_pNodeBasePointer = scast_z(m_nodeAllocator.GetPointer(), NTree::Node*);
        }
    }

    /// <summary>
    /// Sets the root node of the tree.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, the root node will be created, calling the copy constructor of the new element.<br/>
    /// If there is already a root node, then it will be assigned to the input object, calling the assignment operator of
    /// the existing element.
    /// </remarks>
    /// <param name="newRoot">[IN] The new value of the root node.</param>
    void SetRootValue(const T &newRoot)
    {
        if(this->IsEmpty())
        {
            static const puint_z NO_PARENT_POSITION = NTree::END_POSITION_FORWARD;
            static const puint_z NO_PREVIOUS_POSITION = NTree::END_POSITION_FORWARD;
            static const puint_z NO_NEXT_POSITION = NTree::END_POSITION_FORWARD;
            static const puint_z NO_CHILD_POSITION = NTree::END_POSITION_FORWARD;

            T* pNewRoot = new(m_elementAllocator.Allocate()) T(newRoot);
            new(m_nodeAllocator.Allocate()) NTree::Node(NO_PARENT_POSITION, NO_NEXT_POSITION, NO_PREVIOUS_POSITION, NO_CHILD_POSITION);

            m_uRoot = pNewRoot - m_pElementBasePointer;
        }
        else
        {
            *this->GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder) = newRoot;
        }
    }
    
    /// <summary>
    /// Adds an element at the last position of the child node list.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, use the SetRootValue method.<br/>
    /// If the parent node already has the maximum number of child nodes, the new element will not be added.<br/>
    /// If the capacity of the tree is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the new element will be called.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the parent node to which the element will be added as a child. It must not point to an end position.</param>
    /// <param name="newElement">[IN] The value of the new element.</param>
    /// <returns>
    /// An iterator that points to the just added element. If it was not added, the iterator will point to an end position.
    /// </returns>
    NTreeIterator AddChild(const typename NTree::ConstNTreeIterator &parentNode, const T &newElement)
    {
        //        R
        //       / \
        //      0-...
        //     /|\
        //    0-1-2-X
        //
        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();
        
        puint_z uNewNodePosition = NTree::END_POSITION_FORWARD;

        // If the parent node has any child node
        if(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            NTree::Node* pCurrentNode = m_pNodeBasePointer + pParentNode->GetFirstChild();
            puint_z uNumberOfElements = 1U;

            // Navigates to the last child node
            while(pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
                ++uNumberOfElements;
            }

            Z_ASSERT_ERROR(uNumberOfElements < this->MAX_CHILDREN, string_z("It is not possible to add another child to this node, maximum allowed exceeded (") + string_z::FromInteger(this->MAX_CHILDREN) + ").");

            if(uNumberOfElements < this->MAX_CHILDREN)
            {
                // Reserves more memory if necessary
                if(this->GetCount() == this->GetCapacity())
                {
                    puint_z uLastNodePosition = pCurrentNode - m_pNodeBasePointer;
                    this->_ReallocateByFactor(this->GetCapacity() + 1U);
                    pCurrentNode = m_pNodeBasePointer + uLastNodePosition;
                }

                // Adds the child to the end of the child list
                NTree::Node* pNewNode = new(m_nodeAllocator.Allocate()) Node(parentNode.GetInternalPosition(), 
                                                                                NTree::END_POSITION_FORWARD, 
                                                                                pCurrentNode - m_pNodeBasePointer, 
                                                                                NTree::END_POSITION_FORWARD);

                uNewNodePosition = pNewNode - m_pNodeBasePointer;
                pCurrentNode->SetNext(uNewNodePosition);
                
                // Copies the new element
                new(m_elementAllocator.Allocate()) T(newElement);
            }
        }
        else
        {
            // Reserves more memory if necessary
            if(this->GetCount() == this->GetCapacity())
            {
                this->_ReallocateByFactor(this->GetCapacity() + 1U);
                pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();
            }

            // Adds the child as the first of the child list
            NTree::Node* pNewNode = new(m_nodeAllocator.Allocate()) Node(parentNode.GetInternalPosition(), 
                                                                            NTree::END_POSITION_FORWARD, 
                                                                            NTree::END_POSITION_FORWARD, 
                                                                            NTree::END_POSITION_FORWARD);

            uNewNodePosition = pNewNode - m_pNodeBasePointer;
            pParentNode->SetFirstChild(uNewNodePosition);

            // Copies the new element
            new(m_elementAllocator.Allocate()) T(newElement);
        }

        return NTree::NTreeIterator(this, uNewNodePosition, parentNode.GetTraversalOrder());
    }
    
    /// <summary>
    /// Removes an element from the tree and all its descendents.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    /// <param name="node">[IN] An iterator that points to the node to be removed. It must not point to an end position. The root element is a valid target.</param>
    /// <returns>
    /// An iterator that points to the next element (following the traversal order of the input iterator). If the element was the last one, the iterator will point to an end position.
    /// </returns>
    NTreeIterator Remove(const typename NTree::NTreeIterator &node)
    {
        //        X
        //       / \
        //      X-...
        //     /|\
        //    X-X-X...
        //
        
        Z_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pNode = m_pNodeBasePointer + node.GetInternalPosition();

        NTree::NTreeIterator resultantIterator = node;
        ++resultantIterator;

        NTree::Node* pCurrentNode = pNode;
        NTree::Node* pNodeToRemove = null_z;

        // Traverses the tree in any order to remove the entire subtree defined by the input node
        do
        {
            if(pCurrentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetFirstChild();
            }
            else if(pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
            }
            else
            {
                pNodeToRemove = pCurrentNode;

                if(pCurrentNode->GetPrevious() != NTree::END_POSITION_FORWARD)
                {
                    pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetPrevious();
                    pCurrentNode->SetNext(NTree::END_POSITION_FORWARD);
                }
                else if(pCurrentNode->GetParent() != NTree::END_POSITION_FORWARD)
                {
                    pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetParent();
                    pCurrentNode->SetFirstChild(NTree::END_POSITION_FORWARD);
                }
                else
                {
                    // The node being removed is the only one in the tree
                    m_uRoot = NTree::END_POSITION_FORWARD;
                    pCurrentNode = null_z;
                }

                // Removes the element
                T* pElement = m_pElementBasePointer + (pNodeToRemove - m_pNodeBasePointer);
                pElement->~T();
                m_elementAllocator.Deallocate(pElement);

                // Removes the node
                m_nodeAllocator.Deallocate(pNodeToRemove);
            }
        }
        while(pNodeToRemove != pNode);

        return resultantIterator;
    }
    
    /// <summary>
    /// Removes a child node, at a given position in the child list, and all its descendents.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be removed. It must not point to an end position.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the child in the parent's child list. It must be lower than the number of children in the list.</param>
    void RemoveChild(const typename NTree::ConstNTreeIterator &parentNode, const puint_z uChildIndex)
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        NTree::Node* pCurrentNode = pParentNode;

        Z_ASSERT_ERROR(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD, "The node has no children.");

        // If the node has children
        if(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            pCurrentNode = m_pNodeBasePointer + pParentNode->GetFirstChild();
            
            puint_z i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
                ++i;
            }

            Z_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

            // If the child node exists at the specified index
            if(i == uChildIndex)
            {
                // Removes the node
                puint_z uNodeToRemovedPosition = pCurrentNode - m_pNodeBasePointer;
                this->Remove(NTree::NTreeIterator(this, uNodeToRemovedPosition, parentNode.GetTraversalOrder()));
            }
        }
    }
    
    /// <summary>
    /// Inserts a child node at a given position in the child list.
    /// </summary>
    /// <remarks>
    /// If the tree is empty, use the SetRootValue method.<br/>
    /// If the parent node already has the maximum number of child nodes, the new element will not be added.<br/>
    /// If the capacity of the tree is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the new element will be called.
    /// </remarks>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be removed. It must not point to an end position.</param>
    /// <param name="newElement">[IN] The newElement of the new element.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the new child in the parent's child list. It must be lower than the number of children in the list.</param>
    /// <returns>
    /// An iterator that points to the just added element. If it was not added, the iterator will point to an end position.
    /// </returns>
    NTreeIterator InsertChild(const typename NTree::ConstNTreeIterator &parentNode, const T &newElement, const puint_z uChildIndex)
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X-X
        //
        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");

        puint_z uResultNodePosition = NTree::END_POSITION_FORWARD;

        // Reserves more memory if necessary
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        NTree::Node* pCurrentNode = pParentNode;
        puint_z uNewNodePosition = NTree::END_POSITION_FORWARD;

        Z_ASSERT_WARNING(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD, "The node has no children.");

        // If the node has children
        if(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            pCurrentNode = m_pNodeBasePointer + pParentNode->GetFirstChild();
            
            puint_z i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
                ++i;
            }

            // Counts how many child nodes are there
            NTree::Node* pCurrentAux = pCurrentNode;
            puint_z uNumberOfElements = i + 1U;

            while(pCurrentAux->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentAux = m_pNodeBasePointer + pCurrentAux->GetNext();
                ++uNumberOfElements;
            }

            Z_ASSERT_ERROR(uNumberOfElements < this->MAX_CHILDREN, string_z("It is not possible to insert another child to this node, maximum allowed exceeded (") + string_z::FromInteger(this->MAX_CHILDREN) + ").");

            if(uNumberOfElements < this->MAX_CHILDREN)
            {
                Z_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

                // If there is no children at the specified index
                if(i < uChildIndex)
                {
                    // Adds the node to the end of the child list
                    NTree::Node* pNewNode = new(m_nodeAllocator.Allocate()) Node(parentNode.GetInternalPosition(), 
                                                                                    NTree::END_POSITION_FORWARD, 
                                                                                    pCurrentNode - m_pNodeBasePointer, 
                                                                                    NTree::END_POSITION_FORWARD);

                    uNewNodePosition = pNewNode - m_pNodeBasePointer;
                    pCurrentNode->SetNext(uNewNodePosition);
                }
                else
                {
                    // Adds the node at the specified position
                    NTree::Node* pNewNode = new(m_nodeAllocator.Allocate()) Node(parentNode.GetInternalPosition(), 
                                                                                    pCurrentNode - m_pNodeBasePointer, 
                                                                                    pCurrentNode->GetPrevious(), 
                                                                                    NTree::END_POSITION_FORWARD);

                    uNewNodePosition = pNewNode - m_pNodeBasePointer;
                    pCurrentNode->SetPrevious(uNewNodePosition);

                    if(pNewNode->GetPrevious() == NTree::END_POSITION_FORWARD)
                        pParentNode->SetFirstChild(uNewNodePosition);
                    else
                        (m_pNodeBasePointer + pNewNode->GetPrevious())->SetNext(uNewNodePosition);
                }
            }
        }
        else // There are no children
        {
            // Adds the node as the first child node
            NTree::Node* pNewNode = new(m_nodeAllocator.Allocate()) Node(parentNode.GetInternalPosition(), 
                                                                            NTree::END_POSITION_FORWARD, 
                                                                            NTree::END_POSITION_FORWARD, 
                                                                            NTree::END_POSITION_FORWARD);

            uNewNodePosition = pNewNode - m_pNodeBasePointer;
            pParentNode->SetFirstChild(uNewNodePosition);
        }
            
        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);

        uResultNodePosition = uNewNodePosition;

        return NTree::NTreeIterator(this, uResultNodePosition, parentNode.GetTraversalOrder());
    }

    /// <summary>
    /// Gets an iterator that points to a given position in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the tree, starting at zero, to which the iterator will point. It must be lower than the number of elements in the tree.
    /// If it is out of bounds, the returned iterator will point to the end position.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    NTreeIterator GetIterator(const puint_z uIndex, const ETreeTraversalOrder &eTraversalOrder) const
    {
        Z_ASSERT_WARNING(uIndex < this->GetCount(), string_z("The input index (") + string_z::FromInteger(uIndex) + ") is out of bounds.");
        Z_ASSERT_WARNING(!this->IsEmpty(), "It is not possible to get an iterator that points to the given position, the tree is empty.");

        NTree::NTreeIterator iterator(this, 0, eTraversalOrder);
        iterator.MoveFirst();

        for(puint_z i = 0; i < uIndex && !iterator.IsEnd(); ++i)
            ++iterator;

        return iterator;
    }
    
    /// <summary>
    /// Empties the tree.
    /// </summary>
    /// <remarks>
    /// This is equivalent to removing the root node.<br/>
    /// The destructor of each element will be called in an undefined order, from bottom to top.
    /// </remarks>
    void Clear()
    {
        if(!this->IsEmpty())
            this->Remove(this->GetRoot(ETreeTraversalOrder::E_DepthFirstPreOrder));
        // Note: The traversal order does not affect the result
    }
    
    /// <summary>
    /// Gets a child of a node that occupies a given position in the child list.
    /// </summary>
    /// <param name="parentNode">[IN] The node whose child is to be obtained. It must not point to the end position.</param>
    /// <param name="uChildIndex">[IN] The position (zero-based index) of the child in the parent's child list. It must be lower than the number of children in the list.</param>
    /// <returns>
    /// An iterator that points to the child node. If there is not a child at the given position, the iterator will point to the end position.
    /// </returns>
    NTreeIterator GetChild(const typename NTree::ConstNTreeIterator &parentNode, const puint_z uChildIndex) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        NTree::NTreeIterator itResult(this, NTree::END_POSITION_FORWARD, parentNode.GetTraversalOrder());

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        NTree::Node* pCurrentNode = pParentNode;

        // If the node has children
        if(pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            pCurrentNode = m_pNodeBasePointer + pParentNode->GetFirstChild();
            
            puint_z i = 0;

            // Gets the child node at the specified index
            while(i < uChildIndex && pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
                ++i;
            }

            Z_ASSERT_WARNING(i == uChildIndex, "There is not a child node at the specified position index.");

            // If the child node exists at the specified index
            if(i == uChildIndex)
            {
                // Gets the node
                puint_z uNodeToRemovedPosition = pCurrentNode - m_pNodeBasePointer;
                itResult = NTree::NTreeIterator(this, uNodeToRemovedPosition, parentNode.GetTraversalOrder());
            }
        }

        return itResult;
    }
    
    /// <summary>
    /// Gets the parent of a node.
    /// </summary>
    /// <param name="node">[IN] The node whose parent is to be obtained. It must not point to the end position.</param>
    /// <returns>
    /// An iterator that points to the parent node. If the node does not have a parent, the iterator will point to the end position.
    /// </returns>
    NTreeIterator GetParent(const typename NTree::ConstNTreeIterator &node) const
    {
        //        X
        //       / \
        //      X-...
        //     /|\
        //    N-N-N
        //

        Z_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pNode = m_pNodeBasePointer + node.GetInternalPosition();

        return NTree::NTreeIterator(this, pNode->GetParent(), node.GetTraversalOrder());
    }
    
    /// <summary>
    /// Gets the first element in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the first element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    NTreeIterator GetFirst(const ETreeTraversalOrder &eTraversalOrder) const
    {
        NTree::NTreeIterator itFirst = this->GetRoot(eTraversalOrder);
        itFirst.MoveFirst();
        return itFirst;
    }
    
    /// <summary>
    /// Gets the number of child nodes of a parent node.
    /// </summary>
    /// <param name="parentNode">[IN] The node whose children are to be counted. It must not point to the end position.</param>
    /// <returns>
    /// The number of child nodes.
    /// </returns>
    puint_z GetChildrenCount(const typename NTree::ConstNTreeIterator &parentNode) const
    {
        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        puint_z uCount = 0;

        // Gets node pointer and position
        NTree::Node* pCurrentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        // If the node has children
        if(pCurrentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetFirstChild();

            ++uCount; // At least, one

            // Counts the children
            while(pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
            {
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();
                ++uCount;
            }
        }

        return uCount;
    }
    
    /// <summary>
    /// Checks whether a node has children or not.
    /// </summary>
    /// <param name="parentNode">[IN] The node to be checked. It must not point to the end position.</param>
    /// <returns>
    /// True if the node has any child; False otherwise.
    /// </returns>
    bool HasChildren(const typename NTree::ConstNTreeIterator &parentNode) const
    {
        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        return pParentNode->GetFirstChild() != NTree::END_POSITION_FORWARD;
    }
    
    /// <summary>
    /// Checks whether a node has a parent or not. Only a root node lacks parent.
    /// </summary>
    /// <param name="node">[IN] The node whose parent is to be checked. It must not point to the end position.</param>
    /// <returns>
    /// True if the node has parent; False otherwise.
    /// </returns>
    bool HasParent(const typename NTree::ConstNTreeIterator &node) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        Z_ASSERT_ERROR(node.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!node.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pNode = m_pNodeBasePointer + node.GetInternalPosition();

        return pNode->GetParent() != NTree::END_POSITION_FORWARD;
    }

    /// <summary>
    /// Gets the root node of the tree, which is independent from the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited, used to create the iterator that points to the root.</param>
    /// <returns>
    /// An iterator that points to the root element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    NTreeIterator GetRoot(const ETreeTraversalOrder &eTraversalOrder) const
    {
        return NTree::NTreeIterator(this, m_uRoot, eTraversalOrder);
    }
    
    /// <summary>
    /// Checks whether any element in the tree has the same value as a given element.
    /// </summary>
    /// <remarks>
    /// Elements are compared to the provided value using the container's comparator, in an arbitrary order.<br/>
    /// </remarks>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <returns>
    /// True if the element is present in the tree; False otherwise.
    /// </returns>
    bool Contains(const T &element) const
    {
        NTree::ConstNTreeIterator itElement = this->GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);

        while(!itElement.IsEnd() && ComparatorT::Compare(*itElement, element) != 0)
            ++itElement;

        return !itElement.IsEnd();
    }
    
    /// <summary>
    /// Searches for a given element and obtains its position.
    /// </summary>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the position of the first occurrence of the element, depending on the traversal order. If the element is not present in the tree, 
    /// the iterator will point to the end position.
    /// </returns>
    NTreeIterator PositionOf(const T &element, const ETreeTraversalOrder &eTraversalOrder) const
    {
        NTree::NTreeIterator itElement = this->GetFirst(ETreeTraversalOrder::E_DepthFirstPreOrder);

        while(!itElement.IsEnd() && ComparatorT::Compare(*itElement, element) != 0)
            ++itElement;

        return itElement;
    }
    
    /// <summary>
    /// Searches for a given element, starting at a concrete point, and obtains its position.
    /// </summary>
    /// <param name="element">[IN] The value of the element to search for.</param>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <param name="startPosition">[IN] An iterator that points to the node from which to start searching. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the position of the first occurrence of the element, starting at the given position, depending on the traversal order. If the element is not found, 
    /// the iterator will point to the end position.
    /// </returns>
    NTreeIterator PositionOf(const T &element, const ETreeTraversalOrder &eTraversalOrder, const typename NTree::ConstNTreeIterator startPosition) const
    {
        Z_ASSERT_ERROR(!startPosition.IsEnd(), "The start position must not point to the end position.");

        NTree::NTreeIterator itElement = NTree::NTreeIterator(this, startPosition.GetInternalPosition(), startPosition.GetTraversalOrder());

        while(!itElement.IsEnd() && ComparatorT::Compare(*itElement, element) != 0)
            ++itElement;

        return itElement;
    }
    
    /// <summary>
    /// Gets the first child in the child list of a given node.
    /// </summary>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be obtained. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the first child node. If the node has no children, the resultant iterator will point to the end position.
    /// </returns>
    NTreeIterator GetFirstChild(const typename NTree::ConstNTreeIterator &parentNode) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    0-X-X
        //

        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        // Gets node pointer and position
        NTree::Node* pParentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        return NTree::NTreeIterator(this, pParentNode->GetFirstChild(), parentNode.GetTraversalOrder());
    }
    
    /// <summary>
    /// Gets the last child in the child list of a given node.
    /// </summary>
    /// <param name="parentNode">[IN] An iterator that points to the node whose child is to be obtained. It must not point to an end position.</param>
    /// <returns>
    /// An iterator that points to the last child node. If the node has no children, the resultant iterator will point to the end position.
    /// </returns>
    NTreeIterator GetLastChild(const typename NTree::ConstNTreeIterator &parentNode) const
    {
        //        R
        //       / \
        //      X-...
        //     /|\
        //    X-X-X
        //

        Z_ASSERT_ERROR(parentNode.IsValid(), "The input iterator is not valid.");
        Z_ASSERT_ERROR(!parentNode.IsEnd(), "The input iterator must not point to an end position.");
        Z_ASSERT_ERROR(!this->IsEmpty(), "The tree is empty, there are no elements to remove.");

        NTree::NTreeIterator itResult(this, NTree::END_POSITION_FORWARD, parentNode.GetTraversalOrder());

        // Gets node pointer and position
        NTree::Node* pCurrentNode = m_pNodeBasePointer + parentNode.GetInternalPosition();

        // If the node has children
        if(pCurrentNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetFirstChild();

            // Gets the last child
            while(pCurrentNode->GetNext() != NTree::END_POSITION_FORWARD)
                pCurrentNode = m_pNodeBasePointer + pCurrentNode->GetNext();

            // Gets the node
            puint_z uLastChildPosition = pCurrentNode - m_pNodeBasePointer;
            itResult = NTree::NTreeIterator(this, uLastChildPosition, parentNode.GetTraversalOrder());
        }

        return itResult;
    }
    
    /// <summary>
    /// Gets the last element in the tree, depending on the traversal order.
    /// </summary>
    /// <param name="eTraversalOrder">[IN] The order in which the elements of the tree will be visited.</param>
    /// <returns>
    /// An iterator that points to the last element. If the tree is empty, the iterator will point to the end position.
    /// </returns>
    NTreeIterator GetLast(const ETreeTraversalOrder &eTraversalOrder) const
    {
        NTree::NTreeIterator itLast = this->GetRoot(eTraversalOrder);
        itLast.MoveLast();
        return itLast;
    }
    
    /// <summary>
    /// Performs a shallow copy of the contents of the tree to another tree.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// If the capacity of the destination tree is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationTree">[IN/OUT] The destination array to which the contents will be copied. The maximum number of children per node in the tree must 
    /// be greater than or equal to the resident tree's.</param>
    void Clone(NTree &destinationTree) const
    {
        Z_ASSERT_ERROR(destinationTree.MAX_CHILDREN >= this->MAX_CHILDREN, "The maximum number of children per node in the destination tree is lower than the source tree's.");

        if(destinationTree.GetCapacity() < this->GetCapacity())
            destinationTree.Reserve(this->GetCapacity());

        this->m_nodeAllocator.CopyTo(destinationTree.m_nodeAllocator);
        this->m_elementAllocator.CopyTo(destinationTree.m_elementAllocator);
        destinationTree.m_uRoot = m_uRoot;
    }
    
    /// <summary>
    /// Swaps two elements of the tree.
    /// </summary>
    /// <remarks>
    /// The tree must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="elementA">[IN] The position of an element. It must not be an end position.</param>
    /// <param name="elementB">[IN] The position of the other element. It must not be an end position.</param>
    void Swap(const typename NTree::NTreeIterator elementA, const typename NTree::NTreeIterator elementB)
    {
        Z_ASSERT_ERROR(!elementA.IsEnd(), "The element A position is an end position.");
        Z_ASSERT_ERROR(!elementB.IsEnd(), "The element B position is an end position.");
        Z_ASSERT_ERROR(elementA.IsValid(), "The element A's position is not valid.");
        Z_ASSERT_ERROR(elementB.IsValid(), "The element B's position is not valid.");
        Z_ASSERT_WARNING(elementA != elementB, "Both elements are the same.");
        
        T* pElementA = &*elementA;
        T* pElementB = &*elementB;

        u8_z arBytes[sizeof(T)];
        memcpy(arBytes,   pElementA, sizeof(T));
        memcpy(pElementA, pElementB, sizeof(T));
        memcpy(pElementB, arBytes,   sizeof(T));
    }

private:

    /// <summary>
    /// Updates the reference positions of all the nodes related to one given node.
    /// </summary>
    /// <remarks>
    /// This is used when a node is moved to a different position in the internal buffer.
    /// </remarks>
    /// <param name="pNode">[IN] The node whose related nodes are to be updated.</param>
    void _UpdateNodesPositions(typename NTree::Node* pNode)
    {
        const puint_z NODE_POSITION = pNode - m_pNodeBasePointer;

        // Updates the first child node position of its parent
        if(pNode->GetParent() != NTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            //  v
            // [x]
            m_pNodeBasePointer[pNode->GetParent()].SetFirstChild(NODE_POSITION);
        }

        // Updates the previous node position of its previous node
        if(pNode->GetPrevious() != NTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            // [ ] --> [x]
            m_pNodeBasePointer[pNode->GetPrevious()].SetNext(NODE_POSITION);
        }

        // Updates the next node position of its next node
        if(pNode->GetNext() != NTree::END_POSITION_FORWARD)
        {
            // [ ]
            //  |
            // [x] <-- [ ]
            m_pNodeBasePointer[pNode->GetNext()].SetPrevious(NODE_POSITION);
        }

        // Updates the parent node position of all its child nodes
        if(pNode->GetFirstChild() != NTree::END_POSITION_FORWARD)
        {
            // [x] <
            //  ^   \
            //  |    \
            // [ ] -- [ ]
            NTree::Node* pNextNode = m_pNodeBasePointer[pNode->GetFirstChild()];
            while(pNextNode != null_z)
            {
                pNextNode->SetParent(NODE_POSITION);

                if(pNextNode->GetNext() != NTree::END_POSITION_FORWARD)
                    pNextNode = m_pNodeBasePointer[pNextNode->GetNext()];
                else
                    pNextNode = null_z;
            }
        }
    }

    /// <summary>
    /// Increases the capacity of the tree, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const puint_z uNumberOfElements)
    {
        const puint_z FINAL_CAPACITY = scast_z(scast_z(uNumberOfElements, float) * NTree::REALLOCATION_FACTOR, puint_z);
        this->Reserve(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------

public:

    /// <summary>
    /// Gets the element allocator.
    /// </summary>
    /// <returns>
    /// The element allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_elementAllocator;
    }

    /// <summary>
    /// Gets the capacity of the tree, which means the number of elements that can be added before they are reallocated to
    /// another part of memory.
    /// </summary>
    /// <returns>
    /// The capacity of the tree.
    /// </returns>
    puint_z GetCapacity() const
    {
        return m_elementAllocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Gets the number of elements added to the tree.
    /// </summary>
    /// <returns>
    /// The number of elements in the tree.
    /// </returns>
    puint_z GetCount() const
    {
        return m_elementAllocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Indicates whether the tree is empty or not.
    /// </summary>
    /// <returns>
    /// True if the tree is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_elementAllocator.GetAllocatedBytes() == 0;
    }
    
    /// <summary>
    /// Gets the maximum number of child nodes a node can have. It is set when the tree is created.
    /// </summary>
    /// <returns>
    /// The number of child nodes per node. If there is no restriction, the NO_MAXIMUM_CHILDREN constant will be retuned.
    /// </returns>
    puint_z GetMaximumChildren() const
    {
        return this->MAX_CHILDREN;
    }


    // ATTRIBUTES
    // ---------------

protected:

    /// <summary>
    /// The allocator which stores the tree elements.
    /// </summary>
    AllocatorT m_elementAllocator;

      /// <summary>
    /// The allocator which stores the tree nodes for internal operations.
    /// </summary>
    AllocatorT m_nodeAllocator;

    /// <summary>
    /// The position of the root node in the internal buffer.
    /// </summary>
    puint_z m_uRoot;
    
    /// <summary>
    /// A pointer to the buffer stored in the memory allocator, casted to the element type, intended to improve overall performance.
    /// </summary>
    T* m_pElementBasePointer;

    /// <summary>
    /// A pointer to the buffer stored in the memory allocator, casted to the Node type, intended to improve overall performance.
    /// </summary>
    Node* m_pNodeBasePointer;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template <class T, class AllocatorT, class ComparatorT>
puint_z NTree<T, AllocatorT, ComparatorT>::sm_uDefaultCapacity = 1;

template<class T, class AllocatorT, class ComparatorT>
float NTree<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;

} // namespace z


#endif // __NTREE__
