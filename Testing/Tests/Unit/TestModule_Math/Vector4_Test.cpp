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

#include "ZMath/Vector4.h"

#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/Quaternion.h"
#include "ZMath/DualQuaternion.h"
#include "ZMath/SAngle.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( Vector4_TestSuite )

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = -SFloat::_3;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_0, SFloat::_2, -SFloat::_6);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector4 vVectorUT = SCALAR * VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if copy constructor sets vector components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 VECTOR_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);

	// [Execution]
    Vector4 vVectorUT = VECTOR_TO_COPY;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if every input vector's component is copied to the right target vector's component.
/// </summary>
ZTEST_CASE ( Constructor3_VectorComponentsAreCopiedToRightComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

	BaseVector4 INPUT_VECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);

	// [Execution]
	Vector4 vVectorUT(INPUT_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if every input vector's component is copied to the right target vector's component.
/// </summary>
ZTEST_CASE ( Constructor4_VectorComponentsAreCopiedIntoCorrectComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	BaseVector3 INPUT_VECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

	// [Execution]
	Vector4 vVectorUT(INPUT_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}


/// <summary>
/// Checks if every input vector's component is copied to the right target vector's component as well as the value for W component.
/// </summary>
ZTEST_CASE ( Constructor5_VectorComponentsAreCopiedIntoCorrectComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0_5;

	BaseVector3 INPUT_VECTOR(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

	// [Execution]
	Vector4 vVectorUT(INPUT_VECTOR, EXPECTED_VALUE_FOR_W);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if values used as parameters are properly set to vector components.
/// </summary>
ZTEST_CASE ( Constructor6_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

	// [Execution]
    Vector4 vVectorUT(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the value provided is set to all the vector components.
/// </summary>
ZTEST_CASE ( Constructor7_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

	// [Execution]
    Vector4 vVectorUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks if the vector components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor8_VectorComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    float_z* VALID_ARRAY_OF_4_FLOATS = new float_z[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_Z;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_W;

	// [Execution]
    Vector4 vVectorUT(VALID_ARRAY_OF_4_FLOATS);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_z* NULL_ARRAY = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Vector4 vVectorUT(NULL_ARRAY);
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
ZTEST_CASE ( Constructor9_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

	vf32_z PACK;
	SVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W, PACK);

	// [Execution]
	Vector4 vVectorUT(PACK);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if vector components are set to the correct values of the translation matrix.
/// </summary>
ZTEST_CASE ( Constructor10_VectorComponentsAreFilledWithRightMatrixElements_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Matrix4x3 MATRIX(SFloat::_1, SFloat::_0, SFloat::_0,
                            SFloat::_0, SFloat::_1, SFloat::_0,
                            SFloat::_0, SFloat::_0, SFloat::_1,
                            EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);
    const TranslationMatrix<Matrix4x3> TRANSLATION(MATRIX);

	// [Execution]
    Vector4 vVectorUT(TRANSLATION);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if vector components are set to the correct values of the translation matrix.
/// </summary>
ZTEST_CASE ( Constructor11_VectorComponentsAreFilledWithRightMatrixElements_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Matrix4x4 MATRIX(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0,
                            SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0,
                            SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0,
                            EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);
    const TranslationMatrix<Matrix4x4> TRANSLATION(MATRIX);

	// [Execution]
    Vector4 vVectorUT(TRANSLATION);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a vector with all components set to zero but W, that equals one.
/// </summary>
ZTEST_CASE ( GetZeroPoint_ReturnsAPointSetAtOrigin_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetZeroPoint();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a vector with all components set to zero.
/// </summary>
ZTEST_CASE ( GetNullVector_ReturnsANullVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetNullVector();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a vector with all components set to one.
/// </summary>
ZTEST_CASE ( GetVectorOfOnes_ReturnsAVectorOfOnes_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetVectorOfOnes();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to positive direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorX_ReturnsAUnitVectorThatPointsToPositiveDirectionOfXAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorX();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to positive direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorY_ReturnsAUnitVectorThatPointsToPositiveDirectionOfYAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorY();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in Z axis that points to positive direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorZ_ReturnsAUnitVectorThatPointsToPositiveDirectionOfZAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorZ();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in X axis that points to negative direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorInvX_ReturnsAUnitVectorThatPointsToNegativeDirectionOfXAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorInvX();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in Y axis that points to negative direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorInvY_ReturnsAUnitVectorThatPointsToNegativeDirectionOfYAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorInvY();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if it returns a unit vector contained in Z axis that points to negative direction.
/// </summary>
ZTEST_CASE ( GetUnitVectorInvZ_ReturnsAUnitVectorThatPointsToNegativeDirectionOfZAxis_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

	// [Execution]
    Vector4 vVectorUT = Vector4::GetUnitVectorInvZ();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition1_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = -SFloat::_2;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_3, SFloat::_4, SFloat::_5, -SFloat::_9);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorAddition1_VectorIsCorrectlyAddedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_6;

    const Vector4 OPERAND = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVectorUT = OPERAND + OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition2_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_8;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_8);
    const BaseVector3 VECTOR3 = BaseVector3(SFloat::_3, SFloat::_4, SFloat::_5);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 + VECTOR3;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_2 - SFloat::_0_5 - SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_3, SFloat::_4, SFloat::_6, SFloat::_7);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorSubtraction1_VectorIsCorrectlySubtractedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

    const Vector4 OPERAND = Vector4(-SFloat::_0_25, SFloat::_1, -SFloat::_2, SFloat::_5);

	// [Execution]
    Vector4 vVectorUT = OPERAND - OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction2_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_2 - SFloat::_0_5 - SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_7;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_7);
    const BaseVector3 VECTOR3 = BaseVector3(SFloat::_3, SFloat::_4, SFloat::_6);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 - VECTOR3;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = -SFloat::_2;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_0, SFloat::_2, -SFloat::_4);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector4 vVectorUT = VECTOR * SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorProduct2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)10.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)18.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)56.0;

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct2_ProductIsCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    Vector4 vVector1UT = OPERAND1 * OPERAND2;
    Vector4 vVector2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK(vVector1UT == vVector2UT);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
ZTEST_CASE ( OperatorProduct2_VectorCanBeMultipliedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)16.0;

    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND * OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 4 rows and 4 columns.
/// </summary>
ZTEST_CASE ( OperatorProduct3_VectorIsCorrectlyMultipliedByMatrix4x4_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)80.0;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)90.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)100.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)110.0;

    const BaseMatrix4x4 MATRIX = BaseMatrix4x4(SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_3,
                                                 SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7,
                                                 SFloat::_8, SFloat::_9, (float_z)10.0, (float_z)11.0,
                                                 (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0);

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = VECTOR * MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 4 rows and 3 columns.
/// </summary>
ZTEST_CASE ( OperatorProduct4_VectorIsCorrectlyMultipliedByMatrix4x3_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)60.0;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)70.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)80.0;

    const BaseMatrix4x3 MATRIX = BaseMatrix4x3(SFloat::_0, SFloat::_1, SFloat::_2,
                                                 SFloat::_3, SFloat::_4, SFloat::_5,
                                                 SFloat::_6, SFloat::_7, SFloat::_8,
                                                 SFloat::_9, SFloat::_10, (float_z)11.0);

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    BaseVector3 vVectorUT = VECTOR * MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision1_VectorIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z  SCALAR = SFloat::_2;

	// [Execution]
    Vector4 vVectorUT = VECTOR / SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
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
        Vector4 vVectorUT;
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
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 OPERAND1 = Vector4(SFloat::_2, SFloat::_8, SFloat::_9, (float_z)16.0);
    const Vector4 OPERAND2 = Vector4(SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND1 / OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivision2_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0_5);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0_25);

	// [Execution]
    Vector4 vVector1UT = OPERAND1 / OPERAND2;
    Vector4 vVector2UT = OPERAND2 / OPERAND1;

    // [Verification]
    BOOST_CHECK(vVector1UT != vVector2UT);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
ZTEST_CASE ( OperatorDivision2_VectorCanBeDividedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND / OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivision2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // [Preparation]
    const Vector4 OPERAND_WITH_ZERO_X = Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_Y = Vector4(SFloat::_1, SFloat::_0, SFloat::_1, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_Z = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_W = Vector4(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;
    bool bAssertionFailedWhenZEqualsZero = false;
    bool bAssertionFailedWhenWEqualsZero = false;
    Vector4 vVectorUT;

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

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_Z;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenZEqualsZero = true;
    }

    try
    {
        vVectorUT / OPERAND_WITH_ZERO_W;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenWEqualsZero = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenZEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenWEqualsZero);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation1_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, -SFloat::_2);
    const Vector4 OPERAND2 = Vector4(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT += OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation1_VectorIsCorrectlyAddedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_6;

    const Vector4 OPERAND = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT += OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation1_VectorObjectIsCorrectlyAddedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_6;

    const Vector4 OPERAND = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT += vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation2_TwoDifferentVectorsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_3 + SFloat::_0_25;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_2;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, -SFloat::_4, SFloat::_2);
    const BaseVector3 VECTOR3 = BaseVector3(SFloat::_3, SFloat::_4, SFloat::_5);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT += VECTOR3;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation1_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-3.75;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_W = -SFloat::_6;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_7, SFloat::_9);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a correct result is obtained when using the same vector as both operands.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation1_VectorIsCorrectlySubtractedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

    const Vector4 OPERAND = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT -= OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a vector object is correctly added and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation1_VectorObjectIsCorrectlySubtractedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;

    const Vector4 OPERAND = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT -= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if two different vectors are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation2_TwoDifferentVectorsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-3.75;
    const float_z EXPECTED_VALUE_FOR_Y = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_3;

    const Vector4 OPERAND1 = Vector4(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3);
    const BaseVector3 VECTOR3 = BaseVector3(SFloat::_4, SFloat::_5, SFloat::_7);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT -= VECTOR3;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if all the components of the vector are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_VectorIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = -SFloat::_1;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_0, SFloat::_2, -SFloat::_2);
    const float_z  SCALAR = SFloat::_0_5;

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that a vector component is multiplied and assigned to itself.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_VectorComponentIsCorrectlyMultipliedByScalarAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)-663552.0;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)-995328.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)-1327104.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)331776.0;

    const Vector4 VECTOR = Vector4(SFloat::_2, SFloat::_3, SFloat::_4, -SFloat::_1);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT *= vVectorUT.x; // x2  Now x==4,    y==6,    z==8,    w==-2
    vVectorUT *= vVectorUT.y; // x6  Now x==24,   y==36,   z==48,   w==-12
    vVectorUT *= vVectorUT.z; // x48 Now x==1152, y==1728, z==2304, w==-576
    vVectorUT *= vVectorUT.w; // x-576 Now x==-663552, y==-995328, z==-1327104, w==331776

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that every component of one operand is multiplied by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorIsCorrectlyMultipliedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)10.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)18.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)56.0;

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the product between vectors is commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_ProductIsCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    Vector4 vVector1UT = OPERAND1;
    vVector1UT *= OPERAND2;
    Vector4 vVector2UT = OPERAND2;
    vVector2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK(vVector1UT == vVector2UT);
}

