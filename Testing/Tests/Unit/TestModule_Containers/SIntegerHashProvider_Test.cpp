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

#include "ZContainers/ContainersModuleDefinitions.h"
#include "ZContainers/SIntegerHashProvider.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( SIntegerHashProvider_TestSuite )

/// <summary>
/// Checks that it returns zero when the input value is zero.
/// </summary>
ZTEST_CASE ( GenerateHashKey_ItReturnsZeroWhenInputIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_VALUE = 0;
    const puint_z NUMBER_OF_BUCKETS = 4;
    const puint_z EXPECTED_VALUE = 0;

    // [Execution]
    puint_z uHashKey = SIntegerHashProvider::GenerateHashKey(INPUT_VALUE, NUMBER_OF_BUCKETS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uHashKey, EXPECTED_VALUE);
}

/// <summary>
/// Checks that it returns the expected result when using common input values.
/// </summary>
ZTEST_CASE ( GenerateHashKey_ItReturnsExpectedValueWhenUsingCommonInputValues_Test )
{
    // [Preparation]
    const puint_z INPUT_VALUE = 10;
    const puint_z NUMBER_OF_BUCKETS = 4;
    const puint_z EXPECTED_VALUE = 2;

    // [Execution]
    puint_z uHashKey = SIntegerHashProvider::GenerateHashKey(INPUT_VALUE, NUMBER_OF_BUCKETS);
    
    // [Verification]
    BOOST_CHECK_EQUAL(uHashKey, EXPECTED_VALUE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the number of buckets is zero.
/// </summary>
ZTEST_CASE ( GenerateHashKey_AssertionFailsWhenNumberOfBucketsIsZero_Test )
{
    // [Preparation]
    const puint_z INPUT_VALUE = 0;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        SIntegerHashProvider::GenerateHashKey(INPUT_VALUE, 0);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }
    
    // [Verification]
    BOOST_CHECK(bAssertionFailed);
}

#endif

// End - Test Suite: SIntegerHashProvider
ZTEST_SUITE_END()
