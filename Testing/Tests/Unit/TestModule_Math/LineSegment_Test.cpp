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

#include "ZMath/LineSegment.h"
#include "LineSegmentWhiteBox.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/BaseOrb.h"
#include "ZCommon/Exceptions/AssertException.h"

using z::Test::LineSegmentWhiteBox;

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( LineSegment_TestSuite )

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
    LineSegment<T> lineSegmentUT;

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

    const LineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

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
    LineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

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
    LineSegment<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

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
    LineSegment<T> lineSegmentUT = LineSegment<T>::GetUnitLine();

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
    LineSegment<T> lineSegmentUT = LineSegment<T>::GetLineZero();

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
    LineSegment<T> lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the correct length is returned when using a common line segment.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetLength_TheCorrectLengthIsReturnedForCommonLine_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const float_z EXPECTED_LENGTH = VALUE_FOR_A.Distance(VALUE_FOR_B);

    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// [Execution]
    float_z fLength = LINE_SEGMENT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the W components of line points doesn't affect the result when using 4D vectors.
/// </summary>
ZTEST_CASE ( GetLength_WComponentDoesNotAffectTheResult_Test )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_2 };
    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_9 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_3 };

    const Vector4 VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const Vector4 VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const Vector4 VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const Vector4 VALUE_FOR_B2(VECTOR_COMPONENTS_B2);

    const LineSegment<Vector4> LINE_SEGMENT1 = LineSegment<Vector4>(VALUE_FOR_A1, VALUE_FOR_B1);
    const LineSegment<Vector4> LINE_SEGMENT2 = LineSegment<Vector4>(VALUE_FOR_A2, VALUE_FOR_B2);

	// [Execution]
    float_z fLength1 = LINE_SEGMENT1.GetLength();
    float_z fLength2 = LINE_SEGMENT2.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the length is always a positive value.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetLength_IsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>( VALUE_FOR_A,  VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(-VALUE_FOR_A,  VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>( VALUE_FOR_A, -VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(-VALUE_FOR_A, -VALUE_FOR_B);

	// [Execution]
    float_z fLengthBothPositive = LINE_SEGMENT1.GetLength();
    float_z fLengthANegative = LINE_SEGMENT2.GetLength();
    float_z fLengthBNegative = LINE_SEGMENT3.GetLength();
    float_z fLengthBothNegative = LINE_SEGMENT4.GetLength();

    // [Verification]
    BOOST_CHECK(SFloat::IsGreaterOrEquals(fLengthBothPositive, SFloat::_0));
    BOOST_CHECK(SFloat::IsGreaterOrEquals(fLengthANegative, SFloat::_0));
    BOOST_CHECK(SFloat::IsGreaterOrEquals(fLengthBNegative, SFloat::_0));
    BOOST_CHECK(SFloat::IsGreaterOrEquals(fLengthBothNegative, SFloat::_0));
}

/// <summary>
/// Checks that zero is returned when A and B points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetLength_ReturnsZeroWhenBothPointsCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B = VALUE_FOR_A;
    const float_z EXPECTED_LENGTH = SFloat::_0;

    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// [Execution]
    float_z fLength = LINE_SEGMENT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the same length is returned whether the name has each point.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetLength_PointsOrderDoesNotMatter_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_2[] = { -SFloat::_4, -SFloat::_5, -SFloat::_6, -SFloat::_8 };

    const T VALUE_FOR_1(VECTOR_COMPONENTS_1);
    const T VALUE_FOR_2(VECTOR_COMPONENTS_2);

    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_1, VALUE_FOR_2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_2, VALUE_FOR_1);

	// [Execution]
    float_z fLength1 = LINE_SEGMENT1.GetLength();
    float_z fLength2 = LINE_SEGMENT2.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the correct center point of the line is calculated for a common segment.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCenter_TheCenterIsCorrectlyCalculatedForCommonLine_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);

    const T EXPECTED_CENTER = VALUE_FOR_A + (VALUE_FOR_B - VALUE_FOR_A) * SFloat::_0_5;

    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// [Execution]
    T vCenter = LINE_SEGMENT.GetCenter();

    // [Verification]
    BOOST_CHECK(vCenter == EXPECTED_CENTER);
}

/// <summary>
/// Checks that the name of the line's points doesn't matter.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCenter_PointsOrderDoesNotMatter_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_2[] = { -SFloat::_4, -SFloat::_5, -SFloat::_6, -SFloat::_8 };

    const T VALUE_FOR_1(VECTOR_COMPONENTS_1);
    const T VALUE_FOR_2(VECTOR_COMPONENTS_2);

    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_1, VALUE_FOR_2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_2, VALUE_FOR_1);

	// [Execution]
    T vCenter1 = LINE_SEGMENT1.GetCenter();
    T vCenter2 = LINE_SEGMENT2.GetCenter();

    // [Verification]
    BOOST_CHECK(vCenter1 == vCenter2);
}

