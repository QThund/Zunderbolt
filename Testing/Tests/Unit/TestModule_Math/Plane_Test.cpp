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

#include "ZMath/Plane.h"
#include "ZMath/Plane.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"
#include "ZMath/Quaternion.h"
#include "ZMath/Matrix4x3.h"
#include "ZMath/Matrix4x4.h"
#include "ZMath/TranslationMatrix.h"
#include "ZMath/TransformationMatrix.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/SAngle.h"
#include "ZMath/SpaceConversionMatrix.h"
#include "ZCommon/Exceptions/AssertException.h"
using namespace z::Internals;

typedef boost::mpl::list<Vector3, Vector4> TVectorTypes;
typedef boost::mpl::list<Matrix4x3, Matrix4x4> TMatrixTypes;


ZTEST_SUITE_BEGIN( Plane_TestSuite )

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( FriendOperatorProduct_ScalarIsCorrectlyMultipliedByPlane_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_1 + SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_2;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Plane planeUT = SCALAR * PLANE;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if copy constructor sets plane's components properly.
/// </summary>
ZTEST_CASE ( Constructor2_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE_TO_COPY(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Plane planeUT = PLANE_TO_COPY;

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if base type constructor sets plane's components properly.
/// </summary>
ZTEST_CASE ( Constructor3_ValuesAreCopiedProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE_TO_COPY(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Plane planeUT = Plane(PLANE_TO_COPY);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if values used as parameters are properly set to plane's components.
/// </summary>
ZTEST_CASE ( Constructor4_ValuesAreSetProperly_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

	// [Execution]
    Plane planeUT(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks if the value provided is set to all the plane's components.
/// </summary>
ZTEST_CASE ( Constructor5_ValueIsSetForAllComponents_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_ALL = SFloat::_5;

	// [Execution]
    Plane planeUT(EXPECTED_VALUE_FOR_ALL);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_ALL) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_ALL) );
}

/// <summary>
/// Checks if the plane's components are set to the correct floats stored in a valid memory space.
/// </summary>
ZTEST_CASE ( Constructor6_VectorComponentsAreFilledWithValidReferenceTo4Floats_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    float_z* VALID_ARRAY_OF_4_FLOATS = new float_z[4];
    VALID_ARRAY_OF_4_FLOATS[0] = EXPECTED_VALUE_FOR_A;
    VALID_ARRAY_OF_4_FLOATS[1] = EXPECTED_VALUE_FOR_B;
    VALID_ARRAY_OF_4_FLOATS[2] = EXPECTED_VALUE_FOR_C;
    VALID_ARRAY_OF_4_FLOATS[3] = EXPECTED_VALUE_FOR_D;

	// [Execution]
    Plane planeUT(VALID_ARRAY_OF_4_FLOATS);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, VALID_ARRAY_OF_4_FLOATS[0]) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, VALID_ARRAY_OF_4_FLOATS[1]) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, VALID_ARRAY_OF_4_FLOATS[2]) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, VALID_ARRAY_OF_4_FLOATS[3]) );

    // Cleaning
    delete[] VALID_ARRAY_OF_4_FLOATS;
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks if the assertion inside the function fails when a null pointer is received.
/// </summary>
ZTEST_CASE ( Constructor6_AssertionFailsWhenPointerIsNull_Test )
{
    // [Preparation]
    float_z* NULL_ARRAY = null_z;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Plane planeUT(NULL_ARRAY);
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
/// Checks if plane's components are set to the correct values packed in a valid vf32 object.
/// </summary>
ZTEST_CASE ( Constructor7_VectorComponentsAreSetToValidVF32PackedValues_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_3;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

	vf32_z PACK;
	SVF32::Pack(EXPECTED_VALUE_FOR_A, EXPECTED_VALUE_FOR_B, EXPECTED_VALUE_FOR_C, EXPECTED_VALUE_FOR_D, PACK);

	// [Execution]
	Plane planeUT(PACK);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the plane is correctly constructed when using 3 common points (not coincidental).
/// </summary>
ZTEST_CASE ( Constructor8_PlaneIsConstructedWhenUsingThreeCommonPoints_Test )
{
    // [Preparation]
    const Vector3 POINT1 = Vector3(SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector3 POINT2 = Vector3(SFloat::_0, SFloat::_2, SFloat::_0);
    const Vector3 POINT3 = Vector3(SFloat::_0, SFloat::_0, SFloat::_2);

    const float_z EXPECTED_VALUE_FOR_A = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_B = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_C = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_D = (float_z)-1.1547005383792517;

	// [Execution]
    Plane planeUT = Plane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when any of the points coincide.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenAnyOfThePointsCoincide_Test )
{
    // [Preparation]
    const Vector3 SAME_POINT = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 DIFFERENT_POINT = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        Plane(SAME_POINT, SAME_POINT, DIFFERENT_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        Plane(DIFFERENT_POINT, SAME_POINT, SAME_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        Plane(SAME_POINT, DIFFERENT_POINT, SAME_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the points belong to the same line.
/// </summary>
ZTEST_CASE ( Constructor8_AssertionFailsWhenPointsAreCollinear_Test )
{
    // [Preparation]
    const Vector3 POINT1 = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 POINT2 = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);
    const Vector3 POINT3 = Vector3(SFloat::_7, SFloat::_8, SFloat::_9);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Plane(POINT1, POINT2, POINT3);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned plane is normalized.
/// </summary>
ZTEST_CASE ( Constructor8_ConstructedPlaneIsNormalized_Test )
{
    // [Preparation]
    const Vector3 POINT1 = Vector3(SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector3 POINT2 = Vector3(SFloat::_0, SFloat::_2, SFloat::_0);
    const Vector3 POINT3 = Vector3(SFloat::_0, SFloat::_0, SFloat::_2);

    const float_z EXPECTED_VALUE_FOR_A = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_B = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_C = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_D = (float_z)-1.1547005383792517;

	// [Execution]
    Plane planeUT = Plane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that a different order of the points might change the resultant plane.
/// </summary>
ZTEST_CASE ( Constructor8_OrderOfPointsAffectsResult_Test )
{
    // [Preparation]
    const Vector3 POINT1 = Vector3(SFloat::_2, SFloat::_0, SFloat::_0);
    const Vector3 POINT2 = Vector3(SFloat::_0, SFloat::_2, SFloat::_0);
    const Vector3 POINT3 = Vector3(SFloat::_0, SFloat::_0, SFloat::_2);

	// [Execution]
    // Imagine that you use the normal of the plane that points to the origin as the rotation axis
    // of a clock whose hands spins pointing, one by one, to the points
    Plane planeUT1 = Plane(POINT1, POINT2, POINT3); //  Direction
    Plane planeUT2 = Plane(POINT1, POINT3, POINT2); // -Direction
    Plane planeUT3 = Plane(POINT2, POINT1, POINT3); // -Direction
    Plane planeUT4 = Plane(POINT2, POINT3, POINT1); //  Direction
    Plane planeUT5 = Plane(POINT3, POINT1, POINT2); //  Direction
    Plane planeUT6 = Plane(POINT3, POINT2, POINT1); // -Direction

    // [Verification]
    BOOST_CHECK(planeUT1 != planeUT2);
    BOOST_CHECK(planeUT1 != planeUT3);
    BOOST_CHECK(planeUT1 == planeUT4);
    BOOST_CHECK(planeUT1 == planeUT5);
    BOOST_CHECK(planeUT1 != planeUT6);
    BOOST_CHECK(planeUT2 == planeUT3);
    BOOST_CHECK(planeUT2 != planeUT4);
    BOOST_CHECK(planeUT2 != planeUT5);
    BOOST_CHECK(planeUT2 == planeUT6);
    BOOST_CHECK(planeUT3 != planeUT4);
    BOOST_CHECK(planeUT3 != planeUT5);
    BOOST_CHECK(planeUT3 == planeUT6);
    BOOST_CHECK(planeUT4 == planeUT5);
    BOOST_CHECK(planeUT4 != planeUT6);
    BOOST_CHECK(planeUT5 != planeUT6);
}

/// <summary>
/// Checks that the plane is correctly constructed when using 3 common points (not coincidental).
/// </summary>
ZTEST_CASE ( Constructor9_PlaneIsConstructedWhenUsingThreeCommonPoints_Test )
{
    // [Preparation]
    const Vector4 POINT1 = Vector4(SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector4 POINT2 = Vector4(SFloat::_0, SFloat::_2, SFloat::_0, SFloat::_1);
    const Vector4 POINT3 = Vector4(SFloat::_0, SFloat::_0, SFloat::_2, SFloat::_1);

    const float_z EXPECTED_VALUE_FOR_A = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_B = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_C = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_D = (float_z)-1.1547005383792517;

	// [Execution]
    Plane planeUT = Plane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when any of the points coincides.
/// </summary>
ZTEST_CASE ( Constructor9_AssertionFailsWhenAnyOfThePointsCoincides_Test )
{
    // [Preparation]
    const Vector4 SAME_POINT = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector4 DIFFERENT_POINT = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        Plane(SAME_POINT, SAME_POINT, DIFFERENT_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        Plane(DIFFERENT_POINT, SAME_POINT, SAME_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        Plane(SAME_POINT, DIFFERENT_POINT, SAME_POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the points belong to the same line.
/// </summary>
ZTEST_CASE ( Constructor9_AssertionFailsWhenPointsAreCollinear_Test )
{
    // [Preparation]
    const Vector4 POINT1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector4 POINT2 = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_1);
    const Vector4 POINT3 = Vector4(SFloat::_7, SFloat::_8, SFloat::_9, SFloat::_1);

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        Plane(POINT1, POINT2, POINT3);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the returned plane is normalized.
/// </summary>
ZTEST_CASE ( Constructor9_ConstructedPlaneIsNormalized_Test )
{
    // [Preparation]
    const Vector4 POINT1 = Vector4(SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector4 POINT2 = Vector4(SFloat::_0, SFloat::_2, SFloat::_0, SFloat::_1);
    const Vector4 POINT3 = Vector4(SFloat::_0, SFloat::_0, SFloat::_2, SFloat::_1);

    const float_z EXPECTED_VALUE_FOR_A = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_B = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_C = (float_z)0.57735026918962584;
    const float_z EXPECTED_VALUE_FOR_D = (float_z)-1.1547005383792517;

	// [Execution]
    Plane planeUT = Plane(POINT1, POINT2, POINT3);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that a different order of the points might change the resultant plane.
/// </summary>
ZTEST_CASE ( Constructor9_OrderOfPointsAffectsResult_Test )
{
    // [Preparation]
    const Vector4 POINT1 = Vector4(SFloat::_2, SFloat::_0, SFloat::_0, SFloat::_1);
    const Vector4 POINT2 = Vector4(SFloat::_0, SFloat::_2, SFloat::_0, SFloat::_1);
    const Vector4 POINT3 = Vector4(SFloat::_0, SFloat::_0, SFloat::_2, SFloat::_1);

	// [Execution]
    // Imagine that you use the normal of the plane that points to the origin as the rotation axis
    // of a clock whose hands spins pointing, one by one, to the points
    Plane planeUT1 = Plane(POINT1, POINT2, POINT3); //  Direction
    Plane planeUT2 = Plane(POINT1, POINT3, POINT2); // -Direction
    Plane planeUT3 = Plane(POINT2, POINT1, POINT3); // -Direction
    Plane planeUT4 = Plane(POINT2, POINT3, POINT1); //  Direction
    Plane planeUT5 = Plane(POINT3, POINT1, POINT2); //  Direction
    Plane planeUT6 = Plane(POINT3, POINT2, POINT1); // -Direction

    // [Verification]
    BOOST_CHECK(planeUT1 != planeUT2);
    BOOST_CHECK(planeUT1 != planeUT3);
    BOOST_CHECK(planeUT1 == planeUT4);
    BOOST_CHECK(planeUT1 == planeUT5);
    BOOST_CHECK(planeUT1 != planeUT6);
    BOOST_CHECK(planeUT2 == planeUT3);
    BOOST_CHECK(planeUT2 != planeUT4);
    BOOST_CHECK(planeUT2 != planeUT5);
    BOOST_CHECK(planeUT2 == planeUT6);
    BOOST_CHECK(planeUT3 != planeUT4);
    BOOST_CHECK(planeUT3 != planeUT5);
    BOOST_CHECK(planeUT3 == planeUT6);
    BOOST_CHECK(planeUT4 == planeUT5);
    BOOST_CHECK(planeUT4 != planeUT6);
    BOOST_CHECK(planeUT5 != planeUT6);
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetNullPlane_ExpectedValueIsReturned_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_0;

	// [Execution]
    Plane planeUT = Plane::GetNullPlane();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlaneZX_ExpectedValueIsReturned_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_0;

	// [Execution]
    Plane planeUT = Plane::GetPlaneZX();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlaneXY_ExpectedValueIsReturned_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_0;

	// [Execution]
    Plane planeUT = Plane::GetPlaneXY();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}

/// <summary>
/// Checks that the expected value is returned.
/// </summary>
ZTEST_CASE_TEMPLATE ( GetPlaneYZ_ExpectedValueIsReturned_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_0;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_0;

	// [Execution]
    Plane planeUT = Plane::GetPlaneYZ();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_VALUE_FOR_A) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_VALUE_FOR_B) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_VALUE_FOR_C) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_VALUE_FOR_D) );
}


/// <summary>
/// Checks if the operator returns true when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND == RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_TrueWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon);
    const Plane RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND == RIGHT_OPERAND);
}

/// <summary>
/// Checks that when operators are similar but not equal (geometrically speaking), they are considered different.
/// </summary>
ZTEST_CASE ( OperatorEquality_FalseWhenOperatorsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_10);
    const Plane RIGHT_OPERAND(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_5); // LEFT_OPERAND / 2

	// [Execution] / Verification
    BOOST_CHECK(!(LEFT_OPERAND == RIGHT_OPERAND));
}

/// <summary>
/// Checks if the operator returns false when operand components differences equals tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are lower than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsDifferLessThanTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon - SFloat::Epsilon * SFloat::_0_5);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks if the operator returns false when operand components differences are greater than tolerance value.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperandsDifferGreaterThanTolerance_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon + SFloat::Epsilon * SFloat::_0_5);
    const Plane RIGHT_OPERAND(SFloat::_0);

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if the operator returns true when operand components are exactly equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_FalseWhenOperandsAreExactlyEqual_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::Epsilon);
    const Plane RIGHT_OPERAND(SFloat::Epsilon);

	// [Execution] / Verification
    BOOST_CHECK(!( LEFT_OPERAND != RIGHT_OPERAND ));
}

/// <summary>
/// Checks that when operators are similar but not equal (geometrically speaking), they are considered different.
/// </summary>
ZTEST_CASE ( OperatorInequality_TrueWhenOperatorsAreSimilarButNotEqual_Test )
{
    // [Preparation]
    const Plane LEFT_OPERAND(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_10);
    const Plane RIGHT_OPERAND(SFloat::_0_5, SFloat::_1, SFloat::_2, SFloat::_5); // LEFT_OPERAND / 2

	// [Execution] / Verification
    BOOST_CHECK(LEFT_OPERAND != RIGHT_OPERAND);
}

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProduct_PlaneIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Plane planeUT = PLANE * SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivision_PlaneIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z SCALAR = SFloat::_2;

	// [Execution]
    Plane planeUT = PLANE / SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are multiplied by the scalar.
/// </summary>
ZTEST_CASE ( OperatorProductAssignation_PlaneIsCorrectlyMultipliedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z SCALAR = SFloat::_0_5;

	// [Execution]
    Plane planeUT = PLANE;
    planeUT *= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks if all the components of the plane are divided by the scalar.
/// </summary>
ZTEST_CASE ( OperatorDivisionAssignation_PlaneIsCorrectlyDividedByScalar_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_0_5;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_4;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_8);
    const float_z SCALAR = SFloat::_2;

	// [Execution]
    Plane planeUT = PLANE;
    planeUT /= SCALAR;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that all plane components but D are correctly negated.
/// </summary>
ZTEST_CASE ( OperatorUnaryMinus_AllComponentsButDAreNegated_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = -SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = -SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = -SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_D = -SFloat::_8;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, EXPECTED_VALUE_FOR_D);

	// [Execution]
    Plane planeUT = -PLANE;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a plane is correctly assigned to another vector.
/// </summary>
ZTEST_CASE ( OperatorAssignation_PlaneIsAssignedProperlyToAnother_Test )
{
    // [Preparation]
    const float_z EXPECTED_VALUE_FOR_A = SFloat::_1;
    const float_z EXPECTED_VALUE_FOR_B = SFloat::_2;
    const float_z EXPECTED_VALUE_FOR_C = SFloat::_4;
    const float_z EXPECTED_VALUE_FOR_D = SFloat::_8;

    const Plane PLANE = Plane(EXPECTED_VALUE_FOR_A,
                                EXPECTED_VALUE_FOR_B,
                                EXPECTED_VALUE_FOR_C,
                                EXPECTED_VALUE_FOR_D);

	// [Execution]
    Plane planeUT = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    planeUT = PLANE;

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_VALUE_FOR_A);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_VALUE_FOR_B);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_VALUE_FOR_C);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_VALUE_FOR_D);
}

/// <summary>
/// Checks that a common plane becomes a normalized plane.
/// </summary>
ZTEST_CASE ( Normalize_CommonPlaneIsCorrectlyNormalized_Test )
{
    // [Preparation]
    const float_z EXPECTED_SUAREDLENGTH = SFloat::_1;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Plane planeUT = PLANE.Normalize();

    // [Verification]
    float_z fSquaredLength = planeUT.GetSquaredLength();

    BOOST_CHECK(SFloat::AreEqual(fSquaredLength, EXPECTED_SUAREDLENGTH));
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the assertion fails when a null plane is to be normalized.
/// </summary>
ZTEST_CASE ( Normalize_AssertionFailsWhenNullPlaneIsToBeNormalized_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Normalize();
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
/// Checks that the returned dot product result for 1 common plane and a common vector equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct1_ReturnsDotProductForCommonVectorAndPlane_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)32.0;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector3 VECTOR = Vector3(SFloat::_4, SFloat::_5, SFloat::_6);

	// [Execution]
    float_z fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vector is orthogonal to the plane.
/// </summary>
ZTEST_CASE ( DotProduct1_DotProductEqualsZeroWhenVectorIsOrthogonalToPlane_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane PLANE = Plane(SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 VECTOR = Vector3(SFloat::_0, SFloat::_3, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null.
/// </summary>
ZTEST_CASE ( DotProduct1_ReturnsZeroWhenAOperandIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane NONNULL_PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Plane NULL_PLANE = Plane::GetNullPlane();

    const Vector3 NONNULL_VECTOR = Vector3(SFloat::_1, SFloat::_2, SFloat::_3);
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

	// [Execution]
    float_z fResult1UT = NONNULL_PLANE.DotProduct(NULL_VECTOR);
    float_z fResult2UT = NULL_PLANE.DotProduct(NONNULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned dot product result for 1 common plane and a common vector equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct2_ReturnsDotProductForCommonVectorAndPlane_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)32.0;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Vector4 VECTOR = Vector4(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    float_z fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when vector is orthogonal to the plane.
/// </summary>
ZTEST_CASE ( DotProduct2_DotProductEqualsZeroWhenVectorIsOrthogonalToPlane_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane PLANE = Plane(SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR = Vector4(SFloat::_0, SFloat::_3, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.DotProduct(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null.
/// </summary>
ZTEST_CASE ( DotProduct2_ReturnsZeroWhenAOperandIsNull_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane NONNULL_PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Plane NULL_PLANE = Plane::GetNullPlane();

    const Vector4 NONNULL_VECTOR = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector4 NULL_VECTOR = Vector4::GetNullVector();

	// [Execution]
    float_z fResult1UT = NONNULL_PLANE.DotProduct(NULL_VECTOR);
    float_z fResult2UT = NULL_PLANE.DotProduct(NONNULL_VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
ZTEST_CASE ( DotProduct2_VectorsWComponentDoesNotTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 VECTOR1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector4 VECTOR2 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResult1UT = PLANE.DotProduct(VECTOR1);
    float_z fResult2UT = PLANE.DotProduct(VECTOR2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the returned dot product result for 2 common planes equals the expected value.
/// </summary>
ZTEST_CASE ( DotProduct3_ReturnsDotProductFor2Commonplanes_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = (float_z)32.0;

    const Plane OPERAND1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Plane OPERAND2 = Plane(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    float_z fResultUT = OPERAND1.DotProduct(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product is commutative.
/// </summary>
ZTEST_CASE ( DotProduct3_DotProductIsCommutative_Test )
{
    // [Preparation]
    const Plane OPERAND1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_7);
    const Plane OPERAND2 = Plane(SFloat::_4, SFloat::_5, SFloat::_6, SFloat::_8);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the dot product equals zero when planes are orthogonal.
/// </summary>
ZTEST_CASE ( DotProduct3_DotProductEqualsZeroWhenPlanesAreOrthogonal_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane OPERAND1 = Plane(SFloat::_3, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane OPERAND2 = Plane(SFloat::_0, SFloat::_3, SFloat::_0, SFloat::_0);
    const Plane OPERAND3 = Plane(SFloat::_0, SFloat::_0, SFloat::_3, SFloat::_0);

	// [Execution]
    float_z fResult1UT = OPERAND1.DotProduct(OPERAND2);
    float_z fResult2UT = OPERAND2.DotProduct(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the dot product equals zero when at least one operand is null plane.
/// </summary>
ZTEST_CASE ( DotProduct3_ReturnsZeroWhenAOperandIsNullplane_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane NONNULL_PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Plane NULL_PLANE = Plane::GetNullPlane();

	// [Execution]
    float_z fResult1UT = NONNULL_PLANE.DotProduct(NULL_PLANE);
    float_z fResult2UT = NULL_PLANE.DotProduct(NONNULL_PLANE);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the returned angle result for a common vector and a plane equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween1_ReturnsAngleBetweenCommonVectorAndPlane_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 VECTOR = Vector3(SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the angle equals zero when the normal of the plane and the vector are parallel.
/// </summary>
ZTEST_CASE ( AngleBetween1_AngleEqualsZeroWhenVectorAndPlaneNormalAreParallel_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 VECTOR = Vector3(SFloat::_9, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when the normal of the plane and the vector are orthogonal.
/// </summary>
ZTEST_CASE ( AngleBetween1_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorAndPlaneNormalAreOrthogonal_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_90;
    #else
        const float_z EXPECTED_RESULT = SAngle::_HalfPi;
    #endif

    const Plane PLANE = Plane(SFloat::_5, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 VECTOR = Vector3(SFloat::_0, SFloat::_5, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vector and the normal of the plane are opposite.
/// </summary>
ZTEST_CASE ( AngleBetween1_AngleEqualsPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_180;
    #else
        const float_z EXPECTED_RESULT = SAngle::_Pi;
    #endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 VECTOR = Vector3(-SFloat::_1, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
ZTEST_CASE ( AngleBetween1_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                       // _
    const Vector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector3(-SFloat::_1, SFloat::_1, SFloat::_0);  // \_
    const Vector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector3(-SFloat::_1, -SFloat::_1, SFloat::_0); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2UT, SFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector and the normal of the plane are not opposite.
/// </summary>
ZTEST_CASE ( AngleBetween1_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreNotOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_180;
    #else
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_Pi;
    #endif

    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                       // _
    const Vector3 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector3(-SFloat::_1, SFloat::_1, SFloat::_0);  // \_
    const Vector3 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector3(-SFloat::_1, -SFloat::_1, SFloat::_0); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
ZTEST_CASE ( AngleBetween1_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    const Plane NOT_NORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_0_5, SFloat::_0, SFloat::_0);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const Vector3 VECTOR = Vector3(SFloat::_1, SFloat::_1, SFloat::_0);

	// [Execution]
    float_z fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(VECTOR);
    float_z fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the plane or the vector is null.
/// </summary>
ZTEST_CASE ( AngleBetween1_AssertionFailsWhenPlaneOrVectorIsNull_Test )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane NONNULL_PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 NULL_VECTOR = Vector3(SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector3 NONNULL_VECTOR = Vector3(SFloat::_1, SFloat::_1, SFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NULL_PLANE.AngleBetween(NONNULL_VECTOR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NONNULL_PLANE.AngleBetween(NULL_VECTOR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that the returned angle result for a common vector and a plane equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween2_ReturnsAngleBetweenCommonVectorAndPlane_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the angle equals zero when the normal of the plane and the vector are parallel.
/// </summary>
ZTEST_CASE ( AngleBetween2_AngleEqualsZeroWhenVectorAndPlaneNormalAreParallel_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR = Vector4(SFloat::_9, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when the normal of the plane and the vector are orthogonal.
/// </summary>
ZTEST_CASE ( AngleBetween2_AngleEqualsHalfPiRadiansOr90DegreesWhenVectorAndPlaneNormalAreOrthogonal_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_90;
    #else
        const float_z EXPECTED_RESULT = SAngle::_HalfPi;
    #endif

    const Plane PLANE = Plane(SFloat::_5, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR = Vector4(SFloat::_0, SFloat::_5, SFloat::_0, SFloat::_1);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when vector and the normal of the plane are opposite.
/// </summary>
ZTEST_CASE ( AngleBetween2_AngleEqualsPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_180;
    #else
        const float_z EXPECTED_RESULT = SAngle::_Pi;
    #endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 VECTOR = Vector4(-SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1);

	// [Execution]
    float_z fResultUT = PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
ZTEST_CASE ( AngleBetween2_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                                    // _
    const Vector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);  // \_
    const Vector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_1); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2UT, SFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when vector and the normal of the plane are not opposite.
/// </summary>
ZTEST_CASE ( AngleBetween2_AngleIsLowerThanPiRadiansOr180DegreesWhenVectorAndPlaneNormalAreNotOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_180;
    #else
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_Pi;
    #endif

    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                                    // _
    const Vector4 OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);  // \_
    const Vector4 OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Vector4(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_1); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
ZTEST_CASE ( AngleBetween2_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    const Plane NOT_NORMALIZED_PLANE = Plane(SFloat::_0_5, SFloat::_0_5, SFloat::_0, SFloat::_0);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const Vector4 VECTOR = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1);

	// [Execution]
    float_z fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(VECTOR);
    float_z fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(VECTOR);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when either the plane or the vector is null.
/// </summary>
ZTEST_CASE ( AngleBetween2_AssertionFailsWhenPlaneOrVectorIsNull_Test )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane NONNULL_PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 NULL_VECTOR = Vector4(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const Vector4 NONNULL_VECTOR = Vector4(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NULL_PLANE.AngleBetween(NONNULL_VECTOR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NONNULL_PLANE.AngleBetween(NULL_VECTOR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
ZTEST_CASE ( AngleBetween2_VectorsWComponentDoesntTakePartInTheOperation_Test )
{
    // [Preparation]
    const Vector4 VECTOR1 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_1);
    const Vector4 VECTOR2 = Vector4(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_0);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResult1UT = PLANE.AngleBetween(VECTOR1);
    float_z fResult2UT = PLANE.AngleBetween(VECTOR2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the returned angle result for 2 common planes equals the expected value.
/// </summary>
ZTEST_CASE ( AngleBetween3_ReturnsAngleBetween2CommonPlanes_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        float_z EXPECTED_RESULT = SAngle::_45;
    #else
        const float_z EXPECTED_RESULT = SAngle::_QuarterPi;
    #endif

    Plane OPERAND1 = Plane(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    OPERAND1 = OPERAND1.Normalize();
    const Plane OPERAND2 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fResultUT, EXPECTED_RESULT) );
}

/// <summary>
/// Checks that the W component doesn't take part in the dot product operation.
/// </summary>
ZTEST_CASE ( AngleBetween3_DComponentDoesNotTakePartInTheOperation_Test )
{
    // [Preparation]
    Plane OPERAND1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    Plane OPERAND2 = Plane(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_7);
    Plane OPERAND3 = Plane(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_10);
    OPERAND1 = OPERAND1.Normalize();
    OPERAND2 = OPERAND2.Normalize();
    OPERAND3 = OPERAND3.Normalize();

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND1.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the "get angle from dot product" is commutative.
/// </summary>
ZTEST_CASE ( AngleBetween_AngleBetweenIsCommutative_Test )
{
    // [Preparation]
    Plane OPERAND1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    Plane OPERAND2 = Plane(SFloat::_5, SFloat::_6, SFloat::_7, SFloat::_8);
    OPERAND1 = OPERAND1.Normalize();
    OPERAND2 = OPERAND2.Normalize();

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND2.AngleBetween(OPERAND1);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, fResult2UT );
}

/// <summary>
/// Checks that the angle equals zero when planes are parallel.
/// </summary>
ZTEST_CASE ( AngleBetween3_AngleEqualsZeroWhenPlanesAreParallel_Test )
{
    // [Preparation]
    const float_z EXPECTED_RESULT = SFloat::_0;

    const Plane OPERAND1 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane OPERAND2 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_2);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals PI/2 (or 90º) when planes are orthogonal.
/// </summary>
ZTEST_CASE ( AngleBetween3_AngleEqualsHalfPiRadiansOr90DegreesWhenPlanesAreOrthogonal_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_90;
    #else
        const float_z EXPECTED_RESULT = SAngle::_HalfPi;
    #endif

    const Plane OPERAND1 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane OPERAND2 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0);
    const Plane OPERAND3 = Plane(SFloat::_0, SFloat::_0, SFloat::_1, SFloat::_0);

	// [Execution]
    float_z fResult1UT = OPERAND1.AngleBetween(OPERAND2);
    float_z fResult2UT = OPERAND2.AngleBetween(OPERAND3);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1UT, EXPECTED_RESULT );
    BOOST_CHECK_EQUAL( fResult2UT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle equals Pi (or 180º) when plane normals are opposite.
/// </summary>
ZTEST_CASE ( AngleBetween3_AngleEqualsPiRadiansOr180DegreesWhenPlaneNormalsAreOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z EXPECTED_RESULT = SAngle::_180;
    #else
        const float_z EXPECTED_RESULT = SAngle::_Pi;
    #endif

    const Plane OPERAND1 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane OPERAND2 = Plane(-SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultUT = OPERAND1.AngleBetween(OPERAND2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResultUT, EXPECTED_RESULT );
}

/// <summary>
/// Checks that the angle is always positive.
/// </summary>
ZTEST_CASE ( AngleBetween3_AngleIsAlwaysPositive_Test )
{
    // [Preparation]
    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                                // _
    const Plane OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);  // \_
    const Plane OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Plane(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_0); // /¨

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult1UT, SFloat::_0) );
    BOOST_CHECK( SFloat::IsGreaterOrEquals(fResult2UT, SFloat::_0) );
}

/// <summary>
/// Checks that the angle is lower than Pi (or 180º) when plane normals are not opposite.
/// </summary>
ZTEST_CASE ( AngleBetween3_AngleIsLowerThanPiRadiansOr180DegreesWhenPlaneNormalsAreNotOpposite_Test )
{
    // [Preparation]
    #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_180;
    #else
        const float_z HALF_CIRCUMFERENCE_ANGLE = SAngle::_Pi;
    #endif

    const Plane REFERENCE_OPERAND = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);                          // _
    Plane OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);  // \_
    Plane OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = Plane(-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_0); // /¨
    OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE = OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE.Normalize();
    OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE = OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE.Normalize();

	// [Execution]
    float_z fResult1UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_MORE_THAN_HALF_CIRCUMFERENCE);
    float_z fResult2UT = REFERENCE_OPERAND.AngleBetween(OPERAND_SEPARATED_LESS_THAN_HALF_CIRCUMFERENCE);

    // [Verification]
    BOOST_CHECK( SFloat::IsLessThan(fResult1UT, HALF_CIRCUMFERENCE_ANGLE) );
    BOOST_CHECK( SFloat::IsLessThan(fResult2UT, HALF_CIRCUMFERENCE_ANGLE) );
}

/// <summary>
/// Checks that the operation returns a different angle when the plane is not normalized.
/// </summary>
ZTEST_CASE ( AngleBetween3_ReturnsDifferentAngleWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    const Plane NOT_NORMALIZED_PLANE = Plane(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();
    const Plane PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);

	// [Execution]
    float_z fResultWhenNormalized = NORMALIZED_PLANE.AngleBetween(PLANE);
    float_z fResultWhenNotNormalized = NOT_NORMALIZED_PLANE.AngleBetween(PLANE);

    // [Verification]
    BOOST_CHECK( SFloat::AreNotEqual(fResultWhenNormalized, fResultWhenNotNormalized) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
ZTEST_CASE ( AngleBetween3_AssertionFailsWhenOnePlaneIsNull_Test )
{
    // [Preparation]
    const Plane NOT_NULL_PLANE = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_0);
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        NOT_NULL_PLANE.AngleBetween(NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NULL_PLANE.AngleBetween(NOT_NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

// [TODO] Thund: Add a test to check the returned value when assertions are disabled

/// <summary>
/// Checks that a common point is correctly projected on a common plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointProjection_ACommonPointIsProjectedOnACommonPlaneCorrectly_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_0, SFloat::_2, SFloat::_0, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    PLANE = PLANE.Normalize();
    const float_z EXPECTED_POINT_COMPONENTS[] = {SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1};
    T EXPECTED_POINT = T(EXPECTED_POINT_COMPONENTS);

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

/// <summary>
/// Checks that a point that belongs to the plane remains the same.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointProjection_PointsThatBelongToPlaneRemainsTheSame_Test, TVectorTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const float_z POINT_COMPONENTS[] = {PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    T EXPECTED_POINT = POINT;

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

/// <summary>
/// Checks that a common point that is placed in the "negative" side of the space divided by the plane is correctly projected.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointProjection_PointsBehindThePlaneAreCorrectlyProjected_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_0, -SFloat::_2, SFloat::_0, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const float_z EXPECTED_POINT_COMPONENTS[] = {-SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_1};
    T EXPECTED_POINT = T(EXPECTED_POINT_COMPONENTS);

	// [Execution]
    T vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPoint == EXPECTED_POINT );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointProjection_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointProjection(POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the result is different when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointProjection_ResultIsDifferentWhenPlaneIsNotNormalized_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_1, -SFloat::_2, SFloat::_3, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Plane NORMALIZED_PLANE = PLANE.Normalize();

	// [Execution]
    T vProjectedPointOnNonNormalizedPlane = PLANE.PointProjection(POINT);
    T vProjectedPointOnNormalizedPlane = NORMALIZED_PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK( vProjectedPointOnNonNormalizedPlane != vProjectedPointOnNormalizedPlane );
}

/// <summary>
/// Checks that the W component of the point is not affected by the operation.
/// </summary>
ZTEST_CASE ( PointProjection_ItDoesNotAffectWComponent_Test )
{
    // [Preparation]
    const Vector4 POINT = Vector4(SFloat::_4, -SFloat::_8, SFloat::_3, SFloat::_9);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

	// [Execution]
    Vector4 vProjectedPoint = PLANE.PointProjection(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(vProjectedPoint.w, POINT.w);
}

/// <summary>
/// Checks that it returns True when a common point that belongs to the plane is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsTrueWhenUsingACommonPointThatBelongsToThePlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const bool EXPECTED_VALUE = true;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns False when a point that is in the "positive" side of the plane is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenUsingACommonPointThatIsInThePositiveSideOfThePlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns False when a point that is in the "negative" side of the plane is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_ReturnsFalseWhenUsingACommonPointThatIsInTheNegativeSideOfThePlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const bool EXPECTED_VALUE = false;

	// [Execution]
    bool bResult = PLANE.Contains(POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult, EXPECTED_VALUE );
}

/// <summary>
/// Checks that it returns the same result either the plane is normalized or not .
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_PlaneNormalizationDoesNotAffectResult_Test, TVectorTypes )
{
    // [Preparation]
    const float_z CONTAINED_POINT_COMPONENTS[] = {(float_z)2.1250, (float_z)0.8750, SFloat::_3, SFloat::_1};
    const float_z NOT_CONTAINED_POINT_COMPONENTS[] = {SFloat::_2, SFloat::_1, SFloat::_3, SFloat::_1};
    const T CONTAINED_POINT = T(CONTAINED_POINT_COMPONENTS);
    const T NOT_CONTAINED_POINT = T(NOT_CONTAINED_POINT_COMPONENTS);
    const Plane NOT_NORMALIZED_PLANE = Plane(-SFloat::_8, SFloat::_8, SFloat::_0, SFloat::_10);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    bool bResultNotContainedNorNormalized = NOT_NORMALIZED_PLANE.Contains(NOT_CONTAINED_POINT);
    bool bResultNotContainedButNormalized = NORMALIZED_PLANE.Contains(NOT_CONTAINED_POINT);
    bool bResultContainedButNotNormalized = NOT_NORMALIZED_PLANE.Contains(CONTAINED_POINT);
    bool bResultContainedAndNormalized = NORMALIZED_PLANE.Contains(CONTAINED_POINT);

    // [Verification]
    BOOST_CHECK_EQUAL( bResultNotContainedNorNormalized, bResultNotContainedButNormalized );
    BOOST_CHECK_EQUAL( bResultContainedButNotNormalized, bResultContainedAndNormalized );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Contains_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointProjection(POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the W component of the point doesn't affect the result.
/// </summary>
ZTEST_CASE ( Contains_WComponentDoesNotAffectTheResult_Test )
{
    // [Preparation]
    const Vector4 POINT1 = Vector4(SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1);
    const Vector4 POINT2 = Vector4(SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_10);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

    // [Execution]
    bool bResult1 = PLANE.Contains(POINT1);
    bool bResult2 = PLANE.Contains(POINT2);

    // [Verification]
    BOOST_CHECK_EQUAL( bResult1, bResult2 );
}

/// <summary>
/// Checks that the length of a non-normalized plane is correctly calculated.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsCorrectLengthFromNonNormalizedPlane_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_LENGTH = sqrt_z((float_z)14.0);

	// [Execution]
    float_z fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals 1 when the plane is normalized.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsOneWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals zero when the plane is null.
/// </summary>
ZTEST_CASE ( GetLength_ReturnsZeroWhenPlaneIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane::GetNullPlane();
    const float_z EXPECTED_LENGTH = SFloat::_0;

	// [Execution]
    float_z fLength = PLANE.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the D component of the plane doesn't affect the result.
/// </summary>
ZTEST_CASE ( GetLength_DComponentDoesNotAffectResult_Test )
{
    // [Preparation]
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_5);

	// [Execution]
    float_z fLength1 = PLANE1.GetLength();
    float_z fLength2 = PLANE2.GetLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the length of a non-normalized plane is correctly calculated.
/// </summary>
ZTEST_CASE ( GetSquaredLength_ReturnsCorrectLengthFromNonNormalizedPlane_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const float_z EXPECTED_LENGTH = (float_z)14.0;

	// [Execution]
    float_z fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals 1 when the plane is normalized.
/// </summary>
ZTEST_CASE ( GetSquaredLength_ReturnsOneWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const float_z EXPECTED_LENGTH = SFloat::_1;

	// [Execution]
    float_z fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the length equals zero when the plane is null.
/// </summary>
ZTEST_CASE ( GetSquaredLength_ReturnsZeroWhenPlaneIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane::GetNullPlane();
    const float_z EXPECTED_LENGTH = SFloat::_0;

	// [Execution]
    float_z fLength = PLANE.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength, EXPECTED_LENGTH) );
}

/// <summary>
/// Checks that the D component of the plane doesn't affect the result.
/// </summary>
ZTEST_CASE ( GetSquaredLength_DComponentDoesNotAffectResult_Test )
{
    // [Preparation]
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1);
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_5);

	// [Execution]
    float_z fLength1 = PLANE1.GetSquaredLength();
    float_z fLength2 = PLANE2.GetSquaredLength();

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fLength1, fLength2) );
}

/// <summary>
/// Checks that the normal is correctly calculated for a common plane.
/// </summary>
ZTEST_CASE ( GetNormal_NormalIsCorrectlyComputedWhenUsingCommonPlane_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Vector3 EXPECTED_NORMAL(SFloat::_1, SFloat::_2, SFloat::_3);

	// [Execution]
    Vector3 vNormal = PLANE.GetNormal();

    // [Verification]
    BOOST_CHECK( vNormal == EXPECTED_NORMAL );
}

/// <summary>
/// Checks that the normal is not normalized when the plane is not normalized.
/// </summary>
ZTEST_CASE ( GetNormal_ItIsNotNormalizedWhenPlaneIsNotNormalized_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    Vector3 vNormal = PLANE.GetNormal();
    Vector3 vNormalizedNormal = vNormal.Normalize();

    // [Verification]
    BOOST_CHECK( vNormal != vNormalizedNormal );
}

/// <summary>
/// Checks that the normal is normalized when the plane is normalized.
/// </summary>
ZTEST_CASE ( GetNormal_ItIsNormalizedWhenPlaneIsNormalized_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();

	// [Execution]
    Vector3 vNormal = PLANE.GetNormal();
    Vector3 vNormalizedNormal = vNormal.Normalize();

    // [Verification]
    BOOST_CHECK( vNormal == vNormalizedNormal );
}

/// <summary>
/// Checks that it's correctly calculated when a common point and a common plane are used.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointDistance_CorrectlyCalculatedWhenUsingCommonPointAndPlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_DISTANCE = SFloat::_3;
    const float_z POINT_COMPONENTS[] = {-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0};
    T POINT = T(POINT_COMPONENTS);
    POINT = POINT.Normalize() * EXPECTED_DISTANCE;
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

	// [Execution]
    float_z fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that the distance is always positive, even when the point is in the "negative" side of the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointDistance_DistanceIsPositiveWhenPointIsInTheNegativeSideOfPlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_DISTANCE = SFloat::_3;
    const float_z POINT_COMPONENTS[] = {SFloat::_1, -SFloat::_1, SFloat::_0, SFloat::_0};
    T POINT = T(POINT_COMPONENTS);
    POINT = POINT.Normalize() * EXPECTED_DISTANCE;
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

	// [Execution]
    float_z fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that it returns zero when the point belongs to the plane.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointDistance_ReturnsZeroWhenPointBelongsToThePlane_Test, TVectorTypes )
{
    // [Preparation]
    const float_z EXPECTED_DISTANCE = SFloat::_0;
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();
    const float_z POINT_COMPONENTS[] = {PLANE.a * -PLANE.d, PLANE.b * -PLANE.d, PLANE.c * -PLANE.d, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

	// [Execution]
    float_z fDistance = PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistance, EXPECTED_DISTANCE) );
}

/// <summary>
/// Checks that the result is the same when the plane is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointDistance_ResultIsTheSameWhenPlaneIsNotNormalized_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane NOT_NORMALIZED_PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    float_z fDistance1 = NOT_NORMALIZED_PLANE.PointDistance(POINT);
    float_z fDistance2 = NORMALIZED_PLANE.PointDistance(POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(fDistance1, fDistance2) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( PointDistance_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.PointDistance(POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the W component of the point doesn't affect the result.
/// </summary>
ZTEST_CASE ( PointDistance_WComponentDoesNotAffectTheResult_Test )
{
    // [Preparation]
    const float_z POINT_COMPONENTS1[] = {SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_1};
    const float_z POINT_COMPONENTS2[] = {SFloat::_1, SFloat::_1, SFloat::_3, SFloat::_10};
    const Vector4 POINT1 = Vector4(POINT_COMPONENTS1);
    const Vector4 POINT2 = Vector4(POINT_COMPONENTS2);
    const Plane PLANE = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

	// [Execution]
    float_z fResult1 = PLANE.PointDistance(POINT1);
    float_z fResult2 = PLANE.PointDistance(POINT2);

    // [Verification]
    BOOST_CHECK_EQUAL( fResult1, fResult2 );
}

/// <summary>
/// Checks that the output point is not changed when the 3 planes coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenThreePlanesCoincide_Test, TVectorTypes )
{
    //
    //       |
    //       |
    //       |--->
    //       |
    //       | x3
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = PLANE1;

	// [Execution]
    T vIntersection = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK( vIntersection == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 3 planes coincide.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenThreePlanesCoincide_Test, TVectorTypes )
{
    //
    //       |
    //       |
    //       |--->
    //       |
    //       | x3
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = PLANE1;

	// [Execution]
    T vIntersection;
    EIntersections eResult = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other intersects.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesCoincideAndTheOtherIntersects_Test, TVectorTypes )
{
    //
    //       |         /
    //       |        /
    //       |--->   /
    //       |      /
    //       | x2  /
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = Plane(SFloat::_3, SFloat::_2, SFloat::_1, SFloat::_4).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other intersects.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenTwoPlanesCoincideAndTheOtherIntersects_Test, TVectorTypes )
{
    //
    //       |         /
    //       |        /
    //       |--->   /
    //       |      /
    //       | x2  /
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = Plane(SFloat::_3, SFloat::_2, SFloat::_1, SFloat::_4).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other is parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesCoincideAndTheOtherIsParallel_Test, TVectorTypes )
{
    //
    //       |        |
    //       |        |
    //       |--->    |--->
    //       |        |
    //       | x2     |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other is parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTwoPlanesCoincideAndTheOtherIsParallel_Test, TVectorTypes )
{
    //
    //       |        |
    //       |        |
    //       |--->    |--->
    //       |        |
    //       | x2     |
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = PLANE1;
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when 2 planes coincide and the other is parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesAreParallel_Test, TVectorTypes )
{
    //
    //       |        |       |
    //       |        |       |
    //       |--->    |--->   |--->
    //       |        |       |
    //       |        |       |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5).Normalize();
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_6).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 2 planes coincide and the other is parallel.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneTheThreePlanesAreParallel_Test, TVectorTypes )
{
    //
    //       |        |       |
    //       |        |       |
    //       |--->    |--->   |--->
    //       |        |       |
    //       |        |       |
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_5).Normalize();
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_6).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when the three planes intersect but don't share one single point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesIntersectButNotShareASinglePoint_Test, TVectorTypes )
{
    //
    //          /\
    //         /  \
    //        /    \
    //      _/______\_
    //      /        \
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE3 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the three planes intersect but don't share one single point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTheThreePlanesIntersectButNotShareASinglePoint_Test, TVectorTypes )
{
    //
    //          /\
    //         /  \
    //        /    \
    //      _/______\_
    //      /        \
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Plane PLANE1 = Plane(-SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_1, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE3 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_0).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when two of the planes are parallel and intersect with the third one.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTwoPlanesAreParallelAndIntersectTheOther_Test, TVectorTypes )
{
    //
    //       |        |
    //       |-->     |-->
    //       |    ^   |
    //      _|____|___|____
    //       |        |
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_2).Normalize();
    const Plane PLANE3 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_3).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when two of the planes are parallel and intersect with the third one.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsNoneWhenTwoPlanesAreParallelAndIntersectTheOther_Test, TVectorTypes )
{
    //
    //       |        |
    //       |-->     |-->
    //       |    ^   |
    //      _|____|___|____
    //       |        |
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_None;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_0, SFloat::_0, SFloat::_2).Normalize();
    const Plane PLANE3 = Plane(SFloat::_0, SFloat::_1, SFloat::_0, SFloat::_3).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is correctly calculated when the 3 planes coincide in one point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointIsCorrectlyCalculatedWhenTheThreePlanesShareOnePoint_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //
    const float_z POINT_COMPONENTS[] = {SFloat::_2, -SFloat::_4, SFloat::_3, SFloat::_0};
    const T EXPECTED_POINT = T(POINT_COMPONENTS);
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_5, -SFloat::_9).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns One when the 3 planes coincide in one point.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsOneWhenTheThreePlanesShareOnePoint_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_One;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_5, -SFloat::_9).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is not changed when the 3 planes share one line.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointDoesNotChangeWhenTheThreePlanesShareOneLine_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x L
    //      /|\
    //

    // [Preparation]
    const T EXPECTED_POINT = T::GetNullVector();
    const Plane PLANE1 = Plane(SFloat::_1, -SFloat::_1, SFloat::_4, -SFloat::_5).Normalize();
    const Plane PLANE2 = Plane(SFloat::_3, SFloat::_1, SFloat::_1, -SFloat::_3).Normalize();
    const Plane PLANE3 = Plane(SFloat::_5, -SFloat::_1, SFloat::_9, (float_z)-13.0).Normalize();

	// [Execution]
    T vIntersection1 = EXPECTED_POINT;
    T vIntersection2 = EXPECTED_POINT;
    T vIntersection3 = EXPECTED_POINT;
    T vIntersection4 = EXPECTED_POINT;
    T vIntersection5 = EXPECTED_POINT;
    T vIntersection6 = EXPECTED_POINT;
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection1);
    PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection2);
    PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection3);
    PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection4);
    PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection5);
    PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection6);

    // [Verification]
    BOOST_CHECK( vIntersection1 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection2 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection3 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection4 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection5 == EXPECTED_POINT );
    BOOST_CHECK( vIntersection6 == EXPECTED_POINT );
}

/// <summary>
/// Checks that it returns Infinite when the 3 planes share one line.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnsInfiniteWhenTheThreePlanesShareOneLine_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x L
    //      /|\
    //

    // [Preparation]
    const EIntersections EXPECTED_RESULT = EIntersections::E_Infinite;
    const Plane PLANE1 = Plane(SFloat::_1, -SFloat::_1, SFloat::_4, -SFloat::_5).Normalize();
    const Plane PLANE2 = Plane(SFloat::_3, SFloat::_1, SFloat::_1, -SFloat::_3).Normalize();
    const Plane PLANE3 = Plane(SFloat::_5, -SFloat::_1, SFloat::_9, (float_z)-13.0).Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResult1 = PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);
    EIntersections eResult2 = PLANE2.IntersectionPoint(PLANE1, PLANE3, vIntersection);
    EIntersections eResult3 = PLANE3.IntersectionPoint(PLANE2, PLANE1, vIntersection);
    EIntersections eResult4 = PLANE1.IntersectionPoint(PLANE3, PLANE2, vIntersection);
    EIntersections eResult5 = PLANE2.IntersectionPoint(PLANE3, PLANE1, vIntersection);
    EIntersections eResult6 = PLANE3.IntersectionPoint(PLANE1, PLANE2, vIntersection);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
    BOOST_CHECK(eResult3 == EXPECTED_RESULT);
    BOOST_CHECK(eResult4 == EXPECTED_RESULT);
    BOOST_CHECK(eResult5 == EXPECTED_RESULT);
    BOOST_CHECK(eResult6 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the output point is the same even when at least one of the planes is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_OutputPointIsTheSameWhenPlanesAreNotNormalized_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane NOT_NORMALIZED_PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_5, -SFloat::_9);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    T vIntersectionNormalizedPlane;
    T vIntersectionNotNormalizedPlane;

    PLANE1.IntersectionPoint(PLANE2, NORMALIZED_PLANE, vIntersectionNormalizedPlane);
    PLANE1.IntersectionPoint(PLANE2, NOT_NORMALIZED_PLANE, vIntersectionNotNormalizedPlane);

    // [Verification]
    BOOST_CHECK( vIntersectionNormalizedPlane == vIntersectionNotNormalizedPlane );
}

/// <summary>
/// Checks that the returned value is the same even when at least one of the planes is not normalized.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_ReturnedValueIsTheSameWhenPlanesAreNotNormalized_Test, TVectorTypes )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane NOT_NORMALIZED_PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_5, -SFloat::_9);
    const Plane NORMALIZED_PLANE = NOT_NORMALIZED_PLANE.Normalize();

	// [Execution]
    T vIntersection;
    EIntersections eResultNormalizedPlane = PLANE1.IntersectionPoint(PLANE2, NOT_NORMALIZED_PLANE, vIntersection);
    EIntersections eResultNotNormalizedPlane = PLANE1.IntersectionPoint(PLANE2, NORMALIZED_PLANE, vIntersection);

    // [Verification]
    BOOST_CHECK(eResultNormalizedPlane == eResultNotNormalizedPlane);
}

/// <summary>
/// Checks that the W component of the output point doesn't ever change.
/// </summary>
ZTEST_CASE ( IntersectionPoint_WComponentOfOutputPointIsNeverChanged_Test )
{
    //
    //       |  /
    //     \ | /
    //      \|/
    //       x P
    //      /|\
    //

    // [Preparation]
    const float_z EXPECTED_W = SFloat::_5;
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane PLANE3 = Plane(SFloat::_1, SFloat::_2, SFloat::_5, -SFloat::_9).Normalize();
    Vector4 vIntersection;
    vIntersection.w = EXPECTED_W;

	// [Execution]
    PLANE1.IntersectionPoint(PLANE2, PLANE3, vIntersection);

    // [Verification]
    BOOST_CHECK_EQUAL(vIntersection.w, EXPECTED_W);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( IntersectionPoint_AssertionFailsWhenOnePlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const Plane PLANE1 = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane PLANE2 = Plane(SFloat::_1, SFloat::_2, SFloat::_3, -SFloat::_3).Normalize();
    const Plane NULL_PLANE = Plane::GetNullPlane();
    T POINT;
    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        PLANE1.IntersectionPoint(PLANE2, NULL_PLANE, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        PLANE1.IntersectionPoint(NULL_PLANE, PLANE2, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    bool bAssertionFailed3 = false;

    try
    {
        NULL_PLANE.IntersectionPoint(PLANE2, PLANE1, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed3 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed3, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that it returns "positive side" when the other plane is parallel and resides in the positive side of the space division defined by the resident plane.
/// </summary>
ZTEST_CASE( SpaceRelation_ReturnsPositiveSideWhenTheOtherPlaneIsParallelAndIsInThePositiveSide_Test )
{
    //     A        B
    //     |        |
    //     |-->     |-->
    //     |        |
    //

    // [Preparation]
    const Plane PLANE_A = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_1).Normalize();
    const Plane PLANE_B = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2).Normalize();
    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_PositiveSide;

	// [Execution]
    ESpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "negative side" when the other plane is parallel and resides in the negative side of the space division defined by the resident plane.
/// </summary>
ZTEST_CASE( SpaceRelation_ReturnsNegativeSideWhenTheOtherPlaneIsParallelAndIsInTheNegativeSide_Test )
{
    //     B        A
    //     |        |
    //     |-->     |-->
    //     |        |
    //

    // [Preparation]
    const Plane PLANE_A = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Plane PLANE_B = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_2).Normalize();
    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_NegativeSide;

	// [Execution]
    ESpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "both sides" when planes intersect.
/// </summary>
ZTEST_CASE( SpaceRelation_ReturnsBothSidesWhenPlanesIntersect_Test )
{
    //     A B
    //     |/
    //     |-->
    //    /|
    //

    // [Preparation]
    const Plane PLANE_A = Plane(SFloat::_1, SFloat::_1, SFloat::_1, SFloat::_3).Normalize();
    const Plane PLANE_B = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_BothSides;

	// [Execution]
    ESpaceRelation eResult1 = PLANE_A.SpaceRelation(PLANE_B);
    ESpaceRelation eResult2 = PLANE_B.SpaceRelation(PLANE_A);

    // [Verification]
    BOOST_CHECK(eResult1 == EXPECTED_RESULT);
    BOOST_CHECK(eResult2 == EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns "contained" when planes coincide.
/// </summary>
ZTEST_CASE( SpaceRelation_ReturnsContainedWhenPlanesCoincide_Test )
{
    //    A&B
    //     |
    //     |-->>
    //     |
    //

    // [Preparation]
    const Plane PLANE_A = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE_B = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const ESpaceRelation EXPECTED_RESULT = ESpaceRelation::E_Contained;

	// [Execution]
    ESpaceRelation eResult = PLANE_A.SpaceRelation(PLANE_B);

    // [Verification]
    BOOST_CHECK(eResult == EXPECTED_RESULT);
}

/// <summary>
/// Checks that the result is different when one of the planes is not normalized.
/// </summary>
ZTEST_CASE( SpaceRelation_ResultIsDifferentWhenOnePlaneIsNotNormalized_Test )
{
    // [Preparation]
    const Plane PLANE_NORMALIZED = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4).Normalize();
    const Plane PLANE_NOTNORMALIZED = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);

	// [Execution]
    ESpaceRelation eResult1 = PLANE_NORMALIZED.SpaceRelation(PLANE_NORMALIZED);
    ESpaceRelation eResult2 = PLANE_NORMALIZED.SpaceRelation(PLANE_NOTNORMALIZED);

    // [Verification]
    BOOST_CHECK(eResult1 != eResult2);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when one of the planes is null.
/// </summary>
ZTEST_CASE( SpaceRelation_AssertionFailsWhenOnePlaneIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_1, SFloat::_1, -SFloat::_1).Normalize();
    const Plane NULL_PLANE = Plane::GetNullPlane();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed1 = false;

    try
    {
        PLANE.SpaceRelation(NULL_PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed1 = true;
    }

    bool bAssertionFailed2 = false;

    try
    {
        NULL_PLANE.SpaceRelation(PLANE);
    }
    catch(const AssertException&)
    {
        bAssertionFailed2 = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed1, ASSERTION_FAILED);
    BOOST_CHECK_EQUAL(bAssertionFailed2, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary rotation matrix.
/// </summary>
ZTEST_CASE ( Rotate1_PlaneIsCorrectlyTransformedByCommonRotationMatrix_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Plane EXPECTED_RESULT = Plane( (float_z) 0.15430334996209197,
                                           (float_z)-0.87287156094396956,
                                           (float_z)-0.46291004988627582,
                                           PLANE.d );

    // Results calculated with DirectX SDK
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXMATRIX rot;
    // D3DXMatrixRotationYawPitchRoll(&rot, fYaw, fPitch, fRoll);
    // D3DXVECTOR3 vRot(1, 2, 4);
    // D3DXVec3Normalize(&vRot, &vRot);
    // D3DXVec3TransformNormal(&vRot, &vRot, &rot);

	// [Execution]
    Plane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Rotate1_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation matrix is null.
/// </summary>
ZTEST_CASE ( Rotate1_PlaneIsNullWhenRotationMatrixIsNull_Test )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const RotationMatrix3x3 NULL_MATRIX = RotationMatrix3x3(Matrix3x3::GetNullMatrix());

    const Plane EXPECTED_RESULT = Plane(SFloat::_0, SFloat::_0, SFloat::_0, PLANE.d);

	// [Execution]
    Plane planeUT = PLANE.Rotate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary quaternion.
/// </summary>
ZTEST_CASE ( Rotate2_PlaneIsCorrectlyTransformedByCommonQuaternion_Test )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Quaternion TRANSFORMATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);

    const Plane EXPECTED_RESULT = Plane( (float_z)-0.77151674981045959,
                                           (float_z)-0.46291004988627560,
                                           (float_z)-0.43643578047198500,
                                           PLANE.d );

    // Results have been obtained by using DirectX SDK
    // D3DXQUATERNION qRot, qVector, qConjugate;
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXQuaternionRotationYawPitchRoll(&qRot, fYaw, fPitch, fRoll);
    // D3DXQuaternionNormalize(&qRot, &qRot);
    // D3DXQuaternionConjugate(&qConjugate, &qRot);
    // D3DXVECTOR3 vVector(1, 2, 4);
    // D3DXVec3Normalize(&vVector, &vVector);
    // qVector.x = vVector.x; qVector.y = vVector.y; qVector.z = vVector.z; qVector.w = 0;
    // D3DXQuaternionMultiply(&qVector, &qRot, &qVector);
    // D3DXQuaternionMultiply(&qVector, &qVector, &qConjugate);

	// [Execution]
    Plane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity quaternion.
/// </summary>
ZTEST_CASE ( Rotate2_PlaneDoesNotChangeWhenTransformedByIdentityQuaternion_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion TRANSFORMATION = Quaternion::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Rotate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the quaternion is null.
/// </summary>
ZTEST_CASE ( Rotate2_PlaneIsNullWhenQuaternionIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const Plane EXPECTED_RESULT = Plane(SFloat::_0, SFloat::_0, SFloat::_0, PLANE.d);

	// [Execution]
    Plane planeUT = PLANE.Rotate(NULL_QUATERNION);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary scale matrix.
/// </summary>
ZTEST_CASE ( Scale1_PlaneIsCorrectlyScaledByCommonScaleMatrix_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = Plane((float_z)0.70224688317678341, (float_z)0.11704114719613057, (float_z)-0.70224688317678341, (float_z)0.87780860397097937);

	// [Execution]
    Plane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE ( Scale1_PlaneDoesNotChangeWhenScaledByIdentityMatrix_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE.Normalize();

	// [Execution]
    Plane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE ( Scale1_AssertionFailsWhenPlaneIsNull_Test )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3::GetIdentity();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(TRANSFORMATION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the scale matrix is null.
/// </summary>
ZTEST_CASE ( Scale1_AssertionFailsWhenScaleMatrixIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 NULL_MATRIX = ScalingMatrix3x3(Matrix3x3::GetNullMatrix());

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(NULL_MATRIX);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary vector.
/// </summary>
ZTEST_CASE ( Scale2_PlaneIsCorrectlyScaledByCommonVector_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = Plane((float_z)0.70224688317678341, (float_z)0.11704114719613057, (float_z)-0.70224688317678341, (float_z)0.87780860397097937);

	// [Execution]
    Plane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
ZTEST_CASE ( Scale2_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3::GetVectorOfOnes();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Scale(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE ( Scale2_AssertionFailsWhenPlaneIsNull_Test )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const Vector3 TRANSFORMATION = Vector3::GetVectorOfOnes();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(TRANSFORMATION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
ZTEST_CASE ( Scale2_AssertionFailsWhenVectorIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(NULL_VECTOR);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by arbitrary scaling values.
/// </summary>
ZTEST_CASE ( Scale3_PlaneIsCorrectlyScaledByCommonScalingValues_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const float_z SCALE_X = SFloat::_0_25;
    const float_z SCALE_Y = SFloat::_3;
    const float_z SCALE_Z = -SFloat::_1;

    const Plane EXPECTED_RESULT = Plane((float_z)0.70224688317678341, (float_z)0.11704114719613057, (float_z)-0.70224688317678341, (float_z)0.87780860397097937);

	// [Execution]
    Plane planeUT = PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when scale values equal one.
/// </summary>
ZTEST_CASE ( Scale3_PlaneDoesntChangeWhenScaleValuesEqualOne_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE ( Scale3_AssertionFailsWhenPlaneIsNull_Test )
{
    // [Preparation]
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.Scale(SCALE_X, SCALE_Y, SCALE_Z);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
ZTEST_CASE ( Scale3_AssertionFailsWhenVectorIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const float_z ZERO_SCALE_X = SFloat::_0;
    const float_z ZERO_SCALE_Y = SFloat::_0;
    const float_z ZERO_SCALE_Z = SFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Scale(ZERO_SCALE_X, ZERO_SCALE_Y, ZERO_SCALE_Z);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_PlaneIsCorrectlyTranslatedByCommonTranslationMatrix_Test, TMatrixTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSFORMATION = TranslationMatrix<T>(SFloat::_2, SFloat::_4, -SFloat::_6);

    const Plane EXPECTED_RESULT = Plane((float_z)0.21821789023599239, (float_z)0.43643578047198478, (float_z)0.87287156094396956, (float_z)4.1461399144838555);

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_VectorDoesNotChangeWhenTranslatedByIdentityMatrix_Test, TMatrixTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSFORMATION = TranslationMatrix<T>::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation matrix is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_PlaneDoesNotChangeWhenTranslationMatrixIsNull_Test, TMatrixTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> NULL_MATRIX = TranslationMatrix<T>(T::GetNullMatrix());

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(NULL_MATRIX);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector produced by the matrix is orthogonal to the plane's normal.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate1_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test, TMatrixTypes )
{

    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSFORMATION = TranslationMatrix<T>(-SFloat::_2, SFloat::_1, SFloat::_0);

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_PlaneIsCorrectlyTranslatedByCommonTranslationVector_Test, TVectorTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const float_z VECTOR_COMPONENTS[] = {SFloat::_2, SFloat::_4, -SFloat::_6, SFloat::_0};
    const T TRANSFORMATION = T(VECTOR_COMPONENTS);

    const Plane EXPECTED_RESULT = Plane((float_z)0.21821789023599239, (float_z)0.43643578047198478, (float_z)0.87287156094396956, (float_z)4.1461399144838555);

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_PlaneDoesNotChangeWhenTranslationVectorIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const T NULL_VECTOR = T::GetNullVector();

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(NULL_VECTOR);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector is orthogonal to the plane's normal.
/// </summary>
ZTEST_CASE_TEMPLATE ( Translate2_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test, TVectorTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_5).Normalize();
    const float_z VECTOR_COMPONENTS[] = {-SFloat::_2, SFloat::_1, SFloat::_0, SFloat::_0};
    const T TRANSFORMATION = T(VECTOR_COMPONENTS);

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by arbitrary translation values.
/// </summary>
ZTEST_CASE ( Translate3_PlaneIsCorrectlyTranslatedByCommonTranslationValues_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();

    const float_z TRANSLATION_X = SFloat::_2;
    const float_z TRANSLATION_Y = SFloat::_4;
    const float_z TRANSLATION_Z = -SFloat::_6;

    const Plane EXPECTED_RESULT = Plane((float_z)0.21821789023599239, (float_z)0.43643578047198478, (float_z)0.87287156094396956, (float_z)4.1461399144838555);

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when the translation values equal zero.
/// </summary>
ZTEST_CASE ( Translate3_PlaneDoesNotChangeWhenTranslationValuesEqualZero_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();

    const float_z TRANSLATION_X = SFloat::_0;
    const float_z TRANSLATION_Y = SFloat::_0;
    const float_z TRANSLATION_Z = SFloat::_0;

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane does not change when the displacement vector is orthogonal to the plane's normal.
/// </summary>
ZTEST_CASE ( Translate3_PlaneDoesNotChangeWhenDisplacementVectorIsOrthogonalToPlaneNormal_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_0, SFloat::_5).Normalize();

    const float_z TRANSLATION_X = -SFloat::_2;
    const float_z TRANSLATION_Y = SFloat::_1;
    const float_z TRANSLATION_Z = SFloat::_0;

    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Translate(TRANSLATION_X, TRANSLATION_Y, TRANSLATION_Z);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_PlaneIsCorrectlyTransformedByCommonTransformationMatrix_Test, TMatrixTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSLATION = TranslationMatrix<T>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    // Note: The method was tested using translation only, rotation only and scale only, and the results match what expected (same as Translate, Rotate and Scale tests)
    const Plane EXPECTED_RESULT = Plane((float_z)-0.41380294430118403, (float_z)0.70224688317678341, (float_z)-0.57932412202165773, (float_z)-4.5795177722637330);

    // Results calculated using DirectX SDK
    // float_z fYaw = SAngle::_Pi;
    // float_z fPitch = SAngle::_HalfPi;
    // float_z fRoll = SAngle::_QuarterPi;
    // D3DXMATRIX rotation, translation, scaling, transformation;
    // D3DXMatrixRotationYawPitchRoll(&rotation, fYaw, fPitch, fRoll);
    // D3DXMatrixScaling(&scaling, SFloat::_0_25, SFloat::_3, -SFloat::_1);
    // D3DXMatrixTranslation(&translation, SFloat::_2, SFloat::_4, -SFloat::_6);
    // transformation = scaling * rotation * translation;
    //
    // D3DXPLANE planeNew;
    // D3DXPLANE plane(1,2,4,5);
    // D3DXPlaneNormalize(&plane, &plane);
    // D3DXMatrixInverse(&transformation, NULL, &transformation);
    // D3DXMatrixTranspose(&transformation, &transformation);
    // D3DXPlaneTransform(&planeNew, &plane, &transformation);
    // D3DXPlaneNormalize(&planeNew, &planeNew);

	// [Execution]
    Plane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test, TMatrixTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( Transform1_AssertionFailsWhenTransformationMatrixIsNull_Test, TMatrixTypes )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TransformationMatrix<T> NULL_TRANSFORMATION = T::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Transform(NULL_TRANSFORMATION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary space conversion matrix.
/// </summary>
ZTEST_CASE( Transform2_PlaneIsCorrectlyTransformedByCommonSpaceConversionMatrix_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    SpaceConversionMatrix CONVERSION = SpaceConversionMatrix();
    CONVERSION.SetViewSpaceMatrix(Vector3(SFloat::_1, SFloat::_2, SFloat::_3),
                                  Vector3(SFloat::_0, SFloat::_0, SFloat::_1),
                                  Vector3(SFloat::_0, SFloat::_1, SFloat::_0));

    // Note: The method was tested using translation only, rotation only and scale only, and the results match what expected (same as Translate, Rotate and Scale tests)
    const Plane EXPECTED_RESULT = Plane((float_z)0.19518001458970666, (float_z)-0.26024001945294228, (float_z)-0.94561085768930031, (float_z)4.8007935851918324);

    // Results calculated using DirectX SDK
    // D3DXMATRIX transformation;
    // D3DXVECTOR3 vEye(1, 2, 3);
    // D3DXVECTOR3 vUp(0, 0, 1);
    // D3DXVECTOR3 vAt(0, 1, 0);
    // D3DXMatrixLookAtLH(&transformation, &vEye, &vUp, &vAt);
    //
    // D3DXPLANE planeNew;
    // D3DXPLANE plane(1,2,4,5);
    // D3DXPlaneNormalize(&plane, &plane);
    // D3DXMatrixInverse(&transformation, NULL, &transformation);
    // D3DXMatrixTranspose(&transformation, &transformation);
    // D3DXPlaneTransform(&planeNew, &plane, &transformation);
    // D3DXPlaneNormalize(&planeNew, &planeNew);

	// [Execution]
    Plane planeUT = PLANE.Transform(CONVERSION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE( Transform2_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const SpaceConversionMatrix TRANSFORMATION = SpaceConversionMatrix::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.Transform(TRANSFORMATION);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the space conversion matrix is null.
/// </summary>
ZTEST_CASE( Transform2_AssertionFailsWhenMatrixIsNull_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const SpaceConversionMatrix NULL_TRANSFORMATION = SpaceConversionMatrix::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.Transform(NULL_TRANSFORMATION);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary quaternion and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneIsCorrectlyTransformedByCommonQuaternionAndPoint_Test, TVectorTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const Quaternion TRANSFORMATION = Quaternion(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Rotate(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity quaternion.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneDoesntChangeWhenTransformedByIdentityQuaternion_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion TRANSFORMATION = Quaternion::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation quaternion is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_PlaneIsNullWhenRotationQuaternionIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const Quaternion NULL_QUATERNION = Quaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0);

    const Plane EXPECTED_RESULT = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_9);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(NULL_QUATERNION, POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TVectorTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const T POINT = T::GetNullVector();

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Plane EXPECTED_RESULT = PLANE.Rotate(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary rotation matrix and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneIsCorrectlyTransformedByCommonRotationMatrixAndPoint_Test, TVectorTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Rotate(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneDoesNotChangeWhenTransformedByIdentityMatrix_Test, TVectorTypes )
{
    // [Preparation]

    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is nullified when the rotation matrix is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_PlaneIsNullWhenRotationMatrixIsNull_Test, TVectorTypes )
{
    // [Preparation]

    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_3, SFloat::_4);
    const RotationMatrix3x3 NULL_MATRIX = RotationMatrix3x3(Matrix3x3::GetNullMatrix());

    const Plane EXPECTED_RESULT = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_9);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(NULL_MATRIX, POINT);

    // [Verification]
    BOOST_CHECK_EQUAL(planeUT.a, EXPECTED_RESULT.a);
    BOOST_CHECK_EQUAL(planeUT.b, EXPECTED_RESULT.b);
    BOOST_CHECK_EQUAL(planeUT.c, EXPECTED_RESULT.c);
    BOOST_CHECK_EQUAL(planeUT.d, EXPECTED_RESULT.d);
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( RotateWithPivot2_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TVectorTypes )
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const RotationMatrix3x3 TRANSFORMATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const T POINT = T::GetNullVector();

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Plane EXPECTED_RESULT = PLANE.Rotate(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.RotateWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary vector and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3::GetVectorOfOnes();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane NULL_PLANE = Plane::GetNullPlane();
    const Vector3 TRANSFORMATION = Vector3::GetVectorOfOnes();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(TRANSFORMATION, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_AssertionFailsWhenVectorIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const Vector3 NULL_VECTOR = Vector3::GetNullVector();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(NULL_VECTOR, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by arbitrary scale values and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const float_z SCALE_X = SFloat::_0_25;
    const float_z SCALE_Y = SFloat::_3;
    const float_z SCALE_Z = -SFloat::_1;

    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(SCALE_X, SCALE_Y, SCALE_Z)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by scale values that equal one.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const float_z SCALE_X = SFloat::_1;
    const float_z SCALE_Y = SFloat::_1;
    const float_z SCALE_Z = SFloat::_1;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(SCALE_X, SCALE_Y, SCALE_Z, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the scale values equal zero.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_AssertionFailsWhenScaleValuesEqualZero_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const float_z ZERO_SCALE_X = SFloat::_0;
    const float_z ZERO_SCALE_Y = SFloat::_0;
    const float_z ZERO_SCALE_Z = SFloat::_0;

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(ZERO_SCALE_X, ZERO_SCALE_Y, ZERO_SCALE_Z, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot2_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary vector and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneIsCorrectlyScaledByCommonVectorAndPoint_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by a vector of ones.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneDoesNotChangeWhenScaledByAVectorOfOnes_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that an assertion fails when the plane is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_AssertionFailsWhenPlaneIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane NULL_PLANE = Plane(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_1);
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3::GetIdentity();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        NULL_PLANE.ScaleWithPivot(TRANSFORMATION, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the vector is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_AssertionFailsWhenVectorIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const ScalingMatrix3x3 NULL_MATRIX = ScalingMatrix3x3(Matrix3x3::GetNullMatrix());

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.ScaleWithPivot(NULL_MATRIX, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that the plane is correctly transformed by an arbitrary vector.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_PlaneIsCorrectlyScaledByCommonVector_Test, TVectorTypes )
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const T POINT = T(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const ScalingMatrix3x3 TRANSFORMATION = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Scale(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( ScaleWithPivot3_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TVectorTypes )
{
    // [Preparation]
    const T POINT = T::GetNullVector();
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const Vector3 TRANSFORMATION = Vector3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const Plane EXPECTED_RESULT = PLANE.Scale(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.ScaleWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Template method used by TransformWithPivot1_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template()
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSLATION = TranslationMatrix<T>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    const Plane EXPECTED_RESULT = PLANE.Translate(-POINT.x, -POINT.y, -POINT.z)
                                        .Transform(TRANSFORMATION)
                                        .Translate(POINT.x, POINT.y, POINT.z);

	// [Execution]
    Plane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks the plane is correctly transformed by an arbitrary translation matrix and an arbitrary point.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Test, TMatrixTypes )
{
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector3");
    TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template<T, Vector3>();
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector4");
    TransformWithPivot_PlaneIsCorrectlyTransformedByCommonTransformationMatrixAndPoint_Template<T, Vector4>();
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Template method used by TransformWithPivot1_AssertionFailsWhenTransformationMatrixIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template()
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>::GetIdentity();
    const Plane EXPECTED_RESULT = PLANE;

	// [Execution]
    Plane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that the plane doesn't change when it's transformed by an identity matrix.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Test, TMatrixTypes )
{
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector3");
    TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template<T, Vector3>();
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector4");
    TransformWithPivot_PlaneDoesntChangeWhenTransformedByIdentityMatrix_Template<T, Vector4>();
}

/// <summary>
/// Template method used by TransformWithPivot1_AssertionFailsWhenTransformationMatrixIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template()
{
    // [Preparation]
    const float_z POINT_COMPONENTS[] = {-SFloat::_3, SFloat::_1, SFloat::_2, SFloat::_1};
    const VectorType POINT = VectorType(POINT_COMPONENTS);
    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5);
    const TransformationMatrix<T> NULL_TRANSFORMATION = T::GetNullMatrix();

    const bool ASSERTION_FAILED = true;

	// [Execution]
    bool bAssertionFailed = false;

    try
    {
        PLANE.TransformWithPivot(NULL_TRANSFORMATION, POINT);
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL(bAssertionFailed, ASSERTION_FAILED);
}

/// <summary>
/// Checks that an assertion fails when the transformation matrix is null.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Test, TMatrixTypes )
{
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector3");
    TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template<T, Vector3>();
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector4");
    TransformWithPivot_AssertionFailsWhenTransformationMatrixIsNull_Template<T, Vector4>();
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Template method used by TransformWithPivot1_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test
/// using different vector types.
/// </summary>
template<class T, class VectorType>
void TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template()
{
    // [Preparation]
#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    const float_z EULER_ANGLE_X = SAngle::_HalfPi;
    const float_z EULER_ANGLE_Y = SAngle::_Pi;
    const float_z EULER_ANGLE_Z = SAngle::_QuarterPi;
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    const float_z EULER_ANGLE_X = SAngle::_90;
    const float_z EULER_ANGLE_Y = SAngle::_180;
    const float_z EULER_ANGLE_Z = SAngle::_45;
#endif

    const VectorType POINT = VectorType::GetNullVector();

    const Plane PLANE = Plane(SFloat::_1, SFloat::_2, SFloat::_4, SFloat::_5).Normalize();
    const TranslationMatrix<T> TRANSLATION = TranslationMatrix<T>(SFloat::_2, SFloat::_4, -SFloat::_6);
    const RotationMatrix3x3 ROTATION = RotationMatrix3x3(EULER_ANGLE_X, EULER_ANGLE_Y, EULER_ANGLE_Z);
    const ScalingMatrix3x3 SCALE = ScalingMatrix3x3(SFloat::_0_25, SFloat::_3, -SFloat::_1);

    const TransformationMatrix<T> TRANSFORMATION = TransformationMatrix<T>(TRANSLATION, ROTATION, SCALE);

    const Plane EXPECTED_RESULT = PLANE.Transform(TRANSFORMATION);

	// [Execution]
    Plane planeUT = PLANE.TransformWithPivot(TRANSFORMATION, POINT);

    // [Verification]
    BOOST_CHECK( SFloat::AreEqual(planeUT.a, EXPECTED_RESULT.a) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.b, EXPECTED_RESULT.b) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.c, EXPECTED_RESULT.c) );
    BOOST_CHECK( SFloat::AreEqual(planeUT.d, EXPECTED_RESULT.d) );
}

/// <summary>
/// Checks that using a null pivot produces the same result as when no pivot is used.
/// </summary>
ZTEST_CASE_TEMPLATE ( TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Test, TMatrixTypes )
{
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector3");
    TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template<T, Vector3>();
    BOOST_TEST_MESSAGE("ZMath/VectorType=Vector4");
    TransformWithPivot_ReturnsSameValueAsWithoutPivotWhenPivotIsNull_Template<T, Vector4>();
}

/// <summary>
/// Checks that the format of the returned string matches what's expected.
/// </summary>
ZTEST_CASE ( ToString_ReturnedFormatMatchesExpected_Test )
{
    // [Preparation]
    const Plane PLANE = Plane(SFloat::_0_25, (float_z)-0.000002, (float_z)40000.0, SFloat::_0 );

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("PL(0.25,-1.99999999e-06,40000,0)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("PL(0.25,-1.99999999e-06,40000,0)");
    #endif
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #if defined(Z_COMPILER_GCC) && (defined(Z_OS_LINUX) || defined(Z_OS_MAC)) // This is necessary due to a different implementation of the Standard Library when compiling with GCC on Linux or Mac
        string_z EXPECTED_STRING_FORM = Z_L("PL(0.25,-1.9999999999999999e-06,40000,0)");
    #else
        string_z EXPECTED_STRING_FORM = Z_L("PL(0.25,-1.9999999999999999e-06,40000,0)");
    #endif
#endif

	// [Execution]
    Plane planeUT = PLANE;
    string_z strStringForm = planeUT.ToString();

    // [Verification]
    BOOST_CHECK(strStringForm == EXPECTED_STRING_FORM);
}

// [TODO] Thund: Protected methods have not been tested yet, they were postponed

// End - Test Suite: Plane
ZTEST_SUITE_END()
