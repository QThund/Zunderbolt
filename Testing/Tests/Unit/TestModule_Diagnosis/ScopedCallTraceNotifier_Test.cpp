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

#include "ZDiagnosis/ScopedCallTraceNotifier.h"

#include "ZDiagnosis/CallStackTracer.h"
#include "AbstractCallStackTracePrinterMock.h"
#include "ZDiagnosis/CallStackTracePlainTextFormatter.h"
#include "ZCommon/DataTypes/EComparisonType.h"

using z::Test::AbstractCallStackTracePrinterMock;


ZTEST_SUITE_BEGIN( ScopedCallTraceNotifier_TestSuite )

void InitializeCallStackTracer_TestMethod()
{
    static bool bInitialized = false;

    if(!bInitialized)
    {
        CallStackTracer::Get()->SetPrinter(new AbstractCallStackTracePrinterMock(new CallStackTracePlainTextFormatter()));
        bInitialized = true;
    }
}

/// <summary>
/// Checks that a trace is added to the call stack trace.
/// </summary>
ZTEST_CASE ( Constructor_TraceIsAdded_Test )
{
    InitializeCallStackTracer_TestMethod();
    const string_z EXPECTED_TEXT("\
void function(int i)\n\
  | -{0}i32=2\n");

    // [Preparation]
    int i = 2;
    ArgumentTrace argument(i);
    CallTrace trace("void function(int i)", &argument, 1);

    // [Execution]
    ScopedCallTraceNotifier notifier(trace);

    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter().get()->As<AbstractCallStackTracePrinterMock>();
    string_z strPrintedText = pPrinter->GetPrintedText();

    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);

    // [Cleaning]
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that the last trace is removed from the call stack tracer.
/// </summary>
ZTEST_CASE ( Destructor_TraceIsRemoved_Test )
{
    InitializeCallStackTracer_TestMethod();
    const string_z EXPECTED_TEXT("");

    // [Preparation]
    int i = 2;
    ArgumentTrace argument(i);
    CallTrace trace("void function(int i)", &argument, 1);
    {
        ScopedCallTraceNotifier notifier(trace);

    // [Execution]
    } // Destructor is called

    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter().get()->As<AbstractCallStackTracePrinterMock>();
    string_z strPrintedText = pPrinter->GetPrintedText();

    BOOST_CHECK(strPrintedText == EXPECTED_TEXT);

    // [Cleaning]
    pPrinter->ClearPrintedText();
}

// End - Test Suite: ScopedCallTraceNotifier
ZTEST_SUITE_END()
