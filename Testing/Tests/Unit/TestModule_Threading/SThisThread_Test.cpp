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

// Note: Several methods are not testable since it's not possible to have a reference value or to measure the result of their execution

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZThreading/SThisThread.h"

#include "ZTiming/Stopwatch.h"
#include "ZCommon/DataTypes/EComparisonType.h"


// Class whose methods are to be used in the tests of SThisThread
class SThisThreadTestClass
{
public:

    static bool sm_bContinue;
    static bool sm_bFunctionInterrupted;
    static bool sm_bExitFunctionCalled;

    static void ResetFlags()
    {
        sm_bFunctionInterrupted = false;
        sm_bExitFunctionCalled = false;
    }

    static void FunctionToBeInterrupted()
    {
        while(!sm_bContinue)
            ;

        sm_bFunctionInterrupted = SThisThread::IsInterrupted();
    }

    static void ExitFunction()
    {
        sm_bExitFunctionCalled = true;
    }

    static void FunctionExecutedInAnotherThread()
    {
        SThisThread::SetExitFunction(&SThisThreadTestClass::ExitFunction);
    }
};

bool SThisThreadTestClass::sm_bContinue = false;
bool SThisThreadTestClass::sm_bFunctionInterrupted = false;
bool SThisThreadTestClass::sm_bExitFunctionCalled = false;



ZTEST_SUITE_BEGIN( SThisThread_TestSuite )
    
