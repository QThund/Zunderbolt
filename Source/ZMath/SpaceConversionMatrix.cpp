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

#include "ZMath/SpaceConversionMatrix.h"

#include "ZCommon/Assertions.h"
#include "ZMath/BaseQuaternion.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/BaseQuaternion.h"
#include "ZMath/Matrix4x3.h"
#include "ZCommon/DataTypes/SFloat.h"
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
    
SpaceConversionMatrix::SpaceConversionMatrix()
{
    this->ResetToIdentity();
}

SpaceConversionMatrix::SpaceConversionMatrix(const SpaceConversionMatrix &matrix) : Matrix4x4(matrix)
{
}

SpaceConversionMatrix::SpaceConversionMatrix(const BaseMatrix4x4 &matrix) : Matrix4x4(matrix)
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

SpaceConversionMatrix& SpaceConversionMatrix::operator=(const BaseMatrix4x4 &matrix)
{
    BaseMatrix4x4::operator=(matrix);
    return *this;
}

SpaceConversionMatrix SpaceConversionMatrix::operator*(const SpaceConversionMatrix &matrix) const
{
    return scast_z(*this, const Matrix4x4&) * scast_z(matrix, const Matrix4x4&);
}

SpaceConversionMatrix& SpaceConversionMatrix::operator*=(const SpaceConversionMatrix &matrix)
{
    scast_z(*this, Matrix4x4&) *= scast_z(matrix, const Matrix4x4&);
    return *this;
}

void SpaceConversionMatrix::SetWorldSpaceMatrix(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale)
{
    TransformationMatrix<Matrix4x4> aux(vTranslation, qRotation, vScale);

    *this = rcast_z(aux, SpaceConversionMatrix&);
}

void SpaceConversionMatrix::SetWorldSpaceMatrix(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale)
{
    TransformationMatrix<Matrix4x4> aux(vTranslation, qRotation, vScale);

    *this = rcast_z(aux, SpaceConversionMatrix&);
}

void SpaceConversionMatrix::SetWorldSpaceMatrix(const TransformationMatrix<Matrix4x4> &translation, const TransformationMatrix<Matrix4x4> &rotation,
                                                 const TransformationMatrix<Matrix4x4> &scale)
{
    this->ij[0][0] = scale.ij[0][0] * rotation.ij[0][0];
    this->ij[0][1] = scale.ij[0][0] * rotation.ij[0][1];
    this->ij[0][2] = scale.ij[0][0] * rotation.ij[0][2];
    this->ij[0][3] = SFloat::_0;

    this->ij[1][0] = scale.ij[1][1] * rotation.ij[1][0];
    this->ij[1][1] = scale.ij[1][1] * rotation.ij[1][1];
    this->ij[1][2] = scale.ij[1][1] * rotation.ij[1][2];
    this->ij[1][3] = SFloat::_0;

    this->ij[2][0] = scale.ij[2][2] * rotation.ij[2][0];
    this->ij[2][1] = scale.ij[2][2] * rotation.ij[2][1];
    this->ij[2][2] = scale.ij[2][2] * rotation.ij[2][2];
    this->ij[2][3] = SFloat::_0;

    this->ij[3][0] = translation.ij[3][0];
    this->ij[3][1] = translation.ij[3][1];
    this->ij[3][2] = translation.ij[3][2];
    this->ij[3][3] = SFloat::_1;
}

void SpaceConversionMatrix::SetViewSpaceMatrix(const Vector3 &vPointOfView, const Vector3 &vTarget,
                                                const Vector3 &vUpDirection)
{
    Vector3 vZAxis = (vTarget - vPointOfView).Normalize();

    Vector3 vXAxis = vUpDirection.CrossProduct(vZAxis).Normalize();

    Vector3 vYAxis = vZAxis.CrossProduct(vXAxis);

    this->ij[0][0] = vXAxis.x;
    this->ij[0][1] = vYAxis.x;
    this->ij[0][2] = vZAxis.x;
    this->ij[0][3] = SFloat::_0;

    this->ij[1][0] = vXAxis.y;
    this->ij[1][1] = vYAxis.y;
    this->ij[1][2] = vZAxis.y;
    this->ij[1][3] = SFloat::_0;

    this->ij[2][0] = vXAxis.z;
    this->ij[2][1] = vYAxis.z;
    this->ij[2][2] = vZAxis.z;
    this->ij[2][3] = SFloat::_0;

    this->ij[3][0] = -vXAxis.DotProduct(vPointOfView);
    this->ij[3][1] = -vYAxis.DotProduct(vPointOfView);
    this->ij[3][2] = -vZAxis.DotProduct(vPointOfView);
    this->ij[3][3] = SFloat::_1;
}

void SpaceConversionMatrix::SetViewSpaceMatrix(const Vector4 &vPointOfView, const Vector4 &vTarget,
                                                const Vector4 &vUpDirection)
{
    this->SetViewSpaceMatrix(Vector3(vPointOfView),
                             Vector3(vTarget),
                             Vector3(vUpDirection));
}

