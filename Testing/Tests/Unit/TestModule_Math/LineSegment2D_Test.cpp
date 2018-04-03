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

#include "ZMath/LineSegment2D.h"

#include "ZMath/TransformationMatrix3x3.h"
#include "ZMath/BaseQuadrilateral.h"
#include "ZMath/BaseTriangle.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( LineSegment2D_TestSuite )


/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetNullVector();

	// [Execution]
    LineSegment2D lineSegmentUT;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if copy constructor sets segment's points properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B(SFloat::_4, SFloat::_5);

    const LineSegment2D EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if points are copied cortectly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B(SFloat::_4, SFloat::_5);

    const BaseLineSegment<Vector2> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B(SFloat::_4, SFloat::_5);

	// [Execution]
    LineSegment2D lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a unit-length line which point A is placed at origin and point B is contained in the positive X axis.
/// </summary>
ZTEST_CASE ( GetUnitLine_AUnitLengthSegmentPlacedAtOriginAndContainedInPositiveXAxisIsReturned_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetUnitVectorX();

	// [Execution]
    LineSegment2D lineSegmentUT = LineSegment2D::GetUnitLine();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns a zero-length line which points A and B are placed at origin.
/// </summary>
ZTEST_CASE ( GetLineZero_AZeroLengthSegmentPlacedAtOriginIsReturned_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetNullVector();

	// [Execution]
    LineSegment2D lineSegmentUT = LineSegment2D::GetLineZero();

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line is correctly assigned to another line.
/// </summary>
ZTEST_CASE ( OperatorAssignation_LineIsAssignedProperlyToAnother_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A(SFloat::_1, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B(SFloat::_4, SFloat::_5);

    const BaseLineSegment<Vector2> OTHER_LINE = BaseLineSegment<Vector2>(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D lineSegmentUT;
    lineSegmentUT = OTHER_LINE;

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that it returns True when the line intersects with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultB = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultC = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with the triangle at two points.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(-SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) + Vector2(SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) + Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(SFloat::_0, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(SFloat::_0, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A) + Vector2(-SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAC_AB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBA_BC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCB_CA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAC_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCB_CA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B1 = Vector2(-SFloat::_2, SFloat::_3);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B2 = Vector2(SFloat::_3, SFloat::_3);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B3 = Vector2(SFloat::_2, SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAC1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultAC2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultAB1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultAB2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultBC1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultBC2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the triangle don't intersect.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsFalseWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsFalseWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(TRIANGLE); // I

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two vertices of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LA
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const Vector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const Vector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const Vector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultBC = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultCA = LINE_SEGMENT3.Intersection(TRIANGLE); // III

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultA2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultB1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultB2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultC1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultC2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Intersection1_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

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
ZTEST_CASE ( Intersection1_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

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
/// Checks that the expected result is returned when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Intersection1_CorrectResultIsReturnedWhenBothEndpointsCoincide_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_2, SFloat::_0),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_3, SFloat::_0);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);

    const bool EXPECTED_RESULT_INSIDE = true;
    const bool EXPECTED_RESULT_OUTSIDE = false;

	// [Execution]
    bool bResultInside = LINE_SEGMENT_INSIDE.Intersection(TRIANGLE);
    bool bResultOutside = LINE_SEGMENT_OUTSIDE.Intersection(TRIANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( Intersection1_ReturnsTrueWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A) + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB1 = LINE_SEGMENT1.Intersection(TRIANGLE); // I
    bool bResultAB2 = LINE_SEGMENT2.Intersection(TRIANGLE); // II
    bool bResultBC1 = LINE_SEGMENT3.Intersection(TRIANGLE); // III
    bool bResultBC2 = LINE_SEGMENT4.Intersection(TRIANGLE); // IV
    bool bResultCA1 = LINE_SEGMENT5.Intersection(TRIANGLE); // V
    bool bResultCA2 = LINE_SEGMENT6.Intersection(TRIANGLE); // VI

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCA2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B1 = QUAD.A + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B2 = QUAD.B + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - Vector2(-SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = QUAD.C + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B4 = QUAD.D + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultB = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultC = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultD = LINE_SEGMENT4.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A.Lerp(SFloat::_0_5, QUAD.D) + Vector2(-SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B1 = QUAD.A.Lerp(SFloat::_0_5, QUAD.B) + Vector2(SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B.Lerp(SFloat::_0_5, QUAD.A) + Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B2 = QUAD.B.Lerp(SFloat::_0_5, QUAD.C) + Vector2(SFloat::_0, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C.Lerp(SFloat::_0_5, QUAD.B) + Vector2(SFloat::_0, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = QUAD.C.Lerp(SFloat::_0_5, QUAD.D) + Vector2(-SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D.Lerp(SFloat::_0_5, QUAD.C) + Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B4 = QUAD.D.Lerp(SFloat::_0_5, QUAD.A) + Vector2(-SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAD_AB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBA_BC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCB_CD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA_AB = LINE_SEGMENT4.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAD_AB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBA_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCB_CD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA_AB, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line is contained in the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B1 = Vector2(-SFloat::_2, SFloat::_3);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B2 = Vector2(SFloat::_3, SFloat::_3);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B3 = Vector2(SFloat::_4, SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B4 = Vector2(SFloat::_2, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAD1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAD2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultAB1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultAB2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultBC1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultBC2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultCD1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultCD2 = LINE_SEGMENT8.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the quadrilateral don't intersect.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsFalseWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_4, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsFalseWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LINE_SEGMENT.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsTwoContiguousVertices_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA = LINE_SEGMENT4.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_4, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const Vector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const Vector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const Vector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const Vector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultBC = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultCD = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultDA = LINE_SEGMENT4.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenAnEndpointCoincidesWithVertex_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.D;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultA1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultA2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultB1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultB2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultC1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultC2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultD1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultD2 = LINE_SEGMENT8.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultA2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the line intersects with two non-contiguous edges of the qudrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A.Lerp(SFloat::_0_5, QUAD.D) + Vector2(-SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B1 = QUAD.B.Lerp(SFloat::_0_5, QUAD.C) + Vector2(SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.A.Lerp(SFloat::_0_5, QUAD.B) + Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B2 = QUAD.C.Lerp(SFloat::_0_5, QUAD.D) + Vector2(SFloat::_0, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAD_BC = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAB_CD = LINE_SEGMENT2.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAD_BC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB_CD, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Intersection2_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_1, SFloat::_1),
                                                       Vector2(SFloat::_3, SFloat::_1));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(QUAD);
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
ZTEST_CASE ( Intersection2_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        LINE_SEGMENT.Intersection(QUAD);
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
/// Checks that the expected result is returned when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( Intersection2_CorrectResultIsReturnedWhenBothEndpointsCoincide_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_1),
                                                       Vector2(SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);

    const bool EXPECTED_RESULT_INSIDE = true;
    const bool EXPECTED_RESULT_OUTSIDE = false;

	// [Execution]
    bool bResultInside = LINE_SEGMENT_INSIDE.Intersection(QUAD);
    bool bResultOutside = LINE_SEGMENT_OUTSIDE.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns True when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection2_ReturnsTrueWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.A.Lerp(SFloat::_0_5, QUAD.B) + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.B.Lerp(SFloat::_0_5, QUAD.C) + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.C.Lerp(SFloat::_0_5, QUAD.D) + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.D.Lerp(SFloat::_0_5, QUAD.A) + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultAB1 = LINE_SEGMENT1.Intersection(QUAD);
    bool bResultAB2 = LINE_SEGMENT2.Intersection(QUAD);
    bool bResultBC1 = LINE_SEGMENT3.Intersection(QUAD);
    bool bResultBC2 = LINE_SEGMENT4.Intersection(QUAD);
    bool bResultCD1 = LINE_SEGMENT5.Intersection(QUAD);
    bool bResultCD2 = LINE_SEGMENT6.Intersection(QUAD);
    bool bResultDA1 = LINE_SEGMENT7.Intersection(QUAD);
    bool bResultDA2 = LINE_SEGMENT8.Intersection(QUAD);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultAB2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a line segment is correctly rotated.
/// </summary>
ZTEST_CASE ( Rotate_IsCorrectlyRotatedWhenUsingCommonAngle_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Rotate(ANGLE);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated when angle is zero.
/// </summary>
ZTEST_CASE ( Rotate_IsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const float_z ANGLE = SFloat::_0;

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Rotate(ANGLE);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly translated.
/// </summary>
ZTEST_CASE ( Translate1_IsCorrectlyTranslatedWhenUsingCommonTranslationVector_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate1_IsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    const LineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly translated.
/// </summary>
ZTEST_CASE ( Translate2_IsCorrectlyTranslatedWhenUsingCommonTranslationValues_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    const LineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate2_IsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    const LineSegment2D returnedLine = LINE.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_TriangleIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled if scalation is one.
/// </summary>
ZTEST_CASE ( Scale1_IsNotScaledIfScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_IsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled if scale equals one.
/// </summary>
ZTEST_CASE ( Scale2_IsNotScaledIfScalationIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly transformed.
/// </summary>
ZTEST_CASE ( Transform_IsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 Scale = Vector2(SFloat::_2, SFloat::_0_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, Scale);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);

    const LineSegment2D LINE = LineSegment2D(INIT_POS_A, INIT_POS_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Transform(TRANSFORMATION_MATRIX);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform_DoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that all the endpoints of the line segment are moved to the coordinate origin.
/// </summary>
ZTEST_CASE ( Transform_EndpointsAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2::GetNullVector();
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2::GetNullVector();

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly rotated with pivot point.
/// </summary>
ZTEST_CASE ( RotateWithPivot_IsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 PIVOT_POINT = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, -SFloat::_1);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.RotateWithPivot(ANGLE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not rotated with a pivot when angle is zero.
/// </summary>
ZTEST_CASE ( RotateWithPivot_IsNotRotatedWithPivotWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_0, SFloat::_0);
    const float_z ANGLE = SFloat::_0;

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.RotateWithPivot(ANGLE, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly scaled with a pivot.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_IsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_IsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_IsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_7);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const LineSegment2D LINE = LineSegment2D(POINT_A, POINT_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is not scaled with a pivot if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_IsNotScaledWithPivotIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_2, SFloat::_3);

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that a line segment is correctly transformed with a pivot.
/// </summary>
ZTEST_CASE ( TransformWithPivot_IsCorrectlyTransformedWithPivot_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 Scale = Vector2(SFloat::_2, SFloat::_0_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX =
            TransformationMatrix3x3(TRANSLATION, ROTATION, Scale);

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_3, SFloat::_5);

    const LineSegment2D LINE = LineSegment2D(INIT_POS_A, INIT_POS_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the line segment doesn't change when it's transformed by an identity matrix with a pivot point.
/// </summary>
ZTEST_CASE ( TransformWithPivot_DoesntChangeWhenTransformedWithPivotByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_6);

    const LineSegment2D LINE = LineSegment2D(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(returnedLine.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks that the endpoints of the line segment are moved to the pivot point when transforming by a zero matrix.
/// </summary>
ZTEST_CASE ( TransformWithPivot_EndpointsAreMovedToPivotPointWhenTransformedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const Vector2 PIVOT_POINT = Vector2(SFloat::_3, SFloat::_6);

    const LineSegment2D LINE = LineSegment2D(VALUE_FOR_A, VALUE_FOR_B);

	// [Execution]
    LineSegment2D returnedLine = LINE.TransformWithPivot(TRANSFORMATION, PIVOT_POINT);

    // [Verification]
    BOOST_CHECK(returnedLine.A == PIVOT_POINT);
    BOOST_CHECK(returnedLine.B == PIVOT_POINT);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINTA = TRIANGLE.A;
    const Vector2 EXPECTED_POINTB = TRIANGLE.B;
    const Vector2 EXPECTED_POINTC = TRIANGLE.C;

	// [Execution]
    Vector2 vPointA;
    Vector2 vPointB;
    Vector2 vPointC;
    EIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointA); // I
    EIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointB); // II
    EIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointC); // III

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(vPointA == EXPECTED_POINTA);
    BOOST_CHECK(vPointB == EXPECTED_POINTB);
    BOOST_CHECK(vPointC == EXPECTED_POINTC);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with the triangle at two points.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 MIDPOINT_CA = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CA;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_BC;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AC = MIDPOINT_CA;
    const Vector2 EXPECTED_POINT_BA = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_CB = MIDPOINT_BC;

	// [Execution]
    Vector2 vPointAC;
    Vector2 vPointBA;
    Vector2 vPointCB;
    EIntersections eResultAC_AB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAC); // I
    EIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBA); // II
    EIntersections eResultCB_CA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCB); // III

    // [Verification]
    BOOST_CHECK(eResultAC_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBA_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCB_CA == EXPECTED_RESULT);
    BOOST_CHECK(vPointAC == EXPECTED_POINT_AC);
    BOOST_CHECK(vPointBA == EXPECTED_POINT_BA);
    BOOST_CHECK(vPointCB == EXPECTED_POINT_CB);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsInfiniteIntersectionsWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 POINT_INSIDE_TRIANGLE = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 ENDPOINT_A1 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B1 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B2 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B3 = POINT_INSIDE_TRIANGLE + (TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_AC1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_AC2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);

	// [Execution]
    Vector2 vPointAC1;
    Vector2 vPointAC2;
    Vector2 vPointAB1;
    Vector2 vPointAB2;
    Vector2 vPointBC1;
    Vector2 vPointBC2;
    EIntersections eResultAC1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAC1); // I
    EIntersections eResultAC2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAC2); // II
    EIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointAB1); // III
    EIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointAB2); // IV
    EIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointBC1); // V
    EIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointBC2); // VI

    // [Verification]
    BOOST_CHECK(eResultAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAC1 == EXPECTED_POINT_AC1);
    BOOST_CHECK(vPointAC2 == EXPECTED_POINT_AC2);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersctions when the line intersects with two vertices of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LB
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LA
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB = TRIANGLE.A;
    const Vector2 EXPECTED_POINT_BC = TRIANGLE.B;
    const Vector2 EXPECTED_POINT_CA = TRIANGLE.C;

	// [Execution]
    Vector2 vPointAB;
    Vector2 vPointBC;
    Vector2 vPointCA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB); // I
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBC); // II
    EIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCA); // III

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCA == EXPECTED_POINT_CA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const Vector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const Vector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const Vector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_POINT_AB = LINE_SEGMENT1.A;
    const Vector2 EXPECTED_POINT_BC = LINE_SEGMENT2.A;
    const Vector2 EXPECTED_POINT_CA = LINE_SEGMENT3.A;

	// [Execution]
    Vector2 vPointAB = Vector2::GetNullVector();
    Vector2 vPointBC = Vector2::GetNullVector();
    Vector2 vPointCA = Vector2::GetNullVector();
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB); // I
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointBC); // II
    EIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointCA); // III

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCA == EXPECTED_POINT_CA);
}

/// <summary>
/// Checks that it returns one intersection point when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_A1 = TRIANGLE.A;
    const Vector2 EXPECTED_POINT_A2 = TRIANGLE.A;
    const Vector2 EXPECTED_POINT_B1 = TRIANGLE.B;
    const Vector2 EXPECTED_POINT_B2 = TRIANGLE.B;
    const Vector2 EXPECTED_POINT_C1 = TRIANGLE.C;
    const Vector2 EXPECTED_POINT_C2 = TRIANGLE.C;

	// [Execution]
    Vector2 vPointA1;
    Vector2 vPointA2;
    Vector2 vPointB1;
    Vector2 vPointB2;
    Vector2 vPointC1;
    Vector2 vPointC2;
    EIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointA1); // I
    EIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointA2); // II
    EIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointB1); // III
    EIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointB2); // IV
    EIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointC1); // V
    EIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointC2); // VI

    // [Verification]
    BOOST_CHECK(eResultA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultA2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointA1 == EXPECTED_POINT_A1);
    BOOST_CHECK(vPointA2 == EXPECTED_POINT_A2);
    BOOST_CHECK(vPointB1 == EXPECTED_POINT_B1);
    BOOST_CHECK(vPointB2 == EXPECTED_POINT_B2);
    BOOST_CHECK(vPointC1 == EXPECTED_POINT_C1);
    BOOST_CHECK(vPointC2 == EXPECTED_POINT_C2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint);
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
ZTEST_CASE ( IntersectionPoint1_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vPoint);
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
/// Checks that it returns the expected intersection points when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ExpectedIntersectionsReturnedWhenBothEndpointsCoincide_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_3, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_1),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const EIntersections EXPECTED_RESULT_INSIDE = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT_INSIDE = Vector2::GetNullVector();

    const Vector2 ENDPOINT_IN_EDGE = Vector2(SFloat::_3, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_IN_EDGE = LineSegment2D(ENDPOINT_IN_EDGE, ENDPOINT_IN_EDGE);
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_IN_EDGE = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);
    const EIntersections EXPECTED_RESULT_OUTSIDE = EIntersections::E_None;
    const Vector2 EXPECTED_POINT_OUTSIDE = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPointInside = Vector2::GetNullVector();
    Vector2 vPointInEdge = Vector2::GetNullVector();
    Vector2 vPointOutside = Vector2::GetNullVector();

    EIntersections eResultInside = LINE_SEGMENT_INSIDE.IntersectionPoint(TRIANGLE, vPointInside);
    EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vPointInEdge);
    EIntersections eResultOutside = LINE_SEGMENT_OUTSIDE.IntersectionPoint(TRIANGLE, vPointOutside);

    // [Verification]
    BOOST_CHECK(eResultInside == EXPECTED_RESULT_INSIDE);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultOutside == EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK( vPointInside == EXPECTED_POINT_INSIDE );
    BOOST_CHECK( vPointInEdge == EXPECTED_POINT_IN_EDGE );
    BOOST_CHECK( vPointOutside == EXPECTED_POINT_OUTSIDE );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A) + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_CA1 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_POINT_CA2 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);

	// [Execution]
    Vector2 vPointAB1;
    Vector2 vPointAB2;
    Vector2 vPointBC1;
    Vector2 vPointBC2;
    Vector2 vPointCA1;
    Vector2 vPointCA2;
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB1); // I
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB2); // II
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointBC1); // III
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointBC2); // IV
    EIntersections eResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointCA1); // V
    EIntersections eResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointCA2); // VI

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCA1 == EXPECTED_POINT_CA1);
    BOOST_CHECK(vPointCA2 == EXPECTED_POINT_CA2);
}

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherIsInsideTheTriangle_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /  /\             / LB\               / \ \
    //          /  LB \           / /   \             /   LB\
    //         C-------B         C-LA----B           C-------B
    //
    //
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB              / \                LB \
    //           /  /\             / LA\               / \ \
    //          /  LA \           / /   \             /   LA\
    //         C-------B         C-LB----B           C-------B
    //
    //
    //             II                IV                  VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 TRIANGLE_CENTER = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B).Lerp(SFloat::_0_5, TRIANGLE.C);

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_POINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_POINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_POINT_CA1 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_POINT_CA2 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);

	// [Execution]
    Vector2 vPointAB1;
    Vector2 vPointAB2;
    Vector2 vPointBC1;
    Vector2 vPointBC2;
    Vector2 vPointCA1;
    Vector2 vPointCA2;
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vPointAB1); // I
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB2); // II
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vPointBC1); // III
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vPointBC2); // IV
    EIntersections eResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vPointCA1); // V
    EIntersections eResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vPointCA2); // VI

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCA1 == EXPECTED_POINT_CA1);
    BOOST_CHECK(vPointCA2 == EXPECTED_POINT_CA2);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
