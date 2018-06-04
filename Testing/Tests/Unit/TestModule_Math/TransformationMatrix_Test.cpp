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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/TransformationMatrix.h"
#include "TransformationMatrixWhiteBox.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/Quaternion.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZMath/SAngle.h"
#include "ZCommon/Exceptions/AssertException.h"
using namespace z::Internals;

using z::Test::TransformationMatrixWhiteBox;

typedef boost::mpl::list<Matrix4x3, Matrix4x4> TTemplateTypes;

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES && Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z SMALLER_TOLERANCE = 1e-5f;
#else
    const float_z SMALLER_TOLERANCE = SFloat::Epsilon;
#endif


ZTEST_SUITE_BEGIN( TransformationMatrix_TestSuite )

/// <summary>
/// Utility function: This function does nothing, it's intended to skip the filling of a fourth column.
/// </summary>
static void FillFourthColumnIfExists(Matrix4x3 &matrix, const float_z &_03, const float_z &_13, const float_z &_23, const float_z &_33)
{
}

/// <summary>
/// Utility function: This function fills the fourth column of a matrix with arbitrary values.
/// </summary>
static void FillFourthColumnIfExists(Matrix4x4 &matrix, const float_z &_03, const float_z &_13, const float_z &_23, const float_z &_33)
{
    matrix.ij[0][3] = _03;
    matrix.ij[1][3] = _13;
    matrix.ij[2][3] = _23;
    matrix.ij[3][3] = _33;
}

/// <summary>
/// Utility function: This function does nothing, it's intended to skip the ckecking of a fourth column.
/// </summary>
static void CheckFourthColumnIfExists(const Matrix4x3 &matrixA, const Matrix4x3 &matrixB)
{
}

/// <summary>
/// Utility function: Checks if the fourth column of 2 matrices is the same.
/// </summary>
static void CheckFourthColumnIfExists(const Matrix4x4 &matrixA, const Matrix4x4 &matrixB)
{
    BOOST_CHECK( SFloat::AreEqual( matrixA.ij[0][3], matrixB.ij[0][3] ));
    BOOST_CHECK( SFloat::AreEqual( matrixA.ij[1][3], matrixB.ij[1][3] ));
    BOOST_CHECK( SFloat::AreEqual( matrixA.ij[2][3], matrixB.ij[2][3] ));
    BOOST_CHECK( SFloat::AreEqual( matrixA.ij[3][3], matrixB.ij[3][3] ));
}

