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

#include "ZMath/DualQuaternion.h"

#include "ZMath/BaseVector3.h"
#include "ZMath/BaseVector4.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( DualQuaternion_TestSuite )

/// <summary>
/// Checks if all the components of the quaternion are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByQuaternion_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RZ = (float_z)1.5;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_DX = (float_z)2.5;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_DZ = (float_z)3.5;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_4;

    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const float_z SCALAR = SFloat::_0_5;

    // [Execution]
    DualQuaternion dualQuaternionUT = SCALAR * DUALQUATERNION;

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that default values hasn't changed.
/// </summary>
ZTEST_CASE ( Constructor1_DefaultValuesHaveNotChanged_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT;

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks if copy constructor sets dual quaternion components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const BaseQuaternion EXPECTED_VALUE_D = BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const BaseQuaternion EXPECTED_VALUE_R = BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

    const DualQuaternion DQUAT_TO_COPY(EXPECTED_VALUE_R, EXPECTED_VALUE_D);

	// [Execution]
    DualQuaternion dualQuaternionUT = DQUAT_TO_COPY;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_VALUE_D);
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_VALUE_R);
}

/// <summary>
/// Checks that the components of the dual quaternion are correctly copied to other dual quaternion.
/// </summary>
ZTEST_CASE ( Constructor3_IsCorrectlyCopied_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_8;

	// [Execution]
    DualQuaternion dualQuaternionUT(BaseDualQuaternion(BaseQuaternion(EXPECTED_VALUE_FOR_RX, EXPECTED_VALUE_FOR_RY, EXPECTED_VALUE_FOR_RZ, EXPECTED_VALUE_FOR_RW),
                                                         BaseQuaternion(EXPECTED_VALUE_FOR_DX, EXPECTED_VALUE_FOR_DY, EXPECTED_VALUE_FOR_DZ, EXPECTED_VALUE_FOR_DW)));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
ZTEST_CASE ( Constructor4_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_DY = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_DZ = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_DW = (float_z)-19.0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
ZTEST_CASE ( Constructor4_DualPartIsNullWhenTranslationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector3(SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
ZTEST_CASE ( Constructor4_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                                       BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
ZTEST_CASE ( Constructor5_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_DY = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_DZ = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_DW = (float_z)-19.0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
ZTEST_CASE ( Constructor5_DualPartIsNullWhenTranslationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
ZTEST_CASE ( Constructor5_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0),
                                                       BaseVector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
ZTEST_CASE ( Constructor6_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_DZ = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_DW = (float_z)-19.0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7),
                                                       BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual part is a null quaternion when the translation is a null vector.
/// </summary>
ZTEST_CASE ( Constructor6_DualPartIsNullWhenTranslationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector3(SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
ZTEST_CASE ( Constructor6_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseVector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                                       BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual quaternion is correctly created when using common transformations.
/// </summary>
ZTEST_CASE ( Constructor7_IsCorrectlyCreatedWhenUsingCommonTransformations_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = (float_z)12.0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_8;
    const float_z EXPECTED_VALUE_FOR_DZ = (float_z)16.0;
    const float_z EXPECTED_VALUE_FOR_DW = (float_z)-19.0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseVector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8),
                                                       BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the real part is a null quaternion when the translation is a null vector.
/// </summary>
ZTEST_CASE ( Constructor7_DualPartIsNullWhenTranslationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_4;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseVector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that the dual and real parts are null quaternions when the rotation is a null quaternion.
/// </summary>
ZTEST_CASE ( Constructor7_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(BaseVector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                       BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0));

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);
}

/// <summary>
/// Checks that all the values are correctly set.
/// </summary>
ZTEST_CASE ( Constructor8_DualAndRealPartsAreNullWhenRotationIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_DX = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_DY = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_DZ = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_DW = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_RX = SFloat::_5;
    const float_z EXPECTED_VALUE_FOR_RY = SFloat::_6;
    const float_z EXPECTED_VALUE_FOR_RZ = SFloat::_7;
    const float_z EXPECTED_VALUE_FOR_RW = SFloat::_8;

    float_z* arDualPartComponents = new float_z[4];
    arDualPartComponents[0] = EXPECTED_VALUE_FOR_DX;
    arDualPartComponents[1] = EXPECTED_VALUE_FOR_DY;
    arDualPartComponents[2] = EXPECTED_VALUE_FOR_DZ;
    arDualPartComponents[3] = EXPECTED_VALUE_FOR_DW;

    float_z* arRealPartComponents = new float_z[4];
    arRealPartComponents[0] = EXPECTED_VALUE_FOR_RX;
    arRealPartComponents[1] = EXPECTED_VALUE_FOR_RY;
    arRealPartComponents[2] = EXPECTED_VALUE_FOR_RZ;
    arRealPartComponents[3] = EXPECTED_VALUE_FOR_RW;

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion(arRealPartComponents, arDualPartComponents);

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_DX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_DY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_DZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_DW);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_RX);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_RY);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_RZ);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_RW);

    // Cleaning
    delete[] arDualPartComponents;
    delete[] arRealPartComponents;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when the input pointers are null.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenPointersAreNull_Test )
{
    // [Preparation]
    float_z* arDualPartComponents = new float_z[4];
    float_z* arRealPartComponents = new float_z[4];

    const float_z* NULL_POINTER = null_z;

    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bAssertionFailedBecauseRealPartIsNull = false;
    bool bAssertionFailedBecauseDualPartIsNull = false;

    try
    {
        DualQuaternion(arRealPartComponents, NULL_POINTER);
    }
    catch(const AssertException&)
    {
        bAssertionFailedBecauseRealPartIsNull = true;
    }

    try
    {
        DualQuaternion(NULL_POINTER, arDualPartComponents);
    }
    catch(const AssertException&)
    {
        bAssertionFailedBecauseDualPartIsNull = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailedBecauseRealPartIsNull, EXPECTED_VALUE);
    BOOST_CHECK_EQUAL(bAssertionFailedBecauseDualPartIsNull, EXPECTED_VALUE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the real part equals identity and dual one is null.
/// </summary>
ZTEST_CASE ( GetIdentity_DualPartIsNullAndRealPartEqualsIdentity_Test )
{
    // [Preparation]
    const Quaternion EXPECTED_REAL_PART = Quaternion::GetIdentity();
    const Quaternion EXPECTED_DUAL_PART = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    DualQuaternion dualQuaternionUT = DualQuaternion::GetIdentity();

    // [Verification]
    BOOST_CHECK(dualQuaternionUT.r == EXPECTED_REAL_PART);
    BOOST_CHECK(dualQuaternionUT.d == EXPECTED_DUAL_PART);
}

/// <summary>
/// Checks if two different dual quaternions are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAddition_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)7.25, SFloat::_9, (float_z)11.0, (float_z)13.0),
                                                           Quaternion((float_z)14.0, (float_z)16.0, (float_z)18.0, (float_z)20.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1 + OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtraction_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion((float_z)7.25, SFloat::_9, (float_z)11.0, (float_z)13.0),
                                                     Quaternion((float_z)14.0, (float_z)16.0, (float_z)18.0, (float_z)20.0));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1 - OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProduct1_TwoDifferentQuaternionsAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)30.5, (float_z)22.25, (float_z)52.0, (float_z)2.25),
                                                           Quaternion((float_z)123.5, (float_z)111.25, (float_z)183.0, (float_z)-36.75));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1 * OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the product is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProduct1_IsNotCommutative_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

	// [Execution]
    DualQuaternion dualQuaternion1UT = OPERAND1 * OPERAND2;
    DualQuaternion dualQuaternion2UT = OPERAND2 * OPERAND1;

    // [Verification]
    BOOST_CHECK(dualQuaternion1UT != dualQuaternion2UT);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct2_ScalarAndDualQuaternionAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const float_z SCALAR = SFloat::_7;

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION * SCALAR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a vector.
/// </summary>
ZTEST_CASE ( OperatorProduct3_ResultIsCorrectWhenUsingCommonVector_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const BaseVector3 VECTOR(SFloat::_9, SFloat::_10, (float_z)11.0);

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion((float_z)49.0, (float_z)30.0, (float_z)59.0, (float_z)-54.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a vector.
/// </summary>
ZTEST_CASE ( OperatorProduct4_ResultIsCorrectWhenUsingCommonVector_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const BaseVector4 VECTOR(SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0);

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion((float_z)49.0, (float_z)30.0, (float_z)59.0, (float_z)-54.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION * VECTOR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly divided by a scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision_DualQuaternionIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));
    const float_z SCALAR = SFloat::_7;

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION / SCALAR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input scalar equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivision_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));
    const float_z SCALAR = SFloat::_0;

    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DUALQUATERNION / SCALAR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if two different dual quaternions are correctly added.
/// </summary>
ZTEST_CASE ( OperatorAdditionAssignation_TwoDifferentQuaternionsAreCorrectlyAdded_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)7.25, SFloat::_9, (float_z)11.0, (float_z)13.0),
                                                           Quaternion((float_z)14.0, (float_z)16.0, (float_z)18.0, (float_z)20.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT += OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly subtracted.
/// </summary>
ZTEST_CASE ( OperatorSubtractionAssignation_TwoDifferentQuaternionsAreCorrectlySubtracted_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion((float_z)7.25, SFloat::_9, (float_z)11.0, (float_z)13.0),
                                                     Quaternion((float_z)14.0, (float_z)16.0, (float_z)18.0, (float_z)20.0));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT -= OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks if two different dual quaternions are correctly multiplied.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_TwoDifferentQuaternionsAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)30.5, (float_z)22.25, (float_z)52.0, (float_z)2.25),
                                                           Quaternion((float_z)123.5, (float_z)111.25, (float_z)183.0, (float_z)-36.75));

	// [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1;
    dualQuaternionUT *= OPERAND2;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the product is not commutative.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation1_IsNotCommutative_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                     Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_10),
                                                     Quaternion((float_z)11.0, (float_z)12.0, (float_z)13.0, (float_z)14.0));

	// [Execution]
    DualQuaternion dualQuaternion1UT = OPERAND1;
    dualQuaternion1UT *= OPERAND2;
    DualQuaternion dualQuaternion2UT = OPERAND2;
    dualQuaternion2UT *= OPERAND1;

    // [Verification]
    BOOST_CHECK(dualQuaternion1UT != dualQuaternion2UT);
}

