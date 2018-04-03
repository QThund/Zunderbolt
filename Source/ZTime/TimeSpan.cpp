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


#include "ZTime/TimeSpan.h"
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/SInteger.h"


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
const u64_z TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND = 10;
const u64_z TimeSpan::HOURS_PER_DAY = 24;
const u64_z TimeSpan::MINUTES_PER_HOUR = 60;
const u64_z TimeSpan::SECONDS_PER_MINUTE = 60;
const u64_z TimeSpan::MILLISECONDS_PER_SECOND = 1000;
const u64_z TimeSpan::MICROSECONDS_PER_MILLISECOND = 1000;
const u64_z TimeSpan::MAXIMUM_VALUE = -1;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################


TimeSpan::TimeSpan(const u64_z uDays, const u64_z uHours, const u64_z uMinutes, const u64_z uSeconds, const u64_z uMilliseconds, const u64_z uMicroseconds, const u64_z uHundredsNanoseconds)
{
    // Constants containing the max value for each parameter.
    // Remember we have to convert them to hundreds of nanoseconds.
    const u64_z MAX_MICROSECONDS = MAXIMUM_VALUE / HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;
    const u64_z MAX_MILLISECONDS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MICROSECONDS_PER_MILLISECOND );
    const u64_z MAX_SECONDS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_z MAX_MINUTES = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_z MAX_HOURS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);
    const u64_z MAX_DAYS = MAXIMUM_VALUE / (HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND);

    bool bNotGreaterThanMaxValue = (uDays <= MAX_DAYS                &&
                                   uHours <= MAX_HOURS               &&
                                   uMinutes <= MAX_MINUTES           &&
                                   uSeconds <= MAX_SECONDS           &&
                                   uMilliseconds <= MAX_MILLISECONDS &&
                                   uMicroseconds <= MAX_MICROSECONDS &&
                                   uHundredsNanoseconds <= MAXIMUM_VALUE);

    // Assertion to verify that we will not get overflow while calculating the time span
    Z_ASSERT_WARNING(bNotGreaterThanMaxValue == true, "Parameters must be lower than maximum values");

    // To avoid overflow if it happens return max value allowed
    if (!bNotGreaterThanMaxValue)
    {
          m_uTimeSpan = MAXIMUM_VALUE;
    }
    else
    {
        u64_z uMicrosecondsToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * uMicroseconds;
        u64_z uMillisecondsToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * TimeSpan::MICROSECONDS_PER_MILLISECOND * uMilliseconds;
        u64_z uSecondsToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * TimeSpan::MILLISECONDS_PER_SECOND * uSeconds * TimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_z uMinutesToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * TimeSpan::SECONDS_PER_MINUTE * uMinutes * TimeSpan::MILLISECONDS_PER_SECOND * TimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_z uHoursToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * TimeSpan::MINUTES_PER_HOUR * uHours * TimeSpan::SECONDS_PER_MINUTE * TimeSpan::MILLISECONDS_PER_SECOND * TimeSpan::MICROSECONDS_PER_MILLISECOND;
        u64_z uDaysToHundreds = TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND * TimeSpan::HOURS_PER_DAY * uDays * TimeSpan::MINUTES_PER_HOUR * TimeSpan::SECONDS_PER_MINUTE * TimeSpan::MILLISECONDS_PER_SECOND * TimeSpan::MICROSECONDS_PER_MILLISECOND;

        // Now check that we will not have overflow with the addition either
        bNotGreaterThanMaxValue = uMicrosecondsToHundreds <= (MAXIMUM_VALUE - uHundredsNanoseconds ) &&
                                  uMillisecondsToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds)) &&
                                  uSecondsToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds)) &&
                                  uMinutesToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds)) &&
                                  uHoursToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds)) &&
                                  uDaysToHundreds <= (MAXIMUM_VALUE - (uHundredsNanoseconds + uMicrosecondsToHundreds + uMillisecondsToHundreds + uSecondsToHundreds + uMinutesToHundreds + uHoursToHundreds));

        Z_ASSERT_WARNING(bNotGreaterThanMaxValue == true, "The converted values must be low enough to avoid overflow");

        // To avoid overflow if it happens return max value allowed
        if (!bNotGreaterThanMaxValue)
        {
           m_uTimeSpan = MAXIMUM_VALUE;
        }
        else
        {
           // Add all the parameters
           m_uTimeSpan = uHundredsNanoseconds + uMicrosecondsToHundreds +
                         uMillisecondsToHundreds + uSecondsToHundreds +
                         uMinutesToHundreds + uHoursToHundreds + uDaysToHundreds;
        }
    }

}