/// <summary>
/// Checks that when the line segment's end points coincide the center also coincides with them.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetCenter_CenterEqualsSegmentEndPointsWhenTheyCoincide_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B = VALUE_FOR_A;

    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

	// [Execution]
    T vCenter = LINE_SEGMENT.GetCenter();

    // [Verification]
    BOOST_CHECK(vCenter == VALUE_FOR_A);
    BOOST_CHECK(vCenter == VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns False when lines don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenLinesDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesCoincideTotally_Test, TTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT3); // II
    bool bResult4 = LINE_SEGMENT3.Intersection(LINE_SEGMENT1); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenAnEndPointIsContainedInTheOtherLine_Test, TTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4 = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7 = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8 = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the 2 lines share only one of their end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesShareOneEndPointOnly_Test, TTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT6 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_z VECTOR_COMPONENTS_A4[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B4[] = { SFloat::_6, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const LineSegment<T> LINE_SEGMENT7 = LineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const LineSegment<T> LINE_SEGMENT8 = LineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1  = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2  = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3  = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4  = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5  = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6  = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7  = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8  = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV
    bool bResult9  = LINE_SEGMENT1.Intersection(LINE_SEGMENT5); // V
    bool bResult10 = LINE_SEGMENT5.Intersection(LINE_SEGMENT1); // V
    bool bResult11 = LINE_SEGMENT1.Intersection(LINE_SEGMENT6); // VI
    bool bResult12 = LINE_SEGMENT6.Intersection(LINE_SEGMENT1); // VI
    bool bResult13 = LINE_SEGMENT3.Intersection(LINE_SEGMENT5); // VII
    bool bResult14 = LINE_SEGMENT5.Intersection(LINE_SEGMENT3); // VII
    bool bResult15 = LINE_SEGMENT3.Intersection(LINE_SEGMENT6); // VIII
    bool bResult16 = LINE_SEGMENT6.Intersection(LINE_SEGMENT3); // VIII
    bool bResult17 = LINE_SEGMENT1.Intersection(LINE_SEGMENT7); // IX
    bool bResult18 = LINE_SEGMENT7.Intersection(LINE_SEGMENT1); // IX
    bool bResult19 = LINE_SEGMENT3.Intersection(LINE_SEGMENT7); // X
    bool bResult20 = LINE_SEGMENT7.Intersection(LINE_SEGMENT3); // X
    bool bResult21 = LINE_SEGMENT1.Intersection(LINE_SEGMENT8); // XI
    bool bResult22 = LINE_SEGMENT8.Intersection(LINE_SEGMENT1); // XI
    bool bResult23 = LINE_SEGMENT3.Intersection(LINE_SEGMENT8); // XII
    bool bResult24 = LINE_SEGMENT8.Intersection(LINE_SEGMENT3); // XII

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult9,  EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult10, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult11, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult12, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult13, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult14, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult15, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult16, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult17, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult18, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult19, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult20, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult21, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult22, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult23, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult24, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
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
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_A3B3[] = { SFloat::_6, SFloat::_8, SFloat::_9, SFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const bool EXPECTED_RESULT_WHEN_INTERSECT = true;
    const bool EXPECTED_RESULT_WHEN_DONT_INTERSECT = false;

	// [Execution]
    bool bResultIntersection1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);
    bool bResultIntersection2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1);
    bool bResultNoIntersection1 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2);
    bool bResultNoIntersection2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultIntersection1, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(bResultIntersection2, EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK_EQUAL(bResultNoIntersection1, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK_EQUAL(bResultNoIntersection2, EXPECTED_RESULT_WHEN_DONT_INTERSECT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns False when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsFalseWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2);
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenLinesCoincidePartially_Test, TTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3 = LINE_SEGMENT1.Intersection(LINE_SEGMENT4); // II
    bool bResult4 = LINE_SEGMENT4.Intersection(LINE_SEGMENT1); // II
    bool bResult5 = LINE_SEGMENT3.Intersection(LINE_SEGMENT2); // III
    bool bResult6 = LINE_SEGMENT2.Intersection(LINE_SEGMENT3); // III
    bool bResult7 = LINE_SEGMENT3.Intersection(LINE_SEGMENT4); // IV
    bool bResult8 = LINE_SEGMENT4.Intersection(LINE_SEGMENT3); // IV

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one line is totally contained in the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection1_ReturnsTrueWhenOneSegmentIsContainedInTheOther_Test, TTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(LINE_SEGMENT2); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(LINE_SEGMENT1); // I
    bool bResult3  = LINE_SEGMENT1.Intersection(LINE_SEGMENT4);// II
    bool bResult4  = LINE_SEGMENT4.Intersection(LINE_SEGMENT1);// II
    bool bResult5  = LINE_SEGMENT1.Intersection(LINE_SEGMENT5);// III
    bool bResult6  = LINE_SEGMENT5.Intersection(LINE_SEGMENT1);// III
    bool bResult7  = LINE_SEGMENT3.Intersection(LINE_SEGMENT4);// IV
    bool bResult8  = LINE_SEGMENT4.Intersection(LINE_SEGMENT3);// IV
    bool bResult9  = LINE_SEGMENT3.Intersection(LINE_SEGMENT5);// V
    bool bResult10 = LINE_SEGMENT5.Intersection(LINE_SEGMENT3);// V

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult4, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult5, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult6, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult7, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult8, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult9, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult10, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line doesn't intersect the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenLineDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_10, SFloat::_10, SFloat::_10, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenOnlyOneEndPointIsInsideTheOrb_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the line is tangent to the orb by only one end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /            \
    //        |  A1---B1   |
    //        \            /
    //          ` ______ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_3 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIntersectsTheOrbInTwoPoints_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsTrueWhenTheLineIsTangentToTheOrb_Test, TTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(ORB);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsFalseWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = {-SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult1 = LINE_SEGMENT1.Intersection(ORB); // I
    bool bResult2 = LINE_SEGMENT2.Intersection(ORB); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_0 );

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.Intersection(ORB);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.Intersection(ORB);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.Intersection(ORB);
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
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SFloat::_0 );

    float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_9, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SFloat::_0 );

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT.Intersection(ORB_CONTAINED);
    bool bResultNotContained = LINE_SEGMENT.Intersection(ORB_NOT_CONTAINED);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection2_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CONTAINED[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_CONTAINED = LineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z VECTOR_COMPONENTS_NOT_CONTAINED[] = { SFloat::_4, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const bool EXPECTED_RESULT_CONTAINED = true;
    const bool EXPECTED_RESULT_NOT_CONTAINED = false;

	// [Execution]
    bool bResultContained = LINE_SEGMENT_CONTAINED.Intersection(ORB);
    bool bResultNotContained = LINE_SEGMENT_NOT_CONTAINED.Intersection(ORB);
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResultContained, EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK_EQUAL(bResultNotContained, EXPECTED_RESULT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when line segments don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_NoIntersectionPointReturnedWhenLinesDoNotIntersect_Test, TTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that the output point doesn't change when there is no intersection.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_OutputPointIsNotModifiedWhenThereIsNoIntersection_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_8, -SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_OneIntersectionPointIsReturnedWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_1 + SFloat::_0_5, SFloat::_1 + SFloat::_0_5, SFloat::_4 + SFloat::_0_5, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when lines coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsInfinitePointsWhenLinesCoincideTotally_Test, TTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    T OUTPUT_POINT3 = T::GetNullVector();
    T OUTPUT_POINT4 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT3); // II
    EIntersections eResult4 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnEndPointIsContainedInTheOtherLine_Test, TTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    T OUTPUT_POINT3 = T::GetNullVector();
    T OUTPUT_POINT4 = T::GetNullVector();
    T OUTPUT_POINT5 = T::GetNullVector();
    T OUTPUT_POINT6 = T::GetNullVector();
    T OUTPUT_POINT7 = T::GetNullVector();
    T OUTPUT_POINT8 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT3); // II
    EIntersections eResult4 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II
    EIntersections eResult5 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT5); // III
    EIntersections eResult6 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT6); // III
    EIntersections eResult7 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT7); // IV
    EIntersections eResult8 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT8); // IV

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 lines share only one of their end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsOnePointWhenLinesShareOneEndPointOnly_Test, TTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_z VECTOR_COMPONENTS_A3[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B3[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT6 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_z VECTOR_COMPONENTS_A4[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B4[] = { SFloat::_6, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const LineSegment<T> LINE_SEGMENT7 = LineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const LineSegment<T> LINE_SEGMENT8 = LineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    T OUTPUT_POINT3 = T::GetNullVector();
    T OUTPUT_POINT4 = T::GetNullVector();
    T OUTPUT_POINT5 = T::GetNullVector();
    T OUTPUT_POINT6 = T::GetNullVector();
    T OUTPUT_POINT7 = T::GetNullVector();
    T OUTPUT_POINT8 = T::GetNullVector();
    T OUTPUT_POINT9 = T::GetNullVector();
    T OUTPUT_POINT10 = T::GetNullVector();
    T OUTPUT_POINT11 = T::GetNullVector();
    T OUTPUT_POINT12 = T::GetNullVector();
    T OUTPUT_POINT13 = T::GetNullVector();
    T OUTPUT_POINT14 = T::GetNullVector();
    T OUTPUT_POINT15 = T::GetNullVector();
    T OUTPUT_POINT16 = T::GetNullVector();
    T OUTPUT_POINT17 = T::GetNullVector();
    T OUTPUT_POINT18 = T::GetNullVector();
    T OUTPUT_POINT19 = T::GetNullVector();
    T OUTPUT_POINT20 = T::GetNullVector();
    T OUTPUT_POINT21 = T::GetNullVector();
    T OUTPUT_POINT22 = T::GetNullVector();
    T OUTPUT_POINT23 = T::GetNullVector();
    T OUTPUT_POINT24 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    EIntersections eResult2  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    EIntersections eResult3  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT3); // II
    EIntersections eResult4  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT4); // II
    EIntersections eResult5  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT5); // III
    EIntersections eResult6  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT6); // III
    EIntersections eResult7  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_POINT7); // IV
    EIntersections eResult8  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT8); // IV
    EIntersections eResult9  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT5, OUTPUT_POINT9); // V
    EIntersections eResult10 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT10); // V
    EIntersections eResult11 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT6, OUTPUT_POINT11); // VI
    EIntersections eResult12 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT12); // VI
    EIntersections eResult13 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT5, OUTPUT_POINT13); // VII
    EIntersections eResult14 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT14); // VII
    EIntersections eResult15 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT6, OUTPUT_POINT15); // VIII
    EIntersections eResult16 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT16); // VIII
    EIntersections eResult17 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT7, OUTPUT_POINT17); // IX
    EIntersections eResult18 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT18); // IX
    EIntersections eResult19 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT7, OUTPUT_POINT19); // X
    EIntersections eResult20 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT20); // X
    EIntersections eResult21 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT8, OUTPUT_POINT21); // XI
    EIntersections eResult22 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT22); // XI
    EIntersections eResult23 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT8, OUTPUT_POINT23); // XII
    EIntersections eResult24 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT3, OUTPUT_POINT24); // XII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(eResult9 == EXPECTED_RESULT);
    BOOST_CHECK(eResult10 == EXPECTED_RESULT);
    BOOST_CHECK(eResult11 == EXPECTED_RESULT);
    BOOST_CHECK(eResult12 == EXPECTED_RESULT);
    BOOST_CHECK(eResult13 == EXPECTED_RESULT);
    BOOST_CHECK(eResult14 == EXPECTED_RESULT);
    BOOST_CHECK(eResult15 == EXPECTED_RESULT);
    BOOST_CHECK(eResult16 == EXPECTED_RESULT);
    BOOST_CHECK(eResult17 == EXPECTED_RESULT);
    BOOST_CHECK(eResult18 == EXPECTED_RESULT);
    BOOST_CHECK(eResult19 == EXPECTED_RESULT);
    BOOST_CHECK(eResult20 == EXPECTED_RESULT);
    BOOST_CHECK(eResult21 == EXPECTED_RESULT);
    BOOST_CHECK(eResult22 == EXPECTED_RESULT);
    BOOST_CHECK(eResult23 == EXPECTED_RESULT);
    BOOST_CHECK(eResult24 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT24 == EXPECTED_POINT2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_z VECTOR_COMPONENTS_A3B3[] = { SFloat::_6, SFloat::_8, SFloat::_9, SFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const EIntersections EXPECTED_RESULT_WHEN_INTERSECT = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_WHEN_DONT_INTERSECT = EIntersections::E_None;

    const T EXPECTED_INTERSECTION_POINT = VALUE_FOR_A1B1;
    const T EXPECTED_NO_INTERSECTION_POINT = T::GetNullVector();

	// [Execution]
    T vIntersection1 = T::GetNullVector();
    T vIntersection2 = T::GetNullVector();
    T vNoIntersection1 = T::GetNullVector();
    T vNoIntersection2 = T::GetNullVector();
    
    EIntersections eResultIntersection1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, vIntersection1);
    EIntersections eResultIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, vIntersection2);
    EIntersections eResultNoIntersection1 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, vNoIntersection1);
    EIntersections eResultNoIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, vNoIntersection2);

    // [Verification]
    BOOST_CHECK(eResultIntersection1 == EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK(eResultIntersection2 == EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK(eResultNoIntersection1 == EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(eResultNoIntersection2 == EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(vIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsNoPointWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_POINT1);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenLinesCoincidePartially_Test, TTemplateTypes )
{
    // A2---A1---B1---B2  I
    //
    // A2---B1---A1---B2  II
    //
    // A2---A1---B2---B1  III
    //
    // A2---B1---B2---A1  IV
    //
    // B2---A1---A2---B1  V
    //
    // B2---B1---A2---A1  VI
    //
    // A1---A2---B2---B1  VII
    //
    // A1---B2---A2---B1  VIII

    // [Preparation]
    const float_z FIRST_POSITION_COMPONENTS[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z SECOND_POSITION_COMPONENTS[] = { SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z THIRD_POSITION_COMPONENTS[] = { SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z FOURTH_POSITION_COMPONENTS[] = { SFloat::_4, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);
    const T FOURTH_POSITION = T(FOURTH_POSITION_COMPONENTS);

    const LineSegment<T> LINE_SEGMENTA_1 = LineSegment<T>(SECOND_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_1 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const LineSegment<T> LINE_SEGMENTA_2 = LineSegment<T>(THIRD_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_2 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const LineSegment<T> LINE_SEGMENTA_3 = LineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_3 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_4 = LineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_4 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_5 = LineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_5 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_6 = LineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_6 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_7 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_7 = LineSegment<T>(SECOND_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_8 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_8 = LineSegment<T>(THIRD_POSITION, SECOND_POSITION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_POINT1 = SECOND_POSITION;
    const T EXPECTED_POINT2 = THIRD_POSITION;
    const T EXPECTED_POINT3 = SECOND_POSITION;
    const T EXPECTED_POINT4 = THIRD_POSITION;
    const T EXPECTED_POINT5 = SECOND_POSITION;
    const T EXPECTED_POINT6 = THIRD_POSITION;
    const T EXPECTED_POINT7 = SECOND_POSITION;
    const T EXPECTED_POINT8 = SECOND_POSITION;
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();
    T OUTPUT_POINT3 = T::GetNullVector();
    T OUTPUT_POINT4 = T::GetNullVector();
    T OUTPUT_POINT5 = T::GetNullVector();
    T OUTPUT_POINT6 = T::GetNullVector();
    T OUTPUT_POINT7 = T::GetNullVector();
    T OUTPUT_POINT8 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_POINT2); // II
    EIntersections eResult3 = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_POINT3); // III
    EIntersections eResult4 = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_POINT4); // IV
    EIntersections eResult5 = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_POINT5); // V
    EIntersections eResult6 = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_POINT6); // VI
    EIntersections eResult7 = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_POINT7); // VII
    EIntersections eResult8 = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_POINT8); // VIII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT3);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT4);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT5);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT6);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT7);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT8);
}

/// <summary>
/// Checks that it returns two intersection points when one line is totally contained in the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint1_ReturnsTwoPointsWhenOneSegmentIsContainedInTheOther_Test, TTemplateTypes )
{
    // A1A2---B1---B2  I
    //
    // A1A2---B2---B1  II
    //
    // B1B2---A1---A2  III
    //
    // B1B2---A2---A1  IV
    //
    // A1B2---B1---A2  V
    //
    // A1B2---A2---B1  VI
    //
    // A2B1---A1---B2  VII
    //
    // A2B1---B2---A1  VIII
    // [Preparation]
    const float_z FIRST_POSITION_COMPONENTS[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z SECOND_POSITION_COMPONENTS[] = { SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z THIRD_POSITION_COMPONENTS[] = { SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);

    const LineSegment<T> LINE_SEGMENTA_1 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_1 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_2 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_2 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const LineSegment<T> LINE_SEGMENTA_3 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_3 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_4 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_4 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_5 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_5 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_6 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_6 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_7 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_7 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_8 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_8 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_POINT1 = FIRST_POSITION;
    const T EXPECTED_POINT2 = FIRST_POSITION;
    const T EXPECTED_POINT3 = SECOND_POSITION;
    const T EXPECTED_POINT4 = SECOND_POSITION;
    const T EXPECTED_POINT5 = FIRST_POSITION;
    const T EXPECTED_POINT6 = FIRST_POSITION;
    const T EXPECTED_POINT7 = SECOND_POSITION;
    const T EXPECTED_POINT8 = SECOND_POSITION;
    T OUTPUT_POINT1  = T::GetNullVector();
    T OUTPUT_POINT2  = T::GetNullVector();
    T OUTPUT_POINT3  = T::GetNullVector();
    T OUTPUT_POINT4  = T::GetNullVector();
    T OUTPUT_POINT5  = T::GetNullVector();
    T OUTPUT_POINT6  = T::GetNullVector();
    T OUTPUT_POINT7  = T::GetNullVector();
    T OUTPUT_POINT8  = T::GetNullVector();

	// [Execution]
    EIntersections eResult1  = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_POINT1);// I
    EIntersections eResult2  = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_POINT2);// II
    EIntersections eResult3  = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_POINT3);// III
    EIntersections eResult4  = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_POINT4);// IV
    EIntersections eResult5  = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_POINT5);// V
    EIntersections eResult6  = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_POINT6);// VI
    EIntersections eResult7  = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_POINT7);// VII
    EIntersections eResult8  = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_POINT8);// VIII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_POINT3 == EXPECTED_POINT3);
    BOOST_CHECK(OUTPUT_POINT4 == EXPECTED_POINT4);
    BOOST_CHECK(OUTPUT_POINT5 == EXPECTED_POINT5);
    BOOST_CHECK(OUTPUT_POINT6 == EXPECTED_POINT6);
    BOOST_CHECK(OUTPUT_POINT7 == EXPECTED_POINT7);
    BOOST_CHECK(OUTPUT_POINT8 == EXPECTED_POINT8);
}

