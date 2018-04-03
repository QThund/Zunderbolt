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

#ifndef __TEXTSTREAMREADER__
#define __TEXTSTREAMREADER__


#include "ZIO/IOModuleDefinitions.h"

#include "ZIO/ENewLineCharacters.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/DataTypes/SInteger.h"



namespace z
{

/// <summary>
/// Component that parses a stream and interprets its bytes as text using a concrete encoding.
/// </summary>
/// <typeparam name="StreamT">The type of the stream to be read (memory stream, file stream, etc.).</typeparam>
template<class StreamT>
class TextStreamReader
{
    // CONSTANTS
    // ---------------
protected:

    /// <summary>
    /// The sequence of characters for a CRLF new line separator.
    /// </summary>
    static const string_z _NEWLINE_CRLF;
    
    /// <summary>
    /// The sequence of characters for a CR new line separator.
    /// </summary>
    static const string_z _NEWLINE_CR;
    
    /// <summary>
    /// The sequence of characters for a LF new line separator.
    /// </summary>
    static const string_z _NEWLINE_LF;
    
    /// <summary>
    /// The size of a character when using either ISO-8859-1, ASCII or UTF8 encoding, in bytes.
    /// </summary>
    static const puint_z _CHAR_SIZE_ISO88591_ASCII_UTF8;
    
    /// <summary>
    /// The size of a character when using UTF16 encoding, in bytes.
    /// </summary>
    static const puint_z _CHAR_SIZE_UTF16;
    
    /// <summary>
    /// The size of a character when using UTF32 encoding, in bytes.
    /// </summary>
    static const puint_z _CHAR_SIZE_UTF32;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives a stream and stores a reference to it.
    /// </summary>
    /// <remarks>
    /// The encoding of the text in the stream is deduced using the following steps:<br/>
    /// 1- Supossing 2 bytes per character, if the first character is a BOM, the text has UTF16 encoding. The endianness is deduced from the value of the BOM.<br/>
    /// 2- Supossing 4 bytes per character, if the first character is a BOM, the text has UTF32 encoding. The endianness is deduced from the value of the BOM.<br/>
    /// 3- When the text does not start with a BOM, it is supposed to have UTF8 encoding by default.<br/>
    /// <br/>
    /// The default new line character is an LF (line feed, a '\n' character).<br/>
    /// The stream's read pointer is not modified by this operation.
    /// </remarks>
    /// <param name="stream">[IN] The stream to be read.</param>
    TextStreamReader(StreamT& stream) : m_stream(stream),
                                         m_eEncoding(ETextEncoding::E_UTF8),
                                         m_eNewLine(ENewLineCharacters::E_LF),
                                         m_strNewLine(TextStreamReader::_NEWLINE_LF),
                                         m_uCharSize(TextStreamReader::_CHAR_SIZE_ISO88591_ASCII_UTF8)
    {
        m_eEncoding = this->_DetectEncoding(stream);
        m_uCharSize = this->_GetCharSizeForEncoding(m_eEncoding);
        this->SetNewLineSeparator(m_eNewLine);
    }
    
    /// <summary>
    /// Constructor that receives a stream and its encoding.
    /// </summary>
    /// <remarks>
    /// The default new line character is an LF (line feed, a '\n' character).<br/>
    /// The stream's read pointer is not modified by this operation.
    /// </remarks>
    /// <param name="stream">[IN] The stream to be read.</param>
    /// <param name="eStreamEncoding">[IN] The encoding of the text contained in the stream.</param>
    TextStreamReader(StreamT& stream, const ETextEncoding &eStreamEncoding) :
                                                                                m_stream(stream),
                                                                                m_eEncoding(eStreamEncoding),
                                                                                m_eNewLine(ENewLineCharacters::E_LF),
                                                                                m_strNewLine(TextStreamReader::_NEWLINE_LF),
                                                                                m_uCharSize(_GetCharSizeForEncoding(eStreamEncoding))
    {
        this->SetNewLineSeparator(m_eNewLine);
    }



private:

    // Hidden
    TextStreamReader(const TextStreamReader&);


    // METHODS
    // ---------------
private:

    // Hidden
    TextStreamReader& operator=(const TextStreamReader&);

protected:
    
