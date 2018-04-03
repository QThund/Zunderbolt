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

#include "ZTime/STimeZoneFactory.h"

#include "ZTime/TimeZone.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( STimeZoneFactory_TestSuite )

/// <summary>
/// Checks that it returns the expected time zone instance when using a common valid Id.
/// </summary>
ZTEST_CASE( GetTimeZoneById_ReturnsExpectedTimeZoneWhenUsingCommonId_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid");
    const TimeZone* NULL_TIMEZONE = null_z;

	// [Execution]
    const TimeZone* pTimeZone = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);

    // [Verification]
    BOOST_CHECK_NE(pTimeZone, NULL_TIMEZONE);
    BOOST_CHECK(pTimeZone->GetId() == COMMON_TIMEZONE_ID);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when using an invalid Id.
/// </summary>
ZTEST_CASE( GetTimeZoneById_AssertionFailsWhenIdIsNotValid_Test )
{
    // [Preparation]
    const string_z INVALID_TIMEZONE_ID = Z_L("Not valid ID");
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        STimeZoneFactory::GetTimeZoneById(INVALID_TIMEZONE_ID);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns null when using an invalid Id.
/// </summary>
ZTEST_CASE( GetTimeZoneById_ReturnsNullWhenIdIsNotValid_Test )
{
    // [Preparation]
    const string_z INVALID_TIMEZONE_ID = Z_L("Not valid ID");
    const TimeZone* NULL_TIMEZONE = null_z;

	// [Execution]
    const TimeZone* pTimeZone = STimeZoneFactory::GetTimeZoneById(INVALID_TIMEZONE_ID);

    // [Verification]
    BOOST_CHECK_EQUAL(pTimeZone, NULL_TIMEZONE);
}

#endif


// End - Test Suite: STimeZoneFactory
ZTEST_SUITE_END()