/// <summary>
/// Checks that a dual quaternion is correctly multiplied by a scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation2_ScalarAndDualQuaternionAreCorrectlyMultiplied_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));
    const float_z SCALAR = SFloat::_7;

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT *= SCALAR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that a dual quaternion is correctly divided by a scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_DualQuaternionIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));
    const float_z SCALAR = SFloat::_7;

    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT /= SCALAR;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input scalar equals zero.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_AssertionFailsWhenScalarEqualsZero_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion((float_z)1.75, (float_z)7.0, (float_z)14.0, (float_z)21.0),
                                                           Quaternion((float_z)21.0, (float_z)28.0, (float_z)35.0, (float_z)42.0));
    const float_z SCALAR = SFloat::_0;

    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        DUALQUATERNION / SCALAR;
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, EXPECTED_VALUE);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a dual quaternion is correctly assigned to another dual quaternion.
/// </summary>
ZTEST_CASE ( OperatorAssignation_DualQuaternionIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const DualQuaternion EXPECTED_VALUE = DualQuaternion(Quaternion(SFloat::_0_25, SFloat::_1, SFloat::_2, SFloat::_3),
                                                           Quaternion(SFloat::_3, SFloat::_4, SFloat::_5, SFloat::_6));

	// [Execution]
    DualQuaternion dualQuaternionUT;
    dualQuaternionUT = EXPECTED_VALUE;

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == EXPECTED_VALUE);
}

