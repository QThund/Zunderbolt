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

#include "ZCommon/DataTypes/SAnyTypeToStringConverter.h"


namespace z
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

template<>
string_z SAnyTypeToStringConverter::Convert(const bool &object)
{
    return string_z::FromBoolean(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const u8_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const u16_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const u32_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const u64_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const i8_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const i16_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const i32_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const i64_z &object)
{
    return string_z::FromInteger(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const f32_z &object)
{
    return string_z::FromFloat(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const f64_z &object)
{
    return string_z::FromFloat(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const vf32_z &object)
{
    return string_z::FromVF32(object);
}

template<>
string_z SAnyTypeToStringConverter::Convert(const string_z &object)
{
    return object;
}

template<>
string_z SAnyTypeToStringConverter::Convert(const void* pObject)
{
    static const string_z HEXADECIMAL_PREFIX("0x");
    static const string_z WHITESPACE(" ");
    static const string_z NULL_POINTER("<Null>");
        
    string_z strResult;

    if(pObject != null_z)
    {
        // Prints the memory address to which the pointer points
        strResult.Append(HEXADECIMAL_PREFIX);
        strResult.Append(string_z::FromIntegerToHexadecimal(rcast_z(pObject, puint_z)));
    }
    else
    {
        // It is a null pointer
        strResult.Append(NULL_POINTER);
    }

    return strResult;
}


} // namespace z