/// <summary>
/// Checks if copy constructor copies every matrix element properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_EveryMatrixElementCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SFloat::_5;
    EXPECTED_VALUE.ij[1][1] = SFloat::_6;
    EXPECTED_VALUE.ij[1][2] = SFloat::_7;
    EXPECTED_VALUE.ij[2][0] = SFloat::_9;
    EXPECTED_VALUE.ij[2][1] = SFloat::_10;
    EXPECTED_VALUE.ij[2][2] = (float_z)11.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)13.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)14.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)15.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)23.0);

    const TransformationMatrix<T> MATRIX_TO_COPY(EXPECTED_VALUE);

    // [Execution]
    TransformationMatrix<T> matrixUT = MATRIX_TO_COPY;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_EveryElementCopiedToCorrespondingElement_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SFloat::_5;
    EXPECTED_VALUE.ij[1][1] = SFloat::_6;
    EXPECTED_VALUE.ij[1][2] = SFloat::_7;
    EXPECTED_VALUE.ij[2][0] = SFloat::_9;
    EXPECTED_VALUE.ij[2][1] = SFloat::_10;
    EXPECTED_VALUE.ij[2][2] = (float_z)11.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)13.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)14.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)15.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)23.0);

    // [Execution]
    TransformationMatrix<T> matrixUT(EXPECTED_VALUE);

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
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

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
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

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ResultIsDifferentDependingOnQuaternionNormalization_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    TransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_FollowsLeftHandedRules_Test, TTemplateTypes )
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
    const TransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, Quaternion(ROTATION_ANGLE, SFloat::_0, SFloat::_0), SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, Quaternion(SFloat::_0, ROTATION_ANGLE, SFloat::_0), SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, Quaternion(SFloat::_0, SFloat::_0, ROTATION_ANGLE), SCALE);

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
ZTEST_CASE_TEMPLATE ( Constructor4_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
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

    const TransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<T> ROTATION_MATRIX(Vector3::GetNullVector(), ROTATION, Vector3::GetVectorOfOnes());
    const TransformationMatrix<T> SCALE_MATRIX(Vector3::GetNullVector(), Quaternion::GetIdentity(), SCALE);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT = TransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_ResultIsDifferentDependingOnQuaternionNormalization_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION, NORMALIZED_QUATERNION, SCALE);
    TransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION, NOT_NORMALIZED_QUATERNION, SCALE);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_FollowsLeftHandedRules_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ROTATION_ANGLE = SAngle::_90;
    #else
        const float_z ROTATION_ANGLE = SAngle::_HalfPi;
    #endif

    const Vector4 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // Note: Quaternions are supposed to represent left-handed rotations
    const TransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, Quaternion(ROTATION_ANGLE, SFloat::_0, SFloat::_0), SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, Quaternion(SFloat::_0, ROTATION_ANGLE, SFloat::_0), SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, Quaternion(SFloat::_0, SFloat::_0, ROTATION_ANGLE), SCALE);

    const Vector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_X(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Y(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_1);
    const Vector4 EXPECTED_POSITION_AFTER_ROTATION_AROUND_Z(-SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1);

    const Vector4 POSITION_BEFORE_ROTATION_AROUND_X(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_1);
    const Vector4 POSITION_BEFORE_ROTATION_AROUND_Y(-SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector4 POSITION_BEFORE_ROTATION_AROUND_Z(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_1);

    // [Execution]
    Vector4 vPoint1UT = POSITION_BEFORE_ROTATION_AROUND_X.Transform(ROTATION_AROUND_X);
    Vector4 vPoint2UT = POSITION_BEFORE_ROTATION_AROUND_Y.Transform(ROTATION_AROUND_Y);
    Vector4 vPoint3UT = POSITION_BEFORE_ROTATION_AROUND_Z.Transform(ROTATION_AROUND_Z);

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
ZTEST_CASE_TEMPLATE ( Constructor5_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    // Reference values calculated using DirectX SDK:
    // D3DXMATRIX translation, rotation, scale, transformation;
    // D3DXMatrixTranslation(&translation, 1, 2, 3);
    // D3DXQUATERNION qRotation(4, 5, 6, 7);
    // D3DXMatrixRotationQuaternion(&rotation, &qRotation);
    // D3DXMatrixScaling(&scale, 8, 9, 10);
    // transformation = scale * rotation * translation;

    const Vector4 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    const TransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, Quaternion::GetIdentity(), Vector3::GetVectorOfOnes());
    const TransformationMatrix<T> ROTATION_MATRIX(Vector4::GetNullVector(), ROTATION, Vector3::GetVectorOfOnes());
    const TransformationMatrix<T> SCALE_MATRIX(Vector4::GetNullVector(), Quaternion::GetIdentity(), SCALE);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT = TransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the same result is obtained whether the translation vector's fourth component equals zero or one.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_FourthComponentOfTranslationVectorDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 TRANSLATION_W_ONE(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector4 TRANSLATION_W_ZERO(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Quaternion ROTATION(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7);
    const Vector3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    // [Execution]
    TransformationMatrix<T> matrixVectorWOneUT(TRANSLATION_W_ONE, ROTATION, SCALE);
    TransformationMatrix<T> matrixVectorWZeroUT(TRANSLATION_W_ZERO, ROTATION, SCALE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[0][0], matrixVectorWZeroUT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[0][1], matrixVectorWZeroUT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[0][2], matrixVectorWZeroUT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[1][0], matrixVectorWZeroUT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[1][1], matrixVectorWZeroUT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[1][2], matrixVectorWZeroUT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[2][0], matrixVectorWZeroUT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[2][1], matrixVectorWZeroUT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[2][2], matrixVectorWZeroUT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[3][0], matrixVectorWZeroUT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[3][1], matrixVectorWZeroUT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixVectorWOneUT.ij[3][2], matrixVectorWZeroUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixVectorWOneUT, matrixVectorWZeroUT);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
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

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
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

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                      ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                      SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_ResultIsDifferentDependingOnQuaternionNormalization_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixFromNormalizedQuaternionUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                              NORMALIZED_QUATERNION.x, NORMALIZED_QUATERNION.y, NORMALIZED_QUATERNION.z, NORMALIZED_QUATERNION.w,
                                                              SCALE.x, SCALE.y, SCALE.z);
    TransformationMatrix<T> matrixFromNotNormalizedQuaternionUT(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                                 NOT_NORMALIZED_QUATERNION.x, NOT_NORMALIZED_QUATERNION.y, NOT_NORMALIZED_QUATERNION.z, NOT_NORMALIZED_QUATERNION.w,
                                                                 SCALE.x, SCALE.y, SCALE.z);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor6_FollowsLeftHandedRules_Test, TTemplateTypes )
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
    const Quaternion ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION_QUATERNION_AROUND_Y(SFloat::_0, ROTATION_ANGLE, SFloat::_0);
    const Quaternion ROTATION_QUATERNION_AROUND_Z(SFloat::_0, SFloat::_0, ROTATION_ANGLE);

    const TransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_X.x, ROTATION_QUATERNION_AROUND_X.y, ROTATION_QUATERNION_AROUND_X.z, ROTATION_QUATERNION_AROUND_X.w,
                                                     SCALE.x, SCALE.y, SCALE.z);
    const TransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_Y.x, ROTATION_QUATERNION_AROUND_Y.y, ROTATION_QUATERNION_AROUND_Y.z, ROTATION_QUATERNION_AROUND_Y.w,
                                                     SCALE.x, SCALE.y, SCALE.z);
    const TransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                     ROTATION_QUATERNION_AROUND_Z.x, ROTATION_QUATERNION_AROUND_Z.y, ROTATION_QUATERNION_AROUND_Z.z, ROTATION_QUATERNION_AROUND_Z.w,
                                                     SCALE.x, SCALE.y, SCALE.z);

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
ZTEST_CASE_TEMPLATE ( Constructor6_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
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

    const Vector3 ZERO_VECTOR = Vector3::GetNullVector();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Vector3 VECTOR_OF_ONES = Vector3::GetVectorOfOnes();

    const TransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                      IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                                      VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    const TransformationMatrix<T> ROTATION_MATRIX(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                                                   ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                                   VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    const TransformationMatrix<T> SCALE_MATRIX(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                                                IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                                SCALE.x, SCALE.y, SCALE.z);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT = TransformationMatrix<T>(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                                 ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                                                                 SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize());
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]

    const T TRANSLATION = T::GetNullMatrix();
    const Matrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    const Matrix3x3 SCALE = Matrix3x3::GetNullMatrix();

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor7_FollowsLeftHandedRules_Test, TTemplateTypes )
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

    const TransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

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
ZTEST_CASE_TEMPLATE ( Constructor7_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    const T NEUTRAL_TRANSLATION = T::GetNullMatrix();
    const RotationMatrix3x3 NEUTRAL_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 NEUTRAL_SCALE = ScalingMatrix3x3::GetIdentity();

    const TransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    const TransformationMatrix<T> ROTATION_MATRIX(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    const TransformationMatrix<T> SCALE_MATRIX(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.ij[3][0];
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.ij[3][1];
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.ij[3][2];

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize());
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.ij[0][0];
    EXPECTED_VALUE.ij[1][1] = SCALE.ij[1][1];
    EXPECTED_VALUE.ij[2][2] = SCALE.ij[2][2];
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]

    const T TRANSLATION = T::GetNullMatrix();
    const Matrix3x3 ROTATION = Matrix3x3::GetNullMatrix();
    const Matrix3x3 SCALE = Matrix3x3::GetNullMatrix();

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor8_FollowsLeftHandedRules_Test, TTemplateTypes )
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

    const TransformationMatrix<T> ROTATION_AROUND_X(TRANSLATION, ROTATION_QUATERNION_AROUND_X, SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Y(TRANSLATION, ROTATION_QUATERNION_AROUND_Y, SCALE);
    const TransformationMatrix<T> ROTATION_AROUND_Z(TRANSLATION, ROTATION_QUATERNION_AROUND_Z, SCALE);

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
ZTEST_CASE_TEMPLATE ( Constructor8_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(Quaternion(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_7));
    const ScalingMatrix3x3 SCALE(SFloat::_8, SFloat::_9, SFloat::_10);

    const T NEUTRAL_TRANSLATION = T::GetNullMatrix();
    const RotationMatrix3x3 NEUTRAL_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 NEUTRAL_SCALE = ScalingMatrix3x3::GetIdentity();

    const TransformationMatrix<T> TRANSLATION_MATRIX(TRANSLATION, NEUTRAL_ROTATION, NEUTRAL_SCALE);
    const TransformationMatrix<T> ROTATION_MATRIX(NEUTRAL_TRANSLATION, ROTATION, NEUTRAL_SCALE);
    const TransformationMatrix<T> SCALE_MATRIX(NEUTRAL_TRANSLATION, NEUTRAL_ROTATION, SCALE);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT(TRANSLATION, ROTATION, SCALE);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE = T::GetIdentity();

	// [Execution]
    TransformationMatrix<T> matrixUT = TransformationMatrix<T>::GetIdentity();

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct1_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)126.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)132.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)138.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)306.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)321.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)336.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)486.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)510.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)534.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)692.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)726.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)760.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;
    FillFourthColumnIfExists(OPERAND2, (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)126.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)132.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)138.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)306.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)321.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)336.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)486.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)510.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)534.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)692.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)726.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)760.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfRightOperandDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_2;
    OPERANDA1.ij[0][2] = SFloat::_3;
    OPERANDA1.ij[1][0] = SFloat::_4;
    OPERANDA1.ij[1][1] = SFloat::_5;
    OPERANDA1.ij[1][2] = SFloat::_6;
    OPERANDA1.ij[2][0] = SFloat::_7;
    OPERANDA1.ij[2][1] = SFloat::_8;
    OPERANDA1.ij[2][2] = SFloat::_9;
    OPERANDA1.ij[3][0] = SFloat::_10;
    OPERANDA1.ij[3][1] = (float_z)11.0;
    OPERANDA1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDA1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERANDA2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TransformationMatrix<T> OPERANDB1 = OPERANDA1;

    TransformationMatrix<Matrix4x4> OPERANDB2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    // [Execution]
    TransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProduct2_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERAND2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                              (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                              (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                              (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct3_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SFloat::_4;
    EXPECTED_VALUE.ij[1][1] = SFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SFloat::_6;
    EXPECTED_VALUE.ij[2][0] = SFloat::_7;
    EXPECTED_VALUE.ij[2][1] = SFloat::_8;
    EXPECTED_VALUE.ij[2][2] = SFloat::_9;
    EXPECTED_VALUE.ij[3][0] = (float_z)36.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)38.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)40.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that only the fourth row of the translation matrix participates in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct3_OnlyTheFourthRowOfTranslationMatrixMatters_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_2;
    OPERANDA1.ij[0][2] = SFloat::_3;
    OPERANDA1.ij[1][0] = SFloat::_4;
    OPERANDA1.ij[1][1] = SFloat::_5;
    OPERANDA1.ij[1][2] = SFloat::_6;
    OPERANDA1.ij[2][0] = SFloat::_7;
    OPERANDA1.ij[2][1] = SFloat::_8;
    OPERANDA1.ij[2][2] = SFloat::_9;
    OPERANDA1.ij[3][0] = SFloat::_10;
    OPERANDA1.ij[3][1] = (float_z)11.0;
    OPERANDA1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDA1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x3> OPERANDA2 = TranslationMatrix<Matrix4x3>(Matrix4x3((float_z)17.0, (float_z)18.0, (float_z)19.0,
                                                                                         (float_z)20.0, (float_z)21.0, (float_z)22.0,
                                                                                         (float_z)23.0, (float_z)24.0, (float_z)25.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0));

    TransformationMatrix<T> OPERANDB1 = OPERANDA1;

    TranslationMatrix<Matrix4x3> OPERANDB2 = TranslationMatrix<Matrix4x3>(Matrix4x3((float_z)37.0, (float_z)38.0, (float_z)39.0,
                                                                                         (float_z)40.0, (float_z)41.0, (float_z)42.0,
                                                                                         (float_z)43.0, (float_z)44.0, (float_z)45.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0));

    // [Execution]
    TransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProduct3_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x4> OPERAND2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                        (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                        (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                        (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}


/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct4_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]

    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;
    FillFourthColumnIfExists(OPERAND2, (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_2;
    EXPECTED_VALUE.ij[0][2] = SFloat::_3;
    EXPECTED_VALUE.ij[1][0] = SFloat::_4;
    EXPECTED_VALUE.ij[1][1] = SFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SFloat::_6;
    EXPECTED_VALUE.ij[2][0] = SFloat::_7;
    EXPECTED_VALUE.ij[2][1] = SFloat::_8;
    EXPECTED_VALUE.ij[2][2] = SFloat::_9;
    EXPECTED_VALUE.ij[3][0] = (float_z)36.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)38.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)40.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that only the fourth row of the translation matrix participates in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct4_OnlyTheFourthRowOfTranslationMatrixMatters_Test, TTemplateTypes )
{
    // [Preparation]

    TransformationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_2;
    OPERANDA1.ij[0][2] = SFloat::_3;
    OPERANDA1.ij[1][0] = SFloat::_4;
    OPERANDA1.ij[1][1] = SFloat::_5;
    OPERANDA1.ij[1][2] = SFloat::_6;
    OPERANDA1.ij[2][0] = SFloat::_7;
    OPERANDA1.ij[2][1] = SFloat::_8;
    OPERANDA1.ij[2][2] = SFloat::_9;
    OPERANDA1.ij[3][0] = SFloat::_10;
    OPERANDA1.ij[3][1] = (float_z)11.0;
    OPERANDA1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDA1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x4> OPERANDA2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                         (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                         (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    TransformationMatrix<T> OPERANDB1;
    OPERANDB1.ij[0][0] = SFloat::_1;
    OPERANDB1.ij[0][1] = SFloat::_2;
    OPERANDB1.ij[0][2] = SFloat::_3;
    OPERANDB1.ij[1][0] = SFloat::_4;
    OPERANDB1.ij[1][1] = SFloat::_5;
    OPERANDB1.ij[1][2] = SFloat::_6;
    OPERANDB1.ij[2][0] = SFloat::_7;
    OPERANDB1.ij[2][1] = SFloat::_8;
    OPERANDB1.ij[2][2] = SFloat::_9;
    OPERANDB1.ij[3][0] = SFloat::_10;
    OPERANDB1.ij[3][1] = (float_z)11.0;
    OPERANDB1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDB1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x4> OPERANDB2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)37.0, (float_z)38.0, (float_z)39.0, (float_z)49.0,
                                                                                         (float_z)40.0, (float_z)41.0, (float_z)42.0, (float_z)50.0,
                                                                                         (float_z)43.0, (float_z)44.0, (float_z)45.0, (float_z)51.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)52.0));

    // [Execution]
    TransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProduct4_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TranslationMatrix<Matrix4x4> OPERAND2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                        (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                        (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                        (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct5_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]

    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    RotationMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)126.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)132.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)138.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)306.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)321.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)336.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)486.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)510.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)534.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)666.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)699.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)732.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProduct5_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    RotationMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct6_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    ScalingMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)17.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)42.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)75.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)68.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)105.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)150.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)119.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)168.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)225.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)170.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)231.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)300.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProduct6_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    ScalingMatrix3x3 OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that only the diagonal of the scaling matrix participates in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct6_OnlyTheDiagonalOfScalingMatrixMatters_Test, TTemplateTypes )
{
    // [Preparation]

    TransformationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_2;
    OPERANDA1.ij[0][2] = SFloat::_3;
    OPERANDA1.ij[1][0] = SFloat::_4;
    OPERANDA1.ij[1][1] = SFloat::_5;
    OPERANDA1.ij[1][2] = SFloat::_6;
    OPERANDA1.ij[2][0] = SFloat::_7;
    OPERANDA1.ij[2][1] = SFloat::_8;
    OPERANDA1.ij[2][2] = SFloat::_9;
    OPERANDA1.ij[3][0] = SFloat::_10;
    OPERANDA1.ij[3][1] = (float_z)11.0;
    OPERANDA1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDA1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    ScalingMatrix3x3 OPERANDA2;
    OPERANDA2.ij[0][0] = (float_z)17.0;
    OPERANDA2.ij[0][1] = (float_z)18.0;
    OPERANDA2.ij[0][2] = (float_z)19.0;
    OPERANDA2.ij[1][0] = (float_z)20.0;
    OPERANDA2.ij[1][1] = (float_z)21.0;
    OPERANDA2.ij[1][2] = (float_z)22.0;
    OPERANDA2.ij[2][0] = (float_z)23.0;
    OPERANDA2.ij[2][1] = (float_z)24.0;
    OPERANDA2.ij[2][2] = (float_z)25.0;

    TransformationMatrix<T> OPERANDB1 = OPERANDA1;

    ScalingMatrix3x3 OPERANDB2;
    OPERANDB2.ij[0][0] = (float_z)17.0;
    OPERANDB2.ij[0][1] = (float_z)26.0;
    OPERANDB2.ij[0][2] = (float_z)27.0;
    OPERANDB2.ij[1][0] = (float_z)28.0;
    OPERANDB2.ij[1][1] = (float_z)21.0;
    OPERANDB2.ij[1][2] = (float_z)29.0;
    OPERANDB2.ij[2][0] = (float_z)30.0;
    OPERANDB2.ij[2][1] = (float_z)31.0;
    OPERANDB2.ij[2][2] = (float_z)25.0;

    // [Execution]
    TransformationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)126.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)132.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)138.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)306.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)321.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)336.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)486.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)510.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)534.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)692.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)726.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)760.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a transformation matrix can be multiplied by itself (same object instance).
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_CanBeMultipliedByItself_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x3> OPERAND;
    OPERAND.ij[0][0] = SFloat::_1;
    OPERAND.ij[0][1] = SFloat::_2;
    OPERAND.ij[0][2] = SFloat::_3;
    OPERAND.ij[1][0] = SFloat::_4;
    OPERAND.ij[1][1] = SFloat::_5;
    OPERAND.ij[1][2] = SFloat::_6;
    OPERAND.ij[2][0] = SFloat::_7;
    OPERAND.ij[2][1] = SFloat::_8;
    OPERAND.ij[2][2] = SFloat::_9;
    OPERAND.ij[3][0] = SFloat::_10;
    OPERAND.ij[3][1] = (float_z)11.0;
    OPERAND.ij[3][2] = (float_z)12.0;

    TransformationMatrix<Matrix4x3> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)30.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)36.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)42.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)66.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)81.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)96.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)102.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)126.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)150.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)148.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)182.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)216.0;

    // [Execution]
    TransformationMatrix<Matrix4x3> matrixUT = OPERAND;
    matrixUT *= matrixUT;

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
/// Checks that two common matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation2_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = (float_z)17.0;
    OPERAND2.ij[0][1] = (float_z)18.0;
    OPERAND2.ij[0][2] = (float_z)19.0;
    OPERAND2.ij[1][0] = (float_z)20.0;
    OPERAND2.ij[1][1] = (float_z)21.0;
    OPERAND2.ij[1][2] = (float_z)22.0;
    OPERAND2.ij[2][0] = (float_z)23.0;
    OPERAND2.ij[2][1] = (float_z)24.0;
    OPERAND2.ij[2][2] = (float_z)25.0;
    OPERAND2.ij[3][0] = (float_z)26.0;
    OPERAND2.ij[3][1] = (float_z)27.0;
    OPERAND2.ij[3][2] = (float_z)28.0;
    FillFourthColumnIfExists(OPERAND2, (float_z)29.0, (float_z)30.0, (float_z)31.0, (float_z)32.0);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)126.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)132.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)138.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)306.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)321.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)336.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)486.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)510.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)534.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)692.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)726.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)760.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation2_FourthColumnOfRightOperandDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_2;
    OPERANDA1.ij[0][2] = SFloat::_3;
    OPERANDA1.ij[1][0] = SFloat::_4;
    OPERANDA1.ij[1][1] = SFloat::_5;
    OPERANDA1.ij[1][2] = SFloat::_6;
    OPERANDA1.ij[2][0] = SFloat::_7;
    OPERANDA1.ij[2][1] = SFloat::_8;
    OPERANDA1.ij[2][2] = SFloat::_9;
    OPERANDA1.ij[3][0] = SFloat::_10;
    OPERANDA1.ij[3][1] = (float_z)11.0;
    OPERANDA1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERANDA1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERANDA2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TransformationMatrix<T> OPERANDB1 = OPERANDA1;

    TransformationMatrix<Matrix4x4> OPERANDB2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    // [Execution]
    TransformationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    TransformationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) is just copied to the result.
