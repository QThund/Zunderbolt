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

#include "ZDiagnosis/CallStackTracer.h"
#include "AbstractCallStackTracePrinterMock.h"
#include "ZDiagnosis/CallStackTracePlainTextFormatter.h"
#include "ZCommon/DataTypes/EComparisonType.h"

using z::Test::AbstractCallStackTracePrinterMock;


ZTEST_SUITE_BEGIN( CallStackTracer_TestSuite )

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
/// Checks that it creates a call stack trace when it does not exist yet.
/// </summary>
ZTEST_CASE ( AddTrace_CallStackTraceIsCreatedWhenItDoesNotExist_Test )
{
    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_z EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);

    // [Execution]
    CallStackTracer::Get()->AddTrace(callTrace);
    
    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter()->As<AbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);

    // [Cleaning]
    CallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that a call trace is correctly added to the call stack trace.
/// </summary>
ZTEST_CASE ( AddTrace_CallTraceIsAddedToExistingStack_Test )
{
    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_z EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
  -->int function2(float f)\n\
    | -{0}f32=2\n");
    int i = 5;
    float f = 1.0f;
    float f2 = 2.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    ArgumentTrace arArgumentTraces2[] = { ArgumentTrace(f2) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    CallTrace callTrace2("int function2(float f)", arArgumentTraces2, 1);
    CallStackTracer::Get()->AddTrace(callTrace);

    // [Execution]
    CallStackTracer::Get()->AddTrace(callTrace2);
    
    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter()->As<AbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);
    
    // [Cleaning]
    CallStackTracer::Get()->RemoveLastTrace();
    CallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that it removes the last trace only.
/// </summary>
ZTEST_CASE ( RemoveLastTrace_RemovesTheLastTraceOnly_Test )
{
    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    const string_z EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n\
End of call stack trace information.\n");
    int i = 5;
    float f = 1.0f;
    float f2 = 2.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    ArgumentTrace arArgumentTraces2[] = { ArgumentTrace(f2) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    CallTrace callTrace2("int function2(float f)", arArgumentTraces2, 1);
    CallStackTracer::Get()->AddTrace(callTrace);
    CallStackTracer::Get()->AddTrace(callTrace2);

    // [Execution]
    CallStackTracer::Get()->RemoveLastTrace();
    
    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter()->As<AbstractCallStackTracePrinterMock>();
    bool bPrintedTextContainsExpectedTrace = pPrinter->GetPrintedText().Contains(EXPECTED_TEXT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bPrintedTextContainsExpectedTrace);
    
    // [Cleaning]
    CallStackTracer::Get()->RemoveLastTrace();
    pPrinter->ClearPrintedText();
}

/// <summary>
/// Checks that it deletes a call stack trace when it is empty.
/// </summary>
ZTEST_CASE ( RemoveLastTrace_CallStackTraceIsDeletedWhenItIsEmpty_Test )
{
    // [Preparation]
    InitializeCallStackTracer_TestMethod();
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    CallStackTracer::Get()->AddTrace(callTrace);

    // [Execution]
    CallStackTracer::Get()->RemoveLastTrace();
    
    // [Verification]
    CallStackTracer::Get()->Dump();
    AbstractCallStackTracePrinterMock* pPrinter = CallStackTracer::Get()->GetPrinter()->As<AbstractCallStackTracePrinterMock>();
    bool bPrintedTextIsEmpty = pPrinter->GetPrintedText().IsEmpty();
    BOOST_CHECK(bPrintedTextIsEmpty);
}

// End - Test Suite: CallStackTracer
ZTEST_SUITE_END()
