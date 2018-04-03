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


#include "ZMath/Matrix3x3.h"

#include "ZCommon/Assertions.h"
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

Matrix3x3::Matrix3x3()
{
}

Matrix3x3::Matrix3x3(const Matrix3x3 &matrix) : BaseMatrix3x3(matrix)
{
}

Matrix3x3::Matrix3x3(const BaseMatrix3x3 &matrix) : BaseMatrix3x3(matrix)
{
}

Matrix3x3::Matrix3x3(const float_z fValueAll) : BaseMatrix3x3(fValueAll)
{
}

Matrix3x3::Matrix3x3(const float_z f00, const float_z f01, const float_z f02,
                       const float_z f10, const float_z f11, const float_z f12,
                       const float_z f20, const float_z f21, const float_z f22) :
                          BaseMatrix3x3(f00, f01, f02, f10, f11, f12, f20, f21, f22)
{
}

Matrix3x3::Matrix3x3(const float_z *arValues) : BaseMatrix3x3(arValues)
{
}

Matrix3x3::Matrix3x3(const vf32_z row0, const vf32_z row1, const vf32_z row2) : BaseMatrix3x3(row0, row1, row2)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Matrix3x3 Matrix3x3::operator*(const float_z fScalar) const
{
    Matrix3x3 aux;

    aux.ij[0][0] = fScalar * this->ij[0][0];
    aux.ij[0][1] = fScalar * this->ij[0][1];
    aux.ij[0][2] = fScalar * this->ij[0][2];
    aux.ij[1][0] = fScalar * this->ij[1][0];
    aux.ij[1][1] = fScalar * this->ij[1][1];
    aux.ij[1][2] = fScalar * this->ij[1][2];
    aux.ij[2][0] = fScalar * this->ij[2][0];
    aux.ij[2][1] = fScalar * this->ij[2][1];
    aux.ij[2][2] = fScalar * this->ij[2][2];

    return aux;
}

Matrix3x3 operator*(const float_z fScalar, const Matrix3x3 &matrix)
{

    Matrix3x3 aux;

    aux.ij[0][0] = fScalar * matrix.ij[0][0];
    aux.ij[0][1] = fScalar * matrix.ij[0][1];
    aux.ij[0][2] = fScalar * matrix.ij[0][2];
    aux.ij[1][0] = fScalar * matrix.ij[1][0];
    aux.ij[1][1] = fScalar * matrix.ij[1][1];
    aux.ij[1][2] = fScalar * matrix.ij[1][2];
    aux.ij[2][0] = fScalar * matrix.ij[2][0];
    aux.ij[2][1] = fScalar * matrix.ij[2][1];
    aux.ij[2][2] = fScalar * matrix.ij[2][2];

    return aux;
}

Matrix3x3 Matrix3x3::operator*(const BaseMatrix3x3 &matrix) const
{
    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

    return aux;
}

BaseMatrix3x4 Matrix3x3::operator*(const BaseMatrix3x4& matrix) const
{
    BaseMatrix3x4 aux;

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

    return aux;

}

Matrix3x3& Matrix3x3::operator*=(const float_z fScalar)
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

    return *this;
}

Matrix3x3 Matrix3x3::operator/(const float_z fScalar) const
{

    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] * DIVISOR;
    aux.ij[0][1] = this->ij[0][1] * DIVISOR;
    aux.ij[0][2] = this->ij[0][2] * DIVISOR;
    aux.ij[1][0] = this->ij[1][0] * DIVISOR;
    aux.ij[1][1] = this->ij[1][1] * DIVISOR;
    aux.ij[1][2] = this->ij[1][2] * DIVISOR;
    aux.ij[2][0] = this->ij[2][0] * DIVISOR;
    aux.ij[2][1] = this->ij[2][1] * DIVISOR;
    aux.ij[2][2] = this->ij[2][2] * DIVISOR;

    return aux;
}

Matrix3x3 Matrix3x3::operator+(const BaseMatrix3x3 &matrix) const
{
    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] + matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] + matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] + matrix.ij[0][2];
    aux.ij[1][0] = this->ij[1][0] + matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] + matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] + matrix.ij[1][2];
    aux.ij[2][0] = this->ij[2][0] + matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] + matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] + matrix.ij[2][2];

    return aux;
}

Matrix3x3 Matrix3x3::operator-(const BaseMatrix3x3 &matrix) const
{
    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] - matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][1] - matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][2] - matrix.ij[0][2];
    aux.ij[1][0] = this->ij[1][0] - matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] - matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][2] - matrix.ij[1][2];
    aux.ij[2][0] = this->ij[2][0] - matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][1] - matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] - matrix.ij[2][2];

    return aux;
}

Matrix3x3& Matrix3x3::operator*=(const BaseMatrix3x3 &matrix)
{
    Matrix3x3 aux;

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

    aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
    aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
    aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

    aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

    *this = aux;

    return *this;
}

Matrix3x3& Matrix3x3::operator/=(const float_z fScalar)
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    this->ij[0][0] *= DIVISOR;
    this->ij[0][1] *= DIVISOR;
    this->ij[0][2] *= DIVISOR;
    this->ij[1][0] *= DIVISOR;
    this->ij[1][1] *= DIVISOR;
    this->ij[1][2] *= DIVISOR;
    this->ij[2][0] *= DIVISOR;
    this->ij[2][1] *= DIVISOR;
    this->ij[2][2] *= DIVISOR;

    return *this;
}

