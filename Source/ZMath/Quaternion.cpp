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

#include "ZMath/Quaternion.h"
#include "ZMath/MathDefinitions.h"

#include "ZCommon/Assertions.h"
#include "ZMath/SAngle.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"



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

Quaternion::Quaternion() : BaseQuaternion()
{
}

Quaternion::Quaternion(const Quaternion &qQuat) : BaseQuaternion(qQuat)
{
}

Quaternion::Quaternion(const BaseQuaternion &qQuat) : BaseQuaternion(qQuat)
{
}

Quaternion::Quaternion(const float_z fRotationAngleX, const float_z fRotationAngleY, const float_z fRotationAngleZ)
{
    // Calculates half angle
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& HALF_ANGLE_X_RAD = SAngle::DegreesToRadians(fRotationAngleX) * SFloat::_0_5;
        const float_z& HALF_ANGLE_Y_RAD = SAngle::DegreesToRadians(fRotationAngleY) * SFloat::_0_5;
        const float_z& HALF_ANGLE_Z_RAD = SAngle::DegreesToRadians(fRotationAngleZ) * SFloat::_0_5;
    #else
        const float_z& HALF_ANGLE_X_RAD = fRotationAngleX * SFloat::_0_5;
        const float_z& HALF_ANGLE_Y_RAD = fRotationAngleY * SFloat::_0_5;
        const float_z& HALF_ANGLE_Z_RAD = fRotationAngleZ * SFloat::_0_5;
    #endif

    const float_z cx = cos_z(HALF_ANGLE_X_RAD);
    const float_z cy = cos_z(HALF_ANGLE_Y_RAD);
    const float_z cz = cos_z(HALF_ANGLE_Z_RAD);
    const float_z sx = sin_z(HALF_ANGLE_X_RAD);
    const float_z sy = sin_z(HALF_ANGLE_Y_RAD);
    const float_z sz = sin_z(HALF_ANGLE_Z_RAD);

    this->w =  cy * cx * cz + sy * sx * sz;
    this->x =  cy * sx * cz + sy * cx * sz;
    this->y = -cy * sx * sz + sy * cx * cz;
    this->z = -sy * sx * cz + cy * cx * sz;
}

Quaternion::Quaternion(const float_z fValueX, const float_z fValueY, const float_z fValueZ, const float_z fValueW) :
                           BaseQuaternion(fValueX, fValueY, fValueZ, fValueW)
{
}

Quaternion::Quaternion(const float_z* arValues) : BaseQuaternion(arValues)
{
}

Quaternion::Quaternion(const vf32_z value) : BaseQuaternion(value)
{
}

Quaternion::Quaternion(const BaseVector3 &vRotationAxis, const float_z fRotationAngle)
{
    // Calculates half angle
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& HALF_ANGLE_RAD = SAngle::DegreesToRadians(fRotationAngle) * SFloat::_0_5;
    #else
        const float_z& HALF_ANGLE_RAD = fRotationAngle * SFloat::_0_5;
    #endif

    const float_z &fSin = sin_z(HALF_ANGLE_RAD);

    // Please note the axis has to be normalized...

    this->x = vRotationAxis.x * fSin;
    this->y = vRotationAxis.y * fSin;
    this->z = vRotationAxis.z * fSin;

    this->w = cos_z(HALF_ANGLE_RAD);
}

Quaternion::Quaternion(const BaseVector4 &vRotationAxis, const float_z fRotationAngle)
{
    // Calculates half angle
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& HALF_ANGLE_RAD = SAngle::DegreesToRadians(fRotationAngle) * SFloat::_0_5;
    #else
        const float_z& HALF_ANGLE_RAD = fRotationAngle * SFloat::_0_5;
    #endif

    const float_z &fSin = sin_z(HALF_ANGLE_RAD);

    // Please note the axis has to be normalized...

    this->x = vRotationAxis.x * fSin;
    this->y = vRotationAxis.y * fSin;
    this->z = vRotationAxis.z * fSin;

    this->w = cos_z(HALF_ANGLE_RAD);
}

Quaternion::Quaternion(const TransformationMatrix<Matrix4x3> &transformation)
{
    this->QuaternionImp(transformation);
}


Quaternion::Quaternion(const TransformationMatrix<Matrix4x4> &transformation)
{
    this->QuaternionImp(transformation);
}


Quaternion::Quaternion(const RotationMatrix3x3 &rotation)
{
    rotation.GetRotation(*this);
}

