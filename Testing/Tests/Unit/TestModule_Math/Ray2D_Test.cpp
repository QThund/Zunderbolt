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

#include "ZMath/Ray2D.h"

#include "ZMath/Triangle.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"
using namespace z::Internals;


ZTEST_SUITE_BEGIN( Ray2D_TestSuite )

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_DIRECTION = Vector2(SFloat::_4, SFloat::_5);

    Ray2D EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray2D rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_DIRECTION = Vector2(SFloat::_4, SFloat::_5);

    Ray<Vector2, Vector2> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray2D rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_DIRECTION = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Ray2D rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
ZTEST_CASE ( Constructor4_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test )
{
    // [Preparation]
    const Vector2 INPUT_VALUE_FOR_ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INPUT_VALUE_FOR_DIRECTION = Vector2(SFloat::_4, SFloat::_5);

    const Vector2 UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    Ray2D rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns a null ray placed at the origin.
/// </summary>
ZTEST_CASE ( GetNullRay_ReturnsWhatExpected_Test )
{
    // [Preparation]
    Ray2D EXPECTED_VALUE(Vector2::GetNullVector(), Vector2::GetNullVector());

	// [Execution]
    Ray2D obtinedRay = Ray2D::GetNullRay();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to X axis and points to positive direction.
/// </summary>
ZTEST_CASE ( GetRayX_ReturnsWhatExpected_Test )
{
    // [Preparation]
    Ray2D EXPECTED_VALUE(Vector2::GetNullVector(), Vector2::GetUnitVectorX());

	// [Execution]
    Ray2D obtinedRay = Ray2D::GetRayX();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that it returns a ray that is parallel to Y axis and points to positive direction.
/// </summary>
ZTEST_CASE ( GetRayY_ReturnsWhatExpected_Test )
{
    // [Preparation]
    Ray2D EXPECTED_VALUE(Vector2::GetNullVector(), Vector2::GetUnitVectorY());

	// [Execution]
    Ray2D obtinedRay = Ray2D::GetRayY();

    // [Verification]
    BOOST_CHECK(obtinedRay.Origin == EXPECTED_VALUE.Origin);
    BOOST_CHECK(obtinedRay.Direction == EXPECTED_VALUE.Direction);
}

/// <summary>
/// Checks that a ray is correctly assigned to another ray.
/// </summary>
ZTEST_CASE ( OperatorAssignation_RayIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_DIRECTION = Vector2(SFloat::_3, SFloat::_4);

    const Ray2D OTHER_RAY = Ray2D(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray2D rayUT;
    rayUT = OTHER_RAY;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}
/*
/// <summary>
/// Checks that it returns True when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenRayIntersectsWithTriangleVertex_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 DIRECTION1 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 DIRECTION2 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const Vector2 DIRECTION3 = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

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
ZTEST_CASE ( Intersection2_ReturnsFalseWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = -Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenRayBelongsToTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SFloat::_0_25;
    const Vector2 DIRECTION = Vector2(VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenOriginBelongsToEdgeOfTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION1 = Vector2(SFloat::_0, SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION3 = Vector2(SFloat::_1, -SFloat::_2).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
/// Checks that it returns True when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenOriginAndTriangleVertexCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VERTEX_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VERTEX_B, DIRECTION);
    const Ray2D RAY3 = Ray2D(VERTEX_C, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
ZTEST_CASE ( Intersection2_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN;
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
ZTEST_CASE ( Intersection2_AssertionFailsWhenRayDirectionIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2::GetNullVector();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_4, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_5, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE ( Intersection2_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_3, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

/// <summary>
/// Checks that it returns two intersection points when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT_A = VERTEX_A;
    const Vector2 EXPECTED_POINT_B = VERTEX_B;
    const Vector2 EXPECTED_POINT_C = VERTEX_C;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 DIRECTION1 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 DIRECTION2 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const Vector2 DIRECTION3 = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);
    
	// [Execution]
    Vector2 vIntersectionA;
    Vector2 vIntersectionB;
    Vector2 vIntersectionC;
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
ZTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = -Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_POINT = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SFloat::_0_25;
    const Vector2 DIRECTION = Vector2(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection intersection when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION1 = Vector2(SFloat::_0, SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION3 = Vector2(SFloat::_1, -SFloat::_2).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT1 = ORIGIN1;
    const Vector2 EXPECTED_POINT2 = ORIGIN2;
    const Vector2 EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION1 = Vector2(ORIGIN2 - ORIGIN1).Normalize();
    const Vector2 DIRECTION2 = Vector2(ORIGIN3 - ORIGIN2).Normalize();
    const Vector2 DIRECTION3 = Vector2(ORIGIN1 - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT1 = ORIGIN1;
    const Vector2 EXPECTED_POINT2 = ORIGIN2;
    const Vector2 EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
/// Checks that it returns two intersection points when the origin of the ray coincides with a vertex of the triangle and the direction vector points to another edge.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenCoincidesWithVertexOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN1 = VERTEX_A;
    const Vector2 ORIGIN2 = VERTEX_B;
    const Vector2 ORIGIN3 = VERTEX_C;
    const Vector2 DIRECTION1 = Vector2(VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN1).Normalize();
    const Vector2 DIRECTION2 = Vector2(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN2).Normalize();
    const Vector2 DIRECTION3 = Vector2(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT1 = ORIGIN1;
    const Vector2 EXPECTED_POINT2 = ORIGIN2;
    const Vector2 EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION = Vector2(SFloat::_0, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VERTEX_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VERTEX_B, DIRECTION);
    const Ray2D RAY3 = Ray2D(VERTEX_C, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT1 = VERTEX_A;
    const Vector2 EXPECTED_POINT2 = VERTEX_B;
    const Vector2 EXPECTED_POINT3 = VERTEX_C;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
ZTEST_CASE ( IntersectionPoint2_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(EXPECTED_POINT - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_AssertionFailsWhenRayDirectionIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2::GetNullVector();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vIntersection;

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
ZTEST_CASE ( IntersectionPoint2_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_3, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vIntersection;

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
ZTEST_CASE ( IntersectionPoint2_ReturnsTheClosestPointWhenIntersectingWithTwoEdges_Test )
{
    //       Y
    //       |   
    //      /|\
    //  <--/-|-x-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 VERTEX_B = Vector2(-SFloat::_2, SFloat::_1);
    const Vector2 VERTEX_C = Vector2(SFloat::_2, SFloat::_1);

    const Vector2 ORIGIN = Vector2(SFloat::_4, SFloat::_2);
    const Vector2 DIRECTION = Vector2::GetUnitVectorInvX();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vIntersection);
    
    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK( SFloat::IsGreaterOrEquals(vIntersection.x, SFloat::_0) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_POINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_POINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_POINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector2 DIRECTION1 = Vector2(EXPECTED_POINT2 - EXPECTED_POINT1).Normalize();
    const Vector2 DIRECTION2 = Vector2(EXPECTED_POINT3 - EXPECTED_POINT2).Normalize();
    const Vector2 DIRECTION3 = Vector2(EXPECTED_POINT1 - EXPECTED_POINT3).Normalize();

    Vector2 ORIGIN1 = EXPECTED_POINT1 - Vector2(DIRECTION1);
    Vector2 ORIGIN2 = EXPECTED_POINT2 - Vector2(DIRECTION2);
    Vector2 ORIGIN3 = EXPECTED_POINT3 - Vector2(DIRECTION3);

    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
/// Checks that it returns two intersection points when the origin belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenRayBelongsToEdgeOfTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);
    
    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION1 = (VERTEX_A - ORIGIN1).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION2 = (VERTEX_B - ORIGIN2).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION3 = (VERTEX_C - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT1 = ORIGIN1;
    const Vector2 EXPECTED_POINT2 = ORIGIN2;
    const Vector2 EXPECTED_POINT3 = ORIGIN3;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vIntersection1;
    Vector2 vIntersection2;
    Vector2 vIntersection3;
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
/// Checks that it returns two intersection points when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionPointsWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    //         B
    //        / \
    //       /   \
    //      /     \
    //     A-------C
    //

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_SECONDPOINT = Vector2((float_z)2.333333333333333, (float_z)3.333333333333333);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    
	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayIntersectsWithTriangleVertex_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const Vector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const Vector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const Vector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 DIRECTION1 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A - DIRECTION1;
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 DIRECTION2 = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B - DIRECTION2;
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const Vector2 DIRECTION3 = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C - DIRECTION3;
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

	// [Execution]
    Vector2 vFirstIntersectionA;
    Vector2 vFirstIntersectionB;
    Vector2 vFirstIntersectionC;
    Vector2 vSecondIntersectionA;
    Vector2 vSecondIntersectionB;
    Vector2 vSecondIntersectionC;
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
ZTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithTriangleButWouldDoIfRayPointedOppositeDirection_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = -Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is contained in the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayBelongsToTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_FIRSTPOINT = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) + (VERTEX_C - VERTEX_B) * SFloat::_0_25;
    const Vector2 DIRECTION = Vector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection intersection when the origin of the ray is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION1 = Vector2(SFloat::_0, SFloat::_1).Normalize();
    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION3 = Vector2(SFloat::_1, -SFloat::_2).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const Vector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const Vector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
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
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfTriangleAndDirectionPointsToOtherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 ORIGIN2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 ORIGIN3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION1 = Vector2(ORIGIN2 - ORIGIN1).Normalize();
    const Vector2 DIRECTION2 = Vector2(ORIGIN3 - ORIGIN2).Normalize();
    const Vector2 DIRECTION3 = Vector2(ORIGIN1 - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const Vector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const Vector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const Vector2 EXPECTED_SECONDPOINT1 = ORIGIN2;
    const Vector2 EXPECTED_SECONDPOINT2 = ORIGIN3;
    const Vector2 EXPECTED_SECONDPOINT3 = ORIGIN1;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    // [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
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
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION = Vector2(SFloat::_0, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VERTEX_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VERTEX_B, DIRECTION);
    const Ray2D RAY3 = Ray2D(VERTEX_C, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT1 = VERTEX_A;
    const Vector2 EXPECTED_FIRSTPOINT2 = VERTEX_B;
    const Vector2 EXPECTED_FIRSTPOINT3 = VERTEX_C;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
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
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the triangle coincide and direction points to the opposite edge.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginAndTriangleVertexCoincideAndDirectionPointsToOppositeEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ORIGIN1 = VERTEX_A;
    const Vector2 ORIGIN2 = VERTEX_B;
    const Vector2 ORIGIN3 = VERTEX_C;
    const Vector2 DIRECTION1 = Vector2(VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN1).Normalize();
    const Vector2 DIRECTION2 = Vector2(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN2).Normalize();
    const Vector2 DIRECTION3 = Vector2(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const Vector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const Vector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const Vector2 EXPECTED_SECONDPOINT1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_SECONDPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_SECONDPOINT3 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    // [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
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
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ItIsNotNecessaryToNormalizeTheRay_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_SECONDPOINT = Vector2((float_z)2.333333333333333, (float_z)3.333333333333333);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = EXPECTED_FIRSTPOINT - ORIGIN;
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    
	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
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
ZTEST_CASE ( IntersectionPoint3_AssertionFailsWhenRayDirectionIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2::GetNullVector();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vIntersection;

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
ZTEST_CASE ( IntersectionPoint3_AssertionFailsWhenAllTriangleVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_3, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vIntersection;

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
ZTEST_CASE ( IntersectionPoint3_ReturnsTheClosestPointInFirstParameterWhenIntersectingWithTwoEdges_Test )
{
    //       Y
    //       |   
    //      /|\
    //  <--2-|-1-----------O
    //    /  |  \
    //   /___|___\
    //       |______________ X

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 VERTEX_B = Vector2(-SFloat::_2, SFloat::_1);
    const Vector2 VERTEX_C = Vector2(SFloat::_2, SFloat::_1);

    const Vector2 ORIGIN = Vector2(SFloat::_4, SFloat::_2);
    const Vector2 DIRECTION = Vector2::GetUnitVectorInvX();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
    
    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK( SFloat::IsGreaterOrEquals(vFirstIntersection.x, SFloat::_0) );
    BOOST_CHECK( SFloat::IsNegative(vSecondIntersection.x) );
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenRayIntersectWithTwoEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_FIRSTPOINT1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_FIRSTPOINT2 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_FIRSTPOINT3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_SECONDPOINT1 = EXPECTED_FIRSTPOINT2;
    const Vector2 EXPECTED_SECONDPOINT2 = EXPECTED_FIRSTPOINT3;
    const Vector2 EXPECTED_SECONDPOINT3 = EXPECTED_FIRSTPOINT1;

    const Vector2 DIRECTION1 = Vector2(EXPECTED_FIRSTPOINT2 - EXPECTED_FIRSTPOINT1).Normalize();
    const Vector2 DIRECTION2 = Vector2(EXPECTED_FIRSTPOINT3 - EXPECTED_FIRSTPOINT2).Normalize();
    const Vector2 DIRECTION3 = Vector2(EXPECTED_FIRSTPOINT1 - EXPECTED_FIRSTPOINT3).Normalize();

    Vector2 ORIGIN1 = EXPECTED_FIRSTPOINT1 - Vector2(DIRECTION1);
    Vector2 ORIGIN2 = EXPECTED_FIRSTPOINT2 - Vector2(DIRECTION2);
    Vector2 ORIGIN3 = EXPECTED_FIRSTPOINT3 - Vector2(DIRECTION3);

    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
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
ZTEST_CASE ( IntersectionPoint3_IntersectionIsReturnedInFirstParameterWhenThereIsOnlyOneIntersection_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 DIRECTION = Vector2(SFloat::_0, -SFloat::_1);
    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - DIRECTION;
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);

	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    RAY.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection != EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenRayBelongsToEdgeOfTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);
    
    const Vector2 ORIGIN1 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION1 = (VERTEX_A - ORIGIN1).Normalize();
    const Vector2 ORIGIN2 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION2 = (VERTEX_B - ORIGIN2).Normalize();
    const Vector2 ORIGIN3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION3 = (VERTEX_C - ORIGIN3).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const Triangle<Vector2> TRIANGLE = Triangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

    const Vector2 EXPECTED_FIRSTPOINT1 = ORIGIN1;
    const Vector2 EXPECTED_FIRSTPOINT2 = ORIGIN2;
    const Vector2 EXPECTED_FIRSTPOINT3 = ORIGIN3;
    const Vector2 EXPECTED_SECONDPOINT1 = VERTEX_A;
    const Vector2 EXPECTED_SECONDPOINT2 = VERTEX_B;
    const Vector2 EXPECTED_SECONDPOINT3 = VERTEX_C;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vFirstIntersection2;
    Vector2 vFirstIntersection3;
    Vector2 vSecondIntersection1;
    Vector2 vSecondIntersection2;
    Vector2 vSecondIntersection3;
    EIntersections eOriginContainedInAB = RAY1.IntersectionPoint(TRIANGLE, vFirstIntersection1, vSecondIntersection1);
    EIntersections eOriginContainedInBC = RAY2.IntersectionPoint(TRIANGLE, vFirstIntersection2, vSecondIntersection2);
    EIntersections eOriginContainedInCA = RAY3.IntersectionPoint(TRIANGLE, vFirstIntersection3, vSecondIntersection3);
    
    // [Verification]
    BOOST_CHECK(eOriginContainedInAB == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInBC == EXPECTED_RESULT);
    BOOST_CHECK(eOriginContainedInCA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vFirstIntersection3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(vSecondIntersection3 == EXPECTED_SECONDPOINT3);
}*/
/*
/// <summary>
/// Checks that it returns the expected ray when using a common ray and a common line which intersect.
/// </summary>
ZTEST_CASE ( Reflection1_ExpectedRayIsReturnedWhenUsingCommonRayAndLine_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 EXPECTED_RAY_ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 EXPECTED_RAY_DIRECTION = Vector2(SFloat::_1, SFloat::_0);
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_RAY_ORIGIN, EXPECTED_RAY_DIRECTION);

    const Vector2 ORIGIN(SFloat::_2, SFloat::_3);
    const Vector2 DIRECTION = Vector2(EXPECTED_RAY_ORIGIN - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that it returns the opposite ray when the original ray and the line are orthogonal.
/// </summary>
ZTEST_CASE ( Reflection1_OppositeRayIsReturnedWhenRayAndLineAreOrthogonal_Test )
{
    //
    //    A
    //    |
    //    |<--->----O
    //    |
    //    B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_RAY_ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 EXPECTED_RAY_DIRECTION = -DIRECTION;
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_RAY_ORIGIN, EXPECTED_RAY_DIRECTION);

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that the ray is reflected when it intersects with an endpoint of the line segment,.
/// </summary>
ZTEST_CASE ( Reflection1_RayIsReflectedWhenIntersectsWithLineEndpoint_Test )
{
    //    O
    //    |
    //    |______
    //    A           A
    //     \           \  O
    //      \           \ |
    //       \           \|________
    //        B           B
    //     I            II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 EXPECTED_RAY_ORIGIN_A = VALUE_FOR_A;
    const Vector2 EXPECTED_RAY_DIRECTION_A = Vector2(SFloat::_1, SFloat::_0);
    const Ray2D EXPECTED_RAY_A = Ray2D(EXPECTED_RAY_ORIGIN_A, EXPECTED_RAY_DIRECTION_A);

    const Vector2 EXPECTED_RAY_ORIGIN_B = VALUE_FOR_B;
    const Vector2 EXPECTED_RAY_DIRECTION_B = Vector2(SFloat::_1, SFloat::_0);
    const Ray2D EXPECTED_RAY_B = Ray2D(EXPECTED_RAY_ORIGIN_B, EXPECTED_RAY_DIRECTION_B);

    const Vector2 ORIGIN_A(SFloat::_1, SFloat::_4);
    const Vector2 DIRECTION_A = Vector2(VALUE_FOR_A - ORIGIN_A).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION_B = Vector2(VALUE_FOR_B - ORIGIN_B).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    Ray2D returnedRayA;
    Ray2D returnedRayB;

	// [Execution]
    RAY_A.Reflection(LINE_SEGMENT, returnedRayA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedRayB); // II

    // [Verification]
    BOOST_CHECK(returnedRayA.Direction == EXPECTED_RAY_A.Direction);
    BOOST_CHECK(returnedRayA.Origin == EXPECTED_RAY_A.Origin);
    BOOST_CHECK(returnedRayB.Direction == EXPECTED_RAY_B.Direction);
    BOOST_CHECK(returnedRayB.Origin == EXPECTED_RAY_B.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one belongs to the line.
/// </summary>
ZTEST_CASE ( Reflection1_RayIsNotReflectedWhenOriginBelongsToLine_Test )
{
    //
    //    A  
    //     \ 
    //      O----->
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one coincides with tan endpoint of the line.
/// </summary>
ZTEST_CASE ( Reflection1_RayIsNotReflectedWhenItsOriginCoincidesWithLineEndpoint_Test )
{
    //
    //    AO---->    A  
    //     \          \
    //      \          \
    //       \          \
    //        B          BO---->
    //     I          II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN_A = VALUE_FOR_A;
    const Vector2 DIRECTION_A = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = VALUE_FOR_B;
    const Vector2 DIRECTION_B = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Ray2D EXPECTED_RAY_A = RAY_A;
    const Ray2D EXPECTED_RAY_B = RAY_B;

    Ray2D returnedRayA;
    Ray2D returnedRayB;

	// [Execution]
    RAY_A.Reflection(LINE_SEGMENT, returnedRayA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedRayB); // II

    // [Verification]
    BOOST_CHECK(returnedRayA.Direction == EXPECTED_RAY_A.Direction);
    BOOST_CHECK(returnedRayA.Origin == EXPECTED_RAY_A.Origin);
    BOOST_CHECK(returnedRayB.Direction == EXPECTED_RAY_B.Direction);
    BOOST_CHECK(returnedRayB.Origin == EXPECTED_RAY_B.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when it belongs to the line.
/// </summary>
ZTEST_CASE ( Reflection1_RayIsNotReflectedWhenItBelongsToTheLine_Test )
{
    //
    //    A-------O------>----B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = (VALUE_FOR_A - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that returned ray equals original ray when it doesn't point to the ling segment (they don't intersect).
/// </summary>
ZTEST_CASE ( Reflection1_RayIsNotReflectedWhenItDoesNotPointToLine_Test )
{
    //
    //    A
    //    |   O
    //    |    \
    //    |     \
    //    B      v
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

/// <summary>
/// Checks that the ray is not reflected when the original one intersects with both endpoints of the line..
/// </summary>
ZTEST_CASE ( Reflection1_RayIsNotReflectedWhenIntersectsWithBothLineEndpoints_Test )
{
    //
    //   O-------->A------B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
ZTEST_CASE ( Reflection1_AssertionFailsWhenRayIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_0, SFloat::_1);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2::GetNullVector();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed = false;
    Ray2D returnedRay;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedRay); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Reflection1_AssertionFailsWhenLineEndpointsCoincide_Test )
{
    // O-----AB----->
    //
    //       I


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_2, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_A);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed = false;
    Ray2D returnedRay;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedRay); // I
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
/// Checks that the resultant ray is not normalized when input ray is not.
/// </summary>
ZTEST_CASE ( Reflection1_ResultIsNotNormalizedWhenInputRayIsNotNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN; // Not normalized
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the resultant ray is normalized when input ray is.
/// </summary>
ZTEST_CASE ( Reflection1_ResultIsNormalizedWhenInputRayIsNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Ray2D returnedRay;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedRay);

    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that it returns the expected direction vector when using a common ray and a common line which intersect.
/// </summary>
ZTEST_CASE ( Reflection2_ExpectedDirectionIsReturnedWhenUsingCommonRayAndLine_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 EXPECTED_DIRECTION = Vector2(SFloat::_1, SFloat::_0);

    const Vector2 ORIGIN(SFloat::_2, SFloat::_3);
    const Vector2 DIRECTION = Vector2(LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that it returns the opposite direction when the original ray and the line are orthogonal.
/// </summary>
ZTEST_CASE ( Reflection2_OppositeDirectionIsReturnedWhenRayAndLineAreOrthogonal_Test )
{
    //
    //    A
    //    |
    //    |<--->----O
    //    |
    //    B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_DIRECTION = -DIRECTION;

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that the ray is reflected when it intersects with an endpoint of the line segment,.
/// </summary>
ZTEST_CASE ( Reflection2_RayIsReflectedWhenIntersectsWithLineEndpoint_Test )
{
    //    O
    //    |
    //    |______
    //    A           A
    //     \           \  O
    //      \           \ |
    //       \           \|________
    //        B           B
    //     I            II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 EXPECTED_DIRECTION_A = Vector2(SFloat::_1, SFloat::_0);
    const Vector2 EXPECTED_DIRECTION_B = Vector2(SFloat::_1, SFloat::_0);

    const Vector2 ORIGIN_A(SFloat::_1, SFloat::_4);
    const Vector2 DIRECTION_A = Vector2(VALUE_FOR_A - ORIGIN_A).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION_B = Vector2(VALUE_FOR_B - ORIGIN_B).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    Vector2 returnedDirectionA;
    Vector2 returnedDirectionB;

	// [Execution]
    RAY_A.Reflection(LINE_SEGMENT, returnedDirectionA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedDirectionB); // II

    // [Verification]
    BOOST_CHECK(returnedDirectionA == EXPECTED_DIRECTION_A);
    BOOST_CHECK(returnedDirectionB == EXPECTED_DIRECTION_B);
}

/// <summary>
/// Checks that returned direction equals original ray's direction when the origin of this one belongs to the line.
/// </summary>
ZTEST_CASE ( Reflection2_RayIsNotReflectedWhenOriginBelongsToLine_Test )
{
    //
    //    A  
    //     \ 
    //      O----->
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_DIRECTION = DIRECTION;

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that returned ray equals original ray when the origin of this one coincides with tan endpoint of the line.
/// </summary>
ZTEST_CASE ( Reflection2_RayIsNotReflectedWhenItsOriginCoincidesWithLineEndpoint_Test )
{
    //
    //    AO---->    A  
    //     \          \
    //      \          \
    //       \          \
    //        B          BO---->
    //     I          II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN_A = VALUE_FOR_A;
    const Vector2 DIRECTION_A = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = VALUE_FOR_B;
    const Vector2 DIRECTION_B = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 EXPECTED_DIRECTION_A = DIRECTION_A;
    const Vector2 EXPECTED_DIRECTION_B = DIRECTION_B;

    Vector2 returnedDirectionA;
    Vector2 returnedDirectionB;

	// [Execution]
    RAY_A.Reflection(LINE_SEGMENT, returnedDirectionA); // I
    RAY_B.Reflection(LINE_SEGMENT, returnedDirectionB); // II

    // [Verification]
    BOOST_CHECK(returnedDirectionA == EXPECTED_DIRECTION_A);
    BOOST_CHECK(returnedDirectionB == EXPECTED_DIRECTION_B);
}

/// <summary>
/// Checks that returned direction vector equals original ray's direction when it belongs to the line.
/// </summary>
ZTEST_CASE ( Reflection2_RayIsNotReflectedWhenItBelongsToTheLine_Test )
{
    //
    //    A-------O------>----B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = (VALUE_FOR_A - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_DIRECTION = DIRECTION;

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that returned ray equals original ray when it doesn't point to the ling segment (they don't intersect).
/// </summary>
ZTEST_CASE ( Reflection2_RayIsNotReflectedWhenItDoesNotPointToLine_Test )
{
    //
    //    A
    //    |   O
    //    |    \
    //    |     \
    //    B      v
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_DIRECTION = DIRECTION;

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

/// <summary>
/// Checks that the ray is not reflected when the original one intersects with both endpoints of the line..
/// </summary>
ZTEST_CASE ( Reflection2_RayIsNotReflectedWhenIntersectsWithBothLineEndpoints_Test )
{
    //
    //   O-------->A------B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_DIRECTION = DIRECTION;

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    BOOST_CHECK(returnedDirection == EXPECTED_DIRECTION);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
ZTEST_CASE ( Reflection2_AssertionFailsWhenRayIsNull_Test )
{
    // A-----O(d2=0)-----B
    //
    //          I


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_0, SFloat::_1);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2::GetNullVector();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed = false;
    Vector2 returnedDirection;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedDirection); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Reflection2_AssertionFailsWhenLineEndpointsCoincide_Test )
{
    // O-----AB----->
    //
    //       I


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_2, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_A);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed = false;
    Vector2 returnedDirection;

    try
    {
        RAY.Reflection(LINE_SEGMENT, returnedDirection); // I
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
/// Checks that the resultant vector is not normalized when input ray is not.
/// </summary>
ZTEST_CASE ( Reflection2_ResultIsNotNormalizedWhenInputRayIsNotNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN; // Not normalized
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    const Vector2 NORMALIZED_RESULT = returnedDirection.Normalize();

    BOOST_CHECK(returnedDirection != NORMALIZED_RESULT);
}

/// <summary>
/// Checks that the resultant vector is normalized when input ray is.
/// </summary>
ZTEST_CASE ( Reflection2_ResultIsNormalizedWhenInputRayIsNormalized_Test )
{
    //
    //    A  O
    //     \ |
    //      \|______
    //       \
    //        B
    //


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_0);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = (LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B) - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    Vector2 returnedDirection;

	// [Execution]
    RAY.Reflection(LINE_SEGMENT, returnedDirection);

    // [Verification]
    const Vector2 NORMALIZED_RESULT = returnedDirection.Normalize();

    BOOST_CHECK(returnedDirection == NORMALIZED_RESULT);
}
*/
/// <summary>
/// Checks that a ray is correctly transformed.
/// </summary>
ZTEST_CASE ( Transform_RayIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_DIRECTION = Vector2((float_z)-0.24253562503633291, (float_z)0.97014250014533188);
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALATION = Vector2(SFloat::_2, SFloat::_0_5);
   
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#else
    const float_z ROTATION = SAngle::_HalfPi;
#endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	// [Execution]
    Ray2D returnedRay = RAY.Transform(TRANSFORMATION_MATRIX);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

	// [Execution]
    Ray2D returnedRay = RAY.Transform(TRANSFORMATION);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
ZTEST_CASE ( Transform_AssertionFailsWhenMatrixIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Transform(TRANSFORMATION);
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
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( Transform_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALATION = Vector2(SFloat::_2, SFloat::_0_5);
   
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	// [Execution]
    Ray2D returnedRay = RAY.Transform(TRANSFORMATION_MATRIX);
    
    // [Verification]
    const Vector2& NORMALIZED_DIRECTION = returnedRay.Direction.Normalize();

    BOOST_CHECK(returnedRay.Direction == NORMALIZED_DIRECTION);
}

/// <summary>
/// Checks that a ray is correctly rotated.
/// </summary>
ZTEST_CASE ( Rotate_RayIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_90;
#else
    const float_z ANGLE = SAngle::_HalfPi;
#endif

	// [Execution]
    Ray2D returnedRay = RAY.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not rotated when angle is zero.
/// </summary>
ZTEST_CASE ( Rotate_RayIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;
    const float_z ANGLE = SFloat::_0;

	// [Execution]
    Ray2D returnedRay = RAY.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly rotated with pivot point.
/// </summary>
ZTEST_CASE ( RotateWithPivot_RayIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 EXPECTED_DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ANGLE = SAngle::_90;
#else
    const float_z ANGLE = SAngle::_HalfPi;
#endif

    const Vector2 PIVOT_POINT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Ray2D returnedRay = RAY.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not rotated with a pivot when angle is zero.
/// </summary>
ZTEST_CASE ( RotateWithPivot_RayIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;
    const float_z ANGLE = SFloat::_0;

    const Vector2 PIVOT_POINT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Ray2D returnedRay = RAY.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly translated.
/// </summary>
ZTEST_CASE ( Translate1_RayIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_DIRECTION = DIRECTION;
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Ray2D returnedRay = RAY.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate1_RayIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

	// [Execution]
    Ray2D returnedRay = RAY.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly translated.
/// </summary>
ZTEST_CASE ( Translate2_RayIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_DIRECTION = DIRECTION;
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const float_z TRANSLATION_VALUE_X = SFloat::_3;
    const float_z TRANSLATION_VALUE_Y = SFloat::_4;

	// [Execution]
    Ray2D returnedRay = RAY.Translate(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not translated when translation values equal zero.
/// </summary>
ZTEST_CASE ( Translate2_RayIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const float_z TRANSLATION_VALUE_X = SFloat::_0;
    const float_z TRANSLATION_VALUE_Y = SFloat::_0;

	// [Execution]
    Ray2D returnedRay = RAY.Translate(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_RayIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_2, SFloat::_6);
    const Vector2 EXPECTED_DIRECTION = Vector2(SFloat::_4, SFloat::_9).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
ZTEST_CASE ( Scale1_RayIsNotScaledIfScalingValuesEqualOne_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const Vector2 SCALING_VECTOR = Vector2::GetVectorOfOnes();

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
ZTEST_CASE ( Scale1_AssertionFailsWhenScaleVectorIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(SCALING_VECTOR);
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
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( Scale1_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_VECTOR);
    
    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_RayIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_2, SFloat::_6);
    const Vector2 EXPECTED_DIRECTION = Vector2(SFloat::_4, SFloat::_9).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const float_z SCALING_FACTOR_X = SFloat::_2;
    const float_z SCALING_FACTOR_Y = SFloat::_3;

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
ZTEST_CASE ( Scale2_RayIsNotScaledIfScalingValuesEqualOne_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const float_z SCALING_FACTOR_X = SFloat::_1;
    const float_z SCALING_FACTOR_Y = SFloat::_1;

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
ZTEST_CASE ( Scale2_AssertionFailsWhenScaleVectorIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const float_z SCALING_FACTOR_X = SFloat::_0;
    const float_z SCALING_FACTOR_Y = SFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
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
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( Scale2_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const float_z SCALING_FACTOR_X = SFloat::_2;
    const float_z SCALING_FACTOR_Y = SFloat::_3;

	// [Execution]
    Ray2D returnedRay = RAY.Scale(SCALING_FACTOR_X, SCALING_FACTOR_Y);
    
    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_RayIsCorrectlyScaleWithPivot_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_DIRECTION = Vector2((float_z)0.24253562, (float_z)0.97014248).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_RayIsNotScaleWithPivotIfScalingValuesEqualOne_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2::GetVectorOfOnes();

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_AssertionFailsWhenScaleWithPivotVectorIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
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
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly scaled.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_RayIsCorrectlyScaleWithPivot_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_DIRECTION = Vector2((float_z)0.24253562, (float_z)0.97014248).Normalize();
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const float_z SCALING_FACTOR_X = SFloat::_2;
    const float_z SCALING_FACTOR_Y = SFloat::_4;

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that a ray is not scaled if the scaling values equal one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_RayIsNotScaleWithPivotIfScalingValuesEqualOne_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D EXPECTED_RAY = RAY;

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);

    const float_z SCALING_FACTOR_X = SFloat::_1;
    const float_z SCALING_FACTOR_Y = SFloat::_1;

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale vector is null.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_AssertionFailsWhenScaleWithPivotVectorIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_3);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);

    const float_z SCALING_FACTOR_X = SFloat::_0;
    const float_z SCALING_FACTOR_Y = SFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
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
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_2, SFloat::_3);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_4);
    const float_z SCALING_FACTOR_X = SFloat::_2;
    const float_z SCALING_FACTOR_Y = SFloat::_3;

	// [Execution]
    Ray2D returnedRay = RAY.ScaleWithPivot(SCALING_FACTOR_X, SCALING_FACTOR_Y, PIVOT_POINT);
    
    // [Verification]
    const Ray2D NORMALIZED_RESULT = returnedRay.Normalize();

    BOOST_CHECK(returnedRay == NORMALIZED_RESULT);
}

/// <summary>
/// Checks that a ray is correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot_RayIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 EXPECTED_ORIGIN = Vector2(SFloat::_4, SFloat::_1);
    const Vector2 EXPECTED_DIRECTION = Vector2((float_z)-0.24253562503633291, (float_z)0.97014250014533188);
    const Ray2D EXPECTED_RAY = Ray2D(EXPECTED_ORIGIN, EXPECTED_DIRECTION);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALATION = Vector2(SFloat::_2, SFloat::_0_5);
   
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#else
    const float_z ROTATION = SAngle::_HalfPi;
#endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

	// [Execution]
    Ray2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the ray doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( TransformWithPivot_RayDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Ray2D EXPECTED_RAY = RAY;

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

	const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

	// [Execution]
    Ray2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
ZTEST_CASE ( TransformWithPivot_AssertionFailsWhenMatrixIsNull_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

	const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
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

[TODO] Thund: To be uncommented when tests for disabled assertions are implemented

/// <summary>
/// Checks that the ray is moved to the coordinate origin and its direction nullified when it's transformed by a zero matrix.
/// </summary>
ZTEST_CASE ( TransformWithPivot_RayIsMovedToPivotPointWhenTransfomedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

	const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

    const Ray2D EXPECTED_RAY = Ray2D(PIVOT_POINT, Vector2::GetNullVector());

	// [Execution]
    Ray2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(returnedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(returnedRay.Direction == EXPECTED_RAY.Direction);
}

*/
/// <summary>
/// Checks that the resultant ray is normalized.
/// </summary>
ZTEST_CASE ( TransformWithPivot_ResultIsNormalized_Test )
{
    // [Preparation]
    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALATION = Vector2(SFloat::_2, SFloat::_0_5);
   
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z ROTATION = SAngle::_90;
#else
    const float_z ROTATION = SAngle::_HalfPi;
#endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALATION);

	const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

	// [Execution]
    Ray2D returnedRay = RAY.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // [Verification]
    const Vector2& NORMALIZED_DIRECTION = returnedRay.Direction.Normalize();

    BOOST_CHECK(returnedRay.Direction == NORMALIZED_DIRECTION);
}

// [TODO] Thund: Protected methods will be tested in the future

// End - Test Suite: Ray2D
ZTEST_SUITE_END()
