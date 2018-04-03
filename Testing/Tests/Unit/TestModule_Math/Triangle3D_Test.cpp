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

#include "ZMath/Triangle3D.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/SAngle.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Triangle3D_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

	const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> triangleUT;

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle3D<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle3D<T> triangleUT(EXPECTED_TRIANGLE);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const BaseTriangle<T> EXPECTED_TRIANGLE(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle3D<T> triangleUT(EXPECTED_TRIANGLE);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

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
        Triangle3D<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        Triangle3D<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        Triangle3D<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    vf32_z INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SVF32::Pack(VECTOR_COMPONENTS_A[0], VECTOR_COMPONENTS_A[1], VECTOR_COMPONENTS_A[2], VECTOR_COMPONENTS_A[3], INPUT_FVECTOR_A);
    SVF32::Pack(VECTOR_COMPONENTS_B[0], VECTOR_COMPONENTS_B[1], VECTOR_COMPONENTS_B[2], VECTOR_COMPONENTS_B[3], INPUT_FVECTOR_B);
    SVF32::Pack(VECTOR_COMPONENTS_C[0], VECTOR_COMPONENTS_C[1], VECTOR_COMPONENTS_C[2], VECTOR_COMPONENTS_C[3], INPUT_FVECTOR_C);

	// [Execution]
    Triangle3D<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const BaseTriangle<T> OTHER_TRIANGLE = BaseTriangle<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle3D<T> triangleUT;
    triangleUT = OTHER_TRIANGLE;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the normal of a common triangle is correctly calculated.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNormal_ReturnsExpectedNormalFromCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_3, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const Vector3 EXPECTED_NORMAL = Vector3(-0.30151135f, 0.30151135f, 0.90453398f);
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const Vector3 EXPECTED_NORMAL = Vector3((float_z)-0.30151134457776363, (float_z)0.30151134457776363, (float_z)0.90453403373329089);
#endif

	// [Execution]
    Vector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(vNormal.x == EXPECTED_NORMAL.x);
    BOOST_CHECK(vNormal.y == EXPECTED_NORMAL.y);
    BOOST_CHECK(vNormal.z == EXPECTED_NORMAL.z);
}

/// <summary>
/// Checks that the result depends on the order of the points that compound the triangle, following left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNormal_FollowsLeftHandedRules_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_0, SFloat::_1, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_0, SFloat::_2, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_0, SFloat::_1, SFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

	// [Execution]
    Vector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(SFloat::IsGreaterOrEquals(vNormal.y, SFloat::_0));
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNormal_AssertionFailsWhenTwoVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const Triangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const Triangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.GetNormal();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.GetNormal();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.GetNormal();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNormal_AssertionFailsWhenVerticesAreAligned_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10 };

    const Triangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.GetNormal();
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
/// Checks that the normal is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNormal_ResultIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_3, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_2, SFloat::_9 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

	// [Execution]
    Vector3 vNormal = TRIANGLE.GetNormal();

    // [Verification]
    BOOST_CHECK(vNormal == vNormal.Normalize());
}

