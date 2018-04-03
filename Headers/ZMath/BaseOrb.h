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

#ifndef __BASEORB__
#define __BASEORB__

#include "ZCommon/DataTypes/SFloat.h"
#include "ZCommon/DataTypes/SVF32.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Class which represents a orb in the space, defined by its center point and radius.
/// </summary>
/// <remarks>
/// Center point may be expressed as 2D or 3D point or vector, depending on the parameter of the template,
/// which may be 2D vector, 3D vector or 4D vector.<br/>
/// Radius is expressed as a floating point value.<br/>
/// Remember that a orb is the locus of points equidistant from a given one.
/// </remarks>
/// <typeparam name="VectorT">Allowed types: BaseVector2, BaseVector3, BaseVector4, Vector2, Vector3, Vector4.</typeparam>
template <class VectorT>
class BaseOrb
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseOrb() : Center(SFloat::_0), Radius(SFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="orb">[IN] The orb from which we want to create a copy in the resident orb.</param>
    BaseOrb(const BaseOrb &orb) : Center(orb.Center), Radius(orb.Radius)
    {
    }

    /// <summary>
    /// Constructor from a vector which defines center point and a floating point value which
    /// defines the radius of the orb.
    /// </summary>
    /// <param name="vCenter">[IN] Vector to define the center of the orb.</param>
    /// <param name="fRadius">[IN] Floating point value to define the radius of the orb.</param>
    BaseOrb(const VectorT &vCenter, const float_z fRadius) : Center(vCenter), Radius(fRadius)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are the same, false otherwise.
    /// </returns>
    bool operator== (const BaseOrb<VectorT> &orb) const
    {
        return this->Center == orb.Center && SFloat::AreEqual(this->Radius, orb.Radius);
    }

    /// <summary>
    /// Inequality operator. Compares two orbs.
    /// </summary>
    /// <param name="orb">[IN] Orb with which to compare.</param>
    /// <returns>
    /// True if orbs are not the same, false otherwise.
    /// </returns>
    bool operator!= (const BaseOrb<VectorT> &orb) const
    {
        return !(*this == orb);
    }


    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Vector which represents the center point of orb.
    /// </summary>
    VectorT Center;

    /// <summary>
    /// Floating point value representig the radius of the orb.
    /// </summary>
    float_z Radius;
};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_LAYER_MATH_SYMBOLS BaseOrb<Vector2>;
template class Z_LAYER_MATH_SYMBOLS BaseOrb<Vector3>;
template class Z_LAYER_MATH_SYMBOLS BaseOrb<Vector4>;

#endif // Z_MATH_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __BASEORB__

