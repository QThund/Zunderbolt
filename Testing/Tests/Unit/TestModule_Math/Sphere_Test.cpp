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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/Sphere.h"

#include "ZMath/SAngle.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Sphere_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> sphereUT;

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets sphere's center and radius properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

    const Sphere<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Sphere<T> sphereUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets sphere's center and radius properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

    const Orb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Sphere<T> sphereUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

	// [Execution]
    Sphere<T> sphereUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned sphere has not changed since the last time the test was executed.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetUnitSphere_ValueHasNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;

	// [Execution]
    Sphere<T> sphereUT = Sphere<T>::GetUnitSphere();

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a sphere is correctly assigned to another sphere.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_SphereIsAssignedProperlyToAnother_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_4;

    const Orb<T> OTHER_ORB = Orb<T>(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Sphere<T> sphereUT;
    sphereUT = OTHER_ORB;

    // [Verification]
    BOOST_CHECK(sphereUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(sphereUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_CommonSphereIsCorrectlyTranslatedWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const Vector3 TRANSLATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_SphereIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const Vector3 TRANSLATION = Vector3::GetNullVector();

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_CommonSphereIsCorrectlyTranslatedWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const float_z TRANSLATION_X = SFloat::_1;
    const float_z TRANSLATION_Y = SFloat::_2;
    const float_z TRANSLATION_Z = SFloat::_3;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_SphereIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const float_z TRANSLATION_X = SFloat::_0;
    const float_z TRANSLATION_Y = SFloat::_0;
    const float_z TRANSLATION_Z = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_SphereIsNotRotatedWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_SphereIsCorrectlyTransformedByCommonQuaternions_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Quaternion ROTATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_z)0.29289321881345243, (float_z)1.2928932188134525, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_SphereIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_CommonSphereIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const float_z RADIUS_SCALE = SFloat::_2;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the components of the scaling vector and the radius scale equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_SphereIsNotScaledWhenVectorComponentsAndRadiusScaleEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();
    const float_z RADIUS_SCALE = SFloat::_1;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z RADIUS = SFloat::_5;
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_CommonSphereIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;
    const float_z RADIUS_SCALE = SFloat::_2;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_SphereIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;
    const float_z RADIUS_SCALE = SFloat::_1;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonSphereIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const float_z RADIUS_SCALE = SFloat::_2;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the components of the scaling vector equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_SphereIsNotTranslatedWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();
    const float_z RADIUS_SCALE = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonSphereIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;
    const float_z RADIUS_SCALE = SFloat::_2;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_SphereIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;
    const float_z RADIUS_SCALE = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_SphereIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { 0.70710659f, -SFloat::_4, -2.1213202f, SFloat::_1 };
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_z)0.70710678118654768, -SFloat::_4, (float_z)-2.1213203435596428, SFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_SphereIsNotRotatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetIdentity();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_SphereIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not rotated when the rotation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_SphereIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Template method used by Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly translated using common translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_CommonSphereIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_SphereIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, RADIUS) );
}