/// </summary>
ZTEST_CASE( OperatorProductAssignation2_FourthColumnOfLeftOperandIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_2;
    OPERAND1.ij[0][2] = SFloat::_3;
    OPERAND1.ij[1][0] = SFloat::_4;
    OPERAND1.ij[1][1] = SFloat::_5;
    OPERAND1.ij[1][2] = SFloat::_6;
    OPERAND1.ij[2][0] = SFloat::_7;
    OPERAND1.ij[2][1] = SFloat::_8;
    OPERAND1.ij[2][2] = SFloat::_9;
    OPERAND1.ij[3][0] = SFloat::_10;
    OPERAND1.ij[3][1] = (float_z)11.0;
    OPERAND1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(OPERAND1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<Matrix4x4> OPERAND2 = TransformationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                              (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                              (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                              (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND1;
    matrixUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK_EQUAL( matrixUT.ij[0][3], OPERAND1.ij[0][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[1][3], OPERAND1.ij[1][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[2][3], OPERAND1.ij[2][3] );
    BOOST_CHECK_EQUAL( matrixUT.ij[3][3], OPERAND1.ij[3][3] );
}

/// <summary>
/// Checks that a transformation matrix can be multiplied by itself (same object instance).
/// </summary>
ZTEST_CASE( OperatorProductAssignation2_CanBeMultipliedByItself_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> OPERAND;
    OPERAND.ij[0][0] = SFloat::_1;
    OPERAND.ij[0][1] = SFloat::_2;
    OPERAND.ij[0][2] = SFloat::_3;
    OPERAND.ij[1][0] = SFloat::_4;
    OPERAND.ij[1][1] = SFloat::_5;
    OPERAND.ij[1][2] = SFloat::_6;
    OPERAND.ij[2][0] = SFloat::_7;
    OPERAND.ij[2][1] = SFloat::_8;
    OPERAND.ij[2][2] = SFloat::_9;
    OPERAND.ij[3][0] = SFloat::_10;
    OPERAND.ij[3][1] = (float_z)11.0;
    OPERAND.ij[3][2] = (float_z)12.0;
    OPERAND.ij[0][3] = (float_z)13.0;
    OPERAND.ij[1][3] = (float_z)14.0;
    OPERAND.ij[2][3] = (float_z)15.0;
    OPERAND.ij[3][3] = (float_z)16.0;

    TransformationMatrix<Matrix4x4> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)30.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)36.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)42.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)66.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)81.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)96.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)102.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)126.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)150.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)148.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)182.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)216.0;
    EXPECTED_VALUE.ij[0][3] = (float_z)13.0;
    EXPECTED_VALUE.ij[1][3] = (float_z)14.0;
    EXPECTED_VALUE.ij[2][3] = (float_z)15.0;
    EXPECTED_VALUE.ij[3][3] = (float_z)16.0;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixUT = OPERAND;
    matrixUT *= matrixUT;

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
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_9;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const TransformationMatrix<T> EXPECTED_VALUE = MATRIX;

    // [Execution]
    TransformationMatrix<T> matrixUT;
    matrixUT = MATRIX;

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of a common matrix is correctly obtained.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetDeterminant_ItsCorrectlyCalculatedForCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_0;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const float_z EXPECTED_VALUE = (float_z)27.0;

    // [Execution]
    float_z fResultUT = MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the determinant of the identity equals one.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetDeterminant_DeterminantOfIdentityEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<T> IDENTITY = TransformationMatrix<T>::GetIdentity();
    const float_z EXPECTED_VALUE = SFloat::_1;

    // [Execution]
    float_z fResultUT = IDENTITY.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that only the inner 3x3 matrix participates in the determinant calculus.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetDeterminant_OnlyInner3x3MatrixMatters_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX1;
    MATRIX1.ij[0][0] = SFloat::_1;
    MATRIX1.ij[0][1] = SFloat::_2;
    MATRIX1.ij[0][2] = SFloat::_3;
    MATRIX1.ij[1][0] = SFloat::_4;
    MATRIX1.ij[1][1] = SFloat::_5;
    MATRIX1.ij[1][2] = SFloat::_6;
    MATRIX1.ij[2][0] = SFloat::_7;
    MATRIX1.ij[2][1] = SFloat::_8;
    MATRIX1.ij[2][2] = SFloat::_0;
    MATRIX1.ij[3][0] = SFloat::_10;
    MATRIX1.ij[3][1] = (float_z)11.0;
    MATRIX1.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX1, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<T> MATRIX2;
    MATRIX2.ij[0][0] = SFloat::_1;
    MATRIX2.ij[0][1] = SFloat::_2;
    MATRIX2.ij[0][2] = SFloat::_3;
    MATRIX2.ij[1][0] = SFloat::_4;
    MATRIX2.ij[1][1] = SFloat::_5;
    MATRIX2.ij[1][2] = SFloat::_6;
    MATRIX2.ij[2][0] = SFloat::_7;
    MATRIX2.ij[2][1] = SFloat::_8;
    MATRIX2.ij[2][2] = SFloat::_0;
    MATRIX2.ij[3][0] = (float_z)17.0;
    MATRIX2.ij[3][1] = (float_z)18.0;
    MATRIX2.ij[3][2] = (float_z)19.0;
    FillFourthColumnIfExists(MATRIX2, (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)23.0);

    // [Execution]
    float_z fResult1UT = MATRIX1.GetDeterminant();
    float_z fResult2UT = MATRIX2.GetDeterminant();

    // [Verification]
    BOOST_CHECK_EQUAL(fResult1UT, fResult2UT);
}

