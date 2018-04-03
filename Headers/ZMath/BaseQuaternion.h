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

#ifndef __BASEUATERNION__
#define __BASEUATERNION__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// It represents the basic form of a quaternion with its four components: x, y, z and w.
/// </summary>
class Z_LAYER_MATH_SYMBOLS BaseQuaternion
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseQuaternion();

    /// <summary>
    /// Copy constructor. Copies attributes from given quaternion.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion from which we want to create a copy in the resident quaternion.</param>
    BaseQuaternion(const BaseQuaternion &qQuat);

    /// <summary>
    /// Constructor that receives 4 values, one per quaternion's component.
    /// </summary>
    /// <param name="fValueX">[IN] X component value.</param>
    /// <param name="fValueY">[IN] Y component value.</param>
    /// <param name="fValueZ">[IN] Z component value.</param>
    /// <param name="fValueW">[IN] W component value.</param>
    BaseQuaternion(const float_z fValueX, const float_z fValueY, const float_z fValueZ, const float_z fValueW);

    /// <summary>
    /// Constructor that receives a pointer to a sequence of 4 contiguous values, one per quaternion's component.
    /// </summary>
    /// <param name="arValues">[IN] Array of 4 values. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit BaseQuaternion(const float_z* arValues);

    /// <summary>
    /// Constructor that receives four 32 bits floating point type, one per quaternion's component, packaged
    /// into a 128 bits structure.
    /// </summary>
    /// <remarks>
    /// The values order is: X, Y, Z and W.
    /// </remarks>
    /// <param name="value">[IN] A four 32 bits floating point types pack.</param>
    explicit BaseQuaternion(const vf32_z value);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two quaternions.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const BaseQuaternion &qQuat) const;

    /// <summary>
    /// Inequality operator. Compares two quaternions.
    /// </summary>
    /// <param name="qQuat">[IN] The quaternion to compare to.</param>
    /// <returns>
    /// If quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const BaseQuaternion &qQuat) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Quaternion's x component.
    /// </summary>
    float_z x;

    /// <summary>
    /// Quaternion's y component.
    /// </summary>
    float_z y;

    /// <summary>
    /// Quaternion's z component.
    /// </summary>
    float_z z;

    /// <summary>
    /// Quaternion's w component.
    /// </summary>
    float_z w;
};

} // namespace z


#endif // __BASEUATERNION__