ZTEST_CASE ( IntersectionPoint1_ReturnedPointIsTheClosestOneToEndpointA_Test )
{
    //
    //             A
    //            / \  LA
    //           /   \/
    //          /    /\
    //         C----x--B
    //             /
    //            LB
    //
    //             I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const Vector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// [Execution]
    Vector2 vPointAB;
    LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vPointAB); // I

    // [Verification]
    BOOST_CHECK(vPointAB == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vPointAB != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //
    //       LA----A-----LB          A                   A
    //            / \               / \     LA    LA    / \
    //           /   \             /   \   /       \   /   \
    //          /     \           /     \ /         \ /     \
    //         C-------B         C-------B           C-------B
    //                                  /             \
    //                                LB               LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - Vector2(SFloat::_1, SFloat::_1);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINTA = TRIANGLE.A;
    const Vector2 EXPECTED_FIRSTPOINTB = TRIANGLE.B;
    const Vector2 EXPECTED_FIRSTPOINTC = TRIANGLE.C;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointA;
    Vector2 vFirstPointB;
    Vector2 vFirstPointC;
    Vector2 vSecondPointA;
    Vector2 vSecondPointB;
    Vector2 vSecondPointC;
    EIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointA, vSecondPointA); // I
    EIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointB, vSecondPointB); // II
    EIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointC, vSecondPointC); // III

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA == EXPECTED_FIRSTPOINTA);
    BOOST_CHECK(vFirstPointB == EXPECTED_FIRSTPOINTB);
    BOOST_CHECK(vFirstPointC == EXPECTED_FIRSTPOINTC);
    BOOST_CHECK(vSecondPointA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with the triangle at two points.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineIntersectsWithTriangleTwice_Test )
{
    //
    //             A                 A                A
    //            / \               / \  LA       LA / \
    //       LA--x---x--LB         /   \/          \/   \
    //          /     \           /    /\          /\    \
    //         C-------B         C----x--B        C--x----B
    //                               /                \
    //                             LB                  LB
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 MIDPOINT_CA = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CA;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CA + MIDPOINT_CA - MIDPOINT_BC;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AC_AB = MIDPOINT_CA;
    const Vector2 EXPECTED_FIRSTPOINT_BA_BC = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_CB_CA = MIDPOINT_BC;
    const Vector2 EXPECTED_SECONDPOINT_AC_AB = MIDPOINT_AB;
    const Vector2 EXPECTED_SECONDPOINT_BA_BC = MIDPOINT_BC;
    const Vector2 EXPECTED_SECONDPOINT_CB_CA = MIDPOINT_CA;

	// [Execution]
    Vector2 vFirstPointAC_AB;
    Vector2 vFirstPointBA_BC;
    Vector2 vFirstPointCB_CA;
    Vector2 vSecondPointAC_AB;
    Vector2 vSecondPointBA_BC;
    Vector2 vSecondPointCB_CA;
    EIntersections eResultAC_AB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAC_AB, vSecondPointAC_AB); // I
    EIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBA_BC, vSecondPointBA_BC); // II
    EIntersections eResultCB_CA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCB_CA, vSecondPointCB_CA); // III

    // [Verification]
    BOOST_CHECK(eResultAC_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBA_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCB_CA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAC_AB == EXPECTED_FIRSTPOINT_AC_AB);
    BOOST_CHECK(vFirstPointBA_BC == EXPECTED_FIRSTPOINT_BA_BC);
    BOOST_CHECK(vFirstPointCB_CA == EXPECTED_FIRSTPOINT_CB_CA);
    BOOST_CHECK(vSecondPointAC_AB == EXPECTED_SECONDPOINT_AC_AB);
    BOOST_CHECK(vSecondPointBA_BC == EXPECTED_SECONDPOINT_BA_BC);
    BOOST_CHECK(vSecondPointCB_CA == EXPECTED_SECONDPOINT_CB_CA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsInfiniteIntersectionsWhenLineIsContainedInTriangle_Test )
{
    //            A
    //           / \
    //          /   \
    //         /     \
    //        /       \
    //       / LA--LB  \
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segmetn is inside of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheTriangle_Test )
{
    //
    //             A                 A  LA            A
    //            / \               / \/             / \
    //       LA--x-LB\             /  /\            /LB \
    //          /     \           /  LB \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LA
    //
    //             I                III               V
    //
    //             A                 A  LB            A
    //            / \               / \/             / \
    //       LB--x-LA\             /  /\            /LA \
    //          /     \           /  LA \          /  \  \
    //         C-------B         C-------B        C----x--B
    //                                                  \
    //                                                   LB
    //
    //            II                 IV                VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 POINT_INSIDE_TRIANGLE = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 ENDPOINT_A1 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B1 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B2 = POINT_INSIDE_TRIANGLE + (TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = POINT_INSIDE_TRIANGLE;
    const Vector2 ENDPOINT_B3 = POINT_INSIDE_TRIANGLE + (TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) - POINT_INSIDE_TRIANGLE) * SFloat::_2;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_AC1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_AC2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAC1;
    Vector2 vFirstPointAC2;
    Vector2 vFirstPointAB1;
    Vector2 vFirstPointAB2;
    Vector2 vFirstPointBC1;
    Vector2 vFirstPointBC2;
    Vector2 vSecondPointAC1;
    Vector2 vSecondPointAC2;
    Vector2 vSecondPointAB1;
    Vector2 vSecondPointAB2;
    Vector2 vSecondPointBC1;
    Vector2 vSecondPointBC2;
    EIntersections eResultAC1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAC1, vSecondPointAC1); // I
    EIntersections eResultAC2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAC2, vSecondPointAC2); // II
    EIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // III
    EIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // IV
    EIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // V
    EIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // VI

    // [Verification]
    BOOST_CHECK(eResultAC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAC1 == EXPECTED_FIRSTPOINT_AC1);
    BOOST_CHECK(vFirstPointAC2 == EXPECTED_FIRSTPOINT_AC2);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vSecondPointAC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersect_Test )
{
    //            A
    //           / \
    //          /   \    LA
    //         /     \    \
    //        /       \    \
    //       /         \    LB
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersections when the line and the triangle don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsNoIntersectionsWhenLineAndTriangleDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    //            A         LA
    //           / \       /
    //          /   \    LB
    //         /     \  .
    //        /       \.
    //       /        .\
    //      C-----------B
    //
    //            I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersctions when the line intersects with two vertices of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineIntersectsTwoVertices_Test )
{
    //           LA                                        LB
    //            \                                       /
    //             A                 A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B     LB--C-------B--LA       C-------B
    //                  \                           /
    //                   LB                       LA
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB = TRIANGLE.A;
    const Vector2 EXPECTED_FIRSTPOINT_BC = TRIANGLE.B;
    const Vector2 EXPECTED_FIRSTPOINT_CA = TRIANGLE.C;
    const Vector2 EXPECTED_SECONDPOINT_AB = TRIANGLE.B;
    const Vector2 EXPECTED_SECONDPOINT_BC = TRIANGLE.C;
    const Vector2 EXPECTED_SECONDPOINT_CA = TRIANGLE.A;

	// [Execution]
    Vector2 vFirstPointAB;
    Vector2 vFirstPointBC;
    Vector2 vFirstPointCA;
    Vector2 vSecondPointAB;
    Vector2 vSecondPointBC;
    Vector2 vSecondPointCA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB, vSecondPointAB); // I
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBC, vSecondPointBC); // II
    EIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCA, vSecondPointCA); // III

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCA == EXPECTED_SECONDPOINT_CA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /   \             /   \               /   \
    //          /     LB          /     \            LB     \
    //         C-------B         C-LA-LB-B           C-------B
    //
    //             I                II                   III

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.B).Normalize();
    const Vector2 ENDPOINT_B1 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B - (TRIANGLE.B - TRIANGLE.C).Normalize();
    const Vector2 ENDPOINT_B2 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C - (TRIANGLE.C - TRIANGLE.A).Normalize();
    const Vector2 ENDPOINT_B3 = TRIANGLE.A - (TRIANGLE.A - TRIANGLE.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;

    const Vector2 EXPECTED_FIRSTPOINT_AB = ENDPOINT_A1;
    const Vector2 EXPECTED_SECONDPOINT_AB = ENDPOINT_B1;
    const Vector2 EXPECTED_FIRSTPOINT_BC = ENDPOINT_A2;
    const Vector2 EXPECTED_SECONDPOINT_BC = ENDPOINT_B2;
    const Vector2 EXPECTED_FIRSTPOINT_CA = ENDPOINT_A3;
    const Vector2 EXPECTED_SECONDPOINT_CA = ENDPOINT_B3;

	// [Execution]
    Vector2 vFirstPointAB = Vector2::GetNullVector();
    Vector2 vFirstPointBC = Vector2::GetNullVector();
    Vector2 vFirstPointCA = Vector2::GetNullVector();
    Vector2 vSecondPointAB = Vector2::GetNullVector();
    Vector2 vSecondPointBC = Vector2::GetNullVector();
    Vector2 vSecondPointCA = Vector2::GetNullVector();
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB, vSecondPointAB); // I
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointBC, vSecondPointBC); // II
    EIntersections eResultCA = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointCA, vSecondPointCA); // III

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCA == EXPECTED_FIRSTPOINT_CA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCA == EXPECTED_SECONDPOINT_CA);
}

