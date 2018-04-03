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

#ifndef __SNOCOMPARATOR__
#define __SNOCOMPARATOR__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"

namespace z
{


/// <summary>
/// Provides an empty implementation of a comparator, intended to be used when a functionality requires a comparator type for elements that cannot be compared.
/// </summary>
/// <remarks>
/// Type used as template parameter MUST implement both operators "==" and "<".
/// </remarks>
/// <typeparam name="T">The type of the elements to compare.</typeparam>
template <class T>
class SQNoComparator
{
    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SQNoComparator();


    // METHODS
    // --------------
public:

    /// <summary>
    /// Compares two elements.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// Always zero.
    /// </returns>
    static i8_z Compare (const T &leftOperand, const T &rightOperand)
    {
        Z_ASSERT_ERROR(false, "Functions that perform comparisons must not be called when using SQNoComparator.");
        return 0;
    }
};

} // namespace z

#endif // __SNOCOMPARATOR__
