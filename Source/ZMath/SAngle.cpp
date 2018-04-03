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

#include "ZMath/SAngle.h"

#include "ZMath/MathDefinitions.h"


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

#if   Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE

    const float_z SAngle::_15           = 15.0f;
    const float_z SAngle::_30           = 30.0f;
    const float_z SAngle::_45           = 45.0f;
    const float_z SAngle::_60           = 60.0f;
    const float_z SAngle::_90           = 90.0f;
    const float_z SAngle::_180          = 180.0f;
    const float_z SAngle::_270          = 270.0f;
    const float_z SAngle::_360          = 360.0f;
    const float_z SAngle::_HalfPi       = (float_z) (PI_Z * 0.5);
    const float_z SAngle::_QuarterPi    = (float_z) (PI_Z * 0.25);
    const float_z SAngle::_ThirdPi      = (float_z) (PI_Z / 3.0);
    const float_z SAngle::_2Pi          = (float_z) (PI_Z * 2.0);
    const float_z SAngle::_Pi           = PI_Z;
    const float_z SAngle::_3HalfsPi     = (float_z) (PI_Z * 1.5);

    const float_z SAngle::DegreesPerRadian  = (float_z) (180.0 / PI_Z);
    const float_z SAngle::RadiansPerDegree  = (float_z) (PI_Z / 180.0);

#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE

    const float_z SAngle::_15           = 15.0;
    const float_z SAngle::_30           = 30.0;
    const float_z SAngle::_45           = 45.0;
    const float_z SAngle::_60           = 60.0;
    const float_z SAngle::_90           = 90.0;
    const float_z SAngle::_180          = 180.0;
    const float_z SAngle::_270          = 270.0;
    const float_z SAngle::_360          = 360.0;
    const float_z SAngle::_HalfPi       = PI_Z * 0.5;
    const float_z SAngle::_ZuarterPi    = PI_Z * 0.25;
    const float_z SAngle::_ThirdPi      = PI_Z / 3.0;
    const float_z SAngle::_2Pi          = PI_Z * 2.0;
    const float_z SAngle::_Pi           = PI_Z;
    const float_z SAngle::_3HalfsPi     = PI_Z * 1.5;

    const float_z SAngle::DegreesPerRadian  = 180.0 / PI_Z;
    const float_z SAngle::RadiansPerDegree  = PI_Z / 180.0;

#endif


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |            METHODS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_z SAngle::DegreesToRadians(const float_z fDegrees)
{

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    // This workaround is necessary due to an unacceptable loss of precision
    return (float_z) (f64_z(fDegrees) * 4.0 * atan_z(1.0) / 180.0);
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    return fDegrees * SAngle::RadiansPerDegree;
#endif

}

float_z SAngle::RadiansToDegrees(const float_z fRadians)
{

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    // This workaround is necessary due to an unacceptable loss of precision
    return (float_z) (f64_z(fRadians) * 180.0 / (4.0 * atan_z(1.0)));
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    return fRadians * SAngle::DegreesPerRadian;
#endif

}

float_z SAngle::Truncate(const float_z fAngle)
{

#if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
    return fmod_z(fAngle, SAngle::_2Pi);  
#elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
    return fmod_z(fAngle, SAngle::_360);
#endif

}

float_z SAngle::CountRevolutions(const float_z fAngle)
{
    const float_z COMPLETE_REVOLUTION =
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
            SAngle::_2Pi;
        #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            SAngle::_360;
        #endif

    return fAngle / COMPLETE_REVOLUTION;
}

float_z SAngle::CountCompleteRevolutions(const float_z fAngle)
{
    const float_z COMPLETE_REVOLUTION =
        #if Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_RADIANS
            SAngle::_2Pi;
        #elif Z_CONFIG_ANGLENOTATION_DEFAULT == Z_CONFIG_ANGLENOTATION_DEGREES
            SAngle::_360;
        #endif

    return SFloat::Truncate(fAngle / COMPLETE_REVOLUTION);
}

} // namespace z
