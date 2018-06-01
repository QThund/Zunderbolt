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

#ifndef __ALIGNMENT__
#define __ALIGNMENT__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZCommon/CommonModuleDefinitions.h"


namespace z
{

/// <summary>
/// Class which represents a memory alignment, that is, a number that is used to allocate memory at addresses that are power of it.
/// </summary>
/// <remarks>
/// Alignments must be always a power of 2.
/// </remarks>
class Z_COMMON_MODULE_SYMBOLS Alignment
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Constructor from a value.
    /// </summary>
    /// <param name="uAlignment">[IN] Unsigned integer value to define alignment. It MUST be a power of 2.</param>
    explicit Alignment(const puint_z uAlignment);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Conversion operator to unsigned integer.
    /// </summary>
    /// <returns>
    /// The alignment converted into an unsigned integer value.
    /// </returns>
    operator puint_z() const;


    // ATTRIBUTES
    // ---------------
protected:

    /// <summary>
    /// Value which represents the memory alignment, used to allocate memory at addresses that are power of it.
    /// </summary>
    /// <remarks>
    /// This value MUST be always a power of 2.
    /// </remarks>
    puint_z m_uAlignment;

};

} // namespace z


#endif // __ALIGNMENT__
