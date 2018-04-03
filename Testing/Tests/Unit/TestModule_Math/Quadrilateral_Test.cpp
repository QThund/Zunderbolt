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

#include "ZMath/Quadrilateral.h"

#include "ZMath/TransformationMatrix3x3.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( Quadrilateral_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    // [Execution]
    Quadrilateral quadrilateralUT;

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if copy constructor sets quadrilateral components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_6, SFloat::_7);

    const Quadrilateral QUAD_TO_COPY = Quadrilateral(EXPECTED_VALUE_FOR_A,
                                                       EXPECTED_VALUE_FOR_B,
                                                       EXPECTED_VALUE_FOR_C,
                                                       EXPECTED_VALUE_FOR_D);

    // [Execution]
    Quadrilateral quadrilateralUT = QUAD_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks if base copy constructor sets quadrilateral components properly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_6, SFloat::_7);

    const BaseQuadrilateral QUAD_TO_COPY = BaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C,
                                                               EXPECTED_VALUE_FOR_D);

    // [Execution]
    Quadrilateral quadrilateralUT = QUAD_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreCorrectlySet_Test )
{
	// [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_6, SFloat::_7);

    // [Execution]
    Quadrilateral quadrilateralUT = Quadrilateral(EXPECTED_VALUE_FOR_A,
                                                    EXPECTED_VALUE_FOR_B,
                                                    EXPECTED_VALUE_FOR_C,
                                                    EXPECTED_VALUE_FOR_D);

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that it returns a square whose edges' length equal one.
/// </summary>
ZTEST_CASE ( GetUnitSquare_ReturnsTheExpectedSquare_Test )
{
	// [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_0_5, SFloat::_0_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_0_5, SFloat::_0_5);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_0_5, -SFloat::_0_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(-SFloat::_0_5, -SFloat::_0_5);

    // [Execution]
    Quadrilateral quadrilateralUT = Quadrilateral::GetUnitSquare();

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks if assignation operator sets quadrilateral components properly.
/// </summary>
ZTEST_CASE ( AssignationOperator_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_6, SFloat::_7);

    const BaseQuadrilateral QUAD_TO_COPY = BaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C,
                                                               EXPECTED_VALUE_FOR_D);

    // [Execution]
    Quadrilateral quadrilateralUT;
    quadrilateralUT = QUAD_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(quadrilateralUT.A.x, EXPECTED_VALUE_FOR_A.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.A.y, EXPECTED_VALUE_FOR_A.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.x, EXPECTED_VALUE_FOR_B.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.B.y, EXPECTED_VALUE_FOR_B.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.x, EXPECTED_VALUE_FOR_C.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.C.y, EXPECTED_VALUE_FOR_C.y);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.x, EXPECTED_VALUE_FOR_D.x);
    BOOST_CHECK_EQUAL(quadrilateralUT.D.y, EXPECTED_VALUE_FOR_D.y);
}

