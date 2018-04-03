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

#include "ZTime/DateTime.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZTime/TimeZone.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const u64_z DateTime::_HALF_VALUE = 9223372036854775808ULL;
const u64_z DateTime::_HNS_PER_MICROSECOND = 10ULL;
const u64_z DateTime::_HNS_PER_MILLISECOND = 10000ULL;
const u64_z DateTime::_HNS_PER_SECOND   = 10000000ULL;
const u64_z DateTime::_HNS_PER_MINUTE   = 600000000ULL;
const u64_z DateTime::_HNS_PER_HOUR     = 36000000000ULL;
const u64_z DateTime::_HNS_PER_DAY      = 864000000000ULL;
const u64_z DateTime::_HNS_PER_YEAR     = 315360000000000ULL;
const u64_z DateTime::_HNS_PER_LEAPYEAR = 316224000000000ULL;
const TimeSpan DateTime::_UNDEFINED_VALUE(0ULL);


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

DateTime::DateTime() : m_instant(TimeSpan(0)),
                       m_pTimeZone(null_z)
{
}

DateTime::DateTime(const DateTime &dateTime) : m_instant(dateTime.m_instant),
                                               m_pTimeZone(dateTime.m_pTimeZone)
{
}

DateTime::DateTime(const i32_z nYear, const u64_z uMonth, const u64_z uDay,
                   const u64_z uHour, const u64_z uMinute, const u64_z uSecond,
                   const u64_z uMillisecond, const u64_z uMicrosecond, const u64_z uHundredsOfNanosecond,
                   const TimeZone* pTimeZone) : m_pTimeZone(pTimeZone)
{
    // Adjustment required to store the day 1 (Gregorian calendar) as day zero (decimal system)
    static const u64_z DAY_ZERO_ADJUSTMENT = 1ULL;
    
    // These constants represent the maximum date (+29228-09-14 02:48:05.477.580.7) and the minimum date (-29228-04-18 21:11:54.522.419.3)
    static const i32_z MAX_DATE_YEAR        = 29228;
    static const u64_z MAX_DATE_MONTH       = 9ULL;
    static const u64_z MAX_DATE_DAY         = 14ULL;
    static const u64_z MAX_DATE_HOUR        = 2ULL;
    static const u64_z MAX_DATE_MINUTE      = 48ULL;
    static const u64_z MAX_DATE_SECOND      = 5ULL;
    static const u64_z MAX_DATE_MILLISECOND = 477ULL;
    static const u64_z MAX_DATE_MICROSECOND = 580ULL;
    static const u64_z MAX_DATE_HNS         = 7ULL;
    static const i32_z MIN_DATE_YEAR        = -29228;
    static const u64_z MIN_DATE_MONTH       = 4ULL;
    static const u64_z MIN_DATE_DAY         = 18ULL;
    static const u64_z MIN_DATE_HOUR        = 21ULL;
    static const u64_z MIN_DATE_MINUTE      = 11ULL;
    static const u64_z MIN_DATE_SECOND      = 54ULL;
    static const u64_z MIN_DATE_MILLISECOND = 522ULL;
    static const u64_z MIN_DATE_MICROSECOND = 419ULL;
    static const u64_z MIN_DATE_HNS         = 3ULL;

    // These constants represent the maximum values for every part of the date and time
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    static const u64_z MAX_MONTH       = 12ULL;
    static const u64_z MAX_DAY         = 31ULL;
    static const u64_z MAX_HOUR        = 23ULL;
    static const u64_z MAX_MINUTE      = 59ULL;
    static const u64_z MAX_SECOND      = 59ULL;
    static const u64_z MAX_MILLISECOND = 999ULL;
    static const u64_z MAX_MICROSECOND = 999ULL;
    static const u64_z MAX_HNS         = 9ULL;
#endif

    // Checks for invalid inputs
    Z_ASSERT_ERROR(nYear != 0, "The year zero does not exist");
    Z_ASSERT_ERROR(uMonth <= MAX_MONTH, "The value of the month is greater than the maximum allowed, it must be in the range [1, 12]");
    Z_ASSERT_ERROR(uMonth != 0, "The value of the month lower than the minimum allowed, it must be in the range [1, 12]");
    Z_ASSERT_ERROR(uDay <= MAX_DAY, "The value of the day is greater than the maximum allowed, it must be in the range [1, 31]");
    Z_ASSERT_ERROR(uDay != 0, "The value of the day is lower than the minimum allowed, it must be in the range [1, 31]");
    Z_ASSERT_ERROR(uDay <= DateTime::GetDaysInMonth(scast_z(uMonth, unsigned int), nYear), "The value of the day is not valid for the provided month in the provided year");
    Z_ASSERT_ERROR(uHour <= MAX_HOUR, "The value of the hour is not valid, it must be in the range [0, 23]");
    Z_ASSERT_ERROR(uMinute <= MAX_MINUTE, "The value of the minute is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uSecond <= MAX_SECOND, "The value of the second is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uMillisecond <= MAX_MILLISECOND, "The value of the milliseconds is not valid, it must be in the range [0, 999]");
    Z_ASSERT_ERROR(uMicrosecond <= MAX_MICROSECOND, "The value of the microseconds is not valid, it must be in the range [0, 999]");
    Z_ASSERT_ERROR(uHundredsOfNanosecond <= MAX_HNS, "The value of the hundreds of nanoseconds is not valid, it must be in the range [0, 9]");

    // Checks for representable limits
    const bool INPUT_IS_OUT_OF_POSITIVE_LIMIT = nYear > MAX_DATE_YEAR                                                         ||
                                                (nYear   ==      MAX_DATE_YEAR   && (uMonth       > MAX_DATE_MONTH            ||
                                                (uMonth  ==      MAX_DATE_MONTH  && (uDay         > MAX_DATE_DAY              ||
                                                (uDay    ==      MAX_DATE_DAY    && (uHour        > MAX_DATE_HOUR             ||
                                                (uHour   ==      MAX_DATE_HOUR   && (uMinute      > MAX_DATE_MINUTE           ||
                                                (uMinute ==      MAX_DATE_MINUTE && (uSecond      > MAX_DATE_SECOND           ||
                                                (uSecond ==      MAX_DATE_SECOND && (uMillisecond > MAX_DATE_MILLISECOND      ||
                                                (uMillisecond == MAX_DATE_MILLISECOND && (uMicrosecond > MAX_DATE_MICROSECOND ||
                                                (uMicrosecond == MAX_DATE_MICROSECOND && (uHundredsOfNanosecond > MAX_DATE_HNS))))))))))))))));

    const bool INPUT_IS_OUT_OF_NEGATIVE_LIMIT = nYear < MIN_DATE_YEAR                                                         ||
                                                (nYear   ==      MIN_DATE_YEAR   && (uMonth       < MIN_DATE_MONTH            ||
                                                (uMonth  ==      MIN_DATE_MONTH  && (uDay         < MIN_DATE_DAY              ||
                                                (uDay    ==      MIN_DATE_DAY    && (uHour        < MIN_DATE_HOUR             ||
                                                (uHour   ==      MIN_DATE_HOUR   && (uMinute      < MIN_DATE_MINUTE           ||
                                                (uMinute ==      MIN_DATE_MINUTE && (uSecond      < MIN_DATE_SECOND           ||
                                                (uSecond ==      MIN_DATE_SECOND && (uMillisecond < MIN_DATE_MILLISECOND      ||
                                                (uMillisecond == MIN_DATE_MILLISECOND && (uMicrosecond < MIN_DATE_MICROSECOND ||
                                                (uMicrosecond == MIN_DATE_MICROSECOND && (uHundredsOfNanosecond < MIN_DATE_HNS))))))))))))))));

    Z_ASSERT_WARNING(!INPUT_IS_OUT_OF_POSITIVE_LIMIT, "The input date and time is posterior to the maximum value that can be represented by this type");
    Z_ASSERT_WARNING(!INPUT_IS_OUT_OF_NEGATIVE_LIMIT, "The input date and time is anterior to the minimum value that can be represented by this type");

    if(INPUT_IS_OUT_OF_POSITIVE_LIMIT)
    {
        // If the input date and time exceed the highest limit, the result will be the maximum value
        m_instant = TimeSpan(SInteger::MaxU64_Z);
    }
    else if(INPUT_IS_OUT_OF_NEGATIVE_LIMIT)
    {
        // If the input date and time exceed the lowest limit, the result will be the minimum value
        m_instant = TimeSpan(1ULL);
    }
    else
    {
        // All the input values are converted to hundreds of nanoseconds (hns)
        const u64_z MICROSECOND_AS_HNS = uMicrosecond * DateTime::_HNS_PER_MICROSECOND;
        const u64_z MILLISECOND_AS_HNS = uMillisecond * DateTime::_HNS_PER_MILLISECOND;
        const u64_z SECOND_AS_HNS = uSecond * DateTime::_HNS_PER_SECOND;
        const u64_z MINUTE_AS_HNS = uMinute * DateTime::_HNS_PER_MINUTE;
        const u64_z HOUR_AS_HNS = uHour * DateTime::_HNS_PER_HOUR;
        const u64_z DAY_AS_HNS = (uDay - DAY_ZERO_ADJUSTMENT) * DateTime::_HNS_PER_DAY;

        // Sums the days of all completed months
        u64_z uDaysInCompleteMonths = 0;

        for(unsigned int i = 1U; i < uMonth; ++i)
            uDaysInCompleteMonths += DateTime::GetDaysInMonth(i, nYear);

        const u64_z MONTH_AS_HNS = uDaysInCompleteMonths * DateTime::_HNS_PER_DAY;

        const u64_z ABS_YEAR = scast_z(SInteger::Abs(nYear), u64_z);

        // Number of extra days accumulated due to leap years: abs(T.YEAR - 1) / 4 - abs(T.YEAR - 1) / 100 + abs(T.YEAR - 1) / 400
        const u64_z PASSED_COMPLETE_YEARS = ABS_YEAR - 1ULL;
        const u64_z LEAP_DAYS = (PASSED_COMPLETE_YEARS / 4ULL - PASSED_COMPLETE_YEARS / 100ULL + PASSED_COMPLETE_YEARS / 400ULL);

        // Hundreds of nanoseconds in passed years: abs(T.YEAR) * nsh in 1 year + leap days * nsh in 1 day
        u64_z uYearsAsHns = ABS_YEAR * DateTime::_HNS_PER_YEAR + LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Offset applied to positive dates in order to make the year zero-based
        if(nYear > 0)
            uYearsAsHns -= DateTime::_HNS_PER_YEAR;

        // First, the last year's remaining time is summed
        const u64_z REMAINING_TIME = MONTH_AS_HNS + DAY_AS_HNS + HOUR_AS_HNS + MINUTE_AS_HNS + SECOND_AS_HNS +
                                     MILLISECOND_AS_HNS + MICROSECOND_AS_HNS + uHundredsOfNanosecond;

        // If the year is a leap year and is negative, a leap day is added.
        // In absence of leap days, all years are considered equal. Since the remaining time will be substracted to the last year, it may occur that,
        // in case that it is a leap year, the remaining time is greater than 1 common year, which would affect the next year too.
        // In order to keep the remaining time inside the last year, it must be moved 1 day to the negative side.
        // This way, the last year has 366 days and the remaining time is enclosed into it.
        //
        //         -6     -5     -4     -3     -2     -1     +1     +2
        //                              [<<<<<<<<<<<<<<<<<]
        //      |______|______|______|______|______|______|______|______| (365 days-length parts)
        //                    [>>>>>>>>]     ( <=366 days )
        //                           | |
        //
        //     -6     -5       -4       -3     -2     -1     +1     +2
        //                           |++| 1 day
        //                           [<<<<<<<<<<<<<<<<<<<<]
        //  |______|______|__________|______|______|______|______|______|
        //                [>>>>>>>>]     ( <=366 days )
        //                         | |
        //                        |++| 1 day
        //                |<-- +1 day
        if(nYear < 0 && DateTime::_IsLeapYear(nYear))
            uYearsAsHns += DateTime::_HNS_PER_DAY;

        TimeSpan instant;

        if(nYear < 0)
            // If the year is negative, years are subtracted to the offset and days and time are added
            instant = TimeSpan(DateTime::_HALF_VALUE - uYearsAsHns + REMAINING_TIME);
        else
            // If the year is positive, years, days and time are added to the offset
            instant = TimeSpan(DateTime::_HALF_VALUE + uYearsAsHns + REMAINING_TIME);

        // Removes the time zone offset
        m_instant = pTimeZone == null_z ? instant :
                                          this->_GetInstantWithSubtractedTimeZoneOffset(instant, pTimeZone);
    }
}

