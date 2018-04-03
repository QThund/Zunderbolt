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

#ifndef __SHAREDMUTEX__
#define __SHAREDMUTEX__

#include "ZThreading/ThreadingModuleDefinitions.h"
#include <boost/thread/shared_mutex.hpp>

#ifdef Z_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif


namespace z
{

/// <summary>
/// Represents a mechanism to synchronize the access from different threads to a shared resource. Threads can either own the resource preventing others from owning it at the same time or share
/// it with other threads. Shared mutexes can be used to implement a model in which a resource can be read by many but modified by only one at a time.
/// </summary>
/// <remarks>
/// This class is thread-safe.<br/>
/// It is a wrapper for the shared_mutex class, from Boost libraries.
/// </remarks>
class Z_LAYER_THREADING_SYMBOLS SharedMutex
{
    // TYPEDEFS
    // ---------------
public:

    typedef boost::shared_mutex WrappedType;


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. The mutex must be unlocked before it is destroyed.
    /// </summary>
    ~SharedMutex();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Blocks the calling thread if another thread already locked the shared mutex, no matter whether it was exclusive or shared locking. When the other thread unlocks the shared mutex, the 
    /// calling thread may or may not resume immediately; the order of execution of several waiting threads is not deterministic. When it is calling thread's turn, it locks the mutex so no other thread 
    /// can execute the same code until Unlock is called.
    /// </summary>
    /// <remarks>
    /// If the mutex is locked by a thread which is killed before calling Unlock, its state depends on the operating system. On Windows, it will stay in an special state until it is locked and unlocked again;
    /// on Unix-based systems (using POSIX threads), the mutex ends up with an undefined state and it is not safe to try to lock it again. Either way, take into account that the resource protected by the mutex may 
    /// be in an inconsistent state when this happen.
    /// </remarks>
    void Lock();

    /// <summary>
    /// Blocks the calling thread if another thread already performed an exclusive lock on the shared mutex. When another thread performs an exclusive unlock on the shared mutex, the 
    /// calling thread may or may not resume immediately; the order of execution of several waiting threads is not deterministic. If other threads performed a shared lock, the calling thread will also lock 
    /// the shared mutex and continue.
    /// </summary>
    void LockShared();
    
    /// <summary>
    /// Releases the shared mutex so it can be owned by another thread.
    /// </summary>
    void Unlock();
    
    /// <summary>
    /// Releases the shared mutex so another thread can perform an exclusive lock.
    /// </summary>
    void UnlockShared();
    
    /// <summary>
    /// Locks the shared mutex in the exclusive way. If the mutex is already locked by another thread, either in an exclusive or shared manner, it returns immediately.
    /// </summary>
    /// <returns>
    /// True if the shared mutex has been locked by the calling thread; False otherwise.
    /// </returns>
    bool TryLock();
    
    /// <summary>
    /// Locks the shared mutex in the shared way. If the mutex is already locked by another thread in an exclusive manner, it returns immediately.
    /// </summary>
    /// <returns>
    /// True if the shared mutex has been locked by the calling thread; False otherwise.
    /// </returns>
    bool TryLockShared();


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the wrapped shared mutex instance.
    /// </summary>
    /// <remarks>
    /// The usage of this method is discouraged unless it is absolutely necessary. It may not be available in future versions.
    /// </remarks>
    /// <returns>
    /// The wrapped instance.
    /// </returns>
    WrappedType& GetWrappedObject();
    
    /// <summary>
    /// Gets the wrapped shared mutex instance.
    /// </summary>
    /// <remarks>
    /// The usage of this method is discouraged unless it is absolutely necessary. It may not be available in future versions.
    /// </remarks>
    /// <returns>
    /// The wrapped instance.
    /// </returns>
    const WrappedType& GetWrappedObject() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The wrapped shared mutex instance.
    /// </summary>
    WrappedType m_sharedMutex;

};

} // namespace z


#endif // __SHAREDMUTEX__