/// <summary>
/// Checks that a vector can be multiplied by itself.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorCanBeMultipliedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)16.0;

    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT *= OPERAND;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if a vector object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_VectorObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_9;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)16.0;

    const Vector4 OPERAND = Vector4(SFloat::_2, SFloat::_3, SFloat::_1, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT *= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the vector is properly multiplied by a matrix with 4 rows and 4 columns.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation3_VectorIsCorrectlyMultipliedByMatrix4x4_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = (float_z)80.0;
    const float_z EXPECTED_VALUE_FOR_Y = (float_z)90.0;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)100.0;
    const float_z EXPECTED_VALUE_FOR_W = (float_z)110.0;

    const BaseMatrix4x4 MATRIX = BaseMatrix4x4(SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_3,
                                                 SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7,
                                                 SFloat::_8, SFloat::_9, (float_z)10.0, (float_z)11.0,
                                                 (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0);


    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT *= MATRIX;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if all the components of the vector are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation1_VectorIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z  SCALAR = SFloat::_2;

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT /= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
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
        Vector4 vVectorUT;
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
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_Z = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Vector4 VECTOR = Vector4(SFloat::_2, SFloat::_4, SFloat::_8, SFloat::_0_5);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT /= vVectorUT.x; // :2 Now x==1,    y==2,   z==4,  w==0.25
    vVectorUT /= vVectorUT.y; // :2 Now x==0.5,  y==1,   z==2,  w==0.125
    vVectorUT /= vVectorUT.z; // :2 Now x==0.25, y==0.5, z==1,  w==0.0625
    vVectorUT /= vVectorUT.w; // :0.0625 Now x==4, y==8, z==16, w==1

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that every component of one operand is divided by the same component of the other operand.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_VectorIsCorrectlyDividedByAnotherVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 OPERAND1 = Vector4(SFloat::_2, SFloat::_8, SFloat::_9, (float_z)16.0);
    const Vector4 OPERAND2 = Vector4(SFloat::_2, SFloat::_4, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND1;
    vVectorUT /= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the division between vectors is not commutative.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_DivisionIsNotCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    Vector4 vVector1UT = OPERAND1;
    vVector1UT /= OPERAND2;
    Vector4 vVector2UT = OPERAND2;
    vVector2UT /= OPERAND1;

    // [Verification]
    BOOST_CHECK(vVector1UT != vVector2UT);
}

/// <summary>
/// Checks that a vector can be divided by itself.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_VectorCanBeDividedByItself_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = OPERAND;
    vVectorUT /= vVectorUT;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when any of the vector components equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation2_AssertionFailsWhenAnyComponentEqualsZero_Test )
{
    // [Preparation]
    const Vector4 OPERAND_WITH_ZERO_X = Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_Y = Vector4(SFloat::_1, SFloat::_0, SFloat::_1, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_Z = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);
    const Vector4 OPERAND_WITH_ZERO_W = Vector4(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    bool bAssertionFailedWhenXEqualsZero = false;
    bool bAssertionFailedWhenYEqualsZero = false;
    bool bAssertionFailedWhenZEqualsZero = false;
    bool bAssertionFailedWhenWEqualsZero = false;
    Vector4 vVectorUT;

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

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_Z;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenZEqualsZero = true;
    }

    try
    {
        vVectorUT /= OPERAND_WITH_ZERO_W;
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenWEqualsZero = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailedWhenXEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenYEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenZEqualsZero);
    BOOST_CHECK(bAssertionFailedWhenWEqualsZero);
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
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 VECTOR = Vector4(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);

	// [Execution]
    Vector4 vVectorUT;
    vVectorUT = VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that all vector components are correctly negated.
/// </summary>
ZTEST_CASE ( OperatorUnaryMinus_ComponentsAreNegated_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = -SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;

    const Vector4 VECTOR = Vector4(SFloat::_1, -SFloat::_2, SFloat::_3, -SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = -VECTOR;

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that the length of the vector is correctly calculated.
/// </summary>
ZTEST_CASE ( GetLength_LengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // [Preparation]
    const float_z EXPECTED_LENGTH = (float_z)5.4772255750516612;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    float_z fLengthUT = VECTOR.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLengthUT, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the squared length of the vector is correctly calculated.
/// </summary>
ZTEST_CASE ( GetSquaredLength_SquaredLengthOfACommonVectorIsCalculatedCorrectly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE = (float_z)30.0;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    float_z fSquaredLengthUT = VECTOR.GetSquaredLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fSquaredLengthUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common vector becomes a unit vector.
/// </summary>
ZTEST_CASE ( Normalize_CommonVectorIsCorrectlyNormalized_Test )
{
    // [Preparation]
    const float_z EXPECTED_SUAREDLENGTH = SFloat::_1;

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Normalize();

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
    const Vector4 VECTOR = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

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

    const Vector4 VECTOR = Vector4(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_0_25);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT.ResetToOne();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that all vector components are set to zero but W, which equals one.
/// </summary>
ZTEST_CASE ( ResetToZeroPoint_AllVectorComponentsAreSetToZeroAndWEqualsOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_1;

    const Vector4 VECTOR = Vector4(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_0_25);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT.ResetToZeroPoint();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that all vector components are set to zero.
/// </summary>
ZTEST_CASE ( ResetToZeroVector_AllVectorComponentsAreSetToZero_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    const Vector4 VECTOR = Vector4(SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_0_25);

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    vVectorUT.ResetToZeroVector();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that it returns true when all vector components equal zero.
/// </summary>
ZTEST_CASE ( IsZero_ReturnsTrueWhenAllVectorComponentsEqualZero_Test )
{
    // [Preparation]
    const bool EXPECTED_RESULT = true;

    const Vector4 VECTOR = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

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

    const Vector4 VECTOR_X_NOT_EQUAL_ZERO = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR_Y_NOT_EQUAL_ZERO = Vector4(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR_Z_NOT_EQUAL_ZERO = Vector4(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector4 VECTOR_W_NOT_EQUAL_ZERO = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

	// [Execution]
    bool bResult = VECTOR_X_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Y_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_Z_NOT_EQUAL_ZERO.IsZero();
    bResult |= VECTOR_W_NOT_EQUAL_ZERO.IsZero();

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

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);

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

    const Vector4 VECTOR_X_NOT_EQUAL_ONE = Vector4(SFloat::_0, SFloat::_1, SFloat::_1, SFloat::_1);
    const Vector4 VECTOR_Y_NOT_EQUAL_ONE = Vector4(SFloat::_1, SFloat::_0, SFloat::_1, SFloat::_1);
    const Vector4 VECTOR_Z_NOT_EQUAL_ONE = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);
    const Vector4 VECTOR_W_NOT_EQUAL_ONE = Vector4(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    bool bResult = VECTOR_X_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Y_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_Z_NOT_EQUAL_ONE.IsVectorOfOnes();
    bResult |= VECTOR_W_NOT_EQUAL_ONE.IsVectorOfOnes();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned dot product result for 2 common vectors equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct_ReturnsDotProductFor2CommonVectors_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)32.0;

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_10);

	// [Execution]
    float_z fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
ZTEST_CASE ( DotProduct_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_10);
    const Vector4 OPERAND3 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_0);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND1.DotProduct(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductIsCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals zero when vectors are orthogonal.
/// </summary>
ZTEST_CASE ( DotProduct_DotProductEqualsZeroWhenVectorsAreOrthogonal_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Vector4 OPERAND1 = Vector4(SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(SFloat::_0, SFloat::_3, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND3 = Vector4(SFloat::_0, SFloat::_0, SFloat::_3, SFloat::_0);
    const Vector4 OPERAND4 = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_3);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND3);
    float_z fResult3UT = OPERAND3.DotProduct(OPERAND4);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult3UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null vector.
/// </summary>
ZTEST_CASE ( DotProduct_ReturnsZeroWhenAnOperandIsNullVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Vector4 NONNULL_VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 NULL_VECTOR = Vector4::GetNullVector();

	// [Execution]
    float_z fResult1UT = NONNULL_VECTOR.DotProduct(NULL_VECTOR);
    float_z fResult2UT = NULL_VECTOR.DotProduct(NONNULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for 2 common vectors equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween_ReturnsAngleBetween2CommonVectors_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
ZTEST_CASE ( AngleBetween_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_10);
    const Vector4 OPERAND3 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_10);

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND1.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleBetweenIsCommutative_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

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

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(SFloat::_9, SFloat::_0, SFloat::_0, SFloat::_0);

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

    const Vector4 OPERAND1 = Vector4(SFloat::_5, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(SFloat::_0, SFloat::_5, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND3 = Vector4(SFloat::_0, SFloat::_0, SFloat::_5, SFloat::_0);

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND2.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
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

    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(-SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);

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
    const Vector4 REFERENCE_OPERAND = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                                // _
    const Vector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);  // \_
    const Vector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_0); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2UT, SFloat::_0) );
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

    const Vector4 REFERENCE_OPERAND = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                                // _
    const Vector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);  // \_
    const Vector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_0); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that a correct vector is obtained by applying the cross product to 2 common vectors.
/// </summary>
ZTEST_CASE ( CrossProduct_AThirdVectorIsCorrectlyCalculated_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_9);
    const Vector4 EXPECTED_RESULT = Vector4(-SFloat::_10, (float_z)13.0, (float_z)-4.0, SFloat::_8);

	// [Execution]
    Vector4 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that W component doesn't take part in the cross product operation.
/// </summary>
ZTEST_CASE ( CrossProduct_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_9);
    const Vector4 OPERAND3 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_1);

	// [Execution]
    Vector4 vVector1UT = OPERAND1.CrossProduct(OPERAND2);
    Vector4 vVector2UT = OPERAND1.CrossProduct(OPERAND3);

    // [Verification]
    BOOST_CHECK( vVector1UT == vVector2UT );
}

/// <summary>
/// Checks that the W component of the first operand is returned as W component of the resultant vector.
/// </summary>
ZTEST_CASE ( CrossProduct_WComponentOfFirstOperandIsReturned_Test )
{
    // [Preparation]
    const float_z EXPECTED_W = SFloat::_8;
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, EXPECTED_W);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_9);

	// [Execution]
    Vector4 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( vVectorUT.w, EXPECTED_W );
}

/// <summary>
/// Checks that X, Y and Z components equal zero when applying the cross product to 2 parallel vectors that point at the same direction.
/// </summary>
ZTEST_CASE ( CrossProduct_XYZEqualZeroWhenVectorsAreParallelAndSameDirection_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_2, SFloat::_4, SFloat::_6, SFloat::_8);
    const Vector4 EXPECTED_RESULT = Vector4::GetNullVector();

	// [Execution]
    Vector4 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, OPERAND1.w);
}

