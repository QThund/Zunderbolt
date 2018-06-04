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

#include "ZMath/Matrix2x2.h"

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

Matrix2x2::Matrix2x2()
{
}

Matrix2x2::Matrix2x2(const float_z fValueAll)
{
    ij[0][0] = ij[0][1] =
    ij[1][0] = ij[1][1] = fValueAll;
}

Matrix2x2::Matrix2x2(const float_z f00, const float_z f01, const float_z f10, const float_z f11)
{
    ij[0][0] = f00;
    ij[0][1] = f01;
    ij[1][0] = f10;
    ij[1][1] = f11;
}

Matrix2x2::Matrix2x2(const float_z* arValues)
{
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    ij[0][0] = arValues[0];
    ij[0][1] = arValues[1];
    ij[1][0] = arValues[2];
    ij[1][1] = arValues[3];
}

Matrix2x2::Matrix2x2(const vf32_z value)
{
    SVF32::Unpack(value, this->ij[0][0], this->ij[0][1], this->ij[1][0], this->ij[1][1]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool Matrix2x2::operator==(const Matrix2x2 &matrix) const
{
    return SFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
           SFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
           SFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
           SFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]);
}

bool Matrix2x2::operator!=(const Matrix2x2 &matrix) const
{
    return  !(*this == matrix);
}

Matrix2x2 Matrix2x2::operator*(const float_z fScalar) const
{
    Matrix2x2 aux;

    aux.ij[0][0] = fScalar * this->ij[0][0];
    aux.ij[0][1] = fScalar * this->ij[0][1];
    aux.ij[1][0] = fScalar * this->ij[1][0];
    aux.ij[1][1] = fScalar * this->ij[1][1];

    return aux;
}

Matrix2x2 operator*(const float_z fScalar, const Matrix2x2 &matrix)
{
    Matrix2x2 aux;

    aux.ij[0][0] = fScalar * matrix.ij[0][0];
    aux.ij[0][1] = fScalar * matrix.ij[0][1];
    aux.ij[1][0] = fScalar * matrix.ij[1][0];
    aux.ij[1][1] = fScalar * matrix.ij[1][1];

    return aux;
}

Matrix2x2 Matrix2x2::operator*(const Matrix2x2 &matrix) const
{
    Matrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1];
    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1];

    return aux;
}

Matrix2x2 Matrix2x2::operator/(const float_z fScalar) const
{

    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    Matrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * DIVISOR;
    aux.ij[0][1] = this->ij[0][1] * DIVISOR;
    aux.ij[1][0] = this->ij[1][0] * DIVISOR;
    aux.ij[1][1] = this->ij[1][1] * DIVISOR;

    return aux;
}

Matrix2x2 Matrix2x2::operator+(const Matrix2x2 &matrix) const
{
    Matrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];

    return aux;
}

Matrix2x2 Matrix2x2::operator-(const Matrix2x2 &matrix) const
{
    Matrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
    aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];

    return aux;
}

Matrix2x2& Matrix2x2::operator*=(const float_z fScalar)
{
    this->ij[0][0] *= fScalar;
    this->ij[0][1] *= fScalar;
    this->ij[1][0] *= fScalar;
    this->ij[1][1] *= fScalar;

    return *this;
}

Matrix2x2& Matrix2x2::operator*=(const Matrix2x2 &matrix)
{
    Matrix2x2 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1];
    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1];

    *this = aux;

    return *this;
}

Matrix2x2& Matrix2x2::operator/=(const float_z fScalar)
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    this->ij[0][0] *= DIVISOR;
    this->ij[0][1] *= DIVISOR;
    this->ij[1][0] *= DIVISOR;
    this->ij[1][1] *= DIVISOR;

    return *this;
}

Matrix2x2& Matrix2x2::operator+=(const Matrix2x2 &matrix)
{
    this->ij[0][0] += matrix.ij[0][0];
    this->ij[0][1] += matrix.ij[0][1];
    this->ij[1][0] += matrix.ij[1][0];
    this->ij[1][1] += matrix.ij[1][1];

    return *this;
}

Matrix2x2& Matrix2x2::operator-=(const Matrix2x2 &matrix)
{
    this->ij[0][0] -= matrix.ij[0][0];
    this->ij[0][1] -= matrix.ij[0][1];
    this->ij[1][0] -= matrix.ij[1][0];
    this->ij[1][1] -= matrix.ij[1][1];

    return *this;
}

void Matrix2x2::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] =
    this->ij[1][0] = this->ij[1][1] = SFloat::_0;
}

void Matrix2x2::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = SFloat::_1;
    this->ij[0][1] = this->ij[1][0] = SFloat::_0;
}

Matrix2x2 Matrix2x2::Transpose() const
{
    return Matrix2x2(this->ij[0][0], this->ij[1][0], this->ij[0][1], this->ij[1][1]);
}

bool Matrix2x2::IsZero() const
{
    return  SFloat::IsZero(this->ij[0][0]) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::IsZero(this->ij[1][1]);
}

bool Matrix2x2::IsIdentity() const
{
    return  SFloat::AreEqual(this->ij[0][0], SFloat::_1) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], SFloat::_1);
}

float_z Matrix2x2::GetDeterminant() const
{
    return this->ij[0][0] * this->ij[1][1] - this->ij[0][1] * this->ij[1][0];
}

Matrix2x2 Matrix2x2::Invert() const
{
    // We need inverse of determinant in calculus.
    const float_z INV_DET = SFloat::_1 / this->GetDeterminant();

    return Matrix2x2( INV_DET * this->ij[1][1],
                      -INV_DET * this->ij[0][1],
                      -INV_DET * this->ij[1][0],
                       INV_DET * this->ij[0][0] ); 
}

bool Matrix2x2::HasInverse() const
{
    // If Determinant is 0, this matrix has not inverse.
    return SFloat::IsNotZero(this->GetDeterminant());
}

string_z Matrix2x2::ToString() const
{
    static const string_z STRING_PREFIX("M2x2(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->ij[0][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[0][1]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][0]);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->ij[1][1]);
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

const Matrix2x2& Matrix2x2::GetNullMatrix()
{
    static const Matrix2x2 NULLMATRIX(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLMATRIX;
}

const Matrix2x2& Matrix2x2::GetIdentity()
{
    static const Matrix2x2 IDENTITY(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1);
    return IDENTITY;
}

} // namespace z