void SpaceConversionMatrix::SetProjectionSpaceMatrix(const float_z fNearClipPlane, const float_z fFarClipPlane,
                                                      const float_z fAspectRatio, const float_z fVerticalFOV)
{
    // The clipping planes should not coincide
    Z_ASSERT_WARNING(SFloat::AreNotEqual(fNearClipPlane, fFarClipPlane), "The clipping planes should not coincide");

    // The aspect ratio must be positive and not equal zero
    Z_ASSERT_WARNING(SFloat::IsGreaterThan(fAspectRatio, SFloat::_0), "The aspect ratio must be positive and not equal zero");

    // The vertical field of view must be positive and not equal zero
    Z_ASSERT_WARNING(SFloat::IsGreaterThan(fVerticalFOV, SFloat::_0), "The vertical field of view must be positive and not equal zero");

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& HALF_VERT_FOV = SAngle::DegreesToRadians(fVerticalFOV * SFloat::_0_5);
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z& HALF_VERT_FOV = fVerticalFOV * SFloat::_0_5;
    #endif

    Z_ASSERT_WARNING( SFloat::AreNotEqual(HALF_VERT_FOV, SAngle::_HalfPi), "Input vertical FOV must not equal a plain angle" );

    const float_z& SCALE_Y  = float_z((double)SFloat::_1 / tan_z((double)HALF_VERT_FOV));
    const float_z& SCALE_X  = float_z((double)SCALE_Y / (double)fAspectRatio);

    this->ij[0][0] = SCALE_X;
    this->ij[0][1] = SFloat::_0;
    this->ij[0][2] = SFloat::_0;
    this->ij[0][3] = SFloat::_0;
    this->ij[1][0] = SFloat::_0;
    this->ij[1][1] = SCALE_Y;
    this->ij[1][2] = SFloat::_0;
    this->ij[1][3] = SFloat::_0;
    this->ij[2][0] = SFloat::_0;
    this->ij[2][1] = SFloat::_0;
    this->ij[2][2] = fFarClipPlane / (fFarClipPlane - fNearClipPlane);
    this->ij[2][3] = SFloat::_1;
    this->ij[3][0] = SFloat::_0;
    this->ij[3][2] = -fNearClipPlane * this->ij[2][2];
    this->ij[3][1] = SFloat::_0;
    this->ij[3][3] = SFloat::_0;

}

SpaceConversionMatrix SpaceConversionMatrix::SwitchHandConventionViewSpaceMatrix() const
{
    Vector3 vPOV = Vector3(-(this->ij[3][0]*this->ij[0][0] + this->ij[3][1]*this->ij[0][1] + this->ij[3][2]*this->ij[0][2]),
                             -(this->ij[3][0]*this->ij[1][0] + this->ij[3][1]*this->ij[1][1] + this->ij[3][2]*this->ij[1][2]),
                             -(this->ij[3][0]*this->ij[2][0] + this->ij[3][1]*this->ij[2][1] + this->ij[3][2]*this->ij[2][2]) );

    Vector3 vUp(this->ij[0][1], this->ij[1][1], this->ij[2][1]);

    Vector3 vZAxis = Vector3(-this->ij[0][2], -this->ij[1][2], -this->ij[2][2]);

    Vector3 vXAxis = vUp.CrossProduct(vZAxis);

    Vector3 vYAxis = vZAxis.CrossProduct(vXAxis);

    return SpaceConversionMatrix( Matrix4x4(vXAxis.x, vYAxis.x, vZAxis.x, SFloat::_0,
                                              vXAxis.y, vYAxis.y, vZAxis.y, SFloat::_0,
                                              vXAxis.z, vYAxis.z, vZAxis.z, SFloat::_0,
                                              -vXAxis.DotProduct(vPOV), -vYAxis.DotProduct(vPOV), -vZAxis.DotProduct(vPOV), SFloat::_1));
}

void SpaceConversionMatrix::SetWorldSpaceMatrix(const TranslationMatrix<Matrix4x3> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
{
    SetWorldSpaceMatrixImp(translation, rotation, scale);
}

void SpaceConversionMatrix::SetWorldSpaceMatrix(const TranslationMatrix<Matrix4x4> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
{
    SetWorldSpaceMatrixImp(translation, rotation, scale);
}

SpaceConversionMatrix SpaceConversionMatrix::SwitchHandConventionProjectionSpaceMatrix() const
{
    SpaceConversionMatrix switchedMatrix = *this;
    switchedMatrix.ij[2][2] = -this->ij[2][2];
    switchedMatrix.ij[2][3] = -this->ij[2][3];
    return switchedMatrix;
}

template <class MatrixT>
void SpaceConversionMatrix::SetWorldSpaceMatrixImp(const TranslationMatrix<MatrixT> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
{
    TransformationMatrix<Matrix4x4> aux(translation, rotation, scale);

    *this = rcast_z(aux, SpaceConversionMatrix&);
}

SpaceConversionMatrix SpaceConversionMatrix::SwitchHandConventionWorldSpaceMatrix() const
{
    return SpaceConversionMatrix(scast_z(*this, const TransformationMatrix<Matrix4x4>&).SwitchHandConvention());
}

} // namespace z
