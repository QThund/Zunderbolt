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

// !!!
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the Ray_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/Ray.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/BaseOrb.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Ray_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    Ray<T, Vector3> rayUT;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    Ray<T, Vector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray<T, Vector3> rayUT(EXPECTED_RAY);

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
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    BaseRay<T, Vector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray<T, Vector3> rayUT(EXPECTED_RAY);

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
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    Ray<T, Vector3> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

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
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const Vector3 UNEXPECTED_VALUE_FOR_DIRECTION = Vector3(INPUT_VALUE_FOR_DIRECTION).Normalize();

	// [Execution]
    Ray<T, Vector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that it returns a null ray placed at the origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNullRay_ReturnsWhatExpected_Test, TTemplateTypes )
{
    // [Preparation]
    Ray<T, Vector3> EXPECTED_VALUE(T::GetNullVector(), Vector3::GetNullVector());

	// [Execution]
    Ray<T, Vector3> obtinedRay = Ray<T, Vector3>::GetNullRay();

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
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_6 };
    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Ray<T, Vector3> OTHER_RAY = Ray<T, Vector3>(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    Ray<T, Vector3> rayUT;
    rayUT = OTHER_RAY;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the correct value is obtained when using a common ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( Invert_CorrectValueIsReturnedForACommonRay_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const Ray<T, Vector3> EXPECTED_RAY = Ray<T, Vector3>(RAY.Origin, -RAY.Direction);

	// [Execution]
    Ray<T, Vector3> invertedRay = RAY.Invert();

    // [Verification]
    BOOST_CHECK(invertedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(invertedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Invert_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const Vector3 UNEXPECTED_VALUE_FOR_DIRECTION = -INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    Ray<T, Vector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);
    rayUT = rayUT.Invert();

    // [Verification]
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the correct value is obtained when using a common ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( Normalize_CorrectValueIsReturnedForACommonRay_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const Ray<T, Vector3> EXPECTED_RAY = Ray<T, Vector3>(RAY.Origin, RAY.Direction.Normalize());

	// [Execution]
    Ray<T, Vector3> normalizedRay = RAY.Normalize();

    // [Verification]
    BOOST_CHECK(normalizedRay.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(normalizedRay.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks that the correct point is obtained when using a common distance to the ray's origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPoint_ExpectedPointIsReturnedForACommonDistance_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_z DISTANCE = SFloat::_5;
    const T EXPECTED_POINT = RAY.Origin + RAY.Direction * DISTANCE;

	// [Execution]
    T vPoint = RAY.GetPoint(DISTANCE);

    // [Verification]
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that the obtained point coincides with the origin of the ray when the input distance equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPoint_ObtainedPointCoincidesWithOriginOfRayWhenDistanceEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_z DISTANCE = SFloat::_0;
    const T EXPECTED_POINT = RAY.Origin;

	// [Execution]
    T vPoint = RAY.GetPoint(DISTANCE);

    // [Verification]
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that the correct point is obtained when using a negative distance to the ray's origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPoint_ExpectedPointIsReturnedForANegativeDistance_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();
    
    const float_z DISTANCE = -SFloat::_5;
    const T EXPECTED_POINT = RAY.Origin + RAY.Direction * DISTANCE;

	// [Execution]
    T vPoint = RAY.GetPoint(DISTANCE);

    // [Verification]
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertin fails when the ray is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPoint_AssertionFailsWhenRayIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    
    const float_z DISTANCE = SFloat::_5;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.GetPoint(DISTANCE);
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
/// Checks that obtained point is different when the ray is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPoint_UnexpectedPointIsReturnedWhenRayIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const Ray<T, Vector3> NORMALIZED_RAY = NOT_NORMALIZED_RAY.Normalize();
    
    const float_z DISTANCE = SFloat::_5;

	// [Execution]
    T vPointWhenNotNormalized = NOT_NORMALIZED_RAY.GetPoint(DISTANCE);
    T vPointWhenNormalized = NORMALIZED_RAY.GetPoint(DISTANCE);

    // [Verification]
    BOOST_CHECK(vPointWhenNotNormalized != vPointWhenNormalized);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns false when there is no intersection.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenRayDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    //            ___
    //   \       /   \
    //    \     |  x  |
    //     o     \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { -SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray intersects the orb twice.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenRayIntersectsTheOrbTwice_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----|-----|-----
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { -SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray's origin lies on the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray's origin is contained in the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOriginIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o-----------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the ray is tangent to the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenRayIsTangentToTheOrb_Test, TTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_0;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(ORB);
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
ZTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenDirectionVectorIsNull_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(ORB);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertin fails when the ray is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRayIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_3, SFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.Intersection(ORB);
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
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsExpectedResultWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    const float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3 };
    const T VALUE_FOR_CENTER_CONTAINED(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const float_z RADIUS_CONTAINED = SFloat::_0;
    const BaseOrb<T> ORB_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_CONTAINED, RADIUS_CONTAINED);

    const float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_4, SFloat::_3, SFloat::_3 };
    const T VALUE_FOR_CENTER_NOT_CONTAINED(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED);

    const BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_NOT_CONTAINED, RADIUS_CONTAINED);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = RAY.Intersection(ORB_CONTAINED);
    bool bResultNotContained = RAY.Intersection(ORB_NOT_CONTAINED);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_NoIntersectionPointsAreReturnedWhenRayDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    // o            ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_3, SFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_10, SFloat::_10, SFloat::_10, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects the orb twice.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoIntersectionPointsWhenRayIntersectsTheOrbTwice_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin lies on the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray's origin lies on the surface of the orb and the ray points to the interior of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenOriginLiesOnTheSurfaceOfTheOrbAndTheRayPointsToInteriorOfOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //     -----x-----o
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin is contained in the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenOriginIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o--x---------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is tangent to the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenRayIsTangentToTheOrb_Test, TTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns zero intersection points when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoPointsWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_0;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenDirectionVectorIsNull_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION = Vector3::GetNullVector();
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_0;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the ray is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenRayIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_3, SFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.IntersectionPoint(ORB, OUTPUT_POINT);
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
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    const float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER_CONTAINED(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const float_z RADIUS_CONTAINED = SFloat::_0;
    const BaseOrb<T> ORB_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_CONTAINED, RADIUS_CONTAINED);

    const float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER_NOT_CONTAINED(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED);
    const BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_NOT_CONTAINED, RADIUS_CONTAINED);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_One;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const float_z EXPECTED_POINT_COMPONENTS_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT_CONTAINED = T(EXPECTED_POINT_COMPONENTS_CONTAINED);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vPointContained = T::GetNullVector();
    T vPointNotContained = T::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(ORB_CONTAINED, vPointContained);
    EIntersections eResultNotContained = RAY.IntersectionPoint(ORB_NOT_CONTAINED, vPointNotContained);

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns a wrong result when the ray's direction is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsWrongResultWhenRayDirectionIsNotNormalized_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_7, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const Ray<T, Vector3> NORMALIZED_RAY = NOT_NORMALIZED_RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

	// [Execution]
    T vNormalizedRayResult = T::GetNullVector();
    T vNotNormalizedRayResult = T::GetNullVector();

    NORMALIZED_RAY.IntersectionPoint(ORB, vNormalizedRayResult);
    NOT_NORMALIZED_RAY.IntersectionPoint(ORB, vNotNormalizedRayResult);

    // [Verification]
    BOOST_CHECK(vNormalizedRayResult != vNotNormalizedRayResult);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned intersection point is the closest one to the origin of the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnedPointIsTheClosestOneToRayOrigin_Test, TTemplateTypes )
{
    //            ___                     ___
    //           /   \                   /   \
    //    o-----x-----------        ----------x---o
    //           \___/                   \___/
    //
    //             I                       II

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_ORIGIN2[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION2[] = { -SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN2(VECTOR_COMPONENTS_ORIGIN2);
    const Vector3 VALUE_FOR_DIRECTION2(VECTOR_COMPONENTS_DIRECTION2);
    const Ray<T, Vector3> RAY2 = Ray<T, Vector3>(VALUE_FOR_ORIGIN2, VALUE_FOR_DIRECTION2.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_z VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);

    T OUTPUT_POINT = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    RAY.IntersectionPoint(ORB, OUTPUT_POINT);   // I
    RAY2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // [Verification]
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_NoIntersectionPointsAreReturnedWhenRayDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    // o            ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_3, SFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_10, SFloat::_10, SFloat::_10, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray intersects the orb twice.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionPointsWhenRayIntersectsTheOrbTwice_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    float_z VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin lies on the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenOriginLiesOnTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  x  o---------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns two intersection points when the ray's origin lies on the surface of the orb and the ray points to the interior of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenOriginLiesOnTheSurfaceOfTheOrbAndTheRayPointsToInteriorOfOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //     -----x-----o
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray's origin is contained in the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenOriginIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //          |  o--x---------
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns one intersection point when the ray is tangent to the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenRayIsTangentToTheOrb_Test, TTemplateTypes )
{
    //    o-------===------
    //           /   \
    //          |  x  |
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT1[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT1);
    const T EXPECTED_POINT2 = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns zero intersection points when the ray doesn't intersect the orb but would do if it was inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoPointsWhenRayDoesNotIntersectTheOrbButWouldDoIfInverted_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //  <-----o··|·····|··
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { -SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_0;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenDirectionVectorIsNull_Test, TTemplateTypes )
{
    //             ___
    //            /   \
    //        o  |  x  |
    //            \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION = Vector3::GetNullVector();
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_0;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the ray is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenRayIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_3, SFloat::_5};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_1;
    const BaseOrb<T> ORB = BaseOrb<T>(VALUE_FOR_CENTER, RADIUS);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NOT_NORMALIZED_RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);
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
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultWhenRadiusOfTheOrbEqualsZero_Test, TTemplateTypes )
{
    //
    //  o---------x---->
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    RAY = RAY.Normalize();

    const float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_CENTER_CONTAINED(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const float_z RADIUS_CONTAINED = SFloat::_0;
    const BaseOrb<T> ORB_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_CONTAINED, RADIUS_CONTAINED);

    const float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_4, SFloat::_3, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_CENTER_NOT_CONTAINED(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED);
    const BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>(VALUE_FOR_CENTER_NOT_CONTAINED, RADIUS_CONTAINED);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_One;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_FIRSTPOINT_CONTAINED = VALUE_FOR_CENTER_CONTAINED;
    const T EXPECTED_SECONDPOINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstPointContained = T::GetNullVector();
    T vFirstPointNotContained = T::GetNullVector();
    T vSecondPointContained = T::GetNullVector();
    T vSecondPointNotContained = T::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(ORB_CONTAINED, vFirstPointContained, vSecondPointContained);
    EIntersections eResultNotContained = RAY.IntersectionPoint(ORB_NOT_CONTAINED, vFirstPointNotContained, vSecondPointNotContained);

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_FIRSTPOINT_CONTAINED);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_SECONDPOINT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns a wrong result when the ray's direction is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsWrongResultWhenRayDirectionIsNotNormalized_Test, TTemplateTypes )
{
    //            ___
    //           /   \
    //    o-----x-----x-----
    //           \___/
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_7, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> NOT_NORMALIZED_RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);
    const Ray<T, Vector3> NORMALIZED_RAY = NOT_NORMALIZED_RAY.Normalize();

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

	// [Execution]
    T vFirstNormalizedRayResult = T::GetNullVector();
    T vSecondNormalizedRayResult = T::GetNullVector();
    T vFisrtNotNormalizedRayResult = T::GetNullVector();
    T vSecondNotNormalizedRayResult = T::GetNullVector();

    NORMALIZED_RAY.IntersectionPoint(ORB, vFirstNormalizedRayResult, vSecondNormalizedRayResult);
    NOT_NORMALIZED_RAY.IntersectionPoint(ORB, vFisrtNotNormalizedRayResult, vSecondNotNormalizedRayResult);

    // [Verification]
    BOOST_CHECK(vFirstNormalizedRayResult != vFisrtNotNormalizedRayResult);
    BOOST_CHECK(vSecondNormalizedRayResult != vSecondNotNormalizedRayResult);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the first returned intersection point is the closest one to the origin of the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_FirstReturnedPointIsTheClosestOneToRayOrigin_Test, TTemplateTypes )
{
    //            ___                     ___
    //           /   \                   /   \
    //    o-----1-----2-----        ----2-----1---o
    //           \___/                   \___/
    //
    //             I                       II

    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION.Normalize());

    float_z VECTOR_COMPONENTS_ORIGIN2[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION2[] = { -SFloat::_1, SFloat::_0, SFloat::_0};
    const T VALUE_FOR_ORIGIN2(VECTOR_COMPONENTS_ORIGIN2);
    const Vector3 VALUE_FOR_DIRECTION2(VECTOR_COMPONENTS_DIRECTION2);
    const Ray<T, Vector3> RAY2 = Ray<T, Vector3>(VALUE_FOR_ORIGIN2, VALUE_FOR_DIRECTION2.Normalize());

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_z VECTOR_COMPONENTS_OUTPUT_POINT2[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINT2);

    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    T OUTPUT_POINT3 = T::GetNullVector();
    T OUTPUT_POINT4 = T::GetNullVector();

	// [Execution]
    RAY.IntersectionPoint(ORB, OUTPUT_POINT1, OUTPUT_POINT2);   // I
    RAY2.IntersectionPoint(ORB, OUTPUT_POINT3, OUTPUT_POINT4); // II

    // [Verification]
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6};
    const T VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);
    const Ray<T, Vector3> RAY = Ray<T, Vector3>(VALUE_FOR_ORIGIN, VALUE_FOR_DIRECTION);

    const string_z EXPECTED_STRING = string_z("RY(o(") + VALUE_FOR_ORIGIN.ToString() + Z_L("),d(") + VALUE_FOR_DIRECTION.ToString() + Z_L("))");

	// [Execution]
    string_z strReturnedString = RAY.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: Ray
ZTEST_SUITE_END()
