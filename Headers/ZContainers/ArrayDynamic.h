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

#ifndef __DYNAMICARRAY__
#define __DYNAMICARRAY__

#include <algorithm>
#include <cstring>
#include "ZMath/MathModuleDefinitions.h"
#include "ArrayFixed.h"


namespace z
{

/// <summary>
/// Represents a set of elements distributed sequentially as a one-dimensional vector whose length can change if necessary. Every position of 
/// the array can be accessed directly.
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
template<class T, class AllocatorT = PoolAllocator, class ComparatorT = SComparatorDefault<T> >
class ArrayDynamic : public ArrayFixed<T, AllocatorT, ComparatorT>
{
    using ArrayFixed<T, AllocatorT, ComparatorT>::m_allocator;
    using ArrayFixed<T, AllocatorT, ComparatorT>::m_uFirst;
    using ArrayFixed<T, AllocatorT, ComparatorT>::m_uLast;
    using ArrayFixed<T, AllocatorT, ComparatorT>::m_pElementBasePointer;
    

    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// The reallocation factor to be applied to calculate the new capacity on every reallocation. It must be greater than or equal to 1.
    /// </summary>
    static float REALLOCATION_FACTOR;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    /// <remarks>
    /// The initial capacity depends on the value of the default initial capacity of the class.
    /// </remarks>
    ArrayDynamic()
    {
        if(sm_uDefaultCapacity > ArrayDynamic::DEFAULT_CAPACITY)
            this->Reserve(sm_uDefaultCapacity);

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }

    /// <summary>
    /// Constructor that receives the initial capacity.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] The number of elements for which to reserve memory, the initial capacity. If it equals zero, the 
    /// default capacity will be used instead.</param>
    explicit ArrayDynamic(const puint_z uInitialCapacity)
    {
        Z_ASSERT_ERROR(uInitialCapacity > 0, "The initial capacity cannot be zero, it must be, at least, one.");

        puint_z uCapacity = uInitialCapacity;

        if(uInitialCapacity == 0)
            uCapacity = sm_uDefaultCapacity;

        if(uCapacity > ArrayDynamic::DEFAULT_CAPACITY)
            this->Reserve(uCapacity);

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }
    
    /// <summary>
    /// Copy constructor that receives a fixed array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every new element is called, from first to last.<br/>
    /// The capacity of the resultant array will be just the necessary to store the amount of elements of the input array.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    ArrayDynamic(const ArrayFixed<T, AllocatorT, ComparatorT> &arInputArray)
    {
        const puint_z INPUT_COUNT = arInputArray.GetCount();

        // The array is expanded to store the exceeding elements
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        m_uLast = INPUT_COUNT - 1U;// Fixed arrays are supposed not to be empty
        m_uFirst = 0; // Fixed arrays are supposed to start at 0

        // Copies every element
        for(puint_z uIndex = 0; uIndex < m_uLast + 1U; ++uIndex) // Fixed arrays are supposed not to be empty
            new(m_allocator.Allocate()) T(arInputArray[uIndex]);

        m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
    }

