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

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/SAngle.h"
#include "ZMath/Vector3.h"
#include "ZMath/Quaternion.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/Matrix4x3.h"
using namespace z::Internals;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES && Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z SMALLER_TOLERANCE = 1e-5f;
#else
    const float_z SMALLER_TOLERANCE = SFloat::Epsilon;
#endif


ZTEST_SUITE_BEGIN( RotationMatrix3x3_TestSuite )

/// <summary>
/// Checks if copy constructor copies every matrix element properly.
/// </summary>
ZTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // [Preparation]

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;

    const Matrix3x3 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    const RotationMatrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE);

    // [Execution]
    RotationMatrix3x3 matrixUT = MATRIX_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
ZTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // [Preparation]

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    RotationMatrix3x3 matrixUT(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that the expected matrix is obtained when using common angles.
/// </summary>
ZTEST_CASE ( Constructor4_ExpectedValueIsObtainedWhenUsingCommonAngles_Test )
{
    // [Preparation]
    const Matrix3x3 EXPECTED_VALUE((float_z)0.61237243569579447,  (float_z)0.70710678118654757,     (float_z)0.35355339059327373,
                                        (float_z)-0.5,                 (float_z)4.3297802811774670e-017, (float_z)0.86602540378443860,
                                        (float_z)0.61237243569579458,  (float_z)-0.70710678118654746,    (float_z)0.35355339059327384);

    // Reference values obtained from following DirectX SDK statement:
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationYawPitchRoll(&rotm, SAngle::_ThirdPi, SAngle::_QuarterPi, SAngle::_HalfPi);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_X = SAngle::_45;
        const float_z ROTATION_Y = SAngle::_60;
        const float_z ROTATION_Z = SAngle::_90;
    #else
        const float_z ROTATION_X = SAngle::_QuarterPi;
        const float_z ROTATION_Y = SAngle::_ThirdPi;
        const float_z ROTATION_Z = SAngle::_HalfPi;
    #endif

    // [Execution]
    RotationMatrix3x3 matrixUT(ROTATION_X, ROTATION_Y, ROTATION_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that a neutral rotation matrix (an identity matrix) is obtained when angles equal zero.
/// </summary>
ZTEST_CASE ( Constructor4_NeutralRotationIsObtainedWhenAnglesEqualZero_Test )
{
    // [Preparation]
    const Matrix3x3 NEUTRAL_ROTATION = RotationMatrix3x3::GetIdentity();

    const float_z ANGLES = SFloat::_0;

    // [Execution]
    RotationMatrix3x3 matrixUT(ANGLES, ANGLES, ANGLES);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], NEUTRAL_ROTATION.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], NEUTRAL_ROTATION.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], NEUTRAL_ROTATION.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], NEUTRAL_ROTATION.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], NEUTRAL_ROTATION.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], NEUTRAL_ROTATION.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], NEUTRAL_ROTATION.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], NEUTRAL_ROTATION.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], NEUTRAL_ROTATION.ij[2][2]);
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE ( Constructor4_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const RotationMatrix3x3 ROTATION_AROUND_X(ROTATION_ANGLE, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION_AROUND_Y(SFloat::_0, ROTATION_ANGLE, SFloat::_0);
    const RotationMatrix3x3 ROTATION_AROUND_Z(SFloat::_0, SFloat::_0, ROTATION_ANGLE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the expected matrix is obtained when using a common normalized axis and angle.
/// </summary>
ZTEST_CASE ( Constructor5_ExpectedValueIsObtainedWhenUsingCommonNormalizedAxisAndAngle_Test )
{
    // [Preparation]
    const Matrix3x3 EXPECTED_VALUE((float_z)0.72802772538750848,  (float_z)0.60878859791576267,   (float_z)-0.31520164040634452,
                                        (float_z)-0.52510482111191903, (float_z)0.79079055799039111,   (float_z)0.3145079017103789,
                                        (float_z)0.44072730561210988,  (float_z)-0.063456571298848269, (float_z)0.89539527899519555);

    // Reference values obtained from following DirectX SDK statement:
    // D3DXVECTOR3 vAxis(1, 2, 3);
    // D3DXVec3Normalize(&vAxis, &vAxis);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationAxis(&rotm, &vAxis, SAngle::_QuarterPi);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_45;
    #else
        const float_z ANGLE = SAngle::_QuarterPi;
    #endif

    const Vector3 AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    // [Execution]
    RotationMatrix3x3 matrixUT(ANGLE, AXIS);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that the elements of the matrix's diagonal equal the cosine of the rotation angle when a null vector is used as axis.
/// </summary>
ZTEST_CASE ( Constructor5_MatrixDiagonalElementsEqualCosineOfAngleWhenUsingNullVectorAsAxisAndNonZeroAngle_Test )
{
    // [Preparation]
    // Reference values obtained from following DirectX SDK statement:
    // D3DXVECTOR3 vAxis(0, 0, 0);
    // D3DXVec3Normalize(&vAxis, &vAxis);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationAxis(&rotm, &vAxis, SAngle::_ThirdPi);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_60;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 AXIS = Vector3(SFloat::_0, SFloat::_0, SFloat::_0);

    const float_z COS_ANGLE = cos_z(SAngle::_ThirdPi);

    const Matrix3x3 EXPECTED_VALUE(COS_ANGLE,   SFloat::_0, SFloat::_0,
                                        SFloat::_0, COS_ANGLE,   SFloat::_0,
                                        SFloat::_0, SFloat::_0, COS_ANGLE);

    // [Execution]
    RotationMatrix3x3 matrixUT(ANGLE, AXIS);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that a neutral rotation matrix (an Identity matrix) is obtained when the angle equals zero and the axis is a normalized common vector.
/// </summary>
ZTEST_CASE ( Constructor5_NeutralRotationIsObtainedWhenUsingNormalizedCommonVectorAndAngleEqualsZero_Test )
{
    // [Preparation]
    // Reference values obtained from following DirectX SDK statement:
    // D3DXVECTOR3 vAxis(1, 2, 3);
    // D3DXVec3Normalize(&vAxis, &vAxis);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationAxis(&rotm, &vAxis, 0);
    const float_z ANGLE = SFloat::_0;
    const Vector3 AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const RotationMatrix3x3 EXPECTED_VALUE = RotationMatrix3x3::GetIdentity();

    // [Execution]
    RotationMatrix3x3 matrixUT(ANGLE, AXIS);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that a neutral rotation matrix (an Identity matrix) is obtained when the angle equals zero and the axis is a null vector.
/// </summary>
ZTEST_CASE ( Constructor5_NeutralRotationIsObtainedWhenUsingNullVectorAndAngleEqualsZero_Test )
{
    // [Preparation]
    // Reference values obtained from following DirectX SDK statement:
    // D3DXVECTOR3 vAxis(0, 0, 0);
    // D3DXVec3Normalize(&vAxis, &vAxis);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationAxis(&rotm, &vAxis, 0);
    const float_z ANGLE = SFloat::_0;
    const Vector3 AXIS = Vector3::GetNullVector();
    const RotationMatrix3x3 EXPECTED_VALUE = RotationMatrix3x3::GetIdentity();

    // [Execution]
    RotationMatrix3x3 matrixUT(ANGLE, AXIS);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that the obtained value is different when the input axis vector is normalized or not.
/// </summary>
ZTEST_CASE ( Constructor5_ObtainedValueIsDifferentWhenAxisIsNormalizedOrNot_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_45;
    #else
        const float_z ANGLE = SAngle::_QuarterPi;
    #endif

    const Vector3 NORMALIZED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Vector3 NONNORMALIZED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    // [Execution]
    RotationMatrix3x3 matrixWhenAxisIsNormalizedUT(ANGLE, NORMALIZED_AXIS);
    RotationMatrix3x3 matrixWhenAxisIsNotNormalizedUT(ANGLE, NONNORMALIZED_AXIS);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[0][0], matrixWhenAxisIsNotNormalizedUT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[0][1], matrixWhenAxisIsNotNormalizedUT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[0][2], matrixWhenAxisIsNotNormalizedUT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[1][0], matrixWhenAxisIsNotNormalizedUT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[1][1], matrixWhenAxisIsNotNormalizedUT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[1][2], matrixWhenAxisIsNotNormalizedUT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[2][0], matrixWhenAxisIsNotNormalizedUT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[2][1], matrixWhenAxisIsNotNormalizedUT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreNotEqual(matrixWhenAxisIsNormalizedUT.ij[2][2], matrixWhenAxisIsNotNormalizedUT.ij[2][2]) );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE ( Constructor5_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const Vector3 AXIS = Vector3::GetUnitVectorX();
    const RotationMatrix3x3 ROTATION(ROTATION_ANGLE, AXIS);

    const Vector3 POSITION_BEFORE_ROTATION(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION(SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    Vector3 vPointUT = POSITION_BEFORE_ROTATION.Transform(ROTATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPointUT.x, EXPECTED_POSITION_AFTER_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vPointUT.y, EXPECTED_POSITION_AFTER_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vPointUT.z, EXPECTED_POSITION_AFTER_ROTATION.z) );
}

/// <summary>
/// Checks that the expected matrix is obtained when using a common normalized quaternion.
/// </summary>
ZTEST_CASE ( Constructor6_ExpectedValueIsObtainedWhenUsingCommonNormalizedQuaternion_Test )
{
    // [Preparation]
    const Matrix3x3 EXPECTED_VALUE((float_z)0.13333333333333353,  (float_z)0.93333333333333324, (float_z)-0.33333333333333326,
                                        (float_z)-0.66666666666666663, (float_z)0.33333333333333348, (float_z)0.66666666666666652,
                                        (float_z)0.73333333333333317,  (float_z)0.13333333333333336, (float_z)0.66666666666666674);

    // Reference values obtained from following DirectX SDK statement:
    // D3DXQUATERNION Q1(1, 2, 3, 4);
    // D3DXQuaternionNormalize(&Q1, &Q1);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationQuaternion(&rotm, &Q1);

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

    // [Execution]
    RotationMatrix3x3 matrixUT(QUATERNION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that the obtained value is a neutral rotation (an Identity matrix) when the input is a null quaternion.
/// </summary>
ZTEST_CASE ( Constructor6_NeutralRotationIsObtainedWhenQuaternionIsNull_Test )
{
    // [Preparation]
    const RotationMatrix3x3 EXPECTED_VALUE = RotationMatrix3x3::GetIdentity();

    // Reference values obtained from following DirectX SDK statement:
    // D3DXQUATERNION Q1(0, 0, 0, 0);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationQuaternion(&rotm, &Q1);

    const Quaternion QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    // [Execution]
    RotationMatrix3x3 matrixUT(QUATERNION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that the obtained value is a neutral rotation (an Identity matrix) when the input is an identity quaternion.
/// </summary>
ZTEST_CASE ( Constructor6_NeutralRotationIsObtainedWhenQuaternionIsIdentity_Test )
{
    // [Preparation]
    const RotationMatrix3x3 EXPECTED_VALUE = RotationMatrix3x3::GetIdentity();

    // Reference values obtained from following DirectX SDK statements:
    // D3DXQUATERNION Q1(0, 0, 0, 1);
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationQuaternion(&rotm, &Q1);

    const Quaternion QUATERNION = Quaternion::GetIdentity();

    // [Execution]
    RotationMatrix3x3 matrixUT(QUATERNION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
ZTEST_CASE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DIAGONAL = SFloat::_1;

	// [Execution]
    RotationMatrix3x3 matrixUT = RotationMatrix3x3::GetIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE_X1 = SFloat::_1;
    const float_z ANGLE_Y1 = SFloat::_2;
    const float_z ANGLE_Z1 = SFloat::_3;
    const float_z ANGLE_X2 = SFloat::_4;
    const float_z ANGLE_Y2 = SFloat::_5;
    const float_z ANGLE_Z2 = SFloat::_6;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE_X1 = SAngle::RadiansToDegrees(SFloat::_1);
    const float_z ANGLE_Y1 = SAngle::RadiansToDegrees(SFloat::_2);
    const float_z ANGLE_Z1 = SAngle::RadiansToDegrees(SFloat::_3);
    const float_z ANGLE_X2 = SAngle::RadiansToDegrees(SFloat::_4);
    const float_z ANGLE_Y2 = SAngle::RadiansToDegrees(SFloat::_5);
    const float_z ANGLE_Z2 = SAngle::RadiansToDegrees(SFloat::_6);
#endif

    const RotationMatrix3x3 OPERAND1(ANGLE_X1, ANGLE_Y1, ANGLE_Z1);
    const RotationMatrix3x3 OPERAND2(ANGLE_X2, ANGLE_Y2, ANGLE_Z2);

    // Reference values obtained from following DirectX SDK statements:
    // D3DXMATRIX rotm1;
    // D3DXMatrixRotationYawPitchRoll(&rotm1, 2, 1, 3);
    // D3DXMATRIX rotm2;
    // D3DXMatrixRotationYawPitchRoll(&rotm2, 5, 4, 6);
    // D3DXMATRIX rotm = rotm1 * rotm2;
    const float_z EXPECTED_VALUE_FOR_00 = (float_z)0.62862116970450643;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)0.69098397942738221;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)0.35689853624529905;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)-0.16601991351523826;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)0.56755877119703968;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)-0.80642075218442832;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)-0.75978471511062295;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)0.44768089239100362;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)0.47149655913088467;

    // [Execution]
    RotationMatrix3x3 matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const RotationMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    RotationMatrix3x3 matrix1UT = OPERAND1 * OPERAND2;
    RotationMatrix3x3 matrix2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_1;
        const float_z ANGLE_Y = SFloat::_2;
        const float_z ANGLE_Z = SFloat::_3;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_3);
    #endif

    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const Matrix4x4 EXPECTED_VALUE((float_z)2.0798394123794113,  (float_z)0.38123732879438366, (float_z)5.1046851719628510,  SFloat::_0,
                                    (float_z)-2.7950541643506361, (float_z)-2.6744761435268858, (float_z)2.8499469971167666,  SFloat::_0,
                                    (float_z)1.9651819857355277,  (float_z)-4.2073549240394827, (float_z)-1.3490705721969174, SFloat::_0,
                                    SFloat::_0,                  SFloat::_0,                  SFloat::_0,                  SFloat::_1);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = ROTATION * SCALE;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_1;
        const float_z ANGLE_Y = SFloat::_2;
        const float_z ANGLE_Z = SFloat::_3;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_3);
    #endif

    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_4, SFloat::_5, SFloat::_6);

    const Matrix4x4 EXPECTED_VALUE((float_z)0.51995985309485282,  (float_z)0.076247465758876726, (float_z)0.85078086199380853,  SFloat::_0,
                                    (float_z)-0.69876354108765903, (float_z)-0.53489522870537720, (float_z)0.47499116618612774,  SFloat::_0,
                                    (float_z)0.49129549643388193,  (float_z)-0.84147098480789650, (float_z)-0.22484509536615291, SFloat::_0,
                                    SFloat::_4,                   SFloat::_5,                   SFloat::_6,                   SFloat::_1);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = ROTATION * TRANSLATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct4_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_1;
        const float_z ANGLE_Y = SFloat::_2;
        const float_z ANGLE_Z = SFloat::_3;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_3);
    #endif

    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_4, SFloat::_5, SFloat::_6);

    const Matrix4x3 EXPECTED_VALUE((float_z)0.51995985309485282,  (float_z)0.076247465758876726, (float_z)0.85078086199380853,
                                    (float_z)-0.69876354108765903, (float_z)-0.53489522870537720, (float_z)0.47499116618612774,
                                    (float_z)0.49129549643388193,  (float_z)-0.84147098480789650, (float_z)-0.22484509536615291,
                                    SFloat::_4,                   SFloat::_5,                   SFloat::_6);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrixUT = ROTATION * TRANSLATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct5_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_1;
        const float_z ANGLE_Y = SFloat::_2;
        const float_z ANGLE_Z = SFloat::_3;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_3);
    #endif

    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION(Matrix4x4(SFloat::_4,    SFloat::_5,    SFloat::_6,    SFloat::_7,
                                                                      SFloat::_8,    SFloat::_9,    SFloat::_10,   (float_z)11.0,
                                                                      (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                                                      (float_z)16.0, (float_z)17.0, (float_z)18.0, (float_z)19.0));

    const Matrix4x4 EXPECTED_VALUE((float_z)12.899189482376126,  (float_z)14.346177663223664,  (float_z)15.793165844071204,  SFloat::_0,
                                    (float_z)-1.374321999760121,  (float_z)-2.1329896033670286, (float_z)-2.891657206973937,  SFloat::_0,
                                    (float_z)-7.4647270371214791, (float_z)-8.0397476208616467, (float_z)-8.6147682046018144, SFloat::_0,
                                    (float_z)16.0,                (float_z)17.0,                (float_z)18.0,                SFloat::_1);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = ROTATION * TRANSFORMATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct6_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_1;
        const float_z ANGLE_Y = SFloat::_2;
        const float_z ANGLE_Z = SFloat::_3;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_3);
    #endif

    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION(Matrix4x3(SFloat::_4,    SFloat::_5,    SFloat::_6,
                                                                      SFloat::_8,    SFloat::_9,    SFloat::_10,
                                                                      (float_z)12.0, (float_z)13.0, (float_z)14.0,
                                                                      (float_z)16.0, (float_z)17.0, (float_z)18.0));

    const Matrix4x3 EXPECTED_VALUE((float_z)12.899189482376126,  (float_z)14.346177663223664,  (float_z)15.793165844071204,
                                    (float_z)-1.374321999760121,  (float_z)-2.1329896033670286, (float_z)-2.8916572069739370,
                                    (float_z)-7.4647270371214791, (float_z)-8.0397476208616467, (float_z)-8.6147682046018144,
                                    (float_z)16.0,                (float_z)17.0,                (float_z)18.0);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrixUT = ROTATION * TRANSFORMATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Checks that every matrix element is assigned to the right destination matrix element.
