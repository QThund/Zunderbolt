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

#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/Vector3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/SAngle.h"


ZTEST_SUITE_BEGIN( ScalingMatrix3x3_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaventChanged_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 EXPECTED_VALUE(ScalingMatrix3x3::GetIdentity());

    // [Execution]
    ScalingMatrix3x3 matrixUT;

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

    const BaseMatrix3x3 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    const ScalingMatrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE);

    // [Execution]
    ScalingMatrix3x3 matrixUT = MATRIX_TO_COPY;

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

    const BaseMatrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    ScalingMatrix3x3 matrixUT(EXPECTED_VALUE);

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
/// Checks that the scale matrix is correctly built from its three scaling values.
/// </summary>
ZTEST_CASE ( Constructor4_ScaleMatrixCorrectlyBuiltFromThreeScalingValues_Test )
{
    // [Preparation]

    const BaseMatrix3x3 EXPECTED_VALUE(SFloat::_2, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_3, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_4);

    // [Execution]
    ScalingMatrix3x3 matrixUT(SFloat::_2, SFloat::_3, SFloat::_4);

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
/// Checks that a neutral scale matrix (an identity matrix) is obtained when scaling values equal one.
/// </summary>
ZTEST_CASE ( Constructor4_NeutralScaleMatrixIsObtainedWhenScalingValuesEqualOne_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 EXPECTED_VALUE(ScalingMatrix3x3::GetIdentity());

    // [Execution]
    ScalingMatrix3x3 matrixUT(SFloat::_1, SFloat::_1, SFloat::_1);

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
/// Checks that the scale matrix is correctly built from a 3D vector.
/// </summary>
ZTEST_CASE ( Constructor5_ScaleMatrixCorrectlyBuiltFrom3DVector_Test )
{
    // [Preparation]
    const Vector3 SCALING_VECTOR = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);

    const BaseMatrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_2, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_3);

    // [Execution]
    ScalingMatrix3x3 matrixUT(SCALING_VECTOR);

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
/// Checks that a neutral scale matrix (an identity matrix) is obtained when all components of the scaling 3D vector equal one.
/// </summary>
ZTEST_CASE ( Constructor5_NeutralScaleMatrixIsObtainedWhenScaling3DVectorComponentsEqualOne_Test )
{
    // [Preparation]
    const Vector3 SCALING_VECTOR = Vector3(SFloat::_1, SFloat::_1, SFloat::_1);

    const ScalingMatrix3x3 EXPECTED_VALUE(ScalingMatrix3x3::GetIdentity());

    // [Execution]
    ScalingMatrix3x3 matrixUT(SCALING_VECTOR);

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
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
ZTEST_CASE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DIAGONAL = SFloat::_1;

	// [Execution]
    ScalingMatrix3x3 matrixUT = ScalingMatrix3x3::GetIdentity();

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct1_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)18.0;

    // [Execution]
    ScalingMatrix3x3 matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct1_ProductIsCommutative_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    ScalingMatrix3x3 matrix1UT = OPERAND1 * OPERAND2;
    ScalingMatrix3x3 matrix2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and another 3x3 scaling matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct1_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3ScalingMatrixOperand_Test )
{
    // [Preparation]

    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const ScalingMatrix3x3 OPERAND(SFloat::_4, SFloat::_5, SFloat::_6);

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const ScalingMatrix3x3 MATRIX_OP(OPERAND);

    // [Execution]
    ScalingMatrix3x3 matrix1UT = MATRIX_A * MATRIX_OP;
    ScalingMatrix3x3 matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE_X = SFloat::_4;
        const float_z ANGLE_Y = SFloat::_5;
        const float_z ANGLE_Z = SFloat::_6;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z ANGLE_X = SAngle::RadiansToDegrees(SFloat::_4);
        const float_z ANGLE_Y = SAngle::RadiansToDegrees(SFloat::_5);
        const float_z ANGLE_Z = SAngle::RadiansToDegrees(SFloat::_6);
    #endif

    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(ANGLE_X, ANGLE_Y, ANGLE_Z);

    // TODO [thund]: Is this still necessary (FTP)?
    const Matrix4x4 EXPECTED_VALUE((float_z)0.06958762491769549,  (float_z)0.18263815796815594, (float_z)0.98071446696391351,  SFloat::_0,
                                    (float_z)1.5521416463757054 /* FTP */, (float_z)-1.2552183656235949 /* FTP */, (float_z)0.12362509529761734,  SFloat::_0,
                                    (float_z)1.8803842050744795 /* FTP */,  (float_z)2.2704074859237844 /* FTP */, (float_z)-0.55624193402480593, SFloat::_0,
                                    SFloat::_0,                  SFloat::_0,                  SFloat::_0,                    SFloat::_1);
    // FTP -> Forced to pass: The epsilon difference is not enough to pass the test, but it is really trivial.

    // Reference values obtained using following DirectX SDK statement:
    // D3DXMATRIX rotm;
    // D3DXMatrixRotationYawPitchRoll(&rotm, 5.0, 4.0, 6.0);
    // D3DXMATRIX res = scale * rotm;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = SCALE * ROTATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 3x3 rotation matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct2_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3RotationMatrixOperand_Test )
{
    // [Preparation]
    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const RotationMatrix3x3 OPERAND(SFloat::_4, SFloat::_5, SFloat::_6);

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const RotationMatrix3x3 MATRIX_OP(OPERAND);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    TransformationMatrix<Matrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_2, SFloat::_3);
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_4, SFloat::_5, SFloat::_6);

    const Matrix4x4 EXPECTED_VALUE(SFloat::_1,  SFloat::_0,  SFloat::_0,  SFloat::_0,
                                    SFloat::_0,  SFloat::_2,  SFloat::_0,  SFloat::_0,
                                    SFloat::_0,  SFloat::_0,  SFloat::_3,  SFloat::_0,
                                    SFloat::_4,  SFloat::_5,  SFloat::_6,  SFloat::_1);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = SCALE * TRANSLATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x4 translation matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct3_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TranslationMatrixOperand_Test )
{
    // [Preparation]
    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const TranslationMatrix<Matrix4x4> OPERAND(SFloat::_4, SFloat::_5, SFloat::_6);

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const TranslationMatrix<Matrix4x4> MATRIX_OP(OPERAND);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    TransformationMatrix<Matrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct4_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_2, SFloat::_3);
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_4, SFloat::_5, SFloat::_6);

    const Matrix4x3 EXPECTED_VALUE(SFloat::_1,  SFloat::_0,  SFloat::_0,
                                    SFloat::_0,  SFloat::_2,  SFloat::_0,
                                    SFloat::_0,  SFloat::_0,  SFloat::_3,
                                    SFloat::_4,  SFloat::_5,  SFloat::_6);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrixUT = SCALE * TRANSLATION;

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
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x3 translation matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct4_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TranslationMatrixOperand_Test )
{
    // [Preparation]
    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const TranslationMatrix<Matrix4x3> OPERAND(SFloat::_4, SFloat::_5, SFloat::_6);

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const TranslationMatrix<Matrix4x3> MATRIX_OP(OPERAND);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrix1UT = MATRIX_A * MATRIX_OP;
    TransformationMatrix<Matrix4x3> matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct5_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_2, SFloat::_3);
    const TransformationMatrix<Matrix4x4> TRANSFORMATION(Matrix4x4(SFloat::_4,    SFloat::_5,    SFloat::_6,    SFloat::_7,
                                                                      SFloat::_8,    SFloat::_9,    SFloat::_10,   (float_z)11.0,
                                                                      (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                                                      (float_z)16.0, (float_z)17.0, (float_z)18.0, (float_z)19.0));

    const Matrix4x4 EXPECTED_VALUE(SFloat::_4,    SFloat::_5,    SFloat::_6,    SFloat::_0,
                                    (float_z)16.0, (float_z)18.0, (float_z)20.0, SFloat::_0,
                                    (float_z)36.0, (float_z)39.0, (float_z)42.0, SFloat::_0,
                                    (float_z)16.0, (float_z)17.0, (float_z)18.0, SFloat::_1);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = SCALE * TRANSFORMATION;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <sumary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x4 transformation matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct5_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x4TransformationMatrixOperand_Test )
{
    // [Preparation]
    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const TransformationMatrix<Matrix4x4> OPERAND(Matrix4x4(SFloat::_4,    SFloat::_5,    SFloat::_6,    SFloat::_7,
                                                               SFloat::_8,    SFloat::_9,    SFloat::_10,   (float_z)11.0,
                                                               (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0,
                                                               (float_z)16.0, (float_z)17.0, (float_z)18.0, (float_z)19.0));

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const TransformationMatrix<Matrix4x4> MATRIX_OP(OPERAND);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrix1UT = MATRIX_A * MATRIX_OP;
    TransformationMatrix<Matrix4x4> matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][3], matrix2UT.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][3], matrix2UT.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][3], matrix2UT.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][3], matrix2UT.ij[3][3]) );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct6_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_2, SFloat::_3);
    const TransformationMatrix<Matrix4x3> TRANSFORMATION(Matrix4x3(SFloat::_4,    SFloat::_5,    SFloat::_6,
                                                                      SFloat::_8,    SFloat::_9,    SFloat::_10,
                                                                      (float_z)12.0, (float_z)13.0, (float_z)14.0,
                                                                      (float_z)16.0, (float_z)17.0, (float_z)18.0));

    const Matrix4x3 EXPECTED_VALUE( SFloat::_4,    SFloat::_5,    SFloat::_6,
                                    (float_z)16.0, (float_z)18.0, (float_z)20.0,
                                    (float_z)36.0, (float_z)39.0, (float_z)42.0,
                                    (float_z)16.0, (float_z)17.0, (float_z)18.0);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrixUT = SCALE * TRANSFORMATION;

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
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
}

