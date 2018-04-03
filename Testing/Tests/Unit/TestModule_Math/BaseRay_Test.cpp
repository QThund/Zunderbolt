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
// IMPORTANT NOTE: Whatever the test you modify in this file, replicate the same changes in the BaseRay_Vector4_Test.cpp file!
//                 They had to be split because the template has 2 parameters that are not assured to be the same type.
// !!!

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/BaseRay.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"

typedef boost::mpl::list<Vector2, Vector3> TTemplateTypes;


ZTEST_SUITE_BEGIN( BaseRay_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    BaseRay<T, T> rayUT;

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if copy constructor sets ray's components properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    BaseRay<T, T> EXPECTED_RAY(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

	// [Execution]
    BaseRay<T, T> rayUT(EXPECTED_RAY);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_RAY.Origin);
    BOOST_CHECK(rayUT.Direction == EXPECTED_RAY.Direction);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6 };

    const T EXPECTED_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T EXPECTED_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

	// [Execution]
    BaseRay<T, T> rayUT(EXPECTED_VALUE_FOR_ORIGIN, EXPECTED_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin == EXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction == EXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks that the result is not normalized if the direction vector is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ConstructedRayIsNotNormalizedWhenDirectionVectorIsNot_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_ORIGIN[] = { SFloat::_1, SFloat::_2, SFloat::_3 };
    float_z VECTOR_COMPONENTS_DIRECTION[] = { SFloat::_4, SFloat::_5, SFloat::_6 };

    const T INPUT_VALUE_FOR_ORIGIN(VECTOR_COMPONENTS_ORIGIN);
    const T INPUT_VALUE_FOR_DIRECTION(VECTOR_COMPONENTS_DIRECTION);

    const T UNEXPECTED_VALUE_FOR_ORIGIN = INPUT_VALUE_FOR_ORIGIN.Normalize();
    const T UNEXPECTED_VALUE_FOR_DIRECTION = INPUT_VALUE_FOR_DIRECTION.Normalize();

	// [Execution]
    BaseRay<T, T> rayUT(INPUT_VALUE_FOR_ORIGIN, INPUT_VALUE_FOR_DIRECTION);

    // [Verification]
    BOOST_CHECK(rayUT.Origin != UNEXPECTED_VALUE_FOR_ORIGIN);
    BOOST_CHECK(rayUT.Direction != UNEXPECTED_VALUE_FOR_DIRECTION);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::_0), T(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5));
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::_0), T(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::_0), T(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsAreSimilarButNotEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) * SFloat::_3 ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK( !(LEFT_OPERAND == RIGHT_OPERAND) );
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND =  BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::_0), T(SFloat::_0) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that two similar rays are considered different.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsAreSimilarButNotEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseRay<T, T> LEFT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseRay<T, T> RIGHT_OPERAND = BaseRay<T, T>( T(SFloat::Epsilon), T(SFloat::Epsilon * SFloat::_3) ); // LEFT_OPERAND's direction x3

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

// End - Test Suite: BaseRay
ZTEST_SUITE_END()
