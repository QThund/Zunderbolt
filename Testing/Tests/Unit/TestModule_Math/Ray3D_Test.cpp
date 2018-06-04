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

#include "ZMath/Ray3D.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Quaternion.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"
#include "ZMath/SAngle.h"
using namespace z::Internals;

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Ray3D_TestSuite )

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

    Ray3D<T> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray3D<T> rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

    Ray<T, Vector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray3D<T> rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

	// [Execution]
    Ray3D<T> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T INPUT_VALUE_FOR_ORIGIN = T(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 INPUT_VALUE_FOR_DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

    const Vector3 UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    Ray3D<T> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns a null ray placed at the origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNullRay_ReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    Ray3D<T> EXPECTED_VALUE(T::GetNullVector(), Vector3::GetNullVector());

	// [Execution]
    Ray3D<T> obtinedRay = Ray3D<T>::GetNullRay();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to X axis and points to positive direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRayX_ReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    Ray3D<T> EXPECTED_VALUE(T::GetNullVector(), Vector3::GetUnitVectorX());

	// [Execution]
    Ray3D<T> obtinedRay = Ray3D<T>::GetRayX();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to Y axis and points to positive direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRayY_ReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    Ray3D<T> EXPECTED_VALUE(T::GetNullVector(), Vector3::GetUnitVectorY());

	// [Execution]
    Ray3D<T> obtinedRay = Ray3D<T>::GetRayY();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to Z axis and points to positive direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRayZ_ReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    Ray3D<T> EXPECTED_VALUE(T::GetNullVector(), Vector3::GetUnitVectorZ());

	// [Execution]
    Ray3D<T> obtinedRay = Ray3D<T>::GetRayZ();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that a ray is correctly assigned to another ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_RayIsAssignedProperlyToAnother_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> OTHER_RAY = Ray3D<T>(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray3D<T> rayUT;
    rayUT = OTHER_RAY;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns True when a common ray and a common plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenCommonRayIntersectWithCommonPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when ray and plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsFalseWhenRayIsParallelToPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_2, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is contained in the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenRayIsContainedInPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_2, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the plane but would do it if the ray was pointing to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsFalseWhenRayDoesNotIntersectWithPlaneButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only the origin of the ray belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenOnlyOriginBelongsToPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();
    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_2, -SFloat::_3);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_5, SFloat::_6, SFloat::_7).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
