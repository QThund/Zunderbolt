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

#include "ZMath/Vector3.h"

#include "ZCommon/Assertions.h"
#include "ZMath/Quaternion.h"
#include "ZMath/DualQuaternion.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/BaseVector4.h"
#include "ZMath/SAngle.h"
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

Vector3::Vector3()
{
}

Vector3::Vector3(const Vector3 &vVector) : BaseVector3(vVector)
{
}

Vector3::Vector3(const BaseVector3 &vVector) : BaseVector3(vVector)
{
}

Vector3::Vector3(const BaseVector4 &vVector) : BaseVector3(vVector.x, vVector.y, vVector.z)
{
}

Vector3::Vector3(const float_z fValueX, const float_z fValueY, const float_z fValueZ) : BaseVector3(fValueX, fValueY, fValueZ)
{
}

Vector3::Vector3(const float_z fValueAll) : BaseVector3(fValueAll)
{
}

Vector3::Vector3(const float_z* arValues) : BaseVector3(arValues)
{
}

Vector3::Vector3(const vf32_z value) : BaseVector3(value)
{
}

Vector3::Vector3(const TranslationMatrix<Matrix4x3> &translation) :
                       BaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
{
}

Vector3::Vector3(const TranslationMatrix<Matrix4x4> &translation) :
                       BaseVector3(translation.ij[3][0], translation.ij[3][1], translation.ij[3][2])
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

Vector3 Vector3::operator+(const BaseVector3 &vVector) const
{
    return Vector3(this->x + vVector.x, this->y + vVector.y, this->z + vVector.z);
}

Vector3 Vector3::operator-(const BaseVector3 &vVector) const
{
    return Vector3(this->x - vVector.x, this->y - vVector.y, this->z - vVector.z);
}

Vector3 Vector3::operator*(const float_z fScalar) const
{
    return Vector3(this->x * fScalar, this->y * fScalar, this->z * fScalar);
}

Vector3 Vector3::operator*(const BaseVector3 &vVector) const
{
    return Vector3(this->x * vVector.x, this->y * vVector.y, this->z * vVector.z);
}

Vector3 Vector3::operator*(const BaseMatrix3x3 &matrix) const
{
    return Vector3(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                    this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                    this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

}

BaseVector4 Vector3::operator*(const BaseMatrix3x4 &matrix) const
{
    return BaseVector4(this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                        this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                        this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2],
                        this->x * matrix.ij[0][3] + this->y * matrix.ij[1][3] + this->z * matrix.ij[2][3]);

}

Vector3 Vector3::operator/(const float_z fScalar) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING (fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    return Vector3(this->x * DIVISOR, this->y * DIVISOR, this->z * DIVISOR);
}

Vector3 Vector3::operator/(const BaseVector3 &vVector) const
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING (vVector.x != SFloat::_0 && vVector.y != SFloat::_0 && vVector.z != SFloat::_0, "Input vector must not be null");

    return Vector3(this->x / vVector.x, this->y / vVector.y, this->z / vVector.z);
}

Vector3& Vector3::operator+=(const BaseVector3 &vVector)
{
    this->x += vVector.x;
    this->y += vVector.y;
    this->z += vVector.z;

    return *this;
}

Vector3& Vector3::operator-=(const BaseVector3 &vVector)
{
    this->x -= vVector.x;
    this->y -= vVector.y;
    this->z -= vVector.z;

    return *this;
}

Vector3& Vector3::operator*=(const float_z fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;
    this->z *= fScalar;

    return *this;
}

Vector3& Vector3::operator*=(const BaseVector3 &vVector)
{
    this->x *= vVector.x;
    this->y *= vVector.y;
    this->z *= vVector.z;

    return *this;
}

Vector3& Vector3::operator*=(const BaseMatrix3x3 &matrix)
{
    Vector3 vAux( this->x * matrix.ij[0][0] + this->y * matrix.ij[1][0] + this->z * matrix.ij[2][0],
                   this->x * matrix.ij[0][1] + this->y * matrix.ij[1][1] + this->z * matrix.ij[2][1],
                   this->x * matrix.ij[0][2] + this->y * matrix.ij[1][2] + this->z * matrix.ij[2][2]);

    this->x = vAux.x;
    this->y = vAux.y;
    this->z = vAux.z;

    return *this;
}

