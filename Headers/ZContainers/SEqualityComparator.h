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

#ifndef __SEQUALITYCOMPARATOR__
#define __SEQUALITYCOMPARATOR__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"

namespace z
{


/// <summary>
/// Implements functionality for checking if two objects are equal or not.
/// </summary>
/// <remarks>
/// Type used as template parameter MUST implement the equality operator ("==").
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class SEqualityComparator
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SEqualityComparator();


    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// 1 in case operads are different; 0 if they are equal.
    /// </returns>
    static i8_z Compare (const T &leftOperand, const T &rightOperand)
    {
        // Variables representing the three return values
        static const i8_z ARE_NOT_EUAL = 1;
        static const i8_z ARE_EUAL = 0;

        return leftOperand == rightOperand ? ARE_EUAL : 
                                             ARE_NOT_EUAL;
    }
};

} // namespace z

#endif // __SEQUALITYCOMPARATOR__