/*
/// <summary>
/// Checks that it returns True when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenCommonRayIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenRayIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();

    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);

    const float_z ORIGIN_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_1 };
    const T ORIGIN3(ORIGIN_COMPONENTS3);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = RAY1.Intersection(TRIANGLE);
    bool bIntersectsWithB = RAY2.Intersection(TRIANGLE);
    bool bIntersectsWithC = RAY3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsFalseWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = -Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenOriginIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN = VERTEX_B + (VERTEX_A - VERTEX_B) * SFloat::_0_5 + (VERTEX_C - VERTEX_B) * SFloat::_0_5;
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenRayBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN = VERTEX_B + (VERTEX_A - VERTEX_B) * SFloat::_0_5 + (VERTEX_C - VERTEX_B) * SFloat::_0_5;
    const Vector3 DIRECTION = Vector3(VERTEX_A - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenOriginBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const T ORIGIN1 = VERTEX_B + (VERTEX_A - VERTEX_B) * SFloat::_0_5;
    const T ORIGIN2 = VERTEX_C + (VERTEX_A - VERTEX_C) * SFloat::_0_5;
    const T ORIGIN3 = VERTEX_B + (VERTEX_C - VERTEX_B) * SFloat::_0_5;
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bOriginContainedInAB = RAY1.Intersection(TRIANGLE);
    bool bOriginContainedInAC = RAY2.Intersection(TRIANGLE);
    bool bOriginContainedInBC = RAY3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInBC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenRayIntersectsEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const T ORIGIN1 = VERTEX_B + (VERTEX_A - VERTEX_B) * SFloat::_0_5 - DIRECTION;
    const T ORIGIN2 = VERTEX_C + (VERTEX_A - VERTEX_C) * SFloat::_0_5 - DIRECTION;
    const T ORIGIN3 = VERTEX_B + (VERTEX_C - VERTEX_B) * SFloat::_0_5 - DIRECTION;
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = RAY1.Intersection(TRIANGLE);
    bool bIntersectsWithAC = RAY2.Intersection(TRIANGLE);
    bool bIntersectsWithBC = RAY3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ReturnsTrueWhenOriginAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VERTEX_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VERTEX_B, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(VERTEX_C, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bOriginAndACoincide = RAY1.Intersection(TRIANGLE);
    bool bOriginAndBCoincide = RAY2.Intersection(TRIANGLE);
    bool bOriginAndCCoincide = RAY3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bOriginAndACoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndBCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndCCoincide, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(TRIANGLE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection4_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(TRIANGLE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS
*/
/// <summary>
/// Checks that it returns one intersection point when a common ray and a common plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenCommonRayIntersectWithCommonPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const float_z EXPECTED_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_0 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersections when ray and plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayIsParallelToPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_2, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the ray is contained in the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsInfiniteIntersectionsWhenRayIsContainedInPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_2, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersections when the ray doesn't intersect with the plane but would do it if the ray was pointing to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithPlaneButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when only the origin of the ray belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOriginBelongsToPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();
    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const T EXPECTED_POINT = ORIGIN;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const float_z EXPECTED_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_0 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(PLANE, vIntersection);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_5, SFloat::_6, SFloat::_7).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(PLANE, vIntersection);
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
/// Checks that the W component of the intersection point is not changed.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_WComponentOfIntersectionPointDoesNotChange_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const Vector4 EXPECTED_POINT = Vector4(PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_0);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_0 };
    const Vector4 ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(ORIGIN, DIRECTION);

    const float_z EXPECTED_WCOMPONENT = SFloat::_5;

	// [Execution]
    Vector4 vIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_WCOMPONENT);
    RAY.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_WCOMPONENT);
}
/*
/// <summary>
/// Checks that it returns one intersection point when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionPointWhenCommonRayIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();

    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_0 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);

    const float_z ORIGIN_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_0 };
    const T ORIGIN3(ORIGIN_COMPONENTS3);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_A = VERTEX_A;
    const T EXPECTED_POINT_B = VERTEX_B;
    const T EXPECTED_POINT_C = VERTEX_C;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    T vIntersectionC;
    EIntersections eIntersectionsWithA = RAY1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EIntersections eIntersectionsWithB = RAY2.IntersectionPoint(TRIANGLE, vIntersectionB);
    EIntersections eIntersectionsWithC = RAY3.IntersectionPoint(TRIANGLE, vIntersectionC);

    // [Verification]
    BOOST_CHECK(eIntersectionsWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithC == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
}

/// <summary>
/// Checks that it returns no intersections when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = -Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOriginIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = ORIGIN;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T EXPECTED_POINT = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SFloat::_0_25;
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT1 = ORIGIN1;
    const T EXPECTED_POINT2 = ORIGIN2;
    const T EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection1;
    T vIntersection2;
    T vIntersection3;
    EIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EIntersections eOriginContainedInAC = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EIntersections eOriginContainedInBC = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);

    // [Verification]
    BOOST_CHECK(eOriginContainedInAB == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInAC == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInBC == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the triangle and the direction vector points to another edge.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION1 = Vector3(ORIGIN2 - ORIGIN1).Normalize();
    const Vector3 DIRECTION2 = Vector3(ORIGIN3 - ORIGIN2).Normalize();
    const Vector3 DIRECTION3 = Vector3(ORIGIN1 - ORIGIN3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT1 = ORIGIN1;
    const T EXPECTED_POINT2 = ORIGIN2;
    const T EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersection1;
    T vIntersection2;
    T vIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns one intersection when the ray intersects with an one edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayIntersectsOneEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - DIRECTION;
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C) - DIRECTION;
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - DIRECTION;
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection1;
    T vIntersection2;
    T vIntersection3;
    EIntersections eIntersectsWithAB = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EIntersections eIntersectsWithAC = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EIntersections eIntersectsWithBC = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VERTEX_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VERTEX_B, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(VERTEX_C, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT1 = VERTEX_A;
    const T EXPECTED_POINT2 = VERTEX_B;
    const T EXPECTED_POINT3 = VERTEX_C;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection1;
    T vIntersection2;
    T vIntersection3;
    EIntersections eOriginAndACoincide = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EIntersections eOriginAndBCoincide = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EIntersections eOriginAndCCoincide = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);

    // [Verification]
    BOOST_CHECK(eOriginAndACoincide == EXPECTED_RESULT);
    BOOST_CHECK(eOriginAndBCoincide == EXPECTED_RESULT);
    BOOST_CHECK(eOriginAndCCoincide == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection);
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
/// Checks that it returns the closest of the two intersection points.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTheClosestPointWhenIntersectingWithTwoEdges_Test, TTemplateTypes )
{
    //       Y
    //       |
    //      /|\
    //  <--/-|-x-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { -SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T ORIGIN = T(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetUnitVectorInvX();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK( SFloat::IsGreaterOrEquals(vIntersection.x, SFloat::_0) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectWithTwoEdges_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T EXPECTED_POINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector3 DIRECTION1 = Vector3(EXPECTED_POINT2 - EXPECTED_POINT1).Normalize();
    const Vector3 DIRECTION2 = Vector3(EXPECTED_POINT3 - EXPECTED_POINT2).Normalize();
    const Vector3 DIRECTION3 = Vector3(EXPECTED_POINT1 - EXPECTED_POINT3).Normalize();

    T ORIGIN1 = EXPECTED_POINT1 - T(DIRECTION1);
    T ORIGIN2 = EXPECTED_POINT2 - T(DIRECTION2);
    T ORIGIN3 = EXPECTED_POINT3 - T(DIRECTION3);

    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersection1;
    T vIntersection2;
    T vIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
    BOOST_CHECK(vIntersection3 == EXPECTED_POINT3);
}

/// <summary>
/// Checks that the W component of the output intersection point is not changed.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_WComponentOfIntersectionPointIsNotChanged_Test )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const Vector4 VERTEX_A = Vector4(VERTEX_A_COMPONENTS);
    const Vector4 VERTEX_B = Vector4(VERTEX_B_COMPONENTS);
    const Vector4 VERTEX_C = Vector4(VERTEX_C_COMPONENTS);

    const Triangle<Vector4> TRIANGLE = Triangle<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector4 INTERSECTION_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const Vector4 ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(INTERSECTION_POINT - ORIGIN).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(ORIGIN, DIRECTION);

    const float_z EXPECTED_WCOMPONENT = SFloat::_5;

	// [Execution]
    Vector4 vIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_WCOMPONENT);
    RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_WCOMPONENT);
}

/// <summary>
/// Checks that it returns two intersections when the ray belongs to one edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayBelongsToAnEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION1 = Vector3(VERTEX_A - VERTEX_B).Normalize();
    const Vector3 DIRECTION2 = Vector3(VERTEX_C - VERTEX_A).Normalize();
    const Vector3 DIRECTION3 = Vector3(VERTEX_B - VERTEX_C).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    EIntersections eIntersectsWithAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1);
    EIntersections eIntersectsWithAC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2);
    EIntersections eIntersectsWithBC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionPointWhenCommonRayIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();

    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_0 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);

    const float_z ORIGIN_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_0 };
    const T ORIGIN3(ORIGIN_COMPONENTS3);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vSecondIntersectionA;
    T vSecondIntersectionB;
    T vSecondIntersectionC;
    EIntersections eIntersectionsWithA = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eIntersectionsWithB = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eIntersectionsWithC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersectionC, vSecondIntersectionC);

    // [Verification]
    BOOST_CHECK(eIntersectionsWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when a common ray and a common triangle would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = -Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenOriginIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = ORIGIN;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T EXPECTED_FIRSTPOINT = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SFloat::_0_25;
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection intersection when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const T EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const T EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection1;
    T vSecondIntersection2;
    T vSecondIntersection3;
    EIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eOriginContainedInAC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eOriginContainedInBC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eOriginContainedInAB == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInAC == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInBC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the triangle and the direction vector points to another edge.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION1 = Vector3(ORIGIN2 - ORIGIN1).Normalize();
    const Vector3 DIRECTION2 = Vector3(ORIGIN3 - ORIGIN2).Normalize();
    const Vector3 DIRECTION3 = Vector3(ORIGIN1 - ORIGIN3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const T EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const T EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const T EXPECTED_SECONDPOINT1 = ORIGIN2;
    const T EXPECTED_SECONDPOINT2 = ORIGIN3;
    const T EXPECTED_SECONDPOINT3 = ORIGIN1;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    // [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection1;
    T vSecondIntersection2;
    T vSecondIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that it returns one intersection when the ray intersects with an one edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayIntersectsOneEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - DIRECTION;
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C) - DIRECTION;
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - DIRECTION;
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection1;
    T vSecondIntersection2;
    T vSecondIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VERTEX_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VERTEX_B, DIRECTION);
    const Ray3D<T> RAY3 = Ray3D<T>(VERTEX_C, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = VERTEX_A;
    const T EXPECTED_FIRSTPOINT2 = VERTEX_B;
    const T EXPECTED_FIRSTPOINT3 = VERTEX_C;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection1;
    T vSecondIntersection2;
    T vSecondIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection, vIntersection);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        RAY.IntersectionPoint(TRIANGLE, vIntersection, vIntersection);
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
/// Checks that it returns the closest of the two intersection points.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsTheClosestPointInFirstParameterWhenIntersectingWithTwoEdges_Test, TTemplateTypes )
{
    //       Y
    //       |
    //      /|\
    //  <--2-|-1-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { -SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T ORIGIN = T(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetUnitVectorInvX();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK( SFloat::IsGreaterOrEquals(vFirstIntersection.x, SFloat::_0) );
    BOOST_CHECK( SFloat::IsNegative(vSecondIntersection.x) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsTwoIntersectionsWhenRayIntersectWithTwoEdges_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT1 = EXPECTED_FIRSTPOINT2;
    const T EXPECTED_SECONDPOINT2 = EXPECTED_FIRSTPOINT3;
    const T EXPECTED_SECONDPOINT3 = EXPECTED_FIRSTPOINT1;

    const Vector3 DIRECTION1 = Vector3(EXPECTED_FIRSTPOINT2 - EXPECTED_FIRSTPOINT1).Normalize();
    const Vector3 DIRECTION2 = Vector3(EXPECTED_FIRSTPOINT3 - EXPECTED_FIRSTPOINT2).Normalize();
    const Vector3 DIRECTION3 = Vector3(EXPECTED_FIRSTPOINT1 - EXPECTED_FIRSTPOINT3).Normalize();

    T ORIGIN1 = EXPECTED_FIRSTPOINT1 - T(DIRECTION1);
    T ORIGIN2 = EXPECTED_FIRSTPOINT2 - T(DIRECTION2);
    T ORIGIN3 = EXPECTED_FIRSTPOINT3 - T(DIRECTION3);

    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection1;
    T vSecondIntersection2;
    T vSecondIntersection3;
    EIntersections eResult1 = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResult2 = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eResult3 = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}

/// <summary>
/// Checks that the intersection is returned using the first output parameter when only one intersection is detected.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_IntersectionIsReturnedInFirstParameterWhenThereIsOnlyOneIntersection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 DIRECTION = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - DIRECTION;
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection != EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that W component of both output points does not change when 2 intersections are detected.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_WComponentDoesNotChangeWhenTwoIntersectionsAreDetected_Test )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const Vector4 VERTEX_A = Vector4(VERTEX_A_COMPONENTS);
    const Vector4 VERTEX_B = Vector4(VERTEX_B_COMPONENTS);
    const Vector4 VERTEX_C = Vector4(VERTEX_C_COMPONENTS);

    const Vector4 INTERSECTION_POINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector4 INTERSECTION_POINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector3 DIRECTION = Vector3(INTERSECTION_POINT2 - INTERSECTION_POINT1).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(INTERSECTION_POINT1, DIRECTION);

    const Triangle<Vector4> TRIANGLE = Triangle<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C);

    const float_z EXPECTED_FIRST_WCOMPONENT = SFloat::_5;
    const float_z EXPECTED_SECOND_WCOMPONENT = SFloat::_6;

    // [Execution]
    Vector4 vFirstIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_FIRST_WCOMPONENT);
    Vector4 vSecondIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_SECOND_WCOMPONENT);
    RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(vFirstIntersection.w == EXPECTED_FIRST_WCOMPONENT);
    BOOST_CHECK(vSecondIntersection.w == EXPECTED_SECOND_WCOMPONENT);
}

/// <summary>
/// Checks that it returns the farthest intersection point when using the same instance of the point as both output parameters.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsFarthestIntersectionWhenUsingSameObjectAsBothOutputPoints_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T INTERSECTION1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T INTERSECTION2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector3 DIRECTION = Vector3(INTERSECTION2 - INTERSECTION1).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(INTERSECTION1, DIRECTION);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = INTERSECTION2;

    // [Execution]
    T vSameIntersection;
    RAY.IntersectionPoint(TRIANGLE, vSameIntersection, vSameIntersection);

    // [Verification]
    BOOST_CHECK(vSameIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersections when the ray belongs to one edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint6_ReturnsTwoIntersectionsWhenRayBelongsToAnEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION1 = Vector3(VERTEX_A - VERTEX_B).Normalize();
    const Vector3 DIRECTION2 = Vector3(VERTEX_C - VERTEX_A).Normalize();
    const Vector3 DIRECTION3 = Vector3(VERTEX_B - VERTEX_C).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const Triangle<T> TRIANGLE = Triangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_SECONDPOINT1 = VERTEX_A;
    const T EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT2 = VERTEX_C;
    const T EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT3 = VERTEX_B;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersection1;
    T vSecondIntersection1;
    T vFirstIntersection2;
    T vSecondIntersection2;
    T vFirstIntersection3;
    T vSecondIntersection3;
    EIntersections eIntersectsWithAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eIntersectsWithAC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eIntersectsWithBC = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}
*/

