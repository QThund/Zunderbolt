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

#include "ZMath/Quaternion.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES && Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z SMALLER_TOLERANCE = 1e-5f;
#else
    const float_z SMALLER_TOLERANCE = SFloat::Epsilon;
#endif

ZTEST_SUITE_BEGIN( Quaternion_TestSuite )

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)1.5;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_3);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Quaternion qQuaternionUT = SCALAR * QUATERNION;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Quaternion qQuaternionUT;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if copy constructor sets quaternion components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Quaternion QUAT_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);

	// [Execution]
    Quaternion qQuatUT = QUAT_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuatUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuatUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuatUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuatUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the components of the quaternion are correctly copied to other quaternion.
/// </summary>
ZTEST_CASE ( Constructor3_QuaternionIsCorrectlyCopied_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_X = SFloat::_1;
    const float_z EXPECTED_VALUE_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_W = SFloat::_4;
    const BaseQuaternion QUATERNION(EXPECTED_VALUE_X, EXPECTED_VALUE_Y, EXPECTED_VALUE_Z, EXPECTED_VALUE_W);

	// [Execution]
    Quaternion qQuaternionUT(QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that the quaternion is correctly built when using arbitrary Euler angles.
/// </summary>
ZTEST_CASE ( Constructor4_QuaternionIsCorrectlyFormedWhenUsingArbitraryEulerAngles_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const float_z EXPECTED_VALUE_X = (float_z)0.56098552679693092;
    const float_z EXPECTED_VALUE_Y = (float_z)0.092295955641257227;
    const float_z EXPECTED_VALUE_Z = (float_z)0.43045933457687946;
    const float_z EXPECTED_VALUE_W = (float_z)0.70105738464997791;

    // Expected results calculated using DirectX SDK
    // D3DXQUATERNION q3;
    // float_z fYaw = D3DXToRadian(60);
    // float_z fPitch = D3DXToRadian(45);
    // float_z fRoll = D3DXToRadian(90);
    // D3DXQuaternionRotationYawPitchRoll(&q3, fYaw, fPitch, fRoll);

	// [Execution]
    Quaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_W) );
}

/// <summary>
/// Checks that the quaternion is correctly built when using arbitrary Euler angles.
/// </summary>
ZTEST_CASE ( Constructor4_ResultIsNormalizedWhenUsingNonZeroAngles_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const Quaternion NORMALIZED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z).Normalize();

	// [Execution]
    Quaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the identity quaternion is obtained when all the angles equal zero.
/// </summary>
ZTEST_CASE ( Constructor4_IdentityIsObtainedWhenAllAnglesEqualZero_Test )
{
    // [Preparation]
    const float_z ALL_ANGLES_VALUE = SFloat::_0;

    const Quaternion EXPECTED_VALUE = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT(ALL_ANGLES_VALUE, ALL_ANGLES_VALUE, ALL_ANGLES_VALUE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that the quaternion is built by following the Yaw-Pitch-Roll rotation order.
/// </summary>
ZTEST_CASE ( Constructor4_FollowsYawPitchRollRotationOrder_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const Quaternion PITCH = Quaternion(EULER_ANGLE_X, SFloat::_0, SFloat::_0);
    const Quaternion YAW   = Quaternion(SFloat::_0, EULER_ANGLE_Y, SFloat::_0);
    const Quaternion ROLL  = Quaternion(SFloat::_0, SFloat::_0, EULER_ANGLE_Z);

    const Quaternion EXPECTED_VALUE = ROLL * PITCH * YAW;

    // Expected results calculated using DirectX SDK
    // D3DXQUATERNION q3, yaw, pitch, roll;
    // float_z fYaw = D3DXToRadian(60);
    // float_z fPitch = D3DXToRadian(45);
    // float_z fRoll = D3DXToRadian(90);
    // D3DXQuaternionRotationYawPitchRoll(&yaw, fYaw, 0, 0);
    // D3DXQuaternionRotationYawPitchRoll(&pitch, 0, fPitch, 0);
    // D3DXQuaternionRotationYawPitchRoll(&roll, 0, 0, fRoll);
    // q3 = roll * pitch * yaw;

	// [Execution]
    Quaternion qQuaternionUT(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor5_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_X = SFloat::_1;
    const float_z EXPECTED_VALUE_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_W = SFloat::_4;

	// [Execution]
    Quaternion qQuaternionUT(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that every element of the array is put in the correct component.
/// </summary>
ZTEST_CASE ( Constructor6_QuaternionComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    float_z* VALID_ARRAY_OF_4_FLOATS = new float_z[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_Z;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_W;

	// [Execution]
    Quaternion qQuaternionUT(VALID_ARRAY_OF_4_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, VALID_ARRAY_OF_4_FLOATS[0]);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, VALID_ARRAY_OF_4_FLOATS[1]);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, VALID_ARRAY_OF_4_FLOATS[2]);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, VALID_ARRAY_OF_4_FLOATS[3]);

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_z* NULL_ARRAY = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Quaternion qQuaternionUT(NULL_ARRAY);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if quaternion components are set to the correct values packed in a valid vf32 object.
/// </summary>
ZTEST_CASE ( Constructor7_QuaternionComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

	vf32_z PACK;
	SVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W, PACK);

	// [Execution]
	Quaternion qQuaternionUT(PACK);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly formed when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
ZTEST_CASE ( Constructor8_QuaternionCorrectlyFormedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_4).Normalize();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const float_z EXPECTED_VALUE_FOR_X = (float_z)0.083508371238977974;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.16701674247795595;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)0.3340334849559119;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)0.92387953251128674;

    // Expected results calculated using DirectX SDK:
    // D3DXVECTOR3 axis(1, 2, 4);
    // D3DXVec3Normalize(&axis, &axis);
    // float_z fAngle = SAngle::_QuarterPi;
    // D3DXQuaternionRotationAxis(&q3, &axis, fAngle);

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}


/// <summary>
/// Checks that the resultant quaternion is normalized when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
ZTEST_CASE ( Constructor8_QuaternionIsNormalizedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_4).Normalize();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion NORMALIZED_RESULT = Quaternion(AXIS, ANGLE).Normalize();

    // [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using a null vector as axis.
/// </summary>
ZTEST_CASE ( Constructor8_NoRotationStoredInQuaternionWhenUsingNullVectorAsAxis_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3::GetNullVector();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const float_z EXPECTED_VALUE_FOR_VECTOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Z = SFloat::_3;

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    // Verifies that the vector doesn't rotate
    Vector3 vVectorForVerification(SFloat::_1, SFloat::_2, SFloat::_3);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using zero as angle.
/// </summary>
ZTEST_CASE ( Constructor8_NoRotationStoredInQuaternionWhenUsingZeroAsAngle_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const float_z ANGLE = SFloat::_0;

    const float_z EXPECTED_VALUE_FOR_VECTOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Z = SFloat::_3;

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    // Verifies that the vector doesn't rotate
    Vector3 vVectorForVerification(SFloat::_1, SFloat::_2, SFloat::_3);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
}

/// <summary>
/// Checks that the resultant quaternion is not normalized when using a null vector as axis.
/// </summary>
ZTEST_CASE ( Constructor8_ResultIsNotNormalizedWhenUsingNullVectorAsAxis_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3::GetNullVector();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion NORMALIZED_RESULT = Quaternion(AXIS, ANGLE).Normalize();

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is not correct when a not normalized vector is used as axis.
/// </summary>
ZTEST_CASE ( Constructor8_ResultIsIncorrectWhenUsingNotNormalizedAxis_Test )
{
    // [Preparation]
    const Vector3 AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_4);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion CORRECT_QUATERNION(AXIS.Normalize(), ANGLE);

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT != CORRECT_QUATERNION );
}

/// <summary>
/// Checks that the quaternion is correctly formed when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
ZTEST_CASE ( Constructor9_QuaternionCorrectlyFormedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0).Normalize();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const float_z EXPECTED_VALUE_FOR_X = (float_z)0.083508371238977974;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.16701674247795595;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)0.3340334849559119;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)0.92387953251128674;

    // Expected results calculated using DirectX SDK:
    // D3DXVECTOR3 axis(1, 2, 4);
    // D3DXVec3Normalize(&axis, &axis);
    // float_z fAngle = SAngle::_QuarterPi;
    // D3DXQuaternionRotationAxis(&q3, &axis, fAngle);

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the resultant quaternion is normalized when using a normalized vector and an arbitrary angle that doesn't equal zero.
/// </summary>
ZTEST_CASE ( Constructor9_QuaternionIsNormalizedWhenUsingNormalizedVectorAndNonZeroAngle_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0).Normalize();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion NORMALIZED_RESULT = Quaternion(AXIS, ANGLE).Normalize();

    // [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using a null vector as axis.
