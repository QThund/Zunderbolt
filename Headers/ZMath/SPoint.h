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

#ifndef __SPOINT__
#define __SPOINT__

#include "ZMath/Vector3.h"
#include "ZMath/Quaternion.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix3x3.h"


namespace z
{

// Forward declarations
// ---------------------
class Vector2;
class Vector4;
class Vector2;
class Vector3;
class Vector4;
class Matrix4x3;
class Matrix4x4;


/// <summary>
/// Helper class that will be used to perform transformations related to arrays of points (2D, 3D or 4D).
/// </summary>
class Z_MATH_MODULE_SYMBOLS SPoint
{

    // CONSTRUCTORS
    // ---------------
private:

    SPoint() { }


    // METHODS
    // ---------------
public:

    /// 2D TRANSFORMATIONS

    /// <summary>
    /// Translates 2D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 2D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const Vector2 &vTranslation, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 2D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_z fTranslationX, const float_z fTranslationY, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 2D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const float_z fRotationAngle, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 2D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 2D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const Vector2 &vScale, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 2D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_z fScaleX, const float_z fScaleY, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 2D points using a transformation matrix.<br/>
    /// Transformation will be applied to all points in the array.
    /// </summary>
    /// <param name="transformation">[IN] Transformation matrix that will be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const TransformationMatrix3x3 &transformation, Vector2* arPoints, const unsigned int uElements);

    // 3D TRANSFORMATIONS

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const Vector3 &vTranslation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const Vector3 &vTranslation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fTranslationX">[IN] Scalar value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Scalar value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Scalar value that contains the translation to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const TranslationMatrix4x3 &translation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 3D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const TranslationMatrix4x4 &translation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x3 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const TranslationMatrix4x3 &translation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Translates 4D points.
    /// </summary>
    /// <remarks>
    /// Translation will be applied to all points in the array.
    /// </remarks>
    /// <param name="translation">[IN] 4x4 matrix that contains the translation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be translated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Translate(const TranslationMatrix4x4 &translation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 3D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const Quaternion &qRotation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 4D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const Quaternion &qRotation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 3D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const RotationMatrix3x3 &rotation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 4D points.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Rotate(const RotationMatrix3x3 &rotation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const Vector3 &vScale, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const Vector3 &vScale, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Floating point value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Floating point value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Floating point value that contains the scale to be applied on Z component.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale matrix that contains the scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const ScalingMatrix3x3 &scale, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale matrix that contains the Scale to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Scale(const ScalingMatrix3x3 &scale, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const TransformationMatrix4x3 &transformation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const TransformationMatrix4x4 &transformation, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x3 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const TransformationMatrix4x3 &transformation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const TransformationMatrix4x4 &transformation, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 3D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const SpaceConversionMatrix &spaceConversion, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 4D points.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void Transform(const SpaceConversionMatrix &spaceConversion, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="fRotationAngle">[IN] Floating point value that contains the angle that we will use to rotate the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the Y dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const Vector2 &vScale, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 2D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Transformation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 2D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const TransformationMatrix3x3 &transformation, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const Quaternion &qRotation, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const Quaternion &qRotation, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Rotates 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Rotation will be applied to all points in the array.
    /// </remarks>
    /// <param name="rotation">[IN] Rotation to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be rotated. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const Vector3& vScale, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="vScale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const Vector3 &vScale, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector3 &vPivot,
                                      Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="fScaleX">[IN] Scale to be applied to the points in the X dimension.</param>
    /// <param name="fScaleY">[IN] Scale to be applied to the points in the Y dimension.</param>
    /// <param name="fScaleZ">[IN] Scale to be applied to the points in the Z dimension.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector4 &vPivot,
                                      Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements);

    /// <summary>
    /// Scales 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// Scale will be applied to all points in the array.
    /// </remarks>
    /// <param name="scale">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be scaled. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements);

