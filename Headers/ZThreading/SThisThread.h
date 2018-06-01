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

#ifndef __STHISTHREAD__
#define __STHISTHREAD__

#include "ZThreading/ThreadingModuleDefinitions.h"

#include "ZThreading/Thread.h"
#include "ZTime/TimeSpan.h"
#include "ZCommon/Delegate.h"
#include "ZThreading/EThreadPriority.h"

#if defined(Z_OS_WINDOWS)
    #include <Windows.h>
    #undef Yield // This definition appears in Windows headers which prevents us to use the name "Yield" as the name of a method
#endif



namespace z
{
    
/// <summary>
/// Represents the current thread in the operating system.
/// </summary>
/// <remarks>
/// This class acts as an extended wrapper of the Boost's this_thread namespace.
/// </remarks>
class Z_THREADING_MODULE_SYMBOLS SThisThread
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SThisThread();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Makes the calling thread yield execution to any other waiting thread (the operating system decides which one).
    /// </summary>
    static void Yield();
    
    /// <summary>
    /// Suspends the calling thread for a given amount of time.
    /// </summary>
    /// <param name="duration">[IN] The amount of time the thread will be suspended, with millisecond precision.</param>
    static void Sleep(const TimeSpan &duration);
    
    /// <summary>
    /// Generates a string representation of the calling thread.
    /// </summary>
    /// <returns>
    /// A string that contains the representation of the thread with the format: "Thread(#)", where # means the thread's id.
    /// </returns>
    static string_z ToString();

private:

#if defined(Z_OS_WINDOWS)

    /// <summary>
    /// Converts a priority value coming from the operating system API to EThreadPriority equivalent.
    /// </summary>
    /// <param name="nNativePriority">[IN] A native priority value.</param>
    /// <returns>
    /// The corresponding thread priority value.
    /// </returns>
    static EThreadPriority _ConvertFromNativePriority(const int nNativePriority);
    
    /// <summary>
    /// Converts a priority value coming from the engine to the operating system API's equivalent.
    /// </summary>
    /// <param name="ePriority">[IN] A thread priority.</param>
    /// <returns>
    /// The corresponding native priority value.
    /// </returns>
    static int _ConvertToNativePriority(const EThreadPriority &ePriority);
    
#elif defined(Z_OS_LINUX) || defined(Z_OS_MAC)

    /// <summary>
    /// Converts a priority value coming from the operating system API to EThreadPriority equivalent.
    /// </summary>
    /// <param name="nNativePriority">[IN] A native priority value.</param>
    /// <param name="nPolicy">[IN] The scheduling policy. Depending on whether it is FIFO, RoundRobin, OTHER or NORMAL, the range of priority values change.</param>
    /// <returns>
    /// The corresponding thread priority value.
    /// </returns>
    static EThreadPriority _ConvertFromNativePriority(const int nNativePriority, const int nPolicy);
    
    /// <summary>
    /// Converts a priority value coming from the engine to the operating system API's equivalent.
    /// </summary>
    /// <param name="ePriority">[IN] A thread priority.</param>
    /// <returns>
    /// The corresponding native priority value for a NORMAL or OTHER policy.
    /// </returns>
    static int _ConvertToNativePriority(const EThreadPriority &ePriority);

#endif

    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Indicates whether the thread was interrupted or not.
    /// </summary>
    /// <remarks>
    /// Thread interruption is supported only when compiling as a static library, for now.
    /// </remarks>
    /// <returns>
    /// True if the thread was interrupted; False otherwise.
    /// </returns>
    static bool IsInterrupted();
    
    /// <summary>
    /// Gets the ID of the thread using a platform abstraction structure.
    /// </summary>
    /// <returns>
    /// A platform abstraction structure that contains the thread's ID.
    /// </returns>
    static Thread::Id GetId();
    
    /// <summary>
    /// Gets a native handle of the thread using platform specific type.
    /// </summary>
    /// <remarks>
    /// Examples of handle types: HANDLE on Windows, pthread_t on Unix-based systems like Linux or Mac.
    /// </remarks>
    /// <returns>
    /// The thread's handle.
    /// </returns>
    static Thread::NativeThreadHandle GetNativeHandle();
    
    /// <summary>
    /// Stores a function to be called when the thread finishes.
    /// </summary>
    /// <param name="function">[IN] The function to be executed, with neither parameters nor return value.</param>
    static void SetExitFunction(const Delegate<void()> function);
    
    /// <summary>
    /// Gets the priority the operating system gives to the calling thread.
    /// </summary>
    /// <returns>
    /// The priority of the thread.
    /// </returns>
    static EThreadPriority GetPriority();
    
    /// <summary>
    /// Sets the priority the operating system must give to the calling thread.
    /// </summary>
    /// <remarks>
    /// The current user must have permissions to adjust thread priorities.
    /// </remarks>
    /// <param name="ePriority">[IN] The new priority of the thread.</param>
    static void SetPriority(const EThreadPriority &ePriority);
};

} // namespace z


#endif // __STHISTHREAD__