Vector3 operator*(const float_z fScalar, const Vector3 &vVector)
{
    return Vector3(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar);
}

Vector3& Vector3::operator/=(const float_z fScalar)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1 / fScalar;

    this->x *= DIVISOR;
    this->y *= DIVISOR;
    this->z *= DIVISOR;

    return *this;
}

Vector3& Vector3::operator/=(const BaseVector3 &vVector)
{
    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(vVector.x != SFloat::_0 && vVector.y != SFloat::_0 && vVector.z != SFloat::_0, "Input vector must not be null");

    this->x /= vVector.x;
    this->y /= vVector.y;
    this->z /= vVector.z;

    return *this;
}

Vector3& Vector3::operator=(const BaseVector3 &vVector)
{
    BaseVector3::operator=(vVector);
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-this->x, -this->y, -this->z);
}

float_z Vector3::GetLength() const
{
    return sqrt_z(this->x * this->x + this->y * this->y + this->z * this->z);
}

float_z Vector3::GetSquaredLength() const
{
    return this->x*this->x + this->y*this->y + this->z*this->z;
}

Vector3 Vector3::Normalize() const
{
    // Gets vector length
    float_z fLength = this->GetLength();

    // Checkout to avoid division by 0
    Z_ASSERT_WARNING(fLength != SFloat::_0, "The vector is null so it cannot be normalized, this will cause a division by zero");

    //Normalize
    return Vector3(this->x / fLength, this->y / fLength, this->z / fLength);
}

void Vector3::ResetToOne()
{
    this->x = SFloat::_1;
    this->y = SFloat::_1;
    this->z = SFloat::_1;
}

void Vector3::ResetToZero()
{
    this->x = SFloat::_0;
    this->y = SFloat::_0;
    this->z = SFloat::_0;
}

bool Vector3::IsZero() const
{
    return SFloat::IsZero(this->x) && SFloat::IsZero(this->y) && SFloat::IsZero(this->z);
}

bool Vector3::IsVectorOfOnes() const
{
    return SFloat::AreEqual(this->x, SFloat::_1) && SFloat::AreEqual(this->y, SFloat::_1) && SFloat::AreEqual(this->z, SFloat::_1);
}

float_z Vector3::DotProduct(const BaseVector3 &vVector) const
{
    return(this->x * vVector.x + this->y * vVector.y + this->z * vVector.z);
}

float_z Vector3::AngleBetween(const Vector3 &vVector) const
{
    // Note: Square root is performed outside to avoid loss of precision and gain performance
    float_z fLength = sqrt_z(this->GetSquaredLength() * vVector.GetSquaredLength());

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(fLength != SFloat::_0, "Vectors must not be null, this will cause a division by zero");

    float_z fDot = this->DotProduct(vVector)/fLength;

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

Vector3 Vector3::CrossProduct(const BaseVector3 &vVector) const
{
    return Vector3(this->y * vVector.z - this->z * vVector.y,
                    this->z * vVector.x - this->x * vVector.z,
                    this->x * vVector.y - this->y * vVector.x);
}

Vector3 Vector3::Lerp(const float_z fProportion, const Vector3 &vVector) const
{
    return Vector3(this->x * (SFloat::_1 - fProportion) + vVector.x * fProportion,
                    this->y * (SFloat::_1 - fProportion) + vVector.y * fProportion,
                    this->z * (SFloat::_1 - fProportion) + vVector.z * fProportion);
}

float_z Vector3::Distance(const BaseVector3 &vVector) const
{
    return (*this - vVector).GetLength();
}

Vector3 Vector3::Transform(const Quaternion &qRotation) const
{
    Quaternion qAux(this->x, this->y, this->z, SFloat::_0);
    Quaternion qConj = qRotation.Conjugate();

    qAux = (qRotation * qAux) * qConj;

    return Vector3(qAux.x, qAux.y, qAux.z);
}

Vector3 Vector3::Transform(const DualQuaternion &transformation) const
{
    DualQuaternion dqAux(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                          BaseQuaternion(this->x, this->y, this->z, SFloat::_0));
    DualQuaternion dqConj = transformation.DoubleConjugate();

    dqAux = (transformation * dqAux ) * dqConj;

    return Vector3(dqAux.d.x, dqAux.d.y, dqAux.d.z);
}

Vector3 Vector3::Transform(const SpaceConversionMatrix &conversion) const
{
    return Vector3(this->x * conversion.ij[0][0] + this->y * conversion.ij[1][0] + this->z * conversion.ij[2][0] + conversion.ij[3][0],
                    this->x * conversion.ij[0][1] + this->y * conversion.ij[1][1] + this->z * conversion.ij[2][1] + conversion.ij[3][1],
                    this->x * conversion.ij[0][2] + this->y * conversion.ij[1][2] + this->z * conversion.ij[2][2] + conversion.ij[3][2]);
}

Vector3 Vector3::Transform(const RotationMatrix3x3 &rotation) const
{
    return *this * rotation;
}

Vector3 Vector3::Transform(const ScalingMatrix3x3 &scale) const
{
    return Vector3(this->x * scale.ij[0][0], this->y * scale.ij[1][1], this->z * scale.ij[2][2]);
}

Vector3 Vector3::Transform(const TranslationMatrix<Matrix4x3> &translation) const
{
    return TransformImp(translation);
}

Vector3 Vector3::Transform(const TranslationMatrix<Matrix4x4> &translation) const
{
    return TransformImp(translation);
}

Vector3 Vector3::Transform(const TransformationMatrix<Matrix4x3> &transformation) const
{
    return TransformImp(transformation);
}

Vector3 Vector3::Transform(const TransformationMatrix<Matrix4x4> &transformation) const
{
    return TransformImp(transformation);
}

string_z Vector3::ToString() const
{
    static const string_z STRING_PREFIX("V3(");
    static const string_z STRING_COMMA(",");
    static const string_z STRING_END(")");

    string_z strOutput = STRING_PREFIX;
    strOutput.Append(this->x);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->y);
    strOutput.Append(STRING_COMMA);
    strOutput.Append(this->z);
    strOutput.Append(STRING_END);

    return strOutput;
}

