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

#include "ZMath/TransformationMatrix3x3.h"

#include "ZMath/Vector2.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( TransformationMatrix3x3_TestSuite )

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

    const Matrix3x3 EXPECTED_VALUE(EXPECTED_VALUE_FOR_00, EXPECTED_VALUE_FOR_01, EXPECTED_VALUE_FOR_02,
                                        EXPECTED_VALUE_FOR_10, EXPECTED_VALUE_FOR_11, EXPECTED_VALUE_FOR_12,
                                        EXPECTED_VALUE_FOR_20, EXPECTED_VALUE_FOR_21, EXPECTED_VALUE_FOR_22);

    const TransformationMatrix3x3 MATRIX_TO_COPY(EXPECTED_VALUE);

    // [Execution]
    TransformationMatrix3x3 matrixUT = MATRIX_TO_COPY;

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
    TransformationMatrix3x3 matrixUT(EXPECTED_VALUE);

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
/// Checks that the matrix is correctly created when using a combination of common translation, rotation and scaling matrices.
/// </summary>
ZTEST_CASE ( Constructor4_MatrixIsCorrectlyCreatedFromCommonTranslationRotationAndScale_Test )
{
    // [Preparation]
    const Vector2 TRANSLATION(SFloat::_2, SFloat::_3);
    const Vector2 SCALE(SFloat::_4, SFloat::_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_45;
    #else
        const float_z ROTATION = SAngle::_QuarterPi;
    #endif

    const Matrix3x3 EXPECTED_VALUE((float_z)2.8284271247461903,  (float_z)2.8284271247461898, SFloat::_0,
                                        (float_z)-3.5355339059327373, (float_z)3.5355339059327378, SFloat::_0,
                                        SFloat::_2,                  SFloat::_3,                 SFloat::_1);

    // [Execution]
    TransformationMatrix3x3 matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the matrix is correctly created when using a combination of common translation, rotation and scaling matrices.
/// </summary>
ZTEST_CASE ( Constructor4_IdentityMatrixIsObtainedWhenUsingNeutralTransformations_Test )
{
    // [Preparation]

    const Vector2 TRANSLATION(SFloat::_0, SFloat::_0);
    const Vector2 SCALE(SFloat::_1, SFloat::_1);
    const float_z ROTATION = SFloat::_0;

    const TransformationMatrix3x3 EXPECTED_VALUE = TransformationMatrix3x3::GetIdentity();

    // [Execution]
    TransformationMatrix3x3 matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the rotation contained in the matrix follows left-handed rules (counter-clockwise).
/// </summary>
ZTEST_CASE ( Constructor4_RotationFollowsLeftHandedRules_Test )
{
    // [Preparation]
    const Vector2 TRANSLATION(SFloat::_0, SFloat::_0);
    const Vector2 SCALE(SFloat::_1, SFloat::_1);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_45;
    #else
        const float_z ROTATION = SAngle::_QuarterPi;
    #endif

    const Vector2 POINT = Vector2(SFloat::_1, SFloat::_0);

    // [Execution]
    TransformationMatrix3x3 matrix(TRANSLATION, ROTATION, SCALE);
    Vector2 rotatedPointUT = POINT.Transform(matrix);

    // [Verification]
    BOOST_CHECK(SFloat::IsGreaterOrEquals(rotatedPointUT.x, SFloat::_0));
    BOOST_CHECK(SFloat::IsGreaterOrEquals(rotatedPointUT.y, SFloat::_0));
}

/// <summary>
/// Checks that the rotation data is correctly generated (neutral translation and scale used).
/// </summary>
ZTEST_CASE ( Constructor4_RotationDataIsCorrectlyGenerated_Test )
{
    // [Preparation]
    const Vector2 TRANSLATION(SFloat::_0, SFloat::_0);
    const Vector2 SCALE(SFloat::_1, SFloat::_1);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION = SAngle::_60;
    #else
        const float_z ROTATION = SAngle::_ThirdPi;
    #endif

    const Matrix3x3 EXPECTED_VALUE(SFloat::_0_5,                (float_z)0.8660254037844386, SFloat::_0,
                                        (float_z)-0.8660254037844386, SFloat::_0_5,               SFloat::_0,
                                        SFloat::_0,                  SFloat::_0,                 SFloat::_1);

    // [Execution]
    TransformationMatrix3x3 matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the scaling data is correctly generated (neutral rotation and translation used).
/// </summary>
ZTEST_CASE ( Constructor4_ScalingDataIsCorrectlyGenerated_Test )
{
    // [Preparation]

    const Vector2 TRANSLATION(SFloat::_0, SFloat::_0);
    const Vector2 SCALE(SFloat::_2, SFloat::_3);
    const float_z ROTATION = SFloat::_0;

    const Matrix3x3 EXPECTED_VALUE(SFloat::_2, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_3, SFloat::_0,
                                        SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix3x3 matrixUT(TRANSLATION, ROTATION, SCALE);

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
/// Checks that the translation data is correctly generated (neutral rotation and scale used).
/// </summary>
ZTEST_CASE ( Constructor4_TranslationDataIsCorrectlyGenerated_Test )
{
    // [Preparation]

    const Vector2 TRANSLATION(SFloat::_2, SFloat::_3);
    const Vector2 SCALE(SFloat::_1, SFloat::_1);
    const float_z ROTATION = SFloat::_0;

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1, SFloat::_0, SFloat::_0,
                                        SFloat::_0, SFloat::_1, SFloat::_0,
                                        SFloat::_2, SFloat::_3, SFloat::_1);

    // [Execution]
    TransformationMatrix3x3 matrixUT(TRANSLATION, ROTATION, SCALE);

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
    TransformationMatrix3x3 matrixUT = TransformationMatrix3x3::GetIdentity();

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
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
ZTEST_CASE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test )
{
    // [Preparation]

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1,  SFloat::_2,    SFloat::_3,
                                        SFloat::_4,  SFloat::_5,    SFloat::_6,
                                        SFloat::_7,  SFloat::_8,    SFloat::_9);

    // [Execution]
    TransformationMatrix3x3 matrixUT;
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
/// Checks that obtained transformations are neutral when the transformation matrix is the Identity.
/// </summary>
ZTEST_CASE ( Decompose_ObtainedTransformationsAreNeutralWhenMatrixIsIdentity_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 IDENTITY = TransformationMatrix3x3::GetIdentity();
    const Vector2 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0);
    const Vector2 EXPECTED_SCALE(SFloat::_1, SFloat::_1);
    const float_z EXPECTED_ROTATION = SFloat::_0;

    // [Execution]
    Vector2 vTranslationUT(SFloat::_1, SFloat::_1);
    Vector2 vScaleUT;
    float_z fRotationUT = SFloat::_10;
    IDENTITY.Decompose(vTranslationUT, fRotationUT, vScaleUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_TRANSLATION.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_TRANSLATION.y);
    BOOST_CHECK_EQUAL(vScaleUT.x, EXPECTED_SCALE.x);
    BOOST_CHECK_EQUAL(vScaleUT.y, EXPECTED_SCALE.y);
    BOOST_CHECK_EQUAL(fRotationUT, EXPECTED_ROTATION);
}

/// <summary>
/// Checks that transformations obtained from a common transformation matrix are correct.
/// </summary>
ZTEST_CASE ( Decompose_CorrectTransformationsAreObtainedFromCommonMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3((float_z)2.8284271247461903,  (float_z)2.8284271247461898, SFloat::_0,
                                                                         (float_z)-3.5355339059327373, (float_z)3.5355339059327378, SFloat::_0,
                                                                         SFloat::_2,                  SFloat::_3,                 SFloat::_1) );
    const Vector2 EXPECTED_TRANSLATION(SFloat::_2, SFloat::_3);
    const Vector2 EXPECTED_SCALE(SFloat::_4, SFloat::_5);

    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION = SAngle::_45;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION = SAngle::_QuarterPi;
    #endif
    
    // [Execution]
    Vector2 vTranslationUT(SFloat::_1, SFloat::_1);
    Vector2 vScaleUT;
    float_z fRotationUT = SFloat::_10;
    TRANSFORMATION_MATRIX.Decompose(vTranslationUT, fRotationUT, vScaleUT);

    // [Verification]
    BOOST_CHECK(vTranslationUT == EXPECTED_TRANSLATION);
    BOOST_CHECK(vScaleUT == EXPECTED_SCALE);
    BOOST_CHECK( SFloat::AreEqual(fRotationUT, EXPECTED_ROTATION) );
}

/// <summary>
/// Checks that the rotation obtained from a transformation matrix that only contains rotation data is correct.
/// </summary>
ZTEST_CASE ( Decompose_CorrectRotationIsObtainedFromMatrixThatOnlyContainsRotation_Test )
{
    // [Preparation]
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_0_5,                (float_z)0.8660254037844386, SFloat::_0,
                                                                         (float_z)-0.8660254037844386, SFloat::_0_5,               SFloat::_0,
                                                                         SFloat::_0,                  SFloat::_0,                 SFloat::_1) );
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION = SAngle::_60;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION = SAngle::_ThirdPi;
    #endif
        
        const TransformationMatrix3x3 TRANSFORMATION_MATRIX2(Vector2(), EXPECTED_ROTATION, Vector2(1, 1));
    // [Execution]
    Vector2 vTranslationAux;
    Vector2 vScaleAux;
    float_z fRotationUT = SFloat::_0;
    TRANSFORMATION_MATRIX.Decompose(vTranslationAux, fRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationUT, EXPECTED_ROTATION) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale was null (x and y equalled zero).
/// </summary>
ZTEST_CASE ( Decompose_AssertionFailsWhenMatrixScaleIsNull_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Vector2(SFloat::_1, SFloat::_2),
                                                          SFloat::_3,
                                                          Vector2(SFloat::_0, SFloat::_0) );

    float_z fRotation;
    Vector2 vTranslation;
    Vector2 vScale;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRANSFORMATION_MATRIX.Decompose(vTranslation, fRotation, vScale);
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
/// Checks that the translation obtained from a transformation matrix that only contains translation data is correct.
/// </summary>
ZTEST_CASE ( Decompose_CorrectTranslationIsObtainedFromMatrixThatOnlyContainsTranslation_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                                         SFloat::_0, SFloat::_1, SFloat::_0,
                                                                         SFloat::_2, SFloat::_3, SFloat::_1) );
    const Vector2 EXPECTED_TRANSLATION(SFloat::_2, SFloat::_3);

    // [Execution]
    Vector2 vTranslationUT;
    Vector2 vScaleAux;
    float_z fRotationAux;
    TRANSFORMATION_MATRIX.Decompose(vTranslationUT, fRotationAux, vScaleAux);

    // [Verification]
    BOOST_CHECK(vTranslationUT == EXPECTED_TRANSLATION);
}