DateTime::DateTime(const i32_z nYear, const u64_z uMonth, const u64_z uDay, const TimeZone* pTimeZone) :
                m_pTimeZone(pTimeZone)
{
    // Adjustment required to store the day 1 (Gregorian calendar) as day zero (decimal system)
    static const u64_z DAY_ZERO_ADJUSTMENT = 1ULL;

    // These constants represent the maximum date (+29228-09-14 02:48:05.477.580.7) and the minimum date (-29228-04-18 21:11:54.522.419.3)
    static const i32_z MAX_DATE_YEAR        = 29228;
    static const u64_z MAX_DATE_MONTH       = 9ULL;
    static const u64_z MAX_DATE_DAY         = 14ULL;
    static const i32_z MIN_DATE_YEAR        = -29228;
    static const u64_z MIN_DATE_MONTH       = 4ULL;
    static const u64_z MIN_DATE_DAY         = 19ULL; // IMPORTANT: It cannot be 18 because the time would be 00:00:00, which is anterior to 21:11:54

    // These constants represent the maximum values for every part of the date and time
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    static const u64_z MAX_MONTH       = 12ULL;
    static const u64_z MAX_DAY         = 31ULL;
#endif

    // Checks for invalid inputs
    Z_ASSERT_ERROR(nYear != 0, "The year zero does not exist");
    Z_ASSERT_ERROR(uMonth <= MAX_MONTH, "The value of the month is greater than the maximum allowed, it must be in the range [1, 12]");
    Z_ASSERT_ERROR(uMonth != 0, "The value of the month lower than the minimum allowed, it must be in the range [1, 12]");
    Z_ASSERT_ERROR(uDay <= MAX_DAY, "The value of the day is greater than the maximum allowed, it must be in the range [1, 31]");
    Z_ASSERT_ERROR(uDay != 0, "The value of the day is lower than the minimum allowed, it must be in the range [1, 31]");
    Z_ASSERT_ERROR(uDay <= DateTime::GetDaysInMonth(scast_z(uMonth, unsigned int), nYear), "The value of the day is not valid for the provided month in the provided year");

    // Checks for representable limits
    const bool INPUT_IS_OUT_OF_POSITIVE_LIMIT = nYear > MAX_DATE_YEAR                                                         ||
                                                (nYear   ==      MAX_DATE_YEAR   && (uMonth       > MAX_DATE_MONTH            ||
                                                (uMonth  ==      MAX_DATE_MONTH  && (uDay         > MAX_DATE_DAY))));

    const bool INPUT_IS_OUT_OF_NEGATIVE_LIMIT = nYear < MIN_DATE_YEAR                                                         ||
                                                (nYear   ==      MIN_DATE_YEAR   && (uMonth       < MIN_DATE_MONTH            ||
                                                (uMonth  ==      MIN_DATE_MONTH  && (uDay         < MIN_DATE_DAY))));

    Z_ASSERT_WARNING(!INPUT_IS_OUT_OF_POSITIVE_LIMIT, "The input date and time is posterior to the maximum value that can be represented by this type");
    Z_ASSERT_WARNING(!INPUT_IS_OUT_OF_NEGATIVE_LIMIT, "The input date and time is anterior to the minimum value that can be represented by this type");

    if(INPUT_IS_OUT_OF_POSITIVE_LIMIT)
    {
        // If the input date and time exceed the highest limit, the result will be the maximum value
        m_instant = TimeSpan(SInteger::MaxU64_Z);
    }
    else if(INPUT_IS_OUT_OF_NEGATIVE_LIMIT)
    {
        // If the input date and time exceed the lowest limit, the result will be the minimum value
        m_instant = TimeSpan(1ULL);
    }
    else
    {
        // All the input values are converted to hundreds of nanoseconds (hns)
        const u64_z DAY_AS_HNS = (uDay - DAY_ZERO_ADJUSTMENT) * DateTime::_HNS_PER_DAY;

        // Sums the days of all completed months
        u64_z uDaysInCompleteMonths = 0;

        for(unsigned int i = 1U; i < uMonth; ++i)
            uDaysInCompleteMonths += DateTime::GetDaysInMonth(i, nYear);

        const u64_z MONTH_AS_HNS = uDaysInCompleteMonths * DateTime::_HNS_PER_DAY;

        const u64_z ABS_YEAR = scast_z(SInteger::Abs(nYear), u64_z);

        // Number of extra days accumulated due to leap years: abs(T.YEAR - 1) / 4 - abs(T.YEAR - 1) / 100 + abs(T.YEAR - 1) / 400
        const u64_z PASSED_COMPLETE_YEARS = ABS_YEAR - 1ULL;
        const u64_z LEAP_DAYS = (PASSED_COMPLETE_YEARS / 4ULL - PASSED_COMPLETE_YEARS / 100ULL + PASSED_COMPLETE_YEARS / 400ULL);

        // Hundreds of nanoseconds in passed years: abs(T.YEAR) * nsh in 1 year + leap days * nsh in 1 day
        u64_z uYearsAsHns = ABS_YEAR * DateTime::_HNS_PER_YEAR + LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Offset applied to positive dates in order to make the year zero-based
        if(nYear > 0)
            uYearsAsHns -= DateTime::_HNS_PER_YEAR;

        // First, the last year's remaining time is summed
        const u64_z REMAINING_TIME = MONTH_AS_HNS + DAY_AS_HNS;
        
        // If the year is a leap year and is negative, a leap day is added.
        // In absence of leap days, all years are considered equal. Since the remaining time will be substracted to the last year, it may occur that,
        // in case that it is a leap year, the remaining time is greater than 1 common year, which would affect the next year too.
        // In order to keep the remaining time inside the last year, it must be moved 1 day to the negative side.
        // This way, the last year has 366 days and the remaining time is enclosed into it.
        //
        //         -6     -5     -4     -3     -2     -1     +1     +2
        //                              [<<<<<<<<<<<<<<<<<]
        //      |______|______|______|______|______|______|______|______| (365 days-length parts)
        //                    [>>>>>>>>]     ( <=366 days )
        //                           | |
        //
        //     -6     -5       -4       -3     -2     -1     +1     +2
        //                           |++| 1 day
        //                           [<<<<<<<<<<<<<<<<<<<<]
        //  |______|______|__________|______|______|______|______|______|
        //                [>>>>>>>>]     ( <=366 days )
        //                         | |
        //                        |++| 1 day
        //                |<-- +1 day
        if(nYear < 0 && DateTime::_IsLeapYear(nYear))
            uYearsAsHns += DateTime::_HNS_PER_DAY;

        TimeSpan instant;

        if(nYear < 0)
            // If the year is negative, years are subtracted to the offset and days and time are added
            instant = TimeSpan(DateTime::_HALF_VALUE - uYearsAsHns + REMAINING_TIME);
        else
            // If the year is positive, years, days and time are added to the offset
            instant = TimeSpan(DateTime::_HALF_VALUE + uYearsAsHns + REMAINING_TIME);

        // Removes the time zone offset
        m_instant = pTimeZone == null_z ? instant :
                                          this->_GetInstantWithSubtractedTimeZoneOffset(instant, pTimeZone);
    }
}

DateTime::DateTime(const u64_z uHour, const u64_z uMinute, const u64_z uSecond,
                     const u64_z uMillisecond, const u64_z uMicrosecond, const u64_z uHundredsOfNanosecond,
                     const TimeZone* pTimeZone) : m_pTimeZone(pTimeZone)
{
    // These constants represent the maximum values for every part of the date and time
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    static const u64_z MAX_HOUR        = 23ULL;
    static const u64_z MAX_MINUTE      = 59ULL;
    static const u64_z MAX_SECOND      = 59ULL;
    static const u64_z MAX_MILLISECOND = 999ULL;
    static const u64_z MAX_MICROSECOND = 999ULL;
    static const u64_z MAX_HNS         = 9ULL;
#endif

    // Checks for invalid inputs
    Z_ASSERT_ERROR(uHour <= MAX_HOUR, "The value of the hour is not valid, it must be in the range [0, 23]");
    Z_ASSERT_ERROR(uMinute <= MAX_MINUTE, "The value of the minute is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uSecond <= MAX_SECOND, "The value of the second is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uMillisecond <= MAX_MILLISECOND, "The value of the milliseconds is not valid, it must be in the range [0, 999]");
    Z_ASSERT_ERROR(uMicrosecond <= MAX_MICROSECOND, "The value of the microseconds is not valid, it must be in the range [0, 999]");
    Z_ASSERT_ERROR(uHundredsOfNanosecond <= MAX_HNS, "The value of the hundreds of nanoseconds is not valid, it must be in the range [0, 9]");


    // All the input values are converted to hundreds of nanoseconds (hns)
    const u64_z MICROSECOND_AS_HNS = uMicrosecond * DateTime::_HNS_PER_MICROSECOND;
    const u64_z MILLISECOND_AS_HNS = uMillisecond * DateTime::_HNS_PER_MILLISECOND;
    const u64_z SECOND_AS_HNS = uSecond * DateTime::_HNS_PER_SECOND;
    const u64_z MINUTE_AS_HNS = uMinute * DateTime::_HNS_PER_MINUTE;
    const u64_z HOUR_AS_HNS = uHour * DateTime::_HNS_PER_HOUR;

    // First, the last year's remaining time is summed
    const u64_z REMAINING_TIME = HOUR_AS_HNS + MINUTE_AS_HNS + SECOND_AS_HNS +
                                 MILLISECOND_AS_HNS + MICROSECOND_AS_HNS + uHundredsOfNanosecond;

    TimeSpan instant = TimeSpan(DateTime::_HALF_VALUE + REMAINING_TIME);

    // Removes the time zone offset
    m_instant = pTimeZone == null_z ? instant :
                                      this->_GetInstantWithSubtractedTimeZoneOffset(instant, pTimeZone);
}

