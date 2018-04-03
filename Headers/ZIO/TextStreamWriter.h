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

#ifndef __TEXTSTREAMWRITER__
#define __TEXTSTREAMWRITER__


#include "ZIO/IOModuleDefinitions.h"

#include "ZIO/ENewLineCharacters.h"
#include "ZCommon/DataTypes/SInteger.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"



namespace z
{

/// <summary>
/// Component that encodes text and sends it to a stream.
/// </summary>
/// <typeparam name="StreamT">The type of the stream to write to (memory stream, file stream, etc.).</typeparam>
template<class StreamT>
class TextStreamWriter
{
    // CONSTANTS
    // ---------------
protected:
    
    /// <summary>
    /// The default size (in bytes) of the batches used in the write operation.
    /// </summary>
    static const puint_z _COPY_BATCH_SIZE = 4096U; // 4096 bytes is apparently the most common cluster size in a file system. It should be tuned to improve performance


    // CONSTRUCTORS
    // ---------------
public:
    
    /// <summary>
    /// Constructor that receives a stream and the encoding to be used when writing to it.
    /// </summary>
    /// <remarks>
    /// The default new line character is a LF (line feed, a '\n' character).<br/>
    /// The stream's write pointer is not modified by this operation.
    /// </remarks>
    /// <param name="stream">[IN] The stream to write to.</param>
    /// <param name="eStreamEncoding">[IN] The encoding of the text to be written to the stream. The UTF-16 and UTF-32 encodings are 
    /// changed to their corresponding version depending on the local machine's endianness (either LE or BE).</param>
    TextStreamWriter(StreamT& stream, const ETextEncoding &eStreamEncoding) :
                                                                                m_stream(stream),
                                                                                m_eEncoding(eStreamEncoding),
                                                                                m_eNewLine(ENewLineCharacters::E_LF),
                                                                                m_arNewLineCharacters(null_z, 0),
                                                                                m_uCharSize(0)
    {
        // Encoding with no endianness is translated to encoding with the local machine's endianness
        if(eStreamEncoding == ETextEncoding::E_UTF16)
            m_eEncoding = string_z::GetLocalEncodingUTF16();
        else if(eStreamEncoding == ETextEncoding::E_UTF32)
            m_eEncoding = string_z::GetLocalEncodingUTF32();

        // Sets the size of characters in the given encoding, in bytes
        switch(m_eEncoding)
        {
        case ETextEncoding::E_ASCII:
        case ETextEncoding::E_ISO88591:
        case ETextEncoding::E_UTF8:
            m_uCharSize = 1U;
            break;
        case ETextEncoding::E_UTF16LE:
        case ETextEncoding::E_UTF16BE:
            m_uCharSize = 2U;
            break;
        case ETextEncoding::E_UTF32LE:
        case ETextEncoding::E_UTF32BE:
            m_uCharSize = 4U;
            break;
        default:
            break;
        }

        // Sets the characters selected by default that limit the end of a line
        this->SetNewLineSeparator(m_eNewLine);
    }

private:

    // Hidden
    TextStreamWriter(const TextStreamWriter&);


    // DESTRUCTOR
    // ---------------
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    ~TextStreamWriter()
    {
        delete[] m_arNewLineCharacters.Get();
    }


    // METHODS
    // ---------------
private:

    // Hidden
    TextStreamWriter& operator=(const TextStreamWriter&);

public:
    
    /// <summary>
    /// Writes all the characters from the input text to the stream at the current position and adds a new line separator afterwards.
    /// </summary>
    /// <remarks>
    /// Use the SetNewLineSeparator method to choose the sequence of characters that compound the new line separator.<br/>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the new line characters.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, only the new line separator will be written.</param>
    /// <param name="uBatchSize">[Optional][IN] The size, in bytes, of every written batch. It must be greater than zero. It may affect the performance of the operation.</param>
    void WriteLine(const string_z &strInput, const puint_z uBatchSize=TextStreamWriter::_COPY_BATCH_SIZE)
    {
        Z_ASSERT_ERROR(uBatchSize > 0, "The number of bytes per batch must be greater than zero.");

        this->Write(strInput, uBatchSize);
        m_stream.Write(m_arNewLineCharacters.Get(), 0, m_arNewLineCharacters.GetSize() - m_uCharSize); // Quits the last character ('\0')
    }

    /// <summary>
    /// Writes all the characters from the input text to the stream at the current position.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the last character written.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, nothing will be done.</param>
    /// <param name="uBatchSize">[Optional][IN] The size, in bytes, of every written batch. It must be greater than zero. It may affect the performance of the operation.</param>
    void Write(const string_z &strInput, const puint_z uBatchSize=TextStreamWriter::_COPY_BATCH_SIZE)
    {
        Z_ASSERT_ERROR(uBatchSize > 0, "The number of bytes per batch must be greater than zero.");

        if(!strInput.IsEmpty())
        {
            ArrayResult<i8_z> arEncodedString = strInput.ToBytes(m_eEncoding);

            // The stream is copied batch by batch
            const puint_z NUMBER_OF_BATCHES = (arEncodedString.GetSize() - m_uCharSize) / uBatchSize; // Quits the last character ('\0')

            for(puint_z i = 0; i < NUMBER_OF_BATCHES; ++i)
                m_stream.Write(arEncodedString.Get(), i * uBatchSize, uBatchSize);

            const puint_z REST_OF_BYTES = (arEncodedString.GetSize() - m_uCharSize) % uBatchSize; // Quits the last character ('\0')

            if(REST_OF_BYTES != 0)
                m_stream.Write(arEncodedString.Get(), NUMBER_OF_BATCHES * uBatchSize, REST_OF_BYTES);
        }
    }
        
