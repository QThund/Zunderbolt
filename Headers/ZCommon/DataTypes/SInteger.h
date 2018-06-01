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

#ifndef __SINTEGER__
#define __SINTEGER__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZCommon/CommonModuleDefinitions.h"


namespace z
{

/// <summary>
/// Helper class that offers functionality related to integer types.
/// </summary>
class Z_COMMON_MODULE_SYMBOLS SInteger
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// Maximum unsigned 8 bits integer value.
    /// </summary>
    static const u8_z MaxU8_Z;

    /// <summary>
    /// Maximum unsigned 16 bits integer value.
    /// </summary>
    static const u16_z MaxU16_Z;

    /// <summary>
    /// Maximum unsigned 32 bits integer value.
    /// </summary>
    static const u32_z MaxU32_Z;

    /// <summary>
    /// Maximum unsigned 64 bits integer value.
    /// </summary>
    static const u64_z MaxU64_Z;

    /// <summary>
    /// Maximum signed 8 bits integer positive value.
    /// </summary>
    static const i8_z MaxPositiveI8_Z;

    /// <summary>
    /// Maximum signed 8 bits integer positive value.
    /// </summary>
    static const i8_z MaxNegativeI8_Z;

    /// <summary>
    /// Maximum signed 16 bits integer positive value.
    /// </summary>
    static const i16_z MaxPositiveI16_Z;

    /// <summary>
    /// Maximum signed 16 bits integer positive value.
    /// </summary>
    static const i16_z MaxNegativeI16_Z;

    /// <summary>
    /// Maximum signed 32 bits integer positive value.
    /// </summary>
    static const i32_z MaxPositiveI32_Z;

    /// <summary>
    /// Maximum signed 32 bits integer positive value.
    /// </summary>
    static const i32_z MaxNegativeI32_Z;

    /// <summary>
    /// Maximum signed 64 bits integer positive value.
    /// </summary>
    static const i64_z MaxPositiveI64_Z;

    /// <summary>
    /// Maximum signed 64 bits integer positive value.
    /// </summary>
    static const i64_z MaxNegativeI64_Z;


    // CONSTRUCTORS
    // ---------------
private:

    // Default constructor (hidden).
    SInteger();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Returns the absolute value of an 8-bit integer value.
    /// </summary>
    /// <param name="nValue">[IN] An 8-bit integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as an 8-bit integer.
    /// </returns>
    static i8_z Abs(const i8_z nValue);

    /// <summary>
    /// Returns the absolute value of a short integer value.
    /// </summary>
    /// <param name="nValue">[IN] A short integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a short integer.
    /// </returns>
    static i16_z Abs(const i16_z nValue);

    /// <summary>
    /// Returns the absolute value of an integer value.
    /// </summary>
    /// <param name="nValue">[IN] An integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as an integer.
    /// </returns>
    static i32_z Abs(const i32_z nValue);

    /// <summary>
    /// Returns the absolute value of a long integer value.
    /// </summary>
    /// <param name="nValue">[IN] A long integer value to extract its absolute value.</param>
    /// <returns>
    /// The absolute value, expressed as a long integer.
    /// </returns>
    static i64_z Abs(const i64_z nValue);

    /// <summary>
    /// Inverts the order of bytes which compound an integer number and returns the result as output parameter.
    /// </summary>
    /// <remarks>
    /// A 32-bits integer number whose value equals to 0xAABBCCDD will be transformed to 0xDDCCBBAA, for example.
    /// </remarks>
    /// <typeparam name="IntegerT">The integral type passed as argument.</typeparam>
    /// <param name="nValue">[IN] The value whose bytes are to be swapped.</param>
    /// <returns>
    /// The transformed value.
    /// </returns>
    template<typename IntegerT>
    static IntegerT SwapEndianess(const IntegerT nValue)
    {
        const unsigned int INTEGER_SIZE = sizeof(IntegerT);

        // Ambiguous type to treat the same bit strip as byte array and integer types
        // Note: The type change is not immediate, it has memory reading/writing cost
        union IntegerOrBytesUnion
        {
            IntegerT _integer;
            u8_z     _bytes[INTEGER_SIZE];
        };

        IntegerOrBytesUnion srcValue;
        srcValue._integer = nValue;

        IntegerOrBytesUnion swappedValue;

        // Integer's bytes are copied in inverse order to the output float
        for(unsigned int i = 0, j = INTEGER_SIZE - 1; i < INTEGER_SIZE; ++i, --j)
            swappedValue._bytes[i] = srcValue._bytes[j];

        return swappedValue._integer;
    }
    
};

} // namespace z

#endif // __SINTEGER__