/// </summary>
ZTEST_CASE ( Constructor9_NoRotationStoredInQuaternionWhenUsingNullVectorAsAxis_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4::GetNullVector();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const float_z EXPECTED_VALUE_FOR_VECTOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_VECTOR_W = SFloat::_4;

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    // Verifies that the vector doesn't rotate
    Vector4 vVectorForVerification(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
    BOOST_CHECK_EQUAL( vVectorForVerification.w, EXPECTED_VALUE_FOR_VECTOR_W );
}

/// <summary>
/// Checks that the quaternion contains no rotation information when using zero as angle.
/// </summary>
ZTEST_CASE ( Constructor9_NoRotationStoredInQuaternionWhenUsingZeroAsAngle_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0).Normalize();
    const float_z ANGLE = SFloat::_0;

    const float_z EXPECTED_VALUE_FOR_VECTOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_VECTOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_VECTOR_W = SFloat::_4;

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    // Verifies that the vector doesn't rotate
    Vector4 vVectorForVerification(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    qQuaternionUT = qQuaternionUT.Normalize(); // To assure a correct rotation
    vVectorForVerification = vVectorForVerification.Transform(qQuaternionUT);

    BOOST_CHECK_EQUAL( vVectorForVerification.x, EXPECTED_VALUE_FOR_VECTOR_X );
    BOOST_CHECK_EQUAL( vVectorForVerification.y, EXPECTED_VALUE_FOR_VECTOR_Y );
    BOOST_CHECK_EQUAL( vVectorForVerification.z, EXPECTED_VALUE_FOR_VECTOR_Z );
    BOOST_CHECK_EQUAL( vVectorForVerification.w, EXPECTED_VALUE_FOR_VECTOR_W );
}

/// <summary>
/// Checks that the resultant quaternion is not normalized when using a null vector as axis.
/// </summary>
ZTEST_CASE ( Constructor9_ResultIsNotNormalizedWhenUsingNullVectorAsAxis_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4::GetNullVector();

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion NORMALIZED_RESULT = Quaternion(AXIS, ANGLE).Normalize();

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is not correct when a not normalized vector is used as axis.
/// </summary>
ZTEST_CASE ( Constructor9_ResultIsIncorrectWhenUsingNotNormalizedAxis_Test )
{
    // [Preparation]
    const Vector4 AXIS = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_45;
#endif

    const Quaternion CORRECT_QUATERNION(AXIS.Normalize(), ANGLE);

	// [Execution]
	Quaternion qQuaternionUT(AXIS, ANGLE);

    // [Verification]
    BOOST_CHECK( qQuaternionUT != CORRECT_QUATERNION );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that only contains rotation is used.
/// </summary>
ZTEST_CASE ( Constructor10_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const TransformationMatrix<Matrix4x3> TRANSFORMATION(TranslationMatrix<Matrix4x3>(),
                                                           RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           ScalingMatrix3x3());
    const Quaternion EXPECTED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that contains translation, rotation and scale is used.
/// </summary>
ZTEST_CASE ( Constructor10_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const TransformationMatrix<Matrix4x3> TRANSFORMATION(TranslationMatrix<Matrix4x3>(SFloat::_1, SFloat::_2, SFloat::_3),
                                                           RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           ScalingMatrix3x3(SFloat::_0_25, SFloat::_0_5, (float_z)200.0));
    const Quaternion EXPECTED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a identity quaternion is obtained when using a transformation matrix that contains translation and scale but not rotation.
/// </summary>
ZTEST_CASE ( Constructor10_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> TRANSFORMATION(TranslationMatrix<Matrix4x3>(SFloat::_1, SFloat::_2, SFloat::_3),
                                                           RotationMatrix3x3(),
                                                           ScalingMatrix3x3(SFloat::_0_25, SFloat::_0_5, (float_z)200.0));
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a transformation matrix whose elements all equal zero is used.
/// </summary>
ZTEST_CASE ( Constructor10_AssertionFailsWhenUsingNullMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> NULL_MATRIX(TransformationMatrix<Matrix4x3>::GetNullMatrix());
    const Quaternion EXPECTED_RESULT(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Quaternion qQuaternionUT(NULL_MATRIX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an identity quaternion is obtained when a transformation matrix is the identity.
/// </summary>
ZTEST_CASE ( Constructor10_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> TRANSFORMATION(TransformationMatrix<Matrix4x3>::GetIdentity());
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that only contains rotation is used.
/// </summary>
ZTEST_CASE ( Constructor11_QuaternionIsCorrectlyBuiltWhenMatrixOnlyContainsRotation_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const TransformationMatrix<Matrix4x4> TRANSFORMATION(TranslationMatrix<Matrix4x4>(),
                                                           RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           ScalingMatrix3x3());
    const Quaternion EXPECTED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a transformation matrix that contains translation, rotation and scale is used.
/// </summary>
ZTEST_CASE ( Constructor11_QuaternionIsCorrectlyBuiltWhenMatrixContainsTranslationRotationAndScale_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const TransformationMatrix<Matrix4x4> TRANSFORMATION(TranslationMatrix<Matrix4x4>(SFloat::_1, SFloat::_2, SFloat::_3),
                                                           RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z),
                                                           ScalingMatrix3x3(SFloat::_0_25, SFloat::_0_5, (float_z)200.0));
    const Quaternion EXPECTED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a identity quaternion is obtained when using a transformation matrix that contains translation and scale but not rotation.
/// </summary>
ZTEST_CASE ( Constructor11_IdentityIsObtainedWhenMatrixContainsTranslationAndScaleButNotRotation_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSFORMATION(TranslationMatrix<Matrix4x4>(SFloat::_1, SFloat::_2, SFloat::_3),
                                                           RotationMatrix3x3(),
                                                           ScalingMatrix3x3(SFloat::_0_25, SFloat::_0_5, (float_z)200.0));
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a transformation matrix whose elements all equal zero is used.
/// </summary>
ZTEST_CASE ( Constructor11_AssertionFailsWhenUsingNullMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> NULL_MATRIX(TransformationMatrix<Matrix4x4>::GetNullMatrix());
    const Quaternion EXPECTED_RESULT(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Quaternion qQuaternionUT(NULL_MATRIX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an identity quaternion is obtained when a transformation matrix is the identity.
/// </summary>
ZTEST_CASE ( Constructor11_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSFORMATION(TransformationMatrix<Matrix4x4>::GetIdentity());
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
	Quaternion qQuaternionUT(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly formed when a common rotation matrix is used.
/// </summary>
ZTEST_CASE ( Constructor12_QuaternionIsCorrectlyBuiltWhenUsingArbitraryRotationMatrix_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_QuarterPi;
    const float_z EULER_ANGLE_Y = SAngle::_ThirdPi;
    const float_z EULER_ANGLE_Z = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_45;
    const float_z EULER_ANGLE_Y = SAngle::_60;
    const float_z EULER_ANGLE_Z = SAngle::_90;
#endif

    const RotationMatrix3x3 ROTATION(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const Quaternion EXPECTED_RESULT = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

	// [Execution]
	Quaternion qQuaternionUT(ROTATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a rotation matrix whose elements all equal zero is used.
/// </summary>
ZTEST_CASE ( Constructor12_AssertionFailsWhenUsingNullMatrix_Test )
{
    // [Preparation]

    const RotationMatrix3x3 NULL_MATRIX(RotationMatrix3x3::GetNullMatrix());
    const Quaternion EXPECTED_RESULT(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Quaternion quat(NULL_MATRIX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an identity quaternion is obtained when a rotation matrix is the identity.
/// </summary>
ZTEST_CASE ( Constructor12_IdentityIsObtainedWhenUsingIdentityMatrix_Test )
{
    // [Preparation]

    const RotationMatrix3x3 ROTATION(RotationMatrix3x3::GetIdentity());
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
	Quaternion qQuaternionUT(ROTATION);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that X, Y, and Z equal zero and W equals one.
/// </summary>
ZTEST_CASE ( GetIdentity_XYZEqualZeroAndWEqualsOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_XYZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

	// [Execution]
    Quaternion qQuaternionUT = Quaternion::GetIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_XYZ);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different quaternions are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_9;

    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of adding two common quaternions is not normalized.
/// </summary>
ZTEST_CASE ( OperatorAddition_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

    const Quaternion NORMALIZED_RESULT = (OPERAND1 + OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if two different quaternions are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_3;

    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_9);
    const Quaternion OPERAND2 = Quaternion(SFloat::_0_5, SFloat::_4, -SFloat::_5, SFloat::_6);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of subtracting two common quaternions is not normalized.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

    const Quaternion NORMALIZED_RESULT = (OPERAND1 - OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by another arbitrary quaternion.
/// </summary>
ZTEST_CASE ( OperatorProduct1_QuaternionIsCorrectlyMultipliedByAnotherQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)0.34045882057130072;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.20951312035156971;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)0.54997194092287027;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)-0.7332959212304937;

    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the product between quaternions is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternion1UT = OPERAND1 * OPERAND2;
    Quaternion qQuaternion2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the product by an identity quaternion returns the same quaternion.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ProductByIdentityReturnsTheSame_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Quaternion EXPECTED_RESULT = OPERAND;


	// [Execution]
    Quaternion qQuaternionUT = OPERAND * IDENTITY_QUATERNION;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the product of a quaternion by its inverse returns the identity.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ProductByInverseReturnsIdentity_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion INVERSE = OPERAND.Invert();
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND * INVERSE;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2);
    const Quaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();
    const Quaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct2_QuaternionIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_2;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_0, -SFloat::_2, SFloat::_4);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION * SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 3D vector.
/// </summary>
ZTEST_CASE ( OperatorProduct3_QuaternionIsCorrectlyMultipliedBy3DVector_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector3 VECTOR = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)11.0, (float_z)4.0, (float_z)15.0, (float_z)-32.0);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
ZTEST_CASE ( OperatorProduct3_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector3 VECTOR = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Quaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 4D vector.
/// </summary>
ZTEST_CASE ( OperatorProduct4_QuaternionIsCorrectlyMultipliedBy4DVector_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector4 VECTOR = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)19.0, (float_z)20.0, (float_z)39.0, (float_z)-16.0);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
ZTEST_CASE ( OperatorProduct4_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector4 VECTOR = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Quaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by another arbitrary quaternion.
/// </summary>
ZTEST_CASE ( OperatorDivision1_QuaternionIsCorrectlyDividedByAnotherQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-0.23570226039551589;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)-5.5511151231257827e-017;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)-0.23570226039551592;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)0.94280904158206336;

    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the division between quaternions is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivision1_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternion1UT = OPERAND1 / OPERAND2;
    Quaternion qQuaternion2UT = OPERAND2 / OPERAND1;

    // [Verification]
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the division by an identity quaternion returns the same quaternion.
/// </summary>
ZTEST_CASE ( OperatorDivision1_DivisionByIdentityReturnsTheSame_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Quaternion EXPECTED_RESULT = OPERAND;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND / IDENTITY_QUATERNION;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
ZTEST_CASE ( OperatorDivision1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2);
    const Quaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
ZTEST_CASE ( OperatorDivision1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();
    const Quaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1 / OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision2_QuaternionIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_8;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_0, -SFloat::_2, SFloat::_4);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION / SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}


/// <summary>
/// Checks if two different quaternions are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_9;

    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT += OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of adding two common quaternions is not normalized.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

    const Quaternion NORMALIZED_RESULT = (OPERAND1 + OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT += OPERAND2;

    // [Verification]
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if the quaternion is correctly added and assigned to itself (same instance for both operands).
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_AddedToItself_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion EXPECTED_RESULT = Quaternion(SFloat::_0_5, SFloat::_2, SFloat::_4, SFloat::_6);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT += qQuaternionUT;

    // [Verification]
    BOOST_CHECK(qQuaternionUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks if two different quaternions are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_3;

    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_9);
    const Quaternion OPERAND2 = Quaternion(SFloat::_0_5, SFloat::_4, -SFloat::_5, SFloat::_6);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the result of subtracting two common quaternions is not normalized.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion OPERAND2 = Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

    const Quaternion NORMALIZED_RESULT = (OPERAND1 - OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK(qQuaternionUT != NORMALIZED_RESULT);
}

/// <summary>
/// Checks if the quaternion is correctly subtracted and assigned to itself (same instance for both operands).
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_SubtractedToItself_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion EXPECTED_RESULT = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT -= qQuaternionUT;

    // [Verification]
    BOOST_CHECK(qQuaternionUT == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by another arbitrary quaternion.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_QuaternionIsCorrectlyMultipliedByAnotherQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)0.34045882057130072;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.20951312035156971;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)0.54997194092287027;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)-0.7332959212304937;

    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the product between quaternions is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternion1UT = OPERAND1;
    qQuaternion1UT *= OPERAND2;
    Quaternion qQuaternion2UT = OPERAND2;
    qQuaternion2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the product by an identity quaternion returns the same quaternion.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ProductByIdentityReturnsTheSame_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Quaternion EXPECTED_RESULT = OPERAND;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= IDENTITY_QUATERNION;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the product of a quaternion by its inverse returns the identity.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ProductByInverseReturnsIdentity_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion INVERSE = OPERAND.Invert();
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= INVERSE;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2);
    const Quaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();
    const Quaternion NORMALIZED_RESULT = (OPERAND1 * OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by itself (same instance used for both operands).
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_QuaternionIsCorrectlyMultipliedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)0.22222222222222221;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.44444444444444448;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)0.66666666666666674;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)-0.55555555555555569;

    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= qQuaternionUT;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_QuaternionIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_2;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_0, -SFloat::_2, SFloat::_4);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by any of its own components (same instance used for both operands).
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_QuaternionIsCorrectlyMultipliedByOneOfItsComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)288.0;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)576.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)864.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)576.0;

    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT *= qQuaternionUT.x;
    qQuaternionUT *= qQuaternionUT.y; // x 1
    qQuaternionUT *= qQuaternionUT.z; // x 2
    qQuaternionUT *= qQuaternionUT.w; // x 2 x 3

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 3D vector.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation3_QuaternionIsCorrectlyMultipliedBy3DVector_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector3 VECTOR = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)11.0, (float_z)4.0, (float_z)15.0, (float_z)-32.0);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation3_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector3 VECTOR = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Quaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly multiplied by the 4D vector.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation4_QuaternionIsCorrectlyMultipliedBy4DVector_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector4 VECTOR = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)19.0, (float_z)20.0, (float_z)39.0, (float_z)-16.0);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation4_ResultIsNotNormalized_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Vector4 VECTOR = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Quaternion NORMALIZED_RESULT = (QUATERNION * VECTOR).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT *= VECTOR;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by another arbitrary quaternion.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_QuaternionIsCorrectlyDividedByAnotherQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-0.23570226039551589;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)-5.5511151231257827e-017;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)-0.23570226039551592;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)0.94280904158206336;

    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that the division between quaternions is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();

	// [Execution]
    Quaternion qQuaternion1UT = OPERAND1;
    qQuaternion1UT /= OPERAND2;
    Quaternion qQuaternion2UT = OPERAND2;
    qQuaternion2UT /= OPERAND1;

    // [Verification]
    BOOST_CHECK( qQuaternion1UT != qQuaternion2UT );
}

/// <summary>
/// Checks that the division by an identity quaternion returns the same quaternion.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_DivisionByIdentityReturnsTheSame_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Quaternion EXPECTED_RESULT = OPERAND;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= IDENTITY_QUATERNION;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of the product is not normalized when operands are not normalized.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_ResultIsNotNormalizedWhenOperandsAreNotNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2);
    const Quaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the result of the product is normalized when operands are normalized.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_ResultIsNormalizedWhenOperandsAreNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2).Normalize();
    const Quaternion NORMALIZED_RESULT = (OPERAND1 / OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1;
    qQuaternionUT /= OPERAND2;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == NORMALIZED_RESULT );
}

/// <summary>
/// Checks that the quaternion is correctly divided by itself (same instance used for both operands).
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_QuaternionIsCorrectlyDividedByItself_Test )
{
    // [Preparation]
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2).Normalize();
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= qQuaternionUT;

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks if all the components of the quaternion are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_QuaternionIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_8;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_0, -SFloat::_2, SFloat::_4);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT /= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the quaternion is correctly divided by any of its own components (same instance used for both operands).
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_QuaternionIsCorrectlyDivisionByOneOfItsComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)1.5;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)SFloat::_1;

    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_2);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND;
    qQuaternionUT /= qQuaternionUT.x;
    qQuaternionUT /= qQuaternionUT.y; // / 1
    qQuaternionUT /= qQuaternionUT.z; // / 2
    qQuaternionUT /= qQuaternionUT.w; // / 2 / 3

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_VALUE_FOR_W) );
}

