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

#ifndef __CONDITIONVARIABLE__
#define __CONDITIONVARIABLE__

#include "ZThreading/ThreadingModuleDefinitions.h"
#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include <boost/thread/condition_variable.hpp>

#ifdef Z_COMPILER_MSVC
    #pragma warning( push )
    #pragma warning( disable: 4251 ) // This warning occurs when using a template specialization as attribute
#endif


namespace z
{

/// <summary>
/// Represents a mechanism with which threads can wait for a condition to be fulfilled until
/// another thread sends a notification to either one or all the threads waiting for the same condition. When a thread gets notified, it continues its execution
/// and can check if the condition is met; if it does not, it should wait again for a new notification.
/// </summary>
/// <remarks>
/// This class is thread-safe.<br/>
/// It is a wrapper for the condition_variable_any class, from Boost libraries.
/// </remarks>
class Z_LAYER_THREADING_SYMBOLS ConditionVariable
{
    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Blocks the thread until it gets notified from another thread.
    /// </summary>
    /// <remarks>
    /// When the thread blocks, the input lock unlocks its associated mutex. When the thread is notified, the mutex will be locked again.<br/>
    /// According to that just stated, it is recommended to call this method as the first statement of a critical section; otherwise, another thread could modify the
    /// shared resource while the waiting thread is blocked.
    /// </remarks>
    /// <typeparam name="ScopedLockT">The type of scoped lock, like ScopedExclusiveLock or ScopedSharedLock, used by waiting threads.</typeparam>
    /// <param name="lock">[IN] A lock that owns its associated mutex.</param>
    template<class ScopedLockT>
    void Wait(ScopedLockT &lock)
    {
        Z_ASSERT_ERROR(lock.IsOwner(), "The lock does not own the mutex. Locks can only unlock mutexes they already own.");

        m_conditionVariable.wait(lock.GetWrappedObject());
    }
    
    /// <summary>
    /// Sends a notification to only one of the threads that wait for the condition, if any.
    /// </summary>
    /// <remarks>
    /// The order in which waiting threads are notified is undefined.<br/>
    /// When a thread is notified, the lock passed as parameter to Wait is locked again before it continues.
    /// </remarks>
    void NotifyOne();

    /// <summary>
    /// Sends a notification to all the threads that wait for the condition, if any.
    /// </summary>
    /// <remarks>
    /// The order in which waiting threads are notified is undefined.<br/>
    /// When a thread is notified, the lock passed as parameter to Wait is locked again before it continues.
    /// </remarks>
    void NotifyAll();


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the wrapped condition variable instance.
    /// </summary>
    /// <remarks>
    /// The usage of this method is discouraged unless it is absolutely necessary. It may not be available in future versions.
    /// </remarks>
    /// <returns>
    /// The wrapped instance.
    /// </returns>
    boost::condition_variable_any& GetWrappedObject();
    
    /// <summary>
    /// Gets the wrapped condition variable instance.
    /// </summary>
    /// <remarks>
    /// The usage of this method is discouraged unless it is absolutely necessary. It may not be available in future versions.
    /// </remarks>
    /// <returns>
    /// The wrapped instance.
    /// </returns>
    const boost::condition_variable_any& GetWrappedObject() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The wrapped instance.
    /// </summary>
    boost::condition_variable_any m_conditionVariable;
};

} // namespace z


#endif // __CONDITIONVARIABLE__
