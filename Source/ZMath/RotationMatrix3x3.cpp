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

#include "ZMath/RotationMatrix3x3.h"

#include <algorithm>
#include "ZCommon/Assertions.h"
#include "ZMath/Vector3.h"
#include "ZMath/BaseQuaternion.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SAngle.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
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
   
RotationMatrix3x3::RotationMatrix3x3()
{
    this->ResetToIdentity();
}

RotationMatrix3x3::RotationMatrix3x3(const RotationMatrix3x3 &rotation) : Matrix3x3(rotation)
{
}

RotationMatrix3x3::RotationMatrix3x3(const BaseMatrix3x3 &rotation) : Matrix3x3(rotation)
{
}

RotationMatrix3x3::RotationMatrix3x3(const float_z fRotationAngleX, const float_z fRotationAngleY, const float_z fRotationAngleZ)
{

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& ANGLE_X_RAD = SAngle::DegreesToRadians(fRotationAngleX);
        const float_z& ANGLE_Y_RAD = SAngle::DegreesToRadians(fRotationAngleY);
        const float_z& ANGLE_Z_RAD = SAngle::DegreesToRadians(fRotationAngleZ);

        const float_z& fA   = cos_z(ANGLE_X_RAD);
        const float_z& fB   = sin_z(ANGLE_X_RAD);
        const float_z& fC   = cos_z(ANGLE_Y_RAD);
        const float_z& fD   = sin_z(ANGLE_Y_RAD);
        const float_z& fE   = cos_z(ANGLE_Z_RAD);
        const float_z& fF   = sin_z(ANGLE_Z_RAD);
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z& fA   = cos_z(fRotationAngleX);
        const float_z& fB   = sin_z(fRotationAngleX);
        const float_z& fC   = cos_z(fRotationAngleY);
        const float_z& fD   = sin_z(fRotationAngleY);
        const float_z& fE   = cos_z(fRotationAngleZ);
        const float_z& fF   = sin_z(fRotationAngleZ);
    #endif

    float_z fBC  = -fB * fC;
    float_z fBD  = fB * fD;

    ij[0][0]  =  fE * fC + fF * fBD;
    ij[0][1]  =  fA * fF;
    ij[0][2]  =  -fE * fD - fF * fBC;

    ij[1][0]  =  -fF * fC + fE * fBD;
    ij[1][1]  =  fA * fE;
    ij[1][2]  =  fF * fD - fE * fBC;

    ij[2][0]  =  fA * fD;
    ij[2][1]  =  -fB;
    ij[2][2]  =  fA * fC;
}

RotationMatrix3x3::RotationMatrix3x3 (const float_z fRotationAngle, const BaseVector3 &vRotationAxis)
{
    // Taken from http://en.wikipedia.org/wiki/Rotation_representation#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle
    // but changing factors affected by sinus to get a left handed matrix.

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // If angles are specified in degrees, then converts it to radians
        const float_z& ANGLE_RAD = SAngle::DegreesToRadians(fRotationAngle);

        const float_z& fA = cos_z(ANGLE_RAD);
        const float_z& fB = sin_z(ANGLE_RAD);
    #else
        const float_z& fA = cos_z(fRotationAngle);
        const float_z& fB = sin_z(fRotationAngle);
    #endif

    const float_z& fC = vRotationAxis.x*vRotationAxis.y;
    const float_z& fD = vRotationAxis.y*vRotationAxis.z;
    const float_z& fE = vRotationAxis.z*vRotationAxis.x;

    const float_z& fF = (SFloat::_1 - fA) * fC;
    const float_z& fG = (SFloat::_1 - fA) * fD;
    const float_z& fH = (SFloat::_1 - fA) * fE;

    const float_z& fI = -vRotationAxis.x * fB;
    const float_z& fJ = -vRotationAxis.y * fB;
    const float_z& fK = -vRotationAxis.z * fB;

    this->ij[0][0] = fA + (SFloat::_1 - fA) * vRotationAxis.x * vRotationAxis.x;
    this->ij[0][1] = fF - fK;
    this->ij[0][2] = fH + fJ;

    this->ij[1][0] = fF + fK;
    this->ij[1][1] = fA + (SFloat::_1 - fA) * vRotationAxis.y * vRotationAxis.y;
    this->ij[1][2] = fG - fI;

    this->ij[2][0] = fH - fJ;
    this->ij[2][1] = fG + fI;
    this->ij[2][2] = fA + (SFloat::_1 - fA) * vRotationAxis.z * vRotationAxis.z;
}

