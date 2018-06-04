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

#include "ZMath/SpaceConversionMatrix.h"
#include "ZMath/Quaternion.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/SAngle.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/Exceptions/AssertException.h"
using namespace z::Internals;


ZTEST_SUITE_BEGIN( SpaceConversionMatrix_TestSuite )

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

    const Matrix4x4 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02, EXPECTED_VALUE_FOR_03,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12, EXPECTED_VALUE_FOR_13,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22, EXPECTED_VALUE_FOR_23,
                                        EXPECTED_VALUE_FOR_30, EXPECTED_VALUE_FOR_31, EXPECTED_VALUE_FOR_32, EXPECTED_VALUE_FOR_33);

    const SpaceConversionMatrix MATRIX_TO_COPY(EXPECTED_VALUE);

    // [Execution]
    SpaceConversionMatrix matrixUT = MATRIX_TO_COPY;

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
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
ZTEST_CASE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test )
{
    // [Preparation]
    const Matrix4x4 EXPECTED_VALUE(SFloat::_0, SFloat::_1, SFloat::_2, SFloat::_3,
                                        SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7,
                                        SFloat::_8, SFloat::_9, SFloat::_10, (float_z)11.0,
                                        (float_z)12.0, (float_z)13.0, (float_z)14.0, (float_z)15.0);

    // [Execution]
    SpaceConversionMatrix matrixUT(EXPECTED_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]);
}