/// <summary>
/// Checks that it returns True when the determinant of the matrix doesn't equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( HasInverse_ReturnsTrueWhenDeterminantIsNotZero_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<T> MATRIX = TransformationMatrix<T>::GetIdentity();
    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns False when the determinant of the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( HasInverse_ReturnsFalseWhenDeterminantIsZero_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<T> MATRIX(T::GetNullMatrix());
    const bool EXPECTED_VALUE = false;

    // [Execution]
    bool bResultUT = MATRIX.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a common matrix is correctly inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( Invert_CommonMatrixIsCorrectlyInverted_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_0;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-1.7777777777777777;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.88888888888888884;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.1111111111111111;
    EXPECTED_VALUE.ij[1][0] = (float_z)1.5555555555555554;
    EXPECTED_VALUE.ij[1][1] = (float_z)-0.77777777777777768;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.22222222222222221;
    EXPECTED_VALUE.ij[2][0] = (float_z)-0.1111111111111111;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.22222222222222221;
    EXPECTED_VALUE.ij[2][2] = (float_z)-0.1111111111111111;
    EXPECTED_VALUE.ij[3][0] = SFloat::_2;
    EXPECTED_VALUE.ij[3][1] = -SFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    TransformationMatrix<T> matrixUT = MATRIX.Invert();

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
    BOOST_CHECK_EQUAL(matrixUT.ij[3][0], EXPECTED_VALUE.ij[3][0]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][1], EXPECTED_VALUE.ij[3][1]);
    BOOST_CHECK_EQUAL(matrixUT.ij[3][2], EXPECTED_VALUE.ij[3][2]);
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the fourth column is just copied to the resultant matrix and doesn't participate in the operation.
/// </summary>
ZTEST_CASE ( Invert_FourthColumnIsJustCopied_Test )
{
    // [Preparation]
    TransformationMatrix<Matrix4x4> MATRIX1;
    MATRIX1.ij[0][0] = SFloat::_1;
    MATRIX1.ij[0][1] = SFloat::_2;
    MATRIX1.ij[0][2] = SFloat::_3;
    MATRIX1.ij[1][0] = SFloat::_4;
    MATRIX1.ij[1][1] = SFloat::_5;
    MATRIX1.ij[1][2] = SFloat::_6;
    MATRIX1.ij[2][0] = SFloat::_7;
    MATRIX1.ij[2][1] = SFloat::_8;
    MATRIX1.ij[2][2] = SFloat::_0;
    MATRIX1.ij[3][0] = SFloat::_10;
    MATRIX1.ij[3][1] = (float_z)11.0;
    MATRIX1.ij[3][2] = (float_z)12.0;
    MATRIX1.ij[0][3] = (float_z)13.0;
    MATRIX1.ij[1][3] = (float_z)14.0;
    MATRIX1.ij[2][3] = (float_z)15.0;
    MATRIX1.ij[3][3] = (float_z)16.0;

    TransformationMatrix<Matrix4x4> MATRIX2;
    MATRIX2.ij[0][0] = SFloat::_1;
    MATRIX2.ij[0][1] = SFloat::_2;
    MATRIX2.ij[0][2] = SFloat::_3;
    MATRIX2.ij[1][0] = SFloat::_4;
    MATRIX2.ij[1][1] = SFloat::_5;
    MATRIX2.ij[1][2] = SFloat::_6;
    MATRIX2.ij[2][0] = SFloat::_7;
    MATRIX2.ij[2][1] = SFloat::_8;
    MATRIX2.ij[2][2] = SFloat::_0;
    MATRIX2.ij[3][0] = SFloat::_10;
    MATRIX2.ij[3][1] = (float_z)11.0;
    MATRIX2.ij[3][2] = (float_z)12.0;
    MATRIX2.ij[0][3] = (float_z)17.0;
    MATRIX2.ij[1][3] = (float_z)18.0;
    MATRIX2.ij[2][3] = (float_z)19.0;
    MATRIX2.ij[3][3] = (float_z)20.0;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrix1UT = MATRIX1.Invert();
    TransformationMatrix<Matrix4x4> matrix2UT = MATRIX2.Invert();

    // [Verification]
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][0], matrix2UT.ij[0][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][1], matrix2UT.ij[0][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][2], matrix2UT.ij[0][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][0], matrix2UT.ij[1][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][1], matrix2UT.ij[1][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][2], matrix2UT.ij[1][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][0], matrix2UT.ij[2][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][1], matrix2UT.ij[2][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][2], matrix2UT.ij[2][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][0], matrix2UT.ij[3][0]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][1], matrix2UT.ij[3][1]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][2], matrix2UT.ij[3][2]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[0][3], MATRIX1.ij[0][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[1][3], MATRIX1.ij[1][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[2][3], MATRIX1.ij[2][3]);
    BOOST_CHECK_EQUAL(matrix1UT.ij[3][3], MATRIX1.ij[3][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[0][3], MATRIX2.ij[0][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[1][3], MATRIX2.ij[1][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[2][3], MATRIX2.ij[2][3]);
    BOOST_CHECK_EQUAL(matrix2UT.ij[3][3], MATRIX2.ij[3][3]);

}

/// <summary>
/// Checks that 3 translation values are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_0;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const float_z EXPECTED_VALUE_X = MATRIX.ij[3][0];
    const float_z EXPECTED_VALUE_Y = MATRIX.ij[3][1];
    const float_z EXPECTED_VALUE_Z = MATRIX.ij[3][2];

    // [Execution]
    float_z fTranslationXUT = SFloat::_0;
    float_z fTranslationYUT = SFloat::_0;
    float_z fTranslationZUT = SFloat::_0;
    MATRIX.GetTranslation(fTranslationXUT, fTranslationYUT, fTranslationZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTranslationXUT, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(fTranslationYUT, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(fTranslationZUT, EXPECTED_VALUE_Z);
}

/// <summary>
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX = T::GetIdentity();

    const float_z EXPECTED_VALUE_X = SFloat::_0;
    const float_z EXPECTED_VALUE_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_Z = SFloat::_0;

    // [Execution]
    float_z fTranslationXUT = SFloat::_1;
    float_z fTranslationYUT = SFloat::_1;
    float_z fTranslationZUT = SFloat::_1;
    MATRIX.GetTranslation(fTranslationXUT, fTranslationYUT, fTranslationZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTranslationXUT, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(fTranslationYUT, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(fTranslationZUT, EXPECTED_VALUE_Z);
}

/// <summary>
/// Checks that translation vector is correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_0;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const Vector3 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2]);

    // [Execution]
    Vector3 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX = T::GetIdentity();

    const Vector3 EXPECTED_VALUE(SFloat::_0, SFloat::_0, SFloat::_0);

    // [Execution]
    Vector3 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that translation vector is correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_0;
    MATRIX.ij[3][0] = SFloat::_10;
    MATRIX.ij[3][1] = (float_z)11.0;
    MATRIX.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const Vector4 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2], SFloat::_0);

    // [Execution]
    Vector4 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that 3 translation values equal zero when transformation matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> MATRIX = T::GetIdentity();

    const Vector4 EXPECTED_VALUE(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    // [Execution]
    Vector4 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix represents a rotation and a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale1_ValuesAreCorrectlyExtractedWhenMatrixContainsRotationAndScale_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;

    const RotationMatrix3x3 ROTATION(SFloat::_4, SFloat::_5, SFloat::_6);
    const ScalingMatrix3x3 SCALE(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    float_z fScaleXUT = SFloat::_0;
    float_z fScaleYUT = SFloat::_0;
    float_z fScaleZUT = SFloat::_0;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fScaleXUT, EXPECTED_VALUE_FOR_X) );
    BOOST_CHECK( SFloat::AreEqual(fScaleYUT, EXPECTED_VALUE_FOR_Y) );
    BOOST_CHECK( SFloat::AreEqual(fScaleZUT, EXPECTED_VALUE_FOR_Z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale1_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;

    const ScalingMatrix3x3 SCALE(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * RotationMatrix3x3::GetIdentity();
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    float_z fScaleXUT = SFloat::_0;
    float_z fScaleYUT = SFloat::_0;
    float_z fScaleZUT = SFloat::_0;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained values equal 1 when matrix is identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale1_ValuesEqualOneWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_1;

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    float_z fScaleXUT = SFloat::_0;
    float_z fScaleYUT = SFloat::_0;
    float_z fScaleZUT = SFloat::_0;

    TransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale1_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;

    const RotationMatrix3x3 ROTATION(SFloat::_4, SFloat::_5, SFloat::_6);
    const ScalingMatrix3x3 SCALE(-EXPECTED_VALUE_FOR_X, -EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * RotationMatrix3x3::GetIdentity();
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    float_z fScaleXUT = SFloat::_0;
    float_z fScaleYUT = SFloat::_0;
    float_z fScaleZUT = SFloat::_0;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(fScaleXUT, fScaleYUT, fScaleZUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fScaleXUT, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(fScaleYUT, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(fScaleZUT, EXPECTED_VALUE_FOR_Z);
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix represents a rotation and a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale2_ValuesAreCorrectlyExtractedWhenMatrixContainsRotationAndScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3);

    const RotationMatrix3x3 ROTATION(SFloat::_4, SFloat::_5, SFloat::_6);
    const ScalingMatrix3x3 SCALE(EXPECTED_VALUE.x, EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vScale;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScale.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScale.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScale.z, EXPECTED_VALUE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale2_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3);

    const RotationMatrix3x3 ROTATION(SFloat::_4, SFloat::_5, SFloat::_6);
    const ScalingMatrix3x3 SCALE(EXPECTED_VALUE.x, EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * RotationMatrix3x3::GetIdentity();
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vScale;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // [Verification]
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained values equal 1 when matrix is identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale2_ValuesEqualOneWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_VALUE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector3 vScale;

    TransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetScale(vScale);

    // [Verification]
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetScale2_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_VALUE(SFloat::_1, SFloat::_2, SFloat::_3);

    const RotationMatrix3x3 ROTATION(SFloat::_4, SFloat::_5, SFloat::_6);
    const ScalingMatrix3x3 SCALE(-EXPECTED_VALUE.x, -EXPECTED_VALUE.y, EXPECTED_VALUE.z);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * RotationMatrix3x3::GetIdentity();
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vScale;

    TransformationMatrix<T> matrix = ADAPTED_TRANSFORMATION;
    matrix.GetScale(vScale);

    // [Verification]
    BOOST_CHECK_EQUAL(vScale.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vScale.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vScale.z, EXPECTED_VALUE.z);
}

/// <summary>
/// Checks that obtained angles equal expected values when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_45;
        const float_z EXPECTED_ROTATION_Y = SAngle::_60;
        const float_z EXPECTED_ROTATION_Z = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION_X = SAngle::_QuarterPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_ThirdPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_HalfPi;
    #endif

    TransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_z)0.61237243569579447;
    ROTATION.ij[0][1] = (float_z)0.70710678118654757;
    ROTATION.ij[0][2] = (float_z)0.35355339059327373;
    ROTATION.ij[1][0] = (float_z)-0.5;
    ROTATION.ij[1][1] = (float_z)4.3297802811774670e-017;
    ROTATION.ij[1][2] = (float_z)0.86602540378443860;
    ROTATION.ij[2][0] = (float_z)0.61237243569579458;
    ROTATION.ij[2][1] = (float_z)-0.70710678118654746;
    ROTATION.ij[2][2] = (float_z)0.35355339059327384;
    ROTATION.ij[3][0] = SFloat::_0;
    ROTATION.ij[3][1] = SFloat::_0;
    ROTATION.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(ROTATION, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationXUT, EXPECTED_ROTATION_X, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SFloat::AreEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained angles don't equal expected values due to gimbal lock limitation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreNotWhatExpectedWhenGimbalLockOccurs_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_90;
        const float_z EXPECTED_ROTATION_Y = SAngle::_90;
        const float_z EXPECTED_ROTATION_Z = SAngle::_60;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION_X = SAngle::_HalfPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_HalfPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_ThirdPi;
    #endif

    // By rotating 90º (or PI/2) two gimbals, they become alligned so rotating any of them results in the same transformation
    TransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_z)0.86602545;
    ROTATION.ij[0][1] = (float_z)-3.7855173e-008;
    ROTATION.ij[0][2] = (float_z)-0.5;
    ROTATION.ij[1][0] = (float_z)0.5;
    ROTATION.ij[1][1] = (float_z)-2.1855692e-008;
    ROTATION.ij[1][2] = (float_z)0.86602545;
    ROTATION.ij[2][0] = (float_z)-4.3711388e-008;
    ROTATION.ij[2][1] = (float_z)-1.0;
    ROTATION.ij[2][2] = (float_z)1.9106855e-015;
    ROTATION.ij[3][0] = SFloat::_10;
    ROTATION.ij[3][1] = (float_z)11.0;
    ROTATION.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(ROTATION, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    ROTATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fRotationXUT, EXPECTED_ROTATION_X) ||
                 SFloat::AreNotEqual(fRotationYUT, EXPECTED_ROTATION_Y) ||
                 SFloat::AreNotEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained angles equal expected values when transformation matrix represents a rotation and a positive scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation1_AnglesAreCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_45;
        const float_z EXPECTED_ROTATION_Y = SAngle::_60;
        const float_z EXPECTED_ROTATION_Z = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION_X = SAngle::_QuarterPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_ThirdPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_HalfPi;
    #endif

    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION_X, EXPECTED_ROTATION_Y, EXPECTED_ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    ADAPTED_TRANSFORMATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fRotationXUT, EXPECTED_ROTATION_X, SMALLER_TOLERANCE) );
    BOOST_CHECK( SFloat::AreEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SFloat::AreEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ROTATION_X = SAngle::_45;
        const float_z EXPECTED_ROTATION_Y = SAngle::_60;
        const float_z EXPECTED_ROTATION_Z = SAngle::_90;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z EXPECTED_ROTATION_X = SAngle::_QuarterPi;
        const float_z EXPECTED_ROTATION_Y = SAngle::_ThirdPi;
        const float_z EXPECTED_ROTATION_Z = SAngle::_HalfPi;
    #endif

    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION_X, EXPECTED_ROTATION_Y, EXPECTED_ROTATION_Z);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    ADAPTED_TRANSFORMATION.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fRotationXUT, EXPECTED_ROTATION_X) );
    BOOST_CHECK( SFloat::AreNotEqual(fRotationYUT, EXPECTED_ROTATION_Y) );
    BOOST_CHECK( SFloat::AreNotEqual(fRotationZUT, EXPECTED_ROTATION_Z) );
}

/// <summary>
/// Checks that obtained values equal 0 when matrix is identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation1_ValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

    // [Execution]
    float_z fRotationXUT = SFloat::_0;
    float_z fRotationYUT = SFloat::_0;
    float_z fRotationZUT = SFloat::_0;

    TransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetRotation(fRotationXUT, fRotationYUT, fRotationZUT);

    // [Verification]
    BOOST_CHECK_EQUAL( fRotationXUT, EXPECTED_VALUE_FOR_ALL );
    BOOST_CHECK_EQUAL( fRotationYUT, EXPECTED_VALUE_FOR_ALL );
    BOOST_CHECK_EQUAL( fRotationZUT, EXPECTED_VALUE_FOR_ALL );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const Quaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    TransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_z)0.61237243569579447;
    ROTATION.ij[0][1] = (float_z)0.70710678118654757;
    ROTATION.ij[0][2] = (float_z)0.35355339059327373;
    ROTATION.ij[1][0] = (float_z)-0.5;
    ROTATION.ij[1][1] = (float_z)4.3297802811774670e-017;
    ROTATION.ij[1][2] = (float_z)0.86602540378443860;
    ROTATION.ij[2][0] = (float_z)0.61237243569579458;
    ROTATION.ij[2][1] = (float_z)-0.70710678118654746;
    ROTATION.ij[2][2] = (float_z)0.35355339059327384;
    ROTATION.ij[3][0] = SFloat::_10;
    ROTATION.ij[3][1] = (float_z)11.0;
    ROTATION.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(ROTATION, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    Quaternion qRotationUT;
    ROTATION.GetRotation(qRotationUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix represents a rotation and a positive scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation2_RotationIsCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TTemplateTypes )
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

    const Quaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Quaternion qRotationUT;
    ADAPTED_TRANSFORMATION.GetRotation(qRotationUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const Quaternion EXPECTED_VALUE(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Quaternion qRotationUT;
    ADAPTED_TRANSFORMATION.GetRotation(qRotationUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.x, EXPECTED_VALUE.x) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.y, EXPECTED_VALUE.y) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.z, EXPECTED_VALUE.z) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.w, EXPECTED_VALUE.w) );
}