template <class MatrixT>
Vector3 Vector3::TransformImp(const TranslationMatrix<MatrixT> &translation) const
{
    return Vector3(this->x + translation.ij[3][0], this->y + translation.ij[3][1], this->z + translation.ij[3][2]);
}

template <class MatrixT>
Vector3 Vector3::TransformImp(const TransformationMatrix<MatrixT> &transformation) const
{
    return Vector3(this->x * transformation.ij[0][0] + this->y * transformation.ij[1][0] + this->z * transformation.ij[2][0] + transformation.ij[3][0],
                    this->x * transformation.ij[0][1] + this->y * transformation.ij[1][1] + this->z * transformation.ij[2][1] + transformation.ij[3][1],
                    this->x * transformation.ij[0][2] + this->y * transformation.ij[1][2] + this->z * transformation.ij[2][2] + transformation.ij[3][2]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Vector3& Vector3::GetNullVector()
{
    static const Vector3 NULLVECTOR(SFloat::_0,  SFloat::_0,  SFloat::_0);
    return NULLVECTOR;
}

const Vector3& Vector3::GetVectorOfOnes()
{
    static const Vector3 VECTOROFONES(SFloat::_1,  SFloat::_1,  SFloat::_1);
    return VECTOROFONES;
}

const Vector3& Vector3::GetUnitVectorX()
{
    static const Vector3 UNITVECTORX(SFloat::_1,  SFloat::_0,  SFloat::_0);
    return UNITVECTORX;
}

const Vector3& Vector3::GetUnitVectorY()
{
    static const Vector3 UNITVECTORY(SFloat::_0,  SFloat::_1,  SFloat::_0);
    return UNITVECTORY;
}

const Vector3& Vector3::GetUnitVectorZ()
{
    static const Vector3 UNITVECTORZ(SFloat::_0,  SFloat::_0,  SFloat::_1);
    return UNITVECTORZ;
}

const Vector3& Vector3::GetUnitVectorInvX()
{
    static const Vector3 UNITVECTORINVX(-SFloat::_1,  SFloat::_0,  SFloat::_0);
    return UNITVECTORINVX;
}

const Vector3& Vector3::GetUnitVectorInvY()
{
    static const Vector3 UNITVECTORINVY(SFloat::_0,  -SFloat::_1,  SFloat::_0);
    return UNITVECTORINVY;
}

const Vector3& Vector3::GetUnitVectorInvZ()
{
    static const Vector3 UNITVECTORINVZ(SFloat::_0,  SFloat::_0,  -SFloat::_1);
    return UNITVECTORINVZ;
}


} // namespace z
