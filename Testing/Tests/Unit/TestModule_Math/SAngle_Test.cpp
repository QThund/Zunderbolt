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

#include "ZMath/SAngle.h"

#include "ZCommon/DataTypes/SFloat.h"


ZTEST_SUITE_BEGIN( SAngle_TestSuite )

/// <summary>
/// Checks that degrees are correctly converted to radians.
/// </summary>
ZTEST_CASE ( DegreesToRadians_DegreesAreCorrectlyConvertedToRadians_Test )
{
    // [Preparation]
    const float_z DEGREES = SAngle::_45;
    const float_z EXPECTED_VALUE = SAngle::_QuarterPi;

	// [Execution]
    float_z fResultUT = SAngle::DegreesToRadians(DEGREES);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that radians are correctly converted to degrees.
/// </summary>
ZTEST_CASE ( RadiansToDegrees_RadiansAreCorrectlyConvertedToDegrees_Test )
{
    // [Preparation]
    const float_z RADIANS = SAngle::_QuarterPi;
    const float_z EXPECTED_VALUE = SAngle::_45;

	// [Execution]
    float_z fResultUT = SAngle::RadiansToDegrees(RADIANS);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full revolution positive angle is truncated to 0.
/// </summary>
ZTEST_CASE ( Truncate_FullRevolutionPositiveAngleIsTruncatedToZero_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = SAngle::_2Pi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = SAngle::_360;
	#endif

    const float_z EXPECTED_VALUE = SFloat::_0;

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that the full revolution negative angle is truncated to 0.
/// </summary>
ZTEST_CASE ( Truncate_FullRevolutionNegativeAngleIsTruncatedToZero_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = -SAngle::_2Pi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = -SAngle::_360;
	#endif

    const float_z EXPECTED_VALUE = SFloat::_0;

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a positive angle greater than the full revolution positive angle is truncated to a lower equivalent angle.
/// </summary>
ZTEST_CASE ( Truncate_PositiveAnglesGreaterThanFullRevolutionPositiveAngleAreCorrectlyTruncated_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = SAngle::_2Pi + SAngle::_QuarterPi;
		const float_z EXPECTED_VALUE = SAngle::_QuarterPi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = SAngle::_360 + SAngle::_45;
		const float_z EXPECTED_VALUE = SAngle::_45;
	#endif

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_VALUE) );   // Due to precission issues
}

/// <summary>
/// Checks that a negative angle lower than the full revolution negative angle is truncated to a greater equivalent angle.
/// </summary>
ZTEST_CASE ( Truncate_NegativeAnglesLowerThanFullRevolutionNegativeAngleAreCorrectlyTruncated_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = -SAngle::_2Pi - SAngle::_QuarterPi;
		const float_z EXPECTED_VALUE = -SAngle::_QuarterPi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = -SAngle::_360 - SAngle::_45;
		const float_z EXPECTED_VALUE = -SAngle::_45;
	#endif

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_VALUE) );   // Due to precission issues
}

/// <summary>
/// Checks that a positive angle lower than the full revolution positive angle is not truncated.
/// </summary>
ZTEST_CASE ( Truncate_PositiveAnglesLowerThanFullRevolutionPositiveAngleAreNotTruncated_Test )
{
    // [Preparation]
	#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = SAngle::_3HalfsPi;
		const float_z EXPECTED_VALUE = SAngle::_3HalfsPi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = SAngle::_270;
		const float_z EXPECTED_VALUE = SAngle::_270;
	#endif

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that a negative angle greater than the full revolution negative angle is not truncated.
/// </summary>
ZTEST_CASE ( Truncate_NegativeAnglesGreaterThanFullRevolutionNegativeAngleAreNotTruncated_Test )
{
    // [Preparation]
	#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
		const float_z ANGLE = -SAngle::_3HalfsPi;
		const float_z EXPECTED_VALUE = -SAngle::_3HalfsPi;
	#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
		const float_z ANGLE = -SAngle::_270;
		const float_z EXPECTED_VALUE = -SAngle::_270;
	#endif

	// [Execution]
    float_z fResultUT = SAngle::Truncate(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when angle equals zero, revolutions equals zero.
/// </summary>
ZTEST_CASE ( CountRevolutions_ZeroAngleIsCountAsZeroRevolutions_Test )
{
    // [Preparation]
    const float_z ANGLE = SFloat::_0;
    const float_z EXPECTED_VALUE = SFloat::_0;

	// [Execution]
    float_z fResultUT = SAngle::CountRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when the angle describes exactly a circumference, revolutions equals one.
/// </summary>
ZTEST_CASE ( CountRevolutions_CompleteCircunferenceIsCountAsOneRevolution_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = SAngle::_2Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_360;
    #endif

    const float_z EXPECTED_VALUE = SFloat::_1;

	// [Execution]
    float_z fResultUT = SAngle::CountRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolution fractions are taken into account.
/// </summary>
ZTEST_CASE ( CountRevolutions_RevolutionFractionsAreTakenIntoAccount_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = SAngle::_2Pi + SAngle::_Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_360 + SAngle::_180;
    #endif

    const float_z EXPECTED_VALUE = SFloat::_1 + SFloat::_0_5;

	// [Execution]
    float_z fResultUT = SAngle::CountRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolutions are negative when the angle is negative.
/// </summary>
ZTEST_CASE ( CountRevolutions_RevolutionsAreNegativeWhenNegativeAnglesAreUsed_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = -SFloat::_2 * SAngle::_2Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = -SFloat::_2 * SAngle::_360;
    #endif

    const float_z EXPECTED_VALUE = -SFloat::_2;

	// [Execution]
    float_z fResultUT = SAngle::CountRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when angle equals zero, revolutions equals zero.
/// </summary>
ZTEST_CASE ( CountCompleteRevolutions_ZeroAngleIsCountAsZeroRevolutions_Test )
{
    // [Preparation]
    const float_z ANGLE = SFloat::_0;
    const float_z EXPECTED_VALUE = SFloat::_0;

	// [Execution]
    float_z fResultUT = SAngle::CountCompleteRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that when the angle describes exactly a circumference, revolutions equals one.
/// </summary>
ZTEST_CASE ( CountCompleteRevolutions_CompleteCircunferenceIsCountAsOneRevolution_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = SAngle::_2Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_360;
    #endif

    const float_z EXPECTED_VALUE = SFloat::_1;

	// [Execution]
    float_z fResultUT = SAngle::CountCompleteRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolution fractions are not taken into account.
/// </summary>
ZTEST_CASE ( CountCompleteRevolutions_RevolutionFractionsAreNotTakenIntoAccount_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = SAngle::_2Pi + SAngle::_Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = SAngle::_360 + SAngle::_180;
    #endif

    const float_z EXPECTED_VALUE = SFloat::_1;

	// [Execution]
    float_z fResultUT = SAngle::CountCompleteRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

/// <summary>
/// Checks that revolutions are negative when the angle is negative.
/// </summary>
ZTEST_CASE ( CountCompleteRevolutions_RevolutionsAreNegativeWhenNegativeAnglesAreUsed_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
        const float_z ANGLE = -SFloat::_2 * SAngle::_2Pi;
    #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z ANGLE = -SFloat::_2 * SAngle::_360;
    #endif

    const float_z EXPECTED_VALUE = -SFloat::_2;

	// [Execution]
    float_z fResultUT = SAngle::CountCompleteRevolutions(ANGLE);

    // [Verification]
    BOOST_CHECK_EQUAL(fResultUT, EXPECTED_VALUE);
}

// End - Test Suite: SAngle
ZTEST_SUITE_END()
