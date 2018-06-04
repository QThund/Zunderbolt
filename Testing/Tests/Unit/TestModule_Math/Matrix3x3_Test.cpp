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

#include "ZMath/Matrix3x3.h"

#include "ZMath/Matrix3x4.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/Exceptions/AssertException.h"

ZTEST_SUITE_BEGIN( Matrix3x3_TestSuite )


/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_EveryElementIsMultipliedByTheScalar_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_9);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)14.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)18.0;

    const float_z SCALAR_VALUE = SFloat::_2;

    // [Execution]
    Matrix3x3 matrixUT = SCALAR_VALUE * MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks if copy constructor copies every matrix element properly.
/// </summary>
ZTEST_CASE ( Constructor2_EveryMatrixElementCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;

    const Matrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                    EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                    EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    // [Execution]
    Matrix3x3 matrixUT = MATRIX_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
ZTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // [Preparation]
    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    Matrix3x3 matrixUT(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks if the value provided is set to all the matrix components.
/// </summary>
ZTEST_CASE ( Constructor4_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

    // [Execution]
    Matrix3x3 matrixUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if values used as parameters are properly set to matrix components.
/// </summary>
ZTEST_CASE ( Constructor5_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;

	// [Execution]
    Matrix3x3 matrixUT(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks if the matrix components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor6_MatrixComponentsAreFilledWithValidReferenceTo9Floats_Test )
{
   // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;


    float_z* VALID_ARRAY_OF_9_FLOATS = new float_z[9];
    VALID_ARRAY_OF_9_FLOATS[0] = EXPECTED_VALUE_FOR_00;
    VALID_ARRAY_OF_9_FLOATS[1] = EXPECTED_VALUE_FOR_01;
    VALID_ARRAY_OF_9_FLOATS[2] = EXPECTED_VALUE_FOR_02;
    VALID_ARRAY_OF_9_FLOATS[3] = EXPECTED_VALUE_FOR_10;
    VALID_ARRAY_OF_9_FLOATS[4] = EXPECTED_VALUE_FOR_11;
    VALID_ARRAY_OF_9_FLOATS[5] = EXPECTED_VALUE_FOR_12;
    VALID_ARRAY_OF_9_FLOATS[6] = EXPECTED_VALUE_FOR_20;
    VALID_ARRAY_OF_9_FLOATS[7] = EXPECTED_VALUE_FOR_21;
    VALID_ARRAY_OF_9_FLOATS[8] = EXPECTED_VALUE_FOR_22;

	// [Execution]
    Matrix3x3 matrixUT(VALID_ARRAY_OF_9_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);

    // Cleaning
    delete [] VALID_ARRAY_OF_9_FLOATS;
    VALID_ARRAY_OF_9_FLOATS = null_z;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_z* NULL_ARRAY = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Matrix3x3 vMatrixUT(NULL_ARRAY);
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
ZTEST_CASE ( Constructor7_MatrixComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;


	vf32_z PACK0, PACK1, PACK2;
	SVF32::Pack(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, SFloat::_0, PACK0);
	SVF32::Pack(EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, SFloat::_0, PACK1);
	SVF32::Pack(EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, SFloat::_0, PACK2);

	// [Execution]
	Matrix3x3 matrixUT(PACK0, PACK1, PACK2);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero.
/// </summary>
ZTEST_CASE ( GetNullMatrix_AllElementsEqualZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

	// [Execution]
    Matrix3x3 matrixUT = Matrix3x3::GetNullMatrix();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
ZTEST_CASE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DIAGONAL = SFloat::_1;

	// [Execution]
    Matrix3x3 matrixUT = Matrix3x3::GetIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks if the equility operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Matrix3x3 LEFT_OPERAND(SFloat::Epsilon);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equility operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z HALF_TOLERANCE = SFloat::Epsilon * SFloat::_0_5;

    const Matrix3x3 LEFT_OPERAND(HALF_TOLERANCE);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the equility operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z ONE_AND_A_HALF_TOLERANCE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;

    const Matrix3x3 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the equility operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Matrix3x3 LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,
                                      SFloat::_4, SFloat::_5, SFloat::_6,
                                      SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 RIGHT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,
                                       SFloat::_4, SFloat::_5, SFloat::_6,
                                       SFloat::_7, SFloat::_8, SFloat::_9);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Matrix3x3 LEFT_OPERAND(SFloat::Epsilon);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

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
    const Matrix3x3 LEFT_OPERAND(HALF_TOLERANCE);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

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

    const Matrix3x3 LEFT_OPERAND(ONE_AND_A_HALF_TOLERANCE);
    const Matrix3x3 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the inequality operator returns false when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Matrix3x3 LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,
                                      SFloat::_4, SFloat::_5, SFloat::_6,
                                      SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 RIGHT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,
                                       SFloat::_4, SFloat::_5, SFloat::_6,
                                       SFloat::_7, SFloat::_8, SFloat::_9);
	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND));
}

/// <summary>
/// Checks if every element of the matrix is correctly multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct1_EveryElementIsMultipliedByTheScalar_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_9);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)14.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)18.0;

    const float_z SCALAR_VALUE = SFloat::_2;

    // [Execution]
    Matrix3x3 matrixUT = MATRIX * SCALAR_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                              SFloat::_4, SFloat::_5, SFloat::_6,
                              SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)84.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)90.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)96.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)201.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)216.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)231.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)318.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)342.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)366.0;

    // [Execution]
    Matrix3x3 matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct2_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                              SFloat::_4, SFloat::_5, SFloat::_6,
                              SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                              (float_z)13.0, (float_z)14.0, (float_z)15.0,
                              (float_z)16.0, (float_z)17.0, (float_z)18.0);

    // [Execution]
    Matrix3x3 matrix1UT = OPERAND1 * OPERAND2;
    Matrix3x3 matrix2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                              SFloat::_4, SFloat::_5, SFloat::_6,
                              SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x4 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0, (float_z)13.0,
                                  (float_z)14.0, (float_z)15.0, (float_z)16.0, (float_z)17.0,
                                  (float_z)18.0, (float_z)19.0, (float_z)20.0, (float_z)21.0);

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)92.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)98.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)104.0;
    const float_z EXPECTED_VALUE_FOR_03 = (float_z)110.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)218.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)233.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)248.0;
    const float_z EXPECTED_VALUE_FOR_13 = (float_z)263.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)344.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)368.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)392.0;
    const float_z EXPECTED_VALUE_FOR_23 = (float_z)416.0;

    // [Execution]
    Matrix3x4 matrixUT = OPERAND1 * OPERAND2;

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
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision_EveryElementIsDividedByTheScalar_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_2,    SFloat::_4,    SFloat::_6,
                            SFloat::_8,    SFloat::_10,   (float_z)12.0,
                            (float_z)14.0, (float_z)16.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;

    const float_z SCALAR_VALUE = SFloat::_2;

    // [Execution]
    Matrix3x3 matrixUT = MATRIX / SCALAR_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivision_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const float_z ZERO_SCALAR = SFloat::_0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Matrix3x3 vMatrixUT;
        vMatrixUT / ZERO_SCALAR;
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
/// Checks that two common matrices are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition_CommonMatricesAreCorrectlyAdded_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                              SFloat::_4, SFloat::_5, SFloat::_6,
                              SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)11.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)13.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)15.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)17.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)19.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)21.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)23.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)25.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)27.0;

    // [Execution]
    Matrix3x3 matrixUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that two common matrices are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_CommonMatricesAreCorrectlySubtracted_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1((float_z)11.0, (float_z)13.0, (float_z)15.0,
                              (float_z)17.0, (float_z)19.0, (float_z)21.0,
                              (float_z)23.0, (float_z)25.0, (float_z)27.0);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                    SFloat::_4, SFloat::_5, SFloat::_6,
                                    SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    Matrix3x3 matrixUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                                  SFloat::_4, SFloat::_5, SFloat::_6,
                                  SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)84.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)90.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)96.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)201.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)216.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)231.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)318.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)342.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)366.0;

    // [Execution]
    Matrix3x3 matrixUT(OPERAND1);
    matrixUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_ProductIsNotCommutative_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                                  SFloat::_4, SFloat::_5, SFloat::_6,
                                  SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    // [Execution]
    Matrix3x3 matrix1UT(OPERAND1);
    matrix1UT *= OPERAND2;
    Matrix3x3 matrix2UT(OPERAND2);
    matrix2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const Matrix3x3 OPERAND(SFloat::_1, SFloat::_2, SFloat::_3,
                             SFloat::_4, SFloat::_5, SFloat::_6,
                             SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 EXPECTED_VALUE = OPERAND * OPERAND;

	// [Execution]
    Matrix3x3 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // [Verification]
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if all the elements of the matrix are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_MatrixIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_9);

    const float_z  SCALAR = SFloat::_2;

    const Matrix3x3 EXPECTED_VALUE(SFloat::_2,    SFloat::_4,    SFloat::_6,
                                    SFloat::_8,    SFloat::_10,   (float_z)12.0,
                                    (float_z)14.0, (float_z)16.0, (float_z)18.0);

	// [Execution]
    Matrix3x3 matrixUT = MATRIX;
    matrixUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that a matrix element is multiplied and assigned to itself.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_MatrixIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX((float_z)0.9, SFloat::_1,    SFloat::_2,
                            (float_z)0.3, SFloat::_7,    SFloat::_0_5,
                            SFloat::_4,   (float_z)0.02, SFloat::_3);

    Matrix3x3 EXPECTED_VALUE((float_z)0.9, SFloat::_1,    SFloat::_2,
                            (float_z)0.3, SFloat::_7,    SFloat::_0_5,
                            SFloat::_4,   (float_z)0.02, SFloat::_3);

    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[0][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[1][2];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][0];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][1];
    EXPECTED_VALUE = EXPECTED_VALUE * EXPECTED_VALUE.ij[2][2];

	// [Execution]
    Matrix3x3 matrixUT = MATRIX;
    matrixUT *= matrixUT.ij[0][0];
    matrixUT *= matrixUT.ij[0][1];
    matrixUT *= matrixUT.ij[0][2];
    matrixUT *= matrixUT.ij[1][0];
    matrixUT *= matrixUT.ij[1][1];
    matrixUT *= matrixUT.ij[1][2];
    matrixUT *= matrixUT.ij[2][0];
    matrixUT *= matrixUT.ij[2][1];
    matrixUT *= matrixUT.ij[2][2];

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks if every element of the matrix is correctly divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_EveryElementIsDividedByTheScalar_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_2,    SFloat::_4,    SFloat::_6,
                            SFloat::_8,    SFloat::_10,   (float_z)12.0,
                            (float_z)14.0, (float_z)16.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_22 = SFloat::_9;

    const float_z SCALAR_VALUE = SFloat::_2;

    // [Execution]
    Matrix3x3 matrixUT = MATRIX;
    matrixUT /= SCALAR_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that a matrix element is divided and assigned to itself.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_MatrixIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_2,    SFloat::_4,    SFloat::_6,
                            SFloat::_8,    SFloat::_10,   (float_z)12.0,
                            (float_z)14.0, (float_z)16.0, (float_z)18.0);

    Matrix3x3 EXPECTED_VALUE(SFloat::_2,    SFloat::_4,    SFloat::_6,
                              SFloat::_8,    SFloat::_10,   (float_z)12.0,
                              (float_z)14.0, (float_z)16.0, (float_z)18.0);

    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[0][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[1][2];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][0];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][1];
    EXPECTED_VALUE = EXPECTED_VALUE / EXPECTED_VALUE.ij[2][2];

	// [Execution]
    Matrix3x3 matrixUT = MATRIX;
    matrixUT /= matrixUT.ij[0][0];
    matrixUT /= matrixUT.ij[0][1];
    matrixUT /= matrixUT.ij[0][2];
    matrixUT /= matrixUT.ij[1][0];
    matrixUT /= matrixUT.ij[1][1];
    matrixUT /= matrixUT.ij[1][2];
    matrixUT /= matrixUT.ij[2][0];
    matrixUT /= matrixUT.ij[2][1];
    matrixUT /= matrixUT.ij[2][2];

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when the scalar equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const float_z ZERO_SCALAR = SFloat::_0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Matrix3x3 vMatrixUT;
        vMatrixUT /= ZERO_SCALAR;
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
/// Checks that two common matrices are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_CommonMatricesAreCorrectlyAdded_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3,
                              SFloat::_4, SFloat::_5, SFloat::_6,
                              SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)11.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)13.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)15.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)17.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)19.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)21.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)23.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)25.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)27.0;

    // [Execution]
    Matrix3x3 matrixUT = OPERAND1;
    matrixUT += OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22);
}

