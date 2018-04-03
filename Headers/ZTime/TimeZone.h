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

#ifndef __TIMEZONE__
#define __TIMEZONE__

#include "ZTime/DateTime.h"
#include <boost/date_time/local_time/local_time.hpp>

#ifdef Z_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif



namespace z
{

/// <summary>
/// A time zone based on Greenwich Mean Time (GMT), to be used in Coordinated Universal Time (UTC) systems.
/// </summary>
/// <remarks>
/// Time zones are identified by a unique region name in the IANA/Olson time zone database. They also have an abbreviated name
/// intended to be part of ISO 8601 timestamps. The time offset of the time zone may be also affected by the Daylight Saving 
/// Time (DST) offset, which is only active during a limited time lapse in the year (normally, during summer). Both offsets can
/// be either positive or negative. DST will be applied only for dates between 1916 (the first year it was implemented) and
/// 10000 (due to a Boost's limitation).<br/>
/// This class is immutable.
/// </remarks>
class Z_LAYER_TIME_SYMBOLS TimeZone
{
    // INTERNAL CLASSES
    // ---------------
public:

    /// <summary>
    /// Information about a Daylight Saving Time (DST) range.
    /// </summary>
    /// <remarks>
    /// The date and time range during which DST is applied throughout the year depends on some rules specified by
    /// every country (for example, starting the first Sunday of March) and shall vary every year. The offset to
    /// apply can be either positive or negative.<br/>
    /// This class is immutable.
    /// </remarks>
    class Z_LAYER_TIME_SYMBOLS DstInformation
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives all the necessary data to calculate the DST offset and when is it applied.
        /// </summary>
        /// <param name="pTimeZone">[IN] Data to calculate the DST offset. It must not be null.</param>
        explicit DstInformation(boost::local_time::time_zone_ptr pTimeZone);


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Calculates the date and time when the DST offset starts taking effect.
        /// </summary>
        /// <remarks>
        /// Since the DST period is different for every year (although it repeats periodically), it must
        /// be calculated for a given year.
        /// </remarks>
        /// <param name="nYear">[IN] The year on which to base the date and time calculation. Zero is not a valid year value.</param>
        /// <returns>
        /// The first instant (UTC) the DST is active. If the year is zero, it will return an undefined date/time.
        /// </returns>
        DateTime GetStartInYear(const int nYear) const;

        /// <summary>
        /// Calculates the date and time when the DST offset stops taking effect.
        /// </summary>
        /// <remarks>
        /// Since the DST period is different for every year (although it repeats periodically), it must
        /// be calculated for a given year.
        /// </remarks>
        /// <param name="nYear">[IN] The year on which to base the date and time calculation. Zero is not a valid year value.</param>
        /// <returns>
        /// The first instant (UTC) the DST is not active. If the year is zero, it will return an undefined date/time.
        /// </returns>
        DateTime GetEndInYear(const int nYear) const;


        // PROPERTIES
        // ---------------
    public:

        /// <summary>
        /// Gets the offset to be applied when the DST is active.
        /// </summary>
        /// <returns>
        /// An amount of time to be subtracted or added to UTC time.
        /// </returns>
        const TimeSpan& GetOffset() const;
    
        /// <summary>
        /// Indicates whether the offset is negative or positive.
        /// </summary>
        /// <returns>
        /// True if the offset is negative; False otherwise.
        /// </returns>
        const bool IsOffsetNegative() const;
       

        // ATTRIBUTES
        // ---------------
    private:

        /// <summary>
        /// Boost time zone that is used to calculate the DST activation period.
        /// </summary>
        boost::local_time::time_zone_ptr m_pTimeZone;
       
        /// <summary>
        /// The DST offset.
        /// </summary>
        TimeSpan m_offset;

