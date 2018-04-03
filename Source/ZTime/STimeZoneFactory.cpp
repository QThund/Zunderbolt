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

#include "ZTime/STimeZoneFactory.h"

#include "ZTime/DateTime.h"
#include "ZTime/TimeZone.h"
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZContainers/Dictionary.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const TimeZone* STimeZoneFactory::GetTimeZoneById(const string_z &strId)
{
    static bool bTimeZoneDatabaseInitialized = false;
    static boost::local_time::tz_database timeZoneDatabase;
    static Dictionary<string_z, TimeZone*> timeZones(382); // 382 time zones in TimeZoneDatabase.cpp

    TimeZone* pTimeZoneResult = null_z;

    // Initializes the time zone database
    if(!bTimeZoneDatabaseInitialized)
    {
        bTimeZoneDatabaseInitialized = STimeZoneFactory::Initialize(STimeZoneFactory::TIME_ZONE_DATABASE, timeZoneDatabase);
    }

    Dictionary<string_z, TimeZone*>::ConstIterator timeZoneIterator = timeZones.PositionOfKey(strId);

    if(!timeZoneIterator.IsEnd())
    {
        // If the time zone already existed, it is returned directly
        pTimeZoneResult = timeZoneIterator->GetValue();
    }
    else
    {
#if Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_UNICODE
        ArrayResult<i8_z> arId = strId.ToBytes(ETextEncoding::E_ASCII);
        boost::local_time::time_zone_ptr pTimeZone = timeZoneDatabase.time_zone_from_region(arId.Get());
#elif Z_CONFIG_CHARACTERSET_DEFAULT == Z_CONFIG_CHARACTERSET_ASCII
        boost::local_time::time_zone_ptr pTimeZone = timeZoneDatabase.time_zone_from_region(strId);
#endif

        Z_ASSERT_ERROR(pTimeZone != null_z, "The provided ID does not match any time zone available");
        
        // Copies the time zone information
        if(pTimeZone != null_z)
        {
            const string_z TIMEZONE_NAME = pTimeZone->std_zone_abbrev().c_str();
            const bool IS_TZ_NEGATIVE    = pTimeZone->base_utc_offset().is_negative();

            const TimeSpan TIMEZONE_OFFSET = TimeSpan(0,
                                                        SInteger::Abs(pTimeZone->base_utc_offset().hours()),
                                                        SInteger::Abs(pTimeZone->base_utc_offset().minutes()),
                                                        SInteger::Abs(pTimeZone->base_utc_offset().seconds()),
                                                        0, 
                                                        0, 
                                                        0);

            TimeZone::DstInformation dstInfo(pTimeZone);

            pTimeZoneResult = new TimeZone(strId, 
                                            TIMEZONE_NAME, 
                                            TIMEZONE_OFFSET, 
                                            IS_TZ_NEGATIVE,
                                            dstInfo,
                                            pTimeZone->has_dst());

            timeZones.Add(strId, pTimeZoneResult);
        }
    }

    return pTimeZoneResult;
}

bool STimeZoneFactory::Initialize(const char* szSource, boost::local_time::tz_database &database)
{
    bool bResult = false;
    std::istringstream dataBaseStream;
    dataBaseStream.str(szSource);

    database.load_from_stream(dataBaseStream);
    bResult = true;

    return bResult;
}

} // namespace z