/// <summary>
/// Checks that the scale obtained from a transformation matrix that only contains scaling data is correct.
/// </summary>
ZTEST_CASE ( Decompose_CorrectScaleIsObtainedFromMatrixThatOnlyContainsScaling_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_4, SFloat::_0, SFloat::_0,
                                                                         SFloat::_0, SFloat::_5, SFloat::_0,
                                                                         SFloat::_0, SFloat::_0, SFloat::_1) );
    const Vector2 EXPECTED_SCALE(SFloat::_4, SFloat::_5);

    // [Execution]
    Vector2 vTranslationAux;
    Vector2 vScaleUT;
    float_z fRotationAux;
    TRANSFORMATION_MATRIX.Decompose(vTranslationAux, fRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK(vScaleUT == EXPECTED_SCALE);
}

/// <summary>
/// Checks that the translation obtained from a transformation matrix that only contains translation data is correct.
/// </summary>
ZTEST_CASE ( GetTranslation_CorrectTranslationIsObtainedFromMatrixThatOnlyContainsTranslation_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_1, SFloat::_0, SFloat::_0,
                                                                         SFloat::_0, SFloat::_1, SFloat::_0,
                                                                         SFloat::_2, SFloat::_3, SFloat::_1) );
    const Vector2 EXPECTED_TRANSLATION(SFloat::_2, SFloat::_3);

    // [Execution]
    Vector2 vTranslationUT;
    TRANSFORMATION_MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK(vTranslationUT == EXPECTED_TRANSLATION);
}