/// <summary>
/// Checks that the circumcenter of a common triangle is correctly calculated.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCircumcenter_ReturnsExpectedResultFromCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);

    const float_z CIRCUMCENTER_COMPONENTS[] = { (float_z)2.214285714285714, (float_z)1.9285714285714288, (float_z)3.6428571428571428, SFloat::_1 };
    const T EXPECTED_CIRCUMCENTER = T(CIRCUMCENTER_COMPONENTS);

	// [Execution]
    T vCircumcenter = TRIANGLE.GetCircumcenter();

    // [Verification]
    BOOST_CHECK(vCircumcenter == EXPECTED_CIRCUMCENTER);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCircumcenter_AssertionFailsWhenTwoVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const Triangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const Triangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.GetCircumcenter();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.GetCircumcenter();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.GetCircumcenter();
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCircumcenter_AssertionFailsWhenVerticesAreAligned_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10 };

    const Triangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.GetCircumcenter();
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
/// Checks that W component of the output point depends on the value of the W component of the vertices of the triangle.
/// </summary>
ZTEST_CASE ( GetCircumcenter_OutputWComponentDependsOnInputVertices_Test)
{
    // [Preparation]
    const Vector4 VALUE_FOR_A(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1);
    const Vector4 VALUE_FOR_B(SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1);
    const Vector4 VALUE_FOR_C(SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1);

    const Triangle3D<Vector4> TRIANGLE1 = Triangle3D<Vector4>(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    Triangle3D<Vector4> TRIANGLE2 = TRIANGLE1;
    TRIANGLE2.A.w = SFloat::_2;
    TRIANGLE2.B.w = SFloat::_3;
    TRIANGLE2.C.w = SFloat::_4;

	// [Execution]
    Vector4 vCircumcenter1 = TRIANGLE1.GetCircumcenter();
    Vector4 vCircumcenter2 = TRIANGLE2.GetCircumcenter();

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(vCircumcenter1.w, vCircumcenter2.w) );
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const Vector3 TRANSLATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const Vector3 TRANSLATION = Vector3::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_z TRANSLATION_X = SFloat::_1;
    const float_z TRANSLATION_Y = SFloat::_2;
    const float_z TRANSLATION_Z = SFloat::_3;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_z TRANSLATION_X = SFloat::_0;
    const float_z TRANSLATION_Y = SFloat::_0;
    const float_z TRANSLATION_Z = SFloat::_0;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly translated using common translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_CommonTriangleIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_TriangleIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_TriangleIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)-3.5355339059327378, (float_z)-2.1213203435596419, (float_z)-2.0000000000000009, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-4.9497474683058327, (float_z)-0.7071067811865468, (float_z)-1.0000000000000007, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)-3.5355339059327373, (float_z)-0.70710678118654668, (float_z)-3.0000000000000004, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_TriangleIsNotRotatedWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710659f, -SFloat::_4, -2.1213202f, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142138f, -SFloat::_4, -2.8284268f, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { 0.70710647f, -SFloat::_3, -3.5355337f, SFloat::_1 };
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.70710678118654768, -SFloat::_4, (float_z)-2.1213203435596428, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-1.4142135623730949, -SFloat::_4, (float_z)-2.8284271247461907, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)0.70710678118654791, -SFloat::_3, (float_z)-3.5355339059327378, SFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_TriangleIsNotRotatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_TriangleIsCorrectlyTransformedByCommonQuaternions_Test, TTemplateTypes )
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
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.29289321881345243, (float_z)1.2928932188134525, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-1.1213203435596424, (float_z)2.7071067811865479, SFloat::_4, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)0.29289321881345276, (float_z)2.7071067811865479, SFloat::_2, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_TriangleIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_CommonTriangleIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_6, SFloat::_9, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the components of the scaling vector equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_TriangleIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_CommonTriangleIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_6, SFloat::_9, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_TriangleIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_CommonTriangleIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_6, SFloat::_9, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_TriangleIsNotScaledWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const ScalingMatrix3x3 SCALE = Matrix3x3::GetIdentity();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    
    const ScalingMatrix3x3 SCALE = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonTriangleIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the components of the scaling vector equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_TriangleIsNotTranslatedWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonTriangleIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_TriangleIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

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

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)6.0658639918226491, SFloat::_8, (float_z)-10.419417382415922, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)3.5909902576697323, SFloat::_8, (float_z)-8.6516504294495533, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)8.0104076400856545, SFloat::_7, (float_z)-12.717514421272202, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_C = T::GetNullVector();

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the coordinate origin when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_TriangleIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-1.1213203435596424, SFloat::_1, (float_z)2.2928932188134521, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_1, SFloat::_2, (float_z)1.5857864376269051, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when the rotation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_TriangleIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonTriangleIsCorrectlyScaledWhenUsingCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_TriangleIsNotTranslatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the vertices of the triangle are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_0 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

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

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_3, SFloat::_7, -SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)0.52512626584708322, SFloat::_7, (float_z)-1.2322330470336311, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)4.9445436482630054, SFloat::_6, (float_z)-5.2980970388562802, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a common triangle is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_CommonTriangleIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_TriangleVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_C = PIVOT_POINT;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the position of the pivot point when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_TriangleVerticesAreMovedPivotPositionWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_2, SFloat::_3, SFloat::_3, SFloat::_1 };

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const T EXPECTED_VALUE_FOR_A = TRIANGLE.A;
    const T EXPECTED_VALUE_FOR_B = TRIANGLE.B;
    const T EXPECTED_VALUE_FOR_C = TRIANGLE.C;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_TriangleIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the triangle is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_IsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    const float_z POINT_COMPONENTS_A[] = {-SFloat::_0_5,  SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_B[] = {-SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_C[] = { SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(POINT_A, POINT_B, POINT_C);
    
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.22360679774997894, (float_z)0.81989159174992277, (float_z)3.1666666666666665, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-0.22360679774997902, (float_z)1.4161763857498666, (float_z)3.833333333333333, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_C[] = { (float_z)-1.1180339887498949, (float_z)1.1180339887498947, (float_z)3.5, SFloat::_1 };
    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(EXPECTED_VECTOR_COMPONENTS_C);
    const Triangle3D<T> EXPECTED_TRIANGLE = Triangle3D<T>(EXPECTED_VALUE_FOR_A,
                                                            EXPECTED_VALUE_FOR_B,
                                                            EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle3D<T> triangle = TRIANGLE.Transform(CONVERSION);
    	
    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_LineSegmentDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix IDENTITY_MATRIX = SpaceConversionMatrix::GetIdentity();

    const float_z POINT_COMPONENTS_A[] = {-SFloat::_0_5,  SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_B[] = {-SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_C[] = { SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(POINT_A, POINT_B, POINT_C);

    const Triangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;

	// [Execution]
    Triangle3D<T> triangle = TRIANGLE.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that the line segment is nullified when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix NULL_MATRIX = Matrix4x4::GetNullMatrix();

    const float_z POINT_COMPONENTS_A[] = {-SFloat::_0_5,  SFloat::_0_5,  SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_B[] = {-SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const float_z POINT_COMPONENTS_C[] = { SFloat::_0_5,  SFloat::_0_5, -SFloat::_0_5, SFloat::_1 };
    const T POINT_A(POINT_COMPONENTS_A);
    const T POINT_B(POINT_COMPONENTS_B);
    const T POINT_C(POINT_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(POINT_A, POINT_B, POINT_C);

    const Triangle3D<T> EXPECTED_TRIANGLE = Triangle3D<T>(T::GetNullVector(), T::GetNullVector(), T::GetNullVector());

	// [Execution]
    Triangle3D<T> triangle = TRIANGLE.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(triangle == EXPECTED_TRIANGLE);
}

/// <summary>
/// Checks that it returns "negative side" when the triangle is "behind" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheTriangleIsBehindPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //     A        |
    //    / \       |
    //   /   \      |-->
    //  C-----B     |
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the triangle is "in front" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheTriangleIsInFrontPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //    |         A
    //    |        / \
    //    |-->    /   \
    //    |      C-----B
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the triangle intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheTriangleIntersectsWithThePlane_Test, TTemplateTypes )
{
    //     |  A
    //     | / \
    //     |/   \
    //     |-->  \
    //    /|      \
    //   C-|-------B

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the triangle belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsContainedWhenTheTriangleBelongsToPlane_Test, TTemplateTypes )
{
    //       |
    //       A
    //       |
    //       B-->
    //       C
    //       |
    //

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    TRIANGLE = TRIANGLE.ProjectToPlane(PLANE);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the triangle is "behind" the plane and one vertex belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheTriangleIsBehindPlaneAndOneVertexBelongsToPlane_Test, TTemplateTypes )
{
    //     A  |
    //    / \ |
    //   /   \|-->
    //  C-----B
    //        |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the triangle is "in front" of the plane and one vertex belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheTriangleIsInFrontPlaneAndOneVertexBelongsToPlane_Test, TTemplateTypes )
{
    //    |  A
    //    | / \
    //    |/-->\
    //    C-----B
    //    |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = TRIANGLE.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    //     A  |
    //    / \ |
    //   /   \|-->
    //  C-----B
    //        |

    // [Preparation]
    const Plane NONNORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10);
    const Plane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    ESpaceRelation eResultNonNotmalized = TRIANGLE.SpaceRelation(NONNORMALIZED_PLANE);
    ESpaceRelation eResultNormalized = TRIANGLE.SpaceRelation(NORMALIZED_PLANE);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.SpaceRelation(NULL_PLANE);
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
/// Checks that it returns the expected extruded triangle when the input value is positive.
/// </summary>
ZTEST_CASE_TEMPLATE( Extrude_ReturnsWhatExpectedWhenInputValueIsPositive_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z INPUT_VALUE = SFloat::_3;
    const Vector3 DISPLACEMENT = TRIANGLE.GetNormal() * INPUT_VALUE;
    Triangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    EXPECTED_TRIANGLE.A += DISPLACEMENT;
    EXPECTED_TRIANGLE.B += DISPLACEMENT;
    EXPECTED_TRIANGLE.C += DISPLACEMENT;
    
	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that it returns the expected extruded triangle when the input value is negative.
/// </summary>
ZTEST_CASE_TEMPLATE( Extrude_ReturnsWhatExpectedWhenInputValueIsNegative_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z INPUT_VALUE = -SFloat::_3;
    const Vector3 DISPLACEMENT = TRIANGLE.GetNormal() * INPUT_VALUE;
    Triangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    EXPECTED_TRIANGLE.A += DISPLACEMENT;
    EXPECTED_TRIANGLE.B += DISPLACEMENT;
    EXPECTED_TRIANGLE.C += DISPLACEMENT;
    
	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that it returns the expected extruded triangle when the input value is negative.
/// </summary>
ZTEST_CASE_TEMPLATE( Extrude_TriangleDoesNotChangeWhenInputValueIsZero_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z INPUT_VALUE = SFloat::_0;
    const Triangle3D<T> EXPECTED_TRIANGLE = TRIANGLE;
    
	// [Execution]
    Triangle3D<T> returnedTriangle = TRIANGLE.Extrude(INPUT_VALUE);

    // [Verification]
    BOOST_CHECK(returnedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(returnedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(returnedTriangle.C == EXPECTED_TRIANGLE.C);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when, at least, two of the vertices of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Extrude_AssertionFailsWhenTwoVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const bool ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE = true;
    const bool ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE = true;

    const Triangle3D<T> TRIANGLE_A_AND_B(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);
    const Triangle3D<T> TRIANGLE_B_AND_C(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_B);
    const Triangle3D<T> TRIANGLE_C_AND_A(VECTOR_COMPONENTS_C, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z INPUT_VALUE = -SFloat::_3;

	// [Execution]
    bool bAssertionFailedWhenABCoincide = false;

    try
    {
        TRIANGLE_A_AND_B.Extrude(INPUT_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenABCoincide = true;
    }

    bool bAssertionFailedWhenBCCoincide = false;

    try
    {
        TRIANGLE_B_AND_C.Extrude(INPUT_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBCCoincide = true;
    }

    bool bAssertionFailedWhenCACoincide = false;

    try
    {
        TRIANGLE_C_AND_A.Extrude(INPUT_VALUE);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenCACoincide = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenABCoincide, ASSERTION_FAILED_WHEN_A_AND_B_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBCCoincide, ASSERTION_FAILED_WHEN_B_AND_C_COINCIDE);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCACoincide, ASSERTION_FAILED_WHEN_C_AND_A_COINCIDE);
}

/// <summary>
/// Checks that an assertion fails when the vertices of the triangle are aligned.
/// </summary>
ZTEST_CASE_TEMPLATE ( Extrude_AssertionFailsWhenVerticesAreAligned_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10 };

    const Triangle3D<T> TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_C);

    const float_z INPUT_VALUE = -SFloat::_3;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.Extrude(INPUT_VALUE);
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
/// Checks that the correct orthocenter is calculated.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetOrthocenter_OrthocenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { -SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_1 };

    const T POINT_A = T(VECTOR_COMPONENTS_A);
    const T POINT_B = T(VECTOR_COMPONENTS_B);
    const T POINT_C = T(VECTOR_COMPONENTS_C);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(POINT_A, POINT_B, POINT_C);

    const float_z EXPECTED_VALUE_COMPONENTES[] = { SFloat::_3, -SFloat::_2, SFloat::_6, SFloat::_1 };
    const T EXPECTED_VALUE_ORTHOCENTER = T(EXPECTED_VALUE_COMPONENTES);

	// [Execution]
    T orthocenter = TRIANGLE.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK(orthocenter == EXPECTED_VALUE_ORTHOCENTER);
}

/// <summary>
/// Checks that the W component of the vertices affects the result.
/// </summary>
ZTEST_CASE ( GetOrthocenter_WComponentAffectsResult_Test )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_7 };
    const float_z VECTOR_COMPONENTS_B[] = { -SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_8 };
    const float_z VECTOR_COMPONENTS_C1[] = { SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_10 };
    const float_z VECTOR_COMPONENTS_C2[] = { SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_3 };

    const Vector4 POINT_A = Vector4(VECTOR_COMPONENTS_A);
    const Vector4 POINT_B = Vector4(VECTOR_COMPONENTS_B);
    const Vector4 POINT_C1 = Vector4(VECTOR_COMPONENTS_C1);
    const Vector4 POINT_C2 = Vector4(VECTOR_COMPONENTS_C2);

    const Triangle3D<Vector4> TRIANGLE1 = Triangle3D<Vector4>(POINT_A, POINT_B, POINT_C1);
    const Triangle3D<Vector4> TRIANGLE2 = Triangle3D<Vector4>(POINT_A, POINT_B, POINT_C2);
    
    // [Execution]
    Vector4 orthocenter1 = TRIANGLE1.GetOrthocenter();
    Vector4 orthocenter2 = TRIANGLE2.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(orthocenter1.w, orthocenter2.w) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetOrthocenter_AssertionFailsWhenAllPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS[] = { SFloat::_2, SFloat::_3, SFloat::_6, SFloat::_7 };
    const T POINT = T(VECTOR_COMPONENTS);

    const Triangle3D<T> TRIANGLE = Triangle3D<T>(POINT, POINT, POINT);
    
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        TRIANGLE.GetOrthocenter();
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
/// Checks that the triangle is correctly projected to the plane when it is in its negative side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIsInNegativeSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_5, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_COMPONENTS_A[] = { (float_z)1.8095238095238098, (float_z)-3.3809523809523805, (float_z)6.238095238095239, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)2.0952380952380958, (float_z)-1.8095238095238084, (float_z)5.3809523809523832, SFloat::_1 };
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_COMPONENTS_C[] = { -0.66666698f, -0.333334f, 5.3333321f, SFloat::_1 };
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_COMPONENTS_C[] = { (float_z)-0.66666666666666652, (float_z)-0.33333333333333304, (float_z)5.3333333333333339, SFloat::_1 };
#endif
    const Triangle3D<T> EXPECTED_TRIANGLE = Triangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

	// [Execution]
    Triangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the triangle is correctly projected to the plane when it is in its positive side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIsInPositiveSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_COMPONENTS_A[] = { (float_z)-0.28571428571428581, (float_z)-5.5714285714285712, (float_z)-2.1428571428571432, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)-0.95238095238095255, (float_z)4.0952380952380949, (float_z)-6.8095238095238102, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_C[] = { (float_z)-3.5238095238095237, (float_z)3.9523809523809521, (float_z)-6.0952380952380958, SFloat::_1 };
    const Triangle3D<T> EXPECTED_TRIANGLE = Triangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_10).Normalize();

	// [Execution]
    Triangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the triangle is correctly projected to the plane when it intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_TriangleIsProjectedWhenItIntersectsWithPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const float_z EXPECTED_COMPONENTS_A[] = { SFloat::_0, -SFloat::_5, SFloat::_0, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)0.78571428571428581, (float_z)-4.4285714285714288, (float_z)-0.64285714285714235, SFloat::_1 };
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_COMPONENTS_C[] = { -1.9285716f, -2.8571432f, -0.78571475f, SFloat::_1 };
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_COMPONENTS_C[] = { (float_z)-1.9285714285714284, (float_z)-2.8571428571428568, (float_z)-0.78571428571428514, SFloat::_1 };
#endif
    const Triangle3D<T> EXPECTED_TRIANGLE = Triangle3D<T>(EXPECTED_COMPONENTS_A, EXPECTED_COMPONENTS_B, EXPECTED_COMPONENTS_C);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

	// [Execution]
    Triangle3D<T> projectedTriangle = TRIANGLE.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedTriangle.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedTriangle.A == EXPECTED_TRIANGLE.A);
    BOOST_CHECK(projectedTriangle.B == EXPECTED_TRIANGLE.B);
    BOOST_CHECK(projectedTriangle.C == EXPECTED_TRIANGLE.C);
}

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( ProjectToPlane_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane NONNORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10);
    const Plane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    Triangle3D<T> resultNonNotmalized = TRIANGLE.ProjectToPlane(NONNORMALIZED_PLANE);
    Triangle3D<T> resultNormalized = TRIANGLE.ProjectToPlane(NORMALIZED_PLANE);

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
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_C[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const Triangle3D<T> TRIANGLE = Triangle3D<T>(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRIANGLE.ProjectToPlane(NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// End - Test Suite: Triangle3D
ZTEST_SUITE_END()
