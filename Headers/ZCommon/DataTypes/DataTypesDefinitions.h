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

#ifndef __DATATYPESDEFINITIONS__
#define __DATATYPESDEFINITIONS__

#include "ZCommon/DataTypes/CrossPlatformBasicTypes.h"
#include "ZCommon/Endianness.h"


namespace z
{
    
// --------------------------------------------------------------------------------------------------------
// Float type: Defines which floating point type will be used by the whole engine, according to the
// configured precission.
// --------------------------------------------------------------------------------------------------------

#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    typedef f32_z float_z;
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    typedef f64_z float_z;
#endif

// --------------------------------------------------------------------------------------------------------
// Float type size: Defines the floating point type size (in bytes), depending on the configured precission.
// The size depens on the operative system / compiler too.
// --------------------------------------------------------------------------------------------------------
#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #define Z_FLOAT_SIZE 4
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #define Z_FLOAT_SIZE 8
#endif

// --------------------------------------------------------------------------------------------------------
// Integer/Float type sizes equivalence: Defines the integer type whose size equals to the selected floating
// point type size.
// --------------------------------------------------------------------------------------------------------
#if defined(Z_OS_WINDOWS)
    #ifdef Z_COMPILER_MSVC
        #if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
            typedef i32_z int_for_float_z;
        #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
            typedef i64_z int_for_float_z;
        #else
            typedef i32_z int_for_float_z;
        #endif
    #elif Z_COMPILER_GCC
        #if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
            typedef i32_z int_for_float_z;
        #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
            typedef i64_z int_for_float_z;
        #else
            typedef i32_z int_for_float_z;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(Z_OS_LINUX)
    #if Z_COMPILER_GCC
        #if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
            typedef i32_z int_for_float_z;
        #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
            typedef i64_z int_for_float_z;
        #else
            typedef i32_z int_for_float_z;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#elif defined(Z_OS_MAC)
    #if Z_COMPILER_GCC
        #if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
            typedef i32_z int_for_float_z;
        #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
            typedef i64_z int_for_float_z;
        #else
            typedef i32_z int_for_float_z;
        #endif
    #else
        // [TODO] Thund: Test the system in another compiler and write the type sizes in that compiler
    #endif
#else
    // [TODO] Thund: Test the system in another platform and write the type sizes in that machine
    // Win64, Linux64
#endif


// --------------------------------------------------------------------------------------------------------
// 4-components vector mapping to 4x32 floats pack: Defines all basic types used by some engine components,
// whose size is assured to be always the same.
// These definitions are used into many math classes that receives a 4x32-bits floating points pack.
// --------------------------------------------------------------------------------------------------------
#define Z_VF32_FIRST_COMPONENT  this->x
#define Z_VF32_SECOND_COMPONENT this->y
#define Z_VF32_THIRD_COMPONENT  this->z
#define Z_VF32_FOURTH_COMPONENT this->w


// --------------------------------------------------------------------------------------------------------
// Enumeration's integer equivalent: Defines which is the equivalent integer type for enumeration types.
//                       Enumeration types used in Zunderbolt are guaranteed to be 32-bit unsigned integers,
//                       whatever the OS or the architecture it executes on.
// --------------------------------------------------------------------------------------------------------
typedef u32_z enum_int_z;


// --------------------------------------------------------------------------------------------------------
// Enumeration's limits: Concretes the maximum and minimum values an enumerated type can store.
//                       Enumeration types used in Zunderbolt are guaranteed to be 32-bit unsigned integers,
//                       whatever the OS or the architecture it executes on.
// --------------------------------------------------------------------------------------------------------
#define Z_ENUMERATION_MIN_VALUE 0x0
#define Z_ENUMERATION_MAX_VALUE 0xFFFFFFFF

} // namespace z


#endif // __DATATYPESDEFINITIONS__