    /// <summary>
    /// Copy constructor that receives dynamic array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of every new element is called, from first to last.<br/>
    /// The capacity of the resultant array will be just the necessary to store the amount of elements of the input array.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    ArrayDynamic(const ArrayDynamic &arInputArray)
    {
        const puint_z INPUT_COUNT = arInputArray.GetCount();

        // The array is expanded to store the exceeding elements
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        m_uLast = arInputArray.m_uLast;
        m_uFirst = arInputArray.m_uFirst;

        // Copies every element, if input array is not empty
        if(m_uLast != ArrayDynamic::END_POSITION_FORWARD)
            for(puint_z uIndex = 0; uIndex < m_uLast + 1U; ++uIndex)
                new(m_allocator.Allocate()) T(arInputArray[uIndex]);

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
    ArrayDynamic(const T* pArray, const puint_z uNumberOfElements) : ArrayFixed<T, AllocatorT, ComparatorT>(pArray, uNumberOfElements)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies a fixed array.
    /// </summary>
    /// <remarks>
    /// If the input array has less elements than the resident array, the destructor of the last elements (the difference) 
    /// will be called.<br/>
    /// If the input array has more elements than the resident array, the copy constructor of the new elements (the difference)
    /// will be called.<br/>
    /// When copying an element of a position that already exists in the resident array, the assignment operator of that 
    /// element will be called.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    /// <returns>
    /// A reference to the resultant dynamic array.
    /// </returns>
    ArrayDynamic& operator=(const ArrayFixed<T, AllocatorT, ComparatorT> &arInputArray)
    {
        const puint_z INPUT_COUNT = arInputArray.GetCount();
        const puint_z RESIDENT_COUNT = this->GetCount();

        // The array is expanded to store the exceeding elements, if necessary
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        // Destroys exceeding elements of the resident array
        if(INPUT_COUNT < RESIDENT_COUNT)
        {
            for(puint_z uIndex = INPUT_COUNT; uIndex < RESIDENT_COUNT; ++uIndex)
                this->Remove(INPUT_COUNT);
        }

        // Assigns every existing element
        const puint_z ELEMENTS_TO_ASSIGN = std::min(INPUT_COUNT, RESIDENT_COUNT);
        for(puint_z uIndex = 0; uIndex < ELEMENTS_TO_ASSIGN; ++uIndex)
            this->GetValue(uIndex) = arInputArray[uIndex];

        // Copies new elements
        if(INPUT_COUNT > RESIDENT_COUNT)
            for(puint_z uIndex = RESIDENT_COUNT; uIndex < INPUT_COUNT; ++uIndex)
                this->Add(arInputArray[uIndex]);

        m_uLast = INPUT_COUNT - 1U;
        m_uFirst = 0;

        return *this;
    }
    
    /// <summary>
    /// Assignment operator that copies a dynamic array.
    /// </summary>
    /// <remarks>
    /// If the input array has less elements than the resident array, the destructor of the last elements (the difference) 
    /// will be called.<br/>
    /// If the input array has more elements than the resident array, the copy constructor of the new elements (the difference)
    /// will be called.<br/>
    /// When copying an element of a position that already exists in the resident array, the assignment operator of that 
    /// element will be called.
    /// </remarks>
    /// <param name="arInputArray">[IN] The input array to be copied.</param>
    /// <returns>
    /// A reference to the resultant dynamic array.
    /// </returns>
    ArrayDynamic& operator=(const ArrayDynamic &arInputArray)
    {
        const puint_z INPUT_COUNT = arInputArray.GetCount();
        const puint_z RESIDENT_COUNT = this->GetCount();

        // The array is expanded to store the exceeding elements, if necessary
        if(INPUT_COUNT > this->GetCapacity())
            this->Reserve(INPUT_COUNT);

        // Destroys exceeding elements of the resident array
        if(INPUT_COUNT < RESIDENT_COUNT)
        {
            for(puint_z uIndex = INPUT_COUNT; uIndex < RESIDENT_COUNT; ++uIndex)
                this->Remove(INPUT_COUNT);
        }

        // Assigns every existing element
        const puint_z ELEMENTS_TO_ASSIGN = std::min(INPUT_COUNT, RESIDENT_COUNT);
        for(puint_z uIndex = 0; uIndex < ELEMENTS_TO_ASSIGN; ++uIndex)
            this->GetValue(uIndex) = arInputArray[uIndex];

        // Copies new elements
        if(INPUT_COUNT > RESIDENT_COUNT)
            for(puint_z uIndex = RESIDENT_COUNT; uIndex < INPUT_COUNT; ++uIndex)
                this->Add(arInputArray[uIndex]);

        m_uLast = arInputArray.m_uLast;
        m_uFirst = arInputArray.m_uFirst;

        return *this;
    }

    /// <summary>
    /// Increases the capacity of the array, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this array will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const puint_z uNumberOfElements)
    {
        if(uNumberOfElements > this->GetCapacity())
        {
            m_allocator.Reallocate(uNumberOfElements * sizeof(T));
            m_pElementBasePointer = scast_z(m_allocator.GetPointer(), T*);
        }
    }

    /// <summary>
    /// Copies an element to the end of the array.
    /// </summary>
    /// <remarks>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    void Add(const T &newElement)
    {
        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);
        
        if(this->IsEmpty())
            m_uFirst = m_uLast = 0;
        else
            ++m_uLast;

        new(m_allocator.Allocate()) T(newElement);
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array one position forward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="position">[IN] The position where the new element will be placed. It should not be an end position; if it is, 
    /// the element will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// array; otherwise, the behavior is undefined.</param>
    void Insert(const T &newElement, const typename ArrayDynamic::ConstArrayIterator &position)
    {
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        Z_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        // Gets the position of the iterator
        puint_z uIndex = &(*position) - m_pElementBasePointer;

        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        if(this->IsEmpty())
        {
            m_uFirst = m_uLast = 0;
            new(m_allocator.Allocate()) T(newElement);
        }
        else if(uIndex > m_uLast)
        {
            ++m_uLast;
            new(m_allocator.Allocate()) T(newElement);
        }
        else
        {
            // Increases the allocated space
            ++m_uLast;
            m_allocator.Allocate();
            
            // Moves all the contiguous elements 1 position forward
            memmove(m_pElementBasePointer + uIndex + 1U,   // The position where the next blocks are to be moved
                    m_pElementBasePointer + uIndex,        // The position where the element is to be inserted
                    (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)
                   
            // Calls the copy constructor using the position where the element is inserted
            new(m_pElementBasePointer + uIndex) T(newElement);
        }
    }
    
    /// <summary>
    /// Copies an element to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array one position forward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// The copy constructor of the element will be called.<br/>
    /// Use Add method to insert elements at the end.
    /// </remarks>
    /// <param name="newElement">[IN] The element to be copied.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the new element will be placed. It should be lower than the number of elements of the array; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void Insert(const T &newElement, const puint_z uIndex)
    {
        Z_ASSERT_WARNING(!this->IsEmpty() && uIndex <= m_uLast, "The input index is out of bounds");

        if(this->GetCount() == this->GetCapacity())
            this->_ReallocateByFactor(this->GetCapacity() + 1U);

        if(this->IsEmpty())
        {
            m_uFirst = m_uLast = 0;
            new(m_allocator.Allocate()) T(newElement);
        }
        else if(uIndex > m_uLast)
        {
            ++m_uLast;
            new(m_allocator.Allocate()) T(newElement);
        }
        else
        {
            // Increases the allocated space
            ++m_uLast;
            m_allocator.Allocate();

            // Moves all the contiguous elements 1 position forward
            memmove(m_pElementBasePointer + uIndex + 1U,   // The position where the next blocks are to be moved
                    m_pElementBasePointer + uIndex,        // The position where the element is to be inserted
                    (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)

            // Calls the copy constructor using the position where the element is inserted
            new(m_pElementBasePointer + uIndex) T(newElement);
        }
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array one position backward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="position">[IN] The position of the element to be deleted. It should not be an end position; if it is, 
    /// nothing will be done. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// array; otherwise, the behavior is undefined.</param>
    void Remove(const typename ArrayDynamic::ArrayIterator &position)
    {
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator is not valid");
        Z_ASSERT_WARNING(!this->IsEmpty(), "The array is empty, there is nothing to remove");
        Z_ASSERT_WARNING(!this->IsEmpty() && !position.IsEnd(), "The input iterator is out of bounds");

        // Gets the position of the iterator
        puint_z uIndex = &(*position) - m_pElementBasePointer;

        if(!this->IsEmpty() && uIndex <= m_uLast)
        {
            if(this->GetCount() == 1U)
            {
                // The container is emptied
                m_pElementBasePointer->~T();
                m_uFirst = ArrayDynamic::END_POSITION_BACKWARD;
                m_uLast = ArrayDynamic::END_POSITION_FORWARD;
                m_allocator.Clear();
            }
            else
            {
                // Calls the destructor using the position where the element is removed
                (m_pElementBasePointer + uIndex)->~T();

                // Moves all the contiguous elements 1 position backward
                memmove(m_pElementBasePointer + uIndex,        // The position where the next blocks are to be moved
                        m_pElementBasePointer + uIndex + 1U,   // The position where the next blocks are currently
                        (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)

                // Decreases the allocated space
                m_allocator.Deallocate(m_pElementBasePointer + m_uLast);
                --m_uLast;
            }
        }
    }
    
    /// <summary>
    /// Deletes an element placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array one position backward, which will affect the content pointed 
    /// to by any existing iterator or pointer.<br/>
    /// The destructor of the element will be called.
    /// </remarks>
    /// <param name="uIndex">[IN] The index (zero-based) of the element to be deleted. It should be lower than the number of elements of the array; if it is not, 
    /// nothing will happen.</param>
    void Remove(const puint_z uIndex)
    {
        Z_ASSERT_WARNING(!this->IsEmpty(), "The array is empty, there is nothing to remove");
        Z_ASSERT_WARNING(!this->IsEmpty() && uIndex <= m_uLast, "The input index is out of bounds");

        if(!this->IsEmpty() && uIndex <= m_uLast)
        {
            if(this->GetCount() == 1U)
            {
                // The container is emptied
                m_pElementBasePointer->~T();
                m_uFirst = ArrayDynamic::END_POSITION_BACKWARD;
                m_uLast = ArrayDynamic::END_POSITION_FORWARD;
                m_allocator.Clear();
            }
            else
            {
                // Calls the destructor using the position where the element is removed
                (m_pElementBasePointer + uIndex)->~T();

                // Moves all the contiguous elements 1 position backward
                memmove(m_pElementBasePointer + uIndex,        // The position where the next blocks are to be moved
                        m_pElementBasePointer + uIndex + 1U,   // The position where the next blocks are currently
                        (m_uLast - uIndex) * sizeof(T));       // The (size of) number of blocks to move (count - index - 1)

                // Decreases the allocated space
                m_allocator.Deallocate(m_pElementBasePointer + m_uLast);
                --m_uLast;
            }
        }
    }
    
    /// <summary>
    /// Removes all the elements of the array.
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
            for(puint_z uIndex = m_uFirst; uIndex <= m_uLast; ++uIndex)
                (m_pElementBasePointer + uIndex)->~T();

            m_uFirst = ArrayDynamic::END_POSITION_BACKWARD;
            m_uLast = ArrayDynamic::END_POSITION_FORWARD;

            m_allocator.Clear();
        }
    }
    
    /// <summary>
    /// Performs a shallow copy of the contents of the array to another array.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// If the capacity of the destination array is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="arDestinationArray">[IN/OUT] The destination array to which the contents will be copied.</param>
    void Clone(ArrayDynamic &arDestinationArray) const
    {
        if(arDestinationArray.GetCapacity() < this->GetCapacity())
            arDestinationArray.Reserve(this->GetCapacity());

        this->m_allocator.CopyTo(arDestinationArray.m_allocator);
        arDestinationArray.m_uFirst = m_uFirst;
        arDestinationArray.m_uLast = m_uLast;
    }
    
    /// <summary>
    /// Copies a range of elements from another array to the end of the array.
    /// </summary>
    /// <remarks>
    /// If the capacity of the array is exceeded a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same list is safe only if no reallocation is necessary.<br/>
    /// The first and the last element of the range must belong to the same array.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Calling this method is faster than adding each element one by one.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    void AddRange(const typename ArrayDynamic::ConstArrayIterator &first, const typename ArrayDynamic::ConstArrayIterator &last)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        const puint_z NEW_ELEMENTS_COUNT = last.GetInternalPosition() - first.GetInternalPosition() + 1U;

        if(this->GetCapacity() < this->GetCount() + NEW_ELEMENTS_COUNT)
            this->_ReallocateByFactor(this->GetCount() + NEW_ELEMENTS_COUNT);

        const T* pCurrentInput = &*first;
        const T* pAfterLast = (&*last) + 1U;

        // If the array is empty, sets up the first and the last positions
        if(this->IsEmpty())
        {
            m_uFirst = 0;
            m_uLast = -1;
        }

        // Copies each element in the input range
        for(; pCurrentInput != pAfterLast; ++pCurrentInput)
            new(m_allocator.Allocate()) T(*pCurrentInput);

        m_uLast += NEW_ELEMENTS_COUNT;
    }

    /// <summary>
    /// Copies a range of elements from another array to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array N positions forward (where N is the number of elements in the range), 
    /// which will affect the content pointed to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same array is not safe, strange results may be obtained.<br/>
    /// The first and the last element of the range must belong to the same array.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Calling this method is faster than inserting each element one by one.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="uIndex">[IN] The index (zero-based) where the range of elements will be placed. It should be lower than the number of elements of the array; if it is not, 
    /// the element will be inserted at the end by default.</param>
    void InsertRange(const typename ArrayDynamic::ConstArrayIterator &first, const typename ArrayDynamic::ConstArrayIterator &last, const puint_z uIndex)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        Z_ASSERT_WARNING(uIndex < this->GetCount(), "The index is out of bounds.");

        const bool INSERTING_AT_THE_END = uIndex >= this->GetCount();
        const puint_z FIXED_INDEX = INSERTING_AT_THE_END ? this->GetCount() : uIndex;

        const puint_z NEW_ELEMENTS_COUNT = last.GetInternalPosition() - first.GetInternalPosition() + 1U;

        if(this->GetCapacity() < this->GetCount() + NEW_ELEMENTS_COUNT)
            this->_ReallocateByFactor(this->GetCount() + NEW_ELEMENTS_COUNT);
        
        T* pCurrentResident = m_pElementBasePointer + FIXED_INDEX;
        const T* pCurrentInput = &*first;
        const T* pAfterLast = (&*last) + 1U;

        // If the array is empty, sets up the first and the last positions
        if(this->IsEmpty())
            m_uFirst = 0;

        // Occupies the space for the elementas that will be moved
        for(puint_z i = 0; i < NEW_ELEMENTS_COUNT; ++i)
            m_allocator.Allocate();

        // Moves all the elements of positions posterior to insertion position
        if(!INSERTING_AT_THE_END)
            memmove(pCurrentResident + NEW_ELEMENTS_COUNT, pCurrentResident, (this->GetCount() - FIXED_INDEX - NEW_ELEMENTS_COUNT) * sizeof(T));

        // Copies each element in the input range
        for(; pCurrentInput != pAfterLast; ++pCurrentInput, ++pCurrentResident)
            new(pCurrentResident) T(*pCurrentInput);

        if(m_uLast == ArrayDynamic::END_POSITION_FORWARD)
            ++m_uLast; // Trick: Converts END_POSITION_FORWARD (-2) to END_POSITION_BACKWARD (-1) so the sum below is always correct

        m_uLast += NEW_ELEMENTS_COUNT;
    }
    
    /// <summary>
    /// Copies a range of elements from another array to a concrete position of the array.
    /// </summary>
    /// <remarks>
    /// An insertion produces the movement of all the subsequent elements in the array N positions forward (where N is the number of elements in the range), 
    /// which will affect the content pointed to by any existing iterator or pointer.<br/>
    /// If the capacity of the array is exceeded, a reallocation will take place, which will make any existing pointer invalid.<br/>
    /// Copying elements from the same array is not safe, strange results may be obtained.<br/>
    /// The first and the last element of the range must belong to the same array.<br/>
    /// The copy constructor of each element will be called.<br/>
    /// Calling this method is faster than inserting each element one by one.<br/>
    /// Use AddRange method to insert elements at the end.
    /// </remarks>
    /// <param name="first">[IN] The first element of the range. It must be equal or anterior to the last element in the range. It must not point to an end position.</param>
    /// <param name="last">[IN] The last element of the range. It must be equal or posterior to the first element in the range. It must not point to an end position.</param>
    /// <param name="position">[IN] The position where the range of elements will be placed. It should not be an end position; if it is, 
    /// the range will be inserted at the end by default. If the iterator is invalid, the behavior is undefined. It must point to the same
    /// array; otherwise, the behavior is undefined.</param>
    void InsertRange(const typename ArrayDynamic::ConstArrayIterator &first, const typename ArrayDynamic::ConstArrayIterator &last, const typename ArrayDynamic::ArrayIterator &position)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");
        Z_ASSERT_WARNING(!position.IsEnd(), "The insertion position should not point to an end position.");
        Z_ASSERT_ERROR(position.IsValid(), "The input iterator that points to the insertion position is not valid.");

        const bool INSERTING_AT_THE_END = position.IsEnd();
        const puint_z FIXED_INDEX = INSERTING_AT_THE_END ? this->GetCount() : position.GetInternalPosition();

        const puint_z NEW_ELEMENTS_COUNT = last.GetInternalPosition() - first.GetInternalPosition() + 1U;

        if(this->GetCapacity() < this->GetCount() + NEW_ELEMENTS_COUNT)
        {
            this->_ReallocateByFactor(this->GetCount() + NEW_ELEMENTS_COUNT);
        }
        
        T* pCurrentResident = m_pElementBasePointer + FIXED_INDEX;
        const T* pCurrentInput = &*first;
        const T* pAfterLast = (&*last) + 1U;

        // If the array is empty, sets up the first and the last positions
        if(this->IsEmpty())
            m_uFirst = 0;

        // Occupies the space for the elementas that will be moved
        for(puint_z i = 0; i < NEW_ELEMENTS_COUNT; ++i)
            m_allocator.Allocate();

        // Moves all the elements of positions posterior to insertion position
        if(!INSERTING_AT_THE_END)
            memmove(pCurrentResident + NEW_ELEMENTS_COUNT, pCurrentResident, (this->GetCount() - FIXED_INDEX - NEW_ELEMENTS_COUNT) * sizeof(T));

        // Copies each element in the input range
        for(; pCurrentInput != pAfterLast; ++pCurrentInput, ++pCurrentResident)
            new(pCurrentResident) T(*pCurrentInput);
        
        if(m_uLast == ArrayDynamic::END_POSITION_FORWARD)
            ++m_uLast; // Trick: Converts END_POSITION_FORWARD (-2) to END_POSITION_BACKWARD (-1) so the sum below is always correct

        m_uLast += NEW_ELEMENTS_COUNT;
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array N positions backward (where N is the number of elements in the range), 
    /// which will affect the content pointed to by any existing iterator or pointer.<br/>
    /// Calling this method is faster than removing each element one by one.<br/>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be deleted. It must not be an end position. It must point to the same
    /// array; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be deleted. It must not be an end position. It must point to the same
    /// array; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    void RemoveRange(const typename ArrayDynamic::ArrayIterator &first, const typename ArrayDynamic::ArrayIterator &last)
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        const puint_z ELEMENTS_TO_REMOVE_COUNT = last.GetInternalPosition() - first.GetInternalPosition() + 1U;
        
        T* pFirstInRange = &*first;
        T* pAfterLast = (&*last) + 1U;

        // Deletes each element in the input range
        for(T* pElementToDelete = pFirstInRange; pElementToDelete != pAfterLast; ++pElementToDelete)
            (*pElementToDelete).~T();

        const puint_z FIRST_DELETED_POSITION = pFirstInRange - m_pElementBasePointer;
        const puint_z ELEMENTS_AFTER_LAST = this->GetCount() - FIRST_DELETED_POSITION - ELEMENTS_TO_REMOVE_COUNT;

        // Moves all the elements of positions posterior to the last deleted element to the position of the first removed element
        if(ELEMENTS_AFTER_LAST > 0)
            memmove(pFirstInRange, pAfterLast, ELEMENTS_AFTER_LAST * sizeof(T));

        // Destroys the rest of the elements
        pFirstInRange += ELEMENTS_AFTER_LAST; // Sets the pointer after the current last element

        for(puint_z i = 0; i < ELEMENTS_TO_REMOVE_COUNT; ++i, ++pFirstInRange)
            m_allocator.Deallocate(pFirstInRange);

        if(this->IsEmpty())
            m_uFirst = m_uLast = ArrayDynamic::END_POSITION_FORWARD;
        else
            m_uLast -= ELEMENTS_TO_REMOVE_COUNT;
    }
    
