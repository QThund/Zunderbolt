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

#include "ZMath/BasePlane.h"

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

BasePlane::BasePlane() : a(SFloat::_0), b(SFloat::_0), c(SFloat::_0), d(SFloat::_0)
{
}

BasePlane::BasePlane(const BasePlane &plane)
{
    this->a = plane.a;
    this->b = plane.b;
    this->c = plane.c;
    this->d = plane.d;
}

BasePlane::BasePlane(const float_z fValueA, const float_z fValueB, const float_z fValueC, const float_z fValueD) :
                        a(fValueA), b(fValueB), c(fValueC), d(fValueD)
{
}

BasePlane::BasePlane(const float_z fValueAll) : a(fValueAll), b(fValueAll), c(fValueAll), d(fValueAll)
{
}

BasePlane::BasePlane(const float_z* arValues)
{
    // Null pointer checkout
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    // Assignments
    this->a = arValues[0];
    this->b = arValues[1];
    this->c = arValues[2];
    this->d = arValues[3];
}

BasePlane::BasePlane(const vf32_z value)
{
    SVF32::Unpack(value, this->a, this->b, this->c, this->d);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BasePlane::operator==(const BasePlane &plane) const
{
    return ( SFloat::AreEqual(plane.a, this->a) && SFloat::AreEqual(plane.b, this->b) &&
                SFloat::AreEqual(plane.c, this->c) && SFloat::AreEqual(plane.d, this->d) );
}

bool BasePlane::operator!=(const BasePlane &plane) const
{
    return !(*this == plane);
}

} // namespace z
