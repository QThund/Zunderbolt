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

#include "ZThreading/Thread.h"

#include "ZTiming/Stopwatch.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "ZCommon/Exceptions/AssertException.h"
#include "ZThreading/SThisThread.h"
#include "ZTime/TimeSpan.h"

// Class whose methods are to be used in the tests of Thread
class ThreadTestClass
{
public:

    int m_nMember;

    static bool sm_bFunction0Called;
    static bool sm_bFunction1Called;
    static bool sm_bFunction2Called;
    static bool sm_bFunction3Called;
    static bool sm_bFunction4Called;
    static bool sm_bFunction5Called;
    static bool sm_bFunction6Called;
    static bool sm_bFunction7Called;
    static bool sm_bFunction8Called;
    static bool sm_bFunctionInterrupted;

    ThreadTestClass(int param) : m_nMember(param)
    {
    }

    void SetMember(int param)
    {
        m_nMember = param;
    }

    static void ResetFlags()
    {
        sm_bFunction0Called = false;
        sm_bFunction1Called = false;
        sm_bFunction2Called = false;
        sm_bFunction3Called = false;
        sm_bFunction4Called = false;
        sm_bFunction5Called = false;
        sm_bFunction6Called = false;
        sm_bFunction7Called = false;
        sm_bFunction8Called = false;
        sm_bFunctionInterrupted = false;
    }

    static void Wait(unsigned int milliseconds)
    {
        SThisThread::Sleep(TimeSpan(0, 0, 0, 0, milliseconds, 0, 0));
    }

    static void FunctionToBeInterrupted() try
    {
        Delegate<void()> function(&ThreadTestClass::WorkSomeTime);

        Thread thread(function); // The function is assumed to take enough time
        SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 50, 0, 0));
        
        try
        {
            thread.Join();
        }
        catch(const AssertException&)
        {
            sm_bFunctionInterrupted = true;
        }
    }
    catch(...)
    {
        // This block silences the exception thrown in the destructor of the thread instance, don't remove it this time
    }
    
#ifdef Z_COMPILER_GCC
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

    static void WorkSomeTime()
    {
        for(int i = 1; i < 1000000; ++i)
        {
            for(int ii = 1; ii < 500; ++ii)
            {
                int x = ii / i;
            }
        }
    }
    
#ifdef Z_COMPILER_GCC
    #pragma GCC diagnostic pop
#endif

    static void FunctionWith0Params()
    {
        sm_bFunction0Called = true;
    }
    
    static void FunctionWith1Params(int)
    {
        sm_bFunction1Called = true;
    }
    
    static void FunctionWith2Params(int, int)
    {
        sm_bFunction2Called = true;
    }
    
    static void FunctionWith3Params(int, int, int)
    {
        sm_bFunction3Called = true;
    }
    
    static void FunctionWith4Params(int, int, int, int)
    {
        sm_bFunction4Called = true;
    }
    
    static void FunctionWith5Params(int, int, int, int, int)
    {
        sm_bFunction5Called = true;
    }
    
    static void FunctionWith6Params(int, int, int, int, int, int)
    {
        sm_bFunction6Called = true;
    }
    
    static void FunctionWith7Params(int, int, int, int, int, int, int)
    {
        sm_bFunction7Called = true;
    }
    
    static void FunctionWith8Params(int, int, int, int, int, int, int, int)
    {
        sm_bFunction8Called = true;
    }
};

bool ThreadTestClass::sm_bFunction0Called = false;
bool ThreadTestClass::sm_bFunction1Called = false;
bool ThreadTestClass::sm_bFunction2Called = false;
bool ThreadTestClass::sm_bFunction3Called = false;
bool ThreadTestClass::sm_bFunction4Called = false;
bool ThreadTestClass::sm_bFunction5Called = false;
bool ThreadTestClass::sm_bFunction6Called = false;
bool ThreadTestClass::sm_bFunction7Called = false;
bool ThreadTestClass::sm_bFunction8Called = false;
bool ThreadTestClass::sm_bFunctionInterrupted = false;



ZTEST_SUITE_BEGIN( Thread_TestSuite )

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor1_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);

    // [Execution]
    Thread thread(function);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction0Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor2_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int)> function(&ThreadTestClass::FunctionWith1Params);
    int p1 = 0;

    // [Execution]
    Thread thread(function, p1);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction1Called);
}

