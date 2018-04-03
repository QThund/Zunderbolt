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

#include "ZCommon/DataTypes/CharUnicode.h"


ZTEST_SUITE_BEGIN( CharUnicode_TestSuite )
    
/// <summary>
/// Checks that the character is properly initialized to U+0000
/// </summary>
ZTEST_CASE ( Constructor1_CharacterIsProperlyInitializedToZero_Test )
{
    // [Preparation]
    CharUnicode EXPECTED_RESULT(0); 

	// [Execution]
    CharUnicode character;
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the character is properly initialized using a common code point.
/// </summary>
ZTEST_CASE ( Constructor2_CharacterIsProperlyInitialized_Test )
{
    // [Preparation]
    codepoint_z INPUT_CODEPOINT = 159; // arbitrary value
    CharUnicode EXPECTED_RESULT(INPUT_CODEPOINT); 

	// [Execution]
    CharUnicode character(INPUT_CODEPOINT);
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the copy of a character is equal to the original.
/// </summary>
ZTEST_CASE ( Constructor3_CopiedCharacterIsEqualToOriginal_Test )
{
    // [Preparation]
    codepoint_z INPUT_CODEPOINT = 159; // arbitrary value
    CharUnicode EXPECTED_RESULT(INPUT_CODEPOINT);

	// [Execution]
    CharUnicode character(EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the assigned character is equal to the copied character.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CopiedCharacterIsEqualToOriginal_Test )
{
    // [Preparation]
    codepoint_z INPUT_CODEPOINT = 159; // arbitrary value
    CharUnicode EXPECTED_RESULT(INPUT_CODEPOINT);

	// [Execution]
    CharUnicode character(0);
    character = EXPECTED_RESULT;
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when characters have the same code point.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenCharactersHaveSameCodePoint_Test )
{
    // [Preparation]
    const codepoint_z INPUT_CODEPOINT = 159; // arbitrary value
    const CharUnicode CHARACTER1(INPUT_CODEPOINT);
    const CharUnicode CHARACTER2(INPUT_CODEPOINT);
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bResult = CHARACTER1 == CHARACTER2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when characters have a different code point.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenCharactersHaveDifferentCodePoint_Test )
{
    // [Preparation]
    const codepoint_z INPUT_CODEPOINT1 = 159; // arbitrary value
    const codepoint_z INPUT_CODEPOINT2 = 200; // arbitrary value
    const CharUnicode CHARACTER1(INPUT_CODEPOINT1);
    const CharUnicode CHARACTER2(INPUT_CODEPOINT2);
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = CHARACTER1 == CHARACTER2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when characters have the same code point.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenCharactersHaveSameCodePoint_Test )
{
    // [Preparation]
    const codepoint_z INPUT_CODEPOINT = 159; // arbitrary value
    const CharUnicode CHARACTER1(INPUT_CODEPOINT);
    const CharUnicode CHARACTER2(INPUT_CODEPOINT);
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = CHARACTER1 != CHARACTER2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when characters have a different code point.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenCharactersHaveDifferentCodePoint_Test )
{
    // [Preparation]
    const codepoint_z INPUT_CODEPOINT1 = 159; // arbitrary value
    const codepoint_z INPUT_CODEPOINT2 = 200; // arbitrary value
    const CharUnicode CHARACTER1(INPUT_CODEPOINT1);
    const CharUnicode CHARACTER2(INPUT_CODEPOINT2);
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bResult = CHARACTER1 != CHARACTER2;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected code point.
/// </summary>
ZTEST_CASE ( GetCodePoint_ReturnsExpectedCodePoint_Test )
{
    // [Preparation]
    const codepoint_z EXPECTED_CODEPOINT = 159; // arbitrary value
    const CharUnicode CHARACTER(EXPECTED_CODEPOINT);

	// [Execution]
    codepoint_z codepoint = CHARACTER.GetCodePoint();
    
    // [Verification]
    BOOST_CHECK_EQUAL(codepoint, EXPECTED_CODEPOINT);
}

// End - Test Suite: CharUnicode
ZTEST_SUITE_END()
