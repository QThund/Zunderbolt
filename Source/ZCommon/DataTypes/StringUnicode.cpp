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

#include "ZCommon/DataTypes/StringUnicode.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/EComparisonType.h"
#include "ZCommon/DataTypes/ENormalizationForm.h"
#include "ZCommon/DataTypes/ETextEncoding.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"

#include <unicode/ucnv.h>
#include <unicode/fmtable.h>
#include <unicode/decimfmt.h>
#include <unicode/locid.h>
#include <unicode/uchar.h>
#include <sstream>
#include <iomanip>
#include <cstring> // Needed for strlen function


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const int StringUnicode::LENGTH_NULL_TERMINATED = -1;
const int StringUnicode::PATTERN_NOT_FOUND = -1;


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StringUnicode::StringUnicode() : m_strString(),
                                 m_uLength(0)
{
}

StringUnicode::StringUnicode(const StringUnicode &strString) : m_strString(strString.m_strString),
                                                               m_uLength(strString.GetLength())
{
}

StringUnicode::StringUnicode(const i8_z* arBytes)
{
    Z_ASSERT_ERROR(arBytes != null_z, "The input array of bytes must not be null.");

    // CAUTION: This is just a workaround to avoid performance loss due to unncecessry class instancing
    //          If this class inherited from another, a different solution should be applied (calling a common function)
    //          It is not possible to call other constructors until C++11
    new (this) StringUnicode(arBytes, StringUnicode::LENGTH_NULL_TERMINATED, ETextEncoding::E_ISO88591);
}

StringUnicode::StringUnicode(const i8_z* arBytes, const int nLength)
{
    // CAUTION: This is just a workaround to avoid performance loss due to unncecessry class instancing
    //          If this class inherited from another, a different solution should be applied (calling a common function)
    //          It is not possible to call other constructors until C++11
    new (this) StringUnicode(arBytes, nLength, ETextEncoding::E_ISO88591);
}

StringUnicode::StringUnicode(const i8_z* arBytes,
                             const int nLength,
                             const ETextEncoding &eEncoding)
{
    // Only ASCII and ISO 8859-1 encodings can be used along with null-terminated strings' length calculation
    Z_ASSERT_ERROR(((eEncoding == ETextEncoding::E_ASCII || eEncoding == ETextEncoding::E_ISO88591) &&
                    nLength == StringUnicode::LENGTH_NULL_TERMINATED) ||
                    nLength != StringUnicode::LENGTH_NULL_TERMINATED, "Only ASCII and ISO 8859-1 encodings can be used along with null-terminated strings' length calculation");

    UErrorCode errorCode = U_ZERO_ERROR;
    UConverter* pConverter = StringUnicode::_GetConverter(eEncoding);

    int nActualLength = nLength;

    if(nLength == StringUnicode::LENGTH_NULL_TERMINATED &&
       (eEncoding == ETextEncoding::E_ASCII || eEncoding == ETextEncoding::E_ISO88591))
        nActualLength = scast_z(strlen(arBytes), int);

    m_strString = icu::UnicodeString(arBytes, nActualLength, pConverter, errorCode);
    m_uLength = scast_z(m_strString.countChar32(), unsigned int);
}

StringUnicode::StringUnicode(const CharUnicode &character) : m_strString(UChar32(character.GetCodePoint())),
                                                             m_uLength(1U)
{
}

StringUnicode::StringUnicode(const wchar_t* szCharacters)
{
    Z_ASSERT_ERROR(szCharacters != null_z, "The input sequence of characters must not be null.");

    // In Windows, wide chars are 2 bytes length
    // In Linux and Mac OS X, wide chars are 4 bytes length
    ETextEncoding eEncoding = sizeof(wchar_t) == 2 ? string_z::GetLocalEncodingUTF16() :
                                                     string_z::GetLocalEncodingUTF32();

    const int INPUT_LENGTH = scast_z(wcslen(szCharacters) * sizeof(wchar_t), int);

    // CAUTION: This is just a workaround to avoid performance loss due to unncecessry class instancing
    //          If this class inherited from another, a different solution should be applied (calling a common function)
    //          It is not possible to call other constructors until C++11
    new (this) StringUnicode(rcast_z(szCharacters, const i8_z*), INPUT_LENGTH, eEncoding);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StringUnicode& StringUnicode::operator=(const StringUnicode &strString)
{
    // [TODO] Thund: Currently, this operator will invalidate any interator that may be pointing to the string.
    //               In the future we should look for a solution, if there is any.
    m_strString = strString.m_strString;
    m_uLength = strString.GetLength();
    return *this;
}

bool StringUnicode::operator==(const StringUnicode &strString) const
{
    return m_uLength == strString.m_uLength && (m_strString == strString.m_strString) != FALSE;
}

bool StringUnicode::operator!=(const StringUnicode &strString) const
{
    return m_uLength != strString.m_uLength || (m_strString != strString.m_strString) != FALSE;
}

bool StringUnicode::operator<(const StringUnicode &strString) const
{
    return (m_strString < strString.m_strString) != FALSE;
}

bool StringUnicode::operator<=(const StringUnicode &strString) const
{
    return (m_strString <= strString.m_strString) != FALSE;
}

bool StringUnicode::operator>(const StringUnicode &strString) const
{
    return (m_strString > strString.m_strString) != FALSE;
}

bool StringUnicode::operator>=(const StringUnicode &strString) const
{
    return (m_strString >= strString.m_strString) != FALSE;
}

StringUnicode StringUnicode::operator+(const StringUnicode &strString) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    strNewString.m_strString += strString.m_strString;
    strNewString.m_uLength = m_uLength + strString.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const char* szString) const
{
    return this->operator+(StringUnicode(szString));
}

StringUnicode StringUnicode::operator+(const u8_z uInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const i8_z nInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const u16_z uInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const i16_z nInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const u32_z uInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const i32_z nInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const u64_z uInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const i64_z nInteger) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    strNewString.m_strString += strInteger.m_strString;
    strNewString.m_uLength = m_uLength + strInteger.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const f32_z fFloat) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strFloat = StringUnicode::FromFloat(fFloat);
    strNewString.m_strString += strFloat.m_strString;
    strNewString.m_uLength = m_uLength + strFloat.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const f64_z fFloat) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strFloat = StringUnicode::FromFloat(fFloat);
    strNewString.m_strString += strFloat.m_strString;
    strNewString.m_uLength = m_uLength + strFloat.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const bool bBoolean) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strBoolean = StringUnicode::FromBoolean(bBoolean);
    strNewString.m_strString += strBoolean.m_strString;
    strNewString.m_uLength = m_uLength + strBoolean.m_uLength;
    return strNewString;
}