    /// <summary>
    /// Deletes a range of elements placed at a concrete position in the array.
    /// </summary>
    /// <remarks>
    /// A removal produces the movement of all the subsequent elements in the array N positions backward (where N is the number of elements in the range), 
    /// which will affect the content pointed to by any existing iterator or pointer.<br/>
    /// Calling this method is faster than removing each element one by one.<br/>
    /// The destructor of each element will be called.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be deleted. It must be equal or lower than the last element's index in the range. 
    /// It must be lower than the number of elements of the array.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be deleted. It must be equal or greater than the first element's index in the range.
    /// It must be lower than the number of elements of the array.</param>
    void RemoveRange(const puint_z uFirst, const puint_z uLast)
    {
        Z_ASSERT_ERROR(uFirst <= uLast, "The first element must be prior to the last element in the range.");
        Z_ASSERT_ERROR(uFirst < this->GetCount(), "The first position is out of bounds.");
        Z_ASSERT_ERROR(uLast < this->GetCount(), "The last position is out of bounds.");

        const puint_z ELEMENTS_TO_REMOVE_COUNT = uLast - uFirst + 1U;

        T* pFirstInRange = m_pElementBasePointer + uFirst;
        T* pAfterLast = m_pElementBasePointer + uLast + 1U;

        // Deletes each element in the input range
        for(T* pElementToDelete = pFirstInRange; pElementToDelete != pAfterLast; ++pElementToDelete)
            (*pElementToDelete).~T();
        
        const puint_z FIRST_DELETED_POSITION = pFirstInRange - m_pElementBasePointer;
        const puint_z ELEMENTS_AFTER_LAST = this->GetCount() - FIRST_DELETED_POSITION - ELEMENTS_TO_REMOVE_COUNT;

        // Moves all the elements of positions posterior to the last deleted element to the position of the first removed element
        if(ELEMENTS_AFTER_LAST > 0)
            memmove(pFirstInRange, pAfterLast, ELEMENTS_AFTER_LAST * sizeof(T));

        // Destroys the rest of the elements
        pFirstInRange += ELEMENTS_AFTER_LAST; // Sets the pointer after the current last element

        for(puint_z i = 0; i < ELEMENTS_TO_REMOVE_COUNT; ++i, ++pFirstInRange)
            m_allocator.Deallocate(pFirstInRange);

        if(this->IsEmpty())
            m_uFirst = m_uLast = ArrayDynamic::END_POSITION_FORWARD;
        else
            m_uLast -= ELEMENTS_TO_REMOVE_COUNT;
    }
    
