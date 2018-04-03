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

#include "ZCommon/DataTypes/ArrayBasic.h"

ZTEST_SUITE_BEGIN( ArrayBasic_TestSuite )

/// <summary>
/// Checks that input values are correctly stored.
/// </summary>
ZTEST_CASE ( Constructor1_CommonValuesAreCorrectlyStored_Test )
{
    // [Preparation]
    const puint_z COUNT = 4U;
    const int* ARRAY = new int[COUNT];

    // [Execution]
    ArrayBasic<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// Checks that input values are correctly stored when they are null and zero.
/// </summary>
ZTEST_CASE ( Constructor1_InputValuesAreCorrectlyStoredWhenTheyAreNullAndZero_Test )
{
    // [Preparation]
    const puint_z COUNT = 0;
    const int* ARRAY = null_z;

    // [Execution]
    ArrayBasic<const int> array(ARRAY, COUNT);

    // [Verification]
    BOOST_CHECK_EQUAL(array.Get(), ARRAY);
    BOOST_CHECK_EQUAL(array.GetCount(), COUNT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( OperatorArraySubscript_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( Get_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetCount_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the correct number of bytes.
/// </summary>
ZTEST_CASE ( GetSize_ReturnsCorrectNumberOfBytes_Test )
{
    // [Preparation]
    const puint_z COUNT = 4U;
    const int* ARRAY = new int[COUNT];
    const ArrayBasic<const int> INSTANCE(ARRAY, COUNT);
    const puint_z EXPECTED_SIZE = 16U;

    // [Execution]
    puint_z uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

/// <summary>
/// Checks that it returns zero when the number of elements stored in the wrapper is zero.
/// </summary>
ZTEST_CASE ( GetSize_ReturnsZeroWhenWrapperContainsZeroArrayElements_Test )
{
    // [Preparation]
    const puint_z COUNT = 0;
    const int* ARRAY = null_z;
    const ArrayBasic<const int> INSTANCE(ARRAY, COUNT);
    const puint_z EXPECTED_SIZE = 0;

    // [Execution]
    puint_z uSize = INSTANCE.GetSize();

    // [Verification]
    BOOST_CHECK_EQUAL(uSize, EXPECTED_SIZE);
}

// End - Test Suite: ArrayBasic
ZTEST_SUITE_END()
