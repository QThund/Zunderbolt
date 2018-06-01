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

#ifndef __TIMESPAN__
#define __TIMESPAN__

#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZTime/TimeModuleDefinitions.h"


namespace z
{


/// <summary>
/// Represents a time span with an accuracy of hundreds of nanoseconds.
/// </summary>
class Z_TIME_MODULE_SYMBOLS TimeSpan
{

    // CONSTANTS
    // ---------------
private:

    /// <summary>
    /// Constant representing the factor to convert from microseconds to hundreds of nanoseconds.
    /// </summary>
    static const u64_z HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;

    /// <summary>
    /// Constant representing the factor to convert from days to hours.
    /// </summary>
    static const u64_z HOURS_PER_DAY;

    /// <summary>
    /// Constant representing the factor to convert from hours to minutes.
    /// </summary>
    static const u64_z MINUTES_PER_HOUR;

    /// <summary>
    /// Constant representing the factor to convert from minutes to seconds.
    /// </summary>
    static const u64_z SECONDS_PER_MINUTE;

    /// <summary>
    /// Constant representing the factor to convert from seconds to milliseconds.
    /// </summary>
    static const u64_z MILLISECONDS_PER_SECOND;

    /// <summary>
    /// Constant representing the factor to convert from milliseconds to nanoseconds.
    /// </summary>
    static const u64_z MICROSECONDS_PER_MILLISECOND;

    /// <summary>
    /// The maximum value allowed for the type used to store the time value.
    /// </summary>
    static const u64_z MAXIMUM_VALUE;

    // CONSTRUCTORS
     // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    inline TimeSpan() : m_uTimeSpan(0)
    {
    }

    /// <summary>
    /// Constructor that receives a value containing a time span.
    /// </summary>
    /// <param name="uTimeValue">[IN] Value containing a time span in hundreds of nanoseconds.</param>
    explicit inline TimeSpan(const u64_z uTimeValue) : m_uTimeSpan(uTimeValue)
    {
    }

    /// <summary>
    /// Constructor from different units of time.
    /// </summary>
    /// <remarks>
    /// If the number of days, hours, etc. exceeds the maximum quantity of time that a TimeSpan can represent, then it will be set to the maximum value possible.
    /// </remarks>
    /// <param name="uDays">[IN] Number of days.</param>
    /// <param name="uHours">[IN] Number of hours.</param>
    /// <param name="uMinutes">[IN] Number of minutes.</param>
    /// <param name="uSeconds">[IN] Number of seconds.</param>
    /// <param name="uMilliseconds">[IN] Number of milliseconds.</param>
    /// <param name="uMicroseconds">[IN] Number of microseconds.</param>
    /// <param name="uHundredsNanoseconds">[IN] Number of hundreds of nanoseconds.</param>
    TimeSpan(const u64_z uDays,
              const u64_z uHours,
              const u64_z uMinutes,
              const u64_z uSeconds,
              const u64_z uMilliseconds,
              const u64_z uMicroseconds,
              const u64_z uHundredsNanoseconds);

    /// <summary>
    /// Copy constructor. Copies the content of the given time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance that will be used to copy from.</param>
    TimeSpan(const TimeSpan& timeSpan);


    // METHODS
    // --------------
public:

    /// <summary>
    /// Assignment operator. Assigns the provided time span object to the resident time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to be copied from.</param>
    /// <returns>
    /// Reference to the assigned time span.
    /// </returns>
    TimeSpan& operator= (const TimeSpan& timeSpan);

