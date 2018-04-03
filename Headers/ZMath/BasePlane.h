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

#ifndef __BASEPLANE__
#define __BASEPLANE__

#include "ZCommon/DataTypes/DataTypesDefinitions.h"
#include "ZMath/MathModuleDefinitions.h"



namespace z
{

/// <summary>
/// It represents the basic form of a 3D plane, defined by the equation \f$ ax + by + cz + d = 0 \f$.<br/>
/// </summary>
/// <remarks>
/// We can see that the vector (a, b, c) is normal to the plane, and d represents the sorthest distance from plane to the origin.
/// </remarks>
class Z_LAYER_MATH_SYMBOLS BasePlane
{
    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BasePlane();

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="plane">[IN] The plane from which we want to create a copy in the resident plane.</param>
    BasePlane(const BasePlane &plane);

    /// <summary>
    /// Constructor from a floating point value for each coefficient.
    /// </summary>
    /// <param name="fValueA">[IN] Floating point value for a coefficient.</param>
    /// <param name="fValueB">[IN] Floating point value for b coefficient.</param>
    /// <param name="fValueC">[IN] Floating point value for c coefficient.</param>
    /// <param name="fValueD">[IN] Floating point value for independent term d.</param>
    BasePlane(const float_z fValueA, const float_z fValueB, const float_z fValueC, const float_z fValueD);

    /// <summary>
    /// Constructor from a floating point value for all coefficients.
    /// </summary>
    /// <param name="fValueAll">[IN] Floating point value.</param>
    explicit BasePlane(const float_z fValueAll);

    /// <summary>
    /// Constructor from a pointer to a array of floating point values.
    /// </summary>
    /// <param name="arValues">[IN] Array of floating point values. It must have at least four elements. If the pointer is null, the behavior  
    /// is undefined.</param>
    explicit BasePlane(const float_z* arValues);

    /// <summary>
    /// Constructor from a 4x32 packed float value.
    /// </summary>
    /// <param name="value">[IN] 4x32 packed float containing the four components.<br/>
    /// The parse order: 1st value (a coefficient), 2nd value (b coefficient),
    /// 3rd value (c coefficient), 4th value (d independent term).</param>
    explicit BasePlane(const vf32_z value);


    // METHODS
    // --------------
public:

    /// <summary>
    /// Equality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be false, even if they are the same plane:
    /// <br/>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are the same, false otherwise.
    /// </returns>
    bool operator==(const BasePlane &plane) const;

    /// <summary>
    /// Inequality operator. Compares two planes.
    /// </summary>
    /// <remarks>
    /// Note that if any of the planes are not normalized, the result may be true, even if they are the same plane.
    /// <br/>
    /// \f$ x + y + z + 1 = 0\f$ and \f$ 2x + 2y + 2z + 2 = 0\f$ are the same plane but their components are different.
    /// </remarks>
    /// <param name="plane">[IN] Plane with which to compare.</param>
    /// <returns>
    /// True if planes are not the same, false otherwise.
    /// </returns>
    bool operator!=(const BasePlane &plane) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// X coefficient of the plane equation.
    /// </summary>
    float_z a;

    /// <summary>
    /// Y coefficient of the plane equation.
    /// </summary>
    float_z b;

    /// <summary>
    /// Z coefficient of the plane equation.
    /// </summary>
    float_z c;

    /// <summary>
    /// Independent term of the plane equation.
    /// </summary>
    float_z d;
};

} // namespace z


#endif // __BASEPLANE__