/// <summary>
/// Checks that X, Y and Z components equal zero when applying the cross product to 2 parallel vectors that point at opposite direction.
/// </summary>
ZTEST_CASE ( CrossProduct_XYZEqualZeroWhenVectorsAreParallelAndOppositeDirection_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(-SFloat::_1, -SFloat::_2, -SFloat::_3, SFloat::_4);
    const Vector4 EXPECTED_RESULT = Vector4::GetNullVector();

	// [Execution]
    Vector4 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, OPERAND1.w);
}

/// <summary>
/// Checks that follows left-handed rules, so +X x +Y = +Z.
/// </summary>
ZTEST_CASE ( CrossProduct_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 OPERAND2 = Vector4(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0);

	// [Execution]
    Vector4 vVectorUT = OPERAND1.CrossProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that X, Y and Z components equal zero when at least one of the operands is null vector.
/// </summary>
ZTEST_CASE ( CrossProduct_XYZEqualZeroVectorWhenAnOperandIsNullVector_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT_FOR_ALL = SFloat::_0;

    const Vector4 NULL_VECTOR = Vector4::GetNullVector();
    const Vector4 NONNULL_VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT1 = NULL_VECTOR.CrossProduct(NONNULL_VECTOR);;
    Vector4 vVectorUT2 = NONNULL_VECTOR.CrossProduct(NULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT1.x, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT1.y, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT1.z, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT1.w, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.x, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.y, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.z, EXPECTED_RESULT_FOR_ALL);
    BOOST_CHECK_EQUAL(vVectorUT2.w, NONNULL_VECTOR.w);
}

/// <summary>
/// Checks that the cross product is correctly calculated when the same instance is used for both operands.
/// </summary>
ZTEST_CASE ( CrossProduct_BehavesCorrectlyWhenSameInstanceIsUsedAsParameter_Test )
{
    // [Preparation]
    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const Vector4 EXPECTED_RESULT = Vector4::GetNullVector();

	// [Execution]
    Vector4 vVectorUT = OPERAND.CrossProduct(OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, OPERAND.w);
}

/// <summary>
/// Checks that a correct vector is obtained as result of interpolating between 2 common vectors.
/// </summary>
ZTEST_CASE ( Lerp_CorrectLerpedVectorIsObtainedForTwoCommonVectors_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);
    const Vector4 EXPECTED_RESULT = Vector4((float_z)2.5, (float_z)3.5, (float_z)4.5, (float_z)7.5);

	// [Execution]
    Vector4 vVectorUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result of interpolating between 2 equivalent vectors is the same vector.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingTwoEquivalentVectorsGivesSameVector_Test )
{
    // [Preparation]
    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector4 vVectorUT = EXPECTED_RESULT.Lerp(SFloat::_0_5, EXPECTED_RESULT);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the result of interpolating just in the middle between 2 opposite vectors is a null vector.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingInTheMiddleOfTwoOppositeVectorsGivesNullVector_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = -OPERAND1;
    const Vector4 EXPECTED_RESULT = Vector4::GetNullVector();

	// [Execution]
    Vector4 vVectorUT = OPERAND1.Lerp(SFloat::_0_5, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the vector obtained when using a non-null vector and a null vector is just the proportion of the non-null vector.
/// </summary>
ZTEST_CASE ( Lerp_WhenUsedNonNullVectorAndNullVectorTheResultIsAScaledNonNullVector_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4::GetNullVector();
    const Vector4 EXPECTED_RESULT = OPERAND1 * (SFloat::_1 - SFloat::_0_25);

	// [Execution]
    Vector4 vVectorUT = OPERAND1.Lerp(SFloat::_0_25, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 0, the returned vector is the resident vector.
/// </summary>
ZTEST_CASE ( Lerp_ProportionZeroMeansResidentVector_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Vector4 EXPECTED_RESULT = OPERAND1;

	// [Execution]
    Vector4 vVectorUT = OPERAND1.Lerp(SFloat::_0, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that when the proportion equals 1, the returned vector is the input vector.
/// </summary>
ZTEST_CASE ( Lerp_ProportionOneMeansInputVector_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 OPERAND2 = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Vector4 EXPECTED_RESULT = OPERAND2;

	// [Execution]
    Vector4 vVectorUT = OPERAND1.Lerp(SFloat::_1, OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the distance is correctly calculated for two common vectors.
/// </summary>
ZTEST_CASE ( Distance_CorrectlyCalculatedForTwoCommonVectors_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);
    const float_z EXPECTED_RESULT = (float_z)5.196152422706632;

	// [Execution]
    float_z fDistancerUT = OPERAND1.Distance(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistancerUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that W component doesn't take part in the distance calculation.
/// </summary>
ZTEST_CASE ( Distance_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 OPERAND1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 OPERAND2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_10);
    const Vector4 OPERAND3 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1);

	// [Execution]
    float_z fDistancer1UT = OPERAND1.Distance(OPERAND2);
    float_z fDistancer2UT = OPERAND1.Distance(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fDistancer1UT, fDistancer2UT );
}

/// <summary>
/// Checks that the distance equals zero when both vectors are the same.
/// </summary>
ZTEST_CASE ( Distance_ExactlyZeroWhenTwoVectorsAreTheSame_Test )
{
    // [Preparation]
    const Vector4 OPERAND = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_RESULT = SFloat::_0;

	// [Execution]
    float_z fDistancerUT = OPERAND.Distance(OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(fDistancerUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a common vector is correctly homogenized.
/// </summary>
ZTEST_CASE ( Homogenize_CommonVectorIsCorrectlyHomogenized_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_8, SFloat::_4);
    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_0_25, SFloat::_0_5, SFloat::_2, SFloat::_1);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Homogenize();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that a vector is not homogenized when W component equals zero.
/// </summary>
ZTEST_CASE ( Homogenize_VectorIsNotHomogenizedWhenWComponentEqualsZero_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_8, SFloat::_0);
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Homogenize();

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE ( Transform1_VectorIsCorrectlyTransformedByCommonQuaternion_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Quaternion TRANSFORMATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const Vector4 EXPECTED_RESULT = Vector4( (float_z)-3.5355339059327378,
                                               (float_z)-2.1213203435596419,
                                               (float_z)-SFloat::_2,
                                               SFloat::_5);

    // Results have been obtained by using DirectX SDK
    // D3DXQUATERNION qRot, qVector, qConjugate;
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXQuaternionRotationYawPitchRoll(&qRot, fYaw, fPitch, fRoll);
    // D3DXQuaternionNormalize(&qRot, &qRot);
    // D3DXQuaternionConjugate(&qConjugate, &qRot);
    // qVector.x = 1; qVector.y = 2; qVector.z = 4; qVector.w = 0;
    // D3DXQuaternionMultiply(&qVector, &qRot, &qv);
    // D3DXQuaternionMultiply(&qVector, &qVector, &qConjugate);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the W component doesn't take part in the transformation operation.
/// </summary>
ZTEST_CASE ( Transform1_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector4 VECTOR_WITH_OTHER_W = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0);
    const Quaternion TRANSFORMATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector4 vVector1UT = VECTOR.Transform(TRANSFORMATION);
    Vector4 vVector2UT = VECTOR_WITH_OTHER_W.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK_EQUAL( vVector1UT.x, vVector2UT.x );
    BOOST_CHECK_EQUAL( vVector1UT.y, vVector2UT.y );
    BOOST_CHECK_EQUAL( vVector1UT.z, vVector2UT.z );
    // W is not compared since it doesn't change and, therefore, they will be different for both vectors
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity quaternion.
/// </summary>
ZTEST_CASE ( Transform1_VectorDoesntChangeWhenTransformedByIdentityQuaternion_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Quaternion UNIT_QUATERNION = Quaternion::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(UNIT_QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the quaternion is null.
/// </summary>
ZTEST_CASE ( Transform1_XYZEqualZeroWhenQuaternionIsNull_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    Vector4 EXPECTED_RESULT = Vector4::GetNullVector();
    EXPECTED_RESULT.w = VECTOR.w;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary dual quaternion.
/// </summary>
ZTEST_CASE ( Transform2_VectorIsCorrectlyTransformedByCommonDualQuaternion_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EULER_ANGLE_X = SAngle::_HalfPi;
        const float_z EULER_ANGLE_Y = SAngle::_Pi;
        const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EULER_ANGLE_X = SAngle::_90;
        const float_z EULER_ANGLE_Y = SAngle::_180;
        const float_z EULER_ANGLE_Z = SAngle::_45;
    #endif

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const DualQuaternion TRANSFORMATION = DualQuaternion(Vector4(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_0),
                                                           Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z));

    #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
        const Vector4 EXPECTED_RESULT = Vector4( (float_z)-9.1923866,
                                                   (float_z)-3.5355341,
                                                   -SFloat::_6,
                                                   SFloat::_5);

    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
        const Vector4 EXPECTED_RESULT = Vector4( (float_z)-9.1923881554251174,
                                                   (float_z)-3.5355339059327351,
                                                   (float_z)-SFloat::_6,
                                                   SFloat::_5);

    #endif

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the W component doesn't take part in the transformation operation.
/// </summary>
ZTEST_CASE ( Transform2_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector4 VECTOR_WITH_OTHER_W = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0);
    const DualQuaternion TRANSFORMATION = DualQuaternion(Vector4(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_0),
                                                           Quaternion(SFloat::_1, SFloat::_2, SFloat::_4));

	// [Execution]
    Vector4 vVector1UT = VECTOR.Transform(TRANSFORMATION);
    Vector4 vVector2UT = VECTOR_WITH_OTHER_W.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK_EQUAL( vVector1UT.x, vVector2UT.x );
    BOOST_CHECK_EQUAL( vVector1UT.y, vVector2UT.y );
    BOOST_CHECK_EQUAL( vVector1UT.z, vVector2UT.z );
    // W is not compared since it doesn't change and, therefore, they will be different for both vectors
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity dual quaternion.
/// </summary>
ZTEST_CASE ( Transform2_VectorDoesntChangeWhenTransformedByIdentityDualQuaternion_Test )
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const DualQuaternion TRANSFORMATION = DualQuaternion::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the dual quaternion is null.
/// </summary>
ZTEST_CASE ( Transform2_XYZEqualZeroWhenDualQuaternionIsNull_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const DualQuaternion NULL_DUALQUATERNION = DualQuaternion(Vector4::GetNullVector(), Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

    Vector4 EXPECTED_RESULT = Vector4::GetNullVector();
    EXPECTED_RESULT.w = VECTOR.w;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_DUALQUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE ( Transform3_VectorIsCorrectlyTransformedByCommonRotationMatrix_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Vector4 EXPECTED_RESULT = Vector4( (float_z)0.70710678118654768,
                                               (float_z)-SFloat::_4,
                                               (float_z)-2.1213203435596428,
                                               SFloat::_5);

    // Results calculated with DirectX SDK
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 2, 4);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the W component doesn't take part in the transformation operation.
/// </summary>
ZTEST_CASE ( Transform3_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector4 VECTOR_WITH_OTHER_W = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(SFloat::_1, SFloat::_2, SFloat::_4);

	// [Execution]
    Vector4 vVector1UT = VECTOR.Transform(TRANSFORMATION);
    Vector4 vVector2UT = VECTOR_WITH_OTHER_W.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK_EQUAL( vVector1UT.x, vVector2UT.x );
    BOOST_CHECK_EQUAL( vVector1UT.y, vVector2UT.y );
    BOOST_CHECK_EQUAL( vVector1UT.z, vVector2UT.z );
    // W is not compared since it doesn't change and, therefore, they will be different for both vectors
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform3_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the rotation matrix is null.
/// </summary>
ZTEST_CASE ( Transform3_XYZEqualZeroWhenRotationMatrixIsNull_Test )
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const RotationMatrix3x3 NULL_MATRIX = RotationMatrix3x3(Matrix3x3::GetNullMatrix());

    Vector4 EXPECTED_RESULT = Vector4::GetNullVector();
    EXPECTED_RESULT.w = VECTOR.w;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the rotation is applied following left-handed rules.
/// </summary>
ZTEST_CASE ( Transform3_RotationFollowsLeftHandedRules_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SFloat::_0;
    const float_z EULER_ANGLE_Y = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Z = SFloat::_0;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SFloat::_0;
    const float_z EULER_ANGLE_Y = SAngle::_90;
    const float_z EULER_ANGLE_Z = SFloat::_0;
#endif

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_0, SFloat::_0, -SFloat::_1, SFloat::_0);

    // Results calculated with DirectX SDK
    // float_z fYaw = SAngle::_HalfPi;
    // float_z fPitch = SFloat::_0;
    // float_z fRoll = SFloat::_0;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 0, 0);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary scale matrix.
/// </summary>
ZTEST_CASE ( Transform4_VectorIsCorrectlyTransformedByCommonScaleMatrix_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_0_25, SFloat::_6, -SFloat::_4, SFloat::_5);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the W component doesn't take part in the transformation operation.
/// </summary>
ZTEST_CASE ( Transform4_WComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector4 VECTOR_WITH_OTHER_W = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_0);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

	// [Execution]
    Vector4 vVector1UT = VECTOR.Transform(TRANSFORMATION);
    Vector4 vVector2UT = VECTOR_WITH_OTHER_W.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK_EQUAL( vVector1UT.x, vVector2UT.x );
    BOOST_CHECK_EQUAL( vVector1UT.y, vVector2UT.y );
    BOOST_CHECK_EQUAL( vVector1UT.z, vVector2UT.z );
    // W is not compared since it doesn't change and, therefore, they will be different for both vectors
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform4_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the scale matrix is null.
/// </summary>
ZTEST_CASE ( Transform4_XYZEqualZeroWhenScaleMatrixIsNull_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 NULL_MATRIX = ScalingMatrix3x3(Matrix3x3::GetNullMatrix());

    Vector4 EXPECTED_RESULT = Vector4::GetNullVector();
    EXPECTED_RESULT.w = VECTOR.w;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Template method used by Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template()
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const TranslationMatrix<MatrixType> TRANSFORMATION = TranslationMatrix<MatrixType>(SFloat::_1, SFloat::_2, -SFloat::_3);

    const Vector4 EXPECTED_RESULT = Vector4(SFloat::_5, SFloat::_10, -SFloat::_9, VECTOR.w);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE ( Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform5_VectorIsCorrectlyTransformedByCommonTranslationMatrix_Template<Matrix4x4>();
}

/// <summary>
/// Template method used by Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TranslationMatrix<MatrixType> TRANSFORMATION = TranslationMatrix<MatrixType>::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform5_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<Matrix4x4>();
}

/// <summary>
/// Template method used by Transform5_XYZEqualZeroWhenTranslationMatrixIsNull_Test to test
/// using different template parameters for class TranslationMatrix.
/// </summary>
template<class MatrixType>
void Transform5_VectorDoesntChangeWhenTranslationMatrixIsNull_Template()
{
    // [Preparation]

    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TranslationMatrix<MatrixType> NULL_MATRIX = TranslationMatrix<MatrixType>(MatrixType::GetNullMatrix());

    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the vector doesn't change when the translation matrix is null.
/// </summary>
ZTEST_CASE ( Transform5_VectorDoesntChangeWhenTranslationMatrixIsNull_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform5_VectorDoesntChangeWhenTranslationMatrixIsNull_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform5_VectorDoesntChangeWhenTranslationMatrixIsNull_Template<Matrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template()
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_X = SAngle::_90;
        const float_z ROTATION_Y = SAngle::_180;
        const float_z ROTATION_Z = SAngle::_45;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ROTATION_X = SAngle::_HalfPi;
        const float_z ROTATION_Y = SAngle::_Pi;
        const float_z ROTATION_Z = SAngle::_QuarterPi;
    #endif
    const TranslationMatrix<MatrixType> TRANSLATION = TranslationMatrix<MatrixType>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>(TRANSLATION, ROTATION, SCALE);

    const Vector4 EXPECTED_RESULT = Vector4((float_z)14.065863991822649, (float_z)24.0, (float_z)-34.419417382415922, SFloat::_5);

    // Results calculated using DirectX SDK
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SFloat::_0_25, SFloat::_3, -SFloat::_1);
    // D3DXMatrixTranslation(&translation, SFloat::_2, SFloat::_4, -SFloat::_6);
    // D3DXVECTOR4 vVector(1, 2, 4, 5);
    // transformation = scaling * rotation * translation;
    // D3DXVec4Transform(&vVector, &vVector, &transformation);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE ( Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform6_VectorIsCorrectlyTransformedByCommonTransformationMatrix_Template<Matrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TransformationMatrix<MatrixType> TRANSFORMATION = TransformationMatrix<MatrixType>::GetIdentity();
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform6_VectorDoesntChangeWhenTransformedByIdentityMatrix_Template<Matrix4x4>();
}

/// <summary>
/// Template method used by Transform6_VectorIsNullWhenTransformationMatrixIsNull_Test to test
/// using different template parameters for class TransformationMatrix.
/// </summary>
template<class MatrixType>
void Transform6_XYZEqualZeroWhenTransformationMatrixIsNull_Template()
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TransformationMatrix<MatrixType> NULL_MATRIX = TransformationMatrix<MatrixType>(MatrixType::GetNullMatrix());

    Vector4 EXPECTED_RESULT = Vector4::GetNullVector();
    EXPECTED_RESULT.w = VECTOR.w;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the transformation matrix is null.
/// </summary>
ZTEST_CASE ( Transform6_XYZEqualZeroWhenTransformationMatrixIsNull_Test )
{

    BOOST_TEST_MESSAGE("MatrixType=Matrix4x3");
    Transform6_XYZEqualZeroWhenTransformationMatrixIsNull_Template<Matrix4x3>();
    BOOST_TEST_MESSAGE("MatrixType=Matrix4x4");
    Transform6_XYZEqualZeroWhenTransformationMatrixIsNull_Template<Matrix4x4>();
}

/// <summary>
/// Checks that the vector is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE ( Transform7_VectorIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1),
                                  Vector4(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_1),
                                  Vector4(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0));

    const Vector4 EXPECTED_RESULT = Vector4( (float_z)-1.3416407864998741,
                                               (float_z)1.7888543819998315,
                                               (float_z)14.0,
                                               VECTOR.w);

    // Results calculated with DirectX SDK
    // D3DXMATRIX transformation;
    // D3DXVECTOR4 vVector(1, 2, 4, 5);
    // D3DXVECTOR3 vEye(1, 2, 3), vUp(0, 1, 0), vAt(0, 0, 1);
    // D3DXMatrixLookAtLH(&transformation, &vEye, &vAt, &vUp);
    // D3DXVec4Transform(&vVector, &vVector, &transformation);

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the vector doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Transform7_VectorDoesntChangeWhenTransformedByIdentityMatrix_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const SpaceConversionMatrix CONVERSION = SpaceConversionMatrix(Matrix4x4::GetIdentity());
    const Vector4 EXPECTED_RESULT = VECTOR;

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.x, EXPECTED_RESULT.x) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.y, EXPECTED_RESULT.y) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.z, EXPECTED_RESULT.z) );
    BOOST_CHECK( SFloat::AreEqual(vVectorUT.w, EXPECTED_RESULT.w) );
}

/// <summary>
/// Checks that the X, Y and Z vector components equal zero when the space conversion matrix is null.
/// </summary>
ZTEST_CASE ( Transform7_XYZEqualZeroWhenSpaceConversionMatrixIsNull_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const SpaceConversionMatrix NULL_MATRIX = SpaceConversionMatrix(Matrix4x4::GetNullMatrix());

    const Vector4 EXPECTED_RESULT = Vector4::GetNullVector();

	// [Execution]
    Vector4 vVectorUT = VECTOR.Transform(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(vVectorUT.x, EXPECTED_RESULT.x);
    BOOST_CHECK_EQUAL(vVectorUT.y, EXPECTED_RESULT.y);
    BOOST_CHECK_EQUAL(vVectorUT.z, EXPECTED_RESULT.z);
    BOOST_CHECK_EQUAL(vVectorUT.w, EXPECTED_RESULT.w);
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const Vector4 VECTOR = Vector4(SFloat::_0_25, (float_z)-0.000002, (float_z)40000.0, SFloat::_1);

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux
        string_z EXPECTED_STRING_FORM = Z_L("V4(0.25,-1.99999999e-06,40000,1)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("V4(0.25,-1.99999999e-06,40000,1)");
    #endif
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux
        string_z EXPECTED_STRING_FORM = Z_L("V4(0.25,-1.9999999999999999e-06,40000,1)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("V4(0.25,-1.9999999999999999e-06,40000,1)");
    #endif
#endif

	// [Execution]
    Vector4 vVectorUT = VECTOR;
    string_z strStringForm = vVectorUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: Vector4
ZTEST_SUITE_END()
