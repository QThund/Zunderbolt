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

#include "ZTiming/LocalTimeZone.h"

#include "ZTime/STimeZoneFactory.h"
#include "ZCommon/Assertions.h"

#if defined(Z_OS_WINDOWS)
    #include <Windows.h>

    #if defined(Z_COMPILER_GCC) // Only when using MinGW
        #include "Workarounds/WinBase_Workarounds.h"
    #endif

#elif defined(Z_OS_LINUX)
    #include <fstream>
#endif


namespace z
{
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#ifdef Z_OS_WINDOWS

const std::pair<string_z, string_z> LocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[] =
    {
        std::pair<string_z, string_z>(Z_L("AUS Central Standard Time"),    Z_L("Australia/Darwin")),
        std::pair<string_z, string_z>(Z_L("AUS Eastern Standard Time"),    Z_L("Australia/Sydney")),
        std::pair<string_z, string_z>(Z_L("Afghanistan Standard Time"),    Z_L("Asia/Kabul")),
        std::pair<string_z, string_z>(Z_L("Alaskan Standard Time"),    Z_L("America/Anchorage")),
        std::pair<string_z, string_z>(Z_L("Arab Standard Time"),    Z_L("Asia/Riyadh")),
        std::pair<string_z, string_z>(Z_L("Arabian Standard Time"),    Z_L("Asia/Dubai")),
        std::pair<string_z, string_z>(Z_L("Arabic Standard Time"),    Z_L("Asia/Baghdad")),
        std::pair<string_z, string_z>(Z_L("Argentina Standard Time"),    Z_L("America/Buenos_Aires")),
        std::pair<string_z, string_z>(Z_L("Atlantic Standard Time"),    Z_L("America/Halifax")),
        std::pair<string_z, string_z>(Z_L("Azerbaijan Standard Time"),    Z_L("Asia/Baku")),
        std::pair<string_z, string_z>(Z_L("Azores Standard Time"),    Z_L("Atlantic/Azores")),
        std::pair<string_z, string_z>(Z_L("Bahia Standard Time"),    Z_L("America/Bahia")),
        std::pair<string_z, string_z>(Z_L("Bangladesh Standard Time"),    Z_L("Asia/Dhaka")),
        std::pair<string_z, string_z>(Z_L("Canada Central Standard Time"),    Z_L("America/Regina")),
        std::pair<string_z, string_z>(Z_L("Cape Verde Standard Time"),    Z_L("Atlantic/Cape_Verde")),
        std::pair<string_z, string_z>(Z_L("Caucasus Standard Time"),    Z_L("Asia/Yerevan")),
        std::pair<string_z, string_z>(Z_L("Cen. Australia Standard Time"),    Z_L("Australia/Adelaide")),
        std::pair<string_z, string_z>(Z_L("Central America Standard Time"),    Z_L("America/Guatemala")),
        std::pair<string_z, string_z>(Z_L("Central Asia Standard Time"),    Z_L("Asia/Almaty")),
        std::pair<string_z, string_z>(Z_L("Central Brazilian Standard Time"),    Z_L("America/Cuiaba")),
        std::pair<string_z, string_z>(Z_L("Central Europe Standard Time"),    Z_L("Europe/Budapest")),
        std::pair<string_z, string_z>(Z_L("Central European Standard Time"),    Z_L("Europe/Warsaw")),
        std::pair<string_z, string_z>(Z_L("Central Pacific Standard Time"),    Z_L("Pacific/Guadalcanal")),
        std::pair<string_z, string_z>(Z_L("Central Standard Time"),    Z_L("America/Chicago")),
        std::pair<string_z, string_z>(Z_L("Central Standard Time (Mexico)"),    Z_L("America/Mexico_City")),
        std::pair<string_z, string_z>(Z_L("China Standard Time"),    Z_L("Asia/Shanghai")),
        std::pair<string_z, string_z>(Z_L("Dateline Standard Time"),    Z_L("Etc/GMT+12")),
        std::pair<string_z, string_z>(Z_L("E. Africa Standard Time"),    Z_L("Africa/Nairobi")),
        std::pair<string_z, string_z>(Z_L("E. Australia Standard Time"),    Z_L("Australia/Brisbane")),
        std::pair<string_z, string_z>(Z_L("E. Europe Standard Time"),    Z_L("Asia/Nicosia")),
        std::pair<string_z, string_z>(Z_L("E. South America Standard Time"),    Z_L("America/Sao_Paulo")),
        std::pair<string_z, string_z>(Z_L("Eastern Standard Time"),    Z_L("America/New_York")),
        std::pair<string_z, string_z>(Z_L("Egypt Standard Time"),    Z_L("Africa/Cairo")),
        std::pair<string_z, string_z>(Z_L("Ekaterinburg Standard Time"),    Z_L("Asia/Yekaterinburg")),
        std::pair<string_z, string_z>(Z_L("FLE Standard Time"),    Z_L("Europe/Kiev")),
        std::pair<string_z, string_z>(Z_L("Fiji Standard Time"),    Z_L("Pacific/Fiji")),
        std::pair<string_z, string_z>(Z_L("GMT Standard Time"),    Z_L("Europe/London")),
        std::pair<string_z, string_z>(Z_L("GTB Standard Time"),    Z_L("Europe/Bucharest")),
        std::pair<string_z, string_z>(Z_L("Georgian Standard Time"),    Z_L("Asia/Tbilisi")),
        std::pair<string_z, string_z>(Z_L("Greenland Standard Time"),    Z_L("America/Godthab")),
        std::pair<string_z, string_z>(Z_L("Greenwich Standard Time"),    Z_L("Atlantic/Reykjavik")),
        std::pair<string_z, string_z>(Z_L("Hawaiian Standard Time"),    Z_L("Pacific/Honolulu")),
        std::pair<string_z, string_z>(Z_L("India Standard Time"),    Z_L("Asia/Calcutta")),
        std::pair<string_z, string_z>(Z_L("Iran Standard Time"),    Z_L("Asia/Tehran")),
        std::pair<string_z, string_z>(Z_L("Israel Standard Time"),    Z_L("Asia/Jerusalem")),
        std::pair<string_z, string_z>(Z_L("Jordan Standard Time"),    Z_L("Asia/Amman")),
        std::pair<string_z, string_z>(Z_L("Kaliningrad Standard Time"),    Z_L("Europe/Kaliningrad")),
        std::pair<string_z, string_z>(Z_L("Korea Standard Time"),    Z_L("Asia/Seoul")),
        std::pair<string_z, string_z>(Z_L("Libya Standard Time"),    Z_L("Africa/Tripoli")),
        std::pair<string_z, string_z>(Z_L("Magadan Standard Time"),    Z_L("Asia/Magadan")),
        std::pair<string_z, string_z>(Z_L("Mauritius Standard Time"),    Z_L("Indian/Mauritius")),
        std::pair<string_z, string_z>(Z_L("Middle East Standard Time"),    Z_L("Asia/Beirut")),
        std::pair<string_z, string_z>(Z_L("Montevideo Standard Time"),    Z_L("America/Montevideo")),
        std::pair<string_z, string_z>(Z_L("Morocco Standard Time"),    Z_L("Africa/Casablanca")),
        std::pair<string_z, string_z>(Z_L("Mountain Standard Time"),    Z_L("America/Denver")),
        std::pair<string_z, string_z>(Z_L("Mountain Standard Time (Mexico)"),    Z_L("America/Chihuahua")),
        std::pair<string_z, string_z>(Z_L("Myanmar Standard Time"),    Z_L("Asia/Rangoon")),
        std::pair<string_z, string_z>(Z_L("N. Central Asia Standard Time"),    Z_L("Asia/Novosibirsk")),
        std::pair<string_z, string_z>(Z_L("Namibia Standard Time"),    Z_L("Africa/Windhoek")),
        std::pair<string_z, string_z>(Z_L("Nepal Standard Time"),    Z_L("Asia/Katmandu")),
        std::pair<string_z, string_z>(Z_L("New Zealand Standard Time"),    Z_L("Pacific/Auckland")),
        std::pair<string_z, string_z>(Z_L("Newfoundland Standard Time"),    Z_L("America/St_Johns")),
        std::pair<string_z, string_z>(Z_L("North Asia East Standard Time"),    Z_L("Asia/Irkutsk")),
        std::pair<string_z, string_z>(Z_L("North Asia Standard Time"),    Z_L("Asia/Krasnoyarsk")),
        std::pair<string_z, string_z>(Z_L("Pacific SA Standard Time"),    Z_L("America/Santiago")),
        std::pair<string_z, string_z>(Z_L("Pacific Standard Time"),    Z_L("America/Los_Angeles")),
        std::pair<string_z, string_z>(Z_L("Pacific Standard Time (Mexico)"),    Z_L("America/Santa_Isabel")),
        std::pair<string_z, string_z>(Z_L("Pakistan Standard Time"),    Z_L("Asia/Karachi")),
        std::pair<string_z, string_z>(Z_L("Paraguay Standard Time"),    Z_L("America/Asuncion")),
        std::pair<string_z, string_z>(Z_L("Romance Standard Time"),    Z_L("Europe/Paris")),
        std::pair<string_z, string_z>(Z_L("Russian Standard Time"),    Z_L("Europe/Moscow")),
        std::pair<string_z, string_z>(Z_L("SA Eastern Standard Time"),    Z_L("America/Cayenne")),
        std::pair<string_z, string_z>(Z_L("SA Pacific Standard Time"),    Z_L("America/Bogota")),
        std::pair<string_z, string_z>(Z_L("SA Western Standard Time"),    Z_L("America/La_Paz")),
        std::pair<string_z, string_z>(Z_L("SE Asia Standard Time"),    Z_L("Asia/Bangkok")),
        std::pair<string_z, string_z>(Z_L("Samoa Standard Time"),    Z_L("Pacific/Apia")),
        std::pair<string_z, string_z>(Z_L("Singapore Standard Time"),    Z_L("Asia/Singapore")),
        std::pair<string_z, string_z>(Z_L("South Africa Standard Time"),    Z_L("Africa/Johannesburg")),
        std::pair<string_z, string_z>(Z_L("Sri Lanka Standard Time"),    Z_L("Asia/Colombo")),
        std::pair<string_z, string_z>(Z_L("Syria Standard Time"),    Z_L("Asia/Damascus")),
        std::pair<string_z, string_z>(Z_L("Taipei Standard Time"),    Z_L("Asia/Taipei")),
        std::pair<string_z, string_z>(Z_L("Tasmania Standard Time"),    Z_L("Australia/Hobart")),
        std::pair<string_z, string_z>(Z_L("Tokyo Standard Time"),    Z_L("Asia/Tokyo")),
        std::pair<string_z, string_z>(Z_L("Tonga Standard Time"),    Z_L("Pacific/Tongatapu")),
        std::pair<string_z, string_z>(Z_L("Turkey Standard Time"),    Z_L("Europe/Istanbul")),
        std::pair<string_z, string_z>(Z_L("US Eastern Standard Time"),    Z_L("America/Indianapolis")),
        std::pair<string_z, string_z>(Z_L("US Mountain Standard Time"),    Z_L("America/Phoenix")),
        std::pair<string_z, string_z>(Z_L("UTC"),    Z_L("America/Danmarkshavn")),
        std::pair<string_z, string_z>(Z_L("UTC+12"),    Z_L("Pacific/Tarawa")),
        std::pair<string_z, string_z>(Z_L("UTC-02"),    Z_L("America/Noronha")),
        std::pair<string_z, string_z>(Z_L("UTC-11"),    Z_L("Pacific/Midway")),
        std::pair<string_z, string_z>(Z_L("Ulaanbaatar Standard Time"),    Z_L("Asia/Ulaanbaatar")),
        std::pair<string_z, string_z>(Z_L("Venezuela Standard Time"),    Z_L("America/Caracas")),
        std::pair<string_z, string_z>(Z_L("Vladivostok Standard Time"),    Z_L("Asia/Vladivostok")),
        std::pair<string_z, string_z>(Z_L("W. Australia Standard Time"),    Z_L("Australia/Perth")),
        std::pair<string_z, string_z>(Z_L("W. Central Africa Standard Time"),    Z_L("Africa/Lagos")),
        std::pair<string_z, string_z>(Z_L("W. Europe Standard Time"),    Z_L("Europe/Berlin")),
        std::pair<string_z, string_z>(Z_L("West Asia Standard Time"),    Z_L("Asia/Tashkent")),
        std::pair<string_z, string_z>(Z_L("West Pacific Standard Time"),    Z_L("Pacific/Port_Moresby")),
        std::pair<string_z, string_z>(Z_L("Yakutsk Standard Time"),    Z_L("Asia/Yakutsk")),
        std::pair<string_z, string_z>(Z_L("Kamchatka Standard Time"),    Z_L("Asia/Kamchatka")),
    };

const std::map<string_z, string_z> LocalTimeZone::WINDOWS_TZID_MAPPINGS (
                                        LocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY,
                                        &LocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[0] + sizeof(LocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY) / sizeof(LocalTimeZone::WINDOWS_TZID_MAPPINGS_ARRAY[0])
                                                                         );

#endif


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

LocalTimeZone::LocalTimeZone()
{
    m_pTimeZone = LocalTimeZone::GetCurrentTimeZone();
}

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

#ifdef Z_OS_WINDOWS

const TimeZone* LocalTimeZone::GetCurrentTimeZone()
{
    // Gets the time zone information from Windows
    DYNAMIC_TIME_ZONE_INFORMATION tzInfo;
    GetDynamicTimeZoneInformation(&tzInfo);

    // Converts the time zone key name to a Unicode string
    string_z strWindowsTimeZoneId(tzInfo.TimeZoneKeyName);

    // Gets the equivalent time zone ID in the IANA/Olson database
    string_z strTimeZoneId = LocalTimeZone::GetWindowsEquivalentTimeZoneId(strWindowsTimeZoneId);

    // Gets the time zone instance
    return STimeZoneFactory::GetTimeZoneById(strTimeZoneId);
}

const string_z LocalTimeZone::GetWindowsEquivalentTimeZoneId(const string_z &strTimeZoneKeyName)
{
    std::map<string_z, string_z>::const_iterator itFoundId = LocalTimeZone::WINDOWS_TZID_MAPPINGS.find(strTimeZoneKeyName);

    string_z strEquivalentId;

    if(itFoundId != LocalTimeZone::WINDOWS_TZID_MAPPINGS.end())
    {
        strEquivalentId = itFoundId->second;
    }
    else
    {
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
        // Since exception handling is disabled, the destructor of the iterator is not called when the assertion throws the exception.
        // It seems the STL keeps a reference to it and tries to destroy it when the unit test program ends, causing an unexpected error.
        // Note that this only happens when executing the class' unit tests.
        typedef std::map<string_z, string_z>::const_iterator IteratorType;
        itFoundId.~IteratorType();
#endif
        Z_ASSERT_WARNING(false, "The Windows time zone key has no known equivalence");
        strEquivalentId = string_z::GetEmpty();
    }

    return strEquivalentId;
}

#elif defined(Z_OS_LINUX)

const TimeZone* LocalTimeZone::GetCurrentTimeZone()
{
    static const char* TIME_ZONE_CONFIGURATION_FILE = "/etc/timezone";
    const TimeZone* pTimeZone = null_z;
    
    // [TODO] Thund: Replace with FileStream
    // This file exists on Ubuntu but it is not assured that it exists in other distributions
    std::ifstream file (TIME_ZONE_CONFIGURATION_FILE, std::ios::in|std::ios::binary|std::ios::ate);
    
    if (file.is_open())
    {
        // Loads the entire content of the file into a string
        file.seekg(0, std::ios::end);
        size_t uSize = file.tellg();
        char *szContents = new char[uSize];
        file.seekg(0, std::ios::beg);
        file.read(szContents, uSize);
        file.close();
        
        // The time zone name ends with a carriage return character
        static const string_z CARRIAGE_RETURN = "\n";
        
        string_z strTimeZoneId = szContents;
        int nLastCharPosition = strTimeZoneId.IndexOf(CARRIAGE_RETURN, EComparisonType::E_BinaryCaseSensitive) - 1;
        pTimeZone = STimeZoneFactory::GetTimeZoneById(strTimeZoneId.Substring(0, nLastCharPosition));
        
        delete[] szContents;
    }
    else
    {
        Z_ASSERT_ERROR(false, "The time zone could not be retrieved from the operative system configuration file");
    }
    
	return pTimeZone;
}

#elif defined(Z_OS_MAC)

const TimeZone* LocalTimeZone::GetCurrentTimeZone()
{
    // [TODO] Thund: It is possible that localtime is not a link but a file. If this fails in the future,
    //               add the code to handle that situation (use S_ISLINK, lstat, etc.)
    
    static const unsigned int ENOUGH_LENGTH_FOR_TZ_ID = 256U;
    static const char* TIME_ZONE_CONFIGURATION_FILE = "/etc/localtime";
    static const unsigned int TIME_ZONE_REAL_PATH_LENGTH = 20U;
    
    const TimeZone* pTimeZone = null_z;
    char szFilename[ENOUGH_LENGTH_FOR_TZ_ID];
 
    int nSize = readlink(TIME_ZONE_CONFIGURATION_FILE, szFilename, ENOUGH_LENGTH_FOR_TZ_ID);
    
    if (nSize > 0)
    {
        szFilename[nSize] = '\0';
        pTimeZone = STimeZoneFactory::GetTimeZoneById(szFilename + TIME_ZONE_REAL_PATH_LENGTH);
    }
    
    return pTimeZone;
}

#endif


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

const TimeZone* LocalTimeZone::Get() const
{
    return m_pTimeZone;
}


} // namespace z
