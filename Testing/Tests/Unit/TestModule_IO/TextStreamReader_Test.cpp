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

#include "ZIO/TextStreamReader.h"

// The MemoryStream type is used in all the tests
#include "ZIO/MemoryStream.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( TextStreamReader_TestSuite )

/// <summary>
/// Checks that the stream is correctly stored.
/// </summary>
ZTEST_CASE ( Constructor1_StreamIsCorrectlyStored_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const MemoryStream<>* EXPECTED_STREAM = &stream;

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    MemoryStream<>* pStoredStream = &reader.GetStream();
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const ENewLineCharacters EXPECTED_NEWLINE = ENewLineCharacters::E_LF;
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(1);

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ENewLineCharacters eNewLine = reader.GetNewLineSeparator();
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eNewLine == EXPECTED_NEWLINE);
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF8 text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF8_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF8;
    const string_z STREAM_TEXT("TestText");
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains ISO88591 text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForISO88591_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF8;
    const string_z STREAM_TEXT("TestText");
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(ETextEncoding::E_ISO88591);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains ASCII text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForASCII_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF8;
    const string_z STREAM_TEXT("TestText");
    
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(ETextEncoding::E_ASCII);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF16 little endian text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF16LE_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF16LE;
    const string_z STREAM_TEXT = string_z(char_z(0xFFFD)) + "TestText";
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF16 big endian text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF16BE_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF16BE;
    const string_z STREAM_TEXT = string_z(char_z(0xFFFD)) + "TestText";

    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFE, (i8_z)0xFF}; // Big endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF32 little endian text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF32LE_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF32LE;
    const string_z STREAM_TEXT = string_z(char_z(0xFFFD)) + "TestText";
    
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE, 0, 0}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    arBytes[2] = BOM[2];
    arBytes[3] = BOM[3];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the encoding is correctly deduced when the stream contains UTF32 big endian text.
/// </summary>
ZTEST_CASE ( Constructor1_EncodingIsCorrectlyDeducedForUTF32BE_Test )
{
    // [Preparation]
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_UTF32BE;
    const string_z STREAM_TEXT = string_z(char_z(0xFFFD)) + "TestText";
    
    ArrayResult<i8_z> arBytes = STREAM_TEXT.ToBytes(EXPECTED_ENCODING);
    static const i8_z BOM[] = {0, 0, (i8_z)0xFE, (i8_z)0xFF}; // Big endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    arBytes[2] = BOM[2];
    arBytes[3] = BOM[3];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream);

    // [Verification]
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the stream and the encoding are correctly stored.
/// </summary>
ZTEST_CASE ( Constructor2_StreamAndTheEncodingAreCorrectlyStored_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const MemoryStream<>* EXPECTED_STREAM = &stream;
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_ASCII;

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream, EXPECTED_ENCODING);

    // [Verification]
    MemoryStream<>* pStoredStream = &reader.GetStream();
    ETextEncoding eEncoding = reader.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
