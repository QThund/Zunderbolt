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

#include "ZMath/Matrix4x4.h"

#include "ZCommon/Assertions.h"
#include "ZMath/SAngle.h"
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

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(const float_z fValueAll)
{
    ij[0][0] = ij[0][1] = ij[0][2] = ij[0][3] =
    ij[1][0] = ij[1][1] = ij[1][2] = ij[1][3] =
    ij[2][0] = ij[2][1] = ij[2][2] = ij[2][3] =
    ij[3][0] = ij[3][1] = ij[3][2] = ij[3][3] = fValueAll;
}

Matrix4x4::Matrix4x4(const float_z f00, const float_z f01, const float_z f02, const float_z f03,
                     const float_z f10, const float_z f11, const float_z f12, const float_z f13,
                     const float_z f20, const float_z f21, const float_z f22, const float_z f23,
                     const float_z f30, const float_z f31, const float_z f32, const float_z f33)
{
    ij[0][0] = f00;
    ij[0][1] = f01;
    ij[0][2] = f02;
    ij[0][3] = f03;
    ij[1][0] = f10;
    ij[1][1] = f11;
    ij[1][2] = f12;
    ij[1][3] = f13;
    ij[2][0] = f20;
    ij[2][1] = f21;
    ij[2][2] = f22;
    ij[2][3] = f23;
    ij[3][0] = f30;
    ij[3][1] = f31;
    ij[3][2] = f32;
    ij[3][3] = f33;
}

Matrix4x4::Matrix4x4(const float_z* arValues)
{
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    ij[0][0] = arValues[0];
    ij[0][1] = arValues[1];
    ij[0][2] = arValues[2];
    ij[0][3] = arValues[3];
    ij[1][0] = arValues[4];
    ij[1][1] = arValues[5];
    ij[1][2] = arValues[6];
    ij[1][3] = arValues[7];
    ij[2][0] = arValues[8];
    ij[2][1] = arValues[9];
    ij[2][2] = arValues[10];
    ij[2][3] = arValues[11];
    ij[3][0] = arValues[12];
    ij[3][1] = arValues[13];
    ij[3][2] = arValues[14];
    ij[3][3] = arValues[15];
}

Matrix4x4::Matrix4x4(const vf32_z row0, const vf32_z row1, const vf32_z row2, const vf32_z &row3)
{
    SVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], this->ij[0][3]);
    SVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], this->ij[1][3]);
    SVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], this->ij[2][3]);
    SVF32::Unpack(row3, this->ij[3][0], this->ij[3][1], this->ij[3][2], this->ij[3][3]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool Matrix4x4::operator==(const Matrix4x4 &matrix) const
{
    return  SFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
            SFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
            SFloat::AreEqual(this->ij[0][2], matrix.ij[0][2]) &&
            SFloat::AreEqual(this->ij[0][3], matrix.ij[0][3]) &&
            SFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]) &&
            SFloat::AreEqual(this->ij[1][2], matrix.ij[1][2]) &&
            SFloat::AreEqual(this->ij[1][3], matrix.ij[1][3]) &&
            SFloat::AreEqual(this->ij[2][0], matrix.ij[2][0]) &&
            SFloat::AreEqual(this->ij[2][1], matrix.ij[2][1]) &&
            SFloat::AreEqual(this->ij[2][2], matrix.ij[2][2]) &&
            SFloat::AreEqual(this->ij[2][3], matrix.ij[2][3]) &&
            SFloat::AreEqual(this->ij[3][0], matrix.ij[3][0]) &&
            SFloat::AreEqual(this->ij[3][1], matrix.ij[3][1]) &&
            SFloat::AreEqual(this->ij[3][2], matrix.ij[3][2]) &&
            SFloat::AreEqual(this->ij[3][3], matrix.ij[3][3]);
}

bool Matrix4x4::operator!=(const Matrix4x4 &matrix) const
{
    return !(*this == matrix);
}