/// <summary>
/// Checks that it returns one intersection point when the an end point of the line coincides with a vertex of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    //           LA
    //            \
    //             ALB               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLB--LA      CLB-----B
    //                                              /
    //                                            LA
    //
    //             I                III                  V
    //
    //           LB
    //            \
    //             ALA               A                   A
    //            / \               / \                 / \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C------BLA--LB      CLA-----B
    //                                              /
    //                                            LB
    //
    //             II               IV                   VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A + (TRIANGLE.A - TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B + (TRIANGLE.B - TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C + (TRIANGLE.C - TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_A1 = TRIANGLE.A;
    const Vector2 EXPECTED_FIRSTPOINT_A2 = TRIANGLE.A;
    const Vector2 EXPECTED_FIRSTPOINT_B1 = TRIANGLE.B;
    const Vector2 EXPECTED_FIRSTPOINT_B2 = TRIANGLE.B;
    const Vector2 EXPECTED_FIRSTPOINT_C1 = TRIANGLE.C;
    const Vector2 EXPECTED_FIRSTPOINT_C2 = TRIANGLE.C;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointA1  = Vector2::GetNullVector();
    Vector2 vFirstPointA2  = Vector2::GetNullVector();
    Vector2 vFirstPointB1  = Vector2::GetNullVector();
    Vector2 vFirstPointB2  = Vector2::GetNullVector();
    Vector2 vFirstPointC1  = Vector2::GetNullVector();
    Vector2 vFirstPointC2  = Vector2::GetNullVector();
    Vector2 vSecondPointA1 = Vector2::GetNullVector();
    Vector2 vSecondPointA2 = Vector2::GetNullVector();
    Vector2 vSecondPointB1 = Vector2::GetNullVector();
    Vector2 vSecondPointB2 = Vector2::GetNullVector();
    Vector2 vSecondPointC1 = Vector2::GetNullVector();
    Vector2 vSecondPointC2 = Vector2::GetNullVector();
    EIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointA1, vSecondPointA1); // I
    EIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointA2, vSecondPointA2); // II
    EIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointB1, vSecondPointB1); // III
    EIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointB2, vSecondPointB2); // IV
    EIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointC1, vSecondPointC1); // V
    EIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointC2, vSecondPointC2); // VI

    // [Verification]
    BOOST_CHECK(eResultA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultA2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA1 == EXPECTED_FIRSTPOINT_A1);
    BOOST_CHECK(vFirstPointA2 == EXPECTED_FIRSTPOINT_A2);
    BOOST_CHECK(vFirstPointB1 == EXPECTED_FIRSTPOINT_B1);
    BOOST_CHECK(vFirstPointB2 == EXPECTED_FIRSTPOINT_B2);
    BOOST_CHECK(vFirstPointC1 == EXPECTED_FIRSTPOINT_C1);
    BOOST_CHECK(vFirstPointC2 == EXPECTED_FIRSTPOINT_C2);
    BOOST_CHECK(vSecondPointA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC2 == EXPECTED_SECONDPOINT);
}


