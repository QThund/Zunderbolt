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

#ifndef __ROTATIONMATRIX3X3__
#define __ROTATIONMATRIX3X3__

#include "ZMath/Matrix3x3.h"



namespace z
{

// FORWARD DECLARATIONS
// ----------------------
class Vector3;
class Quaternion;
class ScalingMatrix3x3;
class Matrix4x3;
class Matrix4x4;

namespace Internals
{
    template<class MatrixT> class TransformationMatrix;
    template<class MatrixT> class TranslationMatrix;
}

typedef Internals::TranslationMatrix<Matrix4x3> TranslationMatrix4x3;
typedef Internals::TranslationMatrix<Matrix4x4> TranslationMatrix4x4;
typedef Internals::TransformationMatrix<Matrix4x3> TransformationMatrix4x3;
typedef Internals::TransformationMatrix<Matrix4x4> TransformationMatrix4x4;


/// <summary>
/// Class to represent a matrix of floating point values with 3 rows and 3 columns which contains a rotation.
/// </summary>
class Z_MATH_MODULE_SYMBOLS RotationMatrix3x3 : public Matrix3x3
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It is an empty constructor, it does not assign any value.
    /// </summary>
    RotationMatrix3x3();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="rotation">[IN] The 3x3 rotation matrix from which we want to create a copy in the resident matrix.</param>
    RotationMatrix3x3(const RotationMatrix3x3 &rotation);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a rotation matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="rotation">[IN] The 3x3 matrix in which we want the resident 3x3 rotation matrix to be based.</param>
    RotationMatrix3x3(const Matrix3x3 &rotation);

    /// <summary>
    /// Constructor that receives 3 angles, one for each Euler angle, to construct the rotation
    /// matrix of a specified rotation.
    /// </summary>
    /// <remarks>
    /// Zunderbolt follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.<br/>
    /// The rotation matrix is obtained as follows:
    ///
    /// \f$ R = \begin{bmatrix} \cos z & \sin z & 0 \\ -\sin z & \cos z & 0\\ 0 & 0 & 1 \end{bmatrix}
    /// \begin{bmatrix} 1 & 0 & 0\\ 0 & \cos x  & \sin x\\ 0 & -\sin x & \cos x \end{bmatrix}
    /// \begin{bmatrix} \cos y & 0 & -\sin y\\ 0 & 1 & 0\\ \sin y & 0 & \cos y \end{bmatrix} \f$
    ///
    /// This is a slow operation.
    /// </remarks>
    /// <param name="fRotationAngleX">[IN] Rotation angle about X global axis.</param>
    /// <param name="fRotationAngleY">[IN] Rotation angle about Y global axis.</param>
    /// <param name="fRotationAngleZ">[IN] Rotation angle about Z global axis.</param>
    RotationMatrix3x3(const float_z fRotationAngleX, const float_z fRotationAngleY, const float_z fRotationAngleZ);

    /// <summary>
    /// Constructor from an angle and a spin axis defined by a vector.
    /// </summary>
    /// <remarks>
    /// It's computed as follows:
    ///
    /// \f$ R = \begin{bmatrix} \cos\theta & 0 & 0 \\ 0 & \cos\theta & 0 \\ 0 & 0 & \cos\theta \end{bmatrix} + (1- \cos\theta)\cdot
    /// \begin{bmatrix} e_x \\ e_y \\ e_z\end{bmatrix} \cdot \begin{bmatrix} e_x & e_y & e_z\end{bmatrix} +
    /// \begin{bmatrix} 0 & e_z & -e_y \\ -e_z & 0 & e_x \\ e_y & -e_x & 0 \end{bmatrix}\cdot \sin\theta \f$
    ///
    /// where \f$ e=(e_x, e_y, e_z)\f$, is a unit vector defining spin axis.
    /// </remarks>
    /// <param name="fRotationAngle">[IN] Angle of rotation.</param>
    /// <param name="vRotationAxis">[IN] Vector in the direction of the spin axis.</param>
    /// <remarks>
    /// The axis vector must be normalized to construct the rotation matrix properly.
    /// </remarks>
    RotationMatrix3x3(const float_z fRotationAngle, const Vector3 &vRotationAxis);

    /// <summary>
    /// Constructor from a quaternion.
    /// </summary>
    /// <remarks>
    /// Is constructed as follows:<br/>
    /// <br/>
    /// \f$ R = \begin{bmatrix} 1 - 2(q_y^2 + q_z^2) & 2(q_xq_y - q_wq_z) & 2(q_xq_z + q_wq_y) \\
    /// 2(q_xq_y + q_wq_z) & 1 - 2(q_x^2 + q_z^2) & 2(q_yq_z - q_wq_x) \\
    /// 2(q_xq_z - q_wq_y) & 2(q_yq_z + q_wq_x) & 1 - 2(q_x^2 + q_y^2)
    /// \end{bmatrix}\f$<br/>
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation. It must be normalized to construct the rotation matrix properly</param>
    explicit RotationMatrix3x3(const Quaternion &qRotation);


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets an identity matrix.
    /// </summary>
    /// <remarks>
    /// The identity matrix is a matrix whose elements are zero except the main diagonal that is composed by ones:<br/>
    /// <br/>
    /// \f$ I = \begin{bmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1 \end{bmatrix}\f$<br/>
    /// </remarks>
    /// <returns>
    /// The identity matrix.
    /// </returns>
    static const RotationMatrix3x3& GetIdentity();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Multiplies a 3x3 rotation matrix by the current matrix, following matrices product rules.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Rotation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    RotationMatrix3x3 operator*(const RotationMatrix3x3 &matrix) const;

