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

#include "ZTiming/StopwatchEnclosed.h"

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/Exceptions/AssertException.h"



ZTEST_SUITE_BEGIN( StopwatchEnclosed_TestSuite )

/// <summary>
/// Method used in some tests to wait for a given amount of time.
/// </summary>
/// <param name="uMilliseconds">Number of milliseconds to stay waiting.</param>
void Wait_TestMethod(const unsigned int uMilliseconds)
{
    StopwatchEnclosed stopwatch;
    stopwatch.Set();

    while(stopwatch.GetElapsedTimeAsInteger() / 1000000ULL < uMilliseconds)
        ;
}

/// <summary>
/// Checks that the default values set by the default constructor have not changed since the last time the test was executed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const TimeSpan EXPECTED_TIMELAPSE(0);
    const EStopwatchEnclosedBehavior EXPECTED_BEHAVIOR(EStopwatchEnclosedBehavior::E_Clamped);

    // [Execution]
    StopwatchEnclosed stopwatch;
    
    // [Verification]
    EStopwatchEnclosedBehavior eBehavior = stopwatch.GetBehavior();
    TimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(eBehavior == EXPECTED_BEHAVIOR);
    BOOST_CHECK(timeLapse == EXPECTED_TIMELAPSE);
}

/// <summary>
/// Checks that the input values are stored correctly.
/// </summary>
ZTEST_CASE ( Constructor2_InputValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const TimeSpan EXPECTED_TIMELAPSE(0, 0, 0, 0, 123, 0, 0);
    const EStopwatchEnclosedBehavior EXPECTED_BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);

    // [Execution]
    StopwatchEnclosed stopwatch(EXPECTED_TIMELAPSE, EXPECTED_BEHAVIOR);
    
    // [Verification]
    EStopwatchEnclosedBehavior eBehavior = stopwatch.GetBehavior();
    TimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(eBehavior == EXPECTED_BEHAVIOR);
    BOOST_CHECK(timeLapse == EXPECTED_TIMELAPSE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Clamp behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = SFloat::_1;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Clamped);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Clamp behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_z MAXIMUM_VALUE = SFloat::_1;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Clamped);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult == MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Proportional behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = SFloat::_1;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Proportional);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Proportional behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = SFloat::_2;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Proportional);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult >= EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Cyclic behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = SFloat::_1;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Cyclic behavior.
/// </summary>
ZTEST_CASE ( GetProgression_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_z MAXIMUM_VALUE = SFloat::_1;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetProgression();
    
    // [Verification]
    BOOST_CHECK(fResult < MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Clamp behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 100.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Clamped);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Clamp behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingClampBehavior_Test )
{
    // [Preparation]
    const float_z MAXIMUM_VALUE = 100.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Clamped);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult == MAXIMUM_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Proportional behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 100.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Proportional);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Proportional behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingProportionalBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 200.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Proportional);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult >= EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is lower than the time lapse, using Cyclic behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsLowerThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 100.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 200, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult > SFloat::_0);
    BOOST_CHECK(fResult < EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when the time passed is greater than the time lapse, using Cyclic behavior.
/// </summary>
ZTEST_CASE ( GetPercentage_ReturnsExpectedValueWhenTimePassedIsGreaterThanTimeLapseAndUsingCyclicBehavior_Test )
{
    // [Preparation]
    const float_z MAXIMUM_VALUE = 100.0;
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);
    StopwatchEnclosed stopwatch(TIMELAPSE, BEHAVIOR);
    stopwatch.Set();
    Wait_TestMethod(100);

    // [Execution]
    float_z fResult = stopwatch.GetPercentage();
    
    // [Verification]
    BOOST_CHECK(fResult < MAXIMUM_VALUE);
}

/// <summary>
/// Checks that the time lapse is correctly stored.
/// </summary>
ZTEST_CASE ( SetTimeLapseLength_TimeLapseIsCorrectlyStored_Test )
{
    // [Preparation]
    const TimeSpan TIMELAPSE(0, 0, 0, 0, 50, 0, 0);
    const EStopwatchEnclosedBehavior BEHAVIOR(EStopwatchEnclosedBehavior::E_Cyclic);
    StopwatchEnclosed stopwatch;
    
    // [Execution]
    stopwatch.SetTimeLapseLength(TIMELAPSE);
    
    // [Verification]
    TimeSpan timeLapse = stopwatch.GetTimeLapseLength();
    BOOST_CHECK(timeLapse == TIMELAPSE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input time lapse equals zero.
/// </summary>
ZTEST_CASE ( SetTimeLapseLength_AssertionFailsWhenInputIsZero_Test )
{
    // [Preparation]
    const TimeSpan TIMELAPSE(0);
    StopwatchEnclosed stopwatch;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        stopwatch.SetTimeLapseLength(TIMELAPSE);
    }
    catch(const Common::Exceptions::AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: StopwatchEnclosed
ZTEST_SUITE_END()
