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

#include "ZMath/BasePlane.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( BasePlane_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_0;

	// [Execution]
    BasePlane planeUT;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if copy constructor sets plane's components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const BasePlane PLANE_TO_COPY(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    BasePlane planeUT = PLANE_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if values used as parameters are properly set to plane's components.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

	// [Execution]
    BasePlane planeUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if the value provided is set to all the plane's components.
/// </summary>
ZTEST_CASE ( Constructor4_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

	// [Execution]
    BasePlane planeUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if the plane's components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor5_VectorComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    float_z* VALID_ARRAY_OF_4_FLOATS = new float_z[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_A;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_B;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_C;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_D;

	// [Execution]
    BasePlane planeUT(VALID_ARRAY_OF_4_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, VALID_ARRAY_OF_4_FLOATS[0]);
    BOOST_CHECK_EQUAL(planeUT.b, VALID_ARRAY_OF_4_FLOATS[1]);
    BOOST_CHECK_EQUAL(planeUT.c, VALID_ARRAY_OF_4_FLOATS[2]);
    BOOST_CHECK_EQUAL(planeUT.d, VALID_ARRAY_OF_4_FLOATS[3]);

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor5_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_z* NULL_ARRAY = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        BasePlane planeUT(NULL_ARRAY);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if plane's components are set to the correct values packed in a valid vf32 object.
/// </summary>
ZTEST_CASE ( Constructor6_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

	vf32_z PACK;
	SVF32::Pack(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D, PACK);

	// [Execution]
	BasePlane planeUT(PACK);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon);
    const BasePlane RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that when operators are similar but not equal (geometrically speaking), they are considered different.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperatorsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_10);
    const BasePlane RIGHT_OPERAND(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_5); // LEFT_OPERAND / 2

	// [Execution] / Verification
    BOOST_CHECK(!(LEFT_OPERAND == RIGHT_OPERAND));
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const BasePlane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::Epsilon);
    const BasePlane RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that when operators are similar but not equal (geometrically speaking), they are considered different.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperatorsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const BasePlane LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_10);
    const BasePlane RIGHT_OPERAND(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_5); // LEFT_OPERAND / 2

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

// End - Test Suite: BasePlane
ZTEST_SUITE_END()
