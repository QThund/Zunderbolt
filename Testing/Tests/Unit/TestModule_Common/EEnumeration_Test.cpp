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

#include "EEnumerationMock.h"

using Test::EEnumerationMock;


ZTEST_SUITE_BEGIN( EEnumerationMock_TestSuite )

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
ZTEST_CASE ( Constructor1_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EEnumerationMock::EnumType EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input integer value is correctly converted to the corresponding enumeration value.
/// </summary>
ZTEST_CASE ( Constructor2_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;
    const enum_int_z INPUT_VALUE = 1;

	// [Execution]
    EEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input string value is correctly converted to the corresponding enumeration value.
/// </summary>
ZTEST_CASE ( Constructor3_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const char* INPUT_VALUE = Z_L("Value2");
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
ZTEST_CASE ( Constructor4_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input integer value is correctly converted to the corresponding enumeration value.
/// </summary>
ZTEST_CASE ( OperatorAssignation1_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;
    const enum_int_z INPUT_VALUE = 1;

	// [Execution]
    EEnumerationMock eEnumeration(EEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration value is undefined when the input integer value doesn't correspondo to a valid value.
/// </summary>
ZTEST_CASE ( OperatorAssignation1_EnumGetsUndefinedValueWhenInvalidInputValueIsSet_Test )
{
    // [Preparation]
    const ArrayBasic<const EEnumerationMock::EnumType> VALID_VALUES = EEnumerationMock::GetValues();
    const enum_int_z INPUT_VALUE = EEnumerationMock::_NotEnumValue - 1;

	// [Execution]
    EEnumerationMock eEnumeration(EEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    for(size_t i = 0; i < VALID_VALUES.GetCount(); ++i)
    {
        BOOST_CHECK(eEnumeration != VALID_VALUES[i]);
    }
}

/// <summary>
/// Checks that the input string value is correctly converted to the corresponding enumeration value.
/// </summary>
ZTEST_CASE ( OperatorAssignation2_InputValueIsCorrectlyConvertedToCorrespondingEnumValue_Test )
{
    // [Preparation]
    const char* INPUT_VALUE = Z_L("Value2");
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration(EEnumerationMock::E_Value1);
    eEnumeration = INPUT_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
ZTEST_CASE ( OperatorAssignation3_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EEnumerationMock::EnumType EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration(EEnumerationMock::E_Value1);
    eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the input value is correctly stored in the enumeration.
/// </summary>
ZTEST_CASE ( OperatorAssignation4_InputValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const EEnumerationMock EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock eEnumeration(EEnumerationMock::E_Value1);
    eEnumeration = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(eEnumeration == EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality1_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value2;
    const EEnumerationMock OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality1_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value1;
    const EEnumerationMock OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality2_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value2;
    const char* OPERAND2 = Z_L("Value2");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality2_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value1;
    const char* OPERAND2 = Z_L("Value2");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality3_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value2;
    const enum_int_z OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality3_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value1;
    const enum_int_z OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality4_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value2;
    const EEnumerationMock::EnumType OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when operands are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality4_ReturnsFalseWhenOperandsAreNotEqual_Test )
{
    // [Preparation]
    const EEnumerationMock OPERAND1 = EEnumerationMock::E_Value1;
    const EEnumerationMock::EnumType OPERAND2 = EEnumerationMock::E_Value2;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OPERAND1 == OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned values match what expected.
/// </summary>
ZTEST_CASE ( GetValues_ReturnsAllTheValues_Test )
{
    // [Preparation]
    const EEnumerationMock::EnumType EXPECTED_RESULT[] = {EEnumerationMock::E_Value1,
                                                           EEnumerationMock::E_Value2,
                                                           EEnumerationMock::E_Value3};
    const puint_z EXPECTED_COUNT = 3;

	// [Execution]
    const ArrayBasic<const EEnumerationMock::EnumType> arResult = EEnumerationMock::GetValues();

    // [Verification]
    BOOST_CHECK_EQUAL(arResult.GetCount(), EXPECTED_COUNT);

    for(puint_z uIndexResult = 0; uIndexResult < EXPECTED_COUNT; ++uIndexResult)
    {
        BOOST_CHECK_EQUAL(arResult[uIndexResult], EXPECTED_RESULT[uIndexResult]);
    }
}

/// <summary>
/// Checks that the _NotEnumValue value is not included in the list.
/// </summary>
ZTEST_CASE ( GetValues_DoesNotIncludeNotEnumValue_Test )
{
    // [Preparation]
    const puint_z EXPECTED_COUNT = 3;
    const EEnumerationMock::EnumType NOT_INCLUDED_VALUE = EEnumerationMock::_NotEnumValue;

	// [Execution]
    const ArrayBasic<const EEnumerationMock::EnumType> arResult = EEnumerationMock::GetValues();

    // [Verification]
    BOOST_CHECK_EQUAL(arResult.GetCount(), EXPECTED_COUNT);

    for(puint_z uIndexResult = 0; uIndexResult < EXPECTED_COUNT; ++uIndexResult)
    {
        BOOST_CHECK_NE(arResult[uIndexResult], NOT_INCLUDED_VALUE);
    }
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
ZTEST_CASE ( CastToEnumType_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EEnumerationMock ORIGINAL_VALUE = EEnumerationMock::E_Value2;
    const EEnumerationMock::EnumType EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    EEnumerationMock::EnumType eConvertedValue = ORIGINAL_VALUE;

    // [Verification]
    BOOST_CHECK(eConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
ZTEST_CASE ( ToInteger_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EEnumerationMock ORIGINAL_VALUE = EEnumerationMock::E_Value2;
    const enum_int_z EXPECTED_VALUE = EEnumerationMock::E_Value2;

	// [Execution]
    enum_int_z nConvertedValue = ORIGINAL_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(nConvertedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
ZTEST_CASE ( CastToString_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EEnumerationMock ORIGINAL_VALUE = EEnumerationMock::E_Value2;
    const string_z EXPECTED_VALUE = Z_L("Value2");

	// [Execution]
    string_z strConvertedValue(ORIGINAL_VALUE);

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the enumeration is correctly converted.
/// </summary>
ZTEST_CASE ( ToString_EnumerationIsProperlyConverted_Test )
{
    // [Preparation]
    const EEnumerationMock ORIGINAL_VALUE = EEnumerationMock::E_Value2;
    const string_z EXPECTED_VALUE = Z_L("Value2");

	// [Execution]
    string_z strConvertedValue = ORIGINAL_VALUE.ToString();

    // [Verification]
    BOOST_CHECK(strConvertedValue == EXPECTED_VALUE);
}

// End - Test Suite: EEnumerationMock
ZTEST_SUITE_END()