/// <summary>
/// Checks that every matrix element is assigned to the right destination matrix element.
/// </summary>
ZTEST_CASE ( OperatorAssignation_EveryElementAssignedToCorrespondingElement_Test )
{
    // [Preparation]
    const Matrix4x4 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4, 
                                        SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8, 
                                        SFloat::_9, SFloat::_10, (float)11.0, (float)12.0,
                                        (float)13.0, (float)14.0, (float)15.0, (float)16.0);

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK_EQUAL(matrixUT.ij[0][0], EXPECTED_VALUE.ij[0][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][1], EXPECTED_VALUE.ij[0][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][2], EXPECTED_VALUE.ij[0][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[0][3], EXPECTED_VALUE.ij[0][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][0], EXPECTED_VALUE.ij[1][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][1], EXPECTED_VALUE.ij[1][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][2], EXPECTED_VALUE.ij[1][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[1][3], EXPECTED_VALUE.ij[1][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][0], EXPECTED_VALUE.ij[2][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][1], EXPECTED_VALUE.ij[2][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][2], EXPECTED_VALUE.ij[2][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[2][3], EXPECTED_VALUE.ij[2][3]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const SpaceConversionMatrix OPERAND1(Matrix4x4(SFloat::_1,    SFloat::_2,    SFloat::_3,    SFloat::_4,
                                                         SFloat::_5,    SFloat::_6,    SFloat::_7,    SFloat::_8,
                                                         SFloat::_9,    SFloat::_10,   (float_z)11.0, (float_z)12.0,
                                                         (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0));

    const SpaceConversionMatrix OPERAND2(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)20.0,
                                                         (float_z)21.0, (float_z)22.0, (float_z)23.0, (float_z)24.0,
                                                         (float_z)25.0, (float_z)26.0, (float_z)27.0, (float_z)28.0,
                                                         (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0));

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)250.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)260.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)270.0;
    const float_z EXPECTED_VALUE_FOR_03 = (float_z)280.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)618.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)644.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)670.0;
    const float_z EXPECTED_VALUE_FOR_13 = (float_z)696.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)986.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)1028.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)1070.0;
    const float_z EXPECTED_VALUE_FOR_23 = (float_z)1112.0;
    const float_z EXPECTED_VALUE_FOR_30 = (float_z)1354.0;
    const float_z EXPECTED_VALUE_FOR_31 = (float_z)1412.0;
    const float_z EXPECTED_VALUE_FOR_32 = (float_z)1470.0;
    const float_z EXPECTED_VALUE_FOR_33 = (float_z)1528.0;

    // [Execution]
    SpaceConversionMatrix matrixUT = OPERAND1 * OPERAND2;

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
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const SpaceConversionMatrix OPERAND1(Matrix4x4(SFloat::_1,    SFloat::_2,    SFloat::_3,    SFloat::_4,
                                                         SFloat::_5,    SFloat::_6,    SFloat::_7,    SFloat::_8,
                                                         SFloat::_9,    SFloat::_10,   (float_z)11.0, (float_z)12.0,
                                                         (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0));

    const SpaceConversionMatrix OPERAND2(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)20.0,
                                                         (float_z)21.0, (float_z)22.0, (float_z)23.0, (float_z)24.0,
                                                         (float_z)25.0, (float_z)26.0, (float_z)27.0, (float_z)28.0,
                                                         (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0));

    // [Execution]
    SpaceConversionMatrix matrix1UT = OPERAND1 * OPERAND2;
    SpaceConversionMatrix matrix2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_CommonMatricesAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const Matrix4x4 OPERAND1(SFloat::_1,    SFloat::_2,    SFloat::_3,    SFloat::_4,
                                  SFloat::_5,    SFloat::_6,    SFloat::_7,    SFloat::_8,
                                  SFloat::_9,    SFloat::_10,   (float_z)11.0, (float_z)12.0,
                                  (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const SpaceConversionMatrix OPERAND2(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)20.0,
                                                         (float_z)21.0, (float_z)22.0, (float_z)23.0, (float_z)24.0,
                                                         (float_z)25.0, (float_z)26.0, (float_z)27.0, (float_z)28.0,
                                                         (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0));

    const float_z EXPECTED_VALUE_FOR_00 = (float_z)250.0;
    const float_z EXPECTED_VALUE_FOR_01 = (float_z)260.0;
    const float_z EXPECTED_VALUE_FOR_02 = (float_z)270.0;
    const float_z EXPECTED_VALUE_FOR_03 = (float_z)280.0;
    const float_z EXPECTED_VALUE_FOR_10 = (float_z)618.0;
    const float_z EXPECTED_VALUE_FOR_11 = (float_z)644.0;
    const float_z EXPECTED_VALUE_FOR_12 = (float_z)670.0;
    const float_z EXPECTED_VALUE_FOR_13 = (float_z)696.0;
    const float_z EXPECTED_VALUE_FOR_20 = (float_z)986.0;
    const float_z EXPECTED_VALUE_FOR_21 = (float_z)1028.0;
    const float_z EXPECTED_VALUE_FOR_22 = (float_z)1070.0;
    const float_z EXPECTED_VALUE_FOR_23 = (float_z)1112.0;
    const float_z EXPECTED_VALUE_FOR_30 = (float_z)1354.0;
    const float_z EXPECTED_VALUE_FOR_31 = (float_z)1412.0;
    const float_z EXPECTED_VALUE_FOR_32 = (float_z)1470.0;
    const float_z EXPECTED_VALUE_FOR_33 = (float_z)1528.0;

    // [Execution]
    SpaceConversionMatrix matrixUT(OPERAND1);
    matrixUT *= OPERAND2;

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
/// Checks that product operation is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_ProductIsNotCommutative_Test )
{
    // [Preparation]
    const SpaceConversionMatrix OPERAND1(Matrix4x4(SFloat::_1,    SFloat::_2,    SFloat::_3,    SFloat::_4,
                                                         SFloat::_5,    SFloat::_6,    SFloat::_7,    SFloat::_8,
                                                         SFloat::_9,    SFloat::_10,   (float_z)11.0, (float_z)12.0,
                                                         (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0));

    const SpaceConversionMatrix OPERAND2(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)20.0,
                                                         (float_z)21.0, (float_z)22.0, (float_z)23.0, (float_z)24.0,
                                                         (float_z)25.0, (float_z)26.0, (float_z)27.0, (float_z)28.0,
                                                         (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0));

    // [Execution]
    SpaceConversionMatrix matrix1UT(OPERAND1);
    matrix1UT *= OPERAND2;
    SpaceConversionMatrix matrix2UT(OPERAND2);
    matrix2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( matrix1UT != matrix2UT );
}

/// <summary>
/// Checks if a matrix object is correctly multiplied and assigned when using itself (the object) as the other operand.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_MatrixObjectIsCorrectlyMultipliedAndAssignedToItself_Test )
{
    // [Preparation]
    const SpaceConversionMatrix OPERAND(Matrix4x4(SFloat::_1,    SFloat::_2,    SFloat::_3,    SFloat::_4,
                             SFloat::_5,    SFloat::_6,    SFloat::_7,    SFloat::_8,
                             SFloat::_9,    SFloat::_10,   (float_z)11.0, (float_z)12.0,
                             (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0));

    const SpaceConversionMatrix EXPECTED_VALUE = OPERAND * OPERAND;

	// [Execution]
    SpaceConversionMatrix matrixUT = OPERAND;
    matrixUT *= matrixUT;

    // [Verification]
    BOOST_CHECK(matrixUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE ( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE ( SetWorldSpaceMatrix1_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetNullMatrix();
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_ResultIsDifferentDependingOnQuaternionNormalization_Test )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    SpaceConversionMatrix matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    SpaceConversionMatrix matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    SpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, Quaternion(ROTATION_ANGLE, SFloat::_0, SFloat::_0), SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, Quaternion(SFloat::_0, ROTATION_ANGLE, SFloat::_0), SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, Quaternion(SFloat::_0, SFloat::_0, ROTATION_ANGLE), SCALE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix1_CompositionOrderIsScaleRotationTranslation_Test )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    SpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    SpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(Vector3::GetNullVector(), ROTATION, Vector3::GetVectorOfOnes());
    SpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(Vector3::GetNullVector(), Quaternion::GetIdentity(), SCALE);

    const SpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // [Preparation]

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // [Preparation]

    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // [Preparation]

    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE ( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // [Preparation]

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE ( SetWorldSpaceMatrix2_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // [Preparation]

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // [Preparation]

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetNullMatrix();
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_ResultIsDifferentDependingOnQuaternionNormalization_Test )
{
    // [Preparation]

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    SpaceConversionMatrix matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    SpaceConversionMatrix matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.SetWorldSpaceMatrix(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    SpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, Quaternion(ROTATION_ANGLE, SFloat::_0, SFloat::_0), SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, Quaternion(SFloat::_0, ROTATION_ANGLE, SFloat::_0), SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, Quaternion(SFloat::_0, SFloat::_0, ROTATION_ANGLE), SCALE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix2_CompositionOrderIsScaleRotationTranslation_Test )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    SpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    SpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(Vector3::GetNullVector(), ROTATION, Vector3::GetVectorOfOnes());
    SpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(Vector3::GetNullVector(), Quaternion::GetIdentity(), SCALE);

    const SpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize());
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // [Preparation]

    const Matrix4x4 TRANSLATION = Matrix4x4::GetNullMatrix();
    const Matrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    const Matrix3x3 SCALE = Matrix3x3::GetNullMatrix();

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetNullMatrix();
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SFloat::_0, ROTATION_ANGLE, SFloat::_0);
    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SFloat::_0, SFloat::_0, ROTATION_ANGLE);

    SpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix3_CompositionOrderIsScaleRotationTranslation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    const Matrix4x4 NEUTRAL_TRANSLATION = Matrix4x4::GetNullMatrix();
    const RotationMatrix3x3 NEUTRAL_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 NEUTRAL_SCALE = ScalingMatrix3x3::GetIdentity();

    SpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const SpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize());
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // [Preparation]

    const Matrix4x4 TRANSLATION = Matrix4x4::GetNullMatrix();
    const Matrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    const Matrix3x3 SCALE = Matrix3x3::GetNullMatrix();

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetNullMatrix();
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_Y(SFloat::_0, ROTATION_ANGLE, SFloat::_0);
    const RotationMatrix3x3 ROTATION_QUATERNION_AROUND_Z(SFloat::_0, SFloat::_0, ROTATION_ANGLE);

    SpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix4_CompositionOrderIsScaleRotationTranslation_Test )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    const Matrix4x4 NEUTRAL_TRANSLATION = Matrix4x4::GetNullMatrix();
    const RotationMatrix3x3 NEUTRAL_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 NEUTRAL_SCALE = ScalingMatrix3x3::GetIdentity();

    SpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const SpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_TransformationIsCorrectlyBuiltFromCommonTransformations_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_1, SFloat::_2, SFloat::_3), Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> ROTATION(Vector3::GetNullVector(), Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> SCALE(Vector3::GetNullVector(), Quaternion::GetIdentity(), Vector3(SFloat::_8, SFloat::_9, SFloat::_10));

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> ROTATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> SCALE = TransformationMatrix<Matrix4x4>::GetIdentity();

    const Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsTranslation_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION = TransformationMatrix<Matrix4x4>(Vector3(SFloat::_1, SFloat::_2, SFloat::_3), Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> ROTATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> SCALE = TransformationMatrix<Matrix4x4>::GetIdentity();

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsRotation_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> ROTATION(Vector3::GetNullVector(), Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> SCALE = TransformationMatrix<Matrix4x4>::GetIdentity();

    Matrix4x4 EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[0][3] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[1][3] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[2][3] = SFloat::_0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_CorrectResultObtainedWhenOnlyContainsScale_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> ROTATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> SCALE = TransformationMatrix<Matrix4x4>(Vector3::GetNullVector(), Quaternion::GetIdentity(), Vector3(SFloat::_2, SFloat::_3, SFloat::_4));

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that zero matrix (whose 3,3 element equals one) is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_ZeroMatrixWhoseElement33EqualsOneIsObtainedWhenInputsEqualZero_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION(Matrix4x4::GetNullMatrix());
    const TransformationMatrix<Matrix4x4> ROTATION(Matrix4x4::GetNullMatrix());
    const TransformationMatrix<Matrix4x4> SCALE(Matrix4x4::GetNullMatrix());

    Matrix4x4 EXPECTED_VALUE = Matrix4x4::GetNullMatrix();
    EXPECTED_VALUE.ij[3][3] = SFloat::_1;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_FollowsLeftHandedRules_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const TransformationMatrix<Matrix4x4> TRANSLATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> SCALE = TransformationMatrix<Matrix4x4>::GetIdentity();

    const TransformationMatrix<Matrix4x4> ROTATION_QUATERNION_AROUND_X(Vector3::GetNullVector(), Quaternion(ROTATION_ANGLE, SFloat::_0, SFloat::_0).Normalize(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> ROTATION_QUATERNION_AROUND_Y(Vector3::GetNullVector(), Quaternion(SFloat::_0, ROTATION_ANGLE, SFloat::_0).Normalize(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> ROTATION_QUATERNION_AROUND_Z(Vector3::GetNullVector(), Quaternion(SFloat::_0, SFloat::_0, ROTATION_ANGLE).Normalize(), Vector3::GetVectorOfOnes());

    SpaceConversionMatrix ROTATION_AROUND_X;
    ROTATION_AROUND_X.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    SpaceConversionMatrix ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.SetWorldSpaceMatrix(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0);

    const Vector3 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0);
    const Vector3 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0);

    // [Execution]
    Vector3 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector3 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector3 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint1UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_X.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint2UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y.z) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.x, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.x) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.y, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.y) );
    BOOST_CHECK( SFloat::AreEqual(vPoint3UT.z, EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z.z) );
}

