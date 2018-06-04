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

#include "ZMath/TranslationMatrix.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/TransformationMatrix.h"
#include "ZMath/RotationMatrix3x3.h"
#include "ZMath/ScalingMatrix3x3.h"
#include "ZCommon/DataTypes/SVF32.h"
using namespace z::Internals;

typedef boost::mpl::list<Matrix4x3, Matrix4x4> TTemplateTypes;


ZTEST_SUITE_BEGIN( TranslationMatrix_TestSuite )

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
/// Checks that every matrix element is copied to the right destination matrix element.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_EveryElementCopiedToCorrespondingElement_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT(EXPECTED_VALUE);

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
/// Checks that the translation matrix is correctly built from its three displacement values.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_TranslationMatrixCorrectlyBuiltFromThreeValues_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT(SFloat::_2, SFloat::_3, SFloat::_4);

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
/// Checks that identity matrix is obtained when the three displacement values are zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_IdentityMatrixObtainedWhenThreeValuesAreZero_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TranslationMatrix<T> matrixUT(SFloat::_0, SFloat::_0, SFloat::_0);

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
/// Checks that the translation matrix is correctly built from a 3D vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_TranslationMatrixCorrectlyBuiltFrom3DVector_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    const Vector3 TRANSLATION(SFloat::_2, SFloat::_3, SFloat::_4);

    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT(TRANSLATION);

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
/// Checks that identity matrix is obtained when the 3D vector is a zero vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_IdentityMatrixObtainedWhen3DVectorIsZeroVector_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector3 ZERO_VECTOR = Vector3::GetNullVector();
	const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TranslationMatrix<T> matrixUT(ZERO_VECTOR);

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
/// Checks that the translation matrix is correctly built from a 4D vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_TranslationMatrixCorrectlyBuiltFrom4DVector_Test, TTemplateTypes )
{
    // [Preparation]
    T EXPECTED_VALUE;
    const Vector4 TRANSLATION(SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);

    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_2;
    EXPECTED_VALUE.ij[3][1] = SFloat::_3;
    EXPECTED_VALUE.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT(TRANSLATION);

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
/// Checks that identity matrix is obtained when the 4D vector is a zero vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_IdentityMatrixObtainedWhen4DVectorIsZeroVector_Test, TTemplateTypes )
{
    // [Preparation]
    const Vector4 ZERO_VECTOR = Vector4::GetNullVector();
	const T EXPECTED_VALUE = T::GetIdentity();

    // [Execution]
    TranslationMatrix<T> matrixUT(ZERO_VECTOR);

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
/// Checks that w value from a 4D vector doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_WValueFrom4DVectorDoesNotParticipate_Test, TTemplateTypes )
{
	// [Preparation]
    const Vector4 TRANSLATIONA(SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);
	const Vector4 TRANSLATIONB(SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_9);

    // [Execution]
    TranslationMatrix<T> matrixAUT(TRANSLATIONA);
	TranslationMatrix<T> matrixBUT(TRANSLATIONB);

	// [Verification]
	BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that all the elements of the returned matrix equal zero but those that are in the diagonal, which equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetIdentity_AllElementsEqualZeroAndDiagonalEqualsOne_Test, TTemplateTypes )
{
    // [Preparation]
    const T EXPECTED_VALUE = T::GetIdentity();

	// [Execution]
    TranslationMatrix<T> matrixUT = TranslationMatrix<T>::GetIdentity();

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
/// Checks that two translation matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct1_TranslationMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]

    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    const TranslationMatrix<Matrix4x3> OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    TranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
/// Checks that two translation matrices product is commutative.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct1_TranslationMatricesProductIsCommutative_Test, TTemplateTypes )
{
    // [Preparation]

    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    const TranslationMatrix<Matrix4x3> OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;
    TranslationMatrix<Matrix4x3> matrixUT2 = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, OPERAND1);
}

/// <summary>
/// Checks that two translation matrices are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_TranslationMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]

    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    TranslationMatrix<Matrix4x4> OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    TranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;

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
/// Checks that two translation matrices product is commutative.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_TranslationMatricesProductIsCommutative_Test, TTemplateTypes )
{
   // [Preparation]

    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    const TranslationMatrix<Matrix4x4> OPERAND2(SFloat::_4, SFloat::_5, SFloat::_6);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1 * OPERAND2;
    TranslationMatrix<Matrix4x4> matrixUT2 = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][0], matrixUT2.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][1], matrixUT2.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[0][2], matrixUT2.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][0], matrixUT2.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][1], matrixUT2.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[1][2], matrixUT2.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][0], matrixUT2.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][1], matrixUT2.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[2][2], matrixUT2.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][0], matrixUT2.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][1], matrixUT2.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixUT.ij[3][2], matrixUT2.ij[3][2]) );
    CheckFourthColumnIfExists(matrixUT, OPERAND1);
    CheckFourthColumnIfExists(matrixUT2, OPERAND2);
}

