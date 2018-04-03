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

#include "ZMath/BaseQuadrilateral.h"

#include "ZMath/Vector2.h"
#include "ZCommon/DataTypes/SFloat.h"


ZTEST_SUITE_BEGIN( BaseQuadrilateral_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    
    // [Execution]
    BaseQuadrilateral quadrilateralUT;
    
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
    
    const BaseQuadrilateral QUAD_TO_COPY = BaseQuadrilateral(EXPECTED_VALUE_FOR_A,
                                                               EXPECTED_VALUE_FOR_B,
                                                               EXPECTED_VALUE_FOR_C, 
                                                               EXPECTED_VALUE_FOR_D);

    // [Execution]
    BaseQuadrilateral quadrilateralUT = QUAD_TO_COPY;
    
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
ZTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
	// [Preparation]
    const Vector2 EXPECTED_VALUE_FOR_A = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 EXPECTED_VALUE_FOR_B = Vector2(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_VALUE_FOR_C = Vector2(SFloat::_4, SFloat::_5);
    const Vector2 EXPECTED_VALUE_FOR_D = Vector2(SFloat::_6, SFloat::_7);
    
    // [Execution]
    BaseQuadrilateral quadrilateralUT = BaseQuadrilateral(EXPECTED_VALUE_FOR_A,
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
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon), 
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon), 
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0), 
                                                                Vector2(SFloat::_0, SFloat::_0), 
                                                                Vector2(SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5), 
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5), 
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5), 
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0), 
                                                                Vector2(SFloat::_0, SFloat::_0), 
                                                                Vector2(SFloat::_0, SFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), 
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!(LEFT_OPERAND == RIGHT_OPERAND));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon * SFloat::_0_5));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5),
                                                               Vector2(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5,
                                                                        SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0),
                                                                Vector2(SFloat::_0, SFloat::_0));

    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseQuadrilateral LEFT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                               Vector2(SFloat::Epsilon, SFloat::Epsilon));

    const BaseQuadrilateral RIGHT_OPERAND = BaseQuadrilateral(Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon),
                                                                Vector2(SFloat::Epsilon, SFloat::Epsilon));

    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseQuadrilateral
ZTEST_SUITE_END()
