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

#ifndef __DICTIONARY__
#define __DICTIONARY__

#include "ZMath/MathModuleDefinitions.h"
#include "ZContainers/SComparatorDefault.h"
#include "ZMemory/PoolAllocator.h"
#include "ZContainers/KeyValuePair.h"
#include "ZContainers/BinarySearchTree.h"
#include "ZContainers/SKeyValuePairComparator.h"
#include "ZCommon/DataTypes/SAnyTypeToStringConverter.h"


namespace z
{


/// <summary>
/// Represents a data structure that stores pairs composed of a value and its associated key which must be unique in the container. 
/// </summary>
/// <remarks>
/// Key and value types are forced to implement assignment operator, copy constructor and destructor, all of them publicly accessible.<br/>
/// If SComparatorDefault is used as key comparator, keys will be forced to implement operators "==" and "<".
/// </remarks>
/// <typeparam name="KeyT">The type of the keys associated to every value.</typeparam>
/// <typeparam name="ValueT">The type of the values.</typeparam>
/// <typeparam name="AllocatorT">Optional. The allocator used to reserve memory. The default type is PoolAllocator.</typeparam>
/// <typeparam name="KeyComparatorT">Optional. The type of comparator utilized to compare keys. The default type is SComparatorDefault.</typeparam>
/// <typeparam name="ValueComparatorT">Optional. The type of comparator utilized to compare values. The default type is SComparatorDefault.</typeparam>
template<class KeyT, class ValueT, class AllocatorT = PoolAllocator, class KeyComparatorT = SComparatorDefault<KeyT>, class ValueComparatorT = SComparatorDefault<ValueT> >
class Dictionary
{
    // TYPEDEFS (I)
    // ---------------
protected:

    typedef BinarySearchTree<KeyValuePair<KeyT, ValueT>, AllocatorT, SKeyValuePairComparator<KeyT, ValueT, KeyComparatorT> > InternalBinaryTreeType;
    typedef KeyValuePair<KeyT, ValueT> KeyValuePairType;


    // INTERNAL CLASSES
    // ---------------
public:

    /// <summary>
    /// Iterator that steps once per key-value pair of a dictionary, from the lowest key to the greatest.
    /// </summary>
    /// <remarks>
    /// Once an interator have been bound to a dictionary, it cannot point to another dictionary ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the dictionary.<br/>
    /// The position just before the first element or just after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class ConstDictionaryIterator
    {
        // CONSTRUCTORS
	    // ---------------
    public:

        /// <summary>
        /// Constructor that receives the dictionary to iterate through and the position to physically point to. This constructor is intended 
        /// to be used internally, use GetFirst or GetLast methods of the Dictionary class instead.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, it will point to the end position (forward iteration).
        /// </remarks>
        /// <param name="pDictionary">[IN] The dictionary to iterate through. It must not be null.</param>
        /// <param name="uPosition">[IN] The position the iterator will point to. This is not the logical position of dictionary elements, but the physical.
        /// It must be lower than the capacity of the dictionary.</param>
        ConstDictionaryIterator(const Dictionary* pDictionary, const puint_z uPosition) : m_treeIterator(&pDictionary->m_keyValues, 
                                                                                                                  uPosition, 
                                                                                                                  ETreeTraversalOrder::E_DepthFirstInOrder),
                                                                                                   m_pDictionary(pDictionary)
        {
        }


        // METHODS
	    // ---------------
    public:

        /// <summary>
        /// Assignment operator that moves the iterator to the same position of other iterator. The traversal order is also copied.
        /// </summary>
        /// <param name="iterator">[IN] Iterator whose position will be copied. It must point to the same dictionary as the resident iterator.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstDictionaryIterator& operator=(const ConstDictionaryIterator &iterator)
        {
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid.");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "The input iterator points to a different dictionary.");

            m_treeIterator = iterator.m_treeIterator;

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
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the reference to the dictionary element.");

            return *m_treeIterator;
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
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it is not possible to get the pointer to the dictionary element.");

            return m_treeIterator.operator->();
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
        ConstDictionaryIterator operator++(int)
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ConstDictionaryIterator iteratorCopy = *this;
            m_treeIterator++;
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
        ConstDictionaryIterator operator--(int)
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            ConstDictionaryIterator iteratorCopy = *this;
            m_treeIterator--;
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
        ConstDictionaryIterator& operator++()
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Forward), "The iterator points to an end position, it is not possible to increment it");