/// <summary>
/// Checks that the composition order of the transformations corresponds to scale, then rotation and then translation.
/// </summary>
ZTEST_CASE( SetWorldSpaceMatrix5_CompositionOrderIsScaleRotationTranslation_Test )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_1, SFloat::_2, SFloat::_3), Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> ROTATION(Vector3::GetNullVector(), Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7), Vector3::GetVectorOfOnes());
    const TransformationMatrix<Matrix4x4> SCALE(Vector3::GetNullVector(), Quaternion::GetIdentity(), Vector3(SFloat::_8, SFloat::_9, SFloat::_10));

    const TransformationMatrix<Matrix4x4> NEUTRAL_TRANSLATION = TransformationMatrix<Matrix4x4>::GetNullMatrix();
    const TransformationMatrix<Matrix4x4> NEUTRAL_ROTATION = TransformationMatrix<Matrix4x4>::GetIdentity();
    const TransformationMatrix<Matrix4x4> NEUTRAL_SCALE = TransformationMatrix<Matrix4x4>::GetIdentity();

    SpaceConversionMatrix TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.SetWorldSpaceMatrix(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix ROTATION_MATRIX;
    ROTATION_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    SpaceConversionMatrix SCALE_MATRIX;
    SCALE_MATRIX.SetWorldSpaceMatrix(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const SpaceConversionMatrix EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetWorldSpaceMatrix(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the view matrix is correctly built when using common vectors as up, point of view and target.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix1_ViewMatrixIsCorrectlyBuiltFromCommonInputVectors_Test )
{
    // [Preparation]
    const Vector3 UP_DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 POINT_OF_VIEW = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Vector3 TARGET = Vector3(SFloat::_7, SFloat::_8, SFloat::_9);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SFloat::_1, SFloat::_2, SFloat::_3);
    // D3DXVECTOR3 vEye(SFloat::_4, SFloat::_5, SFloat::_6);
    // D3DXVECTOR3 vTarget(SFloat::_7, SFloat::_8, SFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtLH(&viewMatrix, &vEye, &vTarget, &vUp);

    const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4((float_z)-0.40824829046386302, (float_z)-0.70710678118654746, (float_z)0.57735026918962573, SFloat::_0,
                                                               (float_z)0.81649658092772603,  SFloat::_0,                   (float_z)0.57735026918962573, SFloat::_0,
                                                               (float_z)-0.40824829046386302, (float_z)0.70710678118654746,  (float_z)0.57735026918962573, SFloat::_0,
                                                               SFloat::_0,                   (float_z)-1.4142135623730949,  (float_z)-8.6602540378443855, SFloat::_1));

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

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

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when "up" vector is null.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix1_AssertionFailsWhenUpVectorIsNull_Test )
{
    // [Preparation]
    const Vector3 UP_DIRECTION = Vector3(SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 POINT_OF_VIEW = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 TARGET = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFailed = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the point of view equals target vector.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix1_AssertionFailsWhenPointOfViewEqualsTarget_Test )
{
    // [Preparation]
    const Vector3 UP_DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 POINT_OF_VIEW = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Vector3 TARGET = POINT_OF_VIEW;

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFailed = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the view matrix is correctly built when using common vectors as up, point of view and target.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix2_ViewMatrixIsCorrectlyBuiltFromCommonInputVectors_Test )
{
    // [Preparation]
    const Vector4 UP_DIRECTION = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_10);
    const Vector4 POINT_OF_VIEW = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, (float_z)11.0);
    const Vector4 TARGET = Vector4(SFloat::_7, SFloat::_8, SFloat::_9, (float_z)12.0);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SFloat::_1, SFloat::_2, SFloat::_3);
    // D3DXVECTOR3 vEye(SFloat::_4, SFloat::_5, SFloat::_6);
    // D3DXVECTOR3 vTarget(SFloat::_7, SFloat::_8, SFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtLH(&viewMatrix, &vEye, &vTarget, &vUp);

    const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4((float_z)-0.40824829046386302, (float_z)-0.70710678118654746, (float_z)0.57735026918962573, SFloat::_0,
                                                               (float_z)0.81649658092772603,  SFloat::_0,                   (float_z)0.57735026918962573, SFloat::_0,
                                                               (float_z)-0.40824829046386302, (float_z)0.70710678118654746,  (float_z)0.57735026918962573, SFloat::_0,
                                                               SFloat::_0,                   (float_z)-1.4142135623730949,  (float_z)-8.6602540378443855, SFloat::_1));

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

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

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when "up" vector is null.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix2_AssertionFailsWhenUpVectorIsNull_Test )
{
    // [Preparation]
    const Vector4 UP_DIRECTION = Vector4::GetNullVector();
    const Vector4 POINT_OF_VIEW = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 TARGET = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFailed = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the point of view equals target vector.
/// </summary>
ZTEST_CASE( SetViewSpaceMatrix2_AssertionFailsWhenPointOfViewEqualsTarget_Test )
{
    // [Preparation]
    const Vector4 UP_DIRECTION = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 POINT_OF_VIEW = Vector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    const Vector4 TARGET = POINT_OF_VIEW;

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFailed = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, EXPECTED_VALUE );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the projection matrix is correctly built when using common inputs.
/// </summary>
ZTEST_CASE( SetProjectionSpaceMatrix_ProjectionMatrixIsCorrectlyBuiltFromCommonInputs_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = SFloat::_2;
    const float_z ASPECT_RATIO = SFloat::_4;

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z VERTICAL_FOV = SAngle::RadiansToDegrees(SFloat::_3);
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z VERTICAL_FOV = SFloat::_3;
    #endif

    // Reference values obtained by using DirectX SDK:
    // float_z fNearClipPlane = SFloat::_1;
    // float_z fFarClipPlane = SFloat::_2;
    // float_z fVerticalFOV = SFloat::_3;
    // float_z fAspectRatio = SFloat::_4;
    // D3DXMATRIX projectionMatrix;
    // D3DXMatrixPerspectiveFovLH(&projectionMatrix, fVerticalFOV, fAspectRatio, fNearClipPlane, fFarClipPlane);

    const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4((float_z)0.017728711075663112, SFloat::_0,                   SFloat::_0,  SFloat::_0,
                                                               (float_z)SFloat::_0,          (float_z)0.070914844302652449, SFloat::_0,  SFloat::_0,
                                                               SFloat::_0,                   SFloat::_0,                   SFloat::_2,  SFloat::_1,
                                                               SFloat::_0,                   SFloat::_0,                   -SFloat::_2, SFloat::_0));

    // [Execution]
    SpaceConversionMatrix matrixUT;
    matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);
    
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

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the near clip plane equals the far clip plane.
/// </summary>
ZTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenNearAndFarClipPlanesAreTheSame_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = NEAR_CLIP_PLANE;
    const float_z VERTICAL_FOV = SFloat::_3;
    const float_z ASPECT_RATIO = SFloat::_4;

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFail = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(const AssertException&)
    {
        bAssertionFail = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the vertical FOV equals zero.
/// </summary>
ZTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenVerticalFovEqualsZero_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = SFloat::_1;
    const float_z VERTICAL_FOV = SFloat::_0;
    const float_z ASPECT_RATIO = SFloat::_4;

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFail = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(const AssertException&)
    {
        bAssertionFail = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

/// <summary>
/// Checks that the assertion fails when the aspect ratio equals zero.
/// </summary>
ZTEST_CASE( SetProjectionSpaceMatrix_AssertionFailsWhenAspectRatioEqualsZero_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = SFloat::_1;
    const float_z VERTICAL_FOV = SFloat::_3;
    const float_z ASPECT_RATIO = SFloat::_0;

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bAssertionFail = false;
    SpaceConversionMatrix matrixUT;

    try
    {
        matrixUT.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, VERTICAL_FOV, ASPECT_RATIO);
    }
    catch(const AssertException&)
    {
        bAssertionFail = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFail, EXPECTED_VALUE );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the hand convention of the transformations represented by the matrix are correctly switched.
/// </summary>
ZTEST_CASE ( SwitchHandConventionWorldSpaceMatrix_MatrixHandConventionIsCorrectlySwitched_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_X = SAngle::_45;
        const float_z ROTATION_Y = SAngle::_60;
        const float_z ROTATION_Z = SAngle::_90;
    #else
        const float_z ROTATION_X = SAngle::_QuarterPi;
        const float_z ROTATION_Y = SAngle::_ThirdPi;
        const float_z ROTATION_Z = SAngle::_HalfPi;
    #endif

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> INVERTED_TRANSLATION(SFloat::_1, SFloat::_2, -SFloat::_3);
    const RotationMatrix3x3 INVERTED_ROTATION = RotationMatrix3x3(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert();

    const SpaceConversionMatrix TRANSFORMATION(SCALE * ROTATION * TRANSLATION);
    const SpaceConversionMatrix EXPECTED_RESULT(SCALE * INVERTED_ROTATION * INVERTED_TRANSLATION);

    // [Execution]
    SpaceConversionMatrix matrixUT = TRANSFORMATION.SwitchHandConventionWorldSpaceMatrix();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], EXPECTED_RESULT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], EXPECTED_RESULT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], EXPECTED_RESULT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], EXPECTED_RESULT.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], EXPECTED_RESULT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], EXPECTED_RESULT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], EXPECTED_RESULT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], EXPECTED_RESULT.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], EXPECTED_RESULT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], EXPECTED_RESULT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], EXPECTED_RESULT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], EXPECTED_RESULT.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], EXPECTED_RESULT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_RESULT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_RESULT.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_RESULT.ij[3][3]) );
}