/// <summary>
/// Checks that all dual quaternion components are set to zero.
/// </summary>
ZTEST_CASE ( ResetToZero_AllDualQuaternionComponentsAreSetToZero_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_0;

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT.ResetToZero();

    // [Verification]
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.r.w, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.x, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.y, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.z, EXPECTED_VALUE_FOR_ALL);
    BOOST_CHECK_EQUAL(dualQuaternionUT.d.w, EXPECTED_VALUE_FOR_ALL);
}

/// <summary>
/// Checks that the dual quaternion is converted to an identity dual quaternion.
/// </summary>
ZTEST_CASE ( ResetToIdentity_DualQuaternionBecomesIdentity_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const DualQuaternion IDENTITY = DualQuaternion::GetIdentity();

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION;
    dualQuaternionUT.ResetToIdentity();

    // [Verification]
    BOOST_CHECK(dualQuaternionUT == IDENTITY);
}

/// <summary>
/// Checks that a common dual quaternion is correctly conjugated.
/// </summary>
ZTEST_CASE ( Conjugate_CommonDualQuaternionIsCorrectlyConjugated_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const DualQuaternion EXPECTED_RESULT = DualQuaternion(Quaternion(-SFloat::_1, -SFloat::_2, -SFloat::_3, SFloat::_4),
                                                            Quaternion(-SFloat::_5, -SFloat::_6, -SFloat::_7, SFloat::_8));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.Conjugate();

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly double conjugated.
/// </summary>
ZTEST_CASE ( DoubleConjugate_CommonDualQuaternionIsCorrectlyDoubleConjugated_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const DualQuaternion EXPECTED_RESULT = DualQuaternion(Quaternion(-SFloat::_1, -SFloat::_2, -SFloat::_3, SFloat::_4),
                                                            Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, -SFloat::_8));

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.DoubleConjugate();

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the non dual length of a common dual quaternion is what expected.
/// </summary>
ZTEST_CASE ( GetNonDualLength_CorrectNonDualLengthObtainedFromCommonDualQuaternion_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const float_z EXPECTED_LENGTH = (float_z)5.4772255750516612;

	// [Execution]
    float_z fLengthUT = DUALQUATERNION.GetNonDualLength();

    // [Verification]
    BOOST_CHECK_EQUAL(fLengthUT, EXPECTED_LENGTH);
}

/// <summary>
/// Checks that a common dual quaternion is correctly transformed by another common dual quaternion.
/// </summary>
ZTEST_CASE ( Transform_CommonDualQuaternionIsCorrectlyTransformedByAnother_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                     Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_9, SFloat::_10, (float_z)11.0, (float_z)12.0),
                                                     Quaternion((float_z)13.0, (float_z)14.0, (float_z)15.0, (float_z)16.0));
    const DualQuaternion EXPECTED_RESULT = DualQuaternion(Quaternion((float_z)766.0, (float_z)1308.0, (float_z)698.0, (float_z)1784.0),
                                                            Quaternion((float_z)2518.0, (float_z)2884.0, (float_z)2866.0, (float_z)3488.0));

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Transform(OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by identity dual quaternion.
/// </summary>
ZTEST_CASE ( Transform_ResultEqualsOriginalDualQuaternionWhenTransformingByIdentity_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                    Quaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));
    const DualQuaternion IDENTITY = DualQuaternion::GetIdentity();

    const DualQuaternion EXPECTED_RESULT = OPERAND;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND.Transform(IDENTITY);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly rotated and translated.
