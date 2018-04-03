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

#include "ZMath/Matrix4x3.h"

#include "ZCommon/Assertions.h"
#include "ZMath/Matrix3x3.h"
#include "ZCommon/DataTypes/SFloat.h"



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

Matrix4x3::Matrix4x3()
{
}

Matrix4x3::Matrix4x3(const Matrix4x3 &matrix) : BaseMatrix4x3(matrix)
{
}

Matrix4x3::Matrix4x3(const BaseMatrix4x3 &matrix) : BaseMatrix4x3(matrix)
{
}

Matrix4x3::Matrix4x3(const float_z fValueAll) : BaseMatrix4x3(fValueAll)
{
}

Matrix4x3::Matrix4x3(const float_z f00, const float_z f01, const float_z f02,
                       const float_z f10, const float_z f11, const float_z f12,
                       const float_z f20, const float_z f21, const float_z f22,
                       const float_z f30, const float_z f31, const float_z f32) :
                            BaseMatrix4x3(f00, f01, f02, f10, f11, f12, f20, f21, f22, f30, f31, f32)
{
}

Matrix4x3::Matrix4x3(const float_z* arValues) : BaseMatrix4x3(arValues)
{
}

Matrix4x3::Matrix4x3(const vf32_z row0, const vf32_z row1, const vf32_z row2, const vf32_z &row3) :
                            BaseMatrix4x3(row0, row1, row2, row3)
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

Matrix4x3 Matrix4x3::operator*(const float_z fScalar) const
{
    Matrix4x3 aux;

    aux.ij[0][0] = fScalar * this->ij[0][0];
    aux.ij[0][1] = fScalar * this->ij[0][1];
    aux.ij[0][2] = fScalar * this->ij[0][2];
    aux.ij[1][0] = fScalar * this->ij[1][0];
    aux.ij[1][1] = fScalar * this->ij[1][1];
    aux.ij[1][2] = fScalar * this->ij[1][2];
    aux.ij[2][0] = fScalar * this->ij[2][0];
    aux.ij[2][1] = fScalar * this->ij[2][1];
    aux.ij[2][2] = fScalar * this->ij[2][2];
    aux.ij[3][0] = fScalar * this->ij[3][0];
    aux.ij[3][1] = fScalar * this->ij[3][1];
    aux.ij[3][2] = fScalar * this->ij[3][2];

    return aux;
}

Matrix4x3 operator*(const float_z fScalar, const Matrix4x3 &matrix)
{
    Matrix4x3 aux;

    aux.ij[0][0] = fScalar * matrix.ij[0][0];
    aux.ij[0][1] = fScalar * matrix.ij[0][1];
    aux.ij[0][2] = fScalar * matrix.ij[0][2];
    aux.ij[1][0] = fScalar * matrix.ij[1][0];
    aux.ij[1][1] = fScalar * matrix.ij[1][1];
    aux.ij[1][2] = fScalar * matrix.ij[1][2];
    aux.ij[2][0] = fScalar * matrix.ij[2][0];
    aux.ij[2][1] = fScalar * matrix.ij[2][1];
    aux.ij[2][2] = fScalar * matrix.ij[2][2];
    aux.ij[3][0] = fScalar * matrix.ij[3][0];
    aux.ij[3][1] = fScalar * matrix.ij[3][1];
    aux.ij[3][2] = fScalar * matrix.ij[3][2];

    return aux;
}

Matrix4x3 Matrix4x3::operator*(const BaseMatrix3x3& matrix) const
{
    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

    return aux;
}