/// <summary>
/// Checks that obtained value is an identity quaternion when matrix is identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation2_ValueEqualsIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();
    const Quaternion IDENTITY = Quaternion::GetIdentity();

    // [Execution]
    Quaternion qRotationUT;

    TransformationMatrix<T> matrix = TRANSFORMATION;
    matrix.GetRotation(qRotationUT);

    // [Verification]
    BOOST_CHECK_EQUAL( qRotationUT.x, IDENTITY.x );
    BOOST_CHECK_EQUAL( qRotationUT.y, IDENTITY.y );
    BOOST_CHECK_EQUAL( qRotationUT.z, IDENTITY.z );
    BOOST_CHECK_EQUAL( qRotationUT.w, IDENTITY.w );
}

/// <summary>
/// Checks that obtained angle and rotation axis equal expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_RotationAngleAndAxisAreCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    TransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_z)0.53571428571428581;
    ROTATION.ij[0][1] = (float_z)0.76579364625798496;
    ROTATION.ij[0][2] = (float_z)-0.35576719274341861;
    ROTATION.ij[1][0] = (float_z)-0.62293650340084217;
    ROTATION.ij[1][1] = (float_z)0.64285714285714302;
    ROTATION.ij[1][2] = (float_z)0.4457407392288521;
    ROTATION.ij[2][0] = (float_z)0.5700529070291328;
    ROTATION.ij[2][1] = (float_z)-0.017169310657423609;
    ROTATION.ij[2][2] = (float_z)0.8214285714285714;
    ROTATION.ij[3][0] = SFloat::_10;
    ROTATION.ij[3][1] = (float_z)11.0;
    ROTATION.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(ROTATION, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ROTATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE, SMALLER_TOLERANCE) );
}

