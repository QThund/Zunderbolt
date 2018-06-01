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

#ifndef __CALLSTACKTRACER__
#define __CALLSTACKTRACER__

#include <boost/shared_ptr.hpp>

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"
#include "ZDiagnosis/CallTrace.h"
#include "ZDiagnosis/AbstractCallStackTracePrinter.h"
#include "ZDiagnosis/CallStackTrace.h"
#include "ZThreading/Thread.h"
#include "ZThreading/SharedMutex.h"
#include "ZContainers/Dictionary.h"


namespace z
{

/// <summary>
/// Builds and stores the function call stack traces of every thread in a single process. It can also print the call stack trace of a thread, using a custom printer.
/// </summary>
/// <remarks>
/// It is a singleton.<br/>
/// It is thread-safe.
/// </remarks>
class Z_DIAGNOSIS_MODULE_SYMBOLS CallStackTracer
{
    // CONSTRUCTORS
    // ---------------
protected:

    typedef Dictionary<Thread::Id, CallStackTrace*> CallStackTraceContainer;


    // CONSTRUCTORS
    // ---------------
private:

    /// <summary>
    /// Default constructor.
    /// </summary>
    CallStackTracer();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Gets the instance of the call stack tracer.
    /// </summary>
    /// <returns>
    /// A unique instance of the call stack tracer.
    /// </returns>
    static CallStackTracer* Get();
    
    /// <summary>
    /// Adds a function call trace to the top of the call stack for the current thread.
    /// </summary>
    /// <param name="trace">[IN] A function call trace.</param>
    void AddTrace(const CallTrace &trace);

    /// <summary>
    /// Removes a function call trace from the top of the call stack for the current thread. If there are no traces for the current thread, it will fail.
    /// </summary>
    void RemoveLastTrace();

    /// <summary>
    /// Uses a custom printer to send the information of the call stack trace of the current thread to an output channel with a concrete format.
    /// </summary>
    /// <remarks>
    /// If there is not printer assigned, it does nothing.<br/>
    /// If there are no traces for the current thread, it prints a message warning about that.
    /// </remarks>
    virtual void Dump();


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <returns>
    /// The custom printer used by the call stack tracer.
    /// </returns>
    boost::shared_ptr<AbstractCallStackTracePrinter> GetPrinter() const;
    
    /// <summary>
    /// Sets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <param name="pPrinter">[IN] The custom printer to be used by the tracer. It can be null. It will be stored in a shared smart pointer.</param>
    void SetPrinter(const boost::shared_ptr<AbstractCallStackTracePrinter> &pPrinter);
    
    /// <summary>
    /// Sets the custom call stack trace printer used for dumping the call stack trace information.
    /// </summary>
    /// <param name="pPrinter">[IN] The custom printer to be used by the tracer. It can be null. It will be stored in a shared smart pointer.</param>
    void SetPrinter(AbstractCallStackTracePrinter* pPrinter);


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// A dictionary which contains every call stack trace associated to its thread Id.
    /// </summary>
    CallStackTraceContainer m_callStackTraces;
    
    /// <summary>
    /// The custom printer to be used by the tracer.
    /// </summary>
    boost::shared_ptr<AbstractCallStackTracePrinter> m_pPrinter;

    // Synchronization
    
    /// <summary>
    /// Mutex to synchronize the access to the call stack trace dictionary.
    /// </summary>
    mutable SharedMutex m_callStackTracesMutex;
    
    /// <summary>
    /// Mutex to synchronize the access to the printer.
    /// </summary>
    mutable SharedMutex m_printerMutex;
};

} // namespace z


#endif // __CALLSTACKTRACER__
