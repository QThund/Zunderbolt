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

#ifndef __CROSSPLATFORMBASICBASICTYPES__
#define __CROSSPLATFORMBASICBASICTYPES__

#include "ZCommon/InternalDefinitions.h"

#include <xmmintrin.h> // Includes __m128 definition.


namespace z
{

// --------------------------------------------------------------------------------------------------------
// Basic types: Defines all basic types used by some engine components, whose size is assured to be
// always the same.
// --------------------------------------------------------------------------------------------------------

#if defined(Z_OS_WINDOWS) && (Z_OS_WINDOWS == 32)
    #ifdef Z_COMPILER_MSVC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef __m128              vf32_z; // 4 x 32-bits packed floating point numbers

    #elif Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers

    #else
    
        #error Compiler not detected on Windows

    #endif

    typedef u32_z puint_z; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers

#elif defined(Z_OS_LINUX) && (Z_OS_LINUX == 32)
    #if Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers
    #else
    
        #error Compiler not detected on Linux

    #endif

    typedef u32_z puint_z; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers


#elif defined(Z_OS_MAC) && (Z_OS_MAC == 32)
    #if Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers
    #else
    
        #error Compiler not detected on Mac

    #endif

    typedef u32_z puint_z; // Unsigned integer types for pointer conversion (32 bits) common for ms and gcc compilers

#elif defined(Z_OS_WINDOWS) && (Z_OS_WINDOWS == 64)
    #ifdef Z_COMPILER_MSVC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef __m128              vf32_z; // 4 x 32-bits packed floating point numbers

    #elif Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers

    #else
    
        #error Compiler not detected on Windows

    #endif

    typedef u64_z puint_z; // Unsigned integer types for pointer conversion (64 bits) common for ms and gcc compilers

#elif defined(Z_OS_LINUX) && (Z_OS_LINUX == 64)
    #if Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers
    #else
    
        #error Compiler not detected on Linux

    #endif

    typedef u64_z puint_z; // Unsigned integer types for pointer conversion (64 bits) common for ms and gcc compilers


#elif defined(Z_OS_MAC) && (Z_OS_MAC == 64)
    #if Z_COMPILER_GCC
        typedef unsigned char       u8_z;   // Unsigned 8-bits integer
        typedef char                i8_z;   // Signed 8-bits integer
        typedef short unsigned int  u16_z;  // Unsigned 16-bits integer
        typedef short int           i16_z;  // Signed 16-bits integer
        typedef unsigned int        u32_z;  // Unsigned 32-bits integer
        typedef int                 i32_z;  // Signed 32-bits integer
        typedef unsigned long long  u64_z;  // Unsigned 64-bits integer
        typedef long long           i64_z;  // Signed 64-bits integer
        typedef float               f32_z;  // 32-bits floating point number
        typedef double              f64_z;  // 64-bits floating point number
        typedef union
        {
             __m128 m128;
             float m128_f32[4];
             u64_z m128_u64[2];
             i8_z  m128_i8[16];
             i16_z m128_i16[8];
             i32_z m128_i32[4];
             i64_z m128_i64[2];
             u8_z  m128_u8[16];
             u16_z m128_u16[8];
             u32_z m128_u32[4];
        } vf32_z;                           // 4 x 32-bits packed floating point numbers
    #else
    
        #error Compiler not detected on Mac

    #endif

    typedef u64_z puint_z; // Unsigned integer types for pointer conversion (64 bits) common for ms and gcc compilers

#else

    #error OS not detected
    
#endif

} // namespace z


#endif // __CROSSPLATFORMBASICBASICTYPES__
