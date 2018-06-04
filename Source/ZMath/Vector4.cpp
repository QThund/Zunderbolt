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

#include "ZMath/Vector4.h"

#include "ZCommon/Assertions.h"
#include "ZMath/Quaternion.h"
#include "ZMath/DualQuaternion.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/Vector3.h"
#include "ZMath/SAngle.h"
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

Vector4::Vector4()
{
}

Vector4::Vector4(const Vector3 &vVector) : x(vVector.x), y(vVector.y), z(vVector.z), w(SFloat::_0)
{
}

Vector4::Vector4(const Vector3 &vVector, const float_z &fValue) : x(vVector.x), y(vVector.y), z(vVector.z), w(fValue)
{
}

Vector4::Vector4(const float_z fValueX, const float_z fValueY, const float_z fValueZ, const float_z fValueW) : 
                                                                x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
{
}

Vector4::Vector4(const float_z fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll), w(fValueAll)
{
}

Vector4::Vector4(const float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "Input array must not be null");

    // Assignments
    x = arValues[0];
    y = arValues[1];
    z = arValues[2];
    w = arValues[3];
}

Vector4::Vector4(const vf32_z value)
{
    SVF32::Unpack(value, this->x, this->y, this->z, this->w);
}

Vector4::Vector4(const TranslationMatrix4x3 &translation) :
                       Vector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SFloat::_1)
{
}

Vector4::Vector4(const TranslationMatrix4x4 &translation) :
                       Vector4(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2], SFloat::_1)
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

bool Vector4::operator==(const Vector4 &vVector) const
{
    return SFloat::AreEqual(vVector.x, this->x) && SFloat::AreEqual(vVector.y, this->y) &&
           SFloat::AreEqual(vVector.z, this->z) && SFloat::AreEqual(vVector.w, this->w);
}

bool Vector4::operator!=(const Vector4 &vVector) const
{
    return !(*this == vVector);
}

Vector4 Vector4::operator+(const Vector4 &vVector) const
{
    return Vector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w + vVector.w);
}

Vector4 Vector4::operator+(const Vector3 &vVector) const
{
    return Vector4(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z, this->w);
}

Vector4 Vector4::operator-(const Vector4 &vVector) const
{
    return Vector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w - vVector.w);
}

Vector4 Vector4::operator-(const Vector3 &vVector) const
{
    return Vector4(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z, this->w);
}

Vector4 Vector4::operator*(const float_z fScalar) const
{
    return Vector4(this->x * fScalar, this->y * fScalar, this->z * fScalar, this->w * fScalar);
}

Vector4 Vector4::operator*(const Vector4 &vVector) const
{
    return Vector4(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z, this->w * vVector.w);
}

Vector4 Vector4::operator*(const Matrix4x4 &matrix) const
{
    return Vector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                   this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                   this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2],
                   this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3] + this->w * matrix.ij[3][3]);
}

Vector3 Vector4::operator*(const Matrix4x3 &matrix) const
{
    return Vector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0] + this->w * matrix.ij[3][0],
                   this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1] + this->w * matrix.ij[3][1],
                   this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2] + this->w * matrix.ij[3][2]);

}

Vector4 Vector4::operator/(const float_z fScalar) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1 / fScalar;

    return Vector4(this->x * DIVISOR, this->y * DIVISOR, this->z * DIVISOR, this->w * DIVISOR);
}

Vector4 Vector4::operator/(const Vector4 &vVector) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(vVector.x != SFloat::_0 && vVector.y != SFloat::_0 &&
              vVector.z != SFloat::_0 && vVector.w != SFloat::_0, "Input vector must not be null")

    return Vector4(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z, this->w / vVector.w);
}

Vector4& Vector4::operator+=(const Vector4 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;
    this->w += vVector.w;

    return *this;
}

Vector4& Vector4::operator+=(const Vector3 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;

    return *this;
}

