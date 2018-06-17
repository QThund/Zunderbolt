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

#include "ZCommon/DataTypes/StringUnicode.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( CharIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the first position when using a common string.
/// </summary>
ZTEST_CASE ( Constructor1_IteratorPointsToFirstPositionWhenUsingCommonString_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator EXPECTED_ITERATOR(strSourceString);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    StringUnicode::CharIterator iterator(strSourceString);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the iterator points to the end position when using an empty string.
/// </summary>
ZTEST_CASE ( Constructor1_IteratorPointsToEndPositionWhenUsingEmptyString_Test )
{
    // [Preparation]
    StringUnicode strSourceString("");
    const bool IS_END = true;

	// [Execution]
    StringUnicode::CharIterator iterator(strSourceString);
    
    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that the iterator is correctly copied when using a common input interator.
/// </summary>
ZTEST_CASE ( Constructor2_IteratorIsCorrectlyCopiedWhenUsingCommonIterator_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator EXPECTED_ITERATOR(strSourceString);
    ++EXPECTED_ITERATOR;

	// [Execution]
    StringUnicode::CharIterator iterator(EXPECTED_ITERATOR);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the iterator is correctly copied when using an invalid input interator.
/// </summary>
ZTEST_CASE ( Constructor2_IteratorIsCorrectlyCopiedWhenUsingInvalidIterator_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator EXPECTED_ITERATOR(strSourceString);
    EXPECTED_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");

	// [Execution]
    StringUnicode::CharIterator iterator(EXPECTED_ITERATOR);
    
    // [Verification]
    BOOST_CHECK(!iterator.IsValid());
}

/// <summary>
/// Checks that the iterator points to the given position.
/// </summary>
ZTEST_CASE ( Constructor3_IteratorPointsToTheGivenPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const CharUnicode EXPECTED_CHARACTER = 'F';

	// [Execution]
    StringUnicode::CharIterator iterator(SOURCE_STRING, 5);
    
    // [Verification]
    CharUnicode charPointedToByIterator = iterator.GetChar();
    BOOST_CHECK(charPointedToByIterator == EXPECTED_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when input initial position is out of bounds.
/// </summary>
ZTEST_CASE ( Constructor3_IteratorPointsToEndPositionWhenInitialPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    StringUnicode::CharIterator iterator(SOURCE_STRING, SOURCE_STRING.GetLength());
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when the string is empty.
/// </summary>
ZTEST_CASE ( Constructor3_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING = StringUnicode::GetEmpty();
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    StringUnicode::CharIterator iterator(SOURCE_STRING, 0);
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the iterator points to the right position when using characters from the Supplementary Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( Constructor3_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    SOURCE_STRING.Append(CharUnicode(0x00010400));
    const CharUnicode EXPECTED_CHARACTER(CharUnicode(0x00010400)); 

	// [Execution]
    StringUnicode::CharIterator iterator(SOURCE_STRING, 2U);
    
    // [Verification]
    CharUnicode currentChar = iterator.GetChar();
    BOOST_CHECK(currentChar == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR++;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END++;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    StringUnicode::CharIterator iterator(ITERATOR_END);
    iterator++;
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the previous state.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_CommonIteratorStepsForwardProperlyAndReturnsPreviousState_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveFirst();
    const CharUnicode SECOND_CHARACTER('B'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorPreviousState = iterator++;
    
    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator.GetChar() == SECOND_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the previous state when it was pointing to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorPointsToFirstPositionAndReturnsPreviousStateWhenItWaSVectorArrayingToPositionBeforeFirst_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveFirst();
    ORIGINAL_ITERATOR--;
    const CharUnicode FIRST_CHARACTER('A'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorPreviousState = iterator++;
    CharUnicode currentChar = iterator.GetChar();
    
    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(currentChar == FIRST_CHARACTER);
}

/// <summary>
/// Checks that the iterator steps once per code point, and not per code unit.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    StringUnicode::CharIterator ITERATOR(SOURCE_STRING);
    const CharUnicode EXPECTED_CHARACTER('X'); 

	// [Execution]
    ITERATOR++;
    
    // [Verification]
    CharUnicode currentChar = ITERATOR.GetChar();
    BOOST_CHECK(currentChar == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR--;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR_END--;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    StringUnicode::CharIterator iterator(ITERATOR_END);
    iterator--;
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the previous state.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_CommonIteratorStepsBackwardProperlyAndReturnsPreviousState_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveLast();
    const CharUnicode BEFORE_LAST_CHARACTER('M'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorPreviousState = iterator--;
    
    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator.GetChar() == BEFORE_LAST_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the previous state when it was pointing to the end position after the last one.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorPointsToLastPositionAndReturnsPreviousStateWhenItWaSVectorArrayingToLastEndPosition_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;
    const CharUnicode LAST_CHARACTER('N'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorPreviousState = iterator--;
    
    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator.GetChar() == LAST_CHARACTER);
}

/// <summary>
/// Checks that the iterator steps once per code point, and not per code unit.
/// </summary>
ZTEST_CASE ( OperatorPostDecrement_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    SOURCE_STRING.Append(CharUnicode(0x00010400));
    StringUnicode::CharIterator ITERATOR(SOURCE_STRING, 2U);
    const CharUnicode EXPECTED_CHARACTER(CharUnicode(0x00010300)); 

	// [Execution]
    ITERATOR--;
    ITERATOR--;
    
    // [Verification]
    CharUnicode currentChar = ITERATOR.GetChar();
    BOOST_CHECK(currentChar == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_AssertionFailsWhenIteratorAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ++ITERATOR_END;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorDoesNotChangeWhenItAlreadyPointsToLastEndPosition_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    StringUnicode::CharIterator iterator(ITERATOR_END);
    ++iterator;
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps forward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_CommonIteratorStepsForwardProperlyAndReturnsCurrentState_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveFirst();
    const CharUnicode SECOND_CHARACTER('B'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorCurrentState = ++iterator;
    
    // [Verification]
    BOOST_CHECK(iteratorCurrentState.GetChar() == SECOND_CHARACTER);
    BOOST_CHECK(iterator.GetChar() == SECOND_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to the first position and returns the current state when it was pointing to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorPointsToFirstPositionAndReturnsCurrentStateWhenItWaSVectorArrayingToPositionBeforeFirst_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveFirst();
    ORIGINAL_ITERATOR--;
    const CharUnicode FIRST_CHARACTER('A'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorCurrentState = ++iterator;
    
    // [Verification]
    BOOST_CHECK(iteratorCurrentState.GetChar() == FIRST_CHARACTER);
    BOOST_CHECK(iterator.GetChar() == FIRST_CHARACTER);
}

/// <summary>
/// Checks that the iterator steps once per code point, and not per code unit.
/// </summary>
ZTEST_CASE ( OperatorPreIncrement_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    StringUnicode::CharIterator ITERATOR(SOURCE_STRING);
    const CharUnicode EXPECTED_CHARACTER('X'); 

	// [Execution]
    ++ITERATOR;
    
    // [Verification]
    CharUnicode currentChar = ITERATOR.GetChar();
    BOOST_CHECK(currentChar == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator already points to the end position before the first one.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_AssertionFailsWhenIteratorAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        --ITERATOR_END;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator does not change when it already points to the end position.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorDoesNotChangeWhenItAlreadyPointsToEndPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_END(strSourceString);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    StringUnicode::CharIterator iterator(ITERATOR_END);
    --iterator;
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_END);
}

#endif

/// <summary>
/// Checks that the iterator steps backward properly and returns the current state.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_CommonIteratorStepsBackwardProperlyAndReturnsCurrentState_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveLast();
    const CharUnicode BEFORE_LAST_CHARACTER('M'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorCurrentState = --iterator;
    
    // [Verification]
    BOOST_CHECK(iteratorCurrentState.GetChar() == BEFORE_LAST_CHARACTER);
    BOOST_CHECK(iterator.GetChar() == BEFORE_LAST_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to the last position and returns the current state when it was pointing to the end position after the last one.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorPointsToLastPositionAndReturnsCurrentStateWhenItWaSVectorArrayingToLastEndPosition_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ORIGINAL_ITERATOR(strSourceString);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;
    const CharUnicode LAST_CHARACTER('N'); 

	// [Execution]
    StringUnicode::CharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::CharIterator iteratorCurrentState = --iterator;
    
    // [Verification]
    BOOST_CHECK(iteratorCurrentState.GetChar() == LAST_CHARACTER);
    BOOST_CHECK(iterator.GetChar() == LAST_CHARACTER);
}

/// <summary>
/// Checks that the iterator steps once per code point, and not per code unit.
/// </summary>
ZTEST_CASE ( OperatorPreDecrement_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    SOURCE_STRING.Append(CharUnicode(0x00010400));
    StringUnicode::CharIterator ITERATOR(SOURCE_STRING, 2U);
    const CharUnicode EXPECTED_CHARACTER(CharUnicode(0x00010300)); 

	// [Execution]
    --ITERATOR;
    --ITERATOR;
    
    // [Verification]
    CharUnicode currentChar = ITERATOR.GetChar();
    BOOST_CHECK(currentChar == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignation_AssertionFailsWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::CharIterator iterator(strSourceString);
        iterator = INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorAssignation_AssertionFailsWhenInputIteratorPointsToDifferentString_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::CharIterator iterator(STRING_B);
        iterator = ITERATOR_A;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the iterator is copied when it is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignation_IteratorIsCopiedWhenInputIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");

	// [Execution]
    StringUnicode::CharIterator iterator(strSourceString);
    iterator = INVALID_ITERATOR;
    
    // [Verification]
    BOOST_CHECK(iterator == INVALID_ITERATOR);
}

/// <summary>
/// Checks that the iterator is not copied when it points to a different string.
/// </summary>
ZTEST_CASE ( OperatorAssignation_IteratorDoesNotChangeIfInputIteratorPointsToDifferentString_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_A(STRING_A);
    StringUnicode::CharIterator ITERATOR_B(STRING_B);

	// [Execution]
    StringUnicode::CharIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK(iterator != ITERATOR_A);
    BOOST_CHECK(iterator == ITERATOR_B);
}

#endif

/// <summary>
/// Checks that a common iterator is copied.
/// </summary>
ZTEST_CASE ( OperatorAssignation_InputIteratorIsCorrectlyCopied_Test )
{
    // [Preparation]
    StringUnicode STRING_SOURCE("ABCDEFGHIJKMN");
    StringUnicode::CharIterator ITERATOR_A(STRING_SOURCE);
    StringUnicode::CharIterator ITERATOR_B(STRING_SOURCE);

	// [Execution]
    StringUnicode::CharIterator iterator = ITERATOR_B;
    iterator = ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_A);
}

/// <summary>
/// Checks that input iterator is copied when resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorAssignation_InputIteratorIsCorrectlyCopiedWhenResidentIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    StringUnicode::CharIterator VALID_ITERATOR(strSourceString);

	// [Execution]
    StringUnicode::CharIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;
    
    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( SetChar_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator INVALID_ITERATOR(strSourceString);
    INVALID_ITERATOR.MoveLast();
    strSourceString = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;
    const CharUnicode CHARACTER = 'A';

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.SetChar(CHARACTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the iterator points to end position.
/// </summary>
ZTEST_CASE ( SetChar_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    const CharUnicode CHARACTER = 'A';
    StringUnicode::CharIterator iterator(strSourceString);
    iterator.MoveLast();
    ++iterator;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        iterator.SetChar(CHARACTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that nothing happens when iterator points to an end position.
/// </summary>
ZTEST_CASE ( SetChar_NothingHappensWhenIteratorPointsToEndPosition_Test )
{

    // [Preparation]
    StringUnicode ORIGINAL_STRING("ABCDEFGHIJKMN");
    StringUnicode strSourceString(ORIGINAL_STRING);
    StringUnicode::CharIterator iterator(strSourceString);
    iterator.MoveLast();
    ++iterator;
    const CharUnicode CHARACTER = 0xFFFF;

	// [Execution]
    iterator.SetChar(CHARACTER);
    
    // [Verification]
    BOOST_CHECK(strSourceString == ORIGINAL_STRING);
}

#endif

/// <summary>
/// Checks that it returns the expected character when the iterator points to a common position.
/// </summary>
ZTEST_CASE ( SetChar_SetsCharacterCorrectlyWhenIteratorPointsCommonPosition_Test )
{

    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKMN");
    StringUnicode::CharIterator iterator(strSourceString);
    iterator.MoveFirst();
    ++iterator;
    ++iterator;
    const CharUnicode EXPECTED_CHARACTER = 'X';

	// [Execution]
    iterator.SetChar(EXPECTED_CHARACTER);
    
    // [Verification]
    CharUnicode character = iterator.GetChar();
    BOOST_CHECK(character == EXPECTED_CHARACTER);
}


// End - Test Suite: CharIterator
ZTEST_SUITE_END()