Matrix4x4 Matrix4x4::operator*(const float_z fScalar) const
{
    Matrix4x4 aux;

    aux.ij[0][0] = fScalar * this->ij[0][0];
    aux.ij[0][1] = fScalar * this->ij[0][1];
    aux.ij[0][2] = fScalar * this->ij[0][2];
    aux.ij[0][3] = fScalar * this->ij[0][3];
    aux.ij[1][0] = fScalar * this->ij[1][0];
    aux.ij[1][1] = fScalar * this->ij[1][1];
    aux.ij[1][2] = fScalar * this->ij[1][2];
    aux.ij[1][3] = fScalar * this->ij[1][3];
    aux.ij[2][0] = fScalar * this->ij[2][0];
    aux.ij[2][1] = fScalar * this->ij[2][1];
    aux.ij[2][2] = fScalar * this->ij[2][2];
    aux.ij[2][3] = fScalar * this->ij[2][3];
    aux.ij[3][0] = fScalar * this->ij[3][0];
    aux.ij[3][1] = fScalar * this->ij[3][1];
    aux.ij[3][2] = fScalar * this->ij[3][2];
    aux.ij[3][3] = fScalar * this->ij[3][3];

    return aux;
}

Matrix4x4 operator*(const float_z fScalar, const Matrix4x4 &matrix)
{
    Matrix4x4 aux;

    aux.ij[0][0] = fScalar * matrix.ij[0][0];
    aux.ij[0][1] = fScalar * matrix.ij[0][1];
    aux.ij[0][2] = fScalar * matrix.ij[0][2];
    aux.ij[0][3] = fScalar * matrix.ij[0][3];
    aux.ij[1][0] = fScalar * matrix.ij[1][0];
    aux.ij[1][1] = fScalar * matrix.ij[1][1];
    aux.ij[1][2] = fScalar * matrix.ij[1][2];
    aux.ij[1][3] = fScalar * matrix.ij[1][3];
    aux.ij[2][0] = fScalar * matrix.ij[2][0];
    aux.ij[2][1] = fScalar * matrix.ij[2][1];
    aux.ij[2][2] = fScalar * matrix.ij[2][2];
    aux.ij[2][3] = fScalar * matrix.ij[2][3];
    aux.ij[3][0] = fScalar * matrix.ij[3][0];
    aux.ij[3][1] = fScalar * matrix.ij[3][1];
    aux.ij[3][2] = fScalar * matrix.ij[3][2];
    aux.ij[3][3] = fScalar * matrix.ij[3][3];

    return aux;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &matrix) const
{
    Matrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];
    aux.ij[0][3] = this->ij[0][0] * matrix.ij[0][3] + this->ij[0][1] * matrix.ij[1][3] + this->ij[0][2] * matrix.ij[2][3] + this->ij[0][3] * matrix.ij[3][3];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];
    aux.ij[1][3] = this->ij[1][0] * matrix.ij[0][3] + this->ij[1][1] * matrix.ij[1][3] + this->ij[1][2] * matrix.ij[2][3] + this->ij[1][3] * matrix.ij[3][3];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];
    aux.ij[2][3] = this->ij[2][0] * matrix.ij[0][3] + this->ij[2][1] * matrix.ij[1][3] + this->ij[2][2] * matrix.ij[2][3] + this->ij[2][3] * matrix.ij[3][3];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];
    aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3] + this->ij[3][3] * matrix.ij[3][3];

    return aux;
}

Matrix4x3 Matrix4x4::operator*(const Matrix4x3 &matrix) const
{
    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];

    return aux;
}

