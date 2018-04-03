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

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Ray3D_TestSuite )

/// <summary>
/// Checks if default values have not changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION = Vector3::GetNullVector();

	// [Execution]
    Ray3D<T> rayUT;

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

    BaseRay<T, Vector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

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
/// Checks that it returns False when rays don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays intersect but not in Origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenRaysIntersectNoIncludingOrigin_Test, TTemplateTypes )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, -SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(-SFloat::_1, -SFloat::_2, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when rays coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenRaysCoincideTotally_Test, TTemplateTypes )
{
    // O1O2-------->>d1d2  (I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN1, DIRECTION1);

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
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenAnOriginIsContainedInTheOtherRay_Test, TTemplateTypes )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_2, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenRaysShareOriginOnly_Test, TTemplateTypes )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_3, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_3, SFloat::_3, SFloat::_3).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3::GetNullVector();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
/// Checks that it returns the expected result when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsExpectedResultWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O1---O2(d2=0)----->d1
    //
    //        I

    // O1-------->d1
    //
    // O2(d2=0)
    //        II

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3::GetNullVector();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const float_z ORIGIN_COMPONENTS3[] = { SFloat::_9, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN3(ORIGIN_COMPONENTS3);
    const Vector3 DIRECTION3 = Vector3::GetNullVector();
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained1 = RAY1.Intersection(RAY2); // I
    bool bResultContained2 = RAY2.Intersection(RAY1); // I
    bool bResultNotContained1 = RAY3.Intersection(RAY1); // II
    bool bResultNotContained2 = RAY1.Intersection(RAY3); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained1, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultContained2, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained1, EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained2, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test, TTemplateTypes )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, -SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_2, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenOneRayIsContainedInTheOther_Test, TTemplateTypes )
{
    //
    // O1---O2----->>
    //
    //     I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenRaysPointEachOther_Test, TTemplateTypes )
{
    //
    // O1<-------->O2
    //
    //       I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(-SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection1_ItIsNotNecessaryNormalizeRays_Test, TTemplateTypes )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_4, SFloat::_0);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(-SFloat::_1, SFloat::_2, SFloat::_0);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY1.Intersection(RAY2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when ray and line don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenRayAndLineDoNotIntersect_Test, TTemplateTypes )
{

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when ray and line coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenRayAndLineCoincideTotally_Test, TTemplateTypes )
{
    // AO-------->B  (I
    // BO-------->A  (II


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, -DIRECTION);

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
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenOriginIsContainedInTheLine_Test, TTemplateTypes )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = RAY.Intersection(LINE_SEGMENT); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenRayAndLineShareOneEndPointOnly_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION);

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
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenRayOnlyIntersectsWithLineEndpoint_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_6, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_6, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION2);

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
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // A-----O(d2=0)-----B
    //
    //          I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

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
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test, TTemplateTypes )
{
    // O-----AB----->
    //
    //       I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

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
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultWhenTheLengthOfTheLineEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O-----AB----->
    //
    //       I

    // O---------->
    //
    // AB
    //       II


    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_CONTAINED = BaseLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = RAY.Intersection(LINE_SEGMENT_CONTAINED); // I
    bool bResultNotContained = RAY.Intersection(LINE_SEGMENT_NOT_CONTAINED); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_1, -SFloat::_1, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_6, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_0, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ItIsNotNecessaryToNormalize_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(LINE_SEGMENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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
/// Checks that it returns True when a common ray and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenCommonRayIntersectsWithCommonHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common ray intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenRayIntersectsWithHexahedronVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_z ORIGIN_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T ORIGIN_LEFT(ORIGIN_COMPONENTS_LEFT);

    const float_z ORIGIN_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T ORIGIN_RIGHT(ORIGIN_COMPONENTS_RIGHT);

    const Vector3 DIRECTION_A = Vector3(VERTEX_A - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_B = Vector3(VERTEX_B - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_C = Vector3(VERTEX_C - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_D = Vector3(VERTEX_D - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_E = Vector3(VERTEX_E - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_F = Vector3(VERTEX_F - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_G = Vector3(VERTEX_G - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_H = Vector3(VERTEX_H - ORIGIN_LEFT).Normalize();

    const Ray3D<T> RAY_A = Ray3D<T>(ORIGIN_LEFT, DIRECTION_A);
    const Ray3D<T> RAY_B = Ray3D<T>(ORIGIN_LEFT, DIRECTION_B);
    const Ray3D<T> RAY_C = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_C);
    const Ray3D<T> RAY_D = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_D);
    const Ray3D<T> RAY_E = Ray3D<T>(ORIGIN_LEFT, DIRECTION_E);
    const Ray3D<T> RAY_F = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_F);
    const Ray3D<T> RAY_G = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_G);
    const Ray3D<T> RAY_H = Ray3D<T>(ORIGIN_LEFT, DIRECTION_H);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = RAY_A.Intersection(HEXAHEDRON);
    bool bIntersectsWithB = RAY_B.Intersection(HEXAHEDRON);
    bool bIntersectsWithC = RAY_C.Intersection(HEXAHEDRON);
    bool bIntersectsWithD = RAY_D.Intersection(HEXAHEDRON);
    bool bIntersectsWithE = RAY_E.Intersection(HEXAHEDRON);
    bool bIntersectsWithF = RAY_F.Intersection(HEXAHEDRON);
    bool bIntersectsWithG = RAY_G.Intersection(HEXAHEDRON);
    bool bIntersectsWithH = RAY_H.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithH, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common ray and a common hexahedron would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsFalseWhenRayDoesNotIntersectWithHexahedronButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, -DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = RAY.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenOriginIsContainedInHexahedronFace_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    // Note: Directions equal face normals
    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC = RAY_IN_DFGC.Intersection(HEXAHEDRON);
    bool bContainedInADFE = RAY_IN_ADFE.Intersection(HEXAHEDRON);
    bool bContainedInAEHB = RAY_IN_AEHB.Intersection(HEXAHEDRON);
    bool bContainedInCGHB = RAY_IN_CGHB.Intersection(HEXAHEDRON);
    bool bContainedInABCD = RAY_IN_ABCD.Intersection(HEXAHEDRON);
    bool bContainedInEFGH = RAY_IN_EFGH.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray belongs to a face of the hexahedron (it contains its origin and direction is parallel).
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenRayBelongsToHexahedronFace_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(VERTEX_G - VERTEX_D).Normalize();
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(VERTEX_F - VERTEX_A).Normalize();
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(VERTEX_H - VERTEX_A).Normalize();
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(VERTEX_H - VERTEX_C).Normalize();
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(VERTEX_C - VERTEX_A).Normalize();
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(VERTEX_G - VERTEX_E).Normalize();
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC = RAY_IN_DFGC.Intersection(HEXAHEDRON);
    bool bContainedInADFE = RAY_IN_ADFE.Intersection(HEXAHEDRON);
    bool bContainedInAEHB = RAY_IN_AEHB.Intersection(HEXAHEDRON);
    bool bContainedInCGHB = RAY_IN_CGHB.Intersection(HEXAHEDRON);
    bool bContainedInABCD = RAY_IN_ABCD.Intersection(HEXAHEDRON);
    bool bContainedInEFGH = RAY_IN_EFGH.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of a ray is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenOriginIsContainedInHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenOriginBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_ABCD);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_ABCD);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_ABCD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_ABCD);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EFGH);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_EFGH);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_EFGH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_EFGH);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DFGC);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AEHB);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_AEHB);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_DFGC);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bOriginContainedInAB = RAY_IN_AB.Intersection(HEXAHEDRON);
    bool bOriginContainedInBC = RAY_IN_BC.Intersection(HEXAHEDRON);
    bool bOriginContainedInCD = RAY_IN_CD.Intersection(HEXAHEDRON);
    bool bOriginContainedInDA = RAY_IN_DA.Intersection(HEXAHEDRON);
    bool bOriginContainedInEF = RAY_IN_EF.Intersection(HEXAHEDRON);
    bool bOriginContainedInFG = RAY_IN_FG.Intersection(HEXAHEDRON);
    bool bOriginContainedInGH = RAY_IN_GH.Intersection(HEXAHEDRON);
    bool bOriginContainedInHE = RAY_IN_HE.Intersection(HEXAHEDRON);
    bool bOriginContainedInDF = RAY_IN_DF.Intersection(HEXAHEDRON);
    bool bOriginContainedInAE = RAY_IN_AE.Intersection(HEXAHEDRON);
    bool bOriginContainedInBH = RAY_IN_BH.Intersection(HEXAHEDRON);
    bool bOriginContainedInCG = RAY_IN_CG.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bOriginContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginContainedInCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the ray intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenRayIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_z ORIGIN_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T ORIGIN_OVER  = T(ORIGIN_OVER_COMPONENTS);  // For edges of face ABCD
    const T ORIGIN_BELOW = T(ORIGIN_BELOW_COMPONENTS); // For edges of face EFGH
    const T ORIGIN_LEFT  = T(ORIGIN_LEFT_COMPONENTS);  // For edges of face ADFE
    const T ORIGIN_RIGHT = T(ORIGIN_RIGHT_COMPONENTS); // For edges of face CGHB

    const Vector3 DIRECTION_TO_AB = Vector3(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B) - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_AB = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_AB);

    const Vector3 DIRECTION_TO_BC = Vector3(VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_BC = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_BC);

    const Vector3 DIRECTION_TO_CD = Vector3(VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D) - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_CD = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_CD);

    const Vector3 DIRECTION_TO_DA = Vector3(VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A) - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_DA = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_DA);

    const Vector3 DIRECTION_TO_EF = Vector3(VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F) - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_EF = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_EF);

    const Vector3 DIRECTION_TO_FG = Vector3(VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G) - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_FG = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_FG);

    const Vector3 DIRECTION_TO_GH = Vector3(VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H) - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_GH = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_GH);

    const Vector3 DIRECTION_TO_HE = Vector3(VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E) - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_HE = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_HE);

    const Vector3 DIRECTION_TO_DF = Vector3(VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F) - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_DF = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_DF);

    const Vector3 DIRECTION_TO_AE = Vector3(VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E) - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_AE = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_AE);

    const Vector3 DIRECTION_TO_BH = Vector3(VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H) - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_BH = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_BH);

    const Vector3 DIRECTION_TO_CG = Vector3(VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G) - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_CG = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = RAY_TO_AB.Intersection(HEXAHEDRON);
    bool bIntersectsWithBC = RAY_TO_BC.Intersection(HEXAHEDRON);
    bool bIntersectsWithCD = RAY_TO_CD.Intersection(HEXAHEDRON);
    bool bIntersectsWithDA = RAY_TO_DA.Intersection(HEXAHEDRON);
    bool bIntersectsWithEF = RAY_TO_EF.Intersection(HEXAHEDRON);
    bool bIntersectsWithFG = RAY_TO_FG.Intersection(HEXAHEDRON);
    bool bIntersectsWithGH = RAY_TO_GH.Intersection(HEXAHEDRON);
    bool bIntersectsWithHE = RAY_TO_HE.Intersection(HEXAHEDRON);
    bool bIntersectsWithDF = RAY_TO_DF.Intersection(HEXAHEDRON);
    bool bIntersectsWithAE = RAY_TO_AE.Intersection(HEXAHEDRON);
    bool bIntersectsWithBH = RAY_TO_BH.Intersection(HEXAHEDRON);
    bool bIntersectsWithCG = RAY_TO_CG.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the origin of the ray and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ReturnsTrueWhenOriginAndHexahedronVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Ray3D<T> RAY_FROM_A = Ray3D<T>(VERTEX_A, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_B = Ray3D<T>(VERTEX_B, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_C = Ray3D<T>(VERTEX_C, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_D = Ray3D<T>(VERTEX_D, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_E = Ray3D<T>(VERTEX_E, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_F = Ray3D<T>(VERTEX_F, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_G = Ray3D<T>(VERTEX_G, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_H = Ray3D<T>(VERTEX_H, DIRECTION_AEHB);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bOriginAndACoincide = RAY_FROM_A.Intersection(HEXAHEDRON);
    bool bOriginAndBCoincide = RAY_FROM_B.Intersection(HEXAHEDRON);
    bool bOriginAndCCoincide = RAY_FROM_C.Intersection(HEXAHEDRON);
    bool bOriginAndDCoincide = RAY_FROM_D.Intersection(HEXAHEDRON);
    bool bOriginAndECoincide = RAY_FROM_E.Intersection(HEXAHEDRON);
    bool bOriginAndFCoincide = RAY_FROM_F.Intersection(HEXAHEDRON);
    bool bOriginAndGCoincide = RAY_FROM_G.Intersection(HEXAHEDRON);
    bool bOriginAndHCoincide = RAY_FROM_H.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bOriginAndACoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndBCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndCCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndDCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndECoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndFCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndGCoincide, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bOriginAndHCoincide, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = RAY.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(HEXAHEDRON);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when all the vertices of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection5_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        RAY.Intersection(HEXAHEDRON);
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
/// Checks that it returns no intersection points when rays don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoIntersectionPointsWhenRaysDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when rays intersect but not in Origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionPointWhenRaysIntersectNoIncludingOrigin_Test, TTemplateTypes )
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
    const float_z EXPECTED_COMPONENTS[] = { SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_1 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);

    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y, EXPECTED_POINT.z - ORIGIN1.z).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y, EXPECTED_POINT.z - ORIGIN2.z).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

	// [Execution]
    const float_z INTERSECTION_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    T vIntersection = T(INTERSECTION_COMPONENTS);
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when rays coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenRaysCoincideTotally_Test, TTemplateTypes )
{
    // O1O2-------->>d1d2  (I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_4, SFloat::_6).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection); // I
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns one intersection point when an origin of one ray is contained in the other ray (not including the other origin).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnOriginIsContainedInTheOtherRay_Test, TTemplateTypes )
{
    //         ^
    //        /
    //       /
    // O1---O2----->
    //
    //       I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, SFloat::_2, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = ORIGIN2;

	// [Execution]
    const float_z INTERSECTION_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    T vIntersection1 = T(INTERSECTION_COMPONENTS);
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    T vIntersection2 = T(INTERSECTION_COMPONENTS);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenRaysShareOriginOnly_Test, TTemplateTypes )
{
    //       ^
    //      /
    //     /
    // O1O2----->
    //
    //     I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_3, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const T ORIGIN2 = ORIGIN1;
    const Vector3 DIRECTION2 = Vector3(SFloat::_3, SFloat::_3, SFloat::_3).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = ORIGIN1;

	// [Execution]
    const float_z INTERSECTION_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    T vIntersection1 = T(INTERSECTION_COMPONENTS);
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    T vIntersection2 = T(INTERSECTION_COMPONENTS);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // O1---O2(d2=0)----->d1
    //
    //        I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3::GetNullVector();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;
    T vIntersection1;

    try
    {
        RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;
    T vIntersection2;

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

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O1---O2(d2=0)----->d1
    //
    //        I

    // O1-------->d1
    //
    // O2(d2=0)
    //        II

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3::GetNullVector();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const float_z ORIGIN_COMPONENTS3[] = { SFloat::_9, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN3(ORIGIN_COMPONENTS3);
    const Vector3 DIRECTION3 = Vector3::GetNullVector();
    const Ray3D<T> RAY3 = Ray3D<T>(ORIGIN3, DIRECTION3);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_One;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const float_z EXPECTED_POINT_CONTAINED_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_0 };
    const T EXPECTED_POINT_CONTAINED = T(EXPECTED_POINT_CONTAINED_COMPONENTS);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained1 = T::GetNullVector();
    T vIntersectionContained2 = T::GetNullVector();
    T vIntersectionNotContained1 = T::GetNullVector();
    T vIntersectionNotContained2 = T::GetNullVector();

    EIntersections eResultContained1 = RAY1.IntersectionPoint(RAY2, vIntersectionContained1); // I
    EIntersections eResultContained2 = RAY2.IntersectionPoint(RAY1, vIntersectionContained2); // I
    EIntersections eResultNotContained1 = RAY3.IntersectionPoint(RAY1, vIntersectionNotContained1); // II
    EIntersections eResultNotContained2 = RAY1.IntersectionPoint(RAY3, vIntersectionNotContained2); // II

    // [Verification]
    BOOST_CHECK(eResultContained1 == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultContained2 == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained1 == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(eResultNotContained2 == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained1 == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionContained2 == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionNotContained1 == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionNotContained2 == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersections when the ray doesn't intersect with the other but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoIntersectionsWhenRaysDoNotIntersectButWouldDoIfTheyHadAnOppositeDirection_Test, TTemplateTypes )
{
    // ^        ^
    //  \      /
    //   O1   /
    //    ·  /
    //     ·/
    //     /·
    //   O2  ·

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_2, -SFloat::_4, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_2, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

	// [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    T vIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenOneRayIsContainedInTheOther_Test, TTemplateTypes )
{
    //
    // O1---O2----->>
    //
    //     I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT1 = RAY2.Origin;
    const T EXPECTED_POINT2 = RAY2.Origin;

	// [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    T vIntersection2;
    EIntersections eResult2 = RAY2.IntersectionPoint(RAY1, vIntersection2); // I

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection1 == EXPECTED_POINT1);
    BOOST_CHECK(vIntersection2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns two intersection points when rays point each other.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenRaysPointEachOther_Test, TTemplateTypes )
{
    //
    // O1<-------->O2
    //
    //       I

    // [Preparation]
    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_3, SFloat::_4, SFloat::_3, SFloat::_0 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(-SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_POINT1 = RAY1.Origin;
    const T EXPECTED_POINT2 = RAY2.Origin;

	// [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(RAY2, vIntersection1); // I
    T vIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ItIsNotNecessaryNormalizeRays_Test, TTemplateTypes )
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
    const float_z EXPECTED_COMPONENTS[] = { SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_1 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);

    const float_z ORIGIN_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN1(ORIGIN_COMPONENTS1);
    const Vector3 DIRECTION1 = Vector3(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y, EXPECTED_POINT.z - ORIGIN1.z);
    const Ray3D<T> RAY1 = Ray3D<T>(ORIGIN1, DIRECTION1);

    const float_z ORIGIN_COMPONENTS2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN2(ORIGIN_COMPONENTS2);
    const Vector3 DIRECTION2 = Vector3(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y, EXPECTED_POINT.z - ORIGIN2.z);
    const Ray3D<T> RAY2 = Ray3D<T>(ORIGIN2, DIRECTION2);

	// [Execution]
    const float_z INTERSECTION_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    T vIntersection = T(INTERSECTION_COMPONENTS);
    EIntersections eResult = RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that the W component of the intersection point is not changed.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_WComponentOfIntersectionPointDoesNotChange_Test )
{
    // O1     O2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  v    v

    // [Preparation]
    const Vector4 EXPECTED_POINT = Vector4(SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_1);

    const Vector4 ORIGIN1(SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector3 DIRECTION1 = Vector3(EXPECTED_POINT.x - ORIGIN1.x, EXPECTED_POINT.y - ORIGIN1.y, EXPECTED_POINT.z - ORIGIN1.z);
    const Ray3D<Vector4> RAY1 = Ray3D<Vector4>(ORIGIN1, DIRECTION1);

    const Vector4 ORIGIN2(SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector3 DIRECTION2 = Vector3(EXPECTED_POINT.x - ORIGIN2.x, EXPECTED_POINT.y - ORIGIN2.y, EXPECTED_POINT.z - ORIGIN2.z);
    const Ray3D<Vector4> RAY2 = Ray3D<Vector4>(ORIGIN2, DIRECTION2);

    const float_z EXPECTED_WCOMPONENT = SFloat::_5;

	// [Execution]
    Vector4 vIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_WCOMPONENT);
    RAY1.IntersectionPoint(RAY2, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_WCOMPONENT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test, TTemplateTypes )
{
    // AO-------->B  (I
    // BO-------->A  (II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, -DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_POINT1 = RAY1.Origin;
    const T EXPECTED_POINT2 = RAY2.Origin;

	// [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    T vIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test, TTemplateTypes )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const T ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = ORIGIN;

    // [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT1 = VALUE_FOR_A;
    const T EXPECTED_POINT2 = VALUE_FOR_B;

    // [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    T vIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneInersectionWhenRayOnlyIntersectsWithLineEndpoint_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_6, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_6, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT1 = VALUE_FOR_A;
    const T EXPECTED_POINT2 = VALUE_FOR_B;

    // [Execution]
    T vIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vIntersection1); // I
    T vIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // A-----O(d2=0)-----B
    //
    //          I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test, TTemplateTypes )
{
    // O-----AB----->
    //
    //       I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

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
/// Checks that it returns the expected result when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O---AB----->d
    //
    //        I

    // O-------->d
    //
    // AB
    //        II

    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_CONTAINED = BaseLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const float_z EXPECTED_POINT_CONTAINED_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T EXPECTED_POINT_CONTAINED = T(EXPECTED_POINT_CONTAINED_COMPONENTS);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(LINE_SEGMENT_CONTAINED, vIntersectionContained); // I
    EIntersections eResultNotContained = RAY.IntersectionPoint(LINE_SEGMENT_NOT_CONTAINED, vIntersectionNotContained); // II

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_1, -SFloat::_1, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

    // [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_6, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_0, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

    // [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ItIsNotNecessaryToNormalize_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that the W component of the intersection point is not changed.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_WComponentOfIntersectionPointDoesNotChange_Test )
{
    // A
    //  \
    //   \
    //    \
    //     \
    //      \
    //  O----B-->

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const Vector4 VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const Vector4 VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<Vector4> LINE_SEGMENT = BaseLineSegment<Vector4>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const Vector4 ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(VALUE_FOR_B - ORIGIN).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(ORIGIN, DIRECTION);

    const float_z EXPECTED_WCOMPONENT = SFloat::_5;

	// [Execution]
    Vector4 vIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_WCOMPONENT);
    RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_WCOMPONENT);
}

/// <summary>
/// Checks that it returns no intersection points when ray and line don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_6).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_FIRSTPOINT = T::GetNullVector();

	// [Execution]
    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection when ray and line intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayAndLineIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when ray and line coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenRayAndLineCoincideTotally_Test, TTemplateTypes )
{
    // AO-------->B  (I
    // BO-------->A  (II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, -DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT1 = RAY1.Origin;
    const T EXPECTED_SECONDPOINT1 = VALUE_FOR_B;
    const T EXPECTED_FIRSTPOINT2 = RAY2.Origin;
    const T EXPECTED_SECONDPOINT2 = VALUE_FOR_A;

	// [Execution]
    T vFirstIntersection1;
    T vSecondIntersection1;
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    T vFirstIntersection2;
    T vSecondIntersection2;
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenOriginIsContainedInTheLine_Test, TTemplateTypes )
{
    //        ^
    //       /
    //      /
    // A---O---B
    //
    //     I

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const T ORIGIN = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = ORIGIN;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    // [Execution]
    T vFirstIntersection;
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vFirstIntersection, vSecondIntersection); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when the ray's origin and one of the line's endpoints coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenRayAndLineShareOneEndPointOnly_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   /             /
    // AO-----B      BO-----A
    //
    //     I            II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const T EXPECTED_SECONDPOINT1 = T::GetNullVector();
    const T EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const T EXPECTED_SECONDPOINT2 = T::GetNullVector();

    // [Execution]
    T vFirstIntersection1;
    T vSecondIntersection1 = T::GetNullVector();
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    T vFirstIntersection2;
    T vSecondIntersection2 = T::GetNullVector();
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneInersectionWhenRayOnlyIntersectsWithLineEndpoint_Test, TTemplateTypes )
{
    //     ^             ^
    //    /             /
    //   A----B        B-----A
    //  /             /
    // O             O
    //
    //     I             II

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_6, SFloat::_3, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION1 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();
    const Vector3 DIRECTION2 = Vector3(SFloat::_2, SFloat::_6, SFloat::_3).Normalize();
    const Ray3D<T> RAY1 = Ray3D<T>(VALUE_FOR_A, DIRECTION1);
    const Ray3D<T> RAY2 = Ray3D<T>(VALUE_FOR_B, DIRECTION2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT1 = VALUE_FOR_A;
    const T EXPECTED_SECONDPOINT1 = T::GetNullVector();
    const T EXPECTED_FIRSTPOINT2 = VALUE_FOR_B;
    const T EXPECTED_SECONDPOINT2 = T::GetNullVector();

    // [Execution]
    T vFirstIntersection1;
    T vSecondIntersection1 = T::GetNullVector();
    EIntersections eResult1 = RAY1.IntersectionPoint(LINE_SEGMENT, vFirstIntersection1, vSecondIntersection1); // I
    T vFirstIntersection2;
    T vSecondIntersection2 = T::GetNullVector();
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // A-----O(d2=0)-----B
    //
    //          I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

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
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheLengthOfTheLineEqualsZero_Test, TTemplateTypes )
{
    // O-----AB----->
    //
    //       I


    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

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
/// Checks that it returns the expected result when the direction vector of one of the rays is null, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultWhenTheDirectionVectorIsNull_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // O---AB----->d
    //
    //        I

    // O-------->d
    //
    // AB
    //        II

    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_CONTAINED = BaseLineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const BaseLineSegment<T> LINE_SEGMENT_NOT_CONTAINED = BaseLineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const float_z EXPECTED_POINT_CONTAINED_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const T EXPECTED_POINT_CONTAINED = T(EXPECTED_POINT_CONTAINED_COMPONENTS);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionContained = T::GetNullVector();
    T vFirstIntersectionNotContained = T::GetNullVector();
    T vSecondIntersectionContained = T::GetNullVector();
    T vSecondIntersectionNotContained = T::GetNullVector();

    EIntersections eResultContained = RAY.IntersectionPoint(LINE_SEGMENT_CONTAINED, vFirstIntersectionContained, vSecondIntersectionContained); // I
    EIntersections eResultNotContained = RAY.IntersectionPoint(LINE_SEGMENT_NOT_CONTAINED, vFirstIntersectionNotContained, vSecondIntersectionNotContained); // II

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if it had an opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfRayHadAnOppositeDirection_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  O
    //    \·
    //    ·\
    //   ·  \
    //  ·    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(-SFloat::_1, -SFloat::_1, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

    // [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the ray doesn't intersect with the line but would do it if line was infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsNoIntersectionsWhenRayAndLineDoNotIntersectButWouldDoIfLineWasInfinite_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   B  /
    //    ·/
    //    /·
    //   /  ·
    //  O    ·

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_6, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_0, -SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();

    // [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ItIsNotNecessaryToNormalize_Test, TTemplateTypes )
{
    // A      /
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  O    B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_0 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<T> LINE_SEGMENT = BaseLineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_POINT = LINE_SEGMENT.A.Lerp(SFloat::_0_5, LINE_SEGMENT.B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(EXPECTED_POINT - ORIGIN);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

	// [Execution]
    T vIntersection;
    EIntersections eResult = RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that the W component of the intersection point is not changed.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_WComponentOfIntersectionPointDoesNotChange_Test )
{
    // A
    //  \
    //   \
    //    \
    //     \
    //      \
    //  O----B-->

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const Vector4 VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const Vector4 VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const BaseLineSegment<Vector4> LINE_SEGMENT = BaseLineSegment<Vector4>(VALUE_FOR_A, VALUE_FOR_B);

    const float_z ORIGIN_COMPONENTS[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0 };
    const Vector4 ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(VALUE_FOR_B - ORIGIN).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(ORIGIN, DIRECTION);

    const float_z EXPECTED_WCOMPONENT = SFloat::_5;

	// [Execution]
    Vector4 vIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_WCOMPONENT);
    RAY.IntersectionPoint(LINE_SEGMENT, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_WCOMPONENT);
}

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector4> TRIANGLE = BaseTriangle<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<Vector4> TRIANGLE = BaseTriangle<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

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

/// <summary>
/// Checks that it returns expected intersection points when a common ray and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsExpectedIntersectionsWhenCommonRayIntersectsWithCommonHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_z EXPECTED_FIRSTCOMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_0 };
    const T EXPECTED_FIRSTPOINT = T(EXPECTED_FIRSTCOMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayIntersectsWithHexahedronVertex_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_z ORIGIN_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T ORIGIN_LEFT(ORIGIN_COMPONENTS_LEFT);

    const float_z ORIGIN_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T ORIGIN_RIGHT(ORIGIN_COMPONENTS_RIGHT);

    const Vector3 DIRECTION_A = Vector3(VERTEX_A - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_B = Vector3(VERTEX_B - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_C = Vector3(VERTEX_C - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_D = Vector3(VERTEX_D - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_E = Vector3(VERTEX_E - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_F = Vector3(VERTEX_F - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_G = Vector3(VERTEX_G - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_H = Vector3(VERTEX_H - ORIGIN_LEFT).Normalize();

    const Ray3D<T> RAY_A = Ray3D<T>(ORIGIN_LEFT, DIRECTION_A);
    const Ray3D<T> RAY_B = Ray3D<T>(ORIGIN_LEFT, DIRECTION_B);
    const Ray3D<T> RAY_C = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_C);
    const Ray3D<T> RAY_D = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_D);
    const Ray3D<T> RAY_E = Ray3D<T>(ORIGIN_LEFT, DIRECTION_E);
    const Ray3D<T> RAY_F = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_F);
    const Ray3D<T> RAY_G = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_G);
    const Ray3D<T> RAY_H = Ray3D<T>(ORIGIN_LEFT, DIRECTION_H);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;

	// [Execution]
    EIntersections eIntersectionWithA = RAY_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA);
    EIntersections eIntersectionWithB = RAY_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB);
    EIntersections eIntersectionWithC = RAY_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC);
    EIntersections eIntersectionWithD = RAY_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD);
    EIntersections eIntersectionWithE = RAY_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE);
    EIntersections eIntersectionWithF = RAY_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF);
    EIntersections eIntersectionWithG = RAY_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG);
    EIntersections eIntersectionWithH = RAY_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH);

    // [Verification]
    BOOST_CHECK(eIntersectionWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
}

/// <summary>
/// Checks that it returns no intersection points when a common ray and a common hexahedron would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithHexahedronButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, -DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

    T vFirstIntersection = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginIsContainedInHexahedronFace_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    // Note: Directions equal face normals
    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = ORIGIN_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = ORIGIN_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = ORIGIN_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = ORIGIN_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = ORIGIN_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = ORIGIN_EFGH;

    T vFirstIntersectionDFGC = T::GetNullVector();
    T vFirstIntersectionADFE = T::GetNullVector();
    T vFirstIntersectionAEHB = T::GetNullVector();
    T vFirstIntersectionCGHB = T::GetNullVector();
    T vFirstIntersectionABCD = T::GetNullVector();
    T vFirstIntersectionEFGH = T::GetNullVector();

	// [Execution]
    EIntersections eResultDFGC = RAY_IN_DFGC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC);
    EIntersections eResultADFE = RAY_IN_ADFE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE);
    EIntersections eResultAEHB = RAY_IN_AEHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB);
    EIntersections eResultCGHB = RAY_IN_CGHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB);
    EIntersections eResultABCD = RAY_IN_ABCD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD);
    EIntersections eResultEFGH = RAY_IN_EFGH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH);

    // [Verification]
    BOOST_CHECK(eResultDFGC == EXPECTED_RESULT);
    BOOST_CHECK(eResultADFE == EXPECTED_RESULT);
    BOOST_CHECK(eResultAEHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultCGHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultABCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultEFGH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to a face of the hexahedron (it contains its origin and direction is parallel).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsTwoIntersectionWhenRayBelongsToHexahedronFace_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T CENTER_POINT_FG = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_F);
    const T CENTER_POINT_AD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_D);
    const T CENTER_POINT_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const T CENTER_POINT_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const T CENTER_POINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T CENTER_POINT_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);

    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(CENTER_POINT_FG - ORIGIN_DFGC).Normalize();
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(CENTER_POINT_AD - ORIGIN_ADFE).Normalize();
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(CENTER_POINT_AE - ORIGIN_AEHB).Normalize();
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(CENTER_POINT_CG - ORIGIN_CGHB).Normalize();
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(CENTER_POINT_AB - ORIGIN_ABCD).Normalize();
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(CENTER_POINT_EF - ORIGIN_EFGH).Normalize();
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const T EXPECTED_FIRSTPOINT_DFGC = ORIGIN_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = ORIGIN_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = ORIGIN_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = ORIGIN_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = ORIGIN_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = ORIGIN_EFGH;

    T vFirstIntersectionDFGC = T::GetNullVector();
    T vFirstIntersectionADFE = T::GetNullVector();
    T vFirstIntersectionAEHB = T::GetNullVector();
    T vFirstIntersectionCGHB = T::GetNullVector();
    T vFirstIntersectionABCD = T::GetNullVector();
    T vFirstIntersectionEFGH = T::GetNullVector();

	// [Execution]
    EIntersections eResultDFGC = RAY_IN_DFGC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC);
    EIntersections eResultADFE = RAY_IN_ADFE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE);
    EIntersections eResultAEHB = RAY_IN_AEHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB);
    EIntersections eResultCGHB = RAY_IN_CGHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB);
    EIntersections eResultABCD = RAY_IN_ABCD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD);
    EIntersections eResultEFGH = RAY_IN_EFGH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH);

    // [Verification]
    BOOST_CHECK(eResultDFGC == EXPECTED_RESULT);
    BOOST_CHECK(eResultADFE == EXPECTED_RESULT);
    BOOST_CHECK(eResultAEHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultCGHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultABCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultEFGH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of a ray is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginIsContainedInHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_D);

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    T vFirstIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_ABCD);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_ABCD);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_ABCD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_ABCD);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EFGH);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_EFGH);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_EFGH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_EFGH);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DFGC);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AEHB);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_AEHB);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_DFGC);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = ORIGIN_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = ORIGIN_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = ORIGIN_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = ORIGIN_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = ORIGIN_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = ORIGIN_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = ORIGIN_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = ORIGIN_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = ORIGIN_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = ORIGIN_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = ORIGIN_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = ORIGIN_IN_CG;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;

	// [Execution]
    EIntersections eResultAB = RAY_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EIntersections eResultBC = RAY_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EIntersections eResultCD = RAY_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EIntersections eResultDA = RAY_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EIntersections eResultEF = RAY_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EIntersections eResultFG = RAY_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EIntersections eResultGH = RAY_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EIntersections eResultHE = RAY_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EIntersections eResultDF = RAY_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EIntersections eResultAE = RAY_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EIntersections eResultBH = RAY_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EIntersections eResultCG = RAY_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(eResultEF == EXPECTED_RESULT);
    BOOST_CHECK(eResultFG == EXPECTED_RESULT);
    BOOST_CHECK(eResultGH == EXPECTED_RESULT);
    BOOST_CHECK(eResultHE == EXPECTED_RESULT);
    BOOST_CHECK(eResultDF == EXPECTED_RESULT);
    BOOST_CHECK(eResultAE == EXPECTED_RESULT);
    BOOST_CHECK(eResultBH == EXPECTED_RESULT);
    BOOST_CHECK(eResultCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the hexahedron and its direction points to interior.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfHexahedronAndDirectionPointsToInterior_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector3 DIRECTION_AB = Vector3(CENTER_POINT - ORIGIN_IN_AB).Normalize();
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_AB);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_BC = Vector3(CENTER_POINT - ORIGIN_IN_BC).Normalize();
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_BC);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector3 DIRECTION_CD = Vector3(CENTER_POINT - ORIGIN_IN_CD).Normalize();
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_CD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector3 DIRECTION_DA = Vector3(CENTER_POINT - ORIGIN_IN_DA).Normalize();
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_DA);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_EF = Vector3(CENTER_POINT - ORIGIN_IN_EF).Normalize();
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EF);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_FG = Vector3(CENTER_POINT - ORIGIN_IN_FG).Normalize();
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_FG);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_GH = Vector3(CENTER_POINT - ORIGIN_IN_GH).Normalize();
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_GH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_HE = Vector3(CENTER_POINT - ORIGIN_IN_HE).Normalize();
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_HE);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_DF = Vector3(CENTER_POINT - ORIGIN_IN_DF).Normalize();
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DF);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_AE = Vector3(CENTER_POINT - ORIGIN_IN_AE).Normalize();
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AE);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_BH = Vector3(CENTER_POINT - ORIGIN_IN_BH).Normalize();
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_BH);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_CG = Vector3(CENTER_POINT - ORIGIN_IN_CG).Normalize();
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_CG);

    const T EXPECTED_FIRSTPOINT_AB = ORIGIN_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = ORIGIN_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = ORIGIN_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = ORIGIN_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = ORIGIN_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = ORIGIN_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = ORIGIN_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = ORIGIN_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = ORIGIN_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = ORIGIN_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = ORIGIN_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = ORIGIN_IN_CG;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;

	// [Execution]
    EIntersections eResultAB = RAY_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EIntersections eResultBC = RAY_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EIntersections eResultCD = RAY_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EIntersections eResultDA = RAY_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EIntersections eResultEF = RAY_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EIntersections eResultFG = RAY_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EIntersections eResultGH = RAY_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EIntersections eResultHE = RAY_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EIntersections eResultDF = RAY_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EIntersections eResultAE = RAY_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EIntersections eResultBH = RAY_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EIntersections eResultCG = RAY_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(eResultEF == EXPECTED_RESULT);
    BOOST_CHECK(eResultFG == EXPECTED_RESULT);
    BOOST_CHECK(eResultGH == EXPECTED_RESULT);
    BOOST_CHECK(eResultHE == EXPECTED_RESULT);
    BOOST_CHECK(eResultDF == EXPECTED_RESULT);
    BOOST_CHECK(eResultAE == EXPECTED_RESULT);
    BOOST_CHECK(eResultBH == EXPECTED_RESULT);
    BOOST_CHECK(eResultCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenRayIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const T EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const T EXPECTED_FIRSTPOINT_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T ORIGIN_OVER  = T(ORIGIN_OVER_COMPONENTS);  // For edges of face ABCD
    const T ORIGIN_BELOW = T(ORIGIN_BELOW_COMPONENTS); // For edges of face EFGH
    const T ORIGIN_LEFT  = T(ORIGIN_LEFT_COMPONENTS);  // For edges of face ABHE
    const T ORIGIN_RIGHT = T(ORIGIN_RIGHT_COMPONENTS); // For edges of face CDFG

    const Vector3 DIRECTION_TO_AB = Vector3(EXPECTED_FIRSTPOINT_AB - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_AB = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_AB);

    const Vector3 DIRECTION_TO_BC = Vector3(EXPECTED_FIRSTPOINT_BC - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_BC = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_BC);

    const Vector3 DIRECTION_TO_CD = Vector3(EXPECTED_FIRSTPOINT_CD - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_CD = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_CD);

    const Vector3 DIRECTION_TO_DA = Vector3(EXPECTED_FIRSTPOINT_DA - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_DA = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_DA);

    const Vector3 DIRECTION_TO_EF = Vector3(EXPECTED_FIRSTPOINT_EF - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_EF = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_EF);

    const Vector3 DIRECTION_TO_FG = Vector3(EXPECTED_FIRSTPOINT_FG - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_FG = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_FG);

    const Vector3 DIRECTION_TO_GH = Vector3(EXPECTED_FIRSTPOINT_GH - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_GH = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_GH);

    const Vector3 DIRECTION_TO_HE = Vector3(EXPECTED_FIRSTPOINT_HE - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_HE = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_HE);

    const Vector3 DIRECTION_TO_DF = Vector3(EXPECTED_FIRSTPOINT_DF - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_DF = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_DF);

    const Vector3 DIRECTION_TO_AE = Vector3(EXPECTED_FIRSTPOINT_AE - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_AE = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_AE);

    const Vector3 DIRECTION_TO_BH = Vector3(EXPECTED_FIRSTPOINT_BH - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_BH = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_BH);

    const Vector3 DIRECTION_TO_CG = Vector3(EXPECTED_FIRSTPOINT_CG - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_CG = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;

	// [Execution]
    EIntersections eIntersectionsWithAB = RAY_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EIntersections eIntersectionsWithBC = RAY_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EIntersections eIntersectionsWithCD = RAY_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EIntersections eIntersectionsWithDA = RAY_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EIntersections eIntersectionsWithEF = RAY_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EIntersections eIntersectionsWithFG = RAY_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EIntersections eIntersectionsWithGH = RAY_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EIntersections eIntersectionsWithHE = RAY_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EIntersections eIntersectionsWithDF = RAY_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EIntersections eIntersectionsWithAE = RAY_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EIntersections eIntersectionsWithBH = RAY_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EIntersections eIntersectionsWithCG = RAY_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK(eIntersectionsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithCD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithDA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithEF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithFG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithGH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithHE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithDF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithAE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithBH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsOneIntersectionWhenOriginAndHexahedronVertexCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Ray3D<T> RAY_FROM_A = Ray3D<T>(VERTEX_A, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_B = Ray3D<T>(VERTEX_B, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_C = Ray3D<T>(VERTEX_C, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_D = Ray3D<T>(VERTEX_D, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_E = Ray3D<T>(VERTEX_E, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_F = Ray3D<T>(VERTEX_F, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_G = Ray3D<T>(VERTEX_G, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_H = Ray3D<T>(VERTEX_H, DIRECTION_AEHB);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;

	// [Execution]
    EIntersections eResultA = RAY_FROM_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA);
    EIntersections eResultB = RAY_FROM_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB);
    EIntersections eResultC = RAY_FROM_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC);
    EIntersections eResultD = RAY_FROM_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD);
    EIntersections eResultE = RAY_FROM_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE);
    EIntersections eResultF = RAY_FROM_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF);
    EIntersections eResultG = RAY_FROM_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG);
    EIntersections eResultH = RAY_FROM_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(eResultE == EXPECTED_RESULT);
    BOOST_CHECK(eResultF == EXPECTED_RESULT);
    BOOST_CHECK(eResultG == EXPECTED_RESULT);
    BOOST_CHECK(eResultH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray and a vertex of the hexahedron coincide and the direction points to the interior.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ReturnsTwoIntersectionWhenOriginAndHexahedronVertexCoincideAndDirectionPointsToInterior_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const Vector3 DIRECTION_FROM_A = Vector3(CENTER_POINT - VERTEX_A).Normalize();
    const Vector3 DIRECTION_FROM_B = Vector3(CENTER_POINT - VERTEX_B).Normalize();
    const Vector3 DIRECTION_FROM_C = Vector3(CENTER_POINT - VERTEX_C).Normalize();
    const Vector3 DIRECTION_FROM_D = Vector3(CENTER_POINT - VERTEX_D).Normalize();
    const Vector3 DIRECTION_FROM_E = Vector3(CENTER_POINT - VERTEX_E).Normalize();
    const Vector3 DIRECTION_FROM_F = Vector3(CENTER_POINT - VERTEX_F).Normalize();
    const Vector3 DIRECTION_FROM_G = Vector3(CENTER_POINT - VERTEX_G).Normalize();
    const Vector3 DIRECTION_FROM_H = Vector3(CENTER_POINT - VERTEX_H).Normalize();
    const Ray3D<T> RAY_FROM_A = Ray3D<T>(VERTEX_A, DIRECTION_FROM_A);
    const Ray3D<T> RAY_FROM_B = Ray3D<T>(VERTEX_B, DIRECTION_FROM_B);
    const Ray3D<T> RAY_FROM_C = Ray3D<T>(VERTEX_C, DIRECTION_FROM_C);
    const Ray3D<T> RAY_FROM_D = Ray3D<T>(VERTEX_D, DIRECTION_FROM_D);
    const Ray3D<T> RAY_FROM_E = Ray3D<T>(VERTEX_E, DIRECTION_FROM_E);
    const Ray3D<T> RAY_FROM_F = Ray3D<T>(VERTEX_F, DIRECTION_FROM_F);
    const Ray3D<T> RAY_FROM_G = Ray3D<T>(VERTEX_G, DIRECTION_FROM_G);
    const Ray3D<T> RAY_FROM_H = Ray3D<T>(VERTEX_H, DIRECTION_FROM_H);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;

	// [Execution]
    EIntersections eResultA = RAY_FROM_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA);
    EIntersections eResultB = RAY_FROM_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB);
    EIntersections eResultC = RAY_FROM_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC);
    EIntersections eResultD = RAY_FROM_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD);
    EIntersections eResultE = RAY_FROM_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE);
    EIntersections eResultF = RAY_FROM_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF);
    EIntersections eResultG = RAY_FROM_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG);
    EIntersections eResultH = RAY_FROM_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(eResultE == EXPECTED_RESULT);
    BOOST_CHECK(eResultF == EXPECTED_RESULT);
    BOOST_CHECK(eResultG == EXPECTED_RESULT);
    BOOST_CHECK(eResultH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, -SFloat::_4, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_z EXPECTED_FIRSTCOMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_0 };
    const T EXPECTED_FIRSTPOINT = T(EXPECTED_FIRSTCOMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;

    try
    {
        RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint7_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;

    try
    {
        RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
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
/// Checks that W component of output point does not change when intersections are detected.
/// </summary>
ZTEST_CASE ( IntersectionPoint7_WComponentDoesNotChangeWhenIntersectionsAreDetected_Test )
{

    // [Preparation]
    const Vector4 VERTEX_A = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_B = Vector4(SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_C = Vector4(SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_D = Vector4(SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_E = Vector4(SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_F = Vector4(SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_G = Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_H = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);

    const BaseHexahedron<Vector4> HEXAHEDRON = BaseHexahedron<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const Vector4 INTERSECTION_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);

    const Vector3 DIRECTION = Vector3(INTERSECTION_POINT).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(Vector4::GetNullVector(), DIRECTION);

    const float_z EXPECTED_FIRST_WCOMPONENT = SFloat::_5;

    // [Execution]
    Vector4 vFirstIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_FIRST_WCOMPONENT);
    RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(vFirstIntersection.w == EXPECTED_FIRST_WCOMPONENT);
}

/// <summary>
/// Checks that it returns expected intersection points when a common ray and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsExpectedIntersectionsWhenCommonRayIntersectsWithCommonHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_z EXPECTED_FIRSTCOMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_0 };
    const T EXPECTED_FIRSTPOINT = T(EXPECTED_FIRSTCOMPONENTS);
    const float_z EXPECTED_SECONDCOMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T EXPECTED_SECONDPOINT = T(EXPECTED_SECONDCOMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersection;
    T vSecondIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common ray intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenRayIntersectsWithHexahedronVertex_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const float_z ORIGIN_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T ORIGIN_LEFT(ORIGIN_COMPONENTS_LEFT);

    const float_z ORIGIN_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T ORIGIN_RIGHT(ORIGIN_COMPONENTS_RIGHT);

    const Vector3 DIRECTION_A = Vector3(VERTEX_A - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_B = Vector3(VERTEX_B - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_C = Vector3(VERTEX_C - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_D = Vector3(VERTEX_D - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_E = Vector3(VERTEX_E - ORIGIN_LEFT).Normalize();
    const Vector3 DIRECTION_F = Vector3(VERTEX_F - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_G = Vector3(VERTEX_G - ORIGIN_RIGHT).Normalize();
    const Vector3 DIRECTION_H = Vector3(VERTEX_H - ORIGIN_LEFT).Normalize();

    const Ray3D<T> RAY_A = Ray3D<T>(ORIGIN_LEFT, DIRECTION_A);
    const Ray3D<T> RAY_B = Ray3D<T>(ORIGIN_LEFT, DIRECTION_B);
    const Ray3D<T> RAY_C = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_C);
    const Ray3D<T> RAY_D = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_D);
    const Ray3D<T> RAY_E = Ray3D<T>(ORIGIN_LEFT, DIRECTION_E);
    const Ray3D<T> RAY_F = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_F);
    const Ray3D<T> RAY_G = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_G);
    const Ray3D<T> RAY_H = Ray3D<T>(ORIGIN_LEFT, DIRECTION_H);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;
    T vSecondIntersectionA = T::GetNullVector();
    T vSecondIntersectionB = T::GetNullVector();
    T vSecondIntersectionC = T::GetNullVector();
    T vSecondIntersectionD = T::GetNullVector();
    T vSecondIntersectionE = T::GetNullVector();
    T vSecondIntersectionF = T::GetNullVector();
    T vSecondIntersectionG = T::GetNullVector();
    T vSecondIntersectionH = T::GetNullVector();

	// [Execution]
    EIntersections eIntersectionWithA = RAY_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eIntersectionWithB = RAY_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eIntersectionWithC = RAY_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eIntersectionWithD = RAY_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD, vSecondIntersectionD);
    EIntersections eIntersectionWithE = RAY_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE, vSecondIntersectionE);
    EIntersections eIntersectionWithF = RAY_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF, vSecondIntersectionF);
    EIntersections eIntersectionWithG = RAY_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG, vSecondIntersectionG);
    EIntersections eIntersectionWithH = RAY_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH, vSecondIntersectionH);

    // [Verification]
    BOOST_CHECK(eIntersectionWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionWithH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection points when a common ray and a common hexahedron would intersect if the ray pointed to the opposite direction.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsNoIntersectionsWhenRayDoesNotIntersectWithHexahedronButWouldDoIfRayPointedOppositeDirection_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, -DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenOriginIsContainedInHexahedronFace_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    // Note: Directions equal face normals
    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = ORIGIN_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = ORIGIN_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = ORIGIN_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = ORIGIN_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = ORIGIN_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = ORIGIN_EFGH;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    T vFirstIntersectionDFGC = T::GetNullVector();
    T vFirstIntersectionADFE = T::GetNullVector();
    T vFirstIntersectionAEHB = T::GetNullVector();
    T vFirstIntersectionCGHB = T::GetNullVector();
    T vFirstIntersectionABCD = T::GetNullVector();
    T vFirstIntersectionEFGH = T::GetNullVector();
    T vSecondIntersectionDFGC = T::GetNullVector();
    T vSecondIntersectionADFE = T::GetNullVector();
    T vSecondIntersectionAEHB = T::GetNullVector();
    T vSecondIntersectionCGHB = T::GetNullVector();
    T vSecondIntersectionABCD = T::GetNullVector();
    T vSecondIntersectionEFGH = T::GetNullVector();

	// [Execution]
    EIntersections eResultDFGC = RAY_IN_DFGC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC, vSecondIntersectionDFGC);
    EIntersections eResultADFE = RAY_IN_ADFE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE, vSecondIntersectionADFE);
    EIntersections eResultAEHB = RAY_IN_AEHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB, vSecondIntersectionAEHB);
    EIntersections eResultCGHB = RAY_IN_CGHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB, vSecondIntersectionCGHB);
    EIntersections eResultABCD = RAY_IN_ABCD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD, vSecondIntersectionABCD);
    EIntersections eResultEFGH = RAY_IN_EFGH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH, vSecondIntersectionEFGH);

    // [Verification]
    BOOST_CHECK(eResultDFGC == EXPECTED_RESULT);
    BOOST_CHECK(eResultADFE == EXPECTED_RESULT);
    BOOST_CHECK(eResultAEHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultCGHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultABCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultEFGH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vSecondIntersectionDFGC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionADFE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAEHB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCGHB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionABCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEFGH == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the ray belongs to a face of the hexahedron (it contains its origin and direction is parallel).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsTwoIntersectionsWhenRayBelongsToHexahedronFace_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T CENTER_POINT_FG = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_F);
    const T CENTER_POINT_AD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_D);
    const T CENTER_POINT_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const T CENTER_POINT_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const T CENTER_POINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T CENTER_POINT_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);

    const T ORIGIN_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_DFGC = Vector3(CENTER_POINT_FG - ORIGIN_DFGC).Normalize();
    const Ray3D<T> RAY_IN_DFGC = Ray3D<T>(ORIGIN_DFGC, DIRECTION_DFGC);

    const T ORIGIN_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_ADFE = Vector3(CENTER_POINT_AD - ORIGIN_ADFE).Normalize();
    const Ray3D<T> RAY_IN_ADFE = Ray3D<T>(ORIGIN_ADFE, DIRECTION_ADFE);

    const T ORIGIN_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_AEHB = Vector3(CENTER_POINT_AE - ORIGIN_AEHB).Normalize();
    const Ray3D<T> RAY_IN_AEHB = Ray3D<T>(ORIGIN_AEHB, DIRECTION_AEHB);

    const T ORIGIN_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_CGHB = Vector3(CENTER_POINT_CG - ORIGIN_CGHB).Normalize();
    const Ray3D<T> RAY_IN_CGHB = Ray3D<T>(ORIGIN_CGHB, DIRECTION_CGHB);

    const T ORIGIN_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_ABCD = Vector3(CENTER_POINT_AB - ORIGIN_ABCD).Normalize();
    const Ray3D<T> RAY_IN_ABCD = Ray3D<T>(ORIGIN_ABCD, DIRECTION_ABCD);

    const T ORIGIN_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_EFGH = Vector3(CENTER_POINT_EF - ORIGIN_EFGH).Normalize();
    const Ray3D<T> RAY_IN_EFGH = Ray3D<T>(ORIGIN_EFGH, DIRECTION_EFGH);

    const T EXPECTED_FIRSTPOINT_DFGC = ORIGIN_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = ORIGIN_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = ORIGIN_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = ORIGIN_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = ORIGIN_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = ORIGIN_EFGH;
    const T EXPECTED_SECONDPOINT_DFGC = CENTER_POINT_FG;
    const T EXPECTED_SECONDPOINT_ADFE = CENTER_POINT_AD;
    const T EXPECTED_SECONDPOINT_AEHB = CENTER_POINT_AE;
    const T EXPECTED_SECONDPOINT_CGHB = CENTER_POINT_CG;
    const T EXPECTED_SECONDPOINT_ABCD = CENTER_POINT_AB;
    const T EXPECTED_SECONDPOINT_EFGH = CENTER_POINT_EF;

    T vFirstIntersectionDFGC = T::GetNullVector();
    T vFirstIntersectionADFE = T::GetNullVector();
    T vFirstIntersectionAEHB = T::GetNullVector();
    T vFirstIntersectionCGHB = T::GetNullVector();
    T vFirstIntersectionABCD = T::GetNullVector();
    T vFirstIntersectionEFGH = T::GetNullVector();
    T vSecondIntersectionDFGC = T::GetNullVector();
    T vSecondIntersectionADFE = T::GetNullVector();
    T vSecondIntersectionAEHB = T::GetNullVector();
    T vSecondIntersectionCGHB = T::GetNullVector();
    T vSecondIntersectionABCD = T::GetNullVector();
    T vSecondIntersectionEFGH = T::GetNullVector();

	// [Execution]
    EIntersections eResultDFGC = RAY_IN_DFGC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC, vSecondIntersectionDFGC);
    EIntersections eResultADFE = RAY_IN_ADFE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE, vSecondIntersectionADFE);
    EIntersections eResultAEHB = RAY_IN_AEHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB, vSecondIntersectionAEHB);
    EIntersections eResultCGHB = RAY_IN_CGHB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB, vSecondIntersectionCGHB);
    EIntersections eResultABCD = RAY_IN_ABCD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD, vSecondIntersectionABCD);
    EIntersections eResultEFGH = RAY_IN_EFGH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH, vSecondIntersectionEFGH);

    // [Verification]
    BOOST_CHECK(eResultDFGC == EXPECTED_RESULT);
    BOOST_CHECK(eResultADFE == EXPECTED_RESULT);
    BOOST_CHECK(eResultAEHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultCGHB == EXPECTED_RESULT);
    BOOST_CHECK(eResultABCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultEFGH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vSecondIntersectionDFGC == EXPECTED_SECONDPOINT_DFGC);
    BOOST_CHECK(vSecondIntersectionADFE == EXPECTED_SECONDPOINT_ADFE);
    BOOST_CHECK(vSecondIntersectionAEHB == EXPECTED_SECONDPOINT_AEHB);
    BOOST_CHECK(vSecondIntersectionCGHB == EXPECTED_SECONDPOINT_CGHB);
    BOOST_CHECK(vSecondIntersectionABCD == EXPECTED_SECONDPOINT_ABCD);
    BOOST_CHECK(vSecondIntersectionEFGH == EXPECTED_SECONDPOINT_EFGH);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of a ray is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenOriginIsContainedInHexahedron_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_D);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    const T ORIGIN = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION = Vector3(EXPECTED_FIRSTPOINT - ORIGIN).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    T vFirstIntersection;
    T vSecondIntersection = T::GetNullVector();

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenOriginBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 DIRECTION_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_ABCD);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_ABCD);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_ABCD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_ABCD);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EFGH);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_EFGH);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_EFGH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_EFGH);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DFGC);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AEHB);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_AEHB);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_DFGC);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = ORIGIN_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = ORIGIN_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = ORIGIN_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = ORIGIN_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = ORIGIN_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = ORIGIN_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = ORIGIN_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = ORIGIN_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = ORIGIN_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = ORIGIN_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = ORIGIN_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = ORIGIN_IN_CG;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCD = T::GetNullVector();
    T vSecondIntersectionDA = T::GetNullVector();
    T vSecondIntersectionEF = T::GetNullVector();
    T vSecondIntersectionFG = T::GetNullVector();
    T vSecondIntersectionGH = T::GetNullVector();
    T vSecondIntersectionHE = T::GetNullVector();
    T vSecondIntersectionDF = T::GetNullVector();
    T vSecondIntersectionAE = T::GetNullVector();
    T vSecondIntersectionBH = T::GetNullVector();
    T vSecondIntersectionCG = T::GetNullVector();

	// [Execution]
    EIntersections eResultAB = RAY_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eResultBC = RAY_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eResultCD = RAY_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eResultDA = RAY_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eResultEF = RAY_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eResultFG = RAY_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eResultGH = RAY_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eResultHE = RAY_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eResultDF = RAY_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eResultAE = RAY_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eResultBH = RAY_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eResultCG = RAY_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(eResultEF == EXPECTED_RESULT);
    BOOST_CHECK(eResultFG == EXPECTED_RESULT);
    BOOST_CHECK(eResultGH == EXPECTED_RESULT);
    BOOST_CHECK(eResultHE == EXPECTED_RESULT);
    BOOST_CHECK(eResultDF == EXPECTED_RESULT);
    BOOST_CHECK(eResultAE == EXPECTED_RESULT);
    BOOST_CHECK(eResultBH == EXPECTED_RESULT);
    BOOST_CHECK(eResultCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray is contained in an edge of the hexahedron and its direction points to interior.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsTwoIntersectionsWhenOriginBelongsToEdgeOfHexahedronAndDirectionPointsToInterior_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector3 DIRECTION_AB = Vector3(CENTER_POINT - ORIGIN_IN_AB).Normalize();
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_AB);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_BC = Vector3(CENTER_POINT - ORIGIN_IN_BC).Normalize();
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_BC);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector3 DIRECTION_CD = Vector3(CENTER_POINT - ORIGIN_IN_CD).Normalize();
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_CD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector3 DIRECTION_DA = Vector3(CENTER_POINT - ORIGIN_IN_DA).Normalize();
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_DA);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_EF = Vector3(CENTER_POINT - ORIGIN_IN_EF).Normalize();
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EF);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_FG = Vector3(CENTER_POINT - ORIGIN_IN_FG).Normalize();
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_FG);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_GH = Vector3(CENTER_POINT - ORIGIN_IN_GH).Normalize();
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_GH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_HE = Vector3(CENTER_POINT - ORIGIN_IN_HE).Normalize();
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_HE);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_DF = Vector3(CENTER_POINT - ORIGIN_IN_DF).Normalize();
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DF);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_AE = Vector3(CENTER_POINT - ORIGIN_IN_AE).Normalize();
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AE);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_BH = Vector3(CENTER_POINT - ORIGIN_IN_BH).Normalize();
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_BH);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_CG = Vector3(CENTER_POINT - ORIGIN_IN_CG).Normalize();
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_CG);

    const T EXPECTED_FIRSTPOINT_AB = ORIGIN_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = ORIGIN_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = ORIGIN_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = ORIGIN_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = ORIGIN_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = ORIGIN_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = ORIGIN_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = ORIGIN_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = ORIGIN_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = ORIGIN_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = ORIGIN_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = ORIGIN_IN_CG;
    const T EXPECTED_SECONDPOINT_AB = ORIGIN_IN_FG;
    const T EXPECTED_SECONDPOINT_BC = ORIGIN_IN_EF;
    const T EXPECTED_SECONDPOINT_CD = ORIGIN_IN_HE;
    const T EXPECTED_SECONDPOINT_DA = ORIGIN_IN_GH;
    const T EXPECTED_SECONDPOINT_EF = ORIGIN_IN_BC;
    const T EXPECTED_SECONDPOINT_FG = ORIGIN_IN_AB;
    const T EXPECTED_SECONDPOINT_GH = ORIGIN_IN_DA;
    const T EXPECTED_SECONDPOINT_HE = ORIGIN_IN_CD;
    const T EXPECTED_SECONDPOINT_DF = ORIGIN_IN_BH;
    const T EXPECTED_SECONDPOINT_AE = ORIGIN_IN_CG;
    const T EXPECTED_SECONDPOINT_BH = ORIGIN_IN_DF;
    const T EXPECTED_SECONDPOINT_CG = ORIGIN_IN_AE;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB;
    T vSecondIntersectionBC;
    T vSecondIntersectionCD;
    T vSecondIntersectionDA;
    T vSecondIntersectionEF;
    T vSecondIntersectionFG;
    T vSecondIntersectionGH;
    T vSecondIntersectionHE;
    T vSecondIntersectionDF;
    T vSecondIntersectionAE;
    T vSecondIntersectionBH;
    T vSecondIntersectionCG;

	// [Execution]
    EIntersections eResultAB = RAY_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eResultBC = RAY_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eResultCD = RAY_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eResultDA = RAY_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eResultEF = RAY_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eResultFG = RAY_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eResultGH = RAY_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eResultHE = RAY_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eResultDF = RAY_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eResultAE = RAY_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eResultBH = RAY_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eResultCG = RAY_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(eResultEF == EXPECTED_RESULT);
    BOOST_CHECK(eResultFG == EXPECTED_RESULT);
    BOOST_CHECK(eResultGH == EXPECTED_RESULT);
    BOOST_CHECK(eResultHE == EXPECTED_RESULT);
    BOOST_CHECK(eResultDF == EXPECTED_RESULT);
    BOOST_CHECK(eResultAE == EXPECTED_RESULT);
    BOOST_CHECK(eResultBH == EXPECTED_RESULT);
    BOOST_CHECK(eResultCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT_EF);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT_FG);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT_GH);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT_HE);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT_DF);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT_AE);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT_BH);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT_CG);
}