template <class MatrixT>
void Quaternion::QuaternionImp(const TransformationMatrix<MatrixT> &transformation)
{
    transformation.GetRotation(*this);
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

Quaternion Quaternion::operator+(const BaseQuaternion &qQuat) const
{
    return Quaternion(this->x + qQuat.x,
                       this->y + qQuat.y,
                       this->z + qQuat.z,
                       this->w + qQuat.w);
}

Quaternion Quaternion::operator-(const BaseQuaternion &qQuat) const
{
    return Quaternion(this->x - qQuat.x,
                       this->y - qQuat.y,
                       this->z - qQuat.z,
                       this->w - qQuat.w);
}

Quaternion Quaternion::operator*(const BaseQuaternion &qQuat) const
{
    return Quaternion( qQuat.w * this->x + qQuat.x * this->w + qQuat.y * this->z - qQuat.z * this->y,       // Vx
                        qQuat.w * this->y + qQuat.y * this->w + qQuat.z * this->x - qQuat.x * this->z,       // Vy
                        qQuat.w * this->z + qQuat.z * this->w + qQuat.x * this->y - qQuat.y * this->x,       // Vz
                        qQuat.w * this->w - qQuat.x * this->x - qQuat.y * this->y - qQuat.z * this->z );       // W
}

Quaternion Quaternion::operator*(const float_z fScalar) const
{
    return Quaternion( this->x * fScalar,
                        this->y * fScalar,
                        this->z * fScalar,
                        this->w * fScalar);
}

Quaternion Quaternion::operator*(const BaseVector3 &vVector) const
{
    return *this * Quaternion(vVector.x, vVector.y, vVector.z, SFloat::_0);
}

Quaternion Quaternion::operator*(const BaseVector4 &vVector) const
{
    return *this * Quaternion(vVector.x, vVector.y, vVector.z, vVector.w);
}

Quaternion Quaternion::operator/(const BaseQuaternion &qQuat) const
{
    // Note: Quaternion::Invert method's code copied here. The reason is not to require a Quaternion as a parameter
    //       which would break the coherence of the interface (all operators require BaseQuaternion only). Moreover, if
    //       scast_z was used, then the call to Invert couldn't be inlined here. So, we "inline" it manually.
    const float_z& SQUARED_LENGTH = (qQuat.x * qQuat.x) + (qQuat.y * qQuat.y) + (qQuat.z * qQuat.z) + (qQuat.w * qQuat.w);

    Z_ASSERT_WARNING(SQUARED_LENGTH != SFloat::_0, "Input quaternion must not be null, this will cause a division by zero");

    const float_z& NEG_INV_LENGTH = -SFloat::_1/SQUARED_LENGTH;

    return *this * Quaternion(qQuat.x * NEG_INV_LENGTH, qQuat.y * NEG_INV_LENGTH, qQuat.z * NEG_INV_LENGTH, qQuat.w * -NEG_INV_LENGTH);
}

Quaternion Quaternion::operator/(const float_z fScalar) const
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    return Quaternion( this->x * DIVISOR,
                        this->y * DIVISOR,
                        this->z * DIVISOR,
                        this->w * DIVISOR);
}

Quaternion& Quaternion::operator+=(const BaseQuaternion &qQuat)
{
    this->x += qQuat.x;
    this->y += qQuat.y;
    this->z += qQuat.z;
    this->w += qQuat.w;
    return *this;
}

Quaternion& Quaternion::operator-=(const BaseQuaternion &qQuat)
{
    this->x -= qQuat.x;
    this->y -= qQuat.y;
    this->z -= qQuat.z;
    this->w -= qQuat.w;

    return *this;
}

Quaternion& Quaternion::operator*=(const BaseQuaternion &qQuat)
{
    Quaternion resQuat( qQuat.w * this->x + qQuat.x * this->w + qQuat.y * this->z - qQuat.z * this->y,    // Vx
                         qQuat.w * this->y + qQuat.y * this->w + qQuat.z * this->x - qQuat.x * this->z,    // Vy
                         qQuat.w * this->z + qQuat.z * this->w + qQuat.x * this->y - qQuat.y * this->x,    // Vz
                         qQuat.w * this->w - qQuat.x * this->x - qQuat.y * this->y - qQuat.z * this->z );  // W
    this->x = resQuat.x;
    this->y = resQuat.y;
    this->z = resQuat.z;
    this->w = resQuat.w;

    return *this;
}

Quaternion& Quaternion::operator*=(const float_z fScalar)
{
    this->x *= fScalar;
    this->y *= fScalar;
    this->z *= fScalar;
    this->w *= fScalar;

    return *this;
}

