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

#include "ZMath/LineSegment3D.h"

#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( LineSegment3D_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> lineSegmentUT;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if copy constructor sets segment's points properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const LineSegment3D<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment3D<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if points are copied cortectly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TTemplateTypes )
{

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const BaseLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment3D<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a unit-length line which point A is placed at origin and point B is contained in the positive X axis.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetUnitLine_AUnitLengthSegmentPlacedAtOriginAndContainedInPositiveXAxisIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetUnitVectorX();

	// [Execution]
    LineSegment3D<T> lineSegmentUT = LineSegment3D<T>::GetUnitLine();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a zero-length line which points A and B are placed at origin.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetLineZero_AZeroLengthSegmentPlacedAtOriginIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> lineSegmentUT = LineSegment3D<T>::GetLineZero();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line is correctly assigned to another line.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_LineIsAssignedProperlyToAnother_Test, TTemplateTypes )
{

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const BaseLineSegment<T> OTHER_LINE = BaseLineSegment<T>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment3D<T> lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns True when a common line segment and a common plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenCommonLineSegmentIntersectWithCommonPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, -SFloat::_6, -SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when line segment and plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLineSegmentIsParallelToPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_3, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLineSegmentIsContainedInPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SFloat::_2, PLANE.b * -PLANE.d + SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line segment doesn't intersect with the plane but would do it if the line segment was lengthened.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLineSegmentDoesNotIntersectWithPlaneButWouldDoIfLineSegmentWasLengthened_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only an endpoint of the line segment belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenOnlyAnEndpointBelongsToPlane_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d - SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT_A = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT_B = LineSegment3D<T>(POINT_B, POINT_A);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA = LINE_SEGMENT_A.Intersection(PLANE);
    bool bResultB = LINE_SEGMENT_B.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(PLANE);
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
ZTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(PLANE);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.


    // [Preparation]
    const float_z POINT_A_COMPONENTS_CONTAINED[] = { SFloat::_0, SFloat::_4, SFloat::_0, SFloat::_1 };
    const float_z POINT_A_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };

    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);

    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_4).Normalize();

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(PLANE);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when a common line segment and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_6, SFloat::_0, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common line segment intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS1[] = { SFloat::_2, SFloat::_0, SFloat::_1, SFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);

    const float_z POINT_A_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS2[] = { SFloat::_6, SFloat::_0, SFloat::_3, SFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);

    const float_z POINT_A_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_1 };
    const float_z POINT_B_COMPONENTS3[] = { SFloat::_7, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bIntersectsWithB = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bIntersectsWithC = LINE_SEGMENT3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A) + (VERTEX_C - VERTEX_B) * SFloat::_0_5;
    const T POINT_B = POINT_A + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B, POINT_A);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bResult2 = LINE_SEGMENT2.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A) + (VERTEX_C - VERTEX_B) * SFloat::_0_5;
    const T POINT_B = POINT_A.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bEndpointContainedInAB2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bEndpointContainedInAC1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bEndpointContainedInAC2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bEndpointContainedInBC1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bEndpointContainedInBC2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInAB1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bContainedInAB2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bContainedInAC1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bContainedInAC2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bContainedInBC1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bContainedInBC2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenLineSegmentIntersectsEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bIntersectsWithAC = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bIntersectsWithBC = LINE_SEGMENT3.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersectsWithAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithAC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersectsWithBC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenAnEndpointAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 RELATIVE_POSITION_OF_OTHER_POINT = Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointAAndVertexACoincide1 = LINE_SEGMENT1.Intersection(TRIANGLE);
    bool bEndpointBAndVertexACoincide2 = LINE_SEGMENT2.Intersection(TRIANGLE);
    bool bEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.Intersection(TRIANGLE);
    bool bEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.Intersection(TRIANGLE);
    bool bEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.Intersection(TRIANGLE);
    bool bEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointAAndVertexACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAAndVertexBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAAndVertexCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointBAndVertexCCoincide2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
        LINE_SEGMENT.Intersection(TRIANGLE);
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
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
        LINE_SEGMENT.Intersection(TRIANGLE);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheEndpointsCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const float_z POINT_A_COMPONENTS_CONTAINED[] = { SFloat::_2, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);

    const float_z POINT_A_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_1, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(TRIANGLE);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when a common line segment and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TTemplateTypes )
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
    const float_z POINT_A_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
    bool bResult = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIntersectsWithHexahedronVertex_Test, TTemplateTypes )
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

    const float_z POINT_A_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_z POINT_A_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_H);

    const LineSegment3D<T> LINE_SEGMENT_A = LineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const LineSegment3D<T> LINE_SEGMENT_B = LineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const LineSegment3D<T> LINE_SEGMENT_C = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const LineSegment3D<T> LINE_SEGMENT_D = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const LineSegment3D<T> LINE_SEGMENT_E = LineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const LineSegment3D<T> LINE_SEGMENT_F = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const LineSegment3D<T> LINE_SEGMENT_G = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const LineSegment3D<T> LINE_SEGMENT_H = LineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithA = LINE_SEGMENT_A.Intersection(HEXAHEDRON);
    bool bIntersectsWithB = LINE_SEGMENT_B.Intersection(HEXAHEDRON);
    bool bIntersectsWithC = LINE_SEGMENT_C.Intersection(HEXAHEDRON);
    bool bIntersectsWithD = LINE_SEGMENT_D.Intersection(HEXAHEDRON);
    bool bIntersectsWithE = LINE_SEGMENT_E.Intersection(HEXAHEDRON);
    bool bIntersectsWithF = LINE_SEGMENT_F.Intersection(HEXAHEDRON);
    bool bIntersectsWithG = LINE_SEGMENT_G.Intersection(HEXAHEDRON);
    bool bIntersectsWithH = LINE_SEGMENT_H.Intersection(HEXAHEDRON);

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
/// Checks that it returns False when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsFalseWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_0, SFloat::_4, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
    bool bResult = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenAnEndpointIsContainedInHexahedronFace_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.Intersection(HEXAHEDRON);
    bool bContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.Intersection(HEXAHEDRON);
    bool bContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.Intersection(HEXAHEDRON);
    bool bContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.Intersection(HEXAHEDRON);
    bool bContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.Intersection(HEXAHEDRON);
    bool bContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.Intersection(HEXAHEDRON);
    bool bContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.Intersection(HEXAHEDRON);
    bool bContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.Intersection(HEXAHEDRON);
    bool bContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.Intersection(HEXAHEDRON);
    bool bContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.Intersection(HEXAHEDRON);
    bool bContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.Intersection(HEXAHEDRON);
    bool bContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentBelongsToHexahedronFace_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.Intersection(HEXAHEDRON);
    bool bContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.Intersection(HEXAHEDRON);
    bool bContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.Intersection(HEXAHEDRON);
    bool bContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.Intersection(HEXAHEDRON);
    bool bContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.Intersection(HEXAHEDRON);
    bool bContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.Intersection(HEXAHEDRON);
    bool bContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.Intersection(HEXAHEDRON);
    bool bContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.Intersection(HEXAHEDRON);
    bool bContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.Intersection(HEXAHEDRON);
    bool bContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.Intersection(HEXAHEDRON);
    bool bContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.Intersection(HEXAHEDRON);
    bool bContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bContainedInDFGC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInDFGC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInADFE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInAEHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInCGHB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInABCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bContainedInEFGH2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenOnlyOneEndpointIsContainedInHexahedron_Test, TTemplateTypes )
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

    const T POINT_A = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A + Vector3(SFloat::_3, -SFloat::_3, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(HEXAHEDRON);
    bool bResult2 = LINE_SEGMENT2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB1 = LineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB2 = LineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC1 = LineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC2 = LineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD1 = LineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD2 = LineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA1 = LineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA2 = LineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF1 = LineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF2 = LineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG1 = LineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG2 = LineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH1 = LineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH2 = LineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE1 = LineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE2 = LineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF1 = LineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF2 = LineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE1 = LineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE2 = LineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH1 = LineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH2 = LineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG1 = LineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG2 = LineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is fully contained in the hexahedron (not touching the surface).
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIsContainedInHexahedron_Test, TTemplateTypes )
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
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T POINT_A = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B = VERTEX_G.Lerp(SFloat::_0_25, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bLineContained = LINE_SEGMENT.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bLineContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB = LineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC = LineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD = LineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA = LineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF = LineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG = LineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH = LineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE = LineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF = LineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE = LineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH = LineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG = LineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointContainedInAB = LINE_SEGMENT_IN_AB.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBC = LINE_SEGMENT_IN_BC.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCD = LINE_SEGMENT_IN_CD.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDA = LINE_SEGMENT_IN_DA.Intersection(HEXAHEDRON);
    bool bEndpointContainedInEF = LINE_SEGMENT_IN_EF.Intersection(HEXAHEDRON);
    bool bEndpointContainedInFG = LINE_SEGMENT_IN_FG.Intersection(HEXAHEDRON);
    bool bEndpointContainedInGH = LINE_SEGMENT_IN_GH.Intersection(HEXAHEDRON);
    bool bEndpointContainedInHE = LINE_SEGMENT_IN_HE.Intersection(HEXAHEDRON);
    bool bEndpointContainedInDF = LINE_SEGMENT_IN_DF.Intersection(HEXAHEDRON);
    bool bEndpointContainedInAE = LINE_SEGMENT_IN_AE.Intersection(HEXAHEDRON);
    bool bEndpointContainedInBH = LINE_SEGMENT_IN_BH.Intersection(HEXAHEDRON);
    bool bEndpointContainedInCG = LINE_SEGMENT_IN_CG.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointContainedInAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInEF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInFG, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInGH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInHE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInDF, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInAE, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInBH, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointContainedInCG, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line segment intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
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

    const float_z POINT_A_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B));
    const LineSegment3D<T> LINE_SEGMENT_TO_AB = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C));
    const LineSegment3D<T> LINE_SEGMENT_TO_BC = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D));
    const LineSegment3D<T> LINE_SEGMENT_TO_CD = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A));
    const LineSegment3D<T> LINE_SEGMENT_TO_DA = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_EF = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G));;
    const LineSegment3D<T> LINE_SEGMENT_TO_FG = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_GH = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_HE = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_DF = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_AE = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_BH = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G));
    const LineSegment3D<T> LINE_SEGMENT_TO_CG = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersectsWithAB = LINE_SEGMENT_TO_AB.Intersection(HEXAHEDRON);
    bool bIntersectsWithBC = LINE_SEGMENT_TO_BC.Intersection(HEXAHEDRON);
    bool bIntersectsWithCD = LINE_SEGMENT_TO_CD.Intersection(HEXAHEDRON);
    bool bIntersectsWithDA = LINE_SEGMENT_TO_DA.Intersection(HEXAHEDRON);
    bool bIntersectsWithEF = LINE_SEGMENT_TO_EF.Intersection(HEXAHEDRON);
    bool bIntersectsWithFG = LINE_SEGMENT_TO_FG.Intersection(HEXAHEDRON);
    bool bIntersectsWithGH = LINE_SEGMENT_TO_GH.Intersection(HEXAHEDRON);
    bool bIntersectsWithHE = LINE_SEGMENT_TO_HE.Intersection(HEXAHEDRON);
    bool bIntersectsWithDF = LINE_SEGMENT_TO_DF.Intersection(HEXAHEDRON);
    bool bIntersectsWithAE = LINE_SEGMENT_TO_AE.Intersection(HEXAHEDRON);
    bool bIntersectsWithBH = LINE_SEGMENT_TO_BH.Intersection(HEXAHEDRON);
    bool bIntersectsWithCG = LINE_SEGMENT_TO_CG.Intersection(HEXAHEDRON);

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
/// Checks that it returns True when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsTrueWhenEndpointAndHexahedronVertexCoincide_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const LineSegment3D<T> LINE_SEGMENT_FROM_A1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_A2 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B1 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B2 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C1 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C2 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D1 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D2 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E1 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E2 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F1 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F2 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G1 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G2 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H1 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H2 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.Intersection(HEXAHEDRON);
    bool bEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.Intersection(HEXAHEDRON);
    bool bEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.Intersection(HEXAHEDRON);
    bool bEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.Intersection(HEXAHEDRON);
    bool bEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.Intersection(HEXAHEDRON);
    bool bEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.Intersection(HEXAHEDRON);
    bool bEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.Intersection(HEXAHEDRON);
    bool bEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.Intersection(HEXAHEDRON);
    bool bEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.Intersection(HEXAHEDRON);
    bool bEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.Intersection(HEXAHEDRON);
    bool bEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.Intersection(HEXAHEDRON);
    bool bEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.Intersection(HEXAHEDRON);
    bool bEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.Intersection(HEXAHEDRON);
    bool bEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.Intersection(HEXAHEDRON);
    bool bEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.Intersection(HEXAHEDRON);
    bool bEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bEndpointAndACoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndACoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndBCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndBCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndCCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndCCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndDCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndDCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndECoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndECoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndFCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndFCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndGCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndGCoincide2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndHCoincide1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bEndpointAndHCoincide2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
        LINE_SEGMENT.Intersection(HEXAHEDRON);
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
ZTEST_CASE_TEMPLATE ( Intersection3_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(HEXAHEDRON);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection3_ReturnsExpectedResultsWhenLineSegmentEndpointsCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const float_z POINT_A_COMPONENTS_CONTAINED[] = { (float_z)1.5, (float_z)1.5, SFloat::_1, SFloat::_1 };
    const T POINT_A_CONTAINED(POINT_A_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_A_CONTAINED, POINT_A_CONTAINED);

    const float_z POINT_A_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_5, SFloat::_1, SFloat::_1 };
    const T POINT_A_NOT_CONTAINED(POINT_A_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_A_NOT_CONTAINED, POINT_A_NOT_CONTAINED);

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

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(HEXAHEDRON);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(HEXAHEDRON);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenCommonLineSegmentIntersectWithCommonPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { -SFloat::_7, -SFloat::_8, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const float_z EXPECTED_COMPONENTS[] = { (float_z)-5.2000000000000011, (float_z)-5.9000000000000004, SFloat::_7, SFloat::_1 };
    const T EXPECTED_POINT = T(EXPECTED_COMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersection;
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when line segment is plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoInterserctionsWhenLineSegmentIsParallelToPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_3, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenLineSegmentIsContainedInPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, -SFloat::_4).Normalize();

    // The origin is the point of the plane calculated by multiplying the normal by the distance
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SFloat::_2, PLANE.b * -PLANE.d + SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the line segment doesn't intersect with the plane but would do it if the line segment was lengthened.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithPlaneButWouldDoIfLineSegmentWasLengthened_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only an endpoint of the line segment belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyAnEndpointBelongsToPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d - SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT_A = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT_B = LineSegment3D<T>(POINT_B, POINT_A);

    const T EXPECTED_POINT_A = LINE_SEGMENT_A.A;
    const T EXPECTED_POINT_B = LINE_SEGMENT_B.B;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    EIntersections eResultA = LINE_SEGMENT_A.IntersectionPoint(PLANE, vIntersectionA);
    EIntersections eResultB = LINE_SEGMENT_B.IntersectionPoint(PLANE, vIntersectionB);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_4).Normalize();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenPlaneIsNull_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_7, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(PLANE, vIntersection);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_1, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const Plane PLANE = Plane(SFloat::_0, SFloat::_1, SFloat::_0, -SFloat::_4).Normalize();

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_POINT = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(PLANE, vIntersectionContained);
    const EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(PLANE, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B = POINT_A.Lerp(SFloat::_2, EXPECTED_POINT);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

	// [Execution]
    T vIntersection;
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineSegmentIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS1[] = { SFloat::_2, SFloat::_0, SFloat::_1, SFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);

    const float_z POINT_A_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS2[] = { SFloat::_6, SFloat::_0, SFloat::_3, SFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);

    const float_z POINT_A_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_1 };
    const float_z POINT_B_COMPONENTS3[] = { SFloat::_7, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
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
    EIntersections eIntersectionsWithA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EIntersections eIntersectionsWithB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionB);
    EIntersections eIntersectionsWithC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionC);

    // [Verification]
    BOOST_CHECK(eIntersectionsWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectionsWithC == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT_A);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT_B);
    BOOST_CHECK(vIntersectionC == EXPECTED_POINT_C);
}

