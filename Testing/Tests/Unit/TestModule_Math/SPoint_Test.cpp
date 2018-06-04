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

#include "ZMath/SPoint.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/SAngle.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/Quaternion.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"
using namespace z::Internals;


ZTEST_SUITE_BEGIN( SPoint_TestSuite )

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                           Vector2(SFloat::_0_25 + SFloat::_1, -SFloat::_7),
                                           Vector2(SFloat::_0, SFloat::_8)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_5),
                                   Vector2(-SFloat::_1, SFloat::_10)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                           Vector2(SFloat::_0_25 + SFloat::_1, -SFloat::_7),
                                           Vector2(SFloat::_0, SFloat::_8)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_5),
                                   Vector2(-SFloat::_1, SFloat::_10)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 TRANSLATION(SFloat::_1, -SFloat::_2);

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION.x, TRANSLATION.y, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_1, SFloat::_0),
                                           Vector2(SFloat::_0, SFloat::_1),
                                           Vector2(-SFloat::_4, -SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_1, SFloat::_0),
                                   Vector2(-SFloat::_4, SFloat::_4)
                               };

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_1, SFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                               };

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Rotate1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Rotate1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_0, SFloat::_3),
                                           Vector2(SFloat::_0_5, -SFloat::_9),
                                           Vector2(-SFloat::_2, SFloat::_6)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_3),
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_2, -SFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_0, SFloat::_3),
                                           Vector2(SFloat::_0_5, -SFloat::_9),
                                           Vector2(-SFloat::_2, SFloat::_6)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_3),
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_2, -SFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE.x, SCALE.y, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_0_5, SFloat::_3),
                                           Vector2(SFloat::_3 + SFloat::_0_5, SFloat::_3 + SFloat::_0_5),
                                           Vector2(-SFloat::_4, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_5),
                                   Vector2(-SFloat::_1, SFloat::_10)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_0_5, SFloat::_3),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_1),
                                           Vector3(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3),
                                           Vector3(SFloat::_0, SFloat::_8, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_2),
                                   Vector3(SFloat::_0_25, -SFloat::_5, SFloat::_0),
                                   Vector3(-SFloat::_1, SFloat::_10, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_1, SFloat::_0),
                                           Vector4(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3, SFloat::_0),
                                           Vector4(SFloat::_0, SFloat::_8, SFloat::_4, SFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_2, SFloat::_0),
                                   Vector4(SFloat::_0_25, -SFloat::_5, SFloat::_0, SFloat::_0),
                                   Vector4(-SFloat::_1, SFloat::_10, SFloat::_1, SFloat::_0)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_2, SFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_1, SFloat::_0),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_0),
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_0),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_1),
                                           Vector3(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3),
                                           Vector3(SFloat::_0, SFloat::_8, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_2),
                                   Vector3(SFloat::_0_25, -SFloat::_5, SFloat::_0),
                                   Vector3(-SFloat::_1, SFloat::_10, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_1, SFloat::_0),
                                           Vector4(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3, SFloat::_0),
                                           Vector4(SFloat::_0, SFloat::_8, SFloat::_4, SFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_2, SFloat::_0),
                                   Vector4(SFloat::_0_25, -SFloat::_5, SFloat::_0, SFloat::_0),
                                   Vector4(-SFloat::_1, SFloat::_10, SFloat::_1, SFloat::_0)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_2, SFloat::_0),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_1, SFloat::_0),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_0),
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_0),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate7_MoreThanOnePointAreTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_1),
                                           Vector3(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3),
                                           Vector3(SFloat::_0, SFloat::_8, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_2),
                                   Vector3(SFloat::_0_25, -SFloat::_5, SFloat::_0),
                                   Vector3(-SFloat::_1, SFloat::_10, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate7_OnlyOnePointIsTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{

    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate7_AssertionFailsWhenInputIsNull_Test )
{

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate8_MoreThanOnePointAreTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_1),
                                           Vector3(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3),
                                           Vector3(SFloat::_0, SFloat::_8, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_2),
                                   Vector3(SFloat::_0_25, -SFloat::_5, SFloat::_0),
                                   Vector3(-SFloat::_1, SFloat::_10, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate8_OnlyOnePointIsTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_2),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, -SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{

    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate8_AssertionFailsWhenInputIsNull_Test )
{

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate9_MoreThanOnePointAreTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_1, SFloat::_1),
                                           Vector4(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3, SFloat::_1),
                                           Vector4(SFloat::_0, SFloat::_8, SFloat::_4, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_2, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, SFloat::_0, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_10, SFloat::_1, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate9_OnlyOnePointIsTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_2, SFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_1, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate9_NoWorkIsDoneWhenInputNumberIsZero_Test )
{

    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate9_AssertionFailsWhenInputIsNull_Test )
{

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Translate10_MoreThanOnePointAreTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_1, SFloat::_1),
                                           Vector4(SFloat::_0_25 + SFloat::_1, -SFloat::_7, SFloat::_3, SFloat::_1),
                                           Vector4(SFloat::_0, SFloat::_8, SFloat::_4, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_2, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, SFloat::_0, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_10, SFloat::_1, SFloat::_1)
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Translate10_OnlyOnePointIsTransformedCorrectly_Test )
{

    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_2, SFloat::_1),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, -SFloat::_1, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Translate10_NoWorkIsDoneWhenInputNumberIsZero_Test )
{

    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_1, -SFloat::_1, SFloat::_3, SFloat::_1),
                               };

	// [Execution]
    SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Translate10_AssertionFailsWhenInputIsNull_Test )
{

    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Translate(TRANSLATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, SFloat::_1),
                                   Vector3(SFloat::_1, SFloat::_0, SFloat::_2),
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);


	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Rotate2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Rotate2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1),
                                   Vector4(SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1),
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);


	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Rotate3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Rotate3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, SFloat::_1),
                                   Vector3(SFloat::_1, SFloat::_0, SFloat::_2),
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);


	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Rotate4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Rotate4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1),
                                   Vector4(SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1),
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                           arInputPoints[1].Transform(ROTATION),
                                           arInputPoints[2].Transform(ROTATION)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);


	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Rotate5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 EXPECTED_POINTS[] = {
                                           arInputPoints[0].Transform(ROTATION),
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Rotate5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;

	// [Execution]
    SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Rotate5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Rotate(ROTATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_6, -SFloat::_2, -SFloat::_0),
                                           Vector3(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4),
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_6, -SFloat::_2, -SFloat::_0, SFloat::_1),
                                           Vector4(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4, SFloat::_1),
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_6, -SFloat::_2, -SFloat::_0),
                                           Vector3(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4),
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_1, -SFloat::_1, SFloat::_3),
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_1, -SFloat::_2, SFloat::_3);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_6, -SFloat::_2, -SFloat::_0, SFloat::_1),
                                           Vector4(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4, SFloat::_1),
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE.x, SCALE.y, SCALE.z, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_6, -SFloat::_2, -SFloat::_0),
                                           Vector3(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4),
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale7_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_3, -SFloat::_8, -SFloat::_2)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale7_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Scale8_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_6, -SFloat::_2, -SFloat::_0, SFloat::_1),
                                           Vector4(SFloat::_0_25 + SFloat::_0_5, SFloat::_10, SFloat::_4, SFloat::_1),
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Scale8_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_3, -SFloat::_8, -SFloat::_2, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Scale8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Scale8_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Scale(SCALE, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)3.7677669529663689,  SFloat::_4,  (float_z)-8.4748737341529168),
                                           Vector3((float_z)-8.6507958916223728, SFloat::_3,  (float_z)4.5624075439740519),
                                           Vector3((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)10.662058069535208, (float_z)4.5, (float_z)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)3.7677669529663689,  SFloat::_4,  (float_z)-8.4748737341529168),
                                           Vector3((float_z)-8.6507958916223728, SFloat::_3,  (float_z)4.5624075439740519),
                                           Vector3((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)10.662058069535208, (float_z)4.5, (float_z)-14.308504678941933)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)3.7677669529663689,  SFloat::_4,  (float_z)-8.4748737341529168, SFloat::_1),
                                           Vector4((float_z)-8.6507958916223728, SFloat::_3,  (float_z)4.5624075439740519,  SFloat::_1),
                                           Vector4((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933, SFloat::_1)
                                       };

    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)3.7677669529663689,  SFloat::_4,  (float_z)-8.4748737341529168, SFloat::_1),
                                           Vector4((float_z)-8.6507958916223728, SFloat::_3,  (float_z)4.5624075439740519,  SFloat::_1),
                                           Vector4((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)10.662058069535208,  (float_z)4.5, (float_z)-14.308504678941933, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(TRANSFORMATION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)-2.2360679774997898, (float_z)0.74535599249992979, (float_z)2.333333333333333),
                                           Vector3((float_z)-1.1180339887498949, (float_z)-2.6087459737497545, (float_z)7.5833333333333321),
                                           Vector3((float_z)0.67082039324993692, (float_z)3.577708763999663,   SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)0.67082039324993692, (float_z)3.577708763999663, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector3* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( Transform7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)-2.2360679774997898, (float_z)0.74535599249992979, (float_z)2.333333333333333,  SFloat::_1),
                                           Vector4((float_z)-1.1180339887498949, (float_z)-2.6087459737497545, (float_z)7.5833333333333321, SFloat::_1),
                                           Vector4((float_z)0.67082039324993692, (float_z)3.577708763999663,   SFloat::_1,                 SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( Transform7_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)0.67082039324993692, (float_z)3.577708763999663, SFloat::_1, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( Transform7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };

	// [Execution]
    SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( Transform7_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    SpaceConversionMatrix CONVERSION;
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    Vector4* arInputPoints = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::Transform(CONVERSION, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_1, SFloat::_0),
                                           Vector2(SFloat::_2, SFloat::_1),
                                           Vector2(-SFloat::_2, -SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_1, SFloat::_0),
                                   Vector2(-SFloat::_4, SFloat::_4)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_2, -SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(-SFloat::_4, SFloat::_4)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( RotateWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( RotateWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z ROTATION = SAngle::_HalfPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#endif

    Vector2* arInputPoints = null_z;
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_1, SFloat::_1),
                                           Vector2(-SFloat::_0_5, (float_z)-11.0),
                                           Vector2(-SFloat::_3, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_3),
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_3, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2* arInputPoints = null_z;
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE.x, SCALE.y, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_1, SFloat::_1),
                                           Vector2(-SFloat::_0_5, (float_z)-11.0),
                                           Vector2(-SFloat::_3, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_3),
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_3, SFloat::_4)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(-SFloat::_1, SFloat::_2)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 SCALE(SFloat::_2, SFloat::_3);

    Vector2* arInputPoints = null_z;
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot1_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(SFloat::_2, SFloat::_2),
                                           Vector2(SFloat::_5, SFloat::_2 + SFloat::_0_5),
                                           Vector2(-SFloat::_2 - SFloat::_0_5, SFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_0, SFloat::_1),
                                   Vector2(SFloat::_0_25, -SFloat::_5),
                                   Vector2(-SFloat::_1, SFloat::_10)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot1_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_POINTS[] = {
                                           Vector2(-SFloat::_2 - SFloat::_0_5, SFloat::_0)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector2);
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(-SFloat::_1, SFloat::_10)
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( TransformWithPivot1_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGINAL_POINTS[] = {
                                           Vector2(SFloat::_1, -SFloat::_1),
                                       };
    const int POINTS_COUNT = 0;
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2 arInputPoints[] = {
                                   Vector2(SFloat::_1, -SFloat::_1),
                               };
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( TransformWithPivot1_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    Vector2* arInputPoints = null_z;
    const Vector2 PIVOT(SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, SFloat::_1),
                                   Vector3(SFloat::_1, SFloat::_0, SFloat::_2),
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( RotateWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( RotateWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1),
                                   Vector4(SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1),
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( RotateWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( RotateWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const Quaternion ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const Quaternion ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_0, SFloat::_1, SFloat::_1),
                                   Vector3(SFloat::_1, SFloat::_0, SFloat::_2),
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector3 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( RotateWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_4, SFloat::_4, SFloat::_3)
                               };

    const Vector3 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( RotateWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1),
                                   Vector4(SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1),
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[1] - PIVOT).Transform(ROTATION) + PIVOT,
                                           (arInputPoints[2] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( RotateWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POINTS[] = {
                                           (arInputPoints[0] - PIVOT).Transform(ROTATION) + PIVOT,
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( RotateWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_4, SFloat::_4, SFloat::_3, SFloat::_1)
                               };

    const Vector4 ORIGINAL_POINTS[] = {
                                           arInputPoints[0],
                                       };
    const int POINTS_COUNT = 0;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( RotateWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION(SAngle::_HalfPi, SAngle::_QuarterPi, SAngle::_ThirdPi);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION(SAngle::_90, SAngle::_45, SAngle::_60);
#endif

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::RotateWithPivot(ROTATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_4, SFloat::_1, SFloat::_5),
                                           Vector3(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9),
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_4, SFloat::_1, SFloat::_5, SFloat::_1),
                                           Vector4(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9, SFloat::_1),
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_4, SFloat::_1, SFloat::_5),
                                           Vector3(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9),
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot6_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_4, SFloat::_1, SFloat::_5, SFloat::_1),
                                           Vector4(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9, SFloat::_1),
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot6_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot6_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot6_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const Vector3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE.x, SCALE.y, SCALE.z, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot7_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(SFloat::_4, SFloat::_1, SFloat::_5),
                                           Vector3(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9),
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot7_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3(-SFloat::_5, -SFloat::_5, SFloat::_3)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot7_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot7_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot8_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(SFloat::_4, SFloat::_1, SFloat::_5, SFloat::_1),
                                           Vector4(-SFloat::_0_25 - SFloat::_1, (float_z)13.0, SFloat::_9, SFloat::_1),
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( ScaleWithPivot8_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4(-SFloat::_5, -SFloat::_5, SFloat::_3, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( ScaleWithPivot8_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( ScaleWithPivot8_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const ScalingMatrix3x3 SCALE(SFloat::_3, -SFloat::_2, -SFloat::_4);

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::ScaleWithPivot(SCALE, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot2_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)2.823223304703363,  SFloat::_4,  (float_z)-5.1767766952966365),
                                           Vector3((float_z)-9.59533953988538,  SFloat::_3,  (float_z)7.8605045828303322),
                                           Vector3((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2,    SFloat::_1,  SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1,   SFloat::_4,  SFloat::_0_5)
                               };

    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot2_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( TransformWithPivot2_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( TransformWithPivot2_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot3_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)2.823223304703363,  SFloat::_4,  (float_z)-5.1767766952966365, SFloat::_1),
                                           Vector4((float_z)-9.59533953988538,  SFloat::_3,  (float_z)7.8605045828303322,  SFloat::_1),
                                           Vector4((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot3_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( TransformWithPivot3_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( TransformWithPivot3_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pivot point's W component doesn't affect the result.
/// </summary>
ZTEST_CASE ( TransformWithPivot3_WComponentOfPivotDoesNotMatter_Test )
{
    // [Preparation]
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints1[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                };
    Vector4 arInputPoints2[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                };
    const Vector4 PIVOT1(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 PIVOT2(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT1, arInputPoints1, POINTS_COUNT);
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT2, arInputPoints2, POINTS_COUNT);

    // [Verification]
    BOOST_CHECK(arInputPoints1[0] == arInputPoints2[0]);
}

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot4_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)2.823223304703363,  SFloat::_4,  (float_z)-5.1767766952966365),
                                           Vector3((float_z)-9.59533953988538,  SFloat::_3,  (float_z)7.8605045828303322),
                                           Vector3((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);

    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(SFloat::_2, SFloat::_1, SFloat::_0),
                                   Vector3(SFloat::_0_25, -SFloat::_5, -SFloat::_1),
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot4_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector3 EXPECTED_POINTS[] = {
                                           Vector3((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector3);
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( TransformWithPivot4_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector3 ORIGINAL_POINTS[] = {
                                           Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3 arInputPoints[] = {
                                   Vector3(-SFloat::_1, SFloat::_4, SFloat::_0_5)
                               };
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( TransformWithPivot4_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector3* arInputPoints = null_z;
    const Vector3 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when using more than one point, they are all correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot5_MoreThanOnePointAreTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)2.823223304703363,  SFloat::_4,  (float_z)-5.1767766952966365, SFloat::_1),
                                           Vector4((float_z)-9.59533953988538,  SFloat::_3,  (float_z)7.8605045828303322,  SFloat::_1),
                                           Vector4((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);

    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1),
                                   Vector4(SFloat::_0_25, -SFloat::_5, -SFloat::_1, SFloat::_1),
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when using only one point, it's correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot5_OnlyOnePointIsTransformedCorrectly_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_POINTS[] = {
                                           Vector4((float_z)9.7175144212722024, (float_z)4.5, (float_z)-11.010407640085653, SFloat::_1)
                                       };
    const int POINTS_COUNT = sizeof(EXPECTED_POINTS) / sizeof(Vector4);
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == EXPECTED_POINTS[i]);
    }
}

/// <summary>
/// Checks that when the number of points is zero, no work is done on input array.
/// </summary>
ZTEST_CASE ( TransformWithPivot5_NoWorkIsDoneWhenInputNumberIsZero_Test )
{
    // [Preparation]
    const Vector4 ORIGINAL_POINTS[] = {
                                           Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                       };
    const int POINTS_COUNT = 0;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                               };
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);

    // [Verification]
    for(int i = 0; i < POINTS_COUNT; ++i)
    {
        BOOST_CHECK(arInputPoints[i] == ORIGINAL_POINTS[i]);
    }
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that when passing a null pointer as point array an assertion fails.
/// </summary>
ZTEST_CASE ( TransformWithPivot5_AssertionFailsWhenInputIsNull_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4* arInputPoints = null_z;
    const Vector4 PIVOT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPoint::TransformWithPivot(TRANSFORMATION, PIVOT, arInputPoints, POINTS_COUNT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the pivot point's W component doesn't affect the result.
/// </summary>
ZTEST_CASE ( TransformWithPivot5_WComponentOfPivotDoesNotMatter_Test )
{
    // [Preparation]
    const int POINTS_COUNT = 1;
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_90, SAngle::_180, SAngle::_45);
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
#endif
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);

    Vector4 arInputPoints1[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                };
    Vector4 arInputPoints2[] = {
                                   Vector4(-SFloat::_1, SFloat::_4, SFloat::_0_5, SFloat::_1)
                                };
    const Vector4 PIVOT1(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 PIVOT2(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT1, arInputPoints1, POINTS_COUNT);
    SPoint::TransformWithPivot(TRANSFORMATION, PIVOT2, arInputPoints2, POINTS_COUNT);

    // [Verification]
    BOOST_CHECK(arInputPoints1[0] == arInputPoints2[0]);
}

// End - Test Suite: SPoint
ZTEST_SUITE_END()
