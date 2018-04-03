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

#include "ZMath/Vector2.h"

#include "ZCommon/Assertions.h"
#include "ZMath/SAngle.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/BaseMatrix2x2.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/MathDefinitions.h"



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

Vector2::Vector2()
{
}

Vector2::Vector2(const Vector2 &vVector) : BaseVector2(vVector)
{
}

Vector2::Vector2(const BaseVector2 &vVector) : BaseVector2(vVector)
{
}

Vector2::Vector2(const float_z fValueX, const float_z fValueY) : BaseVector2(fValueX, fValueY)
{
}

Vector2::Vector2(const float_z fValueAll) : BaseVector2(fValueAll)
{
}

Vector2::Vector2(const float_z* arValues) : BaseVector2(arValues)
{
}

Vector2::Vector2(const vf32_z value) : BaseVector2 (value)
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

Vector2 Vector2::operator-() const
{
    return Vector2(-this->x, -this->y);
}

Vector2 Vector2::operator+(const BaseVector2 &vVector) const
{
    return Vector2(this->x + vVector.x, this->y + vVector.y);
}

Vector2 Vector2::operator-(const BaseVector2 &vVector) const
{
    return Vector2(this->x - vVector.x, this->y - vVector.y);
}

Vector2 Vector2::operator*(const float_z fScalar) const
{
    return Vector2(this->x * fScalar, this->y * fScalar);
}

Vector2 Vector2::operator*(const BaseVector2 &vVector) const
{
    return Vector2(this->x * vVector.x, this->y * vVector.y);
}

Vector2 Vector2::operator*(const BaseMatrix2x2 &matrix) const
{
    return Vector2(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1]);
}

Vector2 Vector2::operator/(const float_z fScalar) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    return Vector2(this->x * fDivisor, this->y * fDivisor);
}

Vector2 Vector2::operator/(const BaseVector2 &vVector) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(vVector.x != SFloat::_0 && vVector.y != SFloat::_0, "Input vector must not be null");

    return Vector2(this->x / vVector.x, this->y / vVector.y);
}

Vector2& Vector2::operator+=(const BaseVector2 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;

    return *this;
}

Vector2& Vector2::operator-=(const BaseVector2 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;

    return *this;
}

Vector2& Vector2::operator*=(const float_z fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;

    return *this;
}

Vector2& Vector2::operator*=(const BaseMatrix2x2 &matrix)
{
    float_z fValueX = this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0];
    float_z fValueY = this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1];

    this->x = fValueX;
    this->y = fValueY;

    return *this;
}

Vector2& Vector2::operator*=(const BaseVector2 &vVector)
{
    this->x *= vVector.x;
    this->y *= vVector.y;

    return *this;
}

Vector2& Vector2::operator/=(const float_z fScalar)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must no equal zero");

    const float_z &fDivisor = SFloat::_1/fScalar;

    this->x *= fDivisor;
    this->y *= fDivisor;

    return *this;
}

Vector2& Vector2::operator/=(const BaseVector2 &vVector)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING (vVector.x != SFloat::_0 && vVector.y != SFloat::_0, "Input vector must not be null");

    this->x /= vVector.x;
    this->y /= vVector.y;


    return *this;
}

Vector2& Vector2::operator=(const BaseVector2 &vVector)
{
    BaseVector2::operator=(vVector);
    return *this;
}

// Left float product
Vector2 operator*(const float_z fScalar, const Vector2 &vVector)
{
    return Vector2(vVector.x * fScalar, vVector.y * fScalar);
}

float_z Vector2::GetLength() const
{
    return hypot_z(this->x, this->y);
}

float_z Vector2::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y;
}

Vector2 Vector2::GetPerpendicular() const
{
    return Vector2(this->y, -this->x);
}

Vector2 Vector2::Normalize() const
{
    // Gets vector length
    const float_z fLength = this->GetLength();

    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fLength != SFloat::_0, "The vector is null so it cannot be normalized, this will cause a division by zero");

    //Normalize
    return Vector2(this->x / fLength, this->y / fLength);
}

