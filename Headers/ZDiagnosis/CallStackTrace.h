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

#ifndef __CALLSTACKTRACE__
#define __CALLSTACKTRACE__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "ZDiagnosis/CallTrace.h"
#include "ZContainers/ArrayDynamic.h"


namespace z
{

/// <summary>
/// A call stack trace, which stores information about function calls and is associated to a concrete thread.
/// </summary>
class Z_DIAGNOSIS_MODULE_SYMBOLS CallStackTrace
{

    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives the id of a thread as a string.
    /// </summary>
    /// <param name="strThreadId">[IN] The Id of the thread.</param>
    explicit CallStackTrace(const string_z &strThreadId);
    
private:

    // Hidden
    CallStackTrace(const CallStackTrace&);


    // METHODS
    // ---------------
private:

    // Hidden
    CallStackTrace& operator=(const CallStackTrace&);

public:

    /// <summary>
    /// Adds a new call trace to the top of the stack.
    /// </summary>
    /// <param name="callTrace">[IN] A call trace to be copied.</param>
    void Push(const CallTrace &callTrace);

    /// <summary>
    /// Removes the call trace from the top of the stack.
    /// </summary>
    void Pop();

    /// <summary>
    /// Gets a call trace.
    /// </summary>
    /// <param name="uIndex">[IN] The position index (zero-based) in the stack of call traces, from bottom to top. It must be lower than the number of call traces in the stack.</param>
    /// <returns>
    /// The obtained call trace.
    /// </returns>
    CallTrace GetTrace(const puint_z uIndex) const;


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the number of call traces in the stack.
    /// </summary>
    /// <returns>
    /// The number of call traces in the stack.
    /// </returns>
    puint_z GetCount() const;
    
    /// <summary>
    /// Gets the thread Id.
    /// </summary>
    /// <returns>
    /// The thread Id as a string.
    /// </returns>
    string_z GetThreadId() const;


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The function call traces in the call stack trace. It is used as a stack.
    /// </summary>
    ArrayDynamic<CallTrace> m_arCallTraces;
    
    /// <summary>
    /// The Id of the thread associated to this call stack trace.
    /// </summary>
    string_z m_strThreadId;

};

} // namespace z


#endif // __CALLSTACKTRACE__
