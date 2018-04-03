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

#ifndef __SANGLE__
#define __SANGLE__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// Helper class that offers functionality related to angles (radians and degrees).
/// </summary>
class Z_LAYER_MATH_SYMBOLS SAngle
{
    // CONSTANTS
    // ---------------
public:

    /// <summary>
    /// 45 degrees angle.
    /// </summary>
    static const float_z _45;

    /// <summary>
    /// 90 degrees angle.
    /// </summary>
    static const float_z _90;

    /// <summary>
    /// 180 degrees angle.
    /// </summary>
    static const float_z _180;

    /// <summary>
    /// 15 degrees angle.
    /// </summary>
    static const float_z _15;

    /// <summary>
    /// 30 degrees angle.
    /// </summary>
    static const float_z _30;

    /// <summary>
    /// 60 degrees angle.
    /// </summary>
    static const float_z _60;

    /// <summary>
    /// 270 degrees angle.
    /// </summary>
    static const float_z _270;

    /// <summary>
    /// 360 degrees angle.
    /// </summary>
    static const float_z _360;

    /// <summary>
    /// Half Pi radians angle (\f$ \frac{\pi}{2} \f$).
    /// </summary>
    static const float_z _HalfPi;

    /// <summary>
    /// A quarter of Pi radians angle (\f$ \frac{\pi}{4} \f$).
    /// </summary>
    static const float_z _QuarterPi;

    /// <summary>
    /// Third part of Pi radians angle (\f$ \frac{\pi}{3} \f$).
    /// </summary>
    static const float_z _ThirdPi;

    /// <summary>
    /// 2 Pi radians angle (\f$ 2\pi \f$).
    /// </summary>
    static const float_z _2Pi;

    /// <summary>
    /// Pi radians angle (\f$ \pi \f$).
    /// </summary>
    static const float_z _Pi;

    /// <summary>
    /// 3 halfs of Pi radians angle (\f$ \frac{3\pi}{2} \f$).
    /// </summary>
    static const float_z _3HalfsPi;

    /// <summary>
    /// Defines how many degrees are equivalent to 1 radian, and how much accurate is that value.
    /// </summary>
    static const float_z DegreesPerRadian;

    /// <summary>
    /// Defines how many radians are equivalent to 1 degree, and how much accurate is that value.
    /// </summary>
    static const float_z RadiansPerDegree;


    // CONSTRUCTORS
    // ---------------
private:

    // <summary>
    // Default constructor (hidden).
    // </summary>
    SAngle();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Computes the conversion from a value expressed in degrees to its equivalent in radians.
    /// </summary>
    /// <param name="fDegrees">[IN] The angle measured in degrees.</param>
    /// <returns>
    /// The same angle converted to radians.
    /// </returns>
    static float_z DegreesToRadians(const float_z fDegrees);

    /// <summary>
    /// Computes the conversion from a value expressed in radians to its equivalent in degrees.
    /// </summary>
    /// <param name="fRadians">[IN] The angle measured in radians.</param>
    /// <returns>
    /// The same angle converted to degrees.
    /// </returns>
    static float_z RadiansToDegrees(const float_z fRadians);

    /// <summary>
    /// Truncates an angle which describes more than one revolution.
    /// </summary>
    /// <remarks>
    /// If the angle value is greater than one revolution positive angle or lower than one revolution negative angle, then it will be adjusted to remain into that interval.
    /// </remarks>
    /// <param name="fAngle">[IN] The original angle value</param>
    /// <returns>
    /// The truncated angle value.
    /// </returns>
    static float_z Truncate(const float_z fAngle);

    /// <summary>
    /// Counts how many revolutions are represented by an angle, including fractions.
    /// </summary>
    /// <param name="fAngle">[IN] The angle value.</param>
    /// <returns>
    /// The number of revolutions (partial and complete).
    /// </returns>
    static float_z CountRevolutions(const float_z fAngle);

    /// <summary>
    /// Counts how many revolutions are represented by an angle, ignoring fractions.
    /// </summary>
    /// <param name="fAngle">[IN] The angle value.</param>
    /// <returns>
    /// The number of revolutions (only complete).
    /// </returns>
    static float_z CountCompleteRevolutions(const float_z fAngle);
};

} // namespace z


#endif // __SANGLE__