Quaternion& Quaternion::operator*=(const BaseVector3 &vVector)
{
    Quaternion qAux(vVector.x, vVector.y, vVector.z, SFloat::_0);

    *this *= qAux;

    return *this;
}

Quaternion& Quaternion::operator*=(const BaseVector4 &vVector)
{
    Quaternion qAux(vVector.x, vVector.y, vVector.z, vVector.w);

    *this *= qAux;

    return *this;
}

Quaternion& Quaternion::operator/=(const BaseQuaternion &qQuat)
{
    // Note: Quaternion::Invert method's code copied here. The reason is not to require a Quaternion as a parameter
    //       which would break the coherence of the interface (all operators require BaseQuaternion only). Moreover, if
    //       scast_z was used, then the call to Invert couldn't be inlined here. So, we "inline" it manually.
    const float_z& SQUARED_LENGTH = (qQuat.x * qQuat.x) + (qQuat.y * qQuat.y) + (qQuat.z * qQuat.z) + (qQuat.w * qQuat.w);

    Z_ASSERT_WARNING(SQUARED_LENGTH != SFloat::_0, "Input quaternion must not be null, this will cause a division by zero");

    const float_z& NEG_INV_LENGTH = -SFloat::_1/SQUARED_LENGTH;

    *this *= Quaternion(qQuat.x * NEG_INV_LENGTH, qQuat.y * NEG_INV_LENGTH, qQuat.z * NEG_INV_LENGTH, qQuat.w * -NEG_INV_LENGTH);

    return *this;
}

Quaternion& Quaternion::operator/=(const float_z fScalar)
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "Input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    this->x *= DIVISOR;
    this->y *= DIVISOR;
    this->z *= DIVISOR;
    this->w *= DIVISOR;

    return *this;
}

Quaternion& Quaternion::operator=(const BaseQuaternion &qQuat)
{
    BaseQuaternion::operator=(qQuat);
    return *this;
}

Quaternion Quaternion::operator-() const
{
    return Quaternion(-this->x, -this->y, -this->z, -this->w);
}

Quaternion Quaternion::Normalize() const
{
    Z_ASSERT_WARNING(this->GetLength(), "Null quaternions cannot be normalized, this will produce a division by zero");

    const float_z& INV_LENGTH = SFloat::_1 / this->GetLength();

    return Quaternion(this->x * INV_LENGTH, this->y * INV_LENGTH, this->z * INV_LENGTH, this->w * INV_LENGTH);
}

Quaternion Quaternion::Invert() const
{
    // [TODO] Thund: DirectX implementation uses ln(Q) = (0, theta * v), is it faster?
    const float_z& SQUARED_LENGTH = this->GetSquaredLength();

    Z_ASSERT_WARNING(SQUARED_LENGTH != SFloat::_0, "Null quaternions cannot be inverted, this will produce a division by zero");

    const float_z& NEG_INV_LENGTH = -SFloat::_1/SQUARED_LENGTH;

    return Quaternion(this->x * NEG_INV_LENGTH, this->y * NEG_INV_LENGTH, this->z * NEG_INV_LENGTH, this->w * -NEG_INV_LENGTH);
}

Quaternion Quaternion::UnitInvert() const
{
    return this->Conjugate();
}

void Quaternion::ResetToZero()
{
    this->x = this->y = this->z = this->w = SFloat::_0;
}

void Quaternion::ResetToIdentity()
{
    this->x = this->y = this->z = SFloat::_0;
    this->w = SFloat::_1;
}

Quaternion operator*(const float_z fScalar, const Quaternion &qQuat)
{
    return Quaternion( qQuat.x * fScalar, qQuat.y * fScalar, qQuat.z * fScalar, qQuat.w * fScalar);
}

float_z Quaternion::DotProduct(const BaseQuaternion &qQuat) const
{
    return this->x * qQuat.x + this->y * qQuat.y + this->z * qQuat.z + this->w * qQuat.w;
}

float_z Quaternion::AngleBetween(const Quaternion &qQuat) const
{
    // NOTE [Thund]: We should investigate why, if the following product is performed in only
    //               one line, it's different. Tested using MinGW with DOUBLE precision configuration.
    const float_z fInputLength = qQuat.GetLength();
    const float_z fThisLength = this->GetLength();
    const float_z fLengths = fThisLength * fInputLength;

    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(fLengths != SFloat::_0, "uaternions must not be null, this will produce a division by zero");

    float_z fDot = (this->x*qQuat.x + this->y*qQuat.y + this->z*qQuat.z + this->w*qQuat.w)/fLengths;

    // Checkout to avoid undefined values of acos. Remember that -1 <= cos(angle) <= 1.
    Z_ASSERT_WARNING(SFloat::Abs(fDot) <= SFloat::_1, "The value of \"fDor\" must be between -1 and +1");

    float_z fAngle = acos(fDot) * SFloat::_2;

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts angle to degrees
        fAngle = SAngle::RadiansToDegrees(fAngle);
    #endif

    return fAngle;
}

