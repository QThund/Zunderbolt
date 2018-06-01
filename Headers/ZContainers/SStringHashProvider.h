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

#ifndef __SSTRINGHASHPROVIDER__
#define __SSTRINGHASHPROVIDER__

#include "ZContainers/ContainersModuleDefinitions.h"

#include "ZCommon/DataTypes/StringsDefinitions.h"


namespace z
{

/// <summary>
/// Represents a hash provider that generates hash keys from strings.
/// </summary>
class Z_CONTAINERS_MODULE_SYMBOLS SStringHashProvider
{

    // CONSTRUCTORS
    // ---------------
private:

    // Hidden
    SStringHashProvider();


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Generates a hash key from a string.
    /// </summary>
    /// <remarks>
    /// It implements the Jenkins' one-at-a-time hash function, followed by the calculation of the remainder of dividing the result by the number of buckets.
    /// </remarks>
    /// <param name="strInput">[IN] A string value. It can be empty.</param>
    /// <param name="uBucketsInTable">[IN] The number of buckets in the table for which the hash key is to be calculated.</param>
    /// <returns>
    /// A hash key.
    /// </returns>
    static puint_z GenerateHashKey(const string_z &strInput, const puint_z uBucketsInTable);

};

} // namespace z


#endif // __SSTRINGHASHPROVIDER__