/// <summary>
/// Checks that it doesn't return any intersection point when line segments don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_NoIntersectionPointReturnedWhenLinesDoNotIntersect_Test, TTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetNullVector();
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    T OUTPUT_FIRSTPOINT = T::GetNullVector();
    T OUTPUT_SECONDPOINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that the output point doesn't change when there is no intersection.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_OutputPointIsNotModifiedWhenThereIsNoIntersection_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_8, -SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT = T::GetNullVector();
    T OUTPUT_SECONDPOINT = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // [Verification]
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_OneIntersectionPointIsReturnedWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_1 + SFloat::_0_5, SFloat::_1 + SFloat::_0_5, SFloat::_4 + SFloat::_0_5, SFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(VECTOR_COMPONENTS_EXPECTED);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT = T::GetNullVector();
    T OUTPUT_SECONDPOINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT, OUTPUT_SECONDPOINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when lines coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsInfinitePointsWhenLinesCoincideTotally_Test, TTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT3 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT4 = T::GetNullVector();
    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_SECONDPOINT2 = T::GetNullVector();
    T OUTPUT_SECONDPOINT3 = T::GetNullVector();
    T OUTPUT_SECONDPOINT4 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EIntersections eResult4 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndPointIsContainedInTheOtherLine_Test, TTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_FIRSTPOINT = T(VECTOR_COMPONENTS_EXPECTED);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT3 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT4 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT5 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT6 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT7 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT8 = T::GetNullVector();
    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_SECONDPOINT2 = T::GetNullVector();
    T OUTPUT_SECONDPOINT3 = T::GetNullVector();
    T OUTPUT_SECONDPOINT4 = T::GetNullVector();
    T OUTPUT_SECONDPOINT5 = T::GetNullVector();
    T OUTPUT_SECONDPOINT6 = T::GetNullVector();
    T OUTPUT_SECONDPOINT7 = T::GetNullVector();
    T OUTPUT_SECONDPOINT8 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EIntersections eResult3 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EIntersections eResult4 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II
    EIntersections eResult5 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // III
    EIntersections eResult6 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // III
    EIntersections eResult7 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // IV
    EIntersections eResult8 = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // IV

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when the 2 lines share only one of their end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsOnePointWhenLinesShareOneEndPointOnly_Test, TTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_z VECTOR_COMPONENTS_A3[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B3[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT6 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_z VECTOR_COMPONENTS_A4[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B4[] = { SFloat::_6, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const LineSegment<T> LINE_SEGMENT7 = LineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const LineSegment<T> LINE_SEGMENT8 = LineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    const T EXPECTED_SECONDPOINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();    T OUTPUT_SECONDPOINT2 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT3 = T::GetNullVector();    T OUTPUT_SECONDPOINT3 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT4 = T::GetNullVector();    T OUTPUT_SECONDPOINT4 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT5 = T::GetNullVector();    T OUTPUT_SECONDPOINT5 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT6 = T::GetNullVector();    T OUTPUT_SECONDPOINT6 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT7 = T::GetNullVector();    T OUTPUT_SECONDPOINT7 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT8 = T::GetNullVector();    T OUTPUT_SECONDPOINT8 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT9 = T::GetNullVector();    T OUTPUT_SECONDPOINT9 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT10 = T::GetNullVector();   T OUTPUT_SECONDPOINT10 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT11 = T::GetNullVector();   T OUTPUT_SECONDPOINT11 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT12 = T::GetNullVector();   T OUTPUT_SECONDPOINT12 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT13 = T::GetNullVector();   T OUTPUT_SECONDPOINT13 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT14 = T::GetNullVector();   T OUTPUT_SECONDPOINT14 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT15 = T::GetNullVector();   T OUTPUT_SECONDPOINT15 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT16 = T::GetNullVector();   T OUTPUT_SECONDPOINT16 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT17 = T::GetNullVector();   T OUTPUT_SECONDPOINT17 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT18 = T::GetNullVector();   T OUTPUT_SECONDPOINT18 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT19 = T::GetNullVector();   T OUTPUT_SECONDPOINT19 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT20 = T::GetNullVector();   T OUTPUT_SECONDPOINT20 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT21 = T::GetNullVector();   T OUTPUT_SECONDPOINT21 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT22 = T::GetNullVector();   T OUTPUT_SECONDPOINT22 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT23 = T::GetNullVector();   T OUTPUT_SECONDPOINT23 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT24 = T::GetNullVector();   T OUTPUT_SECONDPOINT24 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EIntersections eResult2  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
    EIntersections eResult3  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // II
    EIntersections eResult4  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // II
    EIntersections eResult5  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // III
    EIntersections eResult6  = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // III
    EIntersections eResult7  = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT4, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // IV
    EIntersections eResult8  = LINE_SEGMENT4.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // IV
    EIntersections eResult9  = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT5, OUTPUT_FIRSTPOINT9, OUTPUT_SECONDPOINT9); // V
    EIntersections eResult10 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT10, OUTPUT_SECONDPOINT10); // V
    EIntersections eResult11 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT6, OUTPUT_FIRSTPOINT11, OUTPUT_SECONDPOINT11); // VI
    EIntersections eResult12 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT12, OUTPUT_SECONDPOINT12); // VI
    EIntersections eResult13 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT5, OUTPUT_FIRSTPOINT13, OUTPUT_SECONDPOINT13); // VII
    EIntersections eResult14 = LINE_SEGMENT5.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT14, OUTPUT_SECONDPOINT14); // VII
    EIntersections eResult15 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT6, OUTPUT_FIRSTPOINT15, OUTPUT_SECONDPOINT15); // VIII
    EIntersections eResult16 = LINE_SEGMENT6.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT16, OUTPUT_SECONDPOINT16); // VIII
    EIntersections eResult17 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT7, OUTPUT_FIRSTPOINT17, OUTPUT_SECONDPOINT17); // IX
    EIntersections eResult18 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT18, OUTPUT_SECONDPOINT18); // IX
    EIntersections eResult19 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT7, OUTPUT_FIRSTPOINT19, OUTPUT_SECONDPOINT19); // X
    EIntersections eResult20 = LINE_SEGMENT7.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT20, OUTPUT_SECONDPOINT20); // X
    EIntersections eResult21 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT8, OUTPUT_FIRSTPOINT21, OUTPUT_SECONDPOINT21); // XI
    EIntersections eResult22 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT22, OUTPUT_SECONDPOINT22); // XI
    EIntersections eResult23 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT8, OUTPUT_FIRSTPOINT23, OUTPUT_SECONDPOINT23); // XII
    EIntersections eResult24 = LINE_SEGMENT8.IntersectionPoint(LINE_SEGMENT3, OUTPUT_FIRSTPOINT24, OUTPUT_SECONDPOINT24); // XII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(eResult9 == EXPECTED_RESULT);
    BOOST_CHECK(eResult10 == EXPECTED_RESULT);
    BOOST_CHECK(eResult11 == EXPECTED_RESULT);
    BOOST_CHECK(eResult12 == EXPECTED_RESULT);
    BOOST_CHECK(eResult13 == EXPECTED_RESULT);
    BOOST_CHECK(eResult14 == EXPECTED_RESULT);
    BOOST_CHECK(eResult15 == EXPECTED_RESULT);
    BOOST_CHECK(eResult16 == EXPECTED_RESULT);
    BOOST_CHECK(eResult17 == EXPECTED_RESULT);
    BOOST_CHECK(eResult18 == EXPECTED_RESULT);
    BOOST_CHECK(eResult19 == EXPECTED_RESULT);
    BOOST_CHECK(eResult20 == EXPECTED_RESULT);
    BOOST_CHECK(eResult21 == EXPECTED_RESULT);
    BOOST_CHECK(eResult22 == EXPECTED_RESULT);
    BOOST_CHECK(eResult23 == EXPECTED_RESULT);
    BOOST_CHECK(eResult24 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT9 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT10 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT11 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT12 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT13 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT14 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT15 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT16 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT17 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT18 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT19 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT20 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT21 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT22 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT23 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT24 == EXPECTED_POINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT9 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT10 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT11 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT12 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT13 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT14 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT15 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT16 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT17 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT18 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT19 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT20 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT21 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT22 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT23 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT24 == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();
    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();
    T OUTPUT_SECONDPOINT2 = T::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // I
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
/// Checks that it returns the expected results when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsExpectedResultsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // A2---(A1B1)---B2
    //
    //        I

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_z VECTOR_COMPONENTS_A3B3[] = { SFloat::_6, SFloat::_8, SFloat::_9, SFloat::_1 };
    const T VALUE_FOR_A3B3(VECTOR_COMPONENTS_A3B3);
    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_A3B3, VALUE_FOR_A3B3);

    const EIntersections EXPECTED_RESULT_WHEN_INTERSECT = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_WHEN_DONT_INTERSECT = EIntersections::E_None;

    const T EXPECTED_INTERSECTION_POINT = VALUE_FOR_A1B1;
    const T EXPECTED_NO_INTERSECTION_POINT = T::GetNullVector();

	// [Execution]
    T vFirstIntersection1 = T::GetNullVector();
    T vSecondIntersection1 = T::GetNullVector();
    T vFirstIntersection2 = T::GetNullVector();
    T vSecondIntersection2 = T::GetNullVector();
    T vFirstNoIntersection1 = T::GetNullVector();
    T vSecondNoIntersection1 = T::GetNullVector();
    T vFirstNoIntersection2 = T::GetNullVector();
    T vSecondNoIntersection2 = T::GetNullVector();
    
    EIntersections eResultIntersection1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, vFirstIntersection1, vSecondIntersection1);
    EIntersections eResultIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, vFirstIntersection2, vSecondIntersection2);
    EIntersections eResultNoIntersection1 = LINE_SEGMENT3.IntersectionPoint(LINE_SEGMENT2, vFirstNoIntersection1, vSecondNoIntersection1);
    EIntersections eResultNoIntersection2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT3, vFirstNoIntersection2, vSecondNoIntersection2);

    // [Verification]
    BOOST_CHECK(eResultIntersection1 == EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK(eResultIntersection2 == EXPECTED_RESULT_WHEN_INTERSECT);
    BOOST_CHECK(eResultNoIntersection1 == EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(eResultNoIntersection2 == EXPECTED_RESULT_WHEN_DONT_INTERSECT);
    BOOST_CHECK(vFirstIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vFirstIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vFirstNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vFirstNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vSecondIntersection1 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vSecondIntersection2 == EXPECTED_INTERSECTION_POINT);
    BOOST_CHECK(vSecondNoIntersection1 == EXPECTED_NO_INTERSECTION_POINT);
    BOOST_CHECK(vSecondNoIntersection2 == EXPECTED_NO_INTERSECTION_POINT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it doesn't return any intersection point when the segment doesn't intersect the other but would do it if it was lengthened to the infinite.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsNoPointWhenSegmentDoesNotIntersectButWouldDoIfTheyHadInfiniteLength_Test, TTemplateTypes )
{
    // A1       A2
    //  \      /
    //   B1   /
    //    ·  /
    //     ·/
    //     /·
    //   B2  ·

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();
    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();
    T OUTPUT_SECONDPOINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(LINE_SEGMENT2, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(LINE_SEGMENT1, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenLinesCoincidePartially_Test, TTemplateTypes )
{
    // A2---A1---B1---B2  I
    //
    // A2---B1---A1---B2  II
    //
    // A2---A1---B2---B1  III
    //
    // A2---B1---B2---A1  IV
    //
    // B2---A1---A2---B1  V
    //
    // B2---B1---A2---A1  VI
    //
    // A1---A2---B2---B1  VII
    //
    // A1---B2---A2---B1  VIII

    // [Preparation]
    const float_z FIRST_POSITION_COMPONENTS[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z SECOND_POSITION_COMPONENTS[] = { SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z THIRD_POSITION_COMPONENTS[] = { SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z FOURTH_POSITION_COMPONENTS[] = { SFloat::_4, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);
    const T FOURTH_POSITION = T(FOURTH_POSITION_COMPONENTS);

    const LineSegment<T> LINE_SEGMENTA_1 = LineSegment<T>(SECOND_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_1 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const LineSegment<T> LINE_SEGMENTA_2 = LineSegment<T>(THIRD_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_2 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);

    const LineSegment<T> LINE_SEGMENTA_3 = LineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_3 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_4 = LineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_4 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_5 = LineSegment<T>(SECOND_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_5 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_6 = LineSegment<T>(FOURTH_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_6 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_7 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_7 = LineSegment<T>(SECOND_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_8 = LineSegment<T>(FIRST_POSITION, FOURTH_POSITION);
    const LineSegment<T> LINE_SEGMENTB_8 = LineSegment<T>(THIRD_POSITION, SECOND_POSITION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT1 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT2 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT3 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT4 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT5 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT6 = THIRD_POSITION;
    const T EXPECTED_FIRSTPOINT7 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT8 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT1 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT2 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT3 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT4 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT5 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT6 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT7 = THIRD_POSITION;
    const T EXPECTED_SECONDPOINT8 = THIRD_POSITION;
    T OUTPUT_FIRSTPOINT1 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT3 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT4 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT5 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT6 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT7 = T::GetNullVector();
    T OUTPUT_FIRSTPOINT8 = T::GetNullVector();
    T OUTPUT_SECONDPOINT1 = T::GetNullVector();
    T OUTPUT_SECONDPOINT2 = T::GetNullVector();
    T OUTPUT_SECONDPOINT3 = T::GetNullVector();
    T OUTPUT_SECONDPOINT4 = T::GetNullVector();
    T OUTPUT_SECONDPOINT5 = T::GetNullVector();
    T OUTPUT_SECONDPOINT6 = T::GetNullVector();
    T OUTPUT_SECONDPOINT7 = T::GetNullVector();
    T OUTPUT_SECONDPOINT8 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1); // I
    EIntersections eResult2 = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2); // II
    EIntersections eResult3 = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3); // III
    EIntersections eResult4 = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4); // IV
    EIntersections eResult5 = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5); // V
    EIntersections eResult6 = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6); // VI
    EIntersections eResult7 = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7); // VII
    EIntersections eResult8 = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8); // VIII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT4);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT5);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT6);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT7);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT8);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT3);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT4);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT5);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT6);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT7);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT8);
}

/// <summary>
/// Checks that it returns two intersection points when one line is totally contained in the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint2_ReturnsTwoPointsWhenOneSegmentIsContainedInTheOther_Test, TTemplateTypes )
{
    // A1A2---B1---B2  I
    //
    // A1A2---B2---B1  II
    //
    // B1B2---A1---A2  III
    //
    // B1B2---A2---A1  IV
    //
    // A1B2---B1---A2  V
    //
    // A1B2---A2---B1  VI
    //
    // A2B1---A1---B2  VII
    //
    // A2B1---B2---A1  VIII
    // [Preparation]
    const float_z FIRST_POSITION_COMPONENTS[] = { SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z SECOND_POSITION_COMPONENTS[] = { SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1 };
    const float_z THIRD_POSITION_COMPONENTS[] = { SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_1 };
    const T FIRST_POSITION = T(FIRST_POSITION_COMPONENTS);
    const T SECOND_POSITION = T(SECOND_POSITION_COMPONENTS);
    const T THIRD_POSITION = T(THIRD_POSITION_COMPONENTS);

    const LineSegment<T> LINE_SEGMENTA_1 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_1 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_2 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_2 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const LineSegment<T> LINE_SEGMENTA_3 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_3 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_4 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_4 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_5 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);
    const LineSegment<T> LINE_SEGMENTB_5 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_6 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);
    const LineSegment<T> LINE_SEGMENTB_6 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);

    const LineSegment<T> LINE_SEGMENTA_7 = LineSegment<T>(SECOND_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_7 = LineSegment<T>(FIRST_POSITION, THIRD_POSITION);

    const LineSegment<T> LINE_SEGMENTA_8 = LineSegment<T>(THIRD_POSITION, FIRST_POSITION);
    const LineSegment<T> LINE_SEGMENTB_8 = LineSegment<T>(FIRST_POSITION, SECOND_POSITION);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const T EXPECTED_FIRSTPOINT1 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT2 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT3 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT4 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT5 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT6 = FIRST_POSITION;
    const T EXPECTED_FIRSTPOINT7 = SECOND_POSITION;
    const T EXPECTED_FIRSTPOINT8 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT1 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT2 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT3 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT4 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT5 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT6 = SECOND_POSITION;
    const T EXPECTED_SECONDPOINT7 = FIRST_POSITION;
    const T EXPECTED_SECONDPOINT8 = FIRST_POSITION;
    T OUTPUT_FIRSTPOINT1  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT2  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT3  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT4  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT5  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT6  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT7  = T::GetNullVector();
    T OUTPUT_FIRSTPOINT8  = T::GetNullVector();
    T OUTPUT_SECONDPOINT1  = T::GetNullVector();
    T OUTPUT_SECONDPOINT2  = T::GetNullVector();
    T OUTPUT_SECONDPOINT3  = T::GetNullVector();
    T OUTPUT_SECONDPOINT4  = T::GetNullVector();
    T OUTPUT_SECONDPOINT5  = T::GetNullVector();
    T OUTPUT_SECONDPOINT6  = T::GetNullVector();
    T OUTPUT_SECONDPOINT7  = T::GetNullVector();
    T OUTPUT_SECONDPOINT8  = T::GetNullVector();

	// [Execution]
    EIntersections eResult1  = LINE_SEGMENTA_1.IntersectionPoint(LINE_SEGMENTB_1, OUTPUT_FIRSTPOINT1, OUTPUT_SECONDPOINT1);// I
    EIntersections eResult2  = LINE_SEGMENTA_2.IntersectionPoint(LINE_SEGMENTB_2, OUTPUT_FIRSTPOINT2, OUTPUT_SECONDPOINT2);// II
    EIntersections eResult3  = LINE_SEGMENTA_3.IntersectionPoint(LINE_SEGMENTB_3, OUTPUT_FIRSTPOINT3, OUTPUT_SECONDPOINT3);// III
    EIntersections eResult4  = LINE_SEGMENTA_4.IntersectionPoint(LINE_SEGMENTB_4, OUTPUT_FIRSTPOINT4, OUTPUT_SECONDPOINT4);// IV
    EIntersections eResult5  = LINE_SEGMENTA_5.IntersectionPoint(LINE_SEGMENTB_5, OUTPUT_FIRSTPOINT5, OUTPUT_SECONDPOINT5);// V
    EIntersections eResult6  = LINE_SEGMENTA_6.IntersectionPoint(LINE_SEGMENTB_6, OUTPUT_FIRSTPOINT6, OUTPUT_SECONDPOINT6);// VI
    EIntersections eResult7  = LINE_SEGMENTA_7.IntersectionPoint(LINE_SEGMENTB_7, OUTPUT_FIRSTPOINT7, OUTPUT_SECONDPOINT7);// VII
    EIntersections eResult8  = LINE_SEGMENTA_8.IntersectionPoint(LINE_SEGMENTB_8, OUTPUT_FIRSTPOINT8, OUTPUT_SECONDPOINT8);// VIII

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
    BOOST_CHECK(eResult7 == EXPECTED_RESULT);
    BOOST_CHECK(eResult8 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_FIRSTPOINT1 == EXPECTED_FIRSTPOINT1);
    BOOST_CHECK(OUTPUT_FIRSTPOINT2 == EXPECTED_FIRSTPOINT2);
    BOOST_CHECK(OUTPUT_FIRSTPOINT3 == EXPECTED_FIRSTPOINT3);
    BOOST_CHECK(OUTPUT_FIRSTPOINT4 == EXPECTED_FIRSTPOINT4);
    BOOST_CHECK(OUTPUT_FIRSTPOINT5 == EXPECTED_FIRSTPOINT5);
    BOOST_CHECK(OUTPUT_FIRSTPOINT6 == EXPECTED_FIRSTPOINT6);
    BOOST_CHECK(OUTPUT_FIRSTPOINT7 == EXPECTED_FIRSTPOINT7);
    BOOST_CHECK(OUTPUT_FIRSTPOINT8 == EXPECTED_FIRSTPOINT8);
    BOOST_CHECK(OUTPUT_SECONDPOINT1 == EXPECTED_SECONDPOINT1);
    BOOST_CHECK(OUTPUT_SECONDPOINT2 == EXPECTED_SECONDPOINT2);
    BOOST_CHECK(OUTPUT_SECONDPOINT3 == EXPECTED_SECONDPOINT3);
    BOOST_CHECK(OUTPUT_SECONDPOINT4 == EXPECTED_SECONDPOINT4);
    BOOST_CHECK(OUTPUT_SECONDPOINT5 == EXPECTED_SECONDPOINT5);
    BOOST_CHECK(OUTPUT_SECONDPOINT6 == EXPECTED_SECONDPOINT6);
    BOOST_CHECK(OUTPUT_SECONDPOINT7 == EXPECTED_SECONDPOINT7);
    BOOST_CHECK(OUTPUT_SECONDPOINT8 == EXPECTED_SECONDPOINT8);
}

/// <summary>
/// Checks that it returns no intersection points when the line doesn't intersect the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_NoIntersectionPointsAreReturnedWhenLineDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_10, SFloat::_10, SFloat::_10, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
}


/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionPointWhenOnlyOneEndPointIsInsideTheOrb_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetNullVector();
    T OUTPUT_POINT1F = T::GetNullVector();
    T OUTPUT_POINT1S = T::GetNullVector();
    T OUTPUT_POINT2F = T::GetNullVector();
    T OUTPUT_POINT2S = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb by only one end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetNullVector();
    T OUTPUT_POINT1F = T::GetNullVector();
    T OUTPUT_POINT1S = T::GetNullVector();
    T OUTPUT_POINT2F = T::GetNullVector();
    T OUTPUT_POINT2S = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the orb. Output points should not change.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenTheLineIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //        |  A1---B1  |
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_3 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINTF = EXPECTED_POINT;
    T OUTPUT_POINTS = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns oen intersection point when the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetNullVector();
    T OUTPUT_POINT1F = T::GetNullVector();
    T OUTPUT_POINT1S = T::GetNullVector();
    T OUTPUT_POINT2F = T::GetNullVector();
    T OUTPUT_POINT2S = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINTS);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns two intersection points when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_z VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTS = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINTF = T::GetNullVector();
    T OUTPUT_POINTS = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenTheLineIntersectsTheOrbInTwoPoints_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_z VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTS = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINTF = T::GetNullVector();
    T OUTPUT_POINTS = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrb_Test, TTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINTF = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    const T EXPECTED_POINTS = T::GetNullVector();
    T OUTPUT_POINTF = T::GetNullVector();
    T OUTPUT_POINTS = EXPECTED_POINTS;

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINTF);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINTS);
}