/// </summary>
ZTEST_CASE ( OperatorAssignation_EveryElementAssignedToCorrespondingElement_Test )
{
    // [Preparation]

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    RotationMatrix3x3 matrixUT;
    matrixUT = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied and assigned.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_CommonMatricesAreCorrectlyMultipliedAndAssigned_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X1 = SFloat::_1;
        const float_z ANGLE_Y1 = SFloat::_2;
        const float_z ANGLE_Z1 = SFloat::_3;
        const float_z ANGLE_X2 = SFloat::_4;
        const float_z ANGLE_Y2 = SFloat::_5;
        const float_z ANGLE_Z2 = SFloat::_6;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X1 = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z ANGLE_Y1 = SAngle::RadiansToDegrees(SFloat::_2);
        const float_z ANGLE_Z1 = SAngle::RadiansToDegrees(SFloat::_3);
        const float_z ANGLE_X2 = SAngle::RadiansToDegrees(SFloat::_4);
        const float_z ANGLE_Y2 = SAngle::RadiansToDegrees(SFloat::_5);
        const float_z ANGLE_Z2 = SAngle::RadiansToDegrees(SFloat::_6);
    #endif

    const RotationMatrix3x3 OPERAND1(ANGLE_X1, ANGLE_Y1, ANGLE_Z1);
    const RotationMatrix3x3 OPERAND2(ANGLE_X2, ANGLE_Y2, ANGLE_Z2);

    // Reference values obtained from following DirectX SDK statements:
    // D3DXMATRIX rotm1;
    // D3DXMatrixRotationYawPitchRoll(&rotm1, 2, 1, 3);
    // D3DXMATRIX rotm2;
    // D3DXMatrixRotationYawPitchRoll(&rotm2, 5, 4, 6);
    // D3DXMATRIX rotm = rotm1 * rotm2;
    const float_z EXPECTED_VALUE_FOR_00 = (float_z)0.62862116970450643;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)0.69098397942738221;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)0.35689853624529905;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)-0.16601991351523826;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)0.56755877119703968;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)-0.80642075218442832;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)-0.75978471511062295;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)0.44768089239100362;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)0.47149655913088467;

    // [Execution]
    RotationMatrix3x3 matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const RotationMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    RotationMatrix3x3 matrix1UT = OPERAND1;
    matrix1UT *= OPERAND2;
    RotationMatrix3x3 matrix2UT = OPERAND2;
    matrix2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const RotationMatrix3x3 OPERAND(SFloat::_1, SFloat::_2, SFloat::_3);

    RotationMatrix3x3 EXPECTED_VALUE = OPERAND;
    EXPECTED_VALUE *= OPERAND;

	// [Execution]
    RotationMatrix3x3 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // [Verification]
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the matrix is correctly inverted.
/// </summary>
ZTEST_CASE ( Invert_MatrixIsCorrectlyInverted_Test )
{
    // [Preparation]

    const RotationMatrix3x3 ORIGINAL_VALUE(Matrix3x3(SFloat::_1, SFloat::_2, SFloat::_3,
                                                           SFloat::_4, SFloat::_5, SFloat::_6,
                                                           SFloat::_7, SFloat::_8, SFloat::_9));

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_4, SFloat::_7,
                                        SFloat::_2, SFloat::_5, SFloat::_8,
                                        SFloat::_3, SFloat::_6, SFloat::_9);

    // [Execution]
    RotationMatrix3x3 matrixUT = ORIGINAL_VALUE.Invert();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that obtained angles equal expected values.