/// <summary>
/// Checks that a twice switched matrix equals original value.
/// </summary>
ZTEST_CASE ( SwitchHandConventionWorldSpaceMatrix_SwitchingIsReversible_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_X = SAngle::_45;
        const float_z ROTATION_Y = SAngle::_60;
        const float_z ROTATION_Z = SAngle::_90;
    #else
        const float_z ROTATION_X = SAngle::_QuarterPi;
        const float_z ROTATION_Y = SAngle::_ThirdPi;
        const float_z ROTATION_Z = SAngle::_HalfPi;
    #endif

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const SpaceConversionMatrix TRANSFORMATION(SCALE * ROTATION * TRANSLATION);

    // [Execution]
    SpaceConversionMatrix matrixUT = TRANSFORMATION.SwitchHandConventionWorldSpaceMatrix().SwitchHandConventionWorldSpaceMatrix();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], TRANSFORMATION.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], TRANSFORMATION.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], TRANSFORMATION.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], TRANSFORMATION.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], TRANSFORMATION.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], TRANSFORMATION.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], TRANSFORMATION.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], TRANSFORMATION.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], TRANSFORMATION.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], TRANSFORMATION.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], TRANSFORMATION.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], TRANSFORMATION.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], TRANSFORMATION.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], TRANSFORMATION.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], TRANSFORMATION.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], TRANSFORMATION.ij[3][3]) );
}

