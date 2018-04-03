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
#include <boost/mpl/list.hpp>

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZCommon/DataTypes/StringUnicode.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZCommon/DataTypes/SVF32.h"

#include "CommonTestDefinitions.h"
#include "UnicodeNormalizationTestData.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "ZCommon/DataTypes/ENormalizationForm.h"
#include "ZMemory/AllocationOperators.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<i8_z, i16_z, i32_z, i64_z, u8_z, u16_z, u32_z, u64_z> TTemplateTypes;
typedef boost::mpl::list<i8_z, i16_z, i32_z, i64_z> TZTemplateSignedTypes;
typedef boost::mpl::list<u8_z, u16_z, u32_z, u64_z> TZTemplateUnsignedTypes;
typedef boost::mpl::list<u8_z, u16_z, u32_z, u64_z> TZTemplateUnsignedTypes;


ZTEST_SUITE_BEGIN( StringUnicode_TestSuite )

/// <summary>
/// This method checks if two byte arrays are exactly equal, byte to byte, same length
/// </summary>
/// <param name="pArrayA">[IN] A byte array.</param>
/// <param name="uSizeArrayA">[IN] The length of the byte array.</param>
/// <param name="pArrayB">[IN] A different byte array.</param>
/// <param name="uSizeArrayB">[IN] The length of the second byte array.</param>
/// <returns>
/// True if byte arrays are equal; False otherwise.
/// </returns>
bool CheckByteArraysAreEqual_UtilityMethod(const i8_z* pArrayA, const puint_z uSizeArrayA, const i8_z* pArrayB, const unsigned int uSizeArrayB)
{
    bool bAreEqual = true;

    if(pArrayA == pArrayB || uSizeArrayA == 0 || uSizeArrayB == 0 || pArrayA == null_z || pArrayB == null_z || uSizeArrayA != uSizeArrayB)
    {
        bAreEqual = false;
    }
    else
    {
        puint_z i = 0;

        while(i < uSizeArrayA && pArrayA[i] == pArrayB[i])
            ++i;

        bAreEqual = i == uSizeArrayA;
    }

    return bAreEqual;
}

