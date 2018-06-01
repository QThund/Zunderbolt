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

#ifndef __SPACECONVERSIONMATRIX__
#define __SPACECONVERSIONMATRIX__

#include "ZMath/Matrix4x4.h"



namespace z
{

// Forward declarations
template<class MatrixT> class TranslationMatrix;
template<class MatrixT> class TransformationMatrix;
class RotationMatrix3x3;
class ScalingMatrix3x3;
class BaseVector3;
class BaseVector4;
class Vector3;
class Vector4;
class BaseQuaternion;
class Matrix4x3;
class SpaceConversionMatrix;

// Preventing friend global operator to be called.
SpaceConversionMatrix operator*(const float_z fScalar, const SpaceConversionMatrix &matrix);

/// <summary>
/// Class representing a matrix which symbolizes coordinate system transformations.
/// </summary>
/// <remarks>
/// It adds functionality to change to view, projection and world spaces.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS SpaceConversionMatrix : public Matrix4x4
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor. It's initialized to identity matrix.
    /// </summary>
    SpaceConversionMatrix();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="matrix">[IN] The space conversion matrix from which we want to create a copy in the resident space conversion matrix.</param>
    SpaceConversionMatrix(const SpaceConversionMatrix &matrix);

    /// <summary>
    /// Base type constructor.
    /// </summary>
    /// <remarks>
    /// If you use this constructor, be sure that you are constructing a transformation matrix,
    /// otherwise unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The 4x4 matrix in which we want the resident space conversion matrix to be based.</param>
    SpaceConversionMatrix(const BaseMatrix4x4 &matrix);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Assignation operator. Assigns the provided matrix to the resident matrix.
    /// </summary>
    /// <remarks>
    /// If you use this operator, be sure that you are assigning a space conversion matrix.
    /// Otherwise, unpredictable behavior could be happen.
    /// </remarks>
    /// <param name="matrix">[IN] The matrix to be assigned.</param>
    /// <returns>
    /// A reference to the modified matrix.
    /// </returns>
    SpaceConversionMatrix& operator=(const BaseMatrix4x4 &matrix);

    /// <summary>
    /// Multiplies a space conversion matrix by the resident matrix.
    /// </summary>
    /// <remarks>
    /// This product is not conmmutative.
    /// </remarks>
    /// <param name="matrix">[IN] Matrix to be multiplied by.</param>
    /// <returns>
    /// The resultant matrix.
    /// </returns>
    SpaceConversionMatrix operator*(const SpaceConversionMatrix &matrix) const;


    /// <summary>
    /// Product and assign operator. Current matrix stores the result of the multiplication.
    /// </summary>
    /// <param name="matrix">[IN] The matrix to be multiplied by.</param>
    /// <returns>
    /// The modified matrix.
    /// </returns>
    SpaceConversionMatrix& operator*=(const SpaceConversionMatrix &matrix);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const BaseVector3 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="vTranslation">[IN] Vector which contains the translation (position).</param>
    /// <param name="qRotation">[IN] Quaternion which contains the rotation (orientation).</param>
    /// <param name="vScale">[IN] Vector which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const BaseVector4 &vTranslation, const BaseQuaternion &qRotation, const BaseVector3 &vScale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const TranslationMatrix<Matrix4x3> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const TranslationMatrix<Matrix4x4> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale);

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    void SetWorldSpaceMatrix(const TransformationMatrix<Matrix4x4> &translation, const TransformationMatrix<Matrix4x4> &rotation,
                             const TransformationMatrix<Matrix4x4> &scale);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view. It must not equal the target vector.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at. It must not equal the poit of view vector.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction". If it is null, the result is undefined.</param>
    void SetViewSpaceMatrix(const Vector3 &vPointOfView, const Vector3 &vTarget, const Vector3 &vUpDirection);

