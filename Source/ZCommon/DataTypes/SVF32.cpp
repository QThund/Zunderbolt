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

#include "ZCommon/DataTypes/SVF32.h"

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

void SVF32::Pack(const float_z fFirst, const float_z fSecond, const float_z fThird, const float_z fFourth, vf32_z &pack)
{
    #define Z_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

    #if Z_FLOAT_SIZE != Z_4BYTES_SIZE
        // Types are different so we need to use known-size types and then invoke
        // implicit casting when copying to auxiliar variables.
        f32_z f_1 = scast_z(fFirst, f32_z);
        f32_z f_2 = scast_z(fSecond, f32_z);
        f32_z f_3 = scast_z(fThird, f32_z);
        f32_z f_4 = scast_z(fFourth, f32_z);
    #else
        // Types are the same, no casting is needed so we only use references to maintain names used below
        const f32_z& f_1 = fFirst;
        const f32_z& f_2 = fSecond;
        const f32_z& f_3 = fThird;
        const f32_z& f_4 = fFourth;
    #endif

    pack.m128_f32[0] = f_1;
    pack.m128_f32[1] = f_2;
    pack.m128_f32[2] = f_3;
    pack.m128_f32[3] = f_4;
}

void SVF32::Unpack(const vf32_z pack, float_z &fFirst, float_z &fSecond, float_z &fThird, float_z &fFourth)
{
    #define Z_4BYTES_SIZE 4 // We are working with a 32-bits floats pack

    #if Z_FLOAT_SIZE != Z_4BYTES_SIZE
        // Types are different so we need to use known-size types and then invoke
        // implicit casting when copying to auxiliar variables.
        f32_z f_1 = scast_z(SFloat::_0, f32_z);
        f32_z f_2 = scast_z(SFloat::_0, f32_z);
        f32_z f_3 = scast_z(SFloat::_0, f32_z);
        f32_z f_4 = scast_z(SFloat::_0, f32_z);
    #else
        // Types are the same, no casting is needed so we only use references to maintain names used below
        f32_z& f_1 = fFirst;
        f32_z& f_2 = fSecond;
        f32_z& f_3 = fThird;
        f32_z& f_4 = fFourth;
    #endif

    f_1 = pack.m128_f32[0];
    f_2 = pack.m128_f32[1];
    f_3 = pack.m128_f32[2];
    f_4 = pack.m128_f32[3];

    #if Z_FLOAT_SIZE != Z_4BYTES_SIZE
        fFirst  = scast_z(f_1, float_z);
        fSecond = scast_z(f_2, float_z);
        fThird  = scast_z(f_3, float_z);
        fFourth = scast_z(f_4, float_z);
    #endif
}


} // namespace z
