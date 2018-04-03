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

#include "ZCommon/DataTypes/SFloat.h"

#include <cmath>
#include "ZCommon/DataTypes/StringsDefinitions.h"

namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  CONSTANTS INITIALIZATION  |               ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

// Numbers
#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE

    const float_z SFloat::_0   = 0.0f;
    const float_z SFloat::_1   = 1.0f;
    const float_z SFloat::_2   = 2.0f;
    const float_z SFloat::_3   = 3.0f;
    const float_z SFloat::_4   = 4.0f;
    const float_z SFloat::_5   = 5.0f;
    const float_z SFloat::_6   = 6.0f;
    const float_z SFloat::_7   = 7.0f;
    const float_z SFloat::_8   = 8.0f;
    const float_z SFloat::_9   = 9.0f;
    const float_z SFloat::_10  = 10.0f;
    const float_z SFloat::_0_5 = 0.5f;
    const float_z SFloat::_0_25 = 0.25f;

#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE

    const float_z SFloat::_0   = 0.0;
    const float_z SFloat::_1   = 1.0;
    const float_z SFloat::_2   = 2.0;
    const float_z SFloat::_3   = 3.0;
    const float_z SFloat::_4   = 4.0;
    const float_z SFloat::_5   = 5.0;
    const float_z SFloat::_6   = 6.0;
    const float_z SFloat::_7   = 7.0;
    const float_z SFloat::_8   = 8.0;
    const float_z SFloat::_9   = 9.0;
    const float_z SFloat::_10  = 10.0;
    const float_z SFloat::_0_5 = 0.5;
    const float_z SFloat::_0_25 = 0.25;

#endif

// Epsilon / Tolerance
#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE

    const float_z SFloat::Epsilon = 1e-6f;

#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE

    const float_z SFloat::Epsilon = 1e-12;

#endif

// Max / Min constants
#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE

    const float_z SFloat::MaxFloat_Z = 3.4028234e+38f; // 2 ^ 128
    const float_z SFloat::MinFloat_Z = 1.7014118346046923173168730371588e-38f; // 2 ^ -127

#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE

    const float_z SFloat::MaxFloat_Z = 1.797693134862315e+308; // 2 ^ 1024
    const float_z SFloat::MinFloat_Z = 8.9884656743115795386465259539451e-307; // 2 ^ -1023

#endif

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool SFloat::IsNaN(const float_z fValue)
{
    // [REVIEW] Thund: Boost provides functions to check this
    return fValue != fValue;
}

bool SFloat::IsInfinite(const float_z fValue)
{
    // [REVIEW] Thund: Boost provides functions to check this
    return SFloat::IsLessThan(fValue, -SFloat::MaxFloat_Z) || SFloat::IsGreaterThan(fValue, SFloat::MaxFloat_Z);
}

bool SFloat::IsNanOrInfinite(const float_z fValue)
{
    return SFloat::IsNaN(fValue) || SFloat::IsInfinite(fValue);
}

bool SFloat::AreEqual(const float_z fValueA, const float_z fValueB)
{
    return SFloat::Abs(fValueA - fValueB) <= SFloat::Epsilon;
}

bool SFloat::AreEqual(const float_z fValueA, const float_z fValueB, const float_z fTolerance)
{
    // The tolerance provided must be equal to or greater than the system tolerance. If the tolerance is too small it could become useless.
    Z_ASSERT_WARNING(fTolerance >= SFloat::Epsilon, "The tolerance provided must be equal to or greater than the system tolerance. If the tolerance is too small it could become useless");

    return SFloat::Abs(fValueA - fValueB) <= fTolerance;
}

bool SFloat::AreNotEqual(const float_z fValueA, const float_z fValueB)
{
    return SFloat::Abs(fValueA - fValueB) > SFloat::Epsilon;
}

bool SFloat::AreNotEqual(const float_z fValueA, const float_z fValueB, const float_z fTolerance)
{
    return SFloat::Abs(fValueA - fValueB) > fTolerance;
}

bool SFloat::IsGreaterThan(const float_z fGreaterValue, const float_z fReferenceValue)
{
    // If subtraction result is positive, and is greater than Epsilon (are different numbers), the value is greater
    return (fGreaterValue - fReferenceValue) > SFloat::Epsilon;
}

bool SFloat::IsGreaterThan(const float_z fGreaterValue, const float_z fReferenceValue, const float_z fTolerance)
{
    // If subtraction result is positive, and is greater than Epsilon (are different numbers), the value is greater
    return (fGreaterValue - fReferenceValue) > fTolerance;
}