Matrix4x4 Matrix4x4::operator/(const float_z fScalar) const
{

    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    Matrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] * fDivisor;
    aux.ij[0][1] = this->ij[0][1] * fDivisor;
    aux.ij[0][2] = this->ij[0][2] * fDivisor;
    aux.ij[0][3] = this->ij[0][3] * fDivisor;
    aux.ij[1][0] = this->ij[1][0] * fDivisor;
    aux.ij[1][1] = this->ij[1][1] * fDivisor;
    aux.ij[1][2] = this->ij[1][2] * fDivisor;
    aux.ij[1][3] = this->ij[1][3] * fDivisor;
    aux.ij[2][0] = this->ij[2][0] * fDivisor;
    aux.ij[2][1] = this->ij[2][1] * fDivisor;
    aux.ij[2][2] = this->ij[2][2] * fDivisor;
    aux.ij[2][3] = this->ij[2][3] * fDivisor;
    aux.ij[3][0] = this->ij[3][0] * fDivisor;
    aux.ij[3][1] = this->ij[3][1] * fDivisor;
    aux.ij[3][2] = this->ij[3][2] * fDivisor;
    aux.ij[3][3] = this->ij[3][3] * fDivisor;

    return aux;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &matrix) const
{
    Matrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] + matrix.ij[0][2];
    aux.ij[0][3] = this->ij[0][3] + matrix.ij[0][3];
    aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] + matrix.ij[1][2];
    aux.ij[1][3] = this->ij[1][3] + matrix.ij[1][3];
    aux.ij[2][0] = this->ij[2][0] + matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] + matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] + matrix.ij[2][2];
    aux.ij[2][3] = this->ij[2][3] + matrix.ij[2][3];
    aux.ij[3][0] = this->ij[3][0] + matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][1] + matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][2] + matrix.ij[3][2];
    aux.ij[3][3] = this->ij[3][3] + matrix.ij[3][3];

    return aux;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &matrix) const
{
    Matrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] - matrix.ij[0][2];
    aux.ij[0][3] = this->ij[0][3] - matrix.ij[0][3];
    aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] - matrix.ij[1][2];
    aux.ij[1][3] = this->ij[1][3] - matrix.ij[1][3];
    aux.ij[2][0] = this->ij[2][0] - matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] - matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] - matrix.ij[2][2];
    aux.ij[2][3] = this->ij[2][3] - matrix.ij[2][3];
    aux.ij[3][0] = this->ij[3][0] - matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][1] - matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][2] - matrix.ij[3][2];
    aux.ij[3][3] = this->ij[3][3] - matrix.ij[3][3];

    return aux;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4 &matrix)
{
    Matrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];
    aux.ij[0][3] = this->ij[0][0] * matrix.ij[0][3] + this->ij[0][1] * matrix.ij[1][3] + this->ij[0][2] * matrix.ij[2][3] + this->ij[0][3] * matrix.ij[3][3];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];
    aux.ij[1][3] = this->ij[1][0] * matrix.ij[0][3] + this->ij[1][1] * matrix.ij[1][3] + this->ij[1][2] * matrix.ij[2][3] + this->ij[1][3] * matrix.ij[3][3];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];
    aux.ij[2][3] = this->ij[2][0] * matrix.ij[0][3] + this->ij[2][1] * matrix.ij[1][3] + this->ij[2][2] * matrix.ij[2][3] + this->ij[2][3] * matrix.ij[3][3];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + this->ij[3][3] * matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + this->ij[3][3] * matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + this->ij[3][3] * matrix.ij[3][2];
    aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3] + this->ij[3][3] * matrix.ij[3][3];

    *this = aux;

    return *this;
}

Matrix4x4& Matrix4x4::operator*=(const float_z fScalar)
{
    *this = fScalar * *this;
    return *this;
}

Matrix4x4& Matrix4x4::operator/=(const float_z fScalar)
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    this->ij[0][0] *= fDivisor;
    this->ij[0][1] *= fDivisor;
    this->ij[0][2] *= fDivisor;
    this->ij[0][3] *= fDivisor;
    this->ij[1][0] *= fDivisor;
    this->ij[1][1] *= fDivisor;
    this->ij[1][2] *= fDivisor;
    this->ij[1][3] *= fDivisor;
    this->ij[2][0] *= fDivisor;
    this->ij[2][1] *= fDivisor;
    this->ij[2][2] *= fDivisor;
    this->ij[2][3] *= fDivisor;
    this->ij[3][0] *= fDivisor;
    this->ij[3][1] *= fDivisor;
    this->ij[3][2] *= fDivisor;
    this->ij[3][3] *= fDivisor;

    return *this;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4 &matrix)
{
    this->ij[0][0] += matrix.ij[0][0];
    this->ij[0][1] += matrix.ij[0][1];
    this->ij[0][2] += matrix.ij[0][2];
    this->ij[0][3] += matrix.ij[0][3];
    this->ij[1][0] += matrix.ij[1][0];
    this->ij[1][1] += matrix.ij[1][1];
    this->ij[1][2] += matrix.ij[1][2];
    this->ij[1][3] += matrix.ij[1][3];
    this->ij[2][0] += matrix.ij[2][0];
    this->ij[2][1] += matrix.ij[2][1];
    this->ij[2][2] += matrix.ij[2][2];
    this->ij[2][3] += matrix.ij[2][3];
    this->ij[3][0] += matrix.ij[3][0];
    this->ij[3][1] += matrix.ij[3][1];
    this->ij[3][2] += matrix.ij[3][2];
    this->ij[3][3] += matrix.ij[3][3];

    return *this;
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4 &matrix)
{
    this->ij[0][0] -= matrix.ij[0][0];
    this->ij[0][1] -= matrix.ij[0][1];
    this->ij[0][2] -= matrix.ij[0][2];
    this->ij[0][3] -= matrix.ij[0][3];
    this->ij[1][0] -= matrix.ij[1][0];
    this->ij[1][1] -= matrix.ij[1][1];
    this->ij[1][2] -= matrix.ij[1][2];
    this->ij[1][3] -= matrix.ij[1][3];
    this->ij[2][0] -= matrix.ij[2][0];
    this->ij[2][1] -= matrix.ij[2][1];
    this->ij[2][2] -= matrix.ij[2][2];
    this->ij[2][3] -= matrix.ij[2][3];
    this->ij[3][0] -= matrix.ij[3][0];
    this->ij[3][1] -= matrix.ij[3][1];
    this->ij[3][2] -= matrix.ij[3][2];
    this->ij[3][3] -= matrix.ij[3][3];

    return *this;
}