/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle and the other endpoint is inside the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherIsInsideTheTriangle_Test )
{
    //             A                 A                   A
    //            / LA              / \                LA \
    //           /  /\             / LB\               / \ \
    //          /  LB \           / /   \             /   LB\
    //         C-------B         C-LA----B           C-------B
    //
    //
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB              / \                LB \
    //           /  /\             / LA\               / \ \
    //          /  LA \           / /   \             /   LA\
    //         C-------B         C-LB----B           C-------B
    //
    //
    //             II                IV                  VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 TRIANGLE_CENTER = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B).Lerp(SFloat::_0_5, TRIANGLE.C);

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE_CENTER;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_CA1 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_FIRSTPOINT_CA2 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAB1;
    Vector2 vFirstPointAB2;
    Vector2 vFirstPointBC1;
    Vector2 vFirstPointBC2;
    Vector2 vFirstPointCA1;
    Vector2 vFirstPointCA2;
    Vector2 vSecondPointAB1 = Vector2::GetNullVector();
    Vector2 vSecondPointAB2 = Vector2::GetNullVector();
    Vector2 vSecondPointBC1 = Vector2::GetNullVector();
    Vector2 vSecondPointBC2 = Vector2::GetNullVector();
    Vector2 vSecondPointCA1 = Vector2::GetNullVector();
    Vector2 vSecondPointCA2 = Vector2::GetNullVector();
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // I
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // II
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // III
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // IV
    EIntersections eResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointCA1, vSecondPointCA1); // V
    EIntersections eResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointCA2, vSecondPointCA2); // VI

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCA1 == EXPECTED_FIRSTPOINT_CA1);
    BOOST_CHECK(vFirstPointCA2 == EXPECTED_FIRSTPOINT_CA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA2 == EXPECTED_SECONDPOINT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vFirstPoint, vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint);
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
ZTEST_CASE ( IntersectionPoint2_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vFirstPoint, vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint);
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
/// Checks that it returns the expected intersection points when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ExpectedIntersectionsReturnedWhenBothEndpointsCoincide_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_3, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_1),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const EIntersections EXPECTED_RESULT_INSIDE = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT_INSIDE = Vector2::GetNullVector();

    const Vector2 ENDPOINT_IN_EDGE = Vector2(SFloat::_3, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_IN_EDGE = LineSegment2D(ENDPOINT_IN_EDGE, ENDPOINT_IN_EDGE);
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_IN_EDGE = Vector2(SFloat::_3, SFloat::_2);

    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);
    const EIntersections EXPECTED_RESULT_OUTSIDE = EIntersections::E_None;
    const Vector2 EXPECTED_POINT_OUTSIDE = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointInside = Vector2::GetNullVector();
    Vector2 vFirstPointInEdge = Vector2::GetNullVector();
    Vector2 vFirstPointOutside = Vector2::GetNullVector();
    Vector2 vSecondPointInside = Vector2::GetNullVector();
    Vector2 vSecondPointInEdge = Vector2::GetNullVector();
    Vector2 vSecondPointOutside = Vector2::GetNullVector();

    EIntersections eResultInside = LINE_SEGMENT_INSIDE.IntersectionPoint(TRIANGLE, vFirstPointInside, vSecondPointInside);
    EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(TRIANGLE, vFirstPointInEdge, vSecondPointInEdge);
    EIntersections eResultOutside = LINE_SEGMENT_OUTSIDE.IntersectionPoint(TRIANGLE, vFirstPointOutside, vSecondPointOutside);

    // [Verification]
    BOOST_CHECK(eResultInside == EXPECTED_RESULT_INSIDE);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultOutside == EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK( vFirstPointInside == EXPECTED_POINT_INSIDE );
    BOOST_CHECK( vFirstPointInEdge == EXPECTED_POINT_IN_EDGE );
    BOOST_CHECK( vFirstPointOutside == EXPECTED_POINT_OUTSIDE );
    BOOST_CHECK( vSecondPointInside == EXPECTED_POINT_INSIDE );
    BOOST_CHECK( vSecondPointInEdge == EXPECTED_POINT_IN_EDGE );
    BOOST_CHECK( vSecondPointOutside == EXPECTED_POINT_OUTSIDE );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one inetrsection when only one point of the line segment belongs to an edge of the triangle.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    //             A                 A                   A
    //            / LA--LB          / \           LB---LA \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LA----B           C-------B
    //                               \
    //                                LB
    //             I                III                  V
    //
    //             A                 A                   A
    //            / LB--LA          / \           LA---LB \
    //           /   \             /   \               /   \
    //          /     \           /     \             /     \
    //         C-------B         C-LB----B           C-------B
    //                               \
    //                                LA
    //             II                IV                  VI

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 ENDPOINT_A1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 ENDPOINT_B1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B) + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 ENDPOINT_B2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C) + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 ENDPOINT_B3 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A) + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;

    const Vector2 EXPECTED_FIRSTPOINT_AB1 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_AB2 = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 EXPECTED_FIRSTPOINT_BC1 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_BC2 = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);
    const Vector2 EXPECTED_FIRSTPOINT_CA1 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_FIRSTPOINT_CA2 = TRIANGLE.C.Lerp(SFloat::_0_5, TRIANGLE.A);
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAB1;
    Vector2 vFirstPointAB2;
    Vector2 vFirstPointBC1;
    Vector2 vFirstPointBC2;
    Vector2 vFirstPointCA1;
    Vector2 vFirstPointCA2;
    Vector2 vSecondPointAB1;
    Vector2 vSecondPointAB2;
    Vector2 vSecondPointBC1;
    Vector2 vSecondPointBC2;
    Vector2 vSecondPointCA1;
    Vector2 vSecondPointCA2;
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(TRIANGLE, vFirstPointAB1, vSecondPointAB1); // I
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPointAB2, vSecondPointAB2); // II
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(TRIANGLE, vFirstPointBC1, vSecondPointBC1); // III
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(TRIANGLE, vFirstPointBC2, vSecondPointBC2); // IV
    EIntersections eResultCA1 = LINE_SEGMENT5.IntersectionPoint(TRIANGLE, vFirstPointCA1, vSecondPointCA1); // V
    EIntersections eResultCA2 = LINE_SEGMENT6.IntersectionPoint(TRIANGLE, vFirstPointCA2, vSecondPointCA2); // VI

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCA2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCA1 == EXPECTED_FIRSTPOINT_CA1);
    BOOST_CHECK(vFirstPointCA2 == EXPECTED_FIRSTPOINT_CA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
ZTEST_CASE ( IntersectionPoint2_ReturnedPointIsTheClosestOneToEndpointA_Test )
{
    //
    //             A
    //            / \  LA
    //           /   \/
    //          /    /\
    //         C----x--B
    //             /
    //            LB
    //
    //             I

    // [Preparation]
    const BaseTriangle<Vector2> TRIANGLE = BaseTriangle<Vector2>(Vector2(SFloat::_1, SFloat::_3),
                                                                     Vector2(SFloat::_3, SFloat::_2),
                                                                     Vector2(-SFloat::_1, SFloat::_0));

    const Vector2 MIDPOINT_AB = TRIANGLE.A.Lerp(SFloat::_0_5, TRIANGLE.B);
    const Vector2 MIDPOINT_BC = TRIANGLE.B.Lerp(SFloat::_0_5, TRIANGLE.C);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const Vector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// [Execution]
    Vector2 vFirstPoint, vSecondPoint;
    LINE_SEGMENT2.IntersectionPoint(TRIANGLE, vFirstPoint, vSecondPoint); // I

    // [Verification]
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B1 = QUAD.A + Vector2(SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B2 = QUAD.B + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - Vector2(-SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = QUAD.C + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B4 = QUAD.D + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT_A = QUAD.A;
    const Vector2 EXPECTED_POINT_B = QUAD.B;
    const Vector2 EXPECTED_POINT_C = QUAD.C;
    const Vector2 EXPECTED_POINT_D = QUAD.D;

	// [Execution]
    Vector2 vPointA;
    Vector2 vPointB;
    Vector2 vPointC;
    Vector2 vPointD;
    EIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointA);
    EIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointB);
    EIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointC);
    EIntersections eResultD = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointD);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(vPointA == EXPECTED_POINT_A);
    BOOST_CHECK(vPointB == EXPECTED_POINT_B);
    BOOST_CHECK(vPointC == EXPECTED_POINT_C);
    BOOST_CHECK(vPointD == EXPECTED_POINT_D);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with two contiguous edges of the qudrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_DA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_BC;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_CD;
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_AD_AB = MIDPOINT_DA;
    const Vector2 EXPECTED_POINT_BA_BC = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_CB_CD = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_DC_DA = MIDPOINT_CD;

	// [Execution]
    Vector2 vPointAD_AB;
    Vector2 vPointBA_BC;
    Vector2 vPointCB_CD;
    Vector2 vPointDA_AB;
    EIntersections eResultAD_AB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD_AB);
    EIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBA_BC);
    EIntersections eResultCB_CD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCB_CD);
    EIntersections eResultDA_AB = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA_AB);

    // [Verification]
    BOOST_CHECK(eResultAD_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBA_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vPointAD_AB == EXPECTED_POINT_AD_AB);
    BOOST_CHECK(vPointBA_BC == EXPECTED_POINT_BA_BC);
    BOOST_CHECK(vPointCB_CD == EXPECTED_POINT_CB_CD);
    BOOST_CHECK(vPointDA_AB == EXPECTED_POINT_DC_DA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsInfiniteIntersectionsWhenLineIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);
    const Vector2 POINT_INSIDE = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 ENDPOINT_A1 = POINT_INSIDE;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = POINT_INSIDE;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = POINT_INSIDE;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = POINT_INSIDE;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT_AD_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BA_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CB_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DC_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_POINT_AD_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BA_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CB_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DC_DA2 = MIDPOINT_DA;

	// [Execution]
    Vector2 vPointAD1;
    Vector2 vPointBA1;
    Vector2 vPointCB1;
    Vector2 vPointDA1;
    Vector2 vPointAD2;
    Vector2 vPointBA2;
    Vector2 vPointCB2;
    Vector2 vPointDA2;
    EIntersections eResultAD1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD1);
    EIntersections eResultAD2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAD2);
    EIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBA1);
    EIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBA2);
    EIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCB1);
    EIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCB2);
    EIntersections eResultCD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EIntersections eResultCD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAD1 == EXPECTED_POINT_AD_AB1);
    BOOST_CHECK(vPointBA1 == EXPECTED_POINT_BA_BC1);
    BOOST_CHECK(vPointCB1 == EXPECTED_POINT_CB_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DC_DA1);
    BOOST_CHECK(vPointAD2 == EXPECTED_POINT_AD_AB2);
    BOOST_CHECK(vPointBA2 == EXPECTED_POINT_BA_BC2);
    BOOST_CHECK(vPointCB2 == EXPECTED_POINT_CB_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DC_DA2);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_4, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_POINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vPoint == EXPECTED_POINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsTwoContiguousVertices_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_AB = QUAD.A;
    const Vector2 EXPECTED_POINT_BC = QUAD.B;
    const Vector2 EXPECTED_POINT_CD = QUAD.C;
    const Vector2 EXPECTED_POINT_DA = QUAD.D;

	// [Execution]
    Vector2 vPointAB;
    Vector2 vPointBC;
    Vector2 vPointCD;
    Vector2 vPointDA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB);
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBC);
    EIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCD);
    EIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCD == EXPECTED_POINT_CD);
    BOOST_CHECK(vPointDA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_4, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const Vector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const Vector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const Vector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const Vector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_AB = LINE_SEGMENT1.A;
    const Vector2 EXPECTED_POINT_BC = LINE_SEGMENT2.A;
    const Vector2 EXPECTED_POINT_CD = LINE_SEGMENT3.A;
    const Vector2 EXPECTED_POINT_DA = LINE_SEGMENT4.A;

	// [Execution]
    Vector2 vPointAB;
    Vector2 vPointBC;
    Vector2 vPointCD;
    Vector2 vPointDA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB);
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointBC);
    EIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointCD);
    EIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointDA);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB == EXPECTED_POINT_AB);
    BOOST_CHECK(vPointBC == EXPECTED_POINT_BC);
    BOOST_CHECK(vPointCD == EXPECTED_POINT_CD);
    BOOST_CHECK(vPointDA == EXPECTED_POINT_DA);
}

