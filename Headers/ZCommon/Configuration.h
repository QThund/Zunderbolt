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

#ifndef __ZUNDERBOLT_CONFIGURATION__
#define __ZUNDERBOLT_CONFIGURATION__

namespace z
{

// --------------------------------------------------------------------------------------------------------
// Precission: This block defines the engine's operations precission, this means, how accurate the 
// mathematical operations are. Take on account that more precission decreases performance.
// How to use it: Write a precission definition value as the default precission definition.
// --------------------------------------------------------------------------------------------------------
#define Z_CONFIG_PRECISION_SIMPLE     0x0 // Simple precission: A 32 bits size floating point type.
#define Z_CONFIG_PRECISION_DOUBLE     0x1 // Double precission: A large size (more than 32 bits) floating point type.

#define Z_CONFIG_PRECISION_DEFAULT Z_CONFIG_PRECISION_SIMPLE // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Angle Notation: Defines whether the entire engine will work using Degrees or Radians.
// How to use it: Write an angle notation definition value as the default angle notation definition.
// --------------------------------------------------------------------------------------------------------
#define Z_CONFIG_ANGLENOTATION_RADIANS 0x0 // Radians notation: Angles are represented using radians, from 0 to 2*Pi.
#define Z_CONFIG_ANGLENOTATION_DEGREES 0x1 // Degrees notation: Angles are represented using degrees, from 0º to 360º.

#define Z_CONFIG_ANGLENOTATION_DEFAULT Z_CONFIG_ANGLENOTATION_RADIANS // [Configurable]


// --------------------------------------------------------------------------------------------------------
// Character Set: Specifies the character set used throughout the engine. It can be ASCII: 8 bits 
// per character (using 7 bits, actually), limited to the English alphabet; or Unicode (UTF-16): 16/32-bits wide
// characters to represent all existent alphabets.
//
// How to use it: Write a character set value as the default character set definition.
// --------------------------------------------------------------------------------------------------------
#define Z_CONFIG_CHARACTERSET_ASCII 0x0   // ASCII
#define Z_CONFIG_CHARACTERSET_UNICODE 0x1 // Unicode

#define Z_CONFIG_CHARACTERSET_DEFAULT Z_CONFIG_CHARACTERSET_UNICODE // [Configurable]

    
// --------------------------------------------------------------------------------------------------------
// Asserts behavior: Specifies the behavior of assertions throughout the engine. Assertions can be disabled
// or be replaced by exceptions, for example.
//
// How to use it: Write a behavior value as the default definition.
// --------------------------------------------------------------------------------------------------------
#define Z_CONFIG_ASSERTSBEHAVIOR_ENABLED 0x0
#define Z_CONFIG_ASSERTSBEHAVIOR_DISABLED 0x1
#define Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS 0x2

#define Z_CONFIG_ASSERTSBEHAVIOR_DEFAULT Z_CONFIG_ASSERTSBEHAVIOR_THROWEXCEPTIONS // [Configurable]
    
// --------------------------------------------------------------------------------------------------------
// Asserts tracing behavior: Specifies whether failed assertions will be traced or not.
//
// How to use it: Write a behavior value as the default definition.
// --------------------------------------------------------------------------------------------------------
#define Z_CONFIG_ASSERTSTRACING_DISABLED 0x0
#define Z_CONFIG_ASSERTSTRACING_ENABLED  0x1

#define Z_CONFIG_ASSERTSTRACING_DEFAULT Z_CONFIG_ASSERTSTRACING_ENABLED // [Configurable]


} // namespace z

#endif // __ZUNDERBOLT_CONFIGURATION__
