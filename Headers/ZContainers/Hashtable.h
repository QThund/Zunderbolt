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

#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "ZMath/MathModuleDefinitions.h"

#include "ZContainers/ArrayDynamic.h"
#include "ZContainers/List.h"
#include "SKeyValuePairComparator.h"
#include "ZContainers/SComparatorDefault.h"
#include "ZContainers/KeyValuePair.h"
#include "SIntegerHashProvider.h"
#include "ZMemory/PoolAllocator.h"
#include "ZCommon/DataTypes/SAnyTypeToStringConverter.h"
#include "ZCommon/DataTypes/ArrayResult.h"


namespace z
{

/// <summary>
/// Represents a hash table, a data structure that acts as an associative array that maps unique keys to values.
/// </summary>
/// <remarks>
/// Currently, the hash table is implemented following the separate-chaining model (a.k.a. closed addressing or open hashing). An array is filled with buckets which point to slots 
/// (colliding elements) stored as key-value pairs into a single shared double-linked list; this allows every bucket to grow indefinitely. The array of buckets can grow too 
/// although it implies rehashing everything.<br/>
/// Hash tables use a hash function or hash provider to compute an internal index that determines the position of a new key-value pair. Such provider depends on the key's data type.<br/>
/// Keys and values are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SComparatorDefault is used as key comparator, keys will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="KeyT">The type of the key associated to every value in the table.</typeparam>
/// <typeparam name="ValueT">The type of the values stored in the table.</typeparam>
/// <typeparam name="HashProviderT">Optional. The type of the hash provider. By default, it is SIntegerHashProvider.</typeparam>
/// <typeparam name="AllocatorT">Optional. The type of the allocator that reserves memory for keys, values and buckets. By default, it is PoolAllocator.</typeparam>
/// <typeparam name="KeyComparatorT">Optional. The type of comparator utilized to compare keys. The default type is SComparatorDefault.</typeparam>
/// <typeparam name="ValueComparatorT">Optional. The type of comparator utilized to compare values. The default type is SComparatorDefault.</typeparam>
template<class KeyT, class ValueT, class HashProviderT = SIntegerHashProvider, 
                                   class AllocatorT = PoolAllocator, 
                                   class KeyComparatorT = SComparatorDefault<KeyT>, 
                                   class ValueComparatorT = SComparatorDefault<ValueT> >
class Hashtable
{
    // TYPEDEFS (I)
    // ---------------
protected:

    typedef KeyValuePair<KeyT, ValueT> KeyValuePairType;
    typedef List<KeyValuePairType, AllocatorT, SKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > SlotListType;


    // INTERNAL CLASSES
    // ---------------
public:

    /// <summary>
    /// Stores information about the position and size of a bucket in the slot list.
    /// </summary>
    class Bucket
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Default constructor that sets up the information about a bucket.
        /// </summary>
        Bucket() : m_uSlotPosition(Hashtable::END_POSITION_FORWARD),
                    m_uSlotCount(0)
        {
        }


        // PROPERTIES
        // ---------------
    public:
        
        /// <summary>
        /// Gets the position of the first slot of the bucket.
        /// </summary>
        /// <returns>
        /// The position of the slot.
        /// </returns>
        puint_z GetSlotPosition() const
        {
            return m_uSlotPosition;
        }
        
        /// <summary>
        /// Sets the position of the first slot of the bucket.
        /// </summary>
        /// <param name="uPosition">[IN] The slot position.</param>
        void SetSlotPosition(const puint_z uPosition)
        {
            m_uSlotPosition = uPosition;
        }
        
        /// <summary>
        /// Gets the number of slots stored in the bucket.
        /// </summary>
        /// <returns>
        /// The amount of slots.
        /// </returns>
        puint_z GetSlotCount() const
        {
            return m_uSlotCount;
        }
        
        /// <summary>
        /// Sets the number of slots stored in the bucket.
        /// </summary>
        /// <param name="uCount">[IN] The number of slots.</param>
        void SetSlotCount(const puint_z uCount)
        {
            m_uSlotCount = uCount;
        }


