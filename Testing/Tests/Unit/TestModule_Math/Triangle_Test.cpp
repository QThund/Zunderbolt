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

#include "ZMath/Triangle.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Triangle_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

	const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle<T> triangleUT;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle<T> triangleUT(EXPECTED_TRIANGLE);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const BaseTriangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle<T> triangleUT(EXPECTED_TRIANGLE);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_AssertionFailsWhenInputValuesAreNull_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    float_z* NULL_POINTER = null_z;

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// [Execution]
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        Triangle<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        Triangle<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        Triangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenCIsNull = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenAIsNull, ASSERTION_FAILED_WHEN_A_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBIsNull, ASSERTION_FAILED_WHEN_B_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCIsNull, ASSERTION_FAILED_WHEN_C_IS_NULL);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    vf32_z INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SVF32::Pack(VECTOR_COMPONENTS_A[0], VECTOR_COMPONENTS_A[1], VECTOR_COMPONENTS_A[2], VECTOR_COMPONENTS_A[3], INPUT_FVECTOR_A);
    SVF32::Pack(VECTOR_COMPONENTS_B[0], VECTOR_COMPONENTS_B[1], VECTOR_COMPONENTS_B[2], VECTOR_COMPONENTS_B[3], INPUT_FVECTOR_B);
    SVF32::Pack(VECTOR_COMPONENTS_C[0], VECTOR_COMPONENTS_C[1], VECTOR_COMPONENTS_C[2], VECTOR_COMPONENTS_C[3], INPUT_FVECTOR_C);

	// [Execution]
    Triangle<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly assigned to another triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_TriangleIsAssignedProperlyToAnother_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const BaseTriangle<T> OTHER_TRIANGLE = BaseTriangle<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle<T> triangleUT;
    triangleUT = OTHER_TRIANGLE;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the correct surface is calculated.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetSurface_SurfaceIsCorrectlyCalculatedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VALUE = (float_z)12.0;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_z fSurface = triangleUT.GetSurface();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSurface, EXPECTED_VALUE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetSurface_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetSurface();
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
/// Checks that it returns zero when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetSurface_ReturnsZeroWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_z fResult = triangleUT.GetSurface();

    // [Verification]
    BOOST_CHECK_EQUAL(fResult, EXPECTED_RESULT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleA_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_VALUE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_VALUE = SAngle::_45;
#endif

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_z fAngle = triangleUT.GetAngleA();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleA_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleA();
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
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleB_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_VALUE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_VALUE = SAngle::_45;
#endif

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_z fAngle = triangleUT.GetAngleB();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleB_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleB();
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
/// Checks that the expected angle is returned when using a common triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleC_CorrectAngleIsReturnedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_VALUE = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_VALUE = SAngle::_45;
#endif

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    float_z fAngle = triangleUT.GetAngleC();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fAngle, EXPECTED_VALUE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetAngleC_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetAngleC();
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
/// Checks that the expected incenter is obtained for a common triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetIncenter_CorrectIncenterObtainedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    
    float_z VECTOR_COMPONENTS_EXPECTED[] = { (float_z)2.4142135623730954, (float_z)1.5857864376269049, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    T vIncenter = triangleUT.GetIncenter();

    // [Verification]
    BOOST_CHECK(vIncenter == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetIncenter_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetIncenter();
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
/// Checks that the expected centroid is obtained for a common triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCentroid_CorrectCentroidObtainedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_0, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_0, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    
    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    T vCentroid = triangleUT.GetCentroid();

    // [Verification]
    BOOST_CHECK(vCentroid == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCentroid_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS);
    const T VALUE_FOR_B(VECTOR_COMPONENTS);
    const T VALUE_FOR_C(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    const Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    bool bAssertionFailed = false;

    try
    {
        triangleUT.GetCentroid();
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
/// Checks that the expected output string is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_0, SFloat::_0_5, SFloat::_0_25 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);
    Triangle<T> triangleUT = Triangle<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    const string_z A_STRING = VALUE_FOR_A.ToString();
    const string_z B_STRING = VALUE_FOR_B.ToString();
    const string_z C_STRING = VALUE_FOR_C.ToString();
    const string_z EXPECTED_STRING = string_z("T(a(") + A_STRING + Z_L("),b(") + B_STRING + Z_L("),c(") + C_STRING + Z_L("))");

	// [Execution]
    string_z strReturnedString = triangleUT.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: Triangle
ZTEST_SUITE_END()