StringUnicode StringUnicode::operator+(const vf32_z vfVector) const
{
    StringUnicode strNewString;
    strNewString.m_strString =  m_strString;
    StringUnicode strFloatVector = StringUnicode::FromVF32(vfVector);
    strNewString.m_strString += strFloatVector.m_strString;
    strNewString.m_uLength = m_uLength + strFloatVector.m_uLength;
    return strNewString;
}

CharUnicode StringUnicode::operator[](const unsigned int uIndex) const
{
    // It is not possible to retrieve any character if the string is empty
    Z_ASSERT_ERROR(!this->IsEmpty(), "It is not possible to retrieve any character if the string is empty");

    // Index out of bounds: The index must be lower than the length of the string
    Z_ASSERT_ERROR(!this->IsEmpty() && uIndex < this->GetLength(), "Index out of bounds: The index must be lower than the length of the string");
    
    return StringUnicode::ConstCharIterator(*this, uIndex).GetChar();
}

StringUnicode StringUnicode::Substring(const unsigned int uStartPosition) const
{
    string_z strResult;

    if(uStartPosition < this->GetLength())
        strResult = this->Substring(StringUnicode::ConstCharIterator(*this, uStartPosition));

    return strResult;
}

StringUnicode StringUnicode::Substring(const unsigned int uStartPosition, const unsigned int uLastPosition) const
{
    // The start position index must be lower or equal than the last position index
    Z_ASSERT_ERROR(uStartPosition <= uLastPosition, "The start position index must be lower or equal than the last position index");

    string_z strResult;

    if(uStartPosition < this->GetLength())
    {
        unsigned int uClampedLastPosition = uLastPosition < this->GetLength() ? 
                                                                                uLastPosition :
                                                                                this->GetLength() - 1U;

        strResult = this->Substring(StringUnicode::ConstCharIterator(*this, uStartPosition), StringUnicode::ConstCharIterator(*this, uClampedLastPosition));
    }

    return strResult;
}

StringUnicode StringUnicode::Substring(const StringUnicode::ConstCharIterator& startPosition) const
{
    StringUnicode strResult;

    if(!startPosition.IsEnd())
    {
        m_strString.extract(startPosition.m_iterator.getIndex(), m_strString.length(), strResult.m_strString);
        strResult.m_uLength = scast_z(strResult.m_strString.countChar32(), unsigned int);
    }
    else if(startPosition < this->GetConstCharIterator()) // Is backward end position
        strResult = *this;                                // Returns the entire string

    return strResult;
}

StringUnicode StringUnicode::Substring(const StringUnicode::ConstCharIterator& startPosition, const StringUnicode::ConstCharIterator& lastPosition) const
{
    // The start position index must be lower or equal than the last position index
    Z_ASSERT_ERROR(startPosition <= lastPosition, "The start position must be prior or equal to the last position.");

    StringUnicode strResult;
    int32_t nStartPosition = 0;
    int32_t nLastPosition = 0;
    
    // These 3 lines are necessary to find the position of the second code unit, if any
    icu::StringCharacterIterator itLastCodeUnit = lastPosition.m_iterator;
    itLastCodeUnit.next32(); // Moves to the next character
    itLastCodeUnit.previous(); // Moves to the previous code unit

    if(!startPosition.IsEnd())
    {
        nStartPosition = startPosition.m_iterator.getIndex();
        nLastPosition = itLastCodeUnit.getIndex();
    }
    else if(startPosition < this->GetConstCharIterator()) // Is backward end position
    {
        if(startPosition == lastPosition)
        {
            // Both iterators point to backward end position
            nStartPosition = m_strString.length();
            nLastPosition = nStartPosition;
        }
        else
        {
            nStartPosition = 0;
            nLastPosition = itLastCodeUnit.getIndex();
        }
    }
    else // Is forward end position
    {
        nStartPosition = m_strString.length();
        nLastPosition = nStartPosition;
    }
    
    m_strString.extract(nStartPosition, nLastPosition - nStartPosition + 1, strResult.m_strString);
    strResult.m_uLength = scast_z(strResult.m_strString.countChar32(), unsigned int);

    return strResult;
}

StringUnicode::ConstCharIterator StringUnicode::GetConstCharIterator() const
{
    return StringUnicode::ConstCharIterator(*this);
}

StringUnicode::ConstCharIterator StringUnicode::GetConstCharIterator(const unsigned int uInitialPosition) const
{
    return StringUnicode::ConstCharIterator(*this, uInitialPosition);
}

StringUnicode::CharIterator StringUnicode::GetCharIterator() const
{
    // The constant casting operator is used deliberately due to there is no other way if we want to keep this design,
    // however, the string instance is not modified ever, not even inside the function.
    return StringUnicode::CharIterator(ccast_z(*this, StringUnicode&));
}