        /// <summary>
        /// Indicates whether the offset is negative (True) or positive (False).
        /// </summary>
        bool m_bIsNegative;

    };

        
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// A constant that represents UTC timezone.
    /// </summary>
    static const TimeZone* UTC;

    
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives all the information about the time zone, including DST.
    /// </summary>
    /// <remarks>
    /// Time zones are not intended to be instanced by users, they are created by the STimeZoneFactory class.
    /// </remarks>
    /// <param name="strId">[IN] The region Id in the IANA/Olson time zone database.</param>
    /// <param name="strName">[IN] The abbreviated name of the time zone to be added to timestamps.</param>
    /// <param name="timeZoneOffset">[IN] The offset to be applied to UTC time in order to get local time.</param>
    /// <param name="bIsTimeZoneOffsetNegative">[IN] Indicates whether the time zone offset is negative or positive. 
    /// True if it is negative, False otherwise.</param>
    /// <param name="dstInformation">[IN] Information about the DST period that may affect the final offset.</param>
    /// <param name="bHasDstOffset">[IN] Indicates whether the time zone is affected by the DST or not. True if it is 
    /// affected, False otherwise.</param>
    TimeZone(const string_z &strId, const string_z &strName, 
              const TimeSpan &timeZoneOffset, const bool bIsTimeZoneOffsetNegative, 
              const DstInformation &dstInformation, const bool bHasDstOffset);

private:

    // Hidden
    TimeZone(const TimeZone &timeZone);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Given a date and a time, it calculates the final offset to be applied to the UTC time in order to get
    /// the local time that corresponds to the time zone.
    /// </summary>
    /// <param name="dateTime">[IN] The date and time for which to calculate the offset. Its time zone does not affect the result. 
    /// It must not be undefined.</param>
    /// <param name="offset">[OUT] The final offset to apply to the UTC time.</param>
    /// <param name="bIsNegative">[OUT] The sign of the offset. True if it is negative, False otherwise.</param>
    void CalculateOffset(const DateTime &dateTime, TimeSpan &offset, bool &bIsNegative) const;


private:

    // Hidden
    TimeZone& operator=(const TimeZone &timeZone);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the offset of the time zone (without DST adjustment).
    /// </summary>
    /// <returns>
    /// An amount of time to be subtracted or added to UTC time.
    /// </returns>
    const TimeSpan& GetTimeZoneOffset() const;

    /// <summary>
    /// Gets the abbreviated name of the time zone to be added to timestamps.
    /// </summary>
    /// <returns>
    /// The abbreviated name of the time zone.
    /// </returns>
    const string_z& GetName() const;

    /// <summary>
    /// Gets the region Id in the IANA/Olson time zone database.
    /// </summary>
    /// <returns>
    /// The region Id of the time zone.
    /// </returns>
    const string_z& GetId() const;

    /// <summary>
    /// Indicates whether the time zone offset is negative or not.
    /// </summary>
    /// <returns>
    /// True if the offset is negative; False otherwise.
    /// </returns>
    const bool IsTimeZoneOffsetNegative() const;

    /// <summary>
    /// Gets the information about the DST adjustment.
    /// </summary>
    /// <returns>
    /// A reference to the DST information of the time zone.
    /// </returns>
    const DstInformation& GetDstInfo() const;

    /// <summary>
    /// Indicates whether the time zone may be affected by the DST adjustment or not.
    /// </summary>
    /// <returns>
    /// True if there is DST information; False otherwise.
    /// </returns>
    const bool HasDstOffset() const;


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The abbreviated name of the time zone to be added to timestamps.
    /// </summary>
    string_z m_strName;

    /// <summary>
    /// The region Id in the IANA/Olson time zone database.
    /// </summary>
    string_z m_strId;

    /// <summary>
    /// The information about the DST adjustment.
    /// </summary>
    DstInformation m_dstInformation;

    /// <summary>
    /// The offset of the time zone (without DST adjustment).
    /// </summary>
    TimeSpan m_timeZoneOffset;
    
    /// <summary>
    /// Indicates whether the time zone offset is negative or not. True if the offset is negative; False otherwise.
    /// </summary>
    bool m_bTzOffsetIsNegative;

    /// <summary>
    /// Indicates whether the time zone may be affected by the DST adjustment or not. True if there is DST information; False otherwise.
    /// </summary>
    bool m_bHasDstOffset;
};

} // namespace z


#endif // __TIMEZONE__