    /// <summary>
    /// Addition operator. Adds two time span objects.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to add.</param>
    /// <remarks>
    /// If the result of the addition exceeds the maximum quantity of time that a TimeSpan can represent, then it will be set to the maximum value possible.
    /// </remarks>
    /// <returns>
    /// Time span object containing the result of the adition.
    /// </returns>
    TimeSpan operator+ (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Addition and assignment operator.
    /// </summary>
    /// <remarks>
    /// Resident time span stores the result of the addition. If the result of the addition exceeds the maximum quantity of time that a TimeSpan can represent,
    /// then it will be set to the maximum value possible.
    /// </remarks>
    /// <param name="timeSpan">[IN] The time span to be added.</param>
    /// <returns>
    /// The modified TimeSpan object.
    /// </returns>
    TimeSpan& operator+= (const TimeSpan& timeSpan);

    /// <summary>
    /// Subtraction and assignment operator.
    /// </summary>
    /// <remarks>
    /// The result of the subtraction will be always positive.
    /// When one time span is bigger than the other, and the bigger is subtracted to the smaller one, the result will be the difference, which is positive.
    /// This means that it cannot be used in complex arithmetic operations, for example: 3 - 5 - 6 == 4 instead of -4, -8 or 8, because 3 - 5 == +2, and then 2 - 6 == +4.
    /// </remarks>
    /// <param name="timeSpan">[IN] The time span to be subtracted.</param>
    /// <returns>
    /// The modified TimeSpan object.
    /// </returns>
    TimeSpan& operator-= (const TimeSpan& timeSpan);

    /// <summary>
    /// Subtraction operator. Subtracts two time span objects.
    /// </summary>
    /// <remarks>
    /// The result of the subtraction will be always positive.
    /// When one time span is bigger than the other, and the bigger is subtracted to the smaller one, the result will be the difference, which is positive.
    /// This means that it cannot be used in complex arithmetic operations, for example: 3 - 5 - 6 == 4 instead of -4, -8 or 8, because 3 - 5 == +2, and then 2 - 6 == +4.
    /// </remarks>
    /// <param name="timeSpan">[IN] Time span instance to subtract.</param>
    /// <returns>
    /// Time span object containing the result of the subtraction.
    /// </returns>
    TimeSpan operator- (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Equality operator. Indicates whether the value of the left time span is equal to the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the objects are equal. False otherwise.
    /// </returns>
    inline bool operator== (const TimeSpan& timeSpan) const
    {
        return (this->m_uTimeSpan == timeSpan.m_uTimeSpan);
    }

    /// <summary>
    /// Inequality operator. Indicates whether the value of the left time span is not equal to the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the objects are NOT equal. False otherwise.
    /// </returns>
    inline bool operator!= (const TimeSpan& timeSpan) const
    {
        return (this->m_uTimeSpan != timeSpan.m_uTimeSpan);
    }

    /// <summary>
    /// Greater than operator. Indicates whether the value of the left time span is greater than the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the first time span is greater than the second one. False otherwise.
    /// </returns>
    bool operator> (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Greater than or equal to operator. Indicates whether the value of the left time span is greater than or equal to the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the first time span is greater than or equal to the second one. False otherwise.
    /// </returns>
    bool operator>= (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Less than operator. Indicates whether the value of the left time span is shorter than the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the first time span is shorter than the second one. False otherwise.
    /// </returns>
    bool operator< (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Less than or equal to operator. Indicates whether the value of the left time span is shorter than or equal to the value of the right time span.
    /// </summary>
    /// <param name="timeSpan">[IN] Time span instance to compare.</param>
    /// <returns>
    /// True if the first time span is shorter than or equal to the second one. False otherwise.
    /// </returns>
    bool operator<= (const TimeSpan& timeSpan) const;

    /// <summary>
    /// Gets the length of the time span, in days.
    /// </summary>
    /// <returns>
    /// The number of complete days.
    /// </returns>
    u32_z GetDays() const;

    /// <summary>
    /// Gets the length of the time span, in hours.
    /// </summary>
    /// <returns>
    /// The number of complete hours.
    /// </returns>
    u32_z GetHours() const;

    /// <summary>
    /// Gets the length of the time span, in minutes.
    /// </summary>
    /// <returns>
    /// The number of complete minutes.
    /// </returns>
    u32_z GetMinutes() const;

    /// <summary>
    /// Gets the length of the time span, in seconds.
    /// </summary>
    /// <returns>
    /// The number of complete seconds.
    /// </returns>
    u64_z GetSeconds() const;

    /// <summary>
    /// Gets the length of the time span, in milliseconds.
    /// </summary>
    /// <returns>
    /// The number of complete milliseconds.
    /// </returns>
    u64_z GetMilliseconds() const;

    /// <summary>
    /// Gets the length of the time span, in microseconds.
    /// </summary>
    /// <returns>
    /// The number of complete microseconds.
    /// </returns>
    u64_z GetMicroseconds() const;

    /// <summary>
    /// Gets the length of the time span, in hundreds of nanoseconds.
    /// </summary>
    /// <returns>
    /// The number of hundreds of nanoseconds.
    /// </returns>
    u64_z GetHundredsOfNanoseconds() const;

    /// <summary>
    /// Converts and returns the time span representation as string.
    /// </summary>
    /// <returns>
    /// Time span representation as string.
    /// </returns>
    string_z ToString() const;

    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// Variable representing a time span in hundreds of nanoseconds. Using unsigned long long(64 bits).
    /// </summary>
    u64_z m_uTimeSpan;

};

} // namespace z


#endif // __TIMESPAN__
