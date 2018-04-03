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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZDiagnosis/AbstractCallStackTracePrinter.h"
#include "ZDiagnosis/CallStackTracePlainTextFormatter.h"
#include "AbstractCallStackTracePrinterMock.h"

using z::Test::AbstractCallStackTracePrinterMock;


ZTEST_SUITE_BEGIN( AbstractCallStackTracePrinter_TestSuite )

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( PrintCallStack_ExpectedTextIsPrintedWhenUsingCommonStackTrace_Test )
{
    // [Preparation]
    boost::shared_ptr<ICallStackTraceFormatter> pFormatter(new CallStackTracePlainTextFormatter());
    AbstractCallStackTracePrinterMock printer;
    printer.SetFormatter(pFormatter);
    const string_z EXPECTED_TEXT("Call stack trace for ThreadId\n\
-->int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
  -->int function(int i)\n\
    | -{0}i32=5\n\
    -->int function()\n\
End of call stack trace information.\n");
    CallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    stackTrace.Push(CallTrace("int function(int i, float f)", arArgumentTraces, 2));
    stackTrace.Push(CallTrace("int function(int i)", arArgumentTraces, 1));
    stackTrace.Push(CallTrace("int function()", null_z, 0));

    // [Execution]
    printer.PrintCallStackTrace(stackTrace);
    
    // [Verification]
    BOOST_CHECK(printer.GetPrintedText() == EXPECTED_TEXT);
}


// End - Test Suite: AbstractCallStackTracePrinter
ZTEST_SUITE_END()