Matrix3x3& Matrix3x3::operator+=(const BaseMatrix3x3 &matrix)
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

    return *this;
}

Matrix3x3& Matrix3x3::operator-=(const BaseMatrix3x3 &matrix)
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

    return *this;
}

Matrix3x3& Matrix3x3::operator=(const BaseMatrix3x3 &matrix)
{
    BaseMatrix3x3::operator=(matrix);
    return *this;
}

void Matrix3x3::ResetToZero()
{
    this->ij[0][0] = this->ij[0][1] = this->ij[0][2] =
    this->ij[1][0] = this->ij[1][1] = this->ij[1][2] =
    this->ij[2][0] = this->ij[2][1] = this->ij[2][2] = SFloat::_0;
}

void Matrix3x3::ResetToIdentity()
{
    this->ij[0][0] = this->ij[1][1] = this->ij[2][2] = SFloat::_1;

    this->ij[0][1] = this->ij[0][2] =
    this->ij[1][0] = this->ij[1][2] =
    this->ij[2][0] = this->ij[2][1] = SFloat::_0;
}

Matrix3x3 Matrix3x3::Transpose() const
{
    return Matrix3x3(this->ij[0][0], this->ij[1][0], this->ij[2][0],
                      this->ij[0][1], this->ij[1][1], this->ij[2][1],
                      this->ij[0][2], this->ij[1][2], this->ij[2][2]);
}

bool Matrix3x3::IsZero() const
{
    return  SFloat::IsZero(this->ij[0][0]) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[0][2]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::IsZero(this->ij[1][1]) &&
            SFloat::IsZero(this->ij[1][2]) &&
            SFloat::IsZero(this->ij[2][0]) &&
            SFloat::IsZero(this->ij[2][1]) &&
            SFloat::IsZero(this->ij[2][2]);
}

bool Matrix3x3::IsIdentity() const
{
    return  SFloat::AreEqual(this->ij[0][0], SFloat::_1) &&
            SFloat::IsZero(this->ij[0][1]) &&
            SFloat::IsZero(this->ij[0][2]) &&
            SFloat::IsZero(this->ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], SFloat::_1) &&
            SFloat::IsZero(this->ij[1][2]) &&
            SFloat::IsZero(this->ij[2][0]) &&
            SFloat::IsZero(this->ij[2][1]) &&
            SFloat::AreEqual(this->ij[2][2], SFloat::_1);
}

float_z Matrix3x3::GetDeterminant() const
{
    return this->ij[0][0] * this->ij[1][1] * this->ij[2][2] +
           this->ij[0][1] * this->ij[1][2] * this->ij[2][0] +
           this->ij[0][2] * this->ij[1][0] * this->ij[2][1] -
           this->ij[0][2] * this->ij[1][1] * this->ij[2][0] -
           this->ij[0][0] * this->ij[1][2] * this->ij[2][1] -
           this->ij[0][1] * this->ij[1][0] * this->ij[2][2];
}

Matrix3x3 Matrix3x3::Invert() const
{
    // Gets the inverse of the Determinant.
    const float_z INV_DET = SFloat::_1 / this->GetDeterminant();

    return Matrix3x3( INV_DET * (this->ij[1][1] * this->ij[2][2] - this->ij[1][2] * this->ij[2][1]),
                       INV_DET * (this->ij[0][2] * this->ij[2][1] - this->ij[2][2] * this->ij[0][1]),
                       INV_DET * (this->ij[0][1] * this->ij[1][2] - this->ij[1][1] * this->ij[0][2]),
                       INV_DET * (this->ij[1][2] * this->ij[2][0] - this->ij[2][2] * this->ij[1][0]),
                       INV_DET * (this->ij[0][0] * this->ij[2][2] - this->ij[0][2] * this->ij[2][0]),
                       INV_DET * (this->ij[0][2] * this->ij[1][0] - this->ij[1][2] * this->ij[0][0]),
                       INV_DET * (this->ij[1][0] * this->ij[2][1] - this->ij[2][0] * this->ij[1][1]),
                       INV_DET * (this->ij[0][1] * this->ij[2][0] - this->ij[2][1] * this->ij[0][0]),
                       INV_DET * (this->ij[0][0] * this->ij[1][1] - this->ij[0][1] * this->ij[1][0]) );
}

bool Matrix3x3::HasInverse() const
{
    // If Determinant is 0, this matrix has not inverse.
    return SFloat::IsNotZero(this->GetDeterminant());
}

string_z Matrix3x3::ToString() const
{
    static const string_z STRING_PREFIX("M3x3(");
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

const Matrix3x3& Matrix3x3::GetNullMatrix()
{
    static const Matrix3x3 NULLMATRIX(SFloat::_0, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLMATRIX;
}

const Matrix3x3& Matrix3x3::GetIdentity()
{
    static const Matrix3x3 IDENTITY(SFloat::_1, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_1, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_1);
    return IDENTITY;
}

} // namespace z