/// <summary>
/// Checks that translation obtained from a common transformation matrix is correct.
/// </summary>
ZTEST_CASE ( GetTranslation_CorrectTranslationIsObtainedFromCommonMatrix_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3((float_z)2.8284271,  (float_z)2.8284271, SFloat::_0,
                                                                         (float_z)-3.5355339, (float_z)3.5355339, SFloat::_0,
                                                                         SFloat::_2,          SFloat::_3,         SFloat::_1) );
    const Vector2 EXPECTED_TRANSLATION(SFloat::_2, SFloat::_3);

    // [Execution]
    Vector2 vTranslationUT;
    TRANSFORMATION_MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK(vTranslationUT == EXPECTED_TRANSLATION);
}

/// <summary>
/// Checks that the rotation obtained from a transformation matrix that only contains rotation data is correct.
/// </summary>
ZTEST_CASE ( GetRotation_CorrectRotationIsObtainedFromMatrixThatOnlyContainsRotation_Test )
{
    // [Preparation]
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_0_5,                (float_z)0.8660254037844386, SFloat::_0,
                                                                         (float_z)-0.8660254037844386, SFloat::_0_5,               SFloat::_0,
                                                                         SFloat::_0,                  SFloat::_0,                 SFloat::_1) );
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION = SAngle::_60;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION = SAngle::_ThirdPi;
    #endif

    // [Execution]
    float_z fRotationUT = SFloat::_0;
    TRANSFORMATION_MATRIX.GetRotation(fRotationUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationUT, EXPECTED_ROTATION) );
}

