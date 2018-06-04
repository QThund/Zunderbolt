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

#include "ZMath/Vector2.h"

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/SAngle.h"
#include "ZMath/Matrix2x2.h"
#include "ZMath/Matrix3x3.h"
#include "ZMath/TransformationMatrix3x3.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( Vector2_TestSuite )

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector2 vVectorUT = SCALAR * VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if copy constructor sets vector components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 VECTOR_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

	// [Execution]
    Vector2 vVectorUT = VECTOR_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if every input vector's component is copied to the right target vector's component.
/// </summary>
ZTEST_CASE ( Constructor3_VectorComponentsAreCopiedToRightComponents_Test )
{
    // [Preparation]

    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    Vector2 BASEVECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

	// [Execution]
    Vector2 vVectorUT(BASEVECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if values used as parameters are properly set to vector components.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

	// [Execution]
    Vector2 vVectorUT(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if the value provided is set to all the vector components.
/// </summary>
ZTEST_CASE ( Constructor5_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

	// [Execution]
    Vector2 vVectorUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if the vector components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor6_VectorComponentsAreFilledWithValidReferenceTo2Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    float_z* VALID_ARRAY_OF_2_FLOATS = new float_z[2];
    VALID_ARRAY_OF_2_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_2_FLOATS[1] = EXPECTED_VALUE_FOR_Y;

	// [Execution]
    Vector2 vVectorUT(VALID_ARRAY_OF_2_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);

    // Cleaning
    delete[] VALID_ARRAY_OF_2_FLOATS;
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
        Vector2 vVectorUT(NULL_ARRAY);
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
/// Checks if vector components are set to the correct values packed in a valid vf32 object.
/// </summary>
ZTEST_CASE ( Constructor7_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

	vf32_z PACK;
	SVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, SFloat::_0, SFloat::_0, PACK);

	// [Execution]
	Vector2 vVectorUT(PACK);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a vector with all components set to zero.
/// </summary>
ZTEST_CASE ( GetNullVector_ReturnsANullVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

	// [Execution]
    Vector2 vVectorUT = Vector2::GetNullVector();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a vector with all components set to one.
/// </summary>
ZTEST_CASE ( GetVectorOfOnes_ReturnsAVectorOfOnes_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

	// [Execution]
    Vector2 vVectorUT = Vector2::GetVectorOfOnes();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to positive direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorX_ReturnsAUnitVectorThatPointsToPositiveDirectionOfXAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

	// [Execution]
    Vector2 vVectorUT = Vector2::GetUnitVectorX();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to positive direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorY_ReturnsAUnitVectorThatPointsToPositiveDirectionOfYAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

	// [Execution]
    Vector2 vVectorUT = Vector2::GetUnitVectorY();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to negative direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorInvX_ReturnsAUnitVectorThatPointsToNegativeDirectionOfXAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

	// [Execution]
    Vector2 vVectorUT = Vector2::GetUnitVectorInvX();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to negative direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorInvY_ReturnsAUnitVectorThatPointsToNegativeDirectionOfYAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_1;
	// [Execution]
    Vector2 vVectorUT = Vector2::GetUnitVectorInvY();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon);
    const Vector2 RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const Vector2 RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Vector2 LEFT_OPERAND(SFloat::Epsilon);
    const Vector2 RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;

    const Vector2 OPERAND1 = Vector2(SFloat::_0_25, SFloat::_1);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorAddition_VectorIsCorrectlyAddedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 OPERAND = Vector2(SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND + OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_2 - SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;

    const Vector2 OPERAND1 = Vector2(SFloat::_0_5, SFloat::_1);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_VectorIsCorrectlySubtractedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

    const Vector2 OPERAND = Vector2(-SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND - OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_0);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector2 vVectorUT = VECTOR * SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorProduct2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = 10;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVectorUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct2_ProductIsCommutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = 10;

    const Vector2 OPERAND1 = Vector2(-SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVector1UT = OPERAND1 * OPERAND2;
    Vector2 vVector2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
ZTEST_CASE ( OperatorProduct2_VectorCanBeMultipliedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_4;

    const Vector2 OPERAND = Vector2(-SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = OPERAND * OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 2 rows and 2 columns.
/// </summary>
ZTEST_CASE ( OperatorProduct3_VectorIsCorrectlyMultipliedByMatrix2x2_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = 4;
    const float_z EXPECTED_VALUE_FOR_Y = 7;

    const Matrix2x2 MATRIX = Matrix2x2(SFloat::_0, SFloat::_1,
                                                 SFloat::_2, SFloat::_3);

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = VECTOR * MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision1_VectorIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const float_z  SCALAR = SFloat::_2;

	// [Execution]
    Vector2 vVectorUT = VECTOR / SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivision1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // [Preparation]
    const float_z  SCALAR = SFloat::_0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Vector2 vVectorUT;
        vVectorUT / SCALAR;
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
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorDivision2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = 2;

    const Vector2 OPERAND1 = Vector2(SFloat::_2, SFloat::_8);
    const Vector2 OPERAND2 = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1 / OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivision2_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.4;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVector1UT = OPERAND1 / OPERAND2;
    Vector2 vVector2UT = OPERAND2 / OPERAND1;

    // [Verification]
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_NE(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_NE(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
ZTEST_CASE ( OperatorDivision2_VectorCanBeDividedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    const Vector2 OPERAND = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = OPERAND / OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivision2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // [Preparation]
    const Vector2 OPERAND_WITH_ZERO_X = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 OPERAND_WITH_ZERO_Y = Vector2(SFloat::_1, SFloat::_0);

	// [Execution]
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;

    Vector2 vVectorUT;

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_X;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_Y;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;

    const Vector2 OPERAND1 = Vector2(SFloat::_0_25, SFloat::_1);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1;
    vVectorUT += OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_VectorIsCorrectlyAddedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 OPERAND = Vector2(SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT += OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_VectorObjectIsCorrectlyAddedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 OPERAND = Vector2(SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT += vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-2.75;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;

    const Vector2 OPERAND1 = Vector2(SFloat::_0_25, SFloat::_1);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1;
    vVectorUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_VectorIsCorrectlySubtractedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

    const Vector2 OPERAND = Vector2(SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT -= OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_VectorObjectIsCorrectlySubtractedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

    const Vector2 OPERAND = Vector2(SFloat::_0_25, SFloat::_1);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT -= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_0);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector component is multiplied and assigned to itself.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_VectorComponentIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)24;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)36;

    const Vector2 VECTOR = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT *= vVectorUT.x; // x2  Now x==4,    y==6
    vVectorUT *= vVectorUT.y; // x6  Now x==24,   y==36

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = 10;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVectorUT = OPERAND1;
    vVectorUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_ProductIsCommutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = 10;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVector1UT = OPERAND1;
    vVector1UT *= OPERAND2;
    Vector2 vVector2UT = OPERAND2;
    vVector2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorCanBeMultipliedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_4;

    const Vector2 OPERAND = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT *= OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if a vector object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_9;

    const Vector2 OPERAND = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Vector2 vVectorUT = OPERAND;
    vVectorUT *= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 2 rows and 2 columns.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation3_VectorIsCorrectlyMultipliedByMatrix2x2_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = 4;
    const float_z EXPECTED_VALUE_FOR_Y = 7;

    const Matrix2x2 MATRIX = Matrix2x2(SFloat::_0, SFloat::_1,
                                                 SFloat::_2, SFloat::_3);

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT *= MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_VectorIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const float_z  SCALAR = SFloat::_2;

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT /= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that there is an assertion that warns when the divisor equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_AssertionFailsWhenDivisorEqualsZero_Test )
{
    // [Preparation]
    const float_z  SCALAR = SFloat::_0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Vector2 vVectorUT;
        vVectorUT /= SCALAR;
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
/// Checks that a vector component is divided and assigned to itself.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_VectorComponentIsCorrectlyDividedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT /= vVectorUT.x; // :2 Now x==1,    y==2
    vVectorUT /= vVectorUT.y; // :2 Now x==0.5,  y==1

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = 2;

    const Vector2 OPERAND1 = Vector2(SFloat::_2, SFloat::_8);
    const Vector2 OPERAND2 = Vector2(SFloat::_2, SFloat::_4);

	// [Execution]
    Vector2 vVectorUT = OPERAND1;
    vVectorUT /= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)0.4;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    Vector2 vVector1UT = OPERAND1;
    vVector1UT /= OPERAND2;
    Vector2 vVector2UT = OPERAND2;
    vVector2UT /= OPERAND1;

    // [Verification]
    BOOST_CHECK_EQUAL(vVector1UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVector1UT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_NE(vVector2UT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_NE(vVector2UT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_VectorCanBeDividedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;

    Vector2 vVectorUT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    vVectorUT /= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // [Preparation]
    const Vector2 OPERAND_WITH_ZERO_X = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 OPERAND_WITH_ZERO_Y = Vector2(SFloat::_1, SFloat::_0);

	// [Execution]
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;

    Vector2 vVectorUT;

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_X;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenXEqualsZero = true;
    }

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_Y;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenYEqualsZero = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a vector is correctly assigned to another vector.
/// </summary>
ZTEST_CASE ( OperatorAssignation_VectorIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT;
    vVectorUT = VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that all vector components are correctly negated.
/// </summary>
ZTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;

    const Vector2 VECTOR = Vector2(SFloat::_1, -SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = -VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that the length of the vector is correctly calculated.
/// </summary>
ZTEST_CASE ( GetLength_LengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // [Preparation]
    const float_z EXPECTED_LENGTH = SFloat::_5;

    const Vector2 VECTOR = Vector2(SFloat::_4, SFloat::_3);

	// [Execution]
    float_z fLengthUT = VECTOR.GetLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that the squared length of the vector is correctly calculated.
/// </summary>
ZTEST_CASE ( GetSquaredLength_SquaredLengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = (float_z)25.0;

    const Vector2 VECTOR = Vector2(SFloat::_4, SFloat::_3);

	// [Execution]
    float_z fSquaredLengthUT = VECTOR.GetSquaredLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fSquaredLengthUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the perpendicular of the vector is correctly calculated.
/// </summary>
ZTEST_CASE ( GetPerpendicular_PerpendicularOfACommonVectorIsCalculatedCorrectly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_4;

    const Vector2 VECTOR = Vector2(SFloat::_4, SFloat::_3);

	// [Execution]
	Vector2 vPerpendicularVectorUT = VECTOR.GetPerpendicular();

    // [Verification]
    BOOST_CHECK_EQUAL(vPerpendicularVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vPerpendicularVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks that a common vector becomes a unit vector.
/// </summary>
ZTEST_CASE ( Normalize_CommonVectorIsCorrectlyNormalized_Test )
{
    // [Preparation]
    const float_z EXPECTED_SUAREDLENGTH = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = VECTOR.Normalize();

    // [Verification]
    float_z fSquaredLength = vVectorUT.GetSquaredLength();

    BOOST_CHECK(SFloat::AreEqual(fSquaredLength, EXPECTED_SUAREDLENGTH));
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when a null vector is to be normalized.
/// </summary>
ZTEST_CASE ( Normalize_AssertionFailsWhenNullVectorIsToBeNormalized_Test )
{
    // [Preparation]
    const Vector2 VECTOR = Vector2(SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        VECTOR.Normalize();
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
/// Checks that all vector components are set to one.
/// </summary>
ZTEST_CASE ( ResetToOne_AllVectorComponentsAreSetToOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_1;

    const Vector2 VECTOR = Vector2(SFloat::_1, -SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT.ResetToOne();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all vector components are set to zero.
/// </summary>
ZTEST_CASE ( ResetToZero_AllVectorComponentsAreSetToZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    const Vector2 VECTOR = Vector2(SFloat::_1, -SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = VECTOR;
    vVectorUT.ResetToZero();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that it returns true when all vector components equal zero.
/// </summary>
ZTEST_CASE ( IsZero_ReturnsTrueWhenAllVectorComponentsEqualZero_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;

    const Vector2 VECTOR = Vector2(SFloat::_0, SFloat::_0);

	// [Execution]
    bool bResult = VECTOR.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal zero.
/// </summary>
ZTEST_CASE ( IsZero_ReturnsFalseWhenNotAllVectorComponentsEqualZero_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;

    const Vector2 VECTOR_X_NOT_EQUAL_ZERO = Vector2(SFloat::_1, SFloat::_0);
    const Vector2 VECTOR_Y_NOT_EQUAL_ZERO = Vector2(SFloat::_0, SFloat::_1);


	// [Execution]
    bool bResult = VECTOR_X_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Y_NOT_EQUAL_ZERO.IsZero();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when all vector components equal one.
/// </summary>
ZTEST_CASE ( IsVectorOfOnes_ReturnsTrueWhenAllVectorComponentsEqualOne_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_1);

	// [Execution]
    bool bResult = VECTOR.IsVectorOfOnes();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns false when not all vector components equal one.
/// </summary>
ZTEST_CASE ( IsVectorOfOnes_ReturnsFalseWhenNotAllVectorComponentsEqualOne_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = false;

    const Vector2 VECTOR_X_NOT_EQUAL_ONE = Vector2(SFloat::_0, SFloat::_1);
    const Vector2 VECTOR_Y_NOT_EQUAL_ONE = Vector2(SFloat::_1, SFloat::_0);

	// [Execution]
    bool bResult = VECTOR_X_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Y_NOT_EQUAL_ONE.IsVectorOfOnes();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned dot product result for 2 common vectors equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonVectors_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)14.0;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    float_z fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)14.0;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_4, SFloat::_5);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vectors are orthogonal.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductEqualsZeroWhenVectorsAreOrthogonal_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Vector2 OPERAND1 = Vector2(SFloat::_3, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_2, -SFloat::_3);

	// [Execution]
    float_z fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common vectors equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween_ReturnsAngleBetween2CommonVectors_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    const Vector2 OPERAND1 = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_0, SFloat::_1);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleBetweenIsCommutative_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_0, SFloat::_1);
    
	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND2.AngleBetween(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when vectors are parallel.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleEqualsZeroWhenVectorsAreParallel_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_1);
    const Vector2 OPERAND2 = Vector2(SFloat::_2, SFloat::_2);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when vectors are orthogonal.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorsAreOrthogonal_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_90;
    #else
        const float_z EXPECTED_RESULT = SAngle::_HalfPi;
    #endif

    const Vector2 OPERAND1 = Vector2(SFloat::_2, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_1, -SFloat::_1);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vectors are opposite.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleEqualsPiRadiansOr180DegreesWhenVectorsAreOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_180;
    #else
        const float_z EXPECTED_RESULT = SAngle::_Pi;
    #endif

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(-SFloat::_1, -SFloat::_2);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    const Vector2 OPERAND_IN_I_QUADRANT_1 = Vector2(SFloat::_2, SFloat::_1);
    const Vector2 OPERAND_IN_I_QUADRANT_2 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND_IN_II_QUADRANT_1 = Vector2(-SFloat::_2, SFloat::_1);
    const Vector2 OPERAND_IN_II_QUADRANT_2 = Vector2(-SFloat::_1, SFloat::_2);
    const Vector2 OPERAND_IN_III_QUADRANT_1 = Vector2(-SFloat::_2, -SFloat::_1);
    const Vector2 OPERAND_IN_III_QUADRANT_2 = Vector2(-SFloat::_1, -SFloat::_2);
    const Vector2 OPERAND_IN_IV_QUADRANT_1 = Vector2(SFloat::_2, -SFloat::_1);
    const Vector2 OPERAND_IN_IV_QUADRANT_2 = Vector2(SFloat::_1, -SFloat::_2);


	// [Execution]
    float_z fResult1_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_1UT = OPERAND_IN_I_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_2UT = OPERAND_IN_I_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_I_QUADRANT_1);
    float_z fResult2_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_I_QUADRANT_2);
    float_z fResult3_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_3UT = OPERAND_IN_II_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_I_QUADRANT_1);
    float_z fResult2_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_I_QUADRANT_2);
    float_z fResult3_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_4UT = OPERAND_IN_II_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_5UT = OPERAND_IN_III_QUADRANT_1.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_1);
    float_z fResult6_6UT = OPERAND_IN_III_QUADRANT_2.AngleBetween(OPERAND_IN_IV_QUADRANT_2);

    float_z fResult1_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_I_QUADRANT_1);
    float_z fResult6_7UT = OPERAND_IN_IV_QUADRANT_1.AngleBetween(OPERAND_IN_I_QUADRANT_2);

    float_z fResult1_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_1);
    float_z fResult2_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_II_QUADRANT_2);
    float_z fResult3_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_1);
    float_z fResult4_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_III_QUADRANT_2);
    float_z fResult5_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_I_QUADRANT_1);
    float_z fResult6_8UT = OPERAND_IN_IV_QUADRANT_2.AngleBetween(OPERAND_IN_I_QUADRANT_2);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_1UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_2UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_2UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_2UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_2UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_2UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_2UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_3UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_3UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_3UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_3UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_3UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_3UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_4UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_4UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_4UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_4UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_4UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_4UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_5UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_5UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_5UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_5UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_5UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_5UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_6UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_6UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_6UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_6UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_6UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_6UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_7UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_7UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_7UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_7UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_7UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_7UT, SFloat::_0) );

    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1_8UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2_8UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult3_8UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult4_8UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult5_8UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult6_8UT, SFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector are not opposite.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorsAreNotOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_180;
    #else
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_Pi;
    #endif

    const Vector2 OPERAND_IN_I_QUADRANT = Vector2(SFloat::_2, SFloat::_1);
    const Vector2 OPERAND_IN_II_QUADRANT = Vector2(-SFloat::_1, SFloat::_2);
    const Vector2 OPERAND_IN_III_QUADRANT = Vector2(-SFloat::_1, -SFloat::_2);
    const Vector2 OPERAND_IN_IV_QUADRANT = Vector2(SFloat::_2, -SFloat::_1);

	// [Execution]
    float_z fResult1UT = OPERAND_IN_I_QUADRANT.AngleBetween(OPERAND_IN_II_QUADRANT);
    float_z fResult2UT = OPERAND_IN_I_QUADRANT.AngleBetween(OPERAND_IN_III_QUADRANT);
    float_z fResult3UT = OPERAND_IN_I_QUADRANT.AngleBetween(OPERAND_IN_IV_QUADRANT);


    // [Verification]
    BOOST_CHECK( SFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult3UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that a correct vector is obtained as result of interpolating between 2 common vectors.
/// </summary>
ZTEST_CASE ( Lerp_CorrectLerpedVectorIsObtainedForTwoCommonVectors_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 EXPECTED_RESULT = Vector2(SFloat::_2, SFloat::_3);

	// [Execution]
    Vector2 vVectorUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent vectors is the same vector.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingTwoEquivalentVectorsGivesSameVector_Test )
{
    // [Preparation]
    const Vector2 EXPECTED_RESULT = Vector2(SFloat::_1, SFloat::_2);

	// [Execution]
    Vector2 vVectorUT = EXPECTED_RESULT.Lerp(SFloat::_0_5, EXPECTED_RESULT);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 opposite vectors is a null vector.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingInTheMiddleOfTwoOppositeVectorsGivesNullVector_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = -OPERAND1;
    const Vector2 EXPECTED_RESULT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vVectorUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the vector obtained when using a non-null vector and a null vector is just the proportion of the non-null vector.
/// </summary>
ZTEST_CASE ( Lerp_WhenUsedNonNullVectorAndNullVectorTheResultIsAScaledNonNullVector_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2::GetNullVector();
    const Vector2 EXPECTED_RESULT = OPERAND1 * (SFloat::_1 - SFloat::_0_25);

	// [Execution]
    Vector2 vVectorUT = OPERAND1.Lerp(SFloat::_0_25, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned vector is the resident vector.
/// </summary>
ZTEST_CASE ( Lerp_ProportionZeroMeansResidentVector_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 EXPECTED_RESULT = OPERAND1;

	// [Execution]
    Vector2 vVectorUT = OPERAND1.Lerp(SFloat::_0, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned vector is the input vector.
/// </summary>
ZTEST_CASE ( Lerp_ProportionOneMeansInputVector_Test )
{
    // [Preparation]
    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 OPERAND2 = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 EXPECTED_RESULT = OPERAND2;

	// [Execution]
    Vector2 vVectorUT = OPERAND1.Lerp(SFloat::_1, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the distance between 2 common vectors equals the expected value.
/// </summary>
ZTEST_CASE ( Distance_ReturnsDistanceBetween2CommonVectors_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_5;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_4);
    const Vector2 OPERAND2 = Vector2(SFloat::_5, SFloat::_1);

	// [Execution]
    float_z fResultUT = OPERAND1.Distance(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the distance between 2 common vectors is conmutative.
/// </summary>
ZTEST_CASE ( Distance_DistanceBetween2CommonVectorsIsConmutative_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_5;

    const Vector2 OPERAND1 = Vector2(SFloat::_1, SFloat::_4);
    const Vector2 OPERAND2 = Vector2(SFloat::_5, SFloat::_1);

	// [Execution]
    float_z fResultUT1 = OPERAND1.Distance(OPERAND2);
    float_z fResultUT2 = OPERAND2.Distance(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT1, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResultUT2, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the distance equals zero when both vectors are the same.
/// </summary>
ZTEST_CASE ( Distance_ExactlyZeroWhenTwoVectorsAreTheSame_Test )
{
    // [Preparation]
    const Vector2 OPERAND = Vector2(SFloat::_1, SFloat::_2);
    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fDistanceUT = OPERAND.Distance(OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(fDistanceUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks the distance between 2 opposite vectors equals the sume of their lengths.
/// </summary>
ZTEST_CASE ( Distance_ForTwoOppositeVectorsResultEqualsSumOfTheirLengths_Test )
{
    // [Preparation]
    const Vector2 OPERAND = Vector2(SFloat::_3, SFloat::_4);
    const Vector2 OPPOSITE_OPERAND = Vector2(-SFloat::_1 - SFloat::_0_5, -SFloat::_2);
    const float_z EXPECTED_RESULT = SFloat::_7 + SFloat::_0_5;

	// [Execution]
    float_z fDistancerUT = OPERAND.Distance(OPPOSITE_OPERAND);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistancerUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks if vector is correctly rotated the given angle.
/// </summary>
ZTEST_CASE ( Transform1_VectorIsCorrectlyRotatedTheGivenAngle_Test )
{
    // [Preparation]
    const Vector2 OPERAND = Vector2(SFloat::_3, SFloat::_4);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z TEST_ANGLE = SAngle::_90;
    #else
        const float_z TEST_ANGLE = SAngle::_HalfPi;
    #endif

    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y =  SFloat::_3;

    // [Execution]
    Vector2 vVectorUT = OPERAND.Transform(TEST_ANGLE);

    // [Verification]
    BOOST_CHECK(SFloat::AreEqual(vVectorUT.x, EXPECTED_VALUE_FOR_X));
    BOOST_CHECK(SFloat::AreEqual(vVectorUT.y, EXPECTED_VALUE_FOR_Y));
}

/// <summary>
/// Checks if vector is not modified if the given angle is 0º.
/// </summary>
ZTEST_CASE ( Transform1_VectorIsNotRotatedByZeroAngle_Test )
{
    // [Preparation]
    const Vector2 OPERAND = Vector2(SFloat::_3, SFloat::_4);

    const float_z TEST_ANGLE = SFloat::_0;

    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_4;

    // [Execution]
    Vector2 vVectorUT = OPERAND.Transform(TEST_ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
}

/// <summary>
/// Checks if vector is correctly transformed by an arbitrary transformation matrix.
/// </summary>
ZTEST_CASE ( Transform2_VectorIsCorrectlyTransformedByAMatrix_Test )
{
    // [Preparation]
    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const Vector2 TRANSLATION = Vector2(SFloat::_1, SFloat::_3);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_90;
    #else
        const float_z ROTATION = SAngle::_HalfPi;
    #endif

    const Vector2 SCALE = Vector2(SFloat::_2, SFloat::_0_5);

    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3(TRANSLATION, ROTATION, SCALE);

    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;

    // [Execution]
    Vector2 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_VALUE_FOR_Y) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform2_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // [Preparation]

    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const TransformationMatrix3x3 TRANSFORMATION = TransformationMatrix3x3::GetIdentity();
    const Vector2 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector2 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
}

/// <summary>
/// Checks that the vector is nulled when the transformation matrix is null.
/// </summary>
ZTEST_CASE ( Transform2_VectorIsNullWhenTransformationMatrixIsNull_Test )
{
    // [Preparation]
    const Vector2 VECTOR = Vector2(SFloat::_1, SFloat::_2);
    const TransformationMatrix3x3 NULL_MATRIX = reinterpret_cast<const TransformationMatrix3x3 &> (Matrix3x3::GetNullMatrix());
    const Vector2 EXPECTED_RESULT = Vector2::GetNullVector();

	// [Execution]
    Vector2 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
}

/// <summary>
/// Checks that the string returned is the expected one.
/// </summary>
ZTEST_CASE ( ToString_StringIsCorrectlyGenerated_Test )
{
    // [Preparation]
    const string_z EXPECTED_RESULT = Z_L("V2(1,0.5)");

    const Vector2 OPERAND = Vector2(SFloat::_1, SFloat::_0_5);

	// [Execution]
    string_z fResultUT = OPERAND.ToString();

    // [Verification]
    BOOST_CHECK ( fResultUT == EXPECTED_RESULT );
}

// End - Test Suite: Vector2
ZTEST_SUITE_END()
