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

#include "ZMath/Matrix3x4.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/Matrix4x3.h"

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

Matrix3x4::Matrix3x4()
{
}

Matrix3x4::Matrix3x4(const float_z fValueAll)
{
    ij[0][0] = ij[0][1] = ij[0][2] = ij[0][3] =
    ij[1][0] = ij[1][1] = ij[1][2] = ij[1][3] =
    ij[2][0] = ij[2][1] = ij[2][2] = ij[2][3] = fValueAll;
}

Matrix3x4::Matrix3x4(const float_z f00, const float_z f01, const float_z f02, const float_z f03,
                     const float_z f10, const float_z f11, const float_z f12, const float_z f13,
                     const float_z f20, const float_z f21, const float_z f22, const float_z f23)
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
}

Matrix3x4::Matrix3x4(const float_z *arValues)
{
    Z_ASSERT_ERROR(arValues != null_z, "Input array must not be null");

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
}

Matrix3x4::Matrix3x4(const vf32_z row0, const vf32_z row1, const vf32_z row2)
{
    SVF32::Unpack(row0, this->ij[0][0], this->ij[0][1], this->ij[0][2], this->ij[0][3]);
    SVF32::Unpack(row1, this->ij[1][0], this->ij[1][1], this->ij[1][2], this->ij[1][3]);
    SVF32::Unpack(row2, this->ij[2][0], this->ij[2][1], this->ij[2][2], this->ij[2][3]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool Matrix3x4::operator==(const Matrix3x4 &matrix) const
{
    return    SFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
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
            SFloat::AreEqual(this->ij[2][3], matrix.ij[2][3]);
}

bool Matrix3x4::operator!=(const Matrix3x4 &matrix) const
{
    return !(*this == matrix);
}

Matrix3x4 Matrix3x4::operator*(const float_z fScalar) const
{
    Matrix3x4 aux;

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

    return aux;
}

Matrix3x4 operator*(const float_z fScalar, const Matrix3x4 &matrix)
{
    Matrix3x4 aux;

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

    return aux;
}

Matrix3x4 Matrix3x4::operator/(const float_z fScalar) const
{

    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    Matrix3x4 aux;

    aux.ij[0][0] = this->ij[0][0] * DIVISOR;
    aux.ij[0][1] = this->ij[0][1] * DIVISOR;
    aux.ij[0][2] = this->ij[0][2] * DIVISOR;
    aux.ij[0][3] = this->ij[0][3] * DIVISOR;
    aux.ij[1][0] = this->ij[1][0] * DIVISOR;
    aux.ij[1][1] = this->ij[1][1] * DIVISOR;
    aux.ij[1][2] = this->ij[1][2] * DIVISOR;
    aux.ij[1][3] = this->ij[1][3] * DIVISOR;
    aux.ij[2][0] = this->ij[2][0] * DIVISOR;
    aux.ij[2][1] = this->ij[2][1] * DIVISOR;
    aux.ij[2][2] = this->ij[2][2] * DIVISOR;
    aux.ij[2][3] = this->ij[2][3] * DIVISOR;

    return aux;
}

Matrix3x4 Matrix3x4::operator+(const Matrix3x4 &matrix) const
{
    Matrix3x4 aux;

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

    return aux;
}

Matrix3x4 Matrix3x4::operator-(const Matrix3x4 &matrix) const
{
    Matrix3x4 aux;

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

    return aux;
}

Matrix3x3 Matrix3x4::operator*(const Matrix4x3 &matrix) const
{
    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0] + this->ij[0][3] * matrix.ij[3][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1] + this->ij[0][3] * matrix.ij[3][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2] + this->ij[0][3] * matrix.ij[3][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0] + this->ij[1][3] * matrix.ij[3][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1] + this->ij[1][3] * matrix.ij[3][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2] + this->ij[1][3] * matrix.ij[3][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0] + this->ij[2][3] * matrix.ij[3][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1] + this->ij[2][3] * matrix.ij[3][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2] + this->ij[2][3] * matrix.ij[3][2];

    return aux;
}

Matrix3x4 Matrix3x4::operator*(const Matrix4x4 &matrix) const
{
    Matrix3x4 aux;

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

    return aux;
}

Matrix3x4& Matrix3x4::operator/=(const float_z fScalar)
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

    return *this;
}

Matrix3x4& Matrix3x4::operator+=(const Matrix3x4 &matrix)
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

    return *this;
}

Matrix3x4& Matrix3x4::operator-=(const Matrix3x4 &matrix)
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

    return *this;
}

Matrix3x4& Matrix3x4::operator*=(const float_z fScalar)
{
    this->ij[0][0] *= fScalar;
    this->ij[0][1] *= fScalar;
    this->ij[0][2] *= fScalar;
    this->ij[0][3] *= fScalar;
    this->ij[1][0] *= fScalar;
    this->ij[1][1] *= fScalar;
    this->ij[1][2] *= fScalar;
    this->ij[1][3] *= fScalar;
    this->ij[2][0] *= fScalar;
    this->ij[2][1] *= fScalar;
    this->ij[2][2] *= fScalar;
    this->ij[2][3] *= fScalar;

    return *this;
}

Matrix3x4& Matrix3x4::operator*=(const Matrix4x4 &matrix)
{
    Matrix3x4 aux;

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

    *this = aux;

    return *this;
}

void Matrix3x4::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][1] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = this->ij[2][3] = SFloat::_0;
}

Matrix4x3 Matrix3x4::Transpose() const
{
    return Matrix4x3(this->ij[0][0], this->ij[1][0], this->ij[2][0],
                            this->ij[0][1], this->ij[1][1], this->ij[2][1],
                            this->ij[0][2], this->ij[1][2], this->ij[2][2],
                            this->ij[0][3], this->ij[1][3], this->ij[2][3]);
}

bool Matrix3x4::IsZero() const
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
            SFloat::IsZero(this->ij[2][3]);
}

void Matrix3x4::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = SFloat::_1;

    this->ij[0][1] = this->ij[0][2] = this->ij[0][3] =
    this->ij[1][0] = this->ij[1][2] = this->ij[1][3] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][3] = SFloat::_0;
}

string_z Matrix3x4::ToString() const
{
    static const string_z STRING_PREFIX("M3x4(");
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

const Matrix3x4& Matrix3x4::GetNullMatrix()
{
    static const Matrix3x4 NULLMATRIX(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0,
                                       SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0,
                                       SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLMATRIX;
}

const Matrix3x4& Matrix3x4::GetIdentity()
{
    static const Matrix3x4 IDENTITY(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0,
                                     SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0,
                                     SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0);
    return IDENTITY;
}


} // namespace z

