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

#include "ZMath/BaseMatrix4x4.h"

#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( BaseMatrix4x4_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    BaseMatrix4x4 matrixUT;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// Checks if copy constructor copies every matrix element properly.
/// </summary>
ZTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_03 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_13 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_10+SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_23 = SFloat::_10+SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_30 = SFloat::_10+SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_31 = SFloat::_10+SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_32 = SFloat::_10+SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_33 = SFloat::_10+SFloat::_6;

    const BaseMatrix4x4 MATRIX_TO_COPY(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                                        EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    // [Execution]
    BaseMatrix4x4 matrixUT = MATRIX_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks if the value provided is set to all the matrix components.
/// </summary>
ZTEST_CASE ( Constructor3_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

    BaseMatrix4x4 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
   // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_03 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_13 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_10+SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_23 = SFloat::_10+SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_30 = SFloat::_10+SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_31 = SFloat::_10+SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_32 = SFloat::_10+SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_33 = SFloat::_10+SFloat::_6;

	// [Execution]
    BaseMatrix4x4 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                            EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                            EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                            EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor5_MatrixComponentsAreFilledWithValidReferenceTo16Floats_Test )
{
   // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_03 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_13 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_10 + SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_23 = SFloat::_10 + SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_30 = SFloat::_10 + SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_31 = SFloat::_10 + SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_32 = SFloat::_10 + SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_33 = SFloat::_10 + SFloat::_6;


    float_z* VALID_ARRAY_OF_16_FLOATS = new float_z[16];
    VALID_ARRAY_OF_16_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_16_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_16_FLOATS[2] = EXPECTED_VALUE_FOR_02;
    VALID_ARRAY_OF_16_FLOATS[3] = EXPECTED_VALUE_FOR_03;
    VALID_ARRAY_OF_16_FLOATS[4] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_16_FLOATS[5] = EXPECTED_VALUE_FOR_11;
    VALID_ARRAY_OF_16_FLOATS[6] = EXPECTED_VALUE_FOR_12;
    VALID_ARRAY_OF_16_FLOATS[7] = EXPECTED_VALUE_FOR_13;
    VALID_ARRAY_OF_16_FLOATS[8] = EXPECTED_VALUE_FOR_20;
    VALID_ARRAY_OF_16_FLOATS[9] = EXPECTED_VALUE_FOR_21;
    VALID_ARRAY_OF_16_FLOATS[10] = EXPECTED_VALUE_FOR_22;
    VALID_ARRAY_OF_16_FLOATS[11] = EXPECTED_VALUE_FOR_23;
    VALID_ARRAY_OF_16_FLOATS[12] = EXPECTED_VALUE_FOR_30;
    VALID_ARRAY_OF_16_FLOATS[13] = EXPECTED_VALUE_FOR_31;
    VALID_ARRAY_OF_16_FLOATS[14] = EXPECTED_VALUE_FOR_32;
    VALID_ARRAY_OF_16_FLOATS[15] = EXPECTED_VALUE_FOR_33;

	// [Execution]
    BaseMatrix4x4 matrixUT(VALID_ARRAY_OF_16_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);

    // Cleanup
    delete [] VALID_ARRAY_OF_16_FLOATS;
    VALID_ARRAY_OF_16_FLOATS = null_z;
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
        BaseMatrix4x4 vMatrixUT(NULL_ARRAY);
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
/// Checks if matrix components are set to the correct values packed in valid vf32 objects.
/// </summary>
ZTEST_CASE ( Constructor6_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_03 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_13 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_10 + SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_23 = SFloat::_10 + SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_30 = SFloat::_10 + SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_31 = SFloat::_10 + SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_32 = SFloat::_10 + SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_33 = SFloat::_10 + SFloat::_6;


	vf32_z PACK0, PACK1, PACK2, PACK3;
	SVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03, PACK0);
	SVF32::Pack(EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13, PACK1);
	SVF32::Pack(EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23, PACK2);
	SVF32::Pack(EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33, PACK3);

	// [Execution]
	BaseMatrix4x4 matrixUT(PACK0, PACK1, PACK2, PACK3);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE_FOR_03);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE_FOR_13);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE_FOR_23);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE_FOR_30);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE_FOR_31);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE_FOR_32);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE_FOR_33);
}

/// <summary>
/// Checks if the equality operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseMatrix4x4 LEFT_OPERAND(SFloat::Epsilon);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equality operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z HALF_TOLERANCE = SFloat::Epsilon * SFloat::_0_5;

    const BaseMatrix4x4 LEFT_OPERAND(HALF_TOLERANCE);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equality operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z ONE_AND_A_HALF_TOLERANCE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;

    const BaseMatrix4x4 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the equality operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseMatrix4x4 LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,SFloat::_4,
                                      SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8,
                                      SFloat::_9, SFloat::_10, SFloat::_10 + SFloat::_1, SFloat::_10 + SFloat::_2,
                                      SFloat::_10+ SFloat::_3, SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_5, SFloat::_10 + SFloat::_6);

    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,SFloat::_4,
                                       SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8,
                                       SFloat::_9, SFloat::_10, SFloat::_10 + SFloat::_1, SFloat::_10 + SFloat::_2,
                                       SFloat::_10+ SFloat::_3, SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_5, SFloat::_10 + SFloat::_6);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseMatrix4x4 LEFT_OPERAND(SFloat::Epsilon);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the inequality operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    const float_z HALF_TOLERANCE = SFloat::Epsilon * SFloat::_0_5;

   // [Preparation]
    const BaseMatrix4x4 LEFT_OPERAND(HALF_TOLERANCE);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the inequality operator returns true when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z ONE_AND_A_HALF_TOLERANCE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;

    const BaseMatrix4x4 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseMatrix4x4 LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,SFloat::_4,
                                      SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8,
                                      SFloat::_9, SFloat::_10, SFloat::_10 + SFloat::_1, SFloat::_10 + SFloat::_2,
                                      SFloat::_10+ SFloat::_3, SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_5, SFloat::_10 + SFloat::_6);

    const BaseMatrix4x4 RIGHT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,SFloat::_4,
                                       SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8,
                                       SFloat::_9, SFloat::_10, SFloat::_10 + SFloat::_1, SFloat::_10 + SFloat::_2,
                                       SFloat::_10+ SFloat::_3, SFloat::_10 + SFloat::_4, SFloat::_10 + SFloat::_5, SFloat::_10 + SFloat::_6);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND));
}

// End - Test Suite: BaseMatrix4x4
ZTEST_SUITE_END()
