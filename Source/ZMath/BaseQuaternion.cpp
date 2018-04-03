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

#include "ZMath/BaseQuaternion.h"

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

BaseQuaternion::BaseQuaternion() : x(SFloat::_0), y(SFloat::_0), z(SFloat::_0), w(SFloat::_0)
{
}

BaseQuaternion::BaseQuaternion(const BaseQuaternion &qQuat)
{
    this->x = qQuat.x;
    this->y = qQuat.y;
    this->z = qQuat.z;
    this->w = qQuat.w;
}

BaseQuaternion::BaseQuaternion(const float_z fValueX, const float_z fValueY,
                                 const float_z fValueZ, const float_z fValueW) :
                                       x(fValueX), y(fValueY), z(fValueZ), w(fValueW)
{
}

BaseQuaternion::BaseQuaternion(const float_z* arValues)
{
    // [REVIEW] Thund: Should we put these constants in another place?
    static const int Z_X_INDEX_IN_FLOATTYPE_ARRAY = 0;
    static const int Z_Y_INDEX_IN_FLOATTYPE_ARRAY = 1;
    static const int Z_Z_INDEX_IN_FLOATTYPE_ARRAY = 2;
    static const int Z_W_INDEX_IN_FLOATTYPE_ARRAY = 3;

    Z_ASSERT_ERROR(arValues != null_z, "Input array must not be null");

    this->x = arValues[Z_X_INDEX_IN_FLOATTYPE_ARRAY];
    this->y = arValues[Z_Y_INDEX_IN_FLOATTYPE_ARRAY];
    this->z = arValues[Z_Z_INDEX_IN_FLOATTYPE_ARRAY];
    this->w = arValues[Z_W_INDEX_IN_FLOATTYPE_ARRAY];
}

BaseQuaternion::BaseQuaternion(const vf32_z value)
{
    // Quaternion's components are mapped into the 4x32 pack as configured (see DataTypesDefinitions.h for further information)
    SVF32::Unpack(value, Z_VF32_FIRST_COMPONENT, Z_VF32_SECOND_COMPONENT, Z_VF32_THIRD_COMPONENT, Z_VF32_FOURTH_COMPONENT);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseQuaternion::operator==(const BaseQuaternion &qQuat) const
{
    return   SFloat::AreEqual(this->x, qQuat.x) &&
                SFloat::AreEqual(this->y, qQuat.y) &&
                SFloat::AreEqual(this->z, qQuat.z) &&
                SFloat::AreEqual(this->w, qQuat.w);
}

bool BaseQuaternion::operator!=(const BaseQuaternion &qQuat) const
{
    return !(*this == qQuat);
}

} // namespace z
