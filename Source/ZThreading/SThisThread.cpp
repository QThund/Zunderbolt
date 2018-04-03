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

#include "ZThreading/SThisThread.h"

#include "ZCommon/Assertions.h"
#include <sstream>

#if defined(Z_OS_WINDOWS)
    #include <Windows.h>
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    #include <pthread.h>
#endif



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

void SThisThread::Yield()
{
    boost::this_thread::yield();
}

void SThisThread::Sleep(const TimeSpan &duration)
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(duration.GetMilliseconds()));
}
    
string_z SThisThread::ToString()
{
#if defined(Z_OS_WINDOWS)
    typedef DWORD IdInteger;
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)
    typedef pid_t IdInteger;
#endif

    static const string_z STRING_PART1 = "Thread(";
    static const string_z STRING_PART3 = ")";
    string_z strResult = STRING_PART1;
    std::string strOutput;
    std::stringstream os(strOutput);
    os << SThisThread::GetId();
    string_z strId(os.str().c_str());
    strResult.Append(string_z::FromInteger(strId.ToIntegerFromHexadecimal<IdInteger>()));
    strResult.Append(STRING_PART3);
    return strResult;
}

#if defined(Z_OS_WINDOWS)

EThreadPriority SThisThread::_ConvertFromNativePriority(const int nNativePriority)
{
    EThreadPriority ePriority = EThreadPriority::E_Normal;

    switch(nNativePriority)
    {
    case THREAD_PRIORITY_HIGHEST:
        ePriority = EThreadPriority::E_Highest;
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        ePriority = EThreadPriority::E_High;
        break;
    case THREAD_PRIORITY_NORMAL:
        ePriority = EThreadPriority::E_Normal;
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        ePriority = EThreadPriority::E_Low;
        break;
    case THREAD_PRIORITY_LOWEST:
        ePriority = EThreadPriority::E_Lowest;
        break;
    }

    return ePriority;
}

int SThisThread::_ConvertToNativePriority(const EThreadPriority &ePriority)
{
    int nNativePriority = 0;

    switch(ePriority)
    {
    case EThreadPriority::E_Highest:
        nNativePriority = THREAD_PRIORITY_HIGHEST;
        break;
    case EThreadPriority::E_High:
        nNativePriority = THREAD_PRIORITY_ABOVE_NORMAL;
        break;
    case EThreadPriority::E_Normal:
        nNativePriority = THREAD_PRIORITY_NORMAL;
        break;
    case EThreadPriority::E_Low:
        nNativePriority = THREAD_PRIORITY_BELOW_NORMAL;
        break;
    case EThreadPriority::E_Lowest:
        nNativePriority = THREAD_PRIORITY_LOWEST;
        break;
    default:
        break;
    }

    return nNativePriority;
}

#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)

EThreadPriority SThisThread::_ConvertFromNativePriority(const int nNativePriority, const int nPolicy)
{
    // On Linux, there are different thread scheduling policies which have different priority ranges. In order to provide a concrete and unified set of priorities,
    // we sacrified configuration flexibility (only SCHED_OTHER is used) and "accuracy", so different priorities for different policies may be the same when seen from
    // the user interface point of view. Priority ranges are obtained from the OS and then divided in 3 parts: High, Normal and Low, with two ends: Highest and Lowest
    // for either the maximum and the minimum priority, respectively.

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(nPolicy);
    static const int MAX_PRIORITY = sched_get_priority_max(nPolicy);

    EThreadPriority ePriority = EThreadPriority::E_Normal;

    // Maximum is not assured to be higher than minimum, and they may be negative or positive
    if(MAX_PRIORITY > MIN_PRIORITY)
    {
        const int RANGE_PART = (MAX_PRIORITY - MIN_PRIORITY) / 3;
        const int LOW_PRIORITY_LIMIT = MIN_PRIORITY + RANGE_PART;
        const int HIGH_PRIORITY_LIMIT = MAX_PRIORITY - RANGE_PART;
        
        if(nNativePriority > LOW_PRIORITY_LIMIT && nNativePriority < HIGH_PRIORITY_LIMIT)
        {
            ePriority = EThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EThreadPriority::E_Highest;
        }
        else if(nNativePriority >= HIGH_PRIORITY_LIMIT && nNativePriority < MAX_PRIORITY)
        {
            ePriority = EThreadPriority::E_High;
        }
        else if(nNativePriority > MIN_PRIORITY && nNativePriority <= LOW_PRIORITY_LIMIT)
        {
            ePriority = EThreadPriority::E_Low;
        }
        else if(nNativePriority == MIN_PRIORITY)
        {
            ePriority = EThreadPriority::E_Lowest;
        }
    }
    else if(MAX_PRIORITY < MIN_PRIORITY)
    {
        const int RANGE_PART = (MIN_PRIORITY - MAX_PRIORITY) / 3;
        const int LOW_PRIORITY_LIMIT = MIN_PRIORITY - RANGE_PART;
        const int HIGH_PRIORITY_LIMIT = MAX_PRIORITY + RANGE_PART;
        
        if(nNativePriority > HIGH_PRIORITY_LIMIT && nNativePriority < LOW_PRIORITY_LIMIT / 2)
        {
            ePriority = EThreadPriority::E_Normal;
        }
        else if(nNativePriority == MAX_PRIORITY)
        {
            ePriority = EThreadPriority::E_Highest;
        }
        else if(nNativePriority <= HIGH_PRIORITY_LIMIT && nNativePriority > MAX_PRIORITY)
        {
            ePriority = EThreadPriority::E_High;
        }
        else if(nNativePriority < MIN_PRIORITY && nNativePriority >= LOW_PRIORITY_LIMIT)
        {
            ePriority = EThreadPriority::E_Low;
        }
        else if(nNativePriority == MIN_PRIORITY)
        {
            ePriority = EThreadPriority::E_Lowest;
        }
    }

    return ePriority;
}