/// <summary>
/// Checks that it returns no intersections when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;

	// [Execution]
    T vIntersection;
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A).Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B, POINT_A);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT = POINT_A;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionA;
    T vIntersectionB;
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionB);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA == EXPECTED_POINT);
    BOOST_CHECK(vIntersectionB == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsInfiniteIntersectionsWhenLineSegmentBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A).Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    T vIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangleAndTheOtherEndpointIsInsideTheTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = CENTER_POINT;
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = CENTER_POINT;
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B3 = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_CA);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB1 = LINE_SEGMENT1.A;
    const T EXPECTED_POINT_AB2 = LINE_SEGMENT2.A;
    const T EXPECTED_POINT_AC1 = LINE_SEGMENT3.A;
    const T EXPECTED_POINT_AC2 = LINE_SEGMENT4.A;
    const T EXPECTED_POINT_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_POINT_BC2 = LINE_SEGMENT6.A;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersectionAB1;
    T vIntersectionAB2;
    T vIntersectionAC1;
    T vIntersectionAC2;
    T vIntersectionBC1;
    T vIntersectionBC2;
    EIntersections eContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB1);
    EIntersections eContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAB2);
    EIntersections eContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionAC1);
    EIntersections eContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionAC2);
    EIntersections eContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionBC1);
    EIntersections eContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vIntersectionAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vIntersectionAC1 == EXPECTED_POINT_AC1);
    BOOST_CHECK(vIntersectionAC2 == EXPECTED_POINT_AC2);
    BOOST_CHECK(vIntersectionBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vIntersectionBC2 == EXPECTED_POINT_BC2);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_POINT_AC = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionAB;
    T vIntersectionAC;
    T vIntersectionBC;
    EIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB);
    EIntersections eIntersectsWithAC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionAC);
    EIntersections eIntersectsWithBC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionBC);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionAC == EXPECTED_POINT_AC);
    BOOST_CHECK(vIntersectionBC == EXPECTED_POINT_BC);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 RELATIVE_POSITION_OF_OTHER_POINT = Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionA1;
    T vIntersectionA2;
    T vIntersectionB1;
    T vIntersectionB2;
    T vIntersectionC1;
    T vIntersectionC2;
    EIntersections eEndpointAAndVertexACoincide1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionA1);
    EIntersections eEndpointBAndVertexACoincide2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionA2);
    EIntersections eEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionB1);
    EIntersections eEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vIntersectionB2);
    EIntersections eEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vIntersectionC1);
    EIntersections eEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vIntersectionC2);

    // [Verification]
    BOOST_CHECK(eEndpointAAndVertexACoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexACoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAAndVertexBCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexBCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAAndVertexCCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexCCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionA1 == VERTEX_A);
    BOOST_CHECK(vIntersectionA2 == VERTEX_A);
    BOOST_CHECK(vIntersectionB1 == VERTEX_B);
    BOOST_CHECK(vIntersectionB2 == VERTEX_B);
    BOOST_CHECK(vIntersectionC1 == VERTEX_C);
    BOOST_CHECK(vIntersectionC2 == VERTEX_C);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineSegmentIntersectsWithTwoEdgesOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);

    const T POINT_A1 = MID_POINT_AB.Lerp(-SFloat::_2, MID_POINT_BC);
    const T POINT_B1 = MID_POINT_AB.Lerp(SFloat::_2, MID_POINT_BC);
    const T POINT_A2 = MID_POINT_BC.Lerp(-SFloat::_2, MID_POINT_CA);
    const T POINT_B2 = MID_POINT_BC.Lerp(SFloat::_2, MID_POINT_CA);
    const T POINT_A3 = MID_POINT_CA.Lerp(-SFloat::_2, MID_POINT_AB);
    const T POINT_B3 = MID_POINT_CA.Lerp(SFloat::_2, MID_POINT_AB);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB_BC = MID_POINT_AB;
    const T EXPECTED_POINT_BC_CA = MID_POINT_BC;
    const T EXPECTED_POINT_CA_AB = MID_POINT_CA;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersectionAB_BC;
    T vIntersectionBC_CA;
    T vIntersectionCA_AB;
    EIntersections eIntersectsWithAB_BC = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB_BC);
    EIntersections eIntersectsWithBC_CA = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionBC_CA);
    EIntersections eIntersectsWithCA_AB = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionCA_AB);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC_CA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB_BC == EXPECTED_POINT_AB_BC);
    BOOST_CHECK(vIntersectionBC_CA == EXPECTED_POINT_BC_CA);
    BOOST_CHECK(vIntersectionCA_AB == EXPECTED_POINT_CA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment belongs to the triangle and the line intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenEndpointBelongsToTriangleAndLineIntersectsEdge_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T INNER_POINT = MID_POINT_AB.Lerp(SFloat::_0_5, MID_POINT_BC).Lerp(SFloat::_0_5, MID_POINT_CA);

    const T POINT_A1 = INNER_POINT;
    const T POINT_B1 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_AB);
    const T POINT_A2 = INNER_POINT;
    const T POINT_B2 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_BC);
    const T POINT_A3 = INNER_POINT;
    const T POINT_B3 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_CA);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_POINT_AB = MID_POINT_AB;
    const T EXPECTED_POINT_BC = MID_POINT_BC;
    const T EXPECTED_POINT_CA = MID_POINT_CA;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vIntersectionAB;
    T vIntersectionBC;
    T vIntersectionCA;
    EIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vIntersectionAB);
    EIntersections eIntersectsWithBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vIntersectionBC);
    EIntersections eIntersectsWithCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vIntersectionCA);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCA == EXPECTED_RESULT);
    BOOST_CHECK(vIntersectionAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vIntersectionBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vIntersectionCA == EXPECTED_POINT_CA);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
    T vIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vIntersection);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_3, SFloat::_2, SFloat::_1, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_IN_EDGE[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const LineSegment3D<T> LINE_SEGMENT_IN_EDGE = LineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionInEdge = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(TRIANGLE, vIntersectionContained);
    const EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vIntersectionInEdge);
    const EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(TRIANGLE, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when a common line segment and a common triangle intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenCommonLineSegmentIntersectsWithCommonTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B = POINT_A.Lerp(SFloat::_2, EXPECTED_FIRSTPOINT);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineSegmentIntersectsWithTriangleVertex_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS1[] = { SFloat::_0, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS1[] = { SFloat::_2, SFloat::_0, SFloat::_1, SFloat::_1 };
    const T POINT_A1(POINT_A_COMPONENTS1);
    const T POINT_B1(POINT_B_COMPONENTS1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);

    const float_z POINT_A_COMPONENTS2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS2[] = { SFloat::_6, SFloat::_0, SFloat::_3, SFloat::_1 };
    const T POINT_A2(POINT_A_COMPONENTS2);
    const T POINT_B2(POINT_B_COMPONENTS2);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);

    const float_z POINT_A_COMPONENTS3[] = { SFloat::_4, SFloat::_3, SFloat::_0, SFloat::_1 };
    const float_z POINT_B_COMPONENTS3[] = { SFloat::_7, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T POINT_A3(POINT_A_COMPONENTS3);
    const T POINT_B3(POINT_B_COMPONENTS3);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
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
    T vSecondIntersectionA = T::GetNullVector();
    T vSecondIntersectionB = T::GetNullVector();
    T vSecondIntersectionC = T::GetNullVector();
    EIntersections eIntersectionsWithA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eIntersectionsWithB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eIntersectionsWithC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionC, vSecondIntersectionC);

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
/// Checks that it returns no intersections when a common line segment and a common triangle would intersect if the line segment was lengthened enough.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithTriangleButWouldDoIfLineSegmentWasLengthenedEnough_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    
	// [Execution]
    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointIsContainedInTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A).Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B, POINT_A);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT = POINT_A;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vSecondIntersectionA = T::GetNullVector();
    T vSecondIntersectionB = T::GetNullVector();
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionB, vSecondIntersectionB);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersectionA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vFirstIntersectionB == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersectionB == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line segment is contained in the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenLineSegmentBelongsToTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A).Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B = POINT_A.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);
    
    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;

	// [Execution]
    T vFirstIntersection = T::GetNullVector();
    T vSecondIntersection = T::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_POINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_4, SFloat::_4, SFloat::_4);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionAC1;
    T vFirstIntersectionAC2;
    T vFirstIntersectionBC1;
    T vFirstIntersectionBC2;
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection when an endpoint of the line segment is contained in an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointBelongsToEdgeOfTriangleAndTheOtherEndpointIsInsideTheTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B).Lerp(SFloat::_0_5, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = CENTER_POINT;
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = CENTER_POINT;
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B3 = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionAC1;
    T vFirstIntersectionAC2;
    T vFirstIntersectionBC1;
    T vFirstIntersectionBC2;
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the endpoints of the segment belong to different edges of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenEndpointsBelongToDifferentEdgesOfTheTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B1 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_B);
    const T POINT_A3 = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const T POINT_B3 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB_AC1 = LINE_SEGMENT1.A;
    const T EXPECTED_FIRSTPOINT_AB_AC2 = LINE_SEGMENT2.A;
    const T EXPECTED_FIRSTPOINT_AC_BC1 = LINE_SEGMENT3.A;
    const T EXPECTED_FIRSTPOINT_AC_BC2 = LINE_SEGMENT4.A;
    const T EXPECTED_FIRSTPOINT_AB_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_FIRSTPOINT_AB_BC2 = LINE_SEGMENT6.A;
    const T EXPECTED_SECONDPOINT_AB_AC1 = LINE_SEGMENT1.B;
    const T EXPECTED_SECONDPOINT_AB_AC2 = LINE_SEGMENT2.B;
    const T EXPECTED_SECONDPOINT_AC_BC1 = LINE_SEGMENT3.B;
    const T EXPECTED_SECONDPOINT_AC_BC2 = LINE_SEGMENT4.B;
    const T EXPECTED_SECONDPOINT_AB_BC1 = LINE_SEGMENT5.B;
    const T EXPECTED_SECONDPOINT_AB_BC2 = LINE_SEGMENT6.B;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB_AC1;
    T vFirstIntersectionAB_AC2;
    T vFirstIntersectionAC_BC1;
    T vFirstIntersectionAC_BC2;
    T vFirstIntersectionAB_BC1;
    T vFirstIntersectionAB_BC2;
    T vSecondIntersectionAB_AC1 = T::GetNullVector();
    T vSecondIntersectionAB_AC2 = T::GetNullVector();
    T vSecondIntersectionAC_BC1 = T::GetNullVector();
    T vSecondIntersectionAC_BC2 = T::GetNullVector();
    T vSecondIntersectionAB_BC1 = T::GetNullVector();
    T vSecondIntersectionAB_BC2 = T::GetNullVector();
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_AC1, vSecondIntersectionAB_AC1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_AC2, vSecondIntersectionAB_AC2);
    EIntersections eEndpointContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC_BC1, vSecondIntersectionAC_BC1);
    EIntersections eEndpointContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC_BC2, vSecondIntersectionAC_BC2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC1, vSecondIntersectionAB_BC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC2, vSecondIntersectionAB_BC2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB_AC1 == EXPECTED_FIRSTPOINT_AB_AC1);
    BOOST_CHECK(vFirstIntersectionAB_AC2 == EXPECTED_FIRSTPOINT_AB_AC2);
    BOOST_CHECK(vFirstIntersectionAC_BC1 == EXPECTED_FIRSTPOINT_AC_BC1);
    BOOST_CHECK(vFirstIntersectionAC_BC2 == EXPECTED_FIRSTPOINT_AC_BC2);
    BOOST_CHECK(vFirstIntersectionAB_BC1 == EXPECTED_FIRSTPOINT_AB_BC1);
    BOOST_CHECK(vFirstIntersectionAB_BC2 == EXPECTED_FIRSTPOINT_AB_BC2);
    BOOST_CHECK(vSecondIntersectionAB_AC1 == EXPECTED_SECONDPOINT_AB_AC1);
    BOOST_CHECK(vSecondIntersectionAB_AC2 == EXPECTED_SECONDPOINT_AB_AC2);
    BOOST_CHECK(vSecondIntersectionAC_BC1 == EXPECTED_SECONDPOINT_AC_BC1);
    BOOST_CHECK(vSecondIntersectionAC_BC2 == EXPECTED_SECONDPOINT_AC_BC2);
    BOOST_CHECK(vSecondIntersectionAB_BC1 == EXPECTED_SECONDPOINT_AB_BC1);
    BOOST_CHECK(vSecondIntersectionAB_BC2 == EXPECTED_SECONDPOINT_AB_BC2);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_B1, POINT_A1);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(POINT_B2, POINT_A2);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(POINT_A3, POINT_B3);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(POINT_B3, POINT_A3);

    const T EXPECTED_FIRSTPOINT_AB1 = LINE_SEGMENT1.A;
    const T EXPECTED_FIRSTPOINT_AB2 = LINE_SEGMENT2.A;
    const T EXPECTED_FIRSTPOINT_AC1 = LINE_SEGMENT3.A;
    const T EXPECTED_FIRSTPOINT_AC2 = LINE_SEGMENT4.A;
    const T EXPECTED_FIRSTPOINT_BC1 = LINE_SEGMENT5.A;
    const T EXPECTED_FIRSTPOINT_BC2 = LINE_SEGMENT6.A;
    const T EXPECTED_SECONDPOINT_AB1 = LINE_SEGMENT1.B;
    const T EXPECTED_SECONDPOINT_AB2 = LINE_SEGMENT2.B;
    const T EXPECTED_SECONDPOINT_AC1 = LINE_SEGMENT3.B;
    const T EXPECTED_SECONDPOINT_AC2 = LINE_SEGMENT4.B;
    const T EXPECTED_SECONDPOINT_BC1 = LINE_SEGMENT5.B;
    const T EXPECTED_SECONDPOINT_BC2 = LINE_SEGMENT6.B;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionAC1 = T::GetNullVector();
    T vFirstIntersectionAC2 = T::GetNullVector();
    T vFirstIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionBC2 = T::GetNullVector();
    T vSecondIntersectionAB1 = T::GetNullVector();
    T vSecondIntersectionAB2 = T::GetNullVector();
    T vSecondIntersectionAC1 = T::GetNullVector();
    T vSecondIntersectionAC2 = T::GetNullVector();
    T vSecondIntersectionBC1 = T::GetNullVector();
    T vSecondIntersectionBC2 = T::GetNullVector();
    EIntersections eContainedInAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EIntersections eContainedInAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EIntersections eContainedInAC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionAC1, vSecondIntersectionAC1);
    EIntersections eContainedInAC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionAC2, vSecondIntersectionAC2);
    EIntersections eContainedInBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EIntersections eContainedInBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionBC2, vSecondIntersectionBC2);

    // [Verification]
    BOOST_CHECK(eContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstIntersectionAC1 == EXPECTED_FIRSTPOINT_AC1);
    BOOST_CHECK(vFirstIntersectionAC2 == EXPECTED_FIRSTPOINT_AC2);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT_AB1);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT_AB2);
    BOOST_CHECK(vSecondIntersectionAC1 == EXPECTED_SECONDPOINT_AC1);
    BOOST_CHECK(vSecondIntersectionAC2 == EXPECTED_SECONDPOINT_AC2);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT_BC1);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT_BC2);
}