/// <summary>
/// Checks that obtained angle and axis equal expected values when transformation matrix represents a rotation and a positive scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_RotationIsCorrectlyExtractedWhenMatrixContainsRotationAndPositiveScale_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.53571428571428581,  (float_z)0.76579364625798496,   (float_z)-0.35576719274341861,
                                                     (float_z)-0.62293650340084217, (float_z)0.64285714285714302,   (float_z)0.4457407392288521,
                                                     (float_z)0.5700529070291328,   (float_z)-0.017169310657423609, (float_z)0.8214285714285714));

    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SFloat::AreEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    const RotationMatrix3x3 ROTATION(Matrix3x3((float_z)0.53571427,  (float_z)0.76579368,   (float_z)-0.35576719,
                                                     (float_z)-0.62293649, (float_z)0.64285713,   (float_z)0.44574076,
                                                     (float_z)0.57005292,  (float_z)-0.017169312, (float_z)0.82142854));

    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained axis is a null vector and the obtained angle equals zero when the matrix contains scaling data and the original rotation was neutral.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_NullVectorAndZeroAngleAreObtainedWhenMatrixContainsPositiveScaleAndNeutralRotation_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();

    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    ADAPTED_TRANSFORMATION.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that obtained axis is a null vector and the obtained angle equals zero when the matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_NullVectorAndZeroAngleAreObtainedWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_ANGLE = SAngle::_60;
    #else
        const float_z EXPECTED_ANGLE = SAngle::_ThirdPi;
    #endif

    const Vector3 EXPECTED_AXIS = Vector3(SFloat::_1, SFloat::_2, SFloat::_3).Normalize();

    TransformationMatrix<T> IDENTITY = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector3 vAxisUT;
    float_z fAngleUT = SFloat::_0;
    IDENTITY.GetRotation(fAngleUT, vAxisUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.x, EXPECTED_AXIS.x) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.y, EXPECTED_AXIS.y) );
    BOOST_CHECK( SFloat::AreNotEqual(vAxisUT.z, EXPECTED_AXIS.z) );
    BOOST_CHECK( SFloat::AreNotEqual(fAngleUT, EXPECTED_ANGLE) );
}

/// <summary>
/// Checks that the obtained axis is normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetRotation3_ResultantAxisIsNormalized_Test, TTemplateTypes )
{
    // [Preparation]
    TransformationMatrix<T> ROTATION;
    ROTATION.ij[0][0] = (float_z)0.53571428571428581;
    ROTATION.ij[0][1] = (float_z)0.76579364625798496;
    ROTATION.ij[0][2] = (float_z)-0.35576719274341861;
    ROTATION.ij[1][0] = (float_z)-0.62293650340084217;
    ROTATION.ij[1][1] = (float_z)0.64285714285714302;
    ROTATION.ij[1][2] = (float_z)0.4457407392288521;
    ROTATION.ij[2][0] = (float_z)0.5700529070291328;
    ROTATION.ij[2][1] = (float_z)-0.017169310657423609;
    ROTATION.ij[2][2] = (float_z)0.8214285714285714;
    ROTATION.ij[3][0] = SFloat::_10;
    ROTATION.ij[3][1] = (float_z)11.0;
    ROTATION.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(ROTATION, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    // [Execution]
    Vector3 vAxisUT;
    Vector3 vNormalizedAxis;
    float_z fAngleAux = SFloat::_0;
    ROTATION.GetRotation(fAngleAux, vAxisUT);

    vNormalizedAxis = vAxisUT.Normalize();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.x, vNormalizedAxis.x) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.y, vNormalizedAxis.y) );
    BOOST_CHECK( SFloat::AreEqual(vAxisUT.z, vNormalizedAxis.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const Vector3 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationUT;
    Quaternion qRotationUT;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation vector is null when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_TranslationVectorIsNullWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector3 vTranslationUT;
    Quaternion qRotationAux;
    Vector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotation quaternion equals identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_RotationQuaternionEqualsIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion EXPECTED_ROTATION = Quaternion::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that scaling vector's components equal one when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_ScalingVectorComponentsEqualOneWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const Vector3 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const Vector3 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
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

    const Vector3 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6));

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose1_ValuesAreCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion EXPECTED_ROTATION = Quaternion::GetIdentity();
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const Vector4 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4));
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector4 vTranslationUT;
    Quaternion qRotationUT;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.w, EXPECTED_TRANSLATION.w) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation vector is null when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_TranslationVectorIsNullWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector4 vTranslationUT;
    Quaternion qRotationAux;
    Vector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotation quaternion equals identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_RotationQuaternionEqualsIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Quaternion EXPECTED_ROTATION = Quaternion::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that scaling vector's components equal one when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_ScalingVectorComponentsEqualOneWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const Vector4 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreNotEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that obtained quaternion equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const Vector4 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
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

    const Vector4 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(Vector3(-SFloat::_4, -SFloat::_5, -SFloat::_6));

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose2_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 EXPECTED_TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion EXPECTED_ROTATION = Quaternion::GetIdentity();
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TranslationMatrix<Matrix4x4> TRANSLATION(EXPECTED_TRANSLATION);
    const RotationMatrix3x3 ROTATION(EXPECTED_ROTATION);
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector4 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x3> EXPECTED_TRANSLATION(TRANSLATION, RotationMatrix3x3::GetIdentity(), ScalingMatrix3x3::GetIdentity());
    const TransformationMatrix<Matrix4x3> EXPECTED_ROTATION(TranslationMatrix<Matrix4x3>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());
    const TransformationMatrix<Matrix4x3> EXPECTED_SCALE(TranslationMatrix<Matrix4x3>::GetIdentity(), RotationMatrix3x3::GetIdentity(), SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x3> translationUT;
    TransformationMatrix<Matrix4x3> rotationUT;
    TransformationMatrix<Matrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x3> EXPECTED_TRANSFORMATIONS_VALUE = TransformationMatrix<Matrix4x3>::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    TransformationMatrix<Matrix4x3> translationUT;
    TransformationMatrix<Matrix4x3> rotationUT;
    TransformationMatrix<Matrix4x3> scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( rotationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( scaleUT == EXPECTED_TRANSFORMATIONS_VALUE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x3> EXPECTED_ROTATION(TranslationMatrix<Matrix4x3>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x3> translationAux;
    TransformationMatrix<Matrix4x3> rotationUT;
    TransformationMatrix<Matrix4x3> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<Matrix4x3> EXPECTED_ROTATION(TranslationMatrix<Matrix4x3>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x3> translationAux;
    TransformationMatrix<Matrix4x3> rotationUT;
    TransformationMatrix<Matrix4x3> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x3> EXPECTED_SCALE(TRANSLATION, ROTATION, ScalingMatrix3x3(SFloat::_4, SFloat::_5, SFloat::_6));

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x3> translationAux;
    TransformationMatrix<Matrix4x3> rotationAux;
    TransformationMatrix<Matrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose3_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x3> EXPECTED_SCALE(TRANSLATION, ROTATION, SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x3> translationAux;
    TransformationMatrix<Matrix4x3> rotationAux;
    TransformationMatrix<Matrix4x3> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const TransformationMatrix<Matrix4x4> EXPECTED_TRANSLATION(TRANSLATION, RotationMatrix3x3::GetIdentity(), ScalingMatrix3x3::GetIdentity());
    const TransformationMatrix<Matrix4x4> EXPECTED_ROTATION(TranslationMatrix<Matrix4x4>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());
    const TransformationMatrix<Matrix4x4> EXPECTED_SCALE(TranslationMatrix<Matrix4x4>::GetIdentity(), RotationMatrix3x3::GetIdentity(), SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x4> translationUT;
    TransformationMatrix<Matrix4x4> rotationUT;
    TransformationMatrix<Matrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TransformationMatrix<Matrix4x4> EXPECTED_TRANSFORMATIONS_VALUE = TransformationMatrix<Matrix4x4>::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    TransformationMatrix<Matrix4x4> translationUT;
    TransformationMatrix<Matrix4x4> rotationUT;
    TransformationMatrix<Matrix4x4> scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( rotationUT == EXPECTED_TRANSFORMATIONS_VALUE );
    BOOST_CHECK( scaleUT == EXPECTED_TRANSFORMATIONS_VALUE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> EXPECTED_ROTATION(TranslationMatrix<Matrix4x4>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x4> translationAux;
    TransformationMatrix<Matrix4x4> rotationUT;
    TransformationMatrix<Matrix4x4> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<Matrix4x4> EXPECTED_ROTATION(TranslationMatrix<Matrix4x4>::GetIdentity(), ROTATION, ScalingMatrix3x3::GetIdentity());

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x4> translationAux;
    TransformationMatrix<Matrix4x4> rotationUT;
    TransformationMatrix<Matrix4x4> scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> EXPECTED_SCALE(TRANSLATION, ROTATION, ScalingMatrix3x3(SFloat::_4, SFloat::_5, SFloat::_6));

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x4> translationAux;
    TransformationMatrix<Matrix4x4> rotationAux;
    TransformationMatrix<Matrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose4_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> EXPECTED_SCALE(TRANSLATION, ROTATION, SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TransformationMatrix<Matrix4x4> translationAux;
    TransformationMatrix<Matrix4x4> rotationAux;
    TransformationMatrix<Matrix4x4> scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = EXPECTED_SCALE * EXPECTED_ROTATION * EXPECTED_TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x3> translationUT;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> EXPECTED_TRANSLATION = TranslationMatrix<Matrix4x3>::GetIdentity();
    const RotationMatrix3x3 EXPECTED_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 EXPECTED_SCALE = ScalingMatrix3x3::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    TranslationMatrix<Matrix4x3> translationUT;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x3> translationAux;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleAux;
    TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x3> translationAux;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleAux;
    TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x3> translationAux;
    RotationMatrix3x3 rotationAux;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose5_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x3> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = EXPECTED_SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x3> translationAux;
    RotationMatrix3x3 rotationAux;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that translation, rotation and scale are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_TransformationsAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
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

    const TranslationMatrix<Matrix4x4> EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = EXPECTED_SCALE * EXPECTED_ROTATION * EXPECTED_TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x4> translationUT;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that all the transformations extracted equal identity when the transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_ExtractedTransformationsEqualIdentityWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> EXPECTED_TRANSLATION = TranslationMatrix<Matrix4x4>::GetIdentity();
    const RotationMatrix3x3 EXPECTED_ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 EXPECTED_SCALE = ScalingMatrix3x3::GetIdentity();

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    TranslationMatrix<Matrix4x4> translationUT;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleUT;
    TRANSFORMATION.Decompose(translationUT, rotationUT, scaleUT);

    // [Verification]
    BOOST_CHECK( translationUT == EXPECTED_TRANSLATION );
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x4> translationAux;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT != EXPECTED_ROTATION );
}

/// <summary>
/// Checks that obtained rotation equals expected value when transformation matrix only represents a rotation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_RotationIsCorrectlyExtractedWhenMatrixOnlyContainsRotation_Test, TTemplateTypes )
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
    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x4> translationAux;
    RotationMatrix3x3 rotationUT;
    ScalingMatrix3x3 scaleAux;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationUT, scaleAux);

    // [Verification]
    BOOST_CHECK( rotationUT == EXPECTED_ROTATION );
}

/// <summary>
/// Checks that the returned scale values are always positive, even when original scale was negative.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_ReturnedScaleIsAlwaysPositive_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x4> translationAux;
    RotationMatrix3x3 rotationAux;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that obtained values are correct when the transformation matrix only represents a scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( Decompose6_ValueIsCorrectlyExtractedWhenMatrixOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const RotationMatrix3x3 ROTATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const ScalingMatrix3x3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = EXPECTED_SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    TranslationMatrix<Matrix4x4> translationAux;
    RotationMatrix3x3 rotationAux;
    ScalingMatrix3x3 scaleUT;
    ADAPTED_TRANSFORMATION.Decompose(translationAux, rotationAux, scaleUT);

    // [Verification]
    BOOST_CHECK( scaleUT == EXPECTED_SCALE );
}

/// <summary>
/// Checks that the hand convention of the transformations represented by the matrix are correctly switched.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwitchHandConvention_MatrixHandConventionIsCorrectlySwitched_Test, TTemplateTypes )
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

    const Vector3 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, -SFloat::_3); // Z-axis is inverted
    const Quaternion EXPECTED_ROTATION = Quaternion(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert(); // Rotations are all inverted
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6); // Scale remains the same

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_1, SFloat::_2, SFloat::_3));
    const RotationMatrix3x3 ROTATION(Quaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationUT;
    Quaternion qRotationUT;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationUT, qRotationUT, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

/// <summary>
/// Checks that the translation over Z axis is inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwitchHandConvention_TranslationZComponentIsInverted_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_TRANSLATION(SFloat::_1, SFloat::_2, -SFloat::_3); // Z-axis is inverted

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_1, SFloat::_2, SFloat::_3));
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationUT;
    Quaternion qRotationAux;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationUT, qRotationAux, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.x, EXPECTED_TRANSLATION.x) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.y, EXPECTED_TRANSLATION.y) );
    BOOST_CHECK( SFloat::AreEqual(vTranslationUT.z, EXPECTED_TRANSLATION.z) );
}