/// </summary>
ZTEST_CASE ( GetRotation1_AnglesAreCorrectlyExtracted_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_45;
        const float_z EXPECTED_ROTATION_Y = SAngle::_60;
        const float_z EXPECTED_ROTATION_Z = SAngle::_90;
    #else
        const float_z EXPECTED_ROTATION_X = SAngle::_QuarterPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_ThirdPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_HalfPi;
    #endif

    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.61237243569579447, (float_z)0.70710678118654757,     (float_z)0.35355339059327373,
                                                     (float_z)-0.5,                (float_z)4.3297802811774670e-017, (float_z)0.86602540378443860,
                                                     (float_z)0.61237243569579458, (float_z)-0.70710678118654746,    (float_z)0.35355339059327384));

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;
    
    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);
    
    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationXUT, EXPECTED_ROTATION_X, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SFloat::AreEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained angles don't equal expected values due to gimbal lock limitation.
/// </summary>
ZTEST_CASE ( GetRotation1_AnglesAreNotWhatExpectedWhenGimbalLockOccurs_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_90;
        const float_z EXPECTED_ROTATION_Y = SAngle::_90;
        const float_z EXPECTED_ROTATION_Z = SAngle::_60;
    #else
        const float_z EXPECTED_ROTATION_X = SAngle::_HalfPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_HalfPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_ThirdPi;
    #endif

    // By rotating 90º (or PI/2) two gimbals, they become alligned so rotating any of them results in the same transformation
    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.86602545,      (float_z)-3.7855173e-008, (float_z)-0.5,
                                                     (float_z)0.5,             (float_z)-2.1855692e-008, (float_z)0.86602545,
                                                     (float_z)-4.3711388e-008, (float_z)-1.0,            (float_z)1.9106855e-015));

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fRotationXUT, EXPECTED_ROTATION_X) ||
                 SFloat::AreNotEqual(fRotationYUT, EXPECTED_ROTATION_Y) ||
                 SFloat::AreNotEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that the obtained quaternion matches what expected.