int SThisThread::_ConvertToNativePriority(const EThreadPriority &ePriority)
{
    int nNativePriority = 0;

    // The priority range available depends on the Linux distribution
    static const int MIN_PRIORITY = sched_get_priority_min(SCHED_OTHER);
    static const int MAX_PRIORITY = sched_get_priority_max(SCHED_OTHER);
    
    int nRangePart = 0;
    int nLowPriorityLimit = 0;
    int nHighPriorityLimit = 0;
    
    if(MAX_PRIORITY >= MIN_PRIORITY)
    {
        nRangePart = (MAX_PRIORITY - MIN_PRIORITY) / 3;
        nLowPriorityLimit = MIN_PRIORITY + nRangePart;
        nHighPriorityLimit = MAX_PRIORITY - nRangePart;
    }
    else
    {
        nRangePart = (MIN_PRIORITY - MAX_PRIORITY) / 3;
        nLowPriorityLimit = MIN_PRIORITY - nRangePart;
        nHighPriorityLimit = MAX_PRIORITY + nRangePart;
    }
    
    switch(ePriority)
    {
    case EThreadPriority::E_Highest:
        nNativePriority = MAX_PRIORITY;
        break;
    case EThreadPriority::E_High:
        nNativePriority = nHighPriorityLimit;
        break;
    case EThreadPriority::E_Normal:
        nNativePriority = 0;
        break;
    case EThreadPriority::E_Low:
        nNativePriority = nLowPriorityLimit;
        break;
    case EThreadPriority::E_Lowest:
        nNativePriority = MIN_PRIORITY;
        break;
    default:
        break;
    }

    return nNativePriority;
}

#endif

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool SThisThread::IsInterrupted()
{
    return boost::this_thread::interruption_requested();
}

Thread::Id SThisThread::GetId()
{
    return boost::this_thread::get_id();
}

#if defined(Z_OS_WINDOWS)

Thread::NativeThreadHandle SThisThread::GetNativeHandle()
{
    return ::GetCurrentThread();
}

#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)

Thread::NativeThreadHandle SThisThread::GetNativeHandle()
{
    return pthread_self();
}

#endif

void SThisThread::SetExitFunction(const Delegate<void()> function)
{
    boost::this_thread::at_thread_exit(function);
}

#if defined(Z_OS_WINDOWS)

EThreadPriority SThisThread::GetPriority()
{
    int nNativePriority = ::GetThreadPriority(SThisThread::GetNativeHandle());
    return SThisThread::_ConvertFromNativePriority(nNativePriority);
}

void SThisThread::SetPriority(const EThreadPriority &ePriority)
{
    int nNativePriority = SThisThread::_ConvertToNativePriority(ePriority);
    BOOL uResult = ::SetThreadPriority(SThisThread::GetNativeHandle(), nNativePriority);
    
    Z_ASSERT_WARNING(uResult != 0, string_z("An unexpected error ocurred when attempting to set the priority of the ") + SThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_z::FromInteger(::GetLastError()) + ".");
}

#elif defined(Z_OS_LINUX)

EThreadPriority SThisThread::GetPriority()
{
    sched_param schedulingPolicy;
    int nPolicy;
    
    int nResult = pthread_getschedparam(SThisThread::GetNativeHandle(), &nPolicy, &schedulingPolicy);
    int nNativePriority = schedulingPolicy.__sched_priority;
    
    Z_ASSERT_WARNING(nResult == 0, string_z("An unexpected error ocurred when attempting to get the priority of the ") + SThisThread::ToString() + ". The error code is:" + string_z::FromInteger(errno) + ".");
    
    return SThisThread::_ConvertFromNativePriority(nNativePriority, nPolicy);
}

void SThisThread::SetPriority(const EThreadPriority &ePriority)
{
    int nNativePriority = SThisThread::_ConvertToNativePriority(ePriority);
    
    sched_param schedulingPolicy;
    schedulingPolicy.__sched_priority = nNativePriority;
    
    int nResult = pthread_setschedparam(SThisThread::GetNativeHandle(), SCHED_OTHER, &schedulingPolicy);
    
    Z_ASSERT_WARNING(nResult == 0, string_z("An unexpected error ocurred when attempting to set the priority of the ") + SThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_z::FromInteger(errno) + ".");
}

#elif defined(Z_OS_MAC)

EThreadPriority SThisThread::GetPriority()
{
    sched_param schedulingPolicy;
    int nPolicy;
    
    int nResult = pthread_getschedparam(SThisThread::GetNativeHandle(), &nPolicy, &schedulingPolicy);
    int nNativePriority = schedulingPolicy.sched_priority;
    
    Z_ASSERT_WARNING(nResult == 0, string_z("An unexpected error ocurred when attempting to get the priority of the ") + SThisThread::ToString() + ". The error code is:" + string_z::FromInteger(errno) + ".");
    
    return SThisThread::_ConvertFromNativePriority(nNativePriority, nPolicy);
}

void SThisThread::SetPriority(const EThreadPriority &ePriority)
{
    int nNativePriority = SThisThread::_ConvertToNativePriority(ePriority);
    
    sched_param schedulingPolicy;
    schedulingPolicy.sched_priority = nNativePriority;
    
    int nResult = pthread_setschedparam(SThisThread::GetNativeHandle(), SCHED_OTHER, &schedulingPolicy);
    
    Z_ASSERT_WARNING(nResult == 0, string_z("An unexpected error ocurred when attempting to set the priority of the ") + SThisThread::ToString() + " to " + ePriority.ToString() + ". The error code is:" + string_z::FromInteger(errno) + ".");
}

#endif

} // namespace z
