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

#include "ZThreading/RecursiveMutex.h"

#include "ZThreading/Thread.h"
#include "ZThreading/SThisThread.h"

class RecursiveMutexTestClass
{
public:

    static void Reset()
    {
        sm_uThreadCounter = 0;
        sm_uSharedResource = 0;
        sm_bOneThreadAtATime = true;
        sm_bNoErrorsOccurred = false;
    }

    static void Function(unsigned int uCheckValue)
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

    static void RecursiveFunction(unsigned int uRecursionDepth)
    {
        if(uRecursionDepth > 0)
        {
            sm_bNoErrorsOccurred = false;
            sm_mutex.Lock();
            RecursiveMutexTestClass::RecursiveFunction(uRecursionDepth - 1U);
            sm_mutex.Unlock();
            sm_bNoErrorsOccurred = true;
        }
    }

    static unsigned int sm_uSharedResource;
    static bool sm_bOneThreadAtATime;
    static bool sm_bNoErrorsOccurred;
    static RecursiveMutex sm_mutex;
    static unsigned int sm_uThreadCounter;
};

RecursiveMutex RecursiveMutexTestClass::sm_mutex;
unsigned int RecursiveMutexTestClass::sm_uSharedResource;
unsigned int RecursiveMutexTestClass::sm_uThreadCounter = 0;
bool RecursiveMutexTestClass::sm_bOneThreadAtATime = true;
bool RecursiveMutexTestClass::sm_bNoErrorsOccurred = false;


ZTEST_SUITE_BEGIN( RecursiveMutex_TestSuite )

/// <summary>
/// Checks that only one thread can own the mutex at a time.
/// </summary>
ZTEST_CASE ( Lock_OnlyOneThreadOwnsTheMutexAtATime_Test )
{
    // [Preparation]
    static const unsigned int NUMBER_OF_THREADS = 50U;
    RecursiveMutexTestClass::Reset();
    RecursiveMutexTestClass::sm_uThreadCounter = NUMBER_OF_THREADS;

    // [Execution]
    for(unsigned int uValue = 0; uValue < NUMBER_OF_THREADS; ++uValue)
    {
        Thread thread(Delegate<void(unsigned int)>(RecursiveMutexTestClass::Function), uValue);
        thread.Detach();
    }
    
    // [Verification]
    while(RecursiveMutexTestClass::sm_uThreadCounter > 0)
        SThisThread::Yield();

    BOOST_CHECK(RecursiveMutexTestClass::sm_bOneThreadAtATime);
}

/// <summary>
/// Checks that it can be called many times in recursive function calls.
/// </summary>
ZTEST_CASE ( Lock_ItCanBeCalledManyTimesInRecursiveFunctions_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;
    RecursiveMutexTestClass::Reset();

    // [Execution]
    Thread thread(Delegate<void(unsigned int)>(RecursiveMutexTestClass::RecursiveFunction), 5);
    
    // [Verification]
    thread.Join();
    BOOST_CHECK_EQUAL(RecursiveMutexTestClass::sm_bNoErrorsOccurred, NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that it returns True when the mutex can be locked.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsTrueWhenMutexCanBeLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    RecursiveMutex mutex;

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
}

/// <summary>
/// Checks that it returns True when the mutex has been locked already.
/// </summary>
ZTEST_CASE ( TryLock_ReturnsTrueWhenMutexHasBeenAlreadyLocked_Test )
{
    // [Preparation]
    const bool EXPECTED_VALUE = true;
    RecursiveMutex mutex;
    mutex.Lock();

    // [Execution]
    bool bResult = mutex.TryLock();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);

    // [Cleaning]
    mutex.Unlock();
    mutex.Unlock();
}

// End - Test Suite: RecursiveMutex
ZTEST_SUITE_END()