void Vector2::ResetToOne()
{
    this->x = SFloat::_1;
    this->y = SFloat::_1;
}

void Vector2::ResetToZero()
{
    this->x = SFloat::_0;
    this->y = SFloat::_0;
}

bool Vector2::IsZero() const
{
    return SFloat::IsZero(this->x) && SFloat::IsZero(this->y);
}

bool Vector2::IsVectorOfOnes() const
{
    return SFloat::AreEqual(this->x, SFloat::_1) && SFloat::AreEqual(this->y, SFloat::_1);
}

float_z Vector2::DotProduct(const Vector2 &vVector) const
{
    return this->x * vVector.x + this->y * vVector.y;
}

float_z Vector2::AngleBetween(const Vector2 &vVector) const
{
    // Note: Square root is performed outside to avoid loss of precision and gain performance
    float_z fLengthProd = sqrt_z(this->GetSquaredLength() * vVector.GetSquaredLength());

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(fLengthProd != SFloat::_0, "Vectors must not be null, this will cause a division by zero");

    float_z fDot = this->DotProduct(vVector) / fLengthProd;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(fDot > SFloat::_1)
        fDot = SFloat::_1;
    else if(fDot < -SFloat::_1)
        fDot = -SFloat::_1;

    float_z fAngle = acos_z(fDot);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fAngle), "The resultant angle is NAN" );

    // At this stage we have the angle stored in fAngle expressed in RADIANS.

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

Vector2 Vector2::Lerp(const float_z fProportion, const BaseVector2 &vVector) const
{
    return Vector2(this->x * (SFloat::_1 - fProportion) + vVector.x * fProportion,
                    this->y * (SFloat::_1 - fProportion) + vVector.y * fProportion);
}

float_z Vector2::Distance(const Vector2 &vVector) const
{
    return hypot_z(this->x-vVector.x, this->y-vVector.y);
}

string_z Vector2::ToString() const
{
    static const string_z STRING_PREFIX("V2(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->x);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->y);
    strOutput.Append(STRING_END);

    return strOutput;
}

Vector2 Vector2::Transform(const TransformationMatrix3x3 &matrix) const
{
    return Vector2(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + matrix.ij[2][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + matrix.ij[2][1]);
}

Vector2 Vector2::Transform(const float_z fRotationAngle) const
{
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z fAngleRad = SAngle::DegreesToRadians(fRotationAngle);
    #else
        float_z fAngleRad = fRotationAngle;
    #endif

    const float_z fCosAngle = cos_z(fAngleRad);
    const float_z fSinAngle = sin_z(fAngleRad);

    return Vector2(this->x * fCosAngle - this->y * fSinAngle, this->y * fCosAngle + this->x * fSinAngle);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Vector2& Vector2::GetNullVector()
{
    static const Vector2 NULLVECTOR(SFloat::_0,  SFloat::_0);
    return NULLVECTOR;
}

const Vector2& Vector2::GetVectorOfOnes()
{
    static const Vector2 VECTOROFONES(SFloat::_1,  SFloat::_1);
    return VECTOROFONES;
}

const Vector2& Vector2::GetUnitVectorX()
{
    static const Vector2 UNITVECTORX(SFloat::_1,  SFloat::_0);
    return UNITVECTORX;
}

const Vector2& Vector2::GetUnitVectorY()
{
    static const Vector2 UNITVECTORY(SFloat::_0,  SFloat::_1);
    return UNITVECTORY;
}

const Vector2& Vector2::GetUnitVectorInvX()
{
    static const Vector2 UNITVECTORINVX(-SFloat::_1,  SFloat::_0);
    return UNITVECTORINVX;
}

const Vector2& Vector2::GetUnitVectorInvY()
{
    static const Vector2 UNITVECTORINVY(SFloat::_0,  -SFloat::_1);
    return UNITVECTORINVY;
}

} // namespace z
