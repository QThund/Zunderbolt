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

#include "ZMath/BaseMatrix4x3.h"

#include <memory>
#include <cstring>

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"


namespace z
{



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

BaseMatrix4x3::BaseMatrix4x3()
{
    ij[0][0] = ij[0][1] = ij[0][2] =
    ij[1][0] = ij[1][1] = ij[1][2] =
    ij[2][0] = ij[2][1] = ij[2][2] =
    ij[3][0] = ij[3][1] = ij[3][2] = SFloat::_0;
}

BaseMatrix4x3::BaseMatrix4x3(const BaseMatrix4x3 &matrix)
{
    memcpy(this->ij, matrix.ij, sizeof(float_z) * 12);
}

BaseMatrix4x3::BaseMatrix4x3(const float_z fValueAll)
{
    ij[0][0] = ij[0][1] = ij[0][2] =
    ij[1][0] = ij[1][1] = ij[1][2] =
    ij[2][0] = ij[2][1] = ij[2][2] =
    ij[3][0] = ij[3][1] = ij[3][2] = fValueAll;
}

BaseMatrix4x3::BaseMatrix4x3( const float_z f00, const float_z f01, const float_z f02,
                                const float_z f10, const float_z f11, const float_z f12,
                                const float_z f20, const float_z f21, const float_z f22,
                                const float_z f30, const float_z f31, const float_z f32)
{
    ij[0][0] = f00;
    ij[0][1] = f01;
    ij[0][2] = f02;
    ij[1][0] = f10;
    ij[1][1] = f11;
    ij[1][2] = f12;
    ij[2][0] = f20;
    ij[2][1] = f21;
    ij[2][2] = f22;
    ij[3][0] = f30;
    ij[3][1] = f31;
    ij[3][2] = f32;
}

BaseMatrix4x3::BaseMatrix4x3(const float_z* arValues)
{
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    ij[0][0] = arValues[0];
    ij[0][1] = arValues[1];
    ij[0][2] = arValues[2];
    ij[1][0] = arValues[3];
    ij[1][1] = arValues[4];
    ij[1][2] = arValues[5];
    ij[2][0] = arValues[6];
    ij[2][1] = arValues[7];
    ij[2][2] = arValues[8];
    ij[3][0] = arValues[9];
    ij[3][1] = arValues[10];
    ij[3][2] = arValues[11];
}

BaseMatrix4x3::BaseMatrix4x3(const vf32_z row0, const vf32_z row1, const vf32_z row2, const vf32_z &row3)
{
    float_z fAux;

    SVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], fAux);
    SVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], fAux);
    SVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], fAux);
    SVF32::Unpack(row3, this->ij[3][0], this->ij[3][1], this->ij[3][2], fAux);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseMatrix4x3::operator==(const BaseMatrix4x3 &matrix) const
{
    return    SFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
            SFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
            SFloat::AreEqual(this->ij[0][2], matrix.ij[0][2]) &&
            SFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]) &&
            SFloat::AreEqual(this->ij[1][2], matrix.ij[1][2]) &&
            SFloat::AreEqual(this->ij[2][0], matrix.ij[2][0]) &&
            SFloat::AreEqual(this->ij[2][1], matrix.ij[2][1]) &&
            SFloat::AreEqual(this->ij[2][2], matrix.ij[2][2]) &&
            SFloat::AreEqual(this->ij[3][0], matrix.ij[3][0]) &&
            SFloat::AreEqual(this->ij[3][1], matrix.ij[3][1]) &&
            SFloat::AreEqual(this->ij[3][2], matrix.ij[3][2]);
}

bool BaseMatrix4x3::operator!=(const BaseMatrix4x3 &matrix) const
{
    return !(*this == matrix);
}

} // namespace z
