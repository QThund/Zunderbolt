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

#include "ZMath/ScalingMatrix3x3.h"

#include "ZCommon/Assertions.h"
#include "ZMath/Vector3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
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
    
ScalingMatrix3x3::ScalingMatrix3x3()
{
    this->ResetToIdentity();
}

ScalingMatrix3x3::ScalingMatrix3x3(const ScalingMatrix3x3 &scale) : Matrix3x3(scale)
{
}

ScalingMatrix3x3::ScalingMatrix3x3(const BaseMatrix3x3 &scale) : Matrix3x3(scale)
{
}

ScalingMatrix3x3::ScalingMatrix3x3(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ)
{
    this->ij[0][0] = fScaleX;
    this->ij[1][1] = fScaleY;
    this->ij[2][2] = fScaleZ;

    this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
    this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SFloat::_0;
}

ScalingMatrix3x3::ScalingMatrix3x3(const BaseVector3 &vScale)
{
    this->ij[0][0] = vScale.x;
    this->ij[1][1] = vScale.y;
    this->ij[2][2] = vScale.z;

    this->ij[0][1] = this->ij[0][2] = this->ij[1][0] =
    this->ij[1][2] = this->ij[2][0] = this->ij[2][1] = SFloat::_0;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

ScalingMatrix3x3 ScalingMatrix3x3::operator*(const ScalingMatrix3x3 &matrix) const
{
    return ScalingMatrix3x3(this->ij[0][0] * matrix.ij[0][0],
                             this->ij[1][1] * matrix.ij[1][1],
                             this->ij[2][2] * matrix.ij[2][2]);
}

TransformationMatrix<Matrix4x4> ScalingMatrix3x3::operator*(const RotationMatrix3x3 &matrix) const
{
    TransformationMatrix<Matrix4x4> aux = TransformationMatrix<Matrix4x4>::GetIdentity();

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2];

    aux.ij[1][0] = this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][1] * matrix.ij[1][2];

    aux.ij[2][0] = this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

    return aux;
}

TransformationMatrix<Matrix4x4> ScalingMatrix3x3::operator*(const TranslationMatrix<Matrix4x4> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x4>(matrix);
}

TransformationMatrix<Matrix4x3> ScalingMatrix3x3::operator*(const TranslationMatrix<Matrix4x3> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x3>(matrix);
}

TransformationMatrix<Matrix4x4> ScalingMatrix3x3::operator*(const TransformationMatrix<Matrix4x4> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x4>(matrix);
}

TransformationMatrix<Matrix4x3> ScalingMatrix3x3::operator*(const TransformationMatrix<Matrix4x3> &matrix) const
{
    return this->ProductOperatorImp<Matrix4x3>(matrix);
}

ScalingMatrix3x3& ScalingMatrix3x3::operator=(const BaseMatrix3x3 &matrix)
{
    BaseMatrix3x3::operator=(matrix);
    return *this;
}

ScalingMatrix3x3 ScalingMatrix3x3::Invert() const
{
    // If one of the diagonal elements is 0, the matrix has not inverse.
    Z_ASSERT_WARNING(this->ij[0][0] != SFloat::_0 && this->ij[1][1] != SFloat::_0 && this->ij[2][2] != SFloat::_0, "One of the diagonal elements equals zero, so the matrix has not inverse");

    return ScalingMatrix3x3(SFloat::_1 / this->ij[0][0], SFloat::_1 / this->ij[1][1], SFloat::_1 / this->ij[2][2]);
}

void ScalingMatrix3x3::GetScale(float_z &fScaleX, float_z &fScaleY, float_z &fScaleZ) const
{
    fScaleX = this->ij[0][0];
    fScaleY = this->ij[1][1];
    fScaleZ = this->ij[2][2];
}

void ScalingMatrix3x3::GetScale(BaseVector3 &vScale) const
{
    vScale.x = this->ij[0][0];
    vScale.y = this->ij[1][1];
    vScale.z = this->ij[2][2];
}

float_z ScalingMatrix3x3::GetDeterminant() const
{
    return this->ij[0][0] * this->ij[1][1] * this->ij[2][2];
}

ScalingMatrix3x3& ScalingMatrix3x3::operator*=(const ScalingMatrix3x3 &matrix)
{
    this->ij[0][0] *= matrix.ij[0][0];
    this->ij[1][1] *= matrix.ij[1][1];
    this->ij[2][2] *= matrix.ij[2][2];

    return *this;
}

template <class MatrixT>
TransformationMatrix<MatrixT> ScalingMatrix3x3::ProductOperatorImp(const TranslationMatrix<MatrixT> &matrix) const
{
    TransformationMatrix<MatrixT> aux(TransformationMatrix<MatrixT>::GetIdentity());

    aux.ij[0][0] = this->ij[0][0];
    aux.ij[1][1] = this->ij[1][1];
    aux.ij[2][2] = this->ij[2][2];

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

    return aux;
}

/// <summary>
/// Multiplies a 4x3 or 4x4 transformation matrix by the resident matrix.
/// </summary>
/// <remarks>
/// This product is not conmmutative.
/// </remarks>
/// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
/// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
/// <returns>
/// The resultant 4x3 or 4x4 transformation matrix, depending on the method template parameter.
/// </returns>
template <class MatrixT>
TransformationMatrix<MatrixT> ScalingMatrix3x3::ProductOperatorImp(const TransformationMatrix<MatrixT> &matrix) const
{
    TransformationMatrix<MatrixT> aux(TransformationMatrix<MatrixT>::GetIdentity());

    aux.ij[3][0] = matrix.ij[3][0];
    aux.ij[3][1] = matrix.ij[3][1];
    aux.ij[3][2] = matrix.ij[3][2];

    aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
    aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1];
    aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2];

    aux.ij[1][0] = this->ij[1][1] * matrix.ij[1][0];
    aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
    aux.ij[1][2] = this->ij[1][1] * matrix.ij[1][2];

    aux.ij[2][0] = this->ij[2][2] * matrix.ij[2][0];
    aux.ij[2][1] = this->ij[2][2] * matrix.ij[2][1];
    aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

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

const ScalingMatrix3x3& ScalingMatrix3x3::GetIdentity()
{
    static const ScalingMatrix3x3 IDENTITY(Matrix3x3::GetIdentity());
    return IDENTITY;
}


} // namespace z
