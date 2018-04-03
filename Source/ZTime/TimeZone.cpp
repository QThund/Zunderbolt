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

#include "ZTime/TimeZone.h"

#include "ZCommon/Assertions.h"


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

const TimeZone* TimeZone::UTC = null_z;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

TimeZone::TimeZone(const string_z &strId, const string_z &strName,
                     const TimeSpan &timeZoneOffset, const bool bIsTimeZoneOffsetNegative,
                     const TimeZone::DstInformation &dstInformation, const bool bHasDstOffset) :

            m_strName(strName),
            m_strId(strId),
            m_dstInformation(dstInformation),
            m_timeZoneOffset(timeZoneOffset),
            m_bTzOffsetIsNegative(bIsTimeZoneOffsetNegative),
            m_bHasDstOffset(bHasDstOffset)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void TimeZone::CalculateOffset(const DateTime &dateTime, TimeSpan &offset, bool &bIsNegative) const
{
    // DST started to be applied in 1916
    static const DateTime FIRST_DATETIME_WITH_DST(1916, 1, 1, TimeZone::UTC);

    // Boost can only process dates prior to the year 10.000
    static const DateTime MAXIMUM_DATETIME_WITH_DST = DateTime(10000, 1, 1, TimeZone::UTC) - TimeSpan(1);

    Z_ASSERT_ERROR(dateTime != DateTime::GetUndefinedDate(), "The input date is undefined");

    TimeSpan dstOffset(0);

    offset = m_timeZoneOffset;

    if(m_bHasDstOffset && dateTime >= FIRST_DATETIME_WITH_DST && dateTime < MAXIMUM_DATETIME_WITH_DST)
    {
        DateTime startDateTime = m_dstInformation.GetStartInYear(dateTime.GetYear());
        DateTime endDateTime = m_dstInformation.GetEndInYear(dateTime.GetYear());

        if(dateTime >= startDateTime && dateTime < endDateTime)
        {
            if(!m_bTzOffsetIsNegative && !m_dstInformation.IsOffsetNegative())
            {
                // Both offsets are positive, they are summed
                offset += m_dstInformation.GetOffset();
                bIsNegative = false;
            }
            else if(m_bTzOffsetIsNegative && m_dstInformation.IsOffsetNegative())
            {
                // Both are negative, they are summed
                offset += m_dstInformation.GetOffset();
                bIsNegative = true;
            }
            else if(m_timeZoneOffset >= m_dstInformation.GetOffset())
            {
                // Time zone offset is bigger or equals the DST offset, the result is the difference
                offset -= m_dstInformation.GetOffset();
                bIsNegative = m_bTzOffsetIsNegative;
            }
            else
            {
                // Time zone offset is smaller than the DST offset, the result is the difference
                offset = m_dstInformation.GetOffset() - offset;
                bIsNegative = m_dstInformation.IsOffsetNegative();
            }
        }
        else
        {
            bIsNegative = m_bTzOffsetIsNegative;
        }
    }
    else
    {
        bIsNegative = m_bTzOffsetIsNegative;
    }
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const TimeSpan& TimeZone::GetTimeZoneOffset() const
{
    return m_timeZoneOffset;
}


const string_z& TimeZone::GetName() const
{
    return m_strName;
}

const string_z& TimeZone::GetId() const
{
    return m_strId;
}

const bool TimeZone::IsTimeZoneOffsetNegative() const
{
    return m_bTzOffsetIsNegative;
}

const TimeZone::DstInformation& TimeZone::GetDstInfo() const
{
    return m_dstInformation;
}

const bool TimeZone::HasDstOffset() const
{
    return m_bHasDstOffset;
}

} // namespace z