    /// <summary>
    /// Obtains the size of the characters, in bytes, of a given text encoding.
    /// </summary>
    /// <param name="eTextEncoding">[IN] The text encoding.</param>
    /// <returns>
    /// The size of an encoded character, in bytes.
    /// </returns>
    static puint_z _GetCharSizeForEncoding(const ETextEncoding &eTextEncoding)
    {
        puint_z uCharSize = 0;

        switch(eTextEncoding)
        {
        case ETextEncoding::E_ASCII:
        case ETextEncoding::E_ISO88591:
        case ETextEncoding::E_UTF8:
            uCharSize = TextStreamReader::_CHAR_SIZE_ISO88591_ASCII_UTF8;
            break;
        case ETextEncoding::E_UTF16:
        case ETextEncoding::E_UTF16LE:
        case ETextEncoding::E_UTF16BE:
            uCharSize = TextStreamReader::_CHAR_SIZE_UTF16;
            break;
        case ETextEncoding::E_UTF32:
        case ETextEncoding::E_UTF32LE:
        case ETextEncoding::E_UTF32BE:
            uCharSize = TextStreamReader::_CHAR_SIZE_UTF32;
            break;
        default:
            break;
        }

        return uCharSize;
    }
        
    /// <summary>
    /// Deduces the encoding of the text contained in a stream.
    /// </summary>
    /// <remarks>
    /// The encoding of the text in the stream is deduced using the following steps:<br/>
    /// 1- Supossing 2 bytes per character, if the first character is a BOM, the text has UTF16 encoding. The endianness is deduced from the value of the BOM.<br/>
    /// 2- Supossing 4 bytes per character, if the first character is a BOM, the text has UTF32 encoding. The endianness is deduced from the value of the BOM.<br/>
    /// 3- When the text does not start with a BOM, it is supposed to have UTF8 encoding by default.<br/>
    /// <br/>
    /// The stream's read pointer is not modified by this operation.
    /// </remarks>
    /// <param name="stream">[IN] The stream whose encoding is to be deduced.</param>
    /// <returns>
    /// The encoding of the text.
    /// </returns>
    static ETextEncoding _DetectEncoding(StreamT &stream)
    {
        ETextEncoding eEncoding = ETextEncoding::E_UTF8; // By default

        if(stream.GetLength() >= 2U)
        {
            static const u8_z arFFFE[] = {0xFF, 0xFE}; // BOM Little endian
            static const u8_z arFEFF[] = {0xFE, 0xFF}; // BOM Big endian

            const puint_z ORIGINAL_POSITION = stream.GetPosition();

            u8_z arBOM[4];
            stream.SetPosition(0);
            stream.Read(arBOM, 0, 2U);
            
            if(arBOM[0] == arFFFE[0] && arBOM[1] == arFFFE[1])
                eEncoding = ETextEncoding::E_UTF16LE;
            else if(arBOM[0] == arFEFF[0] && arBOM[1] == arFEFF[1])
                eEncoding = ETextEncoding::E_UTF16BE;

            if(stream.GetLength() >= 4U)
            {
                stream.Read(arBOM, 2U, 2U);

                if(arBOM[0] == arFFFE[0] && arBOM[1] == arFFFE[1] && arBOM[2] == 0 && arBOM[3] == 0)
                    eEncoding = ETextEncoding::E_UTF32LE;
                else if(arBOM[0] == 0 && arBOM[1] == 0 && arBOM[2] == arFEFF[0] && arBOM[3] == arFEFF[1])
                    eEncoding = ETextEncoding::E_UTF32BE;
            }

            stream.SetPosition(ORIGINAL_POSITION); // Sets the pointer back to the original position
        }

        return eEncoding;
    }

public:
    
    /// <summary>
    /// Reads a given amount of characters from the stream and appends them to a string.
    /// </summary>
    /// <remarks>
    /// Take into account that every character may occupy more than one byte in the stream, depending on the text encoding.<br/>
    /// If there is a leading BOM character, it will be included in the output.<br/>
    /// If there is a trailing zero in the sequence of characters, it will be read too.<br/>
    /// Note that the read pointer of the stream is not restored after this operation.
    /// </remarks>
    /// <param name="strOutput">[OUT] The output string to which the read characters will be appended.</param>
    /// <param name="uNumberOfChars">[IN] The number of characters to be read. It must be greater than zero.</param>
    void ReadChars(string_z &strOutput, const puint_z uNumberOfChars)
    {
        const puint_z OUTPUT_STRING_BYTELENGTH = uNumberOfChars * m_uCharSize;
        this->ReadBlock(strOutput, OUTPUT_STRING_BYTELENGTH);
    }
    
