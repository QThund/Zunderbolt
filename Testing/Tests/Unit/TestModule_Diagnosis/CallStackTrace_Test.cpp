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

#include "ZDiagnosis/CallStackTrace.h"


ZTEST_SUITE_BEGIN( CallStackTrace_TestSuite )

/// <summary>
/// Checks that the input parameters are correctly stored
/// </summary>
ZTEST_CASE ( Constructor_InputParametersAreCorrectlyStored_Test )
{
    // [Preparation]
    const string_z EXPECTED_THREAD_ID("Thread(XXXX)");

    // [Execution]
    CallStackTrace callStackTrace(EXPECTED_THREAD_ID);
    
    // [Verification]
    string_z strThreadId = callStackTrace.GetThreadId();
    BOOST_CHECK(strThreadId == EXPECTED_THREAD_ID);
}

/// <summary>
/// Checks that elements can be added to empty stacks.
/// </summary>
ZTEST_CASE ( Push_ElementIsCorrectlyPushedToEmptyStack_Test )
{
    // [Preparation]
    CallStackTrace emptyStack("Id");
    const char* szFunctionName = "void Function()";
    CallTrace trace(szFunctionName, null_z, 0);

    // [Execution]
    emptyStack.Push(trace);

    // [Verification]
    const char* szStoredValue = emptyStack.GetTrace(0).GetFunctionSignature();
    BOOST_CHECK(string_z(szStoredValue) == string_z(szFunctionName));
}

/// <summary>
/// Checks that elements are correctly added at the end of a common stack.
/// </summary>
ZTEST_CASE ( Push_ElementIsCorrectlyPushedAtTheEnd_Test )
{
    // [Preparation]
    CallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const CallTrace EXPECTED_TRACE(szFunctionName, null_z, 0);
    const CallTrace TRACE("", null_z, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);

    // [Execution]
    callStack.Push(EXPECTED_TRACE);

    // [Verification]
    const char* szStoredValue = callStack.GetTrace(callStack.GetCount() - 1U).GetFunctionSignature();
    BOOST_CHECK(string_z(szStoredValue) == string_z(szFunctionName));
}

/// <summary>
/// Checks that the count of elements of the stack is increased after an element is added.
/// </summary>
ZTEST_CASE ( Push_CountIsIncreasedAfterPushingAnElement_Test )
{
    // [Preparation]
    CallStackTrace callStack("Id");
    const CallTrace TRACE("", null_z, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);
    const puint_z ORIGINAL_COUNT = callStack.GetCount();

    // [Execution]
    callStack.Push(TRACE);

    // [Verification]
    puint_z uCount = callStack.GetCount();
    BOOST_CHECK_GT(uCount, ORIGINAL_COUNT);
}

/// <summary>
/// Checks that elements are correctly removed from the last position of the stack.
/// </summary>
ZTEST_CASE ( Pop_ElementIsCorrectlyRemovedFromLastPosition_Test )
{
    // [Preparation]
    CallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const CallTrace EXPECTED_TRACE(szFunctionName, null_z, 0);
    const CallTrace TRACE("", null_z, 0);
    callStack.Push(TRACE);
    callStack.Push(EXPECTED_TRACE);
    callStack.Push(TRACE);

    // [Execution]
    callStack.Pop();

    // [Verification]
    const char* szStoredValue = callStack.GetTrace(callStack.GetCount() - 1U).GetFunctionSignature();
    BOOST_CHECK(string_z(szStoredValue) == string_z(szFunctionName));
}

/// <sumary>
/// Checks if it gets the correct value at supplied position.
/// </sumary>
ZTEST_CASE( GetTrace_GetsCorrectValueAtSuppliedPosition_Test )
{
    // [Preparation]
    CallStackTrace callStack("Id");
    const char* szFunctionName = "void Function()";
    const CallTrace EXPECTED_TRACE(szFunctionName, null_z, 0);
    const CallTrace TRACE("", null_z, 0);
    callStack.Push(TRACE);
    callStack.Push(EXPECTED_TRACE);
    callStack.Push(TRACE);
    const puint_z INPUT_INDEX = 1U;

    // [Execution]
    CallTrace trace = callStack.GetTrace(INPUT_INDEX);

    // [Verification]
    const char* szStoredValue = trace.GetFunctionSignature();
    BOOST_CHECK(string_z(szStoredValue) == string_z(szFunctionName));
}

/// <sumary>
/// Returns the number of elements in the array.
/// </sumary>
ZTEST_CASE( GetCount_ReturnsNumberOfElementsInTheStack_Test )
{
    // [Preparation]
    CallStackTrace callStack("Id");
    const puint_z EXPECTED_COUNT = 3U;
    const CallTrace TRACE("", null_z, 0);
    callStack.Push(TRACE);
    callStack.Push(TRACE);
    callStack.Push(TRACE);

    // [Execution]
    puint_z uCount = callStack.GetCount();

    // [Verification]
    BOOST_CHECK_EQUAL(uCount, EXPECTED_COUNT);
}

// End - Test Suite: CallStackTrace
ZTEST_SUITE_END()