/// <summary>
/// Checks that a quaternion is correctly assigned to another quaternion.
/// </summary>
ZTEST_CASE ( OperatorAssignation_QuaternionIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Quaternion qQuaternionUT;
    qQuaternionUT = QUATERNION;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that all quaternion components are correctly negated.
/// </summary>
ZTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, -SFloat::_4);

	// [Execution]
    Quaternion qQuaternionUT = -QUATERNION;

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that a common quaternion becomes a unit quaternion.
/// </summary>
ZTEST_CASE ( Normalize_CommonQuaternionIsCorrectlyNormalized_Test )
{
    // [Preparation]
    const float_z EXPECTED_SUAREDLENGTH = SFloat::_1;

    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION.Normalize();

    // [Verification]
    float_z fSquaredLength = qQuaternionUT.GetSquaredLength();

    BOOST_CHECK(SFloat::AreEqual(fSquaredLength, EXPECTED_SUAREDLENGTH));
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when a null quaternion is to be normalized.
/// </summary>
ZTEST_CASE ( Normalize_AssertionFailsWhenNullQuaternionIsToBeNormalized_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        QUATERNION.Normalize();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a common quaternion is correctly inverted.
/// </summary>
ZTEST_CASE ( Invert_CommonQuaternionIsCorrectlyInverted_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)-0.033333333333333333, (float_z)0.066666666666666666, (float_z)-0.1, (float_z)0.13333333333333333);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION.Invert();

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a normalized quaternion is correctly inverted.
/// </summary>
ZTEST_CASE ( UnitInvert_NormalizedQuaternionIsCorrectlyInverted_Test )
{
    // [Preparation]
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)-0.18257418583505536, (float_z)0.36514837167011072, (float_z)-0.54772255750516607, (float_z)0.73029674334022143);

	// [Execution]
    Quaternion qQuaternionUT = NORMALIZED_QUATERNION.UnitInvert();

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a quaternion that is not normalized is not correctly inverted.
/// </summary>
ZTEST_CASE ( UnitInvert_NotNormalizedQuaternionIsNotCorrectlyInverted_Test )
{
    // [Preparation]
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion NOT_EXPECTED_RESULT = Quaternion((float_z)-0.18257418, (float_z)0.36514837, (float_z)-0.54772258, (float_z)0.73029673);

	// [Execution]
    Quaternion qQuaternionUT = NOT_NORMALIZED_QUATERNION.UnitInvert();

    // [Verification]
    BOOST_CHECK( qQuaternionUT != NOT_EXPECTED_RESULT );
}

