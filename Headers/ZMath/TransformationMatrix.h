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

#ifndef __TRANSFORMATIONMATRIX__
#define __TRANSFORMATIONMATRIX__

#include "ZMath/MathDefinitions.h"
#include "ZMath/BaseQuaternion.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/Vector3.h"
#include "ZMath/BaseVector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/TranslationMatrix.h"


namespace z
{

// Preventing friend global operator to be called.
template <class MatrixT>
TransformationMatrix<MatrixT> operator*(const float_z fScalar, const TransformationMatrix<MatrixT> &matrix);

/// <summary>
/// Class that represents a transformation matrix.
/// </summary>
/// <remarks>
/// A transformation matrix is, in general, composed of a scale, a rotation and a translation (or any combination of them).<br/>
/// If we note:<br/>
/// <br/>
/// \f$ S = \begin{bmatrix} s_x & 0 & 0 & 0 \\ 0 & s_y & 0 & 0 \\ 0 & 0 & s_z & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$,<br/>
/// <br/>
/// \f$ R = \begin{bmatrix} r_{00} & r_{01} & r_{02} & 0 \\ r_{10} & r_{11} & r_{12} & 0 \\ r_{20} & r_{21} & r_{22} & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$, and <br/>
/// <br/>
/// \f$ T = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$,<br/>
/// <br/>
/// which are the scale matrix, the rotation matrix and the translation matrix respectively, we compose the transformation as follows:<br/>
/// <br/>
/// \f$ SRT = \begin{bmatrix} s_x\dot r_{00} & s_x\dot r_{01} & s_x\dot r_{02} & 0 \\ s_y\dot r_{10} & s_y\dot r_{11} & s_y\dot r_{12} & 0 \\
/// s_z\dot r_{20} & s_z\dot r_{21} & s_z\dot r_{22} & 0 \\ d_x & d_y & d_z & 1 \end{bmatrix}\f$<br/>
/// <br/>
/// Since this class is a template, we allow the use of a 4x4 matrix or a 4x3 one as parameter.<br/>
/// When parameter is a 4x3 matrix, we treat it as a 4x4 matrix, assuming that fourth column is:<br/>
/// <br/>
/// \f$ \begin{bmatrix} 0 \\ 0 \\ 0 \\ 1 \end{bmatrix}\f$.
/// </remarks>
/// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
template <class MatrixT>
class TransformationMatrix : public MatrixT
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    TransformationMatrix() : MatrixT(TransformationMatrix::GetIdentity())
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The matrix from which we want to create a copy in the resident matrix.</param>
    TransformationMatrix(const TransformationMatrix<MatrixT> &matrix) : MatrixT(matrix)
    {
    }

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix in which we want the resident matrix to be based.</param>
    TransformationMatrix(const MatrixT &matrix) : MatrixT(matrix)
    {
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 3D vector which stores the translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="qRotation">[IN] Quaternion with the rotation values. It's supposed to be normalized.</param>
    /// <param name="vScale">[IN] Vector with the scale values (where 1 means 100%).</param>
    TransformationMatrix(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale)
    {
        this->Initialize(vTranslation.x, vTranslation.y, vTranslation.z,
                         qRotation.x, qRotation.y, qRotation.z, qRotation.w,
                         vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor from a 3D vector which stores the scale, a quaternion which stores the rotation
    /// and a 4D vector which stores the translation.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector with the displacement values.</param>
    /// <param name="qRotation">[IN] Quaternion with the rotation values. It's supposed to be normalized.</param>
    /// <param name="vScale">[IN] Vector with the scale values (where 1 means 100%).</param>
    TransformationMatrix(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale)
    {
        this->Initialize(vTranslation.x, vTranslation.y, vTranslation.z,
                         qRotation.x, qRotation.y, qRotation.z, qRotation.w,
                         vScale.x, vScale.y, vScale.z);
    }

    /// <summary>
    /// Constructor that receives three scaling values (where 1 means 100%), one for each axis direction, four rotation values
    /// which define a rotation quaternion and three displacement values which define a translation.
    /// </summary>
    /// <param name="fTranslationX">[IN] Displazament within X direction.</param>
    /// <param name="fTranslationY">[IN] Displazament within Y direction.</param>
    /// <param name="fTranslationZ">[IN] Displazament within Z direction.</param>
    /// <param name="fRotationX">[IN] X component of the rotation quaternion.</param>
    /// <param name="fRotationY">[IN] Y component of the rotation quaternion.</param>
    /// <param name="fRotationZ">[IN] Z component of the rotation quaternion.</param>
    /// <param name="fRotationW">[IN] W component of the rotation quaternion.</param>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    TransformationMatrix(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ,
                                 const float_z fRotationX, const float_z fRotationY, const float_z fRotationZ, const float_z fRotationW,
                                 const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ)
    {
        this->Initialize(fTranslationX, fTranslationY, fTranslationZ,
                         fRotationX, fRotationY, fRotationZ, fRotationW,
                         fScaleX, fScaleY, fScaleZ);
    }

    /// <summary>
    /// Constructor from a translation matrix, a 3x3 rotation matrix and a 3x3 scale matrix.
    /// </summary>
    /// <param name="translation">[IN] A translation matrix.</param>
    /// <param name="rotation">[IN] A rotation matrix.</param>
    /// <param name="scale">[IN] A scale matrix.</param>
    TransformationMatrix(const TranslationMatrix<Matrix4x3> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
    {
        TransformationMatrixImp(translation, rotation, scale);
    }

    /// <summary>
    /// Constructor from a translation matrix, a 3x3 rotation matrix and a 3x3 scale matrix.
    /// </summary>
    /// <param name="translation">[IN] A translation matrix.</param>
    /// <param name="rotation">[IN] A rotation matrix.</param>
    /// <param name="scale">[IN] A scale matrix.</param>
    TransformationMatrix(const TranslationMatrix<Matrix4x4> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
    {
        TransformationMatrixImp(translation, rotation, scale);
    }

private:

    using MatrixT::operator*;
    using MatrixT::operator/;
    using MatrixT::operator+;
    using MatrixT::operator-;
    using MatrixT::operator*=;
    using MatrixT::operator/=;
    using MatrixT::operator+=;
    using MatrixT::operator-=;

    /// <summary>
    /// Constructor from a 4x3 or 4x4 (depending on the constructor template parameter) translation matrix, a 3x3 rotation matrix and
    /// a 3x3 scale matrix.
    /// </summary>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="translation">[IN] A translation matrix.</param>
    /// <param name="rotation">[IN] A rotation matrix.</param>
    /// <param name="scale">[IN] A scale matrix.</param>
    template <class MatrixParamT>
    void TransformationMatrixImp(const TranslationMatrix<MatrixParamT> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale)
    {
        this->ResetToIdentity();

        this->ij[0][0] = scale.ij[0][0] * rotation.ij[0][0];
        this->ij[0][1] = scale.ij[0][0] * rotation.ij[0][1];
        this->ij[0][2] = scale.ij[0][0] * rotation.ij[0][2];

        this->ij[1][0] = scale.ij[1][1] * rotation.ij[1][0];
        this->ij[1][1] = scale.ij[1][1] * rotation.ij[1][1];
        this->ij[1][2] = scale.ij[1][1] * rotation.ij[1][2];

        this->ij[2][0] = scale.ij[2][2] * rotation.ij[2][0];
        this->ij[2][1] = scale.ij[2][2] * rotation.ij[2][1];
        this->ij[2][2] = scale.ij[2][2] * rotation.ij[2][2];

        this->ij[3][0] = translation.ij[3][0];
        this->ij[3][1] = translation.ij[3][1];
        this->ij[3][2] = translation.ij[3][2];
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:<br/>
    /// <br/>
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 & 0 \\ 0 & 1 & 0 & 0 \\ 0 & 0 & 1 & 0 \\ 0 & 0 & 0 & 1 \end{bmatrix}\f$<br/>
    /// </remarks>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    static const TransformationMatrix<MatrixT>& GetIdentity()
    {
        static const TransformationMatrix<MatrixT> IDENTITY(MatrixT::GetIdentity());
        return IDENTITY;
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const TransformationMatrix<Matrix4x3> &matrix) const
    {
        TransformationMatrix<MatrixT> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// The product is calculated knowing that the fourth column is (0,0,0,1).<br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const TransformationMatrix<Matrix4x4> &matrix) const
    {
        TransformationMatrix<MatrixT> outMatrix;
        ProductOperatorImp<Matrix4x4>(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a translation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const TranslationMatrix<Matrix4x3> &matrix) const
    {
        TransformationMatrix<MatrixT> outMatrix;
        ProductOperatorImp<Matrix4x3>(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a translation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const TranslationMatrix<Matrix4x4> &matrix) const
    {
        TransformationMatrix<MatrixT> outMatrix;
        ProductOperatorImp(matrix, outMatrix);
        return outMatrix;
    }

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// The rotation matrix is extended to a 4x4 matrix to allow this product.<br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const RotationMatrix3x3 &matrix) const
    {
        TransformationMatrix<MatrixT> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// The scale matrix is extended to a 4x4 matrix to allow this product.<br/>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant transformation matrix.
    /// </returns>
    TransformationMatrix<MatrixT> operator*(const ScalingMatrix3x3 &matrix) const
    {
        TransformationMatrix<MatrixT> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0];
        aux.ij[0][1] = this->ij[0][1] * matrix.ij[1][1];
        aux.ij[0][2] = this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0];
        aux.ij[1][1] = this->ij[1][1] * matrix.ij[1][1];
        aux.ij[1][2] = this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0];
        aux.ij[2][1] = this->ij[2][1] * matrix.ij[1][1];
        aux.ij[2][2] = this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0];
        aux.ij[3][1] = this->ij[3][1] * matrix.ij[1][1];
        aux.ij[3][2] = this->ij[3][2] * matrix.ij[2][2];

        return aux;
    }

    /// <summary>
    /// Product and assign operator. Resident matrix stores the result of the multiplication.
    /// </summary>
    /// <remarks>
    /// Multiplies a transformation matrix by the resident matrix.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    TransformationMatrix<MatrixT>& operator*=(const TransformationMatrix<Matrix4x3> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Product and assign operator. Resident matrix stores the result of the multiplication.
    /// </summary>
    /// <remarks>
    /// Multiplies a transformation matrix by the resident matrix.<br/>
    /// The product is calculated knowing that last column of matrices is (0,0,0,1).
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    TransformationMatrix<MatrixT>& operator*=(const TransformationMatrix<Matrix4x4> &matrix)
    {
        ProductAssignationOperatorImp(matrix);
        return *this;
    }

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a transformation matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    TransformationMatrix<MatrixT>& operator=(const MatrixT &matrix)
    {
        MatrixT::operator=(matrix);
        return *this;
    }

    /// <summary>
    /// Calculates the determinant of the matrix.
    /// </summary>
    /// <remarks>
    /// Since this is a transformation matrix, its determinant can be calculated as
    /// if it was a 3x3 matrix, removing fourth row and fourth column in calculus:<br/>
    /// <br/>
    /// \f$ \left|A\right| = a_{00}\cdot a_{11}\cdot a_{22} + a_{01}\cdot a_{12}\cdot a_{20} + a_{02}\cdot a_{10}\cdot a_{21} -
    /// (a_{02}\cdot a_{11}\cdot a_{20} + a_{00}\cdot a_{12}\cdot a_{21} + a_{01}\cdot a_{10}\cdot a_{22})\f$
    /// </remarks>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_z GetDeterminant() const
    {
        return this->ij[0][0] * this->ij[1][1] * this->ij[2][2] +
               this->ij[0][1] * this->ij[1][2] * this->ij[2][0] +
               this->ij[0][2] * this->ij[1][0] * this->ij[2][1] -
               this->ij[0][2] * this->ij[1][1] * this->ij[2][0] -
               this->ij[0][0] * this->ij[1][2] * this->ij[2][1] -
               this->ij[0][1] * this->ij[1][0] * this->ij[2][2];
    }

    /// <summary>
    /// Calculates whether the matrix has inverse or not.
    /// </summary>
    /// <remarks>
    /// A matrix has inverse when its determinant doesn't equal zero.
    /// </remarks>
    /// <returns>
    /// True if the matrix has inverse, false otherwise.
    /// </returns>
    bool HasInverse() const
    {
        // If Determinant is 0, this matrix has not inverse.
        return SFloat::IsNotZero(this->GetDeterminant());
    }

    /// <summary>
    /// Inverses the matrix.
    /// </summary>
    /// <remarks>
    /// This method is optimized with respect to the base matrix class so the fourth column is ignored. Take this into
    /// account when performing operations that include matrix transposing (use base matrix class version instead) or
    /// wrong results will be obtained.<br/>
    /// The inverse of a square matrix with non zero determinant is another matrix which verifies that:<br/>
    /// <br/>
    /// \f$ A\cdot A^{-1}  = A^{-1}\cdot A = I\f$<br/>
    /// <br/>
    /// We can calculate the inverse of any matrix by:<br/>
    /// <br/>
    /// \f$ A^{-1} = \frac{1}{\left|A\right|}\cdot C^T_{ij}\f$,<br/>
    /// <br/>
    /// where \f$ C^T_{ij}\f$ is the matrix formed by each cofactor of each element of A, trasposed.<br/>
    /// Since the matrix is a transformation matrix, then the inversion can be optimized avoiding all products by
    /// the elements of the fourth column.<br/>
    /// Inverse has this general form, expressed in function of the scale, the rotation and the translation:<br/>
    /// <br/>
    /// \f$ (SRT)^{-1} = T^{-1}\cdot R^{-1}\cdot S^{-1} = \begin{bmatrix} \frac{r_{00}}{S_x} & \frac{r_{10}}{S_y} & \frac{r_{20}}{S_z} & 0 \\
    /// \frac{r_{01}}{S_x} & \frac{r_{11}}{S_y} & \frac{r_{21}}{S_z} & 0 \\
    /// \frac{r_{02}}{S_x} & \frac{r_{12}}{S_y} & \frac{r_{22}}{S_z} & 0 \\
    /// \frac{-r_{00}d_x-r_{01}d_y-r_{02}d_z}{S_x} & \frac{-r_{10}d_x-r_{11}d_y-r_{12}d_z}{S_y} & \frac{-r_{20}d_x-r_{21}d_y-r_{22}d_z}{S_z} & 1 \end{bmatrix} \f$
    /// </remarks>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    TransformationMatrix<MatrixT> Invert() const
    {
        // The results will be wrong when the determinant equals zero
        Z_ASSERT_WARNING( this->GetDeterminant() != SFloat::_0, "Matrices whose determinant equals zero do not have inverse, this will produce a division by zero" );

        // Gets the inverse of the Determinant.
        const float_z INV_DET = SFloat::_1 / this->GetDeterminant();

        // Binary products are stored in vars to avoid unnecesary repetitions
        const float_z& fA = this->ij[0][0] * this->ij[1][1];
        const float_z& fD = this->ij[2][1] * this->ij[3][0];
        const float_z& fE = this->ij[0][1] * this->ij[1][0];
        const float_z& fH = this->ij[2][0] * this->ij[3][1];
        const float_z& fJ = this->ij[2][1] * this->ij[3][2];
        const float_z& fK = this->ij[2][2] * this->ij[3][1];
        const float_z& fN = this->ij[2][0] * this->ij[3][2];
        const float_z& fO = this->ij[2][2] * this->ij[3][0];
        const float_z& fQ = this->ij[0][1] * this->ij[1][2];
        const float_z& fT = this->ij[0][2] * this->ij[1][1];
        const float_z& fU = this->ij[0][0] * this->ij[1][2];
        const float_z& fX = this->ij[0][2] * this->ij[1][0];

        MatrixT aux;

        aux = *this;

        // 1st column of inverse
        aux.ij[0][0] =  INV_DET * (this->ij[1][1] * this->ij[2][2] - this->ij[1][2] * this->ij[2][1] );
        aux.ij[1][0] = -INV_DET * (this->ij[1][0] * this->ij[2][2] - this->ij[1][2] * this->ij[2][0] );
        aux.ij[2][0] =  INV_DET * (this->ij[1][0] * this->ij[2][1] - this->ij[1][1] * this->ij[2][0] );
        aux.ij[3][0] = -INV_DET * (this->ij[1][0] * fJ + this->ij[1][1] * fO + this->ij[1][2] * fH -
                                   this->ij[1][2] * fD - this->ij[1][0] * fK - this->ij[1][1] * fN );

        // 2nd column of inverse
        aux.ij[0][1] = -INV_DET * (this->ij[0][1] * this->ij[2][2] - this->ij[0][2] * this->ij[2][1] );
        aux.ij[1][1] =  INV_DET * (this->ij[0][0] * this->ij[2][2] - this->ij[0][2] * this->ij[2][0] );
        aux.ij[2][1] = -INV_DET * (this->ij[0][0] * this->ij[2][1] - this->ij[0][1] * this->ij[2][0] );
        aux.ij[3][1] =  INV_DET * (this->ij[0][0] * fJ + this->ij[0][1] * fO + this->ij[0][2] * fH -
                                   this->ij[0][2] * fD - this->ij[0][0] * fK - this->ij[0][1] * fN );

        // 3rd column of inverse
        aux.ij[0][2] =  INV_DET * (fQ - fT);
        aux.ij[1][2] = -INV_DET * (fU - fX);
        aux.ij[2][2] =  INV_DET * (fA - fE);
        aux.ij[3][2] = -INV_DET * (fA * this->ij[3][2] + fQ * this->ij[3][0] + fX * this->ij[3][1] -
                                   fT * this->ij[3][0] - fU * this->ij[3][1] - fE * this->ij[3][2] );

        return aux;
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="fTranslationX">[OUT] Displacement in X axis direction.</param>
    /// <param name="fTranslationY">[OUT] Displacement in Y axis direction.</param>
    /// <param name="fTranslationZ">[OUT] Displacement in Z axis direction.</param>
    void GetTranslation(float_z &fTranslationX, float_z &fTranslationY, float_z &fTranslationZ) const
    {
        fTranslationX = this->ij[3][0];
        fTranslationY = this->ij[3][1];
        fTranslationZ = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement.</param>
    void GetTranslation(BaseVector3 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
    }

    /// <summary>
    /// Extracts the displacement components from the matrix.
    /// </summary>
    /// <param name="vTranslation">[OUT] Vector where to store the displacement. W component of this vector will be set to 0.</param>
    void GetTranslation(BaseVector4 &vTranslation) const
    {
        vTranslation.x = this->ij[3][0];
        vTranslation.y = this->ij[3][1];
        vTranslation.z = this->ij[3][2];
        vTranslation.w = SFloat::_0;
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="fScaleX">[OUT] Resultant scale in X axis direction.</param>
    /// <param name="fScaleY">[OUT] Resultant scale in Y axis direction.</param>
    /// <param name="fScaleZ">[OUT] Resultant scale in Z axis direction.</param>
    void GetScale(float_z &fScaleX, float_z &fScaleY, float_z &fScaleZ) const
    {
        fScaleX = sqrt_z(this->ij[0][0] * this->ij[0][0] + this->ij[0][1] * this->ij[0][1] + this->ij[0][2] * this->ij[0][2]);
        fScaleY = sqrt_z(this->ij[1][0] * this->ij[1][0] + this->ij[1][1] * this->ij[1][1] + this->ij[1][2] * this->ij[1][2]);
        fScaleZ = sqrt_z(this->ij[2][0] * this->ij[2][0] + this->ij[2][1] * this->ij[2][1] + this->ij[2][2] * this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the scale factors from the matrix.
    /// </summary>
    /// <param name="vScale">[OUT] Vector where to store the scale factors.</param>
    void GetScale(BaseVector3 &vScale) const
    {
        vScale.x = sqrt_z(this->ij[0][0] * this->ij[0][0] + this->ij[0][1] * this->ij[0][1] + this->ij[0][2] * this->ij[0][2]);
        vScale.y = sqrt_z(this->ij[1][0] * this->ij[1][0] + this->ij[1][1] * this->ij[1][1] + this->ij[1][2] * this->ij[1][2]);
        vScale.z = sqrt_z(this->ij[2][0] * this->ij[2][0] + this->ij[2][1] * this->ij[2][1] + this->ij[2][2] * this->ij[2][2]);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining the Euler angles.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained angles don't match those used to build the matrix.
    /// </remarks>
    /// <param name="fRotationAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fRotationAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fRotationAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_z &fRotationAngleX, float_z &fRotationAngleY, float_z &fRotationAngleZ) const
    {
        RotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(fRotationAngleX, fRotationAngleY, fRotationAngleZ);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining a rotation quaternion.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="qRotation">[OUT] Quaternion where to store the extracted rotation.</param>
    void GetRotation(BaseQuaternion &qRotation) const
    {
        RotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(qRotation);
    }

    /// <summary>
    /// Extracts the rotation from the transformation matrix, obtaining an angle and a spin axis.
    /// </summary>
    /// <param name="fRotationAngle">[OUT] Angle of rotation.</param>
    /// <param name="vRotationAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_z &fRotationAngle, BaseVector3 &vRotationAxis) const
    {
        RotationMatrix3x3 mAux = this->ToRotationMatrix3x3();
        mAux.GetRotation(fRotationAngle, vRotationAxis);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="vTranslation">[OUT] Vector to store the translation.</param>
    /// <param name="qRotation">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    void Decompose(BaseVector3 &vTranslation, BaseQuaternion &qRotation, BaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRotation);
        this->GetTranslation(vTranslation);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated variables.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained quaternion doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="vTranslation">[OUT] Vector to store the translation.</param>
    /// <param name="qRotation">[OUT] Quaternion to store the rotation.</param>
    /// <param name="vScale">[OUT] Vector to store the scale.</param>
    void Decompose(BaseVector4 &vTranslation, BaseQuaternion &qRotation, BaseVector3 &vScale) const
    {
        this->GetScale(vScale);
        this->GetRotation(qRotation);
        this->GetTranslation(vTranslation);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(TransformationMatrix<Matrix4x3> &translation,
                   TransformationMatrix<Matrix4x3> &rotation,
                   TransformationMatrix<Matrix4x3> &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(TransformationMatrix<Matrix4x4> &translation,
                   TransformationMatrix<Matrix4x4> &rotation,
                   TransformationMatrix<Matrix4x4> &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(TranslationMatrix<Matrix4x3> &translation,
                   RotationMatrix3x3 &rotation,
                   ScalingMatrix3x3 &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// </summary>
    /// <remarks>
    /// Realize that getting the rotation of transformation matrices which were compound of negative scales may
    /// cause that obtained rotation matrix doesn't match that used to build the matrix.
    /// </remarks>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    void Decompose(TranslationMatrix<Matrix4x4> &translation,
                   RotationMatrix3x3 &rotation,
                   ScalingMatrix3x3 &scale) const
    {
        DecomposeImp(translation, rotation, scale);
    }

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// </summary>
    /// <remarks>
    /// Remember that Zunderbolt works with left-hand convention by default.
    /// To do that, we invert both rotation (by trasposing it) and z translation component.<br/>
    /// If the matrix was built using a null scale, the result is undefined.
    /// </remarks>
    /// <returns>
    /// The converted matrix.
    /// </returns>
    TransformationMatrix<MatrixT> SwitchHandConvention() const
    {
        Vector3 vScale;
        this->GetScale(vScale);

        Z_ASSERT_WARNING(vScale.x != SFloat::_0 && vScale.y != SFloat::_0 && vScale.z != SFloat::_0, "The scale must not be null, this will produce a division by zero");

        Vector3 vInvScale = Vector3::GetVectorOfOnes() / vScale;

        // Rotation correction
        TransformationMatrix<MatrixT> switchedMatrix = *this;
        switchedMatrix.ij[0][1] = this->ij[1][0] * vInvScale.y;
        switchedMatrix.ij[1][0] = this->ij[0][1] * vInvScale.x;
        switchedMatrix.ij[0][2] = this->ij[2][0] * vInvScale.z;
        switchedMatrix.ij[2][0] = this->ij[0][2] * vInvScale.x;
        switchedMatrix.ij[2][1] = this->ij[1][2] * vInvScale.y;
        switchedMatrix.ij[1][2] = this->ij[2][1] * vInvScale.z;

        // Scale correction
        switchedMatrix.ij[0][1] *= vScale.x;
        switchedMatrix.ij[1][0] *= vScale.y;
        switchedMatrix.ij[0][2] *= vScale.x;
        switchedMatrix.ij[2][0] *= vScale.z;
        switchedMatrix.ij[2][1] *= vScale.z;
        switchedMatrix.ij[1][2] *= vScale.y;

        // Translation correction
        switchedMatrix.ij[3][2] = -this->ij[3][2];

        return switchedMatrix;
    }

protected:

    /// <summary>
    /// Function to convert the 3x3 submatrix which contains the rotation and the scale into
    /// a 3x3 rotation matrix without the scale.
    /// </summary>
    /// <remarks>
    /// It uses the fact that in a 3x3 rotation matrix,
    /// the length of any row o column vector is 1, so current length of each row in the transformation matrix
    /// is the scale factor (each row have a scale factor which matches with an axis).
    /// Dividing each row by its length we obtain the original rotation matrix.
    /// </remarks>
    /// <returns>
    /// The extracted rotation matrix.
    /// </returns>
    RotationMatrix3x3 ToRotationMatrix3x3() const
    {
        Vector3 vScale;
        this->GetScale(vScale);

        Z_ASSERT_WARNING( !vScale.IsZero(), "The scale must not be null, this will produce a division by zero" );

        Vector3 vInvScale = Vector3::GetVectorOfOnes() / vScale;

        return RotationMatrix3x3(Matrix3x3(this->ij[0][0] * vInvScale.x, this->ij[0][1] * vInvScale.x, this->ij[0][2] * vInvScale.x,
                                             this->ij[1][0] * vInvScale.y, this->ij[1][1] * vInvScale.y, this->ij[1][2] * vInvScale.y,
                                             this->ij[2][0] * vInvScale.z, this->ij[2][1] * vInvScale.z, this->ij[2][2] * vInvScale.z));
    }

    /// <summary>
    /// Initializes the transformation matrix from the components of a scale vector,
    /// a rotation quaternion and a translation vector.
    /// </summary>
    /// <param name="fTranslationX">[IN] Displazament within X direction.</param>
    /// <param name="fTranslationY">[IN] Displazament within Y direction.</param>
    /// <param name="fTranslationZ">[IN] Displazament within Z direction.</param>
    /// <param name="fRotationX">[IN] X component of the rotation quaternion.</param>
    /// <param name="fRotationY">[IN] Y component of the rotation quaternion.</param>
    /// <param name="fRotationZ">[IN] Z component of the rotation quaternion.</param>
    /// <param name="fRotationW">[IN] W component of the rotation quaternion.</param>
    /// <param name="fScaleX">[IN] Scale within X direction.</param>
    /// <param name="fScaleY">[IN] Scale within Y direction.</param>
    /// <param name="fScaleZ">[IN] Scale within Z direction.</param>
    void Initialize(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ,
                    const float_z fRotationX, const float_z fRotationY, const float_z fRotationZ, const float_z fRotationW,
                    const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ)
    {
        BaseQuaternion qRot(fRotationX, fRotationY, fRotationZ, fRotationW);

        RotationMatrix3x3 mRot(qRot);

        this->ResetToIdentity();

        this->ij[0][0] = fScaleX * mRot.ij[0][0];
        this->ij[0][1] = fScaleX * mRot.ij[0][1];
        this->ij[0][2] = fScaleX * mRot.ij[0][2];

        this->ij[1][0] = fScaleY * mRot.ij[1][0];
        this->ij[1][1] = fScaleY * mRot.ij[1][1];
        this->ij[1][2] = fScaleY * mRot.ij[1][2];

        this->ij[2][0] = fScaleZ * mRot.ij[2][0];
        this->ij[2][1] = fScaleZ * mRot.ij[2][1];
        this->ij[2][2] = fScaleZ * mRot.ij[2][2];

        this->ij[3][0] = fTranslationX;
        this->ij[3][1] = fTranslationY;
        this->ij[3][2] = fTranslationZ;
    }

private:

    /// <summary>
    /// Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    /// knowing that fourth column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <param name="outMatrix">[OUT] Resultant matrix.</param>
    template <class MatrixParamT>
    void ProductOperatorImp(const TransformationMatrix<MatrixParamT> &matrix, TransformationMatrix<MatrixT> &outMatrix) const
    {
        outMatrix = *this;

        outMatrix.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        outMatrix.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        outMatrix.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        outMatrix.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        outMatrix.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        outMatrix.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        outMatrix.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        outMatrix.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        outMatrix.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        outMatrix.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        outMatrix.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        outMatrix.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];
    }

    /// <summary>
    /// Multiplies a 4x4 or 4x3 (depending on the method template parameter) translation matrix by the current matrix,
    /// following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <param name="outMatrix">[OUT] Resultant matrix.</param>
    template <class MatrixParamT>
    void ProductOperatorImp(const TranslationMatrix<MatrixParamT> &matrix, TransformationMatrix<MatrixT> &outMatrix) const
    {
        outMatrix = *this;

        outMatrix.ij[3][0] += matrix.ij[3][0];
        outMatrix.ij[3][1] += matrix.ij[3][1];
        outMatrix.ij[3][2] += matrix.ij[3][2];
    }

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// Multiplies a transformation matrix by the resident matrix. No matter if the input matrix or the resident one are
    /// 4x3 or 4x4 matrices ore one of each type. Since both are transformation matrices, the product is calculated
    /// knowing that last column of both matrices is (0,0,0,1), even in 4x3 ones, where it is implicit.
    /// </summary>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    template <class MatrixParamT>
    void ProductAssignationOperatorImp(const TransformationMatrix<MatrixParamT> &matrix)
    {
        TransformationMatrix<MatrixT> aux;

        aux = *this;

        aux.ij[0][0] = this->ij[0][0] * matrix.ij[0][0] + this->ij[0][1] * matrix.ij[1][0] + this->ij[0][2] * matrix.ij[2][0];
        aux.ij[0][1] = this->ij[0][0] * matrix.ij[0][1] + this->ij[0][1] * matrix.ij[1][1] + this->ij[0][2] * matrix.ij[2][1];
        aux.ij[0][2] = this->ij[0][0] * matrix.ij[0][2] + this->ij[0][1] * matrix.ij[1][2] + this->ij[0][2] * matrix.ij[2][2];

        aux.ij[1][0] = this->ij[1][0] * matrix.ij[0][0] + this->ij[1][1] * matrix.ij[1][0] + this->ij[1][2] * matrix.ij[2][0];
        aux.ij[1][1] = this->ij[1][0] * matrix.ij[0][1] + this->ij[1][1] * matrix.ij[1][1] + this->ij[1][2] * matrix.ij[2][1];
        aux.ij[1][2] = this->ij[1][0] * matrix.ij[0][2] + this->ij[1][1] * matrix.ij[1][2] + this->ij[1][2] * matrix.ij[2][2];

        aux.ij[2][0] = this->ij[2][0] * matrix.ij[0][0] + this->ij[2][1] * matrix.ij[1][0] + this->ij[2][2] * matrix.ij[2][0];
        aux.ij[2][1] = this->ij[2][0] * matrix.ij[0][1] + this->ij[2][1] * matrix.ij[1][1] + this->ij[2][2] * matrix.ij[2][1];
        aux.ij[2][2] = this->ij[2][0] * matrix.ij[0][2] + this->ij[2][1] * matrix.ij[1][2] + this->ij[2][2] * matrix.ij[2][2];

        aux.ij[3][0] = this->ij[3][0] * matrix.ij[0][0] + this->ij[3][1] * matrix.ij[1][0] + this->ij[3][2] * matrix.ij[2][0] + matrix.ij[3][0];
        aux.ij[3][1] = this->ij[3][0] * matrix.ij[0][1] + this->ij[3][1] * matrix.ij[1][1] + this->ij[3][2] * matrix.ij[2][1] + matrix.ij[3][1];
        aux.ij[3][2] = this->ij[3][0] * matrix.ij[0][2] + this->ij[3][1] * matrix.ij[1][2] + this->ij[3][2] * matrix.ij[2][2] + matrix.ij[3][2];

        *this = aux;
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated transformation matrices.
    /// They can be 4x3 or 4x4 matrices, depending on the method template parameter.
    /// </summary>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    template <class MatrixParamT>
    void DecomposeImp(TransformationMatrix<MatrixParamT> &translation,
                      TransformationMatrix<MatrixParamT> &rotation,
                      TransformationMatrix<MatrixParamT> &scale) const
    {
        BaseVector3 vAux;
        this->GetScale(vAux);

        scale.ResetToIdentity();

        scale.ij[0][0] = vAux.x;
        scale.ij[1][1] = vAux.y;
        scale.ij[2][2] = vAux.z;

        BaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        rotation = TransformationMatrix<MatrixParamT>(SFloat::_0, SFloat::_0, SFloat::_0,
                                                          qRotAux.x , qRotAux.y , qRotAux.z , qRotAux.w,
                                                          SFloat::_1, SFloat::_1, SFloat::_1);
        this->GetTranslation(vAux);

        translation.ResetToIdentity();

        translation.ij[3][0] = vAux.x;
        translation.ij[3][1] = vAux.y;
        translation.ij[3][2] = vAux.z;
    }

    /// <summary>
    /// Extracts the scale, the rotation and the translation into separated scale, rotation and translation matrices.
    /// The translation matrix can be 4x3 or 4x4 matrix, depending on the method template parameter.
    /// </summary>
    /// <typeparam name="MatrixParamT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="translation">[OUT] Matrix to store the translation.</param>
    /// <param name="rotation">[OUT] Matrix to store the rotation.</param>
    /// <param name="scale">[OUT] Matrix to store the scale.</param>
    template <class MatrixParamT>
    void DecomposeImp(TranslationMatrix<MatrixParamT> &translation,
                      RotationMatrix3x3 &rotation,
                      ScalingMatrix3x3 &scale) const
    {
        BaseVector3 vAux;
        this->GetScale(vAux);

        scale.ResetToIdentity();

        scale.ij[0][0] = vAux.x;
        scale.ij[1][1] = vAux.y;
        scale.ij[2][2] = vAux.z;

        BaseQuaternion qRotAux;
        this->GetRotation(qRotAux);

        // Makes a transformation matrix with current rotation, scale 1 and displacement 0
        rotation = RotationMatrix3x3 (qRotAux);

        this->GetTranslation(vAux);

        translation.ResetToIdentity();

        translation.ij[3][0] = vAux.x;
        translation.ij[3][1] = vAux.y;
        translation.ij[3][2] = vAux.z;
    }

    // Hidden method to prevent it could be used.
    void ResetToZero(){}

};

// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS TransformationMatrix<Matrix4x3>;
template class Z_MATH_MODULE_SYMBOLS TransformationMatrix<Matrix4x4>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS


// Note: The following global operators have been defined this way in order to avoid a mutual inclusion between TranslationMatrix and TransformationMatrix
//       The user can then multiply matrices without worrying about whether a global operator or a class method is called (Koenig Lookup takes place in this case and operators do not have to be "imported").

/// <summary>
/// Multiplies a translation matrix by a transformation matrix, following matrices product rules.
/// </summary>
/// <remarks>
/// This product is not conmmutative.
/// </remarks>
/// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
/// <param name="translation">[IN] A translation matrix, the first operand.</param>
/// <param name="transformation">[IN] A transformation matrix, the second operand.</param>
/// <returns>
/// The resultant transformation matrix, with the same template parameter that the input translation matrix.
/// </returns>
template<class MatrixT>
TransformationMatrix<MatrixT> operator*(const TranslationMatrix<MatrixT> &translation, 
                                                                              const TransformationMatrix<Matrix4x3> &transformation)
{
    TransformationMatrix<MatrixT> aux = TransformationMatrix<MatrixT>::GetIdentity();

    aux.ij[0][0] = transformation.ij[0][0];
    aux.ij[0][1] = transformation.ij[0][1];
    aux.ij[0][2] = transformation.ij[0][2];

    aux.ij[1][0] = transformation.ij[1][0];
    aux.ij[1][1] = transformation.ij[1][1];
    aux.ij[1][2] = transformation.ij[1][2];

    aux.ij[2][0] = transformation.ij[2][0];
    aux.ij[2][1] = transformation.ij[2][1];
    aux.ij[2][2] = transformation.ij[2][2];

    aux.ij[3][0] = translation.ij[3][0] * transformation.ij[0][0] + translation.ij[3][1] * transformation.ij[1][0] + translation.ij[3][2] * transformation.ij[2][0] + transformation.ij[3][0];
    aux.ij[3][1] = translation.ij[3][0] * transformation.ij[0][1] + translation.ij[3][1] * transformation.ij[1][1] + translation.ij[3][2] * transformation.ij[2][1] + transformation.ij[3][1];
    aux.ij[3][2] = translation.ij[3][0] * transformation.ij[0][2] + translation.ij[3][1] * transformation.ij[1][2] + translation.ij[3][2] * transformation.ij[2][2] + transformation.ij[3][2];

    return aux;
}

/// <summary>
/// Multiplies a translation matrix by a transformation matrix, following matrices product rules.
/// </summary>
/// <remarks>
/// This product is not conmmutative.
/// </remarks>
/// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
/// <param name="translation">[IN] A translation matrix, the first operand.</param>
/// <param name="transformation">[IN] A transformation matrix, the second operand.</param>
/// <returns>
/// The resultant transformation matrix, with the same template parameter that the input translation matrix.
/// </returns>
template<class MatrixT>
TransformationMatrix<MatrixT> operator*(const TranslationMatrix<MatrixT> &translation, 
                                                                              const TransformationMatrix<Matrix4x4> &transformation)
{
    TransformationMatrix<MatrixT> aux = TransformationMatrix<MatrixT>::GetIdentity();

    aux.ij[0][0] = transformation.ij[0][0];
    aux.ij[0][1] = transformation.ij[0][1];
    aux.ij[0][2] = transformation.ij[0][2];

    aux.ij[1][0] = transformation.ij[1][0];
    aux.ij[1][1] = transformation.ij[1][1];
    aux.ij[1][2] = transformation.ij[1][2];

    aux.ij[2][0] = transformation.ij[2][0];
    aux.ij[2][1] = transformation.ij[2][1];
    aux.ij[2][2] = transformation.ij[2][2];

    aux.ij[3][0] = translation.ij[3][0] * transformation.ij[0][0] + translation.ij[3][1] * transformation.ij[1][0] + translation.ij[3][2] * transformation.ij[2][0] + transformation.ij[3][0];
    aux.ij[3][1] = translation.ij[3][0] * transformation.ij[0][1] + translation.ij[3][1] * transformation.ij[1][1] + translation.ij[3][2] * transformation.ij[2][1] + transformation.ij[3][1];
    aux.ij[3][2] = translation.ij[3][0] * transformation.ij[0][2] + translation.ij[3][1] * transformation.ij[1][2] + translation.ij[3][2] * transformation.ij[2][2] + transformation.ij[3][2];

    return aux;
}

} // namespace z

    
#endif // __TRANSFORMATIONMATRIX__