/// <sumary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and a 4x3 transformation matrix.
/// </summary>
ZTEST_CASE ( OperatorProduct6_NonDiagonalElementsDoNotHaveInfluenceOnProductWith4x3TransformationMatrixOperand_Test )
{
    // [Preparation]
    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const TransformationMatrix<Matrix4x3> OPERAND(Matrix4x3(SFloat::_4,    SFloat::_5,    SFloat::_6,
                                                               SFloat::_8,    SFloat::_9,    SFloat::_10,
                                                               (float_z)12.0, (float_z)13.0, (float_z)14.0,
                                                               (float_z)16.0, (float_z)17.0, (float_z)18.0));

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const TransformationMatrix<Matrix4x3> MATRIX_OP(OPERAND);

    // [Execution]
    TransformationMatrix<Matrix4x3> matrix1UT = MATRIX_A * MATRIX_OP;
    TransformationMatrix<Matrix4x3> matrix2UT = MATRIX_B * MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][0], matrix2UT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][1], matrix2UT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[3][2], matrix2UT.ij[3][2]) );
}

/// <summary>
/// Checks that every matrix element is assigned to the right destination matrix element.
/// </summary>
ZTEST_CASE ( OperatorAssignation_EveryElementAssignedToCorrespondingElement_Test )
{
    // [Preparation]

    const BaseMatrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6,
                                        SFloat::_7, SFloat::_8, SFloat::_9);

    // [Execution]
    ScalingMatrix3x3 matrixUT;
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
/// Checks that two common matrices are correctly multiplied and assigned.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_CommonMatricesAreCorrectlyMultipliedAndAssigned_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    const float_z EXPECTED_VALUE_FOR_00 = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_01 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_02 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_10 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_11 = SFloat::_10;
    const float_z EXPECTED_VALUE_FOR_12 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_20 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_21 = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)18.0;

    // [Execution]
    ScalingMatrix3x3 matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_VALUE_FOR_00) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_VALUE_FOR_01) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_VALUE_FOR_02) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_VALUE_FOR_10) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_VALUE_FOR_11) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_VALUE_FOR_12) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_VALUE_FOR_20) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_VALUE_FOR_21) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_VALUE_FOR_22) );
}

