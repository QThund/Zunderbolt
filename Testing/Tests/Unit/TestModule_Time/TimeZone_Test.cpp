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

#include "ZTime/TimeZone.h"

#include <sstream>
#include "ZTime/TimeSpan.h"
#include "ZTime/STimeZoneFactory.h"
#include "ZCommon/Exceptions/AssertException.h"


ZTEST_SUITE_BEGIN( TimeZone_TestSuite )

/// <summary>
/// Checks that the instance is correctly constructed when using common input values.
/// </summary>
ZTEST_CASE ( Constructor_InstanceIsCorrectlyConstructedWhenUsingCommonInputs_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid");
    const string_z COMMON_TIMEZONE_NAME = Z_L("CET");
    const TimeSpan COMMON_TIMEZONE_OFFSET = TimeSpan(123456789);
    const bool IS_NEGATIVE = false;
    const bool HAS_DST = true;

    // Creates the DST from Boost data
    boost::local_time::tz_database TIMEZONE_DATABASE;
    std::istringstream streamDbSource;
    streamDbSource.str("\"Europe/Madrid\",\"CET\",\"CET\",\"CEST\",\"CEST\",\"+01:00:00\",\"+01:00:00\",\"-1;0;3\",\"+02:00:00\",\"-1;0;10\",\"+03:00:00\"");
    TIMEZONE_DATABASE.load_from_stream(streamDbSource);

    boost::local_time::time_zone_ptr timeZoneFromDB = TIMEZONE_DATABASE.time_zone_from_region("Europe/Madrid");
    const TimeZone::DstInformation DST_INFO(timeZoneFromDB);

	// [Execution]
    TimeZone timeZone(COMMON_TIMEZONE_ID, COMMON_TIMEZONE_NAME, COMMON_TIMEZONE_OFFSET, IS_NEGATIVE, DST_INFO, HAS_DST);

    // [Verification]
    BOOST_CHECK(timeZone.GetId() == COMMON_TIMEZONE_ID);
    BOOST_CHECK(timeZone.GetName() == COMMON_TIMEZONE_NAME);
    BOOST_CHECK(timeZone.GetTimeZoneOffset() == COMMON_TIMEZONE_OFFSET);
    BOOST_CHECK_EQUAL(timeZone.IsTimeZoneOffsetNegative(), IS_NEGATIVE);
    BOOST_CHECK_EQUAL(timeZone.HasDstOffset(), HAS_DST);
    BOOST_CHECK(timeZone.GetDstInfo().IsOffsetNegative() == DST_INFO.IsOffsetNegative());
    BOOST_CHECK(timeZone.GetDstInfo().GetOffset() == DST_INFO.GetOffset());
}

/// <summary>
/// Checks that it returns the expected result when the DST offset is active.
/// </summary>
ZTEST_CASE ( CalculateOffset_ReturnsExpectedOffsetWhenDstIsActive_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid");
    const TimeZone* TIME_ZONE = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const DateTime DST_START_TIME = TIME_ZONE->GetDstInfo().GetStartInYear(2020);
    const TimeSpan EXPECTED_OFFSET = TimeSpan(72000000000); // +2 hours
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    TimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(DST_START_TIME, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

/// <summary>
/// Checks that it returns the expected result when the DST offset is NOT active.
/// </summary>
ZTEST_CASE ( CalculateOffset_ReturnsExpectedOffsetWhenDstIsNotActive_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid");
    const TimeZone* TIME_ZONE = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const DateTime BEFORE_DST_START_TIME = TIME_ZONE->GetDstInfo().GetStartInYear(2020) - TimeSpan(1);
    const TimeSpan EXPECTED_OFFSET = TimeSpan(36000000000); // +1 hour
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    TimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(BEFORE_DST_START_TIME, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

/// <summary>
/// Checks that the DST is not applied when the date is prior to 1916.
/// </summary>
ZTEST_CASE ( CalculateOffset_DstIsNotAppliedWhenDateIsPriorTo1916_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid"); // +1 hour
    const TimeZone* TIME_ZONE = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const DateTime DATE_BEFORE_1916 = DateTime(1915, 7, 1, TimeZone::UTC);
    const TimeSpan EXPECTED_OFFSET = TimeSpan(36000000000); 
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    TimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(DATE_BEFORE_1916, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

/// <summary>
/// Checks that the DST is not applied when the date is posterior to 9999.
/// </summary>
ZTEST_CASE ( CalculateOffset_DstIsNotAppliedWhenDateIsPosteriorTo9999_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid"); // +1 hour
    const TimeZone* TIME_ZONE = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const DateTime DATE_YEAR_10000 = DateTime(10000, 7, 1, TimeZone::UTC);
    const TimeSpan EXPECTED_OFFSET = TimeSpan(36000000000);
    const bool EXPECTED_OFFSET_SIGN = false;

	// [Execution]
    TimeSpan offset(0);
    bool bOffsetIsNegative = true;
    TIME_ZONE->CalculateOffset(DATE_YEAR_10000, offset, bOffsetIsNegative);

    // [Verification]
    BOOST_CHECK(offset == EXPECTED_OFFSET);
    BOOST_CHECK_EQUAL(bOffsetIsNegative, EXPECTED_OFFSET_SIGN);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the input date and time is undefined.
/// </summary>
ZTEST_CASE ( CalculateOffset_AssertionFailsWhenInputDateIsUndefined_Test )
{
    // [Preparation]
    const string_z COMMON_TIMEZONE_ID = Z_L("Europe/Madrid");
    const TimeZone* TIME_ZONE = STimeZoneFactory::GetTimeZoneById(COMMON_TIMEZONE_ID);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;
    
    try
    {
        TimeSpan offset(0);
        bool bOffsetIsNegative = true;
        TIME_ZONE->CalculateOffset(DateTime::GetUndefinedDate(), offset, bOffsetIsNegative);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetId_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetName_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetTimeZoneOffset_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetDstInfo_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( IsTimeZoneOffsetNegative_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( HasDstOffset_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

// End - Test Suite: TimeZone
ZTEST_SUITE_END()