    /// <summary>
    /// Reads all the characters from the current position to either the first new line character/s or the end of the stream, and appends
    /// them to a string.
    /// </summary>
    /// <remarks>
    /// Use the SetNewLineSeparator method to choose the sequence of characters that compound the new line separator.<br/>
    /// If the first character read (depends on the read pointer of the stream) is a new line separator, nothing will be appended.<br/>
    /// If there is a leading BOM character, it will be included in the output.<br/>
    /// If there is a trailing zero in the sequence of characters, it will be read too.<br/>
    /// The read pointer of the stream will be moved to the position right after the new line characters.
    /// </remarks>
    /// <param name="strOutput">[OUT] The output string to which the read characters will be appended.</param>
    void ReadLine(string_z &strOutput)
    {
        Z_ASSERT_ERROR(m_stream.GetPosition() != m_stream.GetLength(), "The end of the stream was already reached.");

        // Trying with blocks of 256 bytes
        static const puint_z BATCH_SIZE = 256U;

        puint_z uBytesToMoveBackToLastValidChar = 0;
        string_z strBatch;
        i8_z arBytes[BATCH_SIZE];
        int nNewLinePos = string_z::PATTERN_NOT_FOUND;
        bool bEnoughBytesForAnotherBatch = m_stream.GetPosition() + BATCH_SIZE < m_stream.GetLength();

        // Traverses the string until it finds either a new line separator or the end of the stream, adding the read text batch by batch
        while(nNewLinePos == string_z::PATTERN_NOT_FOUND && bEnoughBytesForAnotherBatch)
        {
            strOutput.Append(strBatch);

            m_stream.Read(arBytes, 0, BATCH_SIZE);

            // When using Unicode encoding forms (UTF8 and UTF16), it is possible that the batch ends in the middle of the code units that compound a character
            // For example, if the string contains tha character ǂ (0+01C2 LATIN LETTER ALVEOLAR CLICK), which is described by the code units C7 82 (UTF8), and the current batch
            // only contains the first code unit (C7), the character will not be valid. So, it's necessary to move back to find the last character that has all its code units in 
            // the batch and then start reading from there in the next iteration
            uBytesToMoveBackToLastValidChar = TextStreamReader::_GetBytesToPreviousCharacter(arBytes, BATCH_SIZE, m_eEncoding);
            m_stream.MoveBackward(uBytesToMoveBackToLastValidChar);

            strBatch = string_z(arBytes, BATCH_SIZE - uBytesToMoveBackToLastValidChar, m_eEncoding);

            // It's possible that the separator is divided in two pieces, one part at the end of a batch, and the other at the beginning of the next batch
            if(m_eNewLine == ENewLineCharacters::E_CRLF && strBatch[strBatch.GetLength() - 1U] == TextStreamReader::_NEWLINE_CR[0])
            {
                m_stream.MoveBackward(1U);
                strBatch = strBatch.Substring(0, strBatch.GetLength() - 2U);
            }

            nNewLinePos = strBatch.IndexOf(m_strNewLine, EComparisonType::E_BinaryCaseSensitive);
            bEnoughBytesForAnotherBatch = m_stream.GetPosition() + BATCH_SIZE < m_stream.GetLength();
        }

        if(nNewLinePos != 0)
        {
            // The end of the stream was reached, it gets the rest of the text
            if(!bEnoughBytesForAnotherBatch && nNewLinePos == string_z::PATTERN_NOT_FOUND)
            {
                strOutput.Append(strBatch);

                const puint_z REMAINING_BYTES = m_stream.GetLength() - m_stream.GetPosition();
                m_stream.Read(arBytes, 0, REMAINING_BYTES);
                strBatch = string_z(arBytes, REMAINING_BYTES, m_eEncoding);

                // Checks if there is a new line separator in the remaining text
                nNewLinePos = strBatch.IndexOf(m_strNewLine, EComparisonType::E_BinaryCaseSensitive);

                if(nNewLinePos != 0)
                {
                    if(nNewLinePos != string_z::PATTERN_NOT_FOUND)
                    {
                        // Found new line separator in the remaining text
                        strOutput.Append(strBatch.Substring(0, nNewLinePos - 1U));
                        m_stream.MoveBackward((strBatch.GetLength() - nNewLinePos - m_strNewLine.GetLength()) * m_uCharSize); // Moves the pointer to the position after the separator
                    }
                    else
                    {
                        // End of the stream
                        strOutput.Append(strBatch);
                    }
                }
                else
                {
                    m_stream.MoveBackward((strBatch.GetLength() - m_strNewLine.GetLength()) * m_uCharSize); // Moves the pointer to the position after the separator
                }
            }
            else
            {
                // New line separator found, it gets the text from the current position to the separator, not included
                strOutput.Append(strBatch.Substring(0, nNewLinePos - 1U));
                m_stream.MoveBackward((strBatch.GetLength() - nNewLinePos - m_strNewLine.GetLength()) * m_uCharSize); // Moves the pointer to the position after the separator
            }
        }
        else
        {
            m_stream.MoveBackward((strBatch.GetLength() - m_strNewLine.GetLength()) * m_uCharSize); // Moves the pointer to the position after the separator
        }
    }
    
private:
    