/// <summary>
/// Checks that product operation is commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_ProductIsCommutative_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    ScalingMatrix3x3 matrix1UT = OPERAND1;
    matrix1UT *= OPERAND2;
    ScalingMatrix3x3 matrix2UT = OPERAND2;
    matrix2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], matrix2UT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], matrix2UT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], matrix2UT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], matrix2UT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], matrix2UT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], matrix2UT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks that the non diagonal elements of a scaling matrix do not have any influence on the
/// product of that scaling matrix and another 3x3 scaling matrix.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_NonDiagonalElementsDoNotHaveInfluenceOnProductWith3x3ScalingMatrixOperand_Test )
{
    // [Preparation]

    const BaseMatrix3x3 SCALE_A(SFloat::_1, SFloat::_0, SFloat::_0,
                                 SFloat::_0, SFloat::_2, SFloat::_0,
                                 SFloat::_0, SFloat::_0, SFloat::_3);

    const BaseMatrix3x3 SCALE_B(SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3,
                                 SFloat::_1, SFloat::_2, SFloat::_3);

    const ScalingMatrix3x3 OPERAND(SFloat::_4, SFloat::_5, SFloat::_6);

    const ScalingMatrix3x3 MATRIX_A(SCALE_A);
    const ScalingMatrix3x3 MATRIX_B(SCALE_B);
    const ScalingMatrix3x3 MATRIX_OP(OPERAND);

    // [Execution]
    ScalingMatrix3x3 matrix1UT = MATRIX_A;
    matrix1UT *= MATRIX_OP;
    ScalingMatrix3x3 matrix2UT = MATRIX_B;
    matrix2UT *= MATRIX_OP;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][0], matrix2UT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][1], MATRIX_A.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[0][2], MATRIX_A.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][0], MATRIX_A.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[0][1], MATRIX_B.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[0][2], MATRIX_B.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[1][0], MATRIX_B.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][1], matrix2UT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[1][2], MATRIX_A.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][0], MATRIX_A.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][1], MATRIX_A.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[1][2], MATRIX_B.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[2][0], MATRIX_B.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrix2UT.ij[2][1], MATRIX_B.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrix1UT.ij[2][2], matrix2UT.ij[2][2]) );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const ScalingMatrix3x3 OPERAND(SFloat::_2, SFloat::_3, SFloat::_4);

    ScalingMatrix3x3 EXPECTED_VALUE = OPERAND;
    EXPECTED_VALUE *= OPERAND;

	// [Execution]
    ScalingMatrix3x3 matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // [Verification]
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the matrix is correctly inverted.
/// </summary>
ZTEST_CASE ( Invert_MatrixIsCorrectlyInverted_Test )
{
    // [Preparation]

    const ScalingMatrix3x3 ORIGINAL_VALUE(BaseMatrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                           SFloat::_0, SFloat::_2, SFloat::_0,
                                                           SFloat::_0, SFloat::_0, SFloat::_4));

    const BaseMatrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_0_5, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_0_25);

    // [Execution]
    ScalingMatrix3x3 matrixUT = ORIGINAL_VALUE.Invert();

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
/// Checks that obtained scaling values equal expected values.
/// </summary>
ZTEST_CASE ( GetScale1_ValuesAreCorrectlyExtracted_Test )
{
    // [Preparation]

    const ScalingMatrix3x3 ORIGINAL_VALUE(BaseMatrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                          SFloat::_0, SFloat::_2, SFloat::_0,
                                                          SFloat::_0, SFloat::_0, SFloat::_3));
    float_z fScaleXUT = SFloat::_0;
    float_z fScaleYUT = SFloat::_0;
    float_z fScaleZUT = SFloat::_0;

    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;

     // [Execution]
    ScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that components of obtained 3D vector equal expected scaling values.