RotationMatrix3x3::RotationMatrix3x3(const BaseQuaternion &qRotation)
{
    // Taken from http://osdir.com/ml/games.devel.algorithms/2002-11/msg00318.html

    const float_z& fA   = SFloat::_2 * qRotation.x * qRotation.x;
    const float_z& fB   = SFloat::_2 * qRotation.y * qRotation.y;
    const float_z& fC   = SFloat::_2 * qRotation.z * qRotation.z;

    const float_z& fD   = SFloat::_2 * qRotation.x * qRotation.y;
    const float_z& fE   = SFloat::_2 * qRotation.x * qRotation.z;
    const float_z& fF   = SFloat::_2 * qRotation.x * qRotation.w;
    const float_z& fG   = SFloat::_2 * qRotation.y * qRotation.z;
    const float_z& fH   = SFloat::_2 * qRotation.y * qRotation.w;
    const float_z& fI   = SFloat::_2 * qRotation.z * qRotation.w;

    this->ij[0][0] = SFloat::_1 - fB - fC;
    this->ij[0][1] = fD + fI;
    this->ij[0][2] = fE - fH;

    this->ij[1][0] = fD - fI;
    this->ij[1][1] = SFloat::_1 - fA - fC;
    this->ij[1][2] = fG + fF;

    this->ij[2][0] = fE + fH;
    this->ij[2][1] = fG - fF;
    this->ij[2][2] = SFloat::_1 - fA - fB;
}

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

// Binary operators

