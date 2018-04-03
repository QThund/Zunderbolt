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

#include "ZMath/BaseMatrix2x2.h"

#include <memory>
#include <cstring>

#include "ZCommon/Assertions.h"
#include "ZCommon/DataTypes/StringsDefinitions.h"
#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"


namespace z
{


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################



//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

BaseMatrix2x2::BaseMatrix2x2()
{
    ij[0][0] = SFloat::_0;
    ij[0][1] = SFloat::_0;
    ij[1][0] = SFloat::_0;
    ij[1][1] = SFloat::_0;
}

BaseMatrix2x2::BaseMatrix2x2(const BaseMatrix2x2 &matrix)
{
    memcpy(this->ij, matrix.ij, sizeof(float_z) * 4);
}

BaseMatrix2x2::BaseMatrix2x2(const float_z fValueAll)
{
    ij[0][0] = ij[0][1] =
    ij[1][0] = ij[1][1] = fValueAll;
}

BaseMatrix2x2::BaseMatrix2x2(const float_z f00, const float_z f01, const float_z f10, const float_z f11)
{
    ij[0][0] = f00;
    ij[0][1] = f01;
    ij[1][0] = f10;
    ij[1][1] = f11;
}

/// <summary>
/// Constructor that receives a pointer to 4 floating point values.
/// </summary>
/// <remarks>
/// Keeps the convention rows x columns, so each chunck of 2 consecutive elements
/// corresponds to a row, where each element in the chunck is the column in the row.
/// </remarks>
/// <param name="arValues">[IN] A 4 length array of floating point values. If the pointer is null, the behavior  
/// is undefined.</param>
BaseMatrix2x2::BaseMatrix2x2(const float_z* arValues)
{
    Z_ASSERT_ERROR(arValues != null_z, "The input array must not be null");

    ij[0][0] = arValues[0];
    ij[0][1] = arValues[1];
    ij[1][0] = arValues[2];
    ij[1][1] = arValues[3];
}

/// <summary>
/// Constructor from one 4x32 floating point packed values. Each value contains an element of the matrix.<br/>
/// Each pack element is unpacked following the row x column convention.
/// </summary>
/// <param name="value">[IN] 4x32 values for the matrix.</param>
BaseMatrix2x2::BaseMatrix2x2(const vf32_z value)
{
    SVF32::Unpack(value, this->ij[0][0], this->ij[0][1], this->ij[1][0], this->ij[1][1]);
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool BaseMatrix2x2::operator==(const BaseMatrix2x2 &matrix) const
{
    return SFloat::AreEqual(this->ij[0][0], matrix.ij[0][0]) &&
            SFloat::AreEqual(this->ij[0][1], matrix.ij[0][1]) &&
            SFloat::AreEqual(this->ij[1][0], matrix.ij[1][0]) &&
            SFloat::AreEqual(this->ij[1][1], matrix.ij[1][1]);
}

bool BaseMatrix2x2::operator!=(const BaseMatrix2x2 &matrix) const
{
    return  !(*this == matrix);
}


} // namespace z