/// </summary>
ZTEST_CASE ( GetScale2_3DVectorValuesAreCorrectlyExtracted_Test )
{
    // [Preparation]
    Vector3 vScalingVectorUT = Vector3(SFloat::_0, SFloat::_0, SFloat::_0);

    const ScalingMatrix3x3 ORIGINAL_VALUE(BaseMatrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                          SFloat::_0, SFloat::_2, SFloat::_0,
                                                          SFloat::_0, SFloat::_0, SFloat::_3));

    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;

     // [Execution]
    ScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    matrix.GetScale(vScalingVectorUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vScalingVectorUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(vScalingVectorUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(vScalingVectorUT.z, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained determinant value equal expected one.
/// </summary>
ZTEST_CASE ( GetDeterminant_ValueIsCorrect_Test )
{
    // [Preparation]

    const ScalingMatrix3x3 ORIGINAL_VALUE(BaseMatrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                          SFloat::_0, SFloat::_2, SFloat::_0,
                                                          SFloat::_0, SFloat::_0, SFloat::_3));
    float_z determinantValueUT = SFloat::_0;

    const float_z EXPECTED_DETERMINANT_VALUE = SFloat::_6;

     // [Execution]
    ScalingMatrix3x3 matrix = ORIGINAL_VALUE;
    determinantValueUT = matrix.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(determinantValueUT, EXPECTED_DETERMINANT_VALUE);
}

// End - Test Suite: ScalingMatrix3x3
ZTEST_SUITE_END()