/// <summary>
/// Checks that all quaternion components are set to zero.
/// </summary>
ZTEST_CASE ( ResetToZero_AllQuaternionComponentsAreSetToZero_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT.ResetToZero();

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that the quaternion is converted to an identity quaternion.
/// </summary>
ZTEST_CASE ( ResetToIdentity_QuaternionBecomesIdentity_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_0);
    const Quaternion IDENTITY = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    qQuaternionUT.ResetToIdentity();

    // [Verification]
    BOOST_CHECK(qQuaternionUT == IDENTITY);
}

/// <summary>
/// Checks that the returned dot product result for 2 common quaternions equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonQuaternions_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)0.97590007294853309;

    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7).Normalize();

	// [Execution]
    float_z fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7).Normalize();

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals one when both operands are the same.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductEqualsOneWhenRotationAxisIsTheSame_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)30.0;
    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    float_z fResultUT = OPERAND.DotProduct(OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is a null quaternion.
/// </summary>
ZTEST_CASE ( DotProduct_ReturnsZeroWhenAOperandIsNullQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Quaternion NONNULL_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResult1UT = NONNULL_QUATERNION.DotProduct(NULL_QUATERNION);
    float_z fResult2UT = NULL_QUATERNION.DotProduct(NONNULL_QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common quaternions equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween_ReturnsAngleBetween2CommonQuaternions_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    Vector3 ROTATION_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    const Quaternion OPERAND1 = Quaternion(ROTATION_AXIS, SFloat::_0);
    const Quaternion OPERAND2 = Quaternion(ROTATION_AXIS, EXPECTED_RESULT);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT, SMALLER_TOLERANCE) );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleBetweenIsCommutative_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND2.AngleBetween(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when both quaternions are normalized and are the same.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleEqualsZeroWhenNormalizedQuaternionsAreTheSame_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Quaternion OPERAND = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

	// [Execution]
    float_z fResultUT = OPERAND.AngleBetween(OPERAND);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT, (float_z)1e-05) ); // There is a big loss of precision so a greater tolerance must be used
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z HALF_CIRCUMFERENCE_ANGLE = -SAngle::_180;
    #else
        const float_z HALF_CIRCUMFERENCE_ANGLE = -SAngle::_Pi;
    #endif

    const Quaternion REFERENCE_OPERAND = Quaternion::GetIdentity();
    const Quaternion QUATERNION = Quaternion(Vector3(SFloat::_1, SFloat::_0, SFloat::_0), HALF_CIRCUMFERENCE_ANGLE);

	// [Execution]
    float_z fResultUT = REFERENCE_OPERAND.AngleBetween(QUATERNION);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResultUT, SFloat::_0) );
}