/// <summary>
/// Checks that it returns no intersection points when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_NoIntersectionIsReturnedWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = {-SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;
    T OUTPUT_POINT2F = EXPECTED_POINT;
    T OUTPUT_POINT2S = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_0 );

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1F = EXPECTED_POINT;
    T OUTPUT_POINT1S = EXPECTED_POINT;
    T OUTPUT_POINT2F = EXPECTED_POINT;
    T OUTPUT_POINT2S = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection point when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINTF = EXPECTED_POINT;
    T OUTPUT_POINTS = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINTF, OUTPUT_POINTS);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINTF == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINTS == EXPECTED_POINT);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SFloat::_0 );

    float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_9, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SFloat::_0 );

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_One;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const T EXPECTED_POINT_CONTAINED = T(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vPointContained = T::GetNullVector();
    T vPointNotContained = T::GetNullVector();
    EIntersections eResultContained = LINE_SEGMENT.IntersectionPoint(ORB_CONTAINED, vPointContained);
    EIntersections eResultNotContained = LINE_SEGMENT.IntersectionPoint(ORB_NOT_CONTAINED, vPointNotContained);

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CONTAINED[] = { (float_z)2.5, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_CONTAINED = LineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z VECTOR_COMPONENTS_IN_SURFACE[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_IN_SURFACE(VECTOR_COMPONENTS_IN_SURFACE);
    const LineSegment<T> LINE_SEGMENT_IN_SURFACE = LineSegment<T>(POINT_IN_SURFACE, POINT_IN_SURFACE);

    const float_z VECTOR_COMPONENTS_NOT_CONTAINED[] = { SFloat::_4, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_SURFACE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_SURFACE = POINT_IN_SURFACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vPointContained = T::GetNullVector();
    T vPointInSurface = T::GetNullVector();
    T vPointNotContained = T::GetNullVector();

    EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(ORB, vPointContained);
    EIntersections eResultInSurface = LINE_SEGMENT_IN_SURFACE.IntersectionPoint(ORB, vPointInSurface);
    EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(ORB, vPointNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInSurface == EXPECTED_RESULT_IN_SURFACE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the first point returned is which is nearer to A end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint3_FirstPointIsNearerToAThanSecondPoint_Test, TTemplateTypes )
{
    //               ______                       ______
    //             ´        `                   ´        `
    //           /           \                /           \
    //   A1--------------------B1    B1---------------------A1
    //           \           /                \           /
    //             ` _____ ´                    ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINTF[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT1F = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    float_z VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT1S = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    const T EXPECTED_POINT2F = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    const T EXPECTED_POINT2S = T(VECTOR_COMPONENTS_OUTPUT_POINTF);
    T OUTPUT_POINT1F = T::GetNullVector();
    T OUTPUT_POINT1S = T::GetNullVector();
    T OUTPUT_POINT2F = T::GetNullVector();
    T OUTPUT_POINT2S = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1F, OUTPUT_POINT1S);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2F, OUTPUT_POINT2S);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1F == EXPECTED_POINT1F);
    BOOST_CHECK(OUTPUT_POINT1S == EXPECTED_POINT1S);
    BOOST_CHECK(OUTPUT_POINT2F == EXPECTED_POINT2F);
    BOOST_CHECK(OUTPUT_POINT2S == EXPECTED_POINT2S);
}

/// <summary>
/// Checks that it returns no intersection points when the line doesn't intersect the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_NoIntersectionPointsAreReturnedWhenLineDoesNotIntersectTheOrb_Test, TTemplateTypes )
{
    // A1           ___
    //  \          /   \
    //   \        |  x  |
    //    \        \___/
    //     \
    //      \
    //       B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_10, SFloat::_10, SFloat::_10, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}


/// <summary>
/// Checks that it returns True when only one end point is inside the orb and the other is outside it.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionPointWhenOnlyOneEndPointIsInsideTheOrb_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------|-B1  |    B1---------|-A1  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb by only one end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrbByAnEndPoint_Test, TTemplateTypes )
{
    //              ___                   ___
    //             /   \                 /   \
    // A1---------B1 x  |    B1---------A1 x  |
    //             \___/                 \___/
    //
    //        I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the orb. Output points should not change.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsInfiniteIntersectionsWhenTheLineIsContainedInTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //        |  A1---B1  |
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_1, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_3 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns oen intersection point when the line is contained in the orb and only one end point coincides with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsContainedInTheOrbAndOneEndPointCoincidesWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______                ______
    //          ´        `            ´        `
    //        /           \         /           \
    //        |      A1---B1        |      B1---A1
    //        \           /         \           /
    //          ` _____ ´             ` _____ ´
    //
    //              I                    II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line is contained in the orb and the 2 end points coincide with the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenTheLineIsContainedInTheOrbAndTheTwoEndPointsCoincideWithTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //       A1-----------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects the orb in two points (and the line is not contained in the orb).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenTheLineIntersectsTheOrbInTwoPoints_Test, TTemplateTypes )
{
    //            ______
    //          ´        `
    //        /           \
    //   A1------------------B1
    //        \           /
    //          ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when the line is tangent to the orb (the tangent point is not A or B).
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsOneIntersectionWhenTheLineIsTangentToTheOrb_Test, TTemplateTypes )
{
    //        A1   _____
    //        |  ´       `
    //        |/           \
    //        |      x     |
    //        |\           /
    //        B1 ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_3, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_1, SFloat::_0, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    T OUTPUT_POINT = T::GetNullVector();

	// [Execution]
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection points when the segment does not intersect the orb but would do it if the segment had an infinite length.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_NoIntersectionIsReturnedWhenTheSegmentDoesNotIntersectTheOrbButWouldDoIfItWasInifinite_Test, TTemplateTypes )
{
    //                ___
    //              /     \
    // A1----B1····|···x···|····
    //              \ ___ /
    //
    //         I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = {-SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = EXPECTED_POINT;
    T OUTPUT_POINT2 = EXPECTED_POINT;

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1); // I
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2); // II

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_0 );

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT1 = EXPECTED_POINT;
    T OUTPUT_POINT2 = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT);
}

