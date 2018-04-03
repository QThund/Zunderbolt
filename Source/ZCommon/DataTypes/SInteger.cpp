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

#include "ZCommon/DataTypes/SInteger.h"

#include <stdlib.h>


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const u8_z SInteger::MaxU8_Z = 0xFF;
const u16_z SInteger::MaxU16_Z = 0xFFFF;
const u32_z SInteger::MaxU32_Z = 0xFFFFFFFF;
const u64_z SInteger::MaxU64_Z = 0xFFFFFFFFFFFFFFFFULL;
const i8_z SInteger::MaxPositiveI8_Z = 127;
const i8_z SInteger::MaxNegativeI8_Z = -128;
const i16_z SInteger::MaxPositiveI16_Z = 32767;
const i16_z SInteger::MaxNegativeI16_Z = -32768;
const i32_z SInteger::MaxPositiveI32_Z = 2147483647;
const i32_z SInteger::MaxNegativeI32_Z = -2147483647 - 1;// Defined this way to avoid compiler warnings due to size overflow, see http://bytes.com/topic/c/answers/674140-int-2147483648-a
const i64_z SInteger::MaxPositiveI64_Z = 9223372036854775807LL;
const i64_z SInteger::MaxNegativeI64_Z = -9223372036854775807LL - 1LL;// Defined this way to avoid compiler warnings due to size overflow, see http://bytes.com/topic/c/answers/674140-int-2147483648-a


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

i8_z SInteger::Abs(const i8_z nValue)
{
    return abs(nValue);
}

i16_z SInteger::Abs(const i16_z nValue)
{
    return abs(nValue);
}

i32_z SInteger::Abs(const i32_z nValue)
{
    return abs(nValue);
}

i64_z SInteger::Abs(const i64_z nValue)
{
    return llabs(nValue);
}


} // namespace z