ZTEST_CASE ( Constructor2_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const ENewLineCharacters EXPECTED_NEWLINE = ENewLineCharacters::E_LF;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(1);

    // [Execution]
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);

    // [Verification]
    ENewLineCharacters eNewLine = reader.GetNewLineSeparator();
    BOOST_CHECK(eNewLine == EXPECTED_NEWLINE);
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
ZTEST_CASE ( ReadChars_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z NUMBER_OF_CHARS = 8U;
    const string_z EXPECTED_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
ZTEST_CASE ( ReadChars_ResultIncludesBOM_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const puint_z NUMBER_OF_CHARS = 10U;
    const string_z EXPECTED_TEXT("*TestText");
    
    ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_z(0xFFFE) || strResult[0] == char_z(0xFEFF));
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
ZTEST_CASE ( ReadChars_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z NUMBER_OF_CHARS = 9;
    const string_z INPUT_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    const puint_z ORIGINAL_POSITION = stream.GetPosition();

    // [Execution]
    reader.ReadChars(strResult, NUMBER_OF_CHARS);

    // [Verification]
    puint_z uCurrentPosition = stream.GetPosition();
    BOOST_CHECK(uCurrentPosition > ORIGINAL_POSITION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of characters equals zero.
/// </summary>
ZTEST_CASE ( ReadChars_AssertionFailsWhenInputNumberOfCharsEqualsZero_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const puint_z NUMBER_OF_CHARS = 0;
    const string_z INPUT_TEXT("*TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadChars(strResult, NUMBER_OF_CHARS);
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
/// Checks that it returns empty when the stream contains only one new line separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsEmptyWhenStreamContainsJustOneNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT = string_z::GetEmpty();
    puint_z uBufferSize = 1;
    i8_z arBytes = '\n';
    MemoryStream<> stream(&arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns a non-empty string when the stream contains only one null terminator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsNonEmptyWhenStreamContainsJustOneNullTerminator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("\0", 1U);
    puint_z uBufferSize = 1;
    i8_z arBytes = '\0';
    MemoryStream<> stream(&arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns empty when the new line character appears at the first position.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsEmptyWhenNewLineAppearsTheFirst_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT = string_z::GetEmpty();
    puint_z uBufferSize = 4U;
    const i8_z* arBytes = "\nABC";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the entire text but the new line when this appears at the last position.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsFullStringButLastNewLineWhenItAppearsAtTheEnd_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("ABC");
    puint_z uBufferSize = 4U;
    const i8_z* arBytes = "ABC\n";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is greater than the size of the batches used internally to read the text.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsGreaterThanInternalReadBatchesSize_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ ");
    puint_z uBufferSize = 387U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ \n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is lower than the size of the batches used internally to read the text.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsLowerThanInternalReadBatchesSize_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ ");
    puint_z uBufferSize = 195U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$ \n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the first line (text before the first new line separator) is equal to the size of the batches used internally to read the text.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenFirstLineIsEqualToInternalReadBatchesSize_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    puint_z uBufferSize = 312U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is greater than the size of the batches used internally to read the text, and there is no new line separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsGreaterThanInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    puint_z uBufferSize = 320U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is lower than the size of the batches used internally to read the text, and there is no length separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsLowerThanInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    puint_z uBufferSize = 128U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when the string's length is equal to the size of the batches used internally to read the text, and there is no legnth separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectStringWhenStringLengthIsEqualToInternalReadBatchesSizeAndThereIsNoNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    puint_z uBufferSize = 256U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the LF character as separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineLF_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("AB");
    puint_z uBufferSize = 5U;
    const i8_z* arBytes = "AB\nCD";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the CR character as separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineCR_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("AB");
    puint_z uBufferSize = 5U;
    const i8_z* arBytes = "AB\rCD";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    reader.SetNewLineSeparator(ENewLineCharacters::E_CR);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when using the CR and LF characters as separator.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsCorrectResultWhenUsingNewLineCRLF_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("AB");
    puint_z uBufferSize = 6U;
    const i8_z* arBytes = "AB\r\nCD";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    reader.SetNewLineSeparator(ENewLineCharacters::E_CRLF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the entire text when the chosen new line separator does not match the separator used in it.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsFullTextWhenUsingWrongNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("AB\rCD");
    puint_z uBufferSize = 5U;
    const i8_z* arBytes = "AB\rCD";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
ZTEST_CASE ( ReadLine_ResultIncludesBOM_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const string_z EXPECTED_TEXT("*TestText");
    
    ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_z(0xFFFE) || strResult[0] == char_z(0xFEFF));
}

/// <summary>
/// Checks that tthe internal pointer of the stream points to the position after the new line characters.
/// </summary>
ZTEST_CASE ( ReadLine_StreamInternalPointerPointsToPositionAfterNewLineSeparator_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z INPUT_TEXT("Test\r\nText");
    const puint_z EXPECTED_POSITION = 6; // After \r\n
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    reader.SetNewLineSeparator(ENewLineCharacters::E_CRLF);

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    puint_z uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that it returns the correct result when the new line separator is split in two batches internally.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenTheNewLineSeparatorIsDividedInTwoBatchesInternally_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    const string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    puint_z uBufferSize = 312U;
    const i8_z* arBytes = "\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!\r\n \
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$";
    MemoryStream<> stream(arBytes, uBufferSize);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_CRLF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when a UTF8 character is split in two batches internally.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenUTF8CharacterIsDividedInTwoBatchesInternally_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBN");
    EXPECTED_TEXT.Append(char_z(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$");
    
    string_z strInput(EXPECTED_TEXT);
    
    const ArrayResult<i8_z> arBytes = strInput.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U); // -1 to quit the trailing zero
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when a UTF16 character is split in two batches internally.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenUTF16CharacterIsDividedInTwoBatchesInternally_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_z EXPECTED_TEXT("\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzxc\
1234567890qwertyuiopasdfghjklzx");
    EXPECTED_TEXT.Append(char_z(0x00010300)); // A character compound of 2 codeunits in UTF16 (D800 DF00)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxc");
    
    string_z strInput(EXPECTED_TEXT);
    
    const ArrayResult<i8_z> arBytes = strInput.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 2U); // -2 to quit the trailing zero
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns the correct result when called several times.
/// </summary>
ZTEST_CASE ( ReadLine_ReturnsTheCorrectResultWhenIsCalledSeveralTimes_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    // Note: Each text line below is 64 bytes long
    // Currently, the reader uses 256 bytes per batch
    string_z STREAM_TEXT("\
\r\n34567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    STREAM_TEXT.Append(char_z(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    STREAM_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCV\r\
\n1234567890qwertyuiopasdfghj\r\n\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM\r\n");

    string_z EXPECTED_TEXT("\
34567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!");
    EXPECTED_TEXT.Append(char_z(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    EXPECTED_TEXT.Append("\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCV\
1234567890qwertyuiopasdfghj\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!$\
1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
    
    string_z strInput(STREAM_TEXT);
    
    const ArrayResult<i8_z> arBytes = strInput.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U); // -1 to quit the trailing zero
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_CRLF);
    string_z strResult;

    // [Execution]
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);
    reader.ReadLine(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
ZTEST_CASE ( ReadToEnd_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
ZTEST_CASE ( ReadToEnd_ResultIncludesBOM_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const string_z EXPECTED_TEXT("*TestText");
    
    ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_z(0xFFFE) || strResult[0] == char_z(0xFEFF));
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
ZTEST_CASE ( ReadToEnd_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z INPUT_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    const puint_z EXPECTED_POSITION = stream.GetLength();

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    puint_z uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that the text is correctly read when it contains characters of the Supplementary Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( ReadToEnd_TextIsCorrectlyReadWhenItContainsSMPCharacters_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    string_z EXPECTED_TEXT("TestText");
    EXPECTED_TEXT.Append(char_z(0x00010300));
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadToEnd(strResult);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the entire stream can be read.
/// </summary>
ZTEST_CASE ( ReadBlock_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z NUMBER_OF_BYTES = 8U;
    const string_z EXPECTED_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
ZTEST_CASE ( ReadBlock_ResultIncludesBOM_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const puint_z NUMBER_OF_BYTES = 20U;
    const string_z EXPECTED_TEXT("*TestText");
    
    ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult[0] == char_z(0xFFFE) || strResult[0] == char_z(0xFEFF));
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
ZTEST_CASE ( ReadBlock_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z NUMBER_OF_BYTES = 9;
    const string_z INPUT_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    const puint_z ORIGINAL_POSITION = stream.GetPosition();

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    puint_z uCurrentPosition = stream.GetPosition();
    BOOST_CHECK(uCurrentPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that characters compound of more than one code unit that are not completely contained in the block of bytes are not added to the result.
/// </summary>
ZTEST_CASE ( ReadBlock_IncompleteCharactersAreNotRead_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    const puint_z NUMBER_OF_BYTES = 6U;
    string_z INPUT_TEXT("Test");
    INPUT_TEXT.Append(char_z(0x00010300)); // A character compound of 4 codeunits in UTF8 (F0 90 8C 80)
    INPUT_TEXT.Append("Text");
    const string_z EXPECTED_TEXT("Test");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader.ReadBlock(strResult, NUMBER_OF_BYTES);

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of bytes equals zero.
/// </summary>
ZTEST_CASE ( ReadBlock_AssertionFailsWhenInputNumberOfBytesEqualsZero_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const puint_z NUMBER_OF_BYTES = 0;
    const string_z INPUT_TEXT("*TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadBlock(strResult, NUMBER_OF_BYTES);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks that an assertion fails when the number of bytes is not a multiple of the character size.
/// </summary>
ZTEST_CASE ( ReadBlock_AssertionFailsWhenInputNumberOfBytesIsNotMultipleOfCharacterSize_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const puint_z NUMBER_OF_BYTES = 5U;
    const string_z INPUT_TEXT("*TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        reader.ReadBlock(strResult, NUMBER_OF_BYTES);
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
/// Checks that the entire stream can be read.
/// </summary>
ZTEST_CASE ( OperatorRightShift_FullStreamCanBeRead_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z EXPECTED_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is included in the result string.
/// </summary>
ZTEST_CASE ( OperatorRightShift_ResultIncludesBOM_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    const string_z EXPECTED_TEXT("*TestText");
    
    ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    static const i8_z BOM[] = {(i8_z)0xFF, (i8_z)0xFE}; // Little endian BOM
    arBytes[0] = BOM[0];
    arBytes[1] = BOM[1];
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount());
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult[0] == char_z(0xFFFE) || strResult[0] == char_z(0xFEFF));
}

/// <summary>
/// Checks that the internal pointer of the stream is not restored after the operation.
/// </summary>
ZTEST_CASE ( OperatorRightShift_StreamInternalPointerIsNotRestored_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const string_z INPUT_TEXT("TestText");
    
    const ArrayResult<i8_z> arBytes = INPUT_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    const puint_z EXPECTED_POSITION = stream.GetLength();

    // [Execution]
    reader >> strResult;

    // [Verification]
    puint_z uCurrentPosition = stream.GetPosition();
    BOOST_CHECK_EQUAL(uCurrentPosition, EXPECTED_POSITION);
}

/// <summary>
/// Checks that the text is correctly read when it contains characters of the Supplementary Multilingual Plane (SMP).
/// </summary>
ZTEST_CASE ( OperatorRightShift_TextIsCorrectlyReadWhenItContainsSMPCharacters_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    string_z EXPECTED_TEXT("TestText");
    EXPECTED_TEXT.Append(char_z(0x00010300));
    
    const ArrayResult<i8_z> arBytes = EXPECTED_TEXT.ToBytes(INPUT_ENCODING);
    MemoryStream<> stream(arBytes.Get(), arBytes.GetCount() - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;

    // [Execution]
    reader >> strResult;

    // [Verification]
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that it returns a reference to the text reader instance.
/// </summary>
ZTEST_CASE ( OperatorRightShift_ReturnsReferenceToTextReader_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    puint_z uBufferSize = 8U;
    const i8_z* arBytes = "TestText";
    MemoryStream<> stream(arBytes, uBufferSize - 1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    string_z strResult;
    const TextStreamReader< MemoryStream<> >* EXPECTED_REFERENCE = &reader;

    // [Execution]
    const TextStreamReader< MemoryStream<> >* pReference = &(reader >> strResult);

    // [Verification]
    BOOST_CHECK_EQUAL(pReference, EXPECTED_REFERENCE);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetNewLineSeparator_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that the value is correctly stored.
/// </summary>
ZTEST_CASE ( SetNewLineSeparator_ValueIsCorrectlyStored_Test )
{
    // [Preparation]
    const ENewLineCharacters EXPECTED_VALUE = ENewLineCharacters::E_CR;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(1U);
    TextStreamReader< MemoryStream<> > reader(stream, INPUT_ENCODING);
    reader.SetNewLineSeparator(ENewLineCharacters::E_LF);
    const ENewLineCharacters ORIGINAL_VALUE = reader.GetNewLineSeparator();
    string_z strResult;

    // [Execution]
    reader.SetNewLineSeparator(EXPECTED_VALUE);

    // [Verification]
    ENewLineCharacters eNewLine = reader.GetNewLineSeparator();
    BOOST_CHECK(eNewLine == EXPECTED_VALUE);
    BOOST_CHECK(eNewLine != ORIGINAL_VALUE);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetStreamEncoding_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetStream_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: TextStreamReader
ZTEST_SUITE_END()