/// <summary>
/// Checks that two common matrices are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_CommonMatricesAreCorrectlySubtracted_Test )
{
    // [Preparation]

    const Matrix3x3 OPERAND1((float_z)11.0, (float_z)13.0, (float_z)15.0,
                              (float_z)17.0, (float_z)19.0, (float_z)21.0,
                              (float_z)23.0, (float_z)25.0, (float_z)27.0);

    const Matrix3x3 OPERAND2((float_z)10.0, (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                  (float_z)16.0, (float_z)17.0, (float_z)18.0);

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                    SFloat::_4, SFloat::_5, SFloat::_6,
                                    SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    Matrix3x3 matrixUT = OPERAND1;
    matrixUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
ZTEST_CASE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test )
{
    // [Preparation]

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    Matrix3x3 matrixUT;
    matrixUT = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that every element of the matrix equals zero.
/// </summary>
ZTEST_CASE ( ResetToZero_AllElementsEqualZero_Test )
{
    // [Preparation]

    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                                SFloat::_4, SFloat::_5, SFloat::_6,
                                SFloat::_7, SFloat::_8, SFloat::_9);

    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    // [Execution]
    Matrix3x3 matrixUT(MATRIX);
    matrixUT.ResetToZero();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that every element of the matrix equals zero but diagonal's, which equal one.
/// </summary>
ZTEST_CASE ( ResetToIdentity_AllElementsEqualZeroButDiagonalThatEqualsOne_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_9);

    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DIAGONAL = SFloat::_1;

    // [Execution]
    Matrix3x3 matrixUT(MATRIX);
    matrixUT.ResetToIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_DIAGONAL);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_DIAGONAL);
}