            ++m_treeIterator;

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
        ConstDictionaryIterator& operator--()
        {            
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, it cannot be incremented");
            Z_ASSERT_WARNING(!this->IsEnd(EIterationDirection::E_Backward), "The iterator points to an end position, it is not possible to increment it");

            --m_treeIterator;

            return *this;
        }

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same dictionary to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same dictionary; False otherwise.
        /// </returns>
        bool operator==(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator == iterator.m_treeIterator;
        }

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different dictionary is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different dictionary; False otherwise.
        /// </returns>
        bool operator!=(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator != iterator.m_treeIterator;
        }

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator > iterator.m_treeIterator;
        }

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator < iterator.m_treeIterator;
        }

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator >= iterator.m_treeIterator;
        }

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different dictionaries or they are not valid, the result is undefined.<br/>
        /// This is an expensive operation.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstDictionaryIterator &iterator) const
        {
            Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid");
            Z_ASSERT_ERROR(iterator.IsValid(), "The input iterator is not valid");
            Z_ASSERT_ERROR(m_pDictionary == iterator.m_pDictionary, "Iterators point to different dictionaries");

            return m_treeIterator <= iterator.m_treeIterator;
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the dictionary.
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

            return m_treeIterator.IsEnd();
        }

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the dictionary, distinguishing which of them.
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

            return m_treeIterator.IsEnd(eIterationDirection);
        }

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveFirst()
        {
            m_treeIterator.MoveFirst();
        }

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the dictionary is empty, the iterator will point to the end position (forward iteration).
        /// </remarks>
        void MoveLast()
        {
            m_treeIterator.MoveLast();
        }

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a dictionary may have been shortened while the iterator
        /// was pointing to its last position). If the dictionary to iterate has been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first element or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const
        {
            return m_treeIterator.IsValid();
        }
        
        /// <summary>
        /// Gets the container that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the container. It never changes since the iterator is created.
        /// </returns>
        const Dictionary* GetContainer() const
        {
            return m_pDictionary;
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
            return m_treeIterator.GetInternalPosition();
        }


        // ATTRIBUTES
	    // ---------------
    protected:

        /// <summary>
        /// A wrapped binary search tree iterator.
        /// </summary>
        typename InternalBinaryTreeType::ConstIterator m_treeIterator;
        
        /// <summary>
        /// The traversed dictionary.
        /// </summary>
        const Dictionary* m_pDictionary;

    }; // ConstDictionaryIterator


    // TYPEDEFS (II)
    // ---------------
