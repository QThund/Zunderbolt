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

#ifndef __CALLSTACKTRACEPLAINTEXTFORMATTER__
#define __CALLSTACKTRACEPLAINTEXTFORMATTER__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "ICallStackTraceFormatter.h"


namespace z
{

/// <summary>
/// A call stack trace formatter implementation that generates plain text, without using any existing markup language nor standard format.
/// </summary>
class Z_LAYER_DIAGNOSIS_SYMBOLS CallStackTracePlainTextFormatter : public ICallStackTraceFormatter
{
public:

    Z_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(CallStackTracePlainTextFormatter, ICallStackTraceFormatter);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~CallStackTracePlainTextFormatter();


    // METHODS
    // ---------------
public:

    /// @copydoc ICallStackTraceFormatter::FormatCallStackTraceFooter
    virtual void FormatCallStackTraceFooter(const CallStackTrace &trace, string_z &strFormattedTrace) const;

    /// @copydoc ICallStackTraceFormatter::FormatCallStackTraceHeader
    virtual void FormatCallStackTraceHeader(const CallStackTrace &trace, string_z &strFormattedTrace) const;

    /// @copydoc ICallStackTraceFormatter::FormatCallTrace
    virtual void FormatCallTrace(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const;

    /// @copydoc ICallStackTraceFormatter::FormatCallTraceFooter
    virtual void FormatCallTraceFooter(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const;

    /// @copydoc ICallStackTraceFormatter::FormatCallTraceHeader
    virtual void FormatCallTraceHeader(const CallTrace &trace, const unsigned int uDepthLevel, string_z &strFormattedTrace) const;
    
    /// <summary>
    /// A string representation of the instance.
    /// </summary>
    /// <returns>
    /// The name of the class.
    /// </returns>
    virtual string_z ToString() const;

};

} // namespace z


#endif // __CALLSTACKTRACEPLAINTEXTFORMATTER__