/// <summary>
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfLeftOperandDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<Matrix4x4> OPERANDA1 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TranslationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SFloat::_1;
    OPERANDA2.ij[0][1] = SFloat::_2;
    OPERANDA2.ij[0][2] = SFloat::_3;
    OPERANDA2.ij[1][0] = SFloat::_4;
    OPERANDA2.ij[1][1] = SFloat::_5;
    OPERANDA2.ij[1][2] = SFloat::_6;
    OPERANDA2.ij[2][0] = SFloat::_7;
    OPERANDA2.ij[2][1] = SFloat::_8;
    OPERANDA2.ij[2][2] = SFloat::_9;
    OPERANDA2.ij[3][0] = SFloat::_10;
    OPERANDA2.ij[3][1] = (float_z)11.0;
    OPERANDA2.ij[3][2] = (float_z)12.0;

    TranslationMatrix<Matrix4x4> OPERANDB1 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    TranslationMatrix<T> OPERANDB2 = OPERANDA2;

    // [Execution]
    TranslationMatrix<Matrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    TranslationMatrix<Matrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct2_FourthColumnOfRightOperandDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERANDA1;
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

    TranslationMatrix<Matrix4x4> OPERANDA2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TranslationMatrix<T> OPERANDB1 = OPERANDA1;

    TranslationMatrix<Matrix4x4> OPERANDB2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                               (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                               (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                               (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    // [Execution]
    TranslationMatrix<T> matrixAUT = OPERANDA1 * OPERANDA2;
    TranslationMatrix<T> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a 3x3 scale matrix are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct3_TranslationMatrixAnd3x3ScaleMatrixAreCorrectlyMultiplied_Test, TTemplateTypes )
{
     // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_3);

    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_4;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][0] = SFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SFloat::_10;
    EXPECTED_VALUE.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * SCALE;

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
/// Checks that only the diagonal of the scaling matrix participates in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct3_OnlyTheDiagonalOfScalingMatrixMatters_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERANDA1(SFloat::_1, SFloat::_2, SFloat::_3);

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

    TranslationMatrix<T> OPERANDB1 = OPERANDA1;

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
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE( OperatorProduct3_FourthColumnOfLeftOperandDoesntMatter )
{
     // [Preparation]
    const ScalingMatrix3x3 SCALE(SFloat::_4, SFloat::_5, SFloat::_3);

    TranslationMatrix<Matrix4x4> OPERANDA1(SFloat::_1, SFloat::_2, SFloat::_3);
    FillFourthColumnIfExists(OPERANDA1, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    TranslationMatrix<Matrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixAUT = OPERANDA1 * SCALE;
    TransformationMatrix<Matrix4x4> matrixBUT = OPERANDB1 * SCALE;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a 3x3 rotation matrix are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct4_TranslationMatrixAnd3x3RotationMatrixAreCorrectlyMultiplied_Test, TTemplateTypes )
{
     // [Preparation]
    TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    RotationMatrix3x3 ROTATION;
    ROTATION.ij[0][0] = (float_z)10.0;
    ROTATION.ij[0][1] = (float_z)11.0;
    ROTATION.ij[0][2] = (float_z)12.0;
    ROTATION.ij[1][0] = (float_z)13.0;
    ROTATION.ij[1][1] = (float_z)14.0;
    ROTATION.ij[1][2] = (float_z)15.0;
    ROTATION.ij[2][0] = (float_z)16.0;
    ROTATION.ij[2][1] = (float_z)17.0;
    ROTATION.ij[2][2] = (float_z)18.0;

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = (float_z)10.0;
    EXPECTED_VALUE.ij[0][1] = (float_z)11.0;
    EXPECTED_VALUE.ij[0][2] = (float_z)12.0;
    EXPECTED_VALUE.ij[1][0] = (float_z)13.0;
    EXPECTED_VALUE.ij[1][1] = (float_z)14.0;
    EXPECTED_VALUE.ij[1][2] = (float_z)15.0;
    EXPECTED_VALUE.ij[2][0] = (float_z)16.0;
    EXPECTED_VALUE.ij[2][1] = (float_z)17.0;
    EXPECTED_VALUE.ij[2][2] = (float_z)18.0;
    EXPECTED_VALUE.ij[3][0] = (float_z)84.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)90.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)96.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TransformationMatrix<T> matrixUT = OPERAND1 * ROTATION;

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
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE( OperatorProduct4_FourthColumnOfLeftOperandDoesntMatter )
{
     // [Preparation]
    RotationMatrix3x3 ROTATION;
    ROTATION.ij[0][0] = (float_z)10.0;
    ROTATION.ij[0][1] = (float_z)11.0;
    ROTATION.ij[0][2] = (float_z)12.0;
    ROTATION.ij[1][0] = (float_z)13.0;
    ROTATION.ij[1][1] = (float_z)14.0;
    ROTATION.ij[1][2] = (float_z)15.0;
    ROTATION.ij[2][0] = (float_z)16.0;
    ROTATION.ij[2][1] = (float_z)17.0;
    ROTATION.ij[2][2] = (float_z)18.0;

    TranslationMatrix<Matrix4x4> OPERANDA1(SFloat::_1, SFloat::_2, SFloat::_3);
    FillFourthColumnIfExists(OPERANDA1, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    TranslationMatrix<Matrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixAUT = OPERANDA1 * ROTATION;
    TransformationMatrix<Matrix4x4> matrixBUT = OPERANDB1 * ROTATION;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that a translation matrix and a transformation matrix are correctly multiplied.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProduct5_TranslationMatrixAndTransformationMatrixAreCorrectlyMultiplied_Test, TTemplateTypes )
{
     // [Preparation]
    const TranslationMatrix<T> OPERAND1(SFloat::_1, SFloat::_2, SFloat::_3);

    TransformationMatrix<T> OPERAND2;
    OPERAND2.ij[0][0] = SFloat::_4;
    OPERAND2.ij[0][1] = SFloat::_1;
    OPERAND2.ij[0][2] = SFloat::_2;
    OPERAND2.ij[1][0] = SFloat::_3;
    OPERAND2.ij[1][1] = SFloat::_5;
    OPERAND2.ij[1][2] = SFloat::_4;
    OPERAND2.ij[2][0] = SFloat::_5;
    OPERAND2.ij[2][1] = SFloat::_6;
    OPERAND2.ij[2][2] = SFloat::_3;
    OPERAND2.ij[3][0] = SFloat::_4;
    OPERAND2.ij[3][1] = SFloat::_10;
    OPERAND2.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(OPERAND2, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    TransformationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_4;
    EXPECTED_VALUE.ij[0][1] = SFloat::_1;
    EXPECTED_VALUE.ij[0][2] = SFloat::_2;
    EXPECTED_VALUE.ij[1][0] = SFloat::_3;
    EXPECTED_VALUE.ij[1][1] = SFloat::_5;
    EXPECTED_VALUE.ij[1][2] = SFloat::_4;
    EXPECTED_VALUE.ij[2][0] = SFloat::_5;
    EXPECTED_VALUE.ij[2][1] = SFloat::_6;
    EXPECTED_VALUE.ij[2][2] = SFloat::_3;
    EXPECTED_VALUE.ij[3][0] = (float_z)29.0;
    EXPECTED_VALUE.ij[3][1] = (float_z)39.0;
    EXPECTED_VALUE.ij[3][2] = (float_z)28.0;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

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
/// Checks that the fourth column of the left operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE( OperatorProduct5_FourthColumnOfLeftOperandDoesntMatter, TTemplateTypes )
{
     // [Preparation]
    const TranslationMatrix<Matrix4x4> OPERANDA1(SFloat::_1, SFloat::_2, SFloat::_3);

    TransformationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SFloat::_4;
    OPERANDA2.ij[0][1] = SFloat::_0;
    OPERANDA2.ij[0][2] = SFloat::_0;
    OPERANDA2.ij[1][0] = SFloat::_0;
    OPERANDA2.ij[1][1] = SFloat::_5;
    OPERANDA2.ij[1][2] = SFloat::_0;
    OPERANDA2.ij[2][0] = SFloat::_0;
    OPERANDA2.ij[2][1] = SFloat::_0;
    OPERANDA2.ij[2][2] = SFloat::_3;
    OPERANDA2.ij[3][0] = SFloat::_4;
    OPERANDA2.ij[3][1] = SFloat::_10;
    OPERANDA2.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(OPERANDA2, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    TranslationMatrix<Matrix4x4> OPERANDB1 = OPERANDA1;
    FillFourthColumnIfExists(OPERANDB1, SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);

    TransformationMatrix<T> OPERANDB2 = OPERANDA2;

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<Matrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that the fourth column of the right operand (when using 4x4 matrices) doesn't participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE( OperatorProduct5_FourthColumnOfRightOperandDoesntMatter, TTemplateTypes )
{
     // [Preparation]
    const TranslationMatrix<Matrix4x4> OPERANDA1(SFloat::_1, SFloat::_2, SFloat::_3);

    TransformationMatrix<T> OPERANDA2;
    OPERANDA2.ij[0][0] = SFloat::_4;
    OPERANDA2.ij[0][1] = SFloat::_0;
    OPERANDA2.ij[0][2] = SFloat::_0;
    OPERANDA2.ij[1][0] = SFloat::_0;
    OPERANDA2.ij[1][1] = SFloat::_5;
    OPERANDA2.ij[1][2] = SFloat::_0;
    OPERANDA2.ij[2][0] = SFloat::_0;
    OPERANDA2.ij[2][1] = SFloat::_0;
    OPERANDA2.ij[2][2] = SFloat::_3;
    OPERANDA2.ij[3][0] = SFloat::_4;
    OPERANDA2.ij[3][1] = SFloat::_10;
    OPERANDA2.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(OPERANDA2, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    TranslationMatrix<Matrix4x4> OPERANDB1 = OPERANDA1;

    TransformationMatrix<T> OPERANDB2 = OPERANDA2;
    FillFourthColumnIfExists(OPERANDB2, SFloat::_2, SFloat::_3, SFloat::_4, SFloat::_5);

    // [Execution]
    TransformationMatrix<Matrix4x4> matrixAUT = OPERANDA1 * OPERANDA2;
    TransformationMatrix<Matrix4x4> matrixBUT = OPERANDB1 * OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that product assignation operator works in the right way.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation1_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = SFloat::_1;
    OPERAND2.ij[0][1] = SFloat::_0;
    OPERAND2.ij[0][2] = SFloat::_0;
    OPERAND2.ij[1][0] = SFloat::_0;
    OPERAND2.ij[1][1] = SFloat::_1;
    OPERAND2.ij[1][2] = SFloat::_0;
    OPERAND2.ij[2][0] = SFloat::_0;
    OPERAND2.ij[2][1] = SFloat::_0;
    OPERAND2.ij[2][2] = SFloat::_1;
    OPERAND2.ij[3][0] = SFloat::_3;
    OPERAND2.ij[3][1] = SFloat::_4;
    OPERAND2.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1;
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
/// Checks that a 4x3 translation matrix can be multiplied by itself (same object instance).
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_CanBeMultipliedByItself_Test )
{
     // [Preparation]
    TranslationMatrix<Matrix4x3> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;

    TranslationMatrix<Matrix4x3> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SFloat::_6;
    EXPECTED_VALUE.ij[3][2] = SFloat::_8;

    // [Execution]
    TranslationMatrix<Matrix4x3> matrixUT = OPERAND1;
    matrixUT *= OPERAND1;

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
/// Checks if this is a commutative operation (using a 4x3 translation matrix operator).
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation1_IsCommutative_Test, TTemplateTypes )
{
     // [Preparation]
    TranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x3> OPERAND2;
    OPERAND2.ij[0][0] = SFloat::_1;
    OPERAND2.ij[0][1] = SFloat::_0;
    OPERAND2.ij[0][2] = SFloat::_0;
    OPERAND2.ij[1][0] = SFloat::_0;
    OPERAND2.ij[1][1] = SFloat::_1;
    OPERAND2.ij[1][2] = SFloat::_0;
    OPERAND2.ij[2][0] = SFloat::_0;
    OPERAND2.ij[2][1] = SFloat::_0;
    OPERAND2.ij[2][2] = SFloat::_1;
    OPERAND2.ij[3][0] = SFloat::_3;
    OPERAND2.ij[3][1] = SFloat::_4;
    OPERAND2.ij[3][2] = SFloat::_5;

    // [Execution]
    TranslationMatrix<T> matrixAUT = OPERAND1;
    matrixAUT *= OPERAND2;
    TranslationMatrix<Matrix4x3> matrixBUT = OPERAND2;
    matrixBUT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][0], matrixBUT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][1], matrixBUT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][2], matrixBUT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][0], matrixBUT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][1], matrixBUT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][2], matrixBUT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][0], matrixBUT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][1], matrixBUT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][2], matrixBUT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][0], matrixBUT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][1], matrixBUT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][2], matrixBUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixAUT, OPERAND1);
}