/// <summary>
/// Checks that an assertion fails when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_AssertionFailsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_7 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const T EXPECTED_POINT = T::GetNullVector();
    T OUTPUT_POINT = EXPECTED_POINT;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.IntersectionPoint(ORB, OUTPUT_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
    BOOST_CHECK(OUTPUT_POINT == EXPECTED_POINT);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of the orb equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenTheRadiusEqualsZeroAndTheLineIntersectsTheCenter_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //
    // A1----------x-------B1
    //

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);

    float_z VECTOR_COMPONENTS_CENTER_CONTAINED[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_CONTAINED), SFloat::_0 );

    float_z VECTOR_COMPONENTS_CENTER_NOT_CONTAINED[] = { SFloat::_9, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB_NOT_CONTAINED = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER_NOT_CONTAINED), SFloat::_0 );

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_One;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const T EXPECTED_FIRSTPOINT_CONTAINED = T(VECTOR_COMPONENTS_CENTER_CONTAINED);
    const T EXPECTED_SECONDPOINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstPointContained = T::GetNullVector();
    T vFirstPointNotContained = T::GetNullVector();
    T vSecondPointContained = T::GetNullVector();
    T vSecondPointNotContained = T::GetNullVector();
    EIntersections eResultContained = LINE_SEGMENT.IntersectionPoint(ORB_CONTAINED, vFirstPointContained, vSecondPointContained);
    EIntersections eResultNotContained = LINE_SEGMENT.IntersectionPoint(ORB_NOT_CONTAINED, vFirstPointNotContained, vSecondPointNotContained);

    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_FIRSTPOINT_CONTAINED);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_SECONDPOINT_CONTAINED);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

