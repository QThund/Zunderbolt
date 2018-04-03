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

#ifndef __SCOMPARATORDEFAULT__
#define __SCOMPARATORDEFAULT__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"

namespace z
{


/// <summary>
/// Implements functionality for comparing two objects of the same type.
/// </summary>
/// <remarks>
/// Type used as template parameter MUST implement both operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class SComparatorDefault
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SComparatorDefault();


    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// -1 in case left operand is lower than right operand; 0 if they are equal; +1 if left operand is greater than right operand.
    /// </returns>
    static i8_z Compare (const T &leftOperand, const T &rightOperand)
    {
        // Variables representing the three return values
        static const i8_z LEFT_IS_LOWER_THAN_RIGHT = -1;
        static const i8_z LEFT_IS_GREATER_THAN_RIGHT = 1;
        static const i8_z ARE_EUAL = 0;

        i8_z nResult = LEFT_IS_GREATER_THAN_RIGHT;

        if (leftOperand < rightOperand)
            nResult = LEFT_IS_LOWER_THAN_RIGHT;
        else if (leftOperand == rightOperand)
            nResult = ARE_EUAL;

        return nResult;
    }
};

} // namespace z

#endif // __SCOMPARATORDEFAULT__
