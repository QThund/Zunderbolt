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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZCommon/DataTypes/SAnyTypeToStringConverter.h"

#include "ZCommon/DataTypes/Type.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "RTTITestClasses.h"

using z::Test::DerivedFromInterfaceA;
using z::Test::InterfaceMock1;


// This struct is used as example of "unknown type", not a basic type, not a string_z.
struct UnknownType
{
};
    
    
ZTEST_SUITE_BEGIN( SAnyTypeToStringConverter_TestSuite )
    
/// <summary>
/// Checks that the object is correctly converted to string when using bool.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "true";
    const bool OBJECT = true;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "255";
    const u8_z OBJECT = 255;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "65535";
    const u16_z OBJECT = 65535;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "123456789";
    const u32_z OBJECT = 123456789U;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using unsigned integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "12345678912345678912";
    const u64_z OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "-128";
    const i8_z OBJECT = -128;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "-32768";
    const i16_z OBJECT = -32768;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "-214748364";
    const i32_z OBJECT = -214748364;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using signed integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "-9223372036854775807";
    const i64_z OBJECT = -9223372036854775807;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using floating point numbers of 32 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "1234.54004";
    const f32_z OBJECT = 1234.54f;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using floating point numbers of 64 bits.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "12345678.90123";
    const f64_z OBJECT = 12345678.90123;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using strings.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "STRING";
    const string_z OBJECT = "STRING";

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using non-basic data types.
/// </summary>
ZTEST_CASE ( Convert1_ObjectIsCorrectlyConvertedToStringWhenUsingNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    bool bContainsExpectedText = strResult.Contains(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bContainsExpectedText);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to bool.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " true";
    bool OBJECT = true;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 255";
    u8_z OBJECT = 255;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 65535";
    u16_z OBJECT = 65535;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 123456789";
    u32_z OBJECT = 123456789U;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678912345678912";
    u64_z OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -128";
    i8_z OBJECT = -128;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -32768";
    i16_z OBJECT = -32768;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -214748364";
    i32_z OBJECT = -214748364;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -9223372036854775807";
    i64_z OBJECT = -9223372036854775807;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 32 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "1234.54004";
    f32_z OBJECT = 1234.54f;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 64 bits.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678.90123";
    f64_z OBJECT = 12345678.90123;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to strings.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " STRING";
    string_z OBJECT = "STRING";

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to non-basic data types.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Unknown type at 0x";
    UnknownType OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.Contains(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a basic data type.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    f64_z* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to string.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    string_z* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to non-basic data type.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    UnknownType* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to a basic data type.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678.90123";
    f64_z OBJECT = 12345678.90123;
    f64_z* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to strings.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " STRING";
    string_z OBJECT = "STRING";
    string_z* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to non-basic data types.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Unknown type at 0x";
    UnknownType OBJECT;
    UnknownType* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.Contains(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a basic data type.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    f64_z* pObject = null_z;
    f64_z** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with <Null>
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to string.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    string_z* pObject = null_z;
    string_z** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to non-basic data type.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    UnknownType* pObject = null_z;
    UnknownType** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to void.
/// </summary>
ZTEST_CASE ( Convert2_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToVoid_Test )
{
    // [Preparation]
    int VOID_CONTENT = 0;
    void* OBJECT = &VOID_CONTENT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to bool.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " true";
    const bool OBJECT = true;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 255";
    const u8_z OBJECT = 255;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 65535";
    const u16_z OBJECT = 65535;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 123456789";
    const u32_z OBJECT = 123456789U;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to unsigned integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678912345678912";
    const u64_z OBJECT = 12345678912345678912ULL;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 8 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -128";
    const i8_z OBJECT = -128;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 16 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -32768";
    const i16_z OBJECT = -32768;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 32 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -214748364";
    const i32_z OBJECT = -214748364;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to signed integer of 64 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " -9223372036854775807";
    const i64_z OBJECT = -9223372036854775807;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 32 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "1234.54004";
    const f32_z OBJECT = 1234.54f;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to floating point numbers of 64 bits.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678.90123";
    const f64_z OBJECT = 12345678.90123;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to strings.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " STRING";
    const string_z OBJECT = "STRING";

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to non-basic data types.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to a basic data type.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    const f64_z* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to string.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    const string_z* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a null pointer to non-basic data type.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = "<Null>";
    const UnknownType* pObject = null_z;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(pObject);
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to a basic data type.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " 12345678.90123";
    const f64_z OBJECT = 12345678.90123;
    const f64_z* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to strings.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " STRING";
    const string_z OBJECT = "STRING";
    const string_z* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to pointers to non-basic data types.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Unknown type at 0x";
    const UnknownType OBJECT = UnknownType();
    const UnknownType* pObject = &OBJECT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(&pObject);
    
    // [Verification]
    // Checks that the result starts with 0x, then it appears again for the second address, and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(string_z("0x"), 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                 strResult.Contains(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to a basic data type.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    const f64_z* pObject = null_z;
    const f64_z** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with <Null>
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to string.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    const string_z* pObject = null_z;
    const string_z** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using a pointer to null pointer to non-basic data type.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToNullPointerToNonBasicDataType_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = " <Null>";
    const UnknownType* pObject = null_z;
    const UnknownType** ppObject = &pObject;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(ppObject);
    
    // [Verification]
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                 strResult.IndexOf(EXPECTED_RESULT, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND;
    BOOST_CHECK(bIsCorrectlyConverted);
}

/// <summary>
/// Checks that the object is correctly converted to string when using pointers to void.
/// </summary>
ZTEST_CASE ( Convert3_ObjectIsCorrectlyConvertedToStringWhenUsingPointerToVoid_Test )
{
    // [Preparation]
    const int VOID_CONTENT = 0;
    const void* OBJECT = &VOID_CONTENT;

    // [Execution]
    string_z strResult = SAnyTypeToStringConverter::Convert(OBJECT);
    
    // [Verification]
    // Checks that the result starts with 0x and ends with the string representation of the object
    bool bIsCorrectlyConverted = strResult.IndexOf(string_z("0x"), EComparisonType::E_BinaryCaseSensitive) == 0;
    BOOST_CHECK(bIsCorrectlyConverted);
}

// End - Test Suite: SAnyTypeToStringConverter
ZTEST_SUITE_END()
