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
#include <boost/mpl/list.hpp>

#include "../../testsystem/TestingExternalDefinitions.h"

#include "ZCommon/DataTypes/Type.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZCommon/Exceptions/AssertException.h"
#include "RTTITestClasses.h"

// Type used in some tests as a non-basic type nor string
struct NonBasicType
{
};
    
typedef boost::mpl::list<bool, u8_z, i8_z, u16_z, i16_z, u32_z, i32_z, u64_z, i64_z, f32_z, f64_z, string_z> TZTemplateBasicTypes;

    
ZTEST_SUITE_BEGIN( Type_TestSuite )

/// <summary>
/// Checks that every argument is correctly set to the class attributes.
/// </summary>
ZTEST_CASE ( Constructor_ValuesAreCorrectlySet_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME(Z_L("TYPE NAME"));

	// [Execution]
    Type type(EXPECTED_NAME);
    
    // [Verification]
    string_z strName = type.GetName();

    BOOST_CHECK(strName == EXPECTED_NAME);
}

/// <summary>
/// Checks that it returns True when instances are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsTrueWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME"));
    const Type& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME1"));
    const Type RIGHT_OPERAND(Z_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are not equal, even if their attributes are equal.
/// </summary>
ZTEST_CASE ( OperatorEquality_ReturnsFalseWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME"));
    const Type RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND == RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns False when instances are equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsFalseWhenInstancesAreEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME"));
    const Type& RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = false;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME1"));
    const Type RIGHT_OPERAND(Z_L("TYPE NAME2"));
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// Checks that it returns True when instances are not equal, even if their attributes are equal.
/// </summary>
ZTEST_CASE ( OperatorInequality_ReturnsTrueWhenInstancesAreNotEqualEvenIfAttributesAreEqual_Test )
{
    // [Preparation]
    const Type LEFT_OPERAND(Z_L("TYPE NAME"));
    const Type RIGHT_OPERAND = LEFT_OPERAND;
    const bool EXPECTED_RESULT = true;

	// [Execution]
    bool bResult = LEFT_OPERAND != RIGHT_OPERAND;
    
    // [Verification]
    BOOST_CHECK_EQUAL(bResult, EXPECTED_RESULT);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetName_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns8BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "u8";

	// [Execution]
    const Type* pTypePointer = Type::FindType<u8_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns8BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "i8";

	// [Execution]
    const Type* pTypePointer = Type::FindType<i8_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns16BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "u16";

	// [Execution]
    const Type* pTypePointer = Type::FindType<u16_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns16BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "i16";

	// [Execution]
    const Type* pTypePointer = Type::FindType<i16_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns32BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "u32";

	// [Execution]
    const Type* pTypePointer = Type::FindType<u32_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns32BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "i32";

	// [Execution]
    const Type* pTypePointer = Type::FindType<i32_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns64BitsUnsignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "u64";

	// [Execution]
    const Type* pTypePointer = Type::FindType<u64_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns64BitsSignedIntegerType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "i64";

	// [Execution]
    const Type* pTypePointer = Type::FindType<i64_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns32BitsFloatingPointType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "f32";

	// [Execution]
    const Type* pTypePointer = Type::FindType<f32_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns64BitsFloatingPointType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "f64";

	// [Execution]
    const Type* pTypePointer = Type::FindType<f64_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_Returns4x32BitsPackedFloatingPointType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "vf32";

	// [Execution]
    const Type* pTypePointer = Type::FindType<vf32_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_ReturnsStringType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "string";

	// [Execution]
    const Type* pTypePointer = Type::FindType<string_z>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

/// <summary>
/// Checks that it returns the right type name when calling FindType.
/// </summary>
ZTEST_CASE ( FindType1_ReturnsVoidType_Test )
{
    // [Preparation]
    const string_z EXPECTED_TYPE = "void";

	// [Execution]
    const Type* pTypePointer = Type::FindType<void>();
    string_z strType = pTypePointer->GetName();
    
    // [Verification]
    BOOST_CHECK(strType == EXPECTED_TYPE);
}

#if Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_DISABLED

/// <summary>
/// Checks that null pointer is returned when non basic type is passed.
/// </summary>
ZTEST_CASE ( FindType1_ReturnsNullPointerWithNonBasicType_Test )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;

	// [Execution]
    const Type* pTypePointer = Type::FindType<NonBasicType>();
    
    // [Verification]
    BOOST_CHECK(pTypePointer == NULL_POINTER);
}

#elif Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Assertion failed when passing zero elements as initial capacity.
/// </summary>
ZTEST_CASE ( FindType1_AssertionThrownWithNonBasicType_Test )
{
    // [Preparation]
    const bool ASSERTION_FAILED = true;

    // [Execution]
    bool bAssertionFailed = false;

    try
    {
        Type::FindType<NonBasicType>();
    }
    catch(const AssertException&)
    {
        bAssertionFailed = true;
    }

    // [Verification]
    BOOST_CHECK_EQUAL( bAssertionFailed, ASSERTION_FAILED );
}

#endif // Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT == Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS

/// <summary>
/// Checks that a valid type is found when using basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType2_ValidTypeIsFoundWhenUsingBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    T object;

    // [Execution]
    const Type* pType = Type::FindType(object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using custom types.
/// </summary>
ZTEST_CASE ( FindType2_ValidTypeIsNotFoundWhenUsingNonBasicTypes_Test )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    NonBasicType object;

    // [Execution]
    const Type* pType = Type::FindType(object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointerToNonConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    T object;

    // [Execution]
    const Type* pType = Type::FindType(&object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using null pointers to non-constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingNullPointerToNonConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    T* pObject = null_z;

    // [Execution]
    const Type* pType = Type::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to non-constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointersToPointerToNonConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    T object;
    T* pObject = &object;;
    T** ppObject = &pObject;

    // [Execution]
    const Type* pType = Type::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using pointers to non-constant custom types.
/// </summary>
ZTEST_CASE ( FindType3_ValidTypeIsNotFoundWhenUsingPointerToNonConstantNonBasicType_Test )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    NonBasicType object;

    // [Execution]
    const Type* pType = Type::FindType(&object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointerToConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    const T object = T();

    // [Execution]
    const Type* pType = Type::FindType(&object);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using null pointers to constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingNullPointerToConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    const T* pObject = null_z;

    // [Execution]
    const Type* pType = Type::FindType(pObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is found when using pointers to constant basic types or string.
/// </summary>
ZTEST_CASE_TEMPLATE ( FindType3_ValidTypeIsFoundWhenUsingPointersToPointerToConstantBasicTypesOrString_Test, TZTemplateBasicTypes )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    const T object = T();
    const T* pObject = &object;;
    const T** ppObject = &pObject;

    // [Execution]
    const Type* pType = Type::FindType(ppObject);

    // [Verification]
    BOOST_CHECK_NE(pType, NULL_POINTER);
}

/// <summary>
/// Checks that a valid type is not found when using pointers to constant custom types.
/// </summary>
ZTEST_CASE ( FindType3_ValidTypeIsNotFoundWhenUsingPointerToConstantNonBasicType_Test )
{
    // [Preparation]
    const Type* NULL_POINTER = null_z;
    const NonBasicType object = NonBasicType();

    // [Execution]
    const Type* pType = Type::FindType(&object);

    // [Verification]
    BOOST_CHECK_EQUAL(pType, NULL_POINTER);
}

// End - Test Suite: Type
ZTEST_SUITE_END()
