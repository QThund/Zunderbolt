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

#ifndef __ARRAYFIXED__
#define __ARRAYFIXED__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZMemory/PoolAllocator.h"
#include "ZCommon/Alignment.h"
#include "ZContainers/SComparatorDefault.h"
#include "ZCommon/AllocationOperators.h"
#include "ZContainers/EIterationDirection.h"


#ifdef Z_COMPILER_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"
#endif

namespace z
{

/// <summary>
/// Represents a contiguous sequence of elements that can be arbitrarly accessed using a zero-based
/// index. Its size is defined when it is constructed and cannot be changed afterwards.
/// </summary>
/// <remarks>
/// Elements are assured to be placed contiguously in memory.<br/>
/// Elements are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SComparatorDefault is used as comparator, elements will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of every element in the array.</typeparam>
/// <typeparam name="AllocatorT">Optional. The type of allocator to store the elements of the array. By default, PoolAllocator will
/// be used.</typeparam>
/// <typeparam name="ComparatorT">Optional. The type of comparator to compare elements to each other, used in search and ordering
/// algorithms. By default, SComparatorDefault will be used.</typeparam>
template <class T, class AllocatorT = PoolAllocator, class ComparatorT = SComparatorDefault<T> >
class ArrayFixed
{

    // INTERNAL CLASSES
    // -----------------
public:

    /// <summary>
    /// Iterator that steps once per element of an array and does not allow the modification of them.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to an array, it cannot point to another array ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the array.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ConstArrayIterator
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the array to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the ArrayFixed class instead.
        /// </summary>
        /// <remarks>
        /// If the array is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pArray">[IN] The array to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. It must be lower than the number of elements in the array.</param>
        ConstArrayIterator(const ArrayFixed* pArray, const puint_z uPosition) : m_pArray(pArray), m_uPosition(uPosition)
        {
            Z_ASSERT_ERROR(pArray != null_z, "Invalid argument: The pointer to the array cannot be null");
            Z_ASSERT_WARNING(pArray->GetCount() > uPosition || 
                              uPosition == ArrayFixed::END_POSITION_BACKWARD || 
                              uPosition == ArrayFixed::END_POSITION_FORWARD, "Invalid argument: The position must be lower than the number of elements in the array");

            if(pArray == null_z || 
               (pArray->GetCount() <= uPosition && uPosition != ArrayFixed::END_POSITION_BACKWARD && uPosition != ArrayFixed::END_POSITION_FORWARD))
                m_uPosition = ArrayFixed::END_POSITION_FORWARD;
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same array as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstArrayIterator& operator=(const ConstArrayIterator &iterator)
        {
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "The input iterator points to a different array");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");

            if(m_pArray == iterator.m_pArray)
                m_uPosition = iterator.m_uPosition;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T& operator*() const
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the array element");
            Z_ASSERT_ERROR(!this->IsEnd(), "The iterator points to an end position, it is not possible to get the reference to the array element");

            return *(m_pArray->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const T* operator->() const
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the array element");
            Z_ASSERT_ERROR(!this->IsEnd(), "The iterator points to an end position, it is not possible to get the reference to the array element");

            return m_pArray->m_pElementBasePointer + m_uPosition;
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
        ConstArrayIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator (just replacing ArrayIterator with ConstArrayIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ConstArrayIterator iteratorCopy = *this;

            ++m_uPosition;

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
        ConstArrayIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator (just replacing ArrayIterator with ConstArrayIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");

            ConstArrayIterator iteratorCopy = *this;

            // +1 so the backward end position is moved forward, being 1 unit lower than zero instead of being the greatest number always
            m_uPosition = m_uPosition + 1U > m_pArray->m_uLast + 1U ? m_pArray->m_uLast : --m_uPosition;

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
        ConstArrayIterator& operator++()
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ++m_uPosition;

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
        ConstArrayIterator& operator--()
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");
            
            // +1 so the backward end position is moved forward, being 1 unit lower than zero instead of being the greatest number always
            m_uPosition = m_uPosition + 1U > m_pArray->m_uLast + 1U ? m_pArray->m_uLast : --m_uPosition;

            return *this;
        }
        
        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same array to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same array; False otherwise.
        /// </returns>
        bool operator==(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return m_uPosition == iterator.m_uPosition && m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different array is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different array; False otherwise.
        /// </returns>
        bool operator!=(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return m_uPosition != iterator.m_uPosition || m_pArray != iterator.m_pArray;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition == ArrayFixed::END_POSITION_FORWARD  && iterator.m_uPosition != ArrayFixed::END_POSITION_FORWARD)  ||
                    (m_uPosition != ArrayFixed::END_POSITION_BACKWARD && iterator.m_uPosition == ArrayFixed::END_POSITION_BACKWARD) ||
                    m_uPosition > iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition != ArrayFixed::END_POSITION_FORWARD  && iterator.m_uPosition == ArrayFixed::END_POSITION_FORWARD)  ||
                    (m_uPosition == ArrayFixed::END_POSITION_BACKWARD && iterator.m_uPosition != ArrayFixed::END_POSITION_BACKWARD) ||
                    m_uPosition < iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition == ArrayFixed::END_POSITION_FORWARD  && iterator.m_uPosition != ArrayFixed::END_POSITION_FORWARD)  ||
                    (m_uPosition != ArrayFixed::END_POSITION_BACKWARD && iterator.m_uPosition == ArrayFixed::END_POSITION_BACKWARD) ||
                    m_uPosition >= iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different arrays or they are not valid, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstArrayIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pArray == iterator.m_pArray, "Iterators point to different arrays");

            return ((m_uPosition != ArrayFixed::END_POSITION_FORWARD  && iterator.m_uPosition == ArrayFixed::END_POSITION_FORWARD)  ||
                    (m_uPosition == ArrayFixed::END_POSITION_BACKWARD && iterator.m_uPosition != ArrayFixed::END_POSITION_BACKWARD) ||
                    m_uPosition <= iterator.m_uPosition) &&
                    m_pArray == iterator.m_pArray;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the array.
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
            Z_ASSERT_ERROR(this->IsValid(), "The input iterator is not valid");

            return m_uPosition >= m_pArray->GetCount();
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the array, distinguishing which of them.
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
            Z_ASSERT_ERROR(this->IsValid(), "The input iterator is not valid");

            return (eIterationDirection == EIterationDirection::E_Backward && m_uPosition == ArrayFixed::END_POSITION_BACKWARD) ||
                   (eIterationDirection == EIterationDirection::E_Forward  && (m_uPosition == ArrayFixed::END_POSITION_FORWARD || (m_uPosition > m_pArray->m_uLast && m_uPosition != ArrayFixed::END_POSITION_BACKWARD)));
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_WARNING(!m_pArray->IsEmpty(), "The array is empty, there is no first position");

            m_uPosition = m_pArray->m_uFirst == ArrayFixed::END_POSITION_BACKWARD ? ArrayFixed::END_POSITION_FORWARD : m_pArray->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ArrayIterator

            Z_ASSERT_WARNING(!m_pArray->IsEmpty(), "The array is empty, there is no last position");

            m_uPosition = m_pArray->m_uLast;
        }
        