DateTime::DateTime(const u64_z uHour, const u64_z uMinute, const u64_z uSecond, const u64_z uMillisecond, const TimeZone* pTimeZone) :
                m_pTimeZone(pTimeZone)
{
    // These constants represent the maximum values for every part of the date and time
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    static const u64_z MAX_HOUR        = 23ULL;
    static const u64_z MAX_MINUTE      = 59ULL;
    static const u64_z MAX_SECOND      = 59ULL;
    static const u64_z MAX_MILLISECOND = 999ULL;
#endif

    // Checks for invalid inputs
    Z_ASSERT_ERROR(uHour <= MAX_HOUR, "The value of the hour is not valid, it must be in the range [0, 23]");
    Z_ASSERT_ERROR(uMinute <= MAX_MINUTE, "The value of the minute is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uSecond <= MAX_SECOND, "The value of the second is not valid, it must be in the range [0, 59]");
    Z_ASSERT_ERROR(uMillisecond <= MAX_MILLISECOND, "The value of the milliseconds is not valid, it must be in the range [0, 999]");

    // All the input values are converted to hundreds of nanoseconds (hns)
    const u64_z MILLISECOND_AS_HNS = uMillisecond * DateTime::_HNS_PER_MILLISECOND;
    const u64_z SECOND_AS_HNS = uSecond * DateTime::_HNS_PER_SECOND;
    const u64_z MINUTE_AS_HNS = uMinute * DateTime::_HNS_PER_MINUTE;
    const u64_z HOUR_AS_HNS = uHour * DateTime::_HNS_PER_HOUR;

    // First, the last year's remaining time is summed
    const u64_z REMAINING_TIME = HOUR_AS_HNS + MINUTE_AS_HNS + SECOND_AS_HNS + MILLISECOND_AS_HNS;

    // If the year is positive, years, days and time are added to the offset
    TimeSpan instant = TimeSpan(DateTime::_HALF_VALUE + REMAINING_TIME);

    // Removes the time zone offset
    m_instant = pTimeZone == null_z ? instant :
                                      this->_GetInstantWithSubtractedTimeZoneOffset(instant, pTimeZone);
}

DateTime::DateTime(const DateTime &dateTime, const TimeZone* pTimeZone) : m_instant(dateTime.m_instant),
                                                                              m_pTimeZone(pTimeZone)
{
}

DateTime::DateTime(const string_z &strTimestamp)
{
    static const char_z DATE_SEPARATOR = '-';
    static const char_z TIME_START_SEPARATOR = 'T';
    static const char_z POSITIVE_SIGN = '+';
    static const char_z NEGATIVE_SIGN = '-';

    Z_ASSERT_ERROR(!strTimestamp.IsEmpty(), "The input timestamp must not be empty.");
    Z_ASSERT_ERROR(strTimestamp.IndexOf(" ", EComparisonType::E_BinaryCaseSensitive) == string_z::PATTERN_NOT_FOUND, "The input timestamp must not contain whitespaces.");

    i32_z nYear, nOffsetHours;
    u32_z uMonth, uDay, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, uOffsetMinutes;

    int nTimePosition = strTimestamp.IndexOf(TIME_START_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

    if(nTimePosition != string_z::PATTERN_NOT_FOUND)
    {
        // The timestamp combines Date and Time

        this->_ParseTimestampCompleteDate(strTimestamp, scast_z(nTimePosition, u32_z), nYear, uMonth, uDay);
        this->_ParseTimestampCompleteTime(strTimestamp, scast_z(nTimePosition, u32_z), uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, nOffsetHours, uOffsetMinutes);

        // The date and time is constructed
        *this = DateTime(nYear, uMonth, uDay, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, TimeZone::UTC);

        this->_ApplyOffsetToTimestamp(nOffsetHours, uOffsetMinutes, uHour, uMinute, *this);
    }
    else
    {
        // The timestamp contains either Date or Time information only

        if(strTimestamp[0] == POSITIVE_SIGN || strTimestamp[0] == NEGATIVE_SIGN)
        {
            // It is preceeded by a sign, so it must be a date

            const int SEPARATOR_POSITION = strTimestamp.IndexOf(DATE_SEPARATOR, 1, EComparisonType::E_BinaryCaseSensitive); // Starts from 1 to skip the sign

            if(SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND)
                this->_ParseTimestampIncompleteDateWithSeparators(strTimestamp, SEPARATOR_POSITION, nYear, uMonth, uDay);
            else
                this->_ParseTimestampIncompleteDateWithoutSeparators(strTimestamp, nYear, uMonth, uDay);

            *this = DateTime(nYear, uMonth, uDay, TimeZone::UTC);
        }
        else
        {
            // It is not preceded by a sign, so it may be either a date or a time

            const int FIRST_SEPARATOR_POSITION = strTimestamp.IndexOf(DATE_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

            if(FIRST_SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND)
            {
                const int SECOND_SEPARATOR_POSITION = strTimestamp.IndexOf(DATE_SEPARATOR, FIRST_SEPARATOR_POSITION + 1U, EComparisonType::E_BinaryCaseSensitive);

                if(SECOND_SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND)
                {
                    // It contains 2 hyphens, it must be a date
                    this->_ParseTimestampIncompleteDateWithSeparators(strTimestamp, FIRST_SEPARATOR_POSITION, nYear, uMonth, uDay);
                    *this = DateTime(nYear, uMonth, uDay, TimeZone::UTC);
                }
                else
                {
                    // It is interpreted as time by default, even if it does not contain colons (the hyphen is considered a minus sign of the time offset instead of a date seprator)

                    this->_ParseTimestampIncompleteTime(strTimestamp, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, nOffsetHours, uOffsetMinutes);
                    *this = DateTime(uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, TimeZone::UTC);
                    this->_ApplyOffsetToTimestampWithoutAffectingDate(nOffsetHours, uOffsetMinutes, uHour, uMinute, *this);
                }
            }
            else
            {
                // It is interpreted as time by default, even if it does not contain colons
                this->_ParseTimestampIncompleteTime(strTimestamp, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, nOffsetHours, uOffsetMinutes);
                *this = DateTime(uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond, TimeZone::UTC);
                this->_ApplyOffsetToTimestampWithoutAffectingDate(nOffsetHours, uOffsetMinutes, uHour, uMinute, *this);
            }
        }
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

DateTime& DateTime::operator=(const DateTime& dateTime)
{
    if(this != &dateTime)
    {
        this->m_instant = dateTime.m_instant;
        this->m_pTimeZone = dateTime.m_pTimeZone;
    }

    return *this;
}

DateTime& DateTime::operator+=(const TimeSpan &timeToAdd)
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The date/time is undefined, the time span cannot be added");

    Z_ASSERT_WARNING(DateTime::GetMaxDateTime().m_instant - m_instant >= timeToAdd, "The result of adding that time span exceeds the maximum date, the result will be set to the maximum date allowed");

    // Note: It assumes that the TimeSpan class already prevents from overflow
    if(*this != DateTime::GetUndefinedDate())
        m_instant += timeToAdd;

    return *this;
}

DateTime& DateTime::operator-=(const TimeSpan &timeToSubtract)
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The date/time is undefined, the time span cannot be subtracted");

    if(*this != DateTime::GetUndefinedDate())
    {
        Z_ASSERT_WARNING(m_instant > timeToSubtract, "The result of subtracting that time span exceeds the minimum date, the result will be set to the minimum date allowed");

        if(m_instant <= timeToSubtract)
            m_instant = DateTime::GetMinDateTime().m_instant;
        else
            m_instant -= timeToSubtract;
    }

    return *this;
}

DateTime DateTime::operator+(const TimeSpan &timeToAdd) const
{
    DateTime result(*this);
    result += timeToAdd;

    return result;
}

DateTime DateTime::operator-(const TimeSpan &timeToSubtract) const
{
    DateTime result(*this);
    result -= timeToSubtract;

    return result;
}

TimeSpan DateTime::operator-(const DateTime &dateTime) const
{
    Z_ASSERT_ERROR(!this->IsUndefined() && !dateTime.IsUndefined(), "It is not possible to calculate the difference between undefined dates");

    if(this->IsUndefined() || dateTime.IsUndefined())
    {
        return TimeSpan(0);
    }
    else
    {
        if(dateTime.m_instant < m_instant)
            return m_instant - dateTime.m_instant;
        else
            return dateTime.m_instant - m_instant;
    }
}

bool DateTime::operator==(const DateTime &dateTime) const
{
    // Other members are not checked
    return dateTime.m_instant == m_instant;
}

bool DateTime::operator!=(const DateTime &dateTime) const
{
    // Other members are not checked
    return dateTime.m_instant != m_instant;
}

bool DateTime::operator<(const DateTime &dateTime) const
{
    Z_ASSERT_ERROR(!this->IsUndefined() && !dateTime.IsUndefined(), "It is not possible to compare undefined dates");

    // Other members are not checked
    return this->IsUndefined() || dateTime.IsUndefined() ?
                false :
                m_instant < dateTime.m_instant;
}

bool DateTime::operator>(const DateTime &dateTime) const
{
    Z_ASSERT_ERROR(!this->IsUndefined() && !dateTime.IsUndefined(), "It is not possible to compare undefined dates");

    // Other members are not checked
    return this->IsUndefined() || dateTime.IsUndefined() ?
                false :
                m_instant > dateTime.m_instant;
}

bool DateTime::operator<=(const DateTime &dateTime) const
{
    Z_ASSERT_ERROR(this->IsUndefined() == dateTime.IsUndefined(), "It is not possible to compare undefined dates");

    // Other members are not checked
    return (!this->IsUndefined() && dateTime.IsUndefined()) || (this->IsUndefined() && !dateTime.IsUndefined()) ? // If only one operand is undefined
                false :
                m_instant <= dateTime.m_instant;
}

bool DateTime::operator>=(const DateTime &dateTime) const
{
    Z_ASSERT_ERROR(this->IsUndefined() == dateTime.IsUndefined(), "It is not possible to compare undefined dates");

    // Other members are not checked
    return (!this->IsUndefined() && dateTime.IsUndefined()) || (this->IsUndefined() && !dateTime.IsUndefined()) ? // If only one operand is undefined
               false :
               m_instant >= dateTime.m_instant;
}

unsigned int DateTime::GetDaysInMonth(const unsigned int uMonth, const int nYear)
{
    static const unsigned int FEBRUARY_INDEX = 2;
    static const unsigned int MAXIMUM_MONTH_INDEX = 12;
    static const unsigned int DAYS_IN_MONTH[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    Z_ASSERT_ERROR(uMonth != 0, "The month index must be greater than 0");
    Z_ASSERT_ERROR(uMonth <= MAXIMUM_MONTH_INDEX, "The month index must be lower than 13");

    unsigned int uDays = 0;

    if(uMonth <= MAXIMUM_MONTH_INDEX)
        uDays = DAYS_IN_MONTH[uMonth - 1];

    // If the year is a leap year, add 1 to the number of days in February
    if(uMonth == FEBRUARY_INDEX && DateTime::_IsLeapYear(nYear))
        ++uDays;

    return uDays;
}

const DateTime& DateTime::GetUndefinedDate()
{
    static const DateTime UNDEFINED_DATETIME;
    return UNDEFINED_DATETIME;
}

string_z DateTime::ToString() const
{
    // Output format samples: +YYYYY-MM-DDThh:mm:ss.uuuuuuu+hh:mm
    //                        -YYYY-MM-DDThh:mm:ss.uuuuuuuZ
    //                        +YYYY-MM-DDThh:mm:ss-hh:mm

    static const string_z TIME_SEPARATOR = ":";
    static const string_z DATE_SEPARATOR = "-";
    static const string_z TIME_START_SEPARATOR = "T";
    static const string_z POSITIVE_SIGN = "+";
    static const string_z NEGATIVE_SIGN = "-";
    static const string_z ZULU_TIME = "Z";
    static const string_z ZERO_STRING = "0";

    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined date/times cannot be represented as string");

    string_z strTimestamp;
    if(this->IsNegative())
        strTimestamp.Append(NEGATIVE_SIGN);
    else
        strTimestamp.Append(POSITIVE_SIGN);

    unsigned int uYear;
    unsigned int uMonth;
    unsigned int uDay;
    unsigned int uHour;
    unsigned int uMinute;
    unsigned int uSecond;
    unsigned int uMillisecond;
    unsigned int uMicrosecond;
    unsigned int uHundredOfNanosecond;

    this->Decompose(uYear, uMonth, uDay, uHour, uMinute, uSecond, uMillisecond, uMicrosecond, uHundredOfNanosecond);

    // Negative years are adjusted so the year 1 BC, or -1, is represented by "-0000" in timestamps
    uYear = this->IsNegative() ? uYear - 1U : uYear;

    const string_z& YEAR_STRING = string_z::FromInteger(uYear);

    // Padding with zeroes
    const unsigned int YEAR_STRING_LENGTH = YEAR_STRING.GetLength();

    if(YEAR_STRING_LENGTH < 4U) // YYYYY is allowed, but padding is applied only when width is lower than 4 cyphers
    {
        for(unsigned int i = 0; i < 4U - YEAR_STRING_LENGTH; ++i)
            strTimestamp.Append(ZERO_STRING);
    }

    strTimestamp.Append(YEAR_STRING);
    strTimestamp.Append(DATE_SEPARATOR);

    // Padding with zeroes
    const unsigned int FIRST_NUMBER_WITH_2_CYPHERS = 10U;

    if(uMonth < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
        strTimestamp.Append(ZERO_STRING);

    strTimestamp.Append(string_z::FromInteger(uMonth));
    strTimestamp.Append(DATE_SEPARATOR);

    // Padding with zeroes
    if(uDay < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
        strTimestamp.Append(ZERO_STRING);

    strTimestamp.Append(string_z::FromInteger(uDay));
    strTimestamp.Append(TIME_START_SEPARATOR);

    // Padding with zeroes
    if(uHour < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
        strTimestamp.Append(ZERO_STRING);

    strTimestamp.Append(string_z::FromInteger(uHour));
    strTimestamp.Append(TIME_SEPARATOR);

    // Padding with zeroes
    if(uMinute < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
        strTimestamp.Append(ZERO_STRING);

    strTimestamp.Append(string_z::FromInteger(uMinute));
    strTimestamp.Append(TIME_SEPARATOR);

    // Padding with zeroes
    if(uSecond < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
        strTimestamp.Append(ZERO_STRING);

    strTimestamp.Append(string_z::FromInteger(uSecond));
    
    // Converts milliseconds, microseconds and nanoseconds to a fraction of second
    this->_SecondFractionToString(uMillisecond, uMicrosecond, uHundredOfNanosecond, strTimestamp);

    // Adds the time offset
    if(m_pTimeZone == null_z)
    {
        strTimestamp.Append(ZULU_TIME);
    }
    else
    {
        TimeSpan offset(0);
        bool bIsNegative = false;
        m_pTimeZone->CalculateOffset(*this, offset, bIsNegative);

        if(bIsNegative)
            strTimestamp.Append(NEGATIVE_SIGN);
        else
            strTimestamp.Append(POSITIVE_SIGN);

        static const unsigned int MINUTES_PER_HOUR = 60;
        const unsigned int OFFSET_HOURS = offset.GetHours();
        const unsigned int OFFSET_MINUTES = offset.GetMinutes() % MINUTES_PER_HOUR;

        // Padding with zeroes
        if(OFFSET_HOURS < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
            strTimestamp.Append(ZERO_STRING);

        strTimestamp.Append(string_z::FromInteger(OFFSET_HOURS));
        strTimestamp.Append(TIME_SEPARATOR);

        // Padding with zeroes
        if(OFFSET_MINUTES < FIRST_NUMBER_WITH_2_CYPHERS) // Less than 2 cyphers
            strTimestamp.Append(ZERO_STRING);

        strTimestamp.Append(string_z::FromInteger(OFFSET_MINUTES));
    }

    return strTimestamp;
}

void DateTime::_SecondFractionToString(const unsigned int uMillisecond, const unsigned int uMicrosecond, const unsigned int uHundredOfNanosecond, string_z &strTimestamp) const
{
    static const string_z SECOND_FRACTION_SEPARATOR1 = ".";
    static const string_z ZERO_STRING = "0";
    static const string_z THREE_ZERO_STRING = "000";
    static const string_z SIX_ZERO_STRING = "000000";
    bool bHasFraction = false;

    if(uMillisecond > 0)
    {
        // Has milliseconds
        bHasFraction = true;
        strTimestamp.Append(SECOND_FRACTION_SEPARATOR1);

        const string_z& strMillisecond = string_z::FromInteger(uMillisecond);

        const unsigned int MILLISECOND_LENGTH = strMillisecond.GetLength();

        for(unsigned int i = 0; i < 3U - MILLISECOND_LENGTH; ++i)
            strTimestamp.Append(ZERO_STRING);

        strTimestamp.Append(strMillisecond);

        if(uMicrosecond > 0)
        {
            // Has milliseconds and microseconds
            const string_z& strMicrosecond = string_z::FromInteger(uMicrosecond);

            const unsigned int MICROSECOND_LENGTH = strMicrosecond.GetLength();

            for(unsigned int i = 0; i < 3U - MICROSECOND_LENGTH; ++i)
                strTimestamp.Append(ZERO_STRING);

            strTimestamp.Append(strMicrosecond);

            if(uHundredOfNanosecond > 0)
            {
                // Has milliseconds, microseconds and hundreds of nanoseconds
                strTimestamp.Append(string_z::FromInteger(uHundredOfNanosecond));
            }
        }
        else
        {
            if(uHundredOfNanosecond > 0)
            {
                // Has milliseconds and hundreds of nanoseconds, no microseconds
                strTimestamp.Append(THREE_ZERO_STRING);
                strTimestamp.Append(string_z::FromInteger(uHundredOfNanosecond));
            }
        }
    }
    else
    {
        if(uMicrosecond > 0)
        {
            // Has microseconds, no milliseconds
            bHasFraction = true;
            strTimestamp.Append(SECOND_FRACTION_SEPARATOR1);
            strTimestamp.Append(THREE_ZERO_STRING);

            const string_z& strMicrosecond = string_z::FromInteger(uMicrosecond);

            const unsigned int MICROSECOND_LENGTH = strMicrosecond.GetLength();

            for(unsigned int i = 0; i < 3U - MICROSECOND_LENGTH; ++i)
                strTimestamp.Append(ZERO_STRING);

            strTimestamp.Append(strMicrosecond);

            if(uHundredOfNanosecond > 0)
            {
                // Has microseconds and hundreds of nanoseconds, no milliseconds
                strTimestamp.Append(string_z::FromInteger(uHundredOfNanosecond));
            }
        }
        else
        {
            if(uHundredOfNanosecond > 0)
            {
                // Has hundreds of nanoseconds, no milliseconds, no microseconds
                bHasFraction = true;
                strTimestamp.Append(SECOND_FRACTION_SEPARATOR1);
                strTimestamp.Append(SIX_ZERO_STRING);
                strTimestamp.Append(string_z::FromInteger(uHundredOfNanosecond));
            }
        }
    }

    if(bHasFraction)
    {
        // Removes last zeroes
        static const char_z CHARACTER_ZERO = '0';
        unsigned int uNumberOfZeroesToRemove = 0;

        string_z::ConstCharIterator it = strTimestamp.GetConstCharIterator();
        it.MoveLast();

        while(!it.IsEnd() && it.GetChar() == CHARACTER_ZERO)
        {
            --it;
            ++uNumberOfZeroesToRemove ;
        }

        if(uNumberOfZeroesToRemove > 0)
            strTimestamp = strTimestamp.Substring(0, strTimestamp.GetLength() - 1U - uNumberOfZeroesToRemove);
    }
}

void DateTime::Decompose(unsigned int &uYear, unsigned int &uMonth, unsigned int &uDay, unsigned int &uHour, unsigned int &uMinute, unsigned int &uSecond, 
                          unsigned int &uMillisecond, unsigned int &uMicrosecond, unsigned int &uHundredOfNanosecond) const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The date / time is undefined");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYearProvisional = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYearProvisional = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYearProvisional - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYearProvisional * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYearProvisional > 3ULL && DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(uYearProvisional > 1ULL && (uYearProvisional < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)))
        {
            // Fixes the year value
            ++uYearProvisional;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    uYear = scast_z(uYearProvisional, unsigned int);

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMonth = 1;
        uDay = 1;
        uHour = 0;
        uMinute = 0;
        uSecond = 0;
        uMillisecond = 0;
        uMicrosecond = 0;
        uHundredOfNanosecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYearProvisional, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYearProvisional, int));
            uMonthCounter++;
        }
        
        uMonth = uMonthCounter;
        uDay = scast_z(uDaysInLastYear, unsigned int) + 1;

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        uHour = scast_z(uHoursInLastDay / _HNS_PER_HOUR, unsigned int);

        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        uMinute = scast_z(uMinutesInLastHour / _HNS_PER_MINUTE, unsigned int);

        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        uSecond = scast_z(uSecondsInLastMinute / _HNS_PER_SECOND, unsigned int);

        u64_z uMillisecondsInLastSecond = uSecondsInLastMinute % _HNS_PER_SECOND;
        uMillisecond = scast_z(uMillisecondsInLastSecond / _HNS_PER_MILLISECOND, unsigned int);

        u64_z uMicrosecondsInLastMillisecond = uMillisecondsInLastSecond % _HNS_PER_MILLISECOND;
        uMicrosecond = scast_z(uMicrosecondsInLastMillisecond / _HNS_PER_MICROSECOND, unsigned int);

        uHundredOfNanosecond = scast_z(uMicrosecondsInLastMillisecond % _HNS_PER_MICROSECOND, unsigned int);
    }
}

void DateTime::DecomposeDate(unsigned int &uYear, unsigned int &uMonth, unsigned int &uDay) const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The date is undefined");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYearProvisional = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYearProvisional = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYearProvisional - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYearProvisional * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYearProvisional > 3ULL && DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(uYearProvisional > 1ULL && (uYearProvisional < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)))
        {
            // Fixes the year value
            ++uYearProvisional;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    uYear = scast_z(uYearProvisional, unsigned int);

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMonth = 1;
        uDay = 1;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYearProvisional, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYearProvisional, int));
            uMonthCounter++;
        }
        
        uMonth = uMonthCounter;
        uDay = scast_z(uDaysInLastYear, unsigned int) + 1;
    }
}

void DateTime::DecomposeTime(unsigned int &uHour, unsigned int &uMinute, unsigned int &uSecond) const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The time is undefined");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYearProvisional = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYearProvisional = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYearProvisional - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYearProvisional * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYearProvisional > 3ULL && DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(uYearProvisional > 1ULL && (uYearProvisional < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)))
        {
            // Fixes the year value
            ++uYearProvisional;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uHour = 0;
        uMinute = 0;
        uSecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }
        
        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        uHour = scast_z(uHoursInLastDay / _HNS_PER_HOUR, unsigned int);

        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        uMinute = scast_z(uMinutesInLastHour / _HNS_PER_MINUTE, unsigned int);

        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        uSecond = scast_z(uSecondsInLastMinute / _HNS_PER_SECOND, unsigned int);
    }
}