    /// <summary>
    /// Calculates how many bytes are there between the last complete character (which has all its code units together) and the end of the buffer.
    /// This method is used only for text encodings in which a character can be compound of more than 1 code unit.
    /// </summary>
    /// <param name="arBytes">[IN] The buffer that contains the character sequence. It may have incomplete characters at the end.</param>
    /// <param name="uBufferSize">[IN] The size of the buffer, in bytes.</param>
    /// <param name="eEncoding">[IN] The encoding of the text contained in the buffer.</param>
    static puint_z _GetBytesToPreviousCharacter(i8_z* arBytes, 
                                                       const puint_z uBufferSize, 
                                                       const ETextEncoding &eEncoding)
    {
        puint_z uResult = 0;

        if(eEncoding == ETextEncoding::E_UTF8)
        {
            puint_z uPosition = uBufferSize - 1U; // Last 8 bits code unit
            u8_z* arCodeunits = rcast_z(arBytes, u8_z*);

            while((arCodeunits[uPosition] >> 6U) == 0x02) // Starts with 10xxxxxx
            {
                --uPosition;
                ++uResult;
            }

            // If there are 3 dependent code units, it means the 4 code units are present so the character is complete
            if(uResult == 3U)
                uResult = 0;

            // One position more, to the leading code unit, if any
            if(uResult != 0)
                ++uResult;
        }
        else if(eEncoding == ETextEncoding::E_UTF16 || eEncoding == ETextEncoding::E_UTF16LE || eEncoding == ETextEncoding::E_UTF16BE)
        {
            static const u16_z MINIMUM_HIGH_SURROGATE = 0xD800;
            static const u16_z MAXIMUM_HIGH_SURROGATE = 0xDBFF;

            u16_z uLastCodeunit = rcast_z(arBytes, u16_z*)[uBufferSize / 2U - 1U]; // Last 16 bits code unit

            if(eEncoding != string_z::GetLocalEncodingUTF16())
               uLastCodeunit = SInteger::SwapEndianess(uLastCodeunit);

            // If it's a high surrogate
            if(uLastCodeunit >= MINIMUM_HIGH_SURROGATE && uLastCodeunit <= MAXIMUM_HIGH_SURROGATE)
                uResult += 2U;
        }

        return uResult;
    }

public:

    /// <summary>
    /// Reads all the characters from the current position to the end of the stream and appends them to a string.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character, it will be included in the output.<br/>
    /// If there is a trailing zero in the sequence of characters, it will be read too.<br/>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// This method does the same as the bitwise right shift operator (">>"). It's provided with the only purpose of improving readability 
    /// and/or usability in certain scenarios.
    /// </remarks>
    /// <param name="strOutput">[OUT] The output string to which the read characters will be appended.</param>
    void ReadToEnd(string_z &strOutput)
    {
        const puint_z OUTPUT_STRING_BYTELENGTH = m_stream.GetLength() - m_stream.GetPosition();
        this->ReadBlock(strOutput, OUTPUT_STRING_BYTELENGTH);
    }
    
    /// <summary>
    /// Reads an amount of bytes from the current position, parses them as text and appends them to a string.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character, it will be included in the output.<br/>
    /// If there is a trailing zero in the sequence of characters, it will be read too.<br/>
    /// When using UTF8 or UTF16 encodings, characters can be compound of more than one code unit; if the read block is not big enough to contain all 
    /// the code units of a character, it will not be added to the result. The read pointer of the stream will point to the first code unit of such character 
    /// after this operation (which means that the pointer may be moved backward up to 3 positions).<br/>
    /// In normal circumstances, the read pointer of the stream will point to the position of the character right after the read block.
    /// </remarks>
    /// <param name="strOutput">[OUT] The output string to which the read characters will be appended.</param>
    /// <param name="uNumberOfBytes">[IN] The amount of bytes to read. It must be greater than zero and should be multiple of the character size for 
    /// the current encoding.</param>
    void ReadBlock(string_z &strOutput, const puint_z uNumberOfBytes)
    {
        Z_ASSERT_ERROR(uNumberOfBytes > 0, "The number of bytes to read must be greater than zero.");
        Z_ASSERT_WARNING(uNumberOfBytes % m_uCharSize == 0, string_z("The number of bytes to read should be multiple of the character size for the current encoding (") + string_z::FromInteger(m_uCharSize)  + ").");

        i8_z* arBytes = new i8_z[uNumberOfBytes];

        m_stream.Read(arBytes, 0, uNumberOfBytes);

        // If the character is not totally contained in the block, it is ignored
        puint_z uLastBytesToIgnore = this->_GetBytesToPreviousCharacter(arBytes, uNumberOfBytes, m_eEncoding);
        m_stream.MoveBackward(uLastBytesToIgnore);

        string_z strTextToAppend(arBytes, uNumberOfBytes - uLastBytesToIgnore, m_eEncoding);

        delete[] arBytes;

        strOutput.Append(strTextToAppend);
    }
    