/// <summary>
/// Checks that the default constructor creates an empty string.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultConstructorCreatesEmptyString_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT = StringUnicode::GetEmpty();

	// [Execution]
    StringUnicode strString;

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the copy of a string is equal to the original.
/// </summary>
ZTEST_CASE ( Constructor2_CopiedStringIsEqualToOriginal_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    StringUnicode strString(EXPECTED_RESULT);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor3_Iso88591StringIsCorrectlyConverted_Test )
{

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };

    //
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input is null-termination.
/// </summary>
ZTEST_CASE ( Constructor3_CreatesEmptyStringWhenInputIsNullTermination_Test )
{

    // [Preparation]
    const i8_z INPUT_STRING_BYTES[] = { 0 };
    const StringUnicode EXPECTED_RESULT = StringUnicode::GetEmpty();

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
ZTEST_CASE ( Constructor3_AssertionFailsWhenInputIsNull_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const i8_z* INPUT_STRING_BYTES = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode strString(INPUT_STRING_BYTES);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor4_Iso88591StringIsCorrectlyConverted_Test )
{

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);

    //
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input length equals zero.
/// </summary>
ZTEST_CASE ( Constructor4_CreatesEmptyStringWhenInputLengthEqualsZero_Test )
{

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const StringUnicode EXPECTED_RESULT = StringUnicode::GetEmpty();
    const int ZERO_LENGTH = 0;

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, ZERO_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the string is correctly built when the length is unknown and using a null-terminated input string.
/// </summary>
ZTEST_CASE ( Constructor4_StringIsCorrectlyBuiltWhenInputLengthIsUnknown_Test )
{

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const int UNKNOWN_LENGTH = StringUnicode::LENGTH_NULL_TERMINATED;

    //                                             ñ       B       á
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, UNKNOWN_LENGTH);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ASCII, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor5_AsciiStringIsCorrectlyConverted_Test )
{

    // [Preparation]
    const i8_z INPUT_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                            ' '      B       _       \0
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in ISO 8859-1, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor5_Iso88591StringIsCorrectlyConverted_Test )
{

    // [Preparation]                           'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[]        = { -15, 'B', -31, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_ISO88591;

    //
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-8, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor5_Utf8StringIsCorrectlyConverted_Test )
{

    // [Preparation]
    //                                         ©                       ?                                   ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Little Endian.
/// </summary>
ZTEST_CASE ( Constructor5_Utf16StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM LE                  ©              ?                       ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is correctly converted when the BOM indicates Big Endian.
/// </summary>
ZTEST_CASE ( Constructor5_Utf16StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16, is treated as if it was Big Endian when there is no BOM.
/// </summary>
ZTEST_CASE ( Constructor5_Utf16StringIsTreatedAsBigEndianWhenNoBOM_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16;

    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                            BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding EXPECTED_ENCODING    = ETextEncoding::E_UTF16;
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_BYTES, const i8_z*), EXPECTED_STRING_LENGTH, EXPECTED_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is correctly converted when BOM indicates Little Endian.
/// </summary>
ZTEST_CASE ( Constructor5_Utf32StringIsCorrectlyConvertedWhenBOMLittleEndian_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         BOM LE                        ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is correctly converted when BOM indicates Big Endian.
/// </summary>
ZTEST_CASE ( Constructor5_Utf32StringIsCorrectlyConvertedWhenBOMBigEndian_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         ©                    ?                             ?                             ?                            \0
    //                                         BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-32, is treated as if it was Big Endian when there is no BOM.
/// </summary>
ZTEST_CASE ( Constructor5_Utf32StringIsTreatedAsBigEndianWhenNoBOM_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                         ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32;

    // Note that the following byte sequence is read by a little-endian machine as DCBA, HGFE, etc.
    //                                            BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding EXPECTED_ENCODING    = ETextEncoding::E_UTF32;
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_BYTES, const i8_z*), EXPECTED_STRING_LENGTH, EXPECTED_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16 Big Endian, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor5_Utf16BEStringIsCorrectlyConverted_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16BE;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in UTF-16 Little Endian, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor5_Utf16LEStringIsCorrectlyConverted_Test )
{

    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
    //                                         ©              ?                       ?                       ?                      \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16LE;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-16 encoding.
/// </summary>
ZTEST_CASE ( Constructor5_BOMIsRemovedFromStringWhenUsingUtf16Encoding_Test )
{

    // [Preparation]
    static CharUnicode CHAR_BOM_LE = 0xFFFE;
    //                                        BOM     ©       ?       ?       ?      \0
    const u16_z INPUT_STRING_CODE_UNITS[] = { 0xFFFE, 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != CHAR_BOM_LE);
}

/// <summary>
/// Checks that the BOM character is removed from the resultant string when using UTF-32 encoding.
/// </summary>
ZTEST_CASE ( Constructor5_BOMIsRemovedFromStringWhenUsingUtf32Encoding_Test )
{
    // [Preparation]
    static CharUnicode CHAR_BOM_LE = 0xFFFE;
    //                                        BOM         ©           ?           ?           ?          \0
    const u32_z INPUT_STRING_CODE_UNITS[] = { 0x0000FEFF, 0x000000A9, 0x000016A1, 0x00000634, 0x00000416, 0x00000000 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_CODE_UNITS);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32;

    //                                           ©       ?       ?       ?      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(strString.GetLength(), EXPECTED_RESULT.GetLength());
    BOOST_CHECK(strString[0] != CHAR_BOM_LE);
}

/// <summary>
/// Checks that ill-formed sequences are repaired, replacing the wrong characters by U+FFFD REPLACEMENT CHARACTER, when passing Utf8 string.
/// </summary>
ZTEST_CASE ( Constructor5_IllFormedSequencesAreRepairedUsingReplacementCharacterWhenUsingUtf8_Test )
{

    // [Preparation]
    //                                         A           ILL-FORMED  ñ                       B          \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0x41, (char)0xC2, (char)0xC3, (char)0xB1, (char)0x42, 0 };
    const unsigned int INPUT_STRING_LENGTH = sizeof(INPUT_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF8;

    //                                           A       REPLAC. ñ       B      \0
    const u16_z EXPECTED_STRING_CODE_UNITS[] = { 0x0041, 0xFFFD, 0x00F1, 0x0042, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, INPUT_STRING_LENGTH, INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the values of the optional parameters are ISO 8859-1 encoding and Null-terminated length, when no arguments are passed.
/// </summary>
ZTEST_CASE ( Constructor5_OptionalParametersDefaultToNullTerminatedIso88591_Test )
{

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };

    //                                             ñ       B       á
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it creates an empty string when the input length equals zero.
/// </summary>
ZTEST_CASE ( Constructor5_CreatesEmptyStringWhenInputLengthEqualsZero_Test )
{
    // [Preparation]                    'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const StringUnicode EXPECTED_RESULT = StringUnicode::GetEmpty();
    const int ZERO_LENGTH = 0;
    const ETextEncoding ENCODING = ETextEncoding::E_ISO88591;

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, ZERO_LENGTH, ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when an incorrect combination of parameter values is passed.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenUsingIncorrectParameterValueCombination_Test )
{

    // [Preparation]
    const i8_z INPUT_STRING_BYTES[] = { 'a', 'b', 'c', 0 };
    const int INVALID_LENGTH = StringUnicode::LENGTH_NULL_TERMINATED;
    const ETextEncoding INVALID_ENCODING = ETextEncoding::E_UTF8;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode strString(INPUT_STRING_BYTES, INVALID_LENGTH, INVALID_ENCODING);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the string is correctly built when the length is unknown and using a null-terminated input string.
/// </summary>
ZTEST_CASE ( Constructor5_StringIsCorrectlyBuiltWhenInputLengthIsUnknown_Test )
{

    // [Preparation]                    'ñ', 'B', 'á'
    const i8_z INPUT_STRING_BYTES[] = { -15, 'B', -31, 0 };
    const int UNKNOWN_LENGTH = StringUnicode::LENGTH_NULL_TERMINATED;
    const ETextEncoding ENCODING = ETextEncoding::E_ISO88591;

    //                                             ñ       B       á
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F1, 0x0042, 0x00E1 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    StringUnicode strString(INPUT_STRING_BYTES, UNKNOWN_LENGTH, ENCODING);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the resultant string contains the input character.
/// </summary>
ZTEST_CASE ( Constructor6_ResultContainsInputCharacter_Test )
{

    // [Preparation]
    const CharUnicode INPUT_CHARACTER(0x1234);
    const u16_z EXPECTED_STRING_BYTES[] = { scast_z(INPUT_CHARACTER.GetCodePoint(), u16_z) };
    const StringUnicode EXPECTED_RESULT = StringUnicode(rcast_z(EXPECTED_STRING_BYTES, const i8_z*), sizeof(EXPECTED_STRING_BYTES), string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(INPUT_CHARACTER);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that input string, encoded in either UTF16 or UTF32 depending on the OS and the compiler, is correctly converted.
/// </summary>
ZTEST_CASE ( Constructor7_CommonSequenceIsCorrectlyConverted_Test )
{

    // [Preparation]
    const wchar_t INPUT_STRING_BYTES[] = { 'A', 'B', 'C', 0 };
    const unsigned int EXPECTED_LENGTH = 3;

    //
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x0041, 0x0042, 0x0043 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    unsigned int uLength = strString.GetLength();
    BOOST_CHECK(strString == EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it creates an empty string when the input is null-termination.
/// </summary>
ZTEST_CASE ( Constructor7_CreatesEmptyStringWhenInputIsNullTermination_Test )
{

    // [Preparation]
    const wchar_t INPUT_STRING_BYTES[] = { 0 };
    const StringUnicode EXPECTED_RESULT = StringUnicode::GetEmpty();

	// [Execution]
    StringUnicode strString(INPUT_STRING_BYTES);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input is null.
/// </summary>
ZTEST_CASE ( Constructor7_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const wchar_t* INPUT_STRING_BYTES = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode strString(INPUT_STRING_BYTES);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

/// <summary>
/// Checks that the assigned string is equal to the copied string.
/// </summary>
ZTEST_CASE ( OperatorAssignment_CopiedStringIsEqualToOriginal_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("ABC");

	// [Execution]
    StringUnicode strString;
    strString = EXPECTED_RESULT;

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are exactly the same.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("ABCDE");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are not the same.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenStringsAreNotEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equivalent but not exactly the same.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenStringsAreEquivalentButNotTheSame_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 == STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are exactly the same.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("ABCDE");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are not the same.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenStringsAreNotEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenStringsAreEquivalentButNotTheSame_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 != STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 < STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenInputStringIsLower_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 < STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equal.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 < STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThan_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsGreater_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 <= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsFalseWhenInputStringIsLower_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equal.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorLowerThanOrEquals_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsGreater_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 <= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenInputStringIsLower_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 > STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 > STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when strings are equal.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsFalseWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING2 > STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThan_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsLower_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 > STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when input string is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenInputStringIsLower_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 >= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when input string is greater than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsFalseWhenInputStringIsGreater_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2("FGHIJ");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = STRING1 >= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equal.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenStringsAreEqual_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABCDE");
    const StringUnicode STRING2(STRING1);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING2 >= STRING1;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when strings are equivalent but not exactly the same, and input is lower than resident string.
/// </summary>
ZTEST_CASE ( OperatorGreaterThanOrEquals_ReturnsTrueWhenStringsAreEquivalentButNotTheSameAndInputIsLower_Test )
{
    // [Preparation]
    // Both characters are represented graphically the same way but have different code points. If they were decomposed canonically,
    // they would be exactly the same: U+0041 LATIN CAPITAL LETTER A + U+030A COMBINING RING ABOVE
    u16_z CHAR_STRING1[] = { 0x212B, 0 }; // Å -> U+212B
    u16_z CHAR_STRING2[] = { 0x00C5, 0 }; // Å -> U+00C5
    const StringUnicode STRING1(rcast_z(CHAR_STRING1, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const StringUnicode STRING2(rcast_z(CHAR_STRING2, const i8_z*), 2, string_z::GetLocalEncodingUTF16());
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = STRING1 >= STRING2;

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates both strings, the left one before the right one.
/// </summary>
ZTEST_CASE ( OperatorAddition1_ConcatenatesBothStrings_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABC");
    const StringUnicode STRING2("DEF");
    const StringUnicode EXPECTED_RESULT("ABCDEF");

	// [Execution]
    StringUnicode strResult = STRING1 + STRING2;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates both strings, the left one before the right one.
/// </summary>
ZTEST_CASE ( OperatorAddition2_ConcatenatesBothStrings_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABC");
    const char* STRING2 = "DEF";
    const StringUnicode EXPECTED_RESULT("ABCDEF");

	// [Execution]
    StringUnicode strResult = STRING1 + STRING2;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition3_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u8_z VALUE = 234;
    const StringUnicode EXPECTED_RESULT("ABC234");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition4_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i8_z VALUE = -123;
    const StringUnicode EXPECTED_RESULT("ABC-123");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition5_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u16_z VALUE = 23456;
    const StringUnicode EXPECTED_RESULT("ABC23456");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition6_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i16_z VALUE = -23456;
    const StringUnicode EXPECTED_RESULT("ABC-23456");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition7_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u32_z VALUE = 23456890;
    const StringUnicode EXPECTED_RESULT("ABC23456890");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition8_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i32_z VALUE = -2345689;
    const StringUnicode EXPECTED_RESULT("ABC-2345689");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition9_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u64_z VALUE = 123456890123;
    const StringUnicode EXPECTED_RESULT("ABC123456890123");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition10_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i64_z VALUE = -123456890123;
    const StringUnicode EXPECTED_RESULT("ABC-123456890123");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition11_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const f32_z VALUE = -123.456f;
    const StringUnicode EXPECTED_RESULT("ABC-123.456001");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition12_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const f64_z VALUE = -123456.789;
    const StringUnicode EXPECTED_RESULT("ABC-123456.789");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition13_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const bool VALUE = true;
    const StringUnicode EXPECTED_RESULT("ABCtrue");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( OperatorAddition14_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    vf32_z VALUE;
    SVF32::Pack(1.0f, 2.0f, 3.0f, 4.0f, VALUE);
    const StringUnicode EXPECTED_RESULT("ABCVF(1, 2, 3, 4)");

	// [Execution]
    StringUnicode strResult = STRING + VALUE;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_ReturnsExpectedCharacterWhenUsingCommonIndex_Test )
{

    // [Preparation]
    const StringUnicode STRING1("ABC");
    const unsigned int COMMON_INDEX = 1;
    const CharUnicode EXPECTED_RESULT(0x0042); // B

	// [Execution]
    CharUnicode charResult = STRING1[COMMON_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    CharUnicode EXPECTED_RESULT1('E');
    CharUnicode EXPECTED_RESULT2(0x00011234);
    const unsigned int POSITION1 = 5;
    const unsigned int POSITION2 = 9;

	// [Execution]
    CharUnicode character1 = SOURCE_STRING[POSITION1];
    CharUnicode character2 = SOURCE_STRING[POSITION2];

    // [Verification]
    BOOST_CHECK(character1 == EXPECTED_RESULT1);
    BOOST_CHECK(character2 == EXPECTED_RESULT2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_ReturnsNonCharacterWhenStringIsEmpty_Test )
{

    // [Preparation]
    const StringUnicode EMPTY_STRING("");
    const unsigned int COMMON_INDEX = 1;
    const CharUnicode EXPECTED_RESULT(0xFFFF); // Not a character

	// [Execution]
    CharUnicode charResult = EMPTY_STRING[COMMON_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected character when using a common index.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_ReturnsNonCharacterWhenIndexIsOutOfBounds_Test )
{

    // [Preparation]
    const StringUnicode STRING1("ABC");
    const unsigned int OUTOFBOUNDS_INDEX = 3;
    const CharUnicode EXPECTED_RESULT(0xFFFF); // Not a character

	// [Execution]
    CharUnicode charResult = STRING1[OUTOFBOUNDS_INDEX];

    // [Verification]
    BOOST_CHECK(charResult == EXPECTED_RESULT);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the index is out of bounds.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenIndexIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABC");
    const unsigned int OUTOFBOUNDS_INDEX = 3;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING1[OUTOFBOUNDS_INDEX];
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_AssertionFailsWhenStringIsEmpty_Test )
{

    // [Preparation]
    const StringUnicode EMPTY_STRING("");
    const unsigned int COMMON_INDEX = 1;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        EMPTY_STRING[COMMON_INDEX];
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that it returns the expected result when using common input position.
/// </summary>
ZTEST_CASE ( Substring1_ReturnsExpectedResultWhenUsingCommonInputPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("EFGHIJKLMN");
    const unsigned int START_POSITION = 4;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
ZTEST_CASE ( Substring1_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const StringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 1;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
ZTEST_CASE ( Substring1_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = SOURCE_STRING.GetLength();

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( Substring1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    
    StringUnicode EXPECTED_RESULT("EFGH");
    EXPECTED_RESULT.Append(CharUnicode(0x00011234));
    const unsigned int START_POSITION = 5;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("EFGH");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION + 3;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( Substring2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKLMN");
    
    StringUnicode EXPECTED_RESULT("EFGH");
    EXPECTED_RESULT.Append(CharUnicode(0x00011234));
    const unsigned int START_POSITION = 5;
    const unsigned int LAST_POSITION = START_POSITION + 4;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position is greater than the last position.
/// </summary>
ZTEST_CASE ( Substring2_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
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
/// Checks that an empty string is returned when the start position is greater than the last position.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION - 2;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that an 1-length string is returned when start position equals last position.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsOneLenthStringWhenStartPositionEqualsLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("E");
    const unsigned int START_POSITION = 4;
    const unsigned int LAST_POSITION = START_POSITION;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const StringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = 1;
    const unsigned int LAST_POSITION = 3;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the rest of the string when the last position is out of the string's bounds.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("FGHIJKLMN");
    const unsigned int START_POSITION = 5;
    const unsigned int LAST_POSITION = SOURCE_STRING.GetLength() + 10;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
ZTEST_CASE ( Substring2_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    const unsigned int START_POSITION = SOURCE_STRING.GetLength();
    const unsigned int LAST_POSITION = START_POSITION + 2;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input position.
/// </summary>
ZTEST_CASE ( Substring3_ReturnsExpectedResultWhenUsingCommonInputPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("EFGHIJKLMN");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
ZTEST_CASE ( Substring3_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const StringUnicode EXPECTED_RESULT("");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(1);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the entire string is returned when the start position iterator points to the end position (backward).
/// </summary>
ZTEST_CASE ( Substring3_ReturnsFullStringWhenStartPositionIteratorPointsToBackwardEndPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT = SOURCE_STRING;
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position iterator points to the end position (forward).
/// </summary>
ZTEST_CASE ( Substring3_ReturnsEmptyStringWhenStartPositionIteratorPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using common input positions.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsExpectedResultWhenUsingCommonInputPositions_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("EFGH");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(7);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the start position is greater than the last position.
/// </summary>
ZTEST_CASE ( Substring4_AssertionFailsWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(2);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
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
/// Checks that an empty string is returned when the start position is greater than the last position.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsEmptyStringWhenStartPositionIsGreaterThanLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(2);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

#endif

/// <summary>
/// Checks that an 1-length string is returned when start position equals last position.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsOneLenthStringWhenStartPositionEqualsLastPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("E");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(4);
    const StringUnicode::ConstCharIterator LAST_POSITION = START_POSITION;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the source string is empty.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsEmptyStringWhenSourceStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const StringUnicode EXPECTED_RESULT("");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(1);
    const StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(3);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the rest of the string when the last position is out of the string's bounds.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsTheRestOfTheStringWhenLastPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("FGHIJKLMN");
    const StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(5);
    StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position is out of the string's bounds.
/// </summary>
ZTEST_CASE ( Substring4_ReturnsEmptyStringWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());
    StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the start position iterator and the last position iterator point to the end position (backward).
/// </summary>
ZTEST_CASE ( Substring4_ReturnsEmptyStringWhenBothStartPositionAndLastPositionPointToBackwardEndPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator();
    --LAST_POSITION;

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);
    
    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the start position points to first position when it was pointing to the end position (backward).
/// </summary>
ZTEST_CASE ( Substring4_StartPositionPointsToFirstPositionWhenItWasPointingToBackwardEndPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT("ABCD");
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    const StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(3);

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the entire string is returned when the start position points to the end position (backward) and the last position points to the end position (forward).
/// </summary>
ZTEST_CASE ( Substring4_ReturnsFullStringWhenStartPositionPointsToBackwardEndPositionAndLastPositionPointsToForwardEndPosition_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    const StringUnicode EXPECTED_RESULT = SOURCE_STRING;
    StringUnicode::ConstCharIterator START_POSITION = SOURCE_STRING.GetConstCharIterator();
    --START_POSITION;
    StringUnicode::ConstCharIterator LAST_POSITION = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());

	// [Execution]
    StringUnicode strString = SOURCE_STRING.Substring(START_POSITION, LAST_POSITION);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
ZTEST_CASE ( GetConstCharIterator1_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKLMN");
    StringUnicode::ConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the obtained iterator points to the end position when the string is empty.
/// </summary>
ZTEST_CASE ( GetConstCharIterator1_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const bool IS_END = true;

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that the iterator points to the given position.
/// </summary>
ZTEST_CASE ( GetConstCharIterator2_IteratorPointsToTheGivenPosition_Test )
{

    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const CharUnicode EXPECTED_CHARACTER = 'F';

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(5);
    
    // [Verification]
    CharUnicode charPointedToByIterator = iterator.GetChar();
    BOOST_CHECK(charPointedToByIterator == EXPECTED_CHARACTER);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when input initial position is out of bounds.
/// </summary>
ZTEST_CASE ( GetConstCharIterator2_IteratorPointsToEndPositionWhenInitialPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABCDEFGHIJKMN");
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(SOURCE_STRING.GetLength());
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the iterator points to end position (forward) when the string is empty.
/// </summary>
ZTEST_CASE ( GetConstCharIterator2_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING = StringUnicode::GetEmpty();
    const bool POINTS_TO_END_POSITION = true;

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator(0);
    
    // [Verification]
    bool bPointsToEndPosition = iterator.IsEnd();
    BOOST_CHECK_EQUAL(bPointsToEndPosition, POINTS_TO_END_POSITION);
}

/// <summary>
/// Checks that the obtained iterator points to the first position when the string is not empty.
/// </summary>
ZTEST_CASE ( GetCharIterator_IteratorPointsToFirstPositionWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    StringUnicode strSourceString("ABCDEFGHIJKLMN");
    StringUnicode::CharIterator EXPECTED_ITERATOR(strSourceString);
    EXPECTED_ITERATOR.MoveFirst();

	// [Execution]
    StringUnicode::CharIterator iterator = strSourceString.GetCharIterator();

    // [Verification]
    BOOST_CHECK(iterator == EXPECTED_ITERATOR);
}

/// <summary>
/// Checks that the obtained iterator points to the end position when the string is empty.
/// </summary>
ZTEST_CASE ( GetCharIterator_IteratorPointsToEndPositionWhenStringIsEmpty_Test )
{
    // [Preparation]
    StringUnicode strEmptyString("");
    const bool IS_END = true;

	// [Execution]
    StringUnicode::CharIterator iterator = strEmptyString.GetCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that it converts the string to ASCII correctly.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToAsciiCorrectly_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that characters that cannot be translated to ASCII are replaced by substitution characters (26).
/// </summary>
ZTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByAsciiSubstitutionCharacters_Test )
{
    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_z EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_AsciiNullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that it converts the string to ISO 8859-1 correctly.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToISO88591Correctly_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                          ' '      B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that characters that cannot be translated to ISO 8859-1 are replaced by substitution characters (26).
/// </summary>
ZTEST_CASE ( ToBytes_NonConvertibleCharactersAreReplacedByISO88591SubstitutionCharacters_Test )
{
    // [Preparation]
    const char SUBSTITUTION_CHARACTER = 26;
    const i8_z EXPECTED_STRING_BYTES[]     = { SUBSTITUTION_CHARACTER, 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                           ?       B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0409, 0x0042, 0x005F, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_ISO88591NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]     = { ' ', 'B', '_', 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-8 correctly.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF8Correctly_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_UTF8NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xC2, (char)0xA9, (char)0xE1, (char)0x9A, (char)0xA1, (char)0xD8, (char)0xB4, (char)0xD0, (char)0x96, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF8;

    //                                           ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 correctly and adds a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF16CorrectlyAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                            BOM BE                  ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFE, (char)0xFF, 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                            BOM LE                  ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF16;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_UTF16NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 correctly and adds a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF32CorrectlyAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                         BOM BE                        ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, 0, (char)0xFE, (char)0xFF, 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                         BOM LE                        ©                    ?                             ?                             ?                            \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF32;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_UTF32NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacter_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xFF, (char)0xFE, 0, 0, (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF16LECorrectlyNotAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                              ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                            ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF16LE;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16LEEnconding_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16LE;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-16 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF16BECorrectlyNotAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                              ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, (char)0xA1, (char)0x16, (char)0x34, (char)0x06, (char)0x16, (char)0x04, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                            ©              ?                       ?                       ?                      \0
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF16BE;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF16BEEnconding_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, (char)0xA9, (char)0x16, (char)0xA1, (char)0x06, (char)0x34, (char)0x04, (char)0x16, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF16BE;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 Little Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF32LECorrectlyNotAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                           ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                            ©                    ?                             ?                             ?                            \0
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF32LE;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32LEEncoding_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32LE;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it converts the string to UTF-32 Big Endian correctly and DOES NOT add a BOM character at the beginning.
/// </summary>
ZTEST_CASE ( ToBytes_ConvertsToUTF32BECorrectlyNotAddingBOM_Test )
{
    // [Preparation]
    // Note that the following byte sequence is read by a little-endian machine as BA, DC, FE, HG, etc.
#if Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
    //                                           ©                    ?                             ?                             ?                            \0
    const i8_z INPUT_STRING_BYTES[]        = { (char)0xA9, 0, 0, 0, (char)0xA1, (char)0x16, 0, 0, (char)0x34, (char)0x06, 0, 0, (char)0x16, (char)0x04, 0, 0, 0, 0, 0, 0 };
#elif Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
    //                                            ©                    ?                             ?                             ?                            \0
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
#endif
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING       = ETextEncoding::E_UTF32BE;

    //                                         ©       ?       ?       ?      \0
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416, 0x0000 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
}

/// <summary>
/// Checks that a null terminator is added to the output string when the source string does not have one.
/// </summary>
ZTEST_CASE ( ToBytes_NullTerminatorAddedWhenSourceStringDoesNotTerminatesWithNullCharacterAndUsingUTF32BEEncoding_Test )
{
    // [Preparation]
    const i8_z EXPECTED_STRING_BYTES[]        = { 0, 0, 0, (char)0xA9, 0, 0, (char)0x16, (char)0xA1, 0, 0, (char)0x06, (char)0x34, 0, 0, (char)0x04, (char)0x16, 0, 0, 0, 0 };
    const unsigned int EXPECTED_STRING_LENGTH = sizeof(EXPECTED_STRING_BYTES);
    const ETextEncoding INPUT_ENCODING    = ETextEncoding::E_UTF32BE;

    //                                         ©       ?       ?       ?
    const u16_z SOURCE_STRING_CODE_UNITS[] = { 0x00A9, 0x16A1, 0x0634, 0x0416 };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK(CheckByteArraysAreEqual_UtilityMethod(arByteArray.Get(), arByteArray.GetCount(), EXPECTED_STRING_BYTES, EXPECTED_STRING_LENGTH));
    BOOST_CHECK_NE(arByteArray.GetCount(), sizeof(SOURCE_STRING_CODE_UNITS));
}

/// <summary>
/// Checks that it returns a null pointer when the string is empty.
/// </summary>
ZTEST_CASE ( ToBytes_ReturnsNullPointerWhenStringIsEmpty_Test )
{
    // [Preparation]
    const i8_z* EXPECTED_STRING_BYTES = null_z;
    const unsigned int EXPECTED_STRING_LENGTH = 0;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    const StringUnicode EMPTY_STRING = StringUnicode::GetEmpty();

	// [Execution]
    ArrayResult<char> arByteArray = EMPTY_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(arByteArray.GetCount(), EXPECTED_STRING_LENGTH);
    BOOST_CHECK(arByteArray.Get() == EXPECTED_STRING_BYTES);
}

/// <summary>
/// Checks that the null character is counted when calculating the output length.
/// </summary>
ZTEST_CASE ( ToBytes_FinalNullCharacterIsCountedForOutputLength_Test )
{
    // [Preparation]
    const unsigned int EXPECTED_STRING_LENGTH = 4;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;

    //                                           ' '       B       _
    const u16_z SOURCE_STRING_CODE_UNITS[]   = { 0x0020, 0x0042, 0x005F };
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();
    StringUnicode SOURCE_STRING(rcast_z(SOURCE_STRING_CODE_UNITS, const char*), sizeof(SOURCE_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    ArrayResult<char> arByteArray = SOURCE_STRING.ToBytes(INPUT_ENCODING);

    // [Verification]
    BOOST_CHECK_EQUAL(arByteArray.GetCount(), EXPECTED_STRING_LENGTH);
}

#if Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST == Z_TEST_CONFIG_STRINGUNICODE_NORMALIZE_TEST_ENABLED

/// <summary>
/// Checks that the result of the normalization process is what expected. This test uses the NormalizationTest.txt file,
/// provided by the Unicode Standard, which has been modified to neither include comments nor CJK characteres. See the file UnicodeNormalizationTestData.h.
/// </summary>
ZTEST_CASE ( Normalize_StringIsNormalizedAsExpected_Test )
{
    using ENormalizationForm;
    using namespace Test::Normalization;

    // [Preparation]
    QNormalizationTestFileParser parser;
    parser.ParseFile("NormalizationTest.txt");
    const std::vector<QNormalizationTest>& arSpecificCases        = parser.GetSpecificCases();
    const std::vector<QNormalizationTest>& arCanonicalOrder       = parser.GetCanonicalOrder();
    const std::vector<QNormalizationTest>& arCharacterByCharacter = parser.GetCharacterByCharacter();
    const std::vector<QNormalizationTest>& arPublicReviewIssues   = parser.GetPublicReviewIssues();

    const ETextEncoding ENCODING = ETextEncoding::E_UTF32LE;
    const unsigned int CODEPOINT_SIZE = 4;

    for(unsigned int i = 0; i < arSpecificCases.size(); ++i)
    {
        StringUnicode strOriginal((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arSpecificCases[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        StringUnicode strExpectedNFC((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arSpecificCases[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        StringUnicode strExpectedNFD((const char*)arSpecificCases[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arSpecificCases[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        StringUnicode strResultNFC(strOriginal);
        StringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(ENormalizationForm::E_C);
        strResultNFD.Normalize(ENormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arCanonicalOrder.size(); ++i)
    {
        StringUnicode strOriginal((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arCanonicalOrder[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        StringUnicode strExpectedNFC((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        StringUnicode strExpectedNFD((const char*)arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arCanonicalOrder[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        StringUnicode strResultNFC(strOriginal);
        StringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(ENormalizationForm::E_C);
        strResultNFD.Normalize(ENormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arCharacterByCharacter.size(); ++i)
    {
        StringUnicode strOriginal((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        StringUnicode strExpectedNFC((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        StringUnicode strExpectedNFD((const char*)arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arCharacterByCharacter[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        StringUnicode strResultNFC(strOriginal);
        StringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(ENormalizationForm::E_C);
        strResultNFD.Normalize(ENormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    for(unsigned int i = 0; i < arPublicReviewIssues.size(); ++i)
    {
        StringUnicode strOriginal((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].CodePoints,
                                   arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::ORIGINAL_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                   ENCODING);
        StringUnicode strExpectedNFC((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].CodePoints,
                                      arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFC_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);
        StringUnicode strExpectedNFD((const char*)arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].CodePoints,
                                      arPublicReviewIssues[i].CharacterSequences[QNormalizationTest::NFD_SEQUENCE].ArraySize * CODEPOINT_SIZE,
                                      ENCODING);

        // [Execution]
        StringUnicode strResultNFC(strOriginal);
        StringUnicode strResultNFD(strOriginal);
        strResultNFC.Normalize(ENormalizationForm::E_C);
        strResultNFD.Normalize(ENormalizationForm::E_D);

        // [Verification]
        // Only prints when there is a failed case in order not to saturate the result file
        if(strResultNFC != strExpectedNFC)
        {
            BOOST_CHECK(strResultNFC == strExpectedNFC);
        }
        if(strResultNFD != strExpectedNFD)
        {
            BOOST_CHECK(strResultNFD == strExpectedNFD);
        }
    }

    BOOST_TEST_MESSAGE("Normalization test finished");
}

#endif

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ACC");
    const StringUnicode INPUT_STRING("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const u16_z RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsLowerByLetterCaseAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsGreaterByLetterCaseAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("abcde");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(CharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const StringUnicode INPUT_STRING(CharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode INPUT_STRING("ACC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const u16_z INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using binary case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingBinaryInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ACC");
    const StringUnicode INPUT_STRING("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const u16_z RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is upper case and input is lower case, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByLetterCaseAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("Abcde");
    const StringUnicode INPUT_STRING("abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the only difference is the casing, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsLowerByLetterCaseAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("abcde");
    const StringUnicode INPUT_STRING("Abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it does not return "equal" when the only difference is in the weight of punctuation, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsNotEqualWhenDifferenceIsPunctuationWeightUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(CharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const StringUnicode INPUT_STRING(CharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode INPUT_STRING("ACC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const u16_z INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using binary case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingBinarySensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ACC");
    const StringUnicode INPUT_STRING("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const u16_z RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsLowerByLetterCaseAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is the casing, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsGreaterByLetterCaseAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("abcde");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(CharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const StringUnicode INPUT_STRING(CharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode INPUT_STRING("ACC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const u16_z INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using canonical case insensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingCanonicalInsensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to a base character, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByBaseCharacterAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ACC");
    const StringUnicode INPUT_STRING("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is lower than resident string due to an accent, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByAccentsAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const u16_z RESIDENT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the input string is empty, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsEmptyAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "greater" when the resident string is upper case and input is lower case, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsGreaterWhenInputIsLowerByLetterCaseAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("Abcde");
    const StringUnicode INPUT_STRING("abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the only difference is the casing, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByLetterCaseAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("abcde");
    const StringUnicode INPUT_STRING("Abcde");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the input string equals the resident string, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenInputIsTheSameAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "equal" when the only difference is in the weight of punctuation, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsEqualWhenDifferenceIsPunctuationWeightUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(CharUnicode(0x00C5)); // [.06D9.002B.0008.00C5] LATIN CAPITAL LETTER A WITH RING ABOVE; CANONSEQ
    const StringUnicode INPUT_STRING(CharUnicode(0x212B));    // [.06D9.002B.0008.212B] ANGSTROM SIGN; CANONSEQ
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to a base character, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByBaseCharacterAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode INPUT_STRING("ACC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the input string is lower than resident string due to an accent, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenInputIsGreaterByAccentsAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABCDE");
    const u16_z INPUT_CHARS[] = {'A', 'B', 'C', 'D', 0xC9}; // ABCDÉ
    const StringUnicode INPUT_STRING((const char*)INPUT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "lower" when the resident string is empty, using canonical case sensitive comparison type.
/// </summary>
ZTEST_CASE ( CompareTo_ReturnsLowerWhenResidentIsEmptyAndUsingCanonicalSensitiveComparison_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode INPUT_STRING("ABCDE");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than letters.
/// </summary>
ZTEST_CASE ( CompareTo_PunctuationMarksAreLowerThanLetters_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(",");
    const StringUnicode INPUT_STRING("a");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that whitespace characters are lower than letters.
/// </summary>
ZTEST_CASE ( CompareTo_WhitespacesAreLowerThanLetters_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(" ");
    const StringUnicode INPUT_STRING("a");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that number characters are lower than letters.
/// </summary>
ZTEST_CASE ( CompareTo_NumbersAreLowerThanLetters_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("5");
    const StringUnicode INPUT_STRING("a");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than number characters.
/// </summary>
ZTEST_CASE ( CompareTo_PunctuationMarksAreLowerThanNumbers_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(",");
    const StringUnicode INPUT_STRING("5");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that punctuation mark characters are lower than number characters.
/// </summary>
ZTEST_CASE ( CompareTo_WhitespacesAreLowerThanNumbers_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(" ");
    const StringUnicode INPUT_STRING("6");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that number characters are lower than letters.
/// </summary>
ZTEST_CASE ( CompareTo_WhitespacesAreLowerThanPunctuationMarks_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING(" ");
    const StringUnicode INPUT_STRING(",");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.CompareTo(INPUT_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of any string does not affect the result, since they are normalized when needed internally.
/// </summary>
ZTEST_CASE ( CompareTo_NormalizationDoesNotAffectTheResultWhenUsingCanonicalComparisons_Test )
{
    // [Preparation]
    //                                 A       _        ?        ¨       ñ
    u16_z NONNORMALIZED_SEQUENCE[] = { 0x0041, 0x0331, 0x0341, 0x00A8, 0x00F1 }; // Á_¨ñ
    const StringUnicode NONNORMALIZED_STRING((char*)NONNORMALIZED_SEQUENCE, sizeof(NONNORMALIZED_SEQUENCE), string_z::GetLocalEncodingUTF16());
    StringUnicode NORMALIZED_STRING(NONNORMALIZED_STRING);
    NORMALIZED_STRING.Normalize(ENormalizationForm::E_D);
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResultNormalized = NORMALIZED_STRING.CompareTo(NORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNonNormalized = NORMALIZED_STRING.CompareTo(NONNORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNormalized2 = NORMALIZED_STRING.CompareTo(NORMALIZED_STRING, COMPARISON_TYPE);
    int nResultNonNormalized2 = NORMALIZED_STRING.CompareTo(NONNORMALIZED_STRING, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultNormalized, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNonNormalized);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNonNormalized2);
    BOOST_CHECK_EQUAL(nResultNormalized, nResultNormalized2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( IndexOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
ZTEST_CASE ( IndexOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
ZTEST_CASE ( IndexOf1_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("A");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
ZTEST_CASE ( IndexOf1_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
ZTEST_CASE ( IndexOf1_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
ZTEST_CASE ( IndexOf1_MatchesExactlyAtZeroIndexAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( IndexOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( IndexOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.IndexOf(PATTERN1, EComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.IndexOf(PATTERN2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( IndexOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
ZTEST_CASE ( IndexOf2_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
ZTEST_CASE ( IndexOf2_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("A");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
ZTEST_CASE ( IndexOf2_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of strings affects the result.
/// </summary>
ZTEST_CASE ( IndexOf2_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, START_INDEX, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.IndexOf(NONNORMALIZED_PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
ZTEST_CASE ( IndexOf2_MatchesExactlyAtZeroIndexAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;
    const unsigned int START_INDEX = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( IndexOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 6;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
ZTEST_CASE ( IndexOf2_MatchesPreviousToStartIndexAreNotFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 7;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches are found at the start index.
/// </summary>
ZTEST_CASE ( IndexOf2_MatchesExactlyAtStartIndexAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
ZTEST_CASE ( IndexOf2_PatternIsNotFoundWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 50;

	// [Execution]
    int nResult = RESIDENT_STRING.IndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( IndexOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.IndexOf(PATTERN1, EXPECTED_POSITION1, EComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.IndexOf(PATTERN2, EXPECTED_POSITION2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( LastIndexOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
ZTEST_CASE ( LastIndexOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
ZTEST_CASE ( LastIndexOf1_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("A");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from right to left.
/// </summary>
ZTEST_CASE ( LastIndexOf1_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 3;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
ZTEST_CASE ( LastIndexOf1_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
ZTEST_CASE ( LastIndexOf1_MatchesExactlyAtZeroIndexAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( LastIndexOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( LastIndexOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.LastIndexOf(PATTERN1, EComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.LastIndexOf(PATTERN2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns -1 when the result is not found.
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("A");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = -1;
    const unsigned int START_INDEX = 1;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence, from right to left.
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 3;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the first occurrence after the index, from right to left.
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsTheFirstOccurrenceAfterIndex_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 2;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 13;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const int EXPECTED_RESULT = 1;
    const unsigned int START_INDEX = 13;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of strings affects the result.
/// </summary>
ZTEST_CASE ( LastIndexOf2_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const unsigned int START_INDEX = 4;

	// [Execution]
    int nResultNormalized    = NORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, START_INDEX, COMPARISON_TYPE);
    int nResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.LastIndexOf(NONNORMALIZED_PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(nResultNormalized, nResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
ZTEST_CASE ( LastIndexOf2_MatchesExactlyAtZeroIndexAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 0;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( LastIndexOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 11;
    const unsigned int START_INDEX = 12;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
ZTEST_CASE ( LastIndexOf2_MatchesPreviousToStartIndexAreNotFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {'A', 'b'}; // Ab
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = StringUnicode::PATTERN_NOT_FOUND;
    const unsigned int START_INDEX = 9;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the matches are found at the start index.
/// </summary>
ZTEST_CASE ( LastIndexOf2_MatchesExactlyAtStartIndexAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when the start position is out of bounds.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 5;
    const unsigned int START_INDEX = 50;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( LastIndexOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const int EXPECTED_POSITION1 = 5;
    const int EXPECTED_POSITION2 = 9;

	// [Execution]
    int uPosition1 = SOURCE_STRING.LastIndexOf(PATTERN1, EXPECTED_POSITION1, EComparisonType::E_BinaryCaseSensitive);
    int uPosition2 = SOURCE_STRING.LastIndexOf(PATTERN2, EXPECTED_POSITION2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK_EQUAL(uPosition1, EXPECTED_POSITION1);
    BOOST_CHECK_EQUAL(uPosition2, EXPECTED_POSITION2);
}

/// <summary>
/// Checks that the pattern is found when the index lays inside of an occurrence, using canonical comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenIndexIsInsideAnOccurrenceUsingCanonicalComparison_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("xZA");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 'x', 'Z', 'A', 'b'}; // áÁñ¨ CX`*xZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const int EXPECTED_RESULT = 9;
    const unsigned int START_INDEX = 10;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when the index lays inside of an occurrence, using canonical comparison.
/// </summary>
ZTEST_CASE ( LastIndexOf2_PatternIsFoundWhenIndexIsInsideAnOccurrenceUsingBinaryComparison_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("xZA");
    const u16_z RESIDENT_CHARS[] = {'A', 'B', 'C', '*', 'x', 'Z', 'A', 'b'}; // ABC*xZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const int EXPECTED_RESULT = 4;
    const unsigned int START_INDEX = 5;

	// [Execution]
    int nResult = RESIDENT_STRING.LastIndexOf(PATTERN, START_INDEX, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the pattern is empty.
/// </summary>
ZTEST_CASE ( Contains_ReturnsFalseWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the resident string is empty.
/// </summary>
ZTEST_CASE ( Contains_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the pattern is not found.
/// </summary>
ZTEST_CASE ( Contains_ReturnsMinusOneWhenPatternIsNotFound_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("A");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( Contains_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
ZTEST_CASE ( Contains_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;

	// [Execution]
    bool bResultNormalized    = NORMALIZED_RESIDENT_STRING.Contains(NONNORMALIZED_PATTERN, COMPARISON_TYPE);
    bool bResultNonNormalized = NONNORMALIZED_RESIDENT_STRING.Contains(NONNORMALIZED_PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_NE(bResultNormalized, bResultNonNormalized);
}

/// <summary>
/// Checks that the pattern is found at zero index.
/// </summary>
ZTEST_CASE ( Contains_TheMatchesExactlyAtZeroIndexAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( Contains_TheMatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RESIDENT_STRING.Contains(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( PositionOf1_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns "not found" when the resident string is empty.
/// </summary>
ZTEST_CASE ( PositionOf1_ReturnsNotFoundWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("DEF");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
ZTEST_CASE ( PositionOf1_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsNotFoundWhenStringsDoesNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const bool ITERATOR_POINTS_END = true;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf1_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at zero position.
/// </summary>
ZTEST_CASE ( PositionOf1_MatchesExactlyAtZeroPositionAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( PositionOf1_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( PositionOf1_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const StringUnicode::ConstCharIterator EXPECTED_POSITION1(SOURCE_STRING, 5);
    const StringUnicode::ConstCharIterator EXPECTED_POSITION2(SOURCE_STRING, 9);

	// [Execution]
    StringUnicode::ConstCharIterator position1 = SOURCE_STRING.PositionOf(PATTERN1, EComparisonType::E_BinaryCaseSensitive);
    StringUnicode::ConstCharIterator position2 = SOURCE_STRING.PositionOf(PATTERN2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK(position1 == EXPECTED_POSITION1);
    BOOST_CHECK(position2 == EXPECTED_POSITION2);
}

/// <summary>
/// Checks that it returns "not found" when the pattern is empty.
/// </summary>
ZTEST_CASE ( PositionOf2_ReturnsNotFoundWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that it returns the first occurrence, from left to right.
/// </summary>
ZTEST_CASE ( PositionOf2_ReturnsTheFirstOccurrence_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const StringUnicode RESIDENT_STRING = StringUnicode("B") + PATTERN + "B" + PATTERN + "B";
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 22, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZabc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    ++EXPECTED_RESULT;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(4);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsFoundWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñ¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 28, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(4);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at zero position.
/// </summary>
ZTEST_CASE ( PositionOf2_MatchesExactlyAtZeroPositionAreFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator();
    const StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is found at last position possible.
/// </summary>
ZTEST_CASE ( PositionOf2_MatchesExactlyAtLastPartOfResidentStringAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(11);
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(6);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}
    
/// <summary>
/// Checks that the matches that are previous to the start position are not returned.
/// </summary>
ZTEST_CASE ( PositionOf2_MatchesPreviousToStartPositionAreNotFound_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN(rcast_z(PATTERN_CHARS, const char*), 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(7);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

/// <summary>
/// Checks that the matches are found at the start position.
/// </summary>
ZTEST_CASE ( PositionOf2_MatchesExactlyAtStartPositionAreFound_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    StringUnicode::ConstCharIterator EXPECTED_RESULT = RESIDENT_STRING.GetConstCharIterator(5);
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator(5);

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(result == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( PositionOf2_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    StringUnicode PATTERN1("EFGH");
    PATTERN1.Append(CharUnicode(0x00011234));
    StringUnicode PATTERN2(CharUnicode(0x00011234));
    const StringUnicode::ConstCharIterator EXPECTED_POSITION1(SOURCE_STRING, 5);
    const StringUnicode::ConstCharIterator EXPECTED_POSITION2(SOURCE_STRING, 9);

	// [Execution]
    StringUnicode::ConstCharIterator position1 = SOURCE_STRING.PositionOf(PATTERN1, EXPECTED_POSITION1, EComparisonType::E_BinaryCaseSensitive);
    StringUnicode::ConstCharIterator position2 = SOURCE_STRING.PositionOf(PATTERN2, EXPECTED_POSITION2, EComparisonType::E_BinaryCaseSensitive);

    // [Verification]
    BOOST_CHECK(position1 == EXPECTED_POSITION1);
    BOOST_CHECK(position2 == EXPECTED_POSITION2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
ZTEST_CASE ( PositionOf2_AssertionFailsWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ASSERTION_FAILED = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);
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
/// Checks that the pattern is not found when the start position is out of bounds.
/// </summary>
ZTEST_CASE ( PositionOf2_PatternIsNotFoundWhenStartPositionIsOutOfBounds_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("CX");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING(rcast_z(RESIDENT_CHARS, const char*), 26, string_z::GetLocalEncodingUTF16());
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const bool ITERATOR_POINTS_END = true;
    StringUnicode::ConstCharIterator START_POSITION = RESIDENT_STRING.GetConstCharIterator();
    START_POSITION.MoveLast();
    ++START_POSITION;

	// [Execution]
    StringUnicode::CharIterator result = RESIDENT_STRING.PositionOf(PATTERN, START_POSITION, COMPARISON_TYPE);

    // [Verification]
    bool bPointsEnd = result.IsEnd();
    BOOST_CHECK_EQUAL(bPointsEnd, ITERATOR_POINTS_END);
}

#endif

/// <summary>
/// Checks that the string does not change when the pattern is empty.
/// </summary>
ZTEST_CASE ( Replace_StringDoesNotChangeWhenPatternIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("");
    const StringUnicode REPLACEMENT("XX");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that resident string does not change when it is empty.
/// </summary>
ZTEST_CASE ( Replace_StringDoesNotChangeWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("");
    const StringUnicode PATTERN("ABC");
    const StringUnicode REPLACEMENT("XX");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are removed when replacement string is empty.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreRemovedWhenReplacementStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("ABC");
    const StringUnicode PATTERN("B");
    const StringUnicode REPLACEMENT("");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT("AC");

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that all occurrences are replaced.
/// </summary>
ZTEST_CASE ( Replace_ReplacesAllOccurrences_Test )
{
    // [Preparation]
    const StringUnicode RESIDENT_STRING("AXBXCXDXEXF");
    const StringUnicode PATTERN("X");
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT("A_B_C_D_E_F");

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("X");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("X");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z'}; // áÁñ¨ CX`*ºZ
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 22, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("X");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is not found when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_PatternIsNotFoundWhenStringsDoNotMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("A");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'a', 'b'}; // áÁñ¨ CX`*ºZab
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("X");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using canonical case insensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseInsensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xD1, 0xA8, ' '}; // áÑ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZÁñabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, '_', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // á_CX`*ºZÁñabc
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using canonical case sensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchCanonicallyAndComparisonTypeIsCanonicalCaseSensitive_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xC1, 0xF1, 0xA8, ' '}; // Áñ¨ 
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 8, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // áÁñ¨ CX`*ºZÁñabc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, '_', 'C', 'X', '`', '*', 0xBA, 'Z', 0xC1, 0xF1, 'a', 'b', 'c'}; // á_CX`*ºZÁñabc
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using binary case sensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseSensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("Ab");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñab¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseSensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'c'}; // áÁñab¨ CX`*ºZ_c
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 30, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are replaced when it does not match any substring of the resident string, using binary case insensitive comparison.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreReplacedWhenStringsMatchBitwiseAndComparisonTypeIsBinaryCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 'a', 'b', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b', 'c'}; // áÁñab¨ CX`*ºZAbc
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 32, ETextEncoding::E_UTF16LE);
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_BinaryCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, '_', 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'c'}; // áÁñab¨ CX`*ºZAbc
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 28, ETextEncoding::E_UTF16LE);

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the normalization form of resident string affects the result.
/// </summary>
ZTEST_CASE ( Replace_NormalizationAffectsTheResultWhenUsingCanonicalComparison_Test )
{
    // [Preparation]
    //                                          B       A       ?        _        C
    u16_z NONNORMALIZED_RESIDENT_SEQUENCE[] = { 0x0042, 0x0041, 0x0341, 0x0331, 0x0043 }; // BÁ_C
    const StringUnicode NONNORMALIZED_RESIDENT_STRING((char*)NONNORMALIZED_RESIDENT_SEQUENCE, sizeof(NONNORMALIZED_RESIDENT_SEQUENCE), string_z::GetLocalEncodingUTF16());
    //                                         A       _        ?
    u16_z NONNORMALIZED_PATTERN_SEQUENCE[] = { 0x0041, 0x0331, 0x0341 }; // Á_
    const StringUnicode NONNORMALIZED_PATTERN((char*)NONNORMALIZED_PATTERN_SEQUENCE, sizeof(NONNORMALIZED_PATTERN_SEQUENCE), string_z::GetLocalEncodingUTF16());

    StringUnicode NORMALIZED_RESIDENT_STRING(NONNORMALIZED_RESIDENT_STRING);
    NORMALIZED_RESIDENT_STRING.Normalize(ENormalizationForm::E_D);

    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseSensitive;
    const StringUnicode EXPECTED_RESULT("B_C");

	// [Execution]
    StringUnicode strNormalizedString(NORMALIZED_RESIDENT_STRING);
    StringUnicode strNonNormalizedString(NONNORMALIZED_RESIDENT_STRING);
    strNormalizedString.Replace(NONNORMALIZED_PATTERN, REPLACEMENT, COMPARISON_TYPE);
    strNonNormalizedString.Replace(NONNORMALIZED_PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strNormalizedString != strNonNormalizedString);
}

/// <summary>
/// Checks that the pattern is replaced at zero index.
/// </summary>
ZTEST_CASE ( Replace_MatchesExactlyAtZeroIndexAreReplaced_Test )
{
    // [Preparation]
    const u16_z PATTERN_CHARS[] = {0xE1, 0xC1}; // áÁ
    const StringUnicode PATTERN((const char*)PATTERN_CHARS, 4, string_z::GetLocalEncodingUTF16());
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {'_', 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // _ñ¨ CX`*ºZAb
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 24, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the pattern is replaced at last position possible.
/// </summary>
ZTEST_CASE ( Replace_MatchesExactlyAtLastPartOfResidentStringAreReplaced_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("aB");
    const u16_z RESIDENT_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áÁñ¨ CX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, 0xC1, 0xF1, 0xA8, ' ', 'C', 'X', '`', '*', 0xBA, 'Z', '_'}; // áÁñ¨ CX`*ºZ_
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 24, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the replacement string's length is greater than one.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementIsLongerThanOneCharacter_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("a");
    const u16_z RESIDENT_CHARS[] = {0xE1, 'a', 0xF1, 0xA8, 'a', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'b'}; // áañ¨aCX`*ºZAb
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 26, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("123456");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 56, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the pattern string's length is greater than one.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenSearchPatternIsLongerThanOneCharacter_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("123456");
    const u16_z RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 56, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("_");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, '_', 0xF1, 0xA8, '_', 'C', 'X', '`', '*', 0xBA, 'Z', '_', 'b'}; // á_ñ¨_CX`*ºZ_b
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 26, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctly replaced when the pattern string's and replacement string's length are greater than one.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementAndSearchPatternAreLongerThanOneCharacter_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("123456");
    const u16_z RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4', '5', '6', 0xF1, 0xA8, '1', '2', '3', '4', '5', '6', 'C', 'X', '`', '*', 0xBA, 'Z', '1', '2', '3', '4', '5', '6', 'b'}; // á123456ñ¨123456CX`*ºZ123456b
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 56, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, 'A', 'B', 'C', 0xF1, 0xA8, 'A', 'B', 'C', 'C', 'X', '`', '*', 0xBA, 'Z', 'A', 'B', 'C', 'b'}; // áABCñ¨ABCCX`*ºZABCb
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 38, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the resident string does not change when the pattern is larger.
/// </summary>
ZTEST_CASE ( Replace_StringDoesNotChangeWhenPatternIsBigger_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("123456");
    const u16_z RESIDENT_CHARS[] = {0xE1, '1', '2', '3', '4'}; // á1234
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 10, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("ABC");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = RESIDENT_STRING;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that matches are correctlty replaced when the replacement string is larger than the resident string.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenReplacementIsBiggerThanResidentString_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("12");
    const u16_z RESIDENT_CHARS[] = {0xE1, '1', '2', 'b', '1', '2'}; // á12b12
    const StringUnicode RESIDENT_STRING((const char*)RESIDENT_CHARS, 12, string_z::GetLocalEncodingUTF16());
    const StringUnicode REPLACEMENT("ABCDEFGHI");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const u16_z EXPECTED_CHARS[] = {0xE1, 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'b', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'}; // áABCDEFGHIbABCDEFGHI
    const StringUnicode EXPECTED_RESULT((const char*)EXPECTED_CHARS, 40, string_z::GetLocalEncodingUTF16());

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the string is completely replaced when it equals the search pattern.
/// </summary>
ZTEST_CASE ( Replace_MatchesAreCorrectlyReplacedWhenResidentStringIsEqualToPattern_Test )
{
    // [Preparation]
    const StringUnicode PATTERN("123456");
    const StringUnicode RESIDENT_STRING = PATTERN;
    const StringUnicode REPLACEMENT("ABCDEFGHI");
    const EComparisonType COMPARISON_TYPE = EComparisonType::E_CanonicalCaseInsensitive;
    const StringUnicode EXPECTED_RESULT = REPLACEMENT;

	// [Execution]
    StringUnicode strString(RESIDENT_STRING);
    strString.Replace(PATTERN, REPLACEMENT, COMPARISON_TYPE);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that a common string is correctly appended.
/// </summary>
ZTEST_CASE ( Append1_CommonStringIsCorrectlyAppended_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING("123456");
    const StringUnicode APPENDIX("789");
    const StringUnicode EXPECTED_RESULT("123456789");

	// [Execution]
    StringUnicode strString(ORIGINAL_STRING);
    strString.Append(APPENDIX);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that appending an empty string takes no effect.
/// </summary>
ZTEST_CASE ( Append1_AppendingEmptyStringTakesNoEffect_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING("123456");
    const StringUnicode APPENDIX("");
    const StringUnicode EXPECTED_RESULT = ORIGINAL_STRING;

	// [Execution]
    StringUnicode strString(ORIGINAL_STRING);
    strString.Append(APPENDIX);

    // [Verification]
    BOOST_CHECK(strString == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates both strings, the left one before the right one.
/// </summary>
ZTEST_CASE ( Append2_ConcatenatesBothStrings_Test )
{
    // [Preparation]
    const StringUnicode STRING1("ABC");
    const char* STRING2 = "DEF";
    const StringUnicode EXPECTED_RESULT("ABCDEF");

	// [Execution]
    StringUnicode strResult = STRING1 + STRING2;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append3_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u8_z VALUE = 234;
    const StringUnicode EXPECTED_RESULT("ABC234");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append4_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i8_z VALUE = -123;
    const StringUnicode EXPECTED_RESULT("ABC-123");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append5_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u16_z VALUE = 23456;
    const StringUnicode EXPECTED_RESULT("ABC23456");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append6_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i16_z VALUE = -23456;
    const StringUnicode EXPECTED_RESULT("ABC-23456");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append7_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u32_z VALUE = 23456890;
    const StringUnicode EXPECTED_RESULT("ABC23456890");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append8_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i32_z VALUE = -2345689;
    const StringUnicode EXPECTED_RESULT("ABC-2345689");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append9_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const u64_z VALUE = 123456890123;
    const StringUnicode EXPECTED_RESULT("ABC123456890123");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append10_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const i64_z VALUE = -123456890123;
    const StringUnicode EXPECTED_RESULT("ABC-123456890123");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append11_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const f32_z VALUE = -123.456f;
    const StringUnicode EXPECTED_RESULT("ABC-123.456001");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append12_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const f64_z VALUE = -123456.789;
    const StringUnicode EXPECTED_RESULT("ABC-123456.789");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append13_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    const bool VALUE = true;
    const StringUnicode EXPECTED_RESULT("ABCtrue");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it concatenates the converted input value to the string.
/// </summary>
ZTEST_CASE ( Append14_ConcatenatesStringAndInputValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("ABC");
    vf32_z VALUE;
    SVF32::Pack(1.0f, 2.0f, 3.0f, 4.0f, VALUE);
    const StringUnicode EXPECTED_RESULT("ABCVF(1, 2, 3, 4)");

	// [Execution]
    StringUnicode strResult = STRING;
    strResult.Append(VALUE);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that an empty string is returned when the resident string is empty.
/// </summary>
ZTEST_CASE ( Split_ReturnsOneEmptyStringWhenResidentStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = StringUnicode::GetEmpty();
    const unsigned int EXPECTED_SIZE = 1U;
    const StringUnicode EXPECTED_STRING = StringUnicode::GetEmpty();
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
}

/// <summary>
/// Checks that two empty strings are returned when the resident string contains only 1 separator.
/// </summary>
ZTEST_CASE ( Split_ReturnsTwoEmptyStringsWhenResidentStringIsCompoundOfOnlyOneSeparator_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "/";
    const unsigned int EXPECTED_SIZE = 2U;
    const StringUnicode EXPECTED_STRING = StringUnicode::GetEmpty();
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING);
}

/// <summary>
/// Checks that several empty strings are returned when the resident string contains more than 1 separator only.
/// </summary>
ZTEST_CASE ( Split_ReturnsSeveralEmptyStringsWhenResidentStringIsCompoundOfMoreThanOneSeparatorOnly_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "///";
    const unsigned int EXPECTED_SIZE = 4U;
    const StringUnicode EXPECTED_STRING = StringUnicode::GetEmpty();
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING);
    BOOST_CHECK(arStringParts[3] == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the value of a part that is surrounded by separators, when they are placed at the beginning and at the end of the string.
/// </summary>
ZTEST_CASE ( Split_ReturnsTheValueOfPartSurroundedBySeparatorsWhenTheyArePlacedAtBeginningAndEnd_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "/123/";
    const unsigned int EXPECTED_SIZE = 3U;
    const StringUnicode EXPECTED_STRING_NON_EMPTY = "123";
    const StringUnicode EXPECTED_STRING_EMPTY = StringUnicode::GetEmpty();
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING_EMPTY);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING_NON_EMPTY);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING_EMPTY);
}

/// <summary>
/// Checks that it returns the value of one part when there are not separators in the string.
/// </summary>
ZTEST_CASE ( Split_ReturnsTheValueOfOnePartWhenThereAreNotSeparatorsInString_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "123";
    const unsigned int EXPECTED_SIZE = 1U;
    const StringUnicode EXPECTED_STRING_NON_EMPTY = "123";
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING_NON_EMPTY);
}

/// <summary>
/// Checks that it returns every part of a common string divided by separators.
/// </summary>
ZTEST_CASE ( Split_ReturnsEveryPartOfCommonStringDividedBySeparators_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "123/456/789";
    const unsigned int EXPECTED_SIZE = 3U;
    const StringUnicode EXPECTED_STRING1 = "123";
    const StringUnicode EXPECTED_STRING2 = "456";
    const StringUnicode EXPECTED_STRING3 = "789";
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that it returns every part of a common string divided by separators whose length is greater than one.
/// </summary>
ZTEST_CASE ( Split_ReturnsEveryPartOfCommonStringDividedBySeparatorsOfLengthGreaterThanOne_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "123-/-456-/-789";
    const unsigned int EXPECTED_SIZE = 3U;
    const StringUnicode EXPECTED_STRING1 = "123";
    const StringUnicode EXPECTED_STRING2 = "456";
    const StringUnicode EXPECTED_STRING3 = "789";
    const StringUnicode SEPARATOR = "-/-";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that it returns the entire string when the seperator is empty.
/// </summary>
ZTEST_CASE ( Split_ReturnsEntireStringWhenSeparatorIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode ORIGINAL_STRING = "123/456/789";
    const unsigned int EXPECTED_SIZE = 1U;
    const StringUnicode EXPECTED_STRING = ORIGINAL_STRING;
    const StringUnicode SEPARATOR = StringUnicode::GetEmpty();

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( Split_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{
    // [Preparation]
    StringUnicode ORIGINAL_STRING = "123/";
    ORIGINAL_STRING.Append(CharUnicode(0x00010300));
    ORIGINAL_STRING.Append("/789");
    const unsigned int EXPECTED_SIZE = 3U;
    const StringUnicode EXPECTED_STRING1 = "123";
    const StringUnicode EXPECTED_STRING2 = CharUnicode(0x00010300);
    const StringUnicode EXPECTED_STRING3 = "789";
    const StringUnicode SEPARATOR = "/";

	// [Execution]
    ArrayResult<StringUnicode> arStringParts = ORIGINAL_STRING.Split(SEPARATOR);

    // [Verification]
    BOOST_CHECK_EQUAL(arStringParts.GetCount(), EXPECTED_SIZE);
    BOOST_CHECK(arStringParts[0] == EXPECTED_STRING1);
    BOOST_CHECK(arStringParts[1] == EXPECTED_STRING2);
    BOOST_CHECK(arStringParts[2] == EXPECTED_STRING3);
}

/// <summary>
/// Checks that a common number is correctly parsed.
/// </summary>
ZTEST_CASE ( ToInteger_CommonNumberIsParsed_Test )
{

    // [Preparation]
    const StringUnicode STRING("123456");
    const i64_z EXPECTED_NUMBER = 123456;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a negative number is correctly parsed.
/// </summary>
ZTEST_CASE ( ToInteger_NegativeNumberIsParsed_Test )
{

    // [Preparation]
    const StringUnicode STRING("-123456");
    const i64_z EXPECTED_NUMBER = -123456;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a fractional number is correctly parsed when the separator is a period.
/// </summary>
ZTEST_CASE ( ToInteger_FractionalNumberIsParsedWhenSeparatorIsPeriod_Test )
{

    // [Preparation]
    const StringUnicode STRING("123.456");
    const i64_z EXPECTED_NUMBER = 123;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that commas are ignored when used to express a fractional number.
/// </summary>
ZTEST_CASE ( ToInteger_FractionalNumberCommaSeparatorIsIgnored_Test )
{

    // [Preparation]
    const StringUnicode STRING("123,456");
    const i64_z EXPECTED_NUMBER = 123456;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that there is no rounding performed when a fractional number is parsed.
/// </summary>
ZTEST_CASE ( ToInteger_NoRoundingWhenFractionalNumberIsParsed_Test )
{

    // [Preparation]
    const StringUnicode STRING("123.999");
    const i64_z EXPECTED_NUMBER = 123;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that number preceded by a plus sign (+) are allowed.
/// </summary>
ZTEST_CASE ( ToInteger_PlusSignIsAllowed_Test )
{

    // [Preparation]
    const StringUnicode STRING("+123");
    const i64_z EXPECTED_NUMBER = 123;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid number.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenStringStoresNoValidNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a positive number that exceeds the limits of the type.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenStringContainsATooBigPositiveNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("92233720368547758070");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a negative number that exceeds the limits of the type.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenStringContainsATooBigNegativeNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("92233720368547758080");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToInteger();
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
/// Checks that it returns zero when the string is empty.
/// </summary>
ZTEST_CASE ( ToInteger_ReturnsZeroWhenStringIsEmpty_Test )
{

    // [Preparation]
    const StringUnicode STRING("");
    const i64_z EXPECTED_NUMBER = 0;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the string does not contain a valid number.
/// </summary>
ZTEST_CASE ( ToInteger_ReturnsZeroWhenStringIsNotValid_Test )
{

    // [Preparation]
    const StringUnicode STRING("NotValid");
    const i64_z EXPECTED_NUMBER = 0;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the number is clamped to the maximum range when the string contains a too big positive number.
/// </summary>
ZTEST_CASE ( ToInteger_ReturnsMaximumWhenStringsContainsTooBigPositiveNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("92233720368547758070");
    const i64_z EXPECTED_NUMBER = SInteger::MaxPositiveI64_Z;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the number is clamped to the maximum range when the string contains a too big negative number.
/// </summary>
ZTEST_CASE ( ToInteger_ReturnsMaximumWhenStringsContainsTooBigNegativeNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("-92233720368547758080");
    const i64_z EXPECTED_NUMBER = SInteger::MaxNegativeI64_Z;

	// [Execution]
    i64_z nParsedNumber = STRING.ToInteger();

    // [Verification]
    BOOST_CHECK_EQUAL(nParsedNumber, EXPECTED_NUMBER);
}

#endif

/// <summary>
/// Checks that a common hexadecimal value is correctly converted to an integer.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_CreatesIntegerFromCommonHexadecimalValue_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING = "6AC5FF01";
    const u32_z EXPECTED_VALUE = 0x6AC5FF01;
    u32_z uResult = 0;

    // [Execution]
    uResult = INPUT_STRING.ToIntegerFromHexadecimal<u32_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a zero hexadecimal value is correctly converted to an integer.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_CreatesIntegerFromHexadecimalValueWhenItEqualsZero_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING = "00000000";
    const u32_z EXPECTED_VALUE = 0;
    u32_z uResult = 0;

    // [Execution]
    uResult = INPUT_STRING.ToIntegerFromHexadecimal<u32_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a maximum hexadecimal value is correctly converted to an integer.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_CreatesIntegerFromHexadecimalValueWhenItEqualsMaximum_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING = "FFFFFFFF";
    const u32_z EXPECTED_VALUE = 0xFFFFFFFF;
    u32_z uResult = 0;

    // [Execution]
    uResult = INPUT_STRING.ToIntegerFromHexadecimal<u32_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a 0x-prefixed hexadecimal value is correctly converted to an integer.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_CreatesIntegerFromHexadecimalValueWhenItHas0xPrefix_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING = "0xFFFFFFFF";
    const u32_z EXPECTED_VALUE = 0xFFFFFFFF;
    u32_z uResult = 0;

    // [Execution]
    uResult = INPUT_STRING.ToIntegerFromHexadecimal<u32_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the 0x prefix is case insensitive.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_ThePrefixIsCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING_LOWER_CASE = "0xFFFFFFFF";
    const StringUnicode INPUT_STRING_UPPER_CASE = "0XFFFFFFFF";
    u32_z uResultLowerCase = 0;
    u32_z uResultUpperCase = 0;

    // [Execution]
    uResultLowerCase = INPUT_STRING_LOWER_CASE.ToIntegerFromHexadecimal<u32_z>();
    uResultUpperCase = INPUT_STRING_UPPER_CASE.ToIntegerFromHexadecimal<u32_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResultLowerCase, uResultUpperCase);
}

/// <summary>
/// Checks that it can create integers of different sizes.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_CreatesIntegersOfDifferentSizes_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING_8BITS  = "2A";
    const StringUnicode INPUT_STRING_16BITS = "6AC5";
    const StringUnicode INPUT_STRING_32BITS = "6AC5FF01";
    const StringUnicode INPUT_STRING_64BITS = "6AC5FF016AC5FF01";
    const u8_z  EXPECTED_VALUE_8BITS  = 0x2AU;
    const u16_z EXPECTED_VALUE_16BITS = 0x6AC5U;
    const u32_z EXPECTED_VALUE_32BITS = 0x6AC5FF01U;
    const u64_z EXPECTED_VALUE_64BITS = 0x6AC5FF016AC5FF01ULL;
    u8_z  uResult8Bits  = 0;
    u16_z uResult16Bits = 0;
    u32_z uResult32Bits = 0;
    u64_z uResult64Bits = 0;

    // [Execution]
    uResult8Bits = INPUT_STRING_8BITS.ToIntegerFromHexadecimal<u8_z>();
    uResult16Bits = INPUT_STRING_16BITS.ToIntegerFromHexadecimal<u16_z>();
    uResult32Bits = INPUT_STRING_32BITS.ToIntegerFromHexadecimal<u32_z>();
    uResult64Bits = INPUT_STRING_64BITS.ToIntegerFromHexadecimal<u64_z>();
    
    // [Verification]
    BOOST_CHECK_EQUAL(uResult8Bits,  EXPECTED_VALUE_8BITS);
    BOOST_CHECK_EQUAL(uResult16Bits, EXPECTED_VALUE_16BITS);
    BOOST_CHECK_EQUAL(uResult32Bits, EXPECTED_VALUE_32BITS);
    BOOST_CHECK_EQUAL(uResult64Bits, EXPECTED_VALUE_64BITS);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when string's length is greater than the integer type's size.
/// </summary>
ZTEST_CASE ( ToIntegerFromHexadecimal_AssertionFailsWhenInputStringLengthIsGreaterThanntegerSize_Test )
{
    // [Preparation]
    const StringUnicode INPUT_STRING = "A45FA45FA45FA45F";
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        INPUT_STRING.ToIntegerFromHexadecimal<u32_z>();
    }
    catch(...)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// Checks that the full "true" word is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_FullTrueWordIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("true");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "T", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_TrueAbbreviationTIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("t");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "Y", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_TrueAbbreviationYIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("y");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of true, "1", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_TrueAbbreviation1IsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("1");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full "false" word is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_FullFalseWordIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("false");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "F", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_FalseAbbreviationFIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("f");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "N", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_FalseAbbreviationNIsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("n");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the abbreviation of False, "0", is correctly parsed.
/// </summary>
ZTEST_CASE ( ToBoolean_FalseAbbreviation0IsCorrectlyParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("0");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( ToBoolean_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToBoolean();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid boolean value.
/// </summary>
ZTEST_CASE ( ToBoolean_AssertionFailsWhenStringDoesNotContainValidValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToBoolean();
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
/// Checks that it returns False when the string is empty.
/// </summary>
ZTEST_CASE ( ToBoolean_ReturnsFalseWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode STRING("");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the string does not contain a valid boolean value.
/// </summary>
ZTEST_CASE ( ToBoolean_ReturnsFalseWhenStringDoesNotContainValidValue_Test )
{
    // [Preparation]
    const StringUnicode STRING("NotValid");
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

#endif

/// <summary>
/// Checks that it is case insensitive.
/// </summary>
ZTEST_CASE ( ToBoolean_IsCaseInsensitive_Test )
{
    // [Preparation]
    const StringUnicode STRING("TrUe");
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bParsedValue = STRING.ToBoolean();

    // [Verification]
    BOOST_CHECK_EQUAL(bParsedValue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common number is correctly parsed.
/// </summary>
ZTEST_CASE ( ToFloat_CommonNumberIsParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("123456");
    const f64_z EXPECTED_NUMBER = 123456.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a negative number is correctly parsed.
/// </summary>
ZTEST_CASE ( ToFloat_NegativeNumberIsParsed_Test )
{
    // [Preparation]
    const StringUnicode STRING("-123456");
    const f64_z EXPECTED_NUMBER = -123456.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that a fractional number is correctly parsed when the separator is a period.
/// </summary>
ZTEST_CASE ( ToFloat_FractionalNumberIsParsedWhenSeparatorIsPeriod_Test )
{
    // [Preparation]
    const StringUnicode STRING("123.456");
    const f64_z EXPECTED_NUMBER = 123.456;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that the fractional part of the number is ignored if a comma is used as decimal separator.
/// </summary>
ZTEST_CASE ( ToFloat_IfDecimalSeparatorIsCommaFractionalPartIsIgnored_Test )
{
    // [Preparation]
    const StringUnicode STRING("123,456");
    const f64_z EXPECTED_NUMBER = 123.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that scientific notation is also allowed.
/// </summary>
ZTEST_CASE ( ToFloat_ScientificNotationIsAllowed_Test )
{
    // [Preparation]
    const StringUnicode STRING("1e03");
    const f64_z EXPECTED_NUMBER = 1000.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the string is empty.
/// </summary>
ZTEST_CASE ( ToFloat_AssertionFailsWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode STRING("");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string does not contain a valid number.
/// </summary>
ZTEST_CASE ( ToFloat_AssertionFailsWhenStringStoresNoValidNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("NotValid");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a positive number that exceeds the limits of the type.
/// </summary>
ZTEST_CASE ( ToFloat_AssertionFailsWhenStringContainsATooBigPositiveNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("1e400");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the string contains a negative number that exceeds the limits of the type.
/// </summary>
ZTEST_CASE ( ToFloat_AssertionFailsWhenStringContainsATooBigNegativeNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("-1e400");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STRING.ToFloat();
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
/// Checks that it returns zero when the string is empty.
/// </summary>
ZTEST_CASE ( ToFloat_ReturnsZeroWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode STRING("");
    const f64_z EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the string does not contain a valid number.
/// </summary>
ZTEST_CASE ( ToFloat_ReturnsZeroWhenStringIsNotValid_Test )
{
    // [Preparation]
    const StringUnicode STRING("NotValid");
    const f64_z EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns positive infinite when the string contains a too big positive number.
/// </summary>
ZTEST_CASE ( ToFloat_ReturnsPlusInfiniteWhenStringsContainsTooBigPositiveNumber_Test )
{
    using f64_z;
    using u64_z;

    union UIntToFloat64
    {
        u64_z int_number;
        f64_z float_number;
    };

    // [Preparation]
    const StringUnicode STRING("1e400");
    UIntToFloat64 uitof;
    uitof.int_number = 0x7FF0000000000000; // Positive infinite
    const f64_z EXPECTED_NUMBER = uitof.float_number;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns negative infinite when the string contains a too big negative number.
/// </summary>
ZTEST_CASE ( ToFloat_ReturnsMinusInfiniteWhenStringsContainsTooBigNegativeNumber_Test )
{
    using f64_z;
    using u64_z;

    union UIntToFloat64
    {
        u64_z int_number;
        f64_z float_number;
    };

    // [Preparation]
    const StringUnicode STRING("-1e400");
    UIntToFloat64 uitof;
    uitof.int_number = 0xFFF0000000000000; // Negative infinite
    const f64_z EXPECTED_NUMBER = uitof.float_number;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

/// <summary>
/// Checks that it returns zero when the number is too small.
/// </summary>
ZTEST_CASE ( ToFloat_ReturnsZeroWhenStringsContainsTooSmallNumber_Test )
{
    // [Preparation]
    const StringUnicode STRING("1e-400");
    const f64_z EXPECTED_NUMBER = 0.0;

	// [Execution]
    f64_z fParsedNumber = STRING.ToFloat();

    // [Verification]
    BOOST_CHECK_EQUAL(fParsedNumber, EXPECTED_NUMBER);
}

#endif

/// <summary>
/// Checks that the signed number is correctly converted to a string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FromInteger_SignedValueIsCorrectlyConverted_Test, TZTemplateSignedTypes )
{
#ifdef Z_COMPILER_MSVC
    // This silents the warning caused by the switch structure below due to a type overflow, which is known and deliberated
    #pragma warning( push )
    #pragma warning( disable : 4244)
#endif

    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    StringUnicode EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = SInteger::MaxNegativeI8_Z;
        EXPECTED_RESULT = Z_L("-128");
        break;
    case SIZE_16:
        INPUT = SInteger::MaxNegativeI16_Z;
        EXPECTED_RESULT = Z_L("-32768");
        break;
    case SIZE_32:
        INPUT = SInteger::MaxNegativeI32_Z;
        EXPECTED_RESULT = Z_L("-2147483648");
        break;
    case SIZE_64:
        INPUT = SInteger::MaxNegativeI64_Z;
        EXPECTED_RESULT = Z_L("-9223372036854775808");
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = "";
    }

	// [Execution]
    StringUnicode strResult = StringUnicode::FromInteger(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);

#ifdef Z_COMPILER_MSVC
    #pragma warning( pop )
#endif
}

/// <summary>
/// Checks that the unsigned number is correctly converted to a string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FromInteger_UnsignedValueIsCorrectlyConverted_Test, TZTemplateUnsignedTypes )
{
#ifdef Z_COMPILER_MSVC
    // This silents the warning caused by the switch structure below due to a type overflow, which is known and deliberated
    #pragma warning( push )
    #pragma warning( disable : 4244)
#endif

    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    StringUnicode EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = SInteger::MaxU8_Z;
        EXPECTED_RESULT = Z_L("255");
        break;
    case SIZE_16:
        INPUT = SInteger::MaxU16_Z;
        EXPECTED_RESULT = Z_L("65535");
        break;
    case SIZE_32:
        INPUT = SInteger::MaxU32_Z;
        EXPECTED_RESULT = Z_L("4294967295");
        break;
    case SIZE_64:
        INPUT = SInteger::MaxU64_Z;
        EXPECTED_RESULT = Z_L("18446744073709551615");
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = "";
    }

	// [Execution]
    StringUnicode strResult = StringUnicode::FromInteger(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);

#ifdef Z_COMPILER_MSVC
    #pragma warning( pop )
#endif

}

/// <summary>
/// Checks that zero is correctly converted to a string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FromInteger_ZeroIsCorrectlyConverted_Test, TTemplateTypes )
{
    // [Preparation]
    T INPUT = 0;
    StringUnicode EXPECTED_RESULT = Z_L("0");

	// [Execution]
    StringUnicode strResult = StringUnicode::FromInteger(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for the TRUE value meets the expectations.
/// </summary>
ZTEST_CASE ( FromBoolean_TrueValueIsConvertedFromBooleanAsExpected_Test )
{
    // [Preparation]
    const bool BOOLEAN_VALUE_TRUE = true;
    StringUnicode EXPECTED_RESULT = Z_L("true");

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromBoolean(BOOLEAN_VALUE_TRUE);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for the FALSE value meets the expectations.
/// </summary>
ZTEST_CASE ( FromBoolean_FalseValueIsConvertedFromBooleanAsExpected_Test )
{
    // [Preparation]
    const bool BOOLEAN_VALUE_FALSE = false;
    StringUnicode EXPECTED_RESULT = Z_L("false");

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromBoolean(BOOLEAN_VALUE_FALSE);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for an high number (which requires scientific notation) is what expected.
/// </summary>
ZTEST_CASE ( FromFloat1_HighNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f32_z NUMBER = -12345678901234.0f;
#if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345679e+13");
#else
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345679e+13");
#endif

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a tiny number (which requires scientific notation) is what expected.
/// </summary>
ZTEST_CASE ( FromFloat1_TinyNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f32_z NUMBER = -0.0000000012345678901234f;
#if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
    StringUnicode EXPECTED_RESULT = Z_L("-1.23456789e-09");
#else
    StringUnicode EXPECTED_RESULT = Z_L("-1.23456789e-09");
#endif

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a common number is what expected.
/// </summary>
ZTEST_CASE ( FromFloat1_CommonNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f32_z NUMBER = -12345.6789f;
    StringUnicode EXPECTED_RESULT = Z_L("-12345.6787"); // There is a strange rounding here

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for an high number (which requires scientific notation) is what expected.
/// </summary>
ZTEST_CASE ( FromFloat2_HighNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f64_z NUMBER = -1234567890123456789123456789.0;
#if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345678901234569e+27");
#else
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345678901234569e+27");
#endif

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a tiny number (which requires scientific notation) is what expected.
/// </summary>
ZTEST_CASE ( FromFloat2_TinyNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f64_z NUMBER = -0.000000001234567890123412345678901234;
#if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345678901234124e-09");
#else
    StringUnicode EXPECTED_RESULT = Z_L("-1.2345678901234124e-09");
#endif

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if the string returned for a common number is what expected.
/// </summary>
ZTEST_CASE ( FromFloat2_CommonNumberIsCorrectlyConverted_Test )
{
    // [Preparation]
    const f64_z NUMBER = -1234567890.123456789;
    StringUnicode EXPECTED_RESULT = Z_L("-1234567890.1234567");

	// [Execution]
    StringUnicode strResultUT = StringUnicode::FromFloat(NUMBER);

    // [Verification]
    BOOST_CHECK(strResultUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the length of the string depends on the size of the integer type when the value is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( FromIntegerToHexadecimal_TheLengthOfStringDependsOnTypeSizeWhenValueIsZero_Test, TZTemplateUnsignedTypes )
{
    // [Preparation]
    T INPUT = 0;
    puint_z EXPECTED_LENGTH = sizeof(T) * 2U; // 2 letters per byte

	// [Execution]
    StringUnicode strResult = StringUnicode::FromIntegerToHexadecimal(INPUT);

    // [Verification]
    puint_z uLength = strResult.GetLength();
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns the expected string when using 1 byte.
/// </summary>
ZTEST_CASE ( FromIntegerToHexadecimal_ItReturnsExpectedValueWhenUsingOneByte_Test )
{
    // [Preparation]
    u8_z INPUT = 0x0F;
    StringUnicode EXPECTED_STRING = "0F";

	// [Execution]
    StringUnicode strResult = StringUnicode::FromIntegerToHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 2 bytes.
/// </summary>
ZTEST_CASE ( FromIntegerToHexadecimal_ItReturnsExpectedValueWhenUsingTwoBytes_Test )
{
    // [Preparation]
    u16_z INPUT = 0x01EF;
    StringUnicode EXPECTED_STRING = "01EF";

	// [Execution]
    StringUnicode strResult = StringUnicode::FromIntegerToHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 4 bytes.
/// </summary>
ZTEST_CASE ( FromIntegerToHexadecimal_ItReturnsExpectedValueWhenUsingFourBytes_Test )
{
    // [Preparation]
    u32_z INPUT = 0x0123CDEF;
    StringUnicode EXPECTED_STRING = "0123CDEF";

	// [Execution]
    StringUnicode strResult = StringUnicode::FromIntegerToHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns the expected string when using 8 bytes.
/// </summary>
ZTEST_CASE ( FromIntegerToHexadecimal_ItReturnsExpectedValueWhenUsingEightBytes_Test )
{
    // [Preparation]
    u64_z INPUT = 0x0123456789ABCDEF;
    StringUnicode EXPECTED_STRING = "0123456789ABCDEF";

	// [Execution]
    StringUnicode strResult = StringUnicode::FromIntegerToHexadecimal(INPUT);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_STRING);
}

/// <summary>
/// Checks that it returns zero when the string is empty.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsZeroWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("");
    const StringUnicode::ConstCharIterator EXPECTED_ITERATOR(SOURCE_STRING);
    const bool IS_END = true;

	// [Execution]
    StringUnicode::ConstCharIterator iterator = SOURCE_STRING.GetConstCharIterator();

    // [Verification]
    BOOST_CHECK_EQUAL(iterator.IsEnd(), IS_END);
}

/// <summary>
/// Checks that it returns the expected result value when using a common non-empty string.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsCorrectValueWhenUsingCommonString_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABC");
    const unsigned int EXPECTED_LENGTH = 3;

	// [Execution]
    unsigned int nLength = SOURCE_STRING.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(nLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns the expected result when using characters from the Supplementaty Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( GetLength_ReturnsExpectedResultWhenUsingSMPCharacters_Test )
{

    // [Preparation]
    StringUnicode SOURCE_STRING("ABCD");
    SOURCE_STRING.Append(CharUnicode(0x00010300));
    SOURCE_STRING.Append("EFGH");
    SOURCE_STRING.Append(CharUnicode(0x00011234));
    SOURCE_STRING.Append("IJKL");
    
    const int EXPECTED_LENGTH = 14;

	// [Execution]
    unsigned int uLength = SOURCE_STRING.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(uLength, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that it returns True when the string is empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsTrueWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING = StringUnicode::GetEmpty();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = SOURCE_STRING.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the string is not empty.
/// </summary>
ZTEST_CASE ( IsEmpty_ReturnsFalseWhenStringIsNotEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABC");
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = SOURCE_STRING.IsEmpty();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned buffer contains UTF-16 text.
/// </summary>
ZTEST_CASE ( GetInternalBuffer_ReturnedBufferContainsUTF16Text_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING("ABC");

	// [Execution]
    const u16_z* szCharacters = SOURCE_STRING.GetInternalBuffer();

    // [Verification]
    string_z strStringFromBuffer(rcast_z(szCharacters, const i8_z*), SOURCE_STRING.GetLength() * sizeof(u16_z), string_z::GetLocalEncodingUTF16());
    BOOST_CHECK(strStringFromBuffer == SOURCE_STRING);
}

/// <summary>
/// Checks that the returned buffer is not null when the string is empty.
/// </summary>
ZTEST_CASE ( GetInternalBuffer_ReturnedBufferIsNotNullWhenStringIsEmpty_Test )
{
    // [Preparation]
    const StringUnicode SOURCE_STRING;

	// [Execution]
    const u16_z* szCharacters = SOURCE_STRING.GetInternalBuffer();

    // [Verification]
    BOOST_CHECK(szCharacters != null_z);
}

/// <summary>
/// Checks that it's an empty string, a string whose length is zero.
/// </summary>
ZTEST_CASE ( GetEmpty_ReturnsZeroLengthString_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("");

	// [Execution]
    StringUnicode strResult = StringUnicode::GetEmpty();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to upper case works fine.
/// </summary>
ZTEST_CASE ( ToUpperCase_StringWithEnglishCharactersConvertedToUpperCase_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("ABCDEFG");
    StringUnicode INPUT_STRING("aBcdefg");

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToUpperCase();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with non-ASCII characters and numbers to upper case works fine.
/// </summary>
ZTEST_CASE ( ToUpperCase_StringWithNonASCIICharsAndNumbersConvertedToUpperCase_Test )
{
    // [Preparation]
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();

    // Info for inputs&outputs extracted from:
    // ftp://ftp.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt

    // Inputs:
    // 00F2;LATIN SMALL LETTER O WITH GRAVE
    // 010D;LATIN SMALL LETTER C WITH CARON
    // 0121;LATIN SMALL LETTER G WITH DOT ABOVE
    // 00DB;LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    // 0037;DIGIT SEVEN
    const u16_z INPUT_STRING_CODE_UNITS[]   = { 0x00F2, 0x010D, 0x0121, 0x0037, 0x00DB, 0 };
    const StringUnicode INPUT_STRING(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);

    // Outputs:
    // 00D2;LATIN CAPITAL LETTER O WITH GRAVE
    // 010C;LATIN CAPITAL LETTER C WITH CARON
    // 0120;LATIN CAPITAL LETTER G WITH DOT ABOVE
    // 00DB;LATIN CAPITAL LETTER U WITH CIRCUMFLEX
    // 0037;DIGIT SEVEN
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00D2, 0x010C, 0x0120, 0x0037, 0x00DB, 0 };
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    StringUnicode strResult = INPUT_STRING.ToUpperCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to upper case.
/// </summary>
ZTEST_CASE ( ToUpperCase_EmptyStringConvertedToUpperCase_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode INPUT_STRING("");

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToUpperCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to lower case works fine.
/// </summary>
ZTEST_CASE ( ToLowerCase_StringWithEnglishCharactersConvertedToLowerCase_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("abcdefg");
    StringUnicode INPUT_STRING("AbCDEFG");

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToLowerCase();
    
    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with non-ASCII characters and numbers to lower case works fine.
/// </summary>
ZTEST_CASE ( ToLowerCase_StringWithNonASCIICharsAndNumbersConvertedToLowerCase_Test )
{
    // [Preparation]
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF16();

    // Info for inputs&outputs extracted from:
    // ftp://ftp.unicode.org/Public/UCD/latest/ucd/UnicodeData.txt

    // Inputs:
    // 00D2;LATIN CAPITAL LETTER O WITH GRAVE
    // 010C;LATIN CAPITAL LETTER C WITH CARON
    // 0120;LATIN CAPITAL LETTER G WITH DOT ABOVE
    // 013C;LATIN SMALL LETTER L WITH CEDILLA
    // 0037;DIGIT SEVEN
    const u16_z INPUT_STRING_CODE_UNITS[]   = { 0x00D2, 0x010C, 0x0120, 0x0037, 0x013C, 0 };
    const StringUnicode INPUT_STRING(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);

    // Outputs:
    // 00F2;LATIN SMALL LETTER O WITH GRAVE
    // 010D;LATIN SMALL LETTER C WITH CARON
    // 0121;LATIN SMALL LETTER G WITH DOT ABOVE
    // 013C;LATIN SMALL LETTER L WITH CEDILLA
    // 0037;DIGIT SEVEN
    const u16_z EXPECTED_STRING_CODE_UNITS[]   = { 0x00F2, 0x010D, 0x0121, 0x0037, 0x013C, 0 };
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

    // [Execution]
    StringUnicode strResult = INPUT_STRING.ToLowerCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to lower case.
/// </summary>
ZTEST_CASE ( ToLowerCase_EmptyStringConvertedToLowerCase_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode INPUT_STRING("");

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToLowerCase();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that converting a string with only English characters to folded case works fine.
/// </summary>
ZTEST_CASE ( ToCaseFolded_StringConvertedToFoldedCase_Test )
{
    // [Preparation]
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF32();

    // Data extracted from:
    // http://www.unicode.org/Public/UNIDATA/CaseFolding.txt
    // First row the original value.
    // 01F4; C; 01F5; # LATIN CAPITAL LETTER G WITH ACUTE
    // 0181; C; 0253; # LATIN CAPITAL LETTER B WITH HOOK
    // 004E; C; 006E; # LATIN CAPITAL LETTER N
    // 10426; C; 1044E; # DESERET CAPITAL LETTER OI
    // 00C3; C; 00E3; # LATIN CAPITAL LETTER A WITH TILDE
    // Useful to see the mappings:
    // http://www.branah.com/unicode-converter
    const u32_z INPUT_STRING_CODE_UNITS[]   = { 0x01F4, 0x0181, 0x004E, 0x10426, 0x00C3, 0 };
    const StringUnicode INPUT_STRING(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);
   
    // Third row the mapped value.
    // 01F4; C; 01F5; # LATIN CAPITAL LETTER G WITH ACUTE
    // 0181; C; 0253; # LATIN CAPITAL LETTER B WITH HOOK
    // 004E; C; 006E; # LATIN CAPITAL LETTER N
    // 10426; C; 1044E; # DESERET CAPITAL LETTER OI
    // 00C3; C; 00E3; # LATIN CAPITAL LETTER A WITH TILDE
    const u32_z EXPECTED_STRING_CODE_UNITS[]   = { 0x01F5, 0x0253, 0x006E, 0x1044E, 0x00E3 ,0 };
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the conversion to folded case works fine in the case of the conversion to may change the length in bytes of the resultant string.
/// </summary>
ZTEST_CASE ( ToCaseFolded_StringConvertedToFoldedCaseStringLengthMayChange_Test ) 
{
    // [Preparation]
    const ETextEncoding NATIVE_ENCODING = string_z::GetLocalEncodingUTF32();

    // Data extracted from:
    // http://www.unicode.org/Public/UNIDATA/CaseFolding.txt
    // First row the original value.
    // 03B0; F; 03C5 0308 0301; # GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS.
    // Useful to see the mappings:
    // http://www.branah.com/unicode-converter
    const u32_z INPUT_STRING_CODE_UNITS[]   = { 0x03B0, 0 };
    const StringUnicode INPUT_STRING(rcast_z(INPUT_STRING_CODE_UNITS, const i8_z*), sizeof(INPUT_STRING_CODE_UNITS), NATIVE_ENCODING);
   
    // Third row the mapped value.
    // 03B0; F; 03C5 0308 0301; # GREEK SMALL LETTER UPSILON WITH DIALYTIKA AND TONOS.
    const u32_z EXPECTED_STRING_CODE_UNITS[]   = { 0x03C5, 0x0308, 0x0301, 0 };
    const StringUnicode EXPECTED_RESULT(rcast_z(EXPECTED_STRING_CODE_UNITS, const i8_z*), sizeof(EXPECTED_STRING_CODE_UNITS), NATIVE_ENCODING);

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that empty string remains empty after applying the conversion to folded case.
/// </summary>
ZTEST_CASE ( ToCaseFolded_EmptyStringConvertedToFoldedCase_Test )
{
    // [Preparation]
    const StringUnicode EXPECTED_RESULT("");
    StringUnicode INPUT_STRING("");

	// [Execution]
    StringUnicode strResult = INPUT_STRING.ToCaseFolded();

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_RESULT);
}

// End - Test Suite: StringUnicode
ZTEST_SUITE_END()