void DateTime::DecomposeTime(unsigned int &uHour, unsigned int &uMinute, unsigned int &uSecond, unsigned int &uMillisecond, 
                              unsigned int &uMicrosecond, unsigned int &uHundredOfNanosecond) const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "The time is undefined");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYearProvisional = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYearProvisional = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYearProvisional - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYearProvisional * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYearProvisional > 3ULL && DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        else if(uYearProvisional > 1ULL && (uYearProvisional < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYearProvisional;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYearProvisional + 1ULL, int)))
        {
            // Fixes the year value
            ++uYearProvisional;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uHour = 0;
        uMinute = 0;
        uSecond = 0;
        uMillisecond = 0;
        uMicrosecond = 0;
        uHundredOfNanosecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYearProvisional, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        uHour = scast_z(uHoursInLastDay / _HNS_PER_HOUR, unsigned int);

        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        uMinute = scast_z(uMinutesInLastHour / _HNS_PER_MINUTE, unsigned int);

        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        uSecond = scast_z(uSecondsInLastMinute / _HNS_PER_SECOND, unsigned int);

        u64_z uMillisecondsInLastSecond = uSecondsInLastMinute % _HNS_PER_SECOND;
        uMillisecond = scast_z(uMillisecondsInLastSecond / _HNS_PER_MILLISECOND, unsigned int);

        u64_z uMicrosecondsInLastMillisecond = uMillisecondsInLastSecond % _HNS_PER_MILLISECOND;
        uMicrosecond = scast_z(uMicrosecondsInLastMillisecond / _HNS_PER_MICROSECOND, unsigned int);

        uHundredOfNanosecond = scast_z(uMicrosecondsInLastMillisecond % _HNS_PER_MICROSECOND, unsigned int);
    }
}

