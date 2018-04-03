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

#include "ZTime/DateTime.h"

#include "ZTime/STimeZoneFactory.h"
#include "ZCommon/Exceptions/AssertException.h"
#include "ZTime/TimeZone.h"


ZTEST_SUITE_BEGIN( DateTime_TestSuite )

/// <summary>
/// This method has been created to improve some tests' maintainability. Concretely, this method performs tests for Decompose.
/// </summary>
void CheckDecompose_UtilityMethod(const DateTime &dateTimeToTest, const unsigned int uExpectedYear, const unsigned int uExpectedMonth, const unsigned int uExpectedDay, 
                                                                   const unsigned int uExpectedHour, const unsigned int uExpectedMinute, const unsigned int uExpectedSecond, 
                                                                   const unsigned int uExpectedMillisecond, const unsigned int uExpectedMicrosecond, const unsigned int uExpectedHundredOfNanosecond)
{
    unsigned int uYear = 0;
    unsigned int uMonth = 0;
    unsigned int uDay = 0;
    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;
    unsigned int uMillisecond = 0;
    unsigned int uMicrosecond = 0;
    unsigned int uHundredOfNanosecond = 0;

	// [Execution]
    dateTimeToTest.Decompose(uYear, uMonth, uDay, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond);

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, uExpectedYear);
    BOOST_CHECK_EQUAL(uMonth, uExpectedMonth);
    BOOST_CHECK_EQUAL(uDay, uExpectedDay);
    BOOST_CHECK_EQUAL(uHour, uExpectedHour);
    BOOST_CHECK_EQUAL(uMinute, uExpectedMinute);
    BOOST_CHECK_EQUAL(uSecond, uExpectedSecond);
    BOOST_CHECK_EQUAL(uMillisecond, uExpectedMillisecond);
    BOOST_CHECK_EQUAL(uMicrosecond, uExpectedMicrosecond);
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, uExpectedHundredOfNanosecond);
}

/// <summary>
/// This method has been created to improve some tests' maintainability. Concretely, this method performs tests for DecomposeDate.
/// </summary>
void CheckDecomposeDate_UtilityMethod(const DateTime &dateTimeToTest, const unsigned int uExpectedYear, const unsigned int uExpectedMonth, const unsigned int uExpectedDay)
{
    unsigned int uYear = 0;
    unsigned int uMonth = 0;
    unsigned int uDay = 0;

	// [Execution]
    dateTimeToTest.DecomposeDate(uYear, uMonth, uDay);

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, uExpectedYear);
    BOOST_CHECK_EQUAL(uMonth, uExpectedMonth);
    BOOST_CHECK_EQUAL(uDay, uExpectedDay);
}

/// <summary>
/// This method has been created to improve some tests' maintainability. Concretely, this method performs tests for DecomposeTime1.
/// </summary>
void CheckDecomposeTime1_UtilityMethod(const DateTime &dateTimeToTest, const unsigned int uExpectedHour, const unsigned int uExpectedMinute, const unsigned int uExpectedSecond)
{
    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;

	// [Execution]
    dateTimeToTest.DecomposeTime(uHour, uMinute, uSecond);

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, uExpectedHour);
    BOOST_CHECK_EQUAL(uMinute, uExpectedMinute);
    BOOST_CHECK_EQUAL(uSecond, uExpectedSecond);
}

/// <summary>
/// This method has been created to improve some tests' maintainability. Concretely, this method performs tests for DecomposeTime2.
/// </summary>
void CheckDecomposeTime2_UtilityMethod(const DateTime &dateTimeToTest, const unsigned int uExpectedHour, const unsigned int uExpectedMinute, const unsigned int uExpectedSecond, 
                                                                        const unsigned int uExpectedMillisecond, const unsigned int uExpectedMicrosecond, const unsigned int uExpectedHundredOfNanosecond)
{
    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;
    unsigned int uMillisecond = 0;
    unsigned int uMicrosecond = 0;
    unsigned int uHundredOfNanosecond = 0;

	// [Execution]
    dateTimeToTest.DecomposeTime(uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond);

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, uExpectedHour);
    BOOST_CHECK_EQUAL(uMinute, uExpectedMinute);
    BOOST_CHECK_EQUAL(uSecond, uExpectedSecond);
    BOOST_CHECK_EQUAL(uMillisecond, uExpectedMillisecond);
    BOOST_CHECK_EQUAL(uMicrosecond, uExpectedMicrosecond);
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, uExpectedHundredOfNanosecond);
}

/// <summary>
/// Checks that the default value is an undefined date.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValueIsUndefined_Test )
{
    // [Preparation]

	// [Execution]
    DateTime dateTime;

    // [Verification]
    BOOST_CHECK(dateTime == DateTime::GetUndefinedDate());
}

