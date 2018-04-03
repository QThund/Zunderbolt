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

#include "ZMath/BaseQuadrilateral.h"

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

BaseQuadrilateral::BaseQuadrilateral() : A(SFloat::_0), B(SFloat::_0), C(SFloat::_0), D(SFloat::_0)
{
}

BaseQuadrilateral::BaseQuadrilateral(const BaseQuadrilateral &quad) : A(quad.A), B(quad.B), C(quad.C), D(quad.D)
{
}

BaseQuadrilateral::BaseQuadrilateral(const Vector2 &vA, const Vector2 &vB,
                            const Vector2 &vC, const Vector2 &vD) :
                            A(vA), B(vB), C(vC), D(vD)
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

bool BaseQuadrilateral::operator==(const BaseQuadrilateral &quad) const
{
    return ( this->A == quad.A && this->B == quad.B && this->C == quad.C && this->D == quad.D );
}

bool BaseQuadrilateral::operator!=(const BaseQuadrilateral &quad) const
{
    return !(*this == quad);
}

} // namespace z
