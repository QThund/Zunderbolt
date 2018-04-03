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

#include "ZIO/TextStreamWriter.h"

#include "ZIO/MemoryStream.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( TextStreamWriter_TestSuite )
    
/// <summary>
/// Checks that the stream and the encoding are correctly stored.
/// </summary>
ZTEST_CASE ( Constructor_StreamAndTheEncodingAreCorrectlyStored_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const MemoryStream<>* EXPECTED_STREAM = &stream;
    const ETextEncoding EXPECTED_ENCODING = ETextEncoding::E_ASCII;

    // [Execution]
    TextStreamWriter< MemoryStream<> > writer(stream, EXPECTED_ENCODING);

    // [Verification]
    MemoryStream<>* pStoredStream = &writer.GetStream();
    ETextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
    BOOST_CHECK_EQUAL(pStoredStream, EXPECTED_STREAM);
}

/// <summary>
/// Checks that the input encoding is transformed to its endianness-dependant version when using UTF-16.
/// </summary>
ZTEST_CASE ( Constructor_EncodingIsConvertedToEndiannessDependantVersionWhenUsingUTF16_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16;
    const ETextEncoding EXPECTED_ENCODING = string_z::GetLocalEncodingUTF16();

    // [Execution]
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    ETextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that the input encoding is transformed to its endianness-dependant version when using UTF-32.
/// </summary>
ZTEST_CASE ( Constructor_EncodingIsConvertedToEndiannessDependantVersionWhenUsingUTF32_Test )
{
    // [Preparation]
    MemoryStream<> stream(1);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32;
    const ETextEncoding EXPECTED_ENCODING = string_z::GetLocalEncodingUTF32();

    // [Execution]
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    ETextEncoding eEncoding = writer.GetStreamEncoding();
    BOOST_CHECK(eEncoding == EXPECTED_ENCODING);
}

/// <summary>
/// Checks that all the default values of the data members are correct.
/// </summary>
ZTEST_CASE ( Constructor_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const ENewLineCharacters EXPECTED_NEWLINE = ENewLineCharacters::E_LF;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(1);

    // [Execution]
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    ENewLineCharacters eNewLine = writer.GetNewLineSeparator();
    BOOST_CHECK(eNewLine == EXPECTED_NEWLINE);
}

/// <summary>
/// Checks that the stream position pointer does not change.
/// </summary>
ZTEST_CASE ( Constructor_StreamPositionPointerIsNotChanged_Test )
{
    // [Preparation]
    const puint_z EXPECTED_POSITON = 2;
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(4);
    const int ANY_CONTENT = 0;
    stream.Write(&ANY_CONTENT, 0, sizeof(int));
    stream.SetPosition(EXPECTED_POSITON);

    // [Execution]
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);

    // [Verification]
    puint_z uPosition = writer.GetStream().GetPosition();
    BOOST_CHECK_EQUAL(uPosition, EXPECTED_POSITON);
}

