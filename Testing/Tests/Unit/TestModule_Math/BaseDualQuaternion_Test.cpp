
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

#include "ZMath/BaseDualQuaternion.h"

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"


ZTEST_SUITE_BEGIN( BaseDualQuaternion_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;

    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    BaseDualQuaternion dualQuaternionUT;

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);

    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks if copy constructor sets dual quaternion components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const Quaternion EXPECTED_VALUE_D = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_VALUE_R = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

    const BaseDualQuaternion DQUAT_TO_COPY(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

	// [Execution]
    BaseDualQuaternion dualQuaternionUT = DQUAT_TO_COPY;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks that every value is set to correct quaternion.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const Quaternion EXPECTED_VALUE_D = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_VALUE_R = Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

	// [Execution]
    BaseDualQuaternion dualQuaternionUT(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

    // [Verification]
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon),
                                          Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                          Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                          Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));
	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon),
                                          Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon),
                                           Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon),
                                          Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                          Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS),
                                          Quaternion(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseDualQuaternion LEFT_OPERAND(Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon),
                                          Quaternion(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon));
    const BaseDualQuaternion RIGHT_OPERAND(Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                           Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseDualQuaternion
ZTEST_SUITE_END()