    /// <summary>
    /// Writes a Unicode BOM (U+FEFF Binary Order Mark) to the string at the current position.
    /// </summary>
    /// <remarks>
    /// The byte order of the character depends on the selected encoding's endianness.<br/>
    /// This method should be called only when using either UTF-16 or UTF-32 encodings.
    /// </remarks>
    void WriteBOM()
    {
        Z_ASSERT_WARNING(m_eEncoding == ETextEncoding::E_UTF16LE ||
                         m_eEncoding == ETextEncoding::E_UTF16BE ||
                         m_eEncoding == ETextEncoding::E_UTF32LE ||
                         m_eEncoding == ETextEncoding::E_UTF32BE,
                         string_z("Current text encoding (") + m_eEncoding.ToString() + ") does not use BOMs (Byte Order Marks).");

        static const u16_z BOM_UTF16 = 0xFEFF;
        static const string_z BOM_STRING(rcast_z(&BOM_UTF16, const i8_z*), sizeof(u16_z), string_z::GetLocalEncodingUTF16());

        ArrayBasic<i8_z> arBOM(null_z, 0);

        if(m_eEncoding == ETextEncoding::E_UTF16LE ||
           m_eEncoding == ETextEncoding::E_UTF16BE ||
           m_eEncoding == ETextEncoding::E_UTF32LE ||
           m_eEncoding == ETextEncoding::E_UTF32BE)
        {
            ArrayResult<i8_z> arResult = BOM_STRING.ToBytes(m_eEncoding);
            arResult.Detach();
            arBOM = arResult;
        }

        if(arBOM.GetSize() > 0)
            m_stream.Write(arBOM.Get(), 0, arBOM.GetSize() - m_uCharSize); // Quits the last character ('\0')

        delete[] arBOM.Get();
    }

    /// <summary>
    /// Bitwise left shift operator that writes all the characters from the input text to the stream at the current position.
    /// </summary>
    /// <remarks>
    /// If there is a leading BOM character in the input text, it will be included in the output.<br/>
    /// If there is no leading BOM character in the input text, it will not be added to the output. Use the WriteBOM method to insert a BOM character.<br/>
    /// If there is a trailing zero in the sequence of characters, it will not be written.<br/>
    /// The write pointer of the stream will be moved to the position right after the last character written.<br/>
    /// It only calls Write using the default batch size.
    /// </remarks>
    /// <param name="strInput">[IN] The input string whose characters will be written. If it is empty, nothing will be done.</param>
    /// <returns>
    /// A reference to the text stream writer instance.
    /// </returns>
    TextStreamWriter& operator<<(const string_z &strInput)
    {
        this->Write(strInput);
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
        static const string_z NEW_LINE_CR("\r");
        static const string_z NEW_LINE_LF("\n");
        static const string_z NEW_LINE_CRLF("\r\n");

        switch(eNewLine)
        {
        case ENewLineCharacters::E_CR:
            {
                ArrayResult<i8_z> arResult = NEW_LINE_CR.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        case ENewLineCharacters::E_LF:
            {
                ArrayResult<i8_z> arResult = NEW_LINE_LF.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        case ENewLineCharacters::E_CRLF:
            {
                ArrayResult<i8_z> arResult = NEW_LINE_CRLF.ToBytes(m_eEncoding);
                arResult.Detach();
                m_arNewLineCharacters = arResult;;
                break;
            }
        default:
            break;
        }
        
        m_eNewLine = eNewLine;
    }
    
    /// <summary>
    /// Gets the encoding of the text contained in the stream. It is set when the writer is created.
    /// </summary>
    /// <returns>
    /// The text encoding.
    /// </returns>
    ETextEncoding GetStreamEncoding() const
    {
        return m_eEncoding;
    }

    /// <summary>
    /// Gets the stream being written.
    /// </summary>
    /// <returns>
    /// A reference to the stream being written.
    /// </returns>
    StreamT& GetStream() const
    {
        return m_stream;
    }


    // ATTRIBUTES
    // ---------------
protected:
    
    /// <summary>
    /// The stream being written.
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
    ArrayBasic<i8_z> m_arNewLineCharacters;
        
    /// <summary>
    /// The character size depending on the text encoding.
    /// </summary>
    puint_z m_uCharSize;
};


} // namespace z

#endif // __TEXTSTREAMWRITER__