ArrayResult<i8_z> StringUnicode::ToBytes(const ETextEncoding &eEncoding) const
{
    const unsigned int CHARACTERS_COUNT = scast_z(m_strString.countChar32(), unsigned int);; // It does not include the final null character

    i8_z* pOutputBytes = null_z;
    puint_z uOutputLength = 0;

    if(CHARACTERS_COUNT > 0)
    {
        UErrorCode errorCode = U_ZERO_ERROR;
        UConverter* pConverter = StringUnicode::_GetConverter(eEncoding);
        const unsigned int CODE_UNITS_COUNT = m_strString.length(); // It does not include the final null character

        // Depending on whether the string is already null-terminated or not, a null terminator will be added at the end
        // of the resultant array of bytes
        const unsigned int ADD_NULL_TERMINATION = m_strString.char32At(CHARACTERS_COUNT - 1) == 0 ? 0 : 1;

        // By default, it is assigned as if it was to be encoded in ASCII or ISO 8859-1 (8-bits per character)
        int32_t nRequiredLengthBytes = CHARACTERS_COUNT + ADD_NULL_TERMINATION;

        // Output size calculation for Unicode encoding forms
        switch(eEncoding)
        {
        case ETextEncoding::E_UTF8:
            // It is not possible to know in advance how much memory the UTF-8 will require
            // (each character could be represented by 1, 2, 3 or 4 8-bits code units) so we reserve the maximum it would need
            nRequiredLengthBytes = sizeof(i32_z) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        case ETextEncoding::E_UTF16:
            // We already know the number of 16 bits code units. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i16_z) * (CODE_UNITS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case ETextEncoding::E_UTF16BE:
        case ETextEncoding::E_UTF16LE:
            // We already know the number of 16 bits code units
            nRequiredLengthBytes = sizeof(i16_z) * (CODE_UNITS_COUNT + ADD_NULL_TERMINATION);
            break;
        case ETextEncoding::E_UTF32:
            // The width of UTF32 characters is always 32 bits. A BOM character is added at the beginning
            nRequiredLengthBytes = sizeof(i32_z) * (CHARACTERS_COUNT + 1 + ADD_NULL_TERMINATION);
            break;
        case ETextEncoding::E_UTF32BE:
        case ETextEncoding::E_UTF32LE:
            // The width of UTF32 characters is always 32 bits
            nRequiredLengthBytes = sizeof(i32_z) * (CHARACTERS_COUNT + ADD_NULL_TERMINATION);
            break;
        default:
            break;
        }

        // Conversion from native encoding (UTF16) to input encoding
        const UChar* pBuffer = m_strString.getBuffer();
        pOutputBytes = new char[nRequiredLengthBytes];
        ucnv_reset(pConverter);
        uOutputLength = ucnv_fromUChars(pConverter, pOutputBytes, nRequiredLengthBytes, pBuffer, CODE_UNITS_COUNT, &errorCode);

        // If it was necessary to add a null terminator...
        if(ADD_NULL_TERMINATION == 1)
        {
            // The last character has to be set to zero (ICU adds only 1 byte at the end as the null terminator)
            // The last character has to be added to the output length
            switch(eEncoding)
            {
            case ETextEncoding::E_ASCII:
            case ETextEncoding::E_ISO88591:
            case ETextEncoding::E_UTF8:
                // 8 bits character
                uOutputLength += sizeof(i8_z);
                memset(&pOutputBytes[uOutputLength - sizeof(i8_z)], 0, sizeof(i8_z));
                break;
            case ETextEncoding::E_UTF16:
            case ETextEncoding::E_UTF16BE:
            case ETextEncoding::E_UTF16LE:
                // 16 bits character
                uOutputLength += sizeof(i16_z);
                memset(&pOutputBytes[uOutputLength - sizeof(i16_z)], 0, sizeof(i16_z));
                break;
            case ETextEncoding::E_UTF32:
            case ETextEncoding::E_UTF32BE:
            case ETextEncoding::E_UTF32LE:
                // 32 bits character
                uOutputLength += sizeof(i32_z);
                memset(&pOutputBytes[uOutputLength - sizeof(i32_z)], 0, sizeof(i32_z));
                break;
            default:
                break;
            }
        }
    }

    return ArrayResult<i8_z>(pOutputBytes, uOutputLength);
}

UConverter* StringUnicode::_GetConverter(const ETextEncoding &eEncoding)
{
    // About ICU converters: http://userguide.icu-project.org/conversion/converters
    static UErrorCode errorCode = U_ZERO_ERROR;
    static UConverter* const ASCII_CONVERTER    = ucnv_open("US-ASCII",    &errorCode);
    static UConverter* const ISO88591_CONVERTER = ucnv_open("ISO-8859-1",  &errorCode);
    static UConverter* const UTF8_CONVERTER     = ucnv_open("UTF8",        &errorCode);
    static UConverter* const UTF16_CONVERTER    = ucnv_open("UTF16",       &errorCode);
    static UConverter* const UTF32_CONVERTER    = ucnv_open("UTF32",       &errorCode);
    static UConverter* const UTF16BE_CONVERTER  = ucnv_open("UTF16BE",     &errorCode);
    static UConverter* const UTF16LE_CONVERTER  = ucnv_open("UTF16LE",     &errorCode);
    static UConverter* const UTF32BE_CONVERTER  = ucnv_open("UTF32BE",     &errorCode);
    static UConverter* const UTF32LE_CONVERTER  = ucnv_open("UTF32LE",     &errorCode);

    UConverter* pConverter = null_z;

    switch(eEncoding)
    {
    case ETextEncoding::E_ASCII:
        pConverter = ASCII_CONVERTER;
        break;
    case ETextEncoding::E_ISO88591:
        pConverter = ISO88591_CONVERTER;
        break;
    case ETextEncoding::E_UTF8:
        pConverter = UTF8_CONVERTER;
        break;
    case ETextEncoding::E_UTF16:
        pConverter = UTF16_CONVERTER;
        break;
    case ETextEncoding::E_UTF32:
        pConverter = UTF32_CONVERTER;
        break;
    case ETextEncoding::E_UTF16BE:
        pConverter = UTF16BE_CONVERTER;
        break;
    case ETextEncoding::E_UTF16LE:
        pConverter = UTF16LE_CONVERTER;
        break;
    case ETextEncoding::E_UTF32BE:
        pConverter = UTF32BE_CONVERTER;
        break;
    case ETextEncoding::E_UTF32LE:
        pConverter = UTF32LE_CONVERTER;
        break;
    default:
        break;
    }

    return pConverter;
}

StringUnicode StringUnicode::ToLowerCase() const
{
    StringUnicode strLowerCase(*this);
    // Use English as locale.
    const Locale &en = Locale::getEnglish();
    strLowerCase.m_strString.toLower(en);
    return strLowerCase;
}

StringUnicode StringUnicode::ToUpperCase() const
{
    StringUnicode strUpperCase(*this);
    // Use English as locale.
    const Locale &en = Locale::getEnglish();
    strUpperCase.m_strString.toUpper(en);
    return strUpperCase;
}

StringUnicode StringUnicode::ToCaseFolded() const
{
    StringUnicode strFoldedCase(*this);
    strFoldedCase.m_strString.foldCase(U_FOLD_CASE_DEFAULT);
    strFoldedCase.m_uLength = scast_z(strFoldedCase.m_strString.countChar32(), unsigned int);
    return strFoldedCase;
}

void StringUnicode::Normalize(const ENormalizationForm &eNormalizationForm)
{
    const icu::Normalizer2* pNormalizer = StringUnicode::_GetNormalizer(eNormalizationForm);
    UErrorCode eErrorCode = U_ZERO_ERROR;
    
    UBool bIsNormalized = pNormalizer->isNormalized(m_strString, eErrorCode); // [TODO] Thund: Change this by a call to this->IsNormalized when implemented
    Z_ASSERT_ERROR(U_SUCCESS(eErrorCode), "An error occurred when checking if the string was normalized"); // And this also.

    if(!bIsNormalized && U_SUCCESS(eErrorCode) != FALSE)
    {
        icu::UnicodeString strNormalized;
        pNormalizer->normalize(m_strString, strNormalized, eErrorCode);

        Z_ASSERT_ERROR(U_SUCCESS(eErrorCode), "An error occurred when normalizing the string");

        if(U_SUCCESS(eErrorCode) != FALSE)
        {
            m_strString = strNormalized;
            m_uLength = scast_z(strNormalized.countChar32(), unsigned int);;
        }
    }
}