RotationMatrix3x3 RotationMatrix3x3::operator*(const RotationMatrix3x3 &matrix) const
{
    RotationMatrix3x3 aux;

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

TransformationMatrix<Matrix4x4> RotationMatrix3x3::operator*(const TranslationMatrix<Matrix4x4> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x4>(matrix);
}

TransformationMatrix<Matrix4x3> RotationMatrix3x3::operator*(const TranslationMatrix<Matrix4x3> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x3>(matrix);
}

TransformationMatrix<Matrix4x4> RotationMatrix3x3::operator*(const ScalingMatrix3x3 &matrix) const
{
    TransformationMatrix<Matrix4x4> aux;

    aux.ResetToIdentity();

    aux.ij[0][0] = matrix.ij[0][0] * this->ij[0][0] ;
    aux.ij[0][1] = matrix.ij[1][1] * this->ij[0][1];
    aux.ij[0][2] = matrix.ij[2][2] * this->ij[0][2];

    aux.ij[1][0] = matrix.ij[0][0] * this->ij[1][0];
    aux.ij[1][1] = matrix.ij[1][1] * this->ij[1][1];
    aux.ij[1][2] = matrix.ij[2][2] * this->ij[1][2];

    aux.ij[2][0] = matrix.ij[0][0] * this->ij[2][0];
    aux.ij[2][1] = matrix.ij[1][1] * this->ij[2][1];
    aux.ij[2][2] = matrix.ij[2][2] * this->ij[2][2];

    return aux;
}

TransformationMatrix<Matrix4x4> RotationMatrix3x3::operator*(const TransformationMatrix<Matrix4x4> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x4>(matrix);
}

TransformationMatrix<Matrix4x3> RotationMatrix3x3::operator*(const TransformationMatrix<Matrix4x3> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x3>(matrix);
}

RotationMatrix3x3& RotationMatrix3x3::operator=(const BaseMatrix3x3 &matrix)
{
    BaseMatrix3x3::operator=(matrix);
    return *this;
}

RotationMatrix3x3& RotationMatrix3x3::operator*=(const RotationMatrix3x3 &matrix)
{
    RotationMatrix3x3 aux;

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

RotationMatrix3x3 RotationMatrix3x3::Invert() const
{
    return this->Transpose();
}

void RotationMatrix3x3::GetRotation(float_z &fRotationAngleX, float_z &fRotationAngleY, float_z &fRotationAngleZ) const
{
    // \f$ Rx \begin{bmatrix} 1 & 0 & 0 \\ 0 & cos(X) & sin(X) \\ 0 & -sin(X) & cos(X) \end{bmatrix}\f$
    // \f$ Ry \begin{bmatrix} cos(Y) & 0 & -sin(Y) \\ 0 & 1 & 0 \\ sin(Y) & 0 & cos(Y) \end{bmatrix}\f$
    // \f$ Rz \begin{bmatrix} cos(Z) & sin(Z) & 0 \\ -sin(Z) & cos(Z) & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$
    // \f$ RzRx \begin{bmatrix} cos(Z) & sin(Z)cos(X) & sin(Z)sin(X) \\ -sin(Z) & cos(Z)cos(X) & cos(Z)sin(X) \\ 0 & -sin(X) & cos(X) \end{bmatrix}\f$
    // \f$ RzRxRy \begin{bmatrix} cos(Z)cos(Y) + sin(Z)sin(X)sin(Y) & sin(Z)cos(X) & cos(Z)(-sin(Y)) + sin(Z)sin(X)cos(Y) \\ -sin(Z)cos(Y) + cos(Z)cos(X)sin(Y) & cos(Z)cos(X) & -sin(Z)(-sin(Y)) + cos(Z)sin(X)cos(Y) \\ cos(X)sin(Y) & -sin(X) & cos(X)cos(Y) \end{bmatrix}\f$

    fRotationAngleX = asin_z(-this->ij[2][1]); // m[2,1] == -sin(X)

    const float_z COS_X = cos_z(fRotationAngleX);

    if( SFloat::IsGreaterThan(COS_X, SFloat::_0) )
    {
        fRotationAngleZ = atan2_z(this->ij[0][1], this->ij[1][1]);
        fRotationAngleY = atan2_z(this->ij[2][0], this->ij[2][2]);
    }
    else
    {
        fRotationAngleZ = atan2_z(-this->ij[1][0], this->ij[0][0]);
        fRotationAngleY = SFloat::_0;
    }
    
    // Checkout to avoid NaN values
    Z_ASSERT_WARNING( !SFloat::IsNaN(fRotationAngleX) && !SFloat::IsNaN(fRotationAngleY) && !SFloat::IsNaN(fRotationAngleZ), "One or more calculated angle are NAN" );

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        // Since angles are specified in radians, we convert it to degrees
        fRotationAngleX = SAngle::RadiansToDegrees(fRotationAngleX);
        fRotationAngleY = SAngle::RadiansToDegrees(fRotationAngleY);
        fRotationAngleZ = SAngle::RadiansToDegrees(fRotationAngleZ);
    #endif
}

void RotationMatrix3x3::GetRotation(BaseQuaternion &qRotation) const
{
    // Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/christian.htm

    // If the main diagonal is zero, the rotation matrix is not well-formed
    Z_ASSERT_WARNING( SFloat::IsNotZero(this->ij[0][0] + this->ij[1][1] + this->ij[2][2]), "The main diagonal is zero, the rotation matrix is not well-formed" );
    
    qRotation.w = sqrt_z( std::max(SFloat::_0, SFloat::_1 + this->ij[0][0] + this->ij[1][1] + this->ij[2][2]) ) * SFloat::_0_5;
    qRotation.x = sqrt_z( std::max(SFloat::_0, SFloat::_1 + this->ij[0][0] - this->ij[1][1] - this->ij[2][2]) ) * SFloat::_0_5;
    qRotation.y = sqrt_z( std::max(SFloat::_0, SFloat::_1 - this->ij[0][0] + this->ij[1][1] - this->ij[2][2]) ) * SFloat::_0_5;
    qRotation.z = sqrt_z( std::max(SFloat::_0, SFloat::_1 - this->ij[0][0] - this->ij[1][1] + this->ij[2][2]) ) * SFloat::_0_5;
    
    // This sing depends on hand convention
    SFloat::CopySign(this->ij[1][2] - this->ij[2][1], qRotation.x);
    SFloat::CopySign(this->ij[2][0] - this->ij[0][2], qRotation.y);
    SFloat::CopySign(this->ij[0][1] - this->ij[1][0], qRotation.z);
}

void RotationMatrix3x3::GetRotation(float_z &fRotationAngle, BaseVector3 &vRotationAxis) const
{
    // Source: http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
    // Source: http://en.wikipedia.org/wiki/Rotation_representation_%28mathematics%29#Rotation_matrix_.E2.86.94_Euler_axis.2Fangle

    float_z COS_AUX = (this->ij[0][0] + this->ij[1][1] + this->ij[2][2] - SFloat::_1) * SFloat::_0_5;

    // Sometimes the result of the dot product is not accurate and must be clampped [-1, 1]
    if(COS_AUX > SFloat::_1)
        COS_AUX = SFloat::_1;
    else if(COS_AUX < -SFloat::_1)
        COS_AUX = -SFloat::_1;

    fRotationAngle = acos_z(COS_AUX);

    Z_ASSERT_WARNING( !SFloat::IsNaN(fRotationAngle), "The resultant angle \"fRotationAngle\" is NAN" );

    if( SFloat::AreEqual(COS_AUX, SFloat::_1) ) // Singularity 1: Angle == 0 -> we choose arbitrary axis.
    {
        vRotationAxis = Vector3::GetNullVector();
    }
    else if( SFloat::AreEqual(COS_AUX, -SFloat::_1) ) // Singularity 2: Angle == PI -> we calculate axis.
    {
        const float_z &HALF_SRT_2 = sqrt_z(SFloat::_2) * SFloat::_0_5;

        const float_z &XX = (this->ij[0][0] + SFloat::_1) * SFloat::_0_5;
        const float_z &YY = (this->ij[1][1] + SFloat::_1) * SFloat::_0_5;
        const float_z &ZZ = (this->ij[2][2] + SFloat::_1) * SFloat::_0_5;

        if( SFloat::IsGreaterThan(XX, YY) && SFloat::IsGreaterThan(XX, ZZ) ) // m[0][0] is the largest diagonal term
        {
            if (SFloat::IsZero(XX))
            {
                vRotationAxis.x = SFloat::_0;
                vRotationAxis.y = HALF_SRT_2;
                vRotationAxis.z = HALF_SRT_2;
            }
            else
            {
                Z_ASSERT_WARNING( SFloat::IsGreaterThan(XX, SFloat::_0), "The variable \"XX\" must be greater than zero (matrix element [0,0] is negative, maybe)" );

                vRotationAxis.x = sqrt_z(XX);

                const float_z &INV_X = SFloat::_1 / vRotationAxis.x;
                const float_z &XY = (this->ij[0][1] + this->ij[1][0]) * SFloat::_0_25;
                const float_z &XZ = (this->ij[0][2] + this->ij[2][0]) * SFloat::_0_25;

                vRotationAxis.y = XY * INV_X;
                vRotationAxis.z = XZ * INV_X;
            }
        }
        else if( SFloat::IsGreaterThan(YY, ZZ) ) // m[1][1] is the largest diagonal term
        {
            if (SFloat::IsZero(YY))
            {
                vRotationAxis.x = HALF_SRT_2;
                vRotationAxis.y = SFloat::_0;
                vRotationAxis.z = HALF_SRT_2;
            }
            else
            {
                Z_ASSERT_WARNING( SFloat::IsGreaterThan(YY, SFloat::_0), "The variable \"YY\" must be greater than zero (matrix element [1,1] is negative, maybe)" );

                vRotationAxis.y = sqrt_z(YY);

                const float_z &INV_Y = SFloat::_1 / vRotationAxis.y;
                const float_z &XY = (this->ij[0][1] + this->ij[1][0]) * SFloat::_0_25;
                const float_z &YZ = (this->ij[1][2] + this->ij[2][1]) * SFloat::_0_25;

                vRotationAxis.x = XY * INV_Y;
                vRotationAxis.z = YZ * INV_Y;
            }
        }
        else // m[2][2] is the largest diagonal term so base result on this
        {
            if(SFloat::IsZero(ZZ))
            {
                vRotationAxis.x = HALF_SRT_2;
                vRotationAxis.y = HALF_SRT_2;
                vRotationAxis.z = SFloat::_0;
            }
            else
            {
                Z_ASSERT_WARNING( SFloat::IsGreaterThan(ZZ, SFloat::_0), "The variable \"ZZ\" must be greater than zero (matrix element [2,2] is negative, maybe)" );

                vRotationAxis.z = sqrt_z(ZZ);

                const float_z &INV_Z = SFloat::_1 / vRotationAxis.z;
                const float_z &XZ = (this->ij[0][2] + this->ij[2][0]) * SFloat::_0_25;
                const float_z &YZ = (this->ij[1][2] + this->ij[2][1]) * SFloat::_0_25;

                vRotationAxis.x = XZ * INV_Z;
                vRotationAxis.y = YZ * INV_Z;
            }
        }

        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fRotationAngle = SAngle::_180;
        #endif
    }
    else
    {
        const float_z &HALF_INV_SIN = SFloat::_0_5 / sin_z(fRotationAngle);

        vRotationAxis.x = (this->ij[1][2] - this->ij[2][1]) * HALF_INV_SIN;
        vRotationAxis.y = (this->ij[2][0] - this->ij[0][2]) * HALF_INV_SIN;
        vRotationAxis.z = (this->ij[0][1] - this->ij[1][0]) * HALF_INV_SIN;

        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            // Since angles are specified in radians, we convert it to degrees
            fRotationAngle = SAngle::RadiansToDegrees(fRotationAngle);
        #endif
    }
}

float_z RotationMatrix3x3::GetDeterminant() const
{
    return SFloat::_1;
}

template <class MatrixT>
TransformationMatrix<MatrixT> RotationMatrix3x3::ProductOperatorImp(const TranslationMatrix<MatrixT> &matrix) const
{
    TransformationMatrix<MatrixT> aux(TransformationMatrix<MatrixT>::GetIdentity());

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[0][1] = this->ij[0][1];
    aux.ij[0][2] = this->ij[0][2];

    aux.ij[1][0] = this->ij[1][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[1][2] = this->ij[1][2];

    aux.ij[2][0] = this->ij[2][0];
    aux.ij[2][1] = this->ij[2][1];
    aux.ij[2][2] = this->ij[2][2];

    return aux;
}

template <class MatrixT>
TransformationMatrix<MatrixT> RotationMatrix3x3::ProductOperatorImp(const TransformationMatrix<MatrixT> &matrix) const
{
    TransformationMatrix<MatrixT> aux(TransformationMatrix<MatrixT>::GetIdentity());

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

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


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const RotationMatrix3x3& RotationMatrix3x3::GetIdentity()
{
    static const RotationMatrix3x3 IDENTITY(Matrix3x3::GetIdentity());
    return IDENTITY;
}

} // namespace z
