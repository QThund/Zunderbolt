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

#include "ZContainers/SStringHashProvider.h"

#include "ZCommon/Assertions.h"


namespace z
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

puint_z SStringHashProvider::GenerateHashKey(const string_z &strInput, const puint_z uBucketsInTable)
{
    // See: http://www.burtleburtle.net/bob/hash/doobs.html

    Z_ASSERT_ERROR(uBucketsInTable > 0, "The input number of buckets must be greater than zero.");

    u32_z uHashKey = 0;

    const u16_z* arCharacters = strInput.GetInternalBuffer();
    const puint_z LENGTH = strInput.GetLength();

    for(puint_z i = 0; i < LENGTH; ++i)
    {
        uHashKey += arCharacters[i];
        uHashKey += (uHashKey << 10U);
        uHashKey ^= (uHashKey >> 6U);
    }

    uHashKey += (uHashKey << 3U);
    uHashKey ^= (uHashKey >> 11U);
    uHashKey += (uHashKey << 15U);

    return uHashKey % scast_z(uBucketsInTable, u32_z);
}


} // namespace z