/// <summary>
/// Checks that it returns "negative side" when the ray is "behind" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheRayIsBehindPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //     O   |
    //    /    |
    //   /     |-->
    //  v      |
    //

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the ray is "behind" the plane and they are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheRayIsBehindPlaneAndTheyAreParallel_Test, TTemplateTypes )
{
    //  O    |
    //  |    |
    //  |    |-->
    //  v    |
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(PLANE.a, PLANE.b, PLANE.c).CrossProduct(Vector3::GetUnitVectorX()).Normalize(); // Orthogonal to plane's normal
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the ray is "in front" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheRayIsInFrontPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //     |       O
    //     |        \
    //     |-->      \
    //     |          v
    //

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the ray is "in front" the plane and they are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheRayIsInFrontPlaneAndTheyAreParallel_Test, TTemplateTypes )
{
    //     |       O
    //     |       |
    //     |-->    |
    //     |       v
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(PLANE.a, PLANE.b, PLANE.c).CrossProduct(Vector3::GetUnitVectorX()).Normalize(); // Orthogonal to plane's normal
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the ray is "behind" the plane and intersects with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheRayIsBehindPlaneAndTheyIntersect_Test, TTemplateTypes )
{
    //  O  |
    //   \ |
    //    \|
    //     |-->
    //     |\
    //     | v

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the ray is "in front" the plane and intersects with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheRayIsInFrontPlaneAndTheyIntersect_Test, TTemplateTypes )
{
    //     |  O
    //     | /
    //     |/
    //     |-->
    //    /|
    //   v |

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the ray belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsContainedWhenTheRayBelongsToPlane_Test, TTemplateTypes )
{
    //       |
    //       O
    //       |
    //       |-->
    //       |
    //       v
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 }; // Point contained in the plane
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(PLANE.a, PLANE.b, PLANE.c).CrossProduct(Vector3::GetUnitVectorX()).Normalize(); // Orthogonal to plane's normal
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the origin of the ray belongs to the plane and the ray points towards the positive side.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheRayOriginBelongsToPlaneAndPointsTowardsPositiveSide_Test, TTemplateTypes )
{
    //       |
    //       O
    //       |\
    //       | \
    //       |->\
    //       |   v
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 }; // Point contained in the plane
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(PLANE.a, PLANE.b, PLANE.c);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the origin of the ray belongs to the plane and the ray points towards the negative side.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheRayOriginBelongsToPlaneAndPointsTowardsNegativeSide_Test, TTemplateTypes )
{
    //       |
    //       O
    //      /|
    //     / |
    //    /  |-->
    //   v   |
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z ORIGIN_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 }; // Point contained in the plane
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = -Vector3(PLANE.a, PLANE.b, PLANE.c);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = RAY.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenRayIsNull_Test, TTemplateTypes )
{
    //       |
    //       O    D = 0
    //       |
    //       |
    //       |->
    //       |
    //


    // [Preparation]
    const Ray3D<T> RAY = Ray3D<T>::GetNullRay();
    const Plane PLANE = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.SpaceRelation(PLANE);
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
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane PLANE_NORMALIZED = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE_NOTNORMALIZED = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    ESpaceRelation eResult1 = RAY.SpaceRelation(PLANE_NORMALIZED);
    ESpaceRelation eResult2 = RAY.SpaceRelation(PLANE_NOTNORMALIZED);

    // [Verification]
    BOOST_CHECK(eResult1 == eResult2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.SpaceRelation(NULL_PLANE);
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
/// Checks that the ray is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_RayIsCorrectlyTransformedByCommonQuaternion_Test, TTemplateTypes )
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

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Quaternion TRANSFORMATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN.Transform(TRANSFORMATION),
                                             DIRECTION.Transform(TRANSFORMATION));

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_RayDoesNotChangeWhenTransformedByIdentityQuaternion_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion UNIT_QUATERNION = Quaternion::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(UNIT_QUATERNION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is nullified when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_OriginAndDirectionAreNullifiedWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>::GetNullRay();

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(NULL_QUATERNION);

    // [Verification]
    BOOST_CHECK(ray.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivotWithPivot1_RayIsCorrectlyTransformedByCommonQuaternion_Test, TTemplateTypes )
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

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);
    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Quaternion TRANSFORMATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                             DIRECTION.Transform(TRANSFORMATION));

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivotWithPivot1_RayDoesNotChangeWhenTransformedByIdentityQuaternion_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion UNIT_QUATERNION = Quaternion::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(UNIT_QUATERNION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is nulled when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivotWithPivot1_OriginAndDirectionAreNullifiedWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>::GetNullRay();

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(NULL_QUATERNION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_RayIsCorrectlyTransformedByCommonTranslationVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Vector3 TRANSFORMATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN + TRANSFORMATION,
                                             DIRECTION);

	// [Execution]
    Ray3D<T> ray = RAY.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an null translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_RayDoesNotChangeWhenTransformedByNullVector_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Translate(NULL_VECTOR);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is correctly transformed by arbitrary translation values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_RayIsCorrectlyTransformedByCommonTranslationVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z TRANSLATION_VALUE_X = SFloat::_1;
    const float_z TRANSLATION_VALUE_Y = SFloat::_2;
    const float_z TRANSLATION_VALUE_Z = SFloat::_3;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN + Vector3(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y, TRANSLATION_VALUE_Z),
                                             DIRECTION);

	// [Execution]
    Ray3D<T> ray = RAY.Translate(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y, TRANSLATION_VALUE_Z);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by translation values that equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_RayDoesNotChangeWhenTransformedByNullValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ZERO_VALUE = SFloat::_0;

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Translate(ZERO_VALUE, ZERO_VALUE, ZERO_VALUE);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_RayIsCorrectlyTransformedByCommonScalingVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z TRANSFORMATION_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const Vector3 TRANSFORMATION = Vector3(TRANSFORMATION_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(TRANSFORMATION_COMPONENTS),
                                             (DIRECTION * TRANSFORMATION).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_RayDoesNotChangeWhenTransformedByVectorOfOnes_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 VECTOR_OF_ONES = Vector3::GetVectorOfOnes();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Scale(VECTOR_OF_ONES);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by an null scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_AssertionFailsWhenTransformedByNullScalingVector_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(NULL_VECTOR);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Vector3 TRANSFORMATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(TRANSFORMATION),
                                             (DIRECTION * TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by arbitrary scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_RayIsCorrectlyTransformedByCommonScalingValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z SCALING_VALUE_X = SFloat::_1;
    const float_z SCALING_VALUE_Y = SFloat::_2;
    const float_z SCALING_VALUE_Z = SFloat::_3;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.Scale(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by scaling values that equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_RayDoesNotChangeWhenTransformedByScalingValuesThatEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ONE_VALUE = SFloat::_1;

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Scale(ONE_VALUE, ONE_VALUE, ONE_VALUE);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed scaling values that equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_AssertionFailsWhenTransformedByScalingValuesThatEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ZERO_VALUE = SFloat::_0;

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(ZERO_VALUE, ZERO_VALUE, ZERO_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Create this test when assertions can be disabled -> Scale2_RayIsNullifiedWhenTransformedByScalingValuesThatEqualZero_Test

/// <summary>
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z SCALING_VALUE_X = SFloat::_1;
    const float_z SCALING_VALUE_Y = SFloat::_2;
    const float_z SCALING_VALUE_Z = SFloat::_3;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.Scale(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_RayIsCorrectlyTransformedByCommonScalingVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Vector3 TRANSFORMATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT) * T(TRANSFORMATION) + PIVOT,
                                             (DIRECTION * TRANSFORMATION).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_RayDoesNotChangeWhenTransformedByVectorOfOnes_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 VECTOR_OF_ONES = Vector3::GetVectorOfOnes();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(VECTOR_OF_ONES, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by an null scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_AssertionFailsWhenTransformedByNullScalingVector_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(NULL_VECTOR, PIVOT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Create this test when assertions can be disabled -> ScaleWithPivot1_RayIsNullifiedWhenTransformedByNullScalingVector_Test

/// <summary>
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Vector3 TRANSFORMATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(TRANSFORMATION),
                                             (DIRECTION * TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by arbitrary scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_RayIsCorrectlyTransformedByCommonScalingValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z SCALING_VALUE_X = SFloat::_1;
    const float_z SCALING_VALUE_Y = SFloat::_2;
    const float_z SCALING_VALUE_Z = SFloat::_3;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT) * T(Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)) + PIVOT,
                                             (DIRECTION * Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by scaling values that equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_RayDoesNotChangeWhenTransformedByVectorOfOnes_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ONE_VALUE = SFloat::_1;

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(ONE_VALUE, ONE_VALUE, ONE_VALUE, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed scaling values that equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_AssertionFailsWhenTransformedByNullScalingVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ZERO_VALUE = SFloat::_0;

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(ZERO_VALUE, ZERO_VALUE, ZERO_VALUE, PIVOT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Create this test when assertions can be disabled -> ScaleWithPivot2_RayIsNullifiedWhenTransformedByNullScalingVector_Test

/// <summary>
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z SCALING_VALUE_X = SFloat::_1;
    const float_z SCALING_VALUE_Y = SFloat::_2;
    const float_z SCALING_VALUE_Z = SFloat::_3;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * Vector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_RayIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN.Transform(TRANSFORMATION),
                                             DIRECTION.Transform(TRANSFORMATION));

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 IDENTITY_MATRIX = RotationMatrix3x3::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is nullified when the rotation matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_OriginAndDirectionAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>::GetNullRay();

	// [Execution]
    Ray3D<T> ray = RAY.Rotate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(ray.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_RayIsCorrectlyTransformedByCommonTranslationVector_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TranslationMatrix<Matrix4x3> TRANSFORMATION = TranslationMatrix<Matrix4x3>(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN.Transform(TRANSFORMATION),
                                             DIRECTION);

	// [Execution]
    Ray3D<T> ray = RAY.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by a null translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_RayDoesNotChangeWhenTransformedByNullVector_Test, TTemplateTypes )
{

    // [Preparation]
    const TranslationMatrix<Matrix4x3> NULL_MATRIX = Matrix4x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Translate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate4_RayIsCorrectlyTransformedByCommonTranslationMatrix_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TranslationMatrix<Matrix4x4> TRANSFORMATION = TranslationMatrix<Matrix4x4>(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN.Transform(TRANSFORMATION),
                                             DIRECTION);

	// [Execution]
    Ray3D<T> ray = RAY.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by a null translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate4_RayDoesNotChangeWhenTransformedByNullMatrix_Test, TTemplateTypes )
{

    // [Preparation]
    const TranslationMatrix<Matrix4x4> NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Translate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by a identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate4_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{

    // [Preparation]
    const TranslationMatrix<Matrix4x4> IDENTITY_MATRIX = Matrix4x4::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Translate(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_RayIsCorrectlyTransformedByCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(TRANSFORMATION).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 IDENTITY_MATRIX = ScalingMatrix3x3::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Scale(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by an null scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_AssertionFailsWhenTransformedByNullScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(NULL_MATRIX);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_RayIsCorrectlyTransformedByCommonTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x3> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x3>(Matrix4x3::GetIdentity(), ROTATION, SCALE);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION).Normalize()); // Without translation

	// [Execution]
    Ray3D<T> ray = RAY.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> IDENTITY_MATRIX = TransformationMatrix<Matrix4x3>::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by a null transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_AssertionFailsWhenTransformedByNullTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> NULL_MATRIX = Matrix4x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Transform(NULL_MATRIX);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x3> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x3>(Matrix4x3::GetIdentity(), ROTATION, SCALE);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_RayIsCorrectlyTransformedByCommonTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x4> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x4>(Matrix4x4::GetIdentity(), ROTATION, SCALE);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION).Normalize()); // Without translation

	// [Execution]
    Ray3D<T> ray = RAY.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> IDENTITY_MATRIX = TransformationMatrix<Matrix4x4>::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by a zero transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_AssertionFailsWhenTransformedByNullTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Transform(NULL_MATRIX);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x4> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x4>(Matrix4x4::GetIdentity(), ROTATION, SCALE);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN.Transform(TRANSFORMATION),
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform3_RayIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN.Transform(CONVERSION),
                                             DIRECTION.Transform(CONVERSION));

	// [Execution]
    Ray3D<T> ray = RAY.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform3_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix IDENTITY_MATRIX = SpaceConversionMatrix::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

	// [Execution]
    Ray3D<T> ray = RAY.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is nullified when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform3_OriginAndDirectionAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>::GetNullRay();

	// [Execution]
    Ray3D<T> ray = RAY.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_RayIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                             DIRECTION.Transform(TRANSFORMATION));

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 IDENTITY_MATRIX = RotationMatrix3x3::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(IDENTITY_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray is nullified when the rotation matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_OriginAndDirectionAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>::GetNullRay();

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.RotateWithPivot(NULL_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_RayIsCorrectlyTransformedByCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                              DIRECTION.Transform(TRANSFORMATION).Normalize());

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 IDENTITY_MATRIX = ScalingMatrix3x3::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(IDENTITY_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by an null scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_AssertionFailsWhenTransformedByZeroScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(NULL_MATRIX, PIVOT);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                              DIRECTION.Transform(TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.ScaleWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot1_RayIsCorrectlyTransformedByCommonTransformWithPivotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x3> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x3>(Matrix4x3::GetIdentity(), ROTATION, SCALE);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    T EXPECTED_ORIGIN = ORIGIN;
    EXPECTED_ORIGIN.x -= PIVOT.x;
    EXPECTED_ORIGIN.y -= PIVOT.y;
    EXPECTED_ORIGIN.z -= PIVOT.z;
    EXPECTED_ORIGIN = EXPECTED_ORIGIN.Transform(TRANSFORMATION);
    EXPECTED_ORIGIN.x += PIVOT.x;
    EXPECTED_ORIGIN.y += PIVOT.y;
    EXPECTED_ORIGIN.z += PIVOT.z;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(EXPECTED_ORIGIN,
                                             DIRECTION.Transform(DIRECTION_TRANSFORMATION).Normalize()); // Without translation

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot1_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> IDENTITY_MATRIX = TransformationMatrix<Matrix4x3>::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(IDENTITY_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by a null translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot1_AssertionFailsWhenTransformedByNullTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> NULL_MATRIX = Matrix4x3::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.TransformWithPivot(NULL_MATRIX, PIVOT);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot1_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION = TranslationMatrix<Matrix4x3>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x3> TRANSFORMATION = TransformationMatrix<Matrix4x3>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x3> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x3>(Matrix4x3::GetIdentity(), ROTATION, SCALE);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

/// <summary>
/// Checks that the ray is correctly transformed by an arbitrary transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot2_RayIsCorrectlyTransformedByCommonTransformWithPivotationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x4> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x4>(Matrix4x4::GetIdentity(), ROTATION, SCALE);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    T EXPECTED_ORIGIN = ORIGIN;
    EXPECTED_ORIGIN.x -= PIVOT.x;
    EXPECTED_ORIGIN.y -= PIVOT.y;
    EXPECTED_ORIGIN.z -= PIVOT.z;
    EXPECTED_ORIGIN = EXPECTED_ORIGIN.Transform(TRANSFORMATION);
    EXPECTED_ORIGIN.x += PIVOT.x;
    EXPECTED_ORIGIN.y += PIVOT.y;
    EXPECTED_ORIGIN.z += PIVOT.z;

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(EXPECTED_ORIGIN,
                                             DIRECTION.Transform(DIRECTION_TRANSFORMATION).Normalize()); // Without translation

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot2_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> IDENTITY_MATRIX = TransformationMatrix<Matrix4x4>::GetIdentity();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const Ray3D<T> EXPECTED_RAY = RAY;

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(IDENTITY_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(ray == EXPECTED_RAY);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the ray is nullified when it's transformed by a null translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot2_AssertionFailsWhenTransformedByNullTransformationMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.TransformWithPivot(NULL_MATRIX, PIVOT);
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
/// Checks that the result of the operation is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot2_ResultantRayIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION = TranslationMatrix<Matrix4x4>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(SAngle::_HalfPi, SAngle::_Pi, SAngle::_QuarterPi);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, SFloat::_5, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = TransformationMatrix<Matrix4x4>(TRANSLATION, ROTATION, SCALE);
    const TransformationMatrix<Matrix4x4> DIRECTION_TRANSFORMATION = TransformationMatrix<Matrix4x4>(Matrix4x4::GetIdentity(), ROTATION, SCALE);

    const float_z PIVOT_COMPONENTS[] = { SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_1 };
    const T PIVOT = T(PIVOT_COMPONENTS);

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT).Transform(TRANSFORMATION) + PIVOT,
                                              DIRECTION.Transform(DIRECTION_TRANSFORMATION));
    const Ray3D<T> EXPECTED_NORMALIZEDRAY = EXPECTED_RAY.Normalize();

	// [Execution]
    Ray3D<T> ray = RAY.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(ray.Direction != EXPECTED_RAY.Direction);
    BOOST_CHECK(ray.Direction == EXPECTED_NORMALIZEDRAY.Direction);
}

// [TODO] Thund: Protected methods will be tested in the future.

// End - Test Suite: Ray3D
ZTEST_SUITE_END()
