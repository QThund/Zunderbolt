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

#ifndef __CALLSTACKTRACECONSOLEPRINTER__
#define __CALLSTACKTRACECONSOLEPRINTER__

#include "ZDiagnosis/DiagnosisModuleDefinitions.h"

#include "AbstractCallStackTracePrinter.h"


namespace z
{

/// <summary>
/// A call stack trace printer implementation that sends text to a console.
/// </summary>
class Z_LAYER_DIAGNOSIS_SYMBOLS CallStackTraceConsolePrinter : public AbstractCallStackTracePrinter
{
    Z_RTTI_SUPPORT_DERIVED_FROM_1_CLASS(CallStackTraceConsolePrinter, AbstractCallStackTracePrinter);


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A trace formatter.</param>
    CallStackTraceConsolePrinter(ICallStackTraceFormatter* pFormatter);
    
    /// <summary>
    /// Constructor that receives a formatter to be used when printing.
    /// </summary>
    /// <param name="pFormatter">[IN] A trace formatter.</param>
    CallStackTraceConsolePrinter(boost::shared_ptr<ICallStackTraceFormatter> &pFormatter);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~CallStackTraceConsolePrinter();


    // METHODS
    // ---------------
public:

    /// @copydoc AbstractCallStackTracePrinter::PrintString
    virtual void PrintString(const string_z &strText);

    /// <summary>
    /// A string representation of the instance.
    /// </summary>
    /// <returns>
    /// The name of the class.
    /// </returns>
    virtual string_z ToString() const;

};

} // namespace z


#endif // __CALLSTACKTRACECONSOLEPRINTER__
