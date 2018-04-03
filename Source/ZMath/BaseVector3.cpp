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

#include "ZMath/BaseVector3.h"

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

BaseVector3::BaseVector3() : x(SFloat::_0), y(SFloat::_0), z(SFloat::_0)
{
}

BaseVector3::BaseVector3(const BaseVector3 &vVector)
{
    this->x = vVector.x;
    this->y = vVector.y;
    this->z = vVector.z;
}

BaseVector3::BaseVector3(const float_z fValueX, const float_z fValueY, const float_z fValueZ) :
                                x(fValueX), y(fValueY), z(fValueZ)
{
}

BaseVector3::BaseVector3(const float_z fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll)
{
}

BaseVector3::BaseVector3(const float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    // Assignments
    this->x = arValues[0];
    this->y = arValues[1];
    this->z = arValues[2];
}

BaseVector3::BaseVector3(const vf32_z value)
{
    float_z fAux;

    SVF32::Unpack(value, this->x, this->y, this->z, fAux);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseVector3::operator==(const BaseVector3 &vVector) const
{
    return ( SFloat::AreEqual(vVector.x, this->x) && SFloat::AreEqual(vVector.y, this->y) && SFloat::AreEqual(vVector.z, this->z) );
}

bool BaseVector3::operator!=(const BaseVector3 &vVector) const
{
    return !(*this == vVector);
}

} // namespace z