/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
ZTEST_CASE ( Yield_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SThisThread::Yield();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that the thread sleeps for the expected time.
/// </summary>
ZTEST_CASE ( Sleep_ThreadSleepsForTheExpectedTime_Test )
{
    // [Preparation]
    const TimeSpan EXPECTED_TIME(0, 0, 0, 0, 500, 0 ,0); // ms
    Stopwatch timer;
    timer.Set();

    // [Execution]
    SThisThread::Sleep(EXPECTED_TIME);

    // [Verification]
    TimeSpan ellapsedTime = timer.GetElapsedTimeAsTimeSpan();
    const TimeSpan TOLERANCE(0, 0, 0, 0, 10, 0, 0); // ms
    BOOST_CHECK(ellapsedTime >= EXPECTED_TIME - TOLERANCE && ellapsedTime < EXPECTED_TIME + TOLERANCE);
}

/// <summary>
/// Checks that the output format is what expected.
/// </summary>
ZTEST_CASE ( ToString_FormatIsWhatExpected_Test )
{
    // [Preparation]
    const string_z EXPECTED_PART1("Thread(");
    const string_z EXPECTED_PART2(")");

    // [Execution]
    string_z strResult = SThisThread::ToString();

    // [Verification]
    bool bFormatIsWhatExpected = strResult.IndexOf(EXPECTED_PART1, EComparisonType::E_BinaryCaseSensitive) == 0;
    bFormatIsWhatExpected = bFormatIsWhatExpected && strResult.IndexOf(EXPECTED_PART2, EComparisonType::E_BinaryCaseSensitive) == scast_z(strResult.GetLength() - 1U, int);
    BOOST_CHECK(bFormatIsWhatExpected);
}

#ifndef Z_PREPROCESSOR_IMPORTLIB_ZUNDERBOLT

/// <summary>
/// Checks that it returns True when the thread was interrupted.
/// </summary>
ZTEST_CASE ( IsInterrupted_ReturnsTrueWhenThreadWasInterrupted_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    Delegate<void()> function(&SThisThreadTestClass::FunctionToBeInterrupted);
    SThisThreadTestClass::sm_bContinue = false;
    Thread thread(function);
    SThisThreadTestClass::ResetFlags();
    SThisThread::Sleep(TimeSpan(0, 0, 0, 0, 10, 0, 0));
    thread.Interrupt();
    SThisThreadTestClass::sm_bContinue = true;

    // [Execution]
    thread.Join();

    // [Verification]
    bool bIsInterrupted = SThisThreadTestClass::sm_bFunctionInterrupted;
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the thread was not interrupted.
/// </summary>
ZTEST_CASE ( IsInterrupted_ReturnsFalseWhenThreadWasNotInterrupted_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    Delegate<void()> function(&SThisThreadTestClass::FunctionToBeInterrupted);
    Thread thread(function);
    SThisThreadTestClass::ResetFlags();

    // [Execution]
    thread.Join();

    // [Verification]
    bool bIsInterrupted = SThisThreadTestClass::sm_bFunctionInterrupted;
    BOOST_CHECK_EQUAL(bIsInterrupted, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
ZTEST_CASE ( GetId_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SThisThread::GetId();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that no error ocurrs when it is called.
/// </summary>
ZTEST_CASE ( GetNativeHandle_NoErrorOccurs_Test )
{
    // [Preparation]
    const bool NO_ERRORS_OCCURRED = true;

    // [Execution]
    SThisThread::GetNativeHandle();

    // [Verification]
    BOOST_CHECK(NO_ERRORS_OCCURRED);
}

/// <summary>
/// Checks that the function is called when the thread exits.
/// </summary>
ZTEST_CASE ( SetExitFunction_FunctionIsCalledWhenThreadExits_Test )
{
    // [Preparation]
    SThisThreadTestClass::ResetFlags();
    Delegate<void()> function(&SThisThreadTestClass::FunctionExecutedInAnotherThread);
    
    // [Execution]
    Thread thread(function); // Calls the exit function when finishes

    // [Verification]
    thread.Join();

    BOOST_CHECK(SThisThreadTestClass::sm_bExitFunctionCalled);
}

/// <summary>
/// Checks that the priority is correctly set when it is the Lowest.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLowest_Test )
{
    // [Preparation]
    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Lowest;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Lowest;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    SThisThread::SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = SThisThread::GetPriority();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Low.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsLow_Test )
{
    // [Preparation]
    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Low;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Low;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    SThisThread::SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = SThisThread::GetPriority();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is Normal.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsNormal_Test )
{
    // [Preparation]
    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Normal;

    // [Execution]
    SThisThread::SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = SThisThread::GetPriority();
    BOOST_CHECK(ePriority == INPUT_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is High.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHigh_Test )
{
    // [Preparation]
    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_High;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_High;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    SThisThread::SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = SThisThread::GetPriority();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly set when it is the Highest.
/// </summary>
ZTEST_CASE ( SetPriority_PriorityIsCorrectlySetWhenItIsHighest_Test )
{
    // [Preparation]
    const EThreadPriority INPUT_PRIORITY = EThreadPriority::E_Highest;
#if defined(Z_OS_WINDOWS) || defined(Z_OS_MAC)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Highest;
#elif defined(Z_OS_LINUX)
    const EThreadPriority EXPECTED_PRIORITY = EThreadPriority::E_Normal;
#endif

    // [Execution]
    SThisThread::SetPriority(INPUT_PRIORITY);

    // [Verification]
    EThreadPriority ePriority = SThisThread::GetPriority();
    BOOST_CHECK(ePriority == EXPECTED_PRIORITY);
}

/// <summary>
/// Checks that the priority is correctly obtained.
/// </summary>
ZTEST_CASE ( GetPriority_PriorityIsCorrectlyObtained_Test )
{
    // [Preparation]
    
    // [Execution]
    EThreadPriority ePriority = SThisThread::GetPriority();

    // [Verification]
    BOOST_CHECK(ePriority == EThreadPriority::E_Lowest ||
                ePriority == EThreadPriority::E_Low    ||
                ePriority == EThreadPriority::E_Normal ||
                ePriority == EThreadPriority::E_High   ||
                ePriority == EThreadPriority::E_Highest);
}

// End - Test Suite: SThisThread
ZTEST_SUITE_END()