/// <summary>
/// Checks that it returns one intersection point when the line segment intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T POINT_A1 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B1 = POINT_A1 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A2 = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B2 = POINT_A2 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const T POINT_A3 = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C) - Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const T POINT_B3 = POINT_A3 + Vector3(SFloat::_2, SFloat::_2, SFloat::_2);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T EXPECTED_FIRSTPOINT_AC = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_FIRSTPOINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionAC;
    T vFirstIntersectionBC;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionAC = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    EIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eIntersectsWithAC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionAC, vSecondIntersectionAC);
    EIntersections eIntersectsWithBC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionBC, vSecondIntersectionBC);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionAC == EXPECTED_FIRSTPOINT_AC);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment and a vertex of the triangle coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointAndTriangleVertexCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const Vector3 RELATIVE_POSITION_OF_OTHER_POINT = Vector3(SFloat::_1, SFloat::_1, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(VERTEX_A + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT4 = LineSegment3D<T>(VERTEX_B + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT5 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT);
    const LineSegment3D<T> LINE_SEGMENT6 = LineSegment3D<T>(VERTEX_C + RELATIVE_POSITION_OF_OTHER_POINT, VERTEX_C);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionA1;
    T vFirstIntersectionA2;
    T vFirstIntersectionB1;
    T vFirstIntersectionB2;
    T vFirstIntersectionC1;
    T vFirstIntersectionC2;
    T vSecondIntersectionA1 = T::GetNullVector();
    T vSecondIntersectionA2 = T::GetNullVector();
    T vSecondIntersectionB1 = T::GetNullVector();
    T vSecondIntersectionB2 = T::GetNullVector();
    T vSecondIntersectionC1 = T::GetNullVector();
    T vSecondIntersectionC2 = T::GetNullVector();
    EIntersections eEndpointAAndVertexACoincide1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionA1, vSecondIntersectionA1);
    EIntersections eEndpointBAndVertexACoincide2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionA2, vSecondIntersectionA2);
    EIntersections eEndpointAAndVertexBCoincide1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionB1, vSecondIntersectionB1);
    EIntersections eEndpointBAndVertexBCoincide2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstIntersectionB2, vSecondIntersectionB2);
    EIntersections eEndpointAAndVertexCCoincide1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstIntersectionC1, vSecondIntersectionC1);
    EIntersections eEndpointBAndVertexCCoincide2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstIntersectionC2, vSecondIntersectionC2);

    // [Verification]
    BOOST_CHECK(eEndpointAAndVertexACoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexACoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAAndVertexBCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexBCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAAndVertexCCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointBAndVertexCCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == VERTEX_A);
    BOOST_CHECK(vFirstIntersectionA2 == VERTEX_A);
    BOOST_CHECK(vFirstIntersectionB1 == VERTEX_B);
    BOOST_CHECK(vFirstIntersectionB2 == VERTEX_B);
    BOOST_CHECK(vFirstIntersectionC1 == VERTEX_C);
    BOOST_CHECK(vFirstIntersectionC2 == VERTEX_C);
    BOOST_CHECK(vSecondIntersectionA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment intersects with two edges of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineSegmentIntersectsWithTwoEdgesOfTriangle_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);

    const T POINT_A1 = MID_POINT_AB.Lerp(-SFloat::_2, MID_POINT_BC);
    const T POINT_B1 = MID_POINT_AB.Lerp(SFloat::_2, MID_POINT_BC);
    const T POINT_A2 = MID_POINT_BC.Lerp(-SFloat::_2, MID_POINT_CA);
    const T POINT_B2 = MID_POINT_BC.Lerp(SFloat::_2, MID_POINT_CA);
    const T POINT_A3 = MID_POINT_CA.Lerp(-SFloat::_2, MID_POINT_AB);
    const T POINT_B3 = MID_POINT_CA.Lerp(SFloat::_2, MID_POINT_AB);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB_BC = MID_POINT_AB;
    const T EXPECTED_FIRSTPOINT_BC_CA = MID_POINT_BC;
    const T EXPECTED_FIRSTPOINT_CA_AB = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT_AB_BC = MID_POINT_BC;
    const T EXPECTED_SECONDPOINT_BC_CA = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT_CA_AB = MID_POINT_AB;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersectionAB_BC;
    T vFirstIntersectionBC_CA;
    T vFirstIntersectionCA_AB;
    T vSecondIntersectionAB_BC;
    T vSecondIntersectionBC_CA;
    T vSecondIntersectionCA_AB;
    EIntersections eIntersectsWithAB_BC = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB_BC, vSecondIntersectionAB_BC);
    EIntersections eIntersectsWithBC_CA = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionBC_CA, vSecondIntersectionBC_CA);
    EIntersections eIntersectsWithCA_AB = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionCA_AB, vSecondIntersectionCA_AB);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB_BC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC_CA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB_BC == EXPECTED_FIRSTPOINT_AB_BC);
    BOOST_CHECK(vFirstIntersectionBC_CA == EXPECTED_FIRSTPOINT_BC_CA);
    BOOST_CHECK(vFirstIntersectionCA_AB == EXPECTED_FIRSTPOINT_CA_AB);
    BOOST_CHECK(vSecondIntersectionAB_BC == EXPECTED_SECONDPOINT_AB_BC);
    BOOST_CHECK(vSecondIntersectionBC_CA == EXPECTED_SECONDPOINT_BC_CA);
    BOOST_CHECK(vSecondIntersectionCA_AB == EXPECTED_SECONDPOINT_CA_AB);
}

/// <summary>
/// Checks that it returns one intersection point when an endpoint of the line segment belongs to the triangle and the line intersects with an edge of the triangle.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenEndpointBelongsToTriangleAndLineIntersectsEdge_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);

    const T MID_POINT_AB = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_A);
    const T MID_POINT_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const T MID_POINT_CA = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_A);
    const T INNER_POINT = MID_POINT_AB.Lerp(SFloat::_0_5, MID_POINT_BC).Lerp(SFloat::_0_5, MID_POINT_CA);

    const T POINT_A1 = INNER_POINT;
    const T POINT_B1 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_AB);
    const T POINT_A2 = INNER_POINT;
    const T POINT_B2 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_BC);
    const T POINT_A3 = INNER_POINT;
    const T POINT_B3 = INNER_POINT.Lerp(SFloat::_2, MID_POINT_CA);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A1, POINT_B1);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A2, POINT_B2);
    const LineSegment3D<T> LINE_SEGMENT3 = LineSegment3D<T>(POINT_A3, POINT_B3);

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const T EXPECTED_FIRSTPOINT_AB = MID_POINT_AB;
    const T EXPECTED_FIRSTPOINT_BC = MID_POINT_BC;
    const T EXPECTED_FIRSTPOINT_CA = MID_POINT_CA;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB;
    T vFirstIntersectionBC;
    T vFirstIntersectionCA;
    T vSecondIntersectionAB = T::GetNullVector();
    T vSecondIntersectionBC = T::GetNullVector();
    T vSecondIntersectionCA = T::GetNullVector();
    EIntersections eIntersectsWithAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eIntersectsWithBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eIntersectsWithCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstIntersectionCA, vSecondIntersectionCA);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondIntersectionAB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCA == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenAllTriangleVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_4, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = VERTEX_A;
    const T VERTEX_C = VERTEX_A;

    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstIntersection, vSecondIntersection);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { SFloat::_3, SFloat::_2, SFloat::_1, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_IN_EDGE[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const LineSegment3D<T> LINE_SEGMENT_IN_EDGE = LineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_1, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_5, SFloat::_2, SFloat::_0, SFloat::_1 };
    const T VERTEX_A = T(VERTEX_A_COMPONENTS);
    const T VERTEX_B = T(VERTEX_B_COMPONENTS);
    const T VERTEX_C = T(VERTEX_C_COMPONENTS);
    const BaseTriangle<T> TRIANGLE = BaseTriangle<T>(VERTEX_A, VERTEX_B, VERTEX_C);

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionContained = T::GetNullVector();
    T vFirstIntersectionInEdge = T::GetNullVector();
    T vFirstIntersectionNotContained = T::GetNullVector();
    T vSecondIntersectionContained = T::GetNullVector();
    T vSecondIntersectionInEdge = T::GetNullVector();
    T vSecondIntersectionNotContained = T::GetNullVector();

    const EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(TRIANGLE, vFirstIntersectionContained, vSecondIntersectionContained);
    const EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vFirstIntersectionInEdge, vSecondIntersectionInEdge);
    const EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(TRIANGLE, vFirstIntersectionNotContained, vSecondIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vFirstIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vSecondIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns two intersection points when a common line segment and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TTemplateTypes )
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
    const float_z POINT_A_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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

    const float_z POINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(POINT_COMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vIntersection;
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vIntersection == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineSegmentIntersectsWithHexahedronVertex_Test, TTemplateTypes )
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

    const float_z POINT_A_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_z POINT_A_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_H);

    const LineSegment3D<T> LINE_SEGMENT_A = LineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const LineSegment3D<T> LINE_SEGMENT_B = LineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const LineSegment3D<T> LINE_SEGMENT_C = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const LineSegment3D<T> LINE_SEGMENT_D = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const LineSegment3D<T> LINE_SEGMENT_E = LineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const LineSegment3D<T> LINE_SEGMENT_F = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const LineSegment3D<T> LINE_SEGMENT_G = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const LineSegment3D<T> LINE_SEGMENT_H = LineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

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

	// [Execution]
    T vFirstIntersectionA;
    T vFirstIntersectionB;
    T vFirstIntersectionC;
    T vFirstIntersectionD;
    T vFirstIntersectionE;
    T vFirstIntersectionF;
    T vFirstIntersectionG;
    T vFirstIntersectionH;
    EIntersections eIntersectsWithA = LINE_SEGMENT_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA);
    EIntersections eIntersectsWithB = LINE_SEGMENT_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB);
    EIntersections eIntersectsWithC = LINE_SEGMENT_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC);
    EIntersections eIntersectsWithD = LINE_SEGMENT_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD);
    EIntersections eIntersectsWithE = LINE_SEGMENT_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE);
    EIntersections eIntersectsWithF = LINE_SEGMENT_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF);
    EIntersections eIntersectsWithG = LINE_SEGMENT_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG);
    EIntersections eIntersectsWithH = LINE_SEGMENT_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH);

    // [Verification]
    BOOST_CHECK(eIntersectsWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithH == EXPECTED_RESULT);
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
/// Checks that it returns no intersection points when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_0, SFloat::_4, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFace_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron and the other endpoint is inside the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFaceAndTheOtherEndpointIsInsideTheHexahedron_Test, TTemplateTypes )
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

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_B_DFGC, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_B_ADFE, POINT_A_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_B_AEHB, POINT_A_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_B_CGHB, POINT_A_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_B_ABCD, POINT_A_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = CENTER_POINT;
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_B_EFGH, POINT_A_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
}