Vector4& Vector4::operator-=(const Vector4 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;
    this->w -= vVector.w;

    return *this;
}

Vector4& Vector4::operator-=(const Vector3 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;

    return *this;
}

Vector4& Vector4::operator*=(const float_z fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;
    this->z *= fScalar;
    this->w *= fScalar;

    return *this;
}

Vector4& Vector4::operator*=(const Vector4 &vVector)
{
    this->x *= vVector.x;
    this->y *= vVector.y;
    this->z *= vVector.z;
    this->w *= vVector.w;

    return *this;
}

Vector4& Vector4::operator*=(const Matrix4x4 &matrix)
{
    Vector4 vAux(*this);

    this->x = vAux.x * matrix.ij[0][0] + vAux.y * matrix.ij[1][0] + vAux.z * matrix.ij[2][0] + vAux.w * matrix.ij[3][0];
    this->y = vAux.x * matrix.ij[0][1] + vAux.y * matrix.ij[1][1] + vAux.z * matrix.ij[2][1] + vAux.w * matrix.ij[3][1];
    this->z = vAux.x * matrix.ij[0][2] + vAux.y * matrix.ij[1][2] + vAux.z * matrix.ij[2][2] + vAux.w * matrix.ij[3][2];
    this->w = vAux.x * matrix.ij[0][3] + vAux.y * matrix.ij[1][3] + vAux.z * matrix.ij[2][3] + vAux.w * matrix.ij[3][3];

    return *this;
}

Vector4& Vector4::operator/=(const float_z fScalar)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1 / fScalar;

    this->x *= DIVISOR;
    this->y *= DIVISOR;
    this->z *= DIVISOR;
    this->w *= DIVISOR;

    return *this;
}

Vector4& Vector4::operator/=(const Vector4 &vVector)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING (vVector.x != SFloat::_0 && vVector.y != SFloat::_0 && vVector.z != SFloat::_0 && vVector.w != SFloat::_0, 
               "Input vector must not be null")

    this->x /= vVector.x;
    this->y /= vVector.y;
    this->z /= vVector.z;
    this->w /= vVector.w;

    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4(-this->x, -this->y, -this->z, -this->w);
}

// Left float product
Vector4 operator*(const float_z fScalar, const Vector4 &vVector)
{
    return Vector4(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar, vVector.w * fScalar);
}

float_z Vector4::GetLength() const
{
    return sqrt_z(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

float_z Vector4::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w;
}

Vector4 Vector4::Normalize() const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(this->GetLength() != SFloat::_0, "The vector is null so it cannot be normalized, this will cause a division by zero");

    // Gets inverse of the vector length
    float_z fInvLength = SFloat::_1 / this->GetLength();

    //Normalize
    return Vector4(this->x * fInvLength, this->y * fInvLength, this->z * fInvLength, this->w * fInvLength);
}

void Vector4::ResetToOne()
{
    this->x = SFloat::_1;
    this->y = SFloat::_1;
    this->z = SFloat::_1;
    this->w = SFloat::_1;
}

void Vector4::ResetToZeroPoint()
{
    this->x = SFloat::_0;
    this->y = SFloat::_0;
    this->z = SFloat::_0;
    this->w = SFloat::_1;
}

void Vector4::ResetToZeroVector()
{
    this->x = SFloat::_0;
    this->y = SFloat::_0;
    this->z = SFloat::_0;
    this->w = SFloat::_0;
}
    
bool Vector4::IsZero() const
{
    return SFloat::IsZero(this->x) && SFloat::IsZero(this->y) &&
            SFloat::IsZero(this->z) && SFloat::IsZero(this->w);
}

bool Vector4::IsVectorOfOnes() const
{
    return SFloat::AreEqual(this->x, SFloat::_1) && SFloat::AreEqual(this->y, SFloat::_1) &&
            SFloat::AreEqual(this->z, SFloat::_1) && SFloat::AreEqual(this->w, SFloat::_1);
}