bool SFloat::IsLessThan(const float_z fLowerValue, const float_z fReferenceValue)
{
    // If subtraction result is negative, and is lower than Epsilon (are different numbers), the value is lower
    return (fLowerValue - fReferenceValue) < -SFloat::Epsilon;
}

bool SFloat::IsLessThan(const float_z fLowerValue, const float_z fReferenceValue, const float_z fTolerance)
{
    // If subtraction result is negative, and is lower than Epsilon (are different numbers), the value is lower
    return (fLowerValue - fReferenceValue) < -fTolerance;
}

bool SFloat::IsGreaterOrEquals(const float_z fGreaterOrEqualsValue, const float_z fReferenceValue)
{
    // If subtraction is greater or equals to -Epsilon, the value is greater or equals
    return (fGreaterOrEqualsValue - fReferenceValue) >= -SFloat::Epsilon;
}

bool SFloat::IsGreaterOrEquals(const float_z fGreaterOrEqualsValue, const float_z fReferenceValue, const float_z fTolerance)
{
    // If subtraction is greater or equals to -Epsilon, the value is greater or equals
    return (fGreaterOrEqualsValue - fReferenceValue) >= -fTolerance;
}

bool SFloat::IsLessOrEquals(const float_z fLessOrEqualsValue, const float_z fReferenceValue)
{
    // If subtraction is lower or equals to Epsilon, the value is lower or equals
    return (fLessOrEqualsValue - fReferenceValue) <= SFloat::Epsilon;
}

bool SFloat::IsLessOrEquals(const float_z fLessOrEqualsValue, const float_z fReferenceValue, const float_z fTolerance)
{
    // If subtraction is lower or equals to Epsilon, the value is lower or equals
    return (fLessOrEqualsValue - fReferenceValue) <= fTolerance;
}

bool SFloat::IsZero(const float_z fValue)
{
    return SFloat::AreEqual(fValue, SFloat::_0);
}

bool SFloat::IsZero(const float_z fValue, const float_z fTolerance)
{
    return SFloat::AreEqual(fValue, SFloat::_0, fTolerance);
}

bool SFloat::IsNotZero(const float_z fValue)
{
    return SFloat::AreNotEqual(fValue, SFloat::_0);
}

bool SFloat::IsNotZero(const float_z fValue, const float_z fTolerance)
{
    return SFloat::AreNotEqual(fValue, SFloat::_0, fTolerance);
}

float_z SFloat::Truncate(const float_z fValue)
{
    return fValue >= SFloat::_0 ? floor(fValue) : ceil(fValue);
}

float_z SFloat::Clamp(const float_z fValue, const float_z fMin, const float_z fMax)
{
    const float_z CAMPLED_VALUE = (fValue > fMax) ?  fMax :
                                                        (fValue < fMin) ?  fMin :
                                                                        fValue;
    return CAMPLED_VALUE;
}

float_z SFloat::SwapEndianess(const float_z fValue)
{
    const unsigned int FLOAT_SIZE = sizeof(float_z);

    // Ambiguous type to treat the same bit strip as byte array and floating point types
    // Note: The type change is not immediate, it has memory reading/writing cost
    union FloatOrBytesUnion
    {
        float_z _float;
        u8_z    _bytes[FLOAT_SIZE];
    };

    FloatOrBytesUnion srcValue;
    srcValue._float = fValue;

    FloatOrBytesUnion swappedValue;

    // Float's bytes are copied in inverse order to the output float
    for(unsigned int i = 0, j = FLOAT_SIZE - 1; i < FLOAT_SIZE; ++i, --j)
        swappedValue._bytes[i] = srcValue._bytes[j];

    return swappedValue._float;
}

bool SFloat::IsNegative(const float_z fValue)
{
    return SFloat::IsLessThan(fValue, SFloat::_0);
}

bool SFloat::IsPositive(const float_z fValue)
{
    return SFloat::IsGreaterThan(fValue, SFloat::_0);
}

void SFloat::CopySign(const float_z fSignedValue, float_z &fValueToCopyTo)
{
    // Negative source & Negative target = Keep negative
    // Negative source & Positive target = Change sign
    // Positive source & Negative target = Change sign
    // Positive source & Positive target = Keep positive
    fValueToCopyTo = SFloat::IsNegative(fSignedValue)
                        ?
                        SFloat::IsNegative(fValueToCopyTo) ? fValueToCopyTo : -fValueToCopyTo
                        :
                        SFloat::IsNegative(fValueToCopyTo) ? -fValueToCopyTo : fValueToCopyTo;
}

float_z SFloat::Abs(const float_z fValue)
{
    #if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE

        return fabsf(fValue);

    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE

        return fabsl(fValue);

    #endif
}


} // namespace z