Quaternion Quaternion::Conjugate() const
{
    return Quaternion(-this->x, -this->y, -this->z, this->w);
}

Quaternion Quaternion::Lerp(const float_z fProportion, const Quaternion &qQuat) const
{
    // Separated from the equation to gain performance
    Quaternion qAuxSum(this->x * (SFloat::_1 - fProportion) + qQuat.x * fProportion,
                        this->y * (SFloat::_1 - fProportion) + qQuat.y * fProportion,
                        this->z * (SFloat::_1 - fProportion) + qQuat.z * fProportion,
                        this->w * (SFloat::_1 - fProportion) + qQuat.w * fProportion);

    // Separated from the equation to check for "division by zero"
    float_z fDivisor = ( qAuxSum ).GetLength();

    Z_ASSERT_WARNING(fDivisor != SFloat::_0, "uaternion must not be null and the input proportion must not equal zero, this will produce a division by zero");

    return qAuxSum / fDivisor;
}

Quaternion Quaternion::Slerp(const float_z fProportion, const Quaternion &qQuat) const
{
    Quaternion qReturnValue;

    // Assures that all quaternions are unit length
    Quaternion qNormalizedInputQuat = qQuat.Normalize();
    Quaternion qNormalizedThisQuat = this->Normalize();

    float_z DOT_PRODUCT = qNormalizedThisQuat.DotProduct(qNormalizedInputQuat);

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(DOT_PRODUCT > SFloat::_1)
        DOT_PRODUCT = SFloat::_1;
    else if(DOT_PRODUCT < -SFloat::_1)
        DOT_PRODUCT = -SFloat::_1;

    const float_z ANGLE_B = acos_z(DOT_PRODUCT);

    Z_ASSERT_WARNING( !SFloat::IsNaN(ANGLE_B), "The resultant angle \"ANGLE_B\" is NAN" );

    if( ANGLE_B != SFloat::_0 && SFloat::AreNotEqual(ANGLE_B, PI_Z) )
    {
        const float_z INV_SIN = SFloat::_1/sin_z(ANGLE_B);

        const float_z WEIGHT1 = sin_z((SFloat::_1 - fProportion) * ANGLE_B) * INV_SIN;
        const float_z WEIGHT2 = sin_z(fProportion * ANGLE_B) * INV_SIN;

        // Separated from the equation to gain performance
        const Quaternion AUX_SUM = WEIGHT1 * qNormalizedThisQuat + WEIGHT2 * qNormalizedInputQuat;

        // Separated from the equation to check for "division by zero"
        const float_z DIVISOR = AUX_SUM.GetLength();

        Z_ASSERT_WARNING(DIVISOR != SFloat::_0, "The variable \"DIVISOR\" must not equal zero, this will cause a division by zero");

        qReturnValue = AUX_SUM / DIVISOR;
    }
    else
        qReturnValue = *this;

    return qReturnValue;
}

Quaternion Quaternion::UnitSlerp(const float_z fProportion, const Quaternion &qQuat) const
{
    Quaternion qReturnValue;

    float_z fDot = this->DotProduct(qQuat);

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(fDot > SFloat::_1)
        fDot = SFloat::_1;
    else if(fDot < -SFloat::_1)
        fDot = -SFloat::_1;

    const float_z& ANGLE_B = acos_z(fDot);

    Z_ASSERT_WARNING( !SFloat::IsNaN(ANGLE_B), "The resultant angle \"ANGLE_B\" is NAN" );

    // If angle B is equal to 0 or Pi, then sin will be zero and the following divisions will crash
    if(ANGLE_B != SFloat::_0 && SFloat::AreNotEqual(ANGLE_B, PI_Z))
    {
        const float_z INV_SIN = SFloat::_1/sin_z(ANGLE_B);

        const float_z WEIGHT1 = sin_z((SFloat::_1 - fProportion) * ANGLE_B) * INV_SIN;
        const float_z WEIGHT2 = sin_z(fProportion * ANGLE_B) * INV_SIN;

        // Separated from the equation to gain performance
        const Quaternion AUX_SUM = WEIGHT1 * (*this) + WEIGHT2 * qQuat;

        // Separated from the equation to check for "division by zero"
        const float_z DIVISOR = AUX_SUM.GetLength();

        Z_ASSERT_WARNING(DIVISOR != SFloat::_0, "The variable \"DIVISOR\" must not equal zero, this will cause a division by zero");

        qReturnValue = AUX_SUM / DIVISOR;
    }
    else
        qReturnValue = *this;

    return qReturnValue;
}