/// <summary>
/// Checks that a common quaternion is correctly conjugated.
/// </summary>
ZTEST_CASE ( Conjugate_CommonQuaternionIsCorrectlyConjugated_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_RESULT = Quaternion(-SFloat::_1, SFloat::_2, -SFloat::_3, SFloat::_4);

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION.Conjugate();

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a correct quaternion is obtained as result of interpolating between 2 common quaternions.
/// </summary>
ZTEST_CASE ( Lerp_CorrectLerpedQuaternionIsObtainedForTwoCommonQuaternions_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ANGLE1 = SFloat::_0;
    const float_z ANGLE2 = SFloat::_1;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE1 = SFloat::_0;
    const float_z ANGLE2 = SAngle::RadiansToDegrees(SFloat::_1);
#endif

    const Quaternion OPERAND1 = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), ANGLE1).Normalize();
    const Quaternion OPERAND2 = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), ANGLE2).Normalize();
    //const Quaternion EXPECTED_RESULT = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), SFloat::_0_25).Normalize();
    // [TODO] Thund: There is a problem with imprecision, is it a matter of precision degradation or calculus error? It could be even an imprecision inherent to this Lerp process, reason to use Slerp
    const Quaternion EXPECTED_RESULT = Quaternion((float_z)0.032794551514706963, (float_z)0.065589103029413925, (float_z)0.098383654544120888, (float_z)0.99244306812697791);

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Lerp(SFloat::_0_25, OPERAND2);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent NORMALIZED quaternions is the same quaternion.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingTwoEquivalentNormalizedQuaternionsGivesSameQuaternion_Test )
{
    // [Preparation]
    const Quaternion EXPECTED_RESULT = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = EXPECTED_RESULT.Lerp(SFloat::_0_5, EXPECTED_RESULT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the result is always normalized, even if parameter is not.
/// </summary>
ZTEST_CASE ( Lerp_ResultIsAlwaysNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Quaternion EXPECTED_RESULT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the result of interpolating just in the middle between a quaternion and its conjugated is an identity quaternion.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingInTheMiddleOfQuaternionsAndItsConjugatedGivesIdentityQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = OPERAND1.Conjugate();
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned quaternion is the resident quaternion, normalized.
/// </summary>
ZTEST_CASE ( Lerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Quaternion EXPECTED_RESULT = OPERAND1.Normalize();
    const float_z PROPORTION = SFloat::_0;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned quaternion is the input quaternion, normalized.
/// </summary>
ZTEST_CASE ( Lerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Quaternion EXPECTED_RESULT = OPERAND2.Normalize();
    const float_z PROPORTION = SFloat::_1;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that a correct quaternion is obtained as result of interpolating between 2 common quaternions.
/// </summary>
ZTEST_CASE ( Slerp_CorrectSlerpedQuaternionIsObtainedForTwoCommonQuaternions_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), SFloat::_0).Normalize();
    const Quaternion OPERAND2 = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), SFloat::_1).Normalize();
    const Quaternion EXPECTED_RESULT = Quaternion(Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize(), SFloat::_0_25).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Slerp(SFloat::_0_25, OPERAND2);

    // [Verification]
    BOOST_CHECK( qQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent NORMALIZED quaternions is the same quaternion.
/// </summary>
ZTEST_CASE ( Slerp_InterpolatingTwoEquivalentNormalizedQuaternionsGivesSameQuaternion_Test )
{
    // [Preparation]
    const Quaternion EXPECTED_RESULT = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = EXPECTED_RESULT.Slerp(SFloat::_0_5, EXPECTED_RESULT);
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result is always normalized, even if parameter is not.
/// </summary>
ZTEST_CASE ( Slerp_ResultIsAlwaysNormalized_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8).Normalize();
    const Quaternion EXPECTED_RESULT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2).Normalize();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Slerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 a quaternion and its conjugated is an identity quaternion.
/// </summary>
ZTEST_CASE ( Slerp_InterpolatingInTheMiddleOfQuaternionAndItsConjugatedGivesIdentityQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = OPERAND1.Conjugate();
    const Quaternion EXPECTED_RESULT = Quaternion::GetIdentity();

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Slerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that when the proportion equals 0, the returned quaternion is the resident quaternion, normalized.
/// </summary>
ZTEST_CASE ( Slerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Quaternion EXPECTED_RESULT = OPERAND1.Normalize();
    const float_z PROPORTION = SFloat::_0;

	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Slerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned quaternion is the input quaternion, normalized.
/// </summary>
ZTEST_CASE ( Slerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // [Preparation]
    const Quaternion OPERAND1 = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion OPERAND2 = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Quaternion EXPECTED_RESULT = OPERAND2.Normalize();
    const float_z PROPORTION = SFloat::_1;
    
	// [Execution]
    Quaternion qQuaternionUT = OPERAND1.Slerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(qQuaternionUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that obtained angles equal zero when the quaternion is the identity.
/// </summary>
ZTEST_CASE ( ToEulerAngles_AnglesEqualZeroWhenQuaternionIsIdentity_Test )
{
    // [Preparation]
    const Quaternion IDENTITY = Quaternion::GetIdentity();
    const float_z EXPECTED_ANGLES = SFloat::_0;

	// [Execution]
    float_z fAngleXUT = SFloat::_1;
    float_z fAngleYUT = SFloat::_1;
    float_z fAngleZUT = SFloat::_1;
    IDENTITY.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fAngleXUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleYUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleZUT, EXPECTED_ANGLES);
}

/// <summary>
/// Checks that correct angles are obtained from a common quaternion.
/// </summary>
ZTEST_CASE ( ToEulerAngles_CorrectAnglesAreObtainedFromCommonQuaternion_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_X_ANGLE = SFloat::_1;
        const float_z EXPECTED_Y_ANGLE = SFloat::_2;
        const float_z EXPECTED_Z_ANGLE = (float_z)-2.2831853071795871;
        const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_4);
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z EXPECTED_X_ANGLE = SAngle::RadiansToDegrees(SFloat::_1);
        const float_z EXPECTED_Y_ANGLE = SAngle::RadiansToDegrees(SFloat::_2);

        #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
            const float_z EXPECTED_Z_ANGLE = SAngle::RadiansToDegrees(-2.283185f);
        #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
            const float_z EXPECTED_Z_ANGLE = SAngle::RadiansToDegrees(-2.2831853071795871);
        #endif

        const Quaternion QUATERNION = Quaternion(SAngle::RadiansToDegrees(SFloat::_1), SAngle::RadiansToDegrees(SFloat::_2), SAngle::RadiansToDegrees(SFloat::_4));
    #endif
    
	// [Execution]
    float_z fAngleXUT = SFloat::_0;
    float_z fAngleYUT = SFloat::_0;
    float_z fAngleZUT = SFloat::_0;
    QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngleXUT, EXPECTED_X_ANGLE, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(fAngleYUT, EXPECTED_Y_ANGLE, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(fAngleZUT, EXPECTED_Z_ANGLE, SMALLER_TOLERANCE) );
}

/// <summary>
/// Checks that obtained angles correspond to the same rotation, even if they don't coincide with the values used to create the quaternion.
/// </summary>
ZTEST_CASE ( ToEulerAngles_ObtainedAnglesCorrespondToSameRotationEvenWhenAnglesAreNotWhatExpected_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_4, SFloat::_5, SFloat::_4);
    const Vector3 VECTOR(SFloat::_1, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fAngleXUT = SFloat::_0;
    float_z fAngleYUT = SFloat::_0;
    float_z fAngleZUT = SFloat::_0;
    Vector3 vVectorRotatedWithOriginalAngles = VECTOR.Transform(QUATERNION);

    QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    Quaternion qQuaternionCreatedWithObtainedAngles(fAngleXUT, fAngleYUT, fAngleZUT);
    Vector3 vVectorRotatedWithObtainedAngles = VECTOR.Transform(qQuaternionCreatedWithObtainedAngles);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorRotatedWithOriginalAngles.x, vVectorRotatedWithObtainedAngles.x, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(vVectorRotatedWithOriginalAngles.y, vVectorRotatedWithObtainedAngles.y, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(vVectorRotatedWithOriginalAngles.z, vVectorRotatedWithObtainedAngles.z, SMALLER_TOLERANCE) );
}

/// <summary>
/// Checks that obtained angles equal zero when the quaternion is null.
/// </summary>
ZTEST_CASE ( ToEulerAngles_AnglesEqualZeroWhenQuaternionIsNull_Test )
{
    // [Preparation]
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const float_z EXPECTED_ANGLES = SFloat::_0;

	// [Execution]
    float_z fAngleXUT = SFloat::_1;
    float_z fAngleYUT = SFloat::_1;
    float_z fAngleZUT = SFloat::_1;
    NULL_QUATERNION.ToEulerAngles(fAngleXUT, fAngleYUT, fAngleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fAngleXUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleYUT, EXPECTED_ANGLES);
    BOOST_CHECK_EQUAL(fAngleZUT, EXPECTED_ANGLES);
}

// TODO Thund: There is a special case, when X = +-90º. TEst it!

/// <summary>
/// Checks that the length of a common quaternion is what expected.
/// </summary>
ZTEST_CASE ( GetLength_CorrectLengthObtainedFromCommonQuaternion_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_LENGTH = (float_z)5.4772255750516612;

	// [Execution]
    float_z fLengthUT = QUATERNION.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLengthUT, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that unit quaternions' length equals one.
/// </summary>
ZTEST_CASE ( GetLength_EqualsOneWhenUsingUnitQuaternion_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLengthUT = QUATERNION.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLengthUT, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that identity quaternion's length equals one.
/// </summary>
ZTEST_CASE ( GetLength_EqualsOneWhenUsingIdentity_Test )
{
    // [Preparation]
    const Quaternion IDENTITY = Quaternion::GetIdentity();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLengthUT = IDENTITY.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that null quaternion's length equals zero.
/// </summary>
ZTEST_CASE ( GetLength_EqualsZeroWhenUsingNullQuaternion_Test )
{
    // [Preparation]
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const float_z EXPECTED_LENGTH = SFloat::_0;

	// [Execution]
    float_z fLengthUT = NULL_QUATERNION.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the squared length of a common quaternion is what expected.
/// </summary>
ZTEST_CASE ( GetSquaredLength_CorrectLengthObtainedFromCommonQuaternion_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_LENGTH = (float_z)30.0;

	// [Execution]
    float_z fLengthUT = QUATERNION.GetSquaredLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that unit quaternions' squared length equals one.
/// </summary>
ZTEST_CASE ( GetSquaredLength_EqualsOneWhenUsingUnitQuaternion_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLengthUT = QUATERNION.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLengthUT, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that identity quaternion's squared length equals one.
/// </summary>
ZTEST_CASE ( GetSquaredLength_EqualsOneWhenUsingIdentity_Test )
{
    // [Preparation]
    const Quaternion IDENTITY = Quaternion::GetIdentity();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLengthUT = IDENTITY.GetSquaredLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that null quaternion's squared length equals zero.
/// </summary>
ZTEST_CASE ( GetSquaredLength_EqualsZeroWhenUsingNullQuaternion_Test )
{
    // [Preparation]
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const float_z EXPECTED_LENGTH = SFloat::_0;

	// [Execution]
    float_z fLengthUT = NULL_QUATERNION.GetSquaredLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that correct angle and rotation axis are obtained from a common quaternion.
/// </summary>
ZTEST_CASE ( ToAxisAngle1_CorrectAngleAndAxisAreObtainedFromCommonQuaternion_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SFloat::_2;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::RadiansToDegrees(SFloat::_2);
#endif

    const Vector3 EXPECTED_AXIS = Vector3(-SFloat::_1, SFloat::_2, -SFloat::_3).Normalize();

    const Quaternion QUATERNION(EXPECTED_AXIS, EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the quaternion is the identity.
/// </summary>
ZTEST_CASE ( ToAxisAngle1_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenQuaternionIsIdentity_Test )
{
    // [Preparation]
    const float_z EXPECTED_ANGLE = SFloat::_0;
    const Vector3 UNITVECTORX = Vector3::GetUnitVectorX();

    const Quaternion IDENTITY = Quaternion::GetIdentity();

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector3 vAxisUT;
    IDENTITY.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals PI (or 180º) and rotation axis equals null vector when the quaternion is null.
/// </summary>
ZTEST_CASE ( ToAxisAngle1_AxisIsNullAndAngleEqualsPiOr180WhenQuaternionIsNull_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SAngle::_Pi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::_180;
#endif

    const Vector3 EXPECTED_AXIS = Vector3::GetNullVector();

    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector3 vAxisUT;
    NULL_QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that correct results are obtained when the rotation angle equals Pi (or 180º).
/// </summary>
ZTEST_CASE ( ToAxisAngle1_CorrectValuesObtainedWhenRotationAngleEqualsPiOr180_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SAngle::_Pi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::_180;
#endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Quaternion QUATERNION = Quaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the rotation angle is zero.
/// </summary>
ZTEST_CASE ( ToAxisAngle1_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenRotationAngleIsZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_ANGLE = SFloat::_0;
    const Vector3 UNITVECTORX = Vector3::GetUnitVectorX();

    const Quaternion QUATERNION = Quaternion(UNITVECTORX, EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector3 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle is always positive, even when the angle used to build the quaternion was negative.
/// </summary>
ZTEST_CASE ( ToAxisAngle1_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SFloat::_2;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::RadiansToDegrees(SFloat::_2);
#endif

    const Vector3 AXIS = Vector3(-SFloat::_1, SFloat::_2, -SFloat::_3).Normalize();

    const Quaternion QUATERNION_USING_POSITIVE_ANGLE = Quaternion(AXIS, EXPECTED_ANGLE);
    const Quaternion QUATERNION_USING_NEGATIVE_ANGLE = Quaternion(AXIS, -EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUTFromPositive = SFloat::_0;
    float_z fAngleUTFromNegative = SFloat::_0;
    Vector3 vAxisUT;
    QUATERNION_USING_POSITIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromPositive);
    QUATERNION_USING_NEGATIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromNegative);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngleUTFromPositive, EXPECTED_ANGLE) );
    BOOST_CHECK( SFloat::AreEqual(fAngleUTFromNegative, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that correct angle and rotation axis are obtained from a common quaternion.
/// </summary>
ZTEST_CASE ( ToAxisAngle2_CorrectAngleAndAxisAreObtainedFromCommonQuaternion_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SFloat::_2;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::RadiansToDegrees(SFloat::_2);
#endif

    Vector4 EXPECTED_AXIS = Vector4(-SFloat::_1, SFloat::_2, -SFloat::_3, SFloat::_4).Normalize();
    EXPECTED_AXIS.w = SFloat::_0; // Axis is a vector, not a point

    const Quaternion QUATERNION(Vector4(-SFloat::_1, SFloat::_2, -SFloat::_3, SFloat::_4).Normalize(), EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the quaternion is the identity.
/// </summary>
ZTEST_CASE ( ToAxisAngle2_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenQuaternionIsIdentity_Test )
{
    // [Preparation]
    const float_z EXPECTED_ANGLE = SFloat::_0;
    const Vector4 UNITVECTORX = Vector4::GetUnitVectorX();

    const Quaternion IDENTITY = Quaternion::GetIdentity();

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector4 vAxisUT;
    IDENTITY.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == UNITVECTORX );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals PI (or 180º) and rotation axis equals null vector when the quaternion is null.
/// </summary>
ZTEST_CASE ( ToAxisAngle2_AxisIsNullAndAngleEqualsPiOr180WhenQuaternionIsNull_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SAngle::_Pi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::_180;
#endif

    const Vector4 EXPECTED_AXIS = Vector4::GetNullVector();

    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector4 vAxisUT;
    NULL_QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that correct results are obtained when the rotation angle equals Pi (or 180º).
/// </summary>
ZTEST_CASE ( ToAxisAngle2_CorrectValuesObtainedWhenRotationAngleEqualsPiOr180_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SAngle::_Pi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::_180;
#endif

    Vector4 EXPECTED_AXIS = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    EXPECTED_AXIS.w = SFloat::_0; // Axis is a vector, not a point
    const Quaternion QUATERNION = Quaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle equals zero and rotation axis is a unit vector pointing to positive X axis vector when the rotation angle is zero.
/// </summary>
ZTEST_CASE ( ToAxisAngle2_AxisIsUnitVectorPointingXAndAngleEqualsZeroWhenRotationAngleIsZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_ANGLE = SFloat::_0;
    Vector4 EXPECTED_AXIS = Vector4::GetUnitVectorX();

    const Quaternion QUATERNION = Quaternion(EXPECTED_AXIS, EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUT = SFloat::_0;
    Vector4 vAxisUT;
    QUATERNION.ToAxisAngle(vAxisUT, fAngleUT);

    // [Verification]
    BOOST_CHECK( vAxisUT == EXPECTED_AXIS );
    BOOST_CHECK_EQUAL( fAngleUT, EXPECTED_ANGLE );
}

/// <summary>
/// Checks that obtained angle is always positive, even when the angle used to build the quaternion was negative.
/// </summary>
ZTEST_CASE ( ToAxisAngle2_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_ANGLE = SFloat::_2;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_ANGLE = SAngle::RadiansToDegrees(SFloat::_2);
#endif

    const Vector4 AXIS = Vector4(-SFloat::_1, SFloat::_2, -SFloat::_3, SFloat::_4).Normalize();

    const Quaternion QUATERNION_USING_POSITIVE_ANGLE = Quaternion(AXIS, EXPECTED_ANGLE);
    const Quaternion QUATERNION_USING_NEGATIVE_ANGLE = Quaternion(AXIS, -EXPECTED_ANGLE);

	// [Execution]
    float_z fAngleUTFromPositive = SFloat::_0;
    float_z fAngleUTFromNegative = SFloat::_0;
    Vector4 vAxisUT;
    QUATERNION_USING_POSITIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromPositive);
    QUATERNION_USING_NEGATIVE_ANGLE.ToAxisAngle(vAxisUT, fAngleUTFromNegative);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngleUTFromPositive, EXPECTED_ANGLE) );
    BOOST_CHECK( SFloat::AreEqual(fAngleUTFromNegative, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const Quaternion QUATERNION = Quaternion(SFloat::_0_25, (float_z)-0.000002, (float_z)40000.0, (float_z)1.0 );

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("Q(0.25,-1.99999999e-06,40000,1)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("Q(0.25,-1.99999999e-06,40000,1)");
    #endif
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("Q(0.25,-1.9999999999999999e-06,40000,1)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("Q(0.25,-1.9999999999999999e-06,40000,1)");
    #endif
#endif

	// [Execution]
    Quaternion qQuaternionUT = QUATERNION;
    string_z strStringForm = qQuaternionUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: Quaternion
ZTEST_SUITE_END()
