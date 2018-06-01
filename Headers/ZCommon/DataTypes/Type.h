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

#ifndef __TYPE__
#define __TYPE__

#include "ZCommon/CommonModuleDefinitions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/Assertions.h"

#ifdef Z_COMPILER_MSVC
    // This warning appears when instancing a template to create a data member and that template instance is not exported.
    // In this case, it is not important since the data member is not accessible.
    #pragma warning( disable : 4251 ) // http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#endif


namespace z
{

/// <summary>
/// Describes a data type.
/// </summary>
/// <remarks>
/// Type instances are intended to be unique for every class for which they are defined. Do not create
/// any instance unless you are defining a new class.<br/>
/// This class is immutable and it is not intended to be derived.
/// </remarks>
class Z_COMMON_MODULE_SYMBOLS Type
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor that receives the type's information.
    /// </summary>
    /// <param name="strName">[IN] The unqualified name of the type.</param>
    explicit Type(const string_z &strName);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator that checks if two instances are the same or not.
    /// </summary>
    /// <param name="type">[IN] The other instance to compare to.</param>
    /// <returns>
    /// True if both instances are equal (same memory address); False otherwise.
    /// </returns>
    bool operator==(const Type &type) const;

    /// <summary>
    /// Inequality operator that checks if two instances are different or not.
    /// </summary>
    /// <param name="type">[IN] The other instance to compare to.</param>
    /// <returns>
    /// True if instances are not equal (different memory address); False otherwise.
    /// </returns>
    bool operator!=(const Type &type) const;
    
    /// <summary>
    /// Obtains the type information of a given basic data type or string.
    /// </summary>
    /// <typeparam name="T">The type whose information is to be obtained. Recognized types are: void, bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
    /// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
    /// <returns>
    /// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
    /// </returns>
    template<class T>
    static const Type* FindType()
    {
       // This method will give an error always since it will be called 
       // with non basic data type. See template specializations below.
       Z_ASSERT_ERROR(false, "Error!: The type used as template parameter is not a basic data type.");
       return null_z;
    }
    
    /// <summary>
    /// Gets the type information of an object.
    /// </summary>
    /// <remarks>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
    /// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
    /// <param name="object">[IN] The object whose type information is to be retrieved.</param>
    /// <returns>
    /// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const Type* FindType(const T &object)
    {
        // See template specializations below.
        return null_z;
    }
    
    /// <summary>
    /// Gets the type information of an non-constant object provided as a pointer.
    /// </summary>
    /// <remarks>
    /// Note that it returns the pointed type, instead of treating the pointer-to-type as a type itself. The same applies for pointers-to-pointer.<br/>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: pointers to either void, bool, u8_z, u16_z, 
    /// u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z, vf32_z or string_z.</typeparam>
    /// <param name="pObject">[IN] A pointer to the object whose type information is to be retrieved. If it is null, the type information will be obtained anyway.</param>
    /// <returns>
    /// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const Type* FindType(T* pObject)
    {
        return Type::FindType(ccast_z(pObject, const T*));
    }
    
    /// <summary>
    /// Gets the type information of a constant object provided as a pointer.
    /// </summary>
    /// <remarks>
    /// Note that it returns the pointed type, instead of treating the pointer-to-type as a type itself. The same applies for pointers-to-pointer.<br/>
    /// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
    /// Instead, a null pointer will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: pointers to constant void, bool, u8_z, u16_z, 
    /// u32_z, u64_z, i8_z, i16_z, i32_z, i64_z, f32_z, f64_z, vf32_z or string_z.</typeparam>
    /// <param name="pObject">[IN] A pointer to the object whose type information is to be retrieved. If it is null, the type information will be obtained anyway.</param>
    /// <returns>
    /// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
    /// </returns>
    template<class T>
    static const Type* FindType(const T* pObject)
    {
        return Type::FindType(*pObject);
    }


    // PROPERTIES
    // ---------------
public:

    /// <summary>
    /// Gets the unqualified name of the type.
    /// </summary>
    /// <returns>
    /// The unqualified name of the type.
    /// </returns>
    const string_z& GetName() const;



    // ATTRIBUTES
    // ---------------
private:

    /// <summary>
    /// The unqualified name of the type.
    /// </summary>
    const string_z m_strName;
    
    /// <summary>
    /// Type instance for boolean type.
    /// </summary>
    static const Type* TYPE_INSTANCE_BOOL;

    /// <summary>
    /// Type instance for unsigned 8-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_U8;

    /// <summary>
    /// Type instance for signed 8-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_I8;

    /// <summary>
    /// Type instance for unsigned 16-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_U16;

    /// <summary>
    /// Type instance for signed 16-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_I16;

    /// <summary>
    /// Type instance for unsigned 32-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_U32;

    /// <summary>
    /// Type instance for signed 32-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_I32;

    /// <summary>
    /// Type instance for unsigned 64-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_U64;

    /// <summary>
    /// Type instance for signed 64-bits integer type.
    /// </summary>
    static const Type* TYPE_INSTANCE_I64;

    /// <summary>
    /// Type instance for 32-bits floating point number type.
    /// </summary>
    static const Type* TYPE_INSTANCE_F32;

    /// <summary>
    /// Type instance for 64-bits floating point number type.
    /// </summary>
    static const Type* TYPE_INSTANCE_F64;

    /// <summary>
    /// Type instance for 4 x 32-bits packed floating point numbers type.
    /// </summary>
    static const Type* TYPE_INSTANCE_VF32;
    
    /// <summary>
    /// Type instance for strings type.
    /// </summary>
    static const Type* TYPE_INSTANCE_STRING;
    
    /// <summary>
    /// Type instance for void type.
    /// </summary>
    static const Type* TYPE_INSTANCE_VOID;
};


// SPECIALIZATIONS
// ---------------

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<bool>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<u8_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<i8_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<u16_z>();
    
/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<i16_z>();
    
/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<u32_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<i32_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<u64_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<i64_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<f32_z>();

/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<f64_z>();
    
/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<vf32_z>();
    
/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<string_z>();
    
/// <summary>
/// Obtains the type information of a given basic data type or string.
/// </summary>
/// <typeparam name="T">The type whose information is to be obtained. Recognized types are: bool, u8_z, u16_z, u32_z, u64_z, i8_z, i16_z, i32_z, 
/// i64_z, f32_z, f64_z, vf32_z and string_z.</typeparam>
/// <returns>
/// A constant unique instance of Type. There is one instance for every type, which exists during the whole program's lifecycle. If the type is not recognized, it will return null.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType<void>();

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const bool &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const u8_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const u16_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const u32_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const u64_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const i8_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const i16_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const i32_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const i64_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const f32_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const f64_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const vf32_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const string_z &object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(void* object);

/// <summary>
/// Gets the type information of an object.
/// </summary>
/// <remarks>
/// No type information will be obtained for any type that does not belong to the list of recognized types (see next).
/// Instead, a null pointer will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance whose information is to be retrieved. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The object whose type information is to be retrieved.</param>
/// <returns>
/// A pointer to a unique instance of Type that contains information about the type. The pointer is null if the type is not recognized.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS const Type* Type::FindType(const void* object);


} // namespace z

#endif // __TYPE__