const icu::Normalizer2* StringUnicode::_GetNormalizer(const ENormalizationForm &eNormalizationForm)
{
    const icu::Normalizer2* pNormalizer = null_z;
    UErrorCode eErrorCode = U_ZERO_ERROR;

    switch(eNormalizationForm)
    {
    case ENormalizationForm::E_C:
        pNormalizer = icu::Normalizer2::getNFCInstance(eErrorCode);
        break;
    case ENormalizationForm::E_D:
        pNormalizer = icu::Normalizer2::getNFDInstance(eErrorCode);
        break;
    //case ENormalizationForm::E_KC:
    //case ENormalizationForm::E_KD:
    //    Z_ASSERT_ERROR(false, "Normalization forms KC and KD are not supported currently");
    //    break;
    default:
        break;
    }

    Z_ASSERT_ERROR(!U_FAILURE(eErrorCode), "An error ocurred when attempting to get a normalizer");

    return pNormalizer;
}

int StringUnicode::CompareTo(const StringUnicode &strInputString, const EComparisonType &eComparisonType) const
{
    int nResult = 0;

    switch(eComparisonType)
    {
    case EComparisonType::E_BinaryCaseSensitive:
        nResult = m_strString.compare(strInputString.m_strString);
        break;
    case EComparisonType::E_BinaryCaseInsensitive:
        nResult = m_strString.caseCompare(strInputString.m_strString, U_FOLD_CASE_DEFAULT);
        break;
    case EComparisonType::E_CanonicalCaseInsensitive:
        {
            const icu::Collator* pCollator = StringUnicode::_GetCollator(eComparisonType);
            nResult = pCollator->compare(m_strString, strInputString.m_strString);
        }
        break;
    case EComparisonType::E_CanonicalCaseSensitive:
        {
            const icu::Collator* pCollator = StringUnicode::_GetCollator(eComparisonType);
            nResult = pCollator->compare(m_strString, strInputString.m_strString);
        }
        break;
    //case EComparisonType::E_CompatibilityCaseInsensitive:
    //case EComparisonType::E_CompatibilityCaseSensitive:
    //    Z_ASSERT_ERROR(false, "Compatibility comparisons are not supported yet");
    //    break;
    default:
        break;
    }

    return nResult;
}

const icu::Collator* StringUnicode::_GetCollator(const EComparisonType &eComparisonType)
{
    // Information of interest: http://userguide.icu-project.org/collation/architecture
    static bool bInitialized = false;
    static UErrorCode errorCode = U_ZERO_ERROR;
    // By default, the collation is English
    static icu::Collator* CANONICAL_CASESENSITIVE_COLLATOR = icu::Collator::createInstance(icu::Locale::getEnglish(), errorCode);
    static icu::Collator* CANONICAL_CASEINSENSITIVE_COLLATOR = icu::Collator::createInstance(icu::Locale::getEnglish(), errorCode);

    Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when getting the collator");

    if(!bInitialized)
    {
        CANONICAL_CASESENSITIVE_COLLATOR->setStrength(icu::Collator::TERTIARY);
        CANONICAL_CASESENSITIVE_COLLATOR->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute");
        CANONICAL_CASESENSITIVE_COLLATOR->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute");

        CANONICAL_CASEINSENSITIVE_COLLATOR->setStrength(icu::Collator::SECONDARY); // Secondary: No tertiary checking, no case comparison
        CANONICAL_CASEINSENSITIVE_COLLATOR->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute");
        CANONICAL_CASEINSENSITIVE_COLLATOR->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute");

        bInitialized = true;
    }

    icu::Collator* pCollator = null_z;

    switch(eComparisonType)
    {
    case EComparisonType::E_CanonicalCaseInsensitive:
        pCollator = CANONICAL_CASEINSENSITIVE_COLLATOR;
        break;
    case EComparisonType::E_CanonicalCaseSensitive:
        pCollator = CANONICAL_CASESENSITIVE_COLLATOR;
        break;
    //case EComparisonType::E_CompatibilityCaseInsensitive:
    //case EComparisonType::E_CompatibilityCaseSensitive:
    //    Z_ASSERT_ERROR(false, "Compatibility comparisons are not supported yet");
    //    break;
    default:
        Z_ASSERT_ERROR(false, "Invalid comparison type");
    }

    return pCollator;
}

int StringUnicode::IndexOf(const StringUnicode &strPattern, const EComparisonType::EnumType &eComparisonType) const
{
    int32_t nPosition = StringUnicode::PATTERN_NOT_FOUND;

    if(!strPattern.IsEmpty() && !this->IsEmpty())
    {
        if(eComparisonType == EComparisonType::E_BinaryCaseSensitive)
        {
            nPosition = m_strString.indexOf(strPattern.m_strString);
        }
        else if(eComparisonType == EComparisonType::E_BinaryCaseInsensitive)
        {
            // There is no case insensitive indexOf in ICU so both strings are case-folded before searching
            icu::UnicodeString strResidentCopy = m_strString;
            strResidentCopy.foldCase(U_FOLD_CASE_DEFAULT);
            icu::UnicodeString strPatternCopy = strPattern.m_strString;
            strPatternCopy.foldCase(U_FOLD_CASE_DEFAULT);
            nPosition = strResidentCopy.indexOf(strPatternCopy);
        }
        else
        {
            UErrorCode errorCode = U_ZERO_ERROR;

            // About string search with ICU: http://userguide.icu-project.org/collation/icu-string-search-service
            icu::StringSearch search(strPattern.m_strString, m_strString, Locale::getEnglish(), NULL, errorCode);

            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when creating the internal search object");

            StringUnicode::_ConfigureSearch(eComparisonType, search);
            nPosition = search.next(errorCode);
            
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");
        }

        if(nPosition == USEARCH_DONE)
            nPosition = StringUnicode::PATTERN_NOT_FOUND;
    }

    if(nPosition != StringUnicode::PATTERN_NOT_FOUND)
        nPosition = m_strString.countChar32(0, nPosition);

    return nPosition;
}