        // ATTRIBUTES
        // ---------------
    private:
        
        /// <summary>
        /// The physical position of the first slot in the slot list.
        /// </summary>
        puint_z m_uSlotPosition;
        
        /// <summary>
        /// The number of the slots stored in the bucket.
        /// </summary>
        puint_z m_uSlotCount;
    };


    /// <summary>
    /// Iterator that steps once per key-value pair of a hashtable, in an undefined order.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a hashtable, it cannot point to another hashtable ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the hashtable.<br/>
    /// The position just before the first element or just after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ConstHashtableIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the hashtable to iterate through and the position to physically point to. This constructor is intended 
        /// to be used internally, use GetFirst or GetLast methods of the Hashtable class instead.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pHashtable">[IN] The hashtable to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of hashtable elements, but the physical.
        /// It must be lower than the capacity of the hashtable.</param>
        ConstHashtableIterator(const Hashtable* pHashtable, const puint_z uPosition) : m_slotIterator(&pHashtable->m_slots, uPosition),
                                                                                       m_pHashtable(pHashtable)
        {
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same hashtable as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstHashtableIterator& operator=(const ConstHashtableIterator &iterator)
        {
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "The input iterator points to a different hashtable.");

            m_slotIterator = iterator.m_slotIterator;

            return *this;
        }

        /// <summary>
        /// Indirection operator that returns a reference to the key-value pair the iterator points to.
        /// </summary>
        /// <returns>
        /// A reference to the key-value pair the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const KeyValuePairType& operator*() const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the hashtable element.");

