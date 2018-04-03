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

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( SFloat_TestSuite )

/// <summary>
/// Checks that it returns True when the floating point value is Not a Number.
/// </summary>
ZTEST_CASE ( IsNaN_ReturnsTrueWhenValueIsNaN_Test )
{
    // [Preparation]
    const float_z NAN_VALUE = SFloat::_0 / SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNaN(NAN_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is a number.
/// </summary>
ZTEST_CASE ( IsNaN_ReturnsFalseWhenValueIsANumber_Test )
{
    // [Preparation]
    const float_z NUMBER = SFloat::_1;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNaN(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is an infinite number.
/// </summary>
ZTEST_CASE ( IsNaN_ReturnsFalseWhenValueIsInfinite_Test )
{
    // [Preparation]
    const float_z INFINITE_VALUE = SFloat::MaxFloat_Z * SFloat::MaxFloat_Z;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNaN(INFINITE_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is infinite.
/// </summary>
ZTEST_CASE ( IsInfinite_ReturnsTrueWhenValueIsInfinite_Test )
{
    // [Preparation]
    const float_z INFINITE_VALUE = SFloat::MaxFloat_Z * SFloat::MaxFloat_Z;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsInfinite(INFINITE_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is not infinite.
/// </summary>
ZTEST_CASE ( IsInfinite_ReturnsFalseWhenValueIsNotInfinite_Test )
{
    // [Preparation]
    const float_z NOT_INFINITE = SFloat::_1;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsInfinite(NOT_INFINITE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is not a number.
/// </summary>
ZTEST_CASE ( IsInfinite_ReturnsFalseWhenValueIsNaN_Test )
{
    // [Preparation]
    const float_z NAN_VALUE = SFloat::_0 / SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsInfinite(NAN_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is Not a Number.
/// </summary>
ZTEST_CASE ( IsNanOrInfinite_ReturnsTrueWhenValueIsNaN_Test )
{
    // [Preparation]
    const float_z NAN_VALUE = SFloat::_0 / SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNanOrInfinite(NAN_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when the floating point value is a common number.
/// </summary>
ZTEST_CASE ( IsNanOrInfinite_ReturnsFalseWhenValueIsACommonNumber_Test )
{
    // [Preparation]
    const float_z NUMBER = SFloat::_1;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNanOrInfinite(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when the floating point value is an infinite number.
/// </summary>
ZTEST_CASE ( IsNanOrInfinite_ReturnsTrueWhenValueIsInfinite_Test )
{
    // [Preparation]
    const float_z INFINITE_VALUE = SFloat::MaxFloat_Z * SFloat::MaxFloat_Z;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNanOrInfinite(INFINITE_VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences equal tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual1_ReturnsTrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual1_ReturnsTrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual1_ReturnsFalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are exactly equal.
/// </summary>
ZTEST_CASE ( AreEqual1_ReturnsTrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences equal tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual2_ReturnsTrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual2_ReturnsTrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE - TOLERANCE * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( AreEqual2_ReturnsFalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are exactly equal.
/// </summary>
ZTEST_CASE ( AreEqual2_ReturnsTrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences equal tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual1_ReturnsFalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual1_ReturnsFalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual1_ReturnsTrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are exactly equal.
/// </summary>
ZTEST_CASE ( AreNotEqual1_ReturnsFalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences equal tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual2_ReturnsFalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operand differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual2_ReturnsFalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE - TOLERANCE * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operand differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( AreNotEqual2_ReturnsTrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE * SFloat::_0_5;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are exactly equal.
/// </summary>
ZTEST_CASE ( AreNotEqual2_ReturnsFalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::AreNotEqual(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan1_ReturnsTrueWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan1_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are equal.
/// </summary>
ZTEST_CASE ( IsGreaterThan1_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan1_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan2_ReturnsTrueWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan2_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when operands are equal.
/// </summary>
ZTEST_CASE ( IsGreaterThan2_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterThan2_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE + TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan1_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is lower than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan1_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when operands are equal.
/// </summary>
ZTEST_CASE ( IsLessThan1_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan1_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan2_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is lower than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan2_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when operands are equal.
/// </summary>
ZTEST_CASE ( IsLessThan2_ReturnsFalseWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessThan2_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE + TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessThan(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals1_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is greater than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals1_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are equal.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals1_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals1_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals2_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is greater than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals2_ReturnsTrueWhenLeftOperandIsGreaterOrEqualsRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns true when operands are equal.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals2_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns false when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsGreaterOrEquals2_ReturnsFalseWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE + TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsGreaterOrEquals(LEFT_OPERAND, RIGHT_OPERAND, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals1_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals1_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( IsLessOrEquals1_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::Epsilon;
    const float_z RIGHT_OPERAND = SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals1_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = SFloat::Epsilon + SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when left operand is greater than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals2_ReturnsFalseWhenLeftOperandIsGreaterThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE + TOLERANCE;
    const float_z RIGHT_OPERAND = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by exactly tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals2_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByExactlyTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when operands are equal.
/// </summary>
ZTEST_CASE ( IsLessOrEquals2_ReturnsTrueWhenOperandsAreEqual_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = TOLERANCE;
    const float_z RIGHT_OPERAND = TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when left operand is lower than right one, by more than tolerance.
/// </summary>
ZTEST_CASE ( IsLessOrEquals2_ReturnsTrueWhenLeftOperandIsLowerThanRightOneByMoreThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z LEFT_OPERAND = SFloat::_0;
    const float_z RIGHT_OPERAND = TOLERANCE + TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsLessOrEquals(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals tolerance value.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsTrueWhenValueEqualsTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals negative tolerance value.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsTrueWhenValueEqualsNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsTrueWhenValueIsLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsFalseWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than negative tolerance value.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsFalseWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value exactly equals zero.
/// </summary>
ZTEST_CASE ( IsZero1_ReturnsTrueWhenValueExactlyEqualsZero_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals tolerance value.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsTrueWhenValueEqualsTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = (float_z)1e-3;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value equals negative tolerance value.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsTrueWhenValueEqualsNegativeTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = -TOLERANCE;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsTrueWhenValueIsLessThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = TOLERANCE - TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsFalseWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = TOLERANCE + TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than negative tolerance value.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsFalseWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = -TOLERANCE - TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when the value exactly equals zero.
/// </summary>
ZTEST_CASE ( IsZero2_ReturnsTrueWhenValueExactlyEqualsZero_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = SFloat::_0;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsFalseWhenValueEqualsTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals negative tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsFalseWhenValueEqualsNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsFalseWhenValueIsLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsTrueWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than negative tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsTrueWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value exactly equals zero.
/// </summary>
ZTEST_CASE ( IsNotZero1_ReturnsFalseWhenValueExactlyEqualsZero_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsFalseWhenValueEqualsTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals negative tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsFalseWhenValueEqualsNegativeTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = -TOLERANCE;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsFalseWhenValueIsLessThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = TOLERANCE - TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsTrueWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = TOLERANCE + TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than negative tolerance value.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsTrueWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = -TOLERANCE - TOLERANCE * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value exactly equals zero.
/// </summary>
ZTEST_CASE ( IsNotZero2_ReturnsFalseWhenValueExactlyEqualsZero_Test )
{
    // [Preparation]
    const float_z TOLERANCE = (float_z)1e-3;
    const float_z VALUE = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNotZero(VALUE, TOLERANCE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded off to zero when it equals zero point five.
/// </summary>
ZTEST_CASE ( ToInteger_WhenValueEqualsZeroPointFiveItsRoundedOffToZero_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
#endif

    const float_z NUMBER = SFloat::_0_5;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)0;

	// [Execution]
    IntegerTypeForTest nResultUT = SFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks that a common integer value is correctly converted.
/// </summary>
ZTEST_CASE ( ToInteger_CommonIntegerIsCorrectlyConverted_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
#endif

    const float_z NUMBER = (float_z)102844.592;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)102845;

	// [Execution]
    IntegerTypeForTest nResultUT = SFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded off to one when it is greater than zero point five.
/// </summary>
ZTEST_CASE ( ToInteger_WhenValueIsGreaterThanZeroPointFiveItsRoundedOffToOne_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
#endif

    const float_z NUMBER = SFloat::_0_5 + SFloat::_0_25;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)1;

	// [Execution]
    IntegerTypeForTest nResultUT = SFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is rounded to zero when it is lower than zero point five.
/// </summary>
ZTEST_CASE ( ToInteger_WhenValueIsLessThanZeroPointFiveItsRoundedToZero_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
#endif

    const float_z NUMBER = SFloat::_0_25;
    IntegerTypeForTest EXPECTED_RESULT = (IntegerTypeForTest)0;

	// [Execution]
    IntegerTypeForTest nResultUT = SFloat::ToInteger<IntegerTypeForTest>(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(nResultUT, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion fails when the size of the Integer type used as template parameter is different from the size of the floating point type used by default.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenTheMemorySizeOfIntegerTypeIsDifferentFromSizeOfFloatType_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i32_z IntegerTypeForTest;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i64_z IntegerTypeForTest;
#endif

    const float_z NUMBER = SFloat::_0;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SFloat::ToInteger<IntegerTypeForTest>(NUMBER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion fails when number is higher than the maximum integer representation possible for default precission.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenFloatNumberIsHigherThanTheMaximumIntegerPossible_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
    const float_z MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  8388608; // Maximum convertible integer value = 2^23
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
    const float_z MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED =  4503599627370496l; // Maximum convertible integer value = 2^52
#endif

    const float_z NUMBER = MAXIMUM_POSITIVE_CONVERTIBLE_VALUE_ALLOWED + SFloat::_1;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SFloat::ToInteger<IntegerTypeForTest>(NUMBER);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

/// <summary>
/// Checks if the assertion fails when number is lower than the minimum integer representation possible for default precission.
/// </summary>
ZTEST_CASE ( ToInteger_AssertionFailsWhenFloatNumberIsLowerThanTheMinimumIntegerPossible_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef i32_z IntegerTypeForTest;
    const float_z MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -4194304; // Maximum convertible integer negative value = 2^22
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef i64_z IntegerTypeForTest;
    const float_z MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED = -2251799813685248l; // Maximum convertible integer negative value = 2^51
#endif

    const float_z NUMBER = MAXIMUM_NEGATIVE_CONVERTIBLE_VALUE_ALLOWED - SFloat::_1;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        SFloat::ToInteger<IntegerTypeForTest>(NUMBER);
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
/// Checks if that values are not rounded off.
/// </summary>
ZTEST_CASE ( Truncate_ValueIsNotRoundedOff_Test )
{
    // [Preparation]
    const float_z NUMBER = (float_z)1.9999999;
    const float_z EXPECTED_RESULT = SFloat::_1;

	// [Execution]
    float_z fResultUT = SFloat::Truncate(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the fractional part of the number dissapears.
/// </summary>
ZTEST_CASE ( Truncate_FractionalPartDissapears_Test )
{
    // [Preparation]
    const float_z NUMBER = (float_z)12345.6789;
    const float_z EXPECTED_RESULT = (float_z)12345;

	// [Execution]
    float_z fResultUT = SFloat::Truncate(NUMBER);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if a value that is greater than maximum bound is set to that bound.
/// </summary>
ZTEST_CASE ( Clamp_ReturnsMaxWhenValueIsHigherThanMax_Test )
{
    // [Preparation]
    const float_z NUMBER = SFloat::_5;
    const float_z MAX_BOUND = SFloat::_2;
    const float_z MIN_BOUND = SFloat::_1;
    const float_z EXPECTED_RESULT = MAX_BOUND;

	// [Execution]
    float_z fResultUT = SFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if a value that is lower than minimum bound is set to that bound.
/// </summary>
ZTEST_CASE ( Clamp_ReturnsMinWhenValueIsLowerThanMin_Test )
{
    // [Preparation]
    const float_z NUMBER = -SFloat::_5;
    const float_z MAX_BOUND = SFloat::_2;
    const float_z MIN_BOUND = SFloat::_1;
    const float_z EXPECTED_RESULT = MIN_BOUND;

	// [Execution]
    float_z fResultUT = SFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the value is enclosed in the range Max..Min, then it's returned as is.
/// </summary>
ZTEST_CASE ( Clamp_WhenValueIsEnclosedBetweenMaxAndMinItsReturnedAsIs_Test )
{
    // [Preparation]
    const float_z NUMBER = (float_z)1.5;
    const float_z MAX_BOUND = SFloat::_2;
    const float_z MIN_BOUND = SFloat::_1;
    const float_z EXPECTED_RESULT = NUMBER;

	// [Execution]
    float_z fResultUT = SFloat::Clamp(NUMBER, MIN_BOUND, MAX_BOUND);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if bytes that compound the floating point value are correctly reordered.
/// </summary>
ZTEST_CASE ( SwapEndianess_BytesAreCorrectlyReordered_Test )
{
    // [Preparation]
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    const float_z VALUE = 123456789.1234f;            // a3 79 eb 4c
    const float_z EXPECTED_RESULT = -1.3548143e-017f; // 4c eb 79 a3
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    const float_z VALUE = 123456789.1234;            // 41 9d 6f 34 54 7e 5c 92
    const float_z EXPECTED_RESULT = -3.1530333220209750e-220	; // 92 5c 7e 54 34 6f 9d 41
#endif

	// [Execution]
    float_z fResultUT = SFloat::SwapEndianess(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals negative tolerance value.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsFalseWhenValueEqualsNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNegative(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsTrueWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsNegative(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsNegative_ReturnsFalseWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsNegative(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when the value equals tolerance value.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsFalseWhenValueEqualsTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsPositive(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value is lower than tolerance value.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsFalseWhenValueIsLessThanNegativeTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsPositive(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns True when value is greater than tolerance value.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsTrueWhenValueIsGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResultUT = SFloat::IsPositive(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns False when value equals zero.
/// </summary>
ZTEST_CASE ( IsPositive_ReturnsFalseWhenValueEqualsZero_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::_0;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResultUT = SFloat::IsPositive(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is copied when the source value is positive and the target one is negative.
/// </summary>
ZTEST_CASE ( CopySign_SignIsCopiedWhenSourceIsPositiveAndTargetIsNegative_Test )
{
    // [Preparation]
    const float_z SOURCE = SFloat::_1;
    float_z fTargetUT = -SFloat::_1;

    const float_z EXPECTED_RESULT = SFloat::_1;

	// [Execution]
    SFloat::CopySign(SOURCE, fTargetUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is copied when the source value is positive and the target one is negative.
/// </summary>
ZTEST_CASE ( CopySign_SignIsCopiedWhenSourceIsNegativeAndTargetIsPositive_Test )
{
    // [Preparation]
    const float_z SOURCE = -SFloat::_1;
    float_z fTargetUT = SFloat::_1;

    const float_z EXPECTED_RESULT = -SFloat::_1;

	// [Execution]
    SFloat::CopySign(SOURCE, fTargetUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is the same when the source value is positive and the target one is positive.
/// </summary>
ZTEST_CASE ( CopySign_SignIsTheSameWhenSourceIsPositiveAndTargetIsPositive_Test )
{
    // [Preparation]
    const float_z SOURCE = SFloat::_1;
    float_z fTargetUT = SFloat::_1;

    const float_z EXPECTED_RESULT = SFloat::_1;

	// [Execution]
    SFloat::CopySign(SOURCE, fTargetUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the sign is the same when the source value is negative and the target one is negative.
/// </summary>
ZTEST_CASE ( CopySign_SignIsTheSameWhenSourceIsNegativeAndTargetIsNegative_Test )
{
    // [Preparation]
    const float_z SOURCE = -SFloat::_1;
    float_z fTargetUT = -SFloat::_1;

    const float_z EXPECTED_RESULT = -SFloat::_1;

	// [Execution]
    SFloat::CopySign(SOURCE, fTargetUT);

    // [Verification]
    BOOST_CHECK_EQUAL(fTargetUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns a positive value when original value was already positive.
/// </summary>
ZTEST_CASE ( Abs_ReturnsPositiveWhenValueIsAlreadyPositive_Test )
{
    // [Preparation]
    const float_z VALUE = SFloat::_1;
    const float_z EXPECTED_RESULT = SFloat::_1;

	// [Execution]
    float_z fResultUT = SFloat::Abs(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

/// <summary>
/// Checks if it returns a positive value when original value was negative.
/// </summary>
ZTEST_CASE ( Abs_ReturnsPositiveWhenValueIsNegative_Test )
{
    // [Preparation]
    const float_z VALUE = -SFloat::_1;
    const float_z EXPECTED_RESULT = SFloat::_1;

	// [Execution]
    float_z fResultUT = SFloat::Abs(VALUE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_RESULT);
}

// End - Test Suite: SFloat
ZTEST_SUITE_END()