bool DateTime::_IsLeapYear(const int nYear)
{
    const unsigned int ABS_YEAR = SInteger::Abs(nYear);
    return (ABS_YEAR % 400U) == 0 || ((ABS_YEAR % 100U != 0) && (ABS_YEAR % 4U == 0));
}

TimeSpan DateTime::_GetInstantWithSubtractedTimeZoneOffset(const TimeSpan &instant, const TimeZone* pTimeZone) const
{
    DateTime localDateTime;
    localDateTime.m_instant = instant;

    TimeSpan timeZoneOffset(0);
    bool bOffsetIsNegative = false;
    pTimeZone->CalculateOffset(localDateTime, timeZoneOffset, bOffsetIsNegative);

    // The offset is subtracted to the calculated instant to make it UTC
    if(bOffsetIsNegative)
        localDateTime.m_instant += timeZoneOffset;
    else
        localDateTime.m_instant -= timeZoneOffset;

    return localDateTime.m_instant;
}

TimeSpan DateTime::_GetInstantWithAddedTimeZoneOffset(const TimeSpan &instant, const TimeZone* pTimeZone) const
{
    DateTime localDateTime;
    localDateTime.m_instant = instant;

    TimeSpan timeZoneOffset(0);
    bool bOffsetIsNegative = false;
    pTimeZone->CalculateOffset(localDateTime, timeZoneOffset, bOffsetIsNegative);

    // The offset is added to the calculated instant to make it UTC
    if(bOffsetIsNegative)
        localDateTime.m_instant -= timeZoneOffset;
    else
        localDateTime.m_instant += timeZoneOffset;

    return localDateTime.m_instant;
}


void DateTime::_ParseTimestampCompleteDate(const string_z &strTimestamp, const u32_z uTPosition, i32_z &nYear, u32_z &uMonth, u32_z &uDay) const
{
    static const char_z DATE_SEPARATOR = '-';

    // Gets the Date part only
    const string_z& DATE_PART = strTimestamp.Substring(0, uTPosition - 1);

    const int FIRST_SEPARATOR_POSITION = DATE_PART.IndexOf(DATE_SEPARATOR, 1U, EComparisonType::E_BinaryCaseSensitive); // Starts from 1 because it may have a "-" sign at the beginning

    if(FIRST_SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND)
    {
        // The date uses separators (YYYYY-MM-DD)
        const string_z& YEAR_PART  = DATE_PART.Substring(0,                            FIRST_SEPARATOR_POSITION - 1);
        const string_z& MONTH_PART = DATE_PART.Substring(FIRST_SEPARATOR_POSITION + 1, FIRST_SEPARATOR_POSITION + 2);
        const string_z& DAY_PART   = DATE_PART.Substring(FIRST_SEPARATOR_POSITION + 4, FIRST_SEPARATOR_POSITION + 5);
        nYear  = scast_z(YEAR_PART.ToInteger(),  i32_z);
        uMonth = scast_z(MONTH_PART.ToInteger(), u32_z);
        uDay   = scast_z(DAY_PART.ToInteger(),   u32_z);
    }
    else
    {
        // The date does not use separators (YYYYYMMDD)
        unsigned int uLength = DATE_PART.GetLength();
        const string_z& DAY_PART   = DATE_PART.Substring(uLength - 2U, uLength - 1U);
        const string_z& MONTH_PART = DATE_PART.Substring(uLength - 4U, uLength - 3U);
        const string_z& YEAR_PART  = DATE_PART.Substring(0,            uLength - 5U);
        nYear  = scast_z(YEAR_PART.ToInteger(),  i32_z);
        uMonth = scast_z(MONTH_PART.ToInteger(), u32_z);
        uDay   = scast_z(DAY_PART.ToInteger(),   u32_z);
    }

    // -0000 represents the year 1 BC, or -1, so it must be adjusted
    if(nYear <= 0)
        nYear -= 1;
}

