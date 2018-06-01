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

#ifndef __BASERAY__
#define __BASERAY__

#include "ZCommon/DataTypes/SFloat.h"
#include "ZMath/Vector2.h"
#include "ZMath/Vector3.h"
#include "ZMath/Vector4.h"



namespace z
{

/// <summary>
/// Implements the funcionality of a ray, which is a vector located at a point.
/// </summary>
/// <typeparam name="VectorTOrigin">Allowed types: BaseVector2, BaseVector3, BaseVector4, Vector2, Vector3, Vector4.</typeparam>
/// <typeparam name="VectorTDirection">Allowed types: BaseVector2 (when VectorTOrigin is BaseVector2), BaseVector3 (when VectorTOrigin is BaseVector3 or BaseVector4), 
/// Vector2 (when VectorTOrigin is Vector2), Vector3 (when VectorTOrigin is Vector3 or Vector4).</typeparam>
template<class VectorTOrigin, class VectorTDirection>
class BaseRay
{

    // CONSTRUCTORS
    // ---------------
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    BaseRay() : Origin(SFloat::_0), Direction(SFloat::_0)
    {
    }

    /// <summary>
    /// Copy constructor.
    /// </summary>
    /// <param name="ray">[IN] The ray from which we want to create a copy in the resident ray.</param>
    BaseRay(const BaseRay &ray) : Origin(ray.Origin), Direction(ray.Direction)
    {
    }

    /// <summary>
    /// Constructor from a point and a vector.
    /// </summary>
    /// <remarks>
    /// The direction vector must be normalized to construct the ray properly.
    /// </remarks>
    /// <param name="vOrigin">[IN] Point where the vector is located.</param>
    /// <param name="vDirection">[IN] A vector which defines the direction of the ray.</param>
    BaseRay (const VectorTOrigin &vOrigin, const VectorTDirection &vDirection) :
                        Origin(vOrigin), Direction(vDirection)
    {
    }


    // METHODS
    // ---------------
public:

    /// <summary>
    /// Equality operator. Compares two rays.
    /// </summary>
    /// <remarks>
    /// If rays are not normalized, it may occur that 2 similar rays (but not exactly equal) are considered different.
    /// </remarks>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are the same, false otherwise.
    /// </returns>
    bool operator==(const BaseRay<VectorTOrigin, VectorTDirection> &ray) const
    {
        return ( this->Origin == ray.Origin && this->Direction == ray.Direction );
    }

    /// <summary>
    /// Inequality operator. Compares two rays.
    /// </summary>
    /// <remarks>
    /// If rays are not normalized, it may occur that 2 similar rays (but not exactly equal) are considered different.
    /// </remarks>
    /// <param name="ray">[IN] Ray with which to compare.</param>
    /// <returns>
    /// True if rays are not the same, false otherwise.
    /// </returns>
    bool operator!=(const BaseRay<VectorTOrigin, VectorTDirection> &ray) const
    {
        return !(*this == ray);
    }

    // ATTRIBUTES
    // ---------------
public:

    /// <summary>
    /// Point where the vector is located.
    /// </summary>
    VectorTOrigin Origin;

    /// <summary>
    /// Vector which defines the direction of the ray.
    /// </summary>
    VectorTDirection Direction;

};


// SPECIALIZATION EXPORTATIONS
// -----------------------------
#ifdef Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

template class Z_MATH_MODULE_SYMBOLS BaseRay<Vector2, Vector2>;
template class Z_MATH_MODULE_SYMBOLS BaseRay<Vector3, Vector3>;
template class Z_MATH_MODULE_SYMBOLS BaseRay<Vector4, Vector3>;

#endif // Z_MATH_MODULE_TEMPLATE_SPECIALIZATION_SYMBOLS

} // namespace z


#endif // __BASERAY__
