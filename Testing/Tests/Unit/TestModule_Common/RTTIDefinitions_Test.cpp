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

#include "RTTITestClasses.h"

using z::Test::InterfaceMock1;
using z::Test::DerivedFromInterfaceA;
using z::Test::DerivedFromInterfaceB;
using z::Test::InterfaceMock2;
using z::Test::DerivedFrom2Classes;


ZTEST_SUITE_BEGIN( RTTIDefinitions_TestSuite )


/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the pointed type.
/// </summary>
ZTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    DerivedFrom2Classes* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFromInterfaceA AncestorType;

	// [Execution]
    AncestorType* pResult = OBJECT->As<AncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination is a descendent of the pointed type.
/// </summary>
ZTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFrom2Classes DescendentType;

	// [Execution]
    DescendentType* pResult = OBJECT->As<DescendentType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is the same as object's type.
/// </summary>
ZTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef DerivedFromInterfaceA SameType;
    SameType* OBJECT = new SameType();
    
	// [Execution]
    SameType* pResult = OBJECT->As<SameType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the actual object's type.
/// </summary>
ZTEST_CASE ( As1_ReturnsExpectedPointerWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef InterfaceMock2 OtherBranchAncestorType;

	// [Execution]
    OtherBranchAncestorType* pResult = OBJECT->As<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns a null pointer when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
ZTEST_CASE ( As1_ReturnsNullWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFromInterfaceB OtherBranchType;

	// [Execution]
    OtherBranchType* pResult = OBJECT->As<OtherBranchType>();

    // [Verification]
    BOOST_CHECK(pResult == null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns null when the destination type is a descendent of the type of the object.
/// </summary>
ZTEST_CASE ( As1_ReturnsNullWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFrom2Classes DescendentOfObjectType;

	// [Execution]
    DescendentOfObjectType* pResult = OBJECT->As<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK(pResult == null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the pointed type.
/// </summary>
ZTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    const DerivedFrom2Classes* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFromInterfaceA AncestorType;

	// [Execution]
    const AncestorType* pResult = OBJECT->As<AncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination is a descendent of the pointed type.
/// </summary>
ZTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    const InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFrom2Classes DescendentType;

	// [Execution]
    const DescendentType* pResult = OBJECT->As<DescendentType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is the same as object's type.
/// </summary>
ZTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef DerivedFromInterfaceA SameType;
    const SameType* OBJECT = new SameType();
    
	// [Execution]
    const SameType* pResult = OBJECT->As<SameType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns the expected pointer when the destination type is an ancestor of the actual object's type.
/// </summary>
ZTEST_CASE ( As2_ReturnsExpectedPointerWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    const InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef InterfaceMock2 OtherBranchAncestorType;

	// [Execution]
    const OtherBranchAncestorType* pResult = OBJECT->As<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK(pResult != null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns a null pointer when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
ZTEST_CASE ( As2_ReturnsNullWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    const DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFromInterfaceB OtherBranchType;

	// [Execution]
    const OtherBranchType* pResult = OBJECT->As<OtherBranchType>();

    // [Verification]
    BOOST_CHECK(pResult == null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns null when the destination type is a descendent of the type of the object.
/// </summary>
ZTEST_CASE ( As2_ReturnsNullWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    const DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFrom2Classes DescendentOfObjectType;

	// [Execution]
    const DescendentOfObjectType* pResult = OBJECT->As<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK(pResult == null_z);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is an ancestor of the pointed type.
/// </summary>
ZTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsAncestor_Test )
{
    // [Preparation]
    DerivedFrom2Classes* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFromInterfaceA AncestorType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<AncestorType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination is a descendent of the pointed type.
/// </summary>
ZTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsDescendent_Test )
{
    // [Preparation]
    InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef DerivedFrom2Classes DescendentType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<DescendentType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is the same as object's type.
/// </summary>
ZTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsSameAsObjects_Test )
{
    // [Preparation]
    typedef DerivedFromInterfaceA SameType;
    SameType* OBJECT = new SameType();
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<SameType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns True when the destination type is an ancestor of the actual object's type.
/// </summary>
ZTEST_CASE ( Is_ReturnsTrueWhenDestinationTypeIsAncestorOfObjectNotPointer_Test )
{
    // [Preparation]
    InterfaceMock1* OBJECT = new DerivedFrom2Classes();
    typedef InterfaceMock2 OtherBranchAncestorType;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = OBJECT->Is<OtherBranchAncestorType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns False when the destination type belongs to a different branch in the class hierarchy.
/// </summary>
ZTEST_CASE ( Is_ReturnsFalseWhenDestinationTypeBelongsToDifferentHierarchyBranch_Test )
{
    // [Preparation]
    DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFromInterfaceB OtherBranchType;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OBJECT->Is<OtherBranchType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

/// <summary>
/// Checks that it returns False when the destination type is a descendent of the type of the object.
/// </summary>
ZTEST_CASE ( Is_ReturnsFalseWhenDestinationTypeIsDescendentOfObjectType_Test )
{
    // [Preparation]
    DerivedFromInterfaceA* OBJECT = new DerivedFromInterfaceA();
    typedef DerivedFrom2Classes DescendentOfObjectType;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = OBJECT->Is<DescendentOfObjectType>();

    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);

	// [Cleaning]
    delete OBJECT;
}

// End - Test Suite: InterfaceMock1
ZTEST_SUITE_END()
