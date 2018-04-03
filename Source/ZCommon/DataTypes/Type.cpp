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

#include "ZCommon/DataTypes/Type.h"
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

const Type* Type::TYPE_INSTANCE_BOOL = new Type("bool");

const Type* Type::TYPE_INSTANCE_U8 = new Type("u8");

const Type* Type::TYPE_INSTANCE_I8 = new Type("i8");

const Type* Type::TYPE_INSTANCE_U16 = new Type("u16");

const Type* Type::TYPE_INSTANCE_I16 = new Type("i16");

const Type* Type::TYPE_INSTANCE_U32 = new Type("u32");

const Type* Type::TYPE_INSTANCE_I32 = new Type("i32");

const Type* Type::TYPE_INSTANCE_U64 = new Type("u64");

const Type* Type::TYPE_INSTANCE_I64 = new Type("i64");

const Type* Type::TYPE_INSTANCE_F32 = new Type("f32");

const Type* Type::TYPE_INSTANCE_F64 = new Type("f64");

const Type* Type::TYPE_INSTANCE_VF32 = new Type("vf32");

const Type* Type::TYPE_INSTANCE_STRING = new Type("string");

const Type* Type::TYPE_INSTANCE_VOID = new Type("void");

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Type::Type(const string_z &strName) : m_strName(strName)
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

bool Type::operator==(const Type &type) const
{
    return this == &type;
}

bool Type::operator!=(const Type &type) const
{
    return this != &type;
}

template<>
const Type* Type::FindType<bool>()
{
    return TYPE_INSTANCE_BOOL;
}

template<>
const Type* Type::FindType<u8_z>()
{
    return TYPE_INSTANCE_U8;
}

template<>
const Type* Type::FindType<i8_z>()
{
    return TYPE_INSTANCE_I8;
}

template<>
const Type* Type::FindType<u16_z>()
{
    return TYPE_INSTANCE_U16;
}
    
template<>
const Type* Type::FindType<i16_z>()
{
    return TYPE_INSTANCE_I16;
}
    
template<>
const Type* Type::FindType<u32_z>()
{
    return TYPE_INSTANCE_U32;
}

template<>
const Type* Type::FindType<i32_z>()
{
    return TYPE_INSTANCE_I32;
}

template<>
const Type* Type::FindType<u64_z>()
{
    return TYPE_INSTANCE_U64;
}

template<>
const Type* Type::FindType<i64_z>()
{
    return TYPE_INSTANCE_I64;
}

template<>
const Type* Type::FindType<f32_z>()
{
    return TYPE_INSTANCE_F32;
}

template<>
const Type* Type::FindType<f64_z>()
{
    return TYPE_INSTANCE_F64;
}
    
template<>
const Type* Type::FindType<vf32_z>()
{
    return TYPE_INSTANCE_VF32;
}

template<>
const Type* Type::FindType<string_z>()
{
    return TYPE_INSTANCE_STRING;
}

template<>
const Type* Type::FindType<void>()
{
    return TYPE_INSTANCE_VOID;
}

template<>
const Type* Type::FindType(const bool &)
{
    return Type::FindType<bool>();
}

template<>
const Type* Type::FindType(const u8_z &)
{
    return Type::FindType<u8_z>();
}

template<>
const Type* Type::FindType(const u16_z &)
{
    return Type::FindType<u16_z>();
}

template<>
const Type* Type::FindType(const u32_z &)
{
    return Type::FindType<u32_z>();
}

template<>
const Type* Type::FindType(const u64_z &)
{
    return Type::FindType<u64_z>();
}

template<>
const Type* Type::FindType(const i8_z &)
{
    return Type::FindType<i8_z>();
}

template<>
const Type* Type::FindType(const i16_z &)
{
    return Type::FindType<i16_z>();
}

template<>
const Type* Type::FindType(const i32_z &)
{
    return Type::FindType<i32_z>();
}

template<>
const Type* Type::FindType(const i64_z &)
{
    return Type::FindType<i64_z>();
}

template<>
const Type* Type::FindType(const f32_z &)
{
    return Type::FindType<f32_z>();
}

template<>
const Type* Type::FindType(const f64_z &)
{
    return Type::FindType<f64_z>();
}

template<>
const Type* Type::FindType(const vf32_z &)
{
    return Type::FindType<vf32_z>();
}

template<>
const Type* Type::FindType(const string_z &)
{
    return Type::FindType<string_z>();
}

template<>
const Type* Type::FindType(void*)
{
    return Type::FindType<void>();
}

template<>
const Type* Type::FindType(const void*)
{
    return Type::FindType<void>();
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const string_z& Type::GetName() const
{
    return m_strName;
}

} // namespace z