/// <summary>
/// Checks that it returns one intersection when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.D;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT_A1 = QUAD.A;
    const Vector2 EXPECTED_POINT_B1 = QUAD.B;
    const Vector2 EXPECTED_POINT_C1 = QUAD.C;
    const Vector2 EXPECTED_POINT_D1 = QUAD.D;
    const Vector2 EXPECTED_POINT_A2 = QUAD.A;
    const Vector2 EXPECTED_POINT_B2 = QUAD.B;
    const Vector2 EXPECTED_POINT_C2 = QUAD.C;
    const Vector2 EXPECTED_POINT_D2 = QUAD.D;

	// [Execution]
    Vector2 vPointA1;
    Vector2 vPointB1;
    Vector2 vPointC1;
    Vector2 vPointD1;
    Vector2 vPointA2;
    Vector2 vPointB2;
    Vector2 vPointC2;
    Vector2 vPointD2;
    EIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointA1);
    EIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointA2);
    EIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointB1);
    EIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointB2);
    EIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointC1);
    EIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointC2);
    EIntersections eResultD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointD1);
    EIntersections eResultD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointD2);

    // [Verification]
    BOOST_CHECK(eResultA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultA2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultD2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointA1 == EXPECTED_POINT_A1);
    BOOST_CHECK(vPointB1 == EXPECTED_POINT_B1);
    BOOST_CHECK(vPointC1 == EXPECTED_POINT_C1);
    BOOST_CHECK(vPointD1 == EXPECTED_POINT_D1);
    BOOST_CHECK(vPointA2 == EXPECTED_POINT_A2);
    BOOST_CHECK(vPointB2 == EXPECTED_POINT_B2);
    BOOST_CHECK(vPointC2 == EXPECTED_POINT_C2);
    BOOST_CHECK(vPointD2 == EXPECTED_POINT_D2);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_BC;
    const Vector2 ENDPOINT_B1 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_DA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CD;
    const Vector2 ENDPOINT_B2 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_AD_BC = MIDPOINT_DA;
    const Vector2 EXPECTED_POINT_AB_CD = MIDPOINT_AB;

	// [Execution]
    Vector2 vPointAD_BC;
    Vector2 vPointAB_CD;
    EIntersections eResultAD_BC = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAD_BC);
    EIntersections eResultAB_CD = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB_CD);

    // [Verification]
    BOOST_CHECK(eResultAD_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB_CD == EXPECTED_RESULT);
    BOOST_CHECK(vPointAD_BC == EXPECTED_POINT_AD_BC);
    BOOST_CHECK(vPointAB_CD == EXPECTED_POINT_AB_CD);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_1, SFloat::_1),
                                                       Vector2(SFloat::_3, SFloat::_1));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);
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
ZTEST_CASE ( IntersectionPoint3_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vPoint);
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
/// Checks that it returns the expected intersection points when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsExpectedIntersectionPointWhenBothEndpointsCoincide_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_1),
                                                       Vector2(SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);
    const EIntersections EXPECTED_RESULT_OUTSIDE = EIntersections::E_None;
    const Vector2 EXPECTED_POINT_OUTSIDE = Vector2::GetNullVector();
    
    const Vector2 ENDPOINT_IN_EDGE = Vector2(SFloat::_2, SFloat::_3);
    const LineSegment2D LINE_SEGMENT_IN_EDGE = LineSegment2D(ENDPOINT_IN_EDGE, ENDPOINT_IN_EDGE);
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_IN_EDGE = Vector2(SFloat::_2, SFloat::_3);

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const EIntersections EXPECTED_RESULT_INSIDE = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT_INSIDE = Vector2::GetNullVector();

	// [Execution]
    Vector2 vPointOutside = Vector2::GetNullVector();
    Vector2 vPointInEdge = Vector2::GetNullVector();
    Vector2 vPointInside = Vector2::GetNullVector();

    EIntersections eResultOutside = LINE_SEGMENT_OUTSIDE.IntersectionPoint(QUAD, vPointOutside);
    EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(QUAD, vPointInEdge);
    EIntersections eResultInside = LINE_SEGMENT_INSIDE.IntersectionPoint(QUAD, vPointInside);

    // [Verification]
    BOOST_CHECK(eResultOutside == EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultInside == EXPECTED_RESULT_INSIDE);
    BOOST_CHECK(vPointOutside == EXPECTED_POINT_OUTSIDE);
    BOOST_CHECK(vPointInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vPointInside == EXPECTED_POINT_INSIDE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_POINT_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DA2 = MIDPOINT_DA;

	// [Execution]
    Vector2 vPointAB1;
    Vector2 vPointBC1;
    Vector2 vPointCD1;
    Vector2 vPointDA1;
    Vector2 vPointAB2;
    Vector2 vPointBC2;
    Vector2 vPointCD2;
    Vector2 vPointDA2;
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB1);
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB2);
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBC1);
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBC2);
    EIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCD1);
    EIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCD2);
    EIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointCD1 == EXPECTED_POINT_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DA1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCD2 == EXPECTED_POINT_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DA2);
}

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral and the other endpoint is inside the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherEndpointIsInsideTheQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 CENTER_POINT = QUAD.A.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_POINT_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_POINT_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_POINT_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_POINT_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_POINT_DA2 = MIDPOINT_DA;

	// [Execution]
    Vector2 vPointAB1;
    Vector2 vPointBC1;
    Vector2 vPointCD1;
    Vector2 vPointDA1;
    Vector2 vPointAB2;
    Vector2 vPointBC2;
    Vector2 vPointCD2;
    Vector2 vPointDA2;
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vPointAB1);
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vPointAB2);
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vPointBC1);
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vPointBC2);
    EIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vPointCD1);
    EIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vPointCD2);
    EIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vPointDA1);
    EIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA2 == EXPECTED_RESULT);
    BOOST_CHECK(vPointAB1 == EXPECTED_POINT_AB1);
    BOOST_CHECK(vPointBC1 == EXPECTED_POINT_BC1);
    BOOST_CHECK(vPointCD1 == EXPECTED_POINT_CD1);
    BOOST_CHECK(vPointDA1 == EXPECTED_POINT_DA1);
    BOOST_CHECK(vPointAB2 == EXPECTED_POINT_AB2);
    BOOST_CHECK(vPointBC2 == EXPECTED_POINT_BC2);
    BOOST_CHECK(vPointCD2 == EXPECTED_POINT_CD2);
    BOOST_CHECK(vPointDA2 == EXPECTED_POINT_DA2);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
