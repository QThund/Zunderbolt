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

#include "ZContainers/Dictionary.h"

#include "ZCommon/CommonModuleDefinitions.h"
#include "CallCounter.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::CallCounter;


ZTEST_SUITE_BEGIN( Dictionary_TestSuite )

/// <summary>
/// Checks that the default values have not changed since the last time this test was executed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]

    // [Execution]
    Dictionary<string_z, int> dictionary;

    // [Verification]
    bool bAllocatorIsNotNull = dictionary.GetAllocator() != null_z;
    BOOST_CHECK(bAllocatorIsNotNull);
}

/// <summary>
/// Checks that the default values have not changed since the last time this test was executed.
/// </summary>
ZTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]

    // [Execution]
    Dictionary<string_z, int> dictionary(1);

    // [Verification]
    bool bAllocatorIsNotNull = dictionary.GetAllocator() != null_z;
    BOOST_CHECK(bAllocatorIsNotNull);
}

/// <summary>
/// Checks that the initial capacity is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_CapacityIsCorrectlyStored_Test )
{
    // [Preparation]
    const puint_z EXPECPTED_CAPACITY = 6;

    // [Execution]
    Dictionary<string_z, int> dictionary(EXPECPTED_CAPACITY);

    // [Verification]
    puint_z uCapacity = dictionary.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECPTED_CAPACITY);
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
        Dictionary<string_z, int> dictionary(INPUT_ZERO);
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
/// Checks that the dictionary is correctly copied when it has elements.
/// </summary>
ZTEST_CASE ( Constructor3_DictionaryIsCorrectlyCopiedWhenItHasElements_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);

    const puint_z EXPECTED_COUNT = DICTIONARY.GetCount();

    // [Execution]
    Dictionary<string_z, int> copiedDictionary(DICTIONARY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    puint_z uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when it is empty.
/// </summary>
ZTEST_CASE ( Constructor3_DictionaryIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    Dictionary<string_z, int> copiedDictionary(DICTIONARY);

    // [Verification]
    bool bDictionaryIsEmpty = copiedDictionary.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each element.
/// </summary>
ZTEST_CASE ( Constructor3_CopyConstructorsAreCalledForAllElements_Test )
{
    // [Preparation]
    Dictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    const puint_z EXPECTED_VALUE = DICTIONARY.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    Dictionary<CallCounter, CallCounter> copiedDictionary(DICTIONARY);

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the destructor of every key and every value is called.
/// </summary>
ZTEST_CASE ( Destructor_DestructorOfEveryKeyAndValueIsCalled_Test )
{
    // [Preparation]
    const puint_z EXPECTED_DESTRUCTOR_CALLS = 6;

    {
        Dictionary<CallCounter, CallCounter> dictionary;
        dictionary.Add(CallCounter(), CallCounter());
        dictionary.Add(CallCounter(), CallCounter());
        dictionary.Add(CallCounter(), CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    } // Destructor called

    // [Verification]
    puint_z uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_DESTRUCTOR_CALLS);
}

/// <summary>
/// Checks that the dictionary is correctly copied when it has elements and the destination dictionary is empty.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);

    const puint_z EXPECTED_COUNT = DICTIONARY.GetCount();
    Dictionary<string_z, int> copiedDictionary(8);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    puint_z uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when there are more elements in the source dictionary than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4", "key5"};
    const int EXPECTED_VALUES[] = {1, 3, 5, 6, 8};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    DICTIONARY.Add("key5", 8);
    const puint_z EXPECTED_COUNT = DICTIONARY.GetCount();

    Dictionary<string_z, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    puint_z uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when there are less elements in the source dictionary than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2"};
    const int EXPECTED_VALUES[] = {1, 3};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    const puint_z EXPECTED_COUNT = DICTIONARY.GetCount();

    Dictionary<string_z, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    puint_z uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when there are the same number of elements in the source dictionary than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 3, 5};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 3);
    DICTIONARY.Add("key3", 5);
    const puint_z EXPECTED_COUNT = DICTIONARY.GetCount();

    Dictionary<string_z, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = copiedDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    puint_z uCount = copiedDictionary.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is correctly copied when it is empty and the destination dictionary has elements.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DictionaryIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);
    Dictionary<string_z, int> copiedDictionary(3);
    copiedDictionary.Add("key5", 10);
    copiedDictionary.Add("key6", 11);
    copiedDictionary.Add("key7", 12);

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    bool bDictionaryIsEmpty = copiedDictionary.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each key and value.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllKeysAndValues_Test )
{
    // [Preparation]
    Dictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    Dictionary<CallCounter, CallCounter> copiedDictionary(3);
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());

    const puint_z EXPECTED_COPY_CONSTRUCTORS_VALUE = DICTIONARY.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_COPY_CONSTRUCTORS_VALUE);
}