/// <summary>
/// Checks that the date and time is copied correctly.
/// </summary>
ZTEST_CASE ( Constructor2_DateTimeIsCorrectlyCopied_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 2;
    const u64_z EXPECTED_HOUR        = 3;
    const u64_z EXPECTED_MINUTE      = 4;
    const u64_z EXPECTED_SECOND      = 5;
    const u64_z EXPECTED_MILLISECOND = 666;
    const u64_z EXPECTED_MICROSECOND = 777;
    const u64_z EXPECTED_HNS         = 8;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const DateTime ORIGINAL_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);

    // [Verification]
    BOOST_CHECK(dateTime == ORIGINAL_DATETIME);
    BOOST_CHECK(dateTime.GetTimeZone() == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the undefined date and time is copied.
/// </summary>
ZTEST_CASE ( Constructor2_UndefinedDateTimeIsCopied_Test )
{
    // [Preparation]
    const DateTime EXPECTED_VALUE = DateTime::GetUndefinedDate();

	// [Execution]
    DateTime dateTime(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 11;
    const u64_z EXPECTED_DAY         = 13;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Canary"));

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the time zone is null.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndNullTimeZone_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 11;
    const u64_z EXPECTED_DAY         = 13;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is positive.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsPositive_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 11;
    const u64_z EXPECTED_DAY         = 13;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* POSITIVE_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       POSITIVE_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), POSITIVE_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common date and time and the offset of the time zone is negative.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingCommonDateAndTimeAndTimeZoneOffsetIsNegative_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 11;
    const u64_z EXPECTED_DAY         = 13;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* NEGATIVE_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       NEGATIVE_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), NEGATIVE_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
ZTEST_CASE ( Constructor3_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 11;
    const u64_z EXPECTED_DAY         = 13;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS, TimeZone::UTC);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the year is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenYearIsTooHigh_Test )
{
    // [Preparation]
    const u64_z NOT_ALLOWED_YEAR   = 30000;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year is lower than the minimum allowed.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenYearIsTooLow_Test )
{
    // [Preparation]
    const i32_z NOT_ALLOWED_YEAR   = -30000;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year equals zero.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    const i32_z YEAR_ZERO          = 0;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(YEAR_ZERO, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenMonthIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z NOT_ALLOWED_MONTH  = 13;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, NOT_ALLOWED_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month equals zero.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenMonthEqualsZero_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z MONTH_ZERO         = 0;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, MONTH_ZERO, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenDayIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z NOT_ALLOWED_DAY    = 32;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day equals zero.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenDayEqualsZero_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z DAY_ZERO           = 0;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, DAY_ZERO,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input day is not valid for the provided input month and year.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenDayIsNotValidForTheGivenMonthAndYear_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 2;
    const u64_z NOT_ALLOWED_DAY    = 30;
    const u64_z COMMON_HOUR        = 10;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenHourIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z NOT_ALLOWED_HOUR   = 24;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenMinuteIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 12;
    const u64_z NOT_ALLOWED_MINUTE = 60;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenSecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 12;
    const u64_z COMMON_MINUTE      = 50;
    const u64_z NOT_ALLOWED_SECOND = 60;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenMillisecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR             = 2013;
    const u64_z COMMON_MONTH            = 11;
    const u64_z COMMON_DAY              = 13;
    const u64_z COMMON_HOUR             = 12;
    const u64_z COMMON_MINUTE           = 50;
    const u64_z COMMON_SECOND           = 52;
    const u64_z NOT_ALLOWED_MILLISECOND = 1000;
    const u64_z COMMON_MICROSECOND      = 489;
    const u64_z COMMON_HNS              = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the microsecond is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenMicrosecondIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR             = 2013;
    const u64_z COMMON_MONTH            = 11;
    const u64_z COMMON_DAY              = 13;
    const u64_z COMMON_HOUR             = 12;
    const u64_z COMMON_MINUTE           = 50;
    const u64_z COMMON_SECOND           = 52;
    const u64_z COMMON_MILLISECOND      = 546;
    const u64_z NOT_ALLOWED_MICROSECOND = 1000;
    const u64_z COMMON_HNS              = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, NOT_ALLOWED_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hundred of nanoseconds is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenHundredsOfNanosecondsIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR        = 2013;
    const u64_z COMMON_MONTH       = 11;
    const u64_z COMMON_DAY         = 13;
    const u64_z COMMON_HOUR        = 12;
    const u64_z COMMON_MINUTE      = 50;
    const u64_z COMMON_SECOND      = 52;
    const u64_z COMMON_MILLISECOND = 546;
    const u64_z COMMON_MICROSECOND = 256;
    const u64_z NOT_ALLOWED_HNS    = 10;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, NOT_ALLOWED_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is posterior to maximum.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_z MAX_YEAR        = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH       = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY         = DateTime::GetMaxDateTime().GetDay();
    const u64_z MAX_HOUR        = DateTime::GetMaxDateTime().GetHour();
    const u64_z MAX_MINUTE      = DateTime::GetMaxDateTime().GetMinute();
    const u64_z MAX_SECOND      = DateTime::GetMaxDateTime().GetSecond();
    const u64_z MAX_MILLISECOND = DateTime::GetMaxDateTime().GetMillisecond();
    const u64_z MAX_MICROSECOND = DateTime::GetMaxDateTime().GetMicrosecond();
    const u64_z MAX_HNS         = DateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MAX_HNS_PLUS_ONE = MAX_HNS + 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                           MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                           MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS_PLUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_z MIN_YEAR        = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH       = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY         = DateTime::GetMinDateTime().GetDay();
    const u64_z MIN_HOUR        = DateTime::GetMinDateTime().GetHour();
    const u64_z MIN_MINUTE      = DateTime::GetMinDateTime().GetMinute();
    const u64_z MIN_SECOND      = DateTime::GetMinDateTime().GetSecond();
    const u64_z MIN_MILLISECOND = DateTime::GetMinDateTime().GetMillisecond();
    const u64_z MIN_MICROSECOND = DateTime::GetMinDateTime().GetMicrosecond();
    const u64_z MIN_HNS         = DateTime::GetMinDateTime().GetHundredOfNanosecond();
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MIN_HNS_MINUS_ONE = MIN_HNS - 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(-MIN_YEAR, MIN_MONTH, MIN_DAY,
                           MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                           MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS_MINUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
ZTEST_CASE ( Constructor3_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_z MAX_YEAR        = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH       = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY         = DateTime::GetMaxDateTime().GetDay();
    const u64_z MAX_HOUR        = DateTime::GetMaxDateTime().GetHour();
    const u64_z MAX_MINUTE      = DateTime::GetMaxDateTime().GetMinute();
    const u64_z MAX_SECOND      = DateTime::GetMaxDateTime().GetSecond();
    const u64_z MAX_MILLISECOND = DateTime::GetMaxDateTime().GetMillisecond();
    const u64_z MAX_MICROSECOND = DateTime::GetMaxDateTime().GetMicrosecond();
    const u64_z MAX_HNS         = DateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MAX_HNS_PLUS_ONE = MAX_HNS + 1;
    const DateTime MAX_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    DateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MAX_DATETIME);
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
ZTEST_CASE ( Constructor3_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_z MIN_YEAR        = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH       = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY         = DateTime::GetMinDateTime().GetDay();
    const u64_z MIN_HOUR        = DateTime::GetMinDateTime().GetHour();
    const u64_z MIN_MINUTE      = DateTime::GetMinDateTime().GetMinute();
    const u64_z MIN_SECOND      = DateTime::GetMinDateTime().GetSecond();
    const u64_z MIN_MILLISECOND = DateTime::GetMinDateTime().GetMillisecond();
    const u64_z MIN_MICROSECOND = DateTime::GetMinDateTime().GetMicrosecond();
    const u64_z MIN_HNS         = DateTime::GetMinDateTime().GetHundredOfNanosecond();
    const TimeZone* MIN_TIMEZONE = null_z;
    const u64_z MIN_HNS_MINUS_ONE = MIN_HNS - 1;
    const DateTime MIN_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    DateTime dateTime(-scast_z(MIN_YEAR, i32_z), MIN_MONTH, MIN_DAY,
                       MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                       MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS_MINUS_ONE,
                       MIN_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 1;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -1;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 25;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -25;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 20;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 29;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -20;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 29;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 20;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 28;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -20;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 28;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -1;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 12;
    const u64_z EXPECTED_DAY         = 31;
    const u64_z EXPECTED_HOUR        = 23;
    const u64_z EXPECTED_MINUTE      = 59;
    const u64_z EXPECTED_SECOND      = 59;
    const u64_z EXPECTED_MILLISECOND = 999;
    const u64_z EXPECTED_MICROSECOND = 999;
    const u64_z EXPECTED_HNS         = 9;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 1;
    const u64_z EXPECTED_MONTH       = 12;
    const u64_z EXPECTED_DAY         = 31;
    const u64_z EXPECTED_HOUR        = 23;
    const u64_z EXPECTED_MINUTE      = 59;
    const u64_z EXPECTED_SECOND      = 59;
    const u64_z EXPECTED_MILLISECOND = 999;
    const u64_z EXPECTED_MICROSECOND = 999;
    const u64_z EXPECTED_HNS         = 9;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 12;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -12;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(NEGATIVE_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const u64_z EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(NEGATIVE_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 23;
    const u64_z EXPECTED_MINUTE      = 59;
    const u64_z EXPECTED_SECOND      = 59;
    const u64_z EXPECTED_MILLISECOND = 999;
    const u64_z EXPECTED_MICROSECOND = 999;
    const u64_z EXPECTED_HNS         = 9;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 12;
    const u64_z EXPECTED_DAY         = 31;
    const u64_z EXPECTED_HOUR        = 23;
    const u64_z EXPECTED_MINUTE      = 59;
    const u64_z EXPECTED_SECOND      = 59;
    const u64_z EXPECTED_MILLISECOND = 999;
    const u64_z EXPECTED_MICROSECOND = 999;
    const u64_z EXPECTED_HNS         = 9;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const u64_z MAX_YEAR        = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH       = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY         = DateTime::GetMaxDateTime().GetDay();
    const u64_z MAX_HOUR        = DateTime::GetMaxDateTime().GetHour();
    const u64_z MAX_MINUTE      = DateTime::GetMaxDateTime().GetMinute();
    const u64_z MAX_SECOND      = DateTime::GetMaxDateTime().GetSecond();
    const u64_z MAX_MILLISECOND = DateTime::GetMaxDateTime().GetMillisecond();
    const u64_z MAX_MICROSECOND = DateTime::GetMaxDateTime().GetMicrosecond();
    const u64_z MAX_HNS         = DateTime::GetMaxDateTime().GetHundredOfNanosecond();
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(scast_z(MAX_YEAR, i32_z), MAX_MONTH, MAX_DAY,
                       MAX_HOUR, MAX_MINUTE, MAX_SECOND,
                       MAX_MILLISECOND, MAX_MICROSECOND, MAX_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MAX_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const u64_z MIN_YEAR        = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH       = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY         = DateTime::GetMinDateTime().GetDay();
    const u64_z MIN_HOUR        = DateTime::GetMinDateTime().GetHour();
    const u64_z MIN_MINUTE      = DateTime::GetMinDateTime().GetMinute();
    const u64_z MIN_SECOND      = DateTime::GetMinDateTime().GetSecond();
    const u64_z MIN_MILLISECOND = DateTime::GetMinDateTime().GetMillisecond();
    const u64_z MIN_MICROSECOND = DateTime::GetMinDateTime().GetMicrosecond();
    const u64_z MIN_HNS         = DateTime::GetMinDateTime().GetHundredOfNanosecond();
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(-scast_z(MIN_YEAR, i32_z), MIN_MONTH, MIN_DAY,
                       MIN_HOUR, MIN_MINUTE, MIN_SECOND,
                       MIN_MILLISECOND, MIN_MICROSECOND, MIN_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MIN_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MIN_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MIN_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MIN_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MIN_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MIN_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MIN_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}


/// <summary>
/// Checks that the instance is correctly constructed from a common date and time.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingCommonDateAndTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR  = 2013;
    const u64_z EXPECTED_MONTH = 11;
    const u64_z EXPECTED_DAY   = 13;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("America/Antigua"));

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
ZTEST_CASE ( Constructor4_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR  = 2013;
    const u64_z EXPECTED_MONTH = 11;
    const u64_z EXPECTED_DAY   = 13;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY, TimeZone::UTC);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the year is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenYearIsTooHigh_Test )
{
    // [Preparation]
    const i32_z NOT_ALLOWED_YEAR = 30000;
    const u64_z COMMON_MONTH     = 11;
    const u64_z COMMON_DAY       = 13;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year is lower than the minimum allowed.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenYearIsTooLow_Test )
{
    // [Preparation]
    const i32_z NOT_ALLOWED_YEAR = -30000;
    const u64_z COMMON_MONTH     = 11;
    const u64_z COMMON_DAY       = 13;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_YEAR, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the year equals zero.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenYearEqualsZero_Test )
{
    // [Preparation]
    const i32_z YEAR_ZERO    = 0;
    const u64_z COMMON_MONTH = 11;
    const u64_z COMMON_DAY   = 13;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(YEAR_ZERO, COMMON_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenMonthIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR       = 2013;
    const u64_z NOT_ALLOWED_MONTH = 13;
    const u64_z COMMON_DAY        = 13;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, NOT_ALLOWED_MONTH, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the month equals zero.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenMonthEqualsZero_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR = 2013;
    const u64_z MONTH_ZERO  = 0;
    const u64_z COMMON_DAY  = 13;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, MONTH_ZERO, COMMON_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenDayIsTooHigh_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR     = 2013;
    const u64_z COMMON_MONTH    = 11;
    const u64_z NOT_ALLOWED_DAY = 32;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the day equals zero.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenDayEqualsZero_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR  = 2013;
    const u64_z COMMON_MONTH = 11;
    const u64_z DAY_ZERO     = 0;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, DAY_ZERO,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when input day is not valid for the provided input month and year.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenDayIsNotValidForTheGivenMonthAndYear_Test )
{
    // [Preparation]
    const i32_z COMMON_YEAR     = 2013;
    const u64_z COMMON_MONTH    = 2;
    const u64_z NOT_ALLOWED_DAY = 30;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_YEAR, COMMON_MONTH, NOT_ALLOWED_DAY,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is posterior to maximum.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_z MAX_YEAR  = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY   = DateTime::GetMaxDateTime().GetDay();
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MAX_DAY_PLUS_ONE = MAX_DAY + 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY_PLUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the date and time is prior to minimum.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_z MIN_YEAR  = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY   = DateTime::GetMinDateTime().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MIN_DAY_MINUS_ONE = MIN_DAY - 1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(-MIN_YEAR, MIN_MONTH, MIN_DAY_MINUS_ONE,
                           NULL_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the constructed instance has the maximum value when the input date and time is greater than maximum.
/// </summary>
ZTEST_CASE ( Constructor4_MaximumDateIsConstructedWhenDateIsPosteriorToMaximum_Test )
{
    // [Preparation]
    const i32_z MAX_YEAR  = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY   = DateTime::GetMaxDateTime().GetDay();
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MAX_DAY_PLUS_ONE = MAX_DAY + 1;
    const DateTime MAX_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    DateTime dateTime(MAX_YEAR, MAX_MONTH, MAX_DAY_PLUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MAX_DATETIME);
}

/// <summary>
/// Checks that the constructed instance has the minimum value when the input date and time is lower than minimum.
/// </summary>
ZTEST_CASE ( Constructor4_MinimumDateIsConstructedWhenDateIsAnteriorToMinimum_Test )
{
    // [Preparation]
    const i32_z MIN_YEAR  = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY   = DateTime::GetMinDateTime().GetDay() + 1; // (time is 00:00:00, which would be prior to minimum, so next day is used)
    const TimeZone* NULL_TIMEZONE = null_z;
    const u64_z MIN_DAY_MINUS_ONE = MIN_DAY - 1;
    const DateTime MIN_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    DateTime dateTime(-scast_z(MIN_YEAR, i32_z), MIN_MONTH, MIN_DAY_MINUS_ONE,
                       NULL_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == MIN_DATETIME);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 1;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -1;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 25;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -25;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 20;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 29;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -20;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 29;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 20;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 28;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -20;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 2;
    const u64_z EXPECTED_DAY         = 28;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 12;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -12;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is 004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 4;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is -004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const i32_z NEGATIVE_YEAR        = -4;
    const unsigned int EXPECTED_YEAR = -NEGATIVE_YEAR;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 0;
    const u64_z EXPECTED_MINUTE      = 0;
    const u64_z EXPECTED_SECOND      = 0;
    const u64_z EXPECTED_MILLISECOND = 0;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const u64_z MAX_YEAR        = DateTime::GetMaxDateTime().GetYear();
    const u64_z MAX_MONTH       = DateTime::GetMaxDateTime().GetMonth();
    const u64_z MAX_DAY         = DateTime::GetMaxDateTime().GetDay();
    const u64_z MAX_HOUR        = 0;
    const u64_z MAX_MINUTE      = 0;
    const u64_z MAX_SECOND      = 0;
    const u64_z MAX_MILLISECOND = 0;
    const u64_z MAX_MICROSECOND = 0;
    const u64_z MAX_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(scast_z(MAX_YEAR, i32_z), MAX_MONTH, MAX_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MAX_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MAX_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MAX_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MAX_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MAX_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MAX_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MAX_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MAX_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MAX_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyConstructedWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const u64_z MIN_YEAR        = DateTime::GetMinDateTime().GetYear();
    const u64_z MIN_MONTH       = DateTime::GetMinDateTime().GetMonth();
    const u64_z MIN_DAY         = DateTime::GetMinDateTime().GetDay() + 1;
    const u64_z MIN_HOUR        = 0;
    const u64_z MIN_MINUTE      = 0;
    const u64_z MIN_SECOND      = 0;
    const u64_z MIN_MILLISECOND = 0;
    const u64_z MIN_MICROSECOND = 0;
    const u64_z MIN_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(-scast_z(MIN_YEAR, i32_z), MIN_MONTH, MIN_DAY,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), MIN_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), MIN_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), MIN_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), MIN_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), MIN_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), MIN_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), MIN_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), MIN_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), MIN_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the instance is correctly constructed from a common time.
/// </summary>
ZTEST_CASE ( Constructor5_IsCorrectlyConstructedWhenUsingCommonTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 1;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("America/Antigua"));

	// [Execution]
    DateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
ZTEST_CASE ( Constructor5_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 489;
    const u64_z EXPECTED_HNS         = 5;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS, TimeZone::UTC);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenHourTooHigh_Test )
{
    // [Preparation]
    const u64_z NOT_ALLOWED_HOUR   = 24;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenMinuteTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR        = 12;
    const u64_z NOT_ALLOWED_MINUTE = 60;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenSecondTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR        = 12;
    const u64_z COMMON_MINUTE      = 50;
    const u64_z NOT_ALLOWED_SECOND = 60;
    const u64_z COMMON_MILLISECOND = 654;
    const u64_z COMMON_MICROSECOND = 489;
    const u64_z COMMON_HNS         = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenMillisecondTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR             = 12;
    const u64_z COMMON_MINUTE           = 50;
    const u64_z COMMON_SECOND           = 52;
    const u64_z NOT_ALLOWED_MILLISECOND = 1000;
    const u64_z COMMON_MICROSECOND      = 489;
    const u64_z COMMON_HNS              = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND, COMMON_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the microsecond is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenMicrosecondTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR             = 12;
    const u64_z COMMON_MINUTE           = 50;
    const u64_z COMMON_SECOND           = 52;
    const u64_z COMMON_MILLISECOND      = 546;
    const u64_z NOT_ALLOWED_MICROSECOND = 1000;
    const u64_z COMMON_HNS              = 5;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, NOT_ALLOWED_MICROSECOND, COMMON_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the hundred of nanoseconds is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenHundredsOfNanosecondsTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR        = 12;
    const u64_z COMMON_MINUTE      = 50;
    const u64_z COMMON_SECOND      = 52;
    const u64_z COMMON_MILLISECOND = 546;
    const u64_z COMMON_MICROSECOND = 256;
    const u64_z NOT_ALLOWED_HNS    = 10;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND, COMMON_MICROSECOND, NOT_ALLOWED_HNS,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed from a common time.
/// </summary>
ZTEST_CASE ( Constructor6_IsCorrectlyConstructedWhenUsingCommonTime_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 1;
    const u64_z EXPECTED_MONTH       = 1;
    const u64_z EXPECTED_DAY         = 1;
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const u64_z EXPECTED_MICROSECOND = 0;
    const u64_z EXPECTED_HNS         = 0;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("America/Antigua"));

	// [Execution]
    DateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND,
                       EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetYear(), EXPECTED_YEAR);
    BOOST_CHECK_EQUAL(dateTime.GetMonth(), EXPECTED_MONTH);
    BOOST_CHECK_EQUAL(dateTime.GetDay(), EXPECTED_DAY);
    BOOST_CHECK_EQUAL(dateTime.GetHour(), EXPECTED_HOUR);
    BOOST_CHECK_EQUAL(dateTime.GetMinute(), EXPECTED_MINUTE);
    BOOST_CHECK_EQUAL(dateTime.GetSecond(), EXPECTED_SECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMillisecond(), EXPECTED_MILLISECOND);
    BOOST_CHECK_EQUAL(dateTime.GetMicrosecond(), EXPECTED_MICROSECOND);
    BOOST_CHECK_EQUAL(dateTime.GetHundredOfNanosecond(), EXPECTED_HNS);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the default value of the time zone is null.
/// </summary>
ZTEST_CASE ( Constructor6_TimeZoneDefaultValueIsNull_Test )
{
    // [Preparation]
    const u64_z EXPECTED_HOUR        = 10;
    const u64_z EXPECTED_MINUTE      = 32;
    const u64_z EXPECTED_SECOND      = 23;
    const u64_z EXPECTED_MILLISECOND = 654;
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime dateTime(EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                       EXPECTED_MILLISECOND, TimeZone::UTC);

    // [Verification]
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the hour is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenHourIsTooHigh_Test )
{
    // [Preparation]
    const u64_z NOT_ALLOWED_HOUR   = 24;
    const u64_z COMMON_MINUTE      = 32;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(NOT_ALLOWED_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the minute is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenMinuteIsTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR        = 12;
    const u64_z NOT_ALLOWED_MINUTE = 60;
    const u64_z COMMON_SECOND      = 23;
    const u64_z COMMON_MILLISECOND = 654;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, NOT_ALLOWED_MINUTE, COMMON_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the second is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenSecondIsTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR        = 12;
    const u64_z COMMON_MINUTE      = 50;
    const u64_z NOT_ALLOWED_SECOND = 60;
    const u64_z COMMON_MILLISECOND = 654;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, NOT_ALLOWED_SECOND,
                           COMMON_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the millisecond is greater than the top limit.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenMillisecondIsTooHigh_Test )
{
    // [Preparation]
    const u64_z COMMON_HOUR             = 12;
    const u64_z COMMON_MINUTE           = 50;
    const u64_z COMMON_SECOND           = 52;
    const u64_z NOT_ALLOWED_MILLISECOND = 1000;
    const TimeZone* COMMON_TIMEZONE = null_z;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(COMMON_HOUR, COMMON_MINUTE, COMMON_SECOND,
                           NOT_ALLOWED_MILLISECOND,
                           COMMON_TIMEZONE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the instance is correctly constructed.
/// </summary>
ZTEST_CASE ( Constructor7_InstanceIsCorrectlyConstructed_Test )
{
    // [Preparation]
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const DateTime EXPECTED_DATETIME(1, 2, 3, 4, 5, 6, 7, 8, 9, null_z);

	// [Execution]
    DateTime dateTime(EXPECTED_DATETIME, EXPECTED_TIMEZONE);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
    BOOST_CHECK_EQUAL(dateTime.GetTimeZone(), EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, without year sign, time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNoYearSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1234-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(1234, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with year positive sign but without time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearPositiveSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+1234-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(1234, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with year negative sign but without time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearNegativeSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-1234-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(-1235, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers, and without year sign or time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndNoYearSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers and with year positive sign but without time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndYearPositiveSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+12345-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a year of 5 numbers and with year negative sign but without time fraction or time zone offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithYearOfFiveNumbersAndYearNegativeSignAndNoFractionAndNoTimeZone_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-12345-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(-12346, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("123451223T123456");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:56");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 56, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a positive time offset, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithPositiveTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("123451223T235657+1122");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a positive time offset, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithPositiveTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T23:56:57+11:22");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a negative time offset, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNegativeTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("123451223T123457-1122");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a negative time offset, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithNegativeTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57-11:22");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a time offset and a time fraction, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithTimeOffsetAndFractionUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("123451223T123457.1234567-1122");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with a time offset and a time fraction, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithTimeOffsetAndFractionUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.1234567-11:22");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 23, 56, 57, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 8 numbers.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfEightNumbers_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.12345678");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 7 numbers.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfSevenNumbers_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.1234567");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction of 1 number.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionOfOneNumber_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.1");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 100, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "0000001".
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat0000001_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.0000001");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 0, 0, 1, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "0010023".
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat0010023_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.0010023");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 1, 2, 3, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with fraction with format "1002003".
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithFractionWithFormat1002003_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.1002003");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 100, 200, 3, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp combines a date and a time, with Zulu time.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCombinesDateAndTimeWithZuluTime_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-12-23T12:34:57.1234567Z");
    const DateTime EXPECTED_DATETIME(12345, 12, 23, 12, 34, 57, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year +0000 means 1 BC.
/// </summary>
ZTEST_CASE ( Constructor8_PositiveYear0000Means1BC_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-0000-12-23T12:34:57");
    const DateTime EXPECTED_DATETIME(-1, 12, 23, 12, 34, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year -0000 means 1 BC.
/// </summary>
ZTEST_CASE ( Constructor8_NegativeYear0000Means1BC_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-0000-12-23T12:34:57");
    const DateTime EXPECTED_DATETIME(-1, 12, 23, 12, 34, 57, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00.
/// </summary>
ZTEST_CASE ( Constructor8_Hour24Means00_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1234-12-23T24:00:00");
    const DateTime EXPECTED_DATETIME(1234, 12, 23, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the negative time offset affects the date.
/// </summary>
ZTEST_CASE ( Constructor8_NegativeTimeOffsetAffectsTheDate_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1234-12-23T23:00:00-03:00");
    const DateTime EXPECTED_DATETIME(1234, 12, 24, 2, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the positive time offset affects the date.
/// </summary>
ZTEST_CASE ( Constructor8_PositiveTimeOffsetAffectsTheDate_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1234-12-23T01:00:00+03:00");
    const DateTime EXPECTED_DATETIME(1234, 12, 22, 22, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 4 numbers with a positive sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithPositiveSign_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+1234");
    const DateTime EXPECTED_DATETIME(1234, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 4 numbers with a negative sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithNegativeSign_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-1234");
    const DateTime EXPECTED_DATETIME(-1235, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 5 numbers with a positive sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFiveNumbersWithPositiveSign_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+12345");
    const DateTime EXPECTED_DATETIME(12345, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a year of 5 numbers with a negative sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFiveNumbersWithNegativeSign_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-12345");
    const DateTime EXPECTED_DATETIME(-12346, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 5 numbers without sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfDateWithYearOfFiveNumbersWithoutSignUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("12345-09-15");
    const DateTime EXPECTED_DATETIME(12345, 9, 15, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers without sign.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfDateWithYearOfFourNumbersWithoutSignUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1234-09-15");
    const DateTime EXPECTED_DATETIME(1234, 9, 15, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers with positive sign and month and day, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithPositiveSignAndMonthAndDayUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+12341223");
    const DateTime EXPECTED_DATETIME(1234, 12, 23, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of a date with a year of 4 numbers with negative sign and month and day, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfYearOfFourNumbersWithNegativeSignAndMonthAndDayUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-12341223");
    const DateTime EXPECTED_DATETIME(-1235, 12, 23, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year +0000 is the year 1 BC.
/// </summary>
ZTEST_CASE ( Constructor8_PositiveYear0000Means1BCWhenTimestampIsCompoundOfDateOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("+00001223");
    const DateTime EXPECTED_DATETIME(-1, 12, 23, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the year -0000 is the year 1 BC.
/// </summary>
ZTEST_CASE ( Constructor8_NegativeYear0000Means1BCWhenTimestampIsCompoundOfDateOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("-00001223");
    const DateTime EXPECTED_DATETIME(-1, 12, 23, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour only.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1357");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("135748");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour only with time offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourOnlyWithTimeOffset_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13+0130");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 11, 30, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only with time offset, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyWithTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("1357+0130");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only with time offset, using basic format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyWithTimeOffsetUsingBasicFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("135748+0130");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute only with time offset, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteOnlyWithTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57+01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of hour and minute and second only with time offset, using extended format.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfHourAndMinuteAndSecondOnlyWithTimeOffsetUsingExtendedFormat_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48+01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 12, 27, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset composed of hour only.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48+01");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 12, 57, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with negative time offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithNegativeTimeOffset_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with fraction but without time offset.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithFractionWithoutTimeOffset_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.1234567");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 7 numbers.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfSevenNumbers_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.1234567-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 8 numbers.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfEightNumbers_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.12345678-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 123, 456, 7, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction of 1 number.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionOfOneNumber_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.1-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 100, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction like "0000001".
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionLike0000001_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.0000001-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 0, 0, 1, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with time offset and fraction like "1002003".
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithTimeOffsetAndFractionLike0010023_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.1002003-01:30");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 15, 27, 48, 100, 200, 3, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with fraction and Zulu Time.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithFractionAndZuluTime_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48.1234Z");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 123, 400, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the expected instance is created when the input timestamp is composed of time with Zulu Time.
/// </summary>
ZTEST_CASE ( Constructor8_CreatesExpectedInstanceWhenTimestampCompoundOfTimeWithZuluTime_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("13:57:48Z");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 13, 57, 48, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour only.
/// </summary>
ZTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("24");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour and the minute only.
/// </summary>
ZTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourAndMinuteOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("24:00");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the hour 24 means 00 when the timestamp is composed of the hour, the minute and the second.
/// </summary>
ZTEST_CASE ( Constructor8_Hour24Means00WhenTimeIsCompoundOfHourAndMinuteAndSecond_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("240000");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the negative time offset does not affect the date when the timestamp is composed of time only.
/// </summary>
ZTEST_CASE ( Constructor8_NegativeTimeOffsetDoesNotAffectTheDateWhenTimestampIsCompoundOfTimeOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("23:00:00-03:00");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 2, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the positive time offset does not affect the date when the timestamp is composed of time only.
/// </summary>
ZTEST_CASE ( Constructor8_PositiveTimeOffsetDoesNotAffectTheDateWhenTimestampIsCompoundOfTimeOnly_Test )
{
    // [Preparation]
    const string_z TIMESTAMP("01:00:00+03:00");
    const DateTime EXPECTED_DATETIME(1, 1, 1, 22, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    DateTime dateTime(TIMESTAMP);

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input string is empty.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenInputStringIsEmpty_Test )
{
    // [Preparation]
    const string_z EMPTY_TIMESTAMP;
    const bool ASSERTION_FAILED = true;


	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(EMPTY_TIMESTAMP);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input string contains whitespaces.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenInputStringContainsWhitesSpaces_Test )
{
    // [Preparation]
    const string_z TIMESTAMP = "2000-12-13 10:20:33";
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(TIMESTAMP);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the input date and time are correctly copied.
/// </summary>
ZTEST_CASE ( OperatorAssignation_InputDateTimeIsCorrectlyCopied_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR        = 2013;
    const u64_z EXPECTED_MONTH       = 5;
    const u64_z EXPECTED_DAY         = 2;
    const u64_z EXPECTED_HOUR        = 3;
    const u64_z EXPECTED_MINUTE      = 4;
    const u64_z EXPECTED_SECOND      = 5;
    const u64_z EXPECTED_MILLISECOND = 666;
    const u64_z EXPECTED_MICROSECOND = 777;
    const u64_z EXPECTED_HNS         = 8;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const DateTime EXPECTED_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_HOUR, EXPECTED_MINUTE, EXPECTED_SECOND,
                                      EXPECTED_MILLISECOND, EXPECTED_MICROSECOND, EXPECTED_HNS,
                                      EXPECTED_TIMEZONE);

	// [Execution]
    DateTime dateTime;
    dateTime = EXPECTED_DATETIME;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
    BOOST_CHECK(dateTime.GetTimeZone() == EXPECTED_DATETIME.GetTimeZone());
}

/// <summary>
/// Checks that undefined dates are copied.
/// </summary>
ZTEST_CASE ( OperatorAssignment_UndefinedDateIsCopied_Test )
{
    // [Preparation]
    const u64_z EXPECTED_YEAR  = 2013;
    const u64_z EXPECTED_MONTH = 5;
    const u64_z EXPECTED_DAY   = 2;
    const TimeZone* EXPECTED_TIMEZONE = null_z;
    const DateTime ORIGINAL_DATETIME(EXPECTED_YEAR, EXPECTED_MONTH, EXPECTED_DAY,
                                      EXPECTED_TIMEZONE);
    const DateTime UNDEFINED_DATETIME(DateTime::GetUndefinedDate());

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime = UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a positive date.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedToPositiveDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a negative date.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedToNegativeDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the operator returns the resident value.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_ReturnsResidentValue_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    DateTime& returnedValue = (dateTime += INPUT_TIMESPAN);

    // [Verification]
    BOOST_CHECK(&dateTime == &returnedValue);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZero_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero (time span greater than 1 year).
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const DateTime EXPECTED_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(UNDEFINED_DATETIME);
        dateTime += ANY_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the sum exceeds the maximum date.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_AssertionFailsWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_DATETIME = DateTime::GetMaxDateTime();
    const TimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(MAXIMUM_DATETIME);
        dateTime += INPUT_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_UndefinedDatesDoNotChange_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);

	// [Execution]
    DateTime dateTime(UNDEFINED_DATETIME);
    dateTime += ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the maximum value when the result of the sum is greater than the maximum.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignment_MaximumValueIsSetWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_DATETIME = DateTime::GetMaxDateTime();
    const TimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    DateTime dateTime(MAXIMUM_DATETIME);
    dateTime += INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MAXIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly subtracted to a positive date.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedToPositiveDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly subtracted to a negative date.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedToNegativeDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that the operator returns the resident value.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_ReturnsResidentValue_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    DateTime& returnedValue = (dateTime -= INPUT_TIMESPAN);

    // [Verification]
    BOOST_CHECK(&dateTime == &returnedValue);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZero_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero (time span greater than 1 year).
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const DateTime EXPECTED_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime(ORIGINAL_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(UNDEFINED_DATETIME);
        dateTime -= ANY_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the subtraction exceeds the minimum date.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_AssertionFailsWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    // [Preparation]
    const DateTime MINIMUM_DATETIME = DateTime::GetMinDateTime();
    const TimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime dateTime(MINIMUM_DATETIME);
        dateTime -= INPUT_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_UndefinedDatesDoNotChange_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);

	// [Execution]
    DateTime dateTime(UNDEFINED_DATETIME);
    dateTime -= ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the minimum value when the result of the subtraction is lower than the minimum.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignment_MinimumValueIsSetWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    // [Preparation]
    const DateTime MINIMUM_DATETIME = DateTime::GetMinDateTime();
    const TimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    DateTime dateTime(MINIMUM_DATETIME);
    dateTime -= INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MINIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly added to a positive date.
/// </summary>
ZTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedToPositiveDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly added to a negative date.
/// </summary>
ZTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedToNegativeDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero.
/// </summary>
ZTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZero_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly added when passing through the year zero (time span greater than 1 year).
/// </summary>
ZTEST_CASE ( OperatorAddition_CommonTimeSpanIsCorrectlyAddedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const DateTime EXPECTED_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
ZTEST_CASE ( OperatorAddition_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME + ANY_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the sum exceeds the maximum date.
/// </summary>
ZTEST_CASE ( OperatorAddition_AssertionFailsWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_DATETIME = DateTime::GetMaxDateTime();
    const TimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        MAXIMUM_DATETIME + INPUT_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
ZTEST_CASE ( OperatorAddition_UndefinedDatesDoNotChange_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);

	// [Execution]
    DateTime dateTime = UNDEFINED_DATETIME + ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the maximum value when the result of the sum is greater than the maximum.
/// </summary>
ZTEST_CASE ( OperatorAddition_MaximumValueIsSetWhenAdditionOverflowsAllowedMaximumValue_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_DATETIME = DateTime::GetMaxDateTime();
    const TimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    DateTime dateTime = MAXIMUM_DATETIME + INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MAXIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that a common time span is correctly subtracted to a positive date.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedToPositiveDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(           2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a common time span is correctly subtracted to a negative date.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedToNegativeDate_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME(-100, 1, 5, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-100, 1, 3, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZero_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME( 1,  1,  1, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(            2, 2, 2,  2,   2,   2, 2);
    const DateTime EXPECTED_DATETIME(-1, 12, 30, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

/// <summary>
/// Checks that a time span is correctly subtracted when passing through the year zero (time span greater than 1 year).
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_CommonTimeSpanIsCorrectlySubtractedWhenPassingThroughYearZeroMoreThanOneYear_Test )
{
    // [Preparation]
    const DateTime ORIGINAL_DATETIME( 2, 1,   9, 6, 8, 12, 102, 202, 7, null_z);
    const TimeSpan INPUT_TIMESPAN(          740, 2, 2,  2,   2,   2, 2); // +2 years
    const DateTime EXPECTED_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);

	// [Execution]
    DateTime dateTime = ORIGINAL_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == EXPECTED_DATETIME);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the resident date is undefined.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME - ANY_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the result of the subtraction exceeds the minimum date.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_AssertionFailsWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    // [Preparation]
    const DateTime MINIMUM_DATETIME = DateTime::GetMinDateTime();
    const TimeSpan INPUT_TIMESPAN(1);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        MINIMUM_DATETIME - INPUT_TIMESPAN;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that undefined dates do not change.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_UndefinedDatesDoNotChange_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const TimeSpan ANY_TIMESPAN(1);

	// [Execution]
    DateTime dateTime = UNDEFINED_DATETIME - ANY_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == UNDEFINED_DATETIME);
}

/// <summary>
/// Checks that the result is the minimum value when the result of the subtraction is lower than the minimum.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_MinimumValueIsSetWhenSubtractionOverflowsAllowedMinimumValue_Test )
{
    // [Preparation]
    const DateTime MINIMUM_DATETIME = DateTime::GetMinDateTime();
    const TimeSpan INPUT_TIMESPAN(1);

	// [Execution]
    DateTime dateTime = MINIMUM_DATETIME - INPUT_TIMESPAN;

    // [Verification]
    BOOST_CHECK(dateTime == MINIMUM_DATETIME);
}

#endif

/// <summary>
/// Checks that it returns the expected result when subtracting a negative date to a positive date. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingNegativeDateToPositiveDate_Test )
{
    // [Preparation]
    const DateTime LEFT_DATETIME(  2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime RIGHT_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan EXPECTED_TIMESPAN(    740, 2, 2,  2,   2,   2, 2); // +2 years

	// [Execution]
    TimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting a positive date to a negative date. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingPositiveDateToNegativeDate_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME(-2, 12, 30, 4, 6, 10, 100, 200, 5, null_z);
    const TimeSpan EXPECTED_TIMESPAN(   740, 2, 2,  2,   2,   2, 2); // +2 years

	// [Execution]
    TimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns zero when operands are equal. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsZeroWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME(RIGHT_DATETIME);
    const TimeSpan EXPECTED_TIMESPAN(0);

	// [Execution]
    TimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting positive dates. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 2,  1,  9, 7, 9, 16, 102, 202, 7, null_z);
    const TimeSpan EXPECTED_TIMESPAN(     0, 1, 1,  4,   0,   0, 0);

	// [Execution]
    TimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

/// <summary>
/// Checks that it returns the expected result when subtracting negative dates. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsExpectedTimeSpanWhenSubtractingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 7, 9, 16, 102, 202, 7, null_z);
    const TimeSpan EXPECTED_TIMESPAN(      0, 1, 1,  4,   0,   0, 0);

	// [Execution]
    TimeSpan result = LEFT_DATETIME - RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK(result == EXPECTED_TIMESPAN);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_AssertionFailsWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME - ANY_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME - UNDEFINED_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns zero when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_ReturnsZeroWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const TimeSpan ZERO_TIMESPAN(0);

	// [Execution]
    TimeSpan result1 = UNDEFINED_DATETIME - ANY_DATETIME;
    TimeSpan result2 = ANY_DATETIME - UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK(result1 == ZERO_TIMESPAN);
    BOOST_CHECK(result2 == ZERO_TIMESPAN);
}

#endif

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_TimeZoneDoesNotAffectTheResult_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 9, 16, 102, 202, 7, null_z);
    const TimeSpan EXPECTED_TIMESPAN(         0, 1, 1,  4,   0,   0, 0);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

	// [Execution]
    TimeSpan resultUTC = LEFT_DATETIME_WITH_TIMEZONE - RIGHT_DATETIME_WITH_TIMEZONE;
    TimeSpan resultWithTimeZones = LEFT_DATETIME_WITH_TIMEZONE - RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK(resultUTC == EXPECTED_TIMESPAN);
    BOOST_CHECK(resultUTC == resultWithTimeZones);
}

/// <summary>
/// Checks that it returns True when operands are equal. 
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME == RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal. 
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME == RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorEquality_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE == RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are equal. 
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME != RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are not equal. 
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME != RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorInequality_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE != RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputIsNotLesserThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputIsNotLesserThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME < RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorLowerThan_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE < RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME < ANY_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME < UNDEFINED_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME < ANY_DATETIME;
    bool bResult2 = ANY_DATETIME < UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME > RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE > RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME > ANY_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME > UNDEFINED_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME > ANY_DATETIME;
    bool bResult2 = ANY_DATETIME > UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is less than the resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputIsNotLesserThanOrEqualToResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than the resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputIsNotLesserThanOrEqualToResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is lower than resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputIsLesserThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when dates are equal. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenDatesAreEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME(RIGHT_DATETIME);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME <= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when both dates are undefined. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenBothDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = UNDEFINED_DATETIME <= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE <= RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when only one of the dates is undefined.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenOnlyOneDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME <= ANY_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME <= UNDEFINED_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME <= ANY_DATETIME;
    bool bResult2 = ANY_DATETIME <= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when input operand is greater than or equal to resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input operand is less than or equal to resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputIsNotGreaterThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 1,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing negative dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingNegativeDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(-3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( -2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input operand is greater than resident operand when comparing positive dates. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputIsGreaterThanResidentWhenComparingPositiveDates_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME( 3,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when dates are equal. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenDatesAreEqual_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME(RIGHT_DATETIME);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME >= RIGHT_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when both dates are undefined. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenBothDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = UNDEFINED_DATETIME >= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that time zones do not affect the result. 
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_TimeZonesAreIgnored_Test )
{
    // [Preparation]
    const DateTime RIGHT_DATETIME_UTC(2,  1,  9, 6, 8, 12, 102, 202, 7, null_z);
    const DateTime LEFT_DATETIME_UTC( 2,  1,  9, 7, 8, 12, 102, 202, 7, null_z);

    const TimeZone* pTimeZone1 = STimeZoneFactory::GetTimeZoneById(Z_L("Europe/Madrid"));
    const TimeZone* pTimeZone2 = STimeZoneFactory::GetTimeZoneById(Z_L("America/New_York"));

    const DateTime RIGHT_DATETIME_WITH_TIMEZONE(RIGHT_DATETIME_UTC, pTimeZone1);
    const DateTime LEFT_DATETIME_WITH_TIMEZONE(LEFT_DATETIME_UTC, pTimeZone2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_DATETIME_WITH_TIMEZONE >= RIGHT_DATETIME_WITH_TIMEZONE;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when only one of the dates is undefined.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenOnlyOneDateIsUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        UNDEFINED_DATETIME >= ANY_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        ANY_DATETIME >= UNDEFINED_DATETIME;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that an it returns false when dates are undefined.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenDatesAreUndefined_Test )
{
    // [Preparation]
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const DateTime ANY_DATETIME(1, 1, 1, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = UNDEFINED_DATETIME >= ANY_DATETIME;
    bool bResult2 = ANY_DATETIME >= UNDEFINED_DATETIME;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns the expected number of days for the first month.
/// </summary>
ZTEST_CASE ( GetDaysInMonth_ReturnsExpectedDaysForFirstMonth_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 31;
    const u64_z INPUT_MONTH          = 1;
    const i32_z INPUT_YEAR           = 1;

	// [Execution]
    unsigned int uDays = DateTime::GetDaysInMonth(INPUT_MONTH, INPUT_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns the expected number of days for the last month.
/// </summary>
ZTEST_CASE ( GetDaysInMonth_ReturnsExpectedDaysForLastMonth_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 31;
    const u64_z LAST_MONTH           = 12;
    const i32_z INPUT_YEAR           = 1;

	// [Execution]
    unsigned int uDays = DateTime::GetDaysInMonth(LAST_MONTH, INPUT_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns 29 days when month is February and year is a leap year.
/// </summary>
ZTEST_CASE ( GetDaysInMonth_Returns29DaysWhenMonthIsFebruaryAndYearIsLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 29;
    const u64_z FEBRUARY_MONTH       = 2;
    const i32_z LEAP_YEAR            = 4;

	// [Execution]
    unsigned int uDays = DateTime::GetDaysInMonth(FEBRUARY_MONTH, LEAP_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

/// <summary>
/// Checks that it returns 28 days when month is February and year is not a leap year.
/// </summary>
ZTEST_CASE ( GetDaysInMonth_Returns28DaysWhenMonthIsFebruaryAndYearIsNotLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAYS = 28;
    const u64_z FEBRUARY_MONTH       = 2;
    const i32_z NONLEAP_YEAR         = 1;

	// [Execution]
    unsigned int uDays = DateTime::GetDaysInMonth(FEBRUARY_MONTH, NONLEAP_YEAR);

    // [Verification]
    BOOST_CHECK_EQUAL(uDays, EXPECTED_DAYS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input month is not valid.
/// </summary>
ZTEST_CASE ( GetDaysInMonth_AssertionFailsWhenMonthIsNotValid_Test )
{
    // [Preparation]
    const u64_z NOT_VALID_MONTH = 13;
    const i32_z INPUT_YEAR      = 1;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime::GetDaysInMonth(NOT_VALID_MONTH, INPUT_YEAR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that negative years start at menis zero (1 BC).
/// </summary>
ZTEST_CASE ( ToString_NegativeYearsStartAtMinusZero_Test )
{
    // [Preparation]
    const DateTime DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "-0000-01-01T00:00:00Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp is preceded by a negative sign when the date is negative.
/// </summary>
ZTEST_CASE ( ToString_NegativeSignWhenYearIsNegative_Test )
{
    // [Preparation]
    const DateTime DATETIME(-1234, 1, 1, 0, 0, 0, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "-1233-01-01T00:00:00Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp is preceded by a positive sign when the date is positive.
/// </summary>
ZTEST_CASE ( ToString_PositiveSignWhenYearIsPositive_Test )
{
    // [Preparation]
    const DateTime DATETIME(1234, 1, 1, 0, 0, 0, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "+1234-01-01T00:00:00Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the timestamp ends with a Z when the time is UTC.
/// </summary>
ZTEST_CASE ( ToString_TimestampEndsWithZWhenTimeIsUtc_Test )
{
    // [Preparation]
    const TimeZone* UTC_TZ = null_z;
    const DateTime DATETIME(1234, 2, 11, 13, 14, 25, 0, 0, 0, UTC_TZ);
    const string_z EXPECTED_RESULT = "+1234-02-11T13:14:25Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date and time parts are correctly padded when they are formed by one number.
/// </summary>
ZTEST_CASE ( ToString_DateAndTimePartsAreCorrectlyPaddedWhenTheyAreFormedByOneNumber_Test )
{
    // [Preparation]
    const DateTime DATETIME(3, 2, 1, 4, 5, 6, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "+0003-02-01T04:05:06Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the years formed of five numbers are correctly created.
/// </summary>
ZTEST_CASE ( ToString_YearsOfFiveNumbersAreCorrectlyCreated_Test )
{
    // [Preparation]
    const DateTime DATETIME(12345, 2, 1, 4, 5, 6, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "+12345-02-01T04:05:06Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that only the necessary numbers of the time fraction are added to the timestamp.
/// </summary>
ZTEST_CASE ( ToString_OnlyNecessaryFractionNumbersAreAddedToTimestamp_Test )
{
    // [Preparation]
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 123, 400, 0, null_z);
    const string_z EXPECTED_RESULT = "+0001-01-01T00:00:00.1234Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the fraction with maximum length is correctly created.
/// </summary>
ZTEST_CASE ( ToString_TheMaximumFractionLengthIsCorrectlyCreated_Test )
{
    // [Preparation]
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 123, 456, 7, null_z);
    const string_z EXPECTED_RESULT = "+0001-01-01T00:00:00.1234567Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that no fraction is added when millisecond, microsecond and hundred of nanosecond equal zero.
/// </summary>
ZTEST_CASE ( ToString_NoFractionIsAddedWhenMillisecondMicrosecondAndHundredOfNanosecondEqualZero_Test )
{
    // [Preparation]
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);
    const string_z EXPECTED_RESULT = "+0001-01-01T00:00:00Z";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that positive time offsets are correctly appended.
/// </summary>
ZTEST_CASE ( ToString_PositiveOffsetAreCorrectlyAppended_Test )
{
    // [Preparation]
    const TimeZone* POSITIVE_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Asia/Calcutta")); // IST+5:30
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, POSITIVE_TIMEZONE);
    const string_z EXPECTED_RESULT = "+0001-01-01T00:00:00+05:30";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that negative time offsets are correctly appended.
/// </summary>
ZTEST_CASE ( ToString_NegativeOffsetAreCorrectlyAppended_Test )
{
    // [Preparation]
    const TimeZone* NEGATIVE_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Pacific/Marquesas")); // MART-9:30
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, NEGATIVE_TIMEZONE);
    const string_z EXPECTED_RESULT = "+0001-01-01T00:00:00-09:30";

	// [Execution]
    string_z strTimestamp = DATETIME.ToString();

    // [Verification]
    BOOST_CHECK(strTimestamp == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 5, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 5, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 2, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 2, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 25, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 25, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 20, 2, 29, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 20, 2, 29, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecompose_UtilityMethod(SOURCE_DATETIME, 20, 2, 28, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 20, 2, 28, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 12, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 12, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	CheckDecompose_UtilityMethod(MAXIMUM_POSITIVE_DATETIME, 29228, 9, 14, 2, 48, 5, 477, 580, 7);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	CheckDecompose_UtilityMethod(MAXIMUM_NEGATIVE_DATETIME, 29228, 4, 18, 21, 11, 54, 522, 419, 3);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1996, 1, 1, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1996, 12, 31, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1, 12, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1999, 12, 31, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1999, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 1, 1, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 1, 2, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 3, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 4, 1, 1, 0, 0, 0, 0, 0, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 5, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31, 0, 0, 0, 0, 0, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 1, 1, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 1, 2, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 12, 30, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( Decompose_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecompose_UtilityMethod(SOURCE_DATETIME, 1, 12, 31, 0, 0, 0, 0, 0, 0);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( Decompose_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;
    unsigned int uYear = 0;
    unsigned int uMonth = 0;
    unsigned int uDay = 0;
    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;
    unsigned int uMillisecond = 0;
    unsigned int uMicrosecond = 0;
    unsigned int uHundredOfNanosecond = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.Decompose(uYear, uMonth, uDay, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 5, 1);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 5, 1);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 2, 1);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 2, 1);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 25, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 25, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 20, 2, 29);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 20, 2, 29);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 20, 2, 28);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 20, 2, 28);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 12, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 12, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	CheckDecomposeDate_UtilityMethod(MAXIMUM_POSITIVE_DATETIME, 29228, 9, 14);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	CheckDecomposeDate_UtilityMethod(MAXIMUM_NEGATIVE_DATETIME, 29228, 4, 18);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1996, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1996, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1999, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1999, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 1, 2);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 3, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 4, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 5, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 12, 31);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 2000, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 1, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 1, 2);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 12, 30);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeDate_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeDate_UtilityMethod(SOURCE_DATETIME, 1, 12, 31);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( DecomposeDate_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;
    unsigned int uYear = 0;
    unsigned int uMonth = 0;
    unsigned int uDay = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.DecomposeDate(uYear, uMonth, uDay);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	CheckDecomposeTime1_UtilityMethod(MAXIMUM_POSITIVE_DATETIME, 2, 48, 5);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	CheckDecomposeTime1_UtilityMethod(MAXIMUM_NEGATIVE_DATETIME, 21, 11, 54);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 12, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 23, 59, 59);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime1_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime1_UtilityMethod(SOURCE_DATETIME, 0, 0, 0);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( DecomposeTime1_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.DecomposeTime(uHour, uMinute, uSecond);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

    CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	CheckDecomposeTime2_UtilityMethod(MAXIMUM_POSITIVE_DATETIME, 2, 48, 5, 477, 580, 7);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	CheckDecomposeTime2_UtilityMethod(MAXIMUM_NEGATIVE_DATETIME, 21, 11, 54, 522, 419, 3);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 12, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, 1, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 1);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 23, 59, 59, 999, 999, 9);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( DecomposeTime2_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	CheckDecomposeTime2_UtilityMethod(SOURCE_DATETIME, 0, 0, 0, 0, 0, 0);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( DecomposeTime2_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

    unsigned int uHour = 0;
    unsigned int uMinute = 0;
    unsigned int uSecond = 0;
    unsigned int uMillisecond = 0;
    unsigned int uMicrosecond = 0;
    unsigned int uHundredOfNanosecond = 0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.DecomposeTime(uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns True when the year is a leap year.
/// </summary>
ZTEST_CASE ( IsLeapYear_ReturnsTrueWhenYearIsLeapYear_Test )
{
    // [Preparation]
    const i32_z LEAP_YEAR    = 4;
    const u64_z COMMON_MONTH = 1;
    const u64_z COMMON_DAY   = 2;
    const DateTime ORIGINAL_DATETIME(LEAP_YEAR, COMMON_MONTH, COMMON_DAY, TimeZone::UTC);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ORIGINAL_DATETIME.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the year is not a leap year.
/// </summary>
ZTEST_CASE ( IsLeapYear_ReturnsFalseWhenYearIsNotLeapYear_Test )
{
    // [Preparation]
    const i32_z NONLEAP_YEAR = 100;
    const u64_z COMMON_MONTH = 1;
    const u64_z COMMON_DAY   = 2;
    const DateTime ORIGINAL_DATETIME(NONLEAP_YEAR, COMMON_MONTH, COMMON_DAY, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ORIGINAL_DATETIME.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is calculated using the local time.
/// </summary>
ZTEST_CASE ( IsLeapYear_IsLocalTime_Test )
{
    const bool EXPECTED_RESULT = false;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("America/Santiago")); // CLT-4
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    bool bIsLeapLocal = SOURCE_DATETIME.IsLeapYear();
    bool bIsLeapUtc   = SOURCE_DATETIME_UTC.IsLeapYear();

    // [Verification]
    BOOST_CHECK_EQUAL(bIsLeapLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bIsLeapLocal, bIsLeapUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date is undefined.
/// </summary>
ZTEST_CASE ( IsLeapYear_AssertionFailsWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DateTime::GetUndefinedDate().IsLeapYear();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetTimeZone_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 5, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 5, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 2, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 25;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 25;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 2, 29, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 20;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 2, 28, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 12;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 12;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 29228;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uYear = MAXIMUM_POSITIVE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 29228;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uYear = MAXIMUM_NEGATIVE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1996;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1996;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 1, 1, 12, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1999;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1999;
    const DateTime SOURCE_DATETIME(EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 2, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 3;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 4;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 5;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 2000;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 1, 2, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 30, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetYear_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_YEAR = 1;
    const DateTime SOURCE_DATETIME(-scast_z(EXPECTED_YEAR, int), 12, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uYear = SOURCE_DATETIME.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYear, EXPECTED_YEAR);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
ZTEST_CASE ( GetYear_IsLocalTime_Test )
{
    const unsigned int EXPECTED_YEAR = 13;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(    EXPECTED_YEAR, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    unsigned int uYearLocal = SOURCE_DATETIME.GetYear();
    unsigned int uYearUtc   = SOURCE_DATETIME_UTC.GetYear();

    // [Verification]
    BOOST_CHECK_EQUAL(uYearLocal, EXPECTED_YEAR);
    BOOST_CHECK_NE(uYearLocal, uYearUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined
/// </summary>
ZTEST_CASE ( GetYear_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetYear();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 5;
    const DateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 5;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(1, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(25, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-25, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(20, EXPECTED_MONTH, 29, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(-20, EXPECTED_MONTH, 29, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(20, EXPECTED_MONTH, 28, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 2;
    const DateTime SOURCE_DATETIME(-20, EXPECTED_MONTH, 28, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(1, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(12, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-12, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(4, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 9;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMonth = MAXIMUM_POSITIVE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 4;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMonth = MAXIMUM_NEGATIVE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(1996, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(1996, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(2000, EXPECTED_MONTH, 1, 12, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(1999, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(1999, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 2, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-3, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-4, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-5, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-2000, EXPECTED_MONTH, 1, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 1, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 1;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 2, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 30, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMonth_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const DateTime SOURCE_DATETIME(-1, EXPECTED_MONTH, 31, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMonth = SOURCE_DATETIME.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonth, EXPECTED_MONTH);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
ZTEST_CASE ( GetMonth_IsLocalTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MONTH = 12;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(    12, EXPECTED_MONTH, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    unsigned int uMonthLocal = SOURCE_DATETIME.GetMonth();
    unsigned int uMonthUtc   = SOURCE_DATETIME_UTC.GetMonth();

    // [Verification]
    BOOST_CHECK_EQUAL(uMonthLocal, EXPECTED_MONTH);
    BOOST_CHECK_NE(uMonthLocal, uMonthUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetMonth_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMonth();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(4, 5, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-4, 5, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(4, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-4, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(25, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-25, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 29;
    const DateTime SOURCE_DATETIME(20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 29;
    const DateTime SOURCE_DATETIME(-20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 28;
    const DateTime SOURCE_DATETIME(20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 28;
    const DateTime SOURCE_DATETIME(-20, 2, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(1, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(12, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-12, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(4, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-4, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 14;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uDay = MAXIMUM_POSITIVE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 18;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uDay = MAXIMUM_NEGATIVE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(1996, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(1996, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(2000, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(2000, 1, EXPECTED_DAY, 12, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(1999, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(1999, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 2;
    const DateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-3, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-4, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-5, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-2000, 12, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-2000, 12,EXPECTED_DAY, 0, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-2000, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 1;
    const DateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 23, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 2;
    const DateTime SOURCE_DATETIME(-1, 1, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 30;
    const DateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetDay_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const DateTime SOURCE_DATETIME(-1, 12, EXPECTED_DAY, 0, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uDay = SOURCE_DATETIME.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDay, EXPECTED_DAY);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
ZTEST_CASE ( GetDay_IsLocalTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_DAY = 31;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(    12, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    unsigned int uDayLocal = SOURCE_DATETIME.GetDay();
    unsigned int uDayUtc   = SOURCE_DATETIME_UTC.GetDay();

    // [Verification]
    BOOST_CHECK_EQUAL(uDayLocal, EXPECTED_DAY);
    BOOST_CHECK_NE(uDayLocal, uDayUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetDay_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetDay();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-1, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(1, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(4, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-4, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 2;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uHour = MAXIMUM_POSITIVE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 21;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uHour = MAXIMUM_NEGATIVE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(1996, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 12;
    const DateTime SOURCE_DATETIME(2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(1999, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-4, 1, 2, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-5, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 23;
    const DateTime SOURCE_DATETIME(-1, 1, 1, EXPECTED_HOUR, 59, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHour_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, EXPECTED_HOUR, 0, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uHour = SOURCE_DATETIME.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHour, EXPECTED_HOUR);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
ZTEST_CASE ( GetHour_IsLocalTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HOUR = 1;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(    12, 12, 31, EXPECTED_HOUR, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    unsigned int uHourLocal = SOURCE_DATETIME.GetHour();
    unsigned int uHourUtc   = SOURCE_DATETIME_UTC.GetHour();

    // [Verification]
    BOOST_CHECK_EQUAL(uHourLocal, EXPECTED_HOUR);
    BOOST_CHECK_NE(uHourLocal, uHourUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetHour_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetHour();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 48;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMinute = MAXIMUM_POSITIVE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 11;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMinute = MAXIMUM_NEGATIVE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, EXPECTED_MINUTE, 59, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMinute_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, EXPECTED_MINUTE, 0, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uMinute = SOURCE_DATETIME.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinute, EXPECTED_MINUTE);
}

/// <summary>
/// Checks that it is local time.
/// </summary>
ZTEST_CASE ( GetMinute_IsLocalTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MINUTE = 59;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Pacific/Marquesas")); // MART-9:30
    const DateTime SOURCE_DATETIME(    12, 12, 31, 10, EXPECTED_MINUTE, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    unsigned int uMinuteLocal = SOURCE_DATETIME.GetMinute();
    unsigned int uMinuteUtc   = SOURCE_DATETIME_UTC.GetMinute();

    // [Verification]
    BOOST_CHECK_EQUAL(uMinuteLocal, EXPECTED_MINUTE);
    BOOST_CHECK_NE(uMinuteLocal, uMinuteUtc);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetMinute_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMinute();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is multiple of 5.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 5;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uSecond = MAXIMUM_POSITIVE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 54;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uSecond = MAXIMUM_NEGATIVE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 1, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 59;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, EXPECTED_SECOND, 999, 999, 9, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetSecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_SECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, EXPECTED_SECOND, 0, 0, 0, null_z);

	// [Execution]
    unsigned int uSecond = SOURCE_DATETIME.GetSecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uSecond, EXPECTED_SECOND);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetSecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetSecond();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 477;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMillisecond = MAXIMUM_POSITIVE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 522;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMillisecond = MAXIMUM_NEGATIVE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 1, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 1, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 999;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, EXPECTED_MILLISECOND, 999, 9, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMillisecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MILLISECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, EXPECTED_MILLISECOND, 0, 0, null_z);

	// [Execution]
    unsigned int uMillisecond = SOURCE_DATETIME.GetMillisecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMillisecond, EXPECTED_MILLISECOND);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetMillisecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMillisecond();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 580;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uMicrosecond = MAXIMUM_POSITIVE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 419;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uMicrosecond = MAXIMUM_NEGATIVE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 1, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 1, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 999;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, EXPECTED_MICROSECOND, 9, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetMicrosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_MICROSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, EXPECTED_MICROSECOND, 0, null_z);

	// [Execution]
    unsigned int uMicrosecond = SOURCE_DATETIME.GetMicrosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uMicrosecond, EXPECTED_MICROSECOND);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetMicrosecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetMicrosecond();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 5, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-05-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearAfter29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 5, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 2, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0004-02-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstNegativeLeapYearBefore29FebruaryWithZeroTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 2, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is 0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstPositiveDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(1, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input date and time is -0001-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is positive and multiple of 5.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenYearIsPositiveAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(25, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input year is negative and multiple of 5.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenYearIsNegativeAndMultipleOfFive_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-25, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 29, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 29th of February.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs29February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 29, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a positive leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingPositiveLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(20, 2, 28, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when using a negative leap year and the day 28th of February.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingNegativeLeapYearAndDayIs28February_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-20, 2, 28, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastNegativeInstant_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0001-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(1, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(12, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0012-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-12, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.0.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingFirstInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstPositiveLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(4, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingLastInstantOfFirstNegativeLeapYear_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the maximum date and time allowed.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingMaximumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 7;
    const DateTime MAXIMUM_POSITIVE_DATETIME = DateTime::GetMaxDateTime();

	// [Execution]
    unsigned int uHundredOfNanosecond = MAXIMUM_POSITIVE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is the minimum date and time allowed.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingMinimumDateAndTime_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 3;
    const DateTime MAXIMUM_NEGATIVE_DATETIME = DateTime::GetMinDateTime();

	// [Execution]
    unsigned int uHundredOfNanosecond = MAXIMUM_NEGATIVE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19960101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(1996, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1996-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19961231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(1996, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20001231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 2000-01-01 12:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase20000101T120000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(2000, 1, 1, 12, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is 1999-12-31 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCase19991231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(1999, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-02 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040102T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-4, 1, 2, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0003-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00030101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-3, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0004-01-01 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00040101T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 1;
    const DateTime SOURCE_DATETIME(-4, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0005-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00051231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-5, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 23:59:59.999.999.9..
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-12-31 00:00:00.000.000.1.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20001231T0000000000001_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 1;
    const DateTime SOURCE_DATETIME(-2000, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -2000-01-01 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative20000101T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-2000, 1, 1, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-01 23:59:59.999.999.9.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010101T2359599999999_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 9;
    const DateTime SOURCE_DATETIME(-1, 1, 1, 23, 59, 59, 999, 999, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-01-02 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00010102T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 1, 2, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-30 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011230T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 30, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

/// <summary>
/// Checks that it returns the expected value when input is -0001-12-31 00:00:00.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_ReturnsExpectedValueWhenUsingCornerCaseNegative00011231T000000_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_HUNDREDOFNANOSECOND = 0;
    const DateTime SOURCE_DATETIME(-1, 12, 31, 0, 0, 0, 0, 0, EXPECTED_HUNDREDOFNANOSECOND, null_z);

	// [Execution]
    unsigned int uHundredOfNanosecond = SOURCE_DATETIME.GetHundredOfNanosecond();

    // [Verification]
    BOOST_CHECK_EQUAL(uHundredOfNanosecond, EXPECTED_HUNDREDOFNANOSECOND);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( GetHundredOfNanosecond_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.GetHundredOfNanosecond();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the same date/time with different time zone.
/// </summary>
ZTEST_CASE ( GetUtc_ReturnsSameDateTimeWithDifferentTimeZone_Test )
{
    // [Preparation]
    const TimeZone* EXPECTED_TIMEZONE = null_z;
    const DateTime SOURCE_DATETIME(-4, 12, 31, 23, 59, 59, 999, 999, 9, EXPECTED_TIMEZONE);
    const DateTime UTC_DATETIME(   SOURCE_DATETIME, null_z);

	// [Execution]
    DateTime result = SOURCE_DATETIME.GetUtc();

    // [Verification]
    const TimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == UTC_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns the expected value.
/// </summary>
ZTEST_CASE ( GetMaxDateTime_ReturnsExpectedValue_Test )
{
    // [Preparation]
    const DateTime EXPECTED_DATETIME(29228, 9, 14, 2, 48, 5, 477, 580, 7, null_z);
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime result = DateTime::GetMaxDateTime();

    // [Verification]
    const TimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == EXPECTED_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns the expected value.
/// </summary>
ZTEST_CASE ( GetMinDateTime_ReturnsExpectedValue_Test )
{
    // [Preparation]
    const DateTime EXPECTED_DATETIME(-29228, 4, 18, 21, 11, 54, 522, 419, 3, null_z);
    const TimeZone* EXPECTED_TIMEZONE = null_z;

	// [Execution]
    DateTime result = DateTime::GetMinDateTime();

    // [Verification]
    const TimeZone* pResultTimeZone = result.GetTimeZone();
    BOOST_CHECK(result == EXPECTED_DATETIME);
    BOOST_CHECK(pResultTimeZone == EXPECTED_TIMEZONE);
}

/// <summary>
/// Checks that it returns True when the date is positive.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsTrueWhenDateIsPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const DateTime SOURCE_DATETIME(4, 3, 2, TimeZone::UTC);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the date is not positive.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsFalseWhenDateIsNotPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const DateTime SOURCE_DATETIME(-4, 3, 2, TimeZone::UTC);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date is calculated based on local time in order to know whether it is positive or not.
/// </summary>
ZTEST_CASE ( IsPositive_IsLocalTime_Test )
{
    const bool EXPECTED_RESULT = false;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 30, 0, 0, 0, 0, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    bool bResultLocal = SOURCE_DATETIME.IsPositive();
    bool bResultUtc   = SOURCE_DATETIME_UTC.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bResultLocal, bResultUtc);
}

/// <summary>
/// Checks that it returns True when the date / time represent the first positive instant 0001-01-01 00:00:00.000000000.
/// </summary>
ZTEST_CASE ( IsPositive_FirstPositiveInstantIsConsideredPositive_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const DateTime FIRST_POSITIVE_INSTANT(1, 1, 1, 0, 0, 0, 0, 0, 0, TimeZone::UTC);

	// [Execution]
    bool bResult = FIRST_POSITIVE_INSTANT.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( IsPositive_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.IsPositive();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when date / time is undefined.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsFalseWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();

	// [Execution]
    bool bResult = UNDEFINED_DATETIME.IsPositive();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when the date is not negative.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsTrueWhenDateIsNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const DateTime SOURCE_DATETIME(4, 3, 2, TimeZone::UTC);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the date is negative.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsTrueWhenDateIsNotNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;
    const DateTime SOURCE_DATETIME(-4, 3, 2, TimeZone::UTC);

	// [Execution]
    bool bResult = SOURCE_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the date is calculated based on local time in order to know whether it is negative or not.
/// </summary>
ZTEST_CASE ( IsNegative_IsLocalTime_Test )
{
    const bool EXPECTED_RESULT = true;
    const TimeZone* EXPECTED_TIMEZONE = STimeZoneFactory::GetTimeZoneById(Z_L("Atlantic/Azores")); // AZOT-1
    const DateTime SOURCE_DATETIME(-1, 12, 31, 23, 30, 0, 0, 0, 0, EXPECTED_TIMEZONE);
    const DateTime SOURCE_DATETIME_UTC(SOURCE_DATETIME, null_z);

	// [Execution]
    bool bResultLocal = SOURCE_DATETIME.IsNegative();
    bool bResultUtc   = SOURCE_DATETIME_UTC.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultLocal, EXPECTED_RESULT);
    BOOST_CHECK_NE(bResultLocal, bResultUtc);
}

/// <summary>
/// Checks that it returns False when the date / time represent the first positive instant 0001-01-01 00:00:00.000000000.
/// </summary>
ZTEST_CASE ( IsNegative_FirstNegativeInstantIsNotConsideredNegative_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const DateTime FIRST_POSITIVE_INSTANT(1, 1, 1, 0, 0, 0, 0, 0, 0, TimeZone::UTC);

	// [Execution]
    bool bResult = FIRST_POSITIVE_INSTANT.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the date/time is undefined.
/// </summary>
ZTEST_CASE ( IsNegative_AssertionFailsWhenDateIsUndefined_Test )
{
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        UNDEFINED_DATETIME.IsNegative();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns False when date / time is undefined.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsFalseWhenDateIsUndefined_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;
    const DateTime UNDEFINED_DATETIME = DateTime::GetUndefinedDate();

	// [Execution]
    bool bResult = UNDEFINED_DATETIME.IsNegative();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetUndefinedDate_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that IsUndefined method returns true with an undefined date.
/// </summary>
ZTEST_CASE ( IsUndefined_ReturnsTrueWithUndefinedDate_Test )
{
    const DateTime DATETIME = DateTime::GetUndefinedDate();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bCheckResult = DATETIME.IsUndefined();

    // [Verification]
    BOOST_CHECK_EQUAL(bCheckResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that IsUndefined method returns false with a valid date.
/// </summary>
ZTEST_CASE ( IsUndefined_ReturnsFalseWithValidDate_Test )
{
    const DateTime DATETIME(1, 1, 1, 0, 0, 0, 0, 0, 0, TimeZone::UTC);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bCheckResult = DATETIME.IsUndefined();

    // [Verification]
    BOOST_CHECK_EQUAL(bCheckResult, EXPECTED_RESULT);
}

// End - Test Suite: DateTime
ZTEST_SUITE_END()