/// <summary>
/// Checks that it returns the expected result when the length of the line equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_ReturnsExpectedResultsWhenTheLengthOfSegmentEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //             _____
    //           ´       `
    //         /           \
    //        A1B1   x     |
    //         \           /
    //           ` _____ ´

    // [Preparation]
    const float_z VECTOR_COMPONENTS_CONTAINED[] = { (float_z)2.5, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_CONTAINED(VECTOR_COMPONENTS_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_CONTAINED = LineSegment<T>(POINT_CONTAINED, POINT_CONTAINED);

    const float_z VECTOR_COMPONENTS_IN_SURFACE[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T POINT_IN_SURFACE(VECTOR_COMPONENTS_IN_SURFACE);
    const LineSegment<T> LINE_SEGMENT_IN_SURFACE = LineSegment<T>(POINT_IN_SURFACE, POINT_IN_SURFACE);

    const float_z VECTOR_COMPONENTS_NOT_CONTAINED[] = { SFloat::_4, SFloat::_6, SFloat::_7, SFloat::_1 };
    const T POINT_NOT_CONTAINED(VECTOR_COMPONENTS_NOT_CONTAINED);
    const LineSegment<T> LINE_SEGMENT_NOT_CONTAINED = LineSegment<T>(POINT_NOT_CONTAINED, POINT_NOT_CONTAINED);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT_CONTAINED = EIntersections::E_Infinite;
    const EIntersections EXPECTED_RESULT_IN_SURFACE = EIntersections::E_Two;
    const EIntersections EXPECTED_RESULT_NOT_CONTAINED = EIntersections::E_None;
    const T EXPECTED_POINT_CONTAINED = T::GetNullVector();
    const T EXPECTED_POINT_IN_SURFACE = POINT_IN_SURFACE;
    const T EXPECTED_POINT_NOT_CONTAINED = T::GetNullVector();

	// [Execution]
    T vFirstPointContained = T::GetNullVector();
    T vSecondPointContained = T::GetNullVector();
    T vFirstPointInSurface = T::GetNullVector();
    T vSecondPointInSurface = T::GetNullVector();
    T vFirstPointNotContained = T::GetNullVector();
    T vSecondPointNotContained = T::GetNullVector();

    EIntersections eResultContained = LINE_SEGMENT_CONTAINED.IntersectionPoint(ORB, vFirstPointContained, vSecondPointContained);
    EIntersections eResultInSurface = LINE_SEGMENT_IN_SURFACE.IntersectionPoint(ORB, vFirstPointInSurface, vSecondPointInSurface);
    EIntersections eResultNotContained = LINE_SEGMENT_NOT_CONTAINED.IntersectionPoint(ORB, vFirstPointNotContained, vSecondPointNotContained);
    
    // [Verification]
    BOOST_CHECK(eResultContained == EXPECTED_RESULT_CONTAINED);
    BOOST_CHECK(eResultInSurface == EXPECTED_RESULT_IN_SURFACE);
    BOOST_CHECK(eResultNotContained == EXPECTED_RESULT_NOT_CONTAINED);
    BOOST_CHECK(vFirstPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vFirstPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vFirstPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
    BOOST_CHECK(vSecondPointContained == EXPECTED_POINT_CONTAINED);
    BOOST_CHECK(vSecondPointInSurface == EXPECTED_POINT_IN_SURFACE);
    BOOST_CHECK(vSecondPointNotContained == EXPECTED_POINT_NOT_CONTAINED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the point returned is which is nearer to A end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint4_FirstPointIsNearerToA_Test, TTemplateTypes )
{
    //               ______                       ______
    //             ´        `                   ´        `
    //           /           \                /           \
    //   A1--------------------B1    B1---------------------A1
    //           \           /                \           /
    //             ` _____ ´                    ` _____ ´

    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A, VALUE_FOR_B);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B, VALUE_FOR_A);

    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    BaseOrb<T> ORB = BaseOrb<T>( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    float_z VECTOR_COMPONENTS_OUTPUT_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_OUTPUT_POINT);
    float_z VECTOR_COMPONENTS_OUTPUT_POINTS[] = { SFloat::_3, SFloat::_2, SFloat::_2, SFloat::_1 };
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_OUTPUT_POINTS);
    T OUTPUT_POINT1 = T::GetNullVector();
    T OUTPUT_POINT2 = T::GetNullVector();

	// [Execution]
    EIntersections eResult1 = LINE_SEGMENT1.IntersectionPoint(ORB, OUTPUT_POINT1);
    EIntersections eResult2 = LINE_SEGMENT2.IntersectionPoint(ORB, OUTPUT_POINT2);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(OUTPUT_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(OUTPUT_POINT2 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that it returns the expected distance when lines don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsExpectedDistanceWhenLinesDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_6, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_z EXPECTED_RESULT = sqrt_z(SFloat::_0_5);

	// [Execution]
    float_z fResult = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when lines coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesCoincideTotally_Test, TTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_z fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT3); // II
    float_z fResult4 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT1); // II

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult4, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenAnEndPointIsContainedInTheOtherLine_Test, TTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_z fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_z fResult4 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_z fResult5 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_z fResult6 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_z fResult7 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_z fResult8 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult8, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the 2 lines share only one of their end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesShareOneEndPointOnly_Test, TTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT6 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_z VECTOR_COMPONENTS_A4[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B4[] = { SFloat::_6, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const LineSegment<T> LINE_SEGMENT7 = LineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const LineSegment<T> LINE_SEGMENT8 = LineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2  = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_z fResult3  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_z fResult4  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_z fResult5  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_z fResult6  = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_z fResult7  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_z fResult8  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV
    float_z fResult9  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT5); // V
    float_z fResult10 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT1); // V
    float_z fResult11 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT6); // VI
    float_z fResult12 = LINE_SEGMENT6.MinDistance(LINE_SEGMENT1); // VI
    float_z fResult13 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT5); // VII
    float_z fResult14 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT3); // VII
    float_z fResult15 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT6); // VIII
    float_z fResult16 = LINE_SEGMENT6.MinDistance(LINE_SEGMENT3); // VIII
    float_z fResult17 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT7); // IX
    float_z fResult18 = LINE_SEGMENT7.MinDistance(LINE_SEGMENT1); // IX
    float_z fResult19 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT7); // X
    float_z fResult20 = LINE_SEGMENT7.MinDistance(LINE_SEGMENT3); // X
    float_z fResult21 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT8); // XI
    float_z fResult22 = LINE_SEGMENT8.MinDistance(LINE_SEGMENT1); // XI
    float_z fResult23 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT8); // XII
    float_z fResult24 = LINE_SEGMENT8.MinDistance(LINE_SEGMENT3); // XII

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult3,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult4,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult5,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult6,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult7,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult8,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult9,  EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult10, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult11, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult12, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult13, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult14, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult15, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult16, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult17, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult18, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult19, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult20, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult21, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult22, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult23, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult24, EXPECTED_RESULT) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_AssertionFailsWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // A1------B1  (A2B2)
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
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
/// Checks that it returns the expected result when the length of one of the segments equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsExpectedResultWhenTheLengthOfOneSegmentEqualsZero_Test, TTemplateTypes )
{
    // A1------B1  (A2B2)
    //
    //        I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const float_z EXPECTED_RESULT = SFloat::_3;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I

    // [Verification]
    BOOST_CHECK_EQUAL(fResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(fResult2, EXPECTED_RESULT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns zero when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenLinesCoincidePartially_Test, TTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_z fResult3 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4); // II
    float_z fResult4 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1); // II
    float_z fResult5 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT2); // III
    float_z fResult6 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT3); // III
    float_z fResult7 = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4); // IV
    float_z fResult8 = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3); // IV

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult8, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when one line is totally contained in the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance1_ReturnsZeroWhenOneSegmentIsContainedInTheOther_Test, TTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegment<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegment<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegment<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(LINE_SEGMENT2); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(LINE_SEGMENT1); // I
    float_z fResult3  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT4);// II
    float_z fResult4  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT1);// II
    float_z fResult5  = LINE_SEGMENT1.MinDistance(LINE_SEGMENT5);// III
    float_z fResult6  = LINE_SEGMENT5.MinDistance(LINE_SEGMENT1);// III
    float_z fResult7  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT4);// IV
    float_z fResult8  = LINE_SEGMENT4.MinDistance(LINE_SEGMENT3);// IV
    float_z fResult9  = LINE_SEGMENT3.MinDistance(LINE_SEGMENT5);// V
    float_z fResult10 = LINE_SEGMENT5.MinDistance(LINE_SEGMENT3);// V

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult3, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult4, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult5, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult6, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult7, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult8, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult9, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult10, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns the expected distance when lines don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance2_ReturnsExpectedDistanceWhenLineAndPointDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_6, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_P[] = { SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_z EXPECTED_RESULT = sqrt_z(SFloat::_0_5);

	// [Execution]
    float_z fResult = LINE_SEGMENT1.MinDistance(POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the point is contained in the line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance2_ReturnsZeroWhenThePointIsContainedInTheLine_Test, TTemplateTypes )
{
    //
    // A1---P---B1    B1---P---A1
    //
    //      I             II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_z VECTOR_COMPONENTS_P[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(POINT); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(POINT); // II

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that it returns zero when the point concides with one of the the segment's end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance2_ReturnsZeroWhenSegmentEndPointCoincidesWithPoint_Test, TTemplateTypes )
{
    //
    // A1P---B1    B1P---A1
    //
    //     I          II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_z VECTOR_COMPONENTS_P[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fResult1 = LINE_SEGMENT1.MinDistance(POINT); // I
    float_z fResult2 = LINE_SEGMENT2.MinDistance(POINT); // II

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult1, EXPECTED_RESULT) );
    BOOST_CHECK( SFloat::AreEqual(fResult2, EXPECTED_RESULT) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the length of the segment equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance2_AssertionFailsWhenTheLengthOfTheSegmentEqualsZero_Test, TTemplateTypes )
{
    // P  (A1B1)
    //
    //     I

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    float_z VECTOR_COMPONENTS_P[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT(VECTOR_COMPONENTS_P);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT1.MinDistance(POINT); // I
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
/// Checks that it returns the expected result when the length of the segment equals zero, even if they intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( MinDistance2_ReturnsExpectedResultWhenTheLengthOfTheSegmentEqualsZero_Test, TTemplateTypes )
{
    // P  (A1B1)
    //
    //      I

    // [Preparation]
    const float_z VECTOR_COMPONENTS_A1B1[] = { SFloat::_7, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1B1(VECTOR_COMPONENTS_A1B1);
    const LineSegment<T> LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A1B1, VALUE_FOR_A1B1);

    const float_z POINT_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T POINT = T(POINT_COMPONENTS);

    const float_z EXPECTED_RESULT = SFloat::_3;

	// [Execution]
    float_z fResult = LINE_SEGMENT.MinDistance(POINT); // I

    // [Verification]
    BOOST_CHECK_EQUAL(fResult, EXPECTED_RESULT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_2;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_LengthDoesNotChangeWhenValueEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_1;
    const float_z ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_LengthEqualsZeroWhenInputValueEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_z FACTOR = SFloat::_0;
    const float_z EXPECTED_LENGTH = SFloat::_0;
    float_z fSegmentLength = SFloat::_0;
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its center.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_SegmentIsLengthenedFromCenter_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_CENTER = lineSegmentUT.GetCenter();
    const float_z FACTOR = SFloat::_0;

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_CENTER);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_CENTER);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_0_5;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Lengthen_ItIsFlippedWhenInputValueIsNegative_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> FLIPPED_LINE_SEGMENT = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = -SFloat::_1;

	// [Execution]
    lineSegmentUT.Lengthen(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A ==  FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B ==  FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_2;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_LengthDoesNotChangeWhenValueEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_1;
    const float_z ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_LengthEqualsZeroWhenInputValueEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_z FACTOR = SFloat::_0;
    const float_z EXPECTED_LENGTH = SFloat::_0;
    float_z fSegmentLength = SFloat::_0;
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its A end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_SegmentIsLengthenedFromA_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_A = lineSegmentUT.A;
    const float_z FACTOR = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_A);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_A);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_0_5;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromA_ItIsFlippedWhenInputValueIsNegative_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> FLIPPED_LINE_SEGMENT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_A1 + VALUE_FOR_A1 - VALUE_FOR_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = -SFloat::_1;

	// [Execution]
    lineSegmentUT.LengthenFromA(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A ==  FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B ==  FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_ItIsLengthenedTheCorrectAmountWhenUsingCommonValue_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_2;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is not lengthened when the input factor equals one.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_LengthDoesNotChangeWhenValueEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_1;
    const float_z ORIGINAL_LENGTH = lineSegmentUT.GetLength();
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, ORIGINAL_LENGTH) );
}

