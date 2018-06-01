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

#ifndef __BASEDUALQUATERNION__
#define __BASEDUALQUATERNION__

#include "ZMath/Quaternion.h"



namespace z
{

/// <summary>
/// Base class which implements the basic functionality of a dual quaternion.
/// </summary>
/// <remarks>
/// A dual quaternion is a complex number with two components, a non-dual component and a dual one, e.g. \f$ r + d\varepsilon \f$<br/>
/// Both components (r and d) of a dual quaternion are (regular) quaternions.<br/>
/// The dual unit, called epsilon (\f$ \varepsilon \f$), verifies \f$ \varepsilon^2=0 \f$. Then, a full quaternion looks like:
///<br/>
/// \f$ r_w + r_xi + r_yj + r_zk + (d_w + d_xi + d_yj + d_zk)\varepsilon\f$<br/>
///<br/>
/// We'll normally employ it to represent and execute rigid transformations, that is, transformations which involves
/// one rotation and one translation, without deforming the transformed solid (which acts as a rigid solid).<br/>
/// This class is experimental and therefore subject to changes.
/// </remarks>
class Z_MATH_MODULE_SYMBOLS BaseDualQuaternion
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseDualQuaternion();

    /// <summary>
    /// Copy constructor. Copies attributes from given dual quaternion.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion from which we want to create a copy in the resident dual quaternion.</param>
    BaseDualQuaternion(const BaseDualQuaternion &dualQuat);

    /// <summary>
    /// Constructor from two quaternions, one to initialize the non-dual part and another to do it with the dual part.
    /// </summary>
    /// <param name="qReal">[IN] Quaternion which is the non-dual part of the dual quaternion.</param>
    /// <param name="qDual">[IN] Quaternion which is the dual part of the dual quaternion.</param>
    BaseDualQuaternion(const BaseQuaternion &qReal, const BaseQuaternion &qDual);


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator==(const BaseDualQuaternion &dualQuat) const;

    /// <summary>
    /// Inequality operator. Compares two dual quaternions component by component.
    /// </summary>
    /// <param name="dualQuat">[IN] The dual quaternion to compare to.</param>
    /// <returns>
    /// If dual quaternions are not equals, then it returns true. Otherwise, it returns false.
    /// </returns>
    bool operator!=(const BaseDualQuaternion &dualQuat) const;


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Non-dual (real) part of the dual quaternion. Generally it represents the rotation applied.
    /// </summary>
    Quaternion r;

    /// <summary>
    /// Dual part of the dual quaternion. Generally it represents the traslation applied (modified by the rotation).
    /// </summary>
    Quaternion d;

};

} // namespace z


#endif // __BASEDUALQUATERNION__