/// <summary>
/// Checks that rotation obtained from a common transformation matrix is correct.
/// </summary>
ZTEST_CASE ( GetRotation_CorrectRotationIsObtainedFromCommonMatrix_Test )
{
    // [Preparation]
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3((float_z)2.8284271,  (float_z)2.8284271, SFloat::_0,
                                                                         (float_z)-3.5355339, (float_z)3.5355339, SFloat::_0,
                                                                         SFloat::_2,          SFloat::_3,         SFloat::_1) );
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION = SAngle::_45;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION = SAngle::_QuarterPi;
    #endif

    // [Execution]
    float_z fRotationUT = SFloat::_0;
    TRANSFORMATION_MATRIX.GetRotation(fRotationUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationUT, EXPECTED_ROTATION) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the scale was null (x and y equalled zero).
/// </summary>
ZTEST_CASE ( GetRotation_AssertionFailsWhenMatrixScaleIsNull_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Vector2(SFloat::_1, SFloat::_2),
                                                          SFloat::_3,
                                                          Vector2(SFloat::_0, SFloat::_0) );

    float_z fRotation;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        TRANSFORMATION_MATRIX.GetRotation(fRotation);
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
/// Checks that the scale obtained from a transformation matrix that only contains scaling data is correct.
/// </summary>
ZTEST_CASE ( GetScale_CorrectScaleIsObtainedFromMatrixThatOnlyContainsScaling_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_4, SFloat::_0, SFloat::_0,
                                                                         SFloat::_0, SFloat::_5, SFloat::_0,
                                                                         SFloat::_0, SFloat::_0, SFloat::_1) );
    const Vector2 EXPECTED_SCALE(SFloat::_4, SFloat::_5);

    // [Execution]
    Vector2 vScaleUT;
    TRANSFORMATION_MATRIX.GetScale(vScaleUT);

    // [Verification]
    BOOST_CHECK(vScaleUT == EXPECTED_SCALE);
}

