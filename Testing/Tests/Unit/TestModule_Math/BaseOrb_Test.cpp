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

#include "ZMath/BaseOrb.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( BaseOrb_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    BaseOrb<T> orbUT;

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's point and radius properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

    const BaseOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    BaseOrb<T> orbUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

	// [Execution]
    BaseOrb<T> orbUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T::GetNullVector(), SFloat::_0 );
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T::GetNullVector(), SFloat::_0 );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T::GetNullVector(), SFloat::_0 );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T::GetNullVector(), SFloat::_0 );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND =  BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5 );
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T::GetNullVector(), SFloat::_0 );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseOrb<T> LEFT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );
    const BaseOrb<T> RIGHT_OPERAND = BaseOrb<T>( T(SFloat::Epsilon), SFloat::Epsilon );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseOrb
ZTEST_SUITE_END()