/// <summary>
/// Checks that it returns two intersection points when the endpoints of the line segment belongs to different faces of the hexahedron and the other endpoint is inside the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenEndpointsAreContainedInDifferentHexahedronFaces_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_ABHE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC_ABHE1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_ABHE);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC_ABHE2 = LineSegment3D<T>(POINT_B_ABHE, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_BCHG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE_BCHG1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_BCHG);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE_BCHG2 = LineSegment3D<T>(POINT_B_BCHG, POINT_A_ADFE);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH_ABCD1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH_ABCD2 = LineSegment3D<T>(POINT_B_ABCD, POINT_A_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC_ABHE1 = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_DFGC_ABHE2 = POINT_B_ABHE;
    const T EXPECTED_FIRSTPOINT_ADFE_BCHG1 = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_ADFE_BCHG2 = POINT_B_BCHG;
    const T EXPECTED_FIRSTPOINT_EFGH_ABCD1 = POINT_A_EFGH;
    const T EXPECTED_FIRSTPOINT_EFGH_ABCD2 = POINT_B_ABCD;

	// [Execution]
    T vFirstIntersectionDFGC_ABHE1 = T::GetNullVector();
    T vFirstIntersectionDFGC_ABHE2 = T::GetNullVector();
    T vFirstIntersectionADFE_BCHG1 = T::GetNullVector();
    T vFirstIntersectionADFE_BCHG2 = T::GetNullVector();
    T vFirstIntersectionEFGH_ABCD1 = T::GetNullVector();
    T vFirstIntersectionEFGH_ABCD2 = T::GetNullVector();

    EIntersections eContainedInDFGC_ABHE1 = LINE_SEGMENT_IN_DFGC_ABHE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC_ABHE1);
    EIntersections eContainedInDFGC_ABHE2 = LINE_SEGMENT_IN_DFGC_ABHE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC_ABHE2);
    EIntersections eContainedInADFE_BCHG1 = LINE_SEGMENT_IN_ADFE_BCHG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE_BCHG1);
    EIntersections eContainedInADFE_BCHG2 = LINE_SEGMENT_IN_ADFE_BCHG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE_BCHG2);
    EIntersections eContainedInEFGH_ABCD1 = LINE_SEGMENT_IN_EFGH_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH_ABCD1);
    EIntersections eContainedInEFGH_ABCD2 = LINE_SEGMENT_IN_EFGH_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH_ABCD2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC_ABHE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC_ABHE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE_BCHG1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE_BCHG2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH_ABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH_ABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC_ABHE1 == EXPECTED_FIRSTPOINT_DFGC_ABHE1);
    BOOST_CHECK(vFirstIntersectionDFGC_ABHE2 == EXPECTED_FIRSTPOINT_DFGC_ABHE2);
    BOOST_CHECK(vFirstIntersectionADFE_BCHG1 == EXPECTED_FIRSTPOINT_ADFE_BCHG1);
    BOOST_CHECK(vFirstIntersectionADFE_BCHG2 == EXPECTED_FIRSTPOINT_ADFE_BCHG2);
    BOOST_CHECK(vFirstIntersectionEFGH_ABCD1 == EXPECTED_FIRSTPOINT_EFGH_ABCD1);
    BOOST_CHECK(vFirstIntersectionEFGH_ABCD2 == EXPECTED_FIRSTPOINT_EFGH_ABCD2);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineSegmentBelongsToHexahedronFace_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.A;
    const T EXPECTED_FIRSTPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.A;
    const T EXPECTED_FIRSTPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.A;
    const T EXPECTED_FIRSTPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.A;
    const T EXPECTED_FIRSTPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.A;
    const T EXPECTED_FIRSTPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.A;
    const T EXPECTED_FIRSTPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.A;
    const T EXPECTED_FIRSTPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.A;
    const T EXPECTED_FIRSTPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.A;
    const T EXPECTED_FIRSTPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.A;
    const T EXPECTED_FIRSTPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.A;
    const T EXPECTED_FIRSTPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.A;

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    EIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1);
    EIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2);
    EIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1);
    EIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2);
    EIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1);
    EIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2);
    EIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1);
    EIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2);
    EIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1);
    EIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2);
    EIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1);
    EIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC1);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC2);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE1);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE2);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB1);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB2);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB1);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB2);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD1);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD2);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH1);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH2);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointIsContainedInHexahedron_Test, TTemplateTypes )
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

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_D);

    const T POINT_A = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A.Lerp(SFloat::_2, EXPECTED_FIRSTPOINT);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(HEXAHEDRON, vFirstIntersection1);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(HEXAHEDRON, vFirstIntersection2);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB1 = LineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB2 = LineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC1 = LineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC2 = LineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD1 = LineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD2 = LineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA1 = LineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA2 = LineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF1 = LineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF2 = LineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG1 = LineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG2 = LineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH1 = LineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH2 = LineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE1 = LineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE2 = LineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF1 = LineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF2 = LineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE1 = LineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE2 = LineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH1 = LineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH2 = LineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG1 = LineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG2 = LineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1;
    T vFirstIntersectionBC1;
    T vFirstIntersectionCD1;
    T vFirstIntersectionDA1;
    T vFirstIntersectionEF1;
    T vFirstIntersectionFG1;
    T vFirstIntersectionGH1;
    T vFirstIntersectionHE1;
    T vFirstIntersectionDF1;
    T vFirstIntersectionAE1;
    T vFirstIntersectionBH1;
    T vFirstIntersectionCG1;
    T vFirstIntersectionAB2;
    T vFirstIntersectionBC2;
    T vFirstIntersectionCD2;
    T vFirstIntersectionDA2;
    T vFirstIntersectionEF2;
    T vFirstIntersectionFG2;
    T vFirstIntersectionGH2;
    T vFirstIntersectionHE2;
    T vFirstIntersectionDF2;
    T vFirstIntersectionAE2;
    T vFirstIntersectionBH2;
    T vFirstIntersectionCG2;
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2);
    EIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1);
    EIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2);
    EIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1);
    EIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2);
    EIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1);
    EIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2);
    EIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1);
    EIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2);
    EIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1);
    EIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2);
    EIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1);
    EIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2);
    EIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1);
    EIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2);
    EIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1);
    EIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2);
    EIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1);
    EIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2);
    EIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1);
    EIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB = LineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC = LineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD = LineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA = LineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF = LineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG = LineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH = LineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE = LineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF = LineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE = LineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH = LineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG = LineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT_IN_AB.A;
    const T EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT_IN_BC.A;
    const T EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT_IN_CD.A;
    const T EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT_IN_DA.A;
    const T EXPECTED_FIRSTPOINT_EF = LINE_SEGMENT_IN_EF.A;
    const T EXPECTED_FIRSTPOINT_FG = LINE_SEGMENT_IN_FG.A;
    const T EXPECTED_FIRSTPOINT_GH = LINE_SEGMENT_IN_GH.A;
    const T EXPECTED_FIRSTPOINT_HE = LINE_SEGMENT_IN_HE.A;
    const T EXPECTED_FIRSTPOINT_DF = LINE_SEGMENT_IN_DF.A;
    const T EXPECTED_FIRSTPOINT_AE = LINE_SEGMENT_IN_AE.A;
    const T EXPECTED_FIRSTPOINT_BH = LINE_SEGMENT_IN_BH.A;
    const T EXPECTED_FIRSTPOINT_CG = LINE_SEGMENT_IN_CG.A;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
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
    EIntersections eEndpointContainedInAB = LINE_SEGMENT_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EIntersections eEndpointContainedInBC = LINE_SEGMENT_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EIntersections eEndpointContainedInCD = LINE_SEGMENT_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EIntersections eEndpointContainedInDA = LINE_SEGMENT_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EIntersections eEndpointContainedInEF = LINE_SEGMENT_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EIntersections eEndpointContainedInFG = LINE_SEGMENT_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EIntersections eEndpointContainedInGH = LINE_SEGMENT_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EIntersections eEndpointContainedInHE = LINE_SEGMENT_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EIntersections eEndpointContainedInDF = LINE_SEGMENT_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EIntersections eEndpointContainedInAE = LINE_SEGMENT_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EIntersections eEndpointContainedInBH = LINE_SEGMENT_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EIntersections eEndpointContainedInCG = LINE_SEGMENT_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG == EXPECTED_RESULT);
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
/// Checks that it returns one intersection point when the line segment intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
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

    const float_z POINT_A_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B));
    const LineSegment3D<T> LINE_SEGMENT_TO_AB = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C));
    const LineSegment3D<T> LINE_SEGMENT_TO_BC = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D));
    const LineSegment3D<T> LINE_SEGMENT_TO_CD = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A));
    const LineSegment3D<T> LINE_SEGMENT_TO_DA = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_EF = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G));;
    const LineSegment3D<T> LINE_SEGMENT_TO_FG = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_GH = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_HE = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_DF = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_AE = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_BH = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G));
    const LineSegment3D<T> LINE_SEGMENT_TO_CG = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

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

	// [Execution]
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
    EIntersections eIntersectsWithAB = LINE_SEGMENT_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB);
    EIntersections eIntersectsWithBC = LINE_SEGMENT_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC);
    EIntersections eIntersectsWithCD = LINE_SEGMENT_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD);
    EIntersections eIntersectsWithDA = LINE_SEGMENT_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA);
    EIntersections eIntersectsWithEF = LINE_SEGMENT_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF);
    EIntersections eIntersectsWithFG = LINE_SEGMENT_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG);
    EIntersections eIntersectsWithGH = LINE_SEGMENT_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH);
    EIntersections eIntersectsWithHE = LINE_SEGMENT_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE);
    EIntersections eIntersectsWithDF = LINE_SEGMENT_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF);
    EIntersections eIntersectsWithAE = LINE_SEGMENT_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE);
    EIntersections eIntersectsWithBH = LINE_SEGMENT_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH);
    EIntersections eIntersectsWithCG = LINE_SEGMENT_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithDA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithEF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithFG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithGH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithHE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithDF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCG == EXPECTED_RESULT);
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
/// Checks that it returns one intersection when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenEndpointAndHexahedronVertexCoincide_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const LineSegment3D<T> LINE_SEGMENT_FROM_A1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_A2 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B1 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B2 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C1 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C2 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D1 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D2 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E1 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E2 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F1 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F2 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G1 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G2 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H1 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H2 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

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

	// [Execution]
    T vFirstIntersectionA1;
    T vFirstIntersectionB1;
    T vFirstIntersectionC1;
    T vFirstIntersectionD1;
    T vFirstIntersectionE1;
    T vFirstIntersectionF1;
    T vFirstIntersectionG1;
    T vFirstIntersectionH1;
    T vFirstIntersectionA2;
    T vFirstIntersectionB2;
    T vFirstIntersectionC2;
    T vFirstIntersectionD2;
    T vFirstIntersectionE2;
    T vFirstIntersectionF2;
    T vFirstIntersectionG2;
    T vFirstIntersectionH2;
    EIntersections eEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA1);
    EIntersections eEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA2);
    EIntersections eEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB1);
    EIntersections eEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB2);
    EIntersections eEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC1);
    EIntersections eEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC2);
    EIntersections eEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD1);
    EIntersections eEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD2);
    EIntersections eEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE1);
    EIntersections eEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE2);
    EIntersections eEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF1);
    EIntersections eEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF2);
    EIntersections eEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG1);
    EIntersections eEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG2);
    EIntersections eEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH1);
    EIntersections eEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH2);

    // [Verification]
    BOOST_CHECK(eEndpointAndACoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndACoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndBCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndBCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndCCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndCCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndDCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndDCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndECoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndECoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndFCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndFCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndGCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndGCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndHCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndHCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB1 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC1 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD1 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE1 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF1 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG1 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH1 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vFirstIntersectionA2 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB2 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC2 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD2 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE2 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF2 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG2 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH2 == EXPECTED_FIRSTPOINT_H);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
    T vFirstIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z VERTEX_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VERTEX = T(VERTEX_COMPONENTS);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX, VERTEX);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    T vFirstIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.


    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { (float_z)1.5, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_IN_EDGE[] = { (float_z)1.5, SFloat::_2, SFloat::_4, SFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const LineSegment3D<T> LINE_SEGMENT_IN_EDGE = LineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_z POINT_COMPONENTS_IN_FACE[] = { (float_z)1.5, (float_z)1.5, SFloat::_4, SFloat::_1 };
    const T POINT_IN_FACE(POINT_COMPONENTS_IN_FACE);
    const LineSegment3D<T> LINE_SEGMENT_IN_FACE = LineSegment3D<T>(POINT_IN_FACE, POINT_IN_FACE);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_4, SFloat::_1 };
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

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_IN_FACE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_IN_FACE = POINT_IN_FACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vIntersectionContained = T::GetNullVector();
    T vIntersectionInEdge = T::GetNullVector();
    T vIntersectionInFace = T::GetNullVector();
    T vIntersectionNotContained = T::GetNullVector();

    const EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(HEXAHEDRON, vIntersectionContained);
    const EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(HEXAHEDRON, vIntersectionInEdge);
    const EIntersections eResultInFace = LINE_SEGMENT_IN_FACE.IntersectionPoint(HEXAHEDRON, vIntersectionInFace);
    const EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(HEXAHEDRON, vIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultInFace == EXPECTED_RESULT_IN_FACE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns two intersection points when a common line segment and a common hexahedron intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenCommonLineSegmentIntersectsWithCommonHexahedron_Test, TTemplateTypes )
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
    const float_z POINT_A_COMPONENTS[] = { SFloat::_0, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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

    const float_z FIRSTPOINT_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const float_z SECONDPOINT_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(FIRSTPOINT_COMPONENTS);
    const T EXPECTED_SECONDPOINT = T(SECONDPOINT_COMPONENTS);
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
    T vFirstIntersection;
    T vSecondIntersection;
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when a common line segment intersect with a vertex of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenLineSegmentIntersectsWithHexahedronVertex_Test, TTemplateTypes )
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

    const float_z POINT_A_COMPONENTS_LEFT[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_LEFT(POINT_A_COMPONENTS_LEFT);

    const float_z POINT_A_COMPONENTS_RIGHT[] = { SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T POINT_A_RIGHT(POINT_A_COMPONENTS_RIGHT);

    const T POINT_B_A = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A);
    const T POINT_B_B = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B);
    const T POINT_B_C = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C);
    const T POINT_B_D = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D);
    const T POINT_B_E = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_E);
    const T POINT_B_F = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_F);
    const T POINT_B_G = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_G);
    const T POINT_B_H = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_H);

    const LineSegment3D<T> LINE_SEGMENT_A = LineSegment3D<T>(POINT_A_LEFT, POINT_B_A);
    const LineSegment3D<T> LINE_SEGMENT_B = LineSegment3D<T>(POINT_A_LEFT, POINT_B_B);
    const LineSegment3D<T> LINE_SEGMENT_C = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_C);
    const LineSegment3D<T> LINE_SEGMENT_D = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_D);
    const LineSegment3D<T> LINE_SEGMENT_E = LineSegment3D<T>(POINT_A_LEFT, POINT_B_E);
    const LineSegment3D<T> LINE_SEGMENT_F = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_F);
    const LineSegment3D<T> LINE_SEGMENT_G = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_G);
    const LineSegment3D<T> LINE_SEGMENT_H = LineSegment3D<T>(POINT_A_LEFT, POINT_B_H);

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

	// [Execution]
    T vFirstIntersectionA, vSecondIntersectionA;
    T vFirstIntersectionB, vSecondIntersectionB;
    T vFirstIntersectionC, vSecondIntersectionC;
    T vFirstIntersectionD, vSecondIntersectionD;
    T vFirstIntersectionE, vSecondIntersectionE;
    T vFirstIntersectionF, vSecondIntersectionF;
    T vFirstIntersectionG, vSecondIntersectionG;
    T vFirstIntersectionH, vSecondIntersectionH;
    EIntersections eIntersectsWithA = LINE_SEGMENT_A.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA, vSecondIntersectionA);
    EIntersections eIntersectsWithB = LINE_SEGMENT_B.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB, vSecondIntersectionB);
    EIntersections eIntersectsWithC = LINE_SEGMENT_C.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC, vSecondIntersectionC);
    EIntersections eIntersectsWithD = LINE_SEGMENT_D.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD, vSecondIntersectionD);
    EIntersections eIntersectsWithE = LINE_SEGMENT_E.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE, vSecondIntersectionE);
    EIntersections eIntersectsWithF = LINE_SEGMENT_F.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF, vSecondIntersectionF);
    EIntersections eIntersectsWithG = LINE_SEGMENT_G.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG, vSecondIntersectionG);
    EIntersections eIntersectsWithH = LINE_SEGMENT_H.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH, vSecondIntersectionH);

    // [Verification]
    BOOST_CHECK(eIntersectsWithA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithH == EXPECTED_RESULT);
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
/// Checks that it returns no intersection points when a common line segment and a common hexahedron would intersect if the line segment was lengthened.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsNoIntersectionsWhenLineSegmentDoesNotIntersectWithHexahedronButWouldDoIfLineSegmentWasLengthened_Test, TTemplateTypes )
{

    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_0, SFloat::_4, SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenAnEndpointIsContainedInHexahedronFace_Test, TTemplateTypes )
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

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC + Vector3(SFloat::_1, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE + Vector3(SFloat::_0, SFloat::_0, SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB + Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB + Vector3(SFloat::_0, SFloat::_0, -SFloat::_1);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD + Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH + Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT_DFGC = POINT_A_DFGC;
    const T EXPECTED_FIRSTPOINT_ADFE = POINT_A_ADFE;
    const T EXPECTED_FIRSTPOINT_AEHB = POINT_A_AEHB;
    const T EXPECTED_FIRSTPOINT_CGHB = POINT_A_CGHB;
    const T EXPECTED_FIRSTPOINT_ABCD = POINT_A_ABCD;
    const T EXPECTED_FIRSTPOINT_EFGH = POINT_A_EFGH;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    T vSecondIntersectionDFGC1 = T::GetNullVector();
    T vSecondIntersectionDFGC2 = T::GetNullVector();
    T vSecondIntersectionADFE1 = T::GetNullVector();
    T vSecondIntersectionADFE2 = T::GetNullVector();
    T vSecondIntersectionAEHB1 = T::GetNullVector();
    T vSecondIntersectionAEHB2 = T::GetNullVector();
    T vSecondIntersectionCGHB1 = T::GetNullVector();
    T vSecondIntersectionCGHB2 = T::GetNullVector();
    T vSecondIntersectionABCD1 = T::GetNullVector();
    T vSecondIntersectionABCD2 = T::GetNullVector();
    T vSecondIntersectionEFGH1 = T::GetNullVector();
    T vSecondIntersectionEFGH2 = T::GetNullVector();
    EIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1, vSecondIntersectionDFGC1);
    EIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2, vSecondIntersectionDFGC2);
    EIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1, vSecondIntersectionADFE1);
    EIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2, vSecondIntersectionADFE2);
    EIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1, vSecondIntersectionAEHB1);
    EIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2, vSecondIntersectionAEHB2);
    EIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1, vSecondIntersectionCGHB1);
    EIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2, vSecondIntersectionCGHB2);
    EIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1, vSecondIntersectionABCD1);
    EIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2, vSecondIntersectionABCD2);
    EIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1, vSecondIntersectionEFGH1);
    EIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2, vSecondIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH);
    BOOST_CHECK(vSecondIntersectionDFGC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDFGC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionADFE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionADFE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAEHB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAEHB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCGHB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCGHB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionABCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionABCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEFGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEFGH2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment belongs to a face of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenLineSegmentBelongsToHexahedronFace_Test, TTemplateTypes )
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
    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T POINT_A_DFGC = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_DFGC = POINT_A_DFGC.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC1 = LineSegment3D<T>(POINT_A_DFGC, POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DFGC2 = LineSegment3D<T>(POINT_B_DFGC, POINT_A_DFGC);

    const T POINT_A_ADFE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_F);
    const T POINT_B_ADFE = POINT_A_ADFE.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE1 = LineSegment3D<T>(POINT_A_ADFE, POINT_B_ADFE);
    const LineSegment3D<T> LINE_SEGMENT_IN_ADFE2 = LineSegment3D<T>(POINT_B_ADFE, POINT_A_ADFE);

    const T POINT_A_AEHB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_AEHB = POINT_A_AEHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB1 = LineSegment3D<T>(POINT_A_AEHB, POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AEHB2 = LineSegment3D<T>(POINT_B_AEHB, POINT_A_AEHB);

    const T POINT_A_CGHB = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_H);
    const T POINT_B_CGHB = POINT_A_CGHB.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB1 = LineSegment3D<T>(POINT_A_CGHB, POINT_B_CGHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_CGHB2 = LineSegment3D<T>(POINT_B_CGHB, POINT_A_CGHB);

    const T POINT_A_ABCD = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_C);
    const T POINT_B_ABCD = POINT_A_ABCD.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD1 = LineSegment3D<T>(POINT_A_ABCD, POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_ABCD2 = LineSegment3D<T>(POINT_B_ABCD, POINT_A_ABCD);

    const T POINT_A_EFGH = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B_EFGH = POINT_A_EFGH.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH1 = LineSegment3D<T>(POINT_A_EFGH, POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EFGH2 = LineSegment3D<T>(POINT_B_EFGH, POINT_A_EFGH);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.A;
    const T EXPECTED_FIRSTPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.A;
    const T EXPECTED_FIRSTPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.A;
    const T EXPECTED_FIRSTPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.A;
    const T EXPECTED_FIRSTPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.A;
    const T EXPECTED_FIRSTPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.A;
    const T EXPECTED_FIRSTPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.A;
    const T EXPECTED_FIRSTPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.A;
    const T EXPECTED_FIRSTPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.A;
    const T EXPECTED_FIRSTPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.A;
    const T EXPECTED_FIRSTPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.A;
    const T EXPECTED_FIRSTPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.A;
    const T EXPECTED_SECONDPOINT_DFGC1 = LINE_SEGMENT_IN_DFGC1.B;
    const T EXPECTED_SECONDPOINT_DFGC2 = LINE_SEGMENT_IN_DFGC2.B;
    const T EXPECTED_SECONDPOINT_ADFE1 = LINE_SEGMENT_IN_ADFE1.B;
    const T EXPECTED_SECONDPOINT_ADFE2 = LINE_SEGMENT_IN_ADFE2.B;
    const T EXPECTED_SECONDPOINT_AEHB1 = LINE_SEGMENT_IN_AEHB1.B;
    const T EXPECTED_SECONDPOINT_AEHB2 = LINE_SEGMENT_IN_AEHB2.B;
    const T EXPECTED_SECONDPOINT_CGHB1 = LINE_SEGMENT_IN_CGHB1.B;
    const T EXPECTED_SECONDPOINT_CGHB2 = LINE_SEGMENT_IN_CGHB2.B;
    const T EXPECTED_SECONDPOINT_ABCD1 = LINE_SEGMENT_IN_ABCD1.B;
    const T EXPECTED_SECONDPOINT_ABCD2 = LINE_SEGMENT_IN_ABCD2.B;
    const T EXPECTED_SECONDPOINT_EFGH1 = LINE_SEGMENT_IN_EFGH1.B;
    const T EXPECTED_SECONDPOINT_EFGH2 = LINE_SEGMENT_IN_EFGH2.B;

    T vFirstIntersectionDFGC1 = T::GetNullVector();
    T vFirstIntersectionDFGC2 = T::GetNullVector();
    T vFirstIntersectionADFE1 = T::GetNullVector();
    T vFirstIntersectionADFE2 = T::GetNullVector();
    T vFirstIntersectionAEHB1 = T::GetNullVector();
    T vFirstIntersectionAEHB2 = T::GetNullVector();
    T vFirstIntersectionCGHB1 = T::GetNullVector();
    T vFirstIntersectionCGHB2 = T::GetNullVector();
    T vFirstIntersectionABCD1 = T::GetNullVector();
    T vFirstIntersectionABCD2 = T::GetNullVector();
    T vFirstIntersectionEFGH1 = T::GetNullVector();
    T vFirstIntersectionEFGH2 = T::GetNullVector();
    T vSecondIntersectionDFGC1 = T::GetNullVector();
    T vSecondIntersectionDFGC2 = T::GetNullVector();
    T vSecondIntersectionADFE1 = T::GetNullVector();
    T vSecondIntersectionADFE2 = T::GetNullVector();
    T vSecondIntersectionAEHB1 = T::GetNullVector();
    T vSecondIntersectionAEHB2 = T::GetNullVector();
    T vSecondIntersectionCGHB1 = T::GetNullVector();
    T vSecondIntersectionCGHB2 = T::GetNullVector();
    T vSecondIntersectionABCD1 = T::GetNullVector();
    T vSecondIntersectionABCD2 = T::GetNullVector();
    T vSecondIntersectionEFGH1 = T::GetNullVector();
    T vSecondIntersectionEFGH2 = T::GetNullVector();

	// [Execution]
    EIntersections eContainedInDFGC1 = LINE_SEGMENT_IN_DFGC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC1, vSecondIntersectionDFGC1);
    EIntersections eContainedInDFGC2 = LINE_SEGMENT_IN_DFGC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDFGC2, vSecondIntersectionDFGC2);
    EIntersections eContainedInADFE1 = LINE_SEGMENT_IN_ADFE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE1, vSecondIntersectionADFE1);
    EIntersections eContainedInADFE2 = LINE_SEGMENT_IN_ADFE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionADFE2, vSecondIntersectionADFE2);
    EIntersections eContainedInAEHB1 = LINE_SEGMENT_IN_AEHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB1, vSecondIntersectionAEHB1);
    EIntersections eContainedInAEHB2 = LINE_SEGMENT_IN_AEHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAEHB2, vSecondIntersectionAEHB2);
    EIntersections eContainedInCGHB1 = LINE_SEGMENT_IN_CGHB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB1, vSecondIntersectionCGHB1);
    EIntersections eContainedInCGHB2 = LINE_SEGMENT_IN_CGHB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCGHB2, vSecondIntersectionCGHB2);
    EIntersections eContainedInABCD1 = LINE_SEGMENT_IN_ABCD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD1, vSecondIntersectionABCD1);
    EIntersections eContainedInABCD2 = LINE_SEGMENT_IN_ABCD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionABCD2, vSecondIntersectionABCD2);
    EIntersections eContainedInEFGH1 = LINE_SEGMENT_IN_EFGH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH1, vSecondIntersectionEFGH1);
    EIntersections eContainedInEFGH2 = LINE_SEGMENT_IN_EFGH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEFGH2, vSecondIntersectionEFGH2);

    // [Verification]
    BOOST_CHECK(eContainedInDFGC1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInDFGC2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInADFE2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInAEHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInCGHB2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInABCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eContainedInEFGH2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionDFGC1 == EXPECTED_FIRSTPOINT_DFGC1);
    BOOST_CHECK(vFirstIntersectionDFGC2 == EXPECTED_FIRSTPOINT_DFGC2);
    BOOST_CHECK(vFirstIntersectionADFE1 == EXPECTED_FIRSTPOINT_ADFE1);
    BOOST_CHECK(vFirstIntersectionADFE2 == EXPECTED_FIRSTPOINT_ADFE2);
    BOOST_CHECK(vFirstIntersectionAEHB1 == EXPECTED_FIRSTPOINT_AEHB1);
    BOOST_CHECK(vFirstIntersectionAEHB2 == EXPECTED_FIRSTPOINT_AEHB2);
    BOOST_CHECK(vFirstIntersectionCGHB1 == EXPECTED_FIRSTPOINT_CGHB1);
    BOOST_CHECK(vFirstIntersectionCGHB2 == EXPECTED_FIRSTPOINT_CGHB2);
    BOOST_CHECK(vFirstIntersectionABCD1 == EXPECTED_FIRSTPOINT_ABCD1);
    BOOST_CHECK(vFirstIntersectionABCD2 == EXPECTED_FIRSTPOINT_ABCD2);
    BOOST_CHECK(vFirstIntersectionEFGH1 == EXPECTED_FIRSTPOINT_EFGH1);
    BOOST_CHECK(vFirstIntersectionEFGH2 == EXPECTED_FIRSTPOINT_EFGH2);
    BOOST_CHECK(vSecondIntersectionDFGC1 == EXPECTED_SECONDPOINT_DFGC1);
    BOOST_CHECK(vSecondIntersectionDFGC2 == EXPECTED_SECONDPOINT_DFGC2);
    BOOST_CHECK(vSecondIntersectionADFE1 == EXPECTED_SECONDPOINT_ADFE1);
    BOOST_CHECK(vSecondIntersectionADFE2 == EXPECTED_SECONDPOINT_ADFE2);
    BOOST_CHECK(vSecondIntersectionAEHB1 == EXPECTED_SECONDPOINT_AEHB1);
    BOOST_CHECK(vSecondIntersectionAEHB2 == EXPECTED_SECONDPOINT_AEHB2);
    BOOST_CHECK(vSecondIntersectionCGHB1 == EXPECTED_SECONDPOINT_CGHB1);
    BOOST_CHECK(vSecondIntersectionCGHB2 == EXPECTED_SECONDPOINT_CGHB2);
    BOOST_CHECK(vSecondIntersectionABCD1 == EXPECTED_SECONDPOINT_ABCD1);
    BOOST_CHECK(vSecondIntersectionABCD2 == EXPECTED_SECONDPOINT_ABCD2);
    BOOST_CHECK(vSecondIntersectionEFGH1 == EXPECTED_SECONDPOINT_EFGH1);
    BOOST_CHECK(vSecondIntersectionEFGH2 == EXPECTED_SECONDPOINT_EFGH2);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of a line segment is contained in the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointIsContainedInHexahedron_Test, TTemplateTypes )
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

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const T EXPECTED_FIRSTPOINT = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_D);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();

    const T POINT_A = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);
    const T POINT_B = POINT_A.Lerp(SFloat::_2, EXPECTED_FIRSTPOINT);
    const LineSegment3D<T> LINE_SEGMENT1 = LineSegment3D<T>(POINT_A, POINT_B);
    const LineSegment3D<T> LINE_SEGMENT2 = LineSegment3D<T>(POINT_A, POINT_B);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

	// [Execution]
    T vFirstIntersection1;
    T vFirstIntersection2;
    T vSecondIntersection1 = T::GetNullVector();
    T vSecondIntersection2 = T::GetNullVector();
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(HEXAHEDRON, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(HEXAHEDRON, vFirstIntersection2, vSecondIntersection2);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_ABCD = Vector3(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_EFGH = Vector3(SFloat::_0, -SFloat::_1, SFloat::_0);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB1 = LineSegment3D<T>(POINT_A_IN_AB, 
                                                                    POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB2 = LineSegment3D<T>(POINT_A_IN_AB + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC1 = LineSegment3D<T>(POINT_A_IN_BC, 
                                                                    POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC2 = LineSegment3D<T>(POINT_A_IN_BC + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD1 = LineSegment3D<T>(POINT_A_IN_CD, 
                                                                    POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD2 = LineSegment3D<T>(POINT_A_IN_CD + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA1 = LineSegment3D<T>(POINT_A_IN_DA, 
                                                                    POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA2 = LineSegment3D<T>(POINT_A_IN_DA + RELATIVE_POSITION_OF_POINT_B_ABCD, 
                                                                    POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF1 = LineSegment3D<T>(POINT_A_IN_EF, 
                                                                    POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF2 = LineSegment3D<T>(POINT_A_IN_EF + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG1 = LineSegment3D<T>(POINT_A_IN_FG, 
                                                                    POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG2 = LineSegment3D<T>(POINT_A_IN_FG + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH1 = LineSegment3D<T>(POINT_A_IN_GH, 
                                                                    POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH2 = LineSegment3D<T>(POINT_A_IN_GH + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE1 = LineSegment3D<T>(POINT_A_IN_HE, 
                                                                    POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE2 = LineSegment3D<T>(POINT_A_IN_HE + RELATIVE_POSITION_OF_POINT_B_EFGH, 
                                                                    POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF1 = LineSegment3D<T>(POINT_A_IN_DF, 
                                                                    POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF2 = LineSegment3D<T>(POINT_A_IN_DF + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE1 = LineSegment3D<T>(POINT_A_IN_AE, 
                                                                    POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE2 = LineSegment3D<T>(POINT_A_IN_AE + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH1 = LineSegment3D<T>(POINT_A_IN_BH, 
                                                                    POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH2 = LineSegment3D<T>(POINT_A_IN_BH + RELATIVE_POSITION_OF_POINT_B_AEHB, 
                                                                    POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG1 = LineSegment3D<T>(POINT_A_IN_CG, 
                                                                    POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG2 = LineSegment3D<T>(POINT_A_IN_CG + RELATIVE_POSITION_OF_POINT_B_DFGC, 
                                                                    POINT_A_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1, vSecondIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionBC1, vSecondIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionCD1, vSecondIntersectionCD1 = T::GetNullVector();
    T vFirstIntersectionDA1, vSecondIntersectionDA1 = T::GetNullVector();
    T vFirstIntersectionEF1, vSecondIntersectionEF1 = T::GetNullVector();
    T vFirstIntersectionFG1, vSecondIntersectionFG1 = T::GetNullVector();
    T vFirstIntersectionGH1, vSecondIntersectionGH1 = T::GetNullVector();
    T vFirstIntersectionHE1, vSecondIntersectionHE1 = T::GetNullVector();
    T vFirstIntersectionDF1, vSecondIntersectionDF1 = T::GetNullVector();
    T vFirstIntersectionAE1, vSecondIntersectionAE1 = T::GetNullVector();
    T vFirstIntersectionBH1, vSecondIntersectionBH1 = T::GetNullVector();
    T vFirstIntersectionCG1, vSecondIntersectionCG1 = T::GetNullVector();
    T vFirstIntersectionAB2, vSecondIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionBC2, vSecondIntersectionBC2 = T::GetNullVector();
    T vFirstIntersectionCD2, vSecondIntersectionCD2 = T::GetNullVector();
    T vFirstIntersectionDA2, vSecondIntersectionDA2 = T::GetNullVector();
    T vFirstIntersectionEF2, vSecondIntersectionEF2 = T::GetNullVector();
    T vFirstIntersectionFG2, vSecondIntersectionFG2 = T::GetNullVector();
    T vFirstIntersectionGH2, vSecondIntersectionGH2 = T::GetNullVector();
    T vFirstIntersectionHE2, vSecondIntersectionHE2 = T::GetNullVector();
    T vFirstIntersectionDF2, vSecondIntersectionDF2 = T::GetNullVector();
    T vFirstIntersectionAE2, vSecondIntersectionAE2 = T::GetNullVector();
    T vFirstIntersectionBH2, vSecondIntersectionBH2 = T::GetNullVector();
    T vFirstIntersectionCG2, vSecondIntersectionCG2 = T::GetNullVector();
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2, vSecondIntersectionBC2);
    EIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1, vSecondIntersectionCD1);
    EIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2, vSecondIntersectionCD2);
    EIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1, vSecondIntersectionDA1);
    EIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2, vSecondIntersectionDA2);
    EIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1, vSecondIntersectionEF1);
    EIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2, vSecondIntersectionEF2);
    EIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1, vSecondIntersectionFG1);
    EIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2, vSecondIntersectionFG2);
    EIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1, vSecondIntersectionGH1);
    EIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2, vSecondIntersectionGH2);
    EIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1, vSecondIntersectionHE1);
    EIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2, vSecondIntersectionHE2);
    EIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1, vSecondIntersectionDF1);
    EIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2, vSecondIntersectionDF2);
    EIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1, vSecondIntersectionAE1);
    EIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2, vSecondIntersectionAE2);
    EIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1, vSecondIntersectionBH1);
    EIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2, vSecondIntersectionBH2);
    EIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1, vSecondIntersectionCG1);
    EIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2, vSecondIntersectionCG2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the line segment is contained in an edge of the hexahedron and the other is inside the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenOnlyOneEndpointBelongsToEdgeOfHexahedronAndTheOtherIsInsideTheHexahedron_Test, TTemplateTypes )
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

    const T CENTER_POINT = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_G);

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB1 = LineSegment3D<T>(POINT_A_IN_AB, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC1 = LineSegment3D<T>(POINT_A_IN_BC, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD1 = LineSegment3D<T>(POINT_A_IN_CD, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA1 = LineSegment3D<T>(POINT_A_IN_DA, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF1 = LineSegment3D<T>(POINT_A_IN_EF, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG1 = LineSegment3D<T>(POINT_A_IN_FG, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH1 = LineSegment3D<T>(POINT_A_IN_GH, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE1 = LineSegment3D<T>(POINT_A_IN_HE, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF1 = LineSegment3D<T>(POINT_A_IN_DF, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE1 = LineSegment3D<T>(POINT_A_IN_AE, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH1 = LineSegment3D<T>(POINT_A_IN_BH, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG1 = LineSegment3D<T>(POINT_A_IN_CG, CENTER_POINT);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG2 = LineSegment3D<T>(CENTER_POINT, POINT_A_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = POINT_A_IN_AB;
    const T EXPECTED_FIRSTPOINT_BC = POINT_A_IN_BC;
    const T EXPECTED_FIRSTPOINT_CD = POINT_A_IN_CD;
    const T EXPECTED_FIRSTPOINT_DA = POINT_A_IN_DA;
    const T EXPECTED_FIRSTPOINT_EF = POINT_A_IN_EF;
    const T EXPECTED_FIRSTPOINT_FG = POINT_A_IN_FG;
    const T EXPECTED_FIRSTPOINT_GH = POINT_A_IN_GH;
    const T EXPECTED_FIRSTPOINT_HE = POINT_A_IN_HE;
    const T EXPECTED_FIRSTPOINT_DF = POINT_A_IN_DF;
    const T EXPECTED_FIRSTPOINT_AE = POINT_A_IN_AE;
    const T EXPECTED_FIRSTPOINT_BH = POINT_A_IN_BH;
    const T EXPECTED_FIRSTPOINT_CG = POINT_A_IN_CG;
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

	// [Execution]
    T vFirstIntersectionAB1, vSecondIntersectionAB1 = T::GetNullVector();
    T vFirstIntersectionBC1, vSecondIntersectionBC1 = T::GetNullVector();
    T vFirstIntersectionCD1, vSecondIntersectionCD1 = T::GetNullVector();
    T vFirstIntersectionDA1, vSecondIntersectionDA1 = T::GetNullVector();
    T vFirstIntersectionEF1, vSecondIntersectionEF1 = T::GetNullVector();
    T vFirstIntersectionFG1, vSecondIntersectionFG1 = T::GetNullVector();
    T vFirstIntersectionGH1, vSecondIntersectionGH1 = T::GetNullVector();
    T vFirstIntersectionHE1, vSecondIntersectionHE1 = T::GetNullVector();
    T vFirstIntersectionDF1, vSecondIntersectionDF1 = T::GetNullVector();
    T vFirstIntersectionAE1, vSecondIntersectionAE1 = T::GetNullVector();
    T vFirstIntersectionBH1, vSecondIntersectionBH1 = T::GetNullVector();
    T vFirstIntersectionCG1, vSecondIntersectionCG1 = T::GetNullVector();
    T vFirstIntersectionAB2, vSecondIntersectionAB2 = T::GetNullVector();
    T vFirstIntersectionBC2, vSecondIntersectionBC2 = T::GetNullVector();
    T vFirstIntersectionCD2, vSecondIntersectionCD2 = T::GetNullVector();
    T vFirstIntersectionDA2, vSecondIntersectionDA2 = T::GetNullVector();
    T vFirstIntersectionEF2, vSecondIntersectionEF2 = T::GetNullVector();
    T vFirstIntersectionFG2, vSecondIntersectionFG2 = T::GetNullVector();
    T vFirstIntersectionGH2, vSecondIntersectionGH2 = T::GetNullVector();
    T vFirstIntersectionHE2, vSecondIntersectionHE2 = T::GetNullVector();
    T vFirstIntersectionDF2, vSecondIntersectionDF2 = T::GetNullVector();
    T vFirstIntersectionAE2, vSecondIntersectionAE2 = T::GetNullVector();
    T vFirstIntersectionBH2, vSecondIntersectionBH2 = T::GetNullVector();
    T vFirstIntersectionCG2, vSecondIntersectionCG2 = T::GetNullVector();
    EIntersections eEndpointContainedInAB1 = LINE_SEGMENT_IN_AB1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB1, vSecondIntersectionAB1);
    EIntersections eEndpointContainedInAB2 = LINE_SEGMENT_IN_AB2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB2, vSecondIntersectionAB2);
    EIntersections eEndpointContainedInBC1 = LINE_SEGMENT_IN_BC1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC1, vSecondIntersectionBC1);
    EIntersections eEndpointContainedInBC2 = LINE_SEGMENT_IN_BC2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC2, vSecondIntersectionBC2);
    EIntersections eEndpointContainedInCD1 = LINE_SEGMENT_IN_CD1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD1, vSecondIntersectionCD1);
    EIntersections eEndpointContainedInCD2 = LINE_SEGMENT_IN_CD2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD2, vSecondIntersectionCD2);
    EIntersections eEndpointContainedInDA1 = LINE_SEGMENT_IN_DA1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA1, vSecondIntersectionDA1);
    EIntersections eEndpointContainedInDA2 = LINE_SEGMENT_IN_DA2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA2, vSecondIntersectionDA2);
    EIntersections eEndpointContainedInEF1 = LINE_SEGMENT_IN_EF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF1, vSecondIntersectionEF1);
    EIntersections eEndpointContainedInEF2 = LINE_SEGMENT_IN_EF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF2, vSecondIntersectionEF2);
    EIntersections eEndpointContainedInFG1 = LINE_SEGMENT_IN_FG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG1, vSecondIntersectionFG1);
    EIntersections eEndpointContainedInFG2 = LINE_SEGMENT_IN_FG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG2, vSecondIntersectionFG2);
    EIntersections eEndpointContainedInGH1 = LINE_SEGMENT_IN_GH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH1, vSecondIntersectionGH1);
    EIntersections eEndpointContainedInGH2 = LINE_SEGMENT_IN_GH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH2, vSecondIntersectionGH2);
    EIntersections eEndpointContainedInHE1 = LINE_SEGMENT_IN_HE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE1, vSecondIntersectionHE1);
    EIntersections eEndpointContainedInHE2 = LINE_SEGMENT_IN_HE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE2, vSecondIntersectionHE2);
    EIntersections eEndpointContainedInDF1 = LINE_SEGMENT_IN_DF1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF1, vSecondIntersectionDF1);
    EIntersections eEndpointContainedInDF2 = LINE_SEGMENT_IN_DF2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF2, vSecondIntersectionDF2);
    EIntersections eEndpointContainedInAE1 = LINE_SEGMENT_IN_AE1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE1, vSecondIntersectionAE1);
    EIntersections eEndpointContainedInAE2 = LINE_SEGMENT_IN_AE2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE2, vSecondIntersectionAE2);
    EIntersections eEndpointContainedInBH1 = LINE_SEGMENT_IN_BH1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH1, vSecondIntersectionBH1);
    EIntersections eEndpointContainedInBH2 = LINE_SEGMENT_IN_BH2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH2, vSecondIntersectionBH2);
    EIntersections eEndpointContainedInCG1 = LINE_SEGMENT_IN_CG1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG1, vSecondIntersectionCG1);
    EIntersections eEndpointContainedInCG2 = LINE_SEGMENT_IN_CG2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG2, vSecondIntersectionCG2);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionAB1 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC1 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD1 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA1 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF1 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG1 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH1 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE1 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF1 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE1 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH1 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG1 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vFirstIntersectionAB2 == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstIntersectionBC2 == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstIntersectionCD2 == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstIntersectionDA2 == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vFirstIntersectionEF2 == EXPECTED_FIRSTPOINT_EF);
    BOOST_CHECK(vFirstIntersectionFG2 == EXPECTED_FIRSTPOINT_FG);
    BOOST_CHECK(vFirstIntersectionGH2 == EXPECTED_FIRSTPOINT_GH);
    BOOST_CHECK(vFirstIntersectionHE2 == EXPECTED_FIRSTPOINT_HE);
    BOOST_CHECK(vFirstIntersectionDF2 == EXPECTED_FIRSTPOINT_DF);
    BOOST_CHECK(vFirstIntersectionAE2 == EXPECTED_FIRSTPOINT_AE);
    BOOST_CHECK(vFirstIntersectionBH2 == EXPECTED_FIRSTPOINT_BH);
    BOOST_CHECK(vFirstIntersectionCG2 == EXPECTED_FIRSTPOINT_CG);
    BOOST_CHECK(vSecondIntersectionAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionEF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionFG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionGH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionHE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionDF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionAE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionBH2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionCG2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line segment is contained in an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsTwoIntersectionsWhenLineSegmentBelongsToEdgeOfHexahedron_Test, TTemplateTypes )
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

    const T POINT_A_IN_AB = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_B);
    const T POINT_B_IN_AB = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B);
    const LineSegment3D<T> LINE_SEGMENT_IN_AB = LineSegment3D<T>(POINT_A_IN_AB, POINT_B_IN_AB);

    const T POINT_A_IN_BC = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_C);
    const T POINT_B_IN_BC = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C);
    const LineSegment3D<T> LINE_SEGMENT_IN_BC = LineSegment3D<T>(POINT_A_IN_BC, POINT_B_IN_BC);

    const T POINT_A_IN_CD = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_D);
    const T POINT_B_IN_CD = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D);
    const LineSegment3D<T> LINE_SEGMENT_IN_CD = LineSegment3D<T>(POINT_A_IN_CD, POINT_B_IN_CD);

    const T POINT_A_IN_DA = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_A);
    const T POINT_B_IN_DA = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A);
    const LineSegment3D<T> LINE_SEGMENT_IN_DA = LineSegment3D<T>(POINT_A_IN_DA, POINT_B_IN_DA);

    const T POINT_A_IN_EF = VERTEX_E.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_EF = VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_EF = LineSegment3D<T>(POINT_A_IN_EF, POINT_B_IN_EF);

    const T POINT_A_IN_FG = VERTEX_F.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_FG = VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_FG = LineSegment3D<T>(POINT_A_IN_FG, POINT_B_IN_FG);

    const T POINT_A_IN_GH = VERTEX_G.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_GH = VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_GH = LineSegment3D<T>(POINT_A_IN_GH, POINT_B_IN_GH);

    const T POINT_A_IN_HE = VERTEX_H.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_HE = VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_HE = LineSegment3D<T>(POINT_A_IN_HE, POINT_B_IN_HE);

    const T POINT_A_IN_DF = VERTEX_D.Lerp(SFloat::_0_25, VERTEX_F);
    const T POINT_B_IN_DF = VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F);
    const LineSegment3D<T> LINE_SEGMENT_IN_DF = LineSegment3D<T>(POINT_A_IN_DF, POINT_B_IN_DF);

    const T POINT_A_IN_AE = VERTEX_A.Lerp(SFloat::_0_25, VERTEX_E);
    const T POINT_B_IN_AE = VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E);
    const LineSegment3D<T> LINE_SEGMENT_IN_AE = LineSegment3D<T>(POINT_A_IN_AE, POINT_B_IN_AE);

    const T POINT_A_IN_BH = VERTEX_B.Lerp(SFloat::_0_25, VERTEX_H);
    const T POINT_B_IN_BH = VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H);
    const LineSegment3D<T> LINE_SEGMENT_IN_BH = LineSegment3D<T>(POINT_A_IN_BH, POINT_B_IN_BH);

    const T POINT_A_IN_CG = VERTEX_C.Lerp(SFloat::_0_25, VERTEX_G);
    const T POINT_B_IN_CG = VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G);
    const LineSegment3D<T> LINE_SEGMENT_IN_CG = LineSegment3D<T>(POINT_A_IN_CG, POINT_B_IN_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

    const T EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT_IN_AB.A;
    const T EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT_IN_BC.A;
    const T EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT_IN_CD.A;
    const T EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT_IN_DA.A;
    const T EXPECTED_FIRSTPOINT_EF = LINE_SEGMENT_IN_EF.A;
    const T EXPECTED_FIRSTPOINT_FG = LINE_SEGMENT_IN_FG.A;
    const T EXPECTED_FIRSTPOINT_GH = LINE_SEGMENT_IN_GH.A;
    const T EXPECTED_FIRSTPOINT_HE = LINE_SEGMENT_IN_HE.A;
    const T EXPECTED_FIRSTPOINT_DF = LINE_SEGMENT_IN_DF.A;
    const T EXPECTED_FIRSTPOINT_AE = LINE_SEGMENT_IN_AE.A;
    const T EXPECTED_FIRSTPOINT_BH = LINE_SEGMENT_IN_BH.A;
    const T EXPECTED_FIRSTPOINT_CG = LINE_SEGMENT_IN_CG.A;
    const T EXPECTED_SECONDPOINT_AB = LINE_SEGMENT_IN_AB.B;
    const T EXPECTED_SECONDPOINT_BC = LINE_SEGMENT_IN_BC.B;
    const T EXPECTED_SECONDPOINT_CD = LINE_SEGMENT_IN_CD.B;
    const T EXPECTED_SECONDPOINT_DA = LINE_SEGMENT_IN_DA.B;
    const T EXPECTED_SECONDPOINT_EF = LINE_SEGMENT_IN_EF.B;
    const T EXPECTED_SECONDPOINT_FG = LINE_SEGMENT_IN_FG.B;
    const T EXPECTED_SECONDPOINT_GH = LINE_SEGMENT_IN_GH.B;
    const T EXPECTED_SECONDPOINT_HE = LINE_SEGMENT_IN_HE.B;
    const T EXPECTED_SECONDPOINT_DF = LINE_SEGMENT_IN_DF.B;
    const T EXPECTED_SECONDPOINT_AE = LINE_SEGMENT_IN_AE.B;
    const T EXPECTED_SECONDPOINT_BH = LINE_SEGMENT_IN_BH.B;
    const T EXPECTED_SECONDPOINT_CG = LINE_SEGMENT_IN_CG.B;
    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

	// [Execution]
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
    EIntersections eEndpointContainedInAB = LINE_SEGMENT_IN_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eEndpointContainedInBC = LINE_SEGMENT_IN_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eEndpointContainedInCD = LINE_SEGMENT_IN_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eEndpointContainedInDA = LINE_SEGMENT_IN_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eEndpointContainedInEF = LINE_SEGMENT_IN_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eEndpointContainedInFG = LINE_SEGMENT_IN_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eEndpointContainedInGH = LINE_SEGMENT_IN_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eEndpointContainedInHE = LINE_SEGMENT_IN_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eEndpointContainedInDF = LINE_SEGMENT_IN_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eEndpointContainedInAE = LINE_SEGMENT_IN_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eEndpointContainedInBH = LINE_SEGMENT_IN_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eEndpointContainedInCG = LINE_SEGMENT_IN_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eEndpointContainedInAB == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBC == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCD == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDA == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInEF == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInFG == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInGH == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInHE == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInDF == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInAE == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInBH == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointContainedInCG == EXPECTED_RESULT);
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
/// Checks that it returns one intersection point when the line segment intersects with an edge of the hexahedron.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenLineSegmentIntersectsEdgeOfHexahedron_Test, TTemplateTypes )
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

    const float_z POINT_A_OVER_COMPONENTS[]  = { (float_z)1.5, SFloat::_3, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_BELOW_COMPONENTS[] = { (float_z)1.5, SFloat::_0, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_LEFT_COMPONENTS[]  = { SFloat::_0, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const float_z POINT_A_RIGHT_COMPONENTS[] = { SFloat::_3, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T POINT_A_OVER  = T(POINT_A_OVER_COMPONENTS);  // For edges of face ABCD
    const T POINT_A_BELOW = T(POINT_A_BELOW_COMPONENTS); // For edges of face EFGH
    const T POINT_A_LEFT  = T(POINT_A_LEFT_COMPONENTS);  // For edges of face ADFE
    const T POINT_A_RIGHT = T(POINT_A_RIGHT_COMPONENTS); // For edges of face CGHB

    const T POINT_B_TO_AB = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_B));
    const LineSegment3D<T> LINE_SEGMENT_TO_AB = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_AB);

    const T POINT_B_TO_BC = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_C));
    const LineSegment3D<T> LINE_SEGMENT_TO_BC = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_BC);

    const T POINT_B_TO_CD = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_D));
    const LineSegment3D<T> LINE_SEGMENT_TO_CD = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_CD);

    const T POINT_B_TO_DA = POINT_A_OVER.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_A));
    const LineSegment3D<T> LINE_SEGMENT_TO_DA = LineSegment3D<T>(POINT_A_OVER, POINT_B_TO_DA);

    const T POINT_B_TO_EF = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_E.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_EF = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_EF);

    const T POINT_B_TO_FG = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_F.Lerp(SFloat::_0_5, VERTEX_G));;
    const LineSegment3D<T> LINE_SEGMENT_TO_FG = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_FG);

    const T POINT_B_TO_GH = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_G.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_GH = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_GH);

    const T POINT_B_TO_HE = POINT_A_BELOW.Lerp(SFloat::_2, VERTEX_H.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_HE = LineSegment3D<T>(POINT_A_BELOW, POINT_B_TO_HE);

    const T POINT_B_TO_DF = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_D.Lerp(SFloat::_0_5, VERTEX_F));
    const LineSegment3D<T> LINE_SEGMENT_TO_DF = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_DF);

    const T POINT_B_TO_AE = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_A.Lerp(SFloat::_0_5, VERTEX_E));
    const LineSegment3D<T> LINE_SEGMENT_TO_AE = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_AE);

    const T POINT_B_TO_BH = POINT_A_LEFT.Lerp(SFloat::_2, VERTEX_B.Lerp(SFloat::_0_5, VERTEX_H));
    const LineSegment3D<T> LINE_SEGMENT_TO_BH = LineSegment3D<T>(POINT_A_LEFT, POINT_B_TO_BH);

    const T POINT_B_TO_CG = POINT_A_RIGHT.Lerp(SFloat::_2, VERTEX_C.Lerp(SFloat::_0_5, VERTEX_G));
    const LineSegment3D<T> LINE_SEGMENT_TO_CG = LineSegment3D<T>(POINT_A_RIGHT, POINT_B_TO_CG);

    const BaseHexahedron<T> HEXAHEDRON = BaseHexahedron<T>(VERTEX_A, VERTEX_B, VERTEX_C, VERTEX_D, VERTEX_E, VERTEX_F, VERTEX_G, VERTEX_H);

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

	// [Execution]
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
    EIntersections eIntersectsWithAB = LINE_SEGMENT_TO_AB.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAB, vSecondIntersectionAB);
    EIntersections eIntersectsWithBC = LINE_SEGMENT_TO_BC.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBC, vSecondIntersectionBC);
    EIntersections eIntersectsWithCD = LINE_SEGMENT_TO_CD.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCD, vSecondIntersectionCD);
    EIntersections eIntersectsWithDA = LINE_SEGMENT_TO_DA.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDA, vSecondIntersectionDA);
    EIntersections eIntersectsWithEF = LINE_SEGMENT_TO_EF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionEF, vSecondIntersectionEF);
    EIntersections eIntersectsWithFG = LINE_SEGMENT_TO_FG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionFG, vSecondIntersectionFG);
    EIntersections eIntersectsWithGH = LINE_SEGMENT_TO_GH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionGH, vSecondIntersectionGH);
    EIntersections eIntersectsWithHE = LINE_SEGMENT_TO_HE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionHE, vSecondIntersectionHE);
    EIntersections eIntersectsWithDF = LINE_SEGMENT_TO_DF.IntersectionPoint(HEXAHEDRON, vFirstIntersectionDF, vSecondIntersectionDF);
    EIntersections eIntersectsWithAE = LINE_SEGMENT_TO_AE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionAE, vSecondIntersectionAE);
    EIntersections eIntersectsWithBH = LINE_SEGMENT_TO_BH.IntersectionPoint(HEXAHEDRON, vFirstIntersectionBH, vSecondIntersectionBH);
    EIntersections eIntersectsWithCG = LINE_SEGMENT_TO_CG.IntersectionPoint(HEXAHEDRON, vFirstIntersectionCG, vSecondIntersectionCG);

    // [Verification]
    BOOST_CHECK(eIntersectsWithAB == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBC == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCD == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithDA == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithEF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithFG == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithGH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithHE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithDF == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithAE == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithBH == EXPECTED_RESULT);
    BOOST_CHECK(eIntersectsWithCG == EXPECTED_RESULT);
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
/// Checks that it returns one intersection when an endopoint of the line segment and a vertex of the hexahedron coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsOneIntersectionWhenEndpointAndHexahedronVertexCoincide_Test, TTemplateTypes )
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

    const Vector3 RELATIVE_POSITION_OF_POINT_B_DFGC = Vector3(SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 RELATIVE_POSITION_OF_POINT_B_AEHB = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

    const LineSegment3D<T> LINE_SEGMENT_FROM_A1 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_A2 = LineSegment3D<T>(VERTEX_A, VERTEX_A + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B1 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_B2 = LineSegment3D<T>(VERTEX_B, VERTEX_B + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C1 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_C2 = LineSegment3D<T>(VERTEX_C, VERTEX_C + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D1 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_D2 = LineSegment3D<T>(VERTEX_D, VERTEX_D + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E1 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_E2 = LineSegment3D<T>(VERTEX_E, VERTEX_E + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F1 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_F2 = LineSegment3D<T>(VERTEX_F, VERTEX_F + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G1 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_G2 = LineSegment3D<T>(VERTEX_G, VERTEX_G + RELATIVE_POSITION_OF_POINT_B_DFGC);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H1 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);
    const LineSegment3D<T> LINE_SEGMENT_FROM_H2 = LineSegment3D<T>(VERTEX_H, VERTEX_H + RELATIVE_POSITION_OF_POINT_B_AEHB);

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

	// [Execution]
    T vFirstIntersectionA1, vSecondIntersectionA1 = T::GetNullVector();
    T vFirstIntersectionB1, vSecondIntersectionB1 = T::GetNullVector();
    T vFirstIntersectionC1, vSecondIntersectionC1 = T::GetNullVector();
    T vFirstIntersectionD1, vSecondIntersectionD1 = T::GetNullVector();
    T vFirstIntersectionE1, vSecondIntersectionE1 = T::GetNullVector();
    T vFirstIntersectionF1, vSecondIntersectionF1 = T::GetNullVector();
    T vFirstIntersectionG1, vSecondIntersectionG1 = T::GetNullVector();
    T vFirstIntersectionH1, vSecondIntersectionH1 = T::GetNullVector();
    T vFirstIntersectionA2, vSecondIntersectionA2 = T::GetNullVector();
    T vFirstIntersectionB2, vSecondIntersectionB2 = T::GetNullVector();
    T vFirstIntersectionC2, vSecondIntersectionC2 = T::GetNullVector();
    T vFirstIntersectionD2, vSecondIntersectionD2 = T::GetNullVector();
    T vFirstIntersectionE2, vSecondIntersectionE2 = T::GetNullVector();
    T vFirstIntersectionF2, vSecondIntersectionF2 = T::GetNullVector();
    T vFirstIntersectionG2, vSecondIntersectionG2 = T::GetNullVector();
    T vFirstIntersectionH2, vSecondIntersectionH2 = T::GetNullVector();
    EIntersections eEndpointAndACoincide1 = LINE_SEGMENT_FROM_A1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA1, vSecondIntersectionA1);
    EIntersections eEndpointAndACoincide2 = LINE_SEGMENT_FROM_A2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionA2, vSecondIntersectionB1);
    EIntersections eEndpointAndBCoincide1 = LINE_SEGMENT_FROM_B1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB1, vSecondIntersectionC1);
    EIntersections eEndpointAndBCoincide2 = LINE_SEGMENT_FROM_B2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionB2, vSecondIntersectionD1);
    EIntersections eEndpointAndCCoincide1 = LINE_SEGMENT_FROM_C1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC1, vSecondIntersectionE1);
    EIntersections eEndpointAndCCoincide2 = LINE_SEGMENT_FROM_C2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionC2, vSecondIntersectionF1);
    EIntersections eEndpointAndDCoincide1 = LINE_SEGMENT_FROM_D1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD1, vSecondIntersectionG1);
    EIntersections eEndpointAndDCoincide2 = LINE_SEGMENT_FROM_D2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionD2, vSecondIntersectionH1);
    EIntersections eEndpointAndECoincide1 = LINE_SEGMENT_FROM_E1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE1, vSecondIntersectionA2);
    EIntersections eEndpointAndECoincide2 = LINE_SEGMENT_FROM_E2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionE2, vSecondIntersectionB2);
    EIntersections eEndpointAndFCoincide1 = LINE_SEGMENT_FROM_F1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF1, vSecondIntersectionC2);
    EIntersections eEndpointAndFCoincide2 = LINE_SEGMENT_FROM_F2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionF2, vSecondIntersectionD2);
    EIntersections eEndpointAndGCoincide1 = LINE_SEGMENT_FROM_G1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG1, vSecondIntersectionE2);
    EIntersections eEndpointAndGCoincide2 = LINE_SEGMENT_FROM_G2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionG2, vSecondIntersectionF2);
    EIntersections eEndpointAndHCoincide1 = LINE_SEGMENT_FROM_H1.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH1, vSecondIntersectionG2);
    EIntersections eEndpointAndHCoincide2 = LINE_SEGMENT_FROM_H2.IntersectionPoint(HEXAHEDRON, vFirstIntersectionH2, vSecondIntersectionH2);

    // [Verification]
    BOOST_CHECK(eEndpointAndACoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndACoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndBCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndBCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndCCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndCCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndDCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndDCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndECoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndECoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndFCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndFCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndGCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndGCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndHCoincide1 == EXPECTED_RESULT);
    BOOST_CHECK(eEndpointAndHCoincide2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstIntersectionA1 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB1 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC1 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD1 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE1 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF1 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG1 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH1 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vFirstIntersectionA2 == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstIntersectionB2 == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstIntersectionC2 == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstIntersectionD2 == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vFirstIntersectionE2 == EXPECTED_FIRSTPOINT_E);
    BOOST_CHECK(vFirstIntersectionF2 == EXPECTED_FIRSTPOINT_F);
    BOOST_CHECK(vFirstIntersectionG2 == EXPECTED_FIRSTPOINT_G);
    BOOST_CHECK(vFirstIntersectionH2 == EXPECTED_FIRSTPOINT_H);
    BOOST_CHECK(vSecondIntersectionA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionE2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionF2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionG2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondIntersectionH2 == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenLineSegmentEndpointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_A);

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
    T vFirstIntersection;
    T vSecondIntersection;

    try
    {
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
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
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_AssertionFailsWhenAllHexahedronVerticesCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z POINT_A_COMPONENTS[] = { SFloat::_3, SFloat::_3, SFloat::_1, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

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
        LINE_SEGMENT.IntersectionPoint(HEXAHEDRON, vFirstIntersection, vSecondIntersection);
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
/// Checks that it returns the expected results when the endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint5_ReturnsExpectedResultsWhenEndpointsOfSegmentCoincide_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.


    // [Preparation]
    const float_z POINT_COMPONENTS_CONTAINED[] = { (float_z)1.5, (float_z)1.5, SFloat::_2, SFloat::_1 };
    const T POINT_CONTAINED(POINT_COMPONENTS_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_CONTAINED = LineSegment3D<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z POINT_COMPONENTS_IN_EDGE[] = { (float_z)1.5, SFloat::_2, SFloat::_4, SFloat::_1 };
    const T POINT_IN_EDGE(POINT_COMPONENTS_IN_EDGE);
    const LineSegment3D<T> LINE_SEGMENT_IN_EDGE = LineSegment3D<T>(POINT_IN_EDGE, POINT_IN_EDGE);

    const float_z POINT_COMPONENTS_IN_FACE[] = { (float_z)1.5, (float_z)1.5, SFloat::_4, SFloat::_1 };
    const T POINT_IN_FACE(POINT_COMPONENTS_IN_FACE);
    const LineSegment3D<T> LINE_SEGMENT_IN_FACE = LineSegment3D<T>(POINT_IN_FACE, POINT_IN_FACE);

    const float_z POINT_COMPONENTS_NOT_CONTAINED[] = { SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(POINT_COMPONENTS_NOT_CONTAINED);
    const LineSegment3D<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment3D<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    const float_z VERTEX_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_B_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_C_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_0, SFloat::_1 };
    const float_z VERTEX_D_COMPONENTS[] = { SFloat::_2, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_E_COMPONENTS[] = { SFloat::_1, SFloat::_1, SFloat::_4, SFloat::_1 };
    const float_z VERTEX_F_COMPONENTS[] = { SFloat::_2, SFloat::_1, SFloat::_4, SFloat::_1 };
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

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_IN_FACE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;

    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_EDGE = POINT_IN_EDGE;
    const T EXPECTED_POINT_IN_FACE = POINT_IN_FACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstIntersectionContained = T::GetNullVector();
    T vFirstIntersectionInEdge = T::GetNullVector();
    T vFirstIntersectionInFace = T::GetNullVector();
    T vFirstIntersectionNotContained = T::GetNullVector();
    T vSecondIntersectionContained = T::GetNullVector();
    T vSecondIntersectionInEdge = T::GetNullVector();
    T vSecondIntersectionInFace = T::GetNullVector();
    T vSecondIntersectionNotContained = T::GetNullVector();

    const EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(HEXAHEDRON, vFirstIntersectionContained, vSecondIntersectionContained);
    const EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionInEdge, vSecondIntersectionInEdge);
    const EIntersections eResultInFace = LINE_SEGMENT_IN_FACE.IntersectionPoint(HEXAHEDRON, vFirstIntersectionInFace, vSecondIntersectionInFace);
    const EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(HEXAHEDRON, vFirstIntersectionNotContained, vSecondIntersectionNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultInFace == EXPECTED_RESULT_IN_FACE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vFirstIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vFirstIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondIntersectionInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vSecondIntersectionInFace == EXPECTED_POINT_IN_FACE);
    BOOST_CHECK(vSecondIntersectionNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToTheFurthestEndpointWhenLineAndPlaneDoNotIntersect_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    const float_z POINT_A_COMPONENTS[] = { SFloat::_9, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.A);

	// [Execution]
    float_z fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the endpoints of the segment when the line and the plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToEndpointsWhenLineAndPlaneAreParallel, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d * SFloat::_2, PLANE.b * -PLANE.d * SFloat::_2, PLANE.c * -PLANE.d * SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d * SFloat::_2 - SFloat::_2, PLANE.b * -PLANE.d * SFloat::_2 + SFloat::_1, PLANE.c * -PLANE.d * SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = SFloat::Abs(PLANE.d);

	// [Execution]
    float_z fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the line belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( MaxDistance_ReturnsZeroWhenLineBelongsToPlane, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SFloat::_2, PLANE.b * -PLANE.d + SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MaxDistance_ReturnsTheDistanceToTheFurthestEndpointWhenLineAndPlaneIntersect, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    const float_z POINT_A_COMPONENTS[] = { -SFloat::_9, -SFloat::_6, -SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.A);

	// [Execution]
    float_z fResult = LINE_SEGMENT.MaxDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( MaxDistance_AssertionFailsWhenPlaneIsNull, TTemplateTypes )
{

    // [Preparation]
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const float_z POINT_A_COMPONENTS[] = { -SFloat::_9, -SFloat::_6, -SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.MaxDistance(NULL_PLANE);
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
/// Checks that it returns the distance to the closest endpoint of the segment when the line and the plane don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance_ReturnsTheDistanceToTheClosestEndpointWhenLineAndPlaneDoNotIntersect_Test, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    const float_z POINT_A_COMPONENTS[] = { SFloat::_9, SFloat::_6, SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = PLANE.PointDistance(LINE_SEGMENT.B);

	// [Execution]
    float_z fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the endpoints of the segment when the line and the plane are parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance_ReturnsTheDistanceToEndpointsWhenLineAndPlaneAreParallel, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d * SFloat::_2, PLANE.b * -PLANE.d * SFloat::_2, PLANE.c * -PLANE.d * SFloat::_2, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d * SFloat::_2 - SFloat::_2, PLANE.b * -PLANE.d * SFloat::_2 + SFloat::_1, PLANE.c * -PLANE.d * SFloat::_2, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = SFloat::Abs(PLANE.d);

	// [Execution]
    float_z fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the line belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance_ReturnsZeroWhenLineBelongsToPlane, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    
    const float_z POINT_A_COMPONENTS[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { PLANE.a * -PLANE.d - SFloat::_2, PLANE.b * -PLANE.d + SFloat::_1, PLANE.c * -PLANE.d, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the distance to the furthest endpoint of the segment when the line and the plane intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance_ReturnsZeroWhenLineAndPlaneIntersect, TTemplateTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_1, -SFloat::_1).Normalize();
    const float_z POINT_A_COMPONENTS[] = { -SFloat::_9, -SFloat::_6, -SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult = LINE_SEGMENT.MinDistance(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance_AssertionFailsWhenPlaneIsNull, TTemplateTypes )
{

    // [Preparation]
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const float_z POINT_A_COMPONENTS[] = { -SFloat::_9, -SFloat::_6, -SFloat::_7, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_8, SFloat::_4, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.MinDistance(NULL_PLANE);
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
/// Checks that the line segment is correctly projected to the plane when it is in its negative side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIsInNegativeSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_5, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_COMPONENTS_A[] = { (float_z)1.8095238095238098, (float_z)-3.3809523809523805, (float_z)6.238095238095239, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)2.0952380952380958, (float_z)-1.8095238095238084, (float_z)5.3809523809523832, SFloat::_1 };

    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

	// [Execution]
    LineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the line segment is correctly projected to the plane when it is in its positive side.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIsInPositiveSide_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_COMPONENTS_A[] = { (float_z)-0.28571428571428581, (float_z)-5.5714285714285712, (float_z)-2.1428571428571432, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)-0.95238095238095255, (float_z)4.0952380952380949, (float_z)-6.8095238095238102, SFloat::_1 };
    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_10).Normalize();

	// [Execution]
    LineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the line segment is correctly projected to the plane when it intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( ProjectToPlane_LineSegmentIsProjectedWhenItIntersectsWithPlane_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_COMPONENTS_A[] = { SFloat::_0, -SFloat::_5, SFloat::_0, SFloat::_1 };
    const float_z EXPECTED_COMPONENTS_B[] = { (float_z)0.78571428571428581, (float_z)-4.4285714285714288, (float_z)-0.64285714285714235, SFloat::_1 };
    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LineSegment3D<T>(T(EXPECTED_COMPONENTS_A), T(EXPECTED_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

	// [Execution]
    LineSegment3D<T> projectedLineSegment = LINE_SEGMENT.ProjectToPlane(PLANE);
    
    // [Verification]
    // [TODO] Thund: Uncomment when imprecision issues are resolved
    //ESpaceRelation eResult = projectedLineSegment.SpaceRelation(PLANE);
    //BOOST_CHECK(eResult == ESpaceRelation::E_Contained);
    BOOST_CHECK(projectedLineSegment.A == EXPECTED_LINE_SEGMENT.A);
    BOOST_CHECK(projectedLineSegment.B == EXPECTED_LINE_SEGMENT.B);
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
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

	// [Execution]
    LineSegment3D<T> resultNonNotmalized = LINE_SEGMENT.ProjectToPlane(NONNORMALIZED_PLANE);
    LineSegment3D<T> resultNormalized = LINE_SEGMENT.ProjectToPlane(NORMALIZED_PLANE);

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
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.ProjectToPlane(NULL_PLANE);
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
/// Checks that it returns "negative side" when the line segment is "behind" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheLineSegmentIsBehindPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //     A        |
    //      \       |
    //       \      |-->
    //        B     |
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, -SFloat::_6, -SFloat::_3, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the line segment is "in front" the plane and doesn't intersect with it.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheLineSegmentIsInFrontPlaneAndTheyDoNotIntersect_Test, TTemplateTypes )
{
    //    |         A
    //    |          \
    //    |-->        \
    //    |            B
    //

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_6, -SFloat::_3, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when the line segment intersects with the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsBothSidesWhenTheLineSegmentIntersectsWithThePlane_Test, TTemplateTypes )
{
    //     |  A
    //     | /
    //     |/
    //     |
    //    /|
    //   B |

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { -SFloat::_3, -SFloat::_5, -SFloat::_4, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when the line segment belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsContainedWhenTheLineSegmentBelongsToPlane_Test, TTemplateTypes )
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
    LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    LINE_SEGMENT = LINE_SEGMENT.ProjectToPlane(PLANE);

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the line segment is "behind" the plane and one vertex belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsNegativeSideWhenTheLineSegmentIsBehindPlaneAndOneVertexBelongsToPlane_Test, TTemplateTypes )
{
    //     A  |
    //      \ |
    //       \|-->
    //        B
    //        |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10).Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "positive side" when the line segment is "in front" of the plane and one vertex belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ReturnsPositiveSideWhenTheLineSegmentIsInFrontPlaneAndOneVertexBelongsToPlane_Test, TTemplateTypes )
{
    //    |  A
    //    | /
    //    |/-->
    //    B
    //    |

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10).Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, -SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = LINE_SEGMENT.SpaceRelation(PLANE);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is not different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE( SpaceRelation_ResultIsNotDifferentWhenPlaneIsNotNormalized_Test, TTemplateTypes )
{
    //     A  |
    //      \ |
    //       \|-->
    //        B
    //        |

    // [Preparation]
    const Plane NONNORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_1, SFloat::_2, -SFloat::_10);
    const Plane NORMALIZED_PLANE = NONNORMALIZED_PLANE.Normalize();

    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { NORMALIZED_PLANE.a * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.b * -NORMALIZED_PLANE.d, NORMALIZED_PLANE.c * -NORMALIZED_PLANE.d, SFloat::_1 };
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

	// [Execution]
    ESpaceRelation eResultNonNotmalized = LINE_SEGMENT.SpaceRelation(NONNORMALIZED_PLANE);
    ESpaceRelation eResultNormalized = LINE_SEGMENT.SpaceRelation(NORMALIZED_PLANE);

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
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const BasePlane NULL_PLANE = BasePlane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.SpaceRelation(NULL_PLANE);
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
/// Template method used by Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

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

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the coordinate origin when transformation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform1_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_LineSegmentIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LineSegment3D<T>(POINT_A.Transform(CONVERSION),
                                                                      POINT_B.Transform(CONVERSION));

	// [Execution]
    LineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_LineSegmentDoesNotChangeWhenTransformedByIdentityMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix IDENTITY_MATRIX = SpaceConversionMatrix::GetIdentity();

	const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LINE_SEGMENT;

	// [Execution]
    LineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(IDENTITY_MATRIX);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Checks that the line segment is nullified when the matrix equals null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform2_EndpointsAreNullifiedWhenMatrixIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const SpaceConversionMatrix NULL_MATRIX = Matrix4x4::GetNullMatrix();

	const float_z POINT_A_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z POINT_B_COMPONENTS[] = { SFloat::_5, SFloat::_7, SFloat::_9, SFloat::_1 };
    const T POINT_A(POINT_A_COMPONENTS);
    const T POINT_B(POINT_B_COMPONENTS);
    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(POINT_A, POINT_B);

    const LineSegment3D<T> EXPECTED_LINE_SEGMENT = LineSegment3D<T>(T::GetNullVector(), T::GetNullVector());

	// [Execution]
    LineSegment3D<T> lineSegment = LINE_SEGMENT.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK(lineSegment == EXPECTED_LINE_SEGMENT);
}

/// <summary>
/// Template method used by TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

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

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly transformed using common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_CommonLineSegmentIsCorrectlyTransformedWhenUsingCommonTransformationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_LineSegmentVerticesAreMovedToCoordinateOriginWhenTransformationIsNull_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetNullMatrix();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the position of the pivot point when transformation is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_LineSegmentVerticesAreMovedPivotPositionWhenTransformationIsNull_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class T, class MatrixType>
void TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template()
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const TransformationMatrix<MatrixType> TRANSFORMATION = MatrixType::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not transformed when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    TransformWithPivot_LineSegmentIsNotTransformedWhenTransformationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const Vector3 TRANSLATION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const Vector3 TRANSLATION = Vector3::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_z TRANSLATION_X = SFloat::_1;
    const float_z TRANSLATION_Y = SFloat::_2;
    const float_z TRANSLATION_Z = SFloat::_3;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_z TRANSLATION_X = SFloat::_0;
    const float_z TRANSLATION_Y = SFloat::_0;
    const float_z TRANSLATION_Z = SFloat::_0;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Template method used by Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_4, SFloat::_7, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_3, SFloat::_7, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly translated using common translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_CommonLineSegmentIsCorrectlyTranslatedWhenUsingCommonTranslationMatrix_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetNullMatrix();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationIsZero_Template<T, Matrix4x4>();
}

/// <summary>
/// Template method used by Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class T, class MatrixType>
void Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template()
{

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const TranslationMatrix<MatrixType> TRANSLATION = MatrixType::GetIdentity();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Translate(TRANSLATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Test, TTemplateTypes )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Translate3_LineSegmentIsNotTranslatedWhenTranslationMatrixEqualsIdentity_Template<T, Matrix4x4>();
}

/// <summary>
/// Checks that a line segment is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_LineSegmentIsNotRotatedWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate1_VerticesAreMovedToCoordinateOriginWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_LineSegmentIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710659f, -SFloat::_4, -2.1213202f, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142138f, -SFloat::_4, -2.8284268f, SFloat::_1 };
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { 0.70710678118654768, -SFloat::_4, -2.1213203435596428, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { -1.4142135623730949, -SFloat::_4, -2.8284271247461907, SFloat::_1 };
#endif

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_LineSegmentIsNotRotatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Rotate2_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Rotate(ROTATION);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_LineSegmentIsCorrectlyTransformedByCommonQuaternions_Test, TTemplateTypes )
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

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { (float_z)0.29289321881345243, (float_z)1.2928932188134525, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-1.1213203435596424, (float_z)2.7071067811865479, SFloat::_4, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the quaternion equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_LineSegmentIsNotRotateWithPivotdWhenQuaternionEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_VerticesAreMovedToPivotPositionWhenQuaternionIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion ROTATION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_LineSegmentIsCorrectlyTransformedByCommonRotationMatrix_Test, TTemplateTypes )
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

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { (float_z)-1.1213203435596424, SFloat::_1, (float_z)2.2928932188134521, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when the rotation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_LineSegmentIsNotRotateWithPivotdWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the rotation matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    
    const RotationMatrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));
    
    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.RotateWithPivot(ROTATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the components of the scaling vector equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_LineSegmentIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale1_VerticesAreMovedToCoordinateOriginWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_LineSegmentIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale2_VerticesAreMovedToCoordinateOriginWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonScalingMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_4, SFloat::_9, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_8, SFloat::_6, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_LineSegmentIsNotScaledWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const ScalingMatrix3x3 SCALE = Matrix3x3::GetIdentity();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the coordinate origin when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Scale3_VerticesAreMovedToCoordinateOriginWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    
    const ScalingMatrix3x3 SCALE = Matrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = T::GetNullVector();
    const T EXPECTED_VALUE_FOR_B = T::GetNullVector();

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.Scale(SCALE);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonVector_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const Vector3 SCALE = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the components of the scaling vector equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_LineSegmentIsNotScaledWhenVectorComponentsEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const Vector3 SCALE = Vector3::GetVectorOfOnes();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_VerticesAreMovedToPivotPositionWhenVectorIsNull_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 SCALE = Vector3::GetNullVector();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling values.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonValues_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_2;
    const float_z SCALE_Z = SFloat::_3;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the values equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_LineSegmentIsNotScaledWhenValuesEqualOne_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_VerticesAreMovedPivotPositionWhenValuesEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z SCALE_X = SFloat::_0;
    const float_z SCALE_Y = SFloat::_0;
    const float_z SCALE_Z = SFloat::_0;
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a common line segment is correctly scaled using common scaling matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_CommonLineSegmentIsCorrectlyScaledWhenUsingCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_4, SFloat::_2, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z EXPECTED_VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z EXPECTED_VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_6, SFloat::_0, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_A(EXPECTED_VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(EXPECTED_VECTOR_COMPONENTS_B);

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_3);

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled when the matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_LineSegmentIsNotTranslatedWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_1 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const T EXPECTED_VALUE_FOR_A = LINE_SEGMENT.A;
    const T EXPECTED_VALUE_FOR_B = LINE_SEGMENT.B;

    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetIdentity();

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the position of the pivot point when the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_VerticesAreMovedToPivotPositionWhenMatrixEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3::GetNullMatrix();
    
    const float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0 };
    const float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_1, SFloat::_4, SFloat::_0 };

    const LineSegment3D<T> LINE_SEGMENT = LineSegment3D<T>(T(VECTOR_COMPONENTS_A), T(VECTOR_COMPONENTS_B));

    const float_z PIVOT_COMPONENTS[] = {SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0};
    const T PIVOT_POINT = T(PIVOT_COMPONENTS);

    const T EXPECTED_VALUE_FOR_A = PIVOT_POINT;
    const T EXPECTED_VALUE_FOR_B = PIVOT_POINT;

	// [Execution]
    LineSegment3D<T> returnedLineSegment = LINE_SEGMENT.ScaleWithPivot(SCALE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLineSegment.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLineSegment.B == EXPECTED_VALUE_FOR_B);
}

// [TODO] Thund: Protected methods has not been tested yet.
// [TODO] Thund: Some additional tests could be added for IntersectionPoint that receives a BaseHexahedron:
//                  -Two endpoints coinciding with 2 different vertices

// End - Test Suite: LineSegment3D
ZTEST_SUITE_END()