/// <summary>
/// Checks that every element that occupies the position ij, now is at the position ji.
/// </summary>
ZTEST_CASE ( Transpose_TheRowAndColumOfElementsAreSwapped_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_9);

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_4, SFloat::_7,
                                    SFloat::_2, SFloat::_5, SFloat::_8,
                                    SFloat::_3, SFloat::_6, SFloat::_9);

    // [Execution]
    Matrix3x3 matrixUT = MATRIX.Transpose();

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero.
/// </summary>
ZTEST_CASE ( IsZero_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // [Preparation]
    const Matrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    Matrix3x3 matrixUT = NULL_MATRIX;
    bool bResult = matrixUT.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when not all the matrix elements equal zero.
/// </summary>
ZTEST_CASE ( IsZero_ReturnsFalseWhenNotAllElementsEqualZero_Test )
{
    // [Preparation]
    const Matrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    Matrix3x3 matrixUT = NULL_MATRIX;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][0] = SFloat::_0;
    matrixUT.ij[0][1] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][1] = SFloat::_0;
    matrixUT.ij[0][2] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[0][2] = SFloat::_0;
    matrixUT.ij[1][0] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][0] = SFloat::_0;
    matrixUT.ij[1][1] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][1] = SFloat::_0;
    matrixUT.ij[1][2] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[1][2] = SFloat::_0;
    matrixUT.ij[2][0] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][0] = SFloat::_0;
    matrixUT.ij[2][1] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();    matrixUT.ij[2][1] = SFloat::_0;
    matrixUT.ij[2][2] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns True when all the matrix elements equal zero but the diagonal's, which equal one.
