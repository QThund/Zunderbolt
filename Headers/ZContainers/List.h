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

#ifndef __LIST__
#define __LIST__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"
#include "ZCommon/Assertions.h"
#include "ZMemory/PoolAllocator.h"
#include "ZMemory/Alignment.h"
#include "SComparatorDefault.h"
#include "ZMemory/AllocationOperators.h"
#include "ZContainers/EIterationDirection.h"



namespace z
{

/// <summary>
/// Represents a double linked list of elements that can be accessed either sequentally or arbitrarily, using a zero-based index.
/// </summary>
/// <remarks>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T"> The type of the list elements.</typeparam>
/// <typeparam name="AllocatorT"> The allocator used to reserve memory. The default type is PoolAllocator.</typeparam>
/// <typeparam name="ComparatorT"> The comparator. The default type is SComparatorDefault.</typeparam>
template <class T, class AllocatorT = PoolAllocator, class ComparatorT = SComparatorDefault<T> >
class List
{
    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;


    // INTERNAL CLASSES
    // -----------------

protected:

    /// <summary>
    /// Class intended to store the information needed to link one element of the list to another.
    /// </summary>
    class Link
    {
        // CONSTRUCTORS
        // ---------------

    public:

        /// <summary>
        /// Constructor with the positions in the allocated memory chunk to the previous and next elements,
        /// passed by parameter.
        /// </summary>
        /// <param name="uPrevious">[IN] Position of the previous element.</param>
        /// <param name="uNext">[IN] Position of the next element.</param>
        Link(const puint_z uPrevious, const puint_z uNext) :
                m_uNext(uNext),
                m_uPrevious(uPrevious)
                
        {
        }


        // PROPERTIES
        // ---------------

        /// <summary>
        /// Returns the index of the next element in the list.
        /// </summary>
        /// <returns>
        /// The index of the next element in the list. Returns List::END_POSITION_FORWARD constant if there is no previous element.
        /// </returns>
        puint_z GetNext() const
        {
            return m_uNext;
        }

        /// <summary>
        /// Returns the index of the previous element in the list.
        /// </summary>
        /// <returns>
        /// The index of the previous element in the list. Returns List::END_POSITION_BACKWARD constant if there is no previous element.
        /// </returns>
        puint_z GetPrevious() const
        {
            return m_uPrevious;
        }

        /// <summary>
        /// Sets the index of the next element in the list.
        /// </summary>
        /// <param name="uNext">[IN] The index of the next element in the list. If there is no next element, you must pass List::END_POSITION_FORWARD constant.</param>
        void SetNext(const puint_z uNext)
        {
            m_uNext = uNext;
        }

        /// <summary>
        /// Sets the index of the previous element in the list.
        /// </summary>
        /// <param name="uPrevious">[IN] The index of the previous element in the list. If there is no previous element, you must pass List::END_POSITION_BACKWARD constant.</param>
        void SetPrevious(const puint_z uPrevious)
        {
            m_uPrevious = uPrevious;
        }

    public:

        // ATTRIBUTES
        // ---------------

    protected:

        /// <summary>
        /// The index of the next element in the list. List::END_POSITION_FORWARD must be used when there is no next element.
        /// </summary>
        puint_z m_uNext;

        /// <summary>
        /// The index of the previous element in the list. List::END_POSITION_BACKWARD must be used when there is no previous element.
        /// </summary>
        puint_z m_uPrevious;

    };

public:

