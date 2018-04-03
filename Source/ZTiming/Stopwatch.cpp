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

#include "ZTiming/Stopwatch.h"

#include "ZTiming/TimingModuleDefinitions.h"


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

#if defined(Z_OS_WINDOWS)

    LARGE_INTEGER Stopwatch::sm_frequency;

#elif defined(Z_OS_MAC)

    mach_timebase_info_data_t Stopwatch::sm_timebaseInfo;

#endif
    

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Stopwatch::Stopwatch() : m_uReferenceTime(0)
{
    static bool bInitialized = false;

    // Initializes auxiliar data
    if(!bInitialized)
    {
#if defined(Z_OS_WINDOWS)

        ::QueryPerformanceFrequency(&sm_frequency);

#elif defined(Z_OS_LINUX)

#elif defined(Z_OS_MAC)

        if(sm_timebaseInfo.denom == 0)
            ::mach_timebase_info(&sm_timebaseInfo);
#endif
        bInitialized = true;
    }
}
    
    
//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

u64_z Stopwatch::_GetCurrentInstant()
{

#ifdef Z_OS_WINDOWS

    static const u64_z NANOSECONDS_IN_SECOND = 1000000000ULL;

    LARGE_INTEGER ticks;
    ::QueryPerformanceCounter(&ticks);

    return ticks.QuadPart * NANOSECONDS_IN_SECOND / sm_frequency.QuadPart;

#elif defined(Z_OS_LINUX)

    static const u64_z NANOSECONDS_IN_SECOND = 1000000000ULL;
    
    timespec timeSpecData;
    ::clock_gettime(CLOCK_MONOTONIC_RAW, &timeSpecData);

    return timeSpecData.tv_sec * NANOSECONDS_IN_SECOND + timeSpecData.tv_nsec;

#elif defined (Z_OS_MAC)

    u64_z uRawTime = ::mach_absolute_time();

    return uRawTime * sm_timebaseInfo.numer / sm_timebaseInfo.denom ;

#endif

}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_z Stopwatch::GetElapsedTimeAsFloat() const
{
    Z_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    static const u64_z NANOSECONDS_IN_MILLISECOND = 1000000ULL;
    return scast_z((Stopwatch::_GetCurrentInstant() - m_uReferenceTime) / NANOSECONDS_IN_MILLISECOND, float_z);
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    static const float_z NANOSECONDS_IN_MILLISECOND = 1000000.0;
    return scast_z(Stopwatch::_GetCurrentInstant() - m_uReferenceTime, float_z) / NANOSECONDS_IN_MILLISECOND;
#endif
}

u64_z Stopwatch::GetElapsedTimeAsInteger() const
{
    Z_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

    return Stopwatch::_GetCurrentInstant() - m_uReferenceTime;
}

TimeSpan Stopwatch::GetElapsedTimeAsTimeSpan() const
{
    Z_ASSERT_WARNING(m_uReferenceTime > 0, "The stopwatch has not been set.");

    static const u64_z HUNDRED_OF_NANOSECONDS = 100ULL;
    return TimeSpan((Stopwatch::_GetCurrentInstant() - m_uReferenceTime) / HUNDRED_OF_NANOSECONDS);
}

void Stopwatch::Set()
{
    m_uReferenceTime = Stopwatch::_GetCurrentInstant();
}

} // namespace z