void Matrix4x4::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = this->ij[2][3] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = this->ij[3][3] = SFloat::_0;
}

void Matrix4x4::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = this->ij[3][3] = SFloat::_1;

    this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][3] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SFloat::_0;
}

Matrix4x4 Matrix4x4::Transpose() const
{
    return Matrix4x4(this->ij[0][0], this->ij[1][0], this->ij[2][0], this->ij[3][0],
                      this->ij[0][1], this->ij[1][1], this->ij[2][1], this->ij[3][1],
                      this->ij[0][2], this->ij[1][2], this->ij[2][2], this->ij[3][2],
                      this->ij[0][3], this->ij[1][3], this->ij[2][3], this->ij[3][3]);
}

bool Matrix4x4::IsZero() const
{
    return    SFloat::IsZero(this->ij[0][0]) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[0][2]) &&
            SFloat::IsZero(this->ij[0][3]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::IsZero(this->ij[1][1]) &&
            SFloat::IsZero(this->ij[1][2]) &&
            SFloat::IsZero(this->ij[1][3]) &&
            SFloat::IsZero(this->ij[2][0]) &&
            SFloat::IsZero(this->ij[2][1]) &&
            SFloat::IsZero(this->ij[2][2]) &&
            SFloat::IsZero(this->ij[2][3]) &&
            SFloat::IsZero(this->ij[3][0]) &&
            SFloat::IsZero(this->ij[3][1]) &&
            SFloat::IsZero(this->ij[3][2]) &&
            SFloat::IsZero(this->ij[3][3]);
}

bool Matrix4x4::IsIdentity() const
{
    return    SFloat::AreEqual(this->ij[0][0], SFloat::_1) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[0][2]) &&
            SFloat::IsZero(this->ij[0][3]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], SFloat::_1) &&
            SFloat::IsZero(this->ij[1][2]) &&
            SFloat::IsZero(this->ij[1][3]) &&
            SFloat::IsZero(this->ij[2][0]) &&
            SFloat::IsZero(this->ij[2][1]) &&
            SFloat::AreEqual(this->ij[2][2], SFloat::_1) &&
            SFloat::IsZero(this->ij[2][3]) &&
            SFloat::IsZero(this->ij[3][0]) &&
            SFloat::IsZero(this->ij[3][1]) &&
            SFloat::IsZero(this->ij[3][2]) &&
            SFloat::AreEqual(this->ij[3][3], SFloat::_1);
}

