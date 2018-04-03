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

#include "ZTiming/DateTimeNow.h"

#include "ZTime/TimeZone.h"
#include "ZTime/STimeZoneFactory.h"


ZTEST_SUITE_BEGIN( DateTimeNow_TestSuite )
    
/// <summary>
/// Checks that it creates a valid date and time.
/// </summary>
ZTEST_CASE ( Constructor1_CreatesValidDateTime_Test )
{
    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;

	// [Execution]
    DateTimeNow now;
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
}

/// <summary>
/// Checks that it creates a valid date and time when the input time zone is null.
/// </summary>
ZTEST_CASE ( Constructor2_CreatesValidDateTimeWhenTimeZoneIsNull_Test )
{
    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;
    const TimeZone* NULL_TIMEZONE = null_z;

	// [Execution]
    DateTimeNow now(NULL_TIMEZONE);
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();
    const TimeZone* pTimeZone = now.GetTimeZone();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
    BOOST_CHECK_EQUAL(pTimeZone, NULL_TIMEZONE);
}

/// <summary>
/// Checks that it creates a valid date and time when the input time is not null.
/// </summary>
ZTEST_CASE ( Constructor2_CreatesValidDateTimeWhenTimeZoneIsNotNull_Test )
{
    // [Preparation]
    const bool IS_NOT_UNDEFINED = true;
    const TimeZone* TIMEZONE = STimeZoneFactory::GetTimeZoneById("Europe/London");

	// [Execution]
    DateTimeNow now(TIMEZONE);
    
    // [Verification]
    bool IsNotUndefined = !now.IsUndefined();
    const TimeZone* pTimeZone = now.GetTimeZone();

    BOOST_CHECK_EQUAL(IsNotUndefined, IS_NOT_UNDEFINED);
    BOOST_CHECK_EQUAL(pTimeZone, TIMEZONE);
}

// End - Test Suite: DateTimeNow
ZTEST_SUITE_END()
