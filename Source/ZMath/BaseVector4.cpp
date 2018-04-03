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

#include "ZMath/BaseVector4.h"

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

BaseVector4::BaseVector4() : x(SFloat::_0), y(SFloat::_0), z(SFloat::_0), w(SFloat::_0)
{
}

BaseVector4::BaseVector4(const BaseVector4 &vVector)
{
    this->x = vVector.x;
    this->y = vVector.y;
    this->z = vVector.z;
    this->w = vVector.w;
}

BaseVector4::BaseVector4(const float_z fValueX, const float_z fValueY, const float_z fValueZ, const float_z fValueW) :
                                x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
{
}

BaseVector4::BaseVector4(const float_z fValueAll) : x(fValueAll), y(fValueAll), z(fValueAll), w(fValueAll)
{
}

BaseVector4::BaseVector4(const float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "Input array must not be null");

    // Assignments
    x = arValues[0];
    y = arValues[1];
    z = arValues[2];
    w = arValues[3];
}

BaseVector4::BaseVector4(const vf32_z value)
{
    SVF32::Unpack(value, this->x, this->y, this->z, this->w);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseVector4::operator==(const BaseVector4 &vVector) const
{
    return SFloat::AreEqual(vVector.x, this->x) && SFloat::AreEqual(vVector.y, this->y) &&
            SFloat::AreEqual(vVector.z, this->z) && SFloat::AreEqual(vVector.w, this->w);
}

bool BaseVector4::operator!=(const BaseVector4 &vVector) const
{
    return !(*this == vVector);
}

} // namespace z