            return *m_slotIterator;
        }

        /// <summary>
        /// Dereferencing operator that returns a pointer to the key-value pair the iterator points to.
        /// </summary>
        /// <returns>
        /// A pointer to the key-value pair the iterator points to. If the iterator is invalid or points to an end position,
        /// the result is undefined.
        /// </returns>
        const KeyValuePairType* operator->() const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the hashtable element.");

            return m_slotIterator.operator->();
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
        ConstHashtableIterator operator++(int)
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ConstHashtableIterator iteratorCopy = *this;
            m_slotIterator++;
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
        ConstHashtableIterator operator--(int)
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            ConstHashtableIterator iteratorCopy = *this;
            m_slotIterator--;
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
        ConstHashtableIterator& operator++()
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ++m_slotIterator;

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
        ConstHashtableIterator& operator--()
        {            
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            --m_slotIterator;

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same hashtable to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same hashtable; False otherwise.
        /// </returns>
        bool operator==(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator == iterator.m_slotIterator;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different hashtable is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different hashtable; False otherwise.
        /// </returns>
        bool operator!=(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator != iterator.m_slotIterator;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator > iterator.m_slotIterator;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator < iterator.m_slotIterator;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator >= iterator.m_slotIterator;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different hashtables or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstHashtableIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pHashtable == iterator.m_pHashtable, "Iterators point to different hashtables");

            return m_slotIterator <= iterator.m_slotIterator;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the hashtable.
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

            return m_slotIterator.IsEnd();
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the hashtable, distinguishing which of them.
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

            return m_slotIterator.IsEnd(eIterationDirection);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_slotIterator.MoveFirst();
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the hashtable is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_slotIterator.MoveLast();
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a hashtable may have been shortened while the iterator
        /// was pointing to its last position). If the hashtable to iterate has been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_slotIterator.IsValid();
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const Hashtable* GetContainer() const
        {
            return m_pHashtable;
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
            return m_slotIterator.GetInternalPosition();
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// A wrapped slot list iterator.
        /// </summary>
        typename SlotListType::ConstIterator m_slotIterator;
        
        /// <summary>
        /// The traversed hashtable.
        /// </summary>
        const Hashtable* m_pHashtable;

    }; // ConstHashtableIterator


    // TYPEDEFS (II)
    // ---------------
public:

    typedef typename Hashtable::ConstHashtableIterator ConstIterator;

protected:

    typedef ArrayDynamic<Bucket> BucketsArrayType;


    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Constant to symbolize the end of the sequence near the last element.
    /// </summary>
    static const puint_z END_POSITION_FORWARD = -2;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first element.
    /// </summary>
    static const puint_z END_POSITION_BACKWARD = -1;


    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the initial number of buckets and their expected slots.
    /// </summary>
    /// <param name="uNumberOfBuckets">[IN] The number of buckets in the table. The higher it is, the less collisions occurs. It must be greater than zero.</param>
    /// <param name="uSlotsPerBucket">[IN] The number of expected slots per bucket. The higher it is, the more capacity the table has initially. It must be greater than zero.</param>
    Hashtable(const puint_z uNumberOfBuckets, const puint_z uSlotsPerBucket) : m_arBuckets(uNumberOfBuckets),
                                                                                              m_slots(uNumberOfBuckets * uSlotsPerBucket)
    {
        Z_ASSERT_ERROR(uNumberOfBuckets > 0, "The number of buckets must be greater than zero.");
        Z_ASSERT_ERROR(uSlotsPerBucket > 0, "The number of slots per bucket must be greater than zero.");

        static const Hashtable::Bucket DEFAULT_BUCKET;

        // The array of buckets is pre-allocated and initialized
        for(puint_z uIndex = 0; uIndex < uNumberOfBuckets; ++uIndex)
            m_arBuckets.Add(DEFAULT_BUCKET);
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every copied key and value, in an arbitrary order.<br/>
    /// The capacity of the resultant hashtable is equal to the amount of elements in the input hashtable. If it is empty, then the capacity of the input hashtable is used instead.
    /// </remarks>
    /// <param name="hashtable">[IN] The other hashtable to be copied.</param>
    Hashtable(const Hashtable &hashtable) : m_arBuckets(hashtable.m_arBuckets.GetCount()),
                                              m_slots(hashtable.m_slots.GetCount() == 0 ? hashtable.GetCapacity() : hashtable.m_slots.GetCount())
    {
        static const Hashtable::Bucket DEFAULT_BUCKET;

        // The array of buckets is pre-allocated and initialized
        for(puint_z uIndex = 0; uIndex < hashtable.m_arBuckets.GetCount(); ++uIndex)
            m_arBuckets.Add(DEFAULT_BUCKET);

        // Every key-value pair is copied
        for(Hashtable::ConstHashtableIterator it = hashtable.GetFirst(); !it.IsEnd(); ++it)
            this->Add(it->GetKey(), it->GetValue());
    }


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    /// <remarks>
    /// The destructor of every key and value will be called in an undetermined order.
    /// </remarks>
    ~Hashtable()
    {
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Increases the capacity of the hashtable, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// It does not produce the rehash of any element.<br/>
    /// This operation implies a reallocation, which means that any pointer to elements of this hashtable will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of key-value pairs for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const puint_z uNumberOfElements)
    {
        m_slots.Reserve(uNumberOfElements);
    }

    /// <summary>
    /// Adds a key and its associated value to the hashtable.
    /// </summary>
    /// <remarks>
    /// This operation may imply a reallocation, which means that any pointer to elements of this hashtable will be pointing to garbage.<br/>
    /// The copy constructor of both the new key and the new value will be called.
    /// </remarks>
    /// <param name="key">[IN] The new key. It must not exist in the hashtable yet.</param>
    /// <param name="value">[IN] The new value associated to the new key.</param>
    /// <returns>
    /// An iterator that points to the just added key-value pair. If the key was already in the hashtable, the returned iterator will point to the end position.
    /// </returns>
    ConstHashtableIterator Add(const KeyT &key, const ValueT &value)
    {
        Z_ASSERT_ERROR(!this->ContainsKey(key), string_z("The new key (") + SAnyTypeToStringConverter::Convert(key) + ") already exists in the hashtable.");

        // Gets the corresponding bucket
        puint_z uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        Hashtable::Bucket& bucket = m_arBuckets[uHashKey];
        
        // Creates a key-value by copying the data without calling any constructor
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        memcpy(pKeyValueBlock + sizeof(KeyT) + ((alignof_z(KeyValuePairType) - sizeof(KeyT)) % alignof_z(KeyValuePairType)), &value, sizeof(ValueT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        // Finds the first slot of the bucket
        puint_z uFirstSlotPosition = Hashtable::END_POSITION_FORWARD;

        if(bucket.GetSlotCount() == 0)
        {
            // Adds the first slot to the bucket and stores its position
            m_slots.Add(*pKeyValue);
            uFirstSlotPosition = m_slots.GetLast().GetInternalPosition();
        }
        else
        {
            // Inserts the slot before the first one in the bucket
            typename SlotListType::Iterator newSlot = m_slots.Insert(*pKeyValue, typename SlotListType::Iterator(&m_slots, bucket.GetSlotPosition()));
            uFirstSlotPosition = newSlot.GetInternalPosition();
        }

        bucket.SetSlotPosition(uFirstSlotPosition);
        bucket.SetSlotCount(bucket.GetSlotCount() + 1U);

        return Hashtable::ConstHashtableIterator(this, uFirstSlotPosition);
    }
    
    /// <summary>
    /// Array subscript operator that receives a key and retrieves its associated value.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the hashtable.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& operator[](const KeyT &key) const
    {
        return this->GetValue(key);
    }
    
    /// <summary>
    /// Gets the value that corresponds to the given key.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the hashtable.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& GetValue(const KeyT& key) const
    {
        // Gets the corresponding bucket
        puint_z uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        Hashtable::Bucket& bucket = m_arBuckets[uHashKey];

        Z_ASSERT_ERROR(bucket.GetSlotCount() > 0, string_z("The input key (") + SAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        puint_z uSlot = 0;

        // Traverses all the slots of the bucket
        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
        }
        
        Z_ASSERT_ERROR(uSlot < bucket.GetSlotCount(), string_z("The input key (") + SAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        return ccast_z(slot->GetValue(), ValueT&);
    }

    /// <summary>
    /// Sets the value that corresponds to the given key.
    /// </summary>
    /// <remarks>
    /// It calls the assignment operator of the value.
    /// </remarks>
    /// <param name="key">[IN] A key whose associated value will be modified. It must exist in the hashtable.</param>
    /// <param name="newValue">[IN] The value that will replace the existing one.</param>
    void SetValue(const KeyT& key, const ValueT& newValue) const
    {
        this->GetValue(key) = newValue;
    }
    
    /// <summary>
    /// Checks whether there is any key in the hashtable that is equal to other given key.
    /// </summary>
    /// <remarks>
    /// Keys are compared to the provided key using the container's key comparator.<br/>
    /// </remarks>
    /// <param name="key">[IN] The key to search for.</param>
    /// <returns>
    /// True if the key is present in the hashtable; False otherwise.
    /// </returns>
    bool ContainsKey(const KeyT &key) const
    {
        // Gets the corresponding bucket
        puint_z uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        Hashtable::Bucket& bucket = m_arBuckets[uHashKey];

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        puint_z uSlot = 0;

        // Traverses all the slots of the bucket
        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
        }

        return uSlot != bucket.GetSlotCount();
    }
    
    /// <summary>
    /// Removes an key-value pair from the hashtable by its key.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="key">[IN] The key to search for. It must exist in the hashtable.</param>
    void Remove(const KeyT &key)
    {
        // Gets the corresponding bucket
        puint_z uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        Hashtable::Bucket& bucket = m_arBuckets[uHashKey];

        Z_ASSERT_ERROR(bucket.GetSlotCount() > 0, string_z("The input key (") + SAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        puint_z uSlot = 0;

        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
        }
        
        Z_ASSERT_ERROR(uSlot < bucket.GetSlotCount(), string_z("The input key (") + SAnyTypeToStringConverter::Convert(key) + ") does not exist in the hashtable.");

        typename SlotListType::Iterator itNextSlot = m_slots.Remove(slot);

        // Updates the bucket
        bucket.SetSlotCount(bucket.GetSlotCount() - 1U);

        if(bucket.GetSlotCount() == 0)
        {
            bucket.SetSlotPosition(Hashtable::END_POSITION_FORWARD);
        }
        else if(uSlot == 0)
        {
            puint_z uNewFirstSlotInBucket = itNextSlot.GetInternalPosition();
            bucket.SetSlotPosition(uNewFirstSlotInBucket);
        }
    }

    /// <summary>
    /// Gets the first element in the hashtable, which can be any of the existing elements since no defined order is followed.
    /// </summary>
    /// <returns>
    /// An iterator that points to the first key-value pair. If the hashtable is empty, the iterator will point to the end position.
    /// </returns>
    ConstHashtableIterator GetFirst() const
    {
        Hashtable::ConstHashtableIterator iterator(this, 0);
        iterator.MoveFirst();
        return iterator;
    }

    /// <summary>
    /// Gets the last element in the hashtable, which can be any of the existing elements since no defined order is followed.
    /// </summary>
    /// <returns>
    /// An iterator that points to the last key-value pair. If the hashtable is empty, the iterator will point to the end position.
    /// </returns>
    ConstHashtableIterator GetLast() const
    {
        Hashtable::ConstHashtableIterator iterator(this, 0);
        iterator.MoveLast();
        return iterator;
    }
    
    /// <summary>
    /// Searches for a given key-value pair and obtains its position.
    /// </summary>
    /// <param name="key">[IN] The key of the pair to search for.</param>
    /// <returns>
    /// An iterator that points to the position of the key-value pair. If the key is not present in the hashtable, the iterator will point to the end position.
    /// </returns>
    ConstHashtableIterator PositionOfKey(const KeyT &key) const
    {
        // Gets the corresponding bucket
        puint_z uHashKey = HashProviderT::GenerateHashKey(key, m_arBuckets.GetCount());
        Hashtable::Bucket& bucket = m_arBuckets[uHashKey];

        typename SlotListType::Iterator slot(&m_slots, bucket.GetSlotPosition());
        puint_z uSlot = 0;
        puint_z uResultPosition = bucket.GetSlotPosition();

        // Traverses all the slots of the bucket
        while(uSlot < bucket.GetSlotCount() && KeyComparatorT::Compare(slot->GetKey(), key) != 0)
        {
            ++slot;
            ++uSlot;
            uResultPosition = slot.GetInternalPosition();
        }

        // If the key was not found, the iterator points to an end position
        if(uSlot == bucket.GetSlotCount())
            uResultPosition = Hashtable::END_POSITION_FORWARD;

        return Hashtable::ConstHashtableIterator(this, uResultPosition);
    }

    /// <summary>
    /// Equality operator that checks whether two hashtables are equal.
    /// </summary>
    /// <remarks>
    /// Keys and values are compared using the hashtable's key and value comparator, respectively.
    /// The order in which key-value pairs were added is not relevant.
    /// </remarks>
    /// <param name="hashtable">[IN] The hashtable to compare to.</param>
    /// <returns>
    /// True if all the keys and values of both hashtables are equal; False otherwise.
    /// </returns>
    bool operator==(const Hashtable &hashtable) const
    {
        bool bResult = this->GetCount() == hashtable.GetCount();

        if(bResult && this != &hashtable)
        {
            Hashtable::ConstHashtableIterator itThisKeyValuePair = this->GetFirst();

            while(!itThisKeyValuePair.IsEnd() && bResult)
            {
                Hashtable::ConstHashtableIterator itFoundKey = hashtable.PositionOfKey(itThisKeyValuePair->GetKey());

                bResult = !itFoundKey.IsEnd() && ValueComparatorT::Compare(itThisKeyValuePair->GetValue(), itFoundKey->GetValue()) == 0;
                ++itThisKeyValuePair;
            }
        }

        return bResult;
    }
    
    /// <summary>
    /// Inequality operator that checks whether two hashtables are different.
    /// </summary>
    /// <remarks>
    /// Keys and values are compared using the hashtable's key and value comparators, respectively.
    /// The order in which key-value pairs were added is not relevant.
    /// </remarks>
    /// <param name="hashtable">[IN] The hashtable to compare to.</param>
    /// <returns>
    /// True if any of the keys or values are different; False otherwise.
    /// </returns>
    bool operator!=(const Hashtable &hashtable) const
    {
        return !this->operator==(hashtable);
    }
        
    /// <summary>
    /// Assignment operator that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// All the elements in the resident hashtable will be firstly removed, calling each keys's and value's destructor.
    /// The copy constructor is then called for every copied key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="hashtable">[IN] The other hashtable to be copied.</param>
    /// <returns>
    /// A reference to the resultant hashtable.
    /// </returns>
    Hashtable& operator=(const Hashtable &hashtable)
    {
        static const Hashtable::Bucket DEFAULT_BUCKET;

        if(this != &hashtable)
        {
            // Everything is cleared and prepared for the copy
            m_slots.Clear();
            m_slots.Reserve(hashtable.m_slots.GetCapacity()); // Thund: Using GetCount instead could save some memory?
            m_arBuckets.Clear();
            m_arBuckets.Reserve(hashtable.m_arBuckets.GetCapacity());

            // The array of buckets is pre-allocated and initialized
            for(puint_z uIndex = 0; uIndex < hashtable.m_arBuckets.GetCount(); ++uIndex)
                m_arBuckets.Add(DEFAULT_BUCKET);

            // Every key-value pair is copied
            for(Hashtable::ConstHashtableIterator it = hashtable.GetFirst(); !it.IsEnd(); ++it)
                this->Add(it->GetKey(), it->GetValue());
        }

        return *this;
    }

    /// <summary>
    /// Performs a shallow copy of the content of the hashtable to another hashtable.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// If the capacity of the destination hashtable is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationHashtable">[IN/OUT] The destination hashtable to which the contents will be copied.</param>
    void Clone(Hashtable &destinationHashtable) const
    {
        m_slots.Clone(destinationHashtable.m_slots);
        m_arBuckets.Clone(destinationHashtable.m_arBuckets);
    }
   

    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Returns the number of key-value pairs that can be stored in the hashtable without a reallocation.
    /// </summary>
    /// <returns>
    /// The number of key-value pairs that can be stored in the hashtable without a reallocation.
    /// </returns>
    puint_z GetCapacity() const
    {
        return m_slots.GetCapacity();
    }
    
    /// <summary>
    /// Gets the allocator of keys and values.
    /// </summary>
    /// <returns>
    /// The key-value allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return m_slots.GetAllocator();
    }

    /// <summary>
    /// Gets the number of elements added to the hashtable.
    /// </summary>
    /// <returns>
    /// The number of elements in the hashtable.
    /// </returns>
    puint_z GetCount() const
    {
        return m_slots.GetCount();
    }
    
    /// <summary>
    /// Indicates whether the hashtable is empty or not.
    /// </summary>
    /// <returns>
    /// True if the hashtable is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_slots.IsEmpty();
    }
    
    /// <summary>
    /// Gets all the existing keys from the hashtable.
    /// </summary>
    /// <returns>
    /// An array of keys, in an undefined order. If the hashtable is empty, a null pointer is returned. The wrapper is attached to the array.
    /// </returns>
    ArrayResult<KeyT> GetKeys() const
    {
        KeyT* arKeys = null_z;

        // If the hashtable is empty, a null pointer will be returned
        if(!m_slots.IsEmpty())
            arKeys = new KeyT[m_slots.GetCount()];

        typename SlotListType::Iterator slot = m_slots.GetFirst();
        puint_z uKey = 0;

        for(; !slot.IsEnd(); ++slot, ++uKey)
            new(&arKeys[uKey]) KeyT(slot->GetKey());

        return ArrayResult<KeyT>(arKeys, uKey);
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The array of buckets. Every hash key corresponds to one position in this array.
    /// </summary>
    BucketsArrayType m_arBuckets;

    /// <summary>
    /// The slot list. It is shared among all the buckets. Every bucket knows where its slots are placed in the list.
    /// </summary>
    SlotListType m_slots;

};

} // namespace z


#endif // __HASHTABLE__