void DateTime::_ParseTimestampCompleteTime(const string_z &strTimestamp, const u32_z uTPosition, u32_z &uHour, u32_z &uMinute, u32_z &uSecond, u32_z &uMillisecond, u32_z &uMicrosecond, u32_z &uHundredOfNanosecond, i32_z &nOffsetHours, u32_z& uOffsetMinutes) const
{
    static const char_z SECOND_FRACTION_SEPARATOR1 = '.';
    static const char_z SECOND_FRACTION_SEPARATOR2 = ',';
    static const char_z POSITIVE_SIGN = '+';
    static const char_z NEGATIVE_SIGN = '-';
    static const char_z ZULU_TIME = 'Z';

    const unsigned int FIRST_TIME_POSITION = uTPosition + 1U;

    const string_z& TIME_PART = strTimestamp.Substring(FIRST_TIME_POSITION, strTimestamp.GetLength());

    // Searches for a comma or a dot that indicate the presence of a second fraction
    int nFractionSeparatorPosition = TIME_PART.IndexOf(SECOND_FRACTION_SEPARATOR1, EComparisonType::E_BinaryCaseSensitive);
    if(nFractionSeparatorPosition == string_z::PATTERN_NOT_FOUND)
    {
        nFractionSeparatorPosition = TIME_PART.IndexOf(SECOND_FRACTION_SEPARATOR2, EComparisonType::E_BinaryCaseSensitive);
    }

    if(nFractionSeparatorPosition != string_z::PATTERN_NOT_FOUND)
    {
        // Contains a fraction

        const string_z& TIME_WITHOUT_FRACTION = TIME_PART.Substring(0, nFractionSeparatorPosition - 1);
        this->_ParseTimestampCompleteTimePart(TIME_WITHOUT_FRACTION, uHour, uMinute, uSecond);

        // Searches for a positive or a negative sign
        int nSignPosition = TIME_PART.IndexOf(POSITIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
        if(nSignPosition == string_z::PATTERN_NOT_FOUND)
        {
            nSignPosition = TIME_PART.IndexOf(NEGATIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
        }

        if(nSignPosition != string_z::PATTERN_NOT_FOUND)
        {
            // Contains a positive or negative sign

            const string_z& TIME_FRACTION = TIME_PART.Substring(nFractionSeparatorPosition + 1, nSignPosition - 1);
            this->_ParseTimestampTimeFraction(TIME_FRACTION, uMillisecond, uMicrosecond, uHundredOfNanosecond);
            const string_z& TIME_OFFSET = TIME_PART.Substring(nSignPosition, TIME_PART.GetLength() - 1U);
            this->_ParseTimestampTimeOffset(TIME_OFFSET, nOffsetHours, uOffsetMinutes);
        }
        else
        {
            // Does not contain a positive or negative sign

            nOffsetHours   = 0;
            uOffsetMinutes = 0;

            // Searches for a Z at the end
            unsigned int uLastPosition = TIME_PART.GetLength() - 1U;
            const string_z& LAST_CHAR = TIME_PART[uLastPosition];

            // If Z exists, the last position of the time part is one position before
            if(LAST_CHAR == ZULU_TIME)
                --uLastPosition;

            const string_z& TIME_FRACTION = TIME_PART.Substring(nFractionSeparatorPosition + 1, uLastPosition);
            this->_ParseTimestampTimeFraction(TIME_FRACTION, uMillisecond, uMicrosecond, uHundredOfNanosecond);
        }
    }
    else
    {
        // Does not contain a fraction
        uMillisecond = 0;
        uMicrosecond = 0;
        uHundredOfNanosecond = 0;

        // Searches for a positive or a negative sign
        int nSignPosition = TIME_PART.IndexOf(POSITIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
        if(nSignPosition == string_z::PATTERN_NOT_FOUND)
        {
            nSignPosition = TIME_PART.IndexOf(NEGATIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
        }

        if(nSignPosition != string_z::PATTERN_NOT_FOUND)
        {
            // Contains a positive or negative sign
            const string_z& TIME_WITHOUT_OFFSET = TIME_PART.Substring(0, nSignPosition - 1);
            this->_ParseTimestampCompleteTimePart(TIME_WITHOUT_OFFSET, uHour, uMinute, uSecond);

            const string_z& TIME_OFFSET = TIME_PART.Substring(nSignPosition, TIME_PART.GetLength() - 1U);
            this->_ParseTimestampTimeOffset(TIME_OFFSET, nOffsetHours, uOffsetMinutes);
        }
        else
        {
            // Does not contain a positive or negative sign
            nOffsetHours   = 0;
            uOffsetMinutes = 0;

            // Searches for a Z at the end
            unsigned int uLastPosition = TIME_PART.GetLength() - 1U;
            const string_z& LAST_CHAR = TIME_PART.Substring(uLastPosition, uLastPosition);

            // If Z exists, the last position of the time part is one position before
            if(LAST_CHAR == ZULU_TIME)
                --uLastPosition;

            this->_ParseTimestampCompleteTimePart(TIME_PART.Substring(0, uLastPosition), uHour, uMinute, uSecond);
        }
    }
}

void DateTime::_ParseTimestampCompleteTimePart(const string_z& strTimeWithoutFraction, u32_z& uHour, u32_z& uMinute, u32_z& uSecond) const
{
    static const char_z TIME_SEPARATOR = ':';

    // Calculates the separator space to be skipped in the next operation, depending on whether it exists or not
    u32_z uSeparatorSpace = 0;

    if(strTimeWithoutFraction.IndexOf(TIME_SEPARATOR, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND)
        uSeparatorSpace = 1U;

    const string_z& HOUR   = strTimeWithoutFraction.Substring(0, 1U);
    const string_z& MINUTE = strTimeWithoutFraction.Substring(2U + uSeparatorSpace, 3U + uSeparatorSpace);
    const string_z& SECOND = strTimeWithoutFraction.Substring(4U + uSeparatorSpace * 2U, 5U + uSeparatorSpace * 2U);

    uHour   = scast_z(HOUR.ToInteger(),   u32_z);
    uMinute = scast_z(MINUTE.ToInteger(), u32_z);
    uSecond = scast_z(SECOND.ToInteger(), u32_z);

    // 24 is allowed in a timestamp, but not as a valid hour in this class
    if(uHour == 24)
        uHour = 0;
}

void DateTime::_ParseTimestampTimeOffset(const string_z& strTimeOffset, i32_z& nOffsetHours, u32_z& uOffsetMinutes) const
{
    static const string_z TIME_SEPARATOR = ":";

    const string_z& HOURS = strTimeOffset.Substring(0, 2);
    nOffsetHours = scast_z(HOURS.ToInteger(), u32_z);

    // If the length is greater than 3, that means that it contains more than the hour part (hh:)
    if(strTimeOffset.GetLength() > 3)
    {
        const int SEPARATOR_POSITION = strTimeOffset.IndexOf(TIME_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);
        const u32_z SEPARATOR_WIDTH = SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND ? 1 : 0;

        const string_z& MINUTES = strTimeOffset.Substring(3U + SEPARATOR_WIDTH, 4 + SEPARATOR_WIDTH);
        uOffsetMinutes = scast_z(MINUTES.ToInteger(), u32_z);
    }
    else
    {
        uOffsetMinutes = 0;
    }
}

void DateTime::_ParseTimestampTimeFraction(const string_z& strTimeFraction, u32_z& uMillisecond, u32_z& uMicrosecond, u32_z& uHundredOfNanosecond) const
{
    static const double MAXIMUM_FRACTION_LENGTH = 7.0; // 3 numbers for milliseconds, 3 numbers for microseconds and 1 number for hundreds of nanoseconds
    const double FRACTION_LENGTH = scast_z(strTimeFraction.GetLength(), double);
    // Decimals must be multiplied by 10 N times depending on how many cyphers are there, regarding the maximum, which is set for hundreds of nanoseconds
    // For example: .0132 --> 0132 * 10^3 = 132000 hundreds of nanoseconds, where N = 3 because 7(max) - 4(length) = 3
    const unsigned int DECIMAL_OFFSET = scast_z(powl(10.0, MAXIMUM_FRACTION_LENGTH - FRACTION_LENGTH), unsigned int);

    unsigned int uHundredsOfNanoseconds = 0;

    if(FRACTION_LENGTH > MAXIMUM_FRACTION_LENGTH)
    {
        uHundredsOfNanoseconds = scast_z(strTimeFraction.Substring(0, scast_z(MAXIMUM_FRACTION_LENGTH, unsigned int) - 1U).ToInteger(), unsigned int);
    }
    else
    {
        uHundredsOfNanoseconds = scast_z(strTimeFraction.ToInteger(), unsigned int);
        uHundredsOfNanoseconds *= DECIMAL_OFFSET;
    }

    uMillisecond = uHundredsOfNanoseconds / DateTime::_HNS_PER_MILLISECOND;
    uMicrosecond = (uHundredsOfNanoseconds % DateTime::_HNS_PER_MILLISECOND) / DateTime::_HNS_PER_MICROSECOND;
    uHundredOfNanosecond = (uHundredsOfNanoseconds % DateTime::_HNS_PER_MICROSECOND);
}

void DateTime::_ParseTimestampIncompleteDateWithSeparators(const string_z &strTimestamp, const u32_z uFirstSeparatorPosition, i32_z &nYear, u32_z &uMonth, u32_z &uDay) const
{
    static const u32_z FIRST_DAY_NUMBER = 1;
    static const u32_z SEPARATOR_WIDTH = 1;
    const string_z& YEAR = strTimestamp.Substring(0, uFirstSeparatorPosition - 1U);
    const string_z& MONTH = strTimestamp.Substring(uFirstSeparatorPosition + SEPARATOR_WIDTH, uFirstSeparatorPosition + 2U * SEPARATOR_WIDTH);
    nYear  = scast_z(YEAR.ToInteger(), i32_z);
    uMonth = scast_z(MONTH.ToInteger(), u32_z);

    if(strTimestamp.GetLength() > uFirstSeparatorPosition + 2U * SEPARATOR_WIDTH)
    {
        const string_z& DAY = strTimestamp.Substring(uFirstSeparatorPosition + 4U);
        uDay = scast_z(DAY.ToInteger(), u32_z);
    }
    else
    {
        uDay = FIRST_DAY_NUMBER;
    }

    // -0000 represents the year 1 BC, or -1, so it must be adjusted
    if(nYear <= 0)
        nYear -= 1;
}

void DateTime::_ParseTimestampIncompleteDateWithoutSeparators(const string_z &strTimestamp, i32_z &nYear, u32_z &uMonth, u32_z &uDay) const
{
    static const u32_z FIRST_MONTH_NUMBER = 1;
    static const u32_z FIRST_DAY_NUMBER = 1;
    static const u32_z MAXIMUM_YEAR_SIZE_INCLUDING_SIGN = 6; // +YYYYY

    if(strTimestamp.GetLength() > MAXIMUM_YEAR_SIZE_INCLUDING_SIGN)
    {
        const u32_z LAST_POSITION = strTimestamp.GetLength() - 1U;
        const string_z& DAY = strTimestamp.Substring(LAST_POSITION - 1U, LAST_POSITION);
        const string_z& MONTH = strTimestamp.Substring(LAST_POSITION - 3U, LAST_POSITION - 2U);
        const string_z& YEAR = strTimestamp.Substring(0, LAST_POSITION - 4U);

        nYear  = scast_z(YEAR.ToInteger(), i32_z);
        uMonth = scast_z(MONTH.ToInteger(), u32_z);
        uDay   = scast_z(DAY.ToInteger(), u32_z);
    }
    else
    {
        nYear  = scast_z(strTimestamp.ToInteger(), i32_z);
        uMonth = FIRST_MONTH_NUMBER;
        uDay   = FIRST_DAY_NUMBER;
    }

    // -0000 represents the year 1 BC, or -1, so it must be adjusted
    if(nYear <= 0)
        nYear -= 1;
}

void DateTime::_ParseTimestampIncompleteTime(const string_z &strTimestamp, u32_z &uHour, u32_z &uMinute, u32_z &uSecond, u32_z &uMillisecond, 
                                             u32_z &uMicrosecond, u32_z &uHundredOfNanosecond, i32_z &nOffsetHours, u32_z& uOffsetMinutes) const
{
    static const string_z SECOND_FRACTION_SEPARATOR1 = ".";
    static const string_z SECOND_FRACTION_SEPARATOR2 = ",";
    static const string_z POSITIVE_SIGN = "+";
    static const string_z NEGATIVE_SIGN = "-";
    static const char_z ZULU_TIME = 'Z';

    const u32_z TIME_LENGTH = strTimestamp.GetLength();

    if(TIME_LENGTH > 2)
    {
        // There are more parts besides the hour

        int nFractionSeparator = strTimestamp.IndexOf(SECOND_FRACTION_SEPARATOR1, EComparisonType::E_BinaryCaseSensitive);
        if(nFractionSeparator == string_z::PATTERN_NOT_FOUND)
            nFractionSeparator = strTimestamp.IndexOf(SECOND_FRACTION_SEPARATOR2, EComparisonType::E_BinaryCaseSensitive);

        if(nFractionSeparator != string_z::PATTERN_NOT_FOUND)
        {
            // Contains a fraction
            const string_z& TIME_WITHOUT_FRACTION = strTimestamp.Substring(0, nFractionSeparator - 1U);
            this->_ParseTimestampIncompleteTimePart(TIME_WITHOUT_FRACTION, uHour, uMinute, uSecond);

            int nSignPosition = strTimestamp.IndexOf(POSITIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
            if(nSignPosition == string_z::PATTERN_NOT_FOUND)
                nSignPosition = strTimestamp.IndexOf(NEGATIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);

            if(nSignPosition != string_z::PATTERN_NOT_FOUND)
            {
                // Contains an offset

                const string_z& TIME_FRACTION = strTimestamp.Substring(nFractionSeparator + 1U, nSignPosition - 1U);
                this->_ParseTimestampTimeFraction(TIME_FRACTION, uMillisecond, uMicrosecond, uHundredOfNanosecond);
                const string_z& TIME_OFFSET = strTimestamp.Substring(nSignPosition, TIME_LENGTH - 1U);
                this->_ParseTimestampTimeOffset(TIME_OFFSET, nOffsetHours, uOffsetMinutes);
            }
            else
            {
                // Does not contain an offset
                nOffsetHours   = 0;
                uOffsetMinutes = 0;

                const u32_z Z_WIDTH = strTimestamp[TIME_LENGTH - 1U] == ZULU_TIME ? 1 : 0;
                const string_z& TIME_FRACTION = strTimestamp.Substring(nFractionSeparator + 1U, TIME_LENGTH - 1U - Z_WIDTH);
                this->_ParseTimestampTimeFraction(TIME_FRACTION, uMillisecond, uMicrosecond, uHundredOfNanosecond);
            }
        }
        else
        {
            // Does not contain a fraction

            int nSignPosition = strTimestamp.IndexOf(POSITIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);
            if(nSignPosition == string_z::PATTERN_NOT_FOUND)
                nSignPosition = strTimestamp.IndexOf(NEGATIVE_SIGN, EComparisonType::E_BinaryCaseSensitive);

            if(nSignPosition != string_z::PATTERN_NOT_FOUND)
            {
                // Contains an offset
                const string_z& TIME_WITHOUT_OFFSET = strTimestamp.Substring(0, nSignPosition - 1U);
                this->_ParseTimestampIncompleteTimePart(TIME_WITHOUT_OFFSET, uHour, uMinute, uSecond);
                const string_z& TIME_OFFSET = strTimestamp.Substring(nSignPosition, TIME_LENGTH - 1U);
                this->_ParseTimestampTimeOffset(TIME_OFFSET, nOffsetHours, uOffsetMinutes);
            }
            else
            {
                // Does not contain an offset
                nOffsetHours   = 0;
                uOffsetMinutes = 0;

                const u32_z Z_WIDTH = strTimestamp[TIME_LENGTH - 1U] == ZULU_TIME ? 1 : 0;

                const string_z& TIME_WITHOUT_Z = strTimestamp.Substring(0, TIME_LENGTH - 1U - Z_WIDTH);
                this->_ParseTimestampIncompleteTimePart(TIME_WITHOUT_Z, uHour, uMinute, uSecond);
            }

            uMillisecond = 0;
            uMicrosecond = 0;
            uHundredOfNanosecond = 0;
        }
    }
    else
    {
        // There is information about the hour only
        const string_z& HOUR = strTimestamp.Substring(0, 1);
        uHour = scast_z(HOUR.ToInteger(), u32_z);

        // 24 is allowed in a timestamp, but not as a valid hour in this class
        if(uHour == 24)
            uHour = 0;

        uMinute = 0;
        uSecond = 0;
        uMillisecond = 0;
        uMicrosecond = 0;
        uHundredOfNanosecond = 0;
        nOffsetHours = 0;
        uOffsetMinutes = 0;
    }
}

void DateTime::_ParseTimestampIncompleteTimePart(const string_z& strTimeWithoutFraction, u32_z& uHour, u32_z& uMinute, u32_z& uSecond) const
{
    static const string_z TIME_SEPARATOR = ":";

    const u32_z TIME_LENGTH = strTimeWithoutFraction.GetLength();
    const i32_z FISRT_SEPARATOR_POSITION = strTimeWithoutFraction.IndexOf(TIME_SEPARATOR, EComparisonType::E_BinaryCaseSensitive);

    const string_z& HOUR = strTimeWithoutFraction.Substring(0, 1);
    uHour = scast_z(HOUR.ToInteger(), u32_z);

    // 24:00 is allowed in a timestamp, but not as a valid hour in this class
    if(uHour == 24U)
        uHour = 0;

    if(FISRT_SEPARATOR_POSITION != string_z::PATTERN_NOT_FOUND)
    {
        // It uses separators

        const string_z& MINUTE = strTimeWithoutFraction.Substring(3U, 4U);
        uMinute = scast_z(MINUTE.ToInteger(), u32_z);

        // If the length is greater than 5 (hh:mm), it contains information about the second
        if(TIME_LENGTH > 5U)
        {
            const string_z& SECOND = strTimeWithoutFraction.Substring(6U, 7U);
            uSecond = scast_z(SECOND.ToInteger(), u32_z);
        }
        else
        {
            uSecond = 0;
        }
    }
    else if(TIME_LENGTH > 2U) // If the length is greater than 2 (hh), it contains information about the minute
    {
        // It does not use separators and has minutes

        const string_z& MINUTE = strTimeWithoutFraction.Substring(2U, 3U);
        uMinute = scast_z(MINUTE.ToInteger(), u32_z);

        if(TIME_LENGTH > 4U)// If the length is greater than 4 (hhmm), it contains information about the second
        {
            const string_z& SECOND = strTimeWithoutFraction.Substring(4U, 5U);
            uSecond = scast_z(SECOND.ToInteger(), u32_z);
        }
        else
        {
            uSecond = 0;
        }
    }
    else
    {
        uMinute = 0;
        uSecond = 0;
    }
}

void DateTime::_ApplyOffsetToTimestampWithoutAffectingDate(const i32_z nOffsetHours, const u32_z uOffsetMinutes, const u32_z uHour, const u32_z uMinute, DateTime &dateTime)
{
    static const TimeSpan _HNS_PER_DAY_TIMESPAN(DateTime::_HNS_PER_DAY);

    // The offset is subtracted to the time

    const i32_z OFFSET_SIGN = nOffsetHours < 0 ? -1 : 1;
    TimeSpan offset(DateTime::_HNS_PER_HOUR * scast_z(OFFSET_SIGN * nOffsetHours, u64_z) + DateTime::_HNS_PER_MINUTE * uOffsetMinutes);
    TimeSpan timeInHNS(DateTime::_HNS_PER_HOUR * uHour + DateTime::_HNS_PER_MINUTE * uMinute);

    if(nOffsetHours < 0) // The offset is negative, so it will be added
    {
        if(offset + timeInHNS > _HNS_PER_DAY_TIMESPAN)
            dateTime -= _HNS_PER_DAY_TIMESPAN - offset; // 1 day is subtracted to keep the date being 0001-01-01
        else
            dateTime += offset;
    }
    else if(nOffsetHours > 0 || uOffsetMinutes > 0) // The offset is positive, so it will be subtracted
    {
        if(offset > timeInHNS)
            dateTime += _HNS_PER_DAY_TIMESPAN - offset; // 1 day is added to keep the date being 0001-01-01
        else
            dateTime -= offset;
    }
}

void DateTime::_ApplyOffsetToTimestamp(const i32_z nOffsetHours, const u32_z uOffsetMinutes, const u32_z uHour, const u32_z uMinute, DateTime &dateTime)
{
    // The offset is subtracted to the time

    const i32_z OFFSET_SIGN = nOffsetHours < 0 ? -1 : 1;
    TimeSpan offset(DateTime::_HNS_PER_HOUR * scast_z(OFFSET_SIGN * nOffsetHours, u64_z) + DateTime::_HNS_PER_MINUTE * uOffsetMinutes);
    TimeSpan timeInHNS(DateTime::_HNS_PER_HOUR * uHour + DateTime::_HNS_PER_MINUTE * uMinute);

    if(nOffsetHours < 0) // The offset is negative, so it will be added
        dateTime += offset;
    else if(nOffsetHours > 0 || uOffsetMinutes > 0) // The offset is positive, so it will be subtracted
        dateTime -= offset;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool DateTime::IsLeapYear() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent either normal years or leap years");

    const unsigned int THIS_YEAR = this->GetYear();

    return DateTime::_IsLeapYear(scast_z(THIS_YEAR, int));
}

const TimeZone* DateTime::GetTimeZone() const
{
    return m_pTimeZone;
}

unsigned int DateTime::GetYear() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent years");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    return scast_z(uYear, unsigned int);
}

unsigned int DateTime::GetMonth() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent months");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uMonth = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMonth = 1;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        uMonth = uMonthCounter;
    }

    return scast_z(uMonth, unsigned int);
}

unsigned int DateTime::GetDay() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent days");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uDay = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uDay = 1;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        uDay = uDaysInLastYear + 1;
    }

    return scast_z(uDay, unsigned int);
}

unsigned int DateTime::GetHour() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent hours");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uHour = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uHour = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        uHour = uHoursInLastDay / _HNS_PER_HOUR;
    }

    return scast_z(uHour, unsigned int);
}