/// <summary>
/// Checks that the destructors are called for each key and value.
/// </summary>
ZTEST_CASE ( OperatorAssignment_DestructorsAreCalledForAllKeysAndValues_Test )
{
    // [Preparation]
    Dictionary<CallCounter, CallCounter> DICTIONARY(5);
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());
    DICTIONARY.Add(CallCounter(), CallCounter());

    Dictionary<CallCounter, CallCounter> copiedDictionary(3);
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());
    copiedDictionary.Add(CallCounter(), CallCounter());

    const puint_z EXPECTED_DESTRUCTORS_VALUE = copiedDictionary.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    copiedDictionary = DICTIONARY;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
ZTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalDictionary_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 3, 5};
    Dictionary<string_z, int> sourceDictionary(5);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 3);
    sourceDictionary.Add("key3", 5);

    Dictionary<string_z, int> destinationDictionary(3);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination dictionary has more capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalDictionaryWhenInputDictionaryHasMoreCapacityAndElements_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3"};
    const int EXPECTED_VALUES[] = {1, 2, 3};
    Dictionary<string_z, int> sourceDictionary(3);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 2);
    sourceDictionary.Add("key3", 3);

    Dictionary<string_z, int> destinationDictionary(5);
    destinationDictionary.Add("key4", 4);
    destinationDictionary.Add("key5", 5);
    destinationDictionary.Add("key6", 6);
    destinationDictionary.Add("key7", 7);
    destinationDictionary.Add("key8", 8);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks if it the clone method works properly when the destination dictionary has less capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedDictionaryHasSameValuesThanTheOriginalDictionaryWhenInputDictionaryHasLessCapacityAndElements_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key2", "key3", "key4",  "key5"};
    const int EXPECTED_VALUES[] = {1, 2, 3, 4, 5};
    Dictionary<string_z, int> sourceDictionary(5);
    sourceDictionary.Add("key1", 1);
    sourceDictionary.Add("key2", 2);
    sourceDictionary.Add("key3", 3);
    sourceDictionary.Add("key4", 4);
    sourceDictionary.Add("key5", 5);

    Dictionary<string_z, int> destinationDictionary(3);
    destinationDictionary.Add("key6", 6);
    destinationDictionary.Add("key7", 7);
    destinationDictionary.Add("key8", 8);

    // [Execution]
    sourceDictionary.Clone(destinationDictionary);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = destinationDictionary.GetFirst();
    int i = 0;

    for(; !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the dictionary is empty when removing the only element in it.
/// </summary>
ZTEST_CASE ( Remove1_DictionaryIsEmptyWhenRemovingTheOnlyElementInTheDictionary_Test )
{
    // [Preparation]
    const string_z EXISTING_KEY("key1");
    Dictionary<string_z, int> DICTIONARY(3);
    Dictionary<string_z, int>::ConstDictionaryIterator itElementPosition = DICTIONARY.Add(EXISTING_KEY, 0);

    // [Execution]
    DICTIONARY.Remove(itElementPosition);

    // [Verification]
    bool bDictionaryIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the key-value pair is removed when there are many pairs in the dictionary and the key exists.
/// </summary>
ZTEST_CASE ( Remove1_PairIsCorrectlyRemovedWhenThereAreManyAndKeyExists_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEYS[] = {"key1", "key3", "key4"};
    const int EXPECTED_VALUES[] = {1, 3, 4};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    Dictionary<string_z, int>::ConstDictionaryIterator itElementPosition = DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);
    DICTIONARY.Add("key4", 4);

    // [Execution]
    DICTIONARY.Remove(itElementPosition);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = Dictionary<string_z, int>::ConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the returned iterator points to the end position when there is not next element in the dictionary.
/// </summary>
ZTEST_CASE ( Remove1_ReturnedIteratorPointsToEndPositionWhenThereIsNoNextElementInDictionary_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    Dictionary<string_z, int>::ConstDictionaryIterator itLastElement = DICTIONARY.Add("key2", 2);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itResult = DICTIONARY.Remove(itLastElement);

    // [Verification]
    bool bIteratorPointsToEndPosition = itResult.IsEnd();
    BOOST_CHECK(bIteratorPointsToEndPosition);
}

/// <summary>
/// Checks that the returned iterator points to the next element.
/// </summary>
ZTEST_CASE ( Remove1_ReturnedIteratorPointsToNextElement_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(4);
    DICTIONARY.Add("key1", 1);
    Dictionary<string_z, int>::ConstDictionaryIterator itElementToRemove = DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);
    DICTIONARY.Add("key4", 4);
    Dictionary<string_z, int>::ConstDictionaryIterator EXPECTED_ITERATOR = itElementToRemove;
    ++EXPECTED_ITERATOR;

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itResult = DICTIONARY.Remove(itElementToRemove);

    // [Verification]
    BOOST_CHECK(itResult == EXPECTED_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator points to end position.
/// </summary>
ZTEST_CASE ( Remove1_AssertionFailsWhenTheInputIteratorPointsToEndPosition_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(1);
    Dictionary<string_z, int>::ConstDictionaryIterator itEnd = DICTIONARY.Add("key1", 1);
    ++itEnd;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.Remove(itEnd);
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
/// Checks that the dictionary is empty when removing the only element in it.
/// </summary>
ZTEST_CASE ( Remove2_DictionaryIsEmptyWhenRemovingTheOnlyElementInTheDictionary_Test )
{
    // [Preparation]
    const string_z EXISTING_KEY("key1");
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add(EXISTING_KEY, 0);

    // [Execution]
    DICTIONARY.Remove(EXISTING_KEY);

    // [Verification]
    bool bDictionaryIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bDictionaryIsEmpty);
}

/// <summary>
/// Checks that the key-value pair is removed when there are many pairs in the dictionary and the key exists.
/// </summary>
ZTEST_CASE ( Remove2_PairIsCorrectlyRemovedWhenThereAreManyAndKeyExists_Test )
{
    // [Preparation]
    const string_z EXISTING_KEY("key2");
    const string_z EXPECTED_KEYS[] = {"key1", "key3", "key4"};
    const int EXPECTED_VALUES[] = {1, 3, 4};
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(EXISTING_KEY, 2);
    DICTIONARY.Add("key3", 3);
    DICTIONARY.Add("key4", 4);

    // [Execution]
    DICTIONARY.Remove(EXISTING_KEY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = Dictionary<string_z, int>::ConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input key does not exist in the dictionary.
/// </summary>
ZTEST_CASE ( Remove2_AssertionFailsWhenTheInputKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z NON_EXISTING_KEY("key2");
    Dictionary<string_z, int> DICTIONARY(1);
    DICTIONARY.Add("key1", 1);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.Remove(NON_EXISTING_KEY);
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
/// Checks that the number of elements is correctly counted.
/// </summary>
ZTEST_CASE ( GetCount_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    puint_z uCount = DICTIONARY.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns zero when the dictionary is empty.
/// </summary>
ZTEST_CASE ( GetCount_ReturnsZeroWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 0;
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    puint_z uCount = DICTIONARY.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

/// <summary>
/// Checks that it returns True when the dictionary is empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsTrueWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    bool bResult = DICTIONARY.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary is not empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsFalseWhenDictionaryIsNotEmpty_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);

    // [Execution]
    bool bResult = DICTIONARY.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the correct value is returned when the key exists in the dictionary.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, EXPECTED_VALUE);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    int nValue = DICTIONARY[INPUT_KEY];

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_KEY("key2");
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY[INPUT_KEY];
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
/// Checks that the correct value is returned when the key exists in the dictionary.
/// </sumary>
ZTEST_CASE( GetValue_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, EXPECTED_VALUE);
    DICTIONARY.Add("key3", 3);
    

    // [Execution]
    int nValue = DICTIONARY.GetValue(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
ZTEST_CASE( GetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_KEY("key2");
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.GetValue(INPUT_KEY);
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
/// Checks that the value is set when the key exists in the dictionary.
/// </sumary>
ZTEST_CASE( SetValue_ValueIsSetWhenKeyExists_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key2");
    const int EXPECTED_VALUE = 2;
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(INPUT_KEY, 10);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    DICTIONARY.SetValue(INPUT_KEY, EXPECTED_VALUE);

    // [Verification]
    int nValue = DICTIONARY.GetValue(INPUT_KEY);
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the dictionary.
/// </sumary>
ZTEST_CASE( SetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_KEY("key2");
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.SetValue(INPUT_KEY, 0);
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
/// Checks that the dictionary is emptied.
/// </sumary>
ZTEST_CASE( Clear_TheDictinaryIsEmptied_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    DICTIONARY.Clear();

    // [Verification]
    bool bIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <sumary>
/// Checks that nothing is done when the dictionary is already empty.
/// </sumary>
ZTEST_CASE( Clear_NothingHappensWhenDictionaryIsAlreadyEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    DICTIONARY.Clear();

    // [Verification]
    bool bIsEmpty = DICTIONARY.IsEmpty();
    BOOST_CHECK(bIsEmpty);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
ZTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 4;
    Dictionary<string_z, int> DICTIONARY(2);

    // [Execution]
    DICTIONARY.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = DICTIONARY.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
ZTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 4;
    const string_z EXPECTED_FIRST_KEY("key1");
    const string_z EXPECTED_SECOND_KEY("key2");
    const int EXPECTED_FIRST_VALUE = 1;
    const int EXPECTED_SECOND_VALUE = 2;
    Dictionary<string_z, int> DICTIONARY(2);
    DICTIONARY.Add(EXPECTED_FIRST_KEY, EXPECTED_FIRST_VALUE);
    DICTIONARY.Add(EXPECTED_SECOND_KEY, EXPECTED_SECOND_VALUE);

    // [Execution]
    DICTIONARY.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    Dictionary<string_z, int>::ConstDictionaryIterator it = DICTIONARY.GetFirst();
    BOOST_CHECK(it->GetKey() == EXPECTED_FIRST_KEY);
    BOOST_CHECK(it->GetValue() == EXPECTED_FIRST_VALUE);
    ++it;
    BOOST_CHECK(it->GetKey() == EXPECTED_SECOND_KEY);
    BOOST_CHECK(it->GetValue() == EXPECTED_SECOND_VALUE);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than current reserved.
/// </summary>
ZTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 1;
    const puint_z EXPECTED_CAPACITY = 4;
    Dictionary<string_z, int> DICTIONARY(4);

    // [Execution]
    DICTIONARY.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    puint_z uCapacity = DICTIONARY.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the element is correctly added when the dictionary is empty.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 0;
    const string_z EXPECTED_KEYS[] = {INPUT_KEY};
    const int EXPECTED_VALUES[] = {INPUT_VALUE};
    
    Dictionary<string_z, int> DICTIONARY(3);

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = Dictionary<string_z, int>::ConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when the dictionary only contains one element.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenDictionaryOnlyContainsOneElement_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 0;
    const string_z EXPECTED_KEYS[] = {INPUT_KEY, "key2"};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 1);

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Dictionary<string_z, int>::ConstDictionaryIterator it = Dictionary<string_z, int>::ConstDictionaryIterator(&DICTIONARY, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
ZTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itResult = DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(itResult->GetKey() == INPUT_KEY);
    BOOST_CHECK(itResult->GetValue() == INPUT_VALUE);
}

/// <summary>
/// Checks that the number of elements is incremented after adding.
/// </summary>
ZTEST_CASE ( Add_CountIsIncremented_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    Dictionary<string_z, int> DICTIONARY(3);
    DICTIONARY.Add("key2", 2);
    const puint_z COUNT_BEFORE_ADDING = DICTIONARY.GetCount();

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    puint_z uCountAfterAdding = DICTIONARY.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
ZTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    Dictionary<string_z, int> DICTIONARY(1);
    DICTIONARY.Add("key2", 2);
    const puint_z CAPACITY_BEFORE_ADDING = DICTIONARY.GetCapacity();

    // [Execution]
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    puint_z uCapacityAfterAdding = DICTIONARY.GetCapacity();
    BOOST_CHECK(uCapacityAfterAdding > CAPACITY_BEFORE_ADDING);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the key already exists.
/// </summary>
ZTEST_CASE ( Add_AssertionFailsWhenTheKeyAlreadyExists_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_KEY("key1");
    const int INPUT_VALUE = 1;
    
    Dictionary<string_z, int> DICTIONARY(1);
    DICTIONARY.Add(INPUT_KEY, INPUT_VALUE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        DICTIONARY.Add(INPUT_KEY, 0);
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
/// Checks that the iterator is obtained.
/// </sumary>
ZTEST_CASE( GetFirst_IteratorIsObtained_Test )
{
    // [Preparation]
    const string_z EXPECTED_ELEMENT_KEY("key1");
    const int EXPECTED_ELEMENT_VALUE = 1;
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itFirst = DICTIONARY.GetFirst();

    // [Verification]
    BOOST_CHECK(itFirst->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itFirst->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the dictionary is empty.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnedIteratorPointsToEndWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itFirst = DICTIONARY.GetFirst();

    // [Verification]
    bool bIteratorPointstoEnd = itFirst.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that the iterator is obtained.
/// </sumary>
ZTEST_CASE( GetLast_IteratorIsObtained_Test )
{
    // [Preparation]
    const string_z EXPECTED_ELEMENT_KEY("key3");
    const int EXPECTED_ELEMENT_VALUE = 3;
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itLast = DICTIONARY.GetLast();

    // [Verification]
    BOOST_CHECK(itLast->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itLast->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the dictionary is empty.
/// </sumary>
ZTEST_CASE( GetLast_ReturnedIteratorPointsToEndWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itLast = DICTIONARY.GetLast();

    // [Verification]
    bool bIteratorPointstoEnd = itLast.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <sumary>
/// Checks that it returns True when dictionaries are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenDictionariesAreExactlyEqual_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2 = DICTIONARY1;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY1 == DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when dictionaries are the same instance.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenDictionariesAreTheSameInstance_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);
    DICTIONARY.Add("key4", 4);
    DICTIONARY.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY == DICTIONARY;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the order in which pairs were added to the dictionary does not affect the result.
/// </sumary>
ZTEST_CASE( OperatorEquality_AdditionOrderDoesNotMatter_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2(5);
    DICTIONARY2.Add("key3", 3);
    DICTIONARY2.Add("key2", 2);
    DICTIONARY2.Add("key4", 4);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY1 == DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when dictionaries are empty.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenDictionariesAreEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    Dictionary<string_z, int> DICTIONARY2(5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY1 == DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when both dictionaries have a different number of pairs which are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenDictionariesHaveDifferentNumberOfElementsWithSameValues_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2(4);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key2", 2);
    DICTIONARY2.Add("key3", 3);
    DICTIONARY2.Add("key4", 4);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY1 == DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when both dictionaries have the same number of pairs which are not equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenDictionariesHaveSameNumberOfElementsWithDifferentValues_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2x", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 50);

    Dictionary<string_z, int> DICTIONARY2(5);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key2", 90);
    DICTIONARY2.Add("key3x", 3);
    DICTIONARY2.Add("key4", 4);
    DICTIONARY2.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY1 == DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when dictionaries are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenDictionariesAreExactlyEqual_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2 = DICTIONARY1;

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY1 != DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when dictionaries are the same instance.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenDictionariesAreTheSameInstance_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 2);
    DICTIONARY.Add("key3", 3);
    DICTIONARY.Add("key4", 4);
    DICTIONARY.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY != DICTIONARY;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the order in which pairs were added to the dictionary does not affect the result.
/// </sumary>
ZTEST_CASE( OperatorInequality_AdditionOrderDoesNotMatter_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2(5);
    DICTIONARY2.Add("key3", 3);
    DICTIONARY2.Add("key2", 2);
    DICTIONARY2.Add("key4", 4);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY1 != DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when dictionaries are empty.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenDictionariesAreEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    Dictionary<string_z, int> DICTIONARY2(5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY1 != DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when both dictionaries have a different number of pairs which are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenDictionariesHaveDifferentNumberOfElementsWithSameValues_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 5);

    Dictionary<string_z, int> DICTIONARY2(4);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key2", 2);
    DICTIONARY2.Add("key3", 3);
    DICTIONARY2.Add("key4", 4);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY1 != DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when both dictionaries have the same number of pairs which are not equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenDictionariesHaveSameNumberOfElementsWithDifferentValues_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY1(5);
    DICTIONARY1.Add("key1", 1);
    DICTIONARY1.Add("key2x", 2);
    DICTIONARY1.Add("key3", 3);
    DICTIONARY1.Add("key4", 4);
    DICTIONARY1.Add("key5", 50);

    Dictionary<string_z, int> DICTIONARY2(5);
    DICTIONARY2.Add("key1", 1);
    DICTIONARY2.Add("key2", 90);
    DICTIONARY2.Add("key3x", 3);
    DICTIONARY2.Add("key4", 4);
    DICTIONARY2.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY1 != DICTIONARY2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the dictionary contains the value.
/// </summary>
ZTEST_CASE ( ContainsValue_ReturnsTrueWhenDictionaryContainsTheValue_Test )
{
    // [Preparation]
    const int INPUT_VALUE = 3;
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 4);
    DICTIONARY.Add("key3", INPUT_VALUE);
    DICTIONARY.Add("key4", 6);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY.ContainsValue(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary does not contain the value.
/// </summary>
ZTEST_CASE ( ContainsValue_ReturnsFalseWhenDictionaryDoesNotContainTheValue_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 4);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    const int INPUT_VALUE = 0;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY.ContainsValue(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary is empty.
/// </summary>
ZTEST_CASE ( ContainsValue_ReturnsFalseWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);
    const int INPUT_VALUE = 5;
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY.ContainsValue(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the dictionary contains the key.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsTrueWhenDictionaryContainsTheKey_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key3");
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 4);
    DICTIONARY.Add(INPUT_KEY, 5);
    DICTIONARY.Add("key4", 6);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = DICTIONARY.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary does not contain the key.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsFalseWhenDictionaryDoesNotContainTheKey_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 4);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);
    const string_z INPUT_KEY("key5");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the dictionary is empty.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsFalseWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    Dictionary<string_z, int> DICTIONARY(3);
    const string_z INPUT_KEY("key1");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = DICTIONARY.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected position when the dictionary contains the key.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsExpectedPositionWhenDictionaryContainsTheKey_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key2");
    const int EXPECTED_VALUE = 4;
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add(EXPECTED_KEY, EXPECTED_VALUE);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itPosition = DICTIONARY.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    BOOST_CHECK(itPosition->GetKey() == EXPECTED_KEY);
    BOOST_CHECK(itPosition->GetValue() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the dictionary does not contain the element.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsEndPositionWhenDictionaryDoesNotContainTheElement_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key5");
    Dictionary<string_z, int> DICTIONARY(5);
    DICTIONARY.Add("key1", 1);
    DICTIONARY.Add("key2", 4);
    DICTIONARY.Add("key3", 5);
    DICTIONARY.Add("key4", 6);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itPosition = DICTIONARY.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the dictionary is empty.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsEndPositionWhenDictionaryIsEmpty_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key1");
    Dictionary<string_z, int> DICTIONARY(5);

    // [Execution]
    Dictionary<string_z, int>::ConstDictionaryIterator itPosition = DICTIONARY.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that the capacity is correctly calculated.
/// </summary>
ZTEST_CASE ( GetCapacity_IsCorrectlyCalculated_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CAPACITY = 3;
    Dictionary<string_z, int> DICTIONARY(EXPECTED_CAPACITY);

    // [Execution]
    puint_z uCapacity = DICTIONARY.GetCapacity();

    // [Verification]
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

// End - Test Suite: Dictionary
ZTEST_SUITE_END()