    /// <summary>
    /// Bitwise right shift operator that reads all the characters from the current position to the end of the stream and appends them to a string.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character, it will be included in the output.<br/>
    /// If there is a trailing zero in the sequence of characters, it will be read too.<br/>
    /// Note that the read pointer of the stream is not restored after this operation.<br/>
    /// This method just calls the ReadToEnd method.
    /// </remarks>
    /// <param name="strOutput">[OUT] The output string to which the read characters will be appended.</param>
    /// <returns>
    /// A reference to the stream.
    /// </returns>
    TextStreamReader& operator>>(string_z &strOutput)
    {
        this->ReadToEnd(strOutput);
        return *this;
    }


    // PROPERTIES
    // ---------------
public:
    
    /// <summary>
    /// Gets the chosen new line characters utilized to separate lines.
    /// </summary>
    /// <returns>
    /// The chosen new line separator.
    /// </returns>
    ENewLineCharacters GetNewLineSeparator() const
    {
        return m_eNewLine;
    }

    /// <summary>
    /// Sets the chosen new line characters utilized to separate lines.
    /// </summary>
    /// <param name="eNewLine">[IN] The new line separator.</param>
    void SetNewLineSeparator(const ENewLineCharacters &eNewLine)
    {
        switch(eNewLine)
        {
        case ENewLineCharacters::E_LF:
            m_strNewLine = TextStreamReader::_NEWLINE_LF;
            break;
        case ENewLineCharacters::E_CRLF:
            m_strNewLine = TextStreamReader::_NEWLINE_CRLF;
            break;
        case ENewLineCharacters::E_CR:
            m_strNewLine = TextStreamReader::_NEWLINE_CR;
            break;
        default:
            break;
        }

        m_eNewLine = eNewLine;
    }
    
    /// <summary>
    /// Gets the encoding of the text contained in the stream. It is set when the reader is created.
    /// </summary>
    /// <returns>
    /// The text encoding.
    /// </returns>
    ETextEncoding GetStreamEncoding() const
    {
        return m_eEncoding;
    }

    /// <summary>
    /// Gets the stream being read.
    /// </summary>
    /// <returns>
    /// A reference to the stream being read.
    /// </returns>
    StreamT& GetStream() const
    {
        return m_stream;
    }


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The stream being read.
    /// </summary>
    StreamT& m_stream;
    
    /// <summary>
    /// The encoding of the text.
    /// </summary>
    ETextEncoding m_eEncoding;
    
    /// <summary>
    /// The chosen new line separator.
    /// </summary>
    ENewLineCharacters m_eNewLine;
    
    /// <summary>
    /// The characters that compound the new line separator.
    /// </summary>
    string_z m_strNewLine;
    
    /// <summary>
    /// The character size depending on the text encoding.
    /// </summary>
    puint_z m_uCharSize;

};


// ATTRIBUTE INITIALIZATION
// ----------------------------
template<class StreamT>
const string_z TextStreamReader<StreamT>::_NEWLINE_CRLF("\r\n");

template<class StreamT>
const string_z TextStreamReader<StreamT>::_NEWLINE_CR("\r");

template<class StreamT>
const string_z TextStreamReader<StreamT>::_NEWLINE_LF("\n");

template<class StreamT>
const puint_z TextStreamReader<StreamT>::_CHAR_SIZE_ISO88591_ASCII_UTF8 = 1U;

template<class StreamT>
const puint_z TextStreamReader<StreamT>::_CHAR_SIZE_UTF16 = 2U;

template<class StreamT>
const puint_z TextStreamReader<StreamT>::_CHAR_SIZE_UTF32 = 4U;


} // namespace z

#endif // __TEXTSTREAMREADER__