float_z Matrix4x4::GetDeterminant() const
{
    // Binary products are stored in vars to avoid unnecesary repetitions
    // (each binary product appears 2 times in determinant expresion)
    const float_z& A = this->ij[1][1] * this->ij[2][2];
    const float_z& B = this->ij[1][2] * this->ij[2][3];
    const float_z& C = this->ij[1][3] * this->ij[2][1];
    const float_z& D = this->ij[1][3] * this->ij[2][2];
    const float_z& E = this->ij[1][1] * this->ij[2][3];
    const float_z& F = this->ij[1][2] * this->ij[2][1];
    const float_z& G = this->ij[1][0] * this->ij[2][2];
    const float_z& H = this->ij[1][3] * this->ij[2][0];
    const float_z& I = this->ij[1][0] * this->ij[2][3];
    const float_z& J = this->ij[1][2] * this->ij[2][0];
    const float_z& K = this->ij[1][0] * this->ij[2][1];
    const float_z& L = this->ij[1][1] * this->ij[2][0];

    return this->ij[0][0] * (    A * this->ij[3][3] + B * this->ij[3][1] + C * this->ij[3][2] -
                                D * this->ij[3][1] - E * this->ij[3][2] - F * this->ij[3][3] ) -
            this->ij[0][1] * (    G * this->ij[3][3] + B * this->ij[3][0] + H * this->ij[3][2] -
                                D * this->ij[3][0] - I * this->ij[3][2] - J * this->ij[3][3] ) +
            this->ij[0][2] * (    K * this->ij[3][3] + E * this->ij[3][0] + H * this->ij[3][1] -
                                C * this->ij[3][0] - I * this->ij[3][1] - L * this->ij[3][3] ) -
            this->ij[0][3] * (    K * this->ij[3][2] + A * this->ij[3][0] + J * this->ij[3][1] -
                                F * this->ij[3][0] - G * this->ij[3][1] - L * this->ij[3][2] );
}