/// <summary>
/// Checks that the length of the segment equals zero when the input value equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_LengthEqualsZeroWhenInputValueEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);

    const float_z FACTOR = SFloat::_0;
    const float_z EXPECTED_LENGTH = SFloat::_0;
    float_z fSegmentLength = SFloat::_0;
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is lengthened from its B end point.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_SegmentIsLengthenedFromB_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const T SEGMENT_A = lineSegmentUT.B;
    const float_z FACTOR = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == SEGMENT_A);
    BOOST_CHECK(lineSegmentUT.B == SEGMENT_A);
}

/// <summary>
/// Checks that the segment is lengthened by the amount provided as input value when it's positive and lower than one.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_ItIsLengthenedTheCorrectAmountWhenValueIsPositiveAndLowerThanOne_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = SFloat::_0_5;
    const float_z EXPECTED_LENGTH = lineSegmentUT.GetLength() * FACTOR;
    float_z fSegmentLength = SFloat::_0;

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);
    fSegmentLength = lineSegmentUT.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fSegmentLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the segment is flipped when the input value is negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( LengthenFromB_ItIsFlippedWhenInputValueIsNegative_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegment<T> FLIPPED_LINE_SEGMENT = LineSegment<T>(VALUE_FOR_B1 + VALUE_FOR_B1 - VALUE_FOR_A1, VALUE_FOR_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const float_z FACTOR = -SFloat::_1;

	// [Execution]
    lineSegmentUT.LengthenFromB(FACTOR);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == FLIPPED_LINE_SEGMENT.A);
    BOOST_CHECK(lineSegmentUT.B == FLIPPED_LINE_SEGMENT.B);
}

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    LineSegment<T> lineSegmentUT = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const string_z A_STRING = VALUE_FOR_A1.ToString();
    const string_z B_STRING = VALUE_FOR_B1.ToString();
    const string_z EXPECTED_STRING = string_z(Z_L("LS(a(")) + A_STRING + string_z(Z_L("),b(")) + B_STRING + string_z(Z_L("))"));

	// [Execution]
    string_z strReturnedString = lineSegmentUT.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

/// <summary>
/// Checks that expected points are returned when line segments don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_ExpectedPointsAreReturnedWhenLinesDoNotIntersect_Test, TTemplateTypes )
{
    // A1-------B1
    //
    // A2-------B2

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_0, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_4, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { (float_z)0.2, (float_z)2.4, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT = T::GetNullVector();
    T S2TOS1_POINT = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the intersection point when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWithIntersectionPointWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { (float_z)1.5, (float_z)1.5, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { (float_z)1.5, (float_z)1.5, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT = T::GetNullVector();
    T S2TOS1_POINT = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide when lines intersect somewhere between A and B, both not included.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWhenLinesIntersectSomewhereBetweenAAndBNotIncluded_Test, TTemplateTypes )
{
    // A1     A2
    //  \    /
    //   \  /
    //    \/
    //    /\
    //   /  \
    //  B2   B1

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_1, SFloat::_1, SFloat::_6, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegment<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    T S1TOS2_POINT = T::GetNullVector();
    T S2TOS1_POINT = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT, S2TOS1_POINT);

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT == S2TOS1_POINT);
}

/// <summary>
/// Checks that both returned points coincide with the end point A of the segment whose method is being called when lines coincide totally.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsCoincideWithEndPointAWhenLinesCoincideTotally_Test, TTemplateTypes )
{
    // A1A2------B1B2  (I
    // A1B2------B1A2  (II

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegmentWhiteBox<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    const LineSegmentWhiteBox<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetNullVector();
    T S2TOS1_POINT1 = T::GetNullVector();
    T S1TOS2_POINT2 = T::GetNullVector();
    T S2TOS1_POINT2 = T::GetNullVector();
    T S1TOS2_POINT3 = T::GetNullVector();
    T S2TOS1_POINT3 = T::GetNullVector();
    T S1TOS2_POINT4 = T::GetNullVector();
    T S2TOS1_POINT4 = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the intersection point when an end point of one line is contained in the other line (not including A, and B points in this case).
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_ObtainedPointsCoincideWithIntersectionPointWhenAnEndPointIsContainedInTheOtherLine_Test, TTemplateTypes )
{
    //        B2              A2              B2              A2
    //       /               /               /               /
    // A1---A2---B1    A1---B2---B1    B1---A2---A1    B1---B2---A1
    //
    //       I              II             III              IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegmentWhiteBox<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegmentWhiteBox<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_z VECTOR_COMPONENTS_EXPECTED[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT = T(VECTOR_COMPONENTS_EXPECTED);
    T S1TOS2_POINT1 = T::GetNullVector();
    T S2TOS1_POINT1 = T::GetNullVector();
    T S1TOS2_POINT2 = T::GetNullVector();
    T S2TOS1_POINT2 = T::GetNullVector();
    T S1TOS2_POINT3 = T::GetNullVector();
    T S2TOS1_POINT3 = T::GetNullVector();
    T S1TOS2_POINT4 = T::GetNullVector();
    T S2TOS1_POINT4 = T::GetNullVector();
    T S1TOS2_POINT5 = T::GetNullVector();
    T S2TOS1_POINT5 = T::GetNullVector();
    T S1TOS2_POINT6 = T::GetNullVector();
    T S2TOS1_POINT6 = T::GetNullVector();
    T S1TOS2_POINT7 = T::GetNullVector();
    T S2TOS1_POINT7 = T::GetNullVector();
    T S1TOS2_POINT8 = T::GetNullVector();
    T S2TOS1_POINT8 = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT);
}