/// <summary>
/// Checks that the view matrix is correctly converted from left-handed to right-handed rules and vice versa.
/// </summary>
ZTEST_CASE( SwitchHandConventionViewSpaceMatrix_HandRulesAreCorrectlySwitched_Test )
{
    // [Preparation]
    const Vector3 UP_DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 POINT_OF_VIEW = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Vector3 TARGET = Vector3(SFloat::_7, SFloat::_8, SFloat::_9);

    // Reference values obtained by using DirectX SDK:
    // D3DXVECTOR3 vUp(SFloat::_1, SFloat::_2, SFloat::_3);
    // D3DXVECTOR3 vEye(SFloat::_4, SFloat::_5, SFloat::_6);
    // D3DXVECTOR3 vTarget(SFloat::_7, SFloat::_8, SFloat::_9);
    // D3DXMATRIX viewMatrix;
    // D3DXMatrixLookAtRH(&viewMatrix, &vEye, &vTarget, &vUp);

    SpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4((float_z)0.40824829046386296,  (float_z)-0.70710678118654735, (float_z)-0.57735026918962573, SFloat::_0,
                                                             (float_z)-0.81649658092772592, SFloat::_0,                   (float_z)-0.57735026918962573, SFloat::_0,
                                                             (float_z)0.40824829046386296,  (float_z)0.70710678118654735,  (float_z)-0.57735026918962573, SFloat::_0,
                                                             SFloat::_0,                   (float_z)-1.414213562373094,   (float_z)8.6602540378443837,   SFloat::_1));

    // [Execution]
    SpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionViewSpaceMatrix();

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
    // This different check was necessary due to a different precision
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1], 1e-5) );

    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], EXPECTED_VALUE.ij[3][3]) );
}