    /// <summary>
    /// Gets a range of elements from the array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="first">[IN] The position of the first element to be copied. It must not be an end position. It must point to the same
    /// array; otherwise, the behavior is undefined. It must be equal or anterior to the last element in the range.</param>
    /// <param name="last">[IN] The position of the last element to be copied. It must not be an end position. It must point to to the same
    /// array; otherwise, the behavior is undefined. It must be equal or posterior to the first element in the range.</param>
    /// <returns>
    /// An array that contains a copy of all the elements in the given range.
    /// </returns>
    ArrayDynamic GetRange(const typename ArrayDynamic::ConstArrayIterator &first, const typename ArrayDynamic::ConstArrayIterator &last) const
    {
        Z_ASSERT_ERROR(!first.IsEnd(), "The input iterator that points to the first element must not point to an end position.");
        Z_ASSERT_ERROR(!last.IsEnd(), "The input iterator that points to the last element must not point to an end position.");
        Z_ASSERT_ERROR(first.IsValid(), "The input iterator that points to the first element is not valid.");
        Z_ASSERT_ERROR(last.IsValid(), "The input iterator that points to the last element is not valid.");
        Z_ASSERT_ERROR(first <= last, "The first element must be prior to the last element in the range.");

        const puint_z ELEMENTS_TO_GET_COUNT = last.GetInternalPosition() - first.GetInternalPosition() + 1U;
        
        ArrayDynamic arResult(ELEMENTS_TO_GET_COUNT);

        const T* pCurrentResult = &*first;
        const T* pAfterLast = &*last + 1U;

        // Copies each element in the input range
        for(; pCurrentResult != pAfterLast; ++pCurrentResult)
            new(arResult.m_allocator.Allocate()) T(*pCurrentResult);

        arResult.m_uFirst = 0;
        arResult.m_uLast  = ELEMENTS_TO_GET_COUNT - 1U;

        return arResult;
    }
    
