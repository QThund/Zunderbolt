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

#ifndef __SANYTYPETOSTRINGCONVERTER__
#define __SANYTYPETOSTRINGCONVERTER__

#include "ZCommon/CommonModuleDefinitions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"


namespace z
{

/// <summary>
/// Provides utilities to convert any data type to its representation as string.
/// </summary>
class Z_COMMON_MODULE_SYMBOLS SAnyTypeToStringConverter
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SAnyTypeToStringConverter();
    

    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Converts an instance of any type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "Unknown type" followed by the memory address of the instance will be returned.
    /// </remarks>
    /// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
    /// <param name="object">[IN] The instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z Convert(const T &object)
    {
        // See template specializations below.
        static const string_z UNKNOWN_TYPE_PART1("<Unknown type at ");
        static const string_z UNKNOWN_TYPE_PART2(">");
        static const string_z HEXADECIMAL_PREFIX("0x");

        string_z strResult = UNKNOWN_TYPE_PART1;
        strResult.Append(HEXADECIMAL_PREFIX);
        strResult.Append(string_z::FromIntegerToHexadecimal(rcast_z(&object, puint_z)));
        strResult.Append(UNKNOWN_TYPE_PART2);

        return strResult;
    }
    
    /// <summary>
    /// Converts a pointer-to-non-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: int** --> "0x10AFB34D 0x90AFB11A 256".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "Unknown type" followed by the memory address of the instance will be returned after all the memory addresses.
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted. Recognized types are: pointers to non-constant basic data types, 
    /// pointers to non-constant string_z or pointers to already mentioned types.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z Convert(T* pObject)
    {
        return SAnyTypeToStringConverter::Convert(ccast_z(pObject, const T*));
    }
    
    /// <summary>
    /// Converts a pointer-to-constant-type to its corresponding representation as string.
    /// </summary>
    /// <remarks>
    /// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
    /// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
    /// then both will be dereferenced; this is the maximum number of dereferences supported. Example: int** --> "0x10AFB34D 0x90AFB11A 256".<br/>
    /// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
    /// Any type that does not belong to the list of recognized types (see next) will not be converted.
    /// Instead, a string containing the text "Unknown type" followed by the memory address of the instance will be returned after all the memory addresses.
    /// </remarks>
    /// <typeparam name="T">The type of the pointer to be converted. Recognized types are: pointers to constant basic data types, 
    /// pointers to constant string_z or pointers to already mentioned types.</typeparam>
    /// <param name="pObject">[IN] The pointer to the instance to be converted.</param>
    /// <returns>
    /// The string that contains the representation of the object.
    /// </returns>
    template<class T>
    static string_z Convert(const T* pObject)
    {
        static const string_z HEXADECIMAL_PREFIX("0x");
        static const string_z WHITESPACE(" ");
        static const string_z NULL_POINTER("<Null>");
        
        string_z strResult;

        if(pObject != null_z)
        {
            // Prints the memory address to which the pointer points
            strResult.Append(HEXADECIMAL_PREFIX);
            strResult.Append(string_z::FromIntegerToHexadecimal(rcast_z(pObject, puint_z)));
            strResult.Append(WHITESPACE);

            // It is a pointer to either a basic data type or an unknown type
            strResult.Append(SAnyTypeToStringConverter::Convert(*pObject));
        }
        else
        {
            // It is a null pointer
            strResult.Append(NULL_POINTER);
        }

        return strResult;
    }

};


// SPECIALIZATIONS
// ---------------

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const bool &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const u8_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const u16_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const u32_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const u64_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const i8_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const i16_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const i32_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const i64_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const f32_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const f64_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const vf32_z &object);

/// <summary>
/// Converts an instance of any type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "<Unknown>" will be returned.
/// </remarks>
/// <typeparam name="T">The type of the instance to be converted. Recognized types are: basic data types and string_z.</typeparam>
/// <param name="object">[IN] The instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const string_z &object);

/// <summary>
/// Converts a pointer-to-constant-type to its corresponding representation as string.
/// </summary>
/// <remarks>
/// The string will contain both the memory address contained in the pointer (hexadecimal number, using the suffix "0x") and 
/// the representation as a string of the instance it points to, in that order, separated with a white-space. If the pointer points to another pointer, 
/// then both will be dereferenced; this is the maximum number of dereferences supported. Example: int** --> "0x10AFB34D 0x90AFB11A 256".<br/>
/// If the pointer is null, the resultant string will only contain the text "<Null>".<br/>
/// Any type that does not belong to the list of recognized types (see next) will not be converted.
/// Instead, a string containing the text "Unknown type" followed by the memory address of the instance will be returned after all the memory addresses.
/// </remarks>
/// <typeparam name="T">The type of the pointer to be converted. Recognized types are: pointers to constant basic data types, 
/// pointers to constant string_z or pointers to already mentioned types.</typeparam>
/// <param name="object">[IN] The pointer to the instance to be converted.</param>
/// <returns>
/// The string that contains the representation of the object.
/// </returns>
template<>
Z_COMMON_MODULE_SYMBOLS string_z SAnyTypeToStringConverter::Convert(const void* object);


} // namespace z

#endif // __SANYTYPETOSTRINGCONVERTER__
