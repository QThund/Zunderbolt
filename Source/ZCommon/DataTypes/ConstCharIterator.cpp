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



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StringUnicode::ConstCharIterator::ConstCharIterator(const StringUnicode &strString) : m_pString(&strString),
                                                                                          m_iterator(strString.m_strString),
                                                                                          m_uIndex(0)
{
    if(m_pString->IsEmpty())
        m_uIndex = StringUnicode::END_POSITION_FORWARD;
}

StringUnicode::ConstCharIterator::ConstCharIterator(const ConstCharIterator &iterator) : m_pString(iterator.m_pString),
                                                                                             m_iterator(iterator.m_iterator),
                                                                                             m_uIndex(iterator.m_uIndex)
{
}

StringUnicode::ConstCharIterator::ConstCharIterator(const StringUnicode &strString, const unsigned int uInitialPosition) : 
                                                                                             m_pString(&strString),
                                                                                             m_iterator(strString.m_strString),
                                                                                             m_uIndex(uInitialPosition)
{
    if(uInitialPosition < m_pString->GetLength())
    {
        m_iterator.move32(uInitialPosition, icu::CharacterIterator::kStart);
    }
    else
    {
        m_iterator.setToEnd();
        m_uIndex = StringUnicode::END_POSITION_FORWARD;
    }
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StringUnicode::ConstCharIterator StringUnicode::ConstCharIterator::operator++(int)
{
    // It is not possible to move an invalid iterator forward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator forward");

    // It is not possible to move forward when pointing to the end position after the last character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_FORWARD, "It is not possible to move forward when pointing to the end position after the last character");

    ConstCharIterator previousState(*this);

    // If the iterator is incremented, the result will never be pointing to the position before the first
    if(m_uIndex == StringUnicode::END_POSITION_BACKWARD)
    {
        m_uIndex = 0;
    }
    else if(!m_pString->IsEmpty() && m_uIndex == m_pString->GetLength() - 1U)
    {
        m_iterator.next32();
        m_uIndex = StringUnicode::END_POSITION_FORWARD;
    }
    else if(m_uIndex != StringUnicode::END_POSITION_FORWARD)
    {
        m_iterator.next32();
        ++m_uIndex;
    }

    return previousState;
}

StringUnicode::ConstCharIterator StringUnicode::ConstCharIterator::operator--(int)
{
    // It is not possible to move an invalid iterator backward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator backward");

    // It is not possible to move forward when pointing to the end position before the first character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_BACKWARD, "It is not possible to move forward when pointing to the end position before the first character");

    ConstCharIterator previousState(*this);

    if(m_uIndex == 0)
    {
        m_uIndex = StringUnicode::END_POSITION_BACKWARD;
    }
    else if(m_uIndex == StringUnicode::END_POSITION_FORWARD)
    {
        m_iterator.previous32();
        m_uIndex = m_pString->m_uLength - 1U;
    }
    else if(m_uIndex != StringUnicode::END_POSITION_BACKWARD)
    {
        m_iterator.previous32();
        --m_uIndex;
    }

    return previousState;
}

StringUnicode::ConstCharIterator& StringUnicode::ConstCharIterator::operator++()
{
    // It is not possible to move an invalid iterator forward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator forward");

    // It is not possible to move forward when pointing to the end position after the last character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_FORWARD, "It is not possible to move forward when pointing to the end position after the last character");

    // If the iterator is incremented, the result will never be pointing to the position before the first
    if(m_uIndex == StringUnicode::END_POSITION_BACKWARD)
    {
        m_uIndex = 0;
    }
    else if(!m_pString->IsEmpty() && m_uIndex == m_pString->GetLength() - 1U)
    {
        m_iterator.next32();
        m_uIndex = StringUnicode::END_POSITION_FORWARD;
    }
    else if(m_uIndex != StringUnicode::END_POSITION_FORWARD)
    {
        m_iterator.next32();
        ++m_uIndex;
    }

    return *this;
}

StringUnicode::ConstCharIterator& StringUnicode::ConstCharIterator::operator--()
{
    // It is not possible to move an invalid iterator backward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator backward");

    // It is not possible to move forward when pointing to the end position before the first character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_BACKWARD, "It is not possible to move forward when pointing to the end position before the first character");

    if(m_uIndex == 0)
    {
        m_uIndex = StringUnicode::END_POSITION_BACKWARD;
    }
    else if(m_uIndex == StringUnicode::END_POSITION_FORWARD)
    {
        m_iterator.previous32();
        m_uIndex = m_pString->m_uLength - 1U;
    }
    else if(m_uIndex != StringUnicode::END_POSITION_BACKWARD)
    {
        m_iterator.previous32();
        --m_uIndex;
    }

    return *this;
}

StringUnicode::ConstCharIterator& StringUnicode::ConstCharIterator::operator=(const StringUnicode::ConstCharIterator &iterator)
{
    // The iterator should not be assigned to an invalid iterator
    Z_ASSERT_ERROR(iterator.IsValid(), "The iterator should not be assigned to an invalid iterator");

    // Both iterators must refer to the same string
    Z_ASSERT_WARNING(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    if(&iterator != this && m_pString == iterator.m_pString)
    {
        m_iterator = iterator.m_iterator;
        m_uIndex = iterator.m_uIndex;
    }

    return *this;
}

bool StringUnicode::ConstCharIterator::operator==(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return m_uIndex == iterator.m_uIndex && m_pString == iterator.m_pString;
}

bool StringUnicode::ConstCharIterator::operator!=(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return m_uIndex != iterator.m_uIndex || m_pString != iterator.m_pString;
}

bool StringUnicode::ConstCharIterator::operator>(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return ((m_uIndex != StringUnicode::END_POSITION_BACKWARD && iterator.m_uIndex == StringUnicode::END_POSITION_BACKWARD) ||
            (m_uIndex > iterator.m_uIndex && m_uIndex != StringUnicode::END_POSITION_BACKWARD)) &&
           m_pString == iterator.m_pString;
    // The position before the first is considered lower than any other position
}

bool StringUnicode::ConstCharIterator::operator<(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return ((m_uIndex == StringUnicode::END_POSITION_BACKWARD && iterator.m_uIndex != StringUnicode::END_POSITION_BACKWARD) ||
            (m_uIndex < iterator.m_uIndex && iterator.m_uIndex != StringUnicode::END_POSITION_BACKWARD)) &&
           m_pString == iterator.m_pString;
}

bool StringUnicode::ConstCharIterator::operator>=(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return (m_uIndex == iterator.m_uIndex ||
            ((m_uIndex != StringUnicode::END_POSITION_BACKWARD && iterator.m_uIndex == StringUnicode::END_POSITION_BACKWARD) ||
              (m_uIndex > iterator.m_uIndex && m_uIndex != StringUnicode::END_POSITION_BACKWARD))) &&
           m_pString == iterator.m_pString;
}

bool StringUnicode::ConstCharIterator::operator<=(const ConstCharIterator &iterator) const
{
    // Iterators must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid() && iterator.IsValid(), "Iterators must be valid to get a correct result");

    // Both iterators must refer to the same string
    Z_ASSERT_ERROR(m_pString == iterator.m_pString, "Both iterators must refer to the same string");

    return (m_uIndex == iterator.m_uIndex ||
            ((m_uIndex == StringUnicode::END_POSITION_BACKWARD && iterator.m_uIndex != StringUnicode::END_POSITION_BACKWARD) ||
              (m_uIndex < iterator.m_uIndex && iterator.m_uIndex != StringUnicode::END_POSITION_BACKWARD))) &&
           m_pString == iterator.m_pString;
}

bool StringUnicode::ConstCharIterator::IsEnd() const
{
    // The iterator must be valid to get a correct result
    Z_ASSERT_ERROR(this->IsValid(), "The iterator must be valid to get a correct result");

    return m_uIndex == StringUnicode::END_POSITION_BACKWARD || m_uIndex == StringUnicode::END_POSITION_FORWARD;
}

CharUnicode StringUnicode::ConstCharIterator::GetChar() const
{
    // It is not possible to get the character refered to by an invalid iterator
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to get the character refered to by an invalid iterator");

    // It is not possible to get the character of an end position
    Z_ASSERT_ERROR(!this->IsEnd(), "It is not possible to get the character of an end position");

    static const UChar32 NON_CHARACTER = 0xFFFF; // U+FFFF, the same returned by the current32() method when the iterator points to the end position

    UChar32 character = this->IsEnd() ? NON_CHARACTER : m_iterator.current32();

    return CharUnicode(scast_z(character, codepoint_z));
}

void StringUnicode::ConstCharIterator::MoveFirst()
{
    // It is not possible to go to the first position of an empty string
    Z_ASSERT_WARNING(m_pString->GetLength() > 0, "It is not possible to go to the first position of an empty string");

    m_iterator.first32();
    m_uIndex = m_pString->m_uLength == 0 ? StringUnicode::END_POSITION_FORWARD : 0;
}

void StringUnicode::ConstCharIterator::MoveLast()
{
    // It is not possible to go to the last position of an empty string
    Z_ASSERT_WARNING(m_pString->GetLength() > 0, "It is not possible to go to the last position of an empty string");

    m_iterator.last32();
    m_uIndex = m_pString->m_uLength == 0 ? StringUnicode::END_POSITION_FORWARD : m_pString->m_uLength - 1U;
}

bool StringUnicode::ConstCharIterator::IsValid() const
{
    // If the index of the iterator is outside the bounds of the string, the iterator is not valid
    // The end position is valid
    return m_uIndex <= m_pString->GetLength() || m_uIndex == StringUnicode::END_POSITION_BACKWARD || m_uIndex == StringUnicode::END_POSITION_FORWARD;
}

const StringUnicode* StringUnicode::ConstCharIterator::GetContainer() const
{
    return m_pString;
}

} // namespace z
