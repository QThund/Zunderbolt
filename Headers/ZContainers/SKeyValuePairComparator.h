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

#ifndef __SKEYVALUEPAIRCOMPARATOR__
#define __SKEYVALUEPAIRCOMPARATOR__

#include "ZCommon/CommonModuleDefinitions.h"

#include "ZContainers/KeyValuePair.h"
#include "ZContainers/SComparatorDefault.h"

namespace z
{

/// <summary>
/// Implements functionality for comparing two key-value pairs of the same type.
/// </summary>
/// <remarks>
/// If SComparatorDefault is used as key comparator, the type used as template parameter for the key MUST implement both operators "==" and "<".
/// </remarks>
/// <typeparam name="KeyT">The type of the key.</typeparam>
/// <typeparam name="ValueT">The type of the value.</typeparam>
/// <typeparam name="KeyComparatorT">The type of the comparator to be used to compare keys. It is SComparatorDefault<KeyT> by default.</typeparam>
template<class KeyT, class ValueT, class KeyComparatorT=SComparatorDefault<KeyT> >
class SKeyValuePairComparator
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SKeyValuePairComparator();


    // METHODS
    // ---------------
public:
    
    /// <summary>
    /// Compares two key-value pairs by their key.
    /// </summary>
    /// <param name="leftOperand">[IN] First operand to compare.</param>
    /// <param name="rightOperand">[IN] Second operand to compare.</param>
    /// <returns>
    /// -1 in case left operand is lower than right operand; 0 if they are equal; +1 if left operand is greater than right operand.
    /// </returns>
    static i8_z Compare(const KeyValuePair<KeyT, ValueT> &leftOperand, const KeyValuePair<KeyT, ValueT> &rightOperand)
    {
        return KeyComparatorT::Compare(leftOperand.GetKey(), rightOperand.GetKey());
    }

};

} // namespace z


#endif // __SKEYVALUEPAIRCOMPARATOR__