ZTEST_CASE ( IntersectionPoint3_ReturnedPointIsTheClosestOneToEndpointA_Test )
{

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const Vector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// [Execution]
    Vector2 vFirstPoint;
    LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPoint); // I

    // [Verification]
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

/// <summary>
/// Checks that it returns one intersection when the line intersects with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenLineIntersectsWithVertex_Test )
{
    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - Vector2(SFloat::_1, SFloat::_0);
    const Vector2 ENDPOINT_B1 = QUAD.A + Vector2(SFloat::_1, SFloat::_0);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B2 = QUAD.B + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - Vector2(-SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B3 = QUAD.C + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 ENDPOINT_B4 = QUAD.D + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT_A = QUAD.A;
    const Vector2 EXPECTED_FIRSTPOINT_B = QUAD.B;
    const Vector2 EXPECTED_FIRSTPOINT_C = QUAD.C;
    const Vector2 EXPECTED_FIRSTPOINT_D = QUAD.D;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointA, vSecondPointA;
    Vector2 vFirstPointB, vSecondPointB;
    Vector2 vFirstPointC, vSecondPointC;
    Vector2 vFirstPointD, vSecondPointD;
    EIntersections eResultA = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointA, vSecondPointA);
    EIntersections eResultB = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointB, vSecondPointB);
    EIntersections eResultC = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointC, vSecondPointC);
    EIntersections eResultD = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointD, vSecondPointD);

    // [Verification]
    BOOST_CHECK(eResultA == EXPECTED_RESULT);
    BOOST_CHECK(eResultB == EXPECTED_RESULT);
    BOOST_CHECK(eResultC == EXPECTED_RESULT);
    BOOST_CHECK(eResultD == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA == EXPECTED_FIRSTPOINT_A);
    BOOST_CHECK(vFirstPointB == EXPECTED_FIRSTPOINT_B);
    BOOST_CHECK(vFirstPointC == EXPECTED_FIRSTPOINT_C);
    BOOST_CHECK(vFirstPointD == EXPECTED_FIRSTPOINT_D);
    BOOST_CHECK(vSecondPointA == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersections when the line intersects with two contiguous edges of the qudrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_DA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_BC;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_CD;
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_FIRSTPOINT_AD_AB = MIDPOINT_DA;
    const Vector2 EXPECTED_FIRSTPOINT_BA_BC = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_CB_CD = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_DC_DA = MIDPOINT_CD;
    const Vector2 EXPECTED_SECONDPOINT_AD_AB = MIDPOINT_AB;
    const Vector2 EXPECTED_SECONDPOINT_BA_BC = MIDPOINT_BC;
    const Vector2 EXPECTED_SECONDPOINT_CB_CD = MIDPOINT_CD;
    const Vector2 EXPECTED_SECONDPOINT_DC_DA = MIDPOINT_DA;

	// [Execution]
    Vector2 vFirstPointAD_AB;
    Vector2 vFirstPointBA_BC;
    Vector2 vFirstPointCB_CD;
    Vector2 vFirstPointDA_AB;
    Vector2 vSecondPointAD_AB;
    Vector2 vSecondPointBA_BC;
    Vector2 vSecondPointCB_CD;
    Vector2 vSecondPointDA_AB;
    EIntersections eResultAD_AB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD_AB, vSecondPointAD_AB);
    EIntersections eResultBA_BC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBA_BC, vSecondPointBA_BC);
    EIntersections eResultCB_CD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCB_CD, vSecondPointCB_CD);
    EIntersections eResultDA_AB = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA_AB, vSecondPointDA_AB);

    // [Verification]
    BOOST_CHECK(eResultAD_AB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBA_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCB_CD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA_AB == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD_AB == EXPECTED_FIRSTPOINT_AD_AB);
    BOOST_CHECK(vFirstPointBA_BC == EXPECTED_FIRSTPOINT_BA_BC);
    BOOST_CHECK(vFirstPointCB_CD == EXPECTED_FIRSTPOINT_CB_CD);
    BOOST_CHECK(vFirstPointDA_AB == EXPECTED_FIRSTPOINT_DC_DA);
    BOOST_CHECK(vSecondPointAD_AB == EXPECTED_SECONDPOINT_AD_AB);
    BOOST_CHECK(vSecondPointBA_BC == EXPECTED_SECONDPOINT_BA_BC);
    BOOST_CHECK(vSecondPointCB_CD == EXPECTED_SECONDPOINT_CB_CD);
    BOOST_CHECK(vSecondPointDA_AB == EXPECTED_SECONDPOINT_DC_DA);
}

/// <summary>
/// Checks that it returns infinite intersection points when the line is contained in the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsInfiniteIntersectionsWhenLineIsContainedInQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one endpoint of the segment is inside of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndpointIsInsideTheQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);
    const Vector2 POINT_INSIDE = Vector2(SFloat::_1, SFloat::_2);

    const Vector2 ENDPOINT_A1 = POINT_INSIDE;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + MIDPOINT_AB - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = POINT_INSIDE;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = POINT_INSIDE;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + MIDPOINT_CD - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = POINT_INSIDE;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + MIDPOINT_DA - POINT_INSIDE;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT_AD_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BA_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CB_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DC_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_FIRSTPOINT_AD_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BA_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CB_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DC_DA2 = MIDPOINT_DA;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAD1, vSecondPointAD1;
    Vector2 vFirstPointBA1, vSecondPointBA1;
    Vector2 vFirstPointCB1, vSecondPointCB1;
    Vector2 vFirstPointDA1, vSecondPointDA1;
    Vector2 vFirstPointAD2, vSecondPointAD2;
    Vector2 vFirstPointBA2, vSecondPointBA2;
    Vector2 vFirstPointCB2, vSecondPointCB2;
    Vector2 vFirstPointDA2, vSecondPointDA2;
    EIntersections eResultAD1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD1, vSecondPointAD1);
    EIntersections eResultAD2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAD2, vSecondPointAD2);
    EIntersections eResultAB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBA1, vSecondPointBA1);
    EIntersections eResultAB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBA2, vSecondPointBA2);
    EIntersections eResultBC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCB1, vSecondPointCB1);
    EIntersections eResultBC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCB2, vSecondPointCB2);
    EIntersections eResultCD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EIntersections eResultCD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD1 == EXPECTED_FIRSTPOINT_AD_AB1);
    BOOST_CHECK(vFirstPointBA1 == EXPECTED_FIRSTPOINT_BA_BC1);
    BOOST_CHECK(vFirstPointCB1 == EXPECTED_FIRSTPOINT_CB_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DC_DA1);
    BOOST_CHECK(vFirstPointAD2 == EXPECTED_FIRSTPOINT_AD_AB2);
    BOOST_CHECK(vFirstPointBA2 == EXPECTED_FIRSTPOINT_BA_BC2);
    BOOST_CHECK(vFirstPointCB2 == EXPECTED_FIRSTPOINT_CB_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DC_DA2);
    BOOST_CHECK(vSecondPointAD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersect_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_4, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_5, SFloat::_1);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns no intersection point when the line and the quadrilateral don't intersect but would do if the line was infinite.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsNoIntersectionWhenLineAndQuadrilateralDoNotIntersectButWouldDoIfLineWasInfinite_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A = Vector2(SFloat::_3, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Vector2 EXPECTED_FIRSTPOINT = Vector2::GetNullVector();
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPoint = Vector2::GetNullVector();
    Vector2 vSecondPoint = Vector2::GetNullVector();
    EIntersections eResult = LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPoint == EXPECTED_FIRSTPOINT);
    BOOST_CHECK(vSecondPoint == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two contiguous vertices of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsTwoContiguousVertices_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.B + (QUAD.B - QUAD.A);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.C + (QUAD.C - QUAD.B);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.D + (QUAD.D - QUAD.C);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.A + (QUAD.A - QUAD.D);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_FIRSTPOINT_AB = QUAD.A;
    const Vector2 EXPECTED_FIRSTPOINT_BC = QUAD.B;
    const Vector2 EXPECTED_FIRSTPOINT_CD = QUAD.C;
    const Vector2 EXPECTED_FIRSTPOINT_DA = QUAD.D;
    const Vector2 EXPECTED_SECONDPOINT_AB = QUAD.B;
    const Vector2 EXPECTED_SECONDPOINT_BC = QUAD.C;
    const Vector2 EXPECTED_SECONDPOINT_CD = QUAD.D;
    const Vector2 EXPECTED_SECONDPOINT_DA = QUAD.A;

	// [Execution]
    Vector2 vFirstPointAB, vSecondPointAB;
    Vector2 vFirstPointBC, vSecondPointBC;
    Vector2 vFirstPointCD, vSecondPointCD;
    Vector2 vFirstPointDA, vSecondPointDA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB, vSecondPointAB);
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBC, vSecondPointBC);
    EIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCD, vSecondPointCD);
    EIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA, vSecondPointDA);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstPointDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondPointDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns two intersection points when the line belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_4, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A - (QUAD.A - QUAD.B).Normalize();
    const Vector2 ENDPOINT_B1 = QUAD.B - (QUAD.B - QUAD.A).Normalize();
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = QUAD.B - (QUAD.B - QUAD.C).Normalize();
    const Vector2 ENDPOINT_B2 = QUAD.C - (QUAD.C - QUAD.B).Normalize();
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 ENDPOINT_A3 = QUAD.C - (QUAD.C - QUAD.D).Normalize();
    const Vector2 ENDPOINT_B3 = QUAD.D - (QUAD.D - QUAD.C).Normalize();
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);

    const Vector2 ENDPOINT_A4 = QUAD.D - (QUAD.D - QUAD.A).Normalize();
    const Vector2 ENDPOINT_B4 = QUAD.A - (QUAD.A - QUAD.D).Normalize();
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_FIRSTPOINT_AB = LINE_SEGMENT1.A;
    const Vector2 EXPECTED_FIRSTPOINT_BC = LINE_SEGMENT2.A;
    const Vector2 EXPECTED_FIRSTPOINT_CD = LINE_SEGMENT3.A;
    const Vector2 EXPECTED_FIRSTPOINT_DA = LINE_SEGMENT4.A;
    const Vector2 EXPECTED_SECONDPOINT_AB = LINE_SEGMENT1.B;
    const Vector2 EXPECTED_SECONDPOINT_BC = LINE_SEGMENT2.B;
    const Vector2 EXPECTED_SECONDPOINT_CD = LINE_SEGMENT3.B;
    const Vector2 EXPECTED_SECONDPOINT_DA = LINE_SEGMENT4.B;

	// [Execution]
    Vector2 vFirstPointAB, vSecondPointAB;
    Vector2 vFirstPointBC, vSecondPointBC;
    Vector2 vFirstPointCD, vSecondPointCD;
    Vector2 vFirstPointDA, vSecondPointDA;
    EIntersections eResultAB = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB, vSecondPointAB);
    EIntersections eResultBC = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointBC, vSecondPointBC);
    EIntersections eResultCD = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointCD, vSecondPointCD);
    EIntersections eResultDA = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointDA, vSecondPointDA);

    // [Verification]
    BOOST_CHECK(eResultAB == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB == EXPECTED_FIRSTPOINT_AB);
    BOOST_CHECK(vFirstPointBC == EXPECTED_FIRSTPOINT_BC);
    BOOST_CHECK(vFirstPointCD == EXPECTED_FIRSTPOINT_CD);
    BOOST_CHECK(vFirstPointDA == EXPECTED_FIRSTPOINT_DA);
    BOOST_CHECK(vSecondPointAB == EXPECTED_SECONDPOINT_AB);
    BOOST_CHECK(vSecondPointBC == EXPECTED_SECONDPOINT_BC);
    BOOST_CHECK(vSecondPointCD == EXPECTED_SECONDPOINT_CD);
    BOOST_CHECK(vSecondPointDA == EXPECTED_SECONDPOINT_DA);
}