float_z Vector4::DotProduct(const Vector4 &vVector) const
{
    return this->x * vVector.x + this->y * vVector.y + this->z * vVector.z;
}

float_z Vector4::AngleBetween(const Vector4 &vVector) const
{
    float_z fLength = sqrt_z( (this->x*this->x + this->y*this->y + this->z*this->z) * (vVector.x*vVector.x + vVector.y*vVector.y + vVector.z*vVector.z) );

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(fLength != SFloat::_0, "Vectors must not be null, this will cause a division by zero");

    float_z fDot = (this->x*vVector.x + this->y*vVector.y + this->z*vVector.z) / fLength;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(fDot > SFloat::_1)
        fDot = SFloat::_1;
    else if(fDot < -SFloat::_1)
        fDot = -SFloat::_1;

    float_z fAngle = acos_z(fDot);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fAngle), "The resultant angle is NAN" );

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

Vector4 Vector4::CrossProduct(const Vector4 &vVector) const
{
    return Vector4(this->y * vVector.z - this->z * vVector.y,
                    this->z * vVector.x - this->x * vVector.z,
                    this->x * vVector.y - this->y * vVector.x,
                    this->w);
}

Vector4 Vector4::Lerp(const float_z fProportion, const Vector4 &vVector) const
{
    return Vector4(this->x * (SFloat::_1 - fProportion) + vVector.x * fProportion,
                    this->y * (SFloat::_1 - fProportion) + vVector.y * fProportion,
                    this->z * (SFloat::_1 - fProportion) + vVector.z * fProportion,
                    this->w * (SFloat::_1 - fProportion) + vVector.w * fProportion);
}

float_z Vector4::Distance(const Vector4 &vVector) const
{
    return sqrt_z( (this->x - vVector.x)*(this->x - vVector.x) + (this->y - vVector.y)*(this->y - vVector.y) +
                    (this->z - vVector.z)*(this->z - vVector.z) );
}

Vector4 Vector4::Homogenize() const
{
    Vector4 homogenizedVector;

    if(this->w != SFloat::_0) // Exactly zero
    {
        float_z fInvW = SFloat::_1 / this->w;
        homogenizedVector = Vector4(this->x * fInvW, this->y * fInvW, this->z * fInvW, SFloat::_1);
    }
    else
    {
        homogenizedVector = *this;
    }

    return homogenizedVector;
}

Vector4 Vector4::Transform(const Quaternion &qRotation) const
{
    Quaternion qAux(this->x, this->y, this->z, SFloat::_0);
    Quaternion qConj = qRotation.Conjugate();

    qAux = (qRotation * qAux) * qConj;

    return Vector4(qAux.x, qAux.y, qAux.z, this->w);
}

Vector4 Vector4::Transform(const DualQuaternion &transformation) const
{
    DualQuaternion dqAux(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                          Quaternion(this->x, this->y, this->z, SFloat::_0));
    DualQuaternion dqConj = transformation.DoubleConjugate();

    dqAux = (transformation * dqAux ) * dqConj;

    return Vector4(dqAux.d.x, dqAux.d.y, dqAux.d.z, this->w);
}

Vector4 Vector4::Transform(const RotationMatrix3x3 &rotation) const
{
    return Vector4(this->x * rotation.ij[0][0] + this->y * rotation.ij[1][0] + this->z * rotation.ij[2][0],
                    this->x * rotation.ij[0][1] + this->y * rotation.ij[1][1] + this->z * rotation.ij[2][1],
                    this->x * rotation.ij[0][2] + this->y * rotation.ij[1][2] + this->z * rotation.ij[2][2],
                    this->w);
}

Vector4 Vector4::Transform(const ScalingMatrix3x3 &scale) const
{
    return Vector4(this->x * scale.ij[0][0], this->y * scale.ij[1][1], this->z * scale.ij[2][2], this->w);
}

Vector4 Vector4::Transform(const TranslationMatrix4x3 &translation) const
{
    return TransformImp(translation);
}