/// <summary>
/// Checks that it returns one intersection point when the ray intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenRayIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const T EXPECTED_FIRSTPOINT_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const T EXPECTED_FIRSTPOINT_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const T EXPECTED_FIRSTPOINT_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const T EXPECTED_FIRSTPOINT_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const T EXPECTED_FIRSTPOINT_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z ORIGIN_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z ORIGIN_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T ORIGIN_OVER  = T(ORIGIN_OVER_COMPONENTS);  // For edges of face ABCD
    const T ORIGIN_BELOW = T(ORIGIN_BELOW_COMPONENTS); // For edges of face EFGH
    const T ORIGIN_LEFT  = T(ORIGIN_LEFT_COMPONENTS);  // For edges of face ABHE
    const T ORIGIN_RIGHT = T(ORIGIN_RIGHT_COMPONENTS); // For edges of face CDFG

    const Vector3 DIRECTION_TO_AB = Vector3(EXPECTED_FIRSTPOINT_AB - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_AB = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_AB);

    const Vector3 DIRECTION_TO_BC = Vector3(EXPECTED_FIRSTPOINT_BC - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_BC = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_BC);

    const Vector3 DIRECTION_TO_CD = Vector3(EXPECTED_FIRSTPOINT_CD - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_CD = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_CD);

    const Vector3 DIRECTION_TO_DA = Vector3(EXPECTED_FIRSTPOINT_DA - ORIGIN_OVER).Normalize();
    const Ray3D<T> RAY_TO_DA = Ray3D<T>(ORIGIN_OVER, DIRECTION_TO_DA);

    const Vector3 DIRECTION_TO_EF = Vector3(EXPECTED_FIRSTPOINT_EF - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_EF = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_EF);

    const Vector3 DIRECTION_TO_FG = Vector3(EXPECTED_FIRSTPOINT_FG - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_FG = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_FG);

    const Vector3 DIRECTION_TO_GH = Vector3(EXPECTED_FIRSTPOINT_GH - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_GH = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_GH);

    const Vector3 DIRECTION_TO_HE = Vector3(EXPECTED_FIRSTPOINT_HE - ORIGIN_BELOW).Normalize();
    const Ray3D<T> RAY_TO_HE = Ray3D<T>(ORIGIN_BELOW, DIRECTION_TO_HE);

    const Vector3 DIRECTION_TO_DF = Vector3(EXPECTED_FIRSTPOINT_DF - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_DF = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_DF);

    const Vector3 DIRECTION_TO_AE = Vector3(EXPECTED_FIRSTPOINT_AE - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_AE = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_AE);

    const Vector3 DIRECTION_TO_BH = Vector3(EXPECTED_FIRSTPOINT_BH - ORIGIN_LEFT).Normalize();
    const Ray3D<T> RAY_TO_BH = Ray3D<T>(ORIGIN_LEFT, DIRECTION_TO_BH);

    const Vector3 DIRECTION_TO_CG = Vector3(EXPECTED_FIRSTPOINT_CG - ORIGIN_RIGHT).Normalize();
    const Ray3D<T> RAY_TO_CG = Ray3D<T>(ORIGIN_RIGHT, DIRECTION_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCD = T::GetNullVector();
    T vSecondIntersectionDA = T::GetNullVector();
    T vSecondIntersectionEF = T::GetNullVector();
    T vSecondIntersectionFG = T::GetNullVector();
    T vSecondIntersectionGH = T::GetNullVector();
    T vSecondIntersectionHE = T::GetNullVector();
    T vSecondIntersectionDF = T::GetNullVector();
    T vSecondIntersectionAE = T::GetNullVector();
    T vSecondIntersectionBH = T::GetNullVector();
    T vSecondIntersectionCG = T::GetNullVector();

	// [Execution]
    EIntersections eIntersectionsWithAB = RAY_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eIntersectionsWithBC = RAY_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eIntersectionsWithCD = RAY_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eIntersectionsWithDA = RAY_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eIntersectionsWithEF = RAY_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eIntersectionsWithFG = RAY_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eIntersectionsWithGH = RAY_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eIntersectionsWithHE = RAY_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eIntersectionsWithDF = RAY_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eIntersectionsWithAE = RAY_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eIntersectionsWithBH = RAY_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eIntersectionsWithCG = RAY_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eIntersectionsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithCD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithDA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithEF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithFG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithGH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithHE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithDF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithAE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithBH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the origin of the ray and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsOneIntersectionWhenOriginAndHexahedronVertexCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const Vector3 DIRECTION_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 DIRECTION_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Ray3D<T> RAY_FROM_A = Ray3D<T>(VERTEX_A, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_B = Ray3D<T>(VERTEX_B, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_C = Ray3D<T>(VERTEX_C, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_D = Ray3D<T>(VERTEX_D, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_E = Ray3D<T>(VERTEX_E, DIRECTION_AEHB);
    const Ray3D<T> RAY_FROM_F = Ray3D<T>(VERTEX_F, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_G = Ray3D<T>(VERTEX_G, DIRECTION_DFGC);
    const Ray3D<T> RAY_FROM_H = Ray3D<T>(VERTEX_H, DIRECTION_AEHB);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;
    T vSecondIntersectionA;
    T vSecondIntersectionB;
    T vSecondIntersectionC;
    T vSecondIntersectionD;
    T vSecondIntersectionE;
    T vSecondIntersectionF;
    T vSecondIntersectionG;
    T vSecondIntersectionH;

	// [Execution]
    EIntersections eResultA = RAY_FROM_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eResultB = RAY_FROM_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eResultC = RAY_FROM_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eResultD = RAY_FROM_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD, vSecondIntersectionD);
    EIntersections eResultE = RAY_FROM_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE, vSecondIntersectionE);
    EIntersections eResultF = RAY_FROM_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF, vSecondIntersectionF);
    EIntersections eResultG = RAY_FROM_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG, vSecondIntersectionG);
    EIntersections eResultH = RAY_FROM_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH, vSecondIntersectionH);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(eResultE == EXPECTED_RESULT);
    BOOST_CHECK(eResultF == EXPECTED_RESULT);
    BOOST_CHECK(eResultG == EXPECTED_RESULT);
    BOOST_CHECK(eResultH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the origin of the ray and a vertex of the hexahedron coincide and the direction points to the interior.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsTwoIntersectionWhenOriginAndHexahedronVertexCoincideAndDirectionPointsToInterior_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const Vector3 DIRECTION_FROM_A = Vector3(CENTER_POINT - VERTEX_A).Normalize();
    const Vector3 DIRECTION_FROM_B = Vector3(CENTER_POINT - VERTEX_B).Normalize();
    const Vector3 DIRECTION_FROM_C = Vector3(CENTER_POINT - VERTEX_C).Normalize();
    const Vector3 DIRECTION_FROM_D = Vector3(CENTER_POINT - VERTEX_D).Normalize();
    const Vector3 DIRECTION_FROM_E = Vector3(CENTER_POINT - VERTEX_E).Normalize();
    const Vector3 DIRECTION_FROM_F = Vector3(CENTER_POINT - VERTEX_F).Normalize();
    const Vector3 DIRECTION_FROM_G = Vector3(CENTER_POINT - VERTEX_G).Normalize();
    const Vector3 DIRECTION_FROM_H = Vector3(CENTER_POINT - VERTEX_H).Normalize();
    const Ray3D<T> RAY_FROM_A = Ray3D<T>(VERTEX_A, DIRECTION_FROM_A);
    const Ray3D<T> RAY_FROM_B = Ray3D<T>(VERTEX_B, DIRECTION_FROM_B);
    const Ray3D<T> RAY_FROM_C = Ray3D<T>(VERTEX_C, DIRECTION_FROM_C);
    const Ray3D<T> RAY_FROM_D = Ray3D<T>(VERTEX_D, DIRECTION_FROM_D);
    const Ray3D<T> RAY_FROM_E = Ray3D<T>(VERTEX_E, DIRECTION_FROM_E);
    const Ray3D<T> RAY_FROM_F = Ray3D<T>(VERTEX_F, DIRECTION_FROM_F);
    const Ray3D<T> RAY_FROM_G = Ray3D<T>(VERTEX_G, DIRECTION_FROM_G);
    const Ray3D<T> RAY_FROM_H = Ray3D<T>(VERTEX_H, DIRECTION_FROM_H);

    const T EXPECTED_FIRSTPOINT_A = VERTEX_A;
    const T EXPECTED_FIRSTPOINT_B = VERTEX_B;
    const T EXPECTED_FIRSTPOINT_C = VERTEX_C;
    const T EXPECTED_FIRSTPOINT_D = VERTEX_D;
    const T EXPECTED_FIRSTPOINT_E = VERTEX_E;
    const T EXPECTED_FIRSTPOINT_F = VERTEX_F;
    const T EXPECTED_FIRSTPOINT_G = VERTEX_G;
    const T EXPECTED_FIRSTPOINT_H = VERTEX_H;
    const T EXPECTED_SECONDPOINT_A = VERTEX_G;
    const T EXPECTED_SECONDPOINT_B = VERTEX_F;
    const T EXPECTED_SECONDPOINT_C = VERTEX_E;
    const T EXPECTED_SECONDPOINT_D = VERTEX_H;
    const T EXPECTED_SECONDPOINT_E = VERTEX_C;
    const T EXPECTED_SECONDPOINT_F = VERTEX_B;
    const T EXPECTED_SECONDPOINT_G = VERTEX_A;
    const T EXPECTED_SECONDPOINT_H = VERTEX_D;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;
    T vSecondIntersectionA;
    T vSecondIntersectionB;
    T vSecondIntersectionC;
    T vSecondIntersectionD;
    T vSecondIntersectionE;
    T vSecondIntersectionF;
    T vSecondIntersectionG;
    T vSecondIntersectionH;

	// [Execution]
    EIntersections eResultA = RAY_FROM_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eResultB = RAY_FROM_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eResultC = RAY_FROM_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eResultD = RAY_FROM_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD, vSecondIntersectionD);
    EIntersections eResultE = RAY_FROM_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE, vSecondIntersectionE);
    EIntersections eResultF = RAY_FROM_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF, vSecondIntersectionF);
    EIntersections eResultG = RAY_FROM_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG, vSecondIntersectionG);
    EIntersections eResultH = RAY_FROM_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH, vSecondIntersectionH);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(eResultE == EXPECTED_RESULT);
    BOOST_CHECK(eResultF == EXPECTED_RESULT);
    BOOST_CHECK(eResultG == EXPECTED_RESULT);
    BOOST_CHECK(eResultH == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT_A);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT_B);
    BOOST_CHECK(vSecondIntersectionC == EXPECTED_SECONDPOINT_C);
    BOOST_CHECK(vSecondIntersectionD == EXPECTED_SECONDPOINT_D);
    BOOST_CHECK(vSecondIntersectionE == EXPECTED_SECONDPOINT_E);
    BOOST_CHECK(vSecondIntersectionF == EXPECTED_SECONDPOINT_F);
    BOOST_CHECK(vSecondIntersectionG == EXPECTED_SECONDPOINT_G);
    BOOST_CHECK(vSecondIntersectionH == EXPECTED_SECONDPOINT_H);
}

