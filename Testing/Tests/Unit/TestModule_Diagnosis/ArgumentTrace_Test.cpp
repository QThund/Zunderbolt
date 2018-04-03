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

#include "ZDiagnosis/ArgumentTrace.h"

#include "ZCommon/DataTypes/EComparisonType.h"


// This struct is used as example of "custom type", not a InterfaceMock, not a basic type, not a string_z.
class CustomType
{
public:

    static const Type* GetTypeClass()
    {
        static const Type CUSTOM_TYPE("CustomTypeStatic");
        return &CUSTOM_TYPE;
    }

    const Type* GetTypeObject() const
    {
        static const Type CUSTOM_TYPE("CustomTypeNonStatic");
        return &CUSTOM_TYPE;
    }

    string_z ToString() const
    {
        return "CustomTypeValue";
    }

    i32_z i;
};


ZTEST_SUITE_BEGIN( ArgumentTrace_TestSuite )

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u8");
    const string_z EXPECTED_VALUE("123");
    u8_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u16");
    const string_z EXPECTED_VALUE("123");
    u16_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u32");
    const string_z EXPECTED_VALUE("123");
    u32_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u64");
    const string_z EXPECTED_VALUE("123");
    u64_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i8");
    const string_z EXPECTED_VALUE("123");
    i8_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i16");
    const string_z EXPECTED_VALUE("123");
    i16_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i32");
    const string_z EXPECTED_VALUE("123");
    i32_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i64");
    const string_z EXPECTED_VALUE("123");
    i64_z object = 123;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("f32");
    const string_z EXPECTED_VALUE("123.456001");
    f32_z object = 123.456f;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("f64");
    const string_z EXPECTED_VALUE("123.456");
    f64_z object = 123.456;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("bool");
    const string_z EXPECTED_VALUE("true");
    bool object = true;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_z.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("string");
    const string_z EXPECTED_VALUE("text");
    string_z object = "text";

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
ZTEST_CASE ( Constructor1_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("<Unknown type (size:");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value contains memory address.
/// </summary>
ZTEST_CASE ( Constructor2_TypeNameIsObtainedFromGetTypeObjectAndValueContainsMemoryAddress_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeNonStatic");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(object, TypeWithGetType());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is unknown and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor3_TypeNameIsUnknownAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("<Unknown type (size: ");
    const string_z EXPECTED_VALUE("CustomTypeValue");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(object, TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue == EXPECTED_VALUE;
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor4_TypeNameIsObtainedFromGetTypeObjectAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeNonStatic");
    const string_z EXPECTED_VALUE("CustomTypeValue");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(object, TypeWithGetType(), TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue == EXPECTED_VALUE;
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u8*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    u8_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u16*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    u16_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    u32_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("u64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    u64_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i8*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    i8_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i16*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    i16_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    i32_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("i64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    i64_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("f32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123.456001");
    f32_z object = 123.456f;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("f64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123.456");
    f64_z object = 123.456;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("bool*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("true");
    bool object = true;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_z.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("string*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("text");
    string_z object = "text";

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type void.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingVoid_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("void*");
    const string_z EXPECTED_VALUE1("0x");
    int object = 0;
    void* pObject = &object;

    // [Execution]
    ArgumentTrace trace(pObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0;
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME1("<Unknown type (size:");
    const string_z EXPECTED_NAME2(">*");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");

    CustomType object;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME1, EComparisonType::E_BinaryCaseSensitive) &&
                                         strTypeName.Contains(EXPECTED_NAME2, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to a basic type.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingNullPointerToBasicType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("bool*");
    const string_z EXPECTED_VALUE("<Null>");
    bool* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using pointer to pointer to a basic type.
/// </summary>
ZTEST_CASE ( Constructor5_TypeNameAndValueAreStoredWhenUsingPointerToPointerToBasicType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("bool**");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("true");
    bool object = true;
    bool* pObject = &object;
    bool** ppObject = &pObject;

    // [Execution]
    ArgumentTrace trace(ppObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.IndexOf(EXPECTED_VALUE1, 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value contains memory address.
/// </summary>
ZTEST_CASE ( Constructor6_TypeNameIsObtainedFromGetTypeObjectAndValueContainsMemoryAddress_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeNonStatic*");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(&object, TypeWithGetType());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeClass and value contains <Null>.
/// </summary>
ZTEST_CASE ( Constructor6_TypeNameOfPointerIsObtainedFromGetTypeClassAndValueContainsNull_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeStatic*");
    const string_z EXPECTED_VALUE("<Null>");
    CustomType* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject, TypeWithGetType());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is unknown and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor7_TypeNameIsUnknownAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("<Unknown type (size: 4)>*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("CustomTypeValue");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(&object, TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor8_TypeNameIsObtainedFromGetTypeObjectAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeNonStatic*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("CustomTypeValue");
    CustomType object;

    // [Execution]
    ArgumentTrace trace(&object, TypeWithGetType(), TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeClass and value contains <Null>.
/// </summary>
ZTEST_CASE ( Constructor8_TypeNameOfPointerIsObtainedFromGetTypeClassAndValueContainsNull_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("CustomTypeStatic*");
    const string_z EXPECTED_VALUE("<Null>");
    CustomType* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject, TypeWithGetType(), TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u8_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingU8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const u8*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const u8_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u16_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingU16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const u16*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const u16_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u32_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingU32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const u32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const u32_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type u64_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingU64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const u64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const u64_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i8_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingI8_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const i8*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const i8_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i16_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingI16_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const i16*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const i16_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i32_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingI32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const i32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const i32_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type i64_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingI64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const i64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123");
    const i64_z object = 123;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f32_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingF32_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const f32*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123.456001");
    const f32_z object = 123.456f;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type f64_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingF64_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const f64*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("123.456");
    const f64_z object = 123.456;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type bool.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingBool_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const bool*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("true");
    const bool object = true;

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type string_z.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const string*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("text");
    const string_z object = "text";

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using type void.
/// </summary>
ZTEST_CASE ( Constructor6_TypeNameAndValueAreStoredWhenUsingVoid_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const void*");
    const string_z EXPECTED_VALUE1("0x");
    const void* pObject = "text";

    // [Execution]
    ArgumentTrace trace(pObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0;
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a not recognized type.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingNotRecognizedType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME1("const <Unknown type (size:");
    const string_z EXPECTED_NAME2(">*");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");

    const CustomType object = CustomType();

    // [Execution]
    ArgumentTrace trace(&object);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME1, EComparisonType::E_BinaryCaseSensitive) &&
                                         strTypeName.Contains(EXPECTED_NAME2, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using a null pointer to a basic type.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingNullPointerToBasicType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const bool*");
    const string_z EXPECTED_VALUE("<Null>");
    const bool* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(strValue == EXPECTED_VALUE);
}

/// <summary>
/// Checks that the name of the type and the value are stored when using pointer to pointer to a basic type.
/// </summary>
ZTEST_CASE ( Constructor9_TypeNameAndValueAreStoredWhenUsingPointerToPointerToBasicType_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const bool**");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("true");
    const bool object = true;
    const bool* pObject = &object;
    const bool** ppObject = &pObject;

    // [Execution]
    ArgumentTrace trace(ppObject);

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.IndexOf(EXPECTED_VALUE1, 1U, EComparisonType::E_BinaryCaseSensitive) != string_z::PATTERN_NOT_FOUND &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(strTypeName == EXPECTED_NAME);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value contains memory address.
/// </summary>
ZTEST_CASE ( Constructor10_TypeNameIsObtainedFromGetTypeObjectAndValueContainsMemoryAddress_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const CustomTypeNonStatic*");
    const string_z EXPECTED_VALUE("<Unknown type at 0x");
    const CustomType object = CustomType();

    // [Execution]
    ArgumentTrace trace(&object, TypeWithGetType());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeClass and value contains <Null>.
/// </summary>
ZTEST_CASE ( Constructor10_TypeNameOfPointerIsObtainedFromGetTypeClassAndValueContainsNull_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const CustomTypeStatic*");
    const string_z EXPECTED_VALUE("<Null>");
    const CustomType* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject, TypeWithGetType());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is unknown and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor11_TypeNameIsUnknownAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const <Unknown type (size: 4)>*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("CustomTypeValue");
    const CustomType object = CustomType();

    // [Execution]
    ArgumentTrace trace(&object, TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName.Contains(EXPECTED_NAME, EComparisonType::E_BinaryCaseSensitive);
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeObject and value is obtained from ToString.
/// </summary>
ZTEST_CASE ( Constructor12_TypeNameIsObtainedFromGetTypeObjectAndValueIsObtainedFromToString_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const CustomTypeNonStatic*");
    const string_z EXPECTED_VALUE1("0x");
    const string_z EXPECTED_VALUE2("CustomTypeValue");
    const CustomType object = CustomType();

    // [Execution]
    ArgumentTrace trace(&object, TypeWithGetType(), TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.IndexOf(EXPECTED_VALUE1, EComparisonType::E_BinaryCaseSensitive) == 0 &&
                                      strValue.Contains(EXPECTED_VALUE2, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// Checks that the name of the type is obtained from GetTypeClass and value contains <Null>.
/// </summary>
ZTEST_CASE ( Constructor12_TypeNameOfPointerIsObtainedFromGetTypeClassAndValueContainsNull_Test )
{
    // [Preparation]
    const string_z EXPECTED_NAME("const CustomTypeStatic*");
    const string_z EXPECTED_VALUE("<Null>");
    const CustomType* pObject = null_z;

    // [Execution]
    ArgumentTrace trace(pObject, TypeWithGetType(), TypeWithToString());

    // [Verification]
    string_z strTypeName = trace.GetTypeName();
    string_z strValue = trace.GetValue();
    bool bTypeNameContainsExpectedText = strTypeName == EXPECTED_NAME;
    bool bValueContainsExpectedText = strValue.Contains(EXPECTED_VALUE, EComparisonType::E_BinaryCaseSensitive);
    BOOST_CHECK(bTypeNameContainsExpectedText);
    BOOST_CHECK(bValueContainsExpectedText);
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetTypeName_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}

/// <summary>
/// It is not necessary to test this method since it is just a getter.
/// </summary>
ZTEST_CASE ( GetValue_NotNecessaryToTest_Test )
{
    BOOST_TEST_MESSAGE("It is not necessary to test this method since it is just a getter");
}


// End - Test Suite: ArgumentTrace
ZTEST_SUITE_END()
