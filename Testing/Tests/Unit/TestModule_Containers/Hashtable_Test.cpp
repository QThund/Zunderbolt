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

#include "ZContainers/Hashtable.h"
#include "ZContainers/SStringHashProvider.h"
#include "CallCounter.h"

using z::Test::CallCounter;


ZTEST_SUITE_BEGIN( Hashtable_TestSuite )

/// <summary>
/// Checks that the capacity of the container is correctly set when using common values.
/// </summary>
ZTEST_CASE ( Constructor1_CapacityOfContainerIsCorrect_Test )
{
    // [Preparation]
    const puint_z NUMBER_OF_BUCKETS = 10;
    const puint_z NUMBER_OF_SLOTS = 5;
    const puint_z EXPECTED_CAPACITY = 50;

    // [Execution]
    Hashtable<int, int> hashtable(NUMBER_OF_BUCKETS, NUMBER_OF_SLOTS);

    // [Verification]
    puint_z uCapacity = hashtable.GetCapacity();
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of buckets equals zero.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenNumberOfBucketsEqualsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_ZERO = 0;
    const puint_z NUMBER_OF_SLOTS = 5;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Hashtable<string_z, int> hashtable(INPUT_ZERO, NUMBER_OF_SLOTS);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when slots per buckets equals zero.
/// </summary>
ZTEST_CASE ( Constructor1_AssertionFailsWhenSlotsPerBucketsEqualsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_ZERO = 0;
    const puint_z NUMBER_OF_BUCKETS = 5;
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Hashtable<string_z, int> hashtable(NUMBER_OF_BUCKETS, INPUT_ZERO);
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
/// Checks that every key-value pair is copied.
/// </summary>
ZTEST_CASE ( Constructor2_EveryKeyValuePairIsCopied_Test )
{
    // [Preparation]
    const int EXPECTED_KEYS[] = {0, 2, 1};
    const int EXPECTED_VALUES[] = {0, 2, 1};
    
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(0, 0);
    HASHTABLE.Add(2, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    Hashtable<int, int> hashtableCopy = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(unsigned int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && hashtableCopy[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the copy constructor of every key and value is called.
/// </summary>
ZTEST_CASE ( Constructor2_CopyConstructorOfEveryKeyAndValueIsCalled_Test )
{
    // [Preparation]
    Hashtable<CallCounter, CallCounter> HASHTABLE(10, 2);
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    const puint_z EXPECTED_CALLS = HASHTABLE.GetCount() * 2U + 3U; // +3 due to calls to GenerateHashKey, which receives a copy of an integer
#else
    const puint_z EXPECTED_CALLS = HASHTABLE.GetCount() * 2U + 6U; // +6 due to calls to GenerateHashKey, which receives a copy of an integer
#endif
    CallCounter::ResetCounters();

    // [Execution]
    Hashtable<CallCounter, CallCounter> hashtableCopy = HASHTABLE;

    // [Verification]
    unsigned int uCopyConstructorCalls = CallCounter::GetCopyConstructorCallsCount();
    BOOST_CHECK_EQUAL(uCopyConstructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that an empty hashtable is correctly copied.
/// </summary>
ZTEST_CASE ( Constructor2_ItIsCorrectlyCopiedWhenItIsEmpty_Test )
{
    // [Preparation]
    Hashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    Hashtable<int, int> hashtableCopy = HASHTABLE;

    // [Verification]
    bool bCopyIsEmpty = hashtableCopy.IsEmpty();
    BOOST_CHECK(bCopyIsEmpty);
}

/// <summary>
/// Checks that the destructor of every key and value is called.
/// </summary>
ZTEST_CASE ( Destructor_TheDestructorOfEveryKeyAndValueIsCalled_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_CALLS = 6;

    {
        Hashtable<CallCounter, CallCounter> HASHTABLE(10, 2);
        HASHTABLE.Add(CallCounter(), CallCounter());
        HASHTABLE.Add(CallCounter(), CallCounter());
        HASHTABLE.Add(CallCounter(), CallCounter());
        CallCounter::ResetCounters();

    // [Execution]
    // Destructor is called when the execution flow leaves this block
    }

    // [Verification]
    unsigned int uDestructorCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uDestructorCalls, EXPECTED_CALLS);
}

/// <summary>
/// Checks that the capacity is correctly increased.
/// </summary>
ZTEST_CASE ( Reserve_CapacityIsCorrectlyIncreased_Test )
{
    // [Preparation]
    const puint_z EXPECTED_CAPACITY = 4U;
    Hashtable<int, int> hashtable(1, 1);

    // [Execution]
    hashtable.Reserve(EXPECTED_CAPACITY);

    // [Verification]
    puint_z uStoredCapacity = hashtable.GetCapacity();

    BOOST_CHECK_EQUAL(uStoredCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that elements are correctly reallocated.
/// </summary>
ZTEST_CASE ( Reserve_ElementsAreCorrectlyReallocated_Test )
{
    // [Preparation]
    const bool ELEMENTS_ARE_THE_SAME = true;
    const puint_z INPUT_CAPACITY = 20U;
    Hashtable<int, int> hashtable(1, 3);
    const int NUMBER_OF_ELEMENTS = 3;
    
    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        hashtable.Add(i, i);

    // [Execution]
    hashtable.Reserve(INPUT_CAPACITY); // A reallocation occurs

    // [Verification]
    bool bElementsAreTheSame = true;

    for(int i = 0; i < NUMBER_OF_ELEMENTS; ++i)
        bElementsAreTheSame = bElementsAreTheSame && (hashtable[i] == i);

    BOOST_CHECK_EQUAL(bElementsAreTheSame, ELEMENTS_ARE_THE_SAME);
}

/// <summary>
/// Checks that elements are not reallocated and capacity does not change when attempting to reserve less memory than currently reserved.
/// </summary>
ZTEST_CASE ( Reserve_NothingHappensWhenTheAmountToReserveIsNoGreaterThanCurrentCapacity_Test )
{
    // [Preparation]
    const puint_z INPUT_CAPACITY = 1U;
    const puint_z EXPECTED_CAPACITY = 3U;
    Hashtable<int, int> hashtable(1, EXPECTED_CAPACITY);
    
    for(puint_z i = 0; i < EXPECTED_CAPACITY; ++i)
        hashtable.Add(scast_z(i, int), scast_z(i, int));

    const int* ORIGINAL_FIRST_ELEMENT_ADDRESS = &hashtable[0];

    // [Execution]
    hashtable.Reserve(INPUT_CAPACITY);

    // [Verification]
    puint_z uCapacity = hashtable.GetCapacity();
    int* pFirstElementAddress = &hashtable[0];

    BOOST_CHECK_EQUAL(pFirstElementAddress, ORIGINAL_FIRST_ELEMENT_ADDRESS);
    BOOST_CHECK_EQUAL(uCapacity, EXPECTED_CAPACITY);
}

/// <summary>
/// Checks that the element is correctly added when the hashtable is empty.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    const int INPUT_KEY = 1;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY};
    const int EXPECTED_VALUES[] = {INPUT_VALUE};
    
    Hashtable<int, int> HASHTABLE(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(unsigned int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when the hashtable only contains one element.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashtableOnlyContainsOneElement_Test )
{
    // [Preparation]
    const int INPUT_KEY = 15;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY, 1};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(unsigned int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the element is correctly added when its hash key collides with an existing element's.
/// </summary>
ZTEST_CASE ( Add_ElementIsCorrectlyAddedWhenHashKeyCollidesWithExistingElements_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int INPUT_VALUE = 0;
    const int EXPECTED_KEYS[] = {INPUT_KEY, 1};
    const int EXPECTED_VALUES[] = {INPUT_VALUE, 1};
    
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    bool bResultIsWhatEspected = true;

    for(unsigned int i = 0; i < sizeof(EXPECTED_KEYS) / sizeof(int); ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && HASHTABLE[EXPECTED_KEYS[i]] == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the iterator points to the added element.
/// </summary>
ZTEST_CASE ( Add_ReturnedIteratorPointsToAddedElement_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int INPUT_VALUE = 1;
    
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(4, 2);
    HASHTABLE.Add(6, 3);

    // [Execution]
    Hashtable<int, int>::ConstHashtableIterator itResult = HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

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
    const int INPUT_KEY = 5;
    const int INPUT_VALUE = 1;
    
    Hashtable<int, int> HASHTABLE(10, 1);
    HASHTABLE.Add(6, 2);
    const puint_z COUNT_BEFORE_ADDING = HASHTABLE.GetCount();

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    puint_z uCountAfterAdding = HASHTABLE.GetCount();
    BOOST_CHECK(uCountAfterAdding > COUNT_BEFORE_ADDING);
}

/// <summary>
/// Checks that the capacity is incremented after exceeding its value.
/// </summary>
ZTEST_CASE ( Add_CapacityIsIncrementedWhenNecessary_Test )
{
    // [Preparation]
    const int INPUT_KEY = 6;
    const int INPUT_VALUE = 6;
    
    Hashtable<int, int> HASHTABLE(5, 1);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(2, 2);
    HASHTABLE.Add(3, 3);
    HASHTABLE.Add(4, 4);
    HASHTABLE.Add(5, 5);
    const puint_z CAPACITY_BEFORE_ADDING = HASHTABLE.GetCapacity();

    // [Execution]
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Verification]
    puint_z uCapacityAfterAdding = HASHTABLE.GetCapacity();
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
    const int INPUT_KEY = 1;
    const int INPUT_VALUE = 1;
    
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(INPUT_KEY, INPUT_VALUE);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.Add(INPUT_KEY, 0);
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
/// Checks that the correct value is returned when the key exists in the hashtable.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(3, 3);

    // [Execution]
    int nValue = HASHTABLE[INPUT_KEY];

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that elements can be obtained when they are in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_ElementIsCorrectlyGotWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(21, 3);

    // [Execution]
    int nValue = HASHTABLE[INPUT_KEY];

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the hashtable.
/// </sumary>
ZTEST_CASE( OperatorArraySubscript_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    Hashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE[INPUT_KEY];
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
/// Checks that the correct value is returned when the key exists in the hashtable.
/// </sumary>
ZTEST_CASE( GetValue_CorrectValueIsReturnedWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(3, 3);

    // [Execution]
    int nValue = HASHTABLE.GetValue(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that elements can be obtained when they are in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( GetValue_ElementIsCorrectlyGotWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(21, 3);

    // [Execution]
    int nValue = HASHTABLE.GetValue(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the hashtable.
/// </sumary>
ZTEST_CASE( GetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    Hashtable<int, int> HASHTABLE(5, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.GetValue(INPUT_KEY);
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
/// Checks that the value is set when the key exists in the HASHTABLE.
/// </sumary>
ZTEST_CASE( SetValue_ValueIsSetWhenKeyExists_Test )
{
    // [Preparation]
    const int INPUT_KEY = 2;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, 10);
    HASHTABLE.Add(3, 3);

    // [Execution]
    HASHTABLE.SetValue(INPUT_KEY, EXPECTED_VALUE);

    // [Verification]
    int nValue = HASHTABLE.GetValue(INPUT_KEY);
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that elements can be set when they are in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( SetValue_ElementIsCorrectlySetWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, 0);
    HASHTABLE.Add(21, 3);

    // [Execution]
    HASHTABLE.SetValue(INPUT_KEY, EXPECTED_VALUE);

    // [Verification]
    int nValue = HASHTABLE[INPUT_KEY];
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <sumary>
/// Checks that an assertion fails when the key does not exist in the HASHTABLE.
/// </sumary>
ZTEST_CASE( SetValue_AssertionFailsWhenKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const int INPUT_KEY = 2;
    Hashtable<int, int> HASHTABLE(10, 2);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.SetValue(INPUT_KEY, 0);
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
/// Checks that it returns True when the hashtable contains the key.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsTrueWhenHashtableContainsTheKey_Test )
{
    // [Preparation]
    const string_z INPUT_KEY("key3");
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 4);
    HASHTABLE.Add(INPUT_KEY, 5);
    HASHTABLE.Add("key4", 6);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the hashtable does not contain the key.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsFalseWhenHashtableDoesNotContainTheKey_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 4);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);
    const string_z INPUT_KEY("key5");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the hashtable is empty.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsFalseWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(3, 2);
    const string_z INPUT_KEY("key1");
    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the element is in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( ContainsKey_ReturnsTrueWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const bool EXPECTED_VALUE = true;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, 0);
    HASHTABLE.Add(21, 3);

    // [Execution]
    bool bResult = HASHTABLE.ContainsKey(INPUT_KEY);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the hashtable is empty when removing the only element in it.
/// </summary>
ZTEST_CASE ( Remove_HashtableIsEmptyWhenRemovingTheOnlyElementInTheHashtable_Test )
{
    // [Preparation]
    const string_z EXISTING_KEY("key1");
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(3, 2);
    HASHTABLE.Add(EXISTING_KEY, 0);

    // [Execution]
    HASHTABLE.Remove(EXISTING_KEY);

    // [Verification]
    bool bHashtableIsEmpty = HASHTABLE.IsEmpty();
    BOOST_CHECK(bHashtableIsEmpty);
}

/// <summary>
/// Checks that the key-value pair is removed when there are many pairs in the hashtable and the key exists.
/// </summary>
ZTEST_CASE ( Remove_PairIsCorrectlyRemovedWhenThereAreManyAndKeyExists_Test )
{
    // [Preparation]
    const string_z EXISTING_KEY("key2");
    const string_z EXPECTED_KEYS[] = {"key1", "key3", "key4"};
    const int EXPECTED_VALUES[] = {1, 3, 4};
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(EXISTING_KEY, 2);
    HASHTABLE.Add("key3", 3);
    HASHTABLE.Add("key4", 4);

    // [Execution]
    HASHTABLE.Remove(EXISTING_KEY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator it = Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator(&HASHTABLE, 0);

    int i = 0;

    for(it.MoveFirst(); !it.IsEnd(); ++it, ++i)
    {
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetKey() == EXPECTED_KEYS[i];
        bResultIsWhatEspected = bResultIsWhatEspected && it->GetValue() == EXPECTED_VALUES[i];
    }

    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that elements can be removed when they are in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( Remove_ElementIsCorrectlyRemovedWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int EXPECTED_KEYS[] = {21, 1};
    const int EXPECTED_VALUES[] = {3, 1};
    const int INPUT_KEY = 11;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, 2);
    HASHTABLE.Add(21, 3);

    // [Execution]
    HASHTABLE.Remove(INPUT_KEY);

    // [Verification]
    bool bResultIsWhatEspected = true;

    Hashtable<int, int>::ConstHashtableIterator it = Hashtable<int, int>::ConstHashtableIterator(&HASHTABLE, 0);

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
/// Checks that an assertion fails when the input key does not exist in the hashtable.
/// </summary>
ZTEST_CASE ( Remove_AssertionFailsWhenTheInputKeyDoesNotExist_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z NON_EXISTING_KEY("key2");
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(2, 2);
    HASHTABLE.Add("key1", 1);

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        HASHTABLE.Remove(NON_EXISTING_KEY);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/*

[TODO]: Add a test for the following case: (it failed when removing the first slot in a bucket, when it wasn't fixed)

Hashtable<QHashedString, int, SStringHashProvider> hash(5, 2);
    hash.Add("GBufferPositions", 1);
    hash.Add("GBufferNormals", 2);
    hash.Add("GBufferTangentNormals", 3);
    hash.Add("GBufferAlbedo", 4);
    hash.Add("GBufferSpecular", 5);
    hash.Add("GBufferTangent", 6);
    hash.Add("GBufferBitangent", 6);
    hash.Add("GBufferEmissive", 6);
    hash.Add("GBufferEmissive2", 6);

    hash.Remove("GBufferPositions");
    hash.Remove("GBufferNormals");
    hash.Remove("GBufferTangentNormals");
    hash.Remove("GBufferAlbedo");
    hash.Remove("GBufferSpecular");
    hash.Remove("GBufferTangent");
    hash.Remove("GBufferBitangent");
    hash.Remove("GBufferEmissive");

    hash.Add("GBufferPositions", 1);
    hash.Add("GBufferNormals", 2);
    hash.Add("GBufferTangentNormals", 3);
    hash.Add("GBufferAlbedo", 4);
    hash.Add("GBufferSpecular", 5);
    hash.Add("GBufferTangent", 6);
    hash.Add("GBufferBitangent", 6);
    hash.Add("GBufferEmissive", 6);

    hash.GetValue("GBufferPositions");
    hash.GetValue("GBufferNormals");
    hash.GetValue("GBufferTangentNormals");
    hash.GetValue("GBufferAlbedo");
    hash.GetValue("GBufferSpecular");
    hash.GetValue("GBufferTangent");
    hash.GetValue("GBufferBitangent");
    hash.GetValue("GBufferEmissive");

    hash.Remove("GBufferPositions");
    hash.Remove("GBufferNormals");
    hash.Remove("GBufferTangentNormals");
    hash.Remove("GBufferAlbedo");
    hash.Remove("GBufferSpecular");
    hash.Remove("GBufferTangent");
    hash.Remove("GBufferBitangent");
    hash.Remove("GBufferEmissive");

    hash.Add("GBufferPositions", 1);
    hash.Add("GBufferNormals", 2);
    hash.Add("GBufferTangentNormals", 3);
    hash.Add("GBufferAlbedo", 4);
    hash.Add("GBufferSpecular", 5);
    hash.Add("GBufferTangent", 6);
    hash.Add("GBufferBitangent", 6);
    hash.Add("GBufferEmissive", 6);

    hash.GetValue("GBufferPositions");
    hash.GetValue("GBufferNormals");
    hash.GetValue("GBufferTangentNormals");
    hash.GetValue("GBufferAlbedo");
    hash.GetValue("GBufferSpecular");
    hash.GetValue("GBufferTangent");
    hash.GetValue("GBufferBitangent");
    hash.GetValue("GBufferEmissive");

    hash.Remove("GBufferPositions");
    hash.Remove("GBufferNormals");
    hash.Remove("GBufferTangentNormals");
    hash.Remove("GBufferAlbedo");
    hash.Remove("GBufferSpecular");
    hash.Remove("GBufferTangent");
    hash.Remove("GBufferBitangent");
    hash.Remove("GBufferEmissive");

    hash.Add("GBufferPositions", 1);
    hash.Add("GBufferNormals", 2);
    hash.Add("GBufferTangentNormals", 3);
    hash.Add("GBufferAlbedo", 4);
    hash.Add("GBufferSpecular", 5);
    hash.Add("GBufferTangent", 6);
    hash.Add("GBufferBitangent", 6);
    hash.Add("GBufferEmissive", 6);

    hash.GetValue("GBufferPositions");
    hash.GetValue("GBufferNormals");
    hash.GetValue("GBufferTangentNormals");
    hash.GetValue("GBufferAlbedo");
    hash.GetValue("GBufferSpecular");
    hash.GetValue("GBufferTangent");
    hash.GetValue("GBufferBitangent");
    hash.GetValue("GBufferEmissive");

    */

/// <sumary>
/// Checks that the iterator is obtained.
/// </sumary>
ZTEST_CASE( GetFirst_IteratorIsObtained_Test )
{
    // [Preparation]
    const string_z EXPECTED_ELEMENT_KEY("key1");
    const int EXPECTED_ELEMENT_VALUE = 1;
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itFirst = HASHTABLE.GetFirst();

    // [Verification]
    BOOST_CHECK(itFirst->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itFirst->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the hashtable is empty.
/// </sumary>
ZTEST_CASE( GetFirst_ReturnedIteratorPointsToEndWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itFirst = HASHTABLE.GetFirst();

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
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add(EXPECTED_ELEMENT_KEY, EXPECTED_ELEMENT_VALUE);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itLast = HASHTABLE.GetLast();

    // [Verification]
    BOOST_CHECK(itLast->GetKey() == EXPECTED_ELEMENT_KEY);
    BOOST_CHECK(itLast->GetValue() == EXPECTED_ELEMENT_VALUE);
}

/// <sumary>
/// Checks that the obtained iterator points to end position when the hashtable is empty.
/// </sumary>
ZTEST_CASE( GetLast_ReturnedIteratorPointsToEndWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itLast = HASHTABLE.GetLast();

    // [Verification]
    bool bIteratorPointstoEnd = itLast.IsEnd();
    BOOST_CHECK(bIteratorPointstoEnd);
}

/// <summary>
/// Checks that it returns the expected position when the hashtable contains the key.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsExpectedPositionWhenHashtableContainsTheKey_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key2");
    const int EXPECTED_VALUE = 4;
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add(EXPECTED_KEY, EXPECTED_VALUE);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itPosition = HASHTABLE.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    BOOST_CHECK(itPosition->GetKey() == EXPECTED_KEY);
    BOOST_CHECK(itPosition->GetValue() == EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the hashtable does not contain the element.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsEndPositionWhenHashtableDoesNotContainTheElement_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key5");
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 4);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itPosition = HASHTABLE.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that it returns an iterator that points to the end position when the hashtable is empty.
/// </summary>
ZTEST_CASE ( PositionOfKey_ReturnsEndPositionWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    const string_z EXPECTED_KEY("key1");
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);

    // [Execution]
    Hashtable<string_z, int, SStringHashProvider>::ConstHashtableIterator itPosition = HASHTABLE.PositionOfKey(EXPECTED_KEY);

    // [Verification]
    bool bIteratorIsEnd = itPosition.IsEnd();
    BOOST_CHECK(bIteratorIsEnd);
}

/// <summary>
/// Checks that elements can be obtained when they are in a bucket that contains several slots.
/// </summary>
ZTEST_CASE ( PositionOfKey_ElementIsCorrectlyGotWhenThereIsMoreThanOneElementInBucket_Test )
{
    // [Preparation]
    const int INPUT_KEY = 11;
    const int EXPECTED_VALUE = 2;
    Hashtable<int, int> HASHTABLE(10, 2);
    HASHTABLE.Add(1, 1);
    HASHTABLE.Add(INPUT_KEY, EXPECTED_VALUE);
    HASHTABLE.Add(21, 3);

    // [Execution]
    Hashtable<int, int>::ConstHashtableIterator result = HASHTABLE.PositionOfKey(INPUT_KEY);

    // [Verification]
    int nValue = result->GetValue();
    BOOST_CHECK_EQUAL(nValue, EXPECTED_VALUE);
}

/// <sumary>
/// Checks that it returns True when hashtables are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenHashtablesAreExactlyEqual_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2 = HASHTABLE1;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE1 == HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when hashtables are the same instance.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenHashtablesAreTheSameInstance_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);
    HASHTABLE.Add("key4", 4);
    HASHTABLE.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE == HASHTABLE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the order in which pairs were added to the hashtable does not affect the result.
/// </sumary>
ZTEST_CASE( OperatorEquality_AdditionOrderDoesNotMatter_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);
    HASHTABLE2.Add("key3", 3);
    HASHTABLE2.Add("key2", 2);
    HASHTABLE2.Add("key4", 4);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE1 == HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when hashtables are empty.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsTrueWhenHashtablesAreEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE1 == HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when both hashtables have a different number of pairs which are equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenHashtablesHaveDifferentNumberOfElementsWithSameValues_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(4, 2);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key2", 2);
    HASHTABLE2.Add("key3", 3);
    HASHTABLE2.Add("key4", 4);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE1 == HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when both hashtables have the same number of pairs which are not equal.
/// </sumary>
ZTEST_CASE( OperatorEquality_ReturnsFalseWhenHashtablesHaveSameNumberOfElementsWithDifferentValues_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2x", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 50);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key2", 90);
    HASHTABLE2.Add("key3x", 3);
    HASHTABLE2.Add("key4", 4);
    HASHTABLE2.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE1 == HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when hashtables are exactly equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenHashtablesAreExactlyEqual_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2 = HASHTABLE1;

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE1 != HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when hashtables are the same instance.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenHashtablesAreTheSameInstance_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 2);
    HASHTABLE.Add("key3", 3);
    HASHTABLE.Add("key4", 4);
    HASHTABLE.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE != HASHTABLE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that the order in which pairs were added to the hashtable does not affect the result.
/// </sumary>
ZTEST_CASE( OperatorInequality_AdditionOrderDoesNotMatter_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);
    HASHTABLE2.Add("key3", 3);
    HASHTABLE2.Add("key2", 2);
    HASHTABLE2.Add("key4", 4);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key5", 5);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE1 != HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns False when hashtables are empty.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsFalseWhenHashtablesAreEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = HASHTABLE1 != HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when both hashtables have a different number of pairs which are equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenHashtablesHaveDifferentNumberOfElementsWithSameValues_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(4, 2);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key2", 2);
    HASHTABLE2.Add("key3", 3);
    HASHTABLE2.Add("key4", 4);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE1 != HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <sumary>
/// Checks that it returns True when both hashtables have the same number of pairs which are not equal.
/// </sumary>
ZTEST_CASE( OperatorInequality_ReturnsTrueWhenHashtablesHaveSameNumberOfElementsWithDifferentValues_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE1(5, 2);
    HASHTABLE1.Add("key1", 1);
    HASHTABLE1.Add("key2x", 2);
    HASHTABLE1.Add("key3", 3);
    HASHTABLE1.Add("key4", 4);
    HASHTABLE1.Add("key5", 50);

    Hashtable<string_z, int, SStringHashProvider> HASHTABLE2(5, 2);
    HASHTABLE2.Add("key1", 1);
    HASHTABLE2.Add("key2", 90);
    HASHTABLE2.Add("key3x", 3);
    HASHTABLE2.Add("key4", 4);
    HASHTABLE2.Add("key5", 5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = HASHTABLE1 != HASHTABLE2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the hashtable is correctly copied when it has elements and the destination hashtable is empty.
/// </summary>
ZTEST_CASE ( OperatorAssignment_HashtableIsCorrectlyCopiedWhenItHasElementsAndDestinationIsEmpty_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 3);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);
    HASHTABLE.Add("key5", 8);

    const puint_z EXPECTED_COUNT = HASHTABLE.GetCount();
    Hashtable<string_z, int, SStringHashProvider> copiedHashtable(8, 2);

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = HASHTABLE == copiedHashtable;

    puint_z uCount = copiedHashtable.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the hashtable is correctly copied when there are more elements in the source hashtable than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_HashtableIsCorrectlyCopiedWhenThereAreMoreElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 3);
    HASHTABLE.Add("key3", 5);
    HASHTABLE.Add("key4", 6);
    HASHTABLE.Add("key5", 8);
    const puint_z EXPECTED_COUNT = HASHTABLE.GetCount();

    Hashtable<string_z, int, SStringHashProvider> copiedHashtable(3, 2);
    copiedHashtable.Add("key5", 10);
    copiedHashtable.Add("key6", 11);
    copiedHashtable.Add("key7", 12);

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = HASHTABLE == copiedHashtable;

    puint_z uCount = copiedHashtable.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the hashtable is correctly copied when there are less elements in the source hashtable than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_HashtableIsCorrectlyCopiedWhenThereAreLessElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 3);
    const puint_z EXPECTED_COUNT = HASHTABLE.GetCount();

    Hashtable<string_z, int, SStringHashProvider> copiedHashtable(3, 2);
    copiedHashtable.Add("key5", 10);
    copiedHashtable.Add("key6", 11);
    copiedHashtable.Add("key7", 12);

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = HASHTABLE == copiedHashtable;

    puint_z uCount = copiedHashtable.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the hashtable is correctly copied when there are the same number of elements in the source hashtable than in the destination.
/// </summary>
ZTEST_CASE ( OperatorAssignment_HashtableIsCorrectlyCopiedWhenThereAreSameNumberOfElementsInSourceThanInDestination_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(5, 2);
    HASHTABLE.Add("key1", 1);
    HASHTABLE.Add("key2", 3);
    HASHTABLE.Add("key3", 5);
    const puint_z EXPECTED_COUNT = HASHTABLE.GetCount();

    Hashtable<string_z, int, SStringHashProvider> copiedHashtable(3, 2);
    copiedHashtable.Add("key5", 10);
    copiedHashtable.Add("key6", 11);
    copiedHashtable.Add("key7", 12);

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    bool bResultIsWhatEspected = HASHTABLE == copiedHashtable;

    puint_z uCount = copiedHashtable.GetCount();
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
    BOOST_CHECK(bResultIsWhatEspected);
}

/// <summary>
/// Checks that the hashtable is correctly copied when it is empty and the destination hashtable has elements.
/// </summary>
ZTEST_CASE ( OperatorAssignment_HashtableIsCorrectlyCopiedWhenItIsEmptyAndDestinationHasElements_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> HASHTABLE(3, 2);
    Hashtable<string_z, int, SStringHashProvider> copiedHashtable(3, 2);
    copiedHashtable.Add("key5", 10);
    copiedHashtable.Add("key6", 11);
    copiedHashtable.Add("key7", 12);

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    bool bHashtableIsEmpty = copiedHashtable.IsEmpty();
    BOOST_CHECK(bHashtableIsEmpty);
}

/// <summary>
/// Checks that the copy constructors are called for each key and value.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CopyConstructorsAreCalledForAllKeysAndValues_Test )
{
    // [Preparation]
    Hashtable<CallCounter, CallCounter> HASHTABLE(5, 2);
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());
    HASHTABLE.Add(CallCounter(), CallCounter());

    Hashtable<CallCounter, CallCounter> copiedHashtable(3, 2);
    copiedHashtable.Add(CallCounter(), CallCounter());
    copiedHashtable.Add(CallCounter(), CallCounter());
    copiedHashtable.Add(CallCounter(), CallCounter());

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    const puint_z EXPECTED_COPY_CONSTRUCTORS_VALUE = HASHTABLE.GetCount() * 2U + HASHTABLE.GetCount(); // +GetCount because CallCounter instances are copied when they are passed to GenerateHashKey
#else
    const puint_z EXPECTED_COPY_CONSTRUCTORS_VALUE = HASHTABLE.GetCount() * 2U + HASHTABLE.GetCount() * 2U; // +GetCount*2 because CallCounter instances are copied when they are passed to GenerateHashKey
#endif
    CallCounter::ResetCounters();

    // [Execution]
    copiedHashtable = HASHTABLE;

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
    Hashtable<CallCounter, CallCounter> HASHTABLE(5, 2);
    Hashtable<CallCounter, CallCounter> copiedHashtable(3, 2);
    copiedHashtable.Add(CallCounter(), CallCounter());
    copiedHashtable.Add(CallCounter(), CallCounter());
    copiedHashtable.Add(CallCounter(), CallCounter());

    const puint_z EXPECTED_DESTRUCTORS_VALUE = copiedHashtable.GetCount() * 2U;
    CallCounter::ResetCounters();

    // [Execution]
    copiedHashtable = HASHTABLE;

    // [Verification]
    unsigned int uNumberOfCalls = CallCounter::GetDestructorCallsCount();
    BOOST_CHECK_EQUAL(uNumberOfCalls, EXPECTED_DESTRUCTORS_VALUE);
}

/// <summary>
/// Checks if it the clone method works properly.
/// </summary>
ZTEST_CASE ( Clone_ClonedHashtableHasSameValuesThanTheOriginalHashtable_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> sourceHashtable(5, 2);
    sourceHashtable.Add("key1", 1);
    sourceHashtable.Add("key2", 3);
    sourceHashtable.Add("key3", 5);

    Hashtable<string_z, int, SStringHashProvider> destinationHashtable(3, 2);

    // [Execution]
    sourceHashtable.Clone(destinationHashtable);

    // [Verification]
    BOOST_CHECK(sourceHashtable == destinationHashtable);
}

/// <summary>
/// Checks if it the clone method works properly when the destination hashtable has more capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedHashtableHasSameValuesThanTheOriginalHashtableWhenInputHashtableHasMoreCapacityAndElements_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> sourceHashtable(3, 2);
    sourceHashtable.Add("key1", 1);
    sourceHashtable.Add("key2", 2);
    sourceHashtable.Add("key3", 3);

    Hashtable<string_z, int, SStringHashProvider> destinationHashtable(5, 2);
    destinationHashtable.Add("key4", 4);
    destinationHashtable.Add("key5", 5);
    destinationHashtable.Add("key6", 6);
    destinationHashtable.Add("key7", 7);
    destinationHashtable.Add("key8", 8);

    // [Execution]
    sourceHashtable.Clone(destinationHashtable);

    // [Verification]
    BOOST_CHECK(sourceHashtable == destinationHashtable);
}

/// <summary>
/// Checks if it the clone method works properly when the destination hashtable has less capacity and elements.
/// </summary>
ZTEST_CASE ( Clone_ClonedHashtableHasSameValuesThanTheOriginalHashtableWhenInputHashtableHasLessCapacityAndElements_Test )
{
    // [Preparation]
    Hashtable<string_z, int, SStringHashProvider> sourceHashtable(5, 2);
    sourceHashtable.Add("key1", 1);
    sourceHashtable.Add("key2", 2);
    sourceHashtable.Add("key3", 3);
    sourceHashtable.Add("key4", 4);
    sourceHashtable.Add("key5", 5);

    Hashtable<string_z, int, SStringHashProvider> destinationHashtable(3, 2);
    destinationHashtable.Add("key6", 6);
    destinationHashtable.Add("key7", 7);
    destinationHashtable.Add("key8", 8);

    // [Execution]
    sourceHashtable.Clone(destinationHashtable);

    // [Verification]
    BOOST_CHECK(sourceHashtable == destinationHashtable);
}

/// <summary>
/// Checks if the result contains all existing keys.
/// </summary>
ZTEST_CASE ( GetKeys_ResultContainsAllExistingKeys_Test )
{
    // [Preparation]
    const int EXPECTED_KEYS[] = {10, 11, 12, 13, 14};
    Hashtable<int, int> HASHTABLE(5, 2);
    HASHTABLE.Add(10, 1);
    HASHTABLE.Add(11, 2);
    HASHTABLE.Add(12, 3);
    HASHTABLE.Add(13, 4);
    HASHTABLE.Add(14, 5);

    // [Execution]
    ArrayResult<int> arResult = HASHTABLE.GetKeys();

    // [Verification]
    bool bResultArrayContainsExpectedKeys = arResult.GetCount() == HASHTABLE.GetCount();

    for(puint_z uKey = 0; uKey < arResult.GetCount(); ++uKey)
    {
        bResultArrayContainsExpectedKeys = bResultArrayContainsExpectedKeys && arResult[uKey] == EXPECTED_KEYS[uKey];
    }

    BOOST_CHECK(bResultArrayContainsExpectedKeys);
}

/// <summary>
/// Checks if the result array is attached to its content.
/// </summary>
ZTEST_CASE ( GetKeys_ResultIsAttached_Test )
{
    // [Preparation]
    Hashtable<int, int> HASHTABLE(5, 2);
    HASHTABLE.Add(0, 1);

    // [Execution]
    ArrayResult<int> arResult = HASHTABLE.GetKeys();

    // [Verification]
    BOOST_CHECK(arResult.IsAttached());
}

/// <summary>
/// Checks if the result is null when the hashtable is empty.
/// </summary>
ZTEST_CASE ( GetKeys_ReturnsNullWhenHashtableIsEmpty_Test )
{
    // [Preparation]
    int* EXPECTED_RESULT = null_z;
    puint_z EXPECTED_COUNT = 0;
    Hashtable<int, int> HASHTABLE(5, 2);

    // [Execution]
    ArrayResult<int> arResult = HASHTABLE.GetKeys();

    // [Verification]
    int* pResult = arResult.Get();
    puint_z uCount = arResult.GetCount();
    BOOST_CHECK_EQUAL(pResult, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

// End - Test Suite: Hashtable
ZTEST_SUITE_END()