/// <summary>
/// Checks that it is not necessary to normalize the ray to get correct results.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ItIsNotNecessaryToNormalizeTheRay_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_4, -SFloat::_4, SFloat::_0);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_z EXPECTED_FIRSTCOMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_0 };
    const T EXPECTED_FIRSTPOINT = T(EXPECTED_FIRSTCOMPONENTS);
    const float_z EXPECTED_SECONDCOMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T EXPECTED_SECONDPOINT = T(EXPECTED_SECONDCOMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersection;
    T vSecondIntersection;

	// [Execution]
    EIntersections eResult = RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the direction of the ray is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_AssertionFailsWhenRayDirectionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3::GetNullVector();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_3, SFloat::_3, SFloat::_1);
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
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
/// Checks that W component of output point does not change when intersections are detected.
/// </summary>
ZTEST_CASE ( IntersectionPoint8_WComponentDoesNotChangeWhenIntersectionsAreDetected_Test )
{

    // [Preparation]
    const Vector4 VERTEX_A = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_B = Vector4(SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_C = Vector4(SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_D = Vector4(SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_E = Vector4(SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_F = Vector4(SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0);
    const Vector4 VERTEX_G = Vector4(SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector4 VERTEX_H = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);

    const BaseHexahedron<Vector4> HEXAHEDRON = BaseHexahedron<Vector4>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const Vector4 INTERSECTION_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);

    const Vector3 DIRECTION = Vector3(INTERSECTION_POINT).Normalize();
    const Ray3D<Vector4> RAY = Ray3D<Vector4>(Vector4::GetNullVector(), DIRECTION);

    const float_z EXPECTED_FIRST_WCOMPONENT = SFloat::_5;
    const float_z EXPECTED_SECOND_WCOMPONENT = SFloat::_6;

    // [Execution]
    Vector4 vFirstIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_FIRST_WCOMPONENT);
    Vector4 vSecondIntersection = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, EXPECTED_SECOND_WCOMPONENT);
    RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(vFirstIntersection.w == EXPECTED_FIRST_WCOMPONENT);
    BOOST_CHECK(vSecondIntersection.w == EXPECTED_SECOND_WCOMPONENT);
}

/// <summary>
/// Checks that it returns the intersection point that is closer to the orign of the ray in the first output parameter.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_TheIntersectionPointThatIsCloserToOriginIsReturnedFirst_Test, TTemplateTypes )
{
    //
    //             A ________ D
    //            /|         /|
    //           / |        / |
    //    O---1-B__|_______C --2-->
    //          |  E_______|__F
    //          | /        | /
    //          |/         |/
    //          H_________ G
    //


    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { -SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { -SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { -SFloat::_1, SFloat::_3, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { -SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { -SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    T vFirstIntersection;
    T vSecondIntersection;

	// [Execution]
    RAY.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(SFloat::IsNegative(vFirstIntersection.x));
    BOOST_CHECK(SFloat::IsGreaterOrEquals(vSecondIntersection.x, SFloat::_0));
}

/// <summary>
/// Checks that it returns the second intersection point in both output parameters when using the same object for both.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_SecondIntersectionIsReturnedAsBothParametersWhenTheyAreTheSameObject_Test, TTemplateTypes )
{
    //
    //        A ________ D
    //       /|         /|
    //      / |        / |
    //     B__|_______C  |
    //     |  E_______|__F
    //     | /        | /
    //     |/         |/
    //     H_________ G
    //


    // [Preparation]
    const float_z ORIGIN_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const T ORIGIN(ORIGIN_COMPONENTS);
    const Vector3 DIRECTION = Vector3(SFloat::_1, -SFloat::_1, SFloat::_0).Normalize();
    const Ray3D<T> RAY = Ray3D<T>(ORIGIN, DIRECTION);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const float_z EXPECTED_FIRSTCOMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_0 };
    const T EXPECTED_FIRSTPOINT = T(EXPECTED_FIRSTCOMPONENTS);
    const float_z EXPECTED_SECONDCOMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_0 };
    const T EXPECTED_SECONDPOINT = T(EXPECTED_SECONDCOMPONENTS);

    T vIntersection;

	// [Execution]
    RAY.IntersectionPoint(HEXAHEDRON, vIntersection, vIntersection);

    // [Verification]
    BOOST_CHECK(vIntersection != EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the ray belongs to one edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint8_ReturnsTwoIntersectionsWhenRayBelongsToAnEdgeOfHexahedronAndDirectionPointsTo_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_0 };
    const float_z VERTEX_G_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0 };
    const float_z VERTEX_H_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const T VERTEX_D = T(VERTEX_D_COMPONENTS);
    const T VERTEX_E = T(VERTEX_E_COMPONENTS);
    const T VERTEX_F = T(VERTEX_F_COMPONENTS);
    const T VERTEX_G = T(VERTEX_G_COMPONENTS);
    const T VERTEX_H = T(VERTEX_H_COMPONENTS);
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T ORIGIN_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const Vector3 DIRECTION_AB = Vector3(VERTEX_A - ORIGIN_IN_AB).Normalize();
    const Ray3D<T> RAY_IN_AB = Ray3D<T>(ORIGIN_IN_AB, DIRECTION_AB);

    const T ORIGIN_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const Vector3 DIRECTION_BC = Vector3(VERTEX_B - ORIGIN_IN_BC).Normalize();
    const Ray3D<T> RAY_IN_BC = Ray3D<T>(ORIGIN_IN_BC, DIRECTION_BC);

    const T ORIGIN_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const Vector3 DIRECTION_CD = Vector3(VERTEX_C - ORIGIN_IN_CD).Normalize();
    const Ray3D<T> RAY_IN_CD = Ray3D<T>(ORIGIN_IN_CD, DIRECTION_CD);

    const T ORIGIN_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const Vector3 DIRECTION_DA = Vector3(VERTEX_D - ORIGIN_IN_DA).Normalize();
    const Ray3D<T> RAY_IN_DA = Ray3D<T>(ORIGIN_IN_DA, DIRECTION_DA);

    const T ORIGIN_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_EF = Vector3(VERTEX_E - ORIGIN_IN_EF).Normalize();
    const Ray3D<T> RAY_IN_EF = Ray3D<T>(ORIGIN_IN_EF, DIRECTION_EF);

    const T ORIGIN_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_FG = Vector3(VERTEX_F - ORIGIN_IN_FG).Normalize();
    const Ray3D<T> RAY_IN_FG = Ray3D<T>(ORIGIN_IN_FG, DIRECTION_FG);

    const T ORIGIN_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_GH = Vector3(VERTEX_G - ORIGIN_IN_GH).Normalize();
    const Ray3D<T> RAY_IN_GH = Ray3D<T>(ORIGIN_IN_GH, DIRECTION_GH);

    const T ORIGIN_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_HE = Vector3(VERTEX_H - ORIGIN_IN_HE).Normalize();
    const Ray3D<T> RAY_IN_HE = Ray3D<T>(ORIGIN_IN_HE, DIRECTION_HE);

    const T ORIGIN_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const Vector3 DIRECTION_DF = Vector3(VERTEX_D - ORIGIN_IN_DF).Normalize();
    const Ray3D<T> RAY_IN_DF = Ray3D<T>(ORIGIN_IN_DF, DIRECTION_DF);

    const T ORIGIN_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const Vector3 DIRECTION_AE = Vector3(VERTEX_E - ORIGIN_IN_AE).Normalize();
    const Ray3D<T> RAY_IN_AE = Ray3D<T>(ORIGIN_IN_AE, DIRECTION_AE);

    const T ORIGIN_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const Vector3 DIRECTION_BH = Vector3(VERTEX_B - ORIGIN_IN_BH).Normalize();
    const Ray3D<T> RAY_IN_BH = Ray3D<T>(ORIGIN_IN_BH, DIRECTION_BH);

    const T ORIGIN_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const Vector3 DIRECTION_CG = Vector3(VERTEX_C - ORIGIN_IN_CG).Normalize();
    const Ray3D<T> RAY_IN_CG = Ray3D<T>(ORIGIN_IN_CG, DIRECTION_CG);

    const T EXPECTED_FIRSTPOINT_AB = ORIGIN_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = ORIGIN_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = ORIGIN_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = ORIGIN_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = ORIGIN_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = ORIGIN_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = ORIGIN_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = ORIGIN_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = ORIGIN_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = ORIGIN_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = ORIGIN_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = ORIGIN_IN_CG;
    const T EXPECTED_SECONDPOINT_AB = VERTEX_A;
    const T EXPECTED_SECONDPOINT_BC = VERTEX_B;
    const T EXPECTED_SECONDPOINT_CD = VERTEX_C;
    const T EXPECTED_SECONDPOINT_DA = VERTEX_D;
    const T EXPECTED_SECONDPOINT_EF = VERTEX_E;
    const T EXPECTED_SECONDPOINT_FG = VERTEX_F;
    const T EXPECTED_SECONDPOINT_GH = VERTEX_G;
    const T EXPECTED_SECONDPOINT_HE = VERTEX_H;
    const T EXPECTED_SECONDPOINT_DF = VERTEX_D;
    const T EXPECTED_SECONDPOINT_AE = VERTEX_E;
    const T EXPECTED_SECONDPOINT_BH = VERTEX_B;
    const T EXPECTED_SECONDPOINT_CG = VERTEX_C;
    
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCD;
    T vFirstIntersectionDA;
    T vFirstIntersectionEF;
    T vFirstIntersectionFG;
    T vFirstIntersectionGH;
    T vFirstIntersectionHE;
    T vFirstIntersectionDF;
    T vFirstIntersectionAE;
    T vFirstIntersectionBH;
    T vFirstIntersectionCG;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCD = T::GetNullVector();
    T vSecondIntersectionDA = T::GetNullVector();
    T vSecondIntersectionEF = T::GetNullVector();
    T vSecondIntersectionFG = T::GetNullVector();
    T vSecondIntersectionGH = T::GetNullVector();
    T vSecondIntersectionHE = T::GetNullVector();
    T vSecondIntersectionDF = T::GetNullVector();
    T vSecondIntersectionAE = T::GetNullVector();
    T vSecondIntersectionBH = T::GetNullVector();
    T vSecondIntersectionCG = T::GetNullVector();

	// [Execution]
    EIntersections eResultAB = RAY_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eResultBC = RAY_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eResultCD = RAY_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eResultDA = RAY_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eResultEF = RAY_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eResultFG = RAY_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eResultGH = RAY_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eResultHE = RAY_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eResultDF = RAY_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eResultAE = RAY_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eResultBH = RAY_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eResultCG = RAY_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(eResultEF == EXPECTED_RESULT);
    BOOST_CHECK(eResultFG == EXPECTED_RESULT);
    BOOST_CHECK(eResultGH == EXPECTED_RESULT);
    BOOST_CHECK(eResultHE == EXPECTED_RESULT);
    BOOST_CHECK(eResultDF == EXPECTED_RESULT);
    BOOST_CHECK(eResultAE == EXPECTED_RESULT);
    BOOST_CHECK(eResultBH == EXPECTED_RESULT);
    BOOST_CHECK(eResultCG == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondIntersectionCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondIntersectionDA == EXPECTED_SECONDPOINT_DA);
    BOOST_CHECK(vSecondIntersectionEF == EXPECTED_SECONDPOINT_EF);
    BOOST_CHECK(vSecondIntersectionFG == EXPECTED_SECONDPOINT_FG);
    BOOST_CHECK(vSecondIntersectionGH == EXPECTED_SECONDPOINT_GH);
    BOOST_CHECK(vSecondIntersectionHE == EXPECTED_SECONDPOINT_HE);
    BOOST_CHECK(vSecondIntersectionDF == EXPECTED_SECONDPOINT_DF);
    BOOST_CHECK(vSecondIntersectionAE == EXPECTED_SECONDPOINT_AE);
    BOOST_CHECK(vSecondIntersectionBH == EXPECTED_SECONDPOINT_BH);
    BOOST_CHECK(vSecondIntersectionCG == EXPECTED_SECONDPOINT_CG);
}

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

    const BaseVector3 TRANSFORMATION = BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3);

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

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>(ORIGIN + BaseVector3(TRANSLATION_VALUE_X, TRANSLATION_VALUE_Y, TRANSLATION_VALUE_Z),
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
    const BaseVector3 TRANSFORMATION = BaseVector3(TRANSFORMATION_COMPONENTS);

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

    const BaseVector3 TRANSFORMATION = BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3);

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

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)).Normalize());

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

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)));
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

    const BaseVector3 TRANSFORMATION = BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3);

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

    const BaseVector3 TRANSFORMATION = BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3);

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

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>((ORIGIN - PIVOT) * T(BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)) + PIVOT,
                                             (DIRECTION * BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)).Normalize());

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

    const Ray3D<T> EXPECTED_RAY = Ray3D<T>( ORIGIN * T(BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)),
                                             (DIRECTION * BaseVector3(SCALING_VALUE_X, SCALING_VALUE_Y, SCALING_VALUE_Z)));
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
