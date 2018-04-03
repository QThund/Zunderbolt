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

// Note: Testing a mutex is so hard. Since Boost is used as underlying implementation and it has been already tested both by the dev team and many users, our testing effort is reduced

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZThreading/ScopedExclusiveLock.h"


ZTEST_SUITE_BEGIN( ScopedExclusiveLock_TestSuite )
    
/// <summary>
/// Checks that it owns the mutex when it was not locked and input is True.
/// </summary>
ZTEST_CASE ( Constructor_OwnsTheMutexWhenItWasNotLockedAndInputIsTrue_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    const bool INPUT_VALUE = true;
    Mutex mutex;

    // [Execution]
    ScopedExclusiveLock<Mutex> lock(mutex, INPUT_VALUE);
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it does not own the mutex when it was not locked and input is False.
/// </summary>
ZTEST_CASE ( Constructor_DoesNotOwnTheMutexWhenItWasNotLockedAndInputIsFalse_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    const bool INPUT_VALUE = false;
    Mutex mutex;

    // [Execution]
    ScopedExclusiveLock<Mutex> lock(mutex, INPUT_VALUE);
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the mutex is unlocked.
/// </summary>
ZTEST_CASE ( Destructor_MutexIsUnlocked_Test )
{
    // [Preparation]
    const bool MUTEX_IS_UNLOCKED = true;
    Mutex mutex;
    {
        ScopedExclusiveLock<Mutex> lock(mutex, true);

    // [Execution]
    } // Calls destructor
    
    // [Verification]
    bool bCanBeLocked = mutex.TryLock();
    mutex.Unlock();
    BOOST_CHECK_EQUAL(bCanBeLocked, MUTEX_IS_UNLOCKED);
}

/// <summary>
/// Checks that nothing happens when the mutex was not locked.
/// </summary>
ZTEST_CASE ( Destructor_ItDoesNothingWhenMutexIsNotLocked_Test )
{
    // [Preparation]
    const bool NOTHING_HAPPENS = true;
    Mutex mutex;
    {
        ScopedExclusiveLock<Mutex> lock(mutex, false);

    // [Execution]
    } // Calls destructor
    
    // [Verification]
    BOOST_CHECK(NOTHING_HAPPENS);
}

/// <summary>
/// Checks that it owns the mutex when it was not locked.
/// </summary>
ZTEST_CASE ( Lock_OwnsTheMutexWhenItWasNotLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    Mutex mutex;
    ScopedExclusiveLock<Mutex> lock(mutex, false);

    // [Execution]
    lock.Lock();
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it stops owning the mutex when it was locked.
/// </summary>
ZTEST_CASE ( Unlock_StopsOwningMutexWhenItWasLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    Mutex mutex;
    ScopedExclusiveLock<Mutex> lock(mutex, true);

    // [Execution]
    lock.Unlock();
    
    // [Verification]
    bool bOwnsMutex = lock.IsOwner();
    BOOST_CHECK_EQUAL(bOwnsMutex, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the mutex can be locked.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsTrueWhenMutexCanBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    Mutex mutex;
    ScopedExclusiveLock<Mutex> lock(mutex, false);

    // [Execution]
    bool bResult = lock.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the mutex cannot be locked.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsFalseWhenMutexCannotBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    Mutex mutex;
    ScopedExclusiveLock<Mutex> lock(mutex, true);

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

// End - Test Suite: ScopedExclusiveLock
ZTEST_SUITE_END()