/// <summary>
/// Checks that the correct method of an object is called.
/// </summary>
ZTEST_CASE ( Constructor2_MethodOfCorrectObjectIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    ThreadTestClass object(0);
    Delegate<void(int)> function(&object, &ThreadTestClass::SetMember);
    const int EXPECTED_VALUE = 1;

    // [Execution]
    Thread thread(function, EXPECTED_VALUE);

    // [Verification]
    thread.Join();

    BOOST_CHECK_EQUAL(object.m_nMember, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor3_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int)> function(&ThreadTestClass::FunctionWith2Params);
    int p1 = 0;
    int p2 = 0;

    // [Execution]
    Thread thread(function, p1, p2);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction2Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor4_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int)> function(&ThreadTestClass::FunctionWith3Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction3Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor5_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int, int)> function(&ThreadTestClass::FunctionWith4Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3, p4);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction4Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor6_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int, int, int)> function(&ThreadTestClass::FunctionWith5Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3, p4, p5);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction5Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor7_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int, int, int, int)> function(&ThreadTestClass::FunctionWith6Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3, p4, p5, p6);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction6Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor8_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int, int, int, int, int)> function(&ThreadTestClass::FunctionWith7Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;
    int p7 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3, p4, p5, p6, p7);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction7Called);
}

/// <summary>
/// Checks that the input function is called.
/// </summary>
ZTEST_CASE ( Constructor9_FunctionIsCalled_Test )
{
    // [Preparation]
    ThreadTestClass::ResetFlags();
    Delegate<void(int, int, int, int, int, int, int, int)> function(&ThreadTestClass::FunctionWith8Params);
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int p4 = 0;
    int p5 = 0;
    int p6 = 0;
    int p7 = 0;
    int p8 = 0;

    // [Execution]
    Thread thread(function, p1, p2, p3, p4, p5, p6, p7, p8);

    // [Verification]
    thread.Join();

    BOOST_CHECK(ThreadTestClass::sm_bFunction8Called);
}

