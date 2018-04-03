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

#include "ZMath/DualQuaternion.h"

#include "ZCommon/Assertions.h"
#include "ZMath/BaseVector3.h"
#include "ZMath/BaseVector4.h"


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

DualQuaternion::DualQuaternion()
{
}

DualQuaternion::DualQuaternion(const DualQuaternion &dualQuat) : BaseDualQuaternion(dualQuat)
{
}

DualQuaternion::DualQuaternion(const BaseDualQuaternion &dualQuat) : BaseDualQuaternion(dualQuat)
{
}

DualQuaternion::DualQuaternion(const BaseQuaternion &qReal, const BaseQuaternion &qDual) : BaseDualQuaternion(qReal, qDual)
{
}

DualQuaternion::DualQuaternion(const BaseQuaternion &qRotation, const BaseVector3 &vTranslation)
{
    DualQuaternionImp(qRotation, vTranslation);
}

DualQuaternion::DualQuaternion(const BaseQuaternion &qRotation, const BaseVector4 &vTranslation)
{
    DualQuaternionImp(qRotation, vTranslation);
}

DualQuaternion::DualQuaternion(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation)
{
    DualQuaternionImp(vTranslation, qRotation);
}

DualQuaternion::DualQuaternion(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation)
{
    DualQuaternionImp(vTranslation, qRotation);
}

DualQuaternion::DualQuaternion(const float_z *arValuesReal, const float_z *arValuesDual)
{
    Z_ASSERT_ERROR(arValuesReal != null_z && arValuesDual != null_z, "Input arrays must not be null");

    this->r = Quaternion(arValuesReal[0], arValuesReal[1], arValuesReal[2], arValuesReal[3]);
    this->d = Quaternion(arValuesDual[0], arValuesDual[1], arValuesDual[2], arValuesDual[3]);
}

template <class VectorT>
void DualQuaternion::DualQuaternionImp(const BaseQuaternion &qRotation, const VectorT &vTranslation)
{
    DualQuaternion rotation(qRotation, BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));
    DualQuaternion translation(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                                BaseQuaternion(vTranslation.x * SFloat::_0_5, vTranslation.y * SFloat::_0_5, vTranslation.z * SFloat::_0_5, SFloat::_0));

    *this = translation * rotation;
}

template <class VectorT>
void DualQuaternion::DualQuaternionImp(const VectorT &vTranslation, const BaseQuaternion &qRotation)
{
    DualQuaternion rotation(qRotation, BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));
    DualQuaternion translation(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                                BaseQuaternion(vTranslation.x * SFloat::_0_5, vTranslation.y * SFloat::_0_5, vTranslation.z * SFloat::_0_5, SFloat::_0));

    *this = rotation * translation;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

DualQuaternion DualQuaternion::operator+(const BaseDualQuaternion &dualQuat) const
{
    return DualQuaternion(BaseQuaternion(this->r + dualQuat.r), BaseQuaternion(this->d + dualQuat.d));
}

DualQuaternion DualQuaternion::operator-(const BaseDualQuaternion &dualQuat) const
{
    return DualQuaternion(BaseQuaternion(this->r - dualQuat.r), BaseQuaternion(this->d - dualQuat.d));
}

DualQuaternion DualQuaternion::operator*(const BaseDualQuaternion &dualQuat) const
{
    return DualQuaternion(BaseQuaternion(this->r * dualQuat.r), BaseQuaternion(this->r * dualQuat.d + this->d * dualQuat.r));
}

DualQuaternion DualQuaternion::operator*(const float_z fScalar) const
{
    return DualQuaternion(BaseQuaternion(this->r * fScalar), BaseQuaternion(this->d * fScalar));
}

DualQuaternion operator*(const float_z fScalar, const DualQuaternion &dualQuat)
{
    return DualQuaternion(BaseQuaternion(dualQuat.r * fScalar), BaseQuaternion(dualQuat.d * fScalar));
}

DualQuaternion DualQuaternion::operator*(const BaseVector3 &vVector) const
{
    // Vector3 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    DualQuaternion auxQ(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                         BaseQuaternion(vVector.x, vVector.y, vVector.z, SFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

DualQuaternion DualQuaternion::operator*(const BaseVector4 &vVector) const
{
    // Vector4 is converted to dual quaternion (0, 0, 0, 1)(x, y, z, 0)
    DualQuaternion auxQ(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                         BaseQuaternion(vVector.x, vVector.y, vVector.z, SFloat::_0) );

    auxQ = (*this)*auxQ;

    return auxQ;
}

DualQuaternion DualQuaternion::operator/(const float_z fScalar) const
{
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "The input value must not equal zero");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    return DualQuaternion(BaseQuaternion(this->r * DIVISOR), BaseQuaternion(this->d * DIVISOR));
}

