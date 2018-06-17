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

#include "ZTime/TimeSpan.h"
#include "ZCommon/Exceptions/AssertException.h"

#pragma Z_DISABLE_WARNING(4146)


ZTEST_SUITE_BEGIN( TimeSpan_TestSuite )

/// <summary>
/// Checks constructor with no parameters.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 0;
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpan;

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

/// <summary>
/// Checks constructor with one parameter. Checks if the class member is set correctly
/// </summary>
ZTEST_CASE ( Constructor2_ParameterIsProperlyAssigned_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 15;
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpan(EXPECTED_VALUE_FOR_TIMESPAN);

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

/// <summary>
/// Checks constructor with several values as parameters.
/// These values represent days, hours, minutes, seconds, mseconds, microseconds and hundreds of nanosecs
/// </summary>
ZTEST_CASE ( Constructor3_InstanceIsCorrectlyConstructedWhenUsingCommonTimeValues_Test )
{
    // [Preparation]
    const u64_z VALUE_FOR_DAYS = 1;
    const u64_z VALUE_FOR_HOURS = 1;
    const u64_z VALUE_FOR_MINUTES = 1;
    const u64_z VALUE_FOR_SECONDS = 1;
    const u64_z VALUE_FOR_MSECONDS = 1;
    const u64_z VALUE_FOR_MICROSECONDS = 1;
    const u64_z VALUE_FOR_HUNDREDSNANOSECS = 1;
    //days * 24 = hours
    //hours * 60 = minutes
    //minutes * 60 = seconds
    //seconds * 1000 = mseconds
    //microseconds * 1000 = microsecs
    //microsecs * 10 = hundreds of nanosecs
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 900610010011;
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS,
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);


    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
/// <summary>
/// Checks if the overflow when passing parameter bigger than the maximum allowed provokes the return of max value.
/// </summary>
ZTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_z VALUE_FOR_DAYS = 100000000000;
    const u64_z VALUE_FOR_HOURS = 1;
    const u64_z VALUE_FOR_MINUTES = 1;
    const u64_z VALUE_FOR_SECONDS = 1;
    const u64_z VALUE_FOR_MSECONDS = 1;
    const u64_z VALUE_FOR_MICROSECONDS = 1;
    const u64_z VALUE_FOR_HUNDREDSNANOSECS = 1;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = -1;
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS,
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);

}

/// <summary>
/// Checks if the overflow when computing the sum of all parameters provokes the return of max value.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_z>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
ZTEST_CASE ( Constructor3_MaximumValueIsAssignedWhenAdditionOfParametersProduceOverflow_Test )
{
    // [Preparation]
    const u64_z VALUE_FOR_DAYS = 21350397;
    const u64_z VALUE_FOR_HOURS = 512409556;
    const u64_z VALUE_FOR_MINUTES = 30744573455;
    const u64_z VALUE_FOR_SECONDS = 1844674407369;
    const u64_z VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_z VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_z VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = -1;
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS,
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);

    // [Verification]
    BOOST_CHECK(timeSpan == timeSpanExpectedResult);

}

