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

#ifndef __STRINGUNICODE__
#define __STRINGUNICODE__

#include "ZCommon/CommonModuleDefinitions.h"

#include <unicode/unistr.h>
#include <unicode/schriter.h>
#include <unicode/normalizer2.h>
#include <unicode/coll.h>
#include <unicode/stsearch.h>
#include <unicode/numfmt.h>
#include <sstream>
#include <math.h>

#include "ZCommon/DataTypes/CharUnicode.h"
#include "ZCommon/DataTypes/ArrayResult.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/DataTypes/ENormalizationForm.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "ZCommon/Assertions.h"


namespace z
{

/// <summary>
/// Represents text formed by a sequence of Unicode characters.
/// </summary>
/// <remarks>
/// Internally, characters are encoded in UTF-16. This may change in the future.<br/>
/// Instances of this class are mutable, this means, the same instance can take different values during its lifecycle.<br/>
/// Instances of this class are not thread-safe.
/// </remarks>
class Z_COMMON_MODULE_SYMBOLS StringUnicode
{
    // INTERNAL CLASSES
    // ------------------
public:

    /// <summary>
    /// Iterator that steps once per Unicode character throughout a string. This iterator is constant, which means it does not
    /// allow to modify the referenced string.
    /// </summary>
    /// <remarks>
    /// Once an iterator have been bound to a string, it cannot point to another string ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the string.<br/>
    /// The position before the first character or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class Z_COMMON_MODULE_SYMBOLS ConstCharIterator
    {
        friend class StringUnicode; // This is necessary while the internal implementation is based on ICU


        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the string to iterate.
        /// </summary>
        /// <param name="strString">[IN] The string to iterate. If it is empty, the iterator will point to the end position.</param>
        explicit ConstCharIterator(const StringUnicode &strString);

        /// <summary>
        /// Copy constructor.
        /// </summary>
        /// <param name="iterator">[IN] The iterator to be copied.</param>
        ConstCharIterator(const ConstCharIterator &iterator);
        
        /// <summary>
        /// Constructor that receives the string to iterate and initial position.
        /// </summary>
        /// <param name="strString">[IN] The string to iterate. If it is empty, the iterator will point to the end position.</param>
        /// <param name="uInitialPosition">[IN] The index (starting at zero) of the initial position the iterator will point to. If it is out of bounds, 
        /// the iterator will point to the end position.</param>
        ConstCharIterator(const StringUnicode &strString, const unsigned int uInitialPosition);


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last character (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        ConstCharIterator operator++(int);

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        ConstCharIterator operator--(int);

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstCharIterator& operator++();

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        ConstCharIterator& operator--();

        /// <summary>
        /// Assignment operator that makes a copy of another iterator.
        /// </summary>
        /// <param name="iterator">[IN] The other iterator to be copied.</param>
        /// <returns>
        /// A reference to the resident iterator.
        /// </returns>
        ConstCharIterator& operator=(const ConstCharIterator &iterator);

        /// <summary>
        /// Equality operator that checks if both iterators are the same.
        /// </summary>
        /// <remarks>
        /// An iterator must point to the same position of the same string to be considered equal.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the same position of the same string; False otherwise.
        /// </returns>
        bool operator==(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Inequality operator that checks if both iterators are different.
        /// </summary>
        /// <remarks>
        /// An iterator that points to a different position or to a different string is considered distinct.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if they are pointing to the a different position or a different string; False otherwise.
        /// </returns>
        bool operator!=(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Greater than operator that checks whether resident iterator points to a more posterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator>(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Lower than operator that checks whether resident iterator points to a more anterior position than the input iterator.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator; False otherwise.
        /// </returns>
        bool operator<(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Greater than or equal to operator that checks whether resident iterator points to a more posterior position than the
        /// input iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more posterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator>=(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Lower than or equal to operator that checks whether resident iterator points to a more anterior position than the input
        /// iterator or to the same position.
        /// </summary>
        /// <remarks>
        /// If iterators point to different strings, the result is undefined.
        /// </remarks>
        /// <param name="iterator">[IN] The other iterator to compare to.</param>
        /// <returns>
        /// True if the resident iterator points to a more anterior position than the input iterator or to the same position; False otherwise.
        /// </returns>
        bool operator<=(const ConstCharIterator &iterator) const;

        /// <summary>
        /// Obtains the Unicode character pointed by the interator.
        /// </summary>
        /// <remarks>
        /// If the iterator points to an end position, the character U+FFFF (non-character) will be returned.<br/>
        /// If the iterator is invalid, the behavior is undefined.
        /// </remarks>
        /// <returns>
        /// A Unicode character.
        /// </returns>
        CharUnicode GetChar() const;

        /// <summary>
        /// Indicates whether the iterator is pointing to one of the ends of the string.
        /// </summary>
        /// <remarks>
        /// The position immediately before the first character and the position immediately after the last character are cosidered end
        /// positions; therefore, this method can be used both for forward and backard iteration.<br/>
        /// An invalid iterator is not considered as an end position.
        /// </remarks>
        /// <returns>
        /// True if the iterator is pointing to an end position; False otherwise.
        /// </returns>
        bool IsEnd() const;

        /// <summary>
        /// Makes the iterator point to the first position.
        /// </summary>
        /// <remarks>
        /// If the string is empty, the iterator will point to the end position.
        /// </remarks>
        void MoveFirst();

        /// <summary>
        /// Makes the iterator point to the last position.
        /// </summary>
        /// <remarks>
        /// If the string is empty, the iterator will point to the end position.
        /// </remarks>
        void MoveLast();

        /// <summary>
        /// Checks whether the iterator is valid or not.
        /// </summary>
        /// <remarks>
        /// An iterator is considered invalid when it points to an unexisting position (a string may have been shortened while the iterator
        /// was pointing to its last position). If the string to iterate have been destroyed, there is no way for the iterator to realize that so
        /// its behavior is undefined and this method will not detect that situation.<br/>
        /// The position before the first character or after the last one (end positions) are considered as valid positions.
        /// </remarks>
        /// <returns>
        /// True if the iterator is valid; False otherwise.
        /// </returns>
        bool IsValid() const;
                
        /// <summary>
        /// Gets the string that is being traversed by the iterator.
        /// </summary>
        /// <returns>
        /// A pointer to the string. It never changes since the iterator is created.
        /// </returns>
        const StringUnicode* GetContainer() const;


        // ATTRIBUTES
        // ---------------
    protected:

        /// <summary>
        /// The string to iterate.
        /// </summary>
        const StringUnicode* m_pString;

        /// <summary>
        /// Wrapped class that provides the iteration functionality.
        /// </summary>
        icu::StringCharacterIterator m_iterator;

        /// <summary>
        /// The index of the code point to which the iterator points.
        /// </summary>
        /// <remarks>
        /// Although ICU iterators already store this index, it's not actually the same index. ICU iterators traverse the string code unit by code unit,
        /// and store an index to a code unit, not a code point. A code point may be encoded as 2 code units (UTF16) and the public interface of the
        /// Zunderbolt string classes assume that all indices are code point indices. The only way to be consistent is to keep track of the current code point
        /// the iterator is pointing to at any moment.
        /// </remarks>
        unsigned int m_uIndex;

    }; // ConstCharIterator

    
    /// <summary>
    /// Iterator that steps once per Unicode character throughout a string. This iterator allows to modify the referenced string.
    /// </summary>
    /// <remarks>
    /// Once an iterator have been bound to a string, it cannot point to another string ever.<br/>
    /// Iterators can be invalid, this means, they may not point to an existing position of the string.<br/>
    /// The position before the first character or after the last one (end positions) are considered as valid positions.
    /// </remarks>
    class Z_COMMON_MODULE_SYMBOLS CharIterator : public StringUnicode::ConstCharIterator
    {
        // CONSTRUCTORS
        // ---------------
    public:

        /// <summary>
        /// Constructor that receives the string to iterate.
        /// </summary>
        /// <param name="strString">[IN] The string to iterate.</param>
        explicit CharIterator(StringUnicode &strString);

        /// <summary>
        /// Copy constructor.
        /// </summary>
        /// <param name="iterator">[IN] The iterator to be copied.</param>
        CharIterator(const CharIterator &iterator);
        
        /// <summary>
        /// Constructor that receives the string to iterate and the initial position.
        /// </summary>
        /// <param name="strString">[IN] The string to iterate. If it is empty, the iterator will point to the end position.</param>
        /// <param name="uInitialPosition">[IN] The index (starting at zero) of the initial position the iterator will point to. If it is out of bounds, 
        /// the iterator will point to the end position.</param>
        CharIterator(const StringUnicode &strString, const unsigned int uInitialPosition);


        // METHODS
        // ---------------
    public:

        /// <summary>
        /// Post-increment operator that makes the iterator step forward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last character (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        CharIterator operator++(int);

        /// <summary>
        /// Post-decrement operator that makes the iterator step backward after the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first character (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <param name=".">[IN] Unused parameter.</param>
        /// <returns>
        /// A copy of the previous state of the iterator.
        /// </returns>
        CharIterator operator--(int);

        /// <summary>
        /// Pre-increment operator that makes the iterator step forward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to increment an iterator that already points to the position after the last character (end position).<br/>
        /// It is not possible to increment an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        CharIterator& operator++();

        /// <summary>
        /// Pre-decrement operator that makes the iterator step backward before the expression have been evaluated.
        /// </summary>
        /// <remarks>
        /// It is not possible to decrement an iterator that already points to the position before the first character (end position).<br/>
        /// It is not possible to decrement an invalid iterator.
        /// </remarks>
        /// <returns>
        /// A reference to the iterator.
        /// </returns>
        CharIterator& operator--();

        /// <summary>
        /// Assignment operator that makes a copy of another iterator.
        /// </summary>
        /// <param name="iterator">[IN] The other iterator to be copied.</param>
        /// <returns>
        /// A reference to the resident iterator, after the copy.
        /// </returns>
        CharIterator& operator=(const CharIterator &iterator);

        /// <summary>
        /// Replaces a character in the current position with other.
        /// </summary>
        /// <remarks>
        /// This operation does not invalidate the iterator.<br/>
        /// If the iterator points to an end position, nothing will be done.<br/>
        /// If the iterator is invalid, the behavior is undefined.
        /// </remarks>
        /// <param name="newCharacter">[IN] The new Unicode character.</param>
        void SetChar(const CharUnicode &newCharacter);

    }; // CharIterator


    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Value to be used when the length of a string is unknown but can be calculated by checking for a null terminator.
    /// </summary>
    static const int LENGTH_NULL_TERMINATED;

    /// <summary>
    /// Position returned when the string pattern was not found.
    /// </summary>
    static const int PATTERN_NOT_FOUND;
    
    /// <summary>
    /// Constant to symbolize the end of the sequence near the last character.
    /// </summary>
    static const unsigned int END_POSITION_FORWARD = -1;

    /// <summary>
    /// Constant to symbolize the end of the sequence near the first character.
    /// </summary>
    static const unsigned int END_POSITION_BACKWARD = -2;


    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    StringUnicode();

    /// <summary>
    /// Constructor that makes a copy of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    StringUnicode(const StringUnicode &strString);

    /// <summary>
    /// Constructor that builds a string from an encoded input stream, assuming it is encoded in ISO 8859-1 and is null-terminated.
    /// </summary>
    /// <remarks>
    /// The final null character will not be added to the resultant string.
    /// </remarks>
    /// <param name="arBytes">[IN] The input stream as an array of bytes. It must not be null.</param>
    StringUnicode(const i8_z* arBytes);

    /// <summary>
    /// Constructor that builds a string from an encoded input stream, assuming it is encoded in ISO 8859-1.
    /// </summary>
    /// <remarks>
    /// The final null character will not be added to the resultant string.
    /// </remarks>
    /// <param name="arBytes">[IN] The input stream as an array of bytes. It should not be null. If it is null and the
    /// input length equals zero, an empty string will be created. If is null and the specified length is greater than zero, the behavior is undefined.</param>
    /// <param name="nLength">[IN] The length, in number of bytes, of the input byte stream. If it equals zero, an empty string will be created.
    /// When the input byte stream contains a null-terminated string, the constant LENGTH_NULL_TERMINATED can be used instead.</param>
    StringUnicode(const i8_z* arBytes, const int nLength);

    /// <summary>
    /// Constructor that builds a string from an encoded input stream.
    /// </summary>
    /// <remarks>
    /// The null-terminated option can only be used along with the encodings ASCII and ISO 8859-1, otherwise the result is undefined.<br/>
    /// When passing texts encoded in Unicode, corrupted or ill-formed sequences will be repaired by replacing the erroneous characters by U+FFFD REPLACEMENT CHARACTER.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness), if the input stream begins with a U+FFFE or U+FEFF BYTE ORDER MARK CHARACTERs, the bytes
    /// will be reordered depending on both the local machine architecture and which of both BOMs was specified. The BOM character will not be part of the resultant string.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness) and the input stream does not includes a BOM character, it is treated as if the encoding was big endian.<br/>
    /// When the encoding is UTF-16 LE, UTF-16 BE, UTF-32 LE or UTF-32 BE, the bytes in the stream will be reordered depending on both the endianness specified and the
    /// local machine's architecture. If the stream includes a BOM character, it does not affect the result and will be included in the resultant string.<br/>
    /// If the stream is a null-terminated string (ASCII or ISO 8859-1) and the length is not provided, the final null character will not be added to the resultant string.
    /// </remarks>
    /// <param name="arBytes">[IN] The input stream as an array of bytes. It should not be null. If it is null and the
    /// input length equals zero, an empty string will be created. If is null and the specified length is greater than zero, the behavior is undefined.</param>
    /// <param name="nLength">[Optional][IN] The length, in number of bytes, of the input byte stream. If it equals zero, an empty string will be created.
    /// When the encoding is ASCII or ISO 8859-1 and the input byte stream contains a null-terminated string, the constant LENGTH_NULL_TERMINATED can
    /// be used instead.</param>
    /// <param name="eEncoding">[Optional][IN] The text encoding of the input byte stream.</param>
    StringUnicode(const i8_z* arBytes, const int nLength, const ETextEncoding &eEncoding);

    /// <summary>
    /// Constructor that builds a string from only one character.
    /// </summary>
    /// <param name="character">[IN] The character that will form the new string.</param>
    StringUnicode(const CharUnicode &character);
        
    /// <summary>
    /// Constructor that builds a string from a null-terminated sequence of wide characters.
    /// </summary>
    /// <remarks>
    /// The final null character will not be added to the resultant string.
    /// </remarks>
    /// <param name="szCharacters">[IN] The input sequence of characters. It must not be null.</param>
    StringUnicode(const wchar_t* szCharacters);
    

    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignment operator that copies the value of another string.
    /// </summary>
    /// <param name="strString">[IN] The input string to be copied.</param>
    /// <returns>
    /// A reference to the resident string.
    /// </returns>
    StringUnicode& operator=(const StringUnicode &strString);

    /// <summary>
    /// Equality operator that performs a bitwise comparison of two strings to know if they are equal.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if strings are equal; False otherwise.
    /// </returns>
    bool operator==(const StringUnicode &strString) const;

    /// <summary>
    /// Inequality operator that performs a bitwise comparison of two strings to know if they are different.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if strings are not equal; False otherwise.
    /// </returns>
    bool operator!=(const StringUnicode &strString) const;

    /// <summary>
    /// Less than operator that performs a bitwise comparison of two strings to know which is cosidered "lower" than the other.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if input string (right operand) is lower than the resident string (left operand); False otherwise.
    /// </returns>
    bool operator<(const StringUnicode &strString) const;

    /// <summary>
    /// Less than or equals operator that performs a bitwise comparison of two strings to know which is cosidered "lower" than the
    /// other or whether they are equal or not.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if input string (right operand) is lower than or equals the resident string (left operand); False otherwise.
    /// </returns>
    bool operator<=(const StringUnicode &strString) const;

    /// <summary>
    /// Greater than operator that performs a bitwise comparison of two strings to know which is cosidered "greater" than the other.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if input string (right operand) is greater than the resident string (left operand); False otherwise.
    /// </returns>
    bool operator>(const StringUnicode &strString) const;

    /// <summary>
    /// Greater than or equals operator that performs a bitwise comparison of two strings to know which is cosidered "greater" than the
    /// other or whether they are equal or not.
    /// </summary>
    /// <param name="strString">[IN] The input string to compare to.</param>
    /// <returns>
    /// True if input string (right operand) is greater than or equals the resident string (left operand); False otherwise.
    /// </returns>
    bool operator>=(const StringUnicode &strString) const;

    /// <summary>
    /// Addition operator that generates a new string by concatenating two others.
    /// </summary>
    /// <param name="strString">[IN] The input string to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the input string.
    /// </returns>
    StringUnicode operator+(const StringUnicode &strString) const;

    /// <summary>
    /// Addition operator that generates a new string by concatenating two others.
    /// </summary>
    /// <param name="szString">[IN] The input null-terminated string to append to the resident string. It is assumed to be encoded in ISO 8859-1. It must not be null.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the input string.
    /// </returns>
    StringUnicode operator+(const char* szString) const;

    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const u8_z uInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const i8_z nInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const u16_z uInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const i16_z nInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const u32_z uInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const i32_z nInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const u64_z uInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of an integer to another string.
    /// </summary>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input integer.
    /// </returns>
    StringUnicode operator+(const i64_z nInteger) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of a floating point number to another string.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.<br/>
    /// A dot is used as decimal separator.
    /// </remarks>
    /// <param name="fFloat">[IN] The input floating point number to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input floating point number.
    /// </returns>
    StringUnicode operator+(const f32_z fFloat) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of a floating point number to another string.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.<br/>
    /// A dot is used as decimal separator.
    /// </remarks>
    /// <param name="fFloat">[IN] The input floating point number to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input floating point number.
    /// </returns>
    StringUnicode operator+(const f64_z fFloat) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of a boolean to another string.
    /// </summary>
    /// <remarks>
    /// The input value is converted to either "true" or "false" strings.
    /// </remarks>
    /// <param name="bBoolean">[IN] The input boolean to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input boolean.
    /// </returns>
    StringUnicode operator+(const bool bBoolean) const;
    
    /// <summary>
    /// Addition operator that generates a new string by concatenating the string representation of a vector of floating point numbers to another string.
    /// </summary>
    /// <remarks>
    /// The format of the string to be appended is: VF(First, Second, Third, Fourth).
    /// </remarks>
    /// <param name="vfVector">[IN] The input vector of floating point numbers to append to the resident string.</param>
    /// <returns>
    /// A new string where the resident string appears in first place followed by the string representation of the input vector of floating point numbers.
    /// </returns>
    StringUnicode operator+(const vf32_z vfVector) const;

    /// <summary>
    /// Array subscripting operator that returns a Unicode character located at a given position.
    /// </summary>
    /// <remarks>
    /// If the string is empty, a non-character value will be returned (U+FFFF).
    /// </remarks>
    /// <param name="uIndex">[IN] The zero-based index of the character to retrieve. It must be lower than the lenght of the string or
    /// a non-character value (U+FFFF) will be returned.</param>
    /// <returns>
    /// True if strings are not equal; False otherwise.
    /// </returns>
    CharUnicode operator[](const unsigned int uIndex) const;
    
    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, starting from a given position to the last one.
    /// </summary>
    /// <param name="uStartPosition">[IN] The position (zero-based index) of the first character of the resultant substring.
    /// It must be lower than the length of the string.</param>
    /// <returns>
    /// A subset of the resident string. If the input start position is out of bounds, an empty string is returned.
    /// </returns>
    StringUnicode Substring(const unsigned int uStartPosition) const;

    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, limited by a given range of positions.
    /// </summary>
    /// <param name="uStartPosition">[IN] The position (zero-based index) of the first character of the resultant substring.
    /// It must be lower than the length of the string.</param>
    /// <param name="uLastPosition">[IN] The position (zero-based index) of the last character of the resultant substring. It must be 
    /// greater than the start position. If it is out bounds, the last position will be used instead.</param>
    /// <returns>
    /// A subset of the resident string. If the input start position is out of bounds, an empty string is returned.
    /// </returns>
    StringUnicode Substring(const unsigned int uStartPosition, const unsigned int uLastPosition) const;
    
    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, starting from a given position to the last one.
    /// </summary>
    /// <param name="startPosition">[IN] The position of the first character of the resultant substring.
    /// It must not point to an end position.</param>
    /// <returns>
    /// A subset of the resident string. If the input start position is out of bounds, an empty string is returned.
    /// </returns>
    StringUnicode Substring(const StringUnicode::ConstCharIterator& startPosition) const;

    /// <summary>
    /// Obtains a new string from a subset of characters of the resident string, limited by a given range of positions.
    /// </summary>
    /// <param name="startPosition">[IN] The position of the first character of the resultant substring.
    /// It must not point to an end position.</param>
    /// <param name="lastPosition">[IN] The position of the last character of the resultant substring. It must be 
    /// posterior to the start position. If it is out bounds, the last position will be used instead.</param>
    /// <returns>
    /// A subset of the resident string. If the input start position is out of bounds, an empty string is returned.
    /// </returns>
    StringUnicode Substring(const StringUnicode::ConstCharIterator& startPosition, const StringUnicode::ConstCharIterator& lastPosition) const;

    /// <summary>
    /// Obtains a constant iterator pointing to the first position.
    /// </summary>
    /// <returns>
    /// A constant iterator.
    /// </returns>
    ConstCharIterator GetConstCharIterator() const;
    
    /// <summary>
    /// Obtains a constant iterator pointing to a given position.
    /// </summary>
    /// <param name="uInitialPosition">[IN] The index (starting at zero) of the initial position the iterator will point to. If it is out of bounds, 
    /// the iterator will point to the end position.</param>
    /// <returns>
    /// A constant iterator.
    /// </returns>
    ConstCharIterator GetConstCharIterator(const unsigned int uInitialPosition) const;

    /// <summary>
    /// Obtains a regular iterator pointing to the first position.
    /// </summary>
    /// <returns>
    /// A regular iterator.
    /// </returns>
    CharIterator GetCharIterator() const;

    /// <summary>
    /// Converts the string to an array of bytes encoded in certain text encoding.
    /// </summary>
    /// <remarks>
    /// The output stream will always add a null terminator if the string does not have one.<br/>
    /// Since it is not possible to predict the length of the UTF-8 representation of the string (internally encoded in UTF-16), the
    /// amount of memory reserved to allocate the result may be bigger than necessary when using that encoding. However, the output length
    /// will contain only the size of the occupied memory.<br/>
    /// When the encoding is UTF-16 or UTF-32 (without endianness), the U+FFFE or U+FEFF BYTE ORDER CHARACTER is added at the beginning of the sequence.
    /// Which of both depends on the local machine's endianness.<br/>
    /// When using UTF-16 LE, UTF-16 BE, UTF-32 LE or UTF-32 BE encodings, the bytes of the output stream will be reordered depending on the
    /// local machine's endianness.<br/>
    /// When using the ASCII or ISO 8859-1 encodings, if there are characters that cannot be translated to such encodings, they will be
    /// replaced by Substitution characters (#26 in ASCII table).
    /// </remarks>
    /// <param name="eEncoding">[IN] The encoding of the resultant text.</param>
    /// <returns>
    /// An array of bytes, which contains the encoded text, and the number of bytes (counting the null terminator). If the string is empty, a null array and a 
    /// zero will be returned. The wrapper is attached to the array.
    /// </returns>
    ArrayResult<i8_z> ToBytes(const ETextEncoding &eEncoding) const;

    /// <summary>
    /// Method that returns copy of the string with all its characters in lower case.
    /// </summary>
    /// <remarks>
    /// The result string may have different length, in bytes, not in number of characters, than the original one.
    /// </remarks>
    /// <returns>
    /// String with all its characters in lower case.
    /// </returns>
    StringUnicode ToLowerCase() const;

    /// <summary>
    /// Method that returns copy of the string with all its characters in upper case.
    /// </summary>
    /// <remarks>
    /// The result string may have different length, in bytes, not in number of characters, than the original one.
    /// </remarks>
    /// <returns>
    /// String with all its characters in upper case.
    /// </returns>
    StringUnicode ToUpperCase() const;

    /// <summary>
    /// Method that returns copy of the string with all its characters in folded case.
    /// </summary>
    /// <remarks>
    /// The result string may have different length, in bytes, not in number of characters, than the original one.
    /// </remarks>
    /// <returns>
    /// String with all its characters in folded case.
    /// </returns>
    StringUnicode ToCaseFolded() const;

    /// <summary>
    /// Applies a Unicode text normalization form algorithm to the string.
    /// </summary>
    /// <remarks>
    /// Normalization algorithms are described in the Unicode Standard Annex #15 (http://www.unicode.org/reports/tr15/).<br/>
    /// Currently, the only normalization forms supported are Canonical Decomposition (NFD) and Canonical Decomposition followed
    /// by a Canonical Composition (NFC).<br/>
    /// Normalization allows to compare two strings that are equivalent, i. e. they are compound of different characters
    /// or in a different order but represent the same glyphs or compatibles.
    /// </remarks>
    /// <param name="eNormalizationForm">[IN] The normalization form on which the algorithm will be based. Only NFC and NFD are supported.</param>
    void Normalize(const ENormalizationForm &eNormalizationForm);

    /// <summary>
    /// Compares two Unicode strings to know whether one is greater, lower or equal to the other, depending on the comparison type specified.
    /// </summary>
    /// <remarks>
    /// The comparison is performed following the steps described in the Unicode Collation Algorithm (UCA), available in the Unicode Standard Annex #10
    /// (http://www.unicode.org/reports/tr10/), which is based on the Default Unicode Collation Element Table (DUCET) (http://www.unicode.org/Public/UCA/latest/allkeys.txt).<br/>
    /// Variable collation elements are treated as non-ignorable. For canonical case sensitive comparisons,
    /// only primary to tertiary levels are checked; for canonical case insensitive comparisons, only primary and secondary levels are checked.<br/>
    /// By default, the collation order is English. The expected order when using canonical comparison would be, for example:<br/>
    /// Empty < Whitespaces < Puctuation marks < Numbers < Lowercase letters < Uppercase letters < Accented letters<br/>
    /// <br/>
    /// For canonical comparisons, both strings are normalized (NFD) internally, if they are not already, before compared.<br/>
    /// The fastest comparison type is binary case sensitive. Remember that uppercase letters are lower than lowercase letters when using binary comparison.
    /// </remarks>
    /// <param name="strInputString">[IN] The other string to compare to.</param>
    /// <param name="eComparisonType">[Optional][IN] The comparison type. Compatibility comparisons are not supported yet. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the resident string is bigger than the input string, it returns 1; if the resident string is lower than the input string, it returns -1; if
    /// strings are equal, it returns zero.
    /// </returns>
    int CompareTo(const StringUnicode &strInputString, const EComparisonType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string and returns the character position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns the position of the first Unicode character (zero-based) of the found pattern; if it is not found, it returns the PATTERN_NOT_FOUND constant.
    /// </returns>
    int IndexOf(const StringUnicode &strPattern, const EComparisonType::EnumType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string, starting from a given position, and returns the character
    /// position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="uStart">[IN] The start position to search from. If the position is greater than or equal to the length of the resident
    /// string, the pattern will not be found.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns the position of the first Unicode character (zero-based) of the found pattern; if it is not found, it returns the PATTERN_NOT_FOUND constant.
    /// </returns>
    int IndexOf(const StringUnicode &strPattern, const unsigned int uStart, const EComparisonType::EnumType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;
    
    /// <summary>
    /// Searches for a string pattern throughout the resident string from the end to the beginning and returns the character position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns the position of the first Unicode character (zero-based) of the found pattern; if it is not found, it returns the PATTERN_NOT_FOUND constant.
    /// </returns>
    int LastIndexOf(const StringUnicode &strPattern, const EComparisonType::EnumType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string from the end to the beginning, starting from a given position, and returns the character
    /// position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// Note that, if the start position coincides with any of the characters of an occurrence of the pattern in the string, such occurrence will be found.<br/>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="uStart">[IN] The start position to search from. If the position is greater than or equal to the length of the resident
    /// string, the pattern will be searched starting at the last character.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns the position of the first Unicode character (zero-based) of the found pattern; if it is not found, it returns the PATTERN_NOT_FOUND constant.
    /// </returns>
    int LastIndexOf(const StringUnicode &strPattern, const unsigned int uStart, const EComparisonType::EnumType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string and indicates whether such pattern exists or not.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns True; if it is not found, it returns False.
    /// </returns>
    bool Contains(const StringUnicode &strPattern, const EComparisonType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string and returns an iterator that points to the position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns an iterator that points to the the position of the Unicode character; if it is not found, the resultant iterator will point
    /// to the end position (forward).
    /// </returns>
    CharIterator PositionOf(const StringUnicode &strPattern, const EComparisonType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string, starting from a given position, and returns an iterator that points to the
    /// position of the first occurrence.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.
    /// </remarks>
    /// <param name="strPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="startPosition">[IN] The start position to search from. If the iterator points to an end position, the pattern will not be found.
    /// If the iterator is not valid, the behavior is undefined.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    /// <returns>
    /// If the pattern is found, it returns an iterator that points to the the position of the Unicode character; if it is not found, the resultant iterator will point
    /// to the end position (forward).
    /// </returns>
    CharIterator PositionOf(const StringUnicode &strPattern, const ConstCharIterator &startPosition, const EComparisonType &eComparisonType=EComparisonType::E_BinaryCaseSensitive) const;

    /// <summary>
    /// Searches for a string pattern throughout the resident string, replacing every occurrence with another string.
    /// </summary>
    /// <remarks>
    /// The result may be different depending on whether the resident string is normalized (NFD) or not, when performing canonical comparisons;
    /// it will not be normalized when comparing.<br/>
    /// If the resident string is normalized, a non-normalized replacement string may make it non-normalized too.<br/>
    /// The result will be stored in the resident string.
    /// </remarks>
    /// <param name="strSearchedPattern">[IN] The string pattern to search for. If performing a canonical comparison, it will be normalized internally if it is not already.</param>
    /// <param name="strReplacement">[IN] The replacement string.</param>
    /// <param name="eComparisonType">[Optional][IN] The type of comparison to perform during the search. By default, strings are compared using binary case-sensitive comparison.</param>
    void Replace(const StringUnicode &strSearchedPattern, const StringUnicode &strReplacement, const EComparisonType &eComparisonType=EComparisonType::E_BinaryCaseSensitive);

    /// <summary>
    /// Adds text to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, appending a non-normalized string will make it non-normalized too.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="strStringToAppend">[IN] The string to be appended.</param>
    void Append(const StringUnicode &strStringToAppend);
        
    /// <summary>
    /// Adds null-terminated text to the end of the string, assuming it is encoded in ISO 8859-1.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, appending a non-normalized string will make it non-normalized too.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="szStringToAppend">[IN] The string to be appended. It must not be null.</param>
    void Append(const char* szStringToAppend);

    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const u8_z uInteger);

    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const i8_z nInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const u16_z uInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const i16_z nInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const u32_z uInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const i32_z nInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="uInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const u64_z uInteger);
    
    /// <summary>
    /// Adds the string representation of an integer to the end of the string.
    /// </summary>
    /// <remarks>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="nInteger">[IN] The input integer to append to the resident string.</param>
    void Append(const i64_z nInteger);
        
    /// <summary>
    /// Adds the string representation of a boolean to the end of the string.
    /// </summary>
    /// <remarks>
    /// The input value is converted to either "true" or "false" strings.<br/>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="bBoolean">[IN] The input boolean to append to the resident string.</param>
    void Append(const bool bBoolean);

    /// <summary>
    /// Adds the string representation of a floating point number to the end of the string.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.<br/>
    /// A dot is used as decimal separator.<br/>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="fFloat">[IN] The input floating point number to append to the resident string.</param>
    void Append(const f32_z fFloat);

    /// <summary>
    /// Adds the string representation of a floating point number to the end of the string.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.<br/>
    /// A dot is used as decimal separator.<br/>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="fFloat">[IN] The input floating point number to append to the resident string.</param>
    void Append(const f64_z fFloat);

    /// <summary>
    /// Adds the string representation of a vector of floating point numbers to the end of the string.
    /// </summary>
    /// <remarks>
    /// The format of the string to be appended is: VF(First, Second, Third, Fourth).<br/>
    /// If the resident string is normalized, it will be still normalized after this operation.<br/>
    /// The result is stored in the resident string.
    /// </remarks>
    /// <param name="vfVector">[IN] The input vector of floating point numbers to append to the resident string.</param>
    void Append(const vf32_z vfVector);

    /// <summary>
    /// Splits the string, searching for another string that acts as separator and storing every part in an output array.
    /// </summary>
    /// <remarks>
    /// Separators are not included in the resultant array.<br/>
    /// If the string is empty, it will return an array with one empty string.<br/>
    /// If there are no characters between two separators, it will be considered a part anyway, although the string will be empty.<br/>
    /// Binary case-sensitive comparison is performed to find matches of the separator in the string.
    /// </remarks>
    /// <param name="strSeparator">[IN] The string that will act as separator. If it is empty, the string will not be split and will be returned as is.</param>
    /// <returns>
    /// Array compound of the parts in which the string is divided by the separators, and the number of strings in it (always greater than zero).
    /// The wrapper is attached to the array.
    /// </returns>
    ArrayResult<StringUnicode> Split(const StringUnicode &strSeparator) const;

    /// <summary>
    /// Parses the complete string, which represents an integer number.
    /// </summary>
    /// <remarks>
    /// The number may contain decimals (separated by a period (.)), but they will be ignored.<br/>
    /// The number may be negative, preceded by a dash (-). Positive numbers preceded by a plus sign (+) are also allowed.
    /// </remarks>
    /// <returns>
    /// The integer part of the number represented in the string. If the string does not contain a valid number, zero will be returned.
    /// If the number expressed in the string is bigger than the range of values the type can represent, it will be clamped to that range.
    /// </returns>
    i64_z ToInteger() const;
    
    /// <summary>
    /// Generates an integer value from an hexadecimal number contained in the string.
    /// </summary>
    /// <remarks>
    /// The string can contain a "0x" prefix. Letters can be uppercase or lowercase.<br/>
    /// The length of the string must be equal or lower than the size, in bytes, of the integral type multiplied by 2 (every byte is represented by 2 cyphers).
    /// If the number has a prefix, it is not taken into account in the previous precondition.
    /// </remarks>
    /// <typeparam name="IntegerT">The unsigned integral type to be returned.</typeparam>
    /// <returns>
    /// The obtained integer value.
    /// </returns>
    template<class IntegerT>
    IntegerT ToIntegerFromHexadecimal() const
    {
        static const codepoint_z CODEPOINT_FIRST_NUMBER          = '0';
        static const codepoint_z CODEPOINT_LAST_NUMBER           = '9';
        static const codepoint_z CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
        static const codepoint_z CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
        static const codepoint_z CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
        static const codepoint_z CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';
        static const StringUnicode HEX_PREFIX("0x");

        const unsigned int START_POSITION = this->Contains(HEX_PREFIX, EComparisonType::E_BinaryCaseInsensitive) ? HEX_PREFIX.GetLength() :
                                                                                                                             0;
        const unsigned int STRING_LENGTH = this->GetLength();

        Z_ASSERT_ERROR(STRING_LENGTH - START_POSITION - 1U <= sizeof(IntegerT) * 2U, StringUnicode("The string (\"") + *this + "\") must contain 2 letters per byte of the integer (apart from the prefix, if it has any).");

        IntegerT uMultiplier = 0;
        codepoint_z byteHalf = 0;
        IntegerT value = 0;

        for(unsigned int i = START_POSITION; i < STRING_LENGTH; ++i)
        {
            // It's a change of base (16 to 10), the exponent of the power of 16 is greater as the number occupies a more significant position in the string
            uMultiplier = scast_z(powf(16.0f, scast_z(STRING_LENGTH - i - 1U, float)), IntegerT);

            byteHalf = (*this)[i].GetCodePoint();

            if(byteHalf >= CODEPOINT_FIRST_NUMBER && byteHalf <= CODEPOINT_LAST_NUMBER)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_NUMBER); // 16^n * number
            else if(byteHalf >= CODEPOINT_FIRST_ALPHA_UPPERCASE && byteHalf <= CODEPOINT_LAST_ALPHA_UPPERCASE)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_ALPHA_UPPERCASE + 10U); // 16^n * letter [A-F] (where letters start with a value of 10)
            else if(byteHalf >= CODEPOINT_FIRST_ALPHA_LOWERCASE && byteHalf <= CODEPOINT_LAST_ALPHA_LOWERCASE)
                value += uMultiplier * (byteHalf - CODEPOINT_FIRST_ALPHA_LOWERCASE + 10U); // 16^n * letter [a-f] (where letters start with a value of 10)
            else
                Z_ASSERT_ERROR(false, "The string contains invalid characters.");
        }

        return value;
    }

    /// <summary>
    /// Parses the complete string, which represents a boolean value.
    /// </summary>
    /// <remarks>
    /// The following texts are considered as "true" (case insensitive):<br/>
    /// - true<br/>
    /// - t<br/>
    /// - y<br/>
    /// - 1<br/>
    /// The following texts are considered as "false" (case insensitive):<br/>
    /// - false<br/>
    /// - f<br/>
    /// - n<br/>
    /// - 0
    /// </remarks>
    /// <returns>
    /// True when the string represents the "true" value; False when the string represents the "false" value. If the string does not contain a
    /// valid boolean value, False will be returned.
    /// </returns>
    bool ToBoolean() const;

    /// <summary>
    /// Parses the complete string, which represents a floating point number.
    /// </summary>
    /// <remarks>
    /// The decimals separator is the period (.). The number may be negative, preceded by a dash (-).<br/>
    /// Scientific notation (like "1e3") is allowed.<br/>
    /// A loss of precision may occur during conversion.
    /// </remarks>
    /// <returns>
    /// The floating point number represented in the string. If the string does not contain a valid number, zero will be returned. If the number
    /// is too big, either positive infinite or negative infinite will be returned, depending on the number's sign. If the umber is too small,
    /// zero will be returned.
    /// </returns>
    f64_z ToFloat() const;
    
    /// <summary>
    /// Converts an integer number to a readable character string that represents it.
    /// </summary>
    /// <typeparam name="IntegerT">The type of integral type passed as argument.</typeparam>
    /// <param name="value">[IN] The integer number to be converted.</param>
    /// <returns>
    /// The string that represents the number.
    /// </returns>
    template<class IntegerT>
    static StringUnicode FromInteger(const IntegerT value)
    {
        std::ostringstream output;
        output << value;
        return output.str().c_str();
    }
    
    /// <summary>
    /// Converts an input boolean type to its representation as a string.
    /// </summary>
    /// <param name="bValue">[IN] The boolean value to be converted.</param>
    /// <returns>
    /// The strings "true" or "false".
    /// </returns>
    static StringUnicode FromBoolean(const bool bValue);
        
    /// <summary>
    /// Converts the floating point number to a readable character string that represents it.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.
    /// </remarks>
    /// <param name="fValue">[IN] The floating point number to be converted.</param>
    /// <returns>
    /// The string that represents the number (using a dot as decimal separator).
    /// </returns>
    static StringUnicode FromFloat(const f32_z fValue);
        
    /// <summary>
    /// Converts the floating point number to a readable character string that represents it.
    /// </summary>
    /// <remarks>
    /// String representation for NaN or Infinite values are not guaranteed to be the same for different compilers.
    /// </remarks>
    /// <param name="fValue">[IN] The floating point number to be converted.</param>
    /// <returns>
    /// The string that represents the number (using a dot as decimal separator).
    /// </returns>
    static StringUnicode FromFloat(const f64_z fValue);
    
    /// <summary>
    /// Converts the float vector package to a character string.
    /// </summary>
    /// <param name="vfValue">[IN] A float vector containing four 32-bits floating point values.</param>
    /// <returns>
    /// The package represented as a character string.<br/>
    /// The format is: VF(First, Second, Third, Fourth).
    /// </returns>
    static StringUnicode FromVF32(const vf32_z vfValue);
    
    /// <summary>
    /// Converts an unsigned integer number to its hexadecimal representation as a string.
    /// </summary>
    /// <typeparam name="IntegerT">The unsigned integral type passed as argument.</typeparam>
    /// <param name="uValue">[IN] The value whose bytes are to be printed.</param>
    /// <returns>
    /// The string that contains the hexadecimal representation of the integer.
    /// </returns>
    template<typename IntegerT>
    static StringUnicode FromIntegerToHexadecimal(const IntegerT uValue)
    {
        static const u8_z ASCII_FIRST_NUMBER = 48U;
        static const u8_z ASCII_FIRST_CAPITAL_LETTER = 65U;

        StringUnicode strResult;
        const u8_z* arBytes = rcast_z(&uValue, const u8_z*);
        u8_z uCurrentByteHalf = 0;
        CharUnicode correspondingChar(0);

        // Every half of every byte in the input variable is parsed and transformed to its textual hexadecimal representation
#if Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN
        puint_z uIndexCorrection = 1U;

        for(puint_z uMemOffset = sizeof(IntegerT); uMemOffset > 0; --uMemOffset)
        {
#elif Z_ENDIANNESS == Z_ENDIANNESS_BIGENDIAN
        puint_z uIndexCorrection = 0;

        for(puint_z uMemOffset = 0; uMemOffset < sizeof(IntegerT); ++uMemOffset)
        {
#endif
            // Gets the first half of the byte
            uCurrentByteHalf = arBytes[uMemOffset - uIndexCorrection] >> 4U;

            // Writes the corresponding character for the first half
            correspondingChar = uCurrentByteHalf > 9U ? CharUnicode(ASCII_FIRST_CAPITAL_LETTER + uCurrentByteHalf - 0x0A) : // It's a letter
                                                        CharUnicode(ASCII_FIRST_NUMBER + uCurrentByteHalf);                 // It's a number
            strResult.Append(correspondingChar);

            // Gets the second half of the byte
            uCurrentByteHalf = arBytes[uMemOffset - uIndexCorrection] & 0x0F;

            // Writes the corresponding character for the second half
            correspondingChar = uCurrentByteHalf > 9U ? CharUnicode(ASCII_FIRST_CAPITAL_LETTER + uCurrentByteHalf - 0x0A) : // It's a letter
                                                        CharUnicode(ASCII_FIRST_NUMBER + uCurrentByteHalf);                 // It's a number
            strResult.Append(correspondingChar);
        }

        return strResult;
    }

private:

    /// <summary>
    /// Searches for a string pattern (using binary case insensitive comparisons) throuhout the resident string, replacing every occurrence with another string.
    /// </summary>
    /// <param name="strSearchedPattern">[IN] The string pattern to search for.</param>
    /// <param name="strReplacement">[IN] The replacement string.</param>
    void _ReplaceBinaryCaseInsensitive(const StringUnicode &strSearchedPattern, const StringUnicode &strReplacement);

    /// <summary>
    /// Searches for a string pattern (using canonical comparisons) throuhout the resident string, replacing every occurrence with another string.
    /// </summary>
    /// <param name="strSearchedPattern">[IN] The string pattern to search for.</param>
    /// <param name="strReplacement">[IN] The replacement string.</param>
    /// <param name="eComparisonType">[IN] The type of comparison to perform during the search. Only canonical comparisons allowed.</param>
    void _ReplaceCanonical(const StringUnicode &strSearchedPattern, const StringUnicode &strReplacement, const EComparisonType &eComparisonType);

    /// <summary>
    /// Configures an ICU string search object according to a given comparison type.
    /// </summary>
    /// <param name="eComparisonType">[IN] The comparison type on which to base the search object.</param>
    /// <param name="search">[OUT] The resultant search object.</param>
    static void _ConfigureSearch(const EComparisonType &eComparisonType, icu::StringSearch &search);

    /// <summary>
    /// Gets an ICU number formatter configured to parse integer values.
    /// </summary>
    /// <returns>
    /// A number formatter ready to be used.
    /// </returns>
    static const icu::NumberFormat* _GetIntegerFormatter();

    /// <summary>
    /// Gets an ICU number formatter configured to parse floating point values.
    /// </summary>
    /// <returns>
    /// A number formatter ready to be used.
    /// </returns>
    static const icu::NumberFormat* _GetFloatFormatter();

    /// <summary>
    /// Gets an ICU converter for a given text encoding.
    /// </summary>
    /// <param name="eEncoding">[IN] The text encoding to which the converter will convert.</param>
    /// <returns>
    /// A converter ready to be used.
    /// </returns>
    static UConverter* _GetConverter(const ETextEncoding &eEncoding);

    /// <summary>
    /// Gets an ICU normalizer instance for a normalization form.
    /// </summary>
    /// <param name="eNormalizationForm">[IN] The normalization form on which the algorithm will be based.</param>
    /// <returns>
    /// A normalizer ready to be used.
    /// </returns>
    static const icu::Normalizer2* _GetNormalizer(const ENormalizationForm &eNormalizationForm);

    /// <summary>
    /// Gets an ICU collator instance for a comparison type.
    /// </summary>
    /// <param name="eComparisonType">[IN] The comparison type on which the collation algorithm will be based.</param>
    /// <returns>
    /// An object that applies the chosen collation algorithm to Unicode strings.
    /// </returns>
    static const icu::Collator* _GetCollator(const EComparisonType &eComparisonType);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the length of the string, this means, the number of characters that compose the sequence.
    /// </summary>
    /// <returns>
    /// The number of characters, not including the final null character.
    /// </returns>
    unsigned int GetLength() const;

    /// <summary>
    /// Indicates whether the string is empty or not.
    /// </summary>
    /// <returns>
    /// True if the string is empty; False otherwise.
    /// </returns>
    bool IsEmpty() const;

    /// <summary>
    /// Gets a pointer to the internal buffer of the string.
    /// </summary>
    /// <remarks>
    /// The text in the buffer is encoded in UTF-16.<br/>
    /// It is not recommended to call this method unless it is really necessary (performance constraints). Its signature may change in future versions.<br/>
    /// The string must not be modified while the internal buffer is being used; otherwise, the pointer may become invalid and make the program chrash.
    /// </remarks>
    /// <returns>
    /// A constant pointer to the buffer. The pointer is never null, even when the string is empty (not null-terminating character is included in this case either).
    /// </returns>
    const u16_z* GetInternalBuffer() const;

    /// <summary>
    /// Obtains a constant empty string.
    /// </summary>
    /// <returns>
    /// An empty string.
    /// </returns>
    static const StringUnicode& GetEmpty();

    /// <summary>
    /// Gets the UTF-16 text encoding for the local machine's endianness.
    /// </summary>
    /// <returns>
    /// UTF16LE if the machine is little-endian; UTF16BE if the machine is big-endian.
    /// </returns>
    static ETextEncoding GetLocalEncodingUTF16();
    
    /// <summary>
    /// Gets the UTF-32 text encoding for the local machine's endianness.
    /// </summary>
    /// <returns>
    /// UTF32LE if the machine is little-endian; UTF32BE if the machine is big-endian.
    /// </returns>
    static ETextEncoding GetLocalEncodingUTF32();


    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// Internal string representation.
    /// </summary>
    icu::UnicodeString m_strString;
    
    /// <summary>
    /// The string's length, in code points. It's necessary to store this value separately because calling countChar32 implies traversing the full string every time.
    /// </summary>
    unsigned int m_uLength;

};


// TEMPLATE METHOD SPECIALIZATION
// --------------------------------

/// <summary>
/// Converts an integer number to a readable character string that represents it.
/// </summary>
/// <param name="value">[IN] The integer number to be converted.</param>
/// <returns>
/// The string that represents the number.
/// </returns>
template<>
StringUnicode Z_COMMON_MODULE_SYMBOLS StringUnicode::FromInteger<u8_z>(const u8_z value);

/// <summary>
/// Converts an integer number to a readable character string that represents it.
/// </summary>
/// <param name="value">[IN] The integer number to be converted.</param>
/// <returns>
/// The string that represents the number.
/// </returns>
template<>
StringUnicode Z_COMMON_MODULE_SYMBOLS StringUnicode::FromInteger<i8_z>(const i8_z value);


} // namespace z

#endif // __STRINGUNICODE__