/// <summary>
/// Checks that rotations are inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwitchHandConvention_RotationsAreInverted_Test, TTemplateTypes )
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

    const Quaternion EXPECTED_ROTATION = Quaternion(ROTATION_X, ROTATION_Y, ROTATION_Z).Invert(); // Rotations are all inverted

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_0, SFloat::_0, SFloat::_0));
    const RotationMatrix3x3 ROTATION(Quaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const ScalingMatrix3x3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationUT;
    Vector3 vScaleAux;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationUT, vScaleAux);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.x, EXPECTED_ROTATION.x) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.y, EXPECTED_ROTATION.y) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.z, EXPECTED_ROTATION.z) );
    BOOST_CHECK( SFloat::AreEqual(qRotationUT.w, EXPECTED_ROTATION.w) );
}

/// <summary>
/// Checks that the scale is not affected by the hand convention.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwitchHandConvention_ScaleDoesntChange_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 EXPECTED_SCALE(SFloat::_4, SFloat::_5, SFloat::_6); // Scale remains the same

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_0, SFloat::_0, SFloat::_0));
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3::GetIdentity();
    const ScalingMatrix3x3 SCALE(EXPECTED_SCALE);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleUT;
    ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationAux, vScaleUT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.x, EXPECTED_SCALE.x) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.y, EXPECTED_SCALE.y) );
    BOOST_CHECK( SFloat::AreEqual(vScaleUT.z, EXPECTED_SCALE.z) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the scale contained in the matrix equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwitchHandConvention_AssertionFailsWhenScaleEqualsZero_Test, TTemplateTypes )
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

    const bool EXPECTED_VALUE = true;

    const TranslationMatrix<Matrix4x4> TRANSLATION(Vector3(SFloat::_1, SFloat::_2, SFloat::_3));
    const RotationMatrix3x3 ROTATION(Quaternion(ROTATION_X, ROTATION_Y, ROTATION_Z));
    const ScalingMatrix3x3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * ROTATION * TRANSLATION;
    TransformationMatrix<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    Vector3 vTranslationAux;
    Quaternion qRotationAux;
    Vector3 vScaleAux;
    bool bAssertionFailed = false;

    try
    {
        ADAPTED_TRANSFORMATION.SwitchHandConvention().Decompose(vTranslationAux, qRotationAux, vScaleAux);
    }
    catch(const AssertException&) // TODO [avillalba]: A concrete exception should be used when it's implemented
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the correct rotation is obtained when using a common transformation matrix that contains positive scale.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_CorrectRotationIsObtainedWhenUsingCommonMatrixWithPositiveScale_Test, TTemplateTypes )
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

    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    RotationMatrix3x3 rotationUT = ADAPTED_TRANSFORMATION.ToRotationMatrix3x3();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][0], EXPECTED_ROTATION.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][1], EXPECTED_ROTATION.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][2], EXPECTED_ROTATION.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][0], EXPECTED_ROTATION.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][1], EXPECTED_ROTATION.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][2], EXPECTED_ROTATION.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][0], EXPECTED_ROTATION.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][1], EXPECTED_ROTATION.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][2], EXPECTED_ROTATION.ij[2][2]) );
}

/// <summary>
/// Checks that obtained rotation doesn't equal original value when negative scale was used to compound the transformation.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_RotationDoesntEqualOriginalValueWhenMatrixContainsNegativeScale_Test, TTemplateTypes )
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

    const RotationMatrix3x3 EXPECTED_ROTATION(ROTATION_X, ROTATION_Y, ROTATION_Z);

    const TranslationMatrix<Matrix4x4> TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const ScalingMatrix3x3 SCALE(-SFloat::_4, -SFloat::_5, -SFloat::_6);

    const TransformationMatrix<Matrix4x4> TRANSFORMATION = SCALE * EXPECTED_ROTATION * TRANSLATION;
    TransformationMatrixWhiteBox<T> ADAPTED_TRANSFORMATION; // Adaptation to matrix type
    ADAPTED_TRANSFORMATION.ij[0][0] = TRANSFORMATION.ij[0][0];
    ADAPTED_TRANSFORMATION.ij[0][1] = TRANSFORMATION.ij[0][1];
    ADAPTED_TRANSFORMATION.ij[0][2] = TRANSFORMATION.ij[0][2];
    ADAPTED_TRANSFORMATION.ij[1][0] = TRANSFORMATION.ij[1][0];
    ADAPTED_TRANSFORMATION.ij[1][1] = TRANSFORMATION.ij[1][1];
    ADAPTED_TRANSFORMATION.ij[1][2] = TRANSFORMATION.ij[1][2];
    ADAPTED_TRANSFORMATION.ij[2][0] = TRANSFORMATION.ij[2][0];
    ADAPTED_TRANSFORMATION.ij[2][1] = TRANSFORMATION.ij[2][1];
    ADAPTED_TRANSFORMATION.ij[2][2] = TRANSFORMATION.ij[2][2];
    ADAPTED_TRANSFORMATION.ij[3][0] = TRANSFORMATION.ij[3][0];
    ADAPTED_TRANSFORMATION.ij[3][1] = TRANSFORMATION.ij[3][1];
    ADAPTED_TRANSFORMATION.ij[3][2] = TRANSFORMATION.ij[3][2];
    FillFourthColumnIfExists(ADAPTED_TRANSFORMATION, TRANSFORMATION.ij[0][3], TRANSFORMATION.ij[1][3], TRANSFORMATION.ij[2][3], TRANSFORMATION.ij[3][3]);

    // [Execution]
    RotationMatrix3x3 rotationUT = ADAPTED_TRANSFORMATION.ToRotationMatrix3x3();

    // [Verification]
    BOOST_CHECK(rotationUT != EXPECTED_ROTATION);
}