BaseMatrix4x4 Matrix4x3::operator*(const BaseMatrix3x4& matrix) const
{
    BaseMatrix4x4 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];
    aux.ij[0][3] = this->ij[0][0] * matrix.ij[0][3] + this->ij[0][1] * matrix.ij[1][3] + this->ij[0][2] * matrix.ij[2][3];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];
    aux.ij[1][3] = this->ij[1][0] * matrix.ij[0][3] + this->ij[1][1] * matrix.ij[1][3] + this->ij[1][2] * matrix.ij[2][3];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];
    aux.ij[2][3] = this->ij[2][0] * matrix.ij[0][3] + this->ij[2][1] * matrix.ij[1][3] + this->ij[2][2] * matrix.ij[2][3];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];
    aux.ij[3][3] = this->ij[3][0] * matrix.ij[0][3] + this->ij[3][1] * matrix.ij[1][3] + this->ij[3][2] * matrix.ij[2][3];

    return aux;
}

Matrix4x3& Matrix4x3::operator*=(const float_z fScalar)
{
    this->ij[0][0] *= fScalar;
    this->ij[0][1] *= fScalar;
    this->ij[0][2] *= fScalar;
    this->ij[1][0] *= fScalar;
    this->ij[1][1] *= fScalar;
    this->ij[1][2] *= fScalar;
    this->ij[2][0] *= fScalar;
    this->ij[2][1] *= fScalar;
    this->ij[2][2] *= fScalar;
    this->ij[3][0] *= fScalar;
    this->ij[3][1] *= fScalar;
    this->ij[3][2] *= fScalar;

    return *this;
}

Matrix4x3& Matrix4x3::operator*=(const BaseMatrix3x3& matrix)
{
    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

    aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
    aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
    aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

    *this = aux;

    return *this;
}

Matrix4x3 Matrix4x3::operator/(const float_z fScalar) const
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] * fDivisor;
    aux.ij[0][1] = this->ij[0][1] * fDivisor;
    aux.ij[0][2] = this->ij[0][2] * fDivisor;
    aux.ij[1][0] = this->ij[1][0] * fDivisor;
    aux.ij[1][1] = this->ij[1][1] * fDivisor;
    aux.ij[1][2] = this->ij[1][2] * fDivisor;
    aux.ij[2][0] = this->ij[2][0] * fDivisor;
    aux.ij[2][1] = this->ij[2][1] * fDivisor;
    aux.ij[2][2] = this->ij[2][2] * fDivisor;
    aux.ij[3][0] = this->ij[3][0] * fDivisor;
    aux.ij[3][1] = this->ij[3][1] * fDivisor;
    aux.ij[3][2] = this->ij[3][2] * fDivisor;

    return aux;
}

Matrix4x3 Matrix4x3::operator+(const BaseMatrix4x3 &matrix) const
{
    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] + matrix.ij[0][2];
    aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] + matrix.ij[1][2];
    aux.ij[2][0] = this->ij[2][0] + matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] + matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] + matrix.ij[2][2];
    aux.ij[3][0] = this->ij[3][0] + matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][1] + matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][2] + matrix.ij[3][2];

    return aux;
}

Matrix4x3 Matrix4x3::operator-(const BaseMatrix4x3 &matrix) const
{
    Matrix4x3 aux;

    aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] - matrix.ij[0][2];
    aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] - matrix.ij[1][2];
    aux.ij[2][0] = this->ij[2][0] - matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] - matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] - matrix.ij[2][2];
    aux.ij[3][0] = this->ij[3][0] - matrix.ij[3][0];
    aux.ij[3][1] = this->ij[3][1] - matrix.ij[3][1];
    aux.ij[3][2] = this->ij[3][2] - matrix.ij[3][2];

    return aux;
}

Matrix4x3& Matrix4x3::operator/=(const float_z fScalar)
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    this->ij[0][0] *= fDivisor;
    this->ij[0][1] *= fDivisor;
    this->ij[0][2] *= fDivisor;
    this->ij[1][0] *= fDivisor;
    this->ij[1][1] *= fDivisor;
    this->ij[1][2] *= fDivisor;
    this->ij[2][0] *= fDivisor;
    this->ij[2][1] *= fDivisor;
    this->ij[2][2] *= fDivisor;
    this->ij[3][0] *= fDivisor;
    this->ij[3][1] *= fDivisor;
    this->ij[3][2] *= fDivisor;

    return *this;
}

