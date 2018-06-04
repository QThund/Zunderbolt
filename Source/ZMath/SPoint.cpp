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

#include "ZMath/SPoint.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/SAngle.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"


namespace z
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void SPoint::Translate(const Vector2 &vTranslation, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] += vTranslation;
    }
}

void SPoint::Translate(const float_z fTranslationX, const float_z fTranslationY, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x += fTranslationX;
        arPoints[i].y += fTranslationY;
    }
}

void SPoint::Rotate(const float_z fRotationAngle, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] = arPoints[i].Transform(fRotationAngle);
    }
}

void SPoint::Scale(const Vector2 &vScale, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] *= vScale;
    }
}

void SPoint::Scale(const float_z fScaleX, const float_z fScaleY, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x *= fScaleX;
        arPoints[i].y *= fScaleY;
    }
}

void SPoint::Transform(const TransformationMatrix3x3 &transformation, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] = arPoints[i].Transform(transformation);
    }
}

void SPoint::Translate(const Vector3 &vTranslation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(vTranslation, arPoints[i]);
    }
}

void SPoint::Translate(const Vector3 &vTranslation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(vTranslation, arPoints[i]);
    }
}

void SPoint::Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
    }
}

void SPoint::Translate(const float_z fTranslationX, const float_z fTranslationY, const float_z fTranslationZ, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(fTranslationX, fTranslationY, fTranslationZ, arPoints[i]);
    }
}

void SPoint::Translate(const TranslationMatrix4x3 &translation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(translation, arPoints[i]);
    }
}

void SPoint::Translate(const TranslationMatrix4x4 &translation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(translation, arPoints[i]);
    }
}

void SPoint::Translate(const TranslationMatrix4x3 &translation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(translation, arPoints[i]);
    }
}

void SPoint::Translate(const TranslationMatrix4x4 &translation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Translate(translation, arPoints[i]);
    }
}

void SPoint::Rotate(const Quaternion &qRotation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Rotate(qRotation, arPoints[i]);
    }
}

void SPoint::Rotate(const Quaternion &qRotation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Rotate(qRotation, arPoints[i]);
    }
}

void SPoint::Rotate(const RotationMatrix3x3 &rotation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Rotate(rotation, arPoints[i]);
    }
}

void SPoint::Rotate(const RotationMatrix3x3 &rotation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Rotate(rotation, arPoints[i]);
    }
}

void SPoint::Scale(const Vector3 &vScale, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(vScale, arPoints[i]);
    }
}

void SPoint::Scale(const Vector3 &vScale, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(vScale, arPoints[i]);
    }
}

void SPoint::Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
    }
}

void SPoint::Scale(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);
    }
}

void SPoint::Scale(const ScalingMatrix3x3 &scale, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(scale, arPoints[i]);
    }
}

void SPoint::Scale(const ScalingMatrix3x3 &scale, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Scale(scale, arPoints[i]);
    }
}

void SPoint::Transform(const TransformationMatrix4x3 &transformation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(transformation, arPoints[i]);
    }
}

void SPoint::Transform(const TransformationMatrix4x4 &transformation, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(transformation, arPoints[i]);
    }
}

void SPoint::Transform(const TransformationMatrix4x3 &transformation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(transformation, arPoints[i]);
    }
}

void SPoint::Transform(const TransformationMatrix4x4 &transformation, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(transformation, arPoints[i]);
    }
}

void SPoint::Transform(const SpaceConversionMatrix &spaceConversion, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(spaceConversion, arPoints[i]);
    }
}

void SPoint::Transform(const SpaceConversionMatrix &spaceConversion, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        SPoint::Transform(spaceConversion, arPoints[i]);
    }
}

void SPoint::RotateWithPivot(const float_z fRotationAngle, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] = arPoints[i].Transform(fRotationAngle);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i].x *= fScaleX;
        arPoints[i].y *= fScaleY;

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const Vector2 &vScale, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] *= vScale;

        arPoints[i] += vPivot;
    }
}

void SPoint::TransformWithPivot(const TransformationMatrix3x3 &transformation, const Vector2 &vPivot, Vector2* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        arPoints[i] = arPoints[i].Transform(transformation);

        arPoints[i] += vPivot;
    }
}

void SPoint::RotateWithPivot(const Quaternion &qRotation, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Rotate(qRotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::RotateWithPivot(const Quaternion &qRotation, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Rotate(qRotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Rotate(rotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::RotateWithPivot(const RotationMatrix3x3 &rotation, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Rotate(rotation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const Vector3& vScale, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(vScale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const Vector3 &vScale, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(vScale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector3 &vPivot,
                                    Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const float_z fScaleX, const float_z fScaleY, const float_z fScaleZ, const Vector4 &vPivot,
                                    Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(fScaleX, fScaleY, fScaleZ, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector3 &vPivot, Vector3* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(scale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::ScaleWithPivot(const ScalingMatrix3x3 &scale, const Vector4 &vPivot, Vector4* arPoints, const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Scale(scale, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector3 &vPivot, Vector3* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Transform(transformation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::TransformWithPivot(const TransformationMatrix4x3 &transformation, const Vector4 &vPivot, Vector4* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x -= vPivot.x;
        arPoints[i].y -= vPivot.y;
        arPoints[i].z -= vPivot.z;

        SPoint::Transform(transformation, arPoints[i]);

        arPoints[i].x += vPivot.x;
        arPoints[i].y += vPivot.y;
        arPoints[i].z += vPivot.z;
    }
}

void SPoint::TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector3 &vPivot, Vector3* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i] -= vPivot;

        SPoint::Transform(transformation, arPoints[i]);

        arPoints[i] += vPivot;
    }
}

void SPoint::TransformWithPivot(const TransformationMatrix4x4 &transformation, const Vector4 &vPivot, Vector4* arPoints,
                                        const unsigned int uElements)
{
    // Checks that the point array is not null
    Z_ASSERT_ERROR( arPoints != null_z, "Input array must not be null" );

    for(unsigned int i = 0; i < uElements; ++i)
    {
        arPoints[i].x -= vPivot.x;
        arPoints[i].y -= vPivot.y;
        arPoints[i].z -= vPivot.z;

        SPoint::Transform(transformation, arPoints[i]);

        arPoints[i].x += vPivot.x;
        arPoints[i].y += vPivot.y;
        arPoints[i].z += vPivot.z;
    }
}

} // namespace z