/// <summary>
/// Checks that scale obtained from a common transformation matrix is correct.
/// </summary>
ZTEST_CASE ( GetScale_CorrectScaleIsObtainedFromCommonMatrix_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3((float_z)2.8284271247461903,  (float_z)2.8284271247461898, SFloat::_0,
                                                                         (float_z)-3.5355339059327373, (float_z)3.5355339059327378, SFloat::_0,
                                                                         SFloat::_2,                  SFloat::_3,                 SFloat::_1) );

    const Vector2 EXPECTED_SCALE(SFloat::_4, SFloat::_5);

    // [Execution]
    Vector2 vScaleUT;
    TRANSFORMATION_MATRIX.GetScale(vScaleUT);

    // [Verification]
    BOOST_CHECK(vScaleUT == EXPECTED_SCALE);
}

/// <summary>
/// Checks that resulting matrix matches the expected value, when using a common transformation matrix.
/// </summary>
ZTEST_CASE ( SwitchHandConvention_CorrectResultIsObtainedWhenUsingCommonMatrix_Test )
{
    // [Preparation]

    const Matrix3x3 EXPECTED_VALUE(SFloat::_1,  -SFloat::_2, SFloat::_3,
                                        -SFloat::_4, SFloat::_5,  SFloat::_6,
                                        SFloat::_7,  SFloat::_8,  SFloat::_9);

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_1, SFloat::_2, SFloat::_3,
                                                                         SFloat::_4, SFloat::_5, SFloat::_6,
                                                                         SFloat::_7, SFloat::_8, SFloat::_9) );

    // [Execution]
    TransformationMatrix3x3 matrixUT = TRANSFORMATION_MATRIX.SwitchHandConvention();

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
/// Checks that the rotation is inverted, as hand-convention conversion requires.
/// </summary>
ZTEST_CASE ( SwitchHandConvention_RotationIsInverted_Test )
{
    // [Preparation]
    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_0_5,        (float_z)0.8660254, SFloat::_0,
                                                                         (float_z)-0.8660254, SFloat::_0_5,       SFloat::_0,
                                                                         SFloat::_0,          SFloat::_0,         SFloat::_1) );
    const Vector2 ROTATED_POINT = Vector2(SFloat::_1, SFloat::_0).Transform(TRANSFORMATION_MATRIX);

    // [Execution]
    TransformationMatrix3x3 matrix = TRANSFORMATION_MATRIX.SwitchHandConvention();
    Vector2 vRotatedPointAfterConversion = Vector2(SFloat::_1, SFloat::_0).Transform(matrix);

    // [Verification]
    BOOST_CHECK_EQUAL( vRotatedPointAfterConversion.x, ROTATED_POINT.x );
    BOOST_CHECK_EQUAL( vRotatedPointAfterConversion.y, -ROTATED_POINT.y );
}

/// <summary>
/// Checks that the rotation angle is the same even after inverting the rotation due to hand-convention conversion.
/// </summary>
ZTEST_CASE ( SwitchHandConvention_RotationAngleRemainsTheSame_Test )
{
    // [Preparation]

    const TransformationMatrix3x3 TRANSFORMATION_MATRIX( Matrix3x3(SFloat::_0_5,        (float_z)0.8660254, SFloat::_0,
                                                                         (float_z)-0.8660254, SFloat::_0_5,       SFloat::_0,
                                                                         SFloat::_0,          SFloat::_0,         SFloat::_1) );
    float_z ORIGINAL_ROTATION;
    TRANSFORMATION_MATRIX.GetRotation(ORIGINAL_ROTATION);

    // [Execution]
    TransformationMatrix3x3 matrix = TRANSFORMATION_MATRIX.SwitchHandConvention();
    float_z fRotationUT;
    matrix.GetRotation(fRotationUT);

    // [Verification]
    BOOST_CHECK_EQUAL( fRotationUT, ORIGINAL_ROTATION );
}

// End - Test Suite: TransformationMatrix3x3
ZTEST_SUITE_END()