unsigned int DateTime::GetMinute() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent minutes");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uMinute = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMinute = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        uMinute = uMinutesInLastHour / _HNS_PER_MINUTE;
    }

    return scast_z(uMinute, unsigned int);
}

unsigned int DateTime::GetSecond() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent seconds");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uSecond = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uSecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        uSecond = uSecondsInLastMinute / _HNS_PER_SECOND;
    }

    return scast_z(uSecond, unsigned int);
}

unsigned int DateTime::GetMillisecond() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent milliseconds");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uMillisecond = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMillisecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        u64_z uMillisecondsInLastSecond = uSecondsInLastMinute % _HNS_PER_SECOND;
        uMillisecond = uMillisecondsInLastSecond / _HNS_PER_MILLISECOND;
    }

    return scast_z(uMillisecond, unsigned int);
}

unsigned int DateTime::GetMicrosecond() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent microseconds");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uMicrosecond = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uMicrosecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        u64_z uMillisecondsInLastSecond = uSecondsInLastMinute % _HNS_PER_SECOND;
        u64_z uMicrosecondsInLastMillisecond = uMillisecondsInLastSecond % _HNS_PER_MILLISECOND;
        uMicrosecond = uMicrosecondsInLastMillisecond / _HNS_PER_MICROSECOND;
    }

    return scast_z(uMicrosecond, unsigned int);
}