/// <summary>
/// Checks that a 4x4 translation matrix can be multiplied by itself (same object instance).
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_CanBeMultipliedByItself_Test )
{
     // [Preparation]
    TranslationMatrix<Matrix4x4> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_4;
    EXPECTED_VALUE.ij[3][1] = SFloat::_6;
    EXPECTED_VALUE.ij[3][2] = SFloat::_8;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<Matrix4x4> matrixUT = OPERAND1;
    matrixUT *= OPERAND1;

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
/// Checks if this is a commutative operation (using a 4x4 translation matrix operator).
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation2_IsCommutative_Test, TTemplateTypes )
{
     // [Preparation]
    TranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = SFloat::_1;
    OPERAND2.ij[0][1] = SFloat::_0;
    OPERAND2.ij[0][2] = SFloat::_0;
    OPERAND2.ij[1][0] = SFloat::_0;
    OPERAND2.ij[1][1] = SFloat::_1;
    OPERAND2.ij[1][2] = SFloat::_0;
    OPERAND2.ij[2][0] = SFloat::_0;
    OPERAND2.ij[2][1] = SFloat::_0;
    OPERAND2.ij[2][2] = SFloat::_1;
    OPERAND2.ij[3][0] = SFloat::_3;
    OPERAND2.ij[3][1] = SFloat::_4;
    OPERAND2.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixAUT = OPERAND1;
    matrixAUT *= OPERAND2;
    TranslationMatrix<Matrix4x4> matrixBUT = OPERAND2;
    matrixBUT *= OPERAND1;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][0], matrixBUT.ij[0][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][1], matrixBUT.ij[0][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[0][2], matrixBUT.ij[0][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][0], matrixBUT.ij[1][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][1], matrixBUT.ij[1][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[1][2], matrixBUT.ij[1][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][0], matrixBUT.ij[2][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][1], matrixBUT.ij[2][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[2][2], matrixBUT.ij[2][2]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][0], matrixBUT.ij[3][0]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][1], matrixBUT.ij[3][1]) );
    BOOST_CHECK( SFloat::AreEqual(matrixAUT.ij[3][2], matrixBUT.ij[3][2]) );
    CheckFourthColumnIfExists(matrixAUT, OPERAND1);
    CheckFourthColumnIfExists(matrixBUT, OPERAND2);
}