/// </summary>
ZTEST_CASE ( IsIdentity_ReturnsTrueWhenAllElementsEqualZero_Test )
{
    // [Preparation]
    const Matrix3x3 IDENTITY = Matrix3x3::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    Matrix3x3 matrixUT = IDENTITY;
    bool bResult = matrixUT.IsIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the matrix is not an identity matrix.
/// </summary>
ZTEST_CASE ( IsIdentity_ReturnsFalseWhenItsNotIdentity_Test )
{
    // [Preparation]
    const Matrix3x3 IDENTITY = Matrix3x3::GetIdentity();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    Matrix3x3 matrixUT = IDENTITY;
    bool bAtLeastOneReturnsTrue = false;

    matrixUT.ij[0][0] = SFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][0] = SFloat::_1;
    matrixUT.ij[0][1] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][1] = SFloat::_0;
    matrixUT.ij[0][2] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[0][2] = SFloat::_0;
    matrixUT.ij[1][0] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][0] = SFloat::_0;
    matrixUT.ij[1][1] = SFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][1] = SFloat::_1;
    matrixUT.ij[1][2] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[1][2] = SFloat::_0;
    matrixUT.ij[2][0] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][0] = SFloat::_0;
    matrixUT.ij[2][1] = SFloat::_1;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();    matrixUT.ij[2][1] = SFloat::_0;
    matrixUT.ij[2][2] = SFloat::_0;    bAtLeastOneReturnsTrue |= matrixUT.IsIdentity();

    // [Verification]
    BOOST_CHECK_EQUAL(bAtLeastOneReturnsTrue, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of a common matrix is correctly obtained.
/// </summary>
ZTEST_CASE ( GetDeterminant_ItsCorrectlyCalculatedForCommonMatrix_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_0);

    const float_z EXPECTED_VALUE = (float_z)27.0;

    // [Execution]
    float_z fResultUT = MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the identity equals one.
/// </summary>
ZTEST_CASE ( GetDeterminant_DeterminantOfIdentityEqualsOne_Test )
{
    // [Preparation]
    const Matrix3x3 IDENTITY = Matrix3x3::GetIdentity();
    const float_z EXPECTED_VALUE = SFloat::_1;

    // [Execution]
    float_z fResultUT = IDENTITY.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the zero matrix equals zero.
/// </summary>
ZTEST_CASE ( GetDeterminant_DeterminantOfZeroMatrixEqualsZero_Test )
{
    // [Preparation]
    const Matrix3x3 NULL_MATRIX = Matrix3x3::GetNullMatrix();
    const float_z EXPECTED_VALUE = SFloat::_0;

    // [Execution]
    float_z fResultUT = NULL_MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common matrix is correctly inverted.
/// </summary>
ZTEST_CASE ( Invert_CommonMatrixIsCorrectlyInverted_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_1, SFloat::_2, SFloat::_3,
                            SFloat::_4, SFloat::_5, SFloat::_6,
                            SFloat::_7, SFloat::_8, SFloat::_0);

    const Matrix3x3 EXPECTED_VALUE((float_z)-1.7777777777777777,  (float_z)0.88888888888888884,  (float_z)-0.11111111111111110,
                                    (float_z)1.5555555555555554,   (float_z)-0.77777777777777768, (float_z)0.22222222222222221,
                                    (float_z)-0.1111111111111111, (float_z)0.22222222222222221,  (float_z)-0.1111111111111111);

    // [Execution]
    Matrix3x3 matrixUT = MATRIX.Invert();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
}

/// <summary>
/// Checks that it returns True when the determinant of the matrix doesn't equal zero.
/// </summary>
ZTEST_CASE ( HasInverse_ReturnsTrueWhenDeterminantIsNotZero_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX = Matrix3x3::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the determinant of the matrix equals zero.
/// </summary>
ZTEST_CASE ( HasInverse_ReturnsFalseWhenDeterminantIsZero_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX = Matrix3x3::GetNullMatrix();
    const bool EXPECTED_VALUE = false;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const Matrix3x3 MATRIX(SFloat::_0,    SFloat::_1,    (float_z)0.654321,
                            SFloat::_4,    SFloat::_5,    (float_z)-2.2,
                            SFloat::_8,    SFloat::_9,    (float_z)123456.0);
    #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
        const string_z EXPECTED_STRING_FORM = Z_L("M3x3(0,1,0.654321015,4,5,-2.20000005,8,9,123456)");
    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
        const string_z EXPECTED_STRING_FORM = Z_L("M3x3(0,1,0.65432100000000004,4,5,-2.2000000000000002,8,9,123456)");
    #endif

	// [Execution]
    Matrix3x3 matrixUT = MATRIX;
    string_z strStringForm = matrixUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}


// End - Test Suite: Matrix3x3
ZTEST_SUITE_END()
