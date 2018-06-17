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


ZTEST_SUITE_BEGIN( ConstCharIterator_TestSuite )

/// <summary>
/// Checks that the iterator points to the first position when using a common string.
/// </summary>
ZTEST_CASE ( Constructor1_IteratorPointsToFirstPositionWhenUsingCommonString_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the iterator points to the end position when using an empty string.
/// </summary>
ZTEST_CASE ( Constructor1_IteratorPointsToEndPositionWhenUsingEmptyString_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const bool IS_END = true;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
    
    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that the iterator is correctly copied when using a common input interator.
/// </summary>
ZTEST_CASE ( Constructor2_IteratorIsCorrectlyCopiedWhenUsingCommonIterator_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    ++EXPECTED_ITERATOR;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(EXPECTED_ITERATOR);
    
    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the iterator is correctly copied when using an invalid input interator.
/// </summary>
ZTEST_CASE ( Constructor2_IteratorIsCorrectlyCopiedWhenUsingInvalidIterator_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    EXPECTED_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");

	// [Execution]
    StringUnicode::ConstCharIterator iterator(EXPECTED_ITERATOR);
    
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
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING, 5);
    
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
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING, SOURCE_STRING.GetLength());
    
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
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING, 0);
    
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
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING, 2U);
    
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ITERATOR_END);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveFirst();
    const CharUnicode SECOND_CHARACTER('B'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorPreviousState = iterator++;
    
    // [Verification]
    BOOST_CHECK(iteratorPreviousState == ORIGINAL_ITERATOR);
    BOOST_CHECK(iterator.GetChar() == SECOND_CHARACTER);
}