Vector4 Vector4::Transform(const TranslationMatrix4x4 &translation) const
{
    return TransformImp(translation);
}

Vector4 Vector4::Transform(const TransformationMatrix4x3 &transformation) const
{
    return TransformImp(transformation);
}


Vector4 Vector4::Transform(const TransformationMatrix4x4 &transformation) const
{
    return TransformImp(transformation);
}

Vector4 Vector4::Transform(const SpaceConversionMatrix &conversion) const
{
    return *this * conversion;
}

string_z Vector4::ToString() const
{
    static const string_z STRING_PREFIX("V4(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->x);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->y);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->z);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->w);
    strOutput.Append(STRING_END);

    return strOutput;
}

template <class MatrixT>
Vector4 Vector4::TransformImp(const Internals::TranslationMatrix<MatrixT> &translation) const
{
    return Vector4(this->x + this->w * translation.ij[3][0],
                   this->y + this->w * translation.ij[3][1],
                   this->z + this->w * translation.ij[3][2],
                   this->w);
}

/// <summary>
/// Applies a translation to resident vector, multiplying the vector by a translation matrix
/// to transform it. The translation takes effect depending on if resident vector represents a 3D point
/// \f$(v_x, v_y, v_z, 1)\f$ or a 3D vector \f$(v_x, v_y, v_z, 0)\f$,
/// since a 3D vector cannot be displaced.
/// </summary>
/// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
/// <param name="translation">[IN] The translation matrix. It must be a 4x3 or a 4x4 translation matrix.</param>
/// <returns>
/// The transformed vector.
/// </returns>
template <class MatrixT>
Vector4 Vector4::TransformImp(const Internals::TransformationMatrix<MatrixT> &transformation) const
{
    return Vector4(this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + this->w * transformation.ij[3][0],
                    this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + this->w * transformation.ij[3][1],
                    this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + this->w * transformation.ij[3][2],
                    this->w);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Vector4& Vector4::GetZeroPoint()
{
    static const Vector4 ZEROPOINT(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    return ZEROPOINT;
}

const Vector4& Vector4::GetNullVector()
{
    static const Vector4 NULLVECTOR(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    return NULLVECTOR;
}

const Vector4& Vector4::GetVectorOfOnes()
{
    static const Vector4 VECTOROFONES(SFloat::_1,  SFloat::_1,  SFloat::_1, SFloat::_1);
    return VECTOROFONES;
}

const Vector4& Vector4::GetUnitVectorX()
{
    static const Vector4 UNITVECTORX(SFloat::_1,  SFloat::_0,  SFloat::_0, SFloat::_0);
    return UNITVECTORX;
}

const Vector4& Vector4::GetUnitVectorY()
{
    static const Vector4 UNITVECTORY(SFloat::_0,  SFloat::_1,  SFloat::_0, SFloat::_0);
    return UNITVECTORY;
}

const Vector4& Vector4::GetUnitVectorZ()
{
    static const Vector4 UNITVECTORZ(SFloat::_0,  SFloat::_0,  SFloat::_1, SFloat::_0);
    return UNITVECTORZ;
}

const Vector4& Vector4::GetUnitVectorInvX()
{
    static const Vector4 UNITVECTORINVX(-SFloat::_1,  SFloat::_0,  SFloat::_0, SFloat::_0);
    return UNITVECTORINVX;
}

const Vector4& Vector4::GetUnitVectorInvY()
{
    static const Vector4 UNITVECTORINVY(SFloat::_0,  -SFloat::_1,  SFloat::_0, SFloat::_0);
    return UNITVECTORINVY;
}

const Vector4& Vector4::GetUnitVectorInvZ()
{
    static const Vector4 UNITVECTORINVZ(SFloat::_0,  SFloat::_0,  -SFloat::_1, SFloat::_0);
    return UNITVECTORINVZ;
}


} // namespace z
