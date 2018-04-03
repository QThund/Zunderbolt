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

#include "ZMath/Triangle2D.h"

#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( Triangle2D_TestSuite )

/// <summary>
/// Checks that default values haven't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2::GetNullVector();

	// [Execution]
    Triangle2D triangleUT;
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_8);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_9, SFloat::_6);

    const Triangle2D TRIANGLE_TO_COPY = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle2D triangleUT(TRIANGLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if base type constructor sets triangle components properly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_5, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_4);

    const BaseTriangle<Vector2> BASE_TRIANGLE_TO_COPY = BaseTriangle<Vector2>(EXPECTED_VALUE_FOR_A,
                                                                                  EXPECTED_VALUE_FOR_B,
                                                                                  EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle2D triangleUT(BASE_TRIANGLE_TO_COPY);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_5, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_8);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor5_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_5, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_8);

    const float_z VECTOR_COMPONENTS_A[] = { EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y};
    const float_z VECTOR_COMPONENTS_B[] = { EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y};
    const float_z VECTOR_COMPONENTS_C[] = { EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y};

	// [Execution]
    Triangle2D triangleUT = Triangle2D(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenInputValuesAreNull_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_5, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_8);

    float_z VECTOR_COMPONENTS_A[] = { EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y};
    float_z VECTOR_COMPONENTS_B[] = { EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y};
    float_z VECTOR_COMPONENTS_C[] = { EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y};

    float_z* NULL_POINTER = null_z;

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// [Execution]
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        Triangle2D(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&) 
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        Triangle2D(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&) 
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        Triangle2D(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
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
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor6_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_5, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_8);

    vf32_z INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SVF32::Pack(EXPECTED_VALUE_FOR_A.x, EXPECTED_VALUE_FOR_A.y, SFloat::_0, SFloat::_0, INPUT_FVECTOR_A);
    SVF32::Pack(EXPECTED_VALUE_FOR_B.x, EXPECTED_VALUE_FOR_B.y, SFloat::_0, SFloat::_0, INPUT_FVECTOR_B);
    SVF32::Pack(EXPECTED_VALUE_FOR_C.x, EXPECTED_VALUE_FOR_C.y, SFloat::_0, SFloat::_0, INPUT_FVECTOR_C);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly assigned to another triangle.
/// </summary>
ZTEST_CASE ( OperatorAssignation_TriangleIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_5, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_4);

    const BaseTriangle<Vector2> OTHER_TRIANGLE = BaseTriangle<Vector2>(EXPECTED_VALUE_FOR_A,
                                                                           EXPECTED_VALUE_FOR_B,
                                                                           EXPECTED_VALUE_FOR_C);

	// [Execution]
    Triangle2D triangleUT;
    triangleUT = OTHER_TRIANGLE;
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly transformed.
/// </summary>
ZTEST_CASE ( Transform_TriangleIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 INIT_POS_C = Vector2(SFloat::_2, SFloat::_6);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);
   
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(INIT_POS_A, INIT_POS_B, INIT_POS_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION_MATRIX);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform_TriangleDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the coordinate origin.
/// </summary>
ZTEST_CASE ( Transform_AllVerticesAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2::GetNullVector();

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Transform(TRANSFORMATION);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly transformed with a pivot.
/// </summary>
ZTEST_CASE ( TransformWithPivot_TriangleIsCorrectlyTransformedWithPivot_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 INIT_POS_C = Vector2(SFloat::_2, SFloat::_6);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);
   
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_3, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(INIT_POS_A, INIT_POS_B, INIT_POS_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that the triangle doesn't change when it's transformed by an identity matrix with a pivot point.
/// </summary>
ZTEST_CASE ( TransformWithPivot_TriangleDoesntChangeWhenTransformedWithPivotByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_6);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that all the vertices of the triangle are moved to the pivot point when transforming by a zero matrix.
/// </summary>
ZTEST_CASE ( TransformWithPivot_AllVerticesAreMovedToPivotPointWhenTransformedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_6);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(VALUE_FOR_A, VALUE_FOR_B, VALUE_FOR_C);
    triangleUT = triangleUT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == PIVOT_POINT);
    BOOST_CHECK(triangleUT.B == PIVOT_POINT);
    BOOST_CHECK(triangleUT.C == PIVOT_POINT);
}

