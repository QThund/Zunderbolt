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

#include "ZCommon/DataTypes/SInteger.h"

typedef boost::mpl::list<i8_z, i16_z, i32_z, i64_z, u8_z, u16_z, u32_z, u64_z> TTemplateTypes;
typedef boost::mpl::list<i8_z, i16_z, i32_z, i64_z> TZTemplateSignedTypes;
typedef boost::mpl::list<u8_z, u16_z, u32_z, u64_z> TZTemplateUnsignedTypes;

ZTEST_SUITE_BEGIN( SInteger_TestSuite )

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
ZTEST_CASE ( Abs1_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i8_z INPUT = -50;
    const i8_z EXPECTED_RESULT = 50;

	// [Execution]
    i8_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
ZTEST_CASE ( Abs1_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i8_z INPUT = SInteger::MaxPositiveI8_Z;
    const i8_z EXPECTED_RESULT = SInteger::MaxPositiveI8_Z;

	// [Execution]
    i8_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
ZTEST_CASE ( Abs1_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i8_z INPUT = 0;
    const i8_z EXPECTED_RESULT = 0;

	// [Execution]
    i8_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
ZTEST_CASE ( Abs1_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i8_z INPUT = SInteger::MaxNegativeI8_Z;
    const i8_z EXPECTED_RESULT = INPUT;

	// [Execution]
    i8_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
ZTEST_CASE ( Abs2_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i16_z INPUT = -50;
    const i16_z EXPECTED_RESULT = 50;

	// [Execution]
    i16_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
ZTEST_CASE ( Abs2_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i16_z INPUT = SInteger::MaxPositiveI16_Z;
    const i16_z EXPECTED_RESULT = SInteger::MaxPositiveI16_Z;

	// [Execution]
    i16_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
ZTEST_CASE ( Abs2_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i16_z INPUT = 0;
    const i16_z EXPECTED_RESULT = 0;

	// [Execution]
    i16_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
ZTEST_CASE ( Abs2_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i16_z INPUT = SInteger::MaxNegativeI16_Z;
    const i16_z EXPECTED_RESULT = INPUT;

	// [Execution]
    i16_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
ZTEST_CASE ( Abs3_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i32_z INPUT = -50;
    const i32_z EXPECTED_RESULT = 50;

	// [Execution]
    i32_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
ZTEST_CASE ( Abs3_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i32_z INPUT = SInteger::MaxPositiveI32_Z;
    const i32_z EXPECTED_RESULT = SInteger::MaxPositiveI32_Z;

	// [Execution]
    i32_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
ZTEST_CASE ( Abs3_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i32_z INPUT = 0;
    const i32_z EXPECTED_RESULT = 0;

	// [Execution]
    i32_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
ZTEST_CASE ( Abs3_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i32_z INPUT = SInteger::MaxNegativeI32_Z;
    const i32_z EXPECTED_RESULT = INPUT;

	// [Execution]
    i32_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a negative input value.
/// </summary>
ZTEST_CASE ( Abs4_AbsoluteValueIsReturnedWhenUsingNegativeValue_Test )
{
    // [Preparation]
    const i64_z INPUT = -50;
    const i64_z EXPECTED_RESULT = 50;

	// [Execution]
    i64_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns the expected absolute value when using a positive input value.
/// </summary>
ZTEST_CASE ( Abs4_AbsoluteValueIsReturnedWhenUsingPositiveValue_Test )
{
    // [Preparation]
    const i64_z INPUT = SInteger::MaxPositiveI64_Z;
    const i64_z EXPECTED_RESULT = SInteger::MaxPositiveI64_Z;

	// [Execution]
    i64_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns zero when using zero as input value.
/// </summary>
ZTEST_CASE ( Abs4_ZeroIsReturnedWhenUsingZeroAsInput_Test )
{
    // [Preparation]
    const i64_z INPUT = 0;
    const i64_z EXPECTED_RESULT = 0;

	// [Execution]
    i64_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that the returned value equals the input value when it's the maximum possible negative value.
/// </summary>
ZTEST_CASE ( Abs4_ReturnedValueEqualsInputValueWhenUsingMaximumNegativeValue_Test )
{
    // [Preparation]
    const i64_z INPUT = SInteger::MaxNegativeI64_Z;
    const i64_z EXPECTED_RESULT = INPUT;

	// [Execution]
    i64_z nResult = SInteger::Abs(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the bytes of the input value are correctly swapped when using a common value.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwapEndianess_IsCorrectlySwappedWhenUsingCommonValue_Test, TTemplateTypes )
{
    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    T EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = (T)0xAB;
        EXPECTED_RESULT = INPUT;
        break;
    case SIZE_16:
        INPUT = (T)0xAABB;
        EXPECTED_RESULT = (T)0xBBAA;
        break;
    case SIZE_32:
        INPUT = (T)0xAABBCCDD;
        EXPECTED_RESULT =(T) 0xDDCCBBAA;
        break;
    case SIZE_64:
        INPUT = (T)0xAABBCCDDEEFF0011;
        EXPECTED_RESULT = (T)0x1100FFEEDDCCBBAA;
        break;
    default: // This will cause that the test fails
        INPUT = (T)0;
        EXPECTED_RESULT = (T)1;
    }

	// [Execution]
    T nResult = SInteger::SwapEndianess(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks if the bytes of the input value are correctly swapped when using a common value.
/// </summary>
ZTEST_CASE_TEMPLATE ( SwapEndianess_IsCorrectlySwappedWhenUsingZeroAsInput_Test, TTemplateTypes )
{
    // [Preparation]
    const size_t SIZE_8 = 1;
    const size_t SIZE_16 = 2;
    const size_t SIZE_32 = 4;
    const size_t SIZE_64 = 8;

    const size_t T_SIZE = sizeof(T);

    T INPUT;
    T EXPECTED_RESULT;

    switch(T_SIZE)
    {
    case SIZE_8:
        INPUT = (T)0;
        EXPECTED_RESULT = INPUT;
        break;
    case SIZE_16:
        INPUT = (T)0;
        EXPECTED_RESULT = (T)0;
        break;
    case SIZE_32:
        INPUT = (T)0;
        EXPECTED_RESULT =(T) 0;
        break;
    case SIZE_64:
        INPUT = (T)0;
        EXPECTED_RESULT = (T)0;
        break;
    default: // This will cause that the test fails
        INPUT = 0;
        EXPECTED_RESULT = -1;
    }

	// [Execution]
    T nResult = SInteger::SwapEndianess(INPUT);

    // [Verification]
    BOOST_CHECK_EQUAL(nResult, EXPECTED_RESULT);
}

// End - Test Suite: SInteger
ZTEST_SUITE_END()