DualQuaternion& DualQuaternion::operator+=(const BaseDualQuaternion &dualQuat)
{
    this->r += dualQuat.r;
    this->d += dualQuat.d;

    return *this;
}

DualQuaternion& DualQuaternion::operator-=(const BaseDualQuaternion &dualQuat)
{
    this->r -= dualQuat.r;
    this->d -= dualQuat.d;

    return *this;
}

DualQuaternion& DualQuaternion::operator*=(const BaseDualQuaternion &dualQuat)
{
    DualQuaternion aux(*this);

    this->r = aux.r * dualQuat.r;
    this->d = aux.r * dualQuat.d + aux.d * dualQuat.r;

    return *this;
}

DualQuaternion& DualQuaternion::operator*=(const float_z fScalar)
{
    this->r *= fScalar;
    this->d *= fScalar;

    return *this;
}

DualQuaternion& DualQuaternion::operator/=(const float_z fScalar)
{
    // Checkout to avoid division by zero.
    Z_ASSERT_WARNING(fScalar != SFloat::_0, "The input array must not be null");

    const float_z &DIVISOR = SFloat::_1/fScalar;

    this->r *= DIVISOR;
    this->d *= DIVISOR;

    return *this;
}

DualQuaternion& DualQuaternion::operator=(const BaseDualQuaternion &dualQuat)
{
    BaseDualQuaternion::operator=(dualQuat);
    return *this;
}

void DualQuaternion::ResetToZero()
{
    this->r.ResetToZero();
    this->d.ResetToZero();
}

void DualQuaternion::ResetToIdentity()
{
    this->r.ResetToIdentity();
    this->d.ResetToZero();
}

DualQuaternion DualQuaternion::Conjugate() const
{
    return DualQuaternion(r.Conjugate(), d.Conjugate());
}

DualQuaternion DualQuaternion::DoubleConjugate() const
{
    return DualQuaternion(r.Conjugate(), d.Conjugate() * -SFloat::_1);
}

float_z DualQuaternion::GetNonDualLength() const
{
    return this->r.GetLength();
}

DualQuaternion DualQuaternion::Transform(const DualQuaternion &transformation) const
{
    return DualQuaternion(transformation * (*this) * transformation.DoubleConjugate());
}

DualQuaternion DualQuaternion::TransformRotationFirst(const BaseQuaternion &qRotation, const BaseVector3 &vTranslation) const
{
    return this->TransformRotationFirstImp(qRotation, vTranslation);
}

DualQuaternion DualQuaternion::TransformRotationFirst(const BaseQuaternion &qRotation, const BaseVector4 &vTranslation) const
{
    return this->TransformRotationFirstImp(qRotation, vTranslation);
}

DualQuaternion DualQuaternion::TransformTranslationFirst(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation) const
{
    return this->TransformTranslationFirstImp(vTranslation, qRotation);
}

DualQuaternion DualQuaternion::TransformTranslationFirst(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation) const
{
    return this->TransformTranslationFirstImp(vTranslation, qRotation);
}

DualQuaternion DualQuaternion::Lerp(const float_z fProportion, const DualQuaternion &dualQuat) const
{
    DualQuaternion auxDualQuat = (SFloat::_1 - fProportion) * (*this) + fProportion * dualQuat;
    float_z fLength = auxDualQuat.GetNonDualLength();

    Z_ASSERT_WARNING(fLength != SFloat::_0, "A zero length will produce a division by zero");

    return auxDualQuat / fLength;
}

string_z DualQuaternion::ToString() const
{
    return string_z("DQ(r(") + r.ToString() +
               Z_L("),d(")  + d.ToString() + Z_L("))");
}

template <class VectorT>
DualQuaternion DualQuaternion::TransformRotationFirstImp(const BaseQuaternion &qRotation, const VectorT &vTranslation) const
{
    DualQuaternion rotation(qRotation, BaseQuaternion());
    DualQuaternion translation(Quaternion::GetIdentity(),
                                BaseQuaternion(vTranslation.x * SFloat::_0_5, vTranslation.y * SFloat::_0_5, vTranslation.z * SFloat::_0_5, SFloat::_0));

    return this->Transform(translation * rotation);
}

template <class VectorT>
DualQuaternion DualQuaternion::TransformTranslationFirstImp(const VectorT &vTranslation, const BaseQuaternion &qRotation) const
{
    DualQuaternion rotation(qRotation, BaseQuaternion());
    DualQuaternion translation(Quaternion::GetIdentity(),
                                BaseQuaternion(vTranslation.x * SFloat::_0_5, vTranslation.y * SFloat::_0_5, vTranslation.z * SFloat::_0_5, SFloat::_0));

    return this->Transform(rotation * translation);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const DualQuaternion& DualQuaternion::GetIdentity()
{
    static const DualQuaternion IDENTITY(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1),
                                            BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));
    return IDENTITY;
}


} // namespace z