/// </summary>
ZTEST_CASE ( TransformRotationFirst1_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const BaseVector3 TRANSLATION = BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7);

    const DualQuaternion EXPECTED_RESULT = DualQuaternion(BaseQuaternion((float_z)30.0, (float_z)60.0, (float_z)90.0, (float_z)120.0),
                                                            BaseQuaternion((float_z)718.0, (float_z)820.0, (float_z)1114.0, (float_z)-900.0));

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
ZTEST_CASE ( TransformRotationFirst1_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const BaseVector3 TRANSLATION = BaseVector3(SFloat::_0, SFloat::_0, SFloat::_0);

    const DualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly rotated and translated.
/// </summary>
ZTEST_CASE ( TransformRotationFirst2_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const BaseVector4 TRANSLATION = BaseVector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

    const DualQuaternion EXPECTED_RESULT = DualQuaternion(BaseQuaternion((float_z)30.0, (float_z)60.0, (float_z)90.0, (float_z)120.0),
                                                            BaseQuaternion((float_z)718.0, (float_z)820.0, (float_z)1114.0, (float_z)-900.0));

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
ZTEST_CASE ( TransformRotationFirst2_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const BaseVector4 TRANSLATION = BaseVector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const DualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformRotationFirst(ROTATION, TRANSLATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly translated and rotated.
/// </summary>
ZTEST_CASE ( TransformTranslationFirst1_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const BaseVector3 TRANSLATION = BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7);

    const DualQuaternion EXPECTED_RESULT = DualQuaternion(BaseQuaternion((float_z)30.0, (float_z)60.0, (float_z)90.0, (float_z)120.0),
                                                            BaseQuaternion((float_z)590.0, (float_z)500.0, (float_z)1370.0, (float_z)-900.0));

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
ZTEST_CASE ( TransformTranslationFirst1_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const BaseVector3 TRANSLATION = BaseVector3(SFloat::_0, SFloat::_0, SFloat::_0);

    const DualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a common dual quaternion is correctly translated and rotated.
/// </summary>
ZTEST_CASE ( TransformTranslationFirst2_CommonDualQuaternionIsCorrectlyTransformed_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const BaseVector4 TRANSLATION = BaseVector4(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);

    const DualQuaternion EXPECTED_RESULT = DualQuaternion(BaseQuaternion((float_z)30.0, (float_z)60.0, (float_z)90.0, (float_z)120.0),
                                                            BaseQuaternion((float_z)590.0, (float_z)500.0, (float_z)1370.0, (float_z)-900.0));

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals original dual quaternion when it's transformed by null translation and null rotation.
/// </summary>
ZTEST_CASE ( TransformTranslationFirst2_ResultEqualsOriginalDualQuaternionWhenTransformedByNullTranslationAndRotation_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(BaseQuaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4),
                                                           BaseQuaternion(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8));

    const BaseQuaternion ROTATION = BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const BaseVector4 TRANSLATION = BaseVector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const DualQuaternion EXPECTED_RESULT = DUALQUATERNION;

    // [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION.TransformTranslationFirst(TRANSLATION, ROTATION);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that a correct "lerped" dual quaternion is obtained when two common dual quaternions are used.
/// </summary>
ZTEST_CASE ( Lerp_CorrectLerpedDualQuaternionIsObtainedForTwoCommonDualQuaternions_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(),
                                                     BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_8, SFloat::_9, SFloat::_10, (float_z)11.0).Normalize(),
                                                     BaseVector3((float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_RESULT = DualQuaternion(Quaternion((float_z)0.24356699032036269, (float_z)0.394866515026776, (float_z)0.54616603973318933, (float_z)0.69746556443960261),
                                                            Quaternion((float_z)1.9485359225629015, (float_z)3.2050658530211824, (float_z)2.6460014870025041, (float_z)-4.9507089457357143));
    const float_z PROPORTION = SFloat::_0_25;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the interpolation between two equivalent dual quaternions results in the same dual quaternion.
/// </summary>
ZTEST_CASE ( Lerp_InterpolatingTwoEquivalentDualQuaternionsGivesSameDualQuaternion_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(),
                                                     BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));
    const DualQuaternion OPERAND2 = OPERAND1;

    const DualQuaternion EXPECTED_RESULT = OPERAND1;

    const float_z PROPORTION = SFloat::_0_25;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the real part of the result equals identity when interpolating with the double conjugated.
/// </summary>
ZTEST_CASE ( Lerp_RealPartEqualsIdentityWhenInterpolatingInTheMiddleOfDualQuaternionsAndItsDoubleConjugated_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(),
                                                     BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));
    const DualQuaternion OPERAND2 = OPERAND1.DoubleConjugate();

    const Quaternion EXPECTED_REAL_PART_VALUE = Quaternion::GetIdentity();

    const float_z PROPORTION = SFloat::_0_5;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT.r == EXPECTED_REAL_PART_VALUE );
}

/// <summary>
/// Checks that the result equals left operand when proportion equals zero.
/// </summary>
ZTEST_CASE ( Lerp_ProportionZeroMeansNormalizedResidentQuaternion_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(),
                                                     BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_8, SFloat::_9, SFloat::_10, (float_z)11.0).Normalize(),
                                                     BaseVector3((float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_RESULT = OPERAND1;

    const float_z PROPORTION = SFloat::_0;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the result equals right operand when proportion equals one.
/// </summary>
ZTEST_CASE ( Lerp_ProportionOneMeansNormalizedInputQuaternion_Test )
{
    // [Preparation]
    const DualQuaternion OPERAND1 = DualQuaternion(Quaternion(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize(),
                                                   BaseVector3(SFloat::_5, SFloat::_6, SFloat::_7));
    const DualQuaternion OPERAND2 = DualQuaternion(Quaternion(SFloat::_8, SFloat::_9, SFloat::_10, (float_z)11.0).Normalize(),
                                                   BaseVector3((float_z)12.0, (float_z)13.0, (float_z)14.0));

    const DualQuaternion EXPECTED_RESULT = OPERAND2;

    const float_z PROPORTION = SFloat::_1;

    // [Execution]
    DualQuaternion dualQuaternionUT = OPERAND1.Lerp(PROPORTION, OPERAND2);

    // [Verification]
    BOOST_CHECK( dualQuaternionUT == EXPECTED_RESULT );
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const DualQuaternion DUALQUATERNION = DualQuaternion(Quaternion(SFloat::_0_25, (float_z)-0.000002, (float_z)40000.0, (float_z)1.0),
                                                         Quaternion(SFloat::_0_25, (float_z)-0.000002, (float_z)40000.0, (float_z)1.0));

    #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
        #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
            string_z EXPECTED_STRING_FORM = Z_L("DQ(r(Q(0.25,-1.99999999e-06,40000,1)),d(Q(0.25,-1.99999999e-06,40000,1)))");
        #else
            string_z EXPECTED_STRING_FORM = Z_L("DQ(r(Q(0.25,-1.99999999e-06,40000,1)),d(Q(0.25,-1.99999999e-06,40000,1)))");
        #endif
    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
        #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
            string_z EXPECTED_STRING_FORM = Z_L("DQ(r(Q(0.25,-1.9999999999999999e-06,40000,1)),d(Q(0.25,-1.9999999999999999e-06,40000,1)))");
        #else
            string_z EXPECTED_STRING_FORM = Z_L("DQ(r(Q(0.25,-1.9999999999999999e-06,40000,1)),d(Q(0.25,-1.9999999999999999e-06,40000,1)))");
        #endif
    #endif

	// [Execution]
    DualQuaternion dualQuaternionUT = DUALQUATERNION;
    string_z strStringForm = dualQuaternionUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// End - Test Suite: DualQuaternion
ZTEST_SUITE_END()
