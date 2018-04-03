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

#ifndef __LOCALTIMEZONE__
#define __LOCALTIMEZONE__

#include "ZTiming/TimingModuleDefinitions.h"

#ifdef Z_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif

#include <map>
#include "ZCommon/DataTypes/StringsDefinitions.h"


namespace z
{
    
    // Forward declarations
    // ---------------------
    class TimeZone;


/// <summary>
/// Represents the local time zone, got from the operative system.
/// </summary>
/// <remarks>
/// When it is instanced, it asks the operative system for the configuration about the time zone and stores an equivalent TimeZone instance.
/// From that moment, it acts just as an envelope of that instance.
/// </remarks>
class Z_LAYER_TIMING_SYMBOLS LocalTimeZone
{

	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor. The current time zone is obtained from the operative system and stored.
	/// </summary>
    /// <remarks>
	/// If there is any problem when finding out the time zone, a null pointer will be stored.
	/// </remarks>
	LocalTimeZone();


    // METHODS
	// ---------------
protected:
    
    /// <summary>
    /// The current time zone is obtained from the operative system.
    /// </summary>
    /// <returns>
	/// The equivalent TimeZone instance. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    static const TimeZone* GetCurrentTimeZone();

#ifdef Z_OS_WINDOWS

    /// <summary>
    /// Gets the time zone Id of the IANA/Olson database from a Windows time zone key name.
    /// </summary>
    /// <remarks>
	/// All the equivalences have been obtained from the Unicode Common Locale Data Repository http://www.unicode.org/cldr/charts/24/supplemental/zone_tzid.html.
	/// </remarks>
    /// <param name="strTimeZoneKeyName">A Windows time zone key name.</param>
    /// <returns>
	/// The equivalent time zone ID. If there is no equivalence, it returns an empty string.
	/// </returns>
    static const string_z GetWindowsEquivalentTimeZoneId(const string_z &strTimeZoneKeyName);
	
#endif


	// PROPERTIES
	// ---------------
public:

    /// <summary>
    /// Gets the stored time zone.
    /// </summary>
    /// <returns>
	/// The time zone. If there was any problem when finding out the time zone, a null pointer will be returned.
	/// </returns>
    const TimeZone* Get() const;


	// ATTRIBUTES
	// ---------------
private:

    /// <summary>
    /// The local time zone.
    /// </summary>
    const TimeZone* m_pTimeZone;
    
#ifdef Z_OS_WINDOWS

    /// <summary>
    /// A dictionary with the equivalences between IANA/Olson time zone IDs and Windows time zone keys. 
    /// </summary>
    static const std::map<string_z, string_z> WINDOWS_TZID_MAPPINGS; // [TODO] Thund: Replace with Dictionary, when it exists

    /// <summary>
    /// An array with all the pairs used in the time zone IDs dictionary.
    /// </summary>
    static const std::pair<string_z, string_z> WINDOWS_TZID_MAPPINGS_ARRAY[];

#endif

};

} // namespace z


#ifdef Z_COMPILER_MSVC
    #pragma warning( pop )
#endif

#endif // __LOCALTIMEZONE__