#endif

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when passing parameter bigger the the maximum allowed.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithParameterOccurs_Test )
{
    // [Preparation]
    const u64_z VALUE_FOR_DAYS = 100000000000;
    const u64_z VALUE_FOR_HOURS = 1;
    const u64_z VALUE_FOR_MINUTES = 1;
    const u64_z VALUE_FOR_SECONDS = 1;
    const u64_z VALUE_FOR_MSECONDS = 1;
    const u64_z VALUE_FOR_MICROSECONDS = 1;
    const u64_z VALUE_FOR_HUNDREDSNANOSECS = 1;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS,
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion inside the constructor fails whith overflow when computing the sum of all parameters.
/// </summary>
/// <remarks>
/// The values used in the test are computed as follows: e.g std::numeric_limits<u64_z>::max() / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND - 1: (max value allowed divided by amount of hundreds of nanosecond of every parameter ) minus one.
/// </remarks>
ZTEST_CASE ( Constructor3_AssertionFailsWhenOverflowWithAdditionOccurs_Test )
{
    // [Preparation]
    const u64_z VALUE_FOR_DAYS = 21350397;
    const u64_z VALUE_FOR_HOURS = 512409556;
    const u64_z VALUE_FOR_MINUTES = 30744573455;
    const u64_z VALUE_FOR_SECONDS = 1844674407369;
    const u64_z VALUE_FOR_MSECONDS = 1844674407370954;
    const u64_z VALUE_FOR_MICROSECONDS = 1844674407370955160;
    const u64_z VALUE_FOR_HUNDREDSNANOSECS = 1000000000000000000;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TimeSpan timeSpan(VALUE_FOR_DAYS, VALUE_FOR_HOURS, VALUE_FOR_MINUTES, VALUE_FOR_SECONDS,
                       VALUE_FOR_MSECONDS, VALUE_FOR_MICROSECONDS, VALUE_FOR_HUNDREDSNANOSECS);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that common values are stored correctly.
/// </summary>
ZTEST_CASE ( Constructor4_CommonValuesStoredCorrectly_Test )
{
    // [Preparation]
    const float_z INPUT_VALUE = 123.567;
    const TimeSpan EXPECTED_VALUE(0, 0, 0, 123, 567, 1, 6); // Lack of precission

	// [Execution]
    TimeSpan timeSpan(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(timeSpan == EXPECTED_VALUE);
}

/// <summary>
/// Checks that very small values are stored correctly.
/// </summary>
ZTEST_CASE ( Constructor4_SmallValuesAreStoredCorrectly_Test )
{
    // [Preparation]
    const float_z INPUT_VALUE = 0.000123456;
    const TimeSpan EXPECTED_VALUE(0, 0, 0, 0, 0, 123, 4);

	// [Execution]
    TimeSpan timeSpan(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(timeSpan == EXPECTED_VALUE);
}

/// <summary>
/// Checks that very big values are stored correctly.
/// </summary>
ZTEST_CASE ( Constructor4_BigValuesAreStoredCorrectly_Test )
{
    // [Preparation]
    const float_z INPUT_VALUE = 123456789.0;
    const TimeSpan EXPECTED_VALUE(1234567948140544ULL); // Lack of precission

	// [Execution]
    TimeSpan timeSpan(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(timeSpan == EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the constructor fails whith the input value is a negative number.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenInputIsNegative_Test )
{
    // [Preparation]
    const float_z NEGATIVE_NUMBER = -1.0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TimeSpan timeSpan(NEGATIVE_NUMBER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if copy constructor works properly.
/// </summary>
ZTEST_CASE ( Constructor5_TimeSpanIsCopiedCorrectly_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 150;
    TimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpanResult(timeSpanOriginal);

    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanOriginal);
}

/// <summary>
/// Checks assignment operator.
/// </summary>
ZTEST_CASE ( AssignmentOperator_AssignmentOperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 150;
    TimeSpan timeSpanOriginal(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpanAssigned = timeSpanOriginal;

    // [Verification]
    BOOST_CHECK(timeSpanAssigned == timeSpanOriginal);
}

/// <summary>
/// Checks that addition and assignment operator works properly.
/// The addition is performed and the result is assigned to the first time span instance.
/// </summary>
ZTEST_CASE ( AdditionAndAssignmentOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_z TIMESPAN_VALUE_TO_ADD = 15;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 25;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    timeSpanOriginal += timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the operator fails when the addition of the two operands provokes an overflow.
/// </summary>
ZTEST_CASE ( AdditionAndAssignmentOperator_AssertionFailsWhenAdditionProvokesOverflow_Test)
{
    // [Preparation]
    bool bAssertionFailed = false;
    TimeSpan timeSpanOriginal(-1ULL);
    TimeSpan timeSpanToAdd(-1ULL);

	// [Execution]
    try
    {
        timeSpanOriginal += timeSpanToAdd;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
/// <summary>
/// Checks if the overflow when trying to add time span bigger than the maximum allowed provokes the return of max value.
/// </summary>
ZTEST_CASE ( AdditionAndAssignmentOperator_MaximumValueIsAssignedWhenAdditionProducesOverflow_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = -1;
    TimeSpan timeSpanOriginal(-1);
    TimeSpan timeSpanToAdd(-1);
     //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    timeSpanOriginal += timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);

}

#endif

/// <summary>
/// Checks addition operator. The addition is correctly performed and result is assigned to a new instance.
/// </summary>
ZTEST_CASE ( AdditionOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_z TIMESPAN_VALUE_TO_ADD = 15;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 25;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);


	// [Execution]
    TimeSpan timeSpanResult = timeSpanOriginal + timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}


#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the operator fails when the addition of the two operands provokes an overflow.
/// </summary>
ZTEST_CASE ( AdditionOperator_AssertionFailsWhenAdditionProvokesOverflow_Test )
{
    // [Preparation]
    bool bAssertionFailed = false;
    TimeSpan timeSpanOriginal(-1ULL);
    TimeSpan timeSpanToAdd(-1ULL);

	// [Execution]
    try
    {
        timeSpanOriginal + timeSpanToAdd;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks if the overflow when trying to add time span bigger than the maximum allowed provokes the return of max value.
/// </summary>
ZTEST_CASE ( AdditionOperator_MaximumValueIsAssignedWhenAdditionProducesOverflow_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = -1;
    TimeSpan timeSpanOriginal(-1);
    TimeSpan timeSpanToAdd(-1);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpanResult = timeSpanOriginal + timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);

}

#endif

/// <summary>
/// Checks subtraction operator. The subtraction is correctly done and result is assigned to new instance.
/// </summary>
ZTEST_CASE ( SubtractionOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 15;
    const u64_z TIMESPAN_VALUE_TO_SUBSTRACT = 10;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 5;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpanResult = timeSpanOriginal - timeSpanToSubstract;

    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction operator.
/// In this case checks that if you substract a bigger value the result is the absolute value.
/// </summary>
ZTEST_CASE ( SubtractionOperator_OperationIsDoneCorrectlyWhenSecondOperatorIsBigger_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_z TIMESPAN_VALUE_TO_SUBSTRACT = 15;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 5;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    TimeSpan timeSpanResult = timeSpanOriginal - timeSpanToSubstract;

    // [Verification]
    BOOST_CHECK(timeSpanResult == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction and assignment operator.
/// The subtraction is performed and the result is assigned to the first operand.
/// </summary>
ZTEST_CASE ( SubtractionAndAssignmentOperator_OperationIsDoneCorrectly_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 15;
    const u64_z TIMESPAN_VALUE_TO_SUBSTRACT = 10;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 5;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToSubstract(TIMESPAN_VALUE_TO_SUBSTRACT);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    timeSpanOriginal -= timeSpanToSubstract;

    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}

/// <summary>
/// Checks subtraction operator.
/// In this case checks that if you subtract a bigger value the result is the absolute value and the it is assigned to first operand.
/// </summary>
ZTEST_CASE ( SubtractionAndAssignmentOperator_OperationIsDoneCorrectlyWhenSecondOperatorIsBigger_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN = 10;
    const u64_z TIMESPAN_VALUE_TO_ADD = 15;
    const u64_z EXPECTED_VALUE_FOR_TIMESPAN = 5;
    TimeSpan timeSpanOriginal(INITIAL_VALUE_FOR_TIMESPAN);
    TimeSpan timeSpanToAdd(TIMESPAN_VALUE_TO_ADD);
    //TimeSpan object to perform the comparison.
    TimeSpan timeSpanExpectedResult(EXPECTED_VALUE_FOR_TIMESPAN);

	// [Execution]
    timeSpanOriginal -= timeSpanToAdd;

    // [Verification]
    BOOST_CHECK(timeSpanOriginal == timeSpanExpectedResult);
}

/// <summary>
/// Checks equality operator. Compares to instances and check that the return value is true as they are equal.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsTrueWhenComparingTwoEqualValues_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 == timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks equality operator. This case checks than the return value is false when the values are not equal.
/// </summary>
ZTEST_CASE ( EqualityOperator_ReturnsFalseWhenComparingTwoDifferentValues_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = false;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 == timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks inequality operator. This test checks that the return value is false when comparing two equal values.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsFalseWhenComparingTwoEqualValues_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_VALUE = false;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = (timeSpan1 != timeSpan2);

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks inequality operator. This test checks that the return value is true when comparing two different values.
/// </summary>
ZTEST_CASE ( InequalityOperator_ReturnsTrueWhenComparingTwoDifferentValues_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = (timeSpan1 != timeSpan2);

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than operator.
/// This test checks that the return value is true since first operator is bigger than the second one.
/// </summary>
ZTEST_CASE ( GreaterThanOperator_ReturnsTrueWhenFirstValueGreater_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 > timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than operator.
/// This test checks that the return value is false since first operator is not bigger than the second one.
/// </summary>
ZTEST_CASE ( GreaterThanOperator_ReturnsFalseWhenFirstValueNotGreater_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 16;
    const bool EXPECTED_RESULT = false;

    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 > timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator.
/// First value bigger than the second one, the test checks that the return value is true.
/// </summary>
ZTEST_CASE ( GreaterThanOrEqualsOperator_ReturnsTrueWhenFirstValueGreater_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;

    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator.
/// First value equal to the second one, this test checks that the return value is true.
/// </summary>
ZTEST_CASE ( GreaterThanOrEqualsOperator_ReturnsTrueWhenFirstValueEqualToSecondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 15;
    const bool EXPECTED_RESULT = true;

    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks greater than or equals to operator.
/// First value lower than the second one, this test checks that the return value is false.
/// </summary>
ZTEST_CASE ( GreaterThanOperator_ReturnsFalseWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 15;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 19;
    const bool EXPECTED_RESULT = false;

    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 >= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than operator.
//  First value lower than the second one, this test checks that the return value is true.
/// </summary>
ZTEST_CASE ( LowerThanOperator_ReturnsTrueWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 9;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 < timeSpan2;

    // [Verification]
     BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than operator.
/// First value not lower than the second one, this test checks that the return value is false.
/// </summary>
ZTEST_CASE ( LowerThanOperator_ReturnsFalseWhenFirstValueNotLowerThanSecondOne_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 11;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = false;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 < timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator.
/// First value lower than the second one, this test will check that the return value is true.
/// </summary>
ZTEST_CASE ( LowerThanOrEquals_Operator_ReturnsTrueWhenFirstValueLowerThanSecondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 9;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator.
/// First value equal than the second one, this test will check that the return value is true.
/// </summary>
ZTEST_CASE ( LowerThanOrEqualsOperator_ReturnsTrueWhenFirstValueEqualToSeCondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 10;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_RESULT = true;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks lower than or equals to operator.
/// First value bigger than the second one, so this test checks that the return value is false.
/// </summary>
ZTEST_CASE ( LowerThanOrEqualsOperator_ReturnsFalseWhenFirstValueGreaterThanSeCondValue_Test )
{
    // [Preparation]
    const u64_z INITIAL_VALUE_FOR_TIMESPAN1 = 12;
    const u64_z INITIAL_VALUE_FOR_TIMESPAN2 = 10;
    const bool EXPECTED_VALUE = false;
    TimeSpan timeSpan1(INITIAL_VALUE_FOR_TIMESPAN1);
    TimeSpan timeSpan2(INITIAL_VALUE_FOR_TIMESPAN2);

	// [Execution]
    bool bComparisonResult = timeSpan1 <= timeSpan2;

    // [Verification]
    BOOST_CHECK_EQUAL(bComparisonResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetDays_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 0;
    const TimeSpan MINIMUM_TIMESPAN(scast_z(EXPECTED_VALUE, u64_z));

	// [Execution]
    u32_z uDays = MINIMUM_TIMESPAN.GetDays();

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetDays_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 1428;
    const TimeSpan COMMON_TIMESPAN(1234567890123456ULL);

	// [Execution]
    u32_z uDays = COMMON_TIMESPAN.GetDays();

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetDays_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 21350398;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u32_z uDays = MAXIMUM_TIMESPAN.GetDays();

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetHours_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 0;
    const TimeSpan MINIMUM_TIMESPAN(scast_z(EXPECTED_VALUE, u64_z));

	// [Execution]
    u32_z uHours = MINIMUM_TIMESPAN.GetHours();

    // [Verification]
    BOOST_CHECK_EQUAL(uHours, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetHours_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 342;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u32_z uHours = COMMON_TIMESPAN.GetHours();

    // [Verification]
    BOOST_CHECK_EQUAL(uHours, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetHours_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 512409557;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u32_z uHours = MAXIMUM_TIMESPAN.GetHours();

    // [Verification]
    BOOST_CHECK_EQUAL(uHours, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetMinutes_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 0;
    const TimeSpan MINIMUM_TIMESPAN(scast_z(EXPECTED_VALUE, u64_z));

	// [Execution]
    u32_z uMinutes = MINIMUM_TIMESPAN.GetMinutes();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinutes, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetMinutes_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 20576;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u32_z uMinutes = COMMON_TIMESPAN.GetMinutes();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinutes, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetMinutes_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u32_z EXPECTED_VALUE = 679802384;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u32_z uMinutes = MAXIMUM_TIMESPAN.GetMinutes();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinutes, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetSeconds_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 0LL;
    const TimeSpan MINIMUM_TIMESPAN(EXPECTED_VALUE);

	// [Execution]
    u64_z uSeconds = MINIMUM_TIMESPAN.GetSeconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetSeconds_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1234567LL;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u64_z uSeconds = COMMON_TIMESPAN.GetSeconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetSeconds_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1844674407370ULL;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u64_z uSeconds = MAXIMUM_TIMESPAN.GetSeconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetSecondsAsFloat_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 0.0;
    const TimeSpan MINIMUM_TIMESPAN(scast_z(EXPECTED_VALUE, u64_z));

	// [Execution]
    float_z fSeconds = MINIMUM_TIMESPAN.GetSecondsAsFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetSecondsAsFloat_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_VALUE = 1234567.88;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_VALUE = 1234567.8912345;
#endif
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    float_z fSeconds = COMMON_TIMESPAN.GetSecondsAsFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetSecondsAsFloat_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = 1844674407370.0;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    float_z fSeconds = MAXIMUM_TIMESPAN.GetSecondsAsFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fSeconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetMilliseconds_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 0LL;
    const TimeSpan MINIMUM_TIMESPAN(EXPECTED_VALUE);

	// [Execution]
    u64_z uMilliseconds = MINIMUM_TIMESPAN.GetMilliseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMilliseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetMilliseconds_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1234567891ULL;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u64_z uMilliseconds = COMMON_TIMESPAN.GetMilliseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMilliseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetMilliseconds_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1844674407370955ULL;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u64_z uMilliseconds = MAXIMUM_TIMESPAN.GetMilliseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMilliseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetMicroseconds_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 0LL;
    const TimeSpan MINIMUM_TIMESPAN(EXPECTED_VALUE);

	// [Execution]
    u64_z uMicroseconds = MINIMUM_TIMESPAN.GetMicroseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicroseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetMicroseconds_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1234567891234ULL;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u64_z uMicroseconds = COMMON_TIMESPAN.GetMicroseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicroseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetMicroseconds_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 1844674407370955161ULL;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u64_z uMicroseconds = MAXIMUM_TIMESPAN.GetMicroseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicroseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns zero when the time span has its minimum value.
/// </summary>
ZTEST_CASE ( GetHundredsOfNanoseconds_ReturnsZeroWhenUsingMinimumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 0LL;
    const TimeSpan MINIMUM_TIMESPAN(EXPECTED_VALUE);

	// [Execution]
    u64_z uHundredsOfNanoseconds = MINIMUM_TIMESPAN.GetHundredsOfNanoseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredsOfNanoseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using a common time span.
/// </summary>
ZTEST_CASE ( GetHundredsOfNanoseconds_ReturnsExpectedValueWhenUsingCommonTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 12345678912345ULL;
    const TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    u64_z uHundredsOfNanoseconds = COMMON_TIMESPAN.GetHundredsOfNanoseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredsOfNanoseconds, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected value when using the maximum time span.
/// </summary>
ZTEST_CASE ( GetHundredsOfNanoseconds_ReturnsExpectedValueWhenUsingMaximumTimeSpan_Test )
{
    // [Preparation]
    const u64_z EXPECTED_VALUE = 18446744073709551615ULL;
    const TimeSpan MAXIMUM_TIMESPAN(-1ULL);

	// [Execution]
    u64_z uHundredsOfNanoseconds = MAXIMUM_TIMESPAN.GetHundredsOfNanoseconds();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredsOfNanoseconds, EXPECTED_VALUE);
}

/// <summary>
/// Returns the time span (hundreds of nanosecond) as string.
/// </summary>
ZTEST_CASE ( ToString_ReturnsTimeSpanAsString_Test )
{
    // [Preparation]
    const string_z EXPECTED_VALUE = Z_L("12345678912345");
    TimeSpan COMMON_TIMESPAN(12345678912345ULL);

	// [Execution]
    string_z strStringRepresentation = COMMON_TIMESPAN.ToString();

    // [Verification]
    BOOST_CHECK(strStringRepresentation == EXPECTED_VALUE);
}

// End - Test Suite: TimeSpan
ZTEST_SUITE_END()