/// <summary>
/// Checks that the obtained rotation matrix equals identity when transformation matrix equals identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToRotationMatrix3x3_ObtainedRotationEqualsIdentityWhenMatrixEqualsIdentity_Test, TTemplateTypes )
{
    // [Preparation]

    const RotationMatrix3x3 EXPECTED_ROTATION = RotationMatrix3x3::GetIdentity();

    TransformationMatrixWhiteBox<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();

    // [Execution]
    RotationMatrix3x3 rotationUT = TRANSFORMATION.ToRotationMatrix3x3();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][0], EXPECTED_ROTATION.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][1], EXPECTED_ROTATION.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[0][2], EXPECTED_ROTATION.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][0], EXPECTED_ROTATION.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][1], EXPECTED_ROTATION.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[1][2], EXPECTED_ROTATION.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][0], EXPECTED_ROTATION.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][1], EXPECTED_ROTATION.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(rotationUT.ij[2][2], EXPECTED_ROTATION.ij[2][2]) );
}

/// <summary>
/// Checks that a correct transformation matrix is obtained when using common transformations.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_TransformationIsCorrectlyBuiltFromCommonTransformations_Test, TTemplateTypes )
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

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)-968.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)992.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)-176.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)-396.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)-927.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)1044.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)1180.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)40.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)-810.0;
    EXPECTED_VALUE.ij[3][0] = SFloat::_1;
    EXPECTED_VALUE.ij[3][1] = SFloat::_2;
    EXPECTED_VALUE.ij[3][2] = SFloat::_3;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that an identity matrix is obtained when neutral transformations are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_IdentityIsObtainedWhenNeutralTransformationsAreUsed_Test, TTemplateTypes )
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

    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when rotation and scale are neutral but translation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsTranslation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_1, SFloat::_2, SFloat::_3);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[3][0] = TRANSLATION.x;
    EXPECTED_VALUE.ij[3][1] = TRANSLATION.y;
    EXPECTED_VALUE.ij[3][2] = TRANSLATION.z;

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and scale are neutral but rotation is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsRotation_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)0.13333333333333353;
    EXPECTED_VALUE.ij[0][1] = (float_z)0.93333333333333324;
    EXPECTED_VALUE.ij[0][2] = (float_z)-0.33333333333333326;
    EXPECTED_VALUE.ij[1][0] = (float_z)-0.66666666666666663;
    EXPECTED_VALUE.ij[1][1] = (float_z)0.33333333333333348;
    EXPECTED_VALUE.ij[1][2] = (float_z)0.66666666666666652;
    EXPECTED_VALUE.ij[2][0] = (float_z)0.73333333333333317;
    EXPECTED_VALUE.ij[2][1] = (float_z)0.13333333333333336;
    EXPECTED_VALUE.ij[2][2] = (float_z)0.66666666666666674;
    EXPECTED_VALUE.ij[3][0] = SFloat::_0;
    EXPECTED_VALUE.ij[3][1] = SFloat::_0;
    EXPECTED_VALUE.ij[3][2] = SFloat::_0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the resultant matrix is correct when translation and rotation are neutral but scale is not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_CorrectResultObtainedWhenOnlyContainsScale_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector3 SCALE(SFloat::_2, SFloat::_3, SFloat::_4);

    T EXPECTED_VALUE = T::GetIdentity();
    EXPECTED_VALUE.ij[0][0] = SCALE.x;
    EXPECTED_VALUE.ij[1][1] = SCALE.y;
    EXPECTED_VALUE.ij[2][2] = SCALE.z;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that zero matrix is obtained when all input objects' components equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_ZeroMatrixIsObtainedWhenInputsEqualZero_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 SCALE(SFloat::_0, SFloat::_0, SFloat::_0);

    T EXPECTED_VALUE = T::GetNullMatrix();
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1); // For 4x4 matrices, the (3,3) element equals 1

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the result is different when that input quaternion is normalized and when it's not.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_ResultIsDifferentDependingOnQuaternionNormalization_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 TRANSLATION(SFloat::_0, SFloat::_0, SFloat::_0);
    const Quaternion NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Quaternion NOT_NORMALIZED_QUATERNION = Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 SCALE(SFloat::_1, SFloat::_1, SFloat::_1);

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixFromNormalizedQuaternionUT;
    matrixFromNormalizedQuaternionUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                NORMALIZED_QUATERNION.x, NORMALIZED_QUATERNION.y, NORMALIZED_QUATERNION.z, NORMALIZED_QUATERNION.w,
                                                SCALE.x, SCALE.y, SCALE.z);

    TransformationMatrixWhiteBox<T> matrixFromNotNormalizedQuaternionUT;
    matrixFromNotNormalizedQuaternionUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                                   NOT_NORMALIZED_QUATERNION.x, NOT_NORMALIZED_QUATERNION.y, NOT_NORMALIZED_QUATERNION.z, NOT_NORMALIZED_QUATERNION.w,
                                                   SCALE.x, SCALE.y, SCALE.z);

    // [Verification]
    BOOST_CHECK( matrixFromNormalizedQuaternionUT != matrixFromNotNormalizedQuaternionUT );
}

/// <summary>
/// Checks that the rotation follows left-handed rules.
/// </summary>
ZTEST_CASE_TEMPLATE ( Initialize_FollowsLeftHandedRules_Test, TTemplateTypes )
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
    const Quaternion ROTATION_QUATERNION_AROUND_X(ROTATION_ANGLE, SFloat::_0, SFloat::_0);
    const Quaternion ROTATION_QUATERNION_AROUND_Y(SFloat::_0, ROTATION_ANGLE, SFloat::_0);
    const Quaternion ROTATION_QUATERNION_AROUND_Z(SFloat::_0, SFloat::_0, ROTATION_ANGLE);

    TransformationMatrixWhiteBox<T> ROTATION_AROUND_X;
    ROTATION_AROUND_X.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_X.x, ROTATION_QUATERNION_AROUND_X.y, ROTATION_QUATERNION_AROUND_X.z, ROTATION_QUATERNION_AROUND_X.w,
                                 SCALE.x, SCALE.y, SCALE.z);
    TransformationMatrixWhiteBox<T> ROTATION_AROUND_Y;
    ROTATION_AROUND_Y.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_Y.x, ROTATION_QUATERNION_AROUND_Y.y, ROTATION_QUATERNION_AROUND_Y.z, ROTATION_QUATERNION_AROUND_Y.w,
                                 SCALE.x, SCALE.y, SCALE.z);
    TransformationMatrixWhiteBox<T> ROTATION_AROUND_Z;
    ROTATION_AROUND_Z.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                 ROTATION_QUATERNION_AROUND_Z.x, ROTATION_QUATERNION_AROUND_Z.y, ROTATION_QUATERNION_AROUND_Z.z, ROTATION_QUATERNION_AROUND_Z.w,
                                 SCALE.x, SCALE.y, SCALE.z);

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
ZTEST_CASE_TEMPLATE ( Initialize_CompositionOrderIsScaleRotationTranslation_Test, TTemplateTypes )
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

    const Vector3 ZERO_VECTOR = Vector3::GetNullVector();
    const Quaternion IDENTITY_QUATERNION = Quaternion::GetIdentity();
    const Vector3 VECTOR_OF_ONES = Vector3::GetVectorOfOnes();

    TransformationMatrixWhiteBox<T> TRANSLATION_MATRIX;
    TRANSLATION_MATRIX.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                                  IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                                  VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    TransformationMatrixWhiteBox<T> ROTATION_MATRIX;
    ROTATION_MATRIX.Initialize(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                               ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                               VECTOR_OF_ONES.x, VECTOR_OF_ONES.y, VECTOR_OF_ONES.z);
    TransformationMatrixWhiteBox<T> SCALE_MATRIX;
    SCALE_MATRIX.Initialize(ZERO_VECTOR.x, ZERO_VECTOR.y, ZERO_VECTOR.z,
                            IDENTITY_QUATERNION.x, IDENTITY_QUATERNION.y, IDENTITY_QUATERNION.z, IDENTITY_QUATERNION.w,
                            SCALE.x, SCALE.y, SCALE.z);

    const TransformationMatrix<T> EXPECTED_VALUE = SCALE_MATRIX * ROTATION_MATRIX * TRANSLATION_MATRIX;

    // [Execution]
    TransformationMatrixWhiteBox<T> matrixUT;
    matrixUT.Initialize(TRANSLATION.x, TRANSLATION.y, TRANSLATION.z,
                        ROTATION.x, ROTATION.y, ROTATION.z, ROTATION.w,
                        SCALE.x, SCALE.y, SCALE.z);

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
    CheckFourthColumnIfExists(matrixUT, EXPECTED_VALUE);
}

// End - Test Suite: TransformationMatrix
ZTEST_SUITE_END()