/// </summary>
ZTEST_CASE ( GetRotation2_MatrixIsCorrectlyConvertedInQuaternion_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_X = SAngle::_45;
        const float_z ROTATION_Y = SAngle::_60;
        const float_z ROTATION_Z = SAngle::_90;
    #else
        const float_z ROTATION_X = SAngle::_QuarterPi;
        const float_z ROTATION_Y = SAngle::_ThirdPi;
        const float_z ROTATION_Z = SAngle::_HalfPi;
    #endif

    const Quaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.61237243569579447, (float_z)0.70710678118654757,     (float_z)0.35355339059327373,
                                                     (float_z)-0.5,                (float_z)4.3297802811774670e-017, (float_z)0.86602540378443860,
                                                     (float_z)0.61237243569579458, (float_z)-0.70710678118654746,    (float_z)0.35355339059327384));

    // [Execution]
    Quaternion qResultUT;
    ROTATION.GetRotation(qResultUT);

    // [Verification]
    BOOST_CHECK( qResultUT == EXPECTED_VALUE );
}

/// <summary>
/// Checks that the obtained axis and angle match what expected.
/// </summary>
ZTEST_CASE ( GetRotation3_MatrixIsCorrectlyConvertedInAxisAndAngle_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.53571428571428581,  (float_z)0.76579364625798496,   (float_z)-0.35576719274341861,
                                                     (float_z)-0.62293650340084217, (float_z)0.64285714285714302,   (float_z)0.4457407392288521,
                                                     (float_z)0.5700529070291328,   (float_z)-0.017169310657423609, (float_z)0.8214285714285714));

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the rotation axis obtained is the inverse of which results from the opposite rotation.
/// </summary>
ZTEST_CASE ( GetRotation3_ResultantAxisIsTheOppositeWhenRotationIsTheOpposite_Test )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.53571427,  (float_z)0.76579368,   (float_z)-0.35576719,
                                                     (float_z)-0.62293649, (float_z)0.64285713,   (float_z)0.44574076,
                                                     (float_z)0.57005292,  (float_z)-0.017169312, (float_z)0.82142854));
    const RotationMatrix3x3 OPPOSITE_ROTATION = ROTATION.Invert();

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    Vector3 vAxisFromOppositeRotationUT;
    float_z fAngleFromOppositeRotationUT = SFloat::_0;
    OPPOSITE_ROTATION.GetRotation(fAngleFromOppositeRotationUT, vAxisFromOppositeRotationUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == -vAxisFromOppositeRotationUT );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, fAngleFromOppositeRotationUT) );
}