    /// <summary>
    /// Iterator that steps once per element of a list and does not allow to modify them.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a list, it cannot point to another list ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the list.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ConstListIterator
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the list to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the List class instead.
        /// </summary>
        /// <remarks>
        /// If the list is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pList">[IN] The list to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of list elements, but the physical.
        /// It must be lower than the capacity of the list.</param>
        ConstListIterator(const List* pList, const puint_z uPosition) : m_pList(pList), m_uPosition(uPosition)
        {
            Z_ASSERT_ERROR(pList != null_z, "Invalid argument: The pointer to the list cannot be null");
            Z_ASSERT_WARNING(pList->GetCapacity() > uPosition || 
                              uPosition == List::END_POSITION_BACKWARD || 
                              uPosition == List::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the capacity of the list");

            if(pList == null_z || 
               (pList->GetCapacity() <= uPosition && uPosition != List::END_POSITION_BACKWARD && uPosition != List::END_POSITION_FORWARD) || 
               pList->IsEmpty())
                   m_uPosition = List::END_POSITION_FORWARD;
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same list as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstListIterator& operator=(const ConstListIterator &iterator)
        {
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "The input iterator points to a different list");

            if(m_pList == iterator.m_pList)
                m_uPosition = iterator.m_uPosition;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T& operator*() const
        {
            // Note: This code is a copy of the same method of ListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the list element");

            Z_ASSERT_ERROR(m_uPosition != List::END_POSITION_FORWARD && m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return *(m_pList->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T* operator->() const
        {
            // Note: This code is a copy of the same method of ListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the list element");

            Z_ASSERT_ERROR(m_uPosition != List::END_POSITION_FORWARD && m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return m_pList->m_pElementBasePointer + m_uPosition;
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
        ConstListIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ListIterator (replacing ListIterator with ConstListIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            ConstListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = List::END_POSITION_FORWARD;
            else if(m_uPosition == List::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != List::END_POSITION_FORWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetNext();

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
        ConstListIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ListIterator (replacing ListIterator with ConstListIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            ConstListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = List::END_POSITION_BACKWARD;
            else if(m_uPosition == List::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != List::END_POSITION_BACKWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetPrevious();

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
        ConstListIterator& operator++()
        {
            // Note: This code is a copy of the same method of ListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = List::END_POSITION_FORWARD;
            else if(m_uPosition == List::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != List::END_POSITION_FORWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetNext();

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
        ConstListIterator& operator--()
        {
            // Note: This code is a copy of the same method of ListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = List::END_POSITION_BACKWARD;
            else if(m_uPosition == List::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != List::END_POSITION_BACKWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetPrevious();

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same list to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same list; False otherwise.
        /// </returns>
        bool operator==(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition == iterator.m_uPosition && m_pList == iterator.m_pList;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different list is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different list; False otherwise.
        /// </returns>
        bool operator!=(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            return m_uPosition != iterator.m_uPosition || m_pList != iterator.m_pList;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != List::END_POSITION_FORWARD &&
               m_uPosition != List::END_POSITION_BACKWARD)
            {
                List::ConstListIterator iteratorFromThis = *this;

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
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList &&
               iterator.m_uPosition != m_uPosition &&
               iterator.m_uPosition != List::END_POSITION_BACKWARD &&
               m_uPosition != List::END_POSITION_FORWARD)
            {
                List::ConstListIterator iteratorFromThis = *this;

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
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    List::ConstListIterator iteratorFromThis = *this;

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
        /// If iterators point to different lists or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstListIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pList == iterator.m_pList, "Iterators point to different lists");

            bool bResult = false;

            if(m_pList == iterator.m_pList)
            {
                if(m_uPosition == iterator.m_uPosition)
                    bResult = true;
                else
                {
                    List::ConstListIterator iteratorFromThis = *this;

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
        /// Indicates whether the iterator is pointing to one of the ends of the list.
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
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return m_uPosition == List::END_POSITION_BACKWARD || m_uPosition == List::END_POSITION_FORWARD;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the list, distinguishing which of them.
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
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");

            return (eIterationDirection == EIterationDirection::E_Backward && m_uPosition == List::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EIterationDirection::E_Forward  && m_uPosition == List::END_POSITION_FORWARD);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ListIterator

            m_uPosition = m_pList->m_uFirst == List::END_POSITION_BACKWARD ? List::END_POSITION_FORWARD : m_pList->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ListIterator

            m_uPosition = m_pList->m_uLast;
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a list may have been shortened while the iterator
        /// was pointing to its last position). If the list to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pList != null_z && 
                   (m_uPosition < m_pList->m_linkAllocator.GetPoolSize() / sizeof(List::Link) ||
                    m_uPosition == List::END_POSITION_BACKWARD ||
                    m_uPosition == List::END_POSITION_FORWARD);
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const List* GetContainer() const
        {
            return m_pList;
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
        /// The list the iterator points to.
        /// </summary>
        const List* m_pList;

        /// <summary>
        /// The current iteration position regarding the base position of the buffer (zero). It is zero-based.
        /// </summary>
        puint_z m_uPosition;

    }; // ConstListIterator

    
    /// <summary>
    /// Iterator that steps once per element of a list.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a list, it cannot point to another list ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the list.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ListIterator : public List::ConstListIterator
    {
        using List::ConstListIterator::m_pList;
        using List::ConstListIterator::m_uPosition;


        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the list to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the List class instead.
        /// </summary>
        /// <remarks>
        /// If the list is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pList">[IN] The list to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of list elements, but the physical.
        /// It must be lower than the capacity of the list.</param>
        ListIterator(const List* pList, const puint_z uPosition) : ConstListIterator(pList, uPosition)
        {
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same list as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ListIterator& operator=(const ListIterator &iterator)
        {
            List::ConstListIterator::operator=(iterator);
            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            // Note: This code is a copy of the same method of ConstListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the list element");

            Z_ASSERT_ERROR(m_uPosition != List::END_POSITION_FORWARD && m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return *(m_pList->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the list element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the list element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            // Note: This code is a copy of the same method of ConstListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the list element");

            Z_ASSERT_ERROR(m_uPosition != List::END_POSITION_FORWARD && m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to get the reference to the list element");

            return m_pList->m_pElementBasePointer + m_uPosition;
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
        ListIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ConstListIterator (replacing ConstListIterator with ListIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            ListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = List::END_POSITION_FORWARD;
            else if(m_uPosition == List::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != List::END_POSITION_FORWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetNext();

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
        ListIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ConstListIterator (replacing ConstListIterator with ListIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            ListIterator iteratorCopy = *this;

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = List::END_POSITION_BACKWARD;
            else if(m_uPosition == List::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != List::END_POSITION_BACKWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetPrevious();

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
        ListIterator& operator++()
        {
            // Note: This code is a copy of the same method of ConstListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_FORWARD, "The iterator points to an end position, it is not possible to increment it");

            if(m_uPosition == m_pList->m_uLast)
                m_uPosition = List::END_POSITION_FORWARD;
            else if(m_uPosition == List::END_POSITION_BACKWARD)
                m_uPosition = m_pList->m_uFirst;
            else if(m_uPosition != List::END_POSITION_FORWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetNext();

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
        ListIterator& operator--()
        {
            // Note: This code is a copy of the same method of ConstListIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");

            Z_ASSERT_WARNING(m_uPosition != List::END_POSITION_BACKWARD, "The iterator points to an end position, it is not possible to decrement it");

            if(m_uPosition == m_pList->m_uFirst)
                m_uPosition = List::END_POSITION_BACKWARD;
            else if(m_uPosition == List::END_POSITION_FORWARD)
                m_uPosition = m_pList->m_uLast;
            else if(m_uPosition != List::END_POSITION_BACKWARD)
                m_uPosition = (m_pList->m_pLinkBasePointer + m_uPosition)->GetPrevious();

            return *this;
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ConstListIterator

            m_uPosition = m_pList->m_uFirst == List::END_POSITION_BACKWARD ? List::END_POSITION_FORWARD : m_pList->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the list is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ConstListIterator

            m_uPosition = m_pList->m_uLast;
        }

    }; // ListIterator
    

    // TYPEDEFS
    // --------------
public:

    typedef typename List::ListIterator Iterator;
    typedef typename List::ConstListIterator ConstIterator;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Number of elements for which to reserve memory in the default constructor.
    /// </summary>
    static const puint_z DEFAULT_NUMBER_OF_ELEMENTS = 1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const puint_z END_POSITION_FORWARD;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const puint_z END_POSITION_BACKWARD = -1;
    
public:

    /// <summary>
    /// Constant to symbolize an invalid index returned when an element is not found.
    /// </summary>
    static const puint_z ELEMENT_NOT_FOUND = -1;


    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Default constructor. It reserves memory for the number of elements indicated at DEFAULT_NUMBER_OF_ELEMENTS constants.
    /// </summary>
    List() :
            m_uFirst(List::END_POSITION_BACKWARD),
            m_uLast(List::END_POSITION_FORWARD),
            m_elementAllocator(List::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
            m_linkAllocator(List::DEFAULT_NUMBER_OF_ELEMENTS * sizeof(List::Link), sizeof(List::Link), Alignment(alignof_z(List::Link))),
            m_pElementBasePointer(null_z),
            m_pLinkBasePointer(null_z)
    {
        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pLinkBasePointer = scast_z(m_linkAllocator.GetPointer(), List::Link*);
    }

    /// <summary>
    /// Constructor that reserves space to store the number of elements passed by parameter.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] Number of elements for wich to reserve space. It must be greater than zero.</param>
    explicit List(const puint_z uInitialCapacity) :
                m_uFirst(List::END_POSITION_BACKWARD),
                m_uLast(List::END_POSITION_FORWARD),
                m_elementAllocator(uInitialCapacity * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
                m_linkAllocator(uInitialCapacity * sizeof(List::Link), sizeof(List::Link), Alignment(alignof_z(List::Link))),
                m_pElementBasePointer(null_z),
                m_pLinkBasePointer(null_z)
    {
        Z_ASSERT_ERROR( uInitialCapacity > 0, "Initial capacity must be greater than zero" );

        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pLinkBasePointer = scast_z(m_linkAllocator.GetPointer(), List::Link*);
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every element is called.
    /// </remarks>
    /// <param name="list">[IN] Source list to copy.</param>
    List(const List& list) : m_elementAllocator(list.m_elementAllocator.GetPoolSize(), sizeof(T), Alignment(alignof_z(T))),
                               m_linkAllocator(list.m_linkAllocator.GetPoolSize(), sizeof(List::Link), Alignment(alignof_z(List::Link))),
                               m_pElementBasePointer(null_z),
                               m_pLinkBasePointer(null_z)
    {
        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pLinkBasePointer = scast_z(m_linkAllocator.GetPointer(), List::Link*);

        if(list.m_uFirst == List::END_POSITION_BACKWARD)
        {
            m_uFirst = List::END_POSITION_BACKWARD;
            m_uLast = List::END_POSITION_FORWARD;
        }
        else
        {
            list.m_linkAllocator.CopyTo(m_linkAllocator);
            list.m_elementAllocator.CopyTo(m_elementAllocator);

            m_uFirst = list.m_uFirst;
            m_uLast = list.m_uLast;

            List::ListIterator iteratorOrigin = list.GetFirst();
            List::ListIterator iteratorDestination = this->GetFirst();

            for(; !iteratorOrigin.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
            {
                new(&(*iteratorDestination)) T(*iteratorOrigin);
            }
        }
    }
    
    /// <summary>
    /// Constructor that receives an existing array and its size.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the list.
    /// </remarks>
    /// <param name="pArray">[IN] The existing array that will be copied. It must not be null.</param>
    /// <param name="uNumberOfElements">[IN] The number of elements in the input array. It must be greater than zero.</param>
    List(const T* pArray, const puint_z uNumberOfElements) :
                                                        m_uFirst(List::END_POSITION_BACKWARD),
                                                        m_uLast(List::END_POSITION_FORWARD),
                                                        m_elementAllocator(uNumberOfElements * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
                                                        m_linkAllocator(uNumberOfElements * sizeof(List::Link), sizeof(List::Link), Alignment(alignof_z(List::Link))),
                                                        m_pElementBasePointer(null_z),
                                                        m_pLinkBasePointer(null_z)
    {
        Z_ASSERT_ERROR( pArray != null_z, "The argument pArray is null." );
        Z_ASSERT_ERROR( uNumberOfElements > 0, "The number of elements in the array must be greater than zero." );
        
        m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
        m_pLinkBasePointer = scast_z(m_linkAllocator.GetPointer(), List::Link*);

        const T* pElement = pArray;

        for(puint_z uIndex = 0; uIndex < uNumberOfElements; ++uIndex, ++pElement)
            this->Add(*pElement);
    }


    // DESTRUCTOR
    // ---------------

public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every element is called in the same order they appear in the list.
    /// </remarks>
    ~List()
    {
        if(!this->IsEmpty())
        {
            // Iterates the list in an orderly manner, calling the destructor for each element.
            for(List::ListIterator it = this->GetFirst(); !it.IsEnd(); ++it)
                (*it).~T();
        }
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies one list to another.
    /// </summary>
    /// <remarks>
    /// Assignment operator will be called for every element of the list.
    /// </remarks>
    /// <param name="list">[IN] List to copy in the current list.</param>
    /// <returns>
    /// A reference to the current list.
    /// </returns>
    List& operator= (const List& list)
    {
        if(this != &list)
        {
            if(list.GetCount() == this->GetCount())
            {
                ListIterator iteratorOrigin = list.GetFirst();
                ListIterator iteratorDestination = this->GetFirst();

                for(; !iteratorOrigin.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
                    *iteratorDestination = *iteratorOrigin;
            }
            else if(list.GetCount() < this->GetCount())
            {
                puint_z uFirstIndexToDestroy;
                puint_z uOldLast = m_uLast;

                if(list.GetCount() == 0)
                {
                    uFirstIndexToDestroy = m_uFirst;
                    m_uFirst = List::END_POSITION_BACKWARD;
                    m_uLast = List::END_POSITION_FORWARD;
                }
                else
                {
                    // Makes the copy calling assignment operator with existing elements.

                    T* pElementOrigin = null_z;
                    T* pElementDestination = null_z;
                    List::Link* pLinkOrigin = null_z;
                    List::Link* pLinkDestination = null_z;

                    puint_z uIndexOrigin = list.m_uFirst;
                    puint_z uIndexDestination = m_uFirst;

                    bool bCopied = false;

                    while(!bCopied)
                    {
                        pElementOrigin = list.m_pElementBasePointer + uIndexOrigin;
                        pElementDestination = m_pElementBasePointer + uIndexDestination;

                        *pElementDestination = *pElementOrigin;

                        bCopied = (uIndexOrigin == list.m_uLast);
                        m_uLast = uIndexDestination;

                        pLinkOrigin = list.m_pLinkBasePointer + uIndexOrigin;
                        uIndexOrigin = pLinkOrigin->GetNext();

                        pLinkDestination = m_pLinkBasePointer + uIndexDestination;
                        uIndexDestination = pLinkDestination->GetNext();
                    }
                    uFirstIndexToDestroy = uIndexDestination;
                }

                // Destroys the rest of the destination list

                puint_z uIndex = uFirstIndexToDestroy;
                puint_z uNextIndex;

                bool bDestroyed = false;

                while(!bDestroyed && uIndex != List::END_POSITION_FORWARD)
                {
                    List::Link* pLink = m_pLinkBasePointer + uIndex;
                    uNextIndex = pLink->GetNext();
                    m_linkAllocator.Deallocate(pLink);

                    T* pElement = m_pElementBasePointer+ uIndex;
                    pElement->~T();
                    m_elementAllocator.Deallocate(pElement);

                    bDestroyed = (uIndex == uOldLast);
                    uIndex = uNextIndex;
                }
            }
            else
            {
                // Increases the capacity of the destination, if necessary
                if(list.GetCapacity() > this->GetCapacity())
                    this->Reserve(list.GetCapacity());

                ListIterator iteratorOrigin = list.GetFirst();
                ListIterator iteratorDestination = this->GetFirst();

                // Copies as many elements as it has the destination list.

                for(; !iteratorDestination.IsEnd(); ++iteratorOrigin, ++iteratorDestination)
                    *iteratorDestination = *iteratorOrigin;

                // Adds the rest of elements if needed.

                while(!iteratorOrigin.IsEnd())
                {
                    this->Add(*iteratorOrigin);
                    ++iteratorOrigin;
                }
            }
        }
        
        return *this;
    }
    
    /// <summary>
    /// Equality operator that checks whether two lists are equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other list. Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="list">[IN] The list to compare to.</param>
    /// <returns>
    /// True if all the elements of both lists are equal; False otherwise.
    /// </returns>
    bool operator==(const List &list) const
    {
        bool bAreEqual = true;

        // If they are not the same instance and they are not both empty
        if(this != &list && !(m_uLast == List::END_POSITION_FORWARD && list.m_uLast == List::END_POSITION_FORWARD))
        {
            // If they have the same number of elements
            if(this->GetCount() == list.GetCount())
            {
                List::ConstListIterator itThis = this->GetFirst();
                List::ConstListIterator itInput = list.GetFirst();

                while(bAreEqual && !itThis.IsEnd())
                {
                    bAreEqual = ComparatorT::Compare(*itThis, *itInput) == 0;
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
    /// Inequality operator that checks whether two lists are not equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other list. Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="list">[IN] The list to compare to.</param>
    /// <returns>
    /// True if not all the elements of both lists are equal; False otherwise.
    /// </returns>
    bool operator!=(const List &list) const
    {
        return !this->operator==(list);
    }
    
    /// <summary>
    /// Performs a fast shallow copy of the list elements.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// If the destination list's capacity is lower than the resident list's capacity, it will be increased.<br/>
    /// Neither elements' constructor nor element's assignment operator are called.
    /// </remarks>
    /// <param name="destinationList"> [OUT] Destination list where to copy the list elements.</param>
    void Clone(List &destinationList) const
    {
        // Uncomment when reserve method is implemented
        if(destinationList.GetCapacity() < this->GetCapacity())
            destinationList.Reserve(this->GetCapacity());

        m_elementAllocator.CopyTo(destinationList.m_elementAllocator);
        m_linkAllocator.CopyTo(destinationList.m_linkAllocator);
        destinationList.m_uFirst = m_uFirst;
        destinationList.m_uLast = m_uLast;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the list's size. Note that indexes are zero-based.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& GetValue(const puint_z uIndex) const
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        
        return *this->GetIterator(uIndex);
    }

    /// <summary>
    /// Sets the value of an element located at a given position.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to set. It must be less than the list's size. Note that indexes are zero-based.</param>
    /// <param name="value">[IN] The new value for the element.</param>
    void SetValue(const puint_z uIndex, const T& value)
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );
        
        *this->GetIterator(uIndex) = value;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position. Indexes are zero-based.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the list's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& operator[] (const puint_z uIndex) const
    {
        return this->GetValue(uIndex);
    }
    
    /// <summary>
    /// Gets an iterator that points to a given position in the list.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the list, starting at zero, to which the iterator will point. If it is out of bounds, the returned iterator will point 
    /// to the end position.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    ListIterator GetIterator(const puint_z uIndex) const 
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the list's size" );

        List::ListIterator iterator(this, m_uFirst);

        if(!this->IsEmpty())
            for(puint_z i = 0; i < uIndex; ++i)
                ++iterator;

        return iterator;
    }

    /// <summary>
    /// Gets an iterator that points to the first position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the first element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    ListIterator GetFirst() const
    {
        return List::ListIterator(this, m_uFirst);
    }

    /// <summary>
    /// Gets an iterator that points to the last position in the list.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the last element. If the list is empty, the iterator will point to the end position.
    /// </returns>
    ListIterator GetLast() const
    {
        return List::ListIterator(this, m_uLast);
    }
    
    /// <summary>
    /// Increases the capacity of the list, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this list will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const puint_z uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_elementAllocator.Reallocate(uNumberOfElements * sizeof(T));
            m_linkAllocator.Reallocate(uNumberOfElements * sizeof(List::Link));
            m_pElementBasePointer = scast_z(m_elementAllocator.GetPointer(), T*);
            m_pLinkBasePointer = scast_z(m_linkAllocator.GetPointer(), List::Link*);
        }
    }

    /// <summary>
    /// Copies an element to the end of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    void Add(const T &newElement)
    {
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);
        
        puint_z uNewLinkPrevious = m_uLast;

        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link
            uNewLinkPrevious = List::END_POSITION_BACKWARD;
        }

        // Creates the new link
        List::Link* pNewLastLink = new(m_linkAllocator.Allocate()) List::Link(uNewLinkPrevious, List::END_POSITION_FORWARD);

        if(uNewLinkPrevious != List::END_POSITION_BACKWARD)
        {
            // Makes the last link point to the new link
            List::Link* pLastLink = m_pLinkBasePointer + m_uLast;
            pLastLink->SetNext(pNewLastLink - m_pLinkBasePointer);
            m_uLast = pNewLastLink - m_pLinkBasePointer;
        }
        else
        {
            m_uFirst = m_uLast = pNewLastLink - m_pLinkBasePointer;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the list and returns an iterator that points to it.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="position">[IN] The position where the new element will be placed. It should not be an end position; if it is, 
    /// the element will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    /// <returns>
    /// An iterator that points to the just inserted element.
    /// </returns>
    ListIterator Insert(const T &newElement, const typename List::ConstListIterator &position)
    {
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        Z_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        // Gets the position of the iterator
        puint_z uIndex = &(*position) - m_pElementBasePointer;

        puint_z uNewLinkNext = 0;
        puint_z uNewLinkPrevious = 0;

        List::Link* pNextLink = null_z;
        List::Link* pPreviousLink = null_z;

        // Calculates what's the next link and what's the previous one
        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link nor next link
            uNewLinkPrevious = List::END_POSITION_BACKWARD;
            uNewLinkNext = List::END_POSITION_FORWARD;
        }
        else if(position.IsEnd(EIterationDirection::E_Forward))
        {
            // Adding at the end
            pPreviousLink = m_pLinkBasePointer + m_uLast;
            uNewLinkPrevious = m_uLast;
            uNewLinkNext = List::END_POSITION_FORWARD;
        }
        else if(uIndex == m_uFirst)
        {
            // Adding at the beginning
            pNextLink = m_pLinkBasePointer + m_uFirst;
            uNewLinkPrevious = List::END_POSITION_BACKWARD;
            uNewLinkNext = m_uFirst;
        }
        else
        {
            // Adding somewhere in the middle
            pNextLink = m_pLinkBasePointer + uIndex;
            uNewLinkPrevious = pNextLink->GetPrevious();
            uNewLinkNext = uIndex;
            pPreviousLink = m_pLinkBasePointer + uNewLinkPrevious;
        }

        // Creates the new link
        List::Link* pNewLastLink = new(m_linkAllocator.Allocate()) List::Link(uNewLinkPrevious, uNewLinkNext);
        puint_z uNewLinkPosition = pNewLastLink - m_pLinkBasePointer;

        if(pNextLink)
        {
            // Makes the next link point to the new link
            pNextLink->SetPrevious(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the end
            m_uLast = uNewLinkPosition;
        }
        
        if(pPreviousLink)
        {
            // Makes the next link point to the new link
            pPreviousLink->SetNext(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the beginning
            m_uFirst = uNewLinkPosition;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);

        return List::ListIterator(this, uNewLinkPosition);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the new element will be placed. It should be lower than the number of elements of the list; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void Insert(const T &newElement, const puint_z uIndex)
    {
        Z_ASSERT_WARNING(!this->IsEmpty() && uIndex < this->GetCount(), "The input iterator is out of bounds");
        
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        puint_z uNewLinkNext = 0;
        puint_z uNewLinkPrevious = 0;

        List::Link* pNextLink = null_z;
        List::Link* pPreviousLink = null_z;

        // Gets the physical position of the link at the given ordinal position
        puint_z uPosition = &this->GetValue(uIndex) - m_pElementBasePointer;

        // Calculates what's the next link and what's the previous one
        if(this->IsEmpty())
        {
            // If the list is empty, there is no previous link
            uNewLinkPrevious = List::END_POSITION_BACKWARD;
            uNewLinkNext = List::END_POSITION_FORWARD;
        }
        else if(uPosition >= this->GetCount())
        {
            // Adding at the end
            pPreviousLink = m_pLinkBasePointer + m_uLast;
            uNewLinkPrevious = m_uLast;
            uNewLinkNext = List::END_POSITION_FORWARD;
        }
        else if(uPosition == m_uFirst)
        {
            // Adding at the beginning
            pNextLink = m_pLinkBasePointer + m_uFirst;
            uNewLinkPrevious = List::END_POSITION_BACKWARD;
            uNewLinkNext = m_uFirst;
        }
        else
        {
            // Adding somewhere in the middle
            pNextLink = m_pLinkBasePointer + uPosition;
            uNewLinkPrevious = pNextLink->GetPrevious();
            uNewLinkNext = uPosition;
            pPreviousLink = m_pLinkBasePointer + uNewLinkPrevious;
        }

        // Creates the new link
        List::Link* pNewLastLink = new(m_linkAllocator.Allocate()) List::Link(uNewLinkPrevious, uNewLinkNext);
        puint_z uNewLinkPosition = pNewLastLink - m_pLinkBasePointer;

        if(pNextLink)
        {
            // Makes the next link point to the new link
            pNextLink->SetPrevious(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the end
            m_uLast = uNewLinkPosition;
        }
        
        if(pPreviousLink)
        {
            // Makes the next link point to the new link
            pPreviousLink->SetNext(uNewLinkPosition);
        }
        else
        {
            // The element was inserted at the beginning
            m_uFirst = uNewLinkPosition;
        }

        // Copies the new element
        new(m_elementAllocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the list and returns an iterator that points to the next position.
    /// </summary>
    /// <remarks>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="position">[IN] The position of the element to be deleted. It should not be an end position; if it is, 
    /// nothing will be done. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    /// <returns>
    /// An iterator that points to the ordinal position that was occupied by the just removed element. If there was not another element next, 
    /// the iterator will point to the end position.
    /// </returns>
    ListIterator Remove(const typename List::ListIterator position)
    {
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        Z_ASSERT_WARNING(!this->IsEmpty(), "The list is empty, there is nothing to remove");
        Z_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        puint_z uNext = List::END_POSITION_FORWARD;
        puint_z uPrevious = List::END_POSITION_BACKWARD;

        if(!this->IsEmpty() && !position.IsEnd())
        {
            // Gets the position of the iterator
            puint_z uIndex = &(*position) - m_pElementBasePointer;
            List::Link* pLinkToRemove = m_pLinkBasePointer + uIndex;
            T* pElementToRemove = &(*position);

            uNext = pLinkToRemove->GetNext();
            uPrevious = pLinkToRemove->GetPrevious();

            if(uNext != List::END_POSITION_FORWARD)
            {
                // If there is next link
                List::Link* pNextLink = m_pLinkBasePointer + uNext;
                pNextLink->SetPrevious(uPrevious);
            }
            else if(uPrevious != List::END_POSITION_BACKWARD)
            {
                // If this link was the last one, and there is a previous link, the last link in the list will be the previous link
                m_uLast = uPrevious;
            }
            else
            {
                // If this link was the only one in the list the first and the last position are end positions
                m_uFirst = List::END_POSITION_BACKWARD;
                m_uLast = List::END_POSITION_FORWARD;
            }

            if(uPrevious != List::END_POSITION_BACKWARD)
            {
                List::Link* pPreviousLink = m_pLinkBasePointer + uPrevious;
                pPreviousLink->SetNext(uNext);
            }
            else if(uNext != List::END_POSITION_FORWARD)
            {
                // If this link was the first one, and there is a next link, the first link in the list will be the next link
                m_uFirst = uNext;
            }

            pElementToRemove->~T();
            m_linkAllocator.Deallocate(pLinkToRemove);
            m_elementAllocator.Deallocate(pElementToRemove);
        }

        return List::ListIterator(this, uNext);
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="uIndex">[IN] The index (zero-based) of the element to be deleted. It should be lower than the number of elements of the list; if it is not, 
    /// nothing will happen.</param>
    void Remove(const puint_z uIndex)
    {
        Z_ASSERT_WARNING(!this->IsEmpty(), "The list is empty, there is nothing to remove");
        Z_ASSERT_WARNING(!this->IsEmpty() && uIndex < this->GetCount(), "The input iterator is out of bounds");

        if(!this->IsEmpty() && uIndex < this->GetCount())
        {
            // Gets the position of the iterator
            T* pElementToRemove = &this->GetValue(uIndex);
            puint_z uIndex = pElementToRemove - m_pElementBasePointer;

            List::Link* pLinkToRemove = m_pLinkBasePointer + uIndex;

            puint_z uNext = pLinkToRemove->GetNext();
            puint_z uPrevious = pLinkToRemove->GetPrevious();
            
            if(uNext != List::END_POSITION_FORWARD)
            {
                // If there is next link
                List::Link* pNextLink = m_pLinkBasePointer + uNext;
                pNextLink->SetPrevious(uPrevious);
            }
            else if(uPrevious != List::END_POSITION_BACKWARD)
            {
                // If this link was the last one, and there is a previous link, the last link in the list will be the previous link
                m_uLast = uPrevious;
            }
            else
            {
                // If this link was the only one in the list the first and the last position are end positions
                m_uFirst = List::END_POSITION_BACKWARD;
                m_uLast = List::END_POSITION_FORWARD;
            }

            if(uPrevious != List::END_POSITION_BACKWARD)
            {
                List::Link* pPreviousLink = m_pLinkBasePointer + uPrevious;
                pPreviousLink->SetNext(uNext);
            }
            else if(uNext != List::END_POSITION_FORWARD)
            {
                // If this link was the first one, and there is a next link, the first link in the list will be the next link
                m_uFirst = uNext;
            }

            pElementToRemove->~T();
            m_linkAllocator.Deallocate(pLinkToRemove);
            m_elementAllocator.Deallocate(pElementToRemove);
        }
    }
    
    /// <summary>
    /// Removes all the elements of the list.
    /// </summary>
    /// <remarks>
    /// This operation will make any existing iterator or pointer invalid.<br/>
    /// The destructor of every element will be called.
    /// </remarks>
    void Clear()
    {
        if(!this->IsEmpty())
        {
            // Calls every destructor, from first to last
            for(List::ListIterator it = this->GetFirst(); !it.IsEnd(); ++it)
                (*it).~T();

            m_uFirst = List::END_POSITION_BACKWARD;
            m_uLast = List::END_POSITION_FORWARD;

            m_elementAllocator.Clear();
            m_linkAllocator.Clear();
        }
    }
    
    /// <summary>
    /// Gets a range of elements from the list.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be copied. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be copied. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    /// <returns>
    /// A list that contains a copy of all the elements in the given range.
    /// </returns>
    List GetRange(const typename List::ConstListIterator &first, const typename List::ConstListIterator &last) const
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        List resultList;

        List::ConstListIterator itEnd = last;
        ++itEnd;

        for(List::ConstListIterator it = first; it != itEnd; ++it)
            resultList.Add(*it);

        return resultList;
    }
    
    /// <summary>
    /// Gets a range of elements from the list.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be copied. It must be lower than the number of elements of the list.
    /// It must be equal or lower than the last element's index in the range.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be copied. It must be lower than the number of elements of the list.
    /// It must be equal or greater than the first element's index in the range.</param>
    /// <returns>
    /// An list that contains a copy of all the elements in the given range.
    /// </returns>
    List GetRange(const puint_z uFirst, const puint_z uLast) const
    {
        Z_ASSERT_ERROR(uFirst <= uLast, "The first element must be prior to the last element in the range.");
        Z_ASSERT_ERROR(uFirst < this->GetCount(), "The first position is out of bounds.");
        Z_ASSERT_ERROR(uLast < this->GetCount(), "The last position is out of bounds.");
        
        const puint_z ELEMENTS_TO_GET_COUNT = uLast - uFirst + 1U;

        List resultList(ELEMENTS_TO_GET_COUNT);

        List::ConstListIterator it = this->GetIterator(uFirst);

        for(puint_z i = 0; i < ELEMENTS_TO_GET_COUNT; ++it, ++i)
            resultList.Add(*it);

        return resultList;
    }
    
    /// <summary>
    /// Swaps two elements of the list.
    /// </summary>
    /// <remarks>
    /// The list must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="uElementA">[IN] The index (zero-based) of an element. It must be lower than the number of elements of the list.</param>
    /// <param name="uElementB">[IN] The index (zero-based) of the other element. It must be lower than the number of elements of the list.</param>
    void Swap(const puint_z uElementA, const puint_z uElementB)
    {
        Z_ASSERT_ERROR(uElementA < this->GetCount(), "The first index is out of bounds.");
        Z_ASSERT_ERROR(uElementB < this->GetCount(), "The last index is out of bounds.");
        Z_ASSERT_WARNING(uElementA != uElementB, "Both elements are the same.");
        
        T* pElementA = &this->GetValue(uElementA);
        T* pElementB = &this->GetValue(uElementB);

        u8_z arBytes[sizeof(T)];
        memcpy(arBytes,   pElementA, sizeof(T));
        memcpy(pElementA, pElementB, sizeof(T));
        memcpy(pElementB, arBytes,   sizeof(T));
    }
    
    /// <summary>
    /// Swaps two elements of the list.
    /// </summary>
    /// <remarks>
    /// The list must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="elementA">[IN] The position of an element. It must not be an end position.</param>
    /// <param name="elementB">[IN] The position of the other element. It must not be an end position.</param>
    void Swap(const typename List::ListIterator elementA, const typename List::ListIterator elementB)
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
    
    /// <summary>
    /// Checks if any of the elements in the list is equal to a given one.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the list.</param>
    /// <returns>
    /// True if the element is found; False otherwise.
    /// </returns>
    bool Contains(const T &element) const
    {
        bool bElementFound = false;
        List::ConstListIterator itElement = this->GetFirst();

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*itElement, element) == 0;
            ++itElement;
        }

        return bElementFound;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    puint_z IndexOf(const T &element) const
    {
        bool bElementFound = false;
        List::ConstListIterator itElement = this->GetFirst();
        puint_z uIndex = 0;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : List::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one, starting from a concrete position, and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <param name="uStartIndex">[IN] The start position to search from. It must be lower than the number of elements in the list.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    puint_z IndexOf(const T &element, const puint_z uStartIndex) const
    {
        Z_ASSERT_WARNING(uStartIndex < this->GetCount(), "The input start index must be lower than the number of elements in the list.");

        bool bElementFound = false;
        List::ConstListIterator itElement = this->GetIterator(uStartIndex);
        puint_z uIndex = uStartIndex;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : List::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    ListIterator PositionOf(const T &element) const
    {
        bool bElementFound = false;
        List::ListIterator itElement = this->GetFirst();

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*itElement, element) == 0;
            ++itElement;
        }

        return bElementFound ? --itElement : itElement;
    }
    
    /// <summary>
    /// Searches for the first element in the list equal to a given one, starting from a concrete position, and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the list's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to search for through the list.</param>
    /// <param name="startPosition">[IN] The start position to search from. It must not point to an end position.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    ListIterator PositionOf(const T &element, const typename List::ConstListIterator &startPosition) const
    {
        Z_ASSERT_WARNING(!startPosition.IsEnd(), "The input start position must not point to an end position.");
        Z_ASSERT_ERROR(startPosition.IsValid(), "The input start position is not valid.");

        bool bElementFound = false;
        List::ListIterator itElement = List::ListIterator(this, startPosition.GetInternalPosition());
        puint_z uIndex = 0;

        while(!itElement.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*itElement, element) == 0;
            ++itElement;
            ++uIndex;
        }

        return bElementFound ? --itElement : itElement;
    }
    
    /// <summary>
    /// Copies a range of elements from another list to the end of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    void AddRange(const typename List::ConstListIterator &first, const typename List::ConstListIterator &last)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        // Copies each element in the input range
        List::ConstListIterator it = first;

        for(; it != last; ++it)
            this->Add(*it);

        this->Add(*it);
    }

    /// <summary>
    /// Copies a range of elements from another list to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the range of elements will be placed. It should be lower than the number of elements of the list; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void InsertRange(const typename List::ConstListIterator &first, const typename List::ConstListIterator &last, const puint_z uIndex)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        Z_ASSERT_WARNING(uIndex < this->GetCount(), "The index is out of bounds.");

        // Copies each element in the input range
        List::ConstListIterator it = last;

        for(; it != first; --it)
            this->Insert(*it, uIndex);

        this->Insert(*it, uIndex);
    }
    
    /// <summary>
    /// Copies a range of elements from another list to a concrete position of the list.
    /// </summary>
    /// <remarks>
    /// If the capacity of the list is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same list.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="position">[IN] The position where the range of elements will be placed. It should not be an end position; if it is, 
    /// the range will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// list; otherwise, the behavior is undefined.</param>
    void InsertRange(const typename List::ConstListIterator &first, const typename List::ConstListIterator &last, const typename List::ListIterator &position)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        Z_ASSERT_WARNING(!position.IsEnd(), "The insertion position should not point to an end position.");
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator that points to the insertion position is not valid.");
        
        // Copies each element in the input range
        List::ConstListIterator it = first;

        for(; it != last; ++it)
            this->Insert(*it, position);

        this->Insert(*it, position);
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be deleted. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be deleted. It must not be an end position. It must point to the same
    /// list; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    void RemoveRange(const typename List::ListIterator &first, const typename List::ListIterator &last)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        List::ListIterator it = first;
        List::ListIterator itNext = first;

        while(it != last)
        {
            itNext = it;
            ++itNext;
            this->Remove(it);
            it = itNext;
        }

        this->Remove(it);
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the list.
    /// </summary>
    /// <remarks>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be deleted. It must be equal or lower than the last element's index in the range. 
    /// It must be lower than the number of elements of the list.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be deleted. It must be equal or greater than the first element's index in the range.
    /// It must be lower than the number of elements of the list.</param>
    void RemoveRange(const puint_z uFirst, const puint_z uLast)
    {
        List::ListIterator it = this->GetIterator(uFirst);
        const List::ListIterator LAST = this->GetIterator(uLast);
        List::ListIterator itNext = it;

        while(it != LAST)
        {
            itNext = it;
            ++itNext;
            this->Remove(it);
            it = itNext;
        }

        this->Remove(it);
    }
    
    
private:

    /// <summary>
    /// Increases the capacity of the list, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const puint_z uNumberOfElements)
    {
        const puint_z FINAL_CAPACITY = scast_z(scast_z(uNumberOfElements, float) * List::REALLOCATION_FACTOR, puint_z);
        this->Reserve(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------

public:

    /// <summary>
    /// Returns a constant pointer to the element allocator.
    /// </summary>
    /// <returns>
    /// Constant pointer to the element allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_elementAllocator;
    }

    /// <summary>
    /// Returns the number of elements in the list.
    /// </summary>
    /// <returns>
    /// The number of elements in the list.
    /// </returns>
    puint_z GetCount() const
    {
        return m_elementAllocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Returns the number of elements that can be stored in the list without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of elements that can be stored in the list without a reallocation.
    /// </returns>
    puint_z GetCapacity() const
    {
        return m_elementAllocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Checks whether the list is empty or not.
    /// </summary>
    /// <returns>
    /// True if the list is empty.
    /// </returns>
    bool IsEmpty() const
    {
        return (GetCount() == 0);
    }

    // ATTRIBUTES
    // ---------------

protected:

    /// <summary>
    /// Index of the first element in the sequence. If there is no first element, its value is END_POSITION_BACKWARD constant.
    /// </summary>
    puint_z m_uFirst;

       /// <summary>
    /// Index of the last element in the sequence. If there is no last element, its value is END_POSITION_FORWARD constant.
    /// </summary>
    puint_z m_uLast;

    /// <summary>
    /// The allocator which stores the list elements.
    /// </summary>
    AllocatorT m_elementAllocator;

      /// <summary>
    /// The allocator which stores the double linked list for internals.
    /// </summary>
    AllocatorT m_linkAllocator;

    /// <summary>
    /// A pointer to the buffer stored in the memory allocator, casted to the element type, intended to improve overall performance.
    /// </summary>
    T* m_pElementBasePointer;

    /// <summary>
    /// A pointer to the buffer stored in the memory allocator, casted to the Link type, intended to improve overall performance.
    /// </summary>
    Link* m_pLinkBasePointer;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class T, class AllocatorT, class ComparatorT>
float List<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;

template<class T, class AllocatorT, class ComparatorT>
const puint_z List<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD = -2;

} // namespace z


#endif // __LIST__
