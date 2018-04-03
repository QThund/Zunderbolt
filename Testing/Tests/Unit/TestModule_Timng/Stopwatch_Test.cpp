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

#include "ZTiming/Stopwatch.h"

#include "StopwatchWhiteBox.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::StopwatchWhiteBox;


ZTEST_SUITE_BEGIN( Stopwatch_TestSuite )

/// <summary>
/// Checks that attributes are correctly initialized.
/// </summary>
ZTEST_CASE ( Constructor_ItIsCorrectlyInitialized_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 0;

    // [Execution]
    StopwatchWhiteBox stopWatch;
    
    // [Verification]
    BOOST_CHECK_EQUAL(stopWatch.GetReferenceInstantForTest(), EXPECTED_VALUE);
}

/// <summary>
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsFloat_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    // [Preparation]
    const float_z ZERO = 0.0;
    Stopwatch stopWatch;
    stopWatch.Set();
    
    // Delay
    for(int i = 0; i < 1000000; ++i)
        i = i;

    // [Execution]
    float_z fValue = stopWatch.GetElapsedTimeAsFloat();
    
    // [Verification]
    BOOST_CHECK(fValue > ZERO);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsFloat_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    Stopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsFloat();
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
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsInteger_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    // [Preparation]
    const u64_z ZERO = 0;
    Stopwatch stopWatch;
    stopWatch.Set();
    
    // Delay
    for(int i = 0; i < 10000; ++i)
        i = i;

    // [Execution]
    u64_z uValue = stopWatch.GetElapsedTimeAsInteger();
    
    // [Verification]
    BOOST_CHECK(uValue > ZERO);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsInteger_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    Stopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsInteger();
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
/// Checks that the returned value is greater than zero when the stopwatch is set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsTimeSpan_ReturnedValueIsGreaterThanZeroWhenStopWatchIsSet_Test )
{
    // [Preparation]
    const TimeSpan ZERO = TimeSpan(0);
    Stopwatch stopWatch;
    stopWatch.Set();

    // Delay
    for(int i = 0; i < 10000; ++i)
        i = i;

    // [Execution]
    TimeSpan value = stopWatch.GetElapsedTimeAsTimeSpan();
    
    // [Verification]
    BOOST_CHECK(value > ZERO);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the stopwatch as not been set.
/// </summary>
ZTEST_CASE ( GetElapsedTimeAsTimeSpan_AssertionFailsWhenStopWatchHasNotBeenSet_Test )
{
    // [Preparation]
    Stopwatch stopWatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopWatch.GetElapsedTimeAsTimeSpan();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: Stopwatch
ZTEST_SUITE_END()