        /// <summary>
        /// Increments the position the iterator points to.
        /// </summary>
        /// <remarks>
        /// It is recommended to use pre-increment or post-increment operators instead if the intention is to advance just one position.<br/>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name="uIncrement">[IN] The amount of positions to move the iterator forward. If the new position is out of bounds, the iterator 
        /// will point to the position after the last element (end position).</param>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstArrayIterator& MoveForward(const puint_z uIncrement)
        {
            // Note: This code is a copy of the same method of ArrayIterator
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");
            Z_ASSERT_ERROR(((m_uPosition + uIncrement) <= m_pArray->m_uLast + 1U && (m_uPosition + uIncrement) >= m_uPosition) ||
                            (this->IsEnd(EIterationDirection::E_Backward) && (uIncrement - 1U) <= m_pArray->m_uLast + 1U), string_z("The iterator cannot be incremented by such amount (") + string_z::FromInteger(uIncrement) + ")");

            m_uPosition += uIncrement;

            return *this;
        }

        /// <summary>
        /// Decrements the position the iterator points to.
        /// </summary>
        /// <remarks>
        /// It is recommended to use pre-decrement or post-decrement operators instead if the intention is to move just one position back.<br/>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name="uDecrement">[IN] The amount of positions to move the iterator backward. If the new position is out of bounds, the iterator 
        /// will point to the position before the first element (end position).</param>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstArrayIterator& MoveBackward(const puint_z uDecrement)
        {
            // Note: This code is a copy of the same method of ArrayIterator
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");

            m_uPosition = m_uPosition > m_pArray->m_uLast + 1U ? m_pArray->m_uLast + 1U : m_uPosition;

            Z_ASSERT_ERROR((m_uPosition - uDecrement) <= m_uPosition || (m_uPosition - uDecrement) == ArrayFixed::END_POSITION_BACKWARD, string_z("The iterator cannot be decremented by such amount (") + string_z::FromInteger(uDecrement) + ")");

            m_uPosition -= uDecrement;

            return *this;
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// If the array to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_pArray != null_z && (m_uPosition <= m_pArray->m_allocator.GetPoolSize() / sizeof(T) || m_uPosition >= ArrayFixed::END_POSITION_FORWARD);
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const ArrayFixed* GetContainer() const
        {
            return m_pArray;
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
        /// The array the iterator points to.
        /// </summary>
        const ArrayFixed* m_pArray;

        /// <summary>
        /// The current iteration position regarding the first element. It is zero-based.
        /// </summary>
        puint_z m_uPosition;

    }; // ConstArrayIterator


    /// <summary>
    /// Iterator that steps once per element of an array.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to an array, it cannot point to another array ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the array.<br/>
    /// The position before the first element or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ArrayIterator : public ArrayFixed::ConstArrayIterator
    {
        using ArrayFixed::ConstArrayIterator::m_uPosition;
        using ArrayFixed::ConstArrayIterator::m_pArray;
        
        
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the array to iterate and the position to point to. This constructor is intended to be used internally, use
        /// GetIterator method of the ArrayFixed class instead.
        /// </summary>
        /// <remarks>
        /// If the array is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pArray">[IN] The array to iterate. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. It must be lower than the number of elements in the array.</param>
        ArrayIterator(const ArrayFixed* pArray, const puint_z uPosition) : ConstArrayIterator(pArray, uPosition)
        {
        }


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same array as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ArrayIterator& operator=(const ArrayIterator &iterator)
        {
            ConstArrayIterator::operator=(iterator);
            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T& operator*() const
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the array element");
            Z_ASSERT_ERROR(!this->IsEnd(), "The iterator points to an end position, it is not possible to get the reference to the array element");

            return *(m_pArray->m_pElementBasePointer + m_uPosition);
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the array element the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the array element the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        T* operator->() const
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the array element");
            Z_ASSERT_ERROR(!this->IsEnd(), "The iterator points to an end position, it is not possible to get the reference to the array element");

            return m_pArray->m_pElementBasePointer + m_uPosition;
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
        ArrayIterator operator++(int)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator (just replacing ConstArrayIterator with ArrayIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ArrayIterator iteratorCopy = *this;

            ++m_uPosition;

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
        ArrayIterator operator--(int)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator (just replacing ConstArrayIterator with ArrayIterator)

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");

            ArrayIterator iteratorCopy = *this;

            // +1 so the backward end position is moved forward, being 1 unit lower than zero instead of being the greatest number always
            m_uPosition = m_uPosition + 1U > m_pArray->m_uLast + 1U ? m_pArray->m_uLast : --m_uPosition;

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
        ArrayIterator& operator++()
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ++m_uPosition;

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
        ArrayIterator& operator--()
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");

            // +1 so the backward end position is moved forward, being 1 unit lower than zero instead of being the greatest number always
            m_uPosition = m_uPosition + 1U > m_pArray->m_uLast + 1U ? m_pArray->m_uLast : --m_uPosition;

            return *this;
        }
        
        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_WARNING(!m_pArray->IsEmpty(), "The array is empty, there is no first position");

            m_uPosition = m_pArray->m_uFirst == ArrayFixed::END_POSITION_BACKWARD ? ArrayFixed::END_POSITION_FORWARD : 
                                                                                     m_pArray->m_uFirst;
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the array is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            // Note: This code is a copy of the same method of ConstArrayIterator

            Z_ASSERT_WARNING(!m_pArray->IsEmpty(), "The array is empty, there is no last position");

            m_uPosition = m_pArray->m_uLast;
        }
        
        /// <summary>
        /// Increments the position the iterator points to.
        /// </summary>
        /// <remarks>
        /// It is recommended to use pre-increment or post-increment operators instead if the intention is to advance just one position.<br/>
        /// It is not possible to increment an iterator that already points to the position after the last element (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name="uIncrement">[IN] The amount of positions to move the iterator forward. If the new position is out of bounds, the iterator 
        /// will point to the position after the last element (end position).</param>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ArrayIterator& MoveForward(const puint_z uIncrement)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");
            Z_ASSERT_ERROR(((m_uPosition + uIncrement) <= m_pArray->m_uLast + 1U && (m_uPosition + uIncrement) >= m_uPosition) ||
                            (this->IsEnd(EIterationDirection::E_Backward) && (uIncrement - 1U) <= m_pArray->m_uLast + 1U), string_z("The iterator cannot be incremented by such amount (") + string_z::FromInteger(uIncrement) + ")");

            m_uPosition += uIncrement;

            return *this;
        }
        
        /// <summary>
        /// Decrements the position the iterator points to.
        /// </summary>
        /// <remarks>
        /// It is recommended to use pre-decrement or post-decrement operators instead if the intention is to move just one position back.<br/>
        /// It is not possible to decrement an iterator that already points to the position before the first element (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name="uDecrement">[IN] The amount of positions to move the iterator backward. If the new position is out of bounds, the iterator 
        /// will point to the position before the first element (end position).</param>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ArrayIterator& MoveBackward(const puint_z uDecrement)
        {
            // Note: This code is a copy of the same method of ConstArrayIterator
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be decremented");
            Z_ASSERT_ERROR(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to decrement it");

            m_uPosition = m_uPosition > m_pArray->m_uLast + 1U ? m_pArray->m_uLast + 1U : m_uPosition;

            Z_ASSERT_ERROR((m_uPosition - uDecrement) <= m_uPosition || (m_uPosition - uDecrement) == ArrayFixed::END_POSITION_BACKWARD, string_z("The iterator cannot be decremented by such amount (") + string_z::FromInteger(uDecrement) + ")");

            m_uPosition -= uDecrement;

            return *this;
        }

    }; // ArrayIterator


    // TYPEDEFS
    // --------------
public:

    typedef typename ArrayFixed::ArrayIterator Iterator;
    typedef typename ArrayFixed::ConstArrayIterator ConstIterator;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const puint_z END_POSITION_FORWARD;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const puint_z END_POSITION_BACKWARD = -1;
    
    /// <summary>
    /// The default capacity for an array when it is not specified by the user.
    /// </summary>
    static const puint_z DEFAULT_CAPACITY = 1;

public:

    /// <summary>
    /// Constant to symbolize an invalid index returned when an element is not found.
    /// </summary>
    static const puint_z ELEMENT_NOT_FOUND = -1;


    // CONSTRUCTORS
    // ---------------

public:

    /// <summary>
    /// Constructs a fixed array passing the number of elements to store and their initial value.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the array.
    /// </remarks>
    /// <param name="uCount">[IN] Number of elements to store. It must be greater than zero.</param>
    /// <param name="initialValue">[IN] The initial value to assign to all array elements.</param>
    ArrayFixed(const puint_z uCount, const T &initialValue) :
            m_uFirst(0),
            m_uLast(uCount - 1),
            m_allocator(uCount * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
            m_pElementBasePointer(null_z)
    {
        Z_ASSERT_ERROR( uCount > 0, "Zero elements array is not allowed." );
        Z_ASSERT_ERROR( this->_MultiplicationOverflows(uCount, sizeof(T)) == false, "The amount of memory requested overflows the maximum allowed by this container." );

        for(puint_z uIndex = 0; uIndex < uCount; ++uIndex)
        {
            // Allocates and writes in the returned buffer the initial value
            new(m_allocator.Allocate()) T(initialValue);
        }

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }

    /// <summary>
    /// Constructor that receives an existing array and its size.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the array.
    /// </remarks>
    /// <param name="pArray">[IN] The existing array that will be copied. It must not be null.</param>
    /// <param name="uNumberOfElements">[IN] The number of elements in the input array. It must be greater than zero.</param>
    ArrayFixed(const T* pArray, const puint_z uNumberOfElements) :
            m_uFirst(0),
            m_uLast(uNumberOfElements - 1),
            m_allocator(uNumberOfElements * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
            m_pElementBasePointer(null_z)
    {
        Z_ASSERT_ERROR( pArray != null_z, "The argument pArray is null." );
        Z_ASSERT_ERROR( uNumberOfElements > 0, "Zero elements array is not allowed." );

        for(puint_z uIndex = 0; uIndex < uNumberOfElements; ++uIndex)
        {
            // Allocates and writes in the returned buffer a copy of the input array
            new(m_allocator.Allocate()) T(pArray[uIndex]);
        }

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }

    /// <summary>
    /// Copy constructor. Creates a fixed array from another.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every element of the array.
    /// </remarks>
    /// <param name="fixedArray">[IN] Fixed array from which to copy.</param>
    ArrayFixed(const ArrayFixed &fixedArray) :
            m_uFirst(fixedArray.m_uFirst),
            m_uLast(fixedArray.m_uLast),
            m_allocator(fixedArray.GetCount() * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
            m_pElementBasePointer(null_z)
    {
        for(puint_z uIndex = 0; uIndex < fixedArray.m_uLast + 1U; ++uIndex)
        {
            // Constructs a T object over the buffer returned by the allocator and initializes it with
            // the value of the origin element in the corresponding array position.
            new(m_allocator.Allocate()) T(fixedArray[uIndex]);
        }

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }

protected:

    /// <summary>
    /// Constructs an empty and invalid fixed array. It's responsability of the derived classes to initialize it properly.
    /// </summary>
    ArrayFixed() :
        m_uFirst(END_POSITION_BACKWARD),
        m_uLast(END_POSITION_FORWARD),
        m_allocator(ArrayFixed::DEFAULT_CAPACITY * sizeof(T), sizeof(T), Alignment(alignof_z(T))),
        m_pElementBasePointer(null_z)
    {
    }


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor is called for every element of the array.
    /// </remarks>
    ~ArrayFixed()
    {
        const puint_z ARRAY_COUNT = this->GetCount();

        for(puint_z uIndex = 0; uIndex < ARRAY_COUNT; ++uIndex)
            this->GetValue(uIndex).~T();
    }


    // METHODS
    // ---------------
public:
      
    /// <summary>
    /// Defines the assignment operator which makes a copy of the passed fixed array.
    /// </summary>
    /// <remarks>
    /// If the size of the destination array is less than the size of the origin array, it will copy
    /// only the first elements that fit in the destination array. The exceeding elements are not copied and
    /// the size of the destination array does not change.
    /// If the size of the destination array is greater than the size of the origin array, the remaining
    /// elements in the destination array does not change.
    /// Assignment operator will be called for every element of the array.
    /// </remarks>
    /// <param name="fixedArray">[IN] Fixed array from which to copy.</param>
    /// <returns>
    /// A reference to the resulting fixed array.
    /// </returns>
    ArrayFixed& operator= (const ArrayFixed &fixedArray)
    {
        puint_z uElementsToCopy;

        if(m_uLast > fixedArray.m_uLast)
            uElementsToCopy = fixedArray.GetCount();
        else
            uElementsToCopy = this->GetCount();

        for(puint_z uIndex = 0; uIndex < uElementsToCopy; ++uIndex)
        {
            // Destination array element value = Origin array element value, using pointers arithmetic
            this->SetValue(uIndex, fixedArray.GetValue(uIndex));
        }

        return *this;
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the array's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& operator[] (const puint_z uIndex) const
    {
        return this->GetValue(uIndex);
    }

    /// <summary>
    /// Returns a reference to the element stored in the passed position.
    /// </summary>
    /// <param name="uIndex">[IN] Position of the element to access. It must be less than the array's size.</param>
    /// <returns>
    /// A reference to the element stored in the passed position.
    /// </returns>
    T& GetValue(const puint_z uIndex) const
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the array's size." );
        return *(m_pElementBasePointer + uIndex);
    }

    /// <summary>
    /// Performs a fast shallow copy of the array elements.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// Do not use derived class instances as input argument.
    /// </remarks>
    /// <param name="destinationArray"> [IN/OUT] Destination array where to copy the array elements. The capacity of the two arrays has to be equal.</param>
    void Clone(ArrayFixed &destinationArray) const
    {
        Z_ASSERT_ERROR( destinationArray.GetCapacity() == this->GetCapacity(), "The capacity of the two arrays has to be equal." );
        m_allocator.CopyTo(destinationArray.m_allocator);
    }

    /// <summary>
    /// Copies the passed value in the passed position of the array.
    /// </summary>
    /// <remarks>
    /// The assignment operator will be called for the element that is currently occupying that position.
    /// </remarks>
    /// <param name="uIndex">[IN] Position in the array where to copy the value. It must be less than the array's size.</param>
    /// <param name="value">[IN] Value to copy in the array.</param>
    void SetValue(const puint_z uIndex, const T& value)
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the array's size." );
        *(m_pElementBasePointer + uIndex) = value;
    }

    /// <summary>
    /// Gets an iterator that points to a given position in the array.
    /// </summary>
    /// <param name="uIndex">[IN] Position in the array to which the iterator will point. If it is out of bounds, the returned iterator will point 
    /// to the end position.</param>
    /// <returns>
    /// An iterator that points to the position of the element.
    /// </returns>
    ArrayIterator GetIterator(const puint_z uIndex) const 
    {
        Z_ASSERT_ERROR( uIndex < this->GetCount(), "Index must be less than the array's size." );

        return ArrayFixed::ArrayIterator(this, uIndex);
    }

    /// <summary>
    /// Gets an iterator that points to the first position in the array.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the first element. If the array is empty, the iterator will point to the end position.
    /// </returns>
    ArrayIterator GetFirst() const
    {
        return ArrayFixed::ArrayIterator(this, m_uFirst);
    }

    /// <summary>
    /// Gets an iterator that points to the last position in the array.
    /// </summary>
    /// <returns>
    /// An iterator that points to the position of the last element. If the array is empty, the iterator will point to the end position.
    /// </returns>
    ArrayIterator GetLast() const
    {
        return ArrayFixed::ArrayIterator(this, m_uLast);
    }
    
    /// <summary>
    /// Gets a range of elements from the array.
    /// </summary>
    /// <remarks>
    /// The array must not be empty. The copy constructor of every element of the sub-array will be called.
    /// </remarks>
    /// <param name="uFirst">[IN] The index (zero-based) of the first element of the range. It must be lower than the number of elements of the array. 
    /// It must be lower than or equal to the index of the last element.</param>
    /// <param name="uLast">[IN] The index (zero-based) of the last element of the range. It must be lower than the number of elements of the array. 
    /// It must be greater than or equal to the index of the first element.</param>
    /// <returns>
    /// The sub-array that contains the entire range [first, last].
    /// </returns>
    ArrayFixed GetRange(const puint_z uFirst, const puint_z uLast) const
    {
        Z_ASSERT_ERROR(!this->IsEmpty(), "The array is empty, it is not possible to get any range of elements.");
        Z_ASSERT_ERROR(uFirst < this->GetCount(), "The first index is out of bounds.");
        Z_ASSERT_ERROR(uLast < this->GetCount(), "The last index is out of bounds.");
        Z_ASSERT_ERROR(uFirst <= uLast, "The first index must be lower than or equal to the last index.");

        return ArrayFixed(m_pElementBasePointer + uFirst, uLast - uFirst + 1U);
    }
    
    /// <summary>
    /// Gets a range of elements from the array.
    /// </summary>
    /// <remarks>
    /// The array must not be empty. The copy constructor of every element of the sub-array will be called.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element of the range. It must not be an end position. 
    /// It must be prior to the position of the last element.</param>
    /// <param name="last">[IN] The position of the last element of the range. It must not be an end position. 
    /// It must be posterior to the position of the first element.</param>
    /// <returns>
    /// The sub-array that contains the entire range [first, last].
    /// </returns>
    ArrayFixed GetRange(const typename ArrayFixed::ConstArrayIterator first, const typename ArrayFixed::ConstArrayIterator last) const
    {
        Z_ASSERT_ERROR(!this->IsEmpty(), "The array is empty, it is not possible to get any range of elements.");
        Z_ASSERT_ERROR(!first.IsEnd(), "The first position is an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The last position is an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The first position is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The last position is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first index must be lower than or equal to the last index.");

        return ArrayFixed(&*first, last.GetInternalPosition() - first.GetInternalPosition() + 1U);
    }
    
    /// <summary>
    /// Swaps two elements of the array.
    /// </summary>
    /// <remarks>
    /// The array must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="uElementA">[IN] The index (zero-based) of an element. It must be lower than the number of elements of the array.</param>
    /// <param name="uElementB">[IN] The index (zero-based) of the other element. It must be lower than the number of elements of the array.</param>
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
    /// Swaps two elements of the array.
    /// </summary>
    /// <remarks>
    /// The array must not be empty.<br/>
    /// No assignment operator nor copy constructors are called during this operation.
    /// </remarks>
    /// <param name="elementA">[IN] The position of an element. It must not be an end position.</param>
    /// <param name="elementB">[IN] The position of the other element. It must not be an end position.</param>
    void Swap(const typename ArrayFixed::ArrayIterator elementA, const typename ArrayFixed::ArrayIterator elementB)
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
    /// Equality operator that checks whether two arrays are equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other array. Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="array">[IN] The array to compare to.</param>
    /// <returns>
    /// True if all the elements of both arrays are equal; False otherwise.
    /// </returns>
    bool operator==(const ArrayFixed &array) const
    {
        bool bAreEqual = true;

        // If they are not the same instance and they are not both empty
        if(this != &array && !(m_uLast == ArrayFixed::END_POSITION_FORWARD && array.m_uLast == ArrayFixed::END_POSITION_FORWARD))
        {
            // If they have the same number of elements
            if(m_uLast == array.m_uLast)
            {
                ArrayFixed::ConstArrayIterator itThis = this->GetFirst();
                ArrayFixed::ConstArrayIterator itInput = array.GetFirst();

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
    /// Inequality operator that checks whether two arrays are not equal.
    /// </summary>
    /// <remarks>
    /// Every element is compared with the element at the same position in the other array. Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="array">[IN] The array to compare to.</param>
    /// <returns>
    /// True if not all the elements of both arrays are equal; False otherwise.
    /// </returns>
    bool operator!=(const ArrayFixed &array) const
    {
        return !this->operator==(array);
    }
    
    /// <summary>
    /// Checks if any of the elements in the array is equal to a given one.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the array.</param>
    /// <returns>
    /// True if the element is found; False otherwise.
    /// </returns>
    bool Contains(const T &element) const
    {
        const T* pElement = m_pElementBasePointer;
        puint_z uIndex = 0;
        const puint_z ARRAY_COUNT = this->GetCount();
        
        bool bElementFound = false;

        while(uIndex < ARRAY_COUNT && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*pElement, element) == 0;
            ++pElement;
            ++uIndex;
        }

        return bElementFound;
    }
    
    /// <summary>
    /// Searches for the first element in the array equal to a given one and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the array.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    puint_z IndexOf(const T &element) const
    {
        const T* pElement = m_pElementBasePointer;
        puint_z uIndex = 0;
        const puint_z ARRAY_COUNT = this->GetCount();
        
        bool bElementFound = false;

        while(uIndex < ARRAY_COUNT && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*pElement, element) == 0;
            ++pElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : ArrayFixed::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the array equal to a given one, starting from a concrete position, and obtains its position index.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the array.</param>
    /// <param name="uStartIndex">[IN] The start position to search from. It must be lower than the number of elements in the array.</param>
    /// <returns>
    /// The position index (zero-based) of the first element that is equal to the input one. If the element is not found,
    /// the ELEMENT_NOT_FOUND constant will be returned.
    /// </returns>
    puint_z IndexOf(const T &element, const puint_z uStartIndex) const
    {
        const puint_z ARRAY_COUNT = this->GetCount();
        puint_z uIndex = uStartIndex;

        Z_ASSERT_WARNING(uIndex < ARRAY_COUNT, "The input start index must be lower than the number of elements in the array.");

        const T* pElement = m_pElementBasePointer + uStartIndex;
        
        bool bElementFound = false;

        while(uIndex < ARRAY_COUNT && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*pElement, element) == 0;
            ++pElement;
            ++uIndex;
        }

        return bElementFound ? uIndex - 1U : ArrayFixed::ELEMENT_NOT_FOUND;
    }
    
    /// <summary>
    /// Searches for the first element in the array equal to a given one and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the array.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    ArrayIterator PositionOf(const T &element) const
    {
        const T* pElement = m_pElementBasePointer;
        ArrayFixed::ArrayIterator position = this->GetFirst();

        bool bElementFound = false;

        while(!position.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*pElement, element) == 0;
            ++pElement;
            ++position;
        }

        return bElementFound ? --position : position;
    }
    
    /// <summary>
    /// Searches for the first element in the array equal to a given one, starting from a concrete position, and obtains its position.
    /// </summary>
    /// <remarks>
    /// Elements are compared using the array's comparator.
    /// </remarks>
    /// <param name="element">[IN] The element to be searched through the array.</param>
    /// <param name="startPosition">[IN] The start position to search from. It must not point to an end position.</param>
    /// <returns>
    /// The position of the first element that is equal to the input one. If the element is not found,
    /// the iterator will point to the forward end position.
    /// </returns>
    ArrayIterator PositionOf(const T &element, const typename ArrayFixed::ConstArrayIterator &startPosition) const
    {
        Z_ASSERT_WARNING(!startPosition.IsEnd(), "The input start position must not point to an end position.");
        Z_ASSERT_ERROR(startPosition.IsValid(), "The input start position must not point to an end position.");

        const T* pElement = startPosition.IsEnd() ? null_z : &*startPosition;
        ArrayFixed::ArrayIterator position(this, pElement - m_pElementBasePointer);

        bool bElementFound = false;

        while(!position.IsEnd() && !bElementFound)
        {
            bElementFound = ComparatorT::Compare(*pElement, element) == 0;
            ++pElement;
            ++position;
        }

        return bElementFound ? --position : position;
    }

private:

    /// <summary>
    /// Checks if the multiplication of two operands overflows for the puint_z type.
    /// </summary>
    /// <param name="uOperandA">[IN] Operand to multiply.</param>
    /// <param name="uOperandB">[IN] Operand to multiply.</param>
    /// <returns>
    /// True if the result overflows for the puint_z type.
    /// </returns>
    bool _MultiplicationOverflows(puint_z uOperandA, puint_z uOperandB) const
    {
        return this->_HighestOneBitPosition(uOperandA) + this->_HighestOneBitPosition(uOperandB) > sizeof(puint_z) * 8;
    }

    /// <summary>
    /// Gets the highest one bit position of a number converted to binary format.
    /// </summary>
    /// <param name="uValue">[IN] Number to trate.</param>
    /// <returns>
    /// The highest one bit position of the number passed by parameter.
    /// </returns>
    puint_z _HighestOneBitPosition(puint_z uValue) const
    {
        puint_z position = 0;

        while(uValue != 0)
        {
            ++position;
            uValue >>= 1;
        }

        return position;
    }


    // PROPERTIES
    // ---------------
public:
       /// <summary>
    /// Returns a constant pointer to the allocator.
    /// </summary>
    /// <returns>
    /// Constant pointer to the allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return &m_allocator;
    }

    /// <summary>
    /// Returns the number of elements in the array.
    /// </summary>
    /// <returns>
    /// The number of elements in the array.
    /// </returns>
    puint_z GetCount() const
    {
        return m_allocator.GetAllocatedBytes() / sizeof(T);
    }

    /// <summary>
    /// Returns the number of elements that can be stored in the array without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of elements that can be stored in the array without a reallocation.
    /// </returns>
    puint_z GetCapacity() const
    {
        return m_allocator.GetPoolSize() / sizeof(T);
    }

    /// <summary>
    /// Checks whether the array is empty or not.
    /// </summary>
    /// <returns>
    /// True if the array is empty.
    /// </returns>
    bool IsEmpty() const
    {
        return (this->GetCount() == 0);
    }

    // ATTRIBUTES
    // ---------------

protected:

    /// <summary>
    /// Index of the first element in the sequence. If the index points to an invalid position its value is the
    /// END_POSITION_BACKWARD constant.
    /// </summary>
    puint_z m_uFirst;

       /// <summary>
    /// Index of the last element in the sequence. If the index points to an invalid position its value is the
    /// END_POSITION_FORWARD constant.
    /// </summary>
    puint_z m_uLast;
    
    /// <summary>
    /// The allocator which stores the array elements.
    /// </summary>
    AllocatorT m_allocator;
    
    /// <summary>
    /// A pointer to the buffer stored in the memory allocator, casted to the element type, intended to improve overall performance.
    /// </summary>
    T* m_pElementBasePointer;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
// Note: This definition was moved here from the interior of the class because compilation failed when using GCC compiler, the reason is not yet clear
template<class T, class AllocatorT, class ComparatorT>
const puint_z ArrayFixed<T, AllocatorT, ComparatorT>::END_POSITION_FORWARD = -2;


} // namespace z


#ifdef Z_COMPILER_GCC
#pragma GCC diagnostic pop
#endif

#endif // __ARRAYFIXED__

