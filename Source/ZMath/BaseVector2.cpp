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

#include "ZMath/BaseVector2.h"

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"



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

BaseVector2::BaseVector2() : x(SFloat::_0), y(SFloat::_0)
{
}

BaseVector2::BaseVector2(const BaseVector2 &vVector)
{
    this->x = vVector.x;
    this->y = vVector.y;
}

BaseVector2::BaseVector2(const float_z fValueX, const float_z fValueY) : x(fValueX), y(fValueY)
{
}

BaseVector2::BaseVector2(const float_z fValueAll) : x(fValueAll), y(fValueAll)
{
}

BaseVector2::BaseVector2(const float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    // Assignments
    x = arValues[0];
    y = arValues[1];
}

BaseVector2::BaseVector2(const vf32_z value)
{
    float_z fAux;

    SVF32::Unpack(value, this->x, this->y, fAux, fAux);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseVector2::operator==(const BaseVector2 &vVector) const
{
    return ( SFloat::AreEqual(vVector.x, this->x) && SFloat::AreEqual(vVector.y, this->y) );
}

bool BaseVector2::operator!=(const BaseVector2 &vVector) const
{
    return !(*this == vVector);
}

} // namespace z
