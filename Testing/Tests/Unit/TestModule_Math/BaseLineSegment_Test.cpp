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

#include "ZMath/BaseLineSegment.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/DataTypes/SVF32.h"

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( BaseLineSegment_TestSuite )

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
    BaseLineSegment<T> lineSegmentUT;

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

    const BaseLineSegment<T> EXPECTED_LINESEGMENT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

	// [Execution]
    BaseLineSegment<T> lineSegmentUT(EXPECTED_LINESEGMENT);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);

	// [Execution]
    BaseLineSegment<T> lineSegmentUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B);

    // [Verification]
    BOOST_CHECK(lineSegmentUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(lineSegmentUT.B == EXPECTED_VALUE_FOR_B);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5));
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND =  BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseLineSegment<T> LEFT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseLineSegment<T> RIGHT_OPERAND = BaseLineSegment<T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseLineSegment
ZTEST_SUITE_END()