/// <summary>
/// Checks that it returns one intersection when the an end point of the line coincides with a vertex of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenAnEndpointCoincidesWithVertex_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_A1 = QUAD.A + (QUAD.A - QUAD.B);
    const Vector2 ENDPOINT_B1 = QUAD.A;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = QUAD.B + (QUAD.B - QUAD.C);
    const Vector2 ENDPOINT_B2 = QUAD.B;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = QUAD.C + (QUAD.C - QUAD.D);
    const Vector2 ENDPOINT_B3 = QUAD.C;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = QUAD.D + (QUAD.D - QUAD.A);
    const Vector2 ENDPOINT_B4 = QUAD.D;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT_A1 = QUAD.A;
    const Vector2 EXPECTED_FIRSTPOINT_B1 = QUAD.B;
    const Vector2 EXPECTED_FIRSTPOINT_C1 = QUAD.C;
    const Vector2 EXPECTED_FIRSTPOINT_D1 = QUAD.D;
    const Vector2 EXPECTED_FIRSTPOINT_A2 = QUAD.A;
    const Vector2 EXPECTED_FIRSTPOINT_B2 = QUAD.B;
    const Vector2 EXPECTED_FIRSTPOINT_C2 = QUAD.C;
    const Vector2 EXPECTED_FIRSTPOINT_D2 = QUAD.D;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointA1;
    Vector2 vFirstPointB1;
    Vector2 vFirstPointC1;
    Vector2 vFirstPointD1;
    Vector2 vFirstPointA2;
    Vector2 vFirstPointB2;
    Vector2 vFirstPointC2;
    Vector2 vFirstPointD2;
    Vector2 vSecondPointA1 = Vector2::GetNullVector();
    Vector2 vSecondPointB1 = Vector2::GetNullVector();
    Vector2 vSecondPointC1 = Vector2::GetNullVector();
    Vector2 vSecondPointD1 = Vector2::GetNullVector();
    Vector2 vSecondPointA2 = Vector2::GetNullVector();
    Vector2 vSecondPointB2 = Vector2::GetNullVector();
    Vector2 vSecondPointC2 = Vector2::GetNullVector();
    Vector2 vSecondPointD2 = Vector2::GetNullVector();
    EIntersections eResultA1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointA1, vSecondPointA1);
    EIntersections eResultA2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointA2, vSecondPointA2);
    EIntersections eResultB1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointB1, vSecondPointB1);
    EIntersections eResultB2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointB2, vSecondPointB2);
    EIntersections eResultC1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointC1, vSecondPointC1);
    EIntersections eResultC2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointC2, vSecondPointC2);
    EIntersections eResultD1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointD1, vSecondPointD1);
    EIntersections eResultD2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointD2, vSecondPointD2);

    // [Verification]
    BOOST_CHECK(eResultA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultA2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultD2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointA1 == EXPECTED_FIRSTPOINT_A1);
    BOOST_CHECK(vFirstPointB1 == EXPECTED_FIRSTPOINT_B1);
    BOOST_CHECK(vFirstPointC1 == EXPECTED_FIRSTPOINT_C1);
    BOOST_CHECK(vFirstPointD1 == EXPECTED_FIRSTPOINT_D1);
    BOOST_CHECK(vFirstPointA2 == EXPECTED_FIRSTPOINT_A2);
    BOOST_CHECK(vFirstPointB2 == EXPECTED_FIRSTPOINT_B2);
    BOOST_CHECK(vFirstPointC2 == EXPECTED_FIRSTPOINT_C2);
    BOOST_CHECK(vFirstPointD2 == EXPECTED_FIRSTPOINT_D2);
    BOOST_CHECK(vSecondPointA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointA2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointD2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns two intersection points when the line intersects with two non-contiguous edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsTwoIntersectionsWhenLineIntersectsWithTwoNonContiguousEdges_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_DA + MIDPOINT_DA - MIDPOINT_BC;
    const Vector2 ENDPOINT_B1 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_DA;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_CD;
    const Vector2 ENDPOINT_B2 = MIDPOINT_CD + MIDPOINT_CD - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const EIntersections EXPECTED_RESULT = EIntersections::E_Two;
    const Vector2 EXPECTED_FIRSTPOINT_AD_BC = MIDPOINT_DA;
    const Vector2 EXPECTED_FIRSTPOINT_AB_CD = MIDPOINT_AB;
    const Vector2 EXPECTED_SECONDPOINT_AD_BC = MIDPOINT_BC;
    const Vector2 EXPECTED_SECONDPOINT_AB_CD = MIDPOINT_CD;

	// [Execution]
    Vector2 vFirstPointAD_BC, vSecondPointAD_BC;
    Vector2 vFirstPointAB_CD, vSecondPointAB_CD;
    EIntersections eResultAD_BC = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAD_BC, vSecondPointAD_BC);
    EIntersections eResultAB_CD = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB_CD, vSecondPointAB_CD);

    // [Verification]
    BOOST_CHECK(eResultAD_BC == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB_CD == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAD_BC == EXPECTED_FIRSTPOINT_AD_BC);
    BOOST_CHECK(vFirstPointAB_CD == EXPECTED_FIRSTPOINT_AB_CD);
    BOOST_CHECK(vSecondPointAD_BC == EXPECTED_SECONDPOINT_AD_BC);
    BOOST_CHECK(vSecondPointAB_CD == EXPECTED_SECONDPOINT_AB_CD);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_AssertionFailsWhenBothEndpointsCoincide_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_1, SFloat::_1),
                                                       Vector2(SFloat::_3, SFloat::_1));

    const Vector2 ENDPOINT = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT, ENDPOINT);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vFirstPoint;
    Vector2 vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);
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
ZTEST_CASE ( IntersectionPoint4_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 VERTEX = Vector2(SFloat::_1, SFloat::_2);
    const BaseQuadrilateral QUAD = BaseQuadrilateral(VERTEX, VERTEX, VERTEX, VERTEX);

    const Vector2 ENDPOINT_A = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 ENDPOINT_B = Vector2(SFloat::_3, SFloat::_4);
    const LineSegment2D LINE_SEGMENT = LineSegment2D(ENDPOINT_A, ENDPOINT_B);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    Vector2 vFirstPoint;
    Vector2 vSecondPoint;

    try
    {
        LINE_SEGMENT.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint);
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
/// Checks that it returns the expected intersection points when both endpoints of the line segment coincide.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsExpectedIntersectionPointWhenBothEndpointsCoincide_Test )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    //             A------B
    //            /        \
    //           /          \
    //          /            \
    //         D--------------C

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_1),
                                                       Vector2(SFloat::_1, SFloat::_1));

    const Vector2 ENDPOINT_OUTSIDE = Vector2(SFloat::_4, SFloat::_4);
    const LineSegment2D LINE_SEGMENT_OUTSIDE = LineSegment2D(ENDPOINT_OUTSIDE, ENDPOINT_OUTSIDE);
    const EIntersections EXPECTED_RESULT_OUTSIDE = EIntersections::E_None;
    const Vector2 EXPECTED_POINT_OUTSIDE = Vector2::GetNullVector();
    
    const Vector2 ENDPOINT_IN_EDGE = Vector2(SFloat::_2, SFloat::_3);
    const LineSegment2D LINE_SEGMENT_IN_EDGE = LineSegment2D(ENDPOINT_IN_EDGE, ENDPOINT_IN_EDGE);
    const EIntersections EXPECTED_RESULT_IN_EDGE = EIntersections::E_Two;
    const Vector2 EXPECTED_POINT_IN_EDGE = Vector2(SFloat::_2, SFloat::_3);

    const Vector2 ENDPOINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);
    const LineSegment2D LINE_SEGMENT_INSIDE = LineSegment2D(ENDPOINT_INSIDE, ENDPOINT_INSIDE);
    const EIntersections EXPECTED_RESULT_INSIDE = EIntersections::E_Infinite;
    const Vector2 EXPECTED_POINT_INSIDE = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointOutside = Vector2::GetNullVector();
    Vector2 vFirstPointInEdge = Vector2::GetNullVector();
    Vector2 vFirstPointInside = Vector2::GetNullVector();
    Vector2 vSecondPointOutside = Vector2::GetNullVector();
    Vector2 vSecondPointInEdge = Vector2::GetNullVector();
    Vector2 vSecondPointInside = Vector2::GetNullVector();

    EIntersections eResultOutside = LINE_SEGMENT_OUTSIDE.IntersectionPoint(QUAD, vFirstPointOutside, vSecondPointOutside);
    EIntersections eResultInEdge = LINE_SEGMENT_IN_EDGE.IntersectionPoint(QUAD, vFirstPointInEdge, vSecondPointInEdge);
    EIntersections eResultInside = LINE_SEGMENT_INSIDE.IntersectionPoint(QUAD, vFirstPointInside, vSecondPointInside);

    // [Verification]
    BOOST_CHECK(eResultOutside == EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK(eResultInEdge == EXPECTED_RESULT_IN_EDGE);
    BOOST_CHECK(eResultInside == EXPECTED_RESULT_INSIDE);
    BOOST_CHECK(vFirstPointOutside == EXPECTED_POINT_OUTSIDE);
    BOOST_CHECK(vFirstPointInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vFirstPointInside == EXPECTED_POINT_INSIDE);
    BOOST_CHECK(vSecondPointOutside == EXPECTED_POINT_OUTSIDE);
    BOOST_CHECK(vSecondPointInEdge == EXPECTED_POINT_IN_EDGE);
    BOOST_CHECK(vSecondPointInside == EXPECTED_POINT_INSIDE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdge_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = MIDPOINT_AB + Vector2(SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + Vector2(SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = MIDPOINT_CD + Vector2(-SFloat::_1, -SFloat::_1);
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = MIDPOINT_DA + Vector2(-SFloat::_1, SFloat::_1);
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_FIRSTPOINT_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA2 = MIDPOINT_DA;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAB1;
    Vector2 vFirstPointBC1;
    Vector2 vFirstPointCD1;
    Vector2 vFirstPointDA1;
    Vector2 vFirstPointAB2;
    Vector2 vFirstPointBC2;
    Vector2 vFirstPointCD2;
    Vector2 vFirstPointDA2;
    Vector2 vSecondPointAB1 = Vector2::GetNullVector();
    Vector2 vSecondPointBC1 = Vector2::GetNullVector();
    Vector2 vSecondPointCD1 = Vector2::GetNullVector();
    Vector2 vSecondPointDA1 = Vector2::GetNullVector();
    Vector2 vSecondPointAB2 = Vector2::GetNullVector();
    Vector2 vSecondPointBC2 = Vector2::GetNullVector();
    Vector2 vSecondPointCD2 = Vector2::GetNullVector();
    Vector2 vSecondPointDA2 = Vector2::GetNullVector();
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB1, vSecondPointAB1);
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB2, vSecondPointAB2);
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBC1, vSecondPointBC1);
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBC2, vSecondPointBC2);
    EIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCD1, vSecondPointCD1);
    EIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCD2, vSecondPointCD2);
    EIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointCD1 == EXPECTED_FIRSTPOINT_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DA1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCD2 == EXPECTED_FIRSTPOINT_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns one intersection point when only one point of the line segment belongs to an edge of the quadrilateral and the other endpoint is inside the quadrilateral.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnsOneIntersectionWhenOnlyOneEndPointBelongsToAnEdgeAndTheOtherEndpointIsInsideTheQuadrilateral_Test )
{
    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 CENTER_POINT = QUAD.A.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);
    const Vector2 MIDPOINT_CD = QUAD.C.Lerp(SFloat::_0_5, QUAD.D);
    const Vector2 MIDPOINT_DA = QUAD.D.Lerp(SFloat::_0_5, QUAD.A);

    const Vector2 ENDPOINT_A1 = MIDPOINT_AB;
    const Vector2 ENDPOINT_B1 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT1 = LineSegment2D(ENDPOINT_A1, ENDPOINT_B1);
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_B1, ENDPOINT_A1);

    const Vector2 ENDPOINT_A2 = MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT3 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);
    const LineSegment2D LINE_SEGMENT4 = LineSegment2D(ENDPOINT_B2, ENDPOINT_A2);

    const Vector2 ENDPOINT_A3 = MIDPOINT_CD;
    const Vector2 ENDPOINT_B3 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT5 = LineSegment2D(ENDPOINT_A3, ENDPOINT_B3);
    const LineSegment2D LINE_SEGMENT6 = LineSegment2D(ENDPOINT_B3, ENDPOINT_A3);

    const Vector2 ENDPOINT_A4 = MIDPOINT_DA;
    const Vector2 ENDPOINT_B4 = CENTER_POINT;
    const LineSegment2D LINE_SEGMENT7 = LineSegment2D(ENDPOINT_A4, ENDPOINT_B4);
    const LineSegment2D LINE_SEGMENT8 = LineSegment2D(ENDPOINT_B4, ENDPOINT_A4);

    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Vector2 EXPECTED_FIRSTPOINT_AB1 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC1 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD1 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA1 = MIDPOINT_DA;
    const Vector2 EXPECTED_FIRSTPOINT_AB2 = MIDPOINT_AB;
    const Vector2 EXPECTED_FIRSTPOINT_BC2 = MIDPOINT_BC;
    const Vector2 EXPECTED_FIRSTPOINT_CD2 = MIDPOINT_CD;
    const Vector2 EXPECTED_FIRSTPOINT_DA2 = MIDPOINT_DA;
    const Vector2 EXPECTED_SECONDPOINT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vFirstPointAB1;
    Vector2 vFirstPointBC1;
    Vector2 vFirstPointCD1;
    Vector2 vFirstPointDA1;
    Vector2 vFirstPointAB2;
    Vector2 vFirstPointBC2;
    Vector2 vFirstPointCD2;
    Vector2 vFirstPointDA2;
    Vector2 vSecondPointAB1 = Vector2::GetNullVector();
    Vector2 vSecondPointBC1 = Vector2::GetNullVector();
    Vector2 vSecondPointCD1 = Vector2::GetNullVector();
    Vector2 vSecondPointDA1 = Vector2::GetNullVector();
    Vector2 vSecondPointAB2 = Vector2::GetNullVector();
    Vector2 vSecondPointBC2 = Vector2::GetNullVector();
    Vector2 vSecondPointCD2 = Vector2::GetNullVector();
    Vector2 vSecondPointDA2 = Vector2::GetNullVector();
    EIntersections eResultAB1 = LINE_SEGMENT1.IntersectionPoint(QUAD, vFirstPointAB1, vSecondPointAB1);
    EIntersections eResultAB2 = LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPointAB2, vSecondPointAB2);
    EIntersections eResultBC1 = LINE_SEGMENT3.IntersectionPoint(QUAD, vFirstPointBC1, vSecondPointBC1);
    EIntersections eResultBC2 = LINE_SEGMENT4.IntersectionPoint(QUAD, vFirstPointBC2, vSecondPointBC2);
    EIntersections eResultCD1 = LINE_SEGMENT5.IntersectionPoint(QUAD, vFirstPointCD1, vSecondPointCD1);
    EIntersections eResultCD2 = LINE_SEGMENT6.IntersectionPoint(QUAD, vFirstPointCD2, vSecondPointCD2);
    EIntersections eResultDA1 = LINE_SEGMENT7.IntersectionPoint(QUAD, vFirstPointDA1, vSecondPointDA1);
    EIntersections eResultDA2 = LINE_SEGMENT8.IntersectionPoint(QUAD, vFirstPointDA2, vSecondPointDA2);

    // [Verification]
    BOOST_CHECK(eResultAB1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultAB2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultBC2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultCD2 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA1 == EXPECTED_RESULT);
    BOOST_CHECK(eResultDA2 == EXPECTED_RESULT);
    BOOST_CHECK(vFirstPointAB1 == EXPECTED_FIRSTPOINT_AB1);
    BOOST_CHECK(vFirstPointBC1 == EXPECTED_FIRSTPOINT_BC1);
    BOOST_CHECK(vFirstPointCD1 == EXPECTED_FIRSTPOINT_CD1);
    BOOST_CHECK(vFirstPointDA1 == EXPECTED_FIRSTPOINT_DA1);
    BOOST_CHECK(vFirstPointAB2 == EXPECTED_FIRSTPOINT_AB2);
    BOOST_CHECK(vFirstPointBC2 == EXPECTED_FIRSTPOINT_BC2);
    BOOST_CHECK(vFirstPointCD2 == EXPECTED_FIRSTPOINT_CD2);
    BOOST_CHECK(vFirstPointDA2 == EXPECTED_FIRSTPOINT_DA2);
    BOOST_CHECK(vSecondPointAB1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA1 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointAB2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointBC2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointCD2 == EXPECTED_SECONDPOINT);
    BOOST_CHECK(vSecondPointDA2 == EXPECTED_SECONDPOINT);
}

