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

#ifndef __MATHDEFINITIONS__
#define __MATHDEFINITIONS__

#include "ZCommon/Configuration.h"
#include "ZCommon/DataTypes/SFloat.h"
#include <math.h>


namespace z
{

// --------------------------------------------------------------------------------------------------------
// Trigonometric functions: Wrappers for all the trigonometric functions provided by the runtime libraries.
// --------------------------------------------------------------------------------------------------------
#define sin_z(fRadians)  sin(fRadians)
#define sinh_z(fRadians) sinh(fRadians)
#define cos_z(fRadians)  cos(fRadians)
#define cosh_z(fRadians) cosh(fRadians)
#define tan_z(fRadians)  tan(fRadians)
#define tanh_z(fRadians) tanh(fRadians)
#define asin_z(fRadians) asin(fRadians)
#define acos_z(fRadians) acos(fRadians)
#define atan_z(fRadians) atan(fRadians)
#define atan2_z(fY, fX)  atan2(fY, fX)

// --------------------------------------------------------------------------------------------------------
// Other mathematical functions: Wrappers for non-classified mathematic functions provided by the runtime libraries.
// --------------------------------------------------------------------------------------------------------
#define exp_z(fValue)   exp(fValue)
#define pow_z(fValue,   exponent) pow(fValue, exponent)
#define log_z(fValue)   log(fValue)
#define log10_z(fValue) log10(fValue)
#define sqrt_z(fValue)  sqrt(fValue)

#ifdef Z_COMPILER_MSVC
    #if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
        #define hypot_z(fX, fY) _hypotf(fX, fY)
    #elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
        #define hypot_z(fX, fY) _hypot(fX, fY)
    #endif
#elif defined(Z_COMPILER_GCC)
    #define hypot_z(fX, fY) hypot(fX, fY)
#endif

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    #define fmod_z(fX, fY) fmodf(fX, fY) // To improve the compatibility, we prefer fmodf to fmod overloaded version
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    #define fmod_z(fX, fY) fmod(fX, fY)
#endif

// --------------------------------------------------------------------------------------------------------
// Pi: Defines how much accurate the mathematical Pi value is.
// --------------------------------------------------------------------------------------------------------
const float_z PI_Z = (float_z) (4.0 * atan_z(1.0));

// --------------------------------------------------------------------------------------------------------
// 1/Pi: Defines how much accurate the mathematical Pi value is to calculate its inverse.
// --------------------------------------------------------------------------------------------------------
const float_z INVERSE_PI_Z = (float_z) (1.0 / 4.0 * atan_z(1.0));

} // namespace z


#endif // __MATHDEFINITIONS__
