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

#include "ZContainers/SComparatorDefault.h"


ZTEST_SUITE_BEGIN( SComparatorDefault_TestSuite )

/// <summary>
/// Checks that method compare returns right value when left operand is greater than right operand.
/// </summary>
ZTEST_CASE ( Compare_ReturnsPositiveOneWhenLeftOperandIsGreaterThanRightOperand_Test )
{
    // [Preparation]
    const i8_z EXPECTED_VALUE_OF_COMPARISON = 1;
    const i8_z LEFT_OPERAND = 10;
    const i8_z RIGHT_OPERAND = 5;

    // [Execution]
    i8_z comparisonResult = SComparatorDefault<const i8_z&>::Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );
}

/// <summary>
/// Checks that method compare returns right value when left operand is lower than right operand.
/// </summary>
ZTEST_CASE ( Compare_ReturnsNegativeOneWhenLeftOperandIsLowerThanRightOperand_Test )
{
    // [Preparation]
    const i8_z EXPECTED_VALUE_OF_COMPARISON = -1;
    const i8_z LEFT_OPERAND = 5;
    const i8_z RIGHT_OPERAND = 10;

    // [Execution]
    i8_z comparisonResult = SComparatorDefault<const i8_z&>::Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );
}

/// <summary>
/// Checks that method compare returns right value when left operand is equal to right operand.
/// </summary>
// [Preparation]
ZTEST_CASE ( Compare_ReturnsZeroWhenLeftOperandIsEqualToRightOperand_Test )
{
    const i8_z EXPECTED_VALUE_OF_COMPARISON = 0;
    const i8_z LEFT_OPERAND = 10;
    const i8_z RIGHT_OPERAND = 10;

    // [Execution]
    i8_z comparisonResult = SComparatorDefault<const i8_z&>::Compare(LEFT_OPERAND, RIGHT_OPERAND);

    // [Verification]
    BOOST_CHECK_EQUAL( comparisonResult, EXPECTED_VALUE_OF_COMPARISON );
}

// End - Test Suite: SComparatorDefault
ZTEST_SUITE_END()