/// <summary>
/// Checks that the correct circumcenter is calculated.
/// </summary>
ZTEST_CASE ( GetCircumcenter_CircumcenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test )
{
   // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 POINT_B = Vector2(SFloat::_5, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_3, SFloat::_4);

    const Vector2 EXPECTED_VALUE_CIRCUMCENTER = Vector2(SFloat::_3, SFloat::_2);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    Vector2 circumcenter = triangleUT.GetCircumcenter();
    
    // [Verification]
    BOOST_CHECK(circumcenter.x == EXPECTED_VALUE_CIRCUMCENTER.x);
    BOOST_CHECK(circumcenter.y == EXPECTED_VALUE_CIRCUMCENTER.y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE ( GetCircumcenter_AssertionFailsWhenAllPointsCoincide_Test )
{
    // [Preparation]
    const Vector2 POINT = Vector2(SFloat::_2, SFloat::_2);
    Triangle2D TRIANGLE = Triangle2D(POINT, POINT, POINT);

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
/// Checks that the correct orthocenter is calculated.
/// </summary>
ZTEST_CASE ( GetOrthocenter_OrthocenterIsCorrectlyCalculatedWhenUsingCommonTriangle_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_3);
    const Vector2 POINT_C = Vector2(SFloat::_3, SFloat::_4);

    const Vector2 EXPECTED_VALUE_ORTHOCENTER = Vector2(SFloat::_3, -SFloat::_2);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    Vector2 orthocenter = triangleUT.GetOrthocenter();
    
    // [Verification]
    BOOST_CHECK(orthocenter.x == EXPECTED_VALUE_ORTHOCENTER.x);
    BOOST_CHECK(orthocenter.y == EXPECTED_VALUE_ORTHOCENTER.y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE ( GetOrthocenter_AssertionFailsWhenAllPointsCoincide_Test )
{
   // [Preparation]
    const Vector2 POINT = Vector2(SFloat::_2, SFloat::_2);
    Triangle2D TRIANGLE = Triangle2D(POINT, POINT, POINT);
    
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
/// Checks that a triangle is correctly translated.
/// </summary>
ZTEST_CASE ( Translate1_TriangleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_4, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate1_TriangleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly translated.
/// </summary>
ZTEST_CASE ( Translate2_TriangleIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_4, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate2_TriangleIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly rotated.
/// </summary>
ZTEST_CASE ( Rotate_TriangleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_0, SFloat::_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated when angle is zero.
/// </summary>
ZTEST_CASE ( Rotate_TriangleIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);
    const float_z ANGLE = SFloat::_0;

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Rotate(ANGLE);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly rotated with pivot point.
/// </summary>
ZTEST_CASE ( RotateWithPivot_TriangleIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_0, SFloat::_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 PIVOT_POINT = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_1);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not rotated with a pivot when angle is zero.
/// </summary>
ZTEST_CASE ( RotateWithPivot_TriangleIsNotRotatedWithPivotWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_0, SFloat::_0);
    const float_z ANGLE = SFloat::_0;

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.RotateWithPivot(ANGLE, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_10);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled if Scale is one.
/// </summary>
ZTEST_CASE ( Scale1_TriangleIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_10);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled if scale equals one.
/// </summary>
ZTEST_CASE ( Scale2_TriangleIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is correctly scaled with a pivot.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_2, SFloat::_10 + SFloat::_1);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_TriangleIsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_2, SFloat::_10 + SFloat::_1);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(POINT_A, POINT_B, POINT_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks that a triangle is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_TriangleIsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Triangle2D triangleUT = Triangle2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);
    triangleUT = triangleUT.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);
    
    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

// End - Test Suite: Triangle2D
ZTEST_SUITE_END()
