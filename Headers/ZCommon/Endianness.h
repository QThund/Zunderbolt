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

#ifndef __ENDIANNESS__
#define __ENDIANNESS__

#include "ZCommon/InternalDefinitions.h"

// Little-endian machine
#define Z_ENDIANNESS_LITTLEENDIAN 0x0

// Big-endian machine
#define Z_ENDIANNESS_BIGENDIAN 0x1

// --------------------------------------------------------------------------------------------------------
// Machine endianess: Defines the machine endianess, this means, which order does the hardware follow to 
// store and read bytes.
// --------------------------------------------------------------------------------------------------------
#if defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || defined(_M_ARM) || \
    (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)     || \
    (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN)                 || \
    defined(__LITTLE_ENDIAN__)                                                 || \
    defined(__ARMEL__)                                                         || \
    defined(__THUMBEL__)                                                       || \
    defined(__AARCH64EL__)                                                     || \
    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)

    #define Z_ENDIANNESS Z_ENDIANNESS_LITTLEENDIAN

#elif defined(_M_PPC)                                                      || \
      (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)  || \
      (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN)              || \
      defined(__BIG_ENDIAN__)                                              || \
      defined(__ARMEB__)                                                   || \
      defined(__THUMBEB__)                                                 || \
      defined(__AARCH64EB__)                                               || \
      defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)

    #define Z_ENDIANNESS Z_ENDIANNESS_BIGENDIAN

#else
    #error Endianness could not be detected for this machine
#endif

/// <summary>
/// Checks whether the host machine follows little-endian byte order.
/// </summary>
/// <returns>
/// True if the machine is little-endian; False otherwise.
/// </returns>
inline bool Z_IS_LITTLE_ENDIAN()
{
    static const int ONE = 1;
    return *((const char*)&ONE) == 1;
}

/// <summary>
/// Checks whether the host machine follows big-endian byte order.
/// </summary>
/// <returns>
/// True if the machine is big-endian; False otherwise.
/// </returns>
inline bool Z_IS_BIG_ENDIAN()
{
    static const int ONE = 1;
    return *((const char*)&ONE) == 0;
}

#endif // __ENDIANNESS__
