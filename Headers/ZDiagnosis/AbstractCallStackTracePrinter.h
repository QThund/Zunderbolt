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

#ifndef __ABSTRACTCALLSTACKTRACEPRINTER__
#define __ABSTRACTCALLSTACKTRACEPRINTER__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "ZDiagnosis/ICallStackTraceFormatter.h"
#include "ZDiagnosis/CallStackTrace.h"
#include "ZCommon/RTTIDefinitions.h"
#include <boost/shared_ptr.hpp>


namespace z
{

/// <summary>
/// Represents a component whose job is to send the content of a call stack trace to an output channel, depending on the implementation.
/// </summary>
class Z_DIAGNOSIS_MODULE_SYMBOLS AbstractCallStackTracePrinter
{
    Z_RTTI_SUPPORT_ABSTRACT_CLASS(AbstractCallStackTracePrinter);
    

    // METHODS
    // ---------------
public:
        
    /// <summary>
    /// Prints information from a call stack trace using the format provided by the stored formatter.
    /// </summary>
    /// <param name="callStackTrace">[IN] A call stack trace.</param>
    virtual void PrintCallStackTrace(const CallStackTrace &callStackTrace);
    
    /// <summary>
    /// Prints text to the output channel.
    /// </summary>
    /// <param name="strText">[IN] Text to be printed.</param>
    virtual void PrintString(const string_z &strText)=0;


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Sets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A call stack trace formatter. It will be stored in a shared smart pointer.</param>
    void SetFormatter(ICallStackTraceFormatter* pFormatter);
    
    /// <summary>
    /// Sets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A call stack trace formatter. It will be stored in a shared smart pointer.</param>
    void SetFormatter(boost::shared_ptr<ICallStackTraceFormatter> &pFormatter);
    
    /// <summary>
    /// Gets the call stack trace formatter to be used when printing.
    /// </summary>
    /// <returns>
    /// The stored formatter instance.
    /// </returns>
    boost::shared_ptr<ICallStackTraceFormatter> GetFormatter() const;
    

    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The call stack trace formatter to be used when printing.
    /// </summary>
    boost::shared_ptr<ICallStackTraceFormatter> m_pFormatter;

};

} // namespace z


#endif // __ABSTRACTCALLSTACKTRACEPRINTER__
