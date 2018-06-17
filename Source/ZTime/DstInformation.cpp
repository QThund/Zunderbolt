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
#include "ZCommon/DataTypes/SInteger.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

TimeZone::DstInformation::DstInformation(boost::local_time::time_zone_ptr pTimeZone)
{
    Z_ASSERT_ERROR(pTimeZone != boost::local_time::time_zone_ptr((boost::local_time::time_zone_ptr::element_type*) null_z), "Input time zone data must not be null");

    if(pTimeZone->has_dst())
    {
        m_bIsNegative = pTimeZone->dst_offset().is_negative();

        // The time offset to apply when DST is active
        m_offset = TimeSpan(0,
                             SInteger::Abs(pTimeZone->dst_offset().hours()),
                             SInteger::Abs(pTimeZone->dst_offset().minutes()),
                             SInteger::Abs(pTimeZone->dst_offset().seconds()),
                             0,
                             0,
                             0);
        
        m_pTimeZone = pTimeZone;
    }
    else
    {
        m_offset = TimeSpan(0ULL);
        m_bIsNegative = false;
        m_pTimeZone = boost::local_time::time_zone_ptr((boost::local_time::time_zone_ptr::element_type*) null_z);
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

DateTime TimeZone::DstInformation::GetStartInYear(const int nYear) const
{
    Z_ASSERT_ERROR(nYear != 0, "The input year cannot be zero");

    if(m_pTimeZone->has_dst() && nYear != 0)
    {
        // Does it return local time? or utc time?
        boost::posix_time::ptime startTime = m_pTimeZone->dst_local_start_time(nYear);

        return DateTime(nYear,
                         startTime.date().month(),
                         startTime.date().day(),
                         startTime.time_of_day().hours(),
                         startTime.time_of_day().minutes(), 
                         startTime.time_of_day().seconds(), 0, 0, 0, 0);
    }
    else
    {
        return DateTime::GetUndefinedDate();
    }
}

DateTime TimeZone::DstInformation::GetEndInYear(const int nYear) const
{
    Z_ASSERT_ERROR(nYear != 0, "The input year cannot be zero");

    if(m_pTimeZone->has_dst() && nYear != 0)
    {
        boost::posix_time::ptime endTime = m_pTimeZone->dst_local_end_time(nYear);

        return DateTime(nYear,
                         endTime.date().month(),
                         endTime.date().day(),
                         endTime.time_of_day().hours(),
                         endTime.time_of_day().minutes(), 
                         endTime.time_of_day().seconds(), 0, 0, 0, 0);
    }
    else
    {
        return DateTime::GetUndefinedDate();
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

const TimeSpan& TimeZone::DstInformation::GetOffset() const
{
    return m_offset;
}

const bool TimeZone::DstInformation::IsOffsetNegative() const
{
    return m_bIsNegative;
}


} // namespace z