/// <summary>
/// Checks that a twice switched matrix equals original value.
/// </summary>
ZTEST_CASE( SwitchHandConventionViewSpaceMatrix_SwitchingIsReversible_Test )
{
    // [Preparation]
    const Vector3 UP_DIRECTION = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 POINT_OF_VIEW = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Vector3 TARGET = Vector3(SFloat::_7, SFloat::_8, SFloat::_9);

    SpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetViewSpaceMatrix(POINT_OF_VIEW, TARGET, UP_DIRECTION);

    #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
        const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4(-0.40824845f, -0.70710713f, 0.57735032f, SFloat::_0,
                                                                   0.81649691f,  SFloat::_0,  0.57735032f, SFloat::_0,
                                                                   -0.40824845f, 0.70710713f,  0.57735032f, SFloat::_0,
                                                                   SFloat::_0,  -1.4142156f,  -8.6602573f, SFloat::_1));

    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
        const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4(-0.40824829046386291, -0.70710678118654724, 0.57735026918962573, SFloat::_0,
                                                                   0.81649658092772581,  SFloat::_0,          0.57735026918962573, SFloat::_0,
                                                                   -0.40824829046386291, 0.70710678118654724,  0.57735026918962573, SFloat::_0,
                                                                   SFloat::_0,          -1.4142135623730927,  -8.6602540378443837, SFloat::_1));
    #endif

    // [Execution]
    SpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionViewSpaceMatrix().SwitchHandConventionViewSpaceMatrix();

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
/// Checks that the projection matrix is correctly converted from left-handed to right-handed rules and vice versa.
/// </summary>
ZTEST_CASE( SwitchHandConventionProjectionSpaceMatrix_HandRulesAreCorrectlySwitched_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = SFloat::_2;
    const float_z ASPECT_RATIO = SFloat::_4;

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            const float_z VERTICAL_FOV = SAngle::RadiansToDegrees(SFloat::_3);
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z VERTICAL_FOV = SFloat::_3;
    #endif

    // Reference values obtained by using DirectX SDK:
    // float_z fNearClipPlane = SFloat::_1;
    // float_z fFarClipPlane = SFloat::_2;
    // float_z fVerticalFOV = SFloat::_3;
    // float_z fAspectRatio = SFloat::_4;
    // D3DXMATRIX projectionMatrix;
    // D3DXMatrixPerspectiveFovRH(&projectionMatrix, fVerticalFOV, fAspectRatio, fNearClipPlane, fFarClipPlane);

    SpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);

    const SpaceConversionMatrix EXPECTED_VALUE(Matrix4x4((float_z)0.017728711075663112, SFloat::_0,                   SFloat::_0,  SFloat::_0,
                                                               (float_z)SFloat::_0,          (float_z)0.070914844302652449, SFloat::_0,  SFloat::_0,
                                                               SFloat::_0,                   SFloat::_0,                   -SFloat::_2, -SFloat::_1,
                                                               SFloat::_0,                   SFloat::_0,                   -SFloat::_2, SFloat::_0));

    // [Execution]
    SpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionProjectionSpaceMatrix();

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
/// Checks that a twice switched matrix equals original value.
/// </summary>
ZTEST_CASE( SwitchHandConventionProjectionSpaceMatrix_SwitchingIsReversible_Test )
{
    // [Preparation]
    const float_z NEAR_CLIP_PLANE = SFloat::_1;
    const float_z FAR_CLIP_PLANE = SFloat::_2;
    const float_z VERTICAL_FOV = SFloat::_3;
    const float_z ASPECT_RATIO = SFloat::_4;

    SpaceConversionMatrix ORIGINAL_VALUE;
    ORIGINAL_VALUE.SetProjectionSpaceMatrix(NEAR_CLIP_PLANE, FAR_CLIP_PLANE, ASPECT_RATIO, VERTICAL_FOV);

    // [Execution]
    SpaceConversionMatrix matrixUT = ORIGINAL_VALUE.SwitchHandConventionProjectionSpaceMatrix().SwitchHandConventionProjectionSpaceMatrix();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], ORIGINAL_VALUE.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], ORIGINAL_VALUE.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], ORIGINAL_VALUE.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][3], ORIGINAL_VALUE.ij[0][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], ORIGINAL_VALUE.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], ORIGINAL_VALUE.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], ORIGINAL_VALUE.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][3], ORIGINAL_VALUE.ij[1][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], ORIGINAL_VALUE.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], ORIGINAL_VALUE.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], ORIGINAL_VALUE.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][3], ORIGINAL_VALUE.ij[2][3]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], ORIGINAL_VALUE.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], ORIGINAL_VALUE.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], ORIGINAL_VALUE.ij[3][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][3], ORIGINAL_VALUE.ij[3][3]) );
}

// End - Test Suite: SpaceConversionMatrix
ZTEST_SUITE_END()
