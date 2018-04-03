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

#ifndef __DATETIMENOW__
#define __DATETIMENOW__

#include "ZTiming/TimingModuleDefinitions.h"

#include "ZTime/DateTime.h"


namespace z
{

    // Forward declarations
    // ---------------------       
    class TimeZone;

/// <summary>
/// Represents the system date and time (including time zone and DST) at the moment it is instanced.
/// </summary>
/// <remarks>
/// It is immutable, an instance cannot be modified.<br/>
/// It is wall-clock time, not monotonic, so it is affected by time zone and DST delays besides operating system settings.<br/>
/// The resolution of the clock depends on the operating system, being it between several microseconds and 100 nanoseconds.
/// </remarks>
class Z_LAYER_TIMING_SYMBOLS DateTimeNow : public DateTime
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor that gets the system date and time along with the system time zone.
    /// </summary>
    DateTimeNow();

    /// <summary>
    /// Constructor that gets the system date and time and receives the time zone to be applied.
    /// </summary>
    /// <param name="pTimeZone">The time zone to apply to the system time. If it is null, the time will be UTC.</param>
    DateTimeNow(const TimeZone* pTimeZone);

private:

    // Hidden, not allowed
    DateTimeNow(const DateTimeNow &);


    // METHODS
    // ---------------
private:

    // Hidden, not allowed
    DateTimeNow operator=(const DateTimeNow &);

protected:

    /// <summary>
    /// Gets the system date and time as UTC from the current operating system.
    /// </summary>
    /// <returns>
    /// The system date and time.
    /// </returns>
    static DateTime GetSystemUtcDateTime();

};

} // namespace z


#endif // __DATETIMENOW__
