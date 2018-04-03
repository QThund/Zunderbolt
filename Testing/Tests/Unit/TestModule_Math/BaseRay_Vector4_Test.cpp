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

// !!!
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the BaseRay_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/BaseRay.h"
#include "ZMath/Vector4.h"
#include "ZMath/Vector3.h"


ZTEST_SUITE_BEGIN( BaseRay_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const Vector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    BaseRay<Vector4, Vector3> rayUT;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const Vector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    BaseRay<Vector4, Vector3> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    BaseRay<Vector4, Vector3> rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreSetProperly_Test )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const Vector4 EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    BaseRay<Vector4, Vector3> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
ZTEST_CASE ( Constructor3_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };

    const Vector4 INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const Vector3 INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const Vector4 UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const Vector3 UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    BaseRay<Vector4, Vector3> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::_0), Vector3(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), Vector3(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5));
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::_0), Vector3(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), Vector3(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::_0), Vector3(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) * SFloat::_3 ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK( !(LEFT_OPERAND == RIGHT_OPERAND) );
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND =  BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), Vector3(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), Vector3(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::_0), Vector3(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const BaseRay<Vector4, Vector3> LEFT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon) );
    const BaseRay<Vector4, Vector3> RIGHT_OPERAND = BaseRay<Vector4, Vector3>( Vector4(SFloat::Epsilon), Vector3(SFloat::Epsilon * SFloat::_3) ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

// End - Test Suite: BaseRay
ZTEST_SUITE_END()
