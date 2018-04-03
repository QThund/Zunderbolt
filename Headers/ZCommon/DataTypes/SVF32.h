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

#ifndef __SVF32__
#define __SVF32__

#include "ZCommon/DataTypes/SFloat.h"



namespace z
{

/// <summary>
/// Helper class that offers functionality related to 4 x 32-bits floating point variables packs.
/// </summary>
/// <remarks>
/// This kind of packs are used in SIMD operations.
/// </remarks>
class Z_LAYER_COMMON_SYMBOLS SVF32
{

    // CONSTRUCTORS
    // ---------------
private:

    /// <summary>
    /// Default constructor (hidden).
    /// </summary>
    SVF32();


    // METHODS
    // ---------------
public:
    // [TODO] Thund: Review this doc.
    /// <summary>
    /// Packs four input floating point variables into a 128-bits type.
    /// </summary>
    /// <remarks>
    /// The order of variables in the package must be read from left to right, this is:<br/>
    ///  | Fourth | Third | Second | First | position<br/>
    /// 128       96     64        32      0 bit<br/>
    /// This is endianess-independent.
    /// </remarks>
    /// <param name="fFirst">[IN] First value in the packet.</param>
    /// <param name="fSecond">[IN] Second value in the packet.</param>
    /// <param name="fThird">[IN] Third value in the packet.</param>
    /// <param name="fFourth">[IN] Fourth value in the packet.</param>
    /// <param name="pack">[OUT] The package containing four 32-bits floating point values.</param>
    static void Pack(const float_z fFirst, const float_z fSecond, const float_z fThird, const float_z fFourth, vf32_z &pack);

    /// <summary>
    /// Unpacks into four output floating point variables stored in a 128-bits type.
    /// </summary>
    /// <remarks>
    /// The order of variables in the package is read from left to right, this is:<br/>
    ///  | Fourth | Third | Second | First | position<br/>
    /// 128       96     64        32      0 bit<br/>
    /// This is endianess-independent.
    /// </remarks>
    /// <param name="pack">[IN] The package containing four 32-bits floating point values.</param>
    /// <param name="fFirst">[OUT] First value in the packet.</param>
    /// <param name="fSecond">[OUT] Second value in the packet.</param>
    /// <param name="fThird">[OUT] Third value in the packet.</param>
    /// <param name="fFourth">[OUT] Fourth value in the packet.</param>
    static void Unpack(const vf32_z pack, float_z &fFirst, float_z &fSecond, float_z &fThird, float_z &fFourth);

};

} // namespace z

#endif // __SVF32__
