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

#ifndef __SCOPEDCALLTRACENOTIFIER__
#define __SCOPEDCALLTRACENOTIFIER__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "CallTrace.h"


namespace z
{

/// <summary>
/// Adds or removes call traces from the calling thread's call stack trace. It is intended to be instanced at the very beginning of a function body so it adds
/// a trace through the call stack tracer; when the control flow leaves the function and the instance is destroyed, the last registered trace is removed.
/// </summary>
class Z_DIAGNOSIS_MODULE_SYMBOLS ScopedCallTraceNotifier
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a trace to be registed by the call stack tracer.
    /// </summary>
    /// <param name="trace">A trace to be registered.</param>
    ScopedCallTraceNotifier(const CallTrace &trace);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor. It removes the last registered trace from the call stack trace.
    /// </summary>
    ~ScopedCallTraceNotifier();

};

} // namespace z


#endif // __SCOPEDCALLTRACENOTIFIER__