void Quaternion::ToEulerAngles(float_z &fRotationAngleX, float_z &fRotationAngleY, float_z &fRotationAngleZ) const
{
    // Source: Based on Amy de Buitléir's document about quaternions

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    // This workaround is necessary due to an unacceptable loss of precision
    using f64_z;
    fRotationAngleX = (float_z)asin_z(f64_z(SFloat::_2 * (this->w * this->x - this->z * this->y)));
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS

    fRotationAngleX = asin_z(SFloat::_2 * (this->w * this->x - this->z * this->y));

#endif

    // Checks for +-90º singularity
    if(SFloat::AreEqual(SFloat::Abs(fRotationAngleX), SAngle::_HalfPi))

    {
        fRotationAngleZ = atan2_z(this->z, this->w);
        fRotationAngleY = SFloat::_0;
    }
    else
    {
        fRotationAngleZ = atan2_z(SFloat::_2 * (this->w * this->z + this->x * this->y),
                                  (SFloat::_1 - SFloat::_2 * (this->z * this->z + this->x * this->x)) );
        fRotationAngleY = atan2_z(SFloat::_2 * (this->w * this->y + this->z * this->x),
                                  (SFloat::_1 - SFloat::_2 * (this->x * this->x + this->y * this->y)) );
    }

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts them to radians
        fRotationAngleX = SAngle::RadiansToDegrees(fRotationAngleX);
        fRotationAngleY = SAngle::RadiansToDegrees(fRotationAngleY);
        fRotationAngleZ = SAngle::RadiansToDegrees(fRotationAngleZ);
    #endif
}

void Quaternion::ToAxisAngle(BaseVector3 &vRotationAxis, float_z &fRotationAngle) const
{
    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    float_z fW = this->w;

    if(fW > SFloat::_1)
        fW = SFloat::_1;
    else if(fW < -SFloat::_1)
        fW = -SFloat::_1;

    const float_z& ACOS_W = acos_z(fW);

    Z_ASSERT_WARNING( !SFloat::IsNaN(ACOS_W), "The variable \"ACOS_W\" is NAN" );

    fRotationAngle = SFloat::_2 * ACOS_W;

    // Singularity 1: Angle = 0 -> we choose arbitrary axis.
    if (SFloat::IsZero(fRotationAngle))
    {
        vRotationAxis.x = SFloat::_1;
        vRotationAxis.y = SFloat::_0;
        vRotationAxis.z = SFloat::_0;
    }
    // Singularity 2: Angle = PI -> we calculate axis.
    else if ( SFloat::AreEqual(fRotationAngle, SAngle::_Pi) )
    {
        vRotationAxis.x = this->x;
        vRotationAxis.y = this->y;
        vRotationAxis.z = this->z;
    }
    else
    {
        const float_z &fInvSin = SFloat::_1 / sin_z(ACOS_W);

        vRotationAxis.x = this->x*fInvSin;
        vRotationAxis.y = this->y*fInvSin;
        vRotationAxis.z = this->z*fInvSin;
    }

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        fRotationAngle = SAngle::RadiansToDegrees(fRotationAngle);
    #endif
}

void Quaternion::ToAxisAngle(BaseVector4 &vRotationAxis, float_z &fRotationAngle) const
{
    BaseVector3 vAux;

    this->ToAxisAngle(vAux, fRotationAngle);

    vRotationAxis.x =  vAux.x;
    vRotationAxis.y =  vAux.y;
    vRotationAxis.z =  vAux.z;
    vRotationAxis.w = SFloat::_0;
}

float_z Quaternion::GetLength() const
{
    //           _______________________
    // length = V x^2 + y^2 + z^2 + w^2
    //
    return sqrt_z( (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
}

float_z Quaternion::GetSquaredLength() const
{
    //                    ______________________
    // squared length = (V x^2 + y^2 + z^2 + w^2)^2
    //
    return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);
}

string_z Quaternion::ToString() const
{
    static const string_z STRING_PREFIX("Q(");
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


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const Quaternion& Quaternion::GetIdentity()
{
    static const Quaternion IDENTITY(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    return IDENTITY;
}

} // namespace z
