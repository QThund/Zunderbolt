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

#include "ZMath/BaseQuadrilateral.h"
#include "ZMath/BaseTriangle.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/BaseLineSegment.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( Ray2D_TestSuite )

/// <summary>
/// Checks if default values have not changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_ORIGIN(Vector2::GetNullVector());
    const Vector2 EXPECTED_VALUE_FOR_DIRECTION = Vector2::GetNullVector();

	// [Execution]
    Ray2D rayUT;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

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

    BaseRay<Vector2, Vector2> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

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

/// <summary>
/// Checks that it returns False when rays don't intersect.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersect_Test )
{
    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_4).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays intersect but not in Origin.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenRaysIntersectNoIncludingOrigin_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, -SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(-SFloat::_1, -SFloat::_2).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays coincide totally.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenRaysCoincideTotally_Test )
{
    // O1O2-------->>d1d2  (I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN1, DIRECTION1);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an origin of one ray is contained in the other ray (not including the other origin).
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenAnOriginIsContainedInTheOtherRay_Test )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the 2 rays share only one of their origins.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenRaysShareOriginOnly_Test )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_3, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_3, SFloat::_3).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE ( Intersection1_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 DIRECTION1 = Vector2::GetNullVector();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    
    const Vector2 ORIGIN2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed1 = false;
    
    try
    {
        RAY1.Intersection(RAY2); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        RAY2.Intersection(RAY1); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that the expected result is returned when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE ( Intersection1_ExpectedResultReturnedWhenTheDirectionVectorIsNull_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O1---O2(d2=0)----->d1
    //
    //        I

    //      O3(d3=0)
    // O1---------------->d1
    //
    //        II

    // O3(d3=0)O3(d3=0)-->d1
    //
    //        III

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 DIRECTION1 = Vector2::GetNullVector();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    
    const Vector2 ORIGIN2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const Vector2 ORIGIN3 = Vector2(SFloat::_4, SFloat::_2);
    const Vector2 DIRECTION3 = Vector2::GetNullVector();
    const Ray2D RAY3 = Ray2D(ORIGIN3, DIRECTION3);

    const bool EXPECTED_RESULT_INTERSECTION = true;
    const bool EXPECTED_RESULT_NO_INTERSECTION = false;
    
	// [Execution]
    bool bResultIntersection1 = RAY1.Intersection(RAY2); // I
    bool bResultIntersection2 = RAY2.Intersection(RAY1); // I
    bool bResultNoIntersection1 = RAY2.Intersection(RAY3); // II
    bool bResultNoIntersection2 = RAY3.Intersection(RAY2); // II
    bool bResultCoincidence = RAY3.Intersection(RAY3); // III

    // [Verification]
    BOOST_CHECK_EQUAL(bResultIntersection1, EXPECTED_RESULT_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultIntersection2, EXPECTED_RESULT_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultNoIntersection1, EXPECTED_RESULT_NO_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultNoIntersection2, EXPECTED_RESULT_NO_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultCoincidence, EXPECTED_RESULT_INTERSECTION);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, -SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2);
    bool bResult2 = RAY2.Intersection(RAY1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one fo the rays is contained in the other.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenOneRayIsContainedInTheOther_Test )
{
    //
    // O1---O2----->>
    //
    //     I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays point each other.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenRaysPointEachOther_Test )
{
    //
    // O1<-------->O2
    //
    //       I

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 DIRECTION2 = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(RAY2); // I
    bool bResult2 = RAY2.Intersection(RAY1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it's not necessary that rays are normalized.
/// </summary>
ZTEST_CASE ( Intersection1_ItIsNotNecessaryNormalizeRays_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const Vector2 ORIGIN1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_4);
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(-SFloat::_1, SFloat::_2);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
/// Checks that it returns True when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_A = VERTEX_A;
    const Vector2 DIRECTION_A = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = VERTEX_B;
    const Vector2 DIRECTION_B = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 ORIGIN_C = VERTEX_C;
    const Vector2 DIRECTION_C = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 ORIGIN_D = VERTEX_D;
    const Vector2 DIRECTION_D = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_A = RAY_A.Intersection(QUAD);
    bool bResult_B = RAY_B.Intersection(QUAD);
    bool bResult_C = RAY_C.Intersection(QUAD);
    bool bResult_D = RAY_D.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_D, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_BC = Vector2(SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = Vector2(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION_BC_CD = Vector2(-SFloat::_1, -SFloat::_2).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = Vector2(SFloat::_2, -SFloat::_3);
    const Vector2 DIRECTION_CD_DA = Vector2(-SFloat::_2, SFloat::_3).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = Vector2(-SFloat::_1, -SFloat::_3);
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB_BC = RAY_AB_BC.Intersection(QUAD);
    bool bResult_BC_CD = RAY_BC_CD.Intersection(QUAD);
    bool bResult_CD_DA = RAY_CD_DA.Intersection(QUAD);
    bool bResult_DA_AB = RAY_DA_AB.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD_DA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA_AB, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray belongs to one of the edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginBelongsToAnEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns Fasle when the ray doesn't intersect with the quadrilateral but would do if the direction vector was the opposite.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsFalseWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = -Vector2(SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsFalseWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_A = Vector2(VERTEX_A.x - SFloat::_1, VERTEX_A.y - SFloat::_1);
    const Vector2 DIRECTION_A = (VERTEX_A - ORIGIN_A).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = Vector2(VERTEX_B.x - SFloat::_1, VERTEX_B.y + SFloat::_1);
    const Vector2 DIRECTION_B = (VERTEX_B - ORIGIN_B).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 ORIGIN_C = Vector2(VERTEX_C.x + SFloat::_1, VERTEX_C.y + SFloat::_1);
    const Vector2 DIRECTION_C = (VERTEX_C - ORIGIN_C).Normalize();
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 ORIGIN_D = Vector2(VERTEX_D.x + SFloat::_1, VERTEX_D.y - SFloat::_1);
    const Vector2 DIRECTION_D = (VERTEX_D - ORIGIN_D).Normalize();
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_A = RAY_A.Intersection(QUAD);
    bool bResult_B = RAY_B.Intersection(QUAD);
    bool bResult_C = RAY_C.Intersection(QUAD);
    bool bResult_D = RAY_D.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_A, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_B, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_C, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_D, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray is inside the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayOriginIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector2 DIRECTION_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D) - ORIGIN).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A) - ORIGIN).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_CD = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_CD = Vector2(SFloat::_0, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_CD = Ray2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const Vector2 ORIGIN_BC_DA = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 DIRECTION_BC_DA = Vector2(-SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_BC_DA = Ray2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB_CD = RAY_AB_CD.Intersection(QUAD);
    bool bResult_BC_DA = RAY_BC_DA.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayBelongsToQuadrilateralEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = (VERTEX_A - ORIGIN_AB).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = (VERTEX_B - ORIGIN_BC).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = (VERTEX_C - ORIGIN_CD).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = (VERTEX_D - ORIGIN_DA).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE ( Intersection3_AssertionFailsWhenRayDirectionIsNull )
{
    // [Preparation]
    const Ray2D NULL_RAY = Ray2D::GetNullRay();

    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.Intersection(QUAD);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE ( Intersection3_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;
    const Vector2 VERTEX_D = VERTEX_A;
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = (VERTEX_A - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(QUAD);
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
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
ZTEST_CASE ( Intersection3_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_0, -SFloat::_1);
    const Ray2D NON_NORMALIZED_RAY = Ray2D(ORIGIN, DIRECTION);
    const Ray2D NORMALIZED_RAY = NON_NORMALIZED_RAY.Normalize();

	// [Execution]
    bool bResultNormalized = NORMALIZED_RAY.Intersection(QUAD);
    bool bResultNonNormalized = NON_NORMALIZED_RAY.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultNormalized, bResultNonNormalized);
}

/// <summary>
/// Checks that it returns True when the ray intersects with two contiguous vertices of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection3_ReturnsTrueWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const Vector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const Vector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const Vector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const Vector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult_AB = RAY_AB.Intersection(QUAD);
    bool bResult_BC = RAY_BC.Intersection(QUAD);
    bool bResult_CD = RAY_CD.Intersection(QUAD);
    bool bResult_DA = RAY_DA.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult_DA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns no intersection points when rays don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionPointsWhenRaysDoNotIntersect_Test )
{
    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_4).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when rays intersect but not in Origin.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionPointWhenRaysIntersectNoIncludingOrigin_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = Vector2(SFloat::_2, SFloat::_3);

    const Vector2 ORIGIN1(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_2, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

	// [Execution]
    Vector2 vIntersection = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when rays coincide totally.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenRaysCoincideTotally_Test )
{
    // O1O2-------->>d1d2  (I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    const Ray2D RAY2 = Ray2D(ORIGIN1, DIRECTION1);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection); // I
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns one intersection point when an origin of one ray is contained in the other ray (not including the other origin).
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnOriginIsContainedInTheOtherRay_Test )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_2, SFloat::_3);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = ORIGIN2;

	// [Execution]
    Vector2 vIntersection1 = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    Vector2 vIntersection2 = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 rays share only one of their origins.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenRaysShareOriginOnly_Test )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_3, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2 = ORIGIN1;
    const Vector2 DIRECTION2 = Vector2(SFloat::_3, SFloat::_3).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = ORIGIN1;

	// [Execution]
    Vector2 vIntersection1 = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    Vector2 vIntersection2 = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_AssertionFailsWhenTheDirectionVectorIsNull_Test )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_2, SFloat::_4);
    const Vector2 DIRECTION1 = Vector2::GetNullVector();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);
    
    const Vector2 ORIGIN2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_4).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const bool ASSERTION_FAILED = true;
    
	// [Execution]
    bool bAssertionFailed1 = false;
    Vector2 vIntersection1;

    try
    {
        RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;
    Vector2 vIntersection2;

    try
    {
        RAY2.IntersectionPoint(RAY1, vIntersection2); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersections when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_2, -SFloat::_4).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when one fo the rays is contained in the other.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOneRayIsContainedInTheOther_Test )
{
    //
    // O1---O2----->>
    //
    //     I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = ORIGIN2;


	// [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when rays point each other.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenRaysPointEachOther_Test )
{
    //
    // O1<-------->O2
    //
    //       I

    // [Preparation]
    const Vector2 ORIGIN1(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_3, SFloat::_4);
    const Vector2 DIRECTION2 = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT1 = RAY1.Origin;
    const Vector2 EXPECTED_POINT2 = RAY2.Origin;

	// [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it's not necessary that rays are normalized.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ItIsNotNecessaryNormalizeRays_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = Vector2(SFloat::_2, SFloat::_3);

    const Vector2 ORIGIN1(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION1 = Vector2(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y);
    const Ray2D RAY1 = Ray2D(ORIGIN1, DIRECTION1);

    const Vector2 ORIGIN2(SFloat::_2, SFloat::_2);
    const Vector2 DIRECTION2 = Vector2(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y);
    const Ray2D RAY2 = Ray2D(ORIGIN2, DIRECTION2);

	// [Execution]
    Vector2 vIntersection = Vector2(SFloat::_0, SFloat::_0);
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when a common ray and a common triangle intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenCommonRayIntersectsWithCommonTriangle_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, SFloat::_2);

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);
    
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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX_A, VERTEX_B, VERTEX_C);

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
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_A = VERTEX_A;
    const Vector2 DIRECTION_A = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = VERTEX_B;
    const Vector2 DIRECTION_B = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 ORIGIN_C = VERTEX_C;
    const Vector2 DIRECTION_C = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 ORIGIN_D = VERTEX_D;
    const Vector2 DIRECTION_D = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_A = VERTEX_A;
    const Vector2 EXPECTED_POINT_B = VERTEX_B;
    const Vector2 EXPECTED_POINT_C = VERTEX_C;
    const Vector2 EXPECTED_POINT_D = VERTEX_D;

    Vector2 vIntersectionA;
    Vector2 vIntersectionB;
    Vector2 vIntersectionC;
    Vector2 vIntersectionD;

	// [Execution]
    EIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vIntersectionA);
    EIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vIntersectionB);
    EIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vIntersectionC);
    EIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vIntersectionD);

    // [Verification]
    BOOST_CHECK(eResult_A == EXPECTED_RESULT);
    BOOST_CHECK(eResult_B == EXPECTED_RESULT);
    BOOST_CHECK(eResult_C == EXPECTED_RESULT);
    BOOST_CHECK(eResult_D == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
    BOOST_CHECK(vIntersectionD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_BC = Vector2(SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = Vector2(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION_BC_CD = Vector2(-SFloat::_1, -SFloat::_2).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = Vector2(SFloat::_2, -SFloat::_3);
    const Vector2 DIRECTION_CD_DA = Vector2(-SFloat::_2, SFloat::_3).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = Vector2(-SFloat::_0_5, -SFloat::_3);
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB_BC = Vector2((float_z)1.5714285714285714, (float_z)1.7142857142857144);
    const Vector2 EXPECTED_POINT_BC_CD = Vector2((float_z)2.3999999999999999, (float_z)0.80000000000000004);
    const Vector2 EXPECTED_POINT_CD_DA = Vector2((float_z)1.0909090909090908, (float_z)-1.6363636363636362);
    const Vector2 EXPECTED_POINT_DA_AB = Vector2((float_z)0.08333333333333337, (float_z)-1.4999999999999998);

    Vector2 vIntersection_AB_BC;
    Vector2 vIntersection_BC_CD;
    Vector2 vIntersection_CD_DA;
    Vector2 vIntersection_DA_AB;

	// [Execution]
    EIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD_DA == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge and the ray intersects with other edge.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenOriginBelongsToAnEdgeAndRayIntersectsWithAnotherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB_BC = ORIGIN_AB_BC;
    const Vector2 EXPECTED_POINT_BC_CD = ORIGIN_BC_CD;
    const Vector2 EXPECTED_POINT_CD_DA = ORIGIN_CD_DA;
    const Vector2 EXPECTED_POINT_DA_AB = ORIGIN_DA_AB;

    Vector2 vIntersection_AB_BC;
    Vector2 vIntersection_BC_CD;
    Vector2 vIntersection_CD_DA;
    Vector2 vIntersection_DA_AB;

	// [Execution]
    EIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD_DA == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns two intersection points when the origin coincides with a vertex and the ray intersects with other edge.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenOriginCoincidesWithAVertexAndRayIntersectsWithAnotherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = VERTEX_A;
    const Vector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = VERTEX_B;
    const Vector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = VERTEX_C;
    const Vector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = VERTEX_D;
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB_BC = ORIGIN_AB_BC;
    const Vector2 EXPECTED_POINT_BC_CD = ORIGIN_BC_CD;
    const Vector2 EXPECTED_POINT_CD_DA = ORIGIN_CD_DA;
    const Vector2 EXPECTED_POINT_DA_AB = ORIGIN_DA_AB;

    Vector2 vIntersection_AB_BC;
    Vector2 vIntersection_BC_CD;
    Vector2 vIntersection_CD_DA;
    Vector2 vIntersection_DA_AB;

	// [Execution]
    EIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vIntersection_AB_BC);
    EIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vIntersection_BC_CD);
    EIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vIntersection_CD_DA);
    EIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vIntersection_DA_AB);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD_DA == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersection_BC_CD == EXPECTED_POINT_BC_CD);
    BOOST_CHECK(vIntersection_CD_DA == EXPECTED_POINT_CD_DA);
    BOOST_CHECK(vIntersection_DA_AB == EXPECTED_POINT_DA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when only the origin of the ray belongs to one of the edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyRayOriginBelongsToAnEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_AB = ORIGIN_AB;
    const Vector2 EXPECTED_POINT_BC = ORIGIN_BC;
    const Vector2 EXPECTED_POINT_CD = ORIGIN_CD;
    const Vector2 EXPECTED_POINT_DA = ORIGIN_DA;

    Vector2 vIntersection_AB;
    Vector2 vIntersection_BC;
    Vector2 vIntersection_CD;
    Vector2 vIntersection_DA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral, even of it would do if the direction vector was negated.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

    Vector2 vIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(QUAD, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionsWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

    Vector2 vIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(QUAD, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 DIRECTION_A = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_A = VERTEX_A - DIRECTION_A;
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 DIRECTION_B = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_B = VERTEX_B - DIRECTION_B;
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 DIRECTION_C = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_C = VERTEX_C - DIRECTION_C;
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 DIRECTION_D = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Vector2 ORIGIN_D = VERTEX_D - DIRECTION_D;
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_A = VERTEX_A;
    const Vector2 EXPECTED_POINT_B = VERTEX_B;
    const Vector2 EXPECTED_POINT_C = VERTEX_C;
    const Vector2 EXPECTED_POINT_D = VERTEX_D;

    Vector2 vIntersectionA;
    Vector2 vIntersectionB;
    Vector2 vIntersectionC;
    Vector2 vIntersectionD;

	// [Execution]
    EIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vIntersectionA);
    EIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vIntersectionB);
    EIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vIntersectionC);
    EIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vIntersectionD);

    // [Verification]
    BOOST_CHECK(eResult_A == EXPECTED_RESULT);
    BOOST_CHECK(eResult_B == EXPECTED_RESULT);
    BOOST_CHECK(eResult_C == EXPECTED_RESULT);
    BOOST_CHECK(eResult_D == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
    BOOST_CHECK(vIntersectionD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is containde by the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenRayOriginIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 EXPECTED_POINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_POINT_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 EXPECTED_POINT_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector2 DIRECTION_AB = (EXPECTED_POINT_AB - ORIGIN).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (EXPECTED_POINT_BC - ORIGIN).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (EXPECTED_POINT_CD - ORIGIN).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (EXPECTED_POINT_DA - ORIGIN).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN, DIRECTION_DA);

    Vector2 vIntersection_AB;
    Vector2 vIntersection_BC;
    Vector2 vIntersection_CD;
    Vector2 vIntersection_DA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_CD = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_CD = Vector2(SFloat::_0, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_CD = Ray2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const Vector2 ORIGIN_BC_DA = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 DIRECTION_BC_DA = Vector2(-SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_BC_DA = Ray2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB_CD = Vector2(SFloat::_1, (float_z)1.3333333333333335);
    const Vector2 EXPECTED_POINT_BC_DA = Vector2((float_z)2.4285714285714288, (float_z)0.7142857142857143);

    Vector2 vIntersection_AB_CD;
    Vector2 vIntersection_BC_DA;

	// [Execution]
    EIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vIntersection_AB_CD);
    EIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vIntersection_BC_DA);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_CD == EXPECTED_POINT_AB_CD);
    BOOST_CHECK(vIntersection_BC_DA == EXPECTED_POINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayBelongsToQuadrilateralEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const Vector2 EXPECTED_POINT_AB = ORIGIN_AB;
    const Vector2 EXPECTED_POINT_BC = ORIGIN_BC;
    const Vector2 EXPECTED_POINT_CD = ORIGIN_CD;
    const Vector2 EXPECTED_POINT_DA = ORIGIN_DA;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    Vector2 vIntersection_AB;
    Vector2 vIntersection_BC;
    Vector2 vIntersection_CD;
    Vector2 vIntersection_DA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_AssertionFailsWhenRayDirectionIsNull_Test )
{
    // [Preparation]
    const Ray2D NULL_RAY = Ray2D::GetNullRay();

    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

    Vector2 vIntersection;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.IntersectionPoint(QUAD, vIntersection);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;
    const Vector2 VERTEX_D = VERTEX_A;
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = (VERTEX_A - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

    Vector2 vIntersection;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(QUAD, vIntersection);
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
/// Checks that it's not necessary to normalize the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_CD = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_CD = Vector2(SFloat::_0, -SFloat::_1);
    const Ray2D RAY_AB_CD = Ray2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const Vector2 ORIGIN_BC_DA = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 DIRECTION_BC_DA = Vector2(-SFloat::_2, -SFloat::_1);
    const Ray2D RAY_BC_DA = Ray2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB_CD = Vector2(SFloat::_1, (float_z)1.3333333333333335);
    const Vector2 EXPECTED_POINT_BC_DA = Vector2((float_z)2.4285714285714288, (float_z)0.7142857142857143);

    Vector2 vIntersection_AB_CD;
    Vector2 vIntersection_BC_DA;

	// [Execution]
    EIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vIntersection_AB_CD);
    EIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vIntersection_BC_DA);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB_CD == EXPECTED_POINT_AB_CD);
    BOOST_CHECK(vIntersection_BC_DA == EXPECTED_POINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous vertices.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const Vector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const Vector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const Vector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const Vector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const Vector2 EXPECTED_POINT_AB = VERTEX_A;
    const Vector2 EXPECTED_POINT_BC = VERTEX_B;
    const Vector2 EXPECTED_POINT_CD = VERTEX_C;
    const Vector2 EXPECTED_POINT_DA = VERTEX_D;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    Vector2 vIntersection_AB;
    Vector2 vIntersection_BC;
    Vector2 vIntersection_CD;
    Vector2 vIntersection_DA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vIntersection_AB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vIntersection_BC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vIntersection_CD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vIntersection_DA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection_AB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersection_BC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersection_CD == EXPECTED_POINT_CD);
    BOOST_CHECK(vIntersection_DA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayOriginAndQuadrilateralVertexCoincide_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_A = VERTEX_A;
    const Vector2 DIRECTION_A = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 ORIGIN_B = VERTEX_B;
    const Vector2 DIRECTION_B = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 ORIGIN_C = VERTEX_C;
    const Vector2 DIRECTION_C = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 ORIGIN_D = VERTEX_D;
    const Vector2 DIRECTION_D = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const Vector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const Vector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const Vector2 EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    Vector2 vFirstIntersectionA, vSecondIntersectionA;
    Vector2 vFirstIntersectionB, vSecondIntersectionB;
    Vector2 vFirstIntersectionC, vSecondIntersectionC;
    Vector2 vFirstIntersectionD, vSecondIntersectionD;

	// [Execution]
    EIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vFirstIntersectionD, vSecondIntersectionD);

    // [Verification]
    BOOST_CHECK(eResult_A == EXPECTED_RESULT);
    BOOST_CHECK(eResult_B == EXPECTED_RESULT);
    BOOST_CHECK(eResult_C == EXPECTED_RESULT);
    BOOST_CHECK(eResult_D == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_BC = Vector2(SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = Vector2(SFloat::_3, SFloat::_2);
    const Vector2 DIRECTION_BC_CD = Vector2(-SFloat::_1, -SFloat::_2).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = Vector2(SFloat::_2, -SFloat::_3);
    const Vector2 DIRECTION_CD_DA = Vector2(-SFloat::_2, SFloat::_3).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = Vector2(-SFloat::_0_5, -SFloat::_3);
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB_BC = Vector2((float_z)1.5714285714285714, (float_z)1.7142857142857144);
    const Vector2 EXPECTED_FIRSTPOINT_BC_CD = Vector2((float_z)2.3999999999999999, (float_z)0.80000000000000004);
    const Vector2 EXPECTED_FIRSTPOINT_CD_DA = Vector2((float_z)1.0909090909090908, (float_z)-1.6363636363636362);
    const Vector2 EXPECTED_FIRSTPOINT_DA_AB = Vector2((float_z)0.08333333333333337, (float_z)-1.4999999999999998);
    const Vector2 EXPECTED_SECONDPOINT_AB_BC = Vector2((float_z)2.2000000000000002, (float_z)1.3999999999999999);
    const Vector2 EXPECTED_SECONDPOINT_BC_CD = Vector2((float_z)1.2000000000000002, (float_z)-1.5999999999999996);
    const Vector2 EXPECTED_SECONDPOINT_CD_DA = Vector2((float_z)0.26666666666666683, (float_z)-0.40000000000000036);
    const Vector2 EXPECTED_SECONDPOINT_DA_AB = Vector2((float_z)1.2500000000000002, (float_z)1.5000000000000009);

    Vector2 vFirstIntersection_AB_BC, vSecondIntersection_AB_BC;
    Vector2 vFirstIntersection_BC_CD, vSecondIntersection_BC_CD;
    Vector2 vFirstIntersection_CD_DA, vSecondIntersection_CD_DA;
    Vector2 vFirstIntersection_DA_AB, vSecondIntersection_DA_AB;

	// [Execution]
    EIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vFirstIntersection_AB_BC, vSecondIntersection_AB_BC);
    EIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vFirstIntersection_BC_CD, vSecondIntersection_BC_CD);
    EIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vFirstIntersection_CD_DA, vSecondIntersection_CD_DA);
    EIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vFirstIntersection_DA_AB, vSecondIntersection_DA_AB);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD_DA == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersection_BC_CD == EXPECTED_FIRSTPOINT_BC_CD);
    BOOST_CHECK(vFirstIntersection_CD_DA == EXPECTED_FIRSTPOINT_CD_DA);
    BOOST_CHECK(vFirstIntersection_DA_AB == EXPECTED_FIRSTPOINT_DA_AB);
    BOOST_CHECK(vSecondIntersection_AB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersection_BC_CD == EXPECTED_SECONDPOINT_BC_CD);
    BOOST_CHECK(vSecondIntersection_CD_DA == EXPECTED_SECONDPOINT_CD_DA);
    BOOST_CHECK(vSecondIntersection_DA_AB == EXPECTED_SECONDPOINT_DA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when only the origin of the ray belongs to one of the edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyRayOriginBelongsToAnEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_AB = ORIGIN_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC = ORIGIN_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD = ORIGIN_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA = ORIGIN_DA;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    Vector2 vFirstIntersection_AB, vSecondIntersectionAB;
    Vector2 vFirstIntersection_BC, vSecondIntersectionBC;
    Vector2 vFirstIntersection_CD, vSecondIntersectionCD;
    Vector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral, even of it would do if the direction vector was negated.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithQuadrilateralButWouldDoIfDirectionWasOpposite_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    Vector2 vFirstIntersection = Vector2::GetNullVector();
    Vector2 vSecondIntersection = Vector2::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsNoIntersectionsWhenRayAndQuadrilateralDoesNotIntersect_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    Vector2 vFirstIntersection = Vector2::GetNullVector();
    Vector2 vSecondIntersection = Vector2::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayIntersectsWithQuadrilateralVertex_Test )
{
    //
    //     A ---- B
    //     |      |
    //     |      |
    //     D------C

    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 DIRECTION_A = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_A = VERTEX_A - DIRECTION_A;
    const Ray2D RAY_A = Ray2D(ORIGIN_A, DIRECTION_A);

    const Vector2 DIRECTION_B = Vector2(SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_B = VERTEX_B - DIRECTION_B;
    const Ray2D RAY_B = Ray2D(ORIGIN_B, DIRECTION_B);

    const Vector2 DIRECTION_C = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Vector2 ORIGIN_C = VERTEX_C - DIRECTION_C;
    const Ray2D RAY_C = Ray2D(ORIGIN_C, DIRECTION_C);

    const Vector2 DIRECTION_D = Vector2(-SFloat::_1, SFloat::_1).Normalize();
    const Vector2 ORIGIN_D = VERTEX_D - DIRECTION_D;
    const Ray2D RAY_D = Ray2D(ORIGIN_D, DIRECTION_D);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const Vector2 EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const Vector2 EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const Vector2 EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    Vector2 vFirstIntersectionA, vSecondIntersectionA;
    Vector2 vFirstIntersectionB, vSecondIntersectionB;
    Vector2 vFirstIntersectionC, vSecondIntersectionC;
    Vector2 vFirstIntersectionD, vSecondIntersectionD;

	// [Execution]
    EIntersections eResult_A = RAY_A.IntersectionPoint(QUAD, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eResult_B = RAY_B.IntersectionPoint(QUAD, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eResult_C = RAY_C.IntersectionPoint(QUAD, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eResult_D = RAY_D.IntersectionPoint(QUAD, vFirstIntersectionD, vSecondIntersectionD);

    // [Verification]
    BOOST_CHECK(eResult_A == EXPECTED_RESULT);
    BOOST_CHECK(eResult_B == EXPECTED_RESULT);
    BOOST_CHECK(eResult_C == EXPECTED_RESULT);
    BOOST_CHECK(eResult_D == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is containde by the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsOneIntersectionWhenRayOriginIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);

    const Vector2 DIRECTION_AB = (EXPECTED_FIRSTPOINT_AB - ORIGIN).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (EXPECTED_FIRSTPOINT_BC - ORIGIN).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (EXPECTED_FIRSTPOINT_CD - ORIGIN).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (EXPECTED_FIRSTPOINT_DA - ORIGIN).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN, DIRECTION_DA);

    Vector2 vFirstIntersection_AB, vSecondIntersectionAB;
    Vector2 vFirstIntersection_BC, vSecondIntersectionBC;
    Vector2 vFirstIntersection_CD, vSecondIntersectionCD;
    Vector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoNonContinuousEdges_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_CD = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_CD = Vector2(SFloat::_0, -SFloat::_1).Normalize();
    const Ray2D RAY_AB_CD = Ray2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const Vector2 ORIGIN_BC_DA = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 DIRECTION_BC_DA = Vector2(-SFloat::_2, -SFloat::_1).Normalize();
    const Ray2D RAY_BC_DA = Ray2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB_CD = Vector2(SFloat::_1, (float_z)1.3333333333333335);
    const Vector2 EXPECTED_FIRSTPOINT_BC_DA = Vector2((float_z)2.4285714285714288, (float_z)0.7142857142857143);
    const Vector2 EXPECTED_SECONDPOINT_AB_CD = Vector2(SFloat::_1, (float_z)-1.6666666666666665);
    const Vector2 EXPECTED_SECONDPOINT_BC_DA = Vector2((float_z)0.27272727272727249, (float_z)-0.36363636363636376);

    Vector2 vFirstIntersection_AB_CD;
    Vector2 vFirstIntersection_BC_DA;
    Vector2 vSecondIntersection_AB_CD;
    Vector2 vSecondIntersection_BC_DA;

	// [Execution]
    EIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vFirstIntersection_AB_CD, vSecondIntersection_AB_CD);
    EIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vFirstIntersection_BC_DA, vSecondIntersection_BC_DA);
    
    // [Verification]
    BOOST_CHECK(eResult_AB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vFirstIntersection_BC_DA == EXPECTED_FIRSTPOINT_BC_DA);
    BOOST_CHECK(vSecondIntersection_AB_CD == EXPECTED_SECONDPOINT_AB_CD);
    BOOST_CHECK(vSecondIntersection_BC_DA == EXPECTED_SECONDPOINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayBelongsToQuadrilateralEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 ORIGIN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 ORIGIN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 ORIGIN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const Vector2 EXPECTED_FIRSTPOINT_AB = ORIGIN_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC = ORIGIN_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD = ORIGIN_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA = ORIGIN_DA;
    const Vector2 EXPECTED_SECONDPOINT_AB = VERTEX_B;
    const Vector2 EXPECTED_SECONDPOINT_BC = VERTEX_C;
    const Vector2 EXPECTED_SECONDPOINT_CD = VERTEX_D;
    const Vector2 EXPECTED_SECONDPOINT_DA = VERTEX_A;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    Vector2 vFirstIntersection_AB, vSecondIntersectionAB;
    Vector2 vFirstIntersection_BC, vSecondIntersectionBC;
    Vector2 vFirstIntersection_CD, vSecondIntersectionCD;
    Vector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the origin belongs to an edge and the ray intersects with another edge.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenOriginBelongsToAnEdgeAndRayIntersectsWithAnotherEdge_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_BC = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector2 DIRECTION_AB_BC = (VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN_AB_BC).Normalize();
    const Ray2D RAY_AB_BC = Ray2D(ORIGIN_AB_BC, DIRECTION_AB_BC);

    const Vector2 ORIGIN_BC_CD = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 DIRECTION_BC_CD = (VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D) - ORIGIN_BC_CD).Normalize();
    const Ray2D RAY_BC_CD = Ray2D(ORIGIN_BC_CD, DIRECTION_BC_CD);

    const Vector2 ORIGIN_CD_DA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 DIRECTION_CD_DA = (VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A) - ORIGIN_CD_DA).Normalize();
    const Ray2D RAY_CD_DA = Ray2D(ORIGIN_CD_DA, DIRECTION_CD_DA);

    const Vector2 ORIGIN_DA_AB = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 DIRECTION_DA_AB = (VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_DA_AB).Normalize();
    const Ray2D RAY_DA_AB = Ray2D(ORIGIN_DA_AB, DIRECTION_DA_AB);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB_BC = ORIGIN_AB_BC;
    const Vector2 EXPECTED_FIRSTPOINT_BC_CD = ORIGIN_BC_CD;
    const Vector2 EXPECTED_FIRSTPOINT_CD_DA = ORIGIN_CD_DA;
    const Vector2 EXPECTED_FIRSTPOINT_DA_AB = ORIGIN_DA_AB;
    const Vector2 EXPECTED_SECONDPOINT_AB_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector2 EXPECTED_SECONDPOINT_BC_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector2 EXPECTED_SECONDPOINT_CD_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector2 EXPECTED_SECONDPOINT_DA_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);

    Vector2 vFirstIntersection_AB_BC, vSecondIntersection_AB_BC;
    Vector2 vFirstIntersection_BC_CD, vSecondIntersection_BC_CD;
    Vector2 vFirstIntersection_CD_DA, vSecondIntersection_CD_DA;
    Vector2 vFirstIntersection_DA_AB, vSecondIntersection_DA_AB;

	// [Execution]
    EIntersections eResult_AB_BC = RAY_AB_BC.IntersectionPoint(QUAD, vFirstIntersection_AB_BC, vSecondIntersection_AB_BC);
    EIntersections eResult_BC_CD = RAY_BC_CD.IntersectionPoint(QUAD, vFirstIntersection_BC_CD, vSecondIntersection_BC_CD);
    EIntersections eResult_CD_DA = RAY_CD_DA.IntersectionPoint(QUAD, vFirstIntersection_CD_DA, vSecondIntersection_CD_DA);
    EIntersections eResult_DA_AB = RAY_DA_AB.IntersectionPoint(QUAD, vFirstIntersection_DA_AB, vSecondIntersection_DA_AB);
        
    // [Verification]
    BOOST_CHECK(eResult_AB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD_DA == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersection_BC_CD == EXPECTED_FIRSTPOINT_BC_CD);
    BOOST_CHECK(vFirstIntersection_CD_DA == EXPECTED_FIRSTPOINT_CD_DA);
    BOOST_CHECK(vFirstIntersection_DA_AB == EXPECTED_FIRSTPOINT_DA_AB);
    BOOST_CHECK(vSecondIntersection_AB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersection_BC_CD == EXPECTED_SECONDPOINT_BC_CD);
    BOOST_CHECK(vSecondIntersection_CD_DA == EXPECTED_SECONDPOINT_CD_DA);
    BOOST_CHECK(vSecondIntersection_DA_AB == EXPECTED_SECONDPOINT_DA_AB);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_AssertionFailsWhenRayDirectionIsNull )
{
    // [Preparation]
    const Ray2D NULL_RAY = Ray2D::GetNullRay();

    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const bool ASSERTION_FAILED = true;

    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_AssertionFailsWhenAllQuadrilateralVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = VERTEX_A;
    const Vector2 VERTEX_C = VERTEX_A;
    const Vector2 VERTEX_D = VERTEX_A;
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN(SFloat::_3, SFloat::_3);
    const Vector2 DIRECTION = (VERTEX_A - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(QUAD, vFirstIntersection, vSecondIntersection);
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
/// Checks that it's not necessary to normalize the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ResultIsNotDifferentWhenRayDirectionIsNotNormalized_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 ORIGIN_AB_CD = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION_AB_CD = Vector2(SFloat::_0, -SFloat::_1);
    const Ray2D RAY_AB_CD = Ray2D(ORIGIN_AB_CD, DIRECTION_AB_CD);

    const Vector2 ORIGIN_BC_DA = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 DIRECTION_BC_DA = Vector2(-SFloat::_2, -SFloat::_1);
    const Ray2D RAY_BC_DA = Ray2D(ORIGIN_BC_DA, DIRECTION_BC_DA);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB_CD = Vector2(SFloat::_1, (float_z)1.3333333333333335);
    const Vector2 EXPECTED_FIRSTPOINT_BC_DA = Vector2((float_z)2.4285714285714288, (float_z)0.7142857142857143);
    const Vector2 EXPECTED_SECONDPOINT_AB_CD = Vector2(SFloat::_1, (float_z)-1.6666666666666665);
    const Vector2 EXPECTED_SECONDPOINT_BC_DA = Vector2((float_z)0.27272727272727293, (float_z)-0.36363636363636354);

    Vector2 vFirstIntersection_AB_CD;
    Vector2 vFirstIntersection_BC_DA;
    Vector2 vSecondIntersection_AB_CD;
    Vector2 vSecondIntersection_BC_DA;

	// [Execution]
    EIntersections eResult_AB_CD = RAY_AB_CD.IntersectionPoint(QUAD, vFirstIntersection_AB_CD, vSecondIntersection_AB_CD);
    EIntersections eResult_BC_DA = RAY_BC_DA.IntersectionPoint(QUAD, vFirstIntersection_BC_DA, vSecondIntersection_BC_DA);
    
    // [Verification]
    BOOST_CHECK(eResult_AB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vFirstIntersection_BC_DA == EXPECTED_FIRSTPOINT_BC_DA);
    BOOST_CHECK(vSecondIntersection_AB_CD == EXPECTED_SECONDPOINT_AB_CD);
    BOOST_CHECK(vSecondIntersection_BC_DA == EXPECTED_SECONDPOINT_BC_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects with two contiguous vertices.
/// </summary>
ZTEST_CASE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenRayIntersectsWithTwoContiguousVertices_Test )
{
    // [Preparation]
    const Vector2 VERTEX_A = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 VERTEX_B = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 VERTEX_C = Vector2(SFloat::_3, -SFloat::_1);
    const Vector2 VERTEX_D = Vector2(SFloat::_0, -SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D);

    const Vector2 DIRECTION_AB = (VERTEX_B - VERTEX_A).Normalize();
    const Vector2 ORIGIN_AB = VERTEX_A - DIRECTION_AB;
    const Ray2D RAY_AB = Ray2D(ORIGIN_AB, DIRECTION_AB);

    const Vector2 DIRECTION_BC = (VERTEX_C - VERTEX_B).Normalize();
    const Vector2 ORIGIN_BC = VERTEX_B - DIRECTION_BC;
    const Ray2D RAY_BC = Ray2D(ORIGIN_BC, DIRECTION_BC);

    const Vector2 DIRECTION_CD = (VERTEX_D - VERTEX_C).Normalize();
    const Vector2 ORIGIN_CD = VERTEX_C - DIRECTION_CD;
    const Ray2D RAY_CD = Ray2D(ORIGIN_CD, DIRECTION_CD);

    const Vector2 DIRECTION_DA = (VERTEX_A - VERTEX_D).Normalize();
    const Vector2 ORIGIN_DA = VERTEX_D - DIRECTION_DA;
    const Ray2D RAY_DA = Ray2D(ORIGIN_DA, DIRECTION_DA);

    const Vector2 EXPECTED_FIRSTPOINT_AB = VERTEX_A;
    const Vector2 EXPECTED_FIRSTPOINT_BC = VERTEX_B;
    const Vector2 EXPECTED_FIRSTPOINT_CD = VERTEX_C;
    const Vector2 EXPECTED_FIRSTPOINT_DA = VERTEX_D;
    const Vector2 EXPECTED_SECONDPOINT_AB = VERTEX_B;
    const Vector2 EXPECTED_SECONDPOINT_BC = VERTEX_C;
    const Vector2 EXPECTED_SECONDPOINT_CD = VERTEX_D;
    const Vector2 EXPECTED_SECONDPOINT_DA = VERTEX_A;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    Vector2 vFirstIntersection_AB, vSecondIntersectionAB;
    Vector2 vFirstIntersection_BC, vSecondIntersectionBC;
    Vector2 vFirstIntersection_CD, vSecondIntersectionCD;
    Vector2 vFirstIntersection_DA, vSecondIntersectionDA;

	// [Execution]
    EIntersections eResult_AB = RAY_AB.IntersectionPoint(QUAD, vFirstIntersection_AB, vSecondIntersectionAB);
    EIntersections eResult_BC = RAY_BC.IntersectionPoint(QUAD, vFirstIntersection_BC, vSecondIntersectionBC);
    EIntersections eResult_CD = RAY_CD.IntersectionPoint(QUAD, vFirstIntersection_CD, vSecondIntersectionCD);
    EIntersections eResult_DA = RAY_DA.IntersectionPoint(QUAD, vFirstIntersection_DA, vSecondIntersectionDA);

    // [Verification]
    BOOST_CHECK(eResult_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResult_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResult_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResult_DA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection_AB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersection_BC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersection_CD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersection_DA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns False when ray and line don't intersect.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersect_Test )
{

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_4);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line coincide totally.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, -DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2 = RAY2.Intersection(LINE_SEGMENT); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsTrueWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_2, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY.Intersection(LINE_SEGMENT); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsTrueWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1  = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2  = RAY2.Intersection(LINE_SEGMENT); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray only intersects with a line's endpoint.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsTrueWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_6);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_6).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION1);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1  = RAY1.Intersection(LINE_SEGMENT); // I
    bool bResult2  = RAY2.Intersection(LINE_SEGMENT); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
ZTEST_CASE ( Intersection4_AssertionFailsWhenTheDirectionVectorIsNull_Test )
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
    
    try
    {
        RAY.Intersection(LINE_SEGMENT); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( Intersection4_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
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
    
    try
    {
        RAY.Intersection(LINE_SEGMENT); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsExpectedResultWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    // O---------->
    //
    //   AB
    //       II


    // [Preparation]
    const Vector2 ENDPOINT_CONTAINED(SFloat::_2, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_CONTAINED, ENDPOINT_CONTAINED);

    const Vector2 ENDPOINT_NOT_CONTAINED(SFloat::_4, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_NOT_CONTAINED, ENDPOINT_NOT_CONTAINED);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;
    
	// [Execution]
    bool bResultContained = RAY.Intersection(LINE_SEGMENT_CONTAINED); // I
    bool bResultNotContained = RAY.Intersection(LINE_SEGMENT_NOT_CONTAINED); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE ( Intersection4_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE ( Intersection4_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B


    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test )
{
    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_4);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);

    const Vector2 ORIGIN(SFloat::_4, SFloat::_5);
    const Vector2 DIRECTION = Vector2(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT1 = LINE_SEGMENT.A;
    const Vector2 EXPECTED_POINT2 = LINE_SEGMENT.B;

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, -DIRECTION);

	// [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = ORIGIN;

    // [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT1 = VALUE_FOR_A;
    const Vector2 EXPECTED_POINT2 = VALUE_FOR_B;

    // [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray only intersects with a line's endpoint.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsOneIntersectionWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_6);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_6).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION1);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT1 = VALUE_FOR_A;
    const Vector2 EXPECTED_POINT2 = VALUE_FOR_B;

    // [Execution]
    Vector2 vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    Vector2 vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_AssertionFailsWhenTheDirectionVectorIsNull_Test )
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
    Vector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
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
    Vector2 vIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsExpectedResultWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    // O---------->
    //
    //   AB
    //       II

    // [Preparation]
    const Vector2 ENDPOINT_CONTAINED(SFloat::_2, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_CONTAINED, ENDPOINT_CONTAINED);

    const Vector2 ENDPOINT_NOT_CONTAINED(SFloat::_4, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_NOT_CONTAINED, ENDPOINT_NOT_CONTAINED);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const Vector2 EXPECTED_POINT_CONTAINED = ENDPOINT_CONTAINED;
    const Vector2 EXPECTED_POINT_NOT_CONTAINED = Vector2::GetNullVector();
    
	// [Execution]
    Vector2 vPointContained = Vector2::GetNullVector();
    Vector2 vPointNotContained = Vector2::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(LINE_SEGMENT_CONTAINED, vPointContained); // I
    EIntersections eResultNotContained = RAY.IntersectionPoint(LINE_SEGMENT_NOT_CONTAINED, vPointNotContained); // II

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

    // [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

    // [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint6_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);

    const Vector2 ORIGIN(SFloat::_4, SFloat::_5);
    const Vector2 DIRECTION = Vector2(EXPECTED_POINT - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

	// [Execution]
    Vector2 vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test )
{
    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_4);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_2);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    const Vector2 ORIGIN(SFloat::_4, SFloat::_5);
    const Vector2 DIRECTION = Vector2(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

	// [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test )
{
    // AO-------->B  (I
    // BO-------->A  (II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_FIRSTPOINT1 = LINE_SEGMENT.A;
    const Vector2 EXPECTED_SECONDPOINT1 = LINE_SEGMENT.B;
    const Vector2 EXPECTED_FIRSTPOINT2 = LINE_SEGMENT.B;
    const Vector2 EXPECTED_SECONDPOINT2 = LINE_SEGMENT.A;

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, -DIRECTION);

	// [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vSecondIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    Vector2 vFirstIntersection2;
    Vector2 vSecondIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in the line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_3, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT = ORIGIN;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    // [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection = Vector2::GetNullVector();
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_3);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const Vector2 EXPECTED_SECONDPOINT1 = Vector2::GetNullVector();
    const Vector2 EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const Vector2 EXPECTED_SECONDPOINT2 = Vector2::GetNullVector();

    // [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vSecondIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    Vector2 vFirstIntersection2;
    Vector2 vSecondIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray only intersects with a line's endpoint.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayOnlyIntersectsWithLineEndpoint_Test )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_6);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION1 = Vector2(SFloat::_1, SFloat::_2).Normalize();
    const Vector2 DIRECTION2 = Vector2(SFloat::_2, SFloat::_6).Normalize();
    const Ray2D RAY1 = Ray2D(VALUE_FOR_A, DIRECTION1);
    const Ray2D RAY2 = Ray2D(VALUE_FOR_B, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const Vector2 EXPECTED_SECONDPOINT1 = Vector2::GetNullVector();
    const Vector2 EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const Vector2 EXPECTED_SECONDPOINT2 = Vector2::GetNullVector();

    // [Execution]
    Vector2 vFirstIntersection1;
    Vector2 vSecondIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    Vector2 vFirstIntersection2;
    Vector2 vSecondIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(LINE_SEGMENT, vFirstIntersection2, vSecondIntersection2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction vector of the ray is null, even if it intersects with the line.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_AssertionFailsWhenTheDirectionVectorIsNull_Test )
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
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test )
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
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero, even if it intersects with the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsExpectedResultWhenTheLengthOfTheLineEqualsZero_Test )
{
    // O-----AB----->
    //
    //       I

    // O---------->
    //
    //   AB
    //       II

    // [Preparation]
    const Vector2 ENDPOINT_CONTAINED(SFloat::_2, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_CONTAINED, ENDPOINT_CONTAINED);

    const Vector2 ENDPOINT_NOT_CONTAINED(SFloat::_4, SFloat::_2);
    const BaseLineSegment<Vector2> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<Vector2>(ENDPOINT_NOT_CONTAINED, ENDPOINT_NOT_CONTAINED);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const Vector2 EXPECTED_POINT_CONTAINED = ENDPOINT_CONTAINED;
    const Vector2 EXPECTED_POINT_NOT_CONTAINED = Vector2::GetNullVector();
    
	// [Execution]
    Vector2 vFirstPointContained = Vector2::GetNullVector();
    Vector2 vSecondPointContained = Vector2::GetNullVector();
    Vector2 vFirstPointNotContained = Vector2::GetNullVector();
    Vector2 vSecondPointNotContained = Vector2::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(LINE_SEGMENT_CONTAINED, vFirstPointContained, vSecondPointContained); // I
    EIntersections eResultNotContained = RAY.IntersectionPoint(LINE_SEGMENT_NOT_CONTAINED, vFirstPointNotContained, vSecondPointNotContained); // II

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_1, SFloat::_1);
    const Vector2 DIRECTION = Vector2(-SFloat::_1, -SFloat::_1).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    // [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector2 ORIGIN(SFloat::_0, SFloat::_0);
    const Vector2 DIRECTION = Vector2(SFloat::_1, SFloat::_0).Normalize();
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    // [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_ItIsNotNecessaryToNormalize_Test )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const Vector2 VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 VALUE_FOR_B(SFloat::_2, SFloat::_1);
    const BaseLineSegment<Vector2> LINE_SEGMENT = BaseLineSegment<Vector2>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

    const Vector2 ORIGIN(SFloat::_4, SFloat::_5);
    const Vector2 DIRECTION = Vector2(EXPECTED_FIRSTPOINT - ORIGIN);
    const Ray2D RAY = Ray2D(ORIGIN, DIRECTION);

    // [Execution]
    Vector2 vFirstIntersection;
    Vector2 vSecondIntersection;
    EIntersections eResult1 = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

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