/// <summary>
/// Checks that a sphere is not translated when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_SphereIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_CommonSphereIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);
    const float_z RADIUS_SCALE = SFloat::_2;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_SphereIsNotScaledWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const ScalingMatrix3x3 SCALE = Matrix3x3::GetIdentity();
    const float_z RADIUS_SCALE = SFloat::_1;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE = Matrix3x3::GetNullMatrix();
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Scale(SCALE, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonSphereIsCorrectlyScaledWhenUsingCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);
    const float_z RADIUS_SCALE = SFloat::_2;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_SphereIsNotTranslatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetIdentity();
    const float_z RADIUS_SCALE = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that the center of the sphere is moved to the position of the pivot point when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetNullMatrix();
    const float_z RADIUS_SCALE = SFloat::_0;

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.ScaleWithPivot(SCALE, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Template method used by Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const float_z RADIUS_SCALE = SFloat::_2;

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { (float_z)6.0658639918226491, SFloat::_8, (float_z)-10.419417382415922, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = T::GetNullVector();

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();
    const float_z RADIUS_SCALE = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
}

/// <summary>
/// Checks that all the center of the sphere is moved to the coordinate origin when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();
    const float_z RADIUS_SCALE = SFloat::_1;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(TRANSFORMATION, RADIUS_SCALE);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the sphere is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_SphereIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    const float_z CENTER_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(CENTER, RADIUS);

    const Sphere<T> EXPECTED_SPHERE = Sphere<T>(CENTER.Transform(CONVERSION),
                                                  RADIUS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Checks that the sphere doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_SphereDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix IDENTITY_MATRIX = SpaceConversionMatrix::GetIdentity();

	const float_z CENTER_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(CENTER, RADIUS);

    const Sphere<T> EXPECTED_SPHERE = SPHERE;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Checks that the sphere is nullified when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z CENTER_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T CENTER(CENTER_COMPONENTS);
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(CENTER, RADIUS);

    const Sphere<T> EXPECTED_SPHERE = Sphere<T>(T::GetNullVector(), RADIUS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(returnedSphere == EXPECTED_SPHERE);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);
    const float_z RADIUS_SCALE = SFloat::_2;

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_z EXPECTED_VECTOR_COMPONENTS_CENTER[] = { SFloat::_3, SFloat::_7, -SFloat::_3, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_CENTER(EXPECTED_VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_10;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a common sphere is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_CommonSphereIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_SphereVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_CENTER = PIVOT_POINT;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();
    const float_z RADIUS_SCALE = SFloat::_0;

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
}

/// <summary>
/// Checks that all the center of the sphere is moved to the position of the pivot point when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_SphereVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const T EXPECTED_VALUE_FOR_CENTER = SPHERE.Center;
    const float_z EXPECTED_VALUE_FOR_RADIUS = SPHERE.Radius;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();
    const float_z RADIUS_SCALE = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Sphere<T> returnedSphere = SPHERE.TransformWithPivot(TRANSFORMATION, RADIUS_SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedSphere.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK( SFloat::AreEqual(returnedSphere.Radius, EXPECTED_VALUE_FOR_RADIUS) );
}

/// <summary>
/// Checks that a sphere is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_SphereIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that it returns "negative side" when the sphere is "behind" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheSphereIsBehindPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //     ____        |
    //    /    \       |
    //   |      |      |-->
    //    \____/       |
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_1;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the sphere is "in front" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheSphereIsInFrontPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //    |         ____
    //    |        /    \
    //    |-->    |      |
    //    |        \____/
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_1;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the sphere intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheSphereIntersectsWithThePlane_Test, TTemplateTypes )
{
    //     |
    //   __|__
    //  /  |  \
    // |   |   |
    //  \__|__/
    //     |

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_10;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the sphere is "behind" the plane and is tangent to it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheSphereIsBehindPlaneAndIsTangentToPlane_Test, TTemplateTypes )
{
    //     ____ |
    //    /    \|
    //   |      |-->
    //    \____/|
    //          |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const float_z RADIUS = SFloat::_5;
    const Vector3 PLANE_TO_SPHERE = Vector3(PLANE.a, PLANE.b, PLANE.c) * RADIUS;

    const float_z VECTOR_COMPONENTS_CENTER[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER) - PLANE_TO_SPHERE, RADIUS);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the sphere is "in front" of the plane and is tangent to it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheSphereIsInFrontPlaneAndIsTangentToPlane_Test, TTemplateTypes )
{
    //    | ____
    //    |/    \
    //    |-->   |
    //    |\____/
    //    |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z RADIUS = SFloat::_5;
    const Vector3 PLANE_TO_SPHERE = Vector3(PLANE.a, PLANE.b, PLANE.c) * RADIUS;

    const float_z VECTOR_COMPONENTS_CENTER[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER) + PLANE_TO_SPHERE, RADIUS);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = SPHERE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    //     ____ |
    //    /    \|
    //   |      |-->
    //    \____/|
    //          |

    // [Preparation]
    const Plane NONNORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10);
    const Plane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_z RADIUS = SFloat::_5;
    const Vector3 PLANE_TO_SPHERE = Vector3(NORMALIZED_PLANE.a, NORMALIZED_PLANE.b, NORMALIZED_PLANE.c) * RADIUS;

    const float_z VECTOR_COMPONENTS_CENTER[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SFloat::_1 };
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER) - PLANE_TO_SPHERE, RADIUS);

	// [Execution]
    ESpaceRelation eResultNonNotmalized = SPHERE.SpaceRelation(NONNORMALIZED_PLANE);
    ESpaceRelation eResultNormalized = SPHERE.SpaceRelation(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK(eResultNonNotmalized == eResultNormalized);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.SpaceRelation(NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the radius equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenRadiusEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_0;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const BasePlane PLANE = BasePlane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.SpaceRelation(PLANE);
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
/// Checks that the sphere is correctly projected to the plane when it is in its negative side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIsInNegativeSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_5, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_COMPONENTS_CENTER[] = { (float_z)1.8095238095238098, (float_z)-3.3809523809523805, (float_z)6.238095238095239, SFloat::_1 };

    const Sphere<T> EXPECTED_SPHERE = Sphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

	// [Execution]
    Sphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the sphere is correctly projected to the plane when it is in its positive side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIsInPositiveSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_COMPONENTS_CENTER[] = { (float_z)-0.28571428571428581, (float_z)-5.5714285714285712, (float_z)-2.1428571428571432, SFloat::_1 };
    const Sphere<T> EXPECTED_SPHERE = Sphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_10).Normalize();

	// [Execution]
    Sphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the sphere is correctly projected to the plane when it intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_SphereIsProjectedWhenItIntersectsWithPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const float_z EXPECTED_COMPONENTS_CENTER[] = { SFloat::_0, -SFloat::_5, SFloat::_0, SFloat::_1 };
    const Sphere<T> EXPECTED_SPHERE = Sphere<T>(T(EXPECTED_COMPONENTS_CENTER), RADIUS);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

	// [Execution]
    Sphere<T> projectedSphere = SPHERE.ProjectToPlane(PLANE);

    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedSphere.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedSphere.Center == EXPECTED_SPHERE.Center);
    BOOST_CHECK(projectedSphere.Radius == EXPECTED_SPHERE.Radius);
}

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( ProjectToPlane_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane NONNORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10);
    const Plane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

	// [Execution]
    Sphere<T> resultNonNotmalized = SPHERE.ProjectToPlane(NONNORMALIZED_PLANE);
    Sphere<T> resultNormalized = SPHERE.ProjectToPlane(NORMALIZED_PLANE);

    // [Verification]
    BOOST_CHECK(resultNonNotmalized != resultNormalized);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE( ProjectToPlane_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z RADIUS = SFloat::_5;
    const Sphere<T> SPHERE = Sphere<T>(T(VECTOR_COMPONENTS_CENTER), RADIUS);

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SPHERE.ProjectToPlane(NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: Sphere
ZTEST_SUITE_END()