/// <summary>
/// Checks that it returns False when the point doesn't belong to the quadrilateral.
/// </summary>
ZTEST_CASE ( Contains_ReturnsFalseWhenThePointIsNotInsideTheQuadrilateral_Test )
{
    //   A----------B
    //   |          |
    //   |          |   P
    //   |          |
    //   |          |
    //   D----------C
    //

    // [Preparation]
    const Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    const Vector2 POINT = Vector2(SFloat::_3, SFloat::_4);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = QUAD.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point belongs to one of the edges of the quadrilateral.
/// </summary>
ZTEST_CASE ( Contains_ReturnsTrueWhenThePointBelongsToAnEdgeOfQuadrilateral_Test )
{
    //   A----P-----B   A----------B   A----------B   A----------B
    //   |          |   |          |   |          |   |          |
    //   |          |   |          P   |          |   |          |
    //   |          |   |          |   |          |   P          |
    //   |          |   |          |   |          |   |          |
    //   D----------C   D----------C   D----P-----C   D----------C
    //
    //        I              II             III           IV

    // [Preparation]
    const Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    const Vector2 POINT_AB = QUAD.A.Lerp(SFloat::_0_25, QUAD.B);
    const Vector2 POINT_BC = QUAD.B.Lerp(SFloat::_0_25, QUAD.C);
    const Vector2 POINT_CD = QUAD.C.Lerp(SFloat::_0_25, QUAD.D);
    const Vector2 POINT_DA = QUAD.D.Lerp(SFloat::_0_25, QUAD.A);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResultAB = QUAD.Contains(POINT_AB); // I
    bool bResultBC = QUAD.Contains(POINT_BC); // II
    bool bResultCD = QUAD.Contains(POINT_CD); // III
    bool bResultDA = QUAD.Contains(POINT_DA); // IV

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultBC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultCD, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultDA, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point coincides with one of the vertices of the quadrilateral.
/// </summary>
ZTEST_CASE ( Contains_ReturnsTrueWhenThePointCoincidesWithVertexOfQuadrilateral_Test )
{
    //   AP---------B   A----------BP  A----------B   A----------B
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   |          |   |          |   |          |   |          |
    //   D----------C   D----------C   D----------CP  DP---------C
    //
    //        I              II             III           IV

    // [Preparation]
    const Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    const Vector2 POINT_A = QUAD.A;
    const Vector2 POINT_B = QUAD.B;
    const Vector2 POINT_C = QUAD.C;
    const Vector2 POINT_D = QUAD.D;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResultA = QUAD.Contains(POINT_A); // I
    bool bResultB = QUAD.Contains(POINT_B); // II
    bool bResultC = QUAD.Contains(POINT_C); // III
    bool bResultD = QUAD.Contains(POINT_D); // IV

    // [Verification]
    BOOST_CHECK_EQUAL(bResultA, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultB, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultC, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultD, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the point belongs to the quadrilateral.
/// </summary>
ZTEST_CASE ( Contains_ReturnsTrueWhenThePointIsInsideTheQuadrilateral_Test )
{
    //   A----------B
    //   |          |
    //   |       P  |
    //   |          |
    //   |          |
    //   D----------C
    //

    // [Preparation]
    const Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    const Vector2 POINT = Vector2(SFloat::_0_25, SFloat::_0_25);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = QUAD.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
ZTEST_CASE ( Contains_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 QUAD_POINT = Vector2(SFloat::_1, SFloat::_2);
    const Quadrilateral QUAD = Quadrilateral(QUAD_POINT, QUAD_POINT, QUAD_POINT, QUAD_POINT);
    const Vector2 POINT = Vector2(SFloat::_0_25, SFloat::_0_25);

    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        QUAD.Contains(POINT);
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
/// Checks that it returns what expected when the quadrilateral is complex (two opposite edges intersect).
/// </summary>
ZTEST_CASE ( Contains_ReturnsWhatExpectedWhenTheQuadrilateralIsComplex_Test )
{
    //    A----B      A----B
    //     \  /        \ P/
    //      \/  P       \/
    //      /\          /\
    //     /  \        /  \
    //    C----D      C----D
    //
    //      I           II

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    const Vector2 AUX = QUAD.C;
    QUAD.C = QUAD.D;
    QUAD.D = AUX;
    const Vector2 POINT_OUTSIDE = Vector2(SFloat::_0_25, SFloat::_0);
    const Vector2 POINT_INSIDE = Vector2(SFloat::_0, SFloat::_0_25);

    const bool EXPECTED_RESULT_OUTSIDE = false;
    const bool EXPECTED_RESULT_INSIDE = true;

    // [Execution]
    bool bResultOutside = QUAD.Contains(POINT_OUTSIDE); // I
    bool bResultInside = QUAD.Contains(POINT_INSIDE); // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
}

/// <summary>
/// Checks that it returns what expected when the quadrilateral is concave.
/// </summary>
ZTEST_CASE ( Contains_ReturnsWhatExpectedWhenTheQuadrilateralIsConcave_Test )
{
    //       B            B
    //      /|           /|
    //     / C P        / C
    //    /   \        / P \
    //   A-----D      A-----D
    //
    //      I           II

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral(Vector2(SFloat::_1, SFloat::_1),
                                         Vector2(SFloat::_4, SFloat::_5),
                                         Vector2(SFloat::_3, SFloat::_2),
                                         Vector2(SFloat::_4, SFloat::_1));

    const Vector2 POINT_OUTSIDE = QUAD.C + Vector2(SFloat::_0_25, SFloat::_0);
    const Vector2 POINT_INSIDE = Vector2(SFloat::_2, SFloat::_2);

    const bool EXPECTED_RESULT_OUTSIDE = false;
    const bool EXPECTED_RESULT_INSIDE = true;

    // [Execution]
    bool bResultOutside = QUAD.Contains(POINT_OUTSIDE); // I
    bool bResultInside = QUAD.Contains(POINT_INSIDE);   // II

    // [Verification]
    BOOST_CHECK_EQUAL(bResultOutside, EXPECTED_RESULT_OUTSIDE);
    BOOST_CHECK_EQUAL(bResultInside, EXPECTED_RESULT_INSIDE);
}

/// <summary>
/// Checks that it returns False when the quadrilaterals doesn't intersect.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsFalseWhenQuadrilateralsDoesNotIntersect_Test )
{
    //   A----------B   A----------B
    //   |          |   |          |
    //   |    1     |   |    2     |
    //   |          |   |          |
    //   |          |   |          |
    //   D----------C   D----------C
    //

    // [Preparation]
    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1.Translate(SFloat::_10, SFloat::_10);

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals intersect.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsIntersect_Test )
{
    //   A----------B
    //   |          |
    //   |    1     |
    //   |     A----------B
    //   |     |    |     |
    //   D-----|----C     |
    //         |    2     |
    //         |          |
    //         D----------C

    // [Preparation]
    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1.Translate(SFloat::_0_5, SFloat::_0_5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals share one vertex.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsShareVertex_Test )
{
    //   A----------B
    //   |          |
    //   |    1     |
    //   |          |
    //   |          |
    //   D----------CA----B
    //               | 2  |
    //               |    |
    //               D----C

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
#endif

    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1;

    const Quadrilateral QUAD1_ROT1 = QUAD1;
    const Quadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const Quadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const Quadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const Quadrilateral QUAD2_ROT1 = QUAD2.Translate(SFloat::_1, SFloat::_1);
    const Quadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION).Translate(SFloat::_1, SFloat::_1);
    const Quadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION).Translate(SFloat::_1, SFloat::_1);
    const Quadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(SFloat::_1, SFloat::_1);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the corner of a quadrilateral intersects with the edge of the other quadrilateral.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralCornerIntersectsWithAnEdgeOfTheOther_Test )
{
    //   A----------B A____________B
    //   |          |/            /
    //   |    1     /     2      /
    //   |         /|           /
    //   |        D_|__________C
    //   |          |
    //   |          |
    //   D----------C

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z INITIAL_ROTATION = SAngle::_45;
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z INITIAL_ROTATION = SAngle::_QuarterPi;
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
#endif

    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1.Rotate(INITIAL_ROTATION);

    const Quadrilateral QUAD1_ROT1 = QUAD1;
    const Quadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const Quadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const Quadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const Quadrilateral QUAD2_ROT1 = QUAD2                          .Translate(SFloat::_1, SFloat::_0);
    const Quadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION) .Translate(SFloat::_1, SFloat::_0);
    const Quadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION)    .Translate(SFloat::_1, SFloat::_0);
    const Quadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(SFloat::_1, SFloat::_0);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one of the vertices of a quadrilateral belongs to the edge of the other quadrilateral (excluding coincidental vertices).
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralVertexBelongsToAnEdgeOfTheOther_Test )
{
    //   A----------B   A____________B
    //   |          |  /            /
    //   |    1     | /     2      /
    //   |          |/            /
    //   |          D____________C
    //   |          |
    //   |          |
    //   D----------C

    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z INITIAL_ROTATION = SAngle::_45;
    const float_z QUARTER_ROTATION = SAngle::_90;
    const float_z HALF_ROTATION = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z INITIAL_ROTATION = SAngle::_QuarterPi;
    const float_z QUARTER_ROTATION = SAngle::_HalfPi;
    const float_z HALF_ROTATION = SAngle::_Pi;
#endif

    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1.Rotate(INITIAL_ROTATION);

    const float_z QUAD2_RADIUS = (QUAD2.A - QUAD2.C).GetLength() / 2;
    const float_z QUAD1_AB_LENGTH = (QUAD1.A - QUAD1.B).GetLength();
    const Vector2 QUAD2_POSITION = Vector2(QUAD1_AB_LENGTH / 2 + QUAD2_RADIUS, SFloat::_0);

    const Quadrilateral QUAD1_ROT1 = QUAD1;
    const Quadrilateral QUAD1_ROT2 = QUAD1.Rotate(QUARTER_ROTATION);
    const Quadrilateral QUAD1_ROT3 = QUAD1.Rotate(HALF_ROTATION);
    const Quadrilateral QUAD1_ROT4 = QUAD1.Rotate(-QUARTER_ROTATION);

    const Quadrilateral QUAD2_ROT1 = QUAD2                          .Translate(QUAD2_POSITION);
    const Quadrilateral QUAD2_ROT2 = QUAD2.Rotate(QUARTER_ROTATION) .Translate(QUAD2_POSITION);
    const Quadrilateral QUAD2_ROT3 = QUAD2.Rotate(HALF_ROTATION)    .Translate(QUAD2_POSITION);
    const Quadrilateral QUAD2_ROT4 = QUAD2.Rotate(-QUARTER_ROTATION).Translate(QUAD2_POSITION);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResultQ1R1_Q2R1 = QUAD1_ROT1.Intersection(QUAD2_ROT1);
    bool bResultQ1R1_Q2R2 = QUAD1_ROT1.Intersection(QUAD2_ROT2);
    bool bResultQ1R1_Q2R3 = QUAD1_ROT1.Intersection(QUAD2_ROT3);
    bool bResultQ1R1_Q2R4 = QUAD1_ROT1.Intersection(QUAD2_ROT4);

    bool bResultQ1R2_Q2R1 = QUAD1_ROT2.Intersection(QUAD2_ROT1);
    bool bResultQ1R2_Q2R2 = QUAD1_ROT2.Intersection(QUAD2_ROT2);
    bool bResultQ1R2_Q2R3 = QUAD1_ROT2.Intersection(QUAD2_ROT3);
    bool bResultQ1R2_Q2R4 = QUAD1_ROT2.Intersection(QUAD2_ROT4);

    bool bResultQ1R3_Q2R1 = QUAD1_ROT3.Intersection(QUAD2_ROT1);
    bool bResultQ1R3_Q2R2 = QUAD1_ROT3.Intersection(QUAD2_ROT2);
    bool bResultQ1R3_Q2R3 = QUAD1_ROT3.Intersection(QUAD2_ROT3);
    bool bResultQ1R3_Q2R4 = QUAD1_ROT3.Intersection(QUAD2_ROT4);

    bool bResultQ1R4_Q2R1 = QUAD1_ROT4.Intersection(QUAD2_ROT1);
    bool bResultQ1R4_Q2R2 = QUAD1_ROT4.Intersection(QUAD2_ROT2);
    bool bResultQ1R4_Q2R3 = QUAD1_ROT4.Intersection(QUAD2_ROT3);
    bool bResultQ1R4_Q2R4 = QUAD1_ROT4.Intersection(QUAD2_ROT4);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R1_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R2_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R3_Q2R4, EXPECTED_RESULT);

    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R2, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R3, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResultQ1R4_Q2R4, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilaterals coincide.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenQuadrilateralsCoincide_Test )
{
    //   AA---------BB
    //   |          |
    //   |  1 & 2   |
    //   |          |
    //   |          |
    //   DD---------CC

    // [Preparation]
    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when one quadrilateral contains the other.
/// </summary>
ZTEST_CASE ( Intersection_ReturnsTrueWhenOneQuadrilateralContainsTheOther_Test )
{
    //   A----------B
    //   |    1     |
    //   |  A----B  |
    //   |  | 2  |  |
    //   |  D----C  |
    //   D----------C

    // [Preparation]
    const Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    const Quadrilateral QUAD2 = QUAD1.Scale(SFloat::_0_5, SFloat::_0_5);

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult1 = QUAD1.Intersection(QUAD2);
    bool bResult2 = QUAD2.Intersection(QUAD1);

    // [Verification]
    BOOST_CHECK_EQUAL(bResult1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bResult2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all the vertices of the quadrilateral coincide.
/// </summary>
ZTEST_CASE ( Intersection_AssertionFailsWhenAllVerticesCoincide_Test )
{
    // [Preparation]
    const Vector2 POINT = Vector2(SFloat::_1, SFloat::_2);
    const Quadrilateral QUAD1 = Quadrilateral(POINT, POINT, POINT, POINT);
    const Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.Intersection(QUAD2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.Intersection(QUAD1);
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
/// Checks that it returns True when the quadrilateral is complex.
/// </summary>
ZTEST_CASE ( IsComplex_ReturnsTrueWhenQuadrilateralIsComplex_Test )
{
    //   A----B
    //    \  /
    //     \/
    //     /\
    //    /  \
    //   D----C

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    Vector2 AUX = QUAD.B;
    QUAD.B = QUAD.A;
    QUAD.A = AUX;

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = QUAD.IsComplex();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not complex.
/// </summary>
ZTEST_CASE ( IsComplex_ReturnsFalseWhenQuadrilateralIsNotComplex_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = QUAD.IsComplex();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilateral is convex.
/// </summary>
ZTEST_CASE ( IsConvex_ReturnsTrueWhenQuadrilateralIsConvex_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = QUAD.IsConvex();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not convex.
/// </summary>
ZTEST_CASE ( IsConvex_ReturnsFalseWhenQuadrilateralIsNotConvex_Test )
{
    //   A
    //   |\
    //   | B-C
    //   |  /
    //   | /
    //   |/
    //   D

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                         Vector2(SFloat::_2, SFloat::_2),
                                         Vector2(SFloat::_3, SFloat::_2),
                                         Vector2(SFloat::_1, SFloat::_0));

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = QUAD.IsConvex();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the quadrilateral is concave.
/// </summary>
ZTEST_CASE ( IsConcave_ReturnsTrueWhenQuadrilateralIsConcave_Test )
{
    //   A
    //   |\
    //   | B-C
    //   |  /
    //   | /
    //   |/
    //   D

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral(Vector2(SFloat::_1, SFloat::_3),
                                         Vector2(SFloat::_2, SFloat::_2),
                                         Vector2(SFloat::_3, SFloat::_2),
                                         Vector2(SFloat::_1, SFloat::_0));

    const bool EXPECTED_RESULT = true;

    // [Execution]
    bool bResult = QUAD.IsConcave();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the quadrilateral is not concave.
/// </summary>
ZTEST_CASE ( IsConcave_ReturnsFalseWhenQuadrilateralIsNotConcave_Test )
{
    //   A----B
    //   |    |
    //   |    |
    //   |    |
    //   |    |
    //   D----C

    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();

    const bool EXPECTED_RESULT = false;

    // [Execution]
    bool bResult = QUAD.IsConcave();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected angle of a common corner.
/// </summary>
ZTEST_CASE ( GetAngleA_ReturnsExpectedAngleForCommonCorner_Test )
{
    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    QUAD.B = Vector2(SFloat::_0, SFloat::_0);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_RESULT = SAngle::_45;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
#endif

    // [Execution]
    float_z fResult = QUAD.GetAngleA();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
ZTEST_CASE ( GetAngleA_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.A = Vector2(SFloat::_2, -SFloat::_2);

    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.A = Vector2(SFloat::_0, -SFloat::_0_5);
    QUAD2.B = Vector2(SFloat::_2, -SFloat::_0_5);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z STRAIGHT_ANGLE = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z STRAIGHT_ANGLE = SAngle::_Pi;
#endif

    // [Execution]
    float_z fResult1 = QUAD1.GetAngleA(); // Corner in opposite side
    float_z fResult2 = QUAD2.GetAngleA(); // Straight angle

    // [Verification]
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
ZTEST_CASE ( GetAngleA_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.B = QUAD1.A;
    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.D = QUAD2.A;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleA();
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleA();
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
/// Checks that it returns the expected angle of a common corner.
/// </summary>
ZTEST_CASE ( GetAngleB_ReturnsExpectedAngleForCommonCorner_Test )
{
    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    QUAD.A = Vector2(SFloat::_0, SFloat::_0);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_RESULT = SAngle::_45;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
#endif

    // [Execution]
    float_z fResult = QUAD.GetAngleB();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
ZTEST_CASE ( GetAngleB_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.B = Vector2(-SFloat::_2, -SFloat::_2);

    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.C = Vector2(SFloat::_2, SFloat::_0_5);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z STRAIGHT_ANGLE = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z STRAIGHT_ANGLE = SAngle::_Pi;
#endif

    // [Execution]
    float_z fResult1 = QUAD1.GetAngleB(); // Corner in opposite side
    float_z fResult2 = QUAD2.GetAngleB(); // Straight angle

    // [Verification]
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
ZTEST_CASE ( GetAngleB_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.A = QUAD1.B;
    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.C = QUAD2.B;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleB();
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleB();
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
/// Checks that it returns the expected angle of a common corner.
/// </summary>
ZTEST_CASE ( GetAngleC_ReturnsExpectedAngleForCommonCorner_Test )
{
    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    QUAD.B = Vector2(SFloat::_0, SFloat::_0);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_RESULT = SAngle::_45;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
#endif

    // [Execution]
    float_z fResult = QUAD.GetAngleC();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
ZTEST_CASE ( GetAngleC_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.C = Vector2(-SFloat::_2, SFloat::_2);

    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.B = Vector2(SFloat::_2, -SFloat::_0_5);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z STRAIGHT_ANGLE = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z STRAIGHT_ANGLE = SAngle::_Pi;
#endif

    // [Execution]
    float_z fResult1 = QUAD1.GetAngleC(); // Corner in opposite side
    float_z fResult2 = QUAD2.GetAngleC(); // Straight angle

    // [Verification]
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
ZTEST_CASE ( GetAngleC_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.B = QUAD1.C;
    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.D = QUAD2.C;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleC();
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleC();
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
/// Checks that it returns the expected angle of a common corner.
/// </summary>
ZTEST_CASE ( GetAngleD_ReturnsExpectedAngleForCommonCorner_Test )
{
    // [Preparation]
    Quadrilateral QUAD = Quadrilateral::GetUnitSquare();
    QUAD.A = Vector2(SFloat::_0, SFloat::_0);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EXPECTED_RESULT = SAngle::_45;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
#endif

    // [Execution]
    float_z fResult = QUAD.GetAngleD();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResult, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the returned angle is always less than or equals a straight angle.
/// </summary>
ZTEST_CASE ( GetAngleD_ReturnedAngleIsAlwaysLessThanOrEqualsStraightAngle_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.D = Vector2(SFloat::_2, SFloat::_2);

    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.A = Vector2(-SFloat::_2, -SFloat::_0_5);

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z STRAIGHT_ANGLE = SAngle::_180;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z STRAIGHT_ANGLE = SAngle::_Pi;
#endif

    // [Execution]
    float_z fResult1 = QUAD1.GetAngleD(); // Corner in opposite side
    float_z fResult2 = QUAD2.GetAngleD(); // Straight angle

    // [Verification]
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult1, STRAIGHT_ANGLE) );
    BOOST_CHECK( SFloat::IsLessOrEquals(fResult2, STRAIGHT_ANGLE) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when a contiguous vertex coincides with corner.
/// </summary>
ZTEST_CASE ( GetAngleD_AssertionFailsWhenContiguousVertexAndCornerCoincide_Test )
{
    // [Preparation]
    Quadrilateral QUAD1 = Quadrilateral::GetUnitSquare();
    QUAD1.C = QUAD1.D;
    Quadrilateral QUAD2 = Quadrilateral::GetUnitSquare();
    QUAD2.A = QUAD2.D;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        QUAD1.GetAngleD();
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        QUAD2.GetAngleD();
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
/// Checks that a quadrilateral is correctly rotated.
/// </summary>
ZTEST_CASE ( Rotate_QuadrilateralIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 POINT_D = Vector2(-SFloat::_1, SFloat::_2);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(-SFloat::_2, -SFloat::_1);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Rotate(ANGLE);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not rotated when angle is zero.
/// </summary>
ZTEST_CASE ( Rotate_QuadrilateralIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_2, SFloat::_1);
    const float_z ANGLE = SFloat::_0;

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Quadrilateral result = QUAD.Rotate(ANGLE);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly translated.
/// </summary>
ZTEST_CASE ( Translate1_QuadrilateralIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_0, SFloat::_1);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, SFloat::_5);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Translate(TRANSLATION_VECTOR);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate1_QuadrilateralIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, SFloat::_5);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Quadrilateral result = QUAD.Translate(TRANSLATION_VECTOR);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly translated.
/// </summary>
ZTEST_CASE ( Translate2_QuadrilateralIsCorrectlyTranslated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_0, SFloat::_1);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, SFloat::_5);

    const Vector2 TRANSLATION_VECTOR = Vector2(SFloat::_3, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not translated when translation is zero.
/// </summary>
ZTEST_CASE ( Translate2_QuadrilateralIsNotTranslatedWhenTranslationIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_4, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, SFloat::_5);

    const Vector2 TRANSLATION_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Quadrilateral result = QUAD.Translate(TRANSLATION_VECTOR.x, TRANSLATION_VECTOR.y);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale1_QuadrilateralIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_10);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if Scale is one.
/// </summary>
ZTEST_CASE ( Scale1_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the coordinates origin when the scale equals zero.
/// </summary>
ZTEST_CASE ( Scale1_AllVerticesAreMovedToCoordinatesOriginWhenScaleEqualsZero_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_ALL = Vector2::GetNullVector();

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
ZTEST_CASE ( Scale2_QuadrilateralIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_10 + SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_4, SFloat::_10 + SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_10);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if scale equals one.
/// </summary>
ZTEST_CASE ( Scale2_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the coordinates origin when the scale equals zero.
/// </summary>
ZTEST_CASE ( Scale2_AllVerticesAreMovedToCoordinatesOriginWhenScaleEqualsZero_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_ALL = Vector2::GetNullVector();

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    Quadrilateral result = QUAD.Scale(SCALING_VECTOR.x, SCALING_VECTOR.y);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly transformed.
/// </summary>
ZTEST_CASE ( Transform_QuadrilateralIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 INIT_POS_C = Vector2(SFloat::_2, SFloat::_6);
    const Vector2 INIT_POS_D = Vector2(SFloat::_0, SFloat::_2);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_0, SFloat::_3);

    const Quadrilateral QUAD = Quadrilateral(INIT_POS_A, INIT_POS_B, INIT_POS_C, INIT_POS_D);

	// [Execution]
    const Quadrilateral result = QUAD.Transform(TRANSFORMATION_MATRIX);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that the quadrilateral doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform_QuadrilateralDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(-SFloat::_1, SFloat::_2);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    const Quadrilateral result = QUAD.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices of the quadrilateral are moved to the coordinate origin.
/// </summary>
ZTEST_CASE ( Transform_AllVerticesAreMovedToCoordinateOriginWhenTransfomedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_RESULT_ALL = Vector2::GetNullVector();

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);

	// [Execution]
    const Quadrilateral result = QUAD.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.B == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.C == EXPECTED_RESULT_ALL);
    BOOST_CHECK(result.D == EXPECTED_RESULT_ALL);
}

/// <summary>
/// Checks that a quadrilateral is correctly rotated.
/// </summary>
ZTEST_CASE ( RotateWithPivot_QuadrilateralIsCorrectlyRotated_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(-SFloat::_2, SFloat::_2);
    const Vector2 POINT_C = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 POINT_D = Vector2(-SFloat::_1, SFloat::_2);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_90;
    #else
        const float_z ANGLE = SAngle::_HalfPi;
    #endif

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, -SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, -SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_1, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_2, -SFloat::_3);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_3, SFloat::_1);

	// [Execution]
    Quadrilateral result = QUAD.RotateWithPivot(ANGLE, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not rotated when angle is zero.
/// </summary>
ZTEST_CASE ( RotateWithPivot_QuadrilateralIsNotRotatedWhenAngleIsZero_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(-SFloat::_3, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_2, -SFloat::_2);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_5, SFloat::_0);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_2, SFloat::_1);
    const float_z ANGLE = SFloat::_0;

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const Vector2 PIVOT = Vector2(SFloat::_3, SFloat::_1);

	// [Execution]
    Quadrilateral result = QUAD.RotateWithPivot(ANGLE, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_QuadrilateralIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_3, SFloat::_10);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_3, SFloat::_10 + SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, -SFloat::_6);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if Scale is one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the position of the pivot point when the scale equals zero.
/// </summary>
ZTEST_CASE ( ScaleWithPivot1_AllVerticesAreMovedToPositionOfPivotWhenScaleEqualsZero_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that a quadrilateral is correctly scaled.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_QuadrilateralIsCorrectlyScaled_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_6);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_3, SFloat::_10);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_10 + SFloat::_3, SFloat::_10 + SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_3, -SFloat::_6);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_2, SFloat::_4);

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a quadrilateral is not scaled if scale equals one.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_QuadrilateralIsNotScaledIfScaleIsOne_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_4, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2(SFloat::_1, SFloat::_1);

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices are  moved to the position of the pivot point when the scale equals zero.
/// </summary>
ZTEST_CASE ( ScaleWithPivot2_AllVerticesAreMovedToPositionOfPivotWhenScaleEqualsZero_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const Vector2 SCALING_VECTOR = Vector2::GetNullVector();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Quadrilateral result = QUAD.ScaleWithPivot(SCALING_VECTOR.x, SCALING_VECTOR.y, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that a quadrilateral is correctly transformed.
/// </summary>
ZTEST_CASE ( TransformWithPivot_QuadrilateralIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const Vector2 INIT_POS_A = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 INIT_POS_B = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 INIT_POS_C = Vector2(SFloat::_2, SFloat::_6);
    const Vector2 INIT_POS_D = Vector2(SFloat::_0, SFloat::_2);

    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_2, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_0, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_2, SFloat::_3);

    const Quadrilateral QUAD = Quadrilateral(INIT_POS_A, INIT_POS_B, INIT_POS_C, INIT_POS_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    const Quadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION_MATRIX, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that the quadrilateral doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( TransformWithPivot_QuadrilateralDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(-SFloat::_1, SFloat::_9);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(-SFloat::_2, SFloat::_7);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_0, SFloat::_1);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();

    const Quadrilateral QUAD = Quadrilateral(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    const Quadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(result.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(result.C == EXPECTED_VALUE_FOR_C);
    BOOST_CHECK(result.D == EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all the vertices of the quadrilateral are moved to the position of the pivot when transformation is null.
/// </summary>
ZTEST_CASE ( TransformWithPivot_AllVerticesAreMovedToPositionOfPivotWhenTransfomedByZeroMatrix_Test )
{
    // [Preparation]
    const Vector2 POINT_A = Vector2(SFloat::_1, SFloat::_3);
    const Vector2 POINT_B = Vector2(SFloat::_2, SFloat::_4);
    const Vector2 POINT_C = Vector2(SFloat::_7, SFloat::_5);
    const Vector2 POINT_D = Vector2(SFloat::_2, SFloat::_0);

    const TransformationMatrix3x3 TRANSFORMATION = Matrix3x3::GetNullMatrix();

    const Quadrilateral QUAD = Quadrilateral(POINT_A, POINT_B, POINT_C, POINT_D);
    const Vector2 PIVOT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    const Quadrilateral result = QUAD.TransformWithPivot(TRANSFORMATION, PIVOT);

    // [Verification]
    BOOST_CHECK(result.A == PIVOT);
    BOOST_CHECK(result.B == PIVOT);
    BOOST_CHECK(result.C == PIVOT);
    BOOST_CHECK(result.D == PIVOT);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    Quadrilateral QUAD = Quadrilateral(Vector2(SFloat::_0_25, (float_z)-0.000002),
                                         Vector2((float_z)40000.0, SFloat::_0),
                                         Vector2(SFloat::_3, SFloat::_2),
                                         Vector2(SFloat::_1, -SFloat::_0));

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("QL(a(V2(0.25,-1.99999999e-06)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("QL(a(V2(0.25,-1.99999999e-06)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
    #endif
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("QL(a(V2(0.25,-1.9999999999999999e-06)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("QL(a(V2(0.25,-1.9999999999999999e-06)),b(V2(40000,0)),c(V2(3,2)),d(V2(1,-0)))");
    #endif
#endif

	// [Execution]
    Quadrilateral quadrilateralUT = QUAD;
    string_z strStringForm = quadrilateralUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// [TODO] Thund: Protected methods have not been tested yet, they were postponed

// End - Test Suite: Quadrilateral
ZTEST_SUITE_END()