public:

    typedef typename Dictionary::ConstDictionaryIterator ConstIterator;
    

   	// CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// Constant to symbolize the absence of a key-value pair or the end of the sequence when the dictionary is traversed forward.
    /// </summary>
    static const puint_z END_POSITION_FORWARD = -2;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Dictionary()
    {
    }

    /// <summary>
    /// Constructor that receives the initial capacity.
    /// </summary>
    /// <param name="uInitialCapacity">[IN] The number of key-value pairs for which to reserve memory. It must be greater than zero.</param>
    explicit Dictionary(const puint_z uInitialCapacity) : m_keyValues(uInitialCapacity)
    {
    }
    
    /// <summary>
    /// Copy constructor that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// The copy constructor is called for every key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="dictionary">[IN] The other dictionary to be copied.</param>
    Dictionary(const Dictionary &dictionary) : m_keyValues(dictionary.m_keyValues)
    {
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
    ~Dictionary()
    {
    }


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Assignment operator that receives another instance and stores a copy of it.
    /// </summary>
    /// <remarks>
    /// All the elements in the resident dictionary will be firstly removed, calling each keys's and value's destructor.
    /// The copy constructor is then called for every copied key and value, in an arbitrary order.
    /// </remarks>
    /// <param name="dictionary">[IN] The other dictionary to be copied.</param>
    /// <returns>
    /// A reference to the resultant dictionary.
    /// </returns>
    Dictionary& operator=(const Dictionary &dictionary)
    {
        if(this != &dictionary)
            m_keyValues = dictionary.m_keyValues;

        return *this;
    }
        
    /// <summary>
    /// Performs a shallow copy of the content of the dictionary to another dictionary.
    /// </summary>
    /// <remarks>
    /// Care must be taken when instances store pointers to other objects (like strings do); cloning such types may lead to hard-to-debug errors.<br/>
    /// If the capacity of the destination dictionary is lower than the resident's, it will reserve more memory before the copy takes place.<br/>
    /// No constructors will be called during this operation.
    /// </remarks>
    /// <param name="destinationDictionary">[IN/OUT] The destination dictionary to which the contents will be copied.</param>
    void Clone(Dictionary &destinationDictionary) const
    {
        m_keyValues.Clone(destinationDictionary.m_keyValues);
    }

    /// <summary>
    /// Array subscript operator that receives a key and retrieves its associated value.
    /// </summary>
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the dictionary.</param>
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
    /// <param name="key">[IN] A key whose associated value will be obtained. It must exist in the dictionary.</param>
    /// <returns>
    /// A reference to the associated value.
    /// </returns>
    ValueT& GetValue(const KeyT& key) const
    {
        // Creates a fake key-value pair with the input key
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator position = m_keyValues.PositionOf(*pKeyValue, ETreeTraversalOrder::E_DepthFirstInOrder);

        Z_ASSERT_ERROR(!position.IsEnd(), "The specified key does not exist.");

        return ccast_z(position->GetValue(), ValueT&);
    }

    /// <summary>
    /// Sets the value that corresponds to the given key.
    /// </summary>
    /// <remarks>
    /// It calls the assignment operator of the value.
    /// </remarks>
    /// <param name="key">[IN] A key whose associated value will be modified. It must exist in the dictionary.</param>
    /// <param name="newValue">[IN] The value that will replace the existing one.</param>
    void SetValue(const KeyT& key, const ValueT& newValue) const
    {
        this->GetValue(key) = newValue;
    }

    /// <summary>
    /// Empties the dictionary.
    /// </summary>
    /// <remarks>
    /// The destructor of each key and value will be called in an undefined order.
    /// </remarks>
    void Clear()
    {
        m_keyValues.Clear();
    }

    /// <summary>
    /// Increases the capacity of the dictionary, reserving memory for more elements.
    /// </summary>
    /// <remarks>
    /// This operation implies a reallocation, which means that any pointer to elements of this dictionary will be pointing to garbage.
    /// </remarks>
    /// <param name="uNumberOfElements">[IN] The number of elements for which to reserve memory. It should be greater than the
    /// current capacity or nothing will happen.</param>
    void Reserve(const puint_z uNumberOfElements)
    {
        m_keyValues.Reserve(uNumberOfElements);
    }
    
    /// <summary>
    /// Adds a key and its associated value to the dictionary.
    /// </summary>
    /// <remarks>
    /// This operation may imply a reallocation, which means that any pointer to elements of this dictionary will be pointing to garbage.<br/>
    /// The copy constructor of both the new key and the new value will be called.
    /// </remarks>
    /// <param name="key">[IN] The new key. It must not exist in the directory yet.</param>
    /// <param name="value">[IN] The new value associated to the new key.</param>
    /// <returns>
    /// An iterator that points to the just added key-value pair. If the key was already in the dictionary, the returned iterator will point to the end position.
    /// </returns>
    ConstDictionaryIterator Add(const KeyT &key, const ValueT &value)
    {
        Z_ASSERT_ERROR(!this->ContainsKey(key), "The key already exists in the dictionary.");

        // Creates a key-value by copying the data without calling any constructor (which will be called by the internal binary tree)
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        memcpy(pKeyValueBlock + sizeof(KeyT) + ((alignof_z(KeyValuePairType) - sizeof(KeyT)) % alignof_z(KeyValuePairType)), &value, sizeof(ValueT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.Add(*pKeyValue, ETreeTraversalOrder::E_DepthFirstInOrder);

        return ConstDictionaryIterator(this, treeIterator.GetInternalPosition());
    }

    /// <summary>
    /// Removes an key-value pair from the dictionary by its position.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="pairPosition">[IN] The position of the key-value pair to remove. It must not point to the end position.</param>
    /// <returns>
    /// An iterator that points to the next key-value pair. If the removed pair was the last one in the dictionary, the returned iterator will point to the end position.
    /// </returns>
    ConstDictionaryIterator Remove(const typename Dictionary::ConstDictionaryIterator &pairPosition)
    {
        Z_ASSERT_ERROR(!pairPosition.IsEnd(), "The input iterator must not point to an end position.");

        // Creates a key-value by copying the data without calling any constructor
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &pairPosition->GetKey(), sizeof(KeyT));

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.Remove(typename InternalBinaryTreeType::ConstIterator(&m_keyValues, 
                                                                                                                                        pairPosition.GetInternalPosition(), 
                                                                                                                                        ETreeTraversalOrder::E_DepthFirstInOrder));
        
        return Dictionary::ConstDictionaryIterator(this, treeIterator.GetInternalPosition());

    }
    
    /// <summary>
    /// Removes an key-value pair from the dictionary by its key.
    /// </summary>
    /// <remarks>
    /// The destructor of both the key and the value will be called.
    /// </remarks>
    /// <param name="key">[IN] The key to search for. It must exist in the dictionary.</param>
    void Remove(const KeyT &key)
    {
        // Creates a key-value by copying the data without calling any constructor
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.PositionOf(*pKeyValue, ETreeTraversalOrder::E_DepthFirstInOrder);

        Z_ASSERT_ERROR(!treeIterator.IsEnd(), string_z("The input key (") + SAnyTypeToStringConverter::Convert(key) + ") does not exist in the dictionary.");

        m_keyValues.Remove(treeIterator);
    }

    /// <summary>
    /// Gets the first element in the dictionary, which is the one whose key is the lowest.
    /// </summary>
    /// <returns>
    /// An iterator that points to the first key-value pair. If the dictionary is empty, the iterator will point to the end position.
    /// </returns>
    ConstDictionaryIterator GetFirst() const
    {
        Dictionary::ConstDictionaryIterator iterator(this, 0);
        iterator.MoveFirst();
        return iterator;
    }

    /// <summary>
    /// Gets the last element in the dictionary, which is the one whose key is the greatest.
    /// </summary>
    /// <returns>
    /// An iterator that points to the last key-value pair. If the dictionary is empty, the iterator will point to the end position.
    /// </returns>
    ConstDictionaryIterator GetLast() const
    {
        Dictionary::ConstDictionaryIterator iterator(this, 0);
        iterator.MoveLast();
        return iterator;
    }

    /// <summary>
    /// Checks whether there is any value in the dictionary that is equal to another given value.
    /// </summary>
    /// <remarks>
    /// Values are compared to the provided value using the container's value comparator.<br/>
    /// </remarks>
    /// <param name="value">[IN] The value to search for.</param>
    /// <returns>
    /// True if the value is present in the dictionary; False otherwise.
    /// </returns>
    bool ContainsValue(const ValueT &value) const
    {
        ConstDictionaryIterator itKeyValue = this->GetFirst();

        while(!itKeyValue.IsEnd() && ValueComparatorT::Compare(itKeyValue->GetValue(), value) != 0)
            ++itKeyValue;

        return !itKeyValue.IsEnd();
    }

    /// <summary>
    /// Checks whether there is any key in the dictionary that is equal to other given key.
    /// </summary>
    /// <remarks>
    /// Keys are compared to the provided key using the container's key comparator.<br/>
    /// </remarks>
    /// <param name="key">[IN] The key to search for.</param>
    /// <returns>
    /// True if the key is present in the dictionary; False otherwise.
    /// </returns>
    bool ContainsKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        return m_keyValues.Contains(*pKeyValue);
    }

    /// <summary>
    /// Searches for a given key-value pair and obtains its position.
    /// </summary>
    /// <param name="key">[IN] The key of the pair to search for.</param>
    /// <returns>
    /// An iterator that points to the position of the key-value pair. If the key is not present in the dictionary, the iterator will point to the end position.
    /// </returns>
    ConstDictionaryIterator PositionOfKey(const KeyT &key) const
    {
        // Creates a key-value by copying the key without calling its constructor
        u8_z pKeyValueBlock[sizeof(KeyValuePairType)];
        memcpy(pKeyValueBlock, &key, sizeof(KeyT));
        KeyValuePairType* pKeyValue = rcast_z(pKeyValueBlock, KeyValuePairType*);

        typename InternalBinaryTreeType::ConstIterator treeIterator = m_keyValues.PositionOf(*pKeyValue, ETreeTraversalOrder::E_DepthFirstInOrder);

        return ConstDictionaryIterator(this, treeIterator.GetInternalPosition());
    }

    /// <summary>
    /// Equality operator that checks whether two dictionaries are equal.
    /// </summary>
    /// <remarks>
    /// Every key and value are compared with the key and value at the same position in the other dictionary. Keys and values are compared using the dictionary's 
    /// key and value comparator, respectively. The order in which key-value pairs were added is not relevant.
    /// </remarks>
    /// <param name="dictionary">[IN] The dictionary to compare to.</param>
    /// <returns>
    /// True if all the keys and values of both dictionaries are equal; False otherwise.
    /// </returns>
    bool operator==(const Dictionary &dictionary) const
    {
        bool bResult = this->GetCount() == dictionary.GetCount();

        if(bResult && this != &dictionary)
        {
            Dictionary::ConstDictionaryIterator itThisKeyValuePair = this->GetFirst();
            Dictionary::ConstDictionaryIterator itInputKeyValuePair = dictionary.GetFirst();

            while(!itThisKeyValuePair.IsEnd() && bResult)
            {
                bResult = KeyComparatorT::Compare(itThisKeyValuePair->GetKey(), itInputKeyValuePair->GetKey())       == 0 &&
                          ValueComparatorT::Compare(itThisKeyValuePair->GetValue(), itInputKeyValuePair->GetValue()) == 0;
                ++itThisKeyValuePair;
                ++itInputKeyValuePair;
            }
        }

        return bResult;
    }
    
    /// <summary>
    /// Inequality operator that checks whether two dictionaries are different.
    /// </summary>
    /// <remarks>
    /// Every key and value are compared with the key and value at the same position in the other dictionary. Keys and values are compared using the dictionary's 
    /// key and value comparators, respectively. The order in which key-value pairs were added is not relevant.
    /// </remarks>
    /// <param name="dictionary">[IN] The dictionary to compare to.</param>
    /// <returns>
    /// True if any of the keys or values are different; False otherwise.
    /// </returns>
    bool operator!=(const Dictionary &dictionary) const
    {
        return !Dictionary::operator==(dictionary);
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the allocator of keys and values.
    /// </summary>
    /// <returns>
    /// The key-value allocator.
    /// </returns>
    const AllocatorT* GetAllocator() const
    {
        return m_keyValues.GetAllocator();
    }

    /// <summary>
    /// Gets the capacity of the directory, which means the number of elements that can be added before they are reallocated to
    /// another part of memory.
    /// </summary>
    /// <returns>
    /// The capacity of the dictionary.
    /// </returns>
    puint_z GetCapacity() const
    {
        return m_keyValues.GetCapacity();
    }

    /// <summary>
    /// Gets the number of elements added to the dictionary.
    /// </summary>
    /// <returns>
    /// The number of elements in the dictionary.
    /// </returns>
    puint_z GetCount() const
    {
        return m_keyValues.GetCount();
    }
    
    /// <summary>
    /// Indicates whether the dictionary is empty or not.
    /// </summary>
    /// <returns>
    /// True if the dictionary is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const
    {
        return m_keyValues.IsEmpty();
    }


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// The internal binary search tree that holds all the keys.
    /// </summary>
    InternalBinaryTreeType m_keyValues;
};



} // namespace z


#endif // __DICTIONARY__
