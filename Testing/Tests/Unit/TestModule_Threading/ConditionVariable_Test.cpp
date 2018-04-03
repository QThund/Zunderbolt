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

#include "ZThreading/ConditionVariable.h"

#include "ZThreading/Thread.h"
#include "ZThreading/SThisThread.h"
#include "ZThreading/Mutex.h"
#include "ZThreading/ScopedExclusiveLock.h"


class ConditionVariableTestClass
{
public:

    static void Reset()
    {
        sm_uThreadCounterAfterWait = 0;
        sm_uThreadCounterBeforeWait = 0;
        sm_bLockIsLockedAfterWait = false;
    }

    static void WaitingFunction()
    {
        ScopedExclusiveLock<Mutex> lock(sm_mutex);

        ++sm_uThreadCounterBeforeWait;

        sm_conditionVariable.Wait(lock);

        sm_bLockIsLockedAfterWait = lock.IsOwner();

        ++sm_uThreadCounterAfterWait;
    }

    static bool sm_bLockIsLockedAfterWait;
    static unsigned int sm_uThreadCounterBeforeWait;
    static unsigned int sm_uThreadCounterAfterWait;
    static Mutex sm_mutex;
    static ConditionVariable sm_conditionVariable;

};

bool ConditionVariableTestClass::sm_bLockIsLockedAfterWait = false;
unsigned int ConditionVariableTestClass::sm_uThreadCounterBeforeWait = 0;
unsigned int ConditionVariableTestClass::sm_uThreadCounterAfterWait = 0;
Mutex ConditionVariableTestClass::sm_mutex;
ConditionVariable ConditionVariableTestClass::sm_conditionVariable;


ZTEST_SUITE_BEGIN( ConditionVariable_TestSuite )

/// <summary>
/// Checks that the thread blocks, waiting until it gets notified.
/// </summary>
ZTEST_CASE ( Wait_ThreadBlocksUntilNotified_Test )
{
    // [Preparation]
    Delegate<void()> function(&ConditionVariableTestClass::WaitingFunction);
    Thread thread(function);

    // [Execution]
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bThreadPassedFirstHalf = ConditionVariableTestClass::sm_uThreadCounterBeforeWait > 0;
    bool bThreadDidNotPassSecondHalfBeforeNotification = ConditionVariableTestClass::sm_uThreadCounterAfterWait == 0;
    ConditionVariableTestClass::sm_conditionVariable.NotifyOne();
    thread.Join();
    bool bThreadPassedSecondHalfAfterNotification = ConditionVariableTestClass::sm_uThreadCounterAfterWait > 0;

    // [Verification]
    BOOST_CHECK(bThreadPassedFirstHalf);
    BOOST_CHECK(bThreadDidNotPassSecondHalfBeforeNotification);
    BOOST_CHECK(bThreadPassedSecondHalfAfterNotification);
}

/// <summary>
/// Checks that the mutex is unlocked when the thread waits for a notification.
/// </summary>
ZTEST_CASE ( Wait_MutexIsUnlockedWhileWaiting_Test )
{
    // [Preparation]
    ConditionVariableTestClass::Reset();
    Delegate<void()> function(&ConditionVariableTestClass::WaitingFunction);
    Thread thread1(function);
    Thread thread2(function);

    // [Execution]
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = ConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    ConditionVariableTestClass::sm_conditionVariable.NotifyAll();

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
}

/// <summary>
/// Checks that only one thread is notified.
/// </summary>
ZTEST_CASE ( NotifyOne_OnlyOneThreadIsNotified_Test )
{
    // [Preparation]
    ConditionVariableTestClass::Reset();
    Delegate<void()> function(&ConditionVariableTestClass::WaitingFunction);
    Thread thread1(function);
    Thread thread2(function);

    // [Execution]
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = ConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    ConditionVariableTestClass::sm_conditionVariable.NotifyOne();
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bOnlyOneThreadPassedSecondHalfAfterNotification = ConditionVariableTestClass::sm_uThreadCounterAfterWait == 1;

    // [Verification]
    ConditionVariableTestClass::sm_conditionVariable.NotifyOne(); // Notifies the other thread
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
    BOOST_CHECK(bOnlyOneThreadPassedSecondHalfAfterNotification);
}

/// <summary>
/// Checks that the mutex is locked again when the thread gets notified.
/// </summary>
ZTEST_CASE ( NotifyAll_MutexIsLockedAgainWhenNotified_Test )
{
    // [Preparation]
    ConditionVariableTestClass::Reset();
    Delegate<void()> function(&ConditionVariableTestClass::WaitingFunction);
    Thread thread1(function);
    Thread thread2(function);

    // [Execution]
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    ConditionVariableTestClass::sm_conditionVariable.NotifyAll();

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(ConditionVariableTestClass::sm_bLockIsLockedAfterWait);
}

/// <summary>
/// Checks that all the threads are notified.
/// </summary>
ZTEST_CASE ( NotifyAll_AllThreadsAreNotified_Test )
{
    // [Preparation]
    ConditionVariableTestClass::Reset();
    Delegate<void()> function(&ConditionVariableTestClass::WaitingFunction);
    Thread thread1(function);
    Thread thread2(function);

    // [Execution]
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bSecondThreadEnteredCriticalSectionWhileWaiting = ConditionVariableTestClass::sm_uThreadCounterBeforeWait == 2;
    ConditionVariableTestClass::sm_conditionVariable.NotifyAll();
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 200, 0, 0));
    bool bTwoThreadsPassedSecondHalfAfterNotification = ConditionVariableTestClass::sm_uThreadCounterAfterWait == 2;

    // [Verification]
    thread1.Join();
    thread2.Join();
    BOOST_CHECK(bSecondThreadEnteredCriticalSectionWhileWaiting);
    BOOST_CHECK(bTwoThreadsPassedSecondHalfAfterNotification);
}


// End - Test Suite: ConditionVariable
ZTEST_SUITE_END()
