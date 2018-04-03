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

#ifndef __STOPWATCH__
#define __STOPWATCH__

#include "ZTiming/TimingModuleDefinitions.h"
#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZTime/TimeSpan.h"

#if defined(Z_OS_WINDOWS)

    #include <Windows.h>

#elif defined(Z_OS_LINUX)

    #include <time.h>

#elif defined(Z_OS_MAC)

    #include <mach/mach.h>
    #include <mach/mach_time.h>

#endif


namespace z
{

/// <summary>
/// A stopwatch that calculates the time passed since the last time it was set.
/// </summary>
/// <remarks>
/// Depending on the operating system, the resolution of the time counter may vary (from 100ns to 1ns).<br/>
/// Internal time counter is not affected by thread interruptions nor by system adjustments.
/// </remarks>
class Z_LAYER_TIMING_SYMBOLS Stopwatch
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It only gets some data from the system. Call the Set method to start measuring the time.
    /// </summary>
    Stopwatch();
    

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Gets the current instant from the operating system high resolution time counter.
    /// </summary>
    /// <returns>
    /// The current instant with respect to an arbitrary base time. On Windows, it is expressed in hundreds of nanoseconds. On Linux and Mac it is expressed in nanoseconds.
    /// </returns>
    static u64_z _GetCurrentInstant();


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the elapsed time since the last time the stopwatch was set.
    /// </summary>
    /// <returns>
    /// The elapsed time, in milliseconds, as a floating point number. Note that the fractional part will be zero when compiling using single precision.
    /// </returns>
    float_z GetElapsedTimeAsFloat() const;
    
    /// <summary>
    /// Gets the elapsed time since the last time the stopwatch was set.
    /// </summary>
    /// <returns>
    /// The elapsed time, in nanoseconds, as an unsigned integer number.
    /// </returns>
    u64_z GetElapsedTimeAsInteger() const;
    
    /// <summary>
    /// Gets the elapsed time since the last time the stopwatch was set.
    /// </summary>
    /// <returns>
    /// The elapsed time, in hundreds of nanosecond, as a time span.
    /// </returns>
    TimeSpan GetElapsedTimeAsTimeSpan() const;
    
    /// <summary>
    /// Sets the instant that serves as reference to calculate the elapsed time.
    /// </summary>
    /// <remarks>
    /// It can be set as many times as necessary.
    /// </remarks>
    void Set();


    // ATTRIBUTES
    // ---------------
private:

#if defined(Z_OS_WINDOWS)

    /// <summary>
    /// The frequency of the high performance timer on Windows.
    /// </summary>
    static LARGE_INTEGER sm_frequency;

#elif defined(Z_OS_MAC)

    /// <summary>
    /// The number of ticks per second of the absolute timer on Mac OS.
    /// </summary>
    static mach_timebase_info_data_t sm_timebaseInfo;

#endif

protected:

    /// <summary>
    /// The instant that serves as reference to calculate the elapsed time.
    /// </summary>
    u64_z m_uReferenceTime;
};

} // namespace z


#endif // __STOPWATCH__