Matrix4x3& Matrix4x3::operator+=(const BaseMatrix4x3 &matrix)
{
    this->ij[0][0] += matrix.ij[0][0];
    this->ij[0][1] += matrix.ij[0][1];
    this->ij[0][2] += matrix.ij[0][2];
    this->ij[1][0] += matrix.ij[1][0];
    this->ij[1][1] += matrix.ij[1][1];
    this->ij[1][2] += matrix.ij[1][2];
    this->ij[2][0] += matrix.ij[2][0];
    this->ij[2][1] += matrix.ij[2][1];
    this->ij[2][2] += matrix.ij[2][2];
    this->ij[3][0] += matrix.ij[3][0];
    this->ij[3][1] += matrix.ij[3][1];
    this->ij[3][2] += matrix.ij[3][2];

    return *this;
}

Matrix4x3& Matrix4x3::operator-=(const BaseMatrix4x3 &matrix)
{
    this->ij[0][0] -= matrix.ij[0][0];
    this->ij[0][1] -= matrix.ij[0][1];
    this->ij[0][2] -= matrix.ij[0][2];
    this->ij[1][0] -= matrix.ij[1][0];
    this->ij[1][1] -= matrix.ij[1][1];
    this->ij[1][2] -= matrix.ij[1][2];
    this->ij[2][0] -= matrix.ij[2][0];
    this->ij[2][1] -= matrix.ij[2][1];
    this->ij[2][2] -= matrix.ij[2][2];
    this->ij[3][0] -= matrix.ij[3][0];
    this->ij[3][1] -= matrix.ij[3][1];
    this->ij[3][2] -= matrix.ij[3][2];

    return *this;
}

Matrix4x3& Matrix4x3::operator=(const BaseMatrix4x3 &matrix)
{
    BaseMatrix4x3::operator=(matrix);
    return *this;
}

void Matrix4x3::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] = this->ij[0][2] =
    this->ij[1][0] = this->ij[1][1] = this->ij[1][2] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][2] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SFloat::_0;
}

void Matrix4x3::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = SFloat::_1;
    this->ij[0][1] = this->ij[0][2] =
    this->ij[1][0] = this->ij[1][2] =
    this->ij[2][0] = this->ij[2][1] =
    this->ij[3][0] = this->ij[3][1] = this->ij[3][2] = SFloat::_0;
}

BaseMatrix3x4 Matrix4x3::Transpose() const
{
    return BaseMatrix3x4(this->ij[0][0], this->ij[1][0], this->ij[2][0], this->ij[3][0],
                            this->ij[0][1], this->ij[1][1], this->ij[2][1], this->ij[3][1],
                            this->ij[0][2], this->ij[1][2], this->ij[2][2], this->ij[3][2]);
}

bool Matrix4x3::IsZero() const
{
    return    SFloat::IsZero(this->ij[0][0]) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[0][2]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::IsZero(this->ij[1][1]) &&
            SFloat::IsZero(this->ij[1][2]) &&
            SFloat::IsZero(this->ij[2][0]) &&
            SFloat::IsZero(this->ij[2][1]) &&
            SFloat::IsZero(this->ij[2][2]) &&
            SFloat::IsZero(this->ij[3][0]) &&
            SFloat::IsZero(this->ij[3][1]) &&
            SFloat::IsZero(this->ij[3][2]);
}

string_z Matrix4x3::ToString() const
{
    static const string_z STRING_PREFIX("M4x3(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->ij[0][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[2][2]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[3][2]);
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

const Matrix4x3& Matrix4x3::GetNullMatrix()
{
    static const Matrix4x3 NULLMATRIX(SFloat::_0, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLMATRIX;
}

const Matrix4x3& Matrix4x3::GetIdentity()
{
    static const Matrix4x3 IDENTITY(SFloat::_1, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_1, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_1,
                                        SFloat::_0, SFloat::_0, SFloat::_0);
    return IDENTITY;
}


} // namespace z

