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

StringUnicode::CharIterator::CharIterator(StringUnicode &strString) : ConstCharIterator(strString)
{
}

StringUnicode::CharIterator::CharIterator(const CharIterator &iterator) : ConstCharIterator(iterator)
{
}

StringUnicode::CharIterator::CharIterator(const StringUnicode &strString, const unsigned int uInitialPosition) : 
                                                                                             ConstCharIterator(strString, uInitialPosition)
{
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StringUnicode::CharIterator StringUnicode::CharIterator::operator++(int)
{
    // It is not possible to move an invalid iterator forward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator forward");

    // It is not possible to move forward when pointing to the end position after the last character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_FORWARD, "It is not possible to move forward when pointing to the end position after the last character");

    CharIterator previousState(*this);

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

StringUnicode::CharIterator StringUnicode::CharIterator::operator--(int)
{
    // It is not possible to move an invalid iterator backward
    Z_ASSERT_ERROR(this->IsValid(), "It is not possible to move an invalid iterator backward");

    // It is not possible to move forward when pointing to the end position before the first character
    Z_ASSERT_WARNING(m_uIndex != StringUnicode::END_POSITION_BACKWARD, "It is not possible to move forward when pointing to the end position before the first character");

    CharIterator previousState(*this);

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

StringUnicode::CharIterator& StringUnicode::CharIterator::operator++()
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

StringUnicode::CharIterator& StringUnicode::CharIterator::operator--()
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

StringUnicode::CharIterator& StringUnicode::CharIterator::operator=(const StringUnicode::CharIterator &iterator)
{
    // Returns a reference to this, after the copy. The reference must be converted from the base class to this class
    return scast_z(StringUnicode::ConstCharIterator::operator=(iterator), StringUnicode::CharIterator&);
}

void StringUnicode::CharIterator::SetChar(const CharUnicode &newCharacter)
{
    Z_ASSERT_ERROR(this->IsValid(), "The iterator is not valid, the character cannot be set.");
    Z_ASSERT_ERROR(!this->IsEnd(), "It is not possible to set the character when the iterator points to an end position.");
    
    if(!this->IsEnd())
    {
        // Changes the string
        ccast_z(m_pString, string_z*)->m_strString.setCharAt(m_iterator.getIndex(), newCharacter.GetCodePoint());

        // Updates the iterator
        const i32_z CURRENT_INDEX = m_iterator.getIndex();
        m_iterator.setText(m_pString->m_strString);
        m_iterator.setIndex32(CURRENT_INDEX);
    }
}


} // namespace z
