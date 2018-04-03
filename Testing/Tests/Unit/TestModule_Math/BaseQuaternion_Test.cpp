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

#include "ZMath/BaseQuaternion.h"

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/Exceptions/AssertException.h"

ZTEST_SUITE_BEGIN( BaseQuaternion_TestSuite )

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_0;
    
    // [Execution]
    BaseQuaternion qQuaternionUT;
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if copy constructor sets quaternion components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;
    
    const BaseQuaternion QUAT_TO_COPY(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W);
    
    // [Execution]
    BaseQuaternion qQuatUT = QUAT_TO_COPY;
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuatUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuatUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuatUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuatUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks that every value is set to correct component.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_X = SFloat::_1;
    const float_z EXPECTED_VALUE_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_W = SFloat::_4;
    
    // [Execution]
    BaseQuaternion qQuaternionUT(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_W);
}

/// <summary>
/// Checks that every element of the array is put in the correct component.
/// </summary>
ZTEST_CASE ( Constructor4_QuaternionComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;
    
    float_z* VALID_ARRAY_OF_4_FLOATS = new float_z[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_X;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_Y;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_Z;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_W;
    
    // [Execution]
    BaseQuaternion qQuaternionUT(VALID_ARRAY_OF_4_FLOATS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, VALID_ARRAY_OF_4_FLOATS[0]);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, VALID_ARRAY_OF_4_FLOATS[1]);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, VALID_ARRAY_OF_4_FLOATS[2]);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, VALID_ARRAY_OF_4_FLOATS[3]);
    
    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor4_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    const float_z* NULL_ARRAY = null_z;
    
    // [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        BaseQuaternion qQuaternionUT(NULL_ARRAY);
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
/// Checks if quaternion components are set to the correct values packed in a valid vf32 object.
/// </summary>
ZTEST_CASE ( Constructor5_QuaternionComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_X = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_Y = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_Z = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_W = SFloat::_4;
    
    vf32_z PACK;
    SVF32::Pack(EXPECTED_VALUE_FOR_X, EXPECTED_VALUE_FOR_Y, EXPECTED_VALUE_FOR_Z, EXPECTED_VALUE_FOR_W, PACK);
    
    // [Execution]
    BaseQuaternion qQuaternionUT(PACK);
    
    // [Verification]
    BOOST_CHECK_EQUAL(qQuaternionUT.x, EXPECTED_VALUE_FOR_X);
    BOOST_CHECK_EQUAL(qQuaternionUT.y, EXPECTED_VALUE_FOR_Y);
    BOOST_CHECK_EQUAL(qQuaternionUT.z, EXPECTED_VALUE_FOR_Z);
    BOOST_CHECK_EQUAL(qQuaternionUT.w, EXPECTED_VALUE_FOR_W);
}

/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseQuaternion LEFT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0,SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const BaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const BaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseQuaternion LEFT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    const BaseQuaternion RIGHT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    
    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const BaseQuaternion LEFT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5;
    const BaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const float_z VALUE_FOR_LEFT_OPERAND_COMPONENTS = SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5;
    const BaseQuaternion LEFT_OPERAND(VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS, VALUE_FOR_LEFT_OPERAND_COMPONENTS);
    const BaseQuaternion RIGHT_OPERAND(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    
    // [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const BaseQuaternion LEFT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    const BaseQuaternion RIGHT_OPERAND(SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon, SFloat::Epsilon);
    
    // [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

// End - Test Suite: BaseQuaternion
ZTEST_SUITE_END()