TimeSpan::TimeSpan(const TimeSpan& timeSpan)
{
    m_uTimeSpan = timeSpan.m_uTimeSpan;
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS             |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

TimeSpan& TimeSpan::operator= (const TimeSpan& timeSpan)
{
    m_uTimeSpan = timeSpan.m_uTimeSpan;
    return *this;
}

TimeSpan TimeSpan::operator+ (const TimeSpan& timeSpan) const
{
    return TimeSpan(*this) += timeSpan;
}

TimeSpan& TimeSpan::operator+= (const TimeSpan& timeSpan)
{
    bool bNotGreaterThanMaxValue = ((TimeSpan::MAXIMUM_VALUE  - this->m_uTimeSpan) >= timeSpan.m_uTimeSpan);
    // Assertion to verify that we will not get overflow while calculating the time span
    Z_ASSERT_WARNING(bNotGreaterThanMaxValue == true, "The addition of the two timespan objects can not be higher than maximum value");

    if (bNotGreaterThanMaxValue)
    {
        this->m_uTimeSpan += timeSpan.m_uTimeSpan;
    }
    else
    {
        this->m_uTimeSpan = TimeSpan::MAXIMUM_VALUE;
    }

    return *this;
}

TimeSpan& TimeSpan::operator-= (const TimeSpan& timeSpan)
{
    this->m_uTimeSpan = (this->m_uTimeSpan < timeSpan.m_uTimeSpan) ? (timeSpan.m_uTimeSpan - this->m_uTimeSpan) : (this->m_uTimeSpan - timeSpan.m_uTimeSpan);
    return *this;
}

TimeSpan TimeSpan::operator- (const TimeSpan& timeSpan) const
{
    return TimeSpan(*this) -= timeSpan;
}

bool TimeSpan::operator> (const TimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan > timeSpan.m_uTimeSpan);
}

bool TimeSpan::operator>= (const TimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan >= timeSpan.m_uTimeSpan);
}

bool TimeSpan::operator< (const TimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan < timeSpan.m_uTimeSpan);
}

bool TimeSpan::operator<= (const TimeSpan& timeSpan) const
{
    return (this->m_uTimeSpan <= timeSpan.m_uTimeSpan);
}

u32_z TimeSpan::GetDays() const
{
    return scast_z(m_uTimeSpan / (TimeSpan::HOURS_PER_DAY *
                                  TimeSpan::MINUTES_PER_HOUR *
                                  TimeSpan::SECONDS_PER_MINUTE *
                                  TimeSpan::MILLISECONDS_PER_SECOND *
                                  TimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_z);
}

u32_z TimeSpan::GetHours() const
{
    return scast_z(m_uTimeSpan / (TimeSpan::MINUTES_PER_HOUR *
                                  TimeSpan::SECONDS_PER_MINUTE *
                                  TimeSpan::MILLISECONDS_PER_SECOND *
                                  TimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_z);
}

u32_z TimeSpan::GetMinutes() const
{
    return scast_z(m_uTimeSpan / (TimeSpan::SECONDS_PER_MINUTE *
                                  TimeSpan::MILLISECONDS_PER_SECOND *
                                  TimeSpan::MICROSECONDS_PER_MILLISECOND *
                                  TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND), u32_z);
}

u64_z TimeSpan::GetSeconds() const
{
    return m_uTimeSpan / (TimeSpan::MILLISECONDS_PER_SECOND *
                          TimeSpan::MICROSECONDS_PER_MILLISECOND *
                          TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND);
}

u64_z TimeSpan::GetMilliseconds() const
{
    return m_uTimeSpan / (TimeSpan::MICROSECONDS_PER_MILLISECOND *
                          TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND);
}

u64_z TimeSpan::GetMicroseconds() const
{
    return m_uTimeSpan / TimeSpan::HUNDREDS_OF_NANOSECONDS_PER_MICROSECOND;
}

u64_z TimeSpan::GetHundredsOfNanoseconds() const
{
    return m_uTimeSpan;
}

string_z TimeSpan::ToString() const
{
    return string_z::FromInteger<u64_z>(m_uTimeSpan);
}

} // namespace z