Matrix4x4 Matrix4x4::Invert() const
{
    // Based on http://www.cg.info.hiroshima-cu.ac.jp/~miyazaki/knowledge/teche23.html

    // The results will be wrong when the determinant equals zero
    Z_ASSERT_WARNING( this->GetDeterminant() != SFloat::_0, "Matrices whose determinant equals zero do not have inverse" );

    // Gets the inverse of the Determinant.
    const float_z fInvDet = SFloat::_1 / this->GetDeterminant();

    // Binary products are stored in vars to avoid unnecesary repetitions
    // (each binary product appears 4 times in inverse expresion)
    const float_z& fA = this->ij[0][0] * this->ij[1][1];
    const float_z& fB = this->ij[2][2] * this->ij[3][3];
    const float_z& fC = this->ij[0][3] * this->ij[1][2];
    const float_z& fD = this->ij[2][1] * this->ij[3][0];
    const float_z& fE = this->ij[0][1] * this->ij[1][0];
    const float_z& fF = this->ij[0][2] * this->ij[1][3];
    const float_z& fG = this->ij[2][3] * this->ij[3][2];
    const float_z& fH = this->ij[2][0] * this->ij[3][1];
    const float_z& fI = this->ij[2][3] * this->ij[3][1];
    const float_z& fJ = this->ij[2][1] * this->ij[3][2];
    const float_z& fK = this->ij[2][2] * this->ij[3][1];
    const float_z& fL = this->ij[2][1] * this->ij[3][3];
    const float_z& fM = this->ij[2][3] * this->ij[3][0];
    const float_z& fN = this->ij[2][0] * this->ij[3][2];
    const float_z& fO = this->ij[2][2] * this->ij[3][0];
    const float_z& fP = this->ij[2][0] * this->ij[3][3];
    const float_z& fQ = this->ij[0][1] * this->ij[1][2];
    const float_z& fR = this->ij[0][3] * this->ij[1][1];
    const float_z& fS = this->ij[0][1] * this->ij[1][3];
    const float_z& fT = this->ij[0][2] * this->ij[1][1];
    const float_z& fU = this->ij[0][0] * this->ij[1][2];
    const float_z& fV = this->ij[0][3] * this->ij[1][0];
    const float_z& fW = this->ij[0][0] * this->ij[1][3];
    const float_z& fX = this->ij[0][2] * this->ij[1][0];

    return Matrix4x4( fInvDet * (this->ij[1][1] * fB + this->ij[1][2] * fI + this->ij[1][3] * fJ -
                                  this->ij[1][1] * fG - this->ij[1][2] * fL - this->ij[1][3] * fK ),
                       fInvDet * (this->ij[0][1] * fG + this->ij[0][2] * fL + this->ij[0][3] * fK -
                                  this->ij[0][1] * fB - this->ij[0][2] * fI - this->ij[0][3] * fJ ),
                       fInvDet * (fQ * this->ij[3][3] + fF * this->ij[3][1] + fR * this->ij[3][2] -
                                  fS * this->ij[3][2] - fT * this->ij[3][3] - fC * this->ij[3][1] ),
                       fInvDet * (fS * this->ij[2][2] + fT * this->ij[2][3] + fC * this->ij[2][1] -
                                  fQ * this->ij[2][3] - fF * this->ij[2][1] - fR * this->ij[2][2] ),
                       fInvDet * (this->ij[1][0] * fG + this->ij[1][2] * fP + this->ij[1][3] * fO -
                                  this->ij[1][0] * fB - this->ij[1][2] * fM - this->ij[1][3] * fN ),
                       fInvDet * (this->ij[0][0] * fB + this->ij[0][2] * fM + this->ij[0][3] * fN -
                                  this->ij[0][0] * fG - this->ij[0][2] * fP - this->ij[0][3] * fO ),
                       fInvDet * (fW * this->ij[3][2] + fX * this->ij[3][3] + fC * this->ij[3][0] -
                                  fU * this->ij[3][3] - fF * this->ij[3][0] - fV * this->ij[3][2] ),
                       fInvDet * (fU * this->ij[2][3] + fF * this->ij[2][0] + fV * this->ij[2][2] -
                                  fW * this->ij[2][2] - fX * this->ij[2][3] - fC * this->ij[2][0] ),
                       fInvDet * (this->ij[1][0] * fL + this->ij[1][1] * fM + this->ij[1][3] * fH -
                                  this->ij[1][0] * fI - this->ij[1][1] * fP - this->ij[1][3] * fD ),
                       fInvDet * (this->ij[0][0] * fI + this->ij[0][1] * fP + this->ij[0][3] * fD -
                                  this->ij[0][0] * fL - this->ij[0][1] * fM - this->ij[0][3] * fH ),
                       fInvDet * (fA * this->ij[3][3] + fS * this->ij[3][0] + fV * this->ij[3][1] -
                                  fW * this->ij[3][1] - fE * this->ij[3][3] - fR * this->ij[3][0] ),
                       fInvDet * (fW * this->ij[2][1] + fE * this->ij[2][3] + fR * this->ij[2][0] -
                                  fA * this->ij[2][3] - fS * this->ij[2][0] - fV * this->ij[2][1] ),
                       fInvDet * (this->ij[1][0] * fK + this->ij[1][1] * fN + this->ij[1][2] * fD -
                                  this->ij[1][0] * fJ - this->ij[1][1] * fO - this->ij[1][2] * fH ),
                       fInvDet * (this->ij[0][0] * fJ + this->ij[0][1] * fO + this->ij[0][2] * fH -
                                  this->ij[0][0] * fK - this->ij[0][1] * fN - this->ij[0][2] * fD ),
                       fInvDet * (fU * this->ij[3][1] + fE * this->ij[3][2] + fT * this->ij[3][0] -
                                  fA * this->ij[3][2] - fQ * this->ij[3][0] - fX * this->ij[3][1] ),
                       fInvDet * (fA * this->ij[2][2] + fQ * this->ij[2][0] + fX * this->ij[2][1] -
                                  fU * this->ij[2][1] - fE * this->ij[2][2] - fT * this->ij[2][0] ));
}

bool Matrix4x4::HasInverse() const
{
    // If Determinant is 0, this matrix has not inverse.
    return SFloat::IsNotZero(this->GetDeterminant());
}

string_z Matrix4x4::ToString() const
{
    static const string_z STRING_PREFIX("M4x4(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->ij[0][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][3]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][3]);
    strOutput.Append(STRING_END);

    return strOutput;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Matrix4x4& Matrix4x4::GetNullMatrix()
{
    static const Matrix4x4 NULLMATRIX(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0,
                                       SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0,
                                       SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0,
                                       SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLMATRIX;
}

const Matrix4x4& Matrix4x4::GetIdentity()
{
    static const Matrix4x4 IDENTITY(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0,
                                     SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0,
                                     SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0,
                                     SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    return IDENTITY;
}


} // namespace z

