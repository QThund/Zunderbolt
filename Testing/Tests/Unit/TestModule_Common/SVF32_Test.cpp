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

#include "ZCommon/DataTypes/SVF32.h"

ZTEST_SUITE_BEGIN( SVF32_TestSuite )

/// <summary>
/// Checks if every floating point value is set in the correct place into the vector.
/// </summary>
ZTEST_CASE ( Pack_EveryValueIsSetInTheRightPlace_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_FLOAT1 = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_FLOAT2 = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_FLOAT3 = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_FLOAT4 = SFloat::_4;

	// [Execution]
    vf32_z vectorUT;
    SVF32::Pack(EXPECTED_VALUE_FOR_FLOAT1,
                 EXPECTED_VALUE_FOR_FLOAT2,
                 EXPECTED_VALUE_FOR_FLOAT3,
                 EXPECTED_VALUE_FOR_FLOAT4,
                 vectorUT);

    // [Verification]
    float_z fFloatValueInPosition1;
    float_z fFloatValueInPosition2;
    float_z fFloatValueInPosition3;
    float_z fFloatValueInPosition4;
    SVF32::Unpack(vectorUT,
                   fFloatValueInPosition1,
                   fFloatValueInPosition2,
                   fFloatValueInPosition3,
                   fFloatValueInPosition4);

    BOOST_CHECK_EQUAL(fFloatValueInPosition1, EXPECTED_VALUE_FOR_FLOAT1);
    BOOST_CHECK_EQUAL(fFloatValueInPosition2, EXPECTED_VALUE_FOR_FLOAT2);
    BOOST_CHECK_EQUAL(fFloatValueInPosition3, EXPECTED_VALUE_FOR_FLOAT3);
    BOOST_CHECK_EQUAL(fFloatValueInPosition4, EXPECTED_VALUE_FOR_FLOAT4);
}

/// <summary>
/// Not tested. It's the same as Pack so it's not repeated.
/// </summary>
ZTEST_CASE ( Unpack_NotTested_Test )
{
    BOOST_TEST_MESSAGE(Z_L("It's not a testable method: no inputs, no outputs, just executes a method of a component."));
}

// End - Test Suite: SVF32
ZTEST_SUITE_END()
