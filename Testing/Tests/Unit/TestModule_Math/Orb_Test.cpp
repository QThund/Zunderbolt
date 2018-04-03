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
#include <boost/mpl/list.hpp>
using namespace boost::unit_test;

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZMath/Orb.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZCommon/Exceptions/AssertException.h"

typedef boost::mpl::list<Vector2, Vector3, Vector4> TTemplateTypes;


ZTEST_SUITE_BEGIN( Orb_TestSuite )

/// <summary>
/// Checks if default values have changed.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor1_DefaultValuesHaveNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_0;

	// [Execution]
    Orb<T> orbUT;

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's center and radius properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor2_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

    const Orb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Orb<T> orbUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if copy constructor sets orb's point and radius properly.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor3_ValuesAreCopiedProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

    const BaseOrb<T> EXPECTED_ORB(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Orb<T> orbUT(EXPECTED_ORB);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks if values used as parameters are properly set.
/// </summary>
ZTEST_CASE_TEMPLATE ( Constructor4_ValuesAreSetProperly_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };

    const T EXPECTED_VALUE_FOR_CENTER = T(VECTOR_COMPONENTS_CENTER);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_5;

	// [Execution]
    Orb<T> orbUT(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that the returned orb has not changed since the last time the test was executed.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetUnitOrb_ValueHasNotChanged_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_1;


	// [Execution]
    Orb<T> orbUT = Orb<T>::GetUnitOrb();

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that a orb is correctly assigned to another orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( OperatorAssignation_OrbIsAssignedProperlyToAnother_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const T EXPECTED_VALUE_FOR_CENTER(VECTOR_COMPONENTS);
    const float_z EXPECTED_VALUE_FOR_RADIUS = SFloat::_4;

    const BaseOrb<T> OTHER_ORB = BaseOrb<T>(EXPECTED_VALUE_FOR_CENTER, EXPECTED_VALUE_FOR_RADIUS);

	// [Execution]
    Orb<T> orbUT;
    orbUT = OTHER_ORB;

    // [Verification]
    BOOST_CHECK(orbUT.Center == EXPECTED_VALUE_FOR_CENTER);
    BOOST_CHECK(orbUT.Radius == EXPECTED_VALUE_FOR_RADIUS);
}

/// <summary>
/// Checks that it returns false when the orb doesn't contain the point.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenTheOrbDoesNotContainThePoint_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_POINT[] = { SFloat::_9, SFloat::_8, SFloat::_7, SFloat::_1 };

    const Orb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the orb contains the point (and it doesn't lay on the surface).
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenTheOrbContainsThePoint_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_2, SFloat::_1 };
    float_z VECTOR_COMPONENTS_POINT[] = { SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1 };

    const Orb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SFloat::_2 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when the point lies on the surface of the orb.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenThePointLiesOnTheSurfaceOfTheOrb_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_POINT[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );
    const T POINT = T(VECTOR_COMPONENTS_POINT);
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIsContained = ORB.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(bIsContained, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenRadiusEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };

    const Orb<T> ORB( T(VECTOR_COMPONENTS), SFloat::_0 );
    const T POINT = T(VECTOR_COMPONENTS);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        ORB.Contains(POINT);
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
/// Checks that it returns the expected result when all points coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsExpectedResultWhenRadiusEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    float_z VECTOR1_COMPONENTS[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7 };
    float_z VECTOR2_COMPONENTS[] = { SFloat::_4, SFloat::_2, SFloat::_3, SFloat::_7 };

    const Orb<T> ORB( T(VECTOR1_COMPONENTS), SFloat::_0 );
    const T POINT_COINCIDENT = T(VECTOR1_COMPONENTS);
    const T POINT_NOT_COINCIDENT = T(VECTOR2_COMPONENTS);

    const bool EXPECTED_RESULT_COINCIDENT = true;
    const bool EXPECTED_RESULT_NOT_COINCIDENT = false;

	// [Execution]
    bool bResultCoincident = ORB.Contains(POINT_COINCIDENT);
    bool bResultNotCoincident = ORB.Contains(POINT_NOT_COINCIDENT);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultCoincident, EXPECTED_RESULT_COINCIDENT);
    BOOST_CHECK_EQUAL(bResultNotCoincident, EXPECTED_RESULT_NOT_COINCIDENT);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns false when orbs don't intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsFalseWhenOrbsDoNotIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_9, SFloat::_9, SFloat::_9, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_1 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );

    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs intersect.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsIntersect_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_2, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_1 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are tangent.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsAreTangent_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_1 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are the same.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOrbsAreTheSame_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER), SFloat::_1 );
    const Orb<T> ORB2 = ORB1;

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns true when orbs are tangent.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsTrueWhenOneOrbIsContainedInOther_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_9 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );

    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bIntersect1 = ORB1.Intersection(ORB2);
    bool bIntersect2 = ORB2.Intersection(ORB1);

    // [Verification]
    BOOST_CHECK_EQUAL(bIntersect1, EXPECTED_RESULT);
    BOOST_CHECK_EQUAL(bIntersect2, EXPECTED_RESULT);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the radius of one of the orbs equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_AssertionFailsWhenRadiusEqualsZero_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_0 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        ORB1.Intersection(ORB2);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        ORB2.Intersection(ORB1);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that it returns the expected result when the radius of one of the orbs equals zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( Intersection_ReturnsExpectedResultWhenRadiusEqualsZero_Test, TTemplateTypes )
{
    // Note: This is a special test that checks too many things (which is incorrect in a unit test) just to assure that the 
    //       method behaves as expected when assertions are disabled.

    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER1[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1 };
    float_z VECTOR_COMPONENTS_CENTER2[] = { SFloat::_3, SFloat::_2, SFloat::_3, SFloat::_1 };

    const Orb<T> ORB1( T(VECTOR_COMPONENTS_CENTER1), SFloat::_0 );
    const Orb<T> ORB2( T(VECTOR_COMPONENTS_CENTER2), SFloat::_1 );
    const Orb<T> ORB3( T(VECTOR_COMPONENTS_CENTER2), SFloat::_2 );

    const bool EXPECTE_RESULT_INTERSECTION = true;
    const bool EXPECTE_RESULT_NO_INTERSECTION = false;

	// [Execution]
    bool bResultNoIntersection = ORB1.Intersection(ORB2);
    bool bResultIntersection = ORB1.Intersection(ORB3);

    // [Verification]
    BOOST_CHECK_EQUAL(bResultIntersection, EXPECTE_RESULT_INTERSECTION);
    BOOST_CHECK_EQUAL(bResultNoIntersection, EXPECTE_RESULT_NO_INTERSECTION);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the expected output string is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( ToString_ExpectedOutputIsReturned_Test, TTemplateTypes )
{
    // [Preparation]
    float_z VECTOR_COMPONENTS_CENTER[] = { SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4 };
    const T VECTOR_FOR_CENTER(VECTOR_COMPONENTS_CENTER);
    const float_z RADIUS = SFloat::_5;
    const Orb<T> ORB( VECTOR_FOR_CENTER, RADIUS );

    const string_z CENTER_STRING = VECTOR_FOR_CENTER.ToString();
    const string_z EXPECTED_STRING = string_z("OB(c(") + CENTER_STRING + Z_L("),r(") + string_z::FromFloat(RADIUS) + Z_L("))");

	// [Execution]
    string_z strReturnedString = ORB.ToString();

    // [Verification]
    BOOST_CHECK(strReturnedString == EXPECTED_STRING);
}

// End - Test Suite: Orb
ZTEST_SUITE_END()