    /// <summary>
    /// Sets the view space matrix, also called camera space matrix, defined by the point of view or camera position,
    /// the position of the object we are looking at and the direction we consider is "up direction".
    /// </summary>
    /// <param name="vPointOfView">[IN] Vector which defines the position of the camera or the point of view. It must not equal the target vector.</param>
    /// <param name="vTarget">[IN] Vector which defines the point where we are looking at. It must not equal the poit of view vector.</param>
    /// <param name="vUpDirection">[IN] Vector which defines the "up direction". If it is null, the result is undefined.</param>
    void SetViewSpaceMatrix(const Vector4 &vPointOfView, const Vector4 &vTarget, const Vector4 &vUpDirection);

    /// <summary>
    /// Sets the projection space matrix, which defines how perspective is applied to the scene.
    /// </summary>
    /// <param name="fNearClipPlane">[IN] Floating point value which defines the distance to the nearest clipping plane. It must not equal the far clip plane's distance.</param>
    /// <param name="fFarClipPlane">[IN] Floating point value which defines the distance to the farthest clipping plane. It must not equal the near clip plane's distance.</param>
    /// <param name="fAspectRatio">[IN] Floating point value which defines the frame width/height ratio. If it equals zero, the result is undefined.</param>
    /// <param name="fVerticalFOV">[IN] Floating point value which defines the vertical field of view. If it equals zero, the result is undefined.</param>
    void SetProjectionSpaceMatrix(const float_z fNearClipPlane, const float_z fFarClipPlane,
                                  const float_z fAspectRatio, const float_z fVerticalFOV);

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// </summary>
    /// <remarks>
    /// Remember that Zunderbolt works with left-hand convention by default.<br/>
    /// To do that, we treat the world space matrix as a transformation matrix,
    /// inverting both rotation (by trasposing it) and z translation component.
    /// </remarks>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    SpaceConversionMatrix SwitchHandConventionWorldSpaceMatrix() const;

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// </summary>
    /// <remarks>
    /// Remember that Zunderbolt works with left-hand convention by default.<br/>
    /// To do that, we invert the Z axis, and then the matrix is recalculated.
    /// </remarks>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    SpaceConversionMatrix SwitchHandConventionViewSpaceMatrix() const;

    /// <summary>
    /// Turns the hand convention into opposite rules, that is like if we change the sign of z axis.
    /// </summary>
    /// <remarks>
    /// Remember that Zunderbolt works with left-hand convention by default.<br/>
    /// To do that, we change the sign of elements \f$ a_{22}\f$ and \f$ a_{23}\f$.
    /// </remarks>
    /// <returns>
    /// The switched matrix.
    /// </returns>
    SpaceConversionMatrix SwitchHandConventionProjectionSpaceMatrix() const;

private:

    // Preventing the operators from base class to be used.
    Matrix4x4 operator*(const float_z fScalar) const;
    Matrix4x4 operator*(const BaseMatrix4x4 &matrix) const;
    BaseMatrix4x3 operator*(const BaseMatrix4x3 &matrix) const;
    Matrix4x4 operator/(const float_z fScalar) const;
    Matrix4x4 operator+(const BaseMatrix4x4 &matrix) const;
    Matrix4x4 operator-(const BaseMatrix4x4 &matrix) const;
    Matrix4x4& operator*=(const BaseMatrix4x4 &matrix);
    Matrix4x4& operator*=(const float_z fScalar);
    Matrix4x4& operator/=(const float_z fScalar);
    Matrix4x4& operator+=(const BaseMatrix4x4 &matrix);
    Matrix4x4& operator-=(const BaseMatrix4x4 &matrix);

    // Hidden method to prevent it could be used.
    void ResetToZero();

    /// <summary>
    /// Sets the world space matrix, which usually defines the size, orientation and position of an object in the world space.
    /// </summary>
    /// <typeparam name="MatrixT">Allowed types: Matrix4x3, Matrix4x4.</typeparam>
    /// <param name="translation">[IN] Matrix which contains the translation (position).</param>
    /// <param name="rotation">[IN] Matrix which contains the rotation (orientation).</param>
    /// <param name="scale">[IN] Matrix which contains the scale (size).</param>
    template <class MatrixT>
    void SetWorldSpaceMatrixImp(const TranslationMatrix<MatrixT> &translation, const RotationMatrix3x3 &rotation, const ScalingMatrix3x3 &scale);
};

} // namespace z


#endif // __SPACECONVERSIONMATRIX__