void StringUnicode::_ConfigureSearch(const EComparisonType &eComparisonType, icu::StringSearch &search)
{
    UErrorCode errorCode = U_ZERO_ERROR;

    switch(eComparisonType)
    {
    case EComparisonType::E_CanonicalCaseInsensitive:
        search.setAttribute(USEARCH_CANONICAL_MATCH, USEARCH_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (USEARCH_CANONICAL_MATCH)");
        search.setAttribute(USEARCH_OVERLAP, USEARCH_OFF, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (USEARCH_OVERLAP)");
        search.getCollator()->setStrength(icu::Collator::SECONDARY); // Secondary: No tertiary checking, no case comparison
        search.getCollator()->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (UCOL_NORMALIZATION_MODE)");
        search.getCollator()->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (UCOL_ALTERNATE_HANDLING)");
        break;
    case EComparisonType::E_CanonicalCaseSensitive:
        search.setAttribute(USEARCH_CANONICAL_MATCH, USEARCH_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (USEARCH_CANONICAL_MATCH)");
        search.setAttribute(USEARCH_OVERLAP, USEARCH_OFF, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (USEARCH_OVERLAP)");
        search.getCollator()->setStrength(icu::Collator::TERTIARY); // Tertiary: Case comparison
        search.getCollator()->setAttribute(UCOL_NORMALIZATION_MODE, UCOL_ON, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (UCOL_NORMALIZATION_MODE)");
        search.getCollator()->setAttribute(UCOL_ALTERNATE_HANDLING, UCOL_NON_IGNORABLE, errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An error occurred when calling setAttribute (UCOL_NON_IGNORABLE)");
        break;
    //case EComparisonType::E_CompatibilityCaseInsensitive:
    //case EComparisonType::E_CompatibilityCaseSensitive:
    //    Z_ASSERT_ERROR(false, "Compatibility comparisons are not supported yet");
    //    break;
    default:
        Z_ASSERT_ERROR(false, "Invalid comparison type");
    }
}

int StringUnicode::IndexOf(const StringUnicode &strPattern, const unsigned int uStart, const EComparisonType::EnumType &eComparisonType) const
{
    int32_t nPosition = StringUnicode::PATTERN_NOT_FOUND;

    if(!strPattern.IsEmpty() && !this->IsEmpty() && uStart < this->GetLength())
    {
        ConstCharIterator iterator(*this, uStart);
        int nStartCodeUnitIndex = iterator.m_iterator.getIndex();

        if(eComparisonType == EComparisonType::E_BinaryCaseSensitive)
        {
            nPosition = m_strString.indexOf(strPattern.m_strString, nStartCodeUnitIndex);
        }
        else if(eComparisonType == EComparisonType::E_BinaryCaseInsensitive)
        {
            // There is no case insensitive indexOf in ICU so both strings are converted to lowercase before searching
            icu::UnicodeString strResidentCopy = m_strString;
            strResidentCopy.foldCase(U_FOLD_CASE_DEFAULT);
            icu::UnicodeString strPatternCopy = strPattern.m_strString;
            strPatternCopy.foldCase(U_FOLD_CASE_DEFAULT);
            nPosition = strResidentCopy.indexOf(strPatternCopy, nStartCodeUnitIndex);
        }
        else
        {
            UErrorCode errorCode = U_ZERO_ERROR;

            // About string search with ICU: http://userguide.icu-project.org/collation/icu-string-search-service
            icu::StringSearch search(strPattern.m_strString, m_strString, Locale::getEnglish(), NULL, errorCode);
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when creating the internal search object");

            search.setOffset(nStartCodeUnitIndex, errorCode);
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when setting the offset of the search");

            StringUnicode::_ConfigureSearch(eComparisonType, search);
            nPosition = search.next(errorCode);

            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");
        }

        if(nPosition == USEARCH_DONE)
            nPosition = StringUnicode::PATTERN_NOT_FOUND;
    }

    if(nPosition != StringUnicode::PATTERN_NOT_FOUND)
        nPosition = m_strString.countChar32(0, nPosition);

    return nPosition;
}

int StringUnicode::LastIndexOf(const StringUnicode &strPattern, const EComparisonType::EnumType &eComparisonType) const
{
    int32_t nPosition = StringUnicode::PATTERN_NOT_FOUND;

    if(!strPattern.IsEmpty() && !this->IsEmpty())
    {
        if(eComparisonType == EComparisonType::E_BinaryCaseSensitive)
        {
            nPosition = m_strString.lastIndexOf(strPattern.m_strString);
        }
        else if(eComparisonType == EComparisonType::E_BinaryCaseInsensitive)
        {
            // There is no case insensitive indexOf in ICU so both strings are case-folded before searching
            icu::UnicodeString strResidentCopy = m_strString;
            strResidentCopy.foldCase(U_FOLD_CASE_DEFAULT);
            icu::UnicodeString strPatternCopy = strPattern.m_strString;
            strPatternCopy.foldCase(U_FOLD_CASE_DEFAULT);
            nPosition = strResidentCopy.lastIndexOf(strPatternCopy);
        }
        else
        {
            UErrorCode errorCode = U_ZERO_ERROR;

            // About string search with ICU: http://userguide.icu-project.org/collation/icu-string-search-service
            icu::StringSearch search(strPattern.m_strString, m_strString, Locale::getEnglish(), NULL, errorCode);

            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when creating the internal search object");

            StringUnicode::_ConfigureSearch(eComparisonType, search);
            nPosition = search.last(errorCode);
            
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");
        }

        if(nPosition == USEARCH_DONE)
            nPosition = StringUnicode::PATTERN_NOT_FOUND;
    }

    if(nPosition != StringUnicode::PATTERN_NOT_FOUND)
        nPosition = m_strString.countChar32(0, nPosition);

    return nPosition;
}

int StringUnicode::LastIndexOf(const StringUnicode &strPattern, const unsigned int uStart, const EComparisonType::EnumType &eComparisonType) const
{
    int32_t nPosition = StringUnicode::PATTERN_NOT_FOUND;

    if(!strPattern.IsEmpty() && !this->IsEmpty())
    {
        // Note: It's necessary to increment the start position by the length of the pattern since ICU classes don't find the pattern if the index inside the occurrence
        ConstCharIterator iterator(*this, uStart + strPattern.m_strString.length());
        int nStartCodeUnitIndex = iterator.m_iterator.getIndex();

        if(eComparisonType == EComparisonType::E_BinaryCaseSensitive)
        {
            nPosition = m_strString.lastIndexOf(strPattern.m_strString, 0, nStartCodeUnitIndex);
        }
        else if(eComparisonType == EComparisonType::E_BinaryCaseInsensitive)
        {
            // There is no case insensitive indexOf in ICU so both strings are converted to lowercase before searching
            icu::UnicodeString strResidentCopy = m_strString;
            strResidentCopy.foldCase(U_FOLD_CASE_DEFAULT);
            icu::UnicodeString strPatternCopy = strPattern.m_strString;
            strPatternCopy.foldCase(U_FOLD_CASE_DEFAULT);
            nPosition = strResidentCopy.lastIndexOf(strPatternCopy, 0, nStartCodeUnitIndex);
        }
        else
        {
            UErrorCode errorCode = U_ZERO_ERROR;

            // About string search with ICU: http://userguide.icu-project.org/collation/icu-string-search-service
            icu::StringSearch search(strPattern.m_strString, m_strString, Locale::getEnglish(), NULL, errorCode);
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when creating the internal search object");

            search.setOffset(nStartCodeUnitIndex, errorCode);
            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when setting the offset of the search");

            StringUnicode::_ConfigureSearch(eComparisonType, search);
            nPosition = search.previous(errorCode);

            Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");
        }

        if(nPosition == USEARCH_DONE)
            nPosition = StringUnicode::PATTERN_NOT_FOUND;
    }

    if(nPosition != StringUnicode::PATTERN_NOT_FOUND)
        nPosition = m_strString.countChar32(0, nPosition);

    return nPosition;
}

bool StringUnicode::Contains(const StringUnicode &strPattern, const EComparisonType &eComparisonType) const
{
    return this->IndexOf(strPattern, eComparisonType) != StringUnicode::PATTERN_NOT_FOUND;
}

StringUnicode::CharIterator StringUnicode::PositionOf(const StringUnicode &strPattern, const EComparisonType &eComparisonType) const
{
    CharIterator resultIterator = this->GetCharIterator();

    if(this->GetLength() > 0)
    {
        int nPatternPosition = this->IndexOf(strPattern, 0, eComparisonType);

        if(nPatternPosition == StringUnicode::PATTERN_NOT_FOUND)
        {
            // Returns end position
            resultIterator.MoveLast();
            ++resultIterator;
        }
        else
        {
            resultIterator = CharIterator(*this, nPatternPosition);
        }
    }

    return resultIterator;
}

StringUnicode::CharIterator StringUnicode::PositionOf(const StringUnicode &strPattern, const StringUnicode::ConstCharIterator &startPosition, const EComparisonType &eComparisonType) const
{
    Z_ASSERT_ERROR(!startPosition.IsEnd(), "The start position is out of bounds, it cannot be used to search for the pattern.");
    Z_ASSERT_ERROR(startPosition.IsValid(), "The input iterator is not valid, it cannot be used to search for the pattern.");

    CharIterator resultIterator = this->GetCharIterator();

    if(!this->IsEmpty())
    {
        int nPatternPosition = this->IndexOf(strPattern, startPosition.m_uIndex, eComparisonType);

        if(nPatternPosition == StringUnicode::PATTERN_NOT_FOUND)
        {
            // Returns end position
            resultIterator.MoveLast();
            ++resultIterator;
        }
        else
        {
            resultIterator = CharIterator(*this, nPatternPosition);
        }
    }

    return resultIterator;
}

void StringUnicode::Replace(const StringUnicode &strSearchedPattern, const StringUnicode &strReplacement, const EComparisonType &eComparisonType)
{
    if(!(strSearchedPattern.IsEmpty() || this->IsEmpty()))
    {
        if(eComparisonType == EComparisonType::E_BinaryCaseSensitive)
            m_strString.findAndReplace(strSearchedPattern.m_strString, strReplacement.m_strString);
        else if(eComparisonType == EComparisonType::E_BinaryCaseInsensitive)
            this->_ReplaceBinaryCaseInsensitive(strSearchedPattern, strReplacement);
        else
            this->_ReplaceCanonical(strSearchedPattern, strReplacement, eComparisonType);

        m_uLength = scast_z(m_strString.countChar32(), unsigned int);;
    }
}

void StringUnicode::_ReplaceBinaryCaseInsensitive(const StringUnicode &strSearchedPattern, const StringUnicode &strReplacement)
{
    icu::UnicodeString strPatternCopy = strSearchedPattern.m_strString;
    strPatternCopy.foldCase(U_FOLD_CASE_DEFAULT);
    icu::UnicodeString strResidentCopy = m_strString;
    strResidentCopy.foldCase(U_FOLD_CASE_DEFAULT);

    // Iterates over a copy of the original string, but modifying the original string
    int32_t nPosition = strResidentCopy.indexOf(strPatternCopy);
    int32_t nAccumulatedOffset = 0;
    const int32_t PATTERN_LENGTH = scast_z(strSearchedPattern.GetLength(), int32_t);
    const int32_t REPLACEMENT_LENGTH = scast_z(strReplacement.GetLength(), int32_t);
    const int32_t REPLACEMENT_LENGTH_DIFFERENCE = REPLACEMENT_LENGTH - PATTERN_LENGTH;

    while(nPosition != USEARCH_DONE)
    {
        m_strString.replace(nPosition + nAccumulatedOffset, PATTERN_LENGTH, strReplacement.m_strString);

        // An offset must be kept because the string being modified and the string the iterator traverses are not the same instance
        // Adding this offset we get the position of the found match in the modified string
        nAccumulatedOffset += REPLACEMENT_LENGTH_DIFFERENCE;

        nPosition = strResidentCopy.indexOf(strPatternCopy, nPosition + 1);
    }
}

void StringUnicode::_ReplaceCanonical(const StringUnicode& strSearchedPattern, const StringUnicode &strReplacement, const EComparisonType &eComparisonType)
{
    // Creates the search object
    UErrorCode errorCode = U_ZERO_ERROR;
    icu::StringSearch search(strSearchedPattern.m_strString, m_strString, Locale::getEnglish(), NULL, errorCode);
    Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when creating the internal search object");

    StringUnicode::_ConfigureSearch(eComparisonType, search);

    // Iterates over a copy of the original string, modifying the original string
    int32_t nPosition = search.next(errorCode);
    int32_t nAccumulatedOffset = 0;
    const int32_t PATTERN_LENGTH = scast_z(strSearchedPattern.GetLength(), int32_t);
    const int32_t REPLACEMENT_LENGTH = scast_z(strReplacement.GetLength(), int32_t);
    const int32_t REPLACEMENT_LENGTH_DIFFERENCE = REPLACEMENT_LENGTH - PATTERN_LENGTH;

    Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");

    while(nPosition != USEARCH_DONE)
    {
        m_strString.replace(nPosition + nAccumulatedOffset, PATTERN_LENGTH, strReplacement.m_strString);

        // An offset must be kept because the string being modified and the string the iterator traverses are not the same instance
        // Adding this offset we get the position of the found match in the modified string
        nAccumulatedOffset += REPLACEMENT_LENGTH_DIFFERENCE;

        nPosition = search.next(errorCode);
        Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error occurred when searching the pattern");
    }
}

void StringUnicode::Append(const StringUnicode &strStringToAppend)
{
    m_strString.append(strStringToAppend.m_strString);
    m_uLength += strStringToAppend.GetLength();
}

void StringUnicode::Append(const char* szStringToAppend)
{
    this->Append(StringUnicode(szStringToAppend));
}

void StringUnicode::Append(const u8_z uInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const i8_z nInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const u16_z uInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const i16_z nInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const u32_z uInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const i32_z nInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const u64_z uInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(uInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const i64_z nInteger)
{
    StringUnicode strInteger = StringUnicode::FromInteger(nInteger);
    m_strString.append(strInteger.m_strString);
    m_uLength += strInteger.GetLength();
}

void StringUnicode::Append(const bool bBoolean)
{
    StringUnicode strBoolean = StringUnicode::FromBoolean(bBoolean);
    m_strString.append(strBoolean.m_strString);
    m_uLength += strBoolean.GetLength();
}

void StringUnicode::Append(const f32_z fFloat)
{
    StringUnicode strFloat = StringUnicode::FromFloat(fFloat);
    m_strString.append(strFloat.m_strString);
    m_uLength += strFloat.GetLength();
}

void StringUnicode::Append(const f64_z fFloat)
{
    StringUnicode strFloat = StringUnicode::FromFloat(fFloat);
    m_strString.append(strFloat.m_strString);
    m_uLength += strFloat.GetLength();
}

void StringUnicode::Append(const vf32_z vfVector)
{
    StringUnicode strVectorFloat = StringUnicode::FromVF32(vfVector);
    m_strString.append(strVectorFloat.m_strString);
    m_uLength += strVectorFloat.GetLength();
}

ArrayResult<StringUnicode> StringUnicode::Split(const StringUnicode &strSeparator) const
{
    StringUnicode* arResultParts = null_z;
    puint_z uNumberOfParts = 0;

    if(this->IsEmpty())
    {
        // Returns an empty string
        arResultParts = new StringUnicode[1];
        uNumberOfParts = 1;
    }
    else
    {
        const unsigned int SEPARATOR_LENGTH = strSeparator.GetLength();
        unsigned int uLastFound = this->IndexOf(strSeparator, 0, EComparisonType::E_BinaryCaseSensitive);

        // Separations are counted before the array of strings is created
        while(uLastFound != StringUnicode::PATTERN_NOT_FOUND)
        {
            ++uNumberOfParts;
            uLastFound += SEPARATOR_LENGTH;

            uLastFound = this->IndexOf(strSeparator, uLastFound, EComparisonType::E_BinaryCaseSensitive);
        }

        // Adds the last part which was not counted since no more separators were found
        ++uNumberOfParts;

        // Creates the output array of strings
        arResultParts = new StringUnicode[uNumberOfParts];

        // Extracts every part, searching for separators and getting the text in between, if any
        uLastFound = 0;
        unsigned int uCurrentFound = 0;

        // Parses all the parts but the last one
        for(unsigned int iPart = 0; iPart < uNumberOfParts - 1U; ++iPart)
        {
            uCurrentFound = this->IndexOf(strSeparator, uLastFound, EComparisonType::E_BinaryCaseSensitive);

            if(uLastFound != uCurrentFound)
                arResultParts[iPart] = this->Substring(uLastFound, uCurrentFound - 1U);

            if(uLastFound != StringUnicode::PATTERN_NOT_FOUND)
                uLastFound = uCurrentFound + SEPARATOR_LENGTH;
        }

        // Then the last part
        arResultParts[uNumberOfParts - 1U] = this->Substring(uLastFound);
    }

    return ArrayResult<StringUnicode>(arResultParts, uNumberOfParts);
}

i64_z StringUnicode::ToInteger() const
{
    const icu::NumberFormat* pFormatter = StringUnicode::_GetIntegerFormatter();
    UErrorCode errorCodeParsing = U_ZERO_ERROR;
    UErrorCode errorCodeGetting = U_ZERO_ERROR;

    const bool HAS_POSITIVE_SIGN = m_strString[0] == '+';

    icu::Formattable formattable;
    if(HAS_POSITIVE_SIGN)
        pFormatter->parse(this->Substring(1, this->GetLength()).m_strString, formattable, errorCodeParsing);
    else
        pFormatter->parse(m_strString, formattable, errorCodeParsing);
    
    i64_z nResult = formattable.getInt64(errorCodeGetting);

    Z_ASSERT_ERROR(U_SUCCESS(errorCodeParsing) || nResult != 0LL, "The string cannot be converted to an integer number");
    Z_ASSERT_WARNING(U_SUCCESS(errorCodeParsing) || nResult == 0LL, "The number contained in the string is too big, it will be shrinked to the maximum value the type can represent");
    Z_ASSERT_ERROR(U_SUCCESS(errorCodeGetting), "An unexpected error occurred when getting the value from the formattable object");

    return nResult;
}

bool  StringUnicode::ToBoolean() const
{
    static const StringUnicode BOOLEAN_STRING_TRUE("true");
    static const StringUnicode BOOLEAN_STRING_TRUE_NUMERIC("1");
    static const StringUnicode BOOLEAN_STRING_TRUE_ABBREVIATED1("t");
    static const StringUnicode BOOLEAN_STRING_TRUE_ABBREVIATED2("T");
    static const StringUnicode BOOLEAN_STRING_TRUE_ABBREVIATED3("y");
    static const StringUnicode BOOLEAN_STRING_TRUE_ABBREVIATED4("Y");
    static const StringUnicode BOOLEAN_STRING_FALSE("false");
    static const StringUnicode BOOLEAN_STRING_FALSE_NUMERIC("0");
    static const StringUnicode BOOLEAN_STRING_FALSE_ABBREVIATED1("f");
    static const StringUnicode BOOLEAN_STRING_FALSE_ABBREVIATED2("F");
    static const StringUnicode BOOLEAN_STRING_FALSE_ABBREVIATED3("n");
    static const StringUnicode BOOLEAN_STRING_FALSE_ABBREVIATED4("N");

    bool bResult = false;

    if(this->GetLength() > 1)
    {
        bResult = this->CompareTo(BOOLEAN_STRING_TRUE, EComparisonType::E_BinaryCaseInsensitive) == 0;
        
        // If it's false and the string does not match the "false" word, then it has not got a valid value
        Z_ASSERT_ERROR(bResult == true || (this->CompareTo(BOOLEAN_STRING_FALSE, EComparisonType::E_BinaryCaseInsensitive) == 0), "The string cannot be converted to a boolean value");
    }
    else
    {
        bResult = *this == BOOLEAN_STRING_TRUE_NUMERIC      || 
                  *this == BOOLEAN_STRING_TRUE_ABBREVIATED1 || 
                  *this == BOOLEAN_STRING_TRUE_ABBREVIATED2 || 
                  *this == BOOLEAN_STRING_TRUE_ABBREVIATED3 || 
                  *this == BOOLEAN_STRING_TRUE_ABBREVIATED4;

        // If it's false and the string does not match any of the abbreviations, then it has not got a valid value
        Z_ASSERT_ERROR(bResult == true                            || 
                        *this == BOOLEAN_STRING_FALSE_NUMERIC      ||
                        *this == BOOLEAN_STRING_FALSE_ABBREVIATED1 || 
                        *this == BOOLEAN_STRING_FALSE_ABBREVIATED2 ||
                        *this == BOOLEAN_STRING_FALSE_ABBREVIATED3 ||
                        *this == BOOLEAN_STRING_FALSE_ABBREVIATED4, 
                        "The string cannot be converted to a boolean value");
    }

    return bResult;
}

f64_z StringUnicode::ToFloat() const
{
#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    static const f64_z POSITIVE_INFINITE = +1e308 * 1e308;
    static const f64_z NEGATIVE_INFINITE = -1e308 * 1e308;
#endif
    const icu::NumberFormat* pFormatter = StringUnicode::_GetFloatFormatter();
    UErrorCode errorCodeParsing = U_ZERO_ERROR;
    UErrorCode errorCodeGetting = U_ZERO_ERROR;

    icu::Formattable formattable;
    pFormatter->parse(m_strString, formattable, errorCodeParsing);

    f64_z fResult = formattable.getDouble(errorCodeGetting);

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT != Z_CONFIG_ASSERTSBEHAVIOR_DISABLED
    Z_ASSERT_WARNING(fResult != POSITIVE_INFINITE && fResult != NEGATIVE_INFINITE, "The result is infinite, maybe the string contains a too big number");
#endif
    Z_ASSERT_ERROR(U_SUCCESS(errorCodeParsing) || fResult != 0.0, "The string cannot be converted to a floating point number");
    Z_ASSERT_WARNING(U_SUCCESS(errorCodeParsing) || fResult == 0.0, "The number contained in the string is too big, it will be shrinked to the maximum value the type can represent");
    Z_ASSERT_ERROR(U_SUCCESS(errorCodeGetting), "An unexpected error occurred when getting the value from the formattable object");

    return fResult;
}

const icu::NumberFormat* StringUnicode::_GetIntegerFormatter()
{
    static UErrorCode errorCode = U_ZERO_ERROR;
    static icu::NumberFormat* pNumberFormatter = icu::NumberFormat::createInstance(icu::Locale::getEnglish(), UNUM_DECIMAL, errorCode);
    pNumberFormatter->setParseIntegerOnly(TRUE);
    Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error ocurred when creating an ICU number formatter");
    return pNumberFormatter;
}

const icu::NumberFormat* StringUnicode::_GetFloatFormatter()
{
    static UErrorCode errorCode = U_ZERO_ERROR;
    static const icu::NumberFormat* pNumberFormatter = icu::DecimalFormat::createInstance(icu::Locale::getEnglish(), UNUM_SCIENTIFIC, errorCode);
    Z_ASSERT_ERROR(U_SUCCESS(errorCode), "An unexpected error ocurred when creating an ICU number formatter");
    return pNumberFormatter;
}

template<>
StringUnicode StringUnicode::FromInteger<i8_z>(const i8_z nValue)
{
    // [SMELL] Thund: This specialization is necessary since STL's converter treats signed chars
    //                in a different way than how it does with the other integer types.
    std::ostringstream output;
    output << scast_z(nValue, i32_z);

    return output.str().c_str();
}

template<>
StringUnicode StringUnicode::FromInteger<u8_z>(const u8_z uValue)
{
    // [SMELL] Thund: This specialization is necessary since STL's converter treats unsigned chars
    //                in a different way than how it does with the other integer types.
    std::ostringstream output;
    output << scast_z(uValue, u32_z);

    return output.str().c_str();
}

StringUnicode StringUnicode::FromBoolean(const bool bValue)
{
    return bValue ? "true" : "false";
}

StringUnicode StringUnicode::FromFloat(const f32_z fValue)
{
    std::ostringstream output;
    output << std::setprecision(9) << fValue;
    return output.str().c_str();
}

StringUnicode StringUnicode::FromFloat(const f64_z fValue)
{
    std::ostringstream output;
    output << std::setprecision(17) << fValue;
    return output.str().c_str();
}

StringUnicode StringUnicode::FromVF32(const vf32_z vfValue)
{
    float_z fFirst  = SFloat::_0;
    float_z fSecond = SFloat::_0;
    float_z fThird  = SFloat::_0;
    float_z fFourth = SFloat::_0;

    SVF32::Unpack(vfValue, fFirst, fSecond, fThird, fFourth);

    std::ostringstream output;
    output << "VF(" << std::setprecision(9) << fFirst << ", " << fSecond << ", " << fThird << ", " << fFourth << ")";
    return output.str().c_str();
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

unsigned int StringUnicode::GetLength() const
{
    return m_uLength;
}

bool StringUnicode::IsEmpty() const
{
    return m_uLength == 0;
}

const StringUnicode& StringUnicode::GetEmpty()
{
    static const StringUnicode EMPTY_STRING;
    return EMPTY_STRING;
}

ETextEncoding StringUnicode::GetLocalEncodingUTF16()
{
    return Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN ? ETextEncoding::E_UTF16LE :
                                                         ETextEncoding::E_UTF16BE;
}

ETextEncoding StringUnicode::GetLocalEncodingUTF32()
{
    return Z_ENDIANNESS == Z_ENDIANNESS_LITTLEENDIAN ? ETextEncoding::E_UTF32LE :
                                                         ETextEncoding::E_UTF32BE;
}

const u16_z* StringUnicode::GetInternalBuffer() const
{
    return rcast_z(m_strString.getBuffer(), const u16_z*);
}

} // namespace z