/// <summary>
/// Checks that it returns the closest intersection point to A endpoint, when there are two intersections.
/// </summary>
ZTEST_CASE ( IntersectionPoint4_ReturnedPointIsTheClosestOneToEndpointA_Test )
{

    // [Preparation]
    const BaseQuadrilateral QUAD = BaseQuadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                                       Vector2(SFloat::_3, SFloat::_2),
                                                       Vector2(SFloat::_3, SFloat::_0),
                                                       Vector2(-SFloat::_1, SFloat::_1));

    const Vector2 MIDPOINT_AB = QUAD.A.Lerp(SFloat::_0_5, QUAD.B);
    const Vector2 MIDPOINT_BC = QUAD.B.Lerp(SFloat::_0_5, QUAD.C);

    const Vector2 ENDPOINT_A2 = MIDPOINT_AB + MIDPOINT_AB - MIDPOINT_BC;
    const Vector2 ENDPOINT_B2 = MIDPOINT_BC + MIDPOINT_BC - MIDPOINT_AB;
    const LineSegment2D LINE_SEGMENT2 = LineSegment2D(ENDPOINT_A2, ENDPOINT_B2);

    const Vector2 CLOSEST_INTERSECTION_TO_A = MIDPOINT_AB;
    const Vector2 FARTHEST_INTERSECTION_TO_A = MIDPOINT_BC;

	// [Execution]
    Vector2 vFirstPoint, vSecondPoint;
    LINE_SEGMENT2.IntersectionPoint(QUAD, vFirstPoint, vSecondPoint); // I

    // [Verification]
    BOOST_CHECK(vFirstPoint == CLOSEST_INTERSECTION_TO_A);
    BOOST_CHECK(vFirstPoint != FARTHEST_INTERSECTION_TO_A);
}

// [TODO] Thund: It's necessary to test whether one intersection is returned or not when 
//               the line is partially contained in an edge.

// End - Test Suite: LineSegment2D
ZTEST_SUITE_END()