    /// <summary>
    /// Gets a range of elements from the array.
    /// </summary>
    /// <remarks>
    /// The copy constructor of each element in the range will be called, at least, once.
    /// </remarks>
    /// <param name="uFirst">[IN] The position index (zero-based) of the first element to be copied. It must be lower than the number of elements of the array.
    /// It must be equal or lower than the last element's index in the range.</param>
    /// <param name="uLast">[IN] The position index (zero-based) of the last element to be copied. It must be lower than the number of elements of the array.
    /// It must be equal or greater than the first element's index in the range.</param>
    /// <returns>
    /// An array that contains a copy of all the elements in the given range.
    /// </returns>
    ArrayDynamic GetRange(const puint_z uFirst, const puint_z uLast) const
    {
        Z_ASSERT_ERROR(uFirst <= uLast, "The first element must be prior to the last element in the range.");
        Z_ASSERT_ERROR(uFirst < this->GetCount(), "The first position is out of bounds.");
        Z_ASSERT_ERROR(uLast < this->GetCount(), "The last position is out of bounds.");

        const puint_z ELEMENTS_TO_GET_COUNT = uLast - uFirst + 1U;
        
        ArrayDynamic arResult(ELEMENTS_TO_GET_COUNT);

        T* pCurrentResult = m_pElementBasePointer + uFirst;
        T* pAfterLast = m_pElementBasePointer + uLast + 1U;

        // Copies each element in the input range
        for(; pCurrentResult != pAfterLast; ++pCurrentResult)
            new(arResult.m_allocator.Allocate()) T(*pCurrentResult);

        arResult.m_uFirst = 0;
        arResult.m_uLast  = ELEMENTS_TO_GET_COUNT - 1U;

        return arResult;
    }

private:

    /// <summary>
    /// Increases the capacity of the array, reserving memory for more elements than necessary, depending on the reallocation factor.
    /// </summary>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void _ReallocateByFactor(const puint_z uNumberOfElements)
    {
        const puint_z FINAL_CAPACITY = scast_z(scast_z(uNumberOfElements, float) * ArrayDynamic::REALLOCATION_FACTOR, puint_z);
        this->Reserve(FINAL_CAPACITY);
    }


    // PROPERTIES
    // ---------------
public:


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The default capacity of all arrays when it is not specified. It must be greater or equal to 1.
    /// </summary>
    static puint_z sm_uDefaultCapacity;
};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class T, class AllocatorT, class ComparatorT>
puint_z ArrayDynamic<T, AllocatorT, ComparatorT>::sm_uDefaultCapacity = 1;

template<class T, class AllocatorT, class ComparatorT>
float ArrayDynamic<T, AllocatorT, ComparatorT>::REALLOCATION_FACTOR = 1.5f;


} // namespace z


#endif // __DYNAMICARRAY__
