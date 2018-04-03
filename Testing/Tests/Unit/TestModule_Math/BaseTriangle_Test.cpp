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

#include "ZMath/BaseTriangle.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( BaseTriangle_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    BaseTriangle<T> triangleUT;

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if copy constructor sets triangle's points properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const BaseTriangle<T> EXPECTED_TRIANGLE(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

	// [Execution]
    BaseTriangle<T> triangleUT(EXPECTED_TRIANGLE);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    BaseTriangle<T> triangleUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

	// [Execution]
    BaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if an assertion fails when the input parameters are null pointers.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_AssertionFailsWhenInputValuesAreNull_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    float_z* NULL_POINTER = null_z;

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    const bool ASSERTION_FAILED_WHEN_A_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_B_IS_NULL = true;
    const bool ASSERTION_FAILED_WHEN_C_IS_NULL = true;

	// [Execution]
    bool bAssertionFailedWhenAIsNull = false;

    try
    {
        BaseTriangle<T> triangleUT(NULL_POINTER, VECTOR_COMPONENTS_B, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenAIsNull = true;
    }

    bool bAssertionFailedWhenBIsNull = false;

    try
    {
        BaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, NULL_POINTER, VECTOR_COMPONENTS_C);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenBIsNull = true;
    }

    bool bAssertionFailedWhenCIsNull = false;

    try
    {
        BaseTriangle<T> triangleUT(VECTOR_COMPONENTS_A, VECTOR_COMPONENTS_B, NULL_POINTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailedWhenCIsNull = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedWhenAIsNull, ASSERTION_FAILED_WHEN_A_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenBIsNull, ASSERTION_FAILED_WHEN_B_IS_NULL);
    BOOST_CHECK_EQUAL(bAssertionFailedWhenCIsNull, ASSERTION_FAILED_WHEN_C_IS_NULL);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor5_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_A[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR_COMPONENTS_B[] = { SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8 };
    float_z VECTOR_COMPONENTS_C[] = { SFloat::_0_5, SFloat::_0, SFloat::_9, SFloat::_10 };

    const T EXPECTED_VALUE_FOR_A(VECTOR_COMPONENTS_A);
    const T EXPECTED_VALUE_FOR_B(VECTOR_COMPONENTS_B);
    const T EXPECTED_VALUE_FOR_C(VECTOR_COMPONENTS_C);

    vf32_z INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C;

    SVF32::Pack(VECTOR_COMPONENTS_A[0], VECTOR_COMPONENTS_A[1], VECTOR_COMPONENTS_A[2], VECTOR_COMPONENTS_A[3], INPUT_FVECTOR_A);
    SVF32::Pack(VECTOR_COMPONENTS_B[0], VECTOR_COMPONENTS_B[1], VECTOR_COMPONENTS_B[2], VECTOR_COMPONENTS_B[3], INPUT_FVECTOR_B);
    SVF32::Pack(VECTOR_COMPONENTS_C[0], VECTOR_COMPONENTS_C[1], VECTOR_COMPONENTS_C[2], VECTOR_COMPONENTS_C[3], INPUT_FVECTOR_C);

	// [Execution]
    BaseTriangle<T> triangleUT(INPUT_FVECTOR_A, INPUT_FVECTOR_B, INPUT_FVECTOR_C);

    // [Verification]
    BOOST_CHECK(triangleUT.A == EXPECTED_VALUE_FOR_A);
    BOOST_CHECK(triangleUT.B == EXPECTED_VALUE_FOR_B);
    BOOST_CHECK(triangleUT.C == EXPECTED_VALUE_FOR_C);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5));
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND =  BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5), T(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T::GetNullVector(), T::GetNullVector(), T::GetNullVector() );

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test, TTemplateTypes )
{
    // [Preparation]
    const BaseTriangle<T> LEFT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );
    const BaseTriangle<T> RIGHT_OPERAND = BaseTriangle<T>( T(SFloat::Epsilon), T(SFloat::Epsilon), T(SFloat::Epsilon) );

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseTriangle
ZTEST_SUITE_END()