/// <summary>
/// Checks that the iterator steps once per code point, and not per code unit.
/// </summary>
ZTEST_CASE ( OperatorPostIncrement_IteratorStepsOncePerCodePoint_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING(CharUnicode(0x00010300)); // A character from the SMP (will use more than one code unit internally)
    SOURCE_STRING.Append("X");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
    ITERATOR_END.MoveFirst();
    ITERATOR_END--;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ITERATOR_END);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveLast();
    const CharUnicode BEFORE_LAST_CHARACTER('M'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorPreviousState = iterator--;
    
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;
    const CharUnicode LAST_CHARACTER('N'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorPreviousState = iterator--;
    
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
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING, 2U);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
    ITERATOR_END.MoveLast();
    ++ITERATOR_END;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ITERATOR_END);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveFirst();
    const CharUnicode SECOND_CHARACTER('B'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorCurrentState = ++iterator;
    
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveFirst();
    ORIGINAL_ITERATOR--;
    const CharUnicode FIRST_CHARACTER('A'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorCurrentState = ++iterator;
    
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
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_END(SOURCE_STRING);
    ITERATOR_END.MoveFirst();
    --ITERATOR_END;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ITERATOR_END);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveLast();
    const CharUnicode BEFORE_LAST_CHARACTER('M'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorCurrentState = --iterator;
    
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR.MoveLast();
    ++ORIGINAL_ITERATOR;
    const CharUnicode LAST_CHARACTER('N'); 

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    StringUnicode::ConstCharIterator iteratorCurrentState = --iterator;
    
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
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING, 2U);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
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
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");

	// [Execution]
    StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
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
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);

	// [Execution]
    StringUnicode::ConstCharIterator iterator = ITERATOR_B;
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
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_SOURCE);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_SOURCE);

	// [Execution]
    StringUnicode::ConstCharIterator iterator = ITERATOR_B;
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
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    StringUnicode::ConstCharIterator VALID_ITERATOR(SOURCE_STRING);

	// [Execution]
    StringUnicode::ConstCharIterator iterator = INVALID_ITERATOR;
    iterator = VALID_ITERATOR;
    
    // [Verification]
    BOOST_CHECK(iterator.IsValid());
    BOOST_CHECK(iterator == VALID_ITERATOR);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator == INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR == iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorEquality_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator == ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when iterators are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when iterators are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A == ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator != INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR != iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorInequality_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator != ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns False when iterators are equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenIteratorsAreEqual_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when iterators are not equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenIteratorsAreNotEqual_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A != ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator > INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR > iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator > ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B > ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenResidentIteratorIsNotGreaterThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A > ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator < INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR < iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator < ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_A < ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is not lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenResidentIteratorIsNotLowerThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_B < ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator >= INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR >= iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator >= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is greater than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorIsGreaterThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B >= ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotGreaterThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_B;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A >= ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the input or the resident iterator is not valid.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorsAreNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        iterator <= INVALID_ITERATOR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }
    
    bool bAssertionFailed2 = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(SOURCE_STRING);
        INVALID_ITERATOR <= iterator;
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the input iterator points to a different string.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_AssertionFailsWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::ConstCharIterator iterator(STRING_B);
        iterator <= ITERATOR_A;
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
/// Checks that it returns False when iterators point to a different string.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenIteratorSVectorArrayToDifferentStrings_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode STRING_B("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_B);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the resident iterator is lower than the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorIsLowerThanInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the resident iterator is equal to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenResidentIteratorEqualsInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR_B <= ITERATOR_A;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident iterator is neither greater than nor equals to the input iterator.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenResidentIteratorIsNotLowerThanAndDoNotEqualsInputIterator_Test )
{
    // [Preparation]
    StringUnicode STRING_A("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_A(STRING_A);
    StringUnicode::ConstCharIterator ITERATOR_B(STRING_A);
    ++ITERATOR_A;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR_A <= ITERATOR_B;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.IsEnd();
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
/// Checks that it returns False when the iterator is not valid.
/// </summary>
ZTEST_CASE ( IsEnd_ReturnsFalseWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = INVALID_ITERATOR.IsEnd();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that it returns True when the iterator points to the position before the first.
/// </summary>
ZTEST_CASE ( IsEnd_ReturnsTrueWhenIteratorPointsToPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveFirst();
    ITERATOR--;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the iterator points to the position after the last.
/// </summary>
ZTEST_CASE ( IsEnd_ReturnsTrueWhenIteratorPointsToPositionAfterLast_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator does not point to an end position.
/// </summary>
ZTEST_CASE ( IsEnd_ReturnsFalseWhenIteratorDoesNotPointToEndPosition_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveLast();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsEnd();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the iterator is not valid.
/// </summary>
ZTEST_CASE ( GetChar_AssertionFailsWhenIteratorIsNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = StringUnicode("ABC");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        INVALID_ITERATOR.GetChar();
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
ZTEST_CASE ( GetChar_AssertionFailsWhenIteratorPointsToEndPosition_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveLast();
    ++ITERATOR;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.GetChar();
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
/// Checks that it returns the Unicode code point U+FFFF when iterator points to an end position.
/// </summary>
ZTEST_CASE ( GetChar_ReturnsUFFFFWhenIteratorPointsToEndPosition_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveLast();
    ++ITERATOR;
    const CharUnicode NONCHARACTER = 0xFFFF;

	// [Execution]
    CharUnicode character = ITERATOR.GetChar();
    
    // [Verification]
    BOOST_CHECK(character == NONCHARACTER);
}

#endif

/// <summary>
/// Checks that it returns the expected character when the iterator points to a common position.
/// </summary>
ZTEST_CASE ( GetChar_ReturnsExpectedCharacterWhenIteratorPointsCommonPosition_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveFirst();
    ++ITERATOR;
    ++ITERATOR;
    const CharUnicode EXPECTED_CHARACTER = 'C';

	// [Execution]
    CharUnicode character = ITERATOR.GetChar();
    
    // [Verification]
    BOOST_CHECK(character == EXPECTED_CHARACTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    StringUnicode EMPTY_STRING("");
    StringUnicode::ConstCharIterator ITERATOR(EMPTY_STRING);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveFirst();
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
/// Checks that the iterator points to the end position when the string is empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    StringUnicode EMPTY_STRING("");
    StringUnicode::ConstCharIterator END_ITERATOR(EMPTY_STRING);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    StringUnicode::ConstCharIterator ITERATOR(EMPTY_STRING);

	// [Execution]
    ITERATOR.MoveFirst();
    
    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the first position when the string is not empty.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    ++ORIGINAL_ITERATOR;
    StringUnicode::ConstCharIterator ITERATOR_FIRST(SOURCE_STRING);

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was not valid.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenStringIsNotEmptyAndIteratorWasNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR_FIRST(SOURCE_STRING);
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = "ABC";

	// [Execution]
    StringUnicode::ConstCharIterator iterator(INVALID_ITERATOR);
    iterator.MoveFirst();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

/// <summary>
/// Checks that the iterator points to the first position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveFirst_IteratorPointsToFirstPositionWhenStringIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR--;

    StringUnicode::ConstCharIterator ITERATOR_FIRST(SOURCE_STRING);

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveFirst();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_FIRST);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( MoveLast_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    StringUnicode EMPTY_STRING("");
    StringUnicode::ConstCharIterator ITERATOR(EMPTY_STRING);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ITERATOR.MoveLast();
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
/// Checks that the iterator points to the end position when the string is empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    StringUnicode EMPTY_STRING("");
    StringUnicode::ConstCharIterator END_ITERATOR(EMPTY_STRING);
    END_ITERATOR.MoveLast();
    ++END_ITERATOR;
    StringUnicode::ConstCharIterator ITERATOR(EMPTY_STRING);

	// [Execution]
    ITERATOR.MoveLast();
    
    // [Verification]
    BOOST_CHECK(ITERATOR == END_ITERATOR);
}

#endif

/// <summary>
/// Checks that the iterator points to the last position when the string is not empty.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABC");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    StringUnicode::ConstCharIterator ITERATOR_LAST(SOURCE_STRING);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was not valid.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenStringIsNotEmptyAndIteratorWasNotValid_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABC");
    StringUnicode::ConstCharIterator ITERATOR_LAST(SOURCE_STRING);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;
    StringUnicode::ConstCharIterator INVALID_ITERATOR(SOURCE_STRING);
    INVALID_ITERATOR.MoveLast();
    SOURCE_STRING = "ABC";

	// [Execution]
    StringUnicode::ConstCharIterator iterator(INVALID_ITERATOR);
    iterator.MoveLast();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that the iterator points to the last position even when it was pointing to the position before the first.
/// </summary>
ZTEST_CASE ( MoveLast_IteratorPointsToLastPositionWhenStringIsNotEmptyAndIteratorWaSVectorArrayingToPositionBeforeFirst_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABC");
    StringUnicode::ConstCharIterator ORIGINAL_ITERATOR(SOURCE_STRING);
    ORIGINAL_ITERATOR--;

    StringUnicode::ConstCharIterator ITERATOR_LAST(SOURCE_STRING);
    ++ITERATOR_LAST;
    ++ITERATOR_LAST;

	// [Execution]
    StringUnicode::ConstCharIterator iterator(ORIGINAL_ITERATOR);
    iterator.MoveLast();
    
    // [Verification]
    BOOST_CHECK(iterator == ITERATOR_LAST);
}

/// <summary>
/// Checks that it returns True when iterator points to a common position.
/// </summary>
ZTEST_CASE ( IsValid_ReturnsTrueWhenIteratorPointsToCommonPosition_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABC");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = ITERATOR.IsValid();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the iterator points to an out of bounds position.
/// </summary>
ZTEST_CASE ( IsValid_ReturnsFalseWhenIteratorPointsToOutOfBoundPosition_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCEFGHIJKMN");
    StringUnicode::ConstCharIterator ITERATOR(SOURCE_STRING);
    ITERATOR.MoveLast();
    SOURCE_STRING = "ABC";
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = ITERATOR.IsValid();
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

// End - Test Suite: ConstCharIterator
ZTEST_SUITE_END()