    /// <summary>
    /// Multiplies a 3x3 scale matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Scale matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
    /// </returns>
    TransformationMatrix4x4 operator*(const ScalingMatrix3x3 &matrix) const;

    /// <summary>
    /// Multiplies a 4x4 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
    /// </returns>
    TransformationMatrix4x4 operator*(const TranslationMatrix4x4 &matrix) const;

    /// <summary>
    /// Multiplies a 4x3 translation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix.
    /// </returns>
    TransformationMatrix4x3 operator*(const TranslationMatrix4x3 &matrix) const;

    /// <summary>
    /// Multiplies a 4x4 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x4 transformation matrix.
    /// </returns>
    TransformationMatrix4x4 operator*(const TransformationMatrix4x4 &matrix) const;

    /// <summary>
    /// Multiplies a 4x3 transformation matrix by the current matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 transformation matrix.
    /// </returns>
    TransformationMatrix4x3 operator*(const TransformationMatrix4x3 &matrix) const;

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a rotation matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    RotationMatrix3x3& operator=(const Matrix3x3 &matrix);

    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    RotationMatrix3x3& operator*=(const RotationMatrix3x3 &matrix);

    /// <summary>
    /// Inverts the matrix.
    /// </summary>
    /// <remarks>
    /// In the case of rotation matrices, the transpose is guaranteed to be the inverse of the matrix.
    /// So, it's faster than base class method.
    /// </remarks>
    /// <returns>
    /// The inverse of the matrix.
    /// </returns>
    RotationMatrix3x3 Invert() const;

    /// <summary>
    /// Converts rotation matrix to Euler angles.
    /// </summary>
    /// <remarks>
    /// Zunderbolt follows the rotation order convention: Z, then X, then Y, aka Yaw-Pitch-Roll.
    /// </remarks>
    /// <param name="fRotationAngleX">[OUT] Resultant rotation around X axis.</param>
    /// <param name="fRotationAngleY">[OUT] Resultant rotation around Y axis.</param>
    /// <param name="fRotationAngleZ">[OUT] Resultant rotation around Z axis.</param>
    void GetRotation(float_z &fRotationAngleX, float_z &fRotationAngleY, float_z &fRotationAngleZ) const;

    /// <summary>
    /// Converts rotation matrix to a rotation quaternion.
    /// </summary>
    /// <remarks>
    /// Since rotation matrices are special orthogonal matrices, where \f$ AA^T = AA^{-1} = I\f$, it's always verified
    /// that (1 + trace) > 0.<br/>
    /// Then, we can calculate quaternion component from every matrix trace.<br/>
    /// </remarks>
    /// <param name="qRotation">[OUT] Quaternion where to store the rotation.</param>
    void GetRotation(Quaternion &qRotation) const;

    /// <summary>
    /// Converts rotation matrix to an angle and a spin axis.<br/>
    /// </summary>
    /// <remarks>
    /// Since axis components depends on inverse of sin(angle) it's necessary to take into account when angle is 0 or \f$ \pi\f$.<br/>
    /// When angle equals zero, the returned axis is a null vector.
    /// </remarks>
    /// <param name="fRotationAngle">[OUT] Angle of rotation.</param>
    /// <param name="vRotationAxis">[OUT] Unitary vector in the direction of the spin axis.</param>
    void GetRotation(float_z &fRotationAngle, Vector3 &vRotationAxis) const;

    /// <summary>
    /// Calculates the determinant of the matrix. Since this is a rotation matrix, which is
    /// a special orthogonal matrix, its determinant is 1.
    /// </summary>
    /// <returns>
    /// Floating point value which is the result of the determinant.
    /// </returns>
    float_z GetDeterminant() const;

private:

    // Preventing the operators from base class to be used.
    Matrix3x3 operator*(const float_z fScalar) const;
    Matrix3x3 operator*(const Matrix3x3 &matrix) const;
    Matrix3x4 operator*(const Matrix3x4& matrix) const;
    Matrix3x3 operator/(const float_z fScalar) const;
    Matrix3x3 operator+(const Matrix3x3 &matrix) const;
    Matrix3x3 operator-(const Matrix3x3 &matrix) const;
    Matrix3x3& operator*=(const Matrix3x3 &matrix);
    Matrix3x3& operator*=(const float_z fScalar);
    Matrix3x3& operator/=(const float_z fScalar);
    Matrix3x3& operator+=(const Matrix3x3 &matrix);
    Matrix3x3& operator-=(const Matrix3x3 &matrix);

    // Hidden method to prevent it could be used.
    void ResetToZero();

    /// <summary>
    /// Multiplies a 4x3 or 4x4 translation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="matrix">[IN] Translation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 or 4x4 transformation matrix.
    /// </returns>
    template <class MatrixT>
    Internals::TransformationMatrix<MatrixT> ProductOperatorImp(const Internals::TranslationMatrix<MatrixT> &matrix) const;

    /// <summary>
    /// Multiplies a 4x3 or 4x4 transformation matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="matrix">[IN] Transformation matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant 4x3 or 4x4 transformation matrix.
    /// </returns>
    template <class MatrixT>
    Internals::TransformationMatrix<MatrixT> ProductOperatorImp(const Internals::TransformationMatrix<MatrixT> &matrix) const;
};


// Preventing friend global operator to be called.
RotationMatrix3x3 operator*(const float_z fScalar, const RotationMatrix3x3 &matrix);

} // namespace z


#endif // __ROTATIONMATRIX3X3__
