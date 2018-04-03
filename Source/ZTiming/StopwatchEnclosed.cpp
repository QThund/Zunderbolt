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

#include "ZTiming/StopwatchEnclosed.h"

#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/MathDefinitions.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

StopwatchEnclosed::StopwatchEnclosed() : m_fTimeLapse(SFloat::_0),
                                           m_eBehavior(EStopwatchEnclosedBehavior::E_Clamped)
{
}

StopwatchEnclosed::StopwatchEnclosed(const TimeSpan &timeLapseLength, const EStopwatchEnclosedBehavior &eBehavior) : 
                                                                                                    m_fTimeLapse(0),
                                                                                                    m_eBehavior(eBehavior)
{
    this->SetTimeLapseLength(timeLapseLength);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

float_z StopwatchEnclosed::GetProgression() const
{
    Z_ASSERT_WARNING(m_fTimeLapse != SFloat::_0, "The time lapse's length has not been set yet.");

    float_z fResult = 0.0f;

    switch(m_eBehavior)
    {
    case EStopwatchEnclosedBehavior::E_Clamped:
        fResult = SFloat::Clamp(this->GetElapsedTimeAsFloat() / m_fTimeLapse, SFloat::_0, SFloat::_1);
        break;
    case EStopwatchEnclosedBehavior::E_Proportional:
        fResult = this->GetElapsedTimeAsFloat() / m_fTimeLapse;
        break;
    case EStopwatchEnclosedBehavior::E_Cyclic:
        fResult = fmod_z(this->GetElapsedTimeAsFloat() / m_fTimeLapse, SFloat::_1);
        break;
    default:
        break;
    }

    return fResult;
}

float_z StopwatchEnclosed::GetPercentage() const
{
    Z_ASSERT_WARNING(m_fTimeLapse != SFloat::_0, "The time lapse's length has not been set yet.");

    static const float_z ONE_HUNDRED = 100.0;
    float_z fResult = 0.0f;

    switch(m_eBehavior)
    {
    case EStopwatchEnclosedBehavior::E_Clamped:
        fResult = SFloat::Clamp(this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED, SFloat::_0, ONE_HUNDRED);
        break;
    case EStopwatchEnclosedBehavior::E_Proportional:
        fResult = this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED;
        break;
    case EStopwatchEnclosedBehavior::E_Cyclic:
        fResult = fmod_z(this->GetElapsedTimeAsFloat() / m_fTimeLapse * ONE_HUNDRED, ONE_HUNDRED);
        break;
    default:
        break;
    }

    return fResult;
}

    
//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void StopwatchEnclosed::SetTimeLapseLength(const TimeSpan &length)
{
    Z_ASSERT_WARNING(length.GetHundredsOfNanoseconds() > 0, "The input time lapse's length should be greater than zero.");

#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    m_fTimeLapse = scast_z(length.GetMilliseconds(), float_z);
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    static const float_z HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000.0;
    m_fTimeLapse = scast_z(length.GetHundredsOfNanoseconds(), float_z) / HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND;
#endif
}

TimeSpan StopwatchEnclosed::GetTimeLapseLength() const
{
    
#if Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_SIMPLE
    static const u64_z HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000ULL;
    return TimeSpan(scast_z(m_fTimeLapse, puint_z) * HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND);
#elif Z_CONFIG_PRECISION_DEFAULT == Z_CONFIG_PRECISION_DOUBLE
    static const float_z HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND = 10000.0;
    return TimeSpan(scast_z(m_fTimeLapse * HUNDREDS_OF_NANOSECONDS_IN_MILLISECOND, puint_z));
#endif
}

void StopwatchEnclosed::SetBehavior(const EStopwatchEnclosedBehavior &eBehavior)
{
    m_eBehavior = eBehavior;
}

EStopwatchEnclosedBehavior StopwatchEnclosed::GetBehavior() const
{
    return m_eBehavior;
}


} // namespace z
