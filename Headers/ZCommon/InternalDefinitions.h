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

#ifndef __INTERNALDEFINITIONS__
#define __INTERNALDEFINITIONS__

#include "ZCommon/ExternalDefinitions.h"

// --------------------------------------------------------------------------------------------------------
// Version: Defines the Zunderbolt's current version.
// How to use it: Version format is Major version + Minor version + Revision ("##.####.####").
// --------------------------------------------------------------------------------------------------------
const int Z_VERSION_LENGTH = 13;
const char Z_VERSION[Z_VERSION_LENGTH] = "0.0.0";
const unsigned int Z_VERSION_MAJOR = 0;
const unsigned int Z_VERSION_MINOR = 0;
const unsigned int Z_VERSION_REVISION = 0;


// --------------------------------------------------------------------------------------------------------
// Null Pointer: Defines the value that identifies a null pointer, depending on the compiler.
// --------------------------------------------------------------------------------------------------------
#if defined(Z_COMPILER_MSVC)
    #if Z_COMPILER_MSVC >= 10
        #define null_z 0
    #else
        #define null_z 0
    #endif
#elif defined(Z_COMPILER_GCC)
    #define null_z 0
#endif

// --------------------------------------------------------------------------------------------------------
// Warning disabler: Defines the compiler proprocessor #pragma instruction that disables a warning.
//                   Note that it is not cross-platform since every compiler uses very different syntaxes.
// --------------------------------------------------------------------------------------------------------
#if defined(Z_COMPILER_MSVC)
    #if Z_COMPILER_MSVC >= 10
        #define Z_DISABLE_WARNING(number) warning (disable : number )
    #else
        #define Z_DISABLE_WARNING(number) warning (disable : number )
    #endif
#elif defined(Z_COMPILER_GCC)
    #define Z_DISABLE_WARNING(flag) GCC diagnostic ignored flag
#endif

// --------------------------------------------------------------------------------------------------------
// Dll exportation / importation aliases: Defines which compiler keywords will be used to export and import
// symbols when compiling as a DLL, depending on the operative system and the compiler.
// --------------------------------------------------------------------------------------------------------
#if defined(Z_OS_WINDOWS)
    #if defined(Z_COMPILER_MSVC)
        #define Z_EXPORT_SYMBOLS __declspec( dllexport )
        #define Z_EXPORT_SYMBOLS_EXTERN
        #define Z_IMPORT_SYMBOLS __declspec( dllimport )
        #define Z_IMPORT_SYMBOLS_EXTERN extern
    #elif defined(Z_COMPILER_GCC)
        #define Z_EXPORT_SYMBOLS __attribute__(( dllexport ))
        #define Z_EXPORT_SYMBOLS_EXTERN
        #define Z_IMPORT_SYMBOLS __attribute__(( dllimport ))
        #define Z_IMPORT_SYMBOLS_EXTERN extern
    #endif
#elif defined(Z_OS_LINUX)
    #if defined(Z_COMPILER_GCC)
        #define Z_EXPORT_SYMBOLS __attribute__ ((visibility ("default")))
        #define Z_EXPORT_SYMBOLS_EXTERN
        #define Z_IMPORT_SYMBOLS
        #define Z_IMPORT_SYMBOLS_EXTERN extern
    #endif
#elif defined(Z_OS_MAC)
    #if defined(Z_COMPILER_GCC)
        #define Z_EXPORT_SYMBOLS __attribute__ ((visibility ("default")))
        #define Z_EXPORT_SYMBOLS_EXTERN
        #define Z_IMPORT_SYMBOLS
        #define Z_IMPORT_SYMBOLS_EXTERN extern
    #endif
#endif


// --------------------------------------------------------------------------------------------------------
// Casting operators: Wrappers for every casting operator to make them shorter and configurable.
// -object: An instance of an object of a valid type.
// -type: A type to cast the instance to.
// --------------------------------------------------------------------------------------------------------
#define rcast_z(object, type) reinterpret_cast<type>(object)
#define scast_z(object, type) static_cast<type>(object)
#define dcast_z(object, type) dynamic_cast<type>(object)
#define ccast_z(object, type) const_cast<type>(object)


// --------------------------------------------------------------------------------------------------------
// Alignment calculation functions: Alias for every compiler's alignment calculation function.
// Note: There is a difference between GCC and MSVC functions, it is not possible to use objects in MSVC's version.
// -type: A type name.
// --------------------------------------------------------------------------------------------------------
#if   defined(Z_COMPILER_MSVC)
    #define alignof_z( type ) __alignof(type)
#elif defined(Z_COMPILER_GCC)
    #define alignof_z( type ) __alignof__(type)
#endif


// --------------------------------------------------------------------------------------------------------
// Calculates the offset, in bytes, that would be necessary to add to a memory address in order to align it to 
// the next aligned address.
// -startingPointer: The memory address from which to start searching.
// -alignment: The alignment of the searched memory address. I must be power of 2.
// --------------------------------------------------------------------------------------------------------
#define alignment_offset_z(startingPointer, alignment) ((alignment - (puint_z(startingPointer) & (alignment - 1))) & (alignment - 1))


// --------------------------------------------------------------------------------------------------------
// Calculates the next memory addres that fits into the alignment.
// -startingPointer: The memory address from which to start searching.
// -alignment: The alignment of the searched memory address. I must be power of 2.
// --------------------------------------------------------------------------------------------------------
#define align_z(startingPointer, alignment) (void*)(puint_z(startingPointer) + alignment_offset_z(startingPointer, alignment))


// --------------------------------------------------------------------------------------------------------
// Function signature printing definition: Alias for every compiler's function printing definition.
// --------------------------------------------------------------------------------------------------------
#if   defined(Z_COMPILER_MSVC)
    #define Z_PRINT_FUNCTION __FUNCSIG__
#elif defined(Z_COMPILER_GCC)
    #define Z_PRINT_FUNCTION __PRETTY_FUNCTION__
#endif


#endif // __INTERNALDEFINITIONS__