    /// <summary>
    /// Transforms 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector3 &vPivot, Vector3* arPoints,
                                          const unsigned int uElements);

    /// <summary>
    /// Transforms 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector4 &vPivot, Vector4* arPoints,
                                          const unsigned int uElements);

    /// <summary>
    /// Transforms 3D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 3D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector3 &vPivot, Vector3* arPoints,
                                          const unsigned int uElements);

    /// <summary>
    /// Transforms 4D points, using the provided pivot as the center of transformation.
    /// </summary>
    /// <remarks>
    /// The transformation will be applied to all points in the array.<br/>
    /// The W component of the pivot point doesn't affect the result.
    /// </remarks>
    /// <param name="transformation">[IN] Scale to be applied to the points.</param>
    /// <param name="vPivot">[IN] Point that acts as pivot.</param>
    /// <param name="arPoints">[IN/OUT] Array of 4D points that will be transformed. If it is null, the behavior is undefined.</param>
    /// <param name="uElements">[IN] Number of elements in the array.</param>
    static void TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector4 &vPivot, Vector4* arPoints,
                                          const unsigned int uElements);

private:

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vTranslation">[IN] 3D Vector type that contains the translation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class VectorT>
    static void Translate(const Vector3 &vTranslation, VectorT &vPoint)
    {
        vPoint.x += vTranslation.x;
        vPoint.y += vTranslation.y;
        vPoint.z += vTranslation.z;
    }

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="fTranslationX">[IN] Floating point value that contains the translation to be applied on X component.</param>
    /// <param name="fTranslationY">[IN] Floating point value that contains the translation to be applied on Y component.</param>
    /// <param name="fTranslationZ">[IN] Floating point value that contains the translation to be applied on Z component.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class VectorT>
    static void Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ, VectorT &vPoint)
    {
        vPoint.x += fTranslationX;
        vPoint.y += fTranslationY;
        vPoint.z += fTranslationZ;
    }

    /// <summary>
    /// Translates 3D or 4D points.
    /// </summary>
    /// <typeparam name="MatrixT">Allowed types: TranslationMatrix4x3, TranslationMatrix4x4.</typeparam>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="translation">[IN] 3x3 or 4x4 translation matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be translated.</param>
    template <class MatrixT, class VectorT>
    static void Translate(const MatrixT &translation, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(translation);
    }

    /// <summary>
    /// Rotates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="qRotation">[IN] Quaternion that contains the rotation to be done.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
    template <class VectorT>
    static void Rotate(const Quaternion &qRotation, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(qRotation);
    }

    /// <summary>
    /// Rotates 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="rotation">[IN] Rotation matrix that contains the rotation to be done.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be rotated.</param>
    template <class VectorT>
    static void Rotate(const RotationMatrix3x3 &rotation, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(rotation);
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="vScale">[IN] 3D Vector type that contains the scale to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorT>
    static void Scale(const Vector3 &vScale, VectorT &vPoint)
    {
        vPoint.x *= vScale.x;
        vPoint.y *= vScale.y;
        vPoint.z *= vScale.z;
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="fScaleX">[IN] Scalar value that contains the scale to be applied on X component.</param>
    /// <param name="fScaleY">[IN] Scalar value that contains the scale to be applied on Y component.</param>
    /// <param name="fScaleZ">[IN] Scalar value that contains the scale to be applied on Z component.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorT>
    static void Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, VectorT &vPoint)
    {
        vPoint.x *= fScaleX;
        vPoint.y *= fScaleY;
        vPoint.z *= fScaleZ;
    }

    /// <summary>
    /// Scales 3D or 4D points.
    /// </summary>
    /// <param name="scale">[IN] Scale matrix that contains the scale to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be scaled.</param>
    template <class VectorT>
    static void Scale(const ScalingMatrix3x3 &scale, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(scale);
    }

    /// <summary>
    /// Transforms 3D or 4D points.
    /// </summary>
    /// <typeparam name="MatrixT">Allowed types: TransformationMatrix4x3, TransformationMatrix4x4.</typeparam>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="transformation">[IN] 4x3 or 4x4 matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
    template <class MatrixT, class VectorT>
    static void Transform(const MatrixT &transformation, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(transformation);
    }

    /// <summary>
    /// Transforms 3D or 4D points.
    /// </summary>
    /// <typeparam name="VectorT">Allowed types: Vector3, Vector4.</typeparam>
    /// <param name="spaceConversion">[IN] Space conversion matrix that contains the transformation to be applied.</param>
    /// <param name="vPoint">[IN/OUT] 3D or 4D point that will be transformed.</param>
    template <class VectorT>
    static void Transform(const SpaceConversionMatrix &spaceConversion, VectorT &vPoint)
    {
        vPoint = vPoint.Transform(spaceConversion);
    }
};

} // namespace z


#endif // __SPOINT__