/// <summary>
/// Checks that the obtained axis and angle are calculated correctly when rotation angle equals Pi (or 180º).
/// </summary>
ZTEST_CASE ( GetRotation3_AxisAndAngleAreCalculatedNormallyWhenRotationAngleEqualsPiRadiansOr180Degrees_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_180;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ANGLE = (float_z)3.1415926386886319;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    
    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)-0.8571428571428571, (float_z)0.28571428571428586,  (float_z)0.42857142857142855,
                                                     (float_z)0.28571428571428564, (float_z)-0.42857142857142849, (float_z)0.85714285714285721,
                                                     (float_z)0.42857142857142866, (float_z)0.85714285714285721,  (float_z)0.28571428571428581));

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the obtained axis is a null vector when the rotation angle is zero.
/// </summary>
ZTEST_CASE ( GetRotation3_NullVectorIsReturnedWhenRotationAngleEqualsZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_ANGLE = SFloat::_0;
    const Vector3 EXPECTED_AXIS = Vector3::GetNullVector();

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity(); // Identity is obtained when using zero as angle, it has nothing to do with the value of the axis

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the obtained axis is normalized.
/// </summary>
ZTEST_CASE ( GetRotation3_ResultantAxisIsNormalized_Test )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.53571428571428581,  (float_z)0.76579364625798496,   (float_z)-0.35576719274341861,
                                                     (float_z)-0.62293650340084217, (float_z)0.64285714285714302,   (float_z)0.4457407392288521,
                                                     (float_z)0.5700529070291328,   (float_z)-0.017169310657423609, (float_z)0.8214285714285714));

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleAux = SFloat::_0;
    Vector3 vNormalizedAxisUT;
    ROTATION.GetRotation(fAngleAux, vAxisUT);

    vNormalizedAxisUT = vAxisUT.Normalize();

    // [Verification]
    BOOST_CHECK( vAxisUT == vNormalizedAxisUT );
}

/// <summary>
/// Checks that always returns 1.
/// </summary>
ZTEST_CASE ( GetDeterminant_AlwaysReturnsOne_Test )
{
    // [Preparation]

    const RotationMatrix3x3 ROTATION(Matrix3x3(SFloat::_1, SFloat::_2, SFloat::_3,
                                                     SFloat::_4, SFloat::_5, SFloat::_6,
                                                     SFloat::_7, SFloat::_8, SFloat::_9));
    const float_z EXPECTED_VALUE = SFloat::_1;

    // [Execution]
    float_z fResultUT = ROTATION.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

// End - Test Suite: RotationMatrix3x3
ZTEST_SUITE_END()