/// <summary>
/// Checks that product assignation operator works in the right way.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation3_CommonMatricesAreCorrectlyMultiplied_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERAND1;
    OPERAND1.ij[0][0] = SFloat::_1;
    OPERAND1.ij[0][1] = SFloat::_0;
    OPERAND1.ij[0][2] = SFloat::_0;
    OPERAND1.ij[1][0] = SFloat::_0;
    OPERAND1.ij[1][1] = SFloat::_1;
    OPERAND1.ij[1][2] = SFloat::_0;
    OPERAND1.ij[2][0] = SFloat::_0;
    OPERAND1.ij[2][1] = SFloat::_0;
    OPERAND1.ij[2][2] = SFloat::_1;
    OPERAND1.ij[3][0] = SFloat::_2;
    OPERAND1.ij[3][1] = SFloat::_3;
    OPERAND1.ij[3][2] = SFloat::_4;
    FillFourthColumnIfExists(OPERAND1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> OPERAND2;
    OPERAND2.ij[0][0] = SFloat::_1;
    OPERAND2.ij[0][1] = SFloat::_0;
    OPERAND2.ij[0][2] = SFloat::_0;
    OPERAND2.ij[1][0] = SFloat::_0;
    OPERAND2.ij[1][1] = SFloat::_1;
    OPERAND2.ij[1][2] = SFloat::_0;
    OPERAND2.ij[2][0] = SFloat::_0;
    OPERAND2.ij[2][1] = SFloat::_0;
    OPERAND2.ij[2][2] = SFloat::_1;
    OPERAND2.ij[3][0] = SFloat::_3;
    OPERAND2.ij[3][1] = SFloat::_4;
    OPERAND2.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(OPERAND2, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = SFloat::_5;
    EXPECTED_VALUE.ij[3][1] = SFloat::_7;
    EXPECTED_VALUE.ij[3][2] = SFloat::_9;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT = OPERAND1;
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
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation4_FourthColumnOfRightOperandDoesntMatter_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_0;
    OPERANDA1.ij[0][2] = SFloat::_0;
    OPERANDA1.ij[1][0] = SFloat::_0;
    OPERANDA1.ij[1][1] = SFloat::_1;
    OPERANDA1.ij[1][2] = SFloat::_0;
    OPERANDA1.ij[2][0] = SFloat::_0;
    OPERANDA1.ij[2][1] = SFloat::_0;
    OPERANDA1.ij[2][2] = SFloat::_1;
    OPERANDA1.ij[3][0] = SFloat::_3;
    OPERANDA1.ij[3][1] = SFloat::_4;
    OPERANDA1.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(OPERANDA1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> OPERANDA2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                         (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                         (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TranslationMatrix<T> OPERANDB1 = OPERANDA1;

    TranslationMatrix<Matrix4x4> OPERANDB2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)37.0,
                                                                                         (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)38.0,
                                                                                         (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)39.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    // [Execution]
    TranslationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    TranslationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that only the third first elements of the fourth row of the operands participate in the operation.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorProductAssignation5_OnlyFourthRowElementsOfOperandsParticipate_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> OPERANDA1;
    OPERANDA1.ij[0][0] = SFloat::_1;
    OPERANDA1.ij[0][1] = SFloat::_0;
    OPERANDA1.ij[0][2] = SFloat::_0;
    OPERANDA1.ij[1][0] = SFloat::_0;
    OPERANDA1.ij[1][1] = SFloat::_1;
    OPERANDA1.ij[1][2] = SFloat::_0;
    OPERANDA1.ij[2][0] = SFloat::_0;
    OPERANDA1.ij[2][1] = SFloat::_0;
    OPERANDA1.ij[2][2] = SFloat::_1;
    OPERANDA1.ij[3][0] = SFloat::_3;
    OPERANDA1.ij[3][1] = SFloat::_4;
    OPERANDA1.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(OPERANDA1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> OPERANDA2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)17.0, (float_z)18.0, (float_z)19.0, (float_z)29.0,
                                                                                         (float_z)20.0, (float_z)21.0, (float_z)22.0, (float_z)30.0,
                                                                                         (float_z)23.0, (float_z)24.0, (float_z)25.0, (float_z)31.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)32.0));

    TranslationMatrix<T> OPERANDB1 = OPERANDA1;

    TranslationMatrix<Matrix4x4> OPERANDB2 = TranslationMatrix<Matrix4x4>(Matrix4x4((float_z)7.0, (float_z)8.0, (float_z)9.0, (float_z)7.0,
                                                                                         (float_z)2.0, (float_z)1.0, (float_z)2.0, (float_z)8.0,
                                                                                         (float_z)3.0, (float_z)4.0, (float_z)5.0, (float_z)3.0,
                                                                                         (float_z)26.0, (float_z)27.0, (float_z)28.0, (float_z)40.0));

    // [Execution]
    TranslationMatrix<T> matrixAUT = OPERANDA1;
    matrixAUT *= OPERANDA2;
    TranslationMatrix<T> matrixBUT = OPERANDB1;
    matrixBUT *= OPERANDB2;

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

/// <summary>
/// Checks that every element of the source matrix is copied to the right element of the target matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_EveryElementIsAssignedToRightTargetElement_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
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

    const TranslationMatrix<T> EXPECTED_VALUE = MATRIX;

    // [Execution]
    TranslationMatrix<T> matrixUT;
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
/// Checks that the translation matrix is correctly inverted.
/// </summary>
ZTEST_CASE_TEMPLATE ( Invert_TranslationMatrixIsCorrectlyInverted_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_0;
    MATRIX.ij[0][2] = SFloat::_0;
    MATRIX.ij[1][0] = SFloat::_0;
    MATRIX.ij[1][1] = SFloat::_1;
    MATRIX.ij[1][2] = SFloat::_0;
    MATRIX.ij[2][0] = SFloat::_0;
    MATRIX.ij[2][1] = SFloat::_0;
    MATRIX.ij[2][2] = SFloat::_1;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<T> EXPECTED_VALUE;
    EXPECTED_VALUE.ij[0][0] = SFloat::_1;
    EXPECTED_VALUE.ij[0][1] = SFloat::_0;
    EXPECTED_VALUE.ij[0][2] = SFloat::_0;
    EXPECTED_VALUE.ij[1][0] = SFloat::_0;
    EXPECTED_VALUE.ij[1][1] = SFloat::_1;
    EXPECTED_VALUE.ij[1][2] = SFloat::_0;
    EXPECTED_VALUE.ij[2][0] = SFloat::_0;
    EXPECTED_VALUE.ij[2][1] = SFloat::_0;
    EXPECTED_VALUE.ij[2][2] = SFloat::_1;
    EXPECTED_VALUE.ij[3][0] = -SFloat::_3;
    EXPECTED_VALUE.ij[3][1] = -SFloat::_4;
    EXPECTED_VALUE.ij[3][2] = -SFloat::_5;
    FillFourthColumnIfExists(EXPECTED_VALUE, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    // [Execution]
    TranslationMatrix<T> matrixUT = MATRIX.Invert();

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
/// Checks that the fourth column (when using 4x4 matrices) doesn't participate in the invert operation.
/// </summary>
ZTEST_CASE ( Invert_FourthColumnDoesntParticipate_Test )
{
    // [Preparation]
    TranslationMatrix<Matrix4x4> MATRIX1;
    MATRIX1.ij[0][0] = SFloat::_1;
    MATRIX1.ij[0][1] = SFloat::_0;
    MATRIX1.ij[0][2] = SFloat::_0;
    MATRIX1.ij[1][0] = SFloat::_0;
    MATRIX1.ij[1][1] = SFloat::_1;
    MATRIX1.ij[1][2] = SFloat::_0;
    MATRIX1.ij[2][0] = SFloat::_0;
    MATRIX1.ij[2][1] = SFloat::_0;
    MATRIX1.ij[2][2] = SFloat::_1;
    MATRIX1.ij[3][0] = SFloat::_3;
    MATRIX1.ij[3][1] = SFloat::_4;
    MATRIX1.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<Matrix4x4> MATRIX2;
    MATRIX2.ij[0][0] = SFloat::_1;
    MATRIX2.ij[0][1] = SFloat::_0;
    MATRIX2.ij[0][2] = SFloat::_0;
    MATRIX2.ij[1][0] = SFloat::_0;
    MATRIX2.ij[1][1] = SFloat::_1;
    MATRIX2.ij[1][2] = SFloat::_0;
    MATRIX2.ij[2][0] = SFloat::_0;
    MATRIX2.ij[2][1] = SFloat::_0;
    MATRIX2.ij[2][2] = SFloat::_1;
    MATRIX2.ij[3][0] = SFloat::_3;
    MATRIX2.ij[3][1] = SFloat::_4;
    MATRIX2.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX2, SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

    // [Execution]
    TranslationMatrix<Matrix4x4> matrixAUT = MATRIX1.Invert();
    TranslationMatrix<Matrix4x4> matrixBUT = MATRIX2.Invert();

    // [Verification]
    BOOST_CHECK( matrixAUT == matrixBUT );
}

// <summary>
/// Checks that it returns always True.
/// </summary>
ZTEST_CASE_TEMPLATE ( HasInverse_AlwaysReturnsTrue_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX1;
    MATRIX1.ij[0][0] = SFloat::_1;
    MATRIX1.ij[0][1] = SFloat::_0;
    MATRIX1.ij[0][2] = SFloat::_0;
    MATRIX1.ij[1][0] = SFloat::_0;
    MATRIX1.ij[1][1] = SFloat::_1;
    MATRIX1.ij[1][2] = SFloat::_0;
    MATRIX1.ij[2][0] = SFloat::_0;
    MATRIX1.ij[2][1] = SFloat::_0;
    MATRIX1.ij[2][2] = SFloat::_1;
    MATRIX1.ij[3][0] = SFloat::_3;
    MATRIX1.ij[3][1] = SFloat::_4;
    MATRIX1.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX1, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<T> MATRIX2;
    MATRIX2.ij[0][0] = SFloat::_1;
    MATRIX2.ij[0][1] = SFloat::_2;
    MATRIX2.ij[0][2] = SFloat::_3;
    MATRIX2.ij[1][0] = SFloat::_4;
    MATRIX2.ij[1][1] = SFloat::_5;
    MATRIX2.ij[1][2] = SFloat::_6;
    MATRIX2.ij[2][0] = SFloat::_7;
    MATRIX2.ij[2][1] = SFloat::_8;
    MATRIX2.ij[2][2] = SFloat::_9;
    MATRIX2.ij[3][0] = SFloat::_10;
    MATRIX2.ij[3][1] = (float_z)11.0;
    MATRIX2.ij[3][2] = (float_z)12.0;
    FillFourthColumnIfExists(MATRIX2, (float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0);

    const bool EXPECTED_VALUE = true;

    // [Execution]
    bool bResultAUT = MATRIX1.HasInverse();
    bool bResultBUT = MATRIX2.HasInverse();

    // [Verification]
    BOOST_CHECK_EQUAL(bResultAUT, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bResultBUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that 3 translation values are correctly extracted from a common transformation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation1_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_0;
    MATRIX.ij[0][2] = SFloat::_0;
    MATRIX.ij[1][0] = SFloat::_0;
    MATRIX.ij[1][1] = SFloat::_1;
    MATRIX.ij[1][2] = SFloat::_0;
    MATRIX.ij[2][0] = SFloat::_0;
    MATRIX.ij[2][1] = SFloat::_0;
    MATRIX.ij[2][2] = SFloat::_1;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

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
    TranslationMatrix<T> MATRIX = T::GetIdentity();

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
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_0;
    MATRIX.ij[0][2] = SFloat::_0;
    MATRIX.ij[1][0] = SFloat::_0;
    MATRIX.ij[1][1] = SFloat::_1;
    MATRIX.ij[1][2] = SFloat::_0;
    MATRIX.ij[2][0] = SFloat::_0;
    MATRIX.ij[2][1] = SFloat::_0;
    MATRIX.ij[2][2] = SFloat::_1;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

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
/// Checks that 3 translation values equal zero when translation matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation2_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX = T::GetIdentity();

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
/// Checks that translation vector is correctly extracted from a common translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesAreCorrectlyExtractedFromCommonMatrix_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_0;
    MATRIX.ij[0][2] = SFloat::_0;
    MATRIX.ij[1][0] = SFloat::_0;
    MATRIX.ij[1][1] = SFloat::_1;
    MATRIX.ij[1][2] = SFloat::_0;
    MATRIX.ij[2][0] = SFloat::_0;
    MATRIX.ij[2][1] = SFloat::_0;
    MATRIX.ij[2][2] = SFloat::_1;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    const Vector4 EXPECTED_VALUE(MATRIX.ij[3][0], MATRIX.ij[3][1], MATRIX.ij[3][2], SFloat::_0);

    // [Execution]
    Vector4 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
    BOOST_CHECK_EQUAL(vTranslationUT.w, EXPECTED_VALUE.w);
}

/// <summary>
/// Checks that w value of the translation vector is always zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation3_WValueIsAlwaysZero_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_9;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    TranslationMatrix<T> MATRIX2 = MATRIX;
    MATRIX2.ij[3][0] = -SFloat::_1;
    MATRIX2.ij[3][1] = -SFloat::_2;
    MATRIX2.ij[3][2] = -SFloat::_3;

    const float_z EXPECTED_VALUE = SFloat::_0;

    // [Execution]
    Vector4 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);
    float_z fWValue = vTranslationUT.w;

    Vector4 vTranslationUT2(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6);
    MATRIX2.GetTranslation(vTranslationUT2);
    float_z fWValue2 = vTranslationUT2.w;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fWValue, EXPECTED_VALUE) );
    BOOST_CHECK( SFloat::AreEqual(fWValue2, EXPECTED_VALUE) );
}

/// <summary>
/// Checks that 3 translation values equal zero when translation matrix is the identity.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetTranslation3_TranslationValuesEqualZeroWhenMatrixIsIdentity_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX = T::GetIdentity();

    const Vector4 EXPECTED_VALUE(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    // [Execution]
    Vector4 vTranslationUT(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2);
    MATRIX.GetTranslation(vTranslationUT);

    // [Verification]
    BOOST_CHECK_EQUAL(vTranslationUT.x, EXPECTED_VALUE.x);
    BOOST_CHECK_EQUAL(vTranslationUT.y, EXPECTED_VALUE.y);
    BOOST_CHECK_EQUAL(vTranslationUT.z, EXPECTED_VALUE.z);
    BOOST_CHECK_EQUAL(vTranslationUT.w, EXPECTED_VALUE.w);
}

ZTEST_CASE_TEMPLATE ( GetDeterminant_ResultIsAlwaysOne_Test, TTemplateTypes )
{
    // [Preparation]
    TranslationMatrix<T> MATRIX;
    MATRIX.ij[0][0] = SFloat::_1;
    MATRIX.ij[0][1] = SFloat::_2;
    MATRIX.ij[0][2] = SFloat::_3;
    MATRIX.ij[1][0] = SFloat::_4;
    MATRIX.ij[1][1] = SFloat::_5;
    MATRIX.ij[1][2] = SFloat::_6;
    MATRIX.ij[2][0] = SFloat::_7;
    MATRIX.ij[2][1] = SFloat::_8;
    MATRIX.ij[2][2] = SFloat::_9;
    MATRIX.ij[3][0] = SFloat::_3;
    MATRIX.ij[3][1] = SFloat::_4;
    MATRIX.ij[3][2] = SFloat::_5;
    FillFourthColumnIfExists(MATRIX, SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);

    const float_z EXPECTED_VALUE = 1;

    // [Execution]
    float_z fDeterminant = MATRIX.GetDeterminant();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDeterminant, EXPECTED_VALUE) );
}

// End - Test Suite: TranslationMatrix
ZTEST_SUITE_END()