/// <summary>
/// Checks that obtained points coincide with the shared end point when the 2 lines share only one of their end points.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsCoincideWithSharedEndPointWhenLinesShareOneEndPointOnly_Test, TTemplateTypes )
{
    //      B2           A2           B2           A2        B3           A3           B3           A3
    //     /            /            /            /            \            \            \            \
    // A1A2---B1    A1B2---B1    B1A2---A1    B1B2---A1    A1---A3B1    A1---B3B1    B1---A3A1    B1---B3A1    A1---B1A4---B4    B1---A1A4---B4    A1---B1B4---A4    B1---A1B4---A4
    //
    //     I           II           III           IV           V           VI           VII         VIII            IX                  X                XI                XII

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegmentWhiteBox<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegmentWhiteBox<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_1, SFloat::_3, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegmentWhiteBox<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegmentWhiteBox<T> LINE_SEGMENT6 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_z VECTOR_COMPONENTS_A4[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B4[] = { SFloat::_6, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A4(VECTOR_COMPONENTS_A4);
    const T VALUE_FOR_B4(VECTOR_COMPONENTS_B4);

    const LineSegmentWhiteBox<T> LINE_SEGMENT7 = LineSegment<T>(VALUE_FOR_A4, VALUE_FOR_B4);
    const LineSegmentWhiteBox<T> LINE_SEGMENT8 = LineSegment<T>(VALUE_FOR_B4, VALUE_FOR_A4);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetNullVector();    T S2TOS1_POINT1 = T::GetNullVector();
    T S1TOS2_POINT2 = T::GetNullVector();    T S2TOS1_POINT2 = T::GetNullVector();
    T S1TOS2_POINT3 = T::GetNullVector();    T S2TOS1_POINT3 = T::GetNullVector();
    T S1TOS2_POINT4 = T::GetNullVector();    T S2TOS1_POINT4 = T::GetNullVector();
    T S1TOS2_POINT5 = T::GetNullVector();    T S2TOS1_POINT5 = T::GetNullVector();
    T S1TOS2_POINT6 = T::GetNullVector();    T S2TOS1_POINT6 = T::GetNullVector();
    T S1TOS2_POINT7 = T::GetNullVector();    T S2TOS1_POINT7 = T::GetNullVector();
    T S1TOS2_POINT8 = T::GetNullVector();    T S2TOS1_POINT8 = T::GetNullVector();
    T S1TOS2_POINT9 = T::GetNullVector();    T S2TOS1_POINT9 = T::GetNullVector();
    T S1TOS2_POINT10 = T::GetNullVector();    T S2TOS1_POINT10 = T::GetNullVector();
    T S1TOS2_POINT11 = T::GetNullVector();    T S2TOS1_POINT11 = T::GetNullVector();
    T S1TOS2_POINT12 = T::GetNullVector();    T S2TOS1_POINT12 = T::GetNullVector();
    T S1TOS2_POINT13 = T::GetNullVector();    T S2TOS1_POINT13 = T::GetNullVector();
    T S1TOS2_POINT14 = T::GetNullVector();    T S2TOS1_POINT14 = T::GetNullVector();
    T S1TOS2_POINT15 = T::GetNullVector();    T S2TOS1_POINT15 = T::GetNullVector();
    T S1TOS2_POINT16 = T::GetNullVector();    T S2TOS1_POINT16 = T::GetNullVector();
    T S1TOS2_POINT17 = T::GetNullVector();    T S2TOS1_POINT17 = T::GetNullVector();
    T S1TOS2_POINT18 = T::GetNullVector();    T S2TOS1_POINT18 = T::GetNullVector();
    T S1TOS2_POINT19 = T::GetNullVector();    T S2TOS1_POINT19 = T::GetNullVector();
    T S1TOS2_POINT20 = T::GetNullVector();    T S2TOS1_POINT20 = T::GetNullVector();
    T S1TOS2_POINT21 = T::GetNullVector();    T S2TOS1_POINT21 = T::GetNullVector();
    T S1TOS2_POINT22 = T::GetNullVector();    T S2TOS1_POINT22 = T::GetNullVector();
    T S1TOS2_POINT23 = T::GetNullVector();    T S2TOS1_POINT23 = T::GetNullVector();
    T S1TOS2_POINT24 = T::GetNullVector();    T S2TOS1_POINT24 = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT9, S2TOS1_POINT9); // V
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT10, S2TOS1_POINT10); // V
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT6, S1TOS2_POINT11, S2TOS1_POINT11); // VI
    LINE_SEGMENT6.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT12, S2TOS1_POINT12); // VI
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT13, S2TOS1_POINT13); // VII
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT14, S2TOS1_POINT14); // VII
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT6, S1TOS2_POINT15, S2TOS1_POINT15); // VIII
    LINE_SEGMENT6.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT16, S2TOS1_POINT16); // VIII
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT7, S1TOS2_POINT17, S2TOS1_POINT17); // IX
    LINE_SEGMENT7.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT18, S2TOS1_POINT18); // IX
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT7, S1TOS2_POINT19, S2TOS1_POINT19); // X
    LINE_SEGMENT7.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT20, S2TOS1_POINT20); // X
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT8, S1TOS2_POINT21, S2TOS1_POINT21); // XI
    LINE_SEGMENT8.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT22, S2TOS1_POINT22); // XI
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT8, S1TOS2_POINT23, S2TOS1_POINT23); // XII
    LINE_SEGMENT8.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT24, S2TOS1_POINT24); // XII

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT11 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT12 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT13 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT14 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT15 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT16 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT17 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT18 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT19 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT20 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT21 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT22 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT23 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT24 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT24 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the closest ones to A (in the instance which method is being executed) that is contained in the
/// other line when lines coincide partially, this means, they share more than one point but not all.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsAreTheClosestToAInsideTheOtherLineWhenLinesCoincidePartially_Test, TTemplateTypes )
{
    //
    // A1---A2---B1---B2    A1---B2---B1---A2    B1---A2---A1---B2    B1---B2---A1---A2
    //
    //         I                   II                   III                  IV

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegmentWhiteBox<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    const LineSegmentWhiteBox<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_B2, VALUE_FOR_A2);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetNullVector();    T S2TOS1_POINT1 = T::GetNullVector();
    T S1TOS2_POINT2 = T::GetNullVector();    T S2TOS1_POINT2 = T::GetNullVector();
    T S1TOS2_POINT3 = T::GetNullVector();    T S2TOS1_POINT3 = T::GetNullVector();
    T S1TOS2_POINT4 = T::GetNullVector();    T S2TOS1_POINT4 = T::GetNullVector();
    T S1TOS2_POINT5 = T::GetNullVector();    T S2TOS1_POINT5 = T::GetNullVector();
    T S1TOS2_POINT6 = T::GetNullVector();    T S2TOS1_POINT6 = T::GetNullVector();
    T S1TOS2_POINT7 = T::GetNullVector();    T S2TOS1_POINT7 = T::GetNullVector();
    T S1TOS2_POINT8 = T::GetNullVector();    T S2TOS1_POINT8 = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1); // I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2); // I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3); // II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4); // II
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT5, S2TOS1_POINT5); // III
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT6, S2TOS1_POINT6); // III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7); // IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8); // IV

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT2);
}

/// <summary>
/// Checks that obtained points coincide with the closest ones to A (in the instance which method is being executed) that is contained in the
/// other line when one line is totally contained in the other.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetClosestPoints_BothPointsAreTheClosestToAInsideTheOtherLineWhenOneSegmentIsContainedInTheOther_Test, TTemplateTypes )
{
    //
    // A1---A2---B2---B1    A1---A3----B1B3    A1---B3---B1A3    B1---A3---A1B3    B1---B3---A1A3
    //
    //         I                  II                 III               IV                V

    // [Preparation]
    float_z VECTOR_COMPONENTS_A1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B1[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A1(VECTOR_COMPONENTS_A1);
    const T VALUE_FOR_B1(VECTOR_COMPONENTS_B1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT1 = LineSegment<T>(VALUE_FOR_A1, VALUE_FOR_B1);

    float_z VECTOR_COMPONENTS_A2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A2(VECTOR_COMPONENTS_A2);
    const T VALUE_FOR_B2(VECTOR_COMPONENTS_B2);
    const LineSegmentWhiteBox<T> LINE_SEGMENT2 = LineSegment<T>(VALUE_FOR_A2, VALUE_FOR_B2);

    float_z VECTOR_COMPONENTS_A3[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_B3[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T VALUE_FOR_A3(VECTOR_COMPONENTS_A3);
    const T VALUE_FOR_B3(VECTOR_COMPONENTS_B3);

    const LineSegmentWhiteBox<T> LINE_SEGMENT3 = LineSegment<T>(VALUE_FOR_B1, VALUE_FOR_A1);
    const LineSegmentWhiteBox<T> LINE_SEGMENT4 = LineSegment<T>(VALUE_FOR_A3, VALUE_FOR_B3);
    const LineSegmentWhiteBox<T> LINE_SEGMENT5 = LineSegment<T>(VALUE_FOR_B3, VALUE_FOR_A3);

    float_z VECTOR_COMPONENTS_EXPECTED1[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_EXPECTED2[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_1 };
    const T EXPECTED_POINT1 = T(VECTOR_COMPONENTS_EXPECTED1);
    const T EXPECTED_POINT2 = T(VECTOR_COMPONENTS_EXPECTED2);
    T S1TOS2_POINT1 = T::GetNullVector();    T S2TOS1_POINT1 = T::GetNullVector();
    T S1TOS2_POINT2 = T::GetNullVector();    T S2TOS1_POINT2 = T::GetNullVector();
    T S1TOS2_POINT3 = T::GetNullVector();    T S2TOS1_POINT3 = T::GetNullVector();
    T S1TOS2_POINT4 = T::GetNullVector();    T S2TOS1_POINT4 = T::GetNullVector();
    T S1TOS2_POINT5 = T::GetNullVector();    T S2TOS1_POINT5 = T::GetNullVector();
    T S1TOS2_POINT6 = T::GetNullVector();    T S2TOS1_POINT6 = T::GetNullVector();
    T S1TOS2_POINT7 = T::GetNullVector();    T S2TOS1_POINT7 = T::GetNullVector();
    T S1TOS2_POINT8 = T::GetNullVector();    T S2TOS1_POINT8 = T::GetNullVector();
    T S1TOS2_POINT9 = T::GetNullVector();    T S2TOS1_POINT9 = T::GetNullVector();
    T S1TOS2_POINT10 = T::GetNullVector();   T S2TOS1_POINT10 = T::GetNullVector();

	// [Execution]
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT2, S1TOS2_POINT1, S2TOS1_POINT1);// I
    LINE_SEGMENT2.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT2, S2TOS1_POINT2);// I
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT3, S2TOS1_POINT3);// II
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT4, S2TOS1_POINT4);// II
    LINE_SEGMENT1.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT5, S2TOS1_POINT5);// III
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT1, S1TOS2_POINT6, S2TOS1_POINT6);// III
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT4, S1TOS2_POINT7, S2TOS1_POINT7);// IV
    LINE_SEGMENT4.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT8, S2TOS1_POINT8);// IV
    LINE_SEGMENT3.GetClosestPoints(LINE_SEGMENT5, S1TOS2_POINT9, S2TOS1_POINT9);// V
    LINE_SEGMENT5.GetClosestPoints(LINE_SEGMENT3, S1TOS2_POINT10, S2TOS1_POINT10);// V

    // [Verification]
    BOOST_CHECK(S1TOS2_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT1 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT2 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT3 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT4 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT5 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT6 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT6 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT7 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S2TOS1_POINT8 == EXPECTED_POINT1);
    BOOST_CHECK(S1TOS2_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT9 == EXPECTED_POINT2);
    BOOST_CHECK(S1TOS2_POINT10 == EXPECTED_POINT2);
    BOOST_CHECK(S2TOS1_POINT10 == EXPECTED_POINT2);
}

// End - Test Suite: LineSegment
ZTEST_SUITE_END()
