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

#include "ZThreading/SharedMutex.h"

#include "ZThreading/Thread.h"
#include "ZThreading/SThisThread.h"


class SharedMutexTestClass
{
public:

    static void Reset()
    {
        sm_uThreadCounter = 0;
        sm_uSharedResource = 0;
        sm_bOneThreadAtATime = true;
    }

    static void FunctionExclusiveLock(unsigned int uCheckValue)
    {
        TimeSpan Pause50ms(0, 0, 0, 0, 50, 0, 0);

        SThisThread::Sleep(Pause50ms);

        sm_mutex.Lock();

        sm_uSharedResource += uCheckValue;

        SThisThread::Sleep(Pause50ms);

        sm_uSharedResource -= uCheckValue;

        sm_bOneThreadAtATime = sm_bOneThreadAtATime && sm_uSharedResource == 0;

        sm_mutex.Unlock();

        SThisThread::Sleep(Pause50ms);

        --sm_uThreadCounter;
    }
    
    static void FunctionSharedLock(unsigned int uCheckValue)
    {
        TimeSpan Pause50ms(0, 0, 0, 0, 50, 0, 0);

        SThisThread::Sleep(Pause50ms);

        sm_mutex.LockShared();

        sm_uSharedResource += uCheckValue;

        SThisThread::Sleep(Pause50ms);

        sm_uSharedResource -= uCheckValue;

        sm_bOneThreadAtATime = sm_bOneThreadAtATime && sm_uSharedResource == 0;

        sm_mutex.UnlockShared();

        SThisThread::Sleep(Pause50ms);

        --sm_uThreadCounter;
    }

    static unsigned int sm_uSharedResource;
    static bool sm_bOneThreadAtATime;
    static SharedMutex sm_mutex;
    static unsigned int sm_uThreadCounter;
};

SharedMutex SharedMutexTestClass::sm_mutex;
unsigned int SharedMutexTestClass::sm_uThreadCounter = 0;
unsigned int SharedMutexTestClass::sm_uSharedResource;
bool SharedMutexTestClass::sm_bOneThreadAtATime = true;


ZTEST_SUITE_BEGIN( SharedMutex_TestSuite )
    
/// <summary>
/// Checks that only one thread can own the mutex at a time.
/// </summary>
ZTEST_CASE ( Lock_OnlyOneThreadOwnsTheMutexAtATime_Test )
{
    // [Preparation]
    static const unsigned int NUMBER_OF_THREADS = 50U;
    SharedMutexTestClass::Reset();
    SharedMutexTestClass::sm_uThreadCounter = NUMBER_OF_THREADS;

    // [Execution]
    for(unsigned int uValue = 0; uValue < NUMBER_OF_THREADS; ++uValue)
    {
        Thread thread(Delegate<void(unsigned int)>(SharedMutexTestClass::FunctionExclusiveLock), uValue);
        thread.Detach();
    }
    
    // [Verification]
    while(SharedMutexTestClass::sm_uThreadCounter > 0)
        SThisThread::Yield();

    BOOST_CHECK(SharedMutexTestClass::sm_bOneThreadAtATime);
}

/// <summary>
/// Checks that many threads can own the shared mutex at a time.
/// </summary>
ZTEST_CASE ( LockShared_ManyThreadsOwnTheMutexAtATime_Test )
{
    // [Preparation]
    static const unsigned int NUMBER_OF_THREADS = 50U;
    SharedMutexTestClass::sm_uThreadCounter = NUMBER_OF_THREADS;
    SharedMutexTestClass::sm_bOneThreadAtATime = true;
    const bool EXPECTED_VALUE = false;

    // [Execution]
    for(unsigned int uValue = 0; uValue < NUMBER_OF_THREADS; ++uValue)
    {
        Thread thread(Delegate<void(unsigned int)>(SharedMutexTestClass::FunctionSharedLock), uValue);
        thread.Detach();
    }
    
    // [Verification]
    while(SharedMutexTestClass::sm_uThreadCounter > 0)
        SThisThread::Yield();

    BOOST_CHECK_EQUAL(SharedMutexTestClass::sm_bOneThreadAtATime, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when the mutex was not locked.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsTrueWhenMutexWasNotAlreadyLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    SharedMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in an exclusive way.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsFalseWhenMutexWasLockedExclusive_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    SharedMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in a shared way.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsFalseWhenMutexWasAlreadyLockedShared_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    SharedMutex mutex;
    mutex.LockShared();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns True when the mutex was locked in a shared way.
/// </summary>
ZTEST_CASE ( TryLockShared_ReturnsTrueWhenMutexWasAlreadyLockedShared_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    SharedMutex mutex;
    mutex.LockShared();

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns True when the mutex was was not locked.
/// </summary>
ZTEST_CASE ( TryLockShared_ReturnsTrueWhenMutexWasNotLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    SharedMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.UnlockShared();
}

/// <summary>
/// Checks that it returns False when the mutex was locked in an exclusive way.
/// </summary>
ZTEST_CASE ( TryLockShared_ReturnsFalseWhenMutexWasLockedExclusive_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = false;
    SharedMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLockShared();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

// End - Test Suite: SharedMutex
ZTEST_SUITE_END()
