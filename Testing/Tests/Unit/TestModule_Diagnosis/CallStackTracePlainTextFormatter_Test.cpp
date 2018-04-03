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

#include "ZDiagnosis/CallStackTracePlainTextFormatter.h"


ZTEST_SUITE_BEGIN( CallStackTracePlainTextFormatter_TestSuite )

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallStackTraceFooter_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("End of call stack trace information.\n");
    CallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_z strOutput;

    // [Execution]
    formatter.FormatCallStackTraceFooter(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
ZTEST_CASE ( FormatCallStackTraceFooter_TextIsAppended_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Previous textEnd of call stack trace information.\n");
    CallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_z strOutput("Previous text");

    // [Execution]
    formatter.FormatCallStackTraceFooter(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallStackTraceHeader_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Call stack trace for ThreadId\n");
    CallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_z strOutput;

    // [Execution]
    formatter.FormatCallStackTraceHeader(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
ZTEST_CASE ( FormatCallStackTraceHeader_TextIsAppended_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Previous textCall stack trace for ThreadId\n");
    CallStackTrace stackTrace("ThreadId");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    stackTrace.Push(callTrace);
    string_z strOutput("Previous text");

    // [Execution]
    formatter.FormatCallStackTraceHeader(stackTrace, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallTrace_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput;

    // [Execution]
    formatter.FormatCallTrace(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallTrace_DepthLevelAffestsTheResult_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("\
int function(int i, float f)\n\
    | -{0}i32=5\n\
    | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput1;
    string_z strOutput2;
    const unsigned int DEPTH1 = 0;
    const unsigned int DEPTH2 = 1;

    // [Execution]
    formatter.FormatCallTrace(callTrace, DEPTH1, strOutput1);
    formatter.FormatCallTrace(callTrace, DEPTH2, strOutput2);
    
    // [Verification]
    BOOST_CHECK(strOutput1 != strOutput2);
    BOOST_CHECK(strOutput2 == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
ZTEST_CASE ( FormatCallTrace_TextIsAppended_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Previous text\
int function(int i, float f)\n\
  | -{0}i32=5\n\
  | -{1}f32=1\n");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTrace(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallTraceHeader_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("-->");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput;

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallTraceHeader_DepthLevelAffestsTheResult_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("  -->");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput1;
    string_z strOutput2;
    const unsigned int DEPTH1 = 0;
    const unsigned int DEPTH2 = 1;

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, DEPTH1, strOutput1);
    formatter.FormatCallTraceHeader(callTrace, DEPTH2, strOutput2);
    
    // [Verification]
    BOOST_CHECK(strOutput1 != strOutput2);
    BOOST_CHECK(strOutput2 == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
ZTEST_CASE ( FormatCallTraceHeader_TextIsAppended_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Previous text-->");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTraceHeader(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the expected text is obtained when using a common call stack trace.
/// </summary>
ZTEST_CASE ( FormatCallTraceFooter_ExpectedTextIsObtained_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput;

    // [Execution]
    formatter.FormatCallTraceFooter(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the generated text is appended to the output string.
/// </summary>
ZTEST_CASE ( FormatCallTraceFooter_TextIsAppended_Test )
{
    // [Preparation]
    CallStackTracePlainTextFormatter formatter;
    const string_z EXPECTED_TEXT("Previous text");
    int i = 5;
    float f = 1.0f;
    ArgumentTrace arArgumentTraces[] = { ArgumentTrace(i), ArgumentTrace(f) };
    CallTrace callTrace("int function(int i, float f)", arArgumentTraces, 2);
    string_z strOutput("Previous text");

    // [Execution]
    formatter.FormatCallTraceFooter(callTrace, 0, strOutput);
    
    // [Verification]
    BOOST_CHECK(strOutput == EXPECTED_TEXT);
}

// End - Test Suite: CallStackTracePlainTextFormatter
ZTEST_SUITE_END()
