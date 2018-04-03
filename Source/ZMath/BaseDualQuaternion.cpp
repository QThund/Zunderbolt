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

#include "ZMath/BaseDualQuaternion.h"

#include "ZCommon/DataTypes/SFloat.h"


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

BaseDualQuaternion::BaseDualQuaternion() : r(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0)),
                                           d(BaseQuaternion(SFloat::_0, SFloat::_0, SFloat::_0, SFloat::_0))
{
}

BaseDualQuaternion::BaseDualQuaternion(const BaseDualQuaternion &dualQuat)
{
    this->r.x = dualQuat.r.x;
    this->d.x = dualQuat.d.x;
    this->r.y = dualQuat.r.y;
    this->d.y = dualQuat.d.y;
    this->r.z = dualQuat.r.z;
    this->d.z = dualQuat.d.z;
    this->r.w = dualQuat.r.w;
    this->d.w = dualQuat.d.w;
}

BaseDualQuaternion::BaseDualQuaternion(const BaseQuaternion &qReal, const BaseQuaternion &qDual) : r(qReal), d(qDual)
{
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseDualQuaternion::operator==(const BaseDualQuaternion &dualQuat) const
{
    return this->r == dualQuat.r && this->d == dualQuat.d;
}

bool BaseDualQuaternion::operator!=(const BaseDualQuaternion &dualQuat) const
{
    return !(*this == dualQuat);
}



} // namespace z