/// <summary>
/// Checks that the text is written when using ASCII encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ISO88591;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size lower than the length of the text.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingBatchSizeLowerThanTextLength_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const string_z EXPECTED_TEXT("texttexttexttext\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z BATCH_SIZE = 4U;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size that produces some character to be divided into two halfs.
/// </summary>
ZTEST_CASE ( WriteLine_TextIsWrittenWhenUsingBatchSizeThatDividesCharactersInTwoHalfs_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const string_z EXPECTED_TEXT("texttexttexttext\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16;
    const puint_z BATCH_SIZE = 9U;
    MemoryStream<> stream(40);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), writer.GetStreamEncoding());
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that only the new line separator is written when the input text is empty.
/// </summary>
ZTEST_CASE ( WriteLine_OnlyNewLineSeparatorIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT = string_z::GetEmpty();
    const string_z EXPECTED_TEXT("\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using CR.
/// </summary>
ZTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingCR_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\r");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    const ENewLineCharacters NEW_LINE_SEPARATOR = ENewLineCharacters::E_CR;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using LF.
/// </summary>
ZTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingLF_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    const ENewLineCharacters NEW_LINE_SEPARATOR = ENewLineCharacters::E_LF;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that new line seperator is which expected when using CR-LF.
/// </summary>
ZTEST_CASE ( WriteLine_NewLineSeparatorIsCorrectWhenUsingCRLF_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\r\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    const ENewLineCharacters NEW_LINE_SEPARATOR = ENewLineCharacters::E_CRLF;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    writer.SetNewLineSeparator(NEW_LINE_SEPARATOR);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
ZTEST_CASE ( WriteLine_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    const puint_z ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
ZTEST_CASE ( WriteLine_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text\ntext\n");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteLine(INPUT_TEXT);
    writer.WriteLine(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
ZTEST_CASE ( WriteLine_AssertionFailsWhenBatchSizeIsZero_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z BATCH_SIZE = 0;
    MemoryStream<> stream(1);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.WriteLine(INPUT_TEXT, BATCH_SIZE);
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
/// Checks that the text is written when using ASCII encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ISO88591;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size lower than the length of the text.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingBatchSizeLowerThanTextLength_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const string_z EXPECTED_TEXT("texttexttexttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z BATCH_SIZE = 4U;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using a batch size that produces some character to be divided into two halfs.
/// </summary>
ZTEST_CASE ( Write_TextIsWrittenWhenUsingBatchSizeThatDividesCharactersInTwoHalfs_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const string_z EXPECTED_TEXT("texttexttexttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16;
    const puint_z BATCH_SIZE = 9U;
    MemoryStream<> stream(40);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT, BATCH_SIZE);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), writer.GetStreamEncoding());
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that nothing is written when the input text is empty.
/// </summary>
ZTEST_CASE ( Write_NothingIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT = string_z::GetEmpty();
    const string_z EXPECTED_TEXT("");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
ZTEST_CASE ( Write_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    const puint_z ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
ZTEST_CASE ( Write_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("texttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.Write(INPUT_TEXT);
    writer.Write(INPUT_TEXT);
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the batch size equals zero.
/// </summary>
ZTEST_CASE ( Write_AssertionFailsWhenBatchSizeIsZero_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const string_z INPUT_TEXT("texttexttexttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    const puint_z BATCH_SIZE = 0;
    MemoryStream<> stream(1);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.Write(INPUT_TEXT, BATCH_SIZE);
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
/// Checks that the BOM is written when usint the UTF-16 LE encoding.
/// </summary>
ZTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_z EXPECTED_TEXT = string_z(char_z(0xFEFF));
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-16 BE encoding.
/// </summary>
ZTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_z EXPECTED_TEXT = string_z(char_z(0xFEFF));
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16BE;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-32 LE encoding.
/// </summary>
ZTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_z EXPECTED_TEXT = string_z(char_z(0xFEFF));
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32LE;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the BOM is written when usint the UTF-32 BE encoding.
/// </summary>
ZTEST_CASE ( WriteBOM_BOMIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_z EXPECTED_TEXT = string_z(char_z(0xFEFF));
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32BE;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
ZTEST_CASE ( WriteBOM_PositionIsMovedForward_Test )
{
    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    const puint_z ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer.WriteBOM();
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
ZTEST_CASE ( WriteBOM_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_z EXPECTED_TEXT = string_z(char_z(0xFEFF)) + char_z(0xFEFF);
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer.WriteBOM();
    writer.WriteBOM();
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the encoding is neither UTF16 nor UTF32.
/// </summary>
ZTEST_CASE ( WriteBOM_AssertionFailsWhenEncodingIsNotUTF16NorUTF32_Test )
{
    using Common::Exceptions::AssertException;

    // [Preparation]
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(1);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        writer.WriteBOM();
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
/// Checks that the text is written when using ASCII encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingASCII_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using ISO-8859-1 encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingISO88591_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ISO88591;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-8 encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF8_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), EXPECTED_TEXT.GetLength(), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 LE encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF16LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-16 BE encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF16BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF16BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 2U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 LE encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF32LE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32LE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the text is written when using UTF-32 BE encoding.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_TextIsWrittenWhenUsingEncodingUTF32BE_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF32BE;
    MemoryStream<> stream(12);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 4U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that nothing is written when the input text is empty.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_NothingIsWrittenWhenTextIsEmpty_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT = string_z::GetEmpty();
    const string_z EXPECTED_TEXT("");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
}

/// <summary>
/// Checks that the pointer position of the stream is moved forward.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_PositionIsMovedForward_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_UTF8;
    MemoryStream<> stream(6);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    const puint_z ORIGINAL_POSITION = stream.GetPosition();
    
    // [Execution]
    writer << INPUT_TEXT;
    
    // [Verification]
    puint_z uPosition = stream.GetPosition();
    BOOST_CHECK(uPosition > ORIGINAL_POSITION);
}

/// <summary>
/// Checks that a trailing zero is not added after the text.
/// </summary>
ZTEST_CASE ( OperatorShiftLeft_NoTrailingZeroIsAdded_Test )
{
    // [Preparation]
    const string_z INPUT_TEXT("text");
    const string_z EXPECTED_TEXT("texttext");
    const ETextEncoding INPUT_ENCODING = ETextEncoding::E_ASCII;
    MemoryStream<> stream(18);
    TextStreamWriter< MemoryStream<> > writer(stream, INPUT_ENCODING);
    
    // [Execution]
    writer << INPUT_TEXT;
    writer << INPUT_TEXT;
    
    // [Verification]
    stream.SetPosition(0);
    string_z strResult(rcast_z(stream.GetCurrentPointer(), i8_z*), 1U * (EXPECTED_TEXT.GetLength()), INPUT_ENCODING);
    BOOST_CHECK(strResult == EXPECTED_TEXT);
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
    TextStreamWriter< MemoryStream<> > reader(stream, INPUT_ENCODING);
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


// End - Test Suite: TextStreamWriter
ZTEST_SUITE_END()