/// <summary>
/// Checks that no exceptions are thrown when the thread already finished.
/// </summary>
ZTEST_CASE ( Destructor_NothingHappensWhenThreadWasNotRunning_Test )
{
    // [Preparation]
    const bool NO_EXCEPTIONS_THROWN = true;
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    {
        Thread thread(function);
        thread.Join();
    // [Execution]
    } // Destructor called

    // [Verification]
    BOOST_CHECK(NO_EXCEPTIONS_THROWN);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the instance is destroyed before the thread has finished.
/// </summary>
ZTEST_CASE ( Destructor_AssertionFailsWhenInstanceIsDestroyedBeforeTheThreadHasFinished_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    bool bAssertionFailed = false;

    try
    {
        Thread thread(function); // The function is assumed to take enough time

    // [Execution]
    } // Destructor called
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

    #ifndef Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT

    /// <summary>
    /// Checks that an assertion fails when the thread is not running.
    /// </summary>
    ZTEST_CASE ( Interrupt_AssertionFailsWhenThreadIsNotRunning_Test )
    {
        // [Preparation]
        Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
        const unsigned int WAIT_TIME = 100;
        bool bAssertionFailed = false;

        try
        {
            Thread thread(function, WAIT_TIME); // The function is assumed to take enough time
            thread.Join();
        // [Execution]
            thread.Interrupt();
        }
        catch(const AssertException&)
        {
            bAssertionFailed = true;
        }

        // [Verification]
        BOOST_CHECK(bAssertionFailed);
    }

    #endif

#endif

/// <summary>
/// Checks that this thread waits until the other thread has finished.
/// </summary>
ZTEST_CASE ( Join_WaitsUntilThreadFinishes_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 600;

    Stopwatch elapsedTime;
    elapsedTime.Set();
    Thread thread(function, WAIT_TIME);

    // [Execution]
// [TODO]: This test is very problematic due to inevitable race conditions
//    thread.Join();
//
//    // [Verification]
//    u64_z uMilliseconds = elapsedTime.GetElapsedTimeAsInteger() / 1000000ULL;
//    BOOST_CHECK(uMilliseconds >= WAIT_TIME - 10U); // 10 ms tolerance
//    BOOST_CHECK(uMilliseconds < (WAIT_TIME + 10U)); // 10 ms tolerance
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS && !defined(Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT)

/// <summary>
/// Checks that an assertion fails when the thread is joined after it has been interrupted.
/// </summary>
ZTEST_CASE ( Join_AssertionFailsWhenThreadIsJoinedAfterItHasBeenInterrupted_Test )
{
    using System::Threading::SThisThread;
    using Tools::Time::TimeSpan;
    
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionToBeInterrupted);
    ThreadTestClass::ResetFlags();

    // [Execution]
// [TODO]: This test is very problematic due to inevitable race conditions
//    Thread thread(function); // The function is assumed to take enough time
//    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 30, 0, 0));
//    thread.Interrupt();
//    thread.Join();
//
//    // [Verification]
//    BOOST_CHECK(ThreadTestClass::sm_bFunctionInterrupted);
}

#endif

/// <summary>
/// Checks that the output format is what expected.
/// </summary>
ZTEST_CASE ( ToString_FormatIsWhatExpected_Test )
{
    // [Preparation]
    const string_z EXPECTED_PART1("Thread(");
    const string_z EXPECTED_PART2(")");
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    Thread thread(function, WAIT_TIME);

    // [Execution]
    string_z strResult = thread.ToString();

    // [Verification]
    thread.Join();
    bool bFormatIsWhatExpected = strResult.IndexOf(EXPECTED_PART1, EComparisonType::E_BinaryCaseSensitive) == 0;
    bFormatIsWhatExpected = bFormatIsWhatExpected && strResult.IndexOf(EXPECTED_PART2, EComparisonType::E_BinaryCaseSensitive) == scast_z(strResult.GetLength() - 1U, int);
    BOOST_CHECK(bFormatIsWhatExpected);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
ZTEST_CASE ( ToString_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.ToString();
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
/// Checks that no error occurs when the method is called.
/// </summary>
ZTEST_CASE ( Detach_NoErrorOccursWhenCalled_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    Thread thread(function, WAIT_TIME);

    // [Execution]
    thread.Detach();

    // [Verification]
    const bool NO_ERROR_OCCURRED = true;
    BOOST_CHECK(NO_ERROR_OCCURRED);
}

/// <summary>
/// Checks that it returns True when the thread is still running.
/// </summary>
ZTEST_CASE ( IsAlive_ReturnsTrueWhenThreadIsRunning_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    Thread thread(function, WAIT_TIME);

    // [Execution]
    bool bIsAlive = thread.IsAlive();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsAlive, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread is not running.
/// </summary>
ZTEST_CASE ( IsAlive_ReturnsFalseWhenThreadIsNotRunning_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();

    // [Execution]
    bool bIsAlive = thread.IsAlive();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsAlive, EXPECTED_RESULT);
}
 
#ifndef Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT

/// <summary>
/// Checks that it returns True when the thread was interrupted.
/// </summary>
ZTEST_CASE ( IsInterrupted_ReturnsTrueWhenThreadWasInterrupted_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    Delegate<void()> function(&ThreadTestClass::WorkSomeTime);
    Thread thread(function);
    thread.Interrupt();

    // [Execution]
    bool bIsInterrupted = thread.IsInterrupted();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread was not interrupted.
/// </summary>
ZTEST_CASE ( IsInterrupted_ReturnsFalseWhenThreadWasNotInterrupted_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    const unsigned int WAIT_TIME = 200;
    Thread thread(function, WAIT_TIME);

    // [Execution]
    bool bIsInterrupted = thread.IsInterrupted();
    thread.Join();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

#endif

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
ZTEST_CASE ( GetId_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetId();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
ZTEST_CASE ( GetNativeHandle_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetNativeHandle();
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
/// Checks that the priority is correctly set when it is the Lowest.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLowest_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Lowest;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Lowest;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Low.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLow_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Low;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Low;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Normal.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsNormal_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Normal;

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == INPUT_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is High.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHigh_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_High;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_High;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is the Highest.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHighest_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Highest;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Highest;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    thread.SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = thread.GetPriority();
    thread.Join();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
ZTEST_CASE ( SetPriority_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.SetPriority(EThreadPriority::E_Normal);
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
/// Checks that the priority is correctly obtained.
/// </summary>
ZTEST_CASE ( GetPriority_PriorityIsCorrectlyObtained_Test )
{
    // [Preparation]
    Delegate<void(unsigned int)> function(&ThreadTestClass::Wait);
    unsigned int uWaitTime = 100;
    Thread thread(function, uWaitTime);

    // [Execution]
    EThreadPriority ePriority = thread.GetPriority();

    // [Verification]
    thread.Join();
    BOOST_CHECK(ePriority == EThreadPriority::E_Lowest ||
                ePriority == EThreadPriority::E_Low    ||
                ePriority == EThreadPriority::E_Normal ||
                ePriority == EThreadPriority::E_High   ||
                ePriority == EThreadPriority::E_Highest);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the method is called after the thread has stopped.
/// </summary>
ZTEST_CASE ( GetPriority_AssertionFailsWhenMethodIsCalledAfterThreadHasStopped_Test )
{
    // [Preparation]
    Delegate<void()> function(&ThreadTestClass::FunctionWith0Params);
    Thread thread(function);
    thread.Join();
    bool bAssertionFailed = false;

    // [Execution]
    try
    {
        thread.GetPriority();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: Thread
ZTEST_SUITE_END()