unsigned int DateTime::GetHundredOfNanosecond() const
{
    Z_ASSERT_ERROR(!this->IsUndefined(), "Undefined dates cannot represent nanoseconds");

    // Adds the time zone offset
    TimeSpan localTimeInstant = m_pTimeZone == null_z ? m_instant :
                                                         this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);

    u64_z uHundredOfNanosecond = 0;

    const u64_z HNS_IN_INSTANT = localTimeInstant.GetHundredsOfNanoseconds();

    const bool IS_NEGATIVE_DATE = HNS_IN_INSTANT < DateTime::_HALF_VALUE;

    // Depending on whether the date is negative or not, it is subtracted to the offset or vice versa
    u64_z uInputWithoutOffset = IS_NEGATIVE_DATE ?
                                                  DateTime::_HALF_VALUE - HNS_IN_INSTANT :
                                                  HNS_IN_INSTANT - DateTime::_HALF_VALUE;
    
    // If it is a positive date, the year-zero is added back
    if(!IS_NEGATIVE_DATE)
        uInputWithoutOffset += DateTime::_HNS_PER_YEAR;

    u64_z uYear = 1;
    u64_z uHnsInLastYear = uInputWithoutOffset;

    // Corner case: The year -1. Since the remaining time is substracted to the year, it will be lower than 1 year and hence the result would be zero
    if(uInputWithoutOffset >= DateTime::_HNS_PER_YEAR)
    {
        // Calculates the number of common years that have passed, including the extra days of the leap years (they are removed later)
        const u64_z NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS = uInputWithoutOffset / DateTime::_HNS_PER_YEAR;

        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS = NUMBER_OF_COMMON_YEARS_COUNTING_LEAP_DAYS - 1ULL;
        const u64_z APPROXIMATED_LEAP_DAYS = NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 4ULL - 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 100ULL + 
                                             NUMBER_OF_COMPLETE_PASSED_COMMON_YEARS_COUNTING_LEAP_DAYS / 400ULL;

        // Leap days are substracted to the original time
        const u64_z INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS = uInputWithoutOffset - APPROXIMATED_LEAP_DAYS * DateTime::_HNS_PER_DAY;

        // Counts the number of common years (extra days were substracted)
        uYear = INPUT_WITHOUT_OFFSET_WITHOUT_LEAP_DAYS / DateTime::_HNS_PER_YEAR;

        // Now we know the actual year enclosed in the input time, we can know the actual amount of leap days
        // Leap days are calculated as: (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400, as leap years rule states
        const u64_z ACTUAL_PASSED_COMPLETE_YEARS = uYear - 1ULL;
        const u64_z ACTUAL_LEAP_DAYS = ACTUAL_PASSED_COMPLETE_YEARS / 4ULL - 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 100ULL + 
                                       ACTUAL_PASSED_COMPLETE_YEARS / 400ULL;

        // Gets the amount of time passed in the last year
        uHnsInLastYear = uInputWithoutOffset - ACTUAL_LEAP_DAYS * DateTime::_HNS_PER_DAY - uYear * DateTime::_HNS_PER_YEAR;
    }

    if(IS_NEGATIVE_DATE)
    {
        if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is lower than or equal to 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //            [>]-|
            //             -->
            //                [<]----|

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - (DateTime::_HNS_PER_DAY - uHnsInLastYear);
        }
        else if(uYear > 3ULL && DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)) && uHnsInLastYear <= DateTime::_HNS_PER_DAY)
        {
            // Corner case: It is a leap year and the remaining time is grater than 1 day

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|______|______|______|______|______|______|
            //                    [>>>>>>]     ( <=366 days )
            //                           |--|

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(DateTime::_IsLeapYear(scast_z(uYear, int)) && uHnsInLastYear > DateTime::_HNS_PER_DAY && uHnsInLastYear <= 2ULL * DateTime::_HNS_PER_DAY)
        {
            // Corner case: The next year is a leap year and the remaining time is greater than 1 day and lower than or equal to 2 days

            //     -6     -5     -4     -3     -2     -1     +1     +2
            //  |______|______|_______|______|______|______|______|______|
            //                |     [<<<<<<<<|<<<<<<|<<<<<<]
            //                [>>>] |*|      
            //                |   | |*|
            //                |   |
            //             [>>>]|*| <---

            // The day is inverted and displaced to the beginning of the leap year
            uHnsInLastYear -= DateTime::_HNS_PER_DAY;
            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        else if(uYear > 1ULL && (uYear < 3ULL || uHnsInLastYear != 0)) // Remaining time is zero when it is the first instant of the year
        {
            // Note: year > 1 and year < 3 could be replaced by year == 2, obviously, but this way we can relate the limits with previous parts of the algorithm

            // The year is incremented. Since the remaining time was substracted to the year, it is normally 1 less than it should
            ++uYear;
        }
        
    }
    else if(uHnsInLastYear >= DateTime::_HNS_PER_YEAR)
    {
        // It is a positive year
        // If the remaining time in the last year is equal to or greater than 1 year, it is a leap year

        // There is a corner case: The first day of a leap year
        // It could not be accurately calculated previously, it is 1 year less than it actually is
        // This acts as a flag: If adding 1 year we get a leap year, then we are in the first day
        if(DateTime::_IsLeapYear(scast_z(uYear + 1ULL, int)))
        {
            // Fixes the year value
            ++uYear;

            // Removes the year to get just the remaining time in the first day
            uHnsInLastYear -= DateTime::_HNS_PER_YEAR;
        }
    }

    if(uHnsInLastYear == 0)
    {
        // Shourcut, it is the first instant of the year
        uHundredOfNanosecond = 0;
    }
    else
    {
        if(IS_NEGATIVE_DATE)
        {
            // The last year is reversed to get the actual remaining time
            if(DateTime::_IsLeapYear(scast_z(uYear, int)))
                uHnsInLastYear = DateTime::_HNS_PER_LEAPYEAR - uHnsInLastYear;
            else
                uHnsInLastYear = DateTime::_HNS_PER_YEAR - uHnsInLastYear;
        }

        u64_z uDaysInLastYear = uHnsInLastYear / DateTime::_HNS_PER_DAY;

        static const unsigned int FIRST_MONTH_OF_THE_YEAR = 1;
        static const unsigned int LAST_MONTH_OF_THE_YEAR  = 12;

        unsigned int uMonthCounter = FIRST_MONTH_OF_THE_YEAR;

        // For every month in the year, we subtract its number of days while the days in the current month
        // are lower than or equal to the remaining days
        while(uMonthCounter <= LAST_MONTH_OF_THE_YEAR && DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int)) <= uDaysInLastYear)
        {
            uDaysInLastYear -= DateTime::GetDaysInMonth(uMonthCounter, scast_z(uYear, int));
            uMonthCounter++;
        }

        u64_z uHoursInLastDay = uHnsInLastYear % _HNS_PER_DAY;
        u64_z uMinutesInLastHour = uHoursInLastDay % _HNS_PER_HOUR;
        u64_z uSecondsInLastMinute = uMinutesInLastHour % _HNS_PER_MINUTE;
        u64_z uMillisecondsInLastSecond = uSecondsInLastMinute % _HNS_PER_SECOND;
        u64_z uMicrosecondsInLastMillisecond = uMillisecondsInLastSecond % _HNS_PER_MILLISECOND;
        uHundredOfNanosecond = uMicrosecondsInLastMillisecond % _HNS_PER_MICROSECOND;
    }

    return scast_z(uHundredOfNanosecond, unsigned int);
}

DateTime DateTime::GetUtc() const
{
    return DateTime(*this, null_z);
}

const DateTime& DateTime::GetMaxDateTime()
{
    static const DateTime MAXIMUM_DATETIME(29228, 9, 14, 2, 48, 5, 477, 580, 7, TimeZone::UTC);
    return MAXIMUM_DATETIME;
}

const DateTime& DateTime::GetMinDateTime()
{
    static const DateTime MINIMUM_DATETIME(-29228, 4, 18, 21, 11, 54, 522, 419, 3, TimeZone::UTC);
    return MINIMUM_DATETIME;
}

bool DateTime::IsPositive() const
{
    bool bIsPositive = false;

    if(this->IsUndefined())
    {
        Z_ASSERT_ERROR(false, "The date is undefined, it cannot be positive");
    }
    else if(m_pTimeZone == null_z)
    {
        bIsPositive = m_instant.GetHundredsOfNanoseconds() >= DateTime::_HALF_VALUE;
    }
    else
    {
        // Adds the time zone offset before checking
        TimeSpan localTime = m_instant;
        localTime = this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);
        bIsPositive = localTime.GetHundredsOfNanoseconds() >= DateTime::_HALF_VALUE;
    }

    return bIsPositive;
}

bool DateTime::IsNegative() const
{
    bool bIsNegative = false;

    if(this->IsUndefined())
    {
        Z_ASSERT_ERROR(false, "The date is undefined, it cannot be negative");
    }
    else if(m_pTimeZone == null_z)
    {
        bIsNegative = m_instant.GetHundredsOfNanoseconds() < DateTime::_HALF_VALUE;
    }
    else
    {
        // Adds the time zone offset before checking
        TimeSpan localTime = m_instant;
        localTime = this->_GetInstantWithAddedTimeZoneOffset(m_instant, m_pTimeZone);
        bIsNegative = localTime.GetHundredsOfNanoseconds() < DateTime::_HALF_VALUE;
    }

    return bIsNegative;
}

bool DateTime::IsUndefined() const
{
    return m_instant == DateTime::_UNDEFINED_VALUE;
}

} // namespace z
